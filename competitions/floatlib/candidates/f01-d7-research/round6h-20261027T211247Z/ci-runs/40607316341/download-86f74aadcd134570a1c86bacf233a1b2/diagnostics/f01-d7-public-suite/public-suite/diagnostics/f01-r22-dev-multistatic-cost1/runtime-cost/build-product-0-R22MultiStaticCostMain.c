// Lean compiler output
// Module: R22MultiStaticCostMain
// Imports: public import Init public meta import Init public import BenchFull public import BenchSuite public import Submission
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
uint32_t lean_uint32_lor(uint32_t, uint32_t);
uint32_t lean_uint32_land(uint32_t, uint32_t);
uint8_t lean_uint64_dec_eq(uint64_t, uint64_t);
uint32_t lean_uint64_to_uint32(uint64_t);
uint32_t lp_competition_Submission_FastMul_mul(uint32_t, uint32_t);
uint32_t lean_uint32_shift_right(uint32_t, uint32_t);
uint8_t lean_uint32_dec_eq(uint32_t, uint32_t);
float lean_float32_mul(float, float);
uint8_t lean_float32_beq(float, float);
uint32_t lean_float32_to_bits(float);
float lean_float32_of_bits(uint32_t);
float lean_uint32_to_float32(uint32_t);
extern lean_object* lp_competition_R2W01b_scaleTable;
lean_object* lean_uint32_to_nat(uint32_t);
lean_object* lean_array_fget_borrowed(lean_object*, lean_object*);
uint32_t lean_uint32_sub(uint32_t, uint32_t);
uint8_t lean_uint32_dec_le(uint32_t, uint32_t);
uint8_t lean_uint32_dec_lt(uint32_t, uint32_t);
uint32_t lean_uint32_shift_left(uint32_t, uint32_t);
uint64_t lean_uint64_sub(uint64_t, uint64_t);
uint8_t lean_uint64_dec_lt(uint64_t, uint64_t);
uint64_t lean_uint64_add(uint64_t, uint64_t);
uint64_t lean_uint64_shift_right(uint64_t, uint64_t);
uint64_t lean_uint64_shift_left(uint64_t, uint64_t);
uint64_t lean_uint64_land(uint64_t, uint64_t);
uint64_t lean_uint64_mul(uint64_t, uint64_t);
uint8_t lean_uint64_dec_le(uint64_t, uint64_t);
uint64_t lean_uint32_to_uint64(uint32_t);
uint64_t lean_uint64_lor(uint64_t, uint64_t);
uint32_t lean_uint32_add(uint32_t, uint32_t);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(lean_object*, lean_object*);
uint32_t lean_uint32_of_nat(lean_object*);
uint32_t lean_uint32_xor(uint32_t, uint32_t);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(lean_object*, lean_object*);
float lean_float32_add(float, float);
lean_object* lp_competition_Submission_sum___boxed(lean_object*, lean_object*);
lean_object* lp_competition_Submission_bmm(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lp_competition_Bench_Suite_run(lean_object*, lean_object*, lean_object*, lean_object*);
float lean_uint64_to_float32(uint64_t);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word(lean_object*, lean_object*, lean_object*);
uint32_t lp_competition_Submission_R22OutlineMul_retainedMul(uint32_t, uint32_t);
lean_object* lean_io_getenv(lean_object*);
uint8_t l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(lean_object*, lean_object*);
lean_object* lp_competition_Submission_R22Resident16_guarded(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_ctor_object lp_competition_r22CostInlineOldMul___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*3 + 8, .m_other = 3, .m_tag = 0}, .m_objs = {((lean_object*)(((size_t)(8) << 1) | 1)),((lean_object*)(((size_t)(23) << 1) | 1)),((lean_object*)(((size_t)(127) << 1) | 1)),LEAN_SCALAR_PTR_LITERAL(0, 0, 0, 0, 0, 0, 0, 0)}};
static const lean_object* lp_competition_r22CostInlineOldMul___closed__0 = (const lean_object*)&lp_competition_r22CostInlineOldMul___closed__0_value;
LEAN_EXPORT uint32_t lp_competition_r22CostInlineOldMul(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_r22CostInlineOldMul___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_r22CostOutlinedMul(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_r22CostOutlinedMul___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_runControl___lam__0(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_runControl___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_runControl___lam__1(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_runControl___lam__1___boxed(lean_object*, lean_object*);
static const lean_closure_object lp_competition_runControl___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_runControl___lam__0___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runControl___closed__0 = (const lean_object*)&lp_competition_runControl___closed__0_value;
static const lean_closure_object lp_competition_runControl___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_runControl___lam__1___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runControl___closed__1 = (const lean_object*)&lp_competition_runControl___closed__1_value;
static const lean_closure_object lp_competition_runControl___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_sum___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runControl___closed__2 = (const lean_object*)&lp_competition_runControl___closed__2_value;
static const lean_closure_object lp_competition_runControl___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_bmm, .m_arity = 6, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runControl___closed__3 = (const lean_object*)&lp_competition_runControl___closed__3_value;
LEAN_EXPORT lean_object* lp_competition_runControl();
LEAN_EXPORT lean_object* lp_competition_runControl___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_runInlineOld___lam__1(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_runInlineOld___lam__1___boxed(lean_object*, lean_object*);
static const lean_closure_object lp_competition_runInlineOld___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_runInlineOld___lam__1___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runInlineOld___closed__0 = (const lean_object*)&lp_competition_runInlineOld___closed__0_value;
LEAN_EXPORT lean_object* lp_competition_runInlineOld();
LEAN_EXPORT lean_object* lp_competition_runInlineOld___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_runOutline___lam__1(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_runOutline___lam__1___boxed(lean_object*, lean_object*);
static const lean_closure_object lp_competition_runOutline___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_runOutline___lam__1___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runOutline___closed__0 = (const lean_object*)&lp_competition_runOutline___closed__0_value;
LEAN_EXPORT lean_object* lp_competition_runOutline();
LEAN_EXPORT lean_object* lp_competition_runOutline___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_r22CostNativeProductMul(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_r22CostNativeProductMul___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_runNativeProduct___lam__1(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_runNativeProduct___lam__1___boxed(lean_object*, lean_object*);
static const lean_closure_object lp_competition_runNativeProduct___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_runNativeProduct___lam__1___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runNativeProduct___closed__0 = (const lean_object*)&lp_competition_runNativeProduct___closed__0_value;
LEAN_EXPORT lean_object* lp_competition_runNativeProduct();
LEAN_EXPORT lean_object* lp_competition_runNativeProduct___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_runResident16___lam__1(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_runResident16___lam__1___boxed(lean_object*, lean_object*);
static const lean_closure_object lp_competition_runResident16___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_runResident16___lam__1___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runResident16___closed__0 = (const lean_object*)&lp_competition_runResident16___closed__0_value;
static const lean_closure_object lp_competition_runResident16___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_R22Resident16_guarded, .m_arity = 6, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runResident16___closed__1 = (const lean_object*)&lp_competition_runResident16___closed__1_value;
LEAN_EXPORT lean_object* lp_competition_runResident16();
LEAN_EXPORT lean_object* lp_competition_runResident16___boxed(lean_object*);
static const lean_string_object lp_competition_main___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 14, .m_capacity = 14, .m_length = 13, .m_data = "BENCH_VARIANT"};
static const lean_object* lp_competition_main___closed__0 = (const lean_object*)&lp_competition_main___closed__0_value;
static const lean_string_object lp_competition_main___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 8, .m_capacity = 8, .m_length = 7, .m_data = "control"};
static const lean_object* lp_competition_main___closed__1 = (const lean_object*)&lp_competition_main___closed__1_value;
static const lean_ctor_object lp_competition_main___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__1_value)}};
static const lean_object* lp_competition_main___closed__2 = (const lean_object*)&lp_competition_main___closed__2_value;
static const lean_string_object lp_competition_main___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 10, .m_capacity = 10, .m_length = 9, .m_data = "inlineOld"};
static const lean_object* lp_competition_main___closed__3 = (const lean_object*)&lp_competition_main___closed__3_value;
static const lean_ctor_object lp_competition_main___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__3_value)}};
static const lean_object* lp_competition_main___closed__4 = (const lean_object*)&lp_competition_main___closed__4_value;
static const lean_string_object lp_competition_main___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 8, .m_capacity = 8, .m_length = 7, .m_data = "outline"};
static const lean_object* lp_competition_main___closed__5 = (const lean_object*)&lp_competition_main___closed__5_value;
static const lean_ctor_object lp_competition_main___closed__6_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__5_value)}};
static const lean_object* lp_competition_main___closed__6 = (const lean_object*)&lp_competition_main___closed__6_value;
static const lean_string_object lp_competition_main___closed__7_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 11, .m_capacity = 11, .m_length = 10, .m_data = "nativeprod"};
static const lean_object* lp_competition_main___closed__7 = (const lean_object*)&lp_competition_main___closed__7_value;
static const lean_ctor_object lp_competition_main___closed__8_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__7_value)}};
static const lean_object* lp_competition_main___closed__8 = (const lean_object*)&lp_competition_main___closed__8_value;
static const lean_string_object lp_competition_main___closed__9_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 11, .m_capacity = 11, .m_length = 10, .m_data = "resident16"};
static const lean_object* lp_competition_main___closed__9 = (const lean_object*)&lp_competition_main___closed__9_value;
static const lean_ctor_object lp_competition_main___closed__10_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__9_value)}};
static const lean_object* lp_competition_main___closed__10 = (const lean_object*)&lp_competition_main___closed__10_value;
static const lean_string_object lp_competition_main___closed__11_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 77, .m_capacity = 77, .m_length = 76, .m_data = "BENCH_VARIANT must be control, inlineOld, outline, nativeprod, or resident16"};
static const lean_object* lp_competition_main___closed__11 = (const lean_object*)&lp_competition_main___closed__11_value;
static const lean_ctor_object lp_competition_main___closed__12_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_main___closed__11_value)}};
static const lean_object* lp_competition_main___closed__12 = (const lean_object*)&lp_competition_main___closed__12_value;
LEAN_EXPORT lean_object* _lean_main();
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_r22CostInlineOldMul(uint32_t v_x_6_, uint32_t v_y_7_){
_start:
{
uint32_t v___y_9_; uint32_t v___y_13_; uint32_t v___y_17_; uint32_t v___y_18_; uint32_t v___y_19_; uint64_t v___y_23_; uint8_t v___y_24_; uint32_t v___y_25_; uint64_t v___y_26_; uint32_t v___y_38_; uint32_t v___y_39_; uint32_t v___y_40_; uint64_t v___y_44_; uint8_t v___y_45_; uint32_t v___y_46_; uint64_t v___y_47_; uint8_t v___y_59_; uint8_t v___y_75_; uint8_t v___y_89_; uint8_t v___y_106_; float v___y_113_; float v___y_114_; float v___y_128_; uint8_t v___y_129_; float v___y_144_; uint32_t v___y_154_; uint32_t v___y_158_; uint32_t v___y_162_; uint32_t v___y_163_; uint32_t v___y_164_; uint64_t v___y_168_; uint8_t v___y_169_; uint32_t v___y_170_; uint64_t v___y_171_; uint32_t v___y_183_; uint32_t v___y_184_; uint32_t v___y_185_; uint8_t v___y_189_; uint32_t v___y_190_; uint64_t v___y_191_; uint64_t v___y_192_; uint8_t v___y_204_; uint8_t v___y_220_; uint8_t v___y_234_; uint8_t v___y_251_; float v___y_258_; float v___y_259_; float v___y_273_; uint8_t v___y_274_; float v___y_289_; uint32_t v___y_299_; uint32_t v___y_303_; uint32_t v___y_307_; uint32_t v___y_308_; uint32_t v___y_309_; uint32_t v___y_313_; uint8_t v___y_314_; uint64_t v___y_315_; uint64_t v___y_316_; uint32_t v___y_328_; uint32_t v___y_329_; uint32_t v___y_330_; uint64_t v___y_334_; uint32_t v___y_335_; uint8_t v___y_336_; uint64_t v___y_337_; uint8_t v___y_349_; uint8_t v___y_365_; uint8_t v___y_379_; uint8_t v___y_396_; float v___y_403_; float v___y_404_; float v___y_418_; uint8_t v___y_419_; float v___y_434_; uint32_t v___x_443_; uint32_t v___x_444_; uint8_t v___y_446_; uint8_t v___y_459_; uint8_t v___y_472_; uint32_t v___x_484_; uint32_t v___y_486_; uint32_t v___y_487_; uint32_t v___y_488_; uint32_t v___y_489_; uint32_t v___y_496_; uint8_t v___y_497_; uint32_t v___y_498_; uint32_t v___y_499_; uint64_t v___y_503_; uint64_t v___y_504_; uint32_t v___y_505_; uint8_t v___y_506_; uint64_t v___y_507_; uint8_t v___y_517_; uint64_t v___y_518_; uint64_t v___y_519_; uint8_t v___y_520_; uint32_t v___y_521_; uint64_t v___y_522_; uint64_t v___y_529_; uint64_t v___y_530_; uint32_t v___y_531_; uint8_t v___y_532_; uint64_t v___y_533_; uint64_t v___y_539_; uint64_t v___y_540_; uint64_t v___y_541_; uint8_t v___y_542_; uint32_t v___y_543_; uint64_t v___y_544_; uint64_t v___y_599_; uint64_t v___y_600_; uint64_t v___y_601_; uint64_t v___y_602_; uint32_t v___y_603_; uint8_t v___y_604_; uint64_t v___y_605_; uint64_t v___y_611_; uint64_t v___y_612_; uint64_t v___y_613_; uint64_t v___y_614_; uint64_t v___y_615_; uint64_t v___y_616_; uint8_t v___y_617_; uint32_t v___y_618_; uint64_t v___y_619_; uint64_t v___y_624_; uint64_t v___y_625_; uint64_t v___y_626_; uint64_t v___y_627_; uint32_t v___y_628_; uint8_t v___y_629_; uint64_t v___y_630_; uint64_t v___y_635_; uint64_t v___y_636_; uint64_t v___y_637_; uint64_t v___y_638_; uint64_t v___y_639_; uint64_t v___y_640_; uint8_t v___y_641_; uint32_t v___y_642_; uint64_t v___y_643_; uint64_t v___y_648_; uint64_t v___y_649_; uint64_t v___y_650_; uint64_t v___y_651_; uint32_t v___y_652_; uint8_t v___y_653_; uint64_t v___y_654_; uint64_t v___y_659_; uint64_t v___y_660_; uint64_t v___y_661_; uint64_t v___y_662_; uint64_t v___y_663_; uint64_t v___y_664_; uint8_t v___y_665_; uint32_t v___y_666_; uint64_t v___y_667_; uint64_t v___y_672_; uint64_t v___y_673_; uint64_t v___y_674_; uint32_t v___y_675_; uint8_t v___y_676_; uint64_t v___y_677_; uint64_t v___y_678_; uint64_t v___y_683_; uint64_t v___y_684_; uint64_t v___y_685_; uint64_t v___y_686_; uint64_t v___y_687_; uint64_t v___y_688_; uint8_t v___y_689_; uint32_t v___y_690_; uint64_t v___y_691_; uint64_t v___y_696_; uint64_t v___y_697_; uint64_t v___y_698_; uint64_t v___y_699_; uint32_t v___y_700_; uint8_t v___y_701_; uint64_t v___y_702_; uint64_t v___y_707_; uint64_t v___y_708_; uint64_t v___y_709_; uint64_t v___y_710_; uint8_t v___y_711_; uint32_t v___y_712_; uint64_t v___y_713_; uint64_t v___y_717_; uint64_t v___y_718_; uint32_t v___y_719_; uint8_t v___y_720_; uint64_t v___y_729_; uint64_t v___y_730_; uint8_t v___y_731_; uint32_t v___y_732_; uint64_t v___y_733_; uint64_t v___y_734_; uint32_t v___y_768_; uint32_t v___y_769_; uint32_t v___y_770_; uint32_t v___y_771_; uint32_t v___y_778_; uint8_t v___y_779_; uint32_t v___y_780_; uint32_t v___y_781_; uint64_t v___y_785_; uint64_t v___y_786_; uint8_t v___y_787_; uint32_t v___y_788_; uint64_t v___y_789_; uint8_t v___y_799_; uint64_t v___y_800_; uint64_t v___y_801_; uint8_t v___y_802_; uint32_t v___y_803_; uint64_t v___y_804_; uint64_t v___y_811_; uint64_t v___y_812_; uint8_t v___y_813_; uint32_t v___y_814_; uint64_t v___y_815_; uint64_t v___y_821_; uint64_t v___y_822_; uint64_t v___y_823_; uint8_t v___y_824_; uint32_t v___y_825_; uint64_t v___y_826_; uint64_t v___y_881_; uint64_t v___y_882_; uint64_t v___y_883_; uint64_t v___y_884_; uint8_t v___y_885_; uint32_t v___y_886_; uint64_t v___y_887_; uint64_t v___y_893_; uint64_t v___y_894_; uint64_t v___y_895_; uint64_t v___y_896_; uint64_t v___y_897_; uint8_t v___y_898_; uint64_t v___y_899_; uint32_t v___y_900_; uint64_t v___y_901_; uint64_t v___y_906_; uint64_t v___y_907_; uint64_t v___y_908_; uint64_t v___y_909_; uint8_t v___y_910_; uint32_t v___y_911_; uint64_t v___y_912_; uint64_t v___y_917_; uint64_t v___y_918_; uint64_t v___y_919_; uint64_t v___y_920_; uint64_t v___y_921_; uint64_t v___y_922_; uint8_t v___y_923_; uint32_t v___y_924_; uint64_t v___y_925_; uint64_t v___y_930_; uint64_t v___y_931_; uint64_t v___y_932_; uint64_t v___y_933_; uint8_t v___y_934_; uint32_t v___y_935_; uint64_t v___y_936_; uint64_t v___y_941_; uint64_t v___y_942_; uint64_t v___y_943_; uint64_t v___y_944_; uint64_t v___y_945_; uint64_t v___y_946_; uint8_t v___y_947_; uint32_t v___y_948_; uint64_t v___y_949_; uint64_t v___y_954_; uint64_t v___y_955_; uint64_t v___y_956_; uint64_t v___y_957_; uint8_t v___y_958_; uint32_t v___y_959_; uint64_t v___y_960_; uint64_t v___y_965_; uint64_t v___y_966_; uint64_t v___y_967_; uint64_t v___y_968_; uint64_t v___y_969_; uint8_t v___y_970_; uint32_t v___y_971_; uint64_t v___y_972_; uint64_t v___y_973_; uint64_t v___y_978_; uint64_t v___y_979_; uint64_t v___y_980_; uint64_t v___y_981_; uint8_t v___y_982_; uint32_t v___y_983_; uint64_t v___y_984_; uint64_t v___y_989_; uint64_t v___y_990_; uint64_t v___y_991_; uint64_t v___y_992_; uint8_t v___y_993_; uint32_t v___y_994_; uint64_t v___y_995_; uint64_t v___y_999_; uint64_t v___y_1000_; uint8_t v___y_1001_; uint32_t v___y_1002_; uint64_t v___y_1011_; uint64_t v___y_1012_; uint64_t v___y_1013_; uint8_t v___y_1014_; uint32_t v___y_1015_; uint64_t v___y_1016_; uint32_t v___y_1050_; uint32_t v___y_1051_; uint32_t v___y_1052_; uint32_t v___y_1053_; uint32_t v___y_1060_; uint8_t v___y_1061_; uint32_t v___y_1062_; uint32_t v___y_1063_; uint32_t v___y_1067_; uint64_t v___y_1068_; uint8_t v___y_1069_; uint64_t v___y_1070_; uint64_t v___y_1071_; uint32_t v___y_1081_; uint8_t v___y_1082_; uint8_t v___y_1083_; uint64_t v___y_1084_; uint64_t v___y_1085_; uint64_t v___y_1086_; uint64_t v___y_1093_; uint32_t v___y_1094_; uint8_t v___y_1095_; uint64_t v___y_1096_; uint64_t v___y_1097_; uint32_t v___y_1103_; uint8_t v___y_1104_; uint64_t v___y_1105_; uint64_t v___y_1106_; uint64_t v___y_1107_; uint64_t v___y_1108_; uint32_t v___y_1163_; uint8_t v___y_1164_; uint64_t v___y_1165_; uint64_t v___y_1166_; uint64_t v___y_1167_; uint64_t v___y_1168_; uint64_t v___y_1169_; uint32_t v___y_1175_; uint64_t v___y_1176_; uint8_t v___y_1177_; uint64_t v___y_1178_; uint64_t v___y_1179_; uint64_t v___y_1180_; uint64_t v___y_1181_; uint64_t v___y_1182_; uint64_t v___y_1183_; uint32_t v___y_1188_; uint8_t v___y_1189_; uint64_t v___y_1190_; uint64_t v___y_1191_; uint64_t v___y_1192_; uint64_t v___y_1193_; uint64_t v___y_1194_; uint64_t v___y_1199_; uint32_t v___y_1200_; uint8_t v___y_1201_; uint64_t v___y_1202_; uint64_t v___y_1203_; uint64_t v___y_1204_; uint64_t v___y_1205_; uint64_t v___y_1206_; uint64_t v___y_1207_; uint32_t v___y_1212_; uint8_t v___y_1213_; uint64_t v___y_1214_; uint64_t v___y_1215_; uint64_t v___y_1216_; uint64_t v___y_1217_; uint64_t v___y_1218_; uint64_t v___y_1223_; uint32_t v___y_1224_; uint8_t v___y_1225_; uint64_t v___y_1226_; uint64_t v___y_1227_; uint64_t v___y_1228_; uint64_t v___y_1229_; uint64_t v___y_1230_; uint64_t v___y_1231_; uint64_t v___y_1236_; uint32_t v___y_1237_; uint8_t v___y_1238_; uint64_t v___y_1239_; uint64_t v___y_1240_; uint64_t v___y_1241_; uint64_t v___y_1242_; uint32_t v___y_1247_; uint8_t v___y_1248_; uint64_t v___y_1249_; uint64_t v___y_1250_; uint64_t v___y_1251_; uint64_t v___y_1252_; uint64_t v___y_1253_; uint64_t v___y_1254_; uint64_t v___y_1255_; uint32_t v___y_1260_; uint8_t v___y_1261_; uint64_t v___y_1262_; uint64_t v___y_1263_; uint64_t v___y_1264_; uint64_t v___y_1265_; uint64_t v___y_1266_; uint32_t v___y_1271_; uint8_t v___y_1272_; uint64_t v___y_1273_; uint64_t v___y_1274_; uint64_t v___y_1275_; uint64_t v___y_1276_; uint64_t v___y_1277_; uint32_t v___y_1281_; uint8_t v___y_1282_; uint64_t v___y_1283_; uint64_t v___y_1284_; uint64_t v___y_1293_; uint32_t v___y_1294_; uint8_t v___y_1295_; uint64_t v___y_1296_; uint64_t v___y_1297_; uint64_t v___y_1298_; uint32_t v_eu_1331_; uint32_t v___x_1332_; uint32_t v___x_1333_; uint32_t v___x_1334_; uint8_t v___x_1335_; 
v___x_443_ = 23;
v___x_444_ = lean_uint32_shift_right(v_x_6_, v___x_443_);
v___x_484_ = 255;
v_eu_1331_ = lean_uint32_land(v___x_444_, v___x_484_);
v___x_1332_ = 1;
v___x_1333_ = lean_uint32_sub(v_eu_1331_, v___x_1332_);
v___x_1334_ = 253;
v___x_1335_ = lean_uint32_dec_le(v___x_1333_, v___x_1334_);
if (v___x_1335_ == 0)
{
uint32_t v___x_1336_; uint32_t v_ey_1337_; uint64_t v___y_1339_; uint32_t v___y_1340_; uint8_t v___y_1341_; uint64_t v___y_1342_; uint64_t v___y_1343_; uint64_t v___y_1350_; uint32_t v___y_1351_; uint8_t v___y_1352_; uint64_t v___y_1353_; uint32_t v___y_1360_; uint8_t v___y_1361_; uint32_t v___y_1362_; uint64_t v___y_1363_; uint8_t v___y_1371_; uint32_t v___x_1381_; uint32_t v___x_1382_; uint8_t v___x_1383_; uint8_t v___y_1385_; uint8_t v___y_1386_; uint8_t v___y_1387_; uint8_t v___y_1389_; uint8_t v___y_1390_; uint8_t v___y_1396_; 
v___x_1336_ = lean_uint32_shift_right(v_y_7_, v___x_443_);
v_ey_1337_ = lean_uint32_land(v___x_1336_, v___x_484_);
v___x_1381_ = lean_uint32_add(v_eu_1331_, v_ey_1337_);
v___x_1382_ = 128;
v___x_1383_ = lean_uint32_dec_lt(v___x_1381_, v___x_1382_);
if (v___x_1383_ == 0)
{
uint32_t v___x_1406_; uint32_t v_a_1407_; uint32_t v___x_1408_; uint32_t v___x_1409_; uint8_t v___x_1410_; 
v___x_1406_ = 2147483647;
v_a_1407_ = lean_uint32_land(v_x_6_, v___x_1406_);
v___x_1408_ = 201326591;
v___x_1409_ = lean_uint32_sub(v_a_1407_, v___x_1332_);
v___x_1410_ = lean_uint32_dec_le(v___x_1408_, v___x_1409_);
if (v___x_1410_ == 0)
{
v___y_472_ = v___x_1410_;
goto v___jp_471_;
}
else
{
uint32_t v___x_1411_; uint8_t v___x_1412_; 
v___x_1411_ = 2139095040;
v___x_1412_ = lean_uint32_dec_lt(v_a_1407_, v___x_1411_);
v___y_472_ = v___x_1412_;
goto v___jp_471_;
}
}
else
{
uint32_t v___x_1413_; uint32_t v___x_1414_; uint8_t v___x_1415_; 
v___x_1413_ = 4278190080;
v___x_1414_ = lean_uint32_shift_left(v_x_6_, v___x_1332_);
v___x_1415_ = lean_uint32_dec_le(v___x_1413_, v___x_1414_);
if (v___x_1415_ == 0)
{
uint32_t v___x_1416_; uint8_t v___x_1417_; 
v___x_1416_ = lean_uint32_shift_left(v_y_7_, v___x_1332_);
v___x_1417_ = lean_uint32_dec_le(v___x_1413_, v___x_1416_);
v___y_1396_ = v___x_1417_;
goto v___jp_1395_;
}
else
{
v___y_1396_ = v___x_1415_;
goto v___jp_1395_;
}
}
v___jp_1338_:
{
uint64_t v___x_1344_; uint64_t v___x_1345_; uint8_t v___x_1346_; 
v___x_1344_ = lean_uint32_to_uint64(v_ey_1337_);
v___x_1345_ = 0ULL;
v___x_1346_ = lean_uint64_dec_eq(v___x_1344_, v___x_1345_);
if (v___x_1346_ == 0)
{
uint64_t v___x_1347_; uint64_t v___x_1348_; 
v___x_1347_ = 1ULL;
v___x_1348_ = lean_uint64_sub(v___x_1344_, v___x_1347_);
v___y_1293_ = v___y_1339_;
v___y_1294_ = v___y_1340_;
v___y_1295_ = v___y_1341_;
v___y_1296_ = v___y_1342_;
v___y_1297_ = v___y_1343_;
v___y_1298_ = v___x_1348_;
goto v___jp_1292_;
}
else
{
v___y_1293_ = v___y_1339_;
v___y_1294_ = v___y_1340_;
v___y_1295_ = v___y_1341_;
v___y_1296_ = v___y_1342_;
v___y_1297_ = v___y_1343_;
v___y_1298_ = v___x_1345_;
goto v___jp_1292_;
}
}
v___jp_1349_:
{
uint64_t v___x_1354_; uint64_t v___x_1355_; uint8_t v___x_1356_; 
v___x_1354_ = lean_uint32_to_uint64(v_eu_1331_);
v___x_1355_ = 0ULL;
v___x_1356_ = lean_uint64_dec_eq(v___x_1354_, v___x_1355_);
if (v___x_1356_ == 0)
{
uint64_t v___x_1357_; uint64_t v___x_1358_; 
v___x_1357_ = 1ULL;
v___x_1358_ = lean_uint64_sub(v___x_1354_, v___x_1357_);
v___y_1339_ = v___y_1350_;
v___y_1340_ = v___y_1351_;
v___y_1341_ = v___y_1352_;
v___y_1342_ = v___y_1353_;
v___y_1343_ = v___x_1358_;
goto v___jp_1338_;
}
else
{
v___y_1339_ = v___y_1350_;
v___y_1340_ = v___y_1351_;
v___y_1341_ = v___y_1352_;
v___y_1342_ = v___y_1353_;
v___y_1343_ = v___x_1355_;
goto v___jp_1338_;
}
}
v___jp_1359_:
{
uint32_t v___x_1364_; uint8_t v___x_1365_; 
v___x_1364_ = 0;
v___x_1365_ = lean_uint32_dec_eq(v_ey_1337_, v___x_1364_);
if (v___x_1365_ == 0)
{
uint64_t v___x_1366_; uint64_t v___x_1367_; uint64_t v___x_1368_; 
v___x_1366_ = lean_uint32_to_uint64(v___y_1362_);
v___x_1367_ = 8388608ULL;
v___x_1368_ = lean_uint64_lor(v___x_1366_, v___x_1367_);
v___y_1350_ = v___y_1363_;
v___y_1351_ = v___y_1360_;
v___y_1352_ = v___y_1361_;
v___y_1353_ = v___x_1368_;
goto v___jp_1349_;
}
else
{
uint64_t v___x_1369_; 
v___x_1369_ = lean_uint32_to_uint64(v___y_1362_);
v___y_1350_ = v___y_1363_;
v___y_1351_ = v___y_1360_;
v___y_1352_ = v___y_1361_;
v___y_1353_ = v___x_1369_;
goto v___jp_1349_;
}
}
v___jp_1370_:
{
uint32_t v___x_1372_; uint32_t v_xFraction_1373_; uint32_t v_yFraction_1374_; uint32_t v___x_1375_; uint8_t v___x_1376_; 
v___x_1372_ = 8388607;
v_xFraction_1373_ = lean_uint32_land(v_x_6_, v___x_1372_);
v_yFraction_1374_ = lean_uint32_land(v_y_7_, v___x_1372_);
v___x_1375_ = 0;
v___x_1376_ = lean_uint32_dec_eq(v_eu_1331_, v___x_1375_);
if (v___x_1376_ == 0)
{
uint64_t v___x_1377_; uint64_t v___x_1378_; uint64_t v___x_1379_; 
v___x_1377_ = lean_uint32_to_uint64(v_xFraction_1373_);
v___x_1378_ = 8388608ULL;
v___x_1379_ = lean_uint64_lor(v___x_1377_, v___x_1378_);
v___y_1360_ = v___x_1372_;
v___y_1361_ = v___y_1371_;
v___y_1362_ = v_yFraction_1374_;
v___y_1363_ = v___x_1379_;
goto v___jp_1359_;
}
else
{
uint64_t v___x_1380_; 
v___x_1380_ = lean_uint32_to_uint64(v_xFraction_1373_);
v___y_1360_ = v___x_1372_;
v___y_1361_ = v___y_1371_;
v___y_1362_ = v_yFraction_1374_;
v___y_1363_ = v___x_1380_;
goto v___jp_1359_;
}
}
v___jp_1384_:
{
if (v___y_1386_ == 0)
{
if (v___y_1387_ == 0)
{
v___y_1371_ = v___y_1385_;
goto v___jp_1370_;
}
else
{
v___y_1371_ = v___x_1383_;
goto v___jp_1370_;
}
}
else
{
if (v___y_1387_ == 0)
{
v___y_1371_ = v___x_1383_;
goto v___jp_1370_;
}
else
{
v___y_1371_ = v___y_1385_;
goto v___jp_1370_;
}
}
}
v___jp_1388_:
{
uint32_t v___x_1391_; uint32_t v___x_1392_; uint32_t v___x_1393_; uint8_t v___x_1394_; 
v___x_1391_ = 2147483648;
v___x_1392_ = lean_uint32_land(v_y_7_, v___x_1391_);
v___x_1393_ = 0;
v___x_1394_ = lean_uint32_dec_eq(v___x_1392_, v___x_1393_);
if (v___x_1394_ == 0)
{
v___y_1385_ = v___y_1389_;
v___y_1386_ = v___y_1390_;
v___y_1387_ = v___x_1383_;
goto v___jp_1384_;
}
else
{
v___y_1385_ = v___y_1389_;
v___y_1386_ = v___y_1390_;
v___y_1387_ = v___y_1389_;
goto v___jp_1384_;
}
}
v___jp_1395_:
{
if (v___y_1396_ == 0)
{
uint32_t v___x_1397_; uint32_t v___x_1398_; uint32_t v___x_1399_; uint8_t v___x_1400_; 
v___x_1397_ = 2147483648;
v___x_1398_ = lean_uint32_land(v_x_6_, v___x_1397_);
v___x_1399_ = 0;
v___x_1400_ = lean_uint32_dec_eq(v___x_1398_, v___x_1399_);
if (v___x_1400_ == 0)
{
v___y_1389_ = v___y_1396_;
v___y_1390_ = v___x_1383_;
goto v___jp_1388_;
}
else
{
v___y_1389_ = v___y_1396_;
v___y_1390_ = v___y_1396_;
goto v___jp_1388_;
}
}
else
{
lean_object* v___x_1401_; lean_object* v___x_1402_; lean_object* v___x_1403_; lean_object* v___x_1404_; uint32_t v___x_1405_; 
v___x_1401_ = ((lean_object*)(lp_competition_r22CostInlineOldMul___closed__0));
v___x_1402_ = lean_uint32_to_nat(v_x_6_);
v___x_1403_ = lean_uint32_to_nat(v_y_7_);
v___x_1404_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word(v___x_1401_, v___x_1402_, v___x_1403_);
v___x_1405_ = lean_uint32_of_nat(v___x_1404_);
lean_dec(v___x_1404_);
return v___x_1405_;
}
}
}
else
{
uint32_t v___x_1418_; uint32_t v_ev_1419_; uint64_t v___y_1421_; uint32_t v___y_1422_; uint8_t v___y_1423_; uint64_t v___y_1424_; uint64_t v___y_1425_; uint8_t v___y_1432_; uint32_t v___y_1433_; uint64_t v___y_1434_; uint64_t v___y_1435_; uint32_t v___y_1442_; uint32_t v___y_1443_; uint8_t v___y_1444_; uint64_t v___y_1445_; uint8_t v___y_1453_; uint64_t v___y_1464_; uint64_t v___y_1465_; uint8_t v___y_1466_; uint32_t v___y_1467_; uint64_t v___y_1468_; uint64_t v___y_1475_; uint8_t v___y_1476_; uint32_t v___y_1477_; uint64_t v___y_1478_; uint32_t v___y_1485_; uint8_t v___y_1486_; uint32_t v___y_1487_; uint64_t v___y_1488_; uint8_t v___y_1496_; uint8_t v___y_1507_; uint8_t v___y_1508_; uint8_t v___y_1510_; uint8_t v___y_1511_; uint8_t v___y_1512_; uint8_t v___y_1514_; uint8_t v___y_1515_; uint8_t v___y_1521_; uint32_t v___x_1531_; uint8_t v___x_1532_; uint8_t v___y_1534_; uint8_t v___y_1535_; uint8_t v___y_1537_; uint8_t v___y_1538_; uint8_t v___y_1539_; uint8_t v___y_1541_; uint8_t v___y_1542_; uint8_t v___y_1548_; 
v___x_1418_ = lean_uint32_shift_right(v_y_7_, v___x_443_);
v_ev_1419_ = lean_uint32_land(v___x_1418_, v___x_484_);
v___x_1531_ = lean_uint32_sub(v_ev_1419_, v___x_1332_);
v___x_1532_ = lean_uint32_dec_le(v___x_1531_, v___x_1334_);
if (v___x_1532_ == 0)
{
uint32_t v___x_1558_; uint32_t v___x_1559_; uint8_t v___x_1560_; 
v___x_1558_ = lean_uint32_add(v_eu_1331_, v_ev_1419_);
v___x_1559_ = 128;
v___x_1560_ = lean_uint32_dec_lt(v___x_1558_, v___x_1559_);
if (v___x_1560_ == 0)
{
uint32_t v___x_1561_; uint32_t v_a_1562_; uint32_t v___x_1563_; uint32_t v___x_1564_; uint8_t v___x_1565_; 
v___x_1561_ = 2147483647;
v_a_1562_ = lean_uint32_land(v_x_6_, v___x_1561_);
v___x_1563_ = 201326591;
v___x_1564_ = lean_uint32_sub(v_a_1562_, v___x_1332_);
v___x_1565_ = lean_uint32_dec_le(v___x_1563_, v___x_1564_);
if (v___x_1565_ == 0)
{
v___y_459_ = v___x_1565_;
goto v___jp_458_;
}
else
{
uint32_t v___x_1566_; uint8_t v___x_1567_; 
v___x_1566_ = 2139095040;
v___x_1567_ = lean_uint32_dec_lt(v_a_1562_, v___x_1566_);
v___y_459_ = v___x_1567_;
goto v___jp_458_;
}
}
else
{
uint32_t v___x_1568_; uint32_t v___x_1569_; uint8_t v___x_1570_; 
v___x_1568_ = 4278190080;
v___x_1569_ = lean_uint32_shift_left(v_x_6_, v___x_1332_);
v___x_1570_ = lean_uint32_dec_le(v___x_1568_, v___x_1569_);
if (v___x_1570_ == 0)
{
uint32_t v___x_1571_; uint8_t v___x_1572_; 
v___x_1571_ = lean_uint32_shift_left(v_y_7_, v___x_1332_);
v___x_1572_ = lean_uint32_dec_le(v___x_1568_, v___x_1571_);
v___y_1521_ = v___x_1572_;
goto v___jp_1520_;
}
else
{
v___y_1521_ = v___x_1570_;
goto v___jp_1520_;
}
}
}
else
{
uint32_t v_s_1573_; uint32_t v___x_1574_; uint32_t v___x_1575_; uint32_t v___x_1576_; uint8_t v___x_1577_; 
v_s_1573_ = lean_uint32_add(v_eu_1331_, v_ev_1419_);
v___x_1574_ = 128;
v___x_1575_ = lean_uint32_sub(v_s_1573_, v___x_1574_);
v___x_1576_ = 252;
v___x_1577_ = lean_uint32_dec_le(v___x_1575_, v___x_1576_);
if (v___x_1577_ == 0)
{
uint8_t v___x_1578_; 
v___x_1578_ = lean_uint32_dec_lt(v_s_1573_, v___x_1574_);
if (v___x_1578_ == 0)
{
uint32_t v___x_1579_; uint32_t v_a_1580_; uint32_t v___x_1581_; uint32_t v___x_1582_; uint8_t v___x_1583_; 
v___x_1579_ = 2147483647;
v_a_1580_ = lean_uint32_land(v_x_6_, v___x_1579_);
v___x_1581_ = 201326591;
v___x_1582_ = lean_uint32_sub(v_a_1580_, v___x_1332_);
v___x_1583_ = lean_uint32_dec_le(v___x_1581_, v___x_1582_);
if (v___x_1583_ == 0)
{
v___y_446_ = v___x_1583_;
goto v___jp_445_;
}
else
{
uint32_t v___x_1584_; uint8_t v___x_1585_; 
v___x_1584_ = 2139095040;
v___x_1585_ = lean_uint32_dec_lt(v_a_1580_, v___x_1584_);
v___y_446_ = v___x_1585_;
goto v___jp_445_;
}
}
else
{
uint32_t v___x_1586_; uint32_t v___x_1587_; uint8_t v___x_1588_; 
v___x_1586_ = 4278190080;
v___x_1587_ = lean_uint32_shift_left(v_x_6_, v___x_1332_);
v___x_1588_ = lean_uint32_dec_le(v___x_1586_, v___x_1587_);
if (v___x_1588_ == 0)
{
uint32_t v___x_1589_; uint8_t v___x_1590_; 
v___x_1589_ = lean_uint32_shift_left(v_y_7_, v___x_1332_);
v___x_1590_ = lean_uint32_dec_le(v___x_1586_, v___x_1589_);
v___y_1548_ = v___x_1590_;
goto v___jp_1547_;
}
else
{
v___y_1548_ = v___x_1588_;
goto v___jp_1547_;
}
}
}
else
{
uint32_t v___x_1591_; uint32_t v___x_1592_; uint32_t v___x_1593_; uint64_t v___y_1595_; uint32_t v_a_1613_; uint32_t v___x_1614_; uint32_t v_b_1615_; uint64_t v___x_1616_; uint64_t v___x_1617_; uint64_t v_p_1618_; uint64_t v___x_1619_; uint8_t v___x_1620_; 
v___x_1591_ = 8388607;
v___x_1592_ = lean_uint32_land(v_x_6_, v___x_1591_);
v___x_1593_ = 8388608;
v_a_1613_ = lean_uint32_lor(v___x_1592_, v___x_1593_);
v___x_1614_ = lean_uint32_land(v_y_7_, v___x_1591_);
v_b_1615_ = lean_uint32_lor(v___x_1614_, v___x_1593_);
v___x_1616_ = lean_uint32_to_uint64(v_a_1613_);
v___x_1617_ = lean_uint32_to_uint64(v_b_1615_);
v_p_1618_ = lean_uint64_mul(v___x_1616_, v___x_1617_);
v___x_1619_ = 140737488355328ULL;
v___x_1620_ = lean_uint64_dec_lt(v_p_1618_, v___x_1619_);
if (v___x_1620_ == 0)
{
uint64_t v___x_1621_; uint64_t v___x_1622_; uint64_t v___x_1623_; uint64_t v___x_1624_; uint64_t v___x_1625_; uint64_t v___x_1626_; uint64_t v___x_1627_; 
v___x_1621_ = 8388607ULL;
v___x_1622_ = lean_uint64_add(v_p_1618_, v___x_1621_);
v___x_1623_ = 24ULL;
v___x_1624_ = lean_uint64_shift_right(v_p_1618_, v___x_1623_);
v___x_1625_ = 1ULL;
v___x_1626_ = lean_uint64_land(v___x_1624_, v___x_1625_);
v___x_1627_ = lean_uint64_add(v___x_1622_, v___x_1626_);
v___y_1595_ = v___x_1627_;
goto v___jp_1594_;
}
else
{
uint64_t v___x_1628_; uint64_t v___x_1629_; uint64_t v___x_1630_; uint64_t v___x_1631_; uint64_t v___x_1632_; uint64_t v___x_1633_; uint64_t v___x_1634_; 
v___x_1628_ = 4194303ULL;
v___x_1629_ = lean_uint64_add(v_p_1618_, v___x_1628_);
v___x_1630_ = 23ULL;
v___x_1631_ = lean_uint64_shift_right(v_p_1618_, v___x_1630_);
v___x_1632_ = 1ULL;
v___x_1633_ = lean_uint64_land(v___x_1631_, v___x_1632_);
v___x_1634_ = lean_uint64_add(v___x_1629_, v___x_1633_);
v___y_1595_ = v___x_1634_;
goto v___jp_1594_;
}
v___jp_1594_:
{
uint64_t v___x_1596_; uint64_t v_high_1597_; uint64_t v___x_1598_; uint64_t v___x_1599_; uint64_t v___x_1600_; uint32_t v_q_1601_; uint32_t v___x_1602_; uint32_t v___x_1603_; uint32_t v___x_1604_; uint32_t v_e_1605_; uint32_t v___x_1606_; uint32_t v___x_1607_; uint32_t v___x_1608_; uint32_t v___x_1609_; uint32_t v___x_1610_; uint32_t v___x_1611_; uint32_t v___x_1612_; 
v___x_1596_ = 47ULL;
v_high_1597_ = lean_uint64_shift_right(v___y_1595_, v___x_1596_);
v___x_1598_ = 23ULL;
v___x_1599_ = lean_uint64_add(v___x_1598_, v_high_1597_);
v___x_1600_ = lean_uint64_shift_right(v___y_1595_, v___x_1599_);
v_q_1601_ = lean_uint64_to_uint32(v___x_1600_);
v___x_1602_ = 127;
v___x_1603_ = lean_uint32_sub(v_s_1573_, v___x_1602_);
v___x_1604_ = lean_uint64_to_uint32(v_high_1597_);
v_e_1605_ = lean_uint32_add(v___x_1603_, v___x_1604_);
v___x_1606_ = lean_uint32_xor(v_x_6_, v_y_7_);
v___x_1607_ = 2147483648;
v___x_1608_ = lean_uint32_land(v___x_1606_, v___x_1607_);
v___x_1609_ = lean_uint32_shift_left(v_e_1605_, v___x_443_);
v___x_1610_ = lean_uint32_lor(v___x_1608_, v___x_1609_);
v___x_1611_ = lean_uint32_sub(v_q_1601_, v___x_1593_);
v___x_1612_ = lean_uint32_lor(v___x_1610_, v___x_1611_);
return v___x_1612_;
}
}
}
v___jp_1420_:
{
uint64_t v___x_1426_; uint64_t v___x_1427_; uint8_t v___x_1428_; 
v___x_1426_ = lean_uint32_to_uint64(v_ev_1419_);
v___x_1427_ = 0ULL;
v___x_1428_ = lean_uint64_dec_eq(v___x_1426_, v___x_1427_);
if (v___x_1428_ == 0)
{
uint64_t v___x_1429_; uint64_t v___x_1430_; 
v___x_1429_ = 1ULL;
v___x_1430_ = lean_uint64_sub(v___x_1426_, v___x_1429_);
v___y_729_ = v___y_1421_;
v___y_730_ = v___y_1425_;
v___y_731_ = v___y_1423_;
v___y_732_ = v___y_1422_;
v___y_733_ = v___y_1424_;
v___y_734_ = v___x_1430_;
goto v___jp_728_;
}
else
{
v___y_729_ = v___y_1421_;
v___y_730_ = v___y_1425_;
v___y_731_ = v___y_1423_;
v___y_732_ = v___y_1422_;
v___y_733_ = v___y_1424_;
v___y_734_ = v___x_1427_;
goto v___jp_728_;
}
}
v___jp_1431_:
{
uint64_t v___x_1436_; uint64_t v___x_1437_; uint8_t v___x_1438_; 
v___x_1436_ = lean_uint32_to_uint64(v_eu_1331_);
v___x_1437_ = 0ULL;
v___x_1438_ = lean_uint64_dec_eq(v___x_1436_, v___x_1437_);
if (v___x_1438_ == 0)
{
uint64_t v___x_1439_; uint64_t v___x_1440_; 
v___x_1439_ = 1ULL;
v___x_1440_ = lean_uint64_sub(v___x_1436_, v___x_1439_);
v___y_1421_ = v___y_1435_;
v___y_1422_ = v___y_1433_;
v___y_1423_ = v___y_1432_;
v___y_1424_ = v___y_1434_;
v___y_1425_ = v___x_1440_;
goto v___jp_1420_;
}
else
{
v___y_1421_ = v___y_1435_;
v___y_1422_ = v___y_1433_;
v___y_1423_ = v___y_1432_;
v___y_1424_ = v___y_1434_;
v___y_1425_ = v___x_1437_;
goto v___jp_1420_;
}
}
v___jp_1441_:
{
uint32_t v___x_1446_; uint8_t v___x_1447_; 
v___x_1446_ = 0;
v___x_1447_ = lean_uint32_dec_eq(v_ev_1419_, v___x_1446_);
if (v___x_1447_ == 0)
{
uint64_t v___x_1448_; uint64_t v___x_1449_; uint64_t v___x_1450_; 
v___x_1448_ = lean_uint32_to_uint64(v___y_1442_);
v___x_1449_ = 8388608ULL;
v___x_1450_ = lean_uint64_lor(v___x_1448_, v___x_1449_);
v___y_1432_ = v___y_1444_;
v___y_1433_ = v___y_1443_;
v___y_1434_ = v___y_1445_;
v___y_1435_ = v___x_1450_;
goto v___jp_1431_;
}
else
{
uint64_t v___x_1451_; 
v___x_1451_ = lean_uint32_to_uint64(v___y_1442_);
v___y_1432_ = v___y_1444_;
v___y_1433_ = v___y_1443_;
v___y_1434_ = v___y_1445_;
v___y_1435_ = v___x_1451_;
goto v___jp_1431_;
}
}
v___jp_1452_:
{
uint32_t v___x_1454_; uint32_t v_xFraction_1455_; uint32_t v_yFraction_1456_; uint32_t v___x_1457_; uint8_t v___x_1458_; 
v___x_1454_ = 8388607;
v_xFraction_1455_ = lean_uint32_land(v_x_6_, v___x_1454_);
v_yFraction_1456_ = lean_uint32_land(v_y_7_, v___x_1454_);
v___x_1457_ = 0;
v___x_1458_ = lean_uint32_dec_eq(v_eu_1331_, v___x_1457_);
if (v___x_1458_ == 0)
{
uint64_t v___x_1459_; uint64_t v___x_1460_; uint64_t v___x_1461_; 
v___x_1459_ = lean_uint32_to_uint64(v_xFraction_1455_);
v___x_1460_ = 8388608ULL;
v___x_1461_ = lean_uint64_lor(v___x_1459_, v___x_1460_);
v___y_1442_ = v_yFraction_1456_;
v___y_1443_ = v___x_1454_;
v___y_1444_ = v___y_1453_;
v___y_1445_ = v___x_1461_;
goto v___jp_1441_;
}
else
{
uint64_t v___x_1462_; 
v___x_1462_ = lean_uint32_to_uint64(v_xFraction_1455_);
v___y_1442_ = v_yFraction_1456_;
v___y_1443_ = v___x_1454_;
v___y_1444_ = v___y_1453_;
v___y_1445_ = v___x_1462_;
goto v___jp_1441_;
}
}
v___jp_1463_:
{
uint64_t v___x_1469_; uint64_t v___x_1470_; uint8_t v___x_1471_; 
v___x_1469_ = lean_uint32_to_uint64(v_ev_1419_);
v___x_1470_ = 0ULL;
v___x_1471_ = lean_uint64_dec_eq(v___x_1469_, v___x_1470_);
if (v___x_1471_ == 0)
{
uint64_t v___x_1472_; uint64_t v___x_1473_; 
v___x_1472_ = 1ULL;
v___x_1473_ = lean_uint64_sub(v___x_1469_, v___x_1472_);
v___y_1011_ = v___y_1468_;
v___y_1012_ = v___y_1464_;
v___y_1013_ = v___y_1465_;
v___y_1014_ = v___y_1466_;
v___y_1015_ = v___y_1467_;
v___y_1016_ = v___x_1473_;
goto v___jp_1010_;
}
else
{
v___y_1011_ = v___y_1468_;
v___y_1012_ = v___y_1464_;
v___y_1013_ = v___y_1465_;
v___y_1014_ = v___y_1466_;
v___y_1015_ = v___y_1467_;
v___y_1016_ = v___x_1470_;
goto v___jp_1010_;
}
}
v___jp_1474_:
{
uint64_t v___x_1479_; uint64_t v___x_1480_; uint8_t v___x_1481_; 
v___x_1479_ = lean_uint32_to_uint64(v_eu_1331_);
v___x_1480_ = 0ULL;
v___x_1481_ = lean_uint64_dec_eq(v___x_1479_, v___x_1480_);
if (v___x_1481_ == 0)
{
uint64_t v___x_1482_; uint64_t v___x_1483_; 
v___x_1482_ = 1ULL;
v___x_1483_ = lean_uint64_sub(v___x_1479_, v___x_1482_);
v___y_1464_ = v___y_1478_;
v___y_1465_ = v___y_1475_;
v___y_1466_ = v___y_1476_;
v___y_1467_ = v___y_1477_;
v___y_1468_ = v___x_1483_;
goto v___jp_1463_;
}
else
{
v___y_1464_ = v___y_1478_;
v___y_1465_ = v___y_1475_;
v___y_1466_ = v___y_1476_;
v___y_1467_ = v___y_1477_;
v___y_1468_ = v___x_1480_;
goto v___jp_1463_;
}
}
v___jp_1484_:
{
uint32_t v___x_1489_; uint8_t v___x_1490_; 
v___x_1489_ = 0;
v___x_1490_ = lean_uint32_dec_eq(v_ev_1419_, v___x_1489_);
if (v___x_1490_ == 0)
{
uint64_t v___x_1491_; uint64_t v___x_1492_; uint64_t v___x_1493_; 
v___x_1491_ = lean_uint32_to_uint64(v___y_1485_);
v___x_1492_ = 8388608ULL;
v___x_1493_ = lean_uint64_lor(v___x_1491_, v___x_1492_);
v___y_1475_ = v___y_1488_;
v___y_1476_ = v___y_1486_;
v___y_1477_ = v___y_1487_;
v___y_1478_ = v___x_1493_;
goto v___jp_1474_;
}
else
{
uint64_t v___x_1494_; 
v___x_1494_ = lean_uint32_to_uint64(v___y_1485_);
v___y_1475_ = v___y_1488_;
v___y_1476_ = v___y_1486_;
v___y_1477_ = v___y_1487_;
v___y_1478_ = v___x_1494_;
goto v___jp_1474_;
}
}
v___jp_1495_:
{
uint32_t v___x_1497_; uint32_t v_xFraction_1498_; uint32_t v_yFraction_1499_; uint32_t v___x_1500_; uint8_t v___x_1501_; 
v___x_1497_ = 8388607;
v_xFraction_1498_ = lean_uint32_land(v_x_6_, v___x_1497_);
v_yFraction_1499_ = lean_uint32_land(v_y_7_, v___x_1497_);
v___x_1500_ = 0;
v___x_1501_ = lean_uint32_dec_eq(v_eu_1331_, v___x_1500_);
if (v___x_1501_ == 0)
{
uint64_t v___x_1502_; uint64_t v___x_1503_; uint64_t v___x_1504_; 
v___x_1502_ = lean_uint32_to_uint64(v_xFraction_1498_);
v___x_1503_ = 8388608ULL;
v___x_1504_ = lean_uint64_lor(v___x_1502_, v___x_1503_);
v___y_1485_ = v_yFraction_1499_;
v___y_1486_ = v___y_1496_;
v___y_1487_ = v___x_1497_;
v___y_1488_ = v___x_1504_;
goto v___jp_1484_;
}
else
{
uint64_t v___x_1505_; 
v___x_1505_ = lean_uint32_to_uint64(v_xFraction_1498_);
v___y_1485_ = v_yFraction_1499_;
v___y_1486_ = v___y_1496_;
v___y_1487_ = v___x_1497_;
v___y_1488_ = v___x_1505_;
goto v___jp_1484_;
}
}
v___jp_1506_:
{
if (v___y_1508_ == 0)
{
v___y_1496_ = v___x_1335_;
goto v___jp_1495_;
}
else
{
v___y_1496_ = v___y_1507_;
goto v___jp_1495_;
}
}
v___jp_1509_:
{
if (v___y_1510_ == 0)
{
if (v___y_1512_ == 0)
{
v___y_1507_ = v___y_1511_;
v___y_1508_ = v___x_1335_;
goto v___jp_1506_;
}
else
{
v___y_1496_ = v___x_1335_;
goto v___jp_1495_;
}
}
else
{
v___y_1507_ = v___y_1511_;
v___y_1508_ = v___y_1512_;
goto v___jp_1506_;
}
}
v___jp_1513_:
{
uint32_t v___x_1516_; uint32_t v___x_1517_; uint32_t v___x_1518_; uint8_t v___x_1519_; 
v___x_1516_ = 2147483648;
v___x_1517_ = lean_uint32_land(v_y_7_, v___x_1516_);
v___x_1518_ = 0;
v___x_1519_ = lean_uint32_dec_eq(v___x_1517_, v___x_1518_);
if (v___x_1519_ == 0)
{
v___y_1510_ = v___y_1515_;
v___y_1511_ = v___y_1514_;
v___y_1512_ = v___x_1335_;
goto v___jp_1509_;
}
else
{
v___y_1510_ = v___y_1515_;
v___y_1511_ = v___y_1514_;
v___y_1512_ = v___y_1514_;
goto v___jp_1509_;
}
}
v___jp_1520_:
{
if (v___y_1521_ == 0)
{
uint32_t v___x_1522_; uint32_t v___x_1523_; uint32_t v___x_1524_; uint8_t v___x_1525_; 
v___x_1522_ = 2147483648;
v___x_1523_ = lean_uint32_land(v_x_6_, v___x_1522_);
v___x_1524_ = 0;
v___x_1525_ = lean_uint32_dec_eq(v___x_1523_, v___x_1524_);
if (v___x_1525_ == 0)
{
v___y_1514_ = v___y_1521_;
v___y_1515_ = v___x_1335_;
goto v___jp_1513_;
}
else
{
v___y_1514_ = v___y_1521_;
v___y_1515_ = v___y_1521_;
goto v___jp_1513_;
}
}
else
{
lean_object* v___x_1526_; lean_object* v___x_1527_; lean_object* v___x_1528_; lean_object* v___x_1529_; uint32_t v___x_1530_; 
v___x_1526_ = ((lean_object*)(lp_competition_r22CostInlineOldMul___closed__0));
v___x_1527_ = lean_uint32_to_nat(v_x_6_);
v___x_1528_ = lean_uint32_to_nat(v_y_7_);
v___x_1529_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word(v___x_1526_, v___x_1527_, v___x_1528_);
v___x_1530_ = lean_uint32_of_nat(v___x_1529_);
lean_dec(v___x_1529_);
return v___x_1530_;
}
}
v___jp_1533_:
{
if (v___y_1535_ == 0)
{
v___y_1453_ = v___x_1532_;
goto v___jp_1452_;
}
else
{
v___y_1453_ = v___y_1534_;
goto v___jp_1452_;
}
}
v___jp_1536_:
{
if (v___y_1537_ == 0)
{
if (v___y_1539_ == 0)
{
v___y_1534_ = v___y_1538_;
v___y_1535_ = v___x_1532_;
goto v___jp_1533_;
}
else
{
v___y_1453_ = v___x_1532_;
goto v___jp_1452_;
}
}
else
{
v___y_1534_ = v___y_1538_;
v___y_1535_ = v___y_1539_;
goto v___jp_1533_;
}
}
v___jp_1540_:
{
uint32_t v___x_1543_; uint32_t v___x_1544_; uint32_t v___x_1545_; uint8_t v___x_1546_; 
v___x_1543_ = 2147483648;
v___x_1544_ = lean_uint32_land(v_y_7_, v___x_1543_);
v___x_1545_ = 0;
v___x_1546_ = lean_uint32_dec_eq(v___x_1544_, v___x_1545_);
if (v___x_1546_ == 0)
{
v___y_1537_ = v___y_1542_;
v___y_1538_ = v___y_1541_;
v___y_1539_ = v___x_1532_;
goto v___jp_1536_;
}
else
{
v___y_1537_ = v___y_1542_;
v___y_1538_ = v___y_1541_;
v___y_1539_ = v___y_1541_;
goto v___jp_1536_;
}
}
v___jp_1547_:
{
if (v___y_1548_ == 0)
{
uint32_t v___x_1549_; uint32_t v___x_1550_; uint32_t v___x_1551_; uint8_t v___x_1552_; 
v___x_1549_ = 2147483648;
v___x_1550_ = lean_uint32_land(v_x_6_, v___x_1549_);
v___x_1551_ = 0;
v___x_1552_ = lean_uint32_dec_eq(v___x_1550_, v___x_1551_);
if (v___x_1552_ == 0)
{
v___y_1541_ = v___y_1548_;
v___y_1542_ = v___x_1532_;
goto v___jp_1540_;
}
else
{
v___y_1541_ = v___y_1548_;
v___y_1542_ = v___y_1548_;
goto v___jp_1540_;
}
}
else
{
lean_object* v___x_1553_; lean_object* v___x_1554_; lean_object* v___x_1555_; lean_object* v___x_1556_; uint32_t v___x_1557_; 
v___x_1553_ = ((lean_object*)(lp_competition_r22CostInlineOldMul___closed__0));
v___x_1554_ = lean_uint32_to_nat(v_x_6_);
v___x_1555_ = lean_uint32_to_nat(v_y_7_);
v___x_1556_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word(v___x_1553_, v___x_1554_, v___x_1555_);
v___x_1557_ = lean_uint32_of_nat(v___x_1556_);
lean_dec(v___x_1556_);
return v___x_1557_;
}
}
}
v___jp_8_:
{
uint32_t v___x_10_; uint32_t v___x_11_; 
v___x_10_ = 8388608;
v___x_11_ = lean_uint32_lor(v___y_9_, v___x_10_);
return v___x_11_;
}
v___jp_12_:
{
uint32_t v___x_14_; uint32_t v___x_15_; 
v___x_14_ = 8388608;
v___x_15_ = lean_uint32_lor(v___y_13_, v___x_14_);
return v___x_15_;
}
v___jp_16_:
{
uint32_t v___x_20_; uint32_t v___x_21_; 
v___x_20_ = lean_uint32_land(v___y_17_, v___y_18_);
v___x_21_ = lean_uint32_lor(v___y_19_, v___x_20_);
return v___x_21_;
}
v___jp_22_:
{
uint8_t v___x_27_; 
v___x_27_ = lean_uint64_dec_eq(v___y_26_, v___y_23_);
if (v___x_27_ == 0)
{
uint64_t v___x_28_; uint8_t v___x_29_; 
v___x_28_ = 8388608ULL;
v___x_29_ = lean_uint64_dec_eq(v___y_26_, v___x_28_);
if (v___x_29_ == 0)
{
uint32_t v___x_30_; 
v___x_30_ = lean_uint64_to_uint32(v___y_26_);
if (v___y_24_ == 0)
{
uint32_t v___x_31_; 
v___x_31_ = 0;
v___y_17_ = v___x_30_;
v___y_18_ = v___y_25_;
v___y_19_ = v___x_31_;
goto v___jp_16_;
}
else
{
uint32_t v___x_32_; 
v___x_32_ = 2147483648;
v___y_17_ = v___x_30_;
v___y_18_ = v___y_25_;
v___y_19_ = v___x_32_;
goto v___jp_16_;
}
}
else
{
if (v___y_24_ == 0)
{
uint32_t v___x_33_; 
v___x_33_ = 0;
v___y_13_ = v___x_33_;
goto v___jp_12_;
}
else
{
uint32_t v___x_34_; 
v___x_34_ = 2147483648;
v___y_13_ = v___x_34_;
goto v___jp_12_;
}
}
}
else
{
if (v___y_24_ == 0)
{
uint32_t v___x_35_; 
v___x_35_ = 0;
return v___x_35_;
}
else
{
uint32_t v___x_36_; 
v___x_36_ = 2147483648;
return v___x_36_;
}
}
}
v___jp_37_:
{
uint32_t v___x_41_; uint32_t v___x_42_; 
v___x_41_ = lean_uint32_land(v___y_38_, v___y_39_);
v___x_42_ = lean_uint32_lor(v___y_40_, v___x_41_);
return v___x_42_;
}
v___jp_43_:
{
uint8_t v___x_48_; 
v___x_48_ = lean_uint64_dec_eq(v___y_47_, v___y_44_);
if (v___x_48_ == 0)
{
uint64_t v___x_49_; uint8_t v___x_50_; 
v___x_49_ = 8388608ULL;
v___x_50_ = lean_uint64_dec_eq(v___y_47_, v___x_49_);
if (v___x_50_ == 0)
{
uint32_t v___x_51_; 
v___x_51_ = lean_uint64_to_uint32(v___y_47_);
if (v___y_45_ == 0)
{
uint32_t v___x_52_; 
v___x_52_ = 0;
v___y_38_ = v___x_51_;
v___y_39_ = v___y_46_;
v___y_40_ = v___x_52_;
goto v___jp_37_;
}
else
{
uint32_t v___x_53_; 
v___x_53_ = 2147483648;
v___y_38_ = v___x_51_;
v___y_39_ = v___y_46_;
v___y_40_ = v___x_53_;
goto v___jp_37_;
}
}
else
{
if (v___y_45_ == 0)
{
uint32_t v___x_54_; 
v___x_54_ = 0;
v___y_9_ = v___x_54_;
goto v___jp_8_;
}
else
{
uint32_t v___x_55_; 
v___x_55_ = 2147483648;
v___y_9_ = v___x_55_;
goto v___jp_8_;
}
}
}
else
{
if (v___y_45_ == 0)
{
uint32_t v___x_56_; 
v___x_56_ = 0;
return v___x_56_;
}
else
{
uint32_t v___x_57_; 
v___x_57_ = 2147483648;
return v___x_57_;
}
}
}
v___jp_58_:
{
if (v___y_59_ == 0)
{
uint32_t v___x_60_; 
v___x_60_ = lp_competition_Submission_FastMul_mul(v_x_6_, v_y_7_);
return v___x_60_;
}
else
{
uint32_t v___x_61_; uint32_t v___x_62_; 
v___x_61_ = 4194304;
v___x_62_ = lean_uint32_lor(v_y_7_, v___x_61_);
return v___x_62_;
}
}
v___jp_63_:
{
uint32_t v___x_64_; uint32_t v___x_65_; uint32_t v___x_66_; uint32_t v___x_67_; uint8_t v___x_68_; 
v___x_64_ = 23;
v___x_65_ = lean_uint32_shift_right(v_y_7_, v___x_64_);
v___x_66_ = 255;
v___x_67_ = lean_uint32_land(v___x_65_, v___x_66_);
v___x_68_ = lean_uint32_dec_eq(v___x_67_, v___x_66_);
if (v___x_68_ == 0)
{
v___y_59_ = v___x_68_;
goto v___jp_58_;
}
else
{
uint32_t v___x_69_; uint32_t v___x_70_; uint32_t v___x_71_; uint8_t v___x_72_; 
v___x_69_ = 8388607;
v___x_70_ = lean_uint32_land(v_y_7_, v___x_69_);
v___x_71_ = 0;
v___x_72_ = lean_uint32_dec_eq(v___x_70_, v___x_71_);
if (v___x_72_ == 0)
{
v___y_59_ = v___x_68_;
goto v___jp_58_;
}
else
{
uint32_t v___x_73_; 
v___x_73_ = lp_competition_Submission_FastMul_mul(v_x_6_, v_y_7_);
return v___x_73_;
}
}
}
v___jp_74_:
{
if (v___y_75_ == 0)
{
goto v___jp_63_;
}
else
{
uint32_t v___x_76_; uint32_t v___x_77_; 
v___x_76_ = 4194304;
v___x_77_ = lean_uint32_lor(v_x_6_, v___x_76_);
return v___x_77_;
}
}
v___jp_78_:
{
uint32_t v___x_79_; uint32_t v___x_80_; uint32_t v___x_81_; uint32_t v___x_82_; uint8_t v___x_83_; 
v___x_79_ = 23;
v___x_80_ = lean_uint32_shift_right(v_x_6_, v___x_79_);
v___x_81_ = 255;
v___x_82_ = lean_uint32_land(v___x_80_, v___x_81_);
v___x_83_ = lean_uint32_dec_eq(v___x_82_, v___x_81_);
if (v___x_83_ == 0)
{
v___y_75_ = v___x_83_;
goto v___jp_74_;
}
else
{
uint32_t v___x_84_; uint32_t v___x_85_; uint32_t v___x_86_; uint8_t v___x_87_; 
v___x_84_ = 8388607;
v___x_85_ = lean_uint32_land(v_x_6_, v___x_84_);
v___x_86_ = 0;
v___x_87_ = lean_uint32_dec_eq(v___x_85_, v___x_86_);
if (v___x_87_ == 0)
{
v___y_75_ = v___x_83_;
goto v___jp_74_;
}
else
{
goto v___jp_63_;
}
}
}
v___jp_88_:
{
if (v___y_89_ == 0)
{
goto v___jp_78_;
}
else
{
uint32_t v___x_90_; uint32_t v___x_91_; uint32_t v___x_92_; uint8_t v___x_93_; 
v___x_90_ = 4194304;
v___x_91_ = lean_uint32_land(v_y_7_, v___x_90_);
v___x_92_ = 0;
v___x_93_ = lean_uint32_dec_eq(v___x_91_, v___x_92_);
if (v___x_93_ == 0)
{
goto v___jp_78_;
}
else
{
uint32_t v___x_94_; 
v___x_94_ = lean_uint32_lor(v_y_7_, v___x_90_);
return v___x_94_;
}
}
}
v___jp_95_:
{
uint32_t v___x_96_; uint32_t v___x_97_; uint32_t v___x_98_; uint32_t v___x_99_; uint8_t v___x_100_; 
v___x_96_ = 23;
v___x_97_ = lean_uint32_shift_right(v_y_7_, v___x_96_);
v___x_98_ = 255;
v___x_99_ = lean_uint32_land(v___x_97_, v___x_98_);
v___x_100_ = lean_uint32_dec_eq(v___x_99_, v___x_98_);
if (v___x_100_ == 0)
{
v___y_89_ = v___x_100_;
goto v___jp_88_;
}
else
{
uint32_t v___x_101_; uint32_t v___x_102_; uint32_t v___x_103_; uint8_t v___x_104_; 
v___x_101_ = 8388607;
v___x_102_ = lean_uint32_land(v_y_7_, v___x_101_);
v___x_103_ = 0;
v___x_104_ = lean_uint32_dec_eq(v___x_102_, v___x_103_);
if (v___x_104_ == 0)
{
v___y_89_ = v___x_100_;
goto v___jp_88_;
}
else
{
goto v___jp_78_;
}
}
}
v___jp_105_:
{
if (v___y_106_ == 0)
{
goto v___jp_95_;
}
else
{
uint32_t v___x_107_; uint32_t v___x_108_; uint32_t v___x_109_; uint8_t v___x_110_; 
v___x_107_ = 4194304;
v___x_108_ = lean_uint32_land(v_x_6_, v___x_107_);
v___x_109_ = 0;
v___x_110_ = lean_uint32_dec_eq(v___x_108_, v___x_109_);
if (v___x_110_ == 0)
{
goto v___jp_95_;
}
else
{
uint32_t v___x_111_; 
v___x_111_ = lean_uint32_lor(v_x_6_, v___x_107_);
return v___x_111_;
}
}
}
v___jp_112_:
{
float v_result_115_; uint8_t v___x_116_; 
v_result_115_ = lean_float32_mul(v___y_113_, v___y_114_);
v___x_116_ = lean_float32_beq(v_result_115_, v_result_115_);
if (v___x_116_ == 0)
{
uint32_t v___x_117_; uint32_t v___x_118_; uint32_t v___x_119_; uint32_t v___x_120_; uint8_t v___x_121_; 
v___x_117_ = 23;
v___x_118_ = lean_uint32_shift_right(v_x_6_, v___x_117_);
v___x_119_ = 255;
v___x_120_ = lean_uint32_land(v___x_118_, v___x_119_);
v___x_121_ = lean_uint32_dec_eq(v___x_120_, v___x_119_);
if (v___x_121_ == 0)
{
v___y_106_ = v___x_121_;
goto v___jp_105_;
}
else
{
uint32_t v___x_122_; uint32_t v___x_123_; uint32_t v___x_124_; uint8_t v___x_125_; 
v___x_122_ = 8388607;
v___x_123_ = lean_uint32_land(v_x_6_, v___x_122_);
v___x_124_ = 0;
v___x_125_ = lean_uint32_dec_eq(v___x_123_, v___x_124_);
if (v___x_125_ == 0)
{
v___y_106_ = v___x_121_;
goto v___jp_105_;
}
else
{
goto v___jp_95_;
}
}
}
else
{
uint32_t v___x_126_; 
v___x_126_ = lean_float32_to_bits(v_result_115_);
return v___x_126_;
}
}
v___jp_127_:
{
if (v___y_129_ == 0)
{
float v___x_130_; 
v___x_130_ = lean_float32_of_bits(v_y_7_);
v___y_113_ = v___y_128_;
v___y_114_ = v___x_130_;
goto v___jp_112_;
}
else
{
uint32_t v___x_131_; uint32_t v___x_132_; uint32_t v___x_133_; uint32_t v___x_134_; float v___x_135_; lean_object* v___x_136_; uint32_t v___x_137_; uint32_t v___x_138_; lean_object* v___x_139_; lean_object* v___x_140_; float v___x_141_; float v___x_142_; 
v___x_131_ = 8388607;
v___x_132_ = lean_uint32_land(v_y_7_, v___x_131_);
v___x_133_ = 8388608;
v___x_134_ = lean_uint32_lor(v___x_132_, v___x_133_);
v___x_135_ = lean_uint32_to_float32(v___x_134_);
v___x_136_ = lp_competition_R2W01b_scaleTable;
v___x_137_ = 23;
v___x_138_ = lean_uint32_shift_right(v_y_7_, v___x_137_);
v___x_139_ = lean_uint32_to_nat(v___x_138_);
v___x_140_ = lean_array_fget_borrowed(v___x_136_, v___x_139_);
lean_dec(v___x_139_);
v___x_141_ = lean_unbox_float32(v___x_140_);
v___x_142_ = lean_float32_mul(v___x_135_, v___x_141_);
v___y_113_ = v___y_128_;
v___y_114_ = v___x_142_;
goto v___jp_112_;
}
}
v___jp_143_:
{
uint32_t v___x_145_; uint32_t v_a_146_; uint32_t v___x_147_; uint32_t v___x_148_; uint32_t v___x_149_; uint8_t v___x_150_; 
v___x_145_ = 2147483647;
v_a_146_ = lean_uint32_land(v_y_7_, v___x_145_);
v___x_147_ = 201326591;
v___x_148_ = 1;
v___x_149_ = lean_uint32_sub(v_a_146_, v___x_148_);
v___x_150_ = lean_uint32_dec_le(v___x_147_, v___x_149_);
if (v___x_150_ == 0)
{
v___y_128_ = v___y_144_;
v___y_129_ = v___x_150_;
goto v___jp_127_;
}
else
{
uint32_t v___x_151_; uint8_t v___x_152_; 
v___x_151_ = 2139095040;
v___x_152_ = lean_uint32_dec_lt(v_a_146_, v___x_151_);
v___y_128_ = v___y_144_;
v___y_129_ = v___x_152_;
goto v___jp_127_;
}
}
v___jp_153_:
{
uint32_t v___x_155_; uint32_t v___x_156_; 
v___x_155_ = 8388608;
v___x_156_ = lean_uint32_lor(v___y_154_, v___x_155_);
return v___x_156_;
}
v___jp_157_:
{
uint32_t v___x_159_; uint32_t v___x_160_; 
v___x_159_ = 8388608;
v___x_160_ = lean_uint32_lor(v___y_158_, v___x_159_);
return v___x_160_;
}
v___jp_161_:
{
uint32_t v___x_165_; uint32_t v___x_166_; 
v___x_165_ = lean_uint32_land(v___y_162_, v___y_163_);
v___x_166_ = lean_uint32_lor(v___y_164_, v___x_165_);
return v___x_166_;
}
v___jp_167_:
{
uint8_t v___x_172_; 
v___x_172_ = lean_uint64_dec_eq(v___y_171_, v___y_168_);
if (v___x_172_ == 0)
{
uint64_t v___x_173_; uint8_t v___x_174_; 
v___x_173_ = 8388608ULL;
v___x_174_ = lean_uint64_dec_eq(v___y_171_, v___x_173_);
if (v___x_174_ == 0)
{
uint32_t v___x_175_; 
v___x_175_ = lean_uint64_to_uint32(v___y_171_);
if (v___y_169_ == 0)
{
uint32_t v___x_176_; 
v___x_176_ = 0;
v___y_162_ = v___x_175_;
v___y_163_ = v___y_170_;
v___y_164_ = v___x_176_;
goto v___jp_161_;
}
else
{
uint32_t v___x_177_; 
v___x_177_ = 2147483648;
v___y_162_ = v___x_175_;
v___y_163_ = v___y_170_;
v___y_164_ = v___x_177_;
goto v___jp_161_;
}
}
else
{
if (v___y_169_ == 0)
{
uint32_t v___x_178_; 
v___x_178_ = 0;
v___y_154_ = v___x_178_;
goto v___jp_153_;
}
else
{
uint32_t v___x_179_; 
v___x_179_ = 2147483648;
v___y_154_ = v___x_179_;
goto v___jp_153_;
}
}
}
else
{
if (v___y_169_ == 0)
{
uint32_t v___x_180_; 
v___x_180_ = 0;
return v___x_180_;
}
else
{
uint32_t v___x_181_; 
v___x_181_ = 2147483648;
return v___x_181_;
}
}
}
v___jp_182_:
{
uint32_t v___x_186_; uint32_t v___x_187_; 
v___x_186_ = lean_uint32_land(v___y_183_, v___y_184_);
v___x_187_ = lean_uint32_lor(v___y_185_, v___x_186_);
return v___x_187_;
}
v___jp_188_:
{
uint8_t v___x_193_; 
v___x_193_ = lean_uint64_dec_eq(v___y_192_, v___y_191_);
if (v___x_193_ == 0)
{
uint64_t v___x_194_; uint8_t v___x_195_; 
v___x_194_ = 8388608ULL;
v___x_195_ = lean_uint64_dec_eq(v___y_192_, v___x_194_);
if (v___x_195_ == 0)
{
uint32_t v___x_196_; 
v___x_196_ = lean_uint64_to_uint32(v___y_192_);
if (v___y_189_ == 0)
{
uint32_t v___x_197_; 
v___x_197_ = 0;
v___y_183_ = v___x_196_;
v___y_184_ = v___y_190_;
v___y_185_ = v___x_197_;
goto v___jp_182_;
}
else
{
uint32_t v___x_198_; 
v___x_198_ = 2147483648;
v___y_183_ = v___x_196_;
v___y_184_ = v___y_190_;
v___y_185_ = v___x_198_;
goto v___jp_182_;
}
}
else
{
if (v___y_189_ == 0)
{
uint32_t v___x_199_; 
v___x_199_ = 0;
v___y_158_ = v___x_199_;
goto v___jp_157_;
}
else
{
uint32_t v___x_200_; 
v___x_200_ = 2147483648;
v___y_158_ = v___x_200_;
goto v___jp_157_;
}
}
}
else
{
if (v___y_189_ == 0)
{
uint32_t v___x_201_; 
v___x_201_ = 0;
return v___x_201_;
}
else
{
uint32_t v___x_202_; 
v___x_202_ = 2147483648;
return v___x_202_;
}
}
}
v___jp_203_:
{
if (v___y_204_ == 0)
{
uint32_t v___x_205_; 
v___x_205_ = lp_competition_Submission_FastMul_mul(v_x_6_, v_y_7_);
return v___x_205_;
}
else
{
uint32_t v___x_206_; uint32_t v___x_207_; 
v___x_206_ = 4194304;
v___x_207_ = lean_uint32_lor(v_y_7_, v___x_206_);
return v___x_207_;
}
}
v___jp_208_:
{
uint32_t v___x_209_; uint32_t v___x_210_; uint32_t v___x_211_; uint32_t v___x_212_; uint8_t v___x_213_; 
v___x_209_ = 23;
v___x_210_ = lean_uint32_shift_right(v_y_7_, v___x_209_);
v___x_211_ = 255;
v___x_212_ = lean_uint32_land(v___x_210_, v___x_211_);
v___x_213_ = lean_uint32_dec_eq(v___x_212_, v___x_211_);
if (v___x_213_ == 0)
{
v___y_204_ = v___x_213_;
goto v___jp_203_;
}
else
{
uint32_t v___x_214_; uint32_t v___x_215_; uint32_t v___x_216_; uint8_t v___x_217_; 
v___x_214_ = 8388607;
v___x_215_ = lean_uint32_land(v_y_7_, v___x_214_);
v___x_216_ = 0;
v___x_217_ = lean_uint32_dec_eq(v___x_215_, v___x_216_);
if (v___x_217_ == 0)
{
v___y_204_ = v___x_213_;
goto v___jp_203_;
}
else
{
uint32_t v___x_218_; 
v___x_218_ = lp_competition_Submission_FastMul_mul(v_x_6_, v_y_7_);
return v___x_218_;
}
}
}
v___jp_219_:
{
if (v___y_220_ == 0)
{
goto v___jp_208_;
}
else
{
uint32_t v___x_221_; uint32_t v___x_222_; 
v___x_221_ = 4194304;
v___x_222_ = lean_uint32_lor(v_x_6_, v___x_221_);
return v___x_222_;
}
}
v___jp_223_:
{
uint32_t v___x_224_; uint32_t v___x_225_; uint32_t v___x_226_; uint32_t v___x_227_; uint8_t v___x_228_; 
v___x_224_ = 23;
v___x_225_ = lean_uint32_shift_right(v_x_6_, v___x_224_);
v___x_226_ = 255;
v___x_227_ = lean_uint32_land(v___x_225_, v___x_226_);
v___x_228_ = lean_uint32_dec_eq(v___x_227_, v___x_226_);
if (v___x_228_ == 0)
{
v___y_220_ = v___x_228_;
goto v___jp_219_;
}
else
{
uint32_t v___x_229_; uint32_t v___x_230_; uint32_t v___x_231_; uint8_t v___x_232_; 
v___x_229_ = 8388607;
v___x_230_ = lean_uint32_land(v_x_6_, v___x_229_);
v___x_231_ = 0;
v___x_232_ = lean_uint32_dec_eq(v___x_230_, v___x_231_);
if (v___x_232_ == 0)
{
v___y_220_ = v___x_228_;
goto v___jp_219_;
}
else
{
goto v___jp_208_;
}
}
}
v___jp_233_:
{
if (v___y_234_ == 0)
{
goto v___jp_223_;
}
else
{
uint32_t v___x_235_; uint32_t v___x_236_; uint32_t v___x_237_; uint8_t v___x_238_; 
v___x_235_ = 4194304;
v___x_236_ = lean_uint32_land(v_y_7_, v___x_235_);
v___x_237_ = 0;
v___x_238_ = lean_uint32_dec_eq(v___x_236_, v___x_237_);
if (v___x_238_ == 0)
{
goto v___jp_223_;
}
else
{
uint32_t v___x_239_; 
v___x_239_ = lean_uint32_lor(v_y_7_, v___x_235_);
return v___x_239_;
}
}
}
v___jp_240_:
{
uint32_t v___x_241_; uint32_t v___x_242_; uint32_t v___x_243_; uint32_t v___x_244_; uint8_t v___x_245_; 
v___x_241_ = 23;
v___x_242_ = lean_uint32_shift_right(v_y_7_, v___x_241_);
v___x_243_ = 255;
v___x_244_ = lean_uint32_land(v___x_242_, v___x_243_);
v___x_245_ = lean_uint32_dec_eq(v___x_244_, v___x_243_);
if (v___x_245_ == 0)
{
v___y_234_ = v___x_245_;
goto v___jp_233_;
}
else
{
uint32_t v___x_246_; uint32_t v___x_247_; uint32_t v___x_248_; uint8_t v___x_249_; 
v___x_246_ = 8388607;
v___x_247_ = lean_uint32_land(v_y_7_, v___x_246_);
v___x_248_ = 0;
v___x_249_ = lean_uint32_dec_eq(v___x_247_, v___x_248_);
if (v___x_249_ == 0)
{
v___y_234_ = v___x_245_;
goto v___jp_233_;
}
else
{
goto v___jp_223_;
}
}
}
v___jp_250_:
{
if (v___y_251_ == 0)
{
goto v___jp_240_;
}
else
{
uint32_t v___x_252_; uint32_t v___x_253_; uint32_t v___x_254_; uint8_t v___x_255_; 
v___x_252_ = 4194304;
v___x_253_ = lean_uint32_land(v_x_6_, v___x_252_);
v___x_254_ = 0;
v___x_255_ = lean_uint32_dec_eq(v___x_253_, v___x_254_);
if (v___x_255_ == 0)
{
goto v___jp_240_;
}
else
{
uint32_t v___x_256_; 
v___x_256_ = lean_uint32_lor(v_x_6_, v___x_252_);
return v___x_256_;
}
}
}
v___jp_257_:
{
float v_result_260_; uint8_t v___x_261_; 
v_result_260_ = lean_float32_mul(v___y_258_, v___y_259_);
v___x_261_ = lean_float32_beq(v_result_260_, v_result_260_);
if (v___x_261_ == 0)
{
uint32_t v___x_262_; uint32_t v___x_263_; uint32_t v___x_264_; uint32_t v___x_265_; uint8_t v___x_266_; 
v___x_262_ = 23;
v___x_263_ = lean_uint32_shift_right(v_x_6_, v___x_262_);
v___x_264_ = 255;
v___x_265_ = lean_uint32_land(v___x_263_, v___x_264_);
v___x_266_ = lean_uint32_dec_eq(v___x_265_, v___x_264_);
if (v___x_266_ == 0)
{
v___y_251_ = v___x_266_;
goto v___jp_250_;
}
else
{
uint32_t v___x_267_; uint32_t v___x_268_; uint32_t v___x_269_; uint8_t v___x_270_; 
v___x_267_ = 8388607;
v___x_268_ = lean_uint32_land(v_x_6_, v___x_267_);
v___x_269_ = 0;
v___x_270_ = lean_uint32_dec_eq(v___x_268_, v___x_269_);
if (v___x_270_ == 0)
{
v___y_251_ = v___x_266_;
goto v___jp_250_;
}
else
{
goto v___jp_240_;
}
}
}
else
{
uint32_t v___x_271_; 
v___x_271_ = lean_float32_to_bits(v_result_260_);
return v___x_271_;
}
}
v___jp_272_:
{
if (v___y_274_ == 0)
{
float v___x_275_; 
v___x_275_ = lean_float32_of_bits(v_y_7_);
v___y_258_ = v___y_273_;
v___y_259_ = v___x_275_;
goto v___jp_257_;
}
else
{
uint32_t v___x_276_; uint32_t v___x_277_; uint32_t v___x_278_; uint32_t v___x_279_; float v___x_280_; lean_object* v___x_281_; uint32_t v___x_282_; uint32_t v___x_283_; lean_object* v___x_284_; lean_object* v___x_285_; float v___x_286_; float v___x_287_; 
v___x_276_ = 8388607;
v___x_277_ = lean_uint32_land(v_y_7_, v___x_276_);
v___x_278_ = 8388608;
v___x_279_ = lean_uint32_lor(v___x_277_, v___x_278_);
v___x_280_ = lean_uint32_to_float32(v___x_279_);
v___x_281_ = lp_competition_R2W01b_scaleTable;
v___x_282_ = 23;
v___x_283_ = lean_uint32_shift_right(v_y_7_, v___x_282_);
v___x_284_ = lean_uint32_to_nat(v___x_283_);
v___x_285_ = lean_array_fget_borrowed(v___x_281_, v___x_284_);
lean_dec(v___x_284_);
v___x_286_ = lean_unbox_float32(v___x_285_);
v___x_287_ = lean_float32_mul(v___x_280_, v___x_286_);
v___y_258_ = v___y_273_;
v___y_259_ = v___x_287_;
goto v___jp_257_;
}
}
v___jp_288_:
{
uint32_t v___x_290_; uint32_t v_a_291_; uint32_t v___x_292_; uint32_t v___x_293_; uint32_t v___x_294_; uint8_t v___x_295_; 
v___x_290_ = 2147483647;
v_a_291_ = lean_uint32_land(v_y_7_, v___x_290_);
v___x_292_ = 201326591;
v___x_293_ = 1;
v___x_294_ = lean_uint32_sub(v_a_291_, v___x_293_);
v___x_295_ = lean_uint32_dec_le(v___x_292_, v___x_294_);
if (v___x_295_ == 0)
{
v___y_273_ = v___y_289_;
v___y_274_ = v___x_295_;
goto v___jp_272_;
}
else
{
uint32_t v___x_296_; uint8_t v___x_297_; 
v___x_296_ = 2139095040;
v___x_297_ = lean_uint32_dec_lt(v_a_291_, v___x_296_);
v___y_273_ = v___y_289_;
v___y_274_ = v___x_297_;
goto v___jp_272_;
}
}
v___jp_298_:
{
uint32_t v___x_300_; uint32_t v___x_301_; 
v___x_300_ = 8388608;
v___x_301_ = lean_uint32_lor(v___y_299_, v___x_300_);
return v___x_301_;
}
v___jp_302_:
{
uint32_t v___x_304_; uint32_t v___x_305_; 
v___x_304_ = 8388608;
v___x_305_ = lean_uint32_lor(v___y_303_, v___x_304_);
return v___x_305_;
}
v___jp_306_:
{
uint32_t v___x_310_; uint32_t v___x_311_; 
v___x_310_ = lean_uint32_land(v___y_308_, v___y_307_);
v___x_311_ = lean_uint32_lor(v___y_309_, v___x_310_);
return v___x_311_;
}
v___jp_312_:
{
uint8_t v___x_317_; 
v___x_317_ = lean_uint64_dec_eq(v___y_316_, v___y_315_);
if (v___x_317_ == 0)
{
uint64_t v___x_318_; uint8_t v___x_319_; 
v___x_318_ = 8388608ULL;
v___x_319_ = lean_uint64_dec_eq(v___y_316_, v___x_318_);
if (v___x_319_ == 0)
{
uint32_t v___x_320_; 
v___x_320_ = lean_uint64_to_uint32(v___y_316_);
if (v___y_314_ == 0)
{
uint32_t v___x_321_; 
v___x_321_ = 0;
v___y_307_ = v___y_313_;
v___y_308_ = v___x_320_;
v___y_309_ = v___x_321_;
goto v___jp_306_;
}
else
{
uint32_t v___x_322_; 
v___x_322_ = 2147483648;
v___y_307_ = v___y_313_;
v___y_308_ = v___x_320_;
v___y_309_ = v___x_322_;
goto v___jp_306_;
}
}
else
{
if (v___y_314_ == 0)
{
uint32_t v___x_323_; 
v___x_323_ = 0;
v___y_303_ = v___x_323_;
goto v___jp_302_;
}
else
{
uint32_t v___x_324_; 
v___x_324_ = 2147483648;
v___y_303_ = v___x_324_;
goto v___jp_302_;
}
}
}
else
{
if (v___y_314_ == 0)
{
uint32_t v___x_325_; 
v___x_325_ = 0;
return v___x_325_;
}
else
{
uint32_t v___x_326_; 
v___x_326_ = 2147483648;
return v___x_326_;
}
}
}
v___jp_327_:
{
uint32_t v___x_331_; uint32_t v___x_332_; 
v___x_331_ = lean_uint32_land(v___y_329_, v___y_328_);
v___x_332_ = lean_uint32_lor(v___y_330_, v___x_331_);
return v___x_332_;
}
v___jp_333_:
{
uint8_t v___x_338_; 
v___x_338_ = lean_uint64_dec_eq(v___y_337_, v___y_334_);
if (v___x_338_ == 0)
{
uint64_t v___x_339_; uint8_t v___x_340_; 
v___x_339_ = 8388608ULL;
v___x_340_ = lean_uint64_dec_eq(v___y_337_, v___x_339_);
if (v___x_340_ == 0)
{
uint32_t v___x_341_; 
v___x_341_ = lean_uint64_to_uint32(v___y_337_);
if (v___y_336_ == 0)
{
uint32_t v___x_342_; 
v___x_342_ = 0;
v___y_328_ = v___y_335_;
v___y_329_ = v___x_341_;
v___y_330_ = v___x_342_;
goto v___jp_327_;
}
else
{
uint32_t v___x_343_; 
v___x_343_ = 2147483648;
v___y_328_ = v___y_335_;
v___y_329_ = v___x_341_;
v___y_330_ = v___x_343_;
goto v___jp_327_;
}
}
else
{
if (v___y_336_ == 0)
{
uint32_t v___x_344_; 
v___x_344_ = 0;
v___y_299_ = v___x_344_;
goto v___jp_298_;
}
else
{
uint32_t v___x_345_; 
v___x_345_ = 2147483648;
v___y_299_ = v___x_345_;
goto v___jp_298_;
}
}
}
else
{
if (v___y_336_ == 0)
{
uint32_t v___x_346_; 
v___x_346_ = 0;
return v___x_346_;
}
else
{
uint32_t v___x_347_; 
v___x_347_ = 2147483648;
return v___x_347_;
}
}
}
v___jp_348_:
{
if (v___y_349_ == 0)
{
uint32_t v___x_350_; 
v___x_350_ = lp_competition_Submission_FastMul_mul(v_x_6_, v_y_7_);
return v___x_350_;
}
else
{
uint32_t v___x_351_; uint32_t v___x_352_; 
v___x_351_ = 4194304;
v___x_352_ = lean_uint32_lor(v_y_7_, v___x_351_);
return v___x_352_;
}
}
v___jp_353_:
{
uint32_t v___x_354_; uint32_t v___x_355_; uint32_t v___x_356_; uint32_t v___x_357_; uint8_t v___x_358_; 
v___x_354_ = 23;
v___x_355_ = lean_uint32_shift_right(v_y_7_, v___x_354_);
v___x_356_ = 255;
v___x_357_ = lean_uint32_land(v___x_355_, v___x_356_);
v___x_358_ = lean_uint32_dec_eq(v___x_357_, v___x_356_);
if (v___x_358_ == 0)
{
v___y_349_ = v___x_358_;
goto v___jp_348_;
}
else
{
uint32_t v___x_359_; uint32_t v___x_360_; uint32_t v___x_361_; uint8_t v___x_362_; 
v___x_359_ = 8388607;
v___x_360_ = lean_uint32_land(v_y_7_, v___x_359_);
v___x_361_ = 0;
v___x_362_ = lean_uint32_dec_eq(v___x_360_, v___x_361_);
if (v___x_362_ == 0)
{
v___y_349_ = v___x_358_;
goto v___jp_348_;
}
else
{
uint32_t v___x_363_; 
v___x_363_ = lp_competition_Submission_FastMul_mul(v_x_6_, v_y_7_);
return v___x_363_;
}
}
}
v___jp_364_:
{
if (v___y_365_ == 0)
{
goto v___jp_353_;
}
else
{
uint32_t v___x_366_; uint32_t v___x_367_; 
v___x_366_ = 4194304;
v___x_367_ = lean_uint32_lor(v_x_6_, v___x_366_);
return v___x_367_;
}
}
v___jp_368_:
{
uint32_t v___x_369_; uint32_t v___x_370_; uint32_t v___x_371_; uint32_t v___x_372_; uint8_t v___x_373_; 
v___x_369_ = 23;
v___x_370_ = lean_uint32_shift_right(v_x_6_, v___x_369_);
v___x_371_ = 255;
v___x_372_ = lean_uint32_land(v___x_370_, v___x_371_);
v___x_373_ = lean_uint32_dec_eq(v___x_372_, v___x_371_);
if (v___x_373_ == 0)
{
v___y_365_ = v___x_373_;
goto v___jp_364_;
}
else
{
uint32_t v___x_374_; uint32_t v___x_375_; uint32_t v___x_376_; uint8_t v___x_377_; 
v___x_374_ = 8388607;
v___x_375_ = lean_uint32_land(v_x_6_, v___x_374_);
v___x_376_ = 0;
v___x_377_ = lean_uint32_dec_eq(v___x_375_, v___x_376_);
if (v___x_377_ == 0)
{
v___y_365_ = v___x_373_;
goto v___jp_364_;
}
else
{
goto v___jp_353_;
}
}
}
v___jp_378_:
{
if (v___y_379_ == 0)
{
goto v___jp_368_;
}
else
{
uint32_t v___x_380_; uint32_t v___x_381_; uint32_t v___x_382_; uint8_t v___x_383_; 
v___x_380_ = 4194304;
v___x_381_ = lean_uint32_land(v_y_7_, v___x_380_);
v___x_382_ = 0;
v___x_383_ = lean_uint32_dec_eq(v___x_381_, v___x_382_);
if (v___x_383_ == 0)
{
goto v___jp_368_;
}
else
{
uint32_t v___x_384_; 
v___x_384_ = lean_uint32_lor(v_y_7_, v___x_380_);
return v___x_384_;
}
}
}
v___jp_385_:
{
uint32_t v___x_386_; uint32_t v___x_387_; uint32_t v___x_388_; uint32_t v___x_389_; uint8_t v___x_390_; 
v___x_386_ = 23;
v___x_387_ = lean_uint32_shift_right(v_y_7_, v___x_386_);
v___x_388_ = 255;
v___x_389_ = lean_uint32_land(v___x_387_, v___x_388_);
v___x_390_ = lean_uint32_dec_eq(v___x_389_, v___x_388_);
if (v___x_390_ == 0)
{
v___y_379_ = v___x_390_;
goto v___jp_378_;
}
else
{
uint32_t v___x_391_; uint32_t v___x_392_; uint32_t v___x_393_; uint8_t v___x_394_; 
v___x_391_ = 8388607;
v___x_392_ = lean_uint32_land(v_y_7_, v___x_391_);
v___x_393_ = 0;
v___x_394_ = lean_uint32_dec_eq(v___x_392_, v___x_393_);
if (v___x_394_ == 0)
{
v___y_379_ = v___x_390_;
goto v___jp_378_;
}
else
{
goto v___jp_368_;
}
}
}
v___jp_395_:
{
if (v___y_396_ == 0)
{
goto v___jp_385_;
}
else
{
uint32_t v___x_397_; uint32_t v___x_398_; uint32_t v___x_399_; uint8_t v___x_400_; 
v___x_397_ = 4194304;
v___x_398_ = lean_uint32_land(v_x_6_, v___x_397_);
v___x_399_ = 0;
v___x_400_ = lean_uint32_dec_eq(v___x_398_, v___x_399_);
if (v___x_400_ == 0)
{
goto v___jp_385_;
}
else
{
uint32_t v___x_401_; 
v___x_401_ = lean_uint32_lor(v_x_6_, v___x_397_);
return v___x_401_;
}
}
}
v___jp_402_:
{
float v_result_405_; uint8_t v___x_406_; 
v_result_405_ = lean_float32_mul(v___y_403_, v___y_404_);
v___x_406_ = lean_float32_beq(v_result_405_, v_result_405_);
if (v___x_406_ == 0)
{
uint32_t v___x_407_; uint32_t v___x_408_; uint32_t v___x_409_; uint32_t v___x_410_; uint8_t v___x_411_; 
v___x_407_ = 23;
v___x_408_ = lean_uint32_shift_right(v_x_6_, v___x_407_);
v___x_409_ = 255;
v___x_410_ = lean_uint32_land(v___x_408_, v___x_409_);
v___x_411_ = lean_uint32_dec_eq(v___x_410_, v___x_409_);
if (v___x_411_ == 0)
{
v___y_396_ = v___x_411_;
goto v___jp_395_;
}
else
{
uint32_t v___x_412_; uint32_t v___x_413_; uint32_t v___x_414_; uint8_t v___x_415_; 
v___x_412_ = 8388607;
v___x_413_ = lean_uint32_land(v_x_6_, v___x_412_);
v___x_414_ = 0;
v___x_415_ = lean_uint32_dec_eq(v___x_413_, v___x_414_);
if (v___x_415_ == 0)
{
v___y_396_ = v___x_411_;
goto v___jp_395_;
}
else
{
goto v___jp_385_;
}
}
}
else
{
uint32_t v___x_416_; 
v___x_416_ = lean_float32_to_bits(v_result_405_);
return v___x_416_;
}
}
v___jp_417_:
{
if (v___y_419_ == 0)
{
float v___x_420_; 
v___x_420_ = lean_float32_of_bits(v_y_7_);
v___y_403_ = v___y_418_;
v___y_404_ = v___x_420_;
goto v___jp_402_;
}
else
{
uint32_t v___x_421_; uint32_t v___x_422_; uint32_t v___x_423_; uint32_t v___x_424_; float v___x_425_; lean_object* v___x_426_; uint32_t v___x_427_; uint32_t v___x_428_; lean_object* v___x_429_; lean_object* v___x_430_; float v___x_431_; float v___x_432_; 
v___x_421_ = 8388607;
v___x_422_ = lean_uint32_land(v_y_7_, v___x_421_);
v___x_423_ = 8388608;
v___x_424_ = lean_uint32_lor(v___x_422_, v___x_423_);
v___x_425_ = lean_uint32_to_float32(v___x_424_);
v___x_426_ = lp_competition_R2W01b_scaleTable;
v___x_427_ = 23;
v___x_428_ = lean_uint32_shift_right(v_y_7_, v___x_427_);
v___x_429_ = lean_uint32_to_nat(v___x_428_);
v___x_430_ = lean_array_fget_borrowed(v___x_426_, v___x_429_);
lean_dec(v___x_429_);
v___x_431_ = lean_unbox_float32(v___x_430_);
v___x_432_ = lean_float32_mul(v___x_425_, v___x_431_);
v___y_403_ = v___y_418_;
v___y_404_ = v___x_432_;
goto v___jp_402_;
}
}
v___jp_433_:
{
uint32_t v___x_435_; uint32_t v_a_436_; uint32_t v___x_437_; uint32_t v___x_438_; uint32_t v___x_439_; uint8_t v___x_440_; 
v___x_435_ = 2147483647;
v_a_436_ = lean_uint32_land(v_y_7_, v___x_435_);
v___x_437_ = 201326591;
v___x_438_ = 1;
v___x_439_ = lean_uint32_sub(v_a_436_, v___x_438_);
v___x_440_ = lean_uint32_dec_le(v___x_437_, v___x_439_);
if (v___x_440_ == 0)
{
v___y_418_ = v___y_434_;
v___y_419_ = v___x_440_;
goto v___jp_417_;
}
else
{
uint32_t v___x_441_; uint8_t v___x_442_; 
v___x_441_ = 2139095040;
v___x_442_ = lean_uint32_dec_lt(v_a_436_, v___x_441_);
v___y_418_ = v___y_434_;
v___y_419_ = v___x_442_;
goto v___jp_417_;
}
}
v___jp_445_:
{
if (v___y_446_ == 0)
{
float v___x_447_; 
v___x_447_ = lean_float32_of_bits(v_x_6_);
v___y_144_ = v___x_447_;
goto v___jp_143_;
}
else
{
uint32_t v___x_448_; uint32_t v___x_449_; uint32_t v___x_450_; uint32_t v___x_451_; float v___x_452_; lean_object* v___x_453_; lean_object* v___x_454_; lean_object* v___x_455_; float v___x_456_; float v___x_457_; 
v___x_448_ = 8388607;
v___x_449_ = lean_uint32_land(v_x_6_, v___x_448_);
v___x_450_ = 8388608;
v___x_451_ = lean_uint32_lor(v___x_449_, v___x_450_);
v___x_452_ = lean_uint32_to_float32(v___x_451_);
v___x_453_ = lp_competition_R2W01b_scaleTable;
v___x_454_ = lean_uint32_to_nat(v___x_444_);
v___x_455_ = lean_array_fget_borrowed(v___x_453_, v___x_454_);
lean_dec(v___x_454_);
v___x_456_ = lean_unbox_float32(v___x_455_);
v___x_457_ = lean_float32_mul(v___x_452_, v___x_456_);
v___y_144_ = v___x_457_;
goto v___jp_143_;
}
}
v___jp_458_:
{
if (v___y_459_ == 0)
{
float v___x_460_; 
v___x_460_ = lean_float32_of_bits(v_x_6_);
v___y_289_ = v___x_460_;
goto v___jp_288_;
}
else
{
uint32_t v___x_461_; uint32_t v___x_462_; uint32_t v___x_463_; uint32_t v___x_464_; float v___x_465_; lean_object* v___x_466_; lean_object* v___x_467_; lean_object* v___x_468_; float v___x_469_; float v___x_470_; 
v___x_461_ = 8388607;
v___x_462_ = lean_uint32_land(v_x_6_, v___x_461_);
v___x_463_ = 8388608;
v___x_464_ = lean_uint32_lor(v___x_462_, v___x_463_);
v___x_465_ = lean_uint32_to_float32(v___x_464_);
v___x_466_ = lp_competition_R2W01b_scaleTable;
v___x_467_ = lean_uint32_to_nat(v___x_444_);
v___x_468_ = lean_array_fget_borrowed(v___x_466_, v___x_467_);
lean_dec(v___x_467_);
v___x_469_ = lean_unbox_float32(v___x_468_);
v___x_470_ = lean_float32_mul(v___x_465_, v___x_469_);
v___y_289_ = v___x_470_;
goto v___jp_288_;
}
}
v___jp_471_:
{
if (v___y_472_ == 0)
{
float v___x_473_; 
v___x_473_ = lean_float32_of_bits(v_x_6_);
v___y_434_ = v___x_473_;
goto v___jp_433_;
}
else
{
uint32_t v___x_474_; uint32_t v___x_475_; uint32_t v___x_476_; uint32_t v___x_477_; float v___x_478_; lean_object* v___x_479_; lean_object* v___x_480_; lean_object* v___x_481_; float v___x_482_; float v___x_483_; 
v___x_474_ = 8388607;
v___x_475_ = lean_uint32_land(v_x_6_, v___x_474_);
v___x_476_ = 8388608;
v___x_477_ = lean_uint32_lor(v___x_475_, v___x_476_);
v___x_478_ = lean_uint32_to_float32(v___x_477_);
v___x_479_ = lp_competition_R2W01b_scaleTable;
v___x_480_ = lean_uint32_to_nat(v___x_444_);
v___x_481_ = lean_array_fget_borrowed(v___x_479_, v___x_480_);
lean_dec(v___x_480_);
v___x_482_ = lean_unbox_float32(v___x_481_);
v___x_483_ = lean_float32_mul(v___x_478_, v___x_482_);
v___y_434_ = v___x_483_;
goto v___jp_433_;
}
}
v___jp_485_:
{
uint32_t v___x_490_; uint32_t v___x_491_; uint32_t v___x_492_; uint32_t v___x_493_; uint32_t v___x_494_; 
v___x_490_ = lean_uint32_land(v___y_486_, v___x_484_);
v___x_491_ = lean_uint32_shift_left(v___x_490_, v___x_443_);
v___x_492_ = lean_uint32_lor(v___y_489_, v___x_491_);
v___x_493_ = lean_uint32_land(v___y_487_, v___y_488_);
v___x_494_ = lean_uint32_lor(v___x_492_, v___x_493_);
return v___x_494_;
}
v___jp_495_:
{
if (v___y_497_ == 0)
{
uint32_t v___x_500_; 
v___x_500_ = 0;
v___y_486_ = v___y_496_;
v___y_487_ = v___y_499_;
v___y_488_ = v___y_498_;
v___y_489_ = v___x_500_;
goto v___jp_485_;
}
else
{
uint32_t v___x_501_; 
v___x_501_ = 2147483648;
v___y_486_ = v___y_496_;
v___y_487_ = v___y_499_;
v___y_488_ = v___y_498_;
v___y_489_ = v___x_501_;
goto v___jp_485_;
}
}
v___jp_502_:
{
uint64_t v___x_508_; uint64_t v_encodedExponent_509_; uint32_t v___x_510_; uint64_t v___x_511_; uint8_t v___x_512_; 
v___x_508_ = 171ULL;
v_encodedExponent_509_ = lean_uint64_sub(v___y_503_, v___x_508_);
v___x_510_ = lean_uint64_to_uint32(v_encodedExponent_509_);
v___x_511_ = 8388608ULL;
v___x_512_ = lean_uint64_dec_lt(v___y_507_, v___x_511_);
if (v___x_512_ == 0)
{
uint64_t v___x_513_; uint32_t v___x_514_; 
v___x_513_ = lean_uint64_sub(v___y_507_, v___x_511_);
v___x_514_ = lean_uint64_to_uint32(v___x_513_);
v___y_496_ = v___x_510_;
v___y_497_ = v___y_506_;
v___y_498_ = v___y_505_;
v___y_499_ = v___x_514_;
goto v___jp_495_;
}
else
{
uint32_t v___x_515_; 
v___x_515_ = lean_uint64_to_uint32(v___y_504_);
v___y_496_ = v___x_510_;
v___y_497_ = v___y_506_;
v___y_498_ = v___y_505_;
v___y_499_ = v___x_515_;
goto v___jp_495_;
}
}
v___jp_516_:
{
uint64_t v___x_523_; uint8_t v___x_524_; 
v___x_523_ = 425ULL;
v___x_524_ = lean_uint64_dec_lt(v___x_523_, v___y_522_);
if (v___x_524_ == 0)
{
if (v___y_517_ == 0)
{
v___y_503_ = v___y_522_;
v___y_504_ = v___y_518_;
v___y_505_ = v___y_521_;
v___y_506_ = v___y_520_;
v___y_507_ = v___y_519_;
goto v___jp_502_;
}
else
{
uint64_t v___x_525_; 
v___x_525_ = 8388608ULL;
v___y_503_ = v___y_522_;
v___y_504_ = v___y_518_;
v___y_505_ = v___y_521_;
v___y_506_ = v___y_520_;
v___y_507_ = v___x_525_;
goto v___jp_502_;
}
}
else
{
if (v___y_520_ == 0)
{
uint32_t v___x_526_; 
v___x_526_ = 2139095040;
return v___x_526_;
}
else
{
uint32_t v___x_527_; 
v___x_527_ = 4286578688;
return v___x_527_;
}
}
}
v___jp_528_:
{
uint64_t v___x_534_; uint8_t v_carry_535_; 
v___x_534_ = 16777216ULL;
v_carry_535_ = lean_uint64_dec_eq(v___y_533_, v___x_534_);
if (v_carry_535_ == 0)
{
v___y_517_ = v_carry_535_;
v___y_518_ = v___y_529_;
v___y_519_ = v___y_533_;
v___y_520_ = v___y_532_;
v___y_521_ = v___y_531_;
v___y_522_ = v___y_530_;
goto v___jp_516_;
}
else
{
uint64_t v___x_536_; uint64_t v___x_537_; 
v___x_536_ = 1ULL;
v___x_537_ = lean_uint64_add(v___y_530_, v___x_536_);
v___y_517_ = v_carry_535_;
v___y_518_ = v___y_529_;
v___y_519_ = v___y_533_;
v___y_520_ = v___y_532_;
v___y_521_ = v___y_531_;
v___y_522_ = v___x_537_;
goto v___jp_516_;
}
}
v___jp_538_:
{
uint64_t v_position_545_; uint64_t v___x_546_; uint8_t v___x_547_; 
v_position_545_ = lean_uint64_add(v___y_544_, v___y_541_);
v___x_546_ = 172ULL;
v___x_547_ = lean_uint64_dec_lt(v_position_545_, v___x_546_);
if (v___x_547_ == 0)
{
uint64_t v___x_548_; uint8_t v___x_549_; 
v___x_548_ = 23ULL;
v___x_549_ = lean_uint64_dec_lt(v___y_544_, v___x_548_);
if (v___x_549_ == 0)
{
uint64_t v___x_550_; uint8_t v___x_551_; 
v___x_550_ = lean_uint64_sub(v___y_544_, v___x_548_);
v___x_551_ = lean_uint64_dec_eq(v___x_550_, v___y_539_);
if (v___x_551_ == 0)
{
uint64_t v___x_552_; uint8_t v___x_553_; 
v___x_552_ = 64ULL;
v___x_553_ = lean_uint64_dec_lt(v___x_550_, v___x_552_);
if (v___x_553_ == 0)
{
uint8_t v___x_554_; 
v___x_554_ = lean_uint64_dec_eq(v___x_550_, v___x_552_);
if (v___x_554_ == 0)
{
v___y_529_ = v___y_539_;
v___y_530_ = v_position_545_;
v___y_531_ = v___y_543_;
v___y_532_ = v___y_542_;
v___y_533_ = v___y_539_;
goto v___jp_528_;
}
else
{
uint64_t v___x_555_; uint8_t v___x_556_; 
v___x_555_ = 9223372036854775808ULL;
v___x_556_ = lean_uint64_dec_lt(v___x_555_, v___y_540_);
if (v___x_556_ == 0)
{
v___y_529_ = v___y_539_;
v___y_530_ = v_position_545_;
v___y_531_ = v___y_543_;
v___y_532_ = v___y_542_;
v___y_533_ = v___y_539_;
goto v___jp_528_;
}
else
{
uint64_t v___x_557_; 
v___x_557_ = 1ULL;
v___y_529_ = v___y_539_;
v___y_530_ = v_position_545_;
v___y_531_ = v___y_543_;
v___y_532_ = v___y_542_;
v___y_533_ = v___x_557_;
goto v___jp_528_;
}
}
}
else
{
uint64_t v_quotient_558_; uint64_t v___x_559_; uint64_t v___x_560_; uint64_t v___x_561_; uint64_t v_remainder_562_; uint64_t v___x_563_; uint64_t v_half_564_; uint8_t v___x_565_; 
v_quotient_558_ = lean_uint64_shift_right(v___y_540_, v___x_550_);
v___x_559_ = 1ULL;
v___x_560_ = lean_uint64_shift_left(v___x_559_, v___x_550_);
v___x_561_ = lean_uint64_sub(v___x_560_, v___x_559_);
v_remainder_562_ = lean_uint64_land(v___y_540_, v___x_561_);
v___x_563_ = lean_uint64_sub(v___x_550_, v___x_559_);
v_half_564_ = lean_uint64_shift_left(v___x_559_, v___x_563_);
v___x_565_ = lean_uint64_dec_lt(v_remainder_562_, v_half_564_);
if (v___x_565_ == 0)
{
uint8_t v___x_566_; 
v___x_566_ = lean_uint64_dec_lt(v_half_564_, v_remainder_562_);
if (v___x_566_ == 0)
{
uint64_t v___x_567_; uint8_t v___x_568_; 
v___x_567_ = lean_uint64_land(v_quotient_558_, v___x_559_);
v___x_568_ = lean_uint64_dec_eq(v___x_567_, v___y_539_);
if (v___x_568_ == 0)
{
uint64_t v___x_569_; 
v___x_569_ = lean_uint64_add(v_quotient_558_, v___x_559_);
v___y_529_ = v___y_539_;
v___y_530_ = v_position_545_;
v___y_531_ = v___y_543_;
v___y_532_ = v___y_542_;
v___y_533_ = v___x_569_;
goto v___jp_528_;
}
else
{
v___y_529_ = v___y_539_;
v___y_530_ = v_position_545_;
v___y_531_ = v___y_543_;
v___y_532_ = v___y_542_;
v___y_533_ = v_quotient_558_;
goto v___jp_528_;
}
}
else
{
uint64_t v___x_570_; 
v___x_570_ = lean_uint64_add(v_quotient_558_, v___x_559_);
v___y_529_ = v___y_539_;
v___y_530_ = v_position_545_;
v___y_531_ = v___y_543_;
v___y_532_ = v___y_542_;
v___y_533_ = v___x_570_;
goto v___jp_528_;
}
}
else
{
v___y_529_ = v___y_539_;
v___y_530_ = v_position_545_;
v___y_531_ = v___y_543_;
v___y_532_ = v___y_542_;
v___y_533_ = v_quotient_558_;
goto v___jp_528_;
}
}
}
else
{
v___y_529_ = v___y_539_;
v___y_530_ = v_position_545_;
v___y_531_ = v___y_543_;
v___y_532_ = v___y_542_;
v___y_533_ = v___y_540_;
goto v___jp_528_;
}
}
else
{
uint64_t v___x_571_; uint64_t v___x_572_; 
v___x_571_ = lean_uint64_sub(v___x_548_, v___y_544_);
v___x_572_ = lean_uint64_shift_left(v___y_540_, v___x_571_);
v___y_529_ = v___y_539_;
v___y_530_ = v_position_545_;
v___y_531_ = v___y_543_;
v___y_532_ = v___y_542_;
v___y_533_ = v___x_572_;
goto v___jp_528_;
}
}
else
{
uint64_t v___x_573_; uint8_t v___x_574_; 
v___x_573_ = 149ULL;
v___x_574_ = lean_uint64_dec_lt(v___y_541_, v___x_573_);
if (v___x_574_ == 0)
{
uint64_t v___x_575_; uint64_t v___x_576_; 
v___x_575_ = lean_uint64_sub(v___y_541_, v___x_573_);
v___x_576_ = lean_uint64_shift_left(v___y_540_, v___x_575_);
v___y_23_ = v___y_539_;
v___y_24_ = v___y_542_;
v___y_25_ = v___y_543_;
v___y_26_ = v___x_576_;
goto v___jp_22_;
}
else
{
uint64_t v___x_577_; uint8_t v___x_578_; 
v___x_577_ = lean_uint64_sub(v___x_573_, v___y_541_);
v___x_578_ = lean_uint64_dec_eq(v___x_577_, v___y_539_);
if (v___x_578_ == 0)
{
uint64_t v___x_579_; uint8_t v___x_580_; 
v___x_579_ = 64ULL;
v___x_580_ = lean_uint64_dec_lt(v___x_577_, v___x_579_);
if (v___x_580_ == 0)
{
uint8_t v___x_581_; 
v___x_581_ = lean_uint64_dec_eq(v___x_577_, v___x_579_);
if (v___x_581_ == 0)
{
v___y_23_ = v___y_539_;
v___y_24_ = v___y_542_;
v___y_25_ = v___y_543_;
v___y_26_ = v___y_539_;
goto v___jp_22_;
}
else
{
uint64_t v___x_582_; uint8_t v___x_583_; 
v___x_582_ = 9223372036854775808ULL;
v___x_583_ = lean_uint64_dec_lt(v___x_582_, v___y_540_);
if (v___x_583_ == 0)
{
v___y_23_ = v___y_539_;
v___y_24_ = v___y_542_;
v___y_25_ = v___y_543_;
v___y_26_ = v___y_539_;
goto v___jp_22_;
}
else
{
uint64_t v___x_584_; 
v___x_584_ = 1ULL;
v___y_23_ = v___y_539_;
v___y_24_ = v___y_542_;
v___y_25_ = v___y_543_;
v___y_26_ = v___x_584_;
goto v___jp_22_;
}
}
}
else
{
uint64_t v_quotient_585_; uint64_t v___x_586_; uint64_t v___x_587_; uint64_t v___x_588_; uint64_t v_remainder_589_; uint64_t v___x_590_; uint64_t v_half_591_; uint8_t v___x_592_; 
v_quotient_585_ = lean_uint64_shift_right(v___y_540_, v___x_577_);
v___x_586_ = 1ULL;
v___x_587_ = lean_uint64_shift_left(v___x_586_, v___x_577_);
v___x_588_ = lean_uint64_sub(v___x_587_, v___x_586_);
v_remainder_589_ = lean_uint64_land(v___y_540_, v___x_588_);
v___x_590_ = lean_uint64_sub(v___x_577_, v___x_586_);
v_half_591_ = lean_uint64_shift_left(v___x_586_, v___x_590_);
v___x_592_ = lean_uint64_dec_lt(v_remainder_589_, v_half_591_);
if (v___x_592_ == 0)
{
uint8_t v___x_593_; 
v___x_593_ = lean_uint64_dec_lt(v_half_591_, v_remainder_589_);
if (v___x_593_ == 0)
{
uint64_t v___x_594_; uint8_t v___x_595_; 
v___x_594_ = lean_uint64_land(v_quotient_585_, v___x_586_);
v___x_595_ = lean_uint64_dec_eq(v___x_594_, v___y_539_);
if (v___x_595_ == 0)
{
uint64_t v___x_596_; 
v___x_596_ = lean_uint64_add(v_quotient_585_, v___x_586_);
v___y_23_ = v___y_539_;
v___y_24_ = v___y_542_;
v___y_25_ = v___y_543_;
v___y_26_ = v___x_596_;
goto v___jp_22_;
}
else
{
v___y_23_ = v___y_539_;
v___y_24_ = v___y_542_;
v___y_25_ = v___y_543_;
v___y_26_ = v_quotient_585_;
goto v___jp_22_;
}
}
else
{
uint64_t v___x_597_; 
v___x_597_ = lean_uint64_add(v_quotient_585_, v___x_586_);
v___y_23_ = v___y_539_;
v___y_24_ = v___y_542_;
v___y_25_ = v___y_543_;
v___y_26_ = v___x_597_;
goto v___jp_22_;
}
}
else
{
v___y_23_ = v___y_539_;
v___y_24_ = v___y_542_;
v___y_25_ = v___y_543_;
v___y_26_ = v_quotient_585_;
goto v___jp_22_;
}
}
}
else
{
v___y_23_ = v___y_539_;
v___y_24_ = v___y_542_;
v___y_25_ = v___y_543_;
v___y_26_ = v___y_540_;
goto v___jp_22_;
}
}
}
}
v___jp_598_:
{
uint64_t v___x_606_; uint64_t v___x_607_; uint8_t v___x_608_; 
v___x_606_ = 1ULL;
v___x_607_ = lean_uint64_shift_right(v___y_600_, v___x_606_);
v___x_608_ = lean_uint64_dec_eq(v___x_607_, v___y_599_);
if (v___x_608_ == 0)
{
uint64_t v___x_609_; 
v___x_609_ = lean_uint64_add(v___y_605_, v___x_606_);
v___y_539_ = v___y_599_;
v___y_540_ = v___y_601_;
v___y_541_ = v___y_602_;
v___y_542_ = v___y_604_;
v___y_543_ = v___y_603_;
v___y_544_ = v___x_609_;
goto v___jp_538_;
}
else
{
v___y_539_ = v___y_599_;
v___y_540_ = v___y_601_;
v___y_541_ = v___y_602_;
v___y_542_ = v___y_604_;
v___y_543_ = v___y_603_;
v___y_544_ = v___y_605_;
goto v___jp_538_;
}
}
v___jp_610_:
{
uint64_t v___x_620_; uint8_t v___x_621_; 
v___x_620_ = lean_uint64_shift_right(v___y_613_, v___y_611_);
v___x_621_ = lean_uint64_dec_eq(v___x_620_, v___y_612_);
if (v___x_621_ == 0)
{
uint64_t v___x_622_; 
v___x_622_ = lean_uint64_add(v___y_615_, v___y_611_);
v___y_599_ = v___y_612_;
v___y_600_ = v___y_619_;
v___y_601_ = v___y_614_;
v___y_602_ = v___y_616_;
v___y_603_ = v___y_618_;
v___y_604_ = v___y_617_;
v___y_605_ = v___x_622_;
goto v___jp_598_;
}
else
{
v___y_599_ = v___y_612_;
v___y_600_ = v___y_619_;
v___y_601_ = v___y_614_;
v___y_602_ = v___y_616_;
v___y_603_ = v___y_618_;
v___y_604_ = v___y_617_;
v___y_605_ = v___y_615_;
goto v___jp_598_;
}
}
v___jp_623_:
{
uint64_t v___x_631_; uint64_t v___x_632_; uint8_t v___x_633_; 
v___x_631_ = 2ULL;
v___x_632_ = lean_uint64_shift_right(v___y_625_, v___x_631_);
v___x_633_ = lean_uint64_dec_eq(v___x_632_, v___y_624_);
if (v___x_633_ == 0)
{
v___y_611_ = v___x_631_;
v___y_612_ = v___y_624_;
v___y_613_ = v___y_625_;
v___y_614_ = v___y_626_;
v___y_615_ = v___y_630_;
v___y_616_ = v___y_627_;
v___y_617_ = v___y_629_;
v___y_618_ = v___y_628_;
v___y_619_ = v___x_632_;
goto v___jp_610_;
}
else
{
v___y_611_ = v___x_631_;
v___y_612_ = v___y_624_;
v___y_613_ = v___y_625_;
v___y_614_ = v___y_626_;
v___y_615_ = v___y_630_;
v___y_616_ = v___y_627_;
v___y_617_ = v___y_629_;
v___y_618_ = v___y_628_;
v___y_619_ = v___y_625_;
goto v___jp_610_;
}
}
v___jp_634_:
{
uint64_t v___x_644_; uint8_t v___x_645_; 
v___x_644_ = lean_uint64_shift_right(v___y_635_, v___y_636_);
v___x_645_ = lean_uint64_dec_eq(v___x_644_, v___y_637_);
if (v___x_645_ == 0)
{
uint64_t v___x_646_; 
v___x_646_ = lean_uint64_add(v___y_639_, v___y_636_);
v___y_624_ = v___y_637_;
v___y_625_ = v___y_643_;
v___y_626_ = v___y_638_;
v___y_627_ = v___y_640_;
v___y_628_ = v___y_642_;
v___y_629_ = v___y_641_;
v___y_630_ = v___x_646_;
goto v___jp_623_;
}
else
{
v___y_624_ = v___y_637_;
v___y_625_ = v___y_643_;
v___y_626_ = v___y_638_;
v___y_627_ = v___y_640_;
v___y_628_ = v___y_642_;
v___y_629_ = v___y_641_;
v___y_630_ = v___y_639_;
goto v___jp_623_;
}
}
v___jp_647_:
{
uint64_t v___x_655_; uint64_t v___x_656_; uint8_t v___x_657_; 
v___x_655_ = 4ULL;
v___x_656_ = lean_uint64_shift_right(v___y_648_, v___x_655_);
v___x_657_ = lean_uint64_dec_eq(v___x_656_, v___y_649_);
if (v___x_657_ == 0)
{
v___y_635_ = v___y_648_;
v___y_636_ = v___x_655_;
v___y_637_ = v___y_649_;
v___y_638_ = v___y_650_;
v___y_639_ = v___y_654_;
v___y_640_ = v___y_651_;
v___y_641_ = v___y_653_;
v___y_642_ = v___y_652_;
v___y_643_ = v___x_656_;
goto v___jp_634_;
}
else
{
v___y_635_ = v___y_648_;
v___y_636_ = v___x_655_;
v___y_637_ = v___y_649_;
v___y_638_ = v___y_650_;
v___y_639_ = v___y_654_;
v___y_640_ = v___y_651_;
v___y_641_ = v___y_653_;
v___y_642_ = v___y_652_;
v___y_643_ = v___y_648_;
goto v___jp_634_;
}
}
v___jp_658_:
{
uint64_t v___x_668_; uint8_t v___x_669_; 
v___x_668_ = lean_uint64_shift_right(v___y_664_, v___y_659_);
v___x_669_ = lean_uint64_dec_eq(v___x_668_, v___y_660_);
if (v___x_669_ == 0)
{
uint64_t v___x_670_; 
v___x_670_ = lean_uint64_add(v___y_661_, v___y_659_);
v___y_648_ = v___y_667_;
v___y_649_ = v___y_660_;
v___y_650_ = v___y_662_;
v___y_651_ = v___y_663_;
v___y_652_ = v___y_666_;
v___y_653_ = v___y_665_;
v___y_654_ = v___x_670_;
goto v___jp_647_;
}
else
{
v___y_648_ = v___y_667_;
v___y_649_ = v___y_660_;
v___y_650_ = v___y_662_;
v___y_651_ = v___y_663_;
v___y_652_ = v___y_666_;
v___y_653_ = v___y_665_;
v___y_654_ = v___y_661_;
goto v___jp_647_;
}
}
v___jp_671_:
{
uint64_t v___x_679_; uint64_t v___x_680_; uint8_t v___x_681_; 
v___x_679_ = 8ULL;
v___x_680_ = lean_uint64_shift_right(v___y_677_, v___x_679_);
v___x_681_ = lean_uint64_dec_eq(v___x_680_, v___y_672_);
if (v___x_681_ == 0)
{
v___y_659_ = v___x_679_;
v___y_660_ = v___y_672_;
v___y_661_ = v___y_678_;
v___y_662_ = v___y_673_;
v___y_663_ = v___y_674_;
v___y_664_ = v___y_677_;
v___y_665_ = v___y_676_;
v___y_666_ = v___y_675_;
v___y_667_ = v___x_680_;
goto v___jp_658_;
}
else
{
v___y_659_ = v___x_679_;
v___y_660_ = v___y_672_;
v___y_661_ = v___y_678_;
v___y_662_ = v___y_673_;
v___y_663_ = v___y_674_;
v___y_664_ = v___y_677_;
v___y_665_ = v___y_676_;
v___y_666_ = v___y_675_;
v___y_667_ = v___y_677_;
goto v___jp_658_;
}
}
v___jp_682_:
{
uint64_t v___x_692_; uint8_t v___x_693_; 
v___x_692_ = lean_uint64_shift_right(v___y_686_, v___y_683_);
v___x_693_ = lean_uint64_dec_eq(v___x_692_, v___y_685_);
if (v___x_693_ == 0)
{
uint64_t v___x_694_; 
v___x_694_ = lean_uint64_add(v___y_684_, v___y_683_);
v___y_672_ = v___y_685_;
v___y_673_ = v___y_687_;
v___y_674_ = v___y_688_;
v___y_675_ = v___y_690_;
v___y_676_ = v___y_689_;
v___y_677_ = v___y_691_;
v___y_678_ = v___x_694_;
goto v___jp_671_;
}
else
{
v___y_672_ = v___y_685_;
v___y_673_ = v___y_687_;
v___y_674_ = v___y_688_;
v___y_675_ = v___y_690_;
v___y_676_ = v___y_689_;
v___y_677_ = v___y_691_;
v___y_678_ = v___y_684_;
goto v___jp_671_;
}
}
v___jp_695_:
{
uint64_t v___x_703_; uint64_t v___x_704_; uint8_t v___x_705_; 
v___x_703_ = 16ULL;
v___x_704_ = lean_uint64_shift_right(v___y_697_, v___x_703_);
v___x_705_ = lean_uint64_dec_eq(v___x_704_, v___y_696_);
if (v___x_705_ == 0)
{
v___y_683_ = v___x_703_;
v___y_684_ = v___y_702_;
v___y_685_ = v___y_696_;
v___y_686_ = v___y_697_;
v___y_687_ = v___y_698_;
v___y_688_ = v___y_699_;
v___y_689_ = v___y_701_;
v___y_690_ = v___y_700_;
v___y_691_ = v___x_704_;
goto v___jp_682_;
}
else
{
v___y_683_ = v___x_703_;
v___y_684_ = v___y_702_;
v___y_685_ = v___y_696_;
v___y_686_ = v___y_697_;
v___y_687_ = v___y_698_;
v___y_688_ = v___y_699_;
v___y_689_ = v___y_701_;
v___y_690_ = v___y_700_;
v___y_691_ = v___y_697_;
goto v___jp_682_;
}
}
v___jp_706_:
{
uint64_t v___x_714_; uint8_t v___x_715_; 
v___x_714_ = lean_uint64_shift_right(v___y_709_, v___y_707_);
v___x_715_ = lean_uint64_dec_eq(v___x_714_, v___y_708_);
if (v___x_715_ == 0)
{
v___y_696_ = v___y_708_;
v___y_697_ = v___y_713_;
v___y_698_ = v___y_709_;
v___y_699_ = v___y_710_;
v___y_700_ = v___y_712_;
v___y_701_ = v___y_711_;
v___y_702_ = v___y_707_;
goto v___jp_695_;
}
else
{
v___y_696_ = v___y_708_;
v___y_697_ = v___y_713_;
v___y_698_ = v___y_709_;
v___y_699_ = v___y_710_;
v___y_700_ = v___y_712_;
v___y_701_ = v___y_711_;
v___y_702_ = v___y_708_;
goto v___jp_695_;
}
}
v___jp_716_:
{
uint64_t v___x_721_; uint8_t v___x_722_; 
v___x_721_ = 0ULL;
v___x_722_ = lean_uint64_dec_eq(v___y_717_, v___x_721_);
if (v___x_722_ == 0)
{
uint64_t v___x_723_; uint64_t v___x_724_; uint8_t v___x_725_; 
v___x_723_ = 32ULL;
v___x_724_ = lean_uint64_shift_right(v___y_717_, v___x_723_);
v___x_725_ = lean_uint64_dec_eq(v___x_724_, v___x_721_);
if (v___x_725_ == 0)
{
v___y_707_ = v___x_723_;
v___y_708_ = v___x_721_;
v___y_709_ = v___y_717_;
v___y_710_ = v___y_718_;
v___y_711_ = v___y_720_;
v___y_712_ = v___y_719_;
v___y_713_ = v___x_724_;
goto v___jp_706_;
}
else
{
v___y_707_ = v___x_723_;
v___y_708_ = v___x_721_;
v___y_709_ = v___y_717_;
v___y_710_ = v___y_718_;
v___y_711_ = v___y_720_;
v___y_712_ = v___y_719_;
v___y_713_ = v___y_717_;
goto v___jp_706_;
}
}
else
{
if (v___y_720_ == 0)
{
uint32_t v___x_726_; 
v___x_726_ = 0;
return v___x_726_;
}
else
{
uint32_t v___x_727_; 
v___x_727_ = 2147483648;
return v___x_727_;
}
}
}
v___jp_728_:
{
uint64_t v___x_735_; uint64_t v___x_736_; uint64_t v___x_737_; uint8_t v___x_738_; 
v___x_735_ = lean_uint64_mul(v___y_733_, v___y_729_);
v___x_736_ = lean_uint64_add(v___y_730_, v___y_734_);
v___x_737_ = 281474976710656ULL;
v___x_738_ = lean_uint64_dec_lt(v___x_735_, v___x_737_);
if (v___x_738_ == 0)
{
v___y_717_ = v___x_735_;
v___y_718_ = v___x_736_;
v___y_719_ = v___y_732_;
v___y_720_ = v___y_731_;
goto v___jp_716_;
}
else
{
uint64_t v___x_739_; uint8_t v___x_740_; 
v___x_739_ = 123ULL;
v___x_740_ = lean_uint64_dec_le(v___x_736_, v___x_739_);
if (v___x_740_ == 0)
{
v___y_717_ = v___x_735_;
v___y_718_ = v___x_736_;
v___y_719_ = v___y_732_;
v___y_720_ = v___y_731_;
goto v___jp_716_;
}
else
{
uint64_t v___x_741_; uint8_t v___x_742_; 
v___x_741_ = 0ULL;
v___x_742_ = lean_uint64_dec_eq(v___x_735_, v___x_741_);
if (v___x_742_ == 0)
{
uint64_t v___x_743_; uint64_t v___x_744_; uint8_t v___x_745_; 
v___x_743_ = 149ULL;
v___x_744_ = lean_uint64_sub(v___x_743_, v___x_736_);
v___x_745_ = lean_uint64_dec_eq(v___x_744_, v___x_741_);
if (v___x_745_ == 0)
{
uint64_t v___x_746_; uint8_t v___x_747_; 
v___x_746_ = 64ULL;
v___x_747_ = lean_uint64_dec_lt(v___x_744_, v___x_746_);
if (v___x_747_ == 0)
{
uint8_t v___x_748_; 
v___x_748_ = lean_uint64_dec_eq(v___x_744_, v___x_746_);
if (v___x_748_ == 0)
{
v___y_44_ = v___x_741_;
v___y_45_ = v___y_731_;
v___y_46_ = v___y_732_;
v___y_47_ = v___x_741_;
goto v___jp_43_;
}
else
{
uint64_t v___x_749_; uint8_t v___x_750_; 
v___x_749_ = 9223372036854775808ULL;
v___x_750_ = lean_uint64_dec_lt(v___x_749_, v___x_735_);
if (v___x_750_ == 0)
{
v___y_44_ = v___x_741_;
v___y_45_ = v___y_731_;
v___y_46_ = v___y_732_;
v___y_47_ = v___x_741_;
goto v___jp_43_;
}
else
{
uint64_t v___x_751_; 
v___x_751_ = 1ULL;
v___y_44_ = v___x_741_;
v___y_45_ = v___y_731_;
v___y_46_ = v___y_732_;
v___y_47_ = v___x_751_;
goto v___jp_43_;
}
}
}
else
{
uint64_t v_quotient_752_; uint64_t v___x_753_; uint64_t v___x_754_; uint64_t v___x_755_; uint64_t v_remainder_756_; uint64_t v___x_757_; uint64_t v_half_758_; uint8_t v___x_759_; 
v_quotient_752_ = lean_uint64_shift_right(v___x_735_, v___x_744_);
v___x_753_ = 1ULL;
v___x_754_ = lean_uint64_shift_left(v___x_753_, v___x_744_);
v___x_755_ = lean_uint64_sub(v___x_754_, v___x_753_);
v_remainder_756_ = lean_uint64_land(v___x_735_, v___x_755_);
v___x_757_ = lean_uint64_sub(v___x_744_, v___x_753_);
v_half_758_ = lean_uint64_shift_left(v___x_753_, v___x_757_);
v___x_759_ = lean_uint64_dec_lt(v_remainder_756_, v_half_758_);
if (v___x_759_ == 0)
{
uint8_t v___x_760_; 
v___x_760_ = lean_uint64_dec_lt(v_half_758_, v_remainder_756_);
if (v___x_760_ == 0)
{
uint64_t v___x_761_; uint8_t v___x_762_; 
v___x_761_ = lean_uint64_land(v_quotient_752_, v___x_753_);
v___x_762_ = lean_uint64_dec_eq(v___x_761_, v___x_741_);
if (v___x_762_ == 0)
{
uint64_t v___x_763_; 
v___x_763_ = lean_uint64_add(v_quotient_752_, v___x_753_);
v___y_44_ = v___x_741_;
v___y_45_ = v___y_731_;
v___y_46_ = v___y_732_;
v___y_47_ = v___x_763_;
goto v___jp_43_;
}
else
{
v___y_44_ = v___x_741_;
v___y_45_ = v___y_731_;
v___y_46_ = v___y_732_;
v___y_47_ = v_quotient_752_;
goto v___jp_43_;
}
}
else
{
uint64_t v___x_764_; 
v___x_764_ = lean_uint64_add(v_quotient_752_, v___x_753_);
v___y_44_ = v___x_741_;
v___y_45_ = v___y_731_;
v___y_46_ = v___y_732_;
v___y_47_ = v___x_764_;
goto v___jp_43_;
}
}
else
{
v___y_44_ = v___x_741_;
v___y_45_ = v___y_731_;
v___y_46_ = v___y_732_;
v___y_47_ = v_quotient_752_;
goto v___jp_43_;
}
}
}
else
{
v___y_44_ = v___x_741_;
v___y_45_ = v___y_731_;
v___y_46_ = v___y_732_;
v___y_47_ = v___x_735_;
goto v___jp_43_;
}
}
else
{
if (v___y_731_ == 0)
{
uint32_t v___x_765_; 
v___x_765_ = 0;
return v___x_765_;
}
else
{
uint32_t v___x_766_; 
v___x_766_ = 2147483648;
return v___x_766_;
}
}
}
}
}
v___jp_767_:
{
uint32_t v___x_772_; uint32_t v___x_773_; uint32_t v___x_774_; uint32_t v___x_775_; uint32_t v___x_776_; 
v___x_772_ = lean_uint32_land(v___y_769_, v___x_484_);
v___x_773_ = lean_uint32_shift_left(v___x_772_, v___x_443_);
v___x_774_ = lean_uint32_lor(v___y_771_, v___x_773_);
v___x_775_ = lean_uint32_land(v___y_768_, v___y_770_);
v___x_776_ = lean_uint32_lor(v___x_774_, v___x_775_);
return v___x_776_;
}
v___jp_777_:
{
if (v___y_779_ == 0)
{
uint32_t v___x_782_; 
v___x_782_ = 0;
v___y_768_ = v___y_781_;
v___y_769_ = v___y_778_;
v___y_770_ = v___y_780_;
v___y_771_ = v___x_782_;
goto v___jp_767_;
}
else
{
uint32_t v___x_783_; 
v___x_783_ = 2147483648;
v___y_768_ = v___y_781_;
v___y_769_ = v___y_778_;
v___y_770_ = v___y_780_;
v___y_771_ = v___x_783_;
goto v___jp_767_;
}
}
v___jp_784_:
{
uint64_t v___x_790_; uint64_t v_encodedExponent_791_; uint32_t v___x_792_; uint64_t v___x_793_; uint8_t v___x_794_; 
v___x_790_ = 171ULL;
v_encodedExponent_791_ = lean_uint64_sub(v___y_786_, v___x_790_);
v___x_792_ = lean_uint64_to_uint32(v_encodedExponent_791_);
v___x_793_ = 8388608ULL;
v___x_794_ = lean_uint64_dec_lt(v___y_789_, v___x_793_);
if (v___x_794_ == 0)
{
uint64_t v___x_795_; uint32_t v___x_796_; 
v___x_795_ = lean_uint64_sub(v___y_789_, v___x_793_);
v___x_796_ = lean_uint64_to_uint32(v___x_795_);
v___y_778_ = v___x_792_;
v___y_779_ = v___y_787_;
v___y_780_ = v___y_788_;
v___y_781_ = v___x_796_;
goto v___jp_777_;
}
else
{
uint32_t v___x_797_; 
v___x_797_ = lean_uint64_to_uint32(v___y_785_);
v___y_778_ = v___x_792_;
v___y_779_ = v___y_787_;
v___y_780_ = v___y_788_;
v___y_781_ = v___x_797_;
goto v___jp_777_;
}
}
v___jp_798_:
{
uint64_t v___x_805_; uint8_t v___x_806_; 
v___x_805_ = 425ULL;
v___x_806_ = lean_uint64_dec_lt(v___x_805_, v___y_804_);
if (v___x_806_ == 0)
{
if (v___y_799_ == 0)
{
v___y_785_ = v___y_800_;
v___y_786_ = v___y_804_;
v___y_787_ = v___y_802_;
v___y_788_ = v___y_803_;
v___y_789_ = v___y_801_;
goto v___jp_784_;
}
else
{
uint64_t v___x_807_; 
v___x_807_ = 8388608ULL;
v___y_785_ = v___y_800_;
v___y_786_ = v___y_804_;
v___y_787_ = v___y_802_;
v___y_788_ = v___y_803_;
v___y_789_ = v___x_807_;
goto v___jp_784_;
}
}
else
{
if (v___y_802_ == 0)
{
uint32_t v___x_808_; 
v___x_808_ = 2139095040;
return v___x_808_;
}
else
{
uint32_t v___x_809_; 
v___x_809_ = 4286578688;
return v___x_809_;
}
}
}
v___jp_810_:
{
uint64_t v___x_816_; uint8_t v_carry_817_; 
v___x_816_ = 16777216ULL;
v_carry_817_ = lean_uint64_dec_eq(v___y_815_, v___x_816_);
if (v_carry_817_ == 0)
{
v___y_799_ = v_carry_817_;
v___y_800_ = v___y_811_;
v___y_801_ = v___y_815_;
v___y_802_ = v___y_813_;
v___y_803_ = v___y_814_;
v___y_804_ = v___y_812_;
goto v___jp_798_;
}
else
{
uint64_t v___x_818_; uint64_t v___x_819_; 
v___x_818_ = 1ULL;
v___x_819_ = lean_uint64_add(v___y_812_, v___x_818_);
v___y_799_ = v_carry_817_;
v___y_800_ = v___y_811_;
v___y_801_ = v___y_815_;
v___y_802_ = v___y_813_;
v___y_803_ = v___y_814_;
v___y_804_ = v___x_819_;
goto v___jp_798_;
}
}
v___jp_820_:
{
uint64_t v_position_827_; uint64_t v___x_828_; uint8_t v___x_829_; 
v_position_827_ = lean_uint64_add(v___y_826_, v___y_822_);
v___x_828_ = 172ULL;
v___x_829_ = lean_uint64_dec_lt(v_position_827_, v___x_828_);
if (v___x_829_ == 0)
{
uint64_t v___x_830_; uint8_t v___x_831_; 
v___x_830_ = 23ULL;
v___x_831_ = lean_uint64_dec_lt(v___y_826_, v___x_830_);
if (v___x_831_ == 0)
{
uint64_t v___x_832_; uint8_t v___x_833_; 
v___x_832_ = lean_uint64_sub(v___y_826_, v___x_830_);
v___x_833_ = lean_uint64_dec_eq(v___x_832_, v___y_821_);
if (v___x_833_ == 0)
{
uint64_t v___x_834_; uint8_t v___x_835_; 
v___x_834_ = 64ULL;
v___x_835_ = lean_uint64_dec_lt(v___x_832_, v___x_834_);
if (v___x_835_ == 0)
{
uint8_t v___x_836_; 
v___x_836_ = lean_uint64_dec_eq(v___x_832_, v___x_834_);
if (v___x_836_ == 0)
{
v___y_811_ = v___y_821_;
v___y_812_ = v_position_827_;
v___y_813_ = v___y_824_;
v___y_814_ = v___y_825_;
v___y_815_ = v___y_821_;
goto v___jp_810_;
}
else
{
uint64_t v___x_837_; uint8_t v___x_838_; 
v___x_837_ = 9223372036854775808ULL;
v___x_838_ = lean_uint64_dec_lt(v___x_837_, v___y_823_);
if (v___x_838_ == 0)
{
v___y_811_ = v___y_821_;
v___y_812_ = v_position_827_;
v___y_813_ = v___y_824_;
v___y_814_ = v___y_825_;
v___y_815_ = v___y_821_;
goto v___jp_810_;
}
else
{
uint64_t v___x_839_; 
v___x_839_ = 1ULL;
v___y_811_ = v___y_821_;
v___y_812_ = v_position_827_;
v___y_813_ = v___y_824_;
v___y_814_ = v___y_825_;
v___y_815_ = v___x_839_;
goto v___jp_810_;
}
}
}
else
{
uint64_t v_quotient_840_; uint64_t v___x_841_; uint64_t v___x_842_; uint64_t v___x_843_; uint64_t v_remainder_844_; uint64_t v___x_845_; uint64_t v_half_846_; uint8_t v___x_847_; 
v_quotient_840_ = lean_uint64_shift_right(v___y_823_, v___x_832_);
v___x_841_ = 1ULL;
v___x_842_ = lean_uint64_shift_left(v___x_841_, v___x_832_);
v___x_843_ = lean_uint64_sub(v___x_842_, v___x_841_);
v_remainder_844_ = lean_uint64_land(v___y_823_, v___x_843_);
v___x_845_ = lean_uint64_sub(v___x_832_, v___x_841_);
v_half_846_ = lean_uint64_shift_left(v___x_841_, v___x_845_);
v___x_847_ = lean_uint64_dec_lt(v_remainder_844_, v_half_846_);
if (v___x_847_ == 0)
{
uint8_t v___x_848_; 
v___x_848_ = lean_uint64_dec_lt(v_half_846_, v_remainder_844_);
if (v___x_848_ == 0)
{
uint64_t v___x_849_; uint8_t v___x_850_; 
v___x_849_ = lean_uint64_land(v_quotient_840_, v___x_841_);
v___x_850_ = lean_uint64_dec_eq(v___x_849_, v___y_821_);
if (v___x_850_ == 0)
{
uint64_t v___x_851_; 
v___x_851_ = lean_uint64_add(v_quotient_840_, v___x_841_);
v___y_811_ = v___y_821_;
v___y_812_ = v_position_827_;
v___y_813_ = v___y_824_;
v___y_814_ = v___y_825_;
v___y_815_ = v___x_851_;
goto v___jp_810_;
}
else
{
v___y_811_ = v___y_821_;
v___y_812_ = v_position_827_;
v___y_813_ = v___y_824_;
v___y_814_ = v___y_825_;
v___y_815_ = v_quotient_840_;
goto v___jp_810_;
}
}
else
{
uint64_t v___x_852_; 
v___x_852_ = lean_uint64_add(v_quotient_840_, v___x_841_);
v___y_811_ = v___y_821_;
v___y_812_ = v_position_827_;
v___y_813_ = v___y_824_;
v___y_814_ = v___y_825_;
v___y_815_ = v___x_852_;
goto v___jp_810_;
}
}
else
{
v___y_811_ = v___y_821_;
v___y_812_ = v_position_827_;
v___y_813_ = v___y_824_;
v___y_814_ = v___y_825_;
v___y_815_ = v_quotient_840_;
goto v___jp_810_;
}
}
}
else
{
v___y_811_ = v___y_821_;
v___y_812_ = v_position_827_;
v___y_813_ = v___y_824_;
v___y_814_ = v___y_825_;
v___y_815_ = v___y_823_;
goto v___jp_810_;
}
}
else
{
uint64_t v___x_853_; uint64_t v___x_854_; 
v___x_853_ = lean_uint64_sub(v___x_830_, v___y_826_);
v___x_854_ = lean_uint64_shift_left(v___y_823_, v___x_853_);
v___y_811_ = v___y_821_;
v___y_812_ = v_position_827_;
v___y_813_ = v___y_824_;
v___y_814_ = v___y_825_;
v___y_815_ = v___x_854_;
goto v___jp_810_;
}
}
else
{
uint64_t v___x_855_; uint8_t v___x_856_; 
v___x_855_ = 149ULL;
v___x_856_ = lean_uint64_dec_lt(v___y_822_, v___x_855_);
if (v___x_856_ == 0)
{
uint64_t v___x_857_; uint64_t v___x_858_; 
v___x_857_ = lean_uint64_sub(v___y_822_, v___x_855_);
v___x_858_ = lean_uint64_shift_left(v___y_823_, v___x_857_);
v___y_168_ = v___y_821_;
v___y_169_ = v___y_824_;
v___y_170_ = v___y_825_;
v___y_171_ = v___x_858_;
goto v___jp_167_;
}
else
{
uint64_t v___x_859_; uint8_t v___x_860_; 
v___x_859_ = lean_uint64_sub(v___x_855_, v___y_822_);
v___x_860_ = lean_uint64_dec_eq(v___x_859_, v___y_821_);
if (v___x_860_ == 0)
{
uint64_t v___x_861_; uint8_t v___x_862_; 
v___x_861_ = 64ULL;
v___x_862_ = lean_uint64_dec_lt(v___x_859_, v___x_861_);
if (v___x_862_ == 0)
{
uint8_t v___x_863_; 
v___x_863_ = lean_uint64_dec_eq(v___x_859_, v___x_861_);
if (v___x_863_ == 0)
{
v___y_168_ = v___y_821_;
v___y_169_ = v___y_824_;
v___y_170_ = v___y_825_;
v___y_171_ = v___y_821_;
goto v___jp_167_;
}
else
{
uint64_t v___x_864_; uint8_t v___x_865_; 
v___x_864_ = 9223372036854775808ULL;
v___x_865_ = lean_uint64_dec_lt(v___x_864_, v___y_823_);
if (v___x_865_ == 0)
{
v___y_168_ = v___y_821_;
v___y_169_ = v___y_824_;
v___y_170_ = v___y_825_;
v___y_171_ = v___y_821_;
goto v___jp_167_;
}
else
{
uint64_t v___x_866_; 
v___x_866_ = 1ULL;
v___y_168_ = v___y_821_;
v___y_169_ = v___y_824_;
v___y_170_ = v___y_825_;
v___y_171_ = v___x_866_;
goto v___jp_167_;
}
}
}
else
{
uint64_t v_quotient_867_; uint64_t v___x_868_; uint64_t v___x_869_; uint64_t v___x_870_; uint64_t v_remainder_871_; uint64_t v___x_872_; uint64_t v_half_873_; uint8_t v___x_874_; 
v_quotient_867_ = lean_uint64_shift_right(v___y_823_, v___x_859_);
v___x_868_ = 1ULL;
v___x_869_ = lean_uint64_shift_left(v___x_868_, v___x_859_);
v___x_870_ = lean_uint64_sub(v___x_869_, v___x_868_);
v_remainder_871_ = lean_uint64_land(v___y_823_, v___x_870_);
v___x_872_ = lean_uint64_sub(v___x_859_, v___x_868_);
v_half_873_ = lean_uint64_shift_left(v___x_868_, v___x_872_);
v___x_874_ = lean_uint64_dec_lt(v_remainder_871_, v_half_873_);
if (v___x_874_ == 0)
{
uint8_t v___x_875_; 
v___x_875_ = lean_uint64_dec_lt(v_half_873_, v_remainder_871_);
if (v___x_875_ == 0)
{
uint64_t v___x_876_; uint8_t v___x_877_; 
v___x_876_ = lean_uint64_land(v_quotient_867_, v___x_868_);
v___x_877_ = lean_uint64_dec_eq(v___x_876_, v___y_821_);
if (v___x_877_ == 0)
{
uint64_t v___x_878_; 
v___x_878_ = lean_uint64_add(v_quotient_867_, v___x_868_);
v___y_168_ = v___y_821_;
v___y_169_ = v___y_824_;
v___y_170_ = v___y_825_;
v___y_171_ = v___x_878_;
goto v___jp_167_;
}
else
{
v___y_168_ = v___y_821_;
v___y_169_ = v___y_824_;
v___y_170_ = v___y_825_;
v___y_171_ = v_quotient_867_;
goto v___jp_167_;
}
}
else
{
uint64_t v___x_879_; 
v___x_879_ = lean_uint64_add(v_quotient_867_, v___x_868_);
v___y_168_ = v___y_821_;
v___y_169_ = v___y_824_;
v___y_170_ = v___y_825_;
v___y_171_ = v___x_879_;
goto v___jp_167_;
}
}
else
{
v___y_168_ = v___y_821_;
v___y_169_ = v___y_824_;
v___y_170_ = v___y_825_;
v___y_171_ = v_quotient_867_;
goto v___jp_167_;
}
}
}
else
{
v___y_168_ = v___y_821_;
v___y_169_ = v___y_824_;
v___y_170_ = v___y_825_;
v___y_171_ = v___y_823_;
goto v___jp_167_;
}
}
}
}
v___jp_880_:
{
uint64_t v___x_888_; uint64_t v___x_889_; uint8_t v___x_890_; 
v___x_888_ = 1ULL;
v___x_889_ = lean_uint64_shift_right(v___y_881_, v___x_888_);
v___x_890_ = lean_uint64_dec_eq(v___x_889_, v___y_882_);
if (v___x_890_ == 0)
{
uint64_t v___x_891_; 
v___x_891_ = lean_uint64_add(v___y_887_, v___x_888_);
v___y_821_ = v___y_882_;
v___y_822_ = v___y_883_;
v___y_823_ = v___y_884_;
v___y_824_ = v___y_885_;
v___y_825_ = v___y_886_;
v___y_826_ = v___x_891_;
goto v___jp_820_;
}
else
{
v___y_821_ = v___y_882_;
v___y_822_ = v___y_883_;
v___y_823_ = v___y_884_;
v___y_824_ = v___y_885_;
v___y_825_ = v___y_886_;
v___y_826_ = v___y_887_;
goto v___jp_820_;
}
}
v___jp_892_:
{
uint64_t v___x_902_; uint8_t v___x_903_; 
v___x_902_ = lean_uint64_shift_right(v___y_893_, v___y_899_);
v___x_903_ = lean_uint64_dec_eq(v___x_902_, v___y_894_);
if (v___x_903_ == 0)
{
uint64_t v___x_904_; 
v___x_904_ = lean_uint64_add(v___y_896_, v___y_899_);
v___y_881_ = v___y_901_;
v___y_882_ = v___y_894_;
v___y_883_ = v___y_895_;
v___y_884_ = v___y_897_;
v___y_885_ = v___y_898_;
v___y_886_ = v___y_900_;
v___y_887_ = v___x_904_;
goto v___jp_880_;
}
else
{
v___y_881_ = v___y_901_;
v___y_882_ = v___y_894_;
v___y_883_ = v___y_895_;
v___y_884_ = v___y_897_;
v___y_885_ = v___y_898_;
v___y_886_ = v___y_900_;
v___y_887_ = v___y_896_;
goto v___jp_880_;
}
}
v___jp_905_:
{
uint64_t v___x_913_; uint64_t v___x_914_; uint8_t v___x_915_; 
v___x_913_ = 2ULL;
v___x_914_ = lean_uint64_shift_right(v___y_906_, v___x_913_);
v___x_915_ = lean_uint64_dec_eq(v___x_914_, v___y_907_);
if (v___x_915_ == 0)
{
v___y_893_ = v___y_906_;
v___y_894_ = v___y_907_;
v___y_895_ = v___y_908_;
v___y_896_ = v___y_912_;
v___y_897_ = v___y_909_;
v___y_898_ = v___y_910_;
v___y_899_ = v___x_913_;
v___y_900_ = v___y_911_;
v___y_901_ = v___x_914_;
goto v___jp_892_;
}
else
{
v___y_893_ = v___y_906_;
v___y_894_ = v___y_907_;
v___y_895_ = v___y_908_;
v___y_896_ = v___y_912_;
v___y_897_ = v___y_909_;
v___y_898_ = v___y_910_;
v___y_899_ = v___x_913_;
v___y_900_ = v___y_911_;
v___y_901_ = v___y_906_;
goto v___jp_892_;
}
}
v___jp_916_:
{
uint64_t v___x_926_; uint8_t v___x_927_; 
v___x_926_ = lean_uint64_shift_right(v___y_917_, v___y_922_);
v___x_927_ = lean_uint64_dec_eq(v___x_926_, v___y_919_);
if (v___x_927_ == 0)
{
uint64_t v___x_928_; 
v___x_928_ = lean_uint64_add(v___y_918_, v___y_922_);
v___y_906_ = v___y_925_;
v___y_907_ = v___y_919_;
v___y_908_ = v___y_920_;
v___y_909_ = v___y_921_;
v___y_910_ = v___y_923_;
v___y_911_ = v___y_924_;
v___y_912_ = v___x_928_;
goto v___jp_905_;
}
else
{
v___y_906_ = v___y_925_;
v___y_907_ = v___y_919_;
v___y_908_ = v___y_920_;
v___y_909_ = v___y_921_;
v___y_910_ = v___y_923_;
v___y_911_ = v___y_924_;
v___y_912_ = v___y_918_;
goto v___jp_905_;
}
}
v___jp_929_:
{
uint64_t v___x_937_; uint64_t v___x_938_; uint8_t v___x_939_; 
v___x_937_ = 4ULL;
v___x_938_ = lean_uint64_shift_right(v___y_930_, v___x_937_);
v___x_939_ = lean_uint64_dec_eq(v___x_938_, v___y_931_);
if (v___x_939_ == 0)
{
v___y_917_ = v___y_930_;
v___y_918_ = v___y_936_;
v___y_919_ = v___y_931_;
v___y_920_ = v___y_932_;
v___y_921_ = v___y_933_;
v___y_922_ = v___x_937_;
v___y_923_ = v___y_934_;
v___y_924_ = v___y_935_;
v___y_925_ = v___x_938_;
goto v___jp_916_;
}
else
{
v___y_917_ = v___y_930_;
v___y_918_ = v___y_936_;
v___y_919_ = v___y_931_;
v___y_920_ = v___y_932_;
v___y_921_ = v___y_933_;
v___y_922_ = v___x_937_;
v___y_923_ = v___y_934_;
v___y_924_ = v___y_935_;
v___y_925_ = v___y_930_;
goto v___jp_916_;
}
}
v___jp_940_:
{
uint64_t v___x_950_; uint8_t v___x_951_; 
v___x_950_ = lean_uint64_shift_right(v___y_941_, v___y_945_);
v___x_951_ = lean_uint64_dec_eq(v___x_950_, v___y_942_);
if (v___x_951_ == 0)
{
uint64_t v___x_952_; 
v___x_952_ = lean_uint64_add(v___y_944_, v___y_945_);
v___y_930_ = v___y_949_;
v___y_931_ = v___y_942_;
v___y_932_ = v___y_943_;
v___y_933_ = v___y_946_;
v___y_934_ = v___y_947_;
v___y_935_ = v___y_948_;
v___y_936_ = v___x_952_;
goto v___jp_929_;
}
else
{
v___y_930_ = v___y_949_;
v___y_931_ = v___y_942_;
v___y_932_ = v___y_943_;
v___y_933_ = v___y_946_;
v___y_934_ = v___y_947_;
v___y_935_ = v___y_948_;
v___y_936_ = v___y_944_;
goto v___jp_929_;
}
}
v___jp_953_:
{
uint64_t v___x_961_; uint64_t v___x_962_; uint8_t v___x_963_; 
v___x_961_ = 8ULL;
v___x_962_ = lean_uint64_shift_right(v___y_954_, v___x_961_);
v___x_963_ = lean_uint64_dec_eq(v___x_962_, v___y_955_);
if (v___x_963_ == 0)
{
v___y_941_ = v___y_954_;
v___y_942_ = v___y_955_;
v___y_943_ = v___y_956_;
v___y_944_ = v___y_960_;
v___y_945_ = v___x_961_;
v___y_946_ = v___y_957_;
v___y_947_ = v___y_958_;
v___y_948_ = v___y_959_;
v___y_949_ = v___x_962_;
goto v___jp_940_;
}
else
{
v___y_941_ = v___y_954_;
v___y_942_ = v___y_955_;
v___y_943_ = v___y_956_;
v___y_944_ = v___y_960_;
v___y_945_ = v___x_961_;
v___y_946_ = v___y_957_;
v___y_947_ = v___y_958_;
v___y_948_ = v___y_959_;
v___y_949_ = v___y_954_;
goto v___jp_940_;
}
}
v___jp_964_:
{
uint64_t v___x_974_; uint8_t v___x_975_; 
v___x_974_ = lean_uint64_shift_right(v___y_968_, v___y_972_);
v___x_975_ = lean_uint64_dec_eq(v___x_974_, v___y_966_);
if (v___x_975_ == 0)
{
uint64_t v___x_976_; 
v___x_976_ = lean_uint64_add(v___y_965_, v___y_972_);
v___y_954_ = v___y_973_;
v___y_955_ = v___y_966_;
v___y_956_ = v___y_967_;
v___y_957_ = v___y_969_;
v___y_958_ = v___y_970_;
v___y_959_ = v___y_971_;
v___y_960_ = v___x_976_;
goto v___jp_953_;
}
else
{
v___y_954_ = v___y_973_;
v___y_955_ = v___y_966_;
v___y_956_ = v___y_967_;
v___y_957_ = v___y_969_;
v___y_958_ = v___y_970_;
v___y_959_ = v___y_971_;
v___y_960_ = v___y_965_;
goto v___jp_953_;
}
}
v___jp_977_:
{
uint64_t v___x_985_; uint64_t v___x_986_; uint8_t v___x_987_; 
v___x_985_ = 16ULL;
v___x_986_ = lean_uint64_shift_right(v___y_981_, v___x_985_);
v___x_987_ = lean_uint64_dec_eq(v___x_986_, v___y_978_);
if (v___x_987_ == 0)
{
v___y_965_ = v___y_984_;
v___y_966_ = v___y_978_;
v___y_967_ = v___y_979_;
v___y_968_ = v___y_981_;
v___y_969_ = v___y_980_;
v___y_970_ = v___y_982_;
v___y_971_ = v___y_983_;
v___y_972_ = v___x_985_;
v___y_973_ = v___x_986_;
goto v___jp_964_;
}
else
{
v___y_965_ = v___y_984_;
v___y_966_ = v___y_978_;
v___y_967_ = v___y_979_;
v___y_968_ = v___y_981_;
v___y_969_ = v___y_980_;
v___y_970_ = v___y_982_;
v___y_971_ = v___y_983_;
v___y_972_ = v___x_985_;
v___y_973_ = v___y_981_;
goto v___jp_964_;
}
}
v___jp_988_:
{
uint64_t v___x_996_; uint8_t v___x_997_; 
v___x_996_ = lean_uint64_shift_right(v___y_992_, v___y_989_);
v___x_997_ = lean_uint64_dec_eq(v___x_996_, v___y_990_);
if (v___x_997_ == 0)
{
v___y_978_ = v___y_990_;
v___y_979_ = v___y_991_;
v___y_980_ = v___y_992_;
v___y_981_ = v___y_995_;
v___y_982_ = v___y_993_;
v___y_983_ = v___y_994_;
v___y_984_ = v___y_989_;
goto v___jp_977_;
}
else
{
v___y_978_ = v___y_990_;
v___y_979_ = v___y_991_;
v___y_980_ = v___y_992_;
v___y_981_ = v___y_995_;
v___y_982_ = v___y_993_;
v___y_983_ = v___y_994_;
v___y_984_ = v___y_990_;
goto v___jp_977_;
}
}
v___jp_998_:
{
uint64_t v___x_1003_; uint8_t v___x_1004_; 
v___x_1003_ = 0ULL;
v___x_1004_ = lean_uint64_dec_eq(v___y_1000_, v___x_1003_);
if (v___x_1004_ == 0)
{
uint64_t v___x_1005_; uint64_t v___x_1006_; uint8_t v___x_1007_; 
v___x_1005_ = 32ULL;
v___x_1006_ = lean_uint64_shift_right(v___y_1000_, v___x_1005_);
v___x_1007_ = lean_uint64_dec_eq(v___x_1006_, v___x_1003_);
if (v___x_1007_ == 0)
{
v___y_989_ = v___x_1005_;
v___y_990_ = v___x_1003_;
v___y_991_ = v___y_999_;
v___y_992_ = v___y_1000_;
v___y_993_ = v___y_1001_;
v___y_994_ = v___y_1002_;
v___y_995_ = v___x_1006_;
goto v___jp_988_;
}
else
{
v___y_989_ = v___x_1005_;
v___y_990_ = v___x_1003_;
v___y_991_ = v___y_999_;
v___y_992_ = v___y_1000_;
v___y_993_ = v___y_1001_;
v___y_994_ = v___y_1002_;
v___y_995_ = v___y_1000_;
goto v___jp_988_;
}
}
else
{
if (v___y_1001_ == 0)
{
uint32_t v___x_1008_; 
v___x_1008_ = 0;
return v___x_1008_;
}
else
{
uint32_t v___x_1009_; 
v___x_1009_ = 2147483648;
return v___x_1009_;
}
}
}
v___jp_1010_:
{
uint64_t v___x_1017_; uint64_t v___x_1018_; uint64_t v___x_1019_; uint8_t v___x_1020_; 
v___x_1017_ = lean_uint64_mul(v___y_1013_, v___y_1012_);
v___x_1018_ = lean_uint64_add(v___y_1011_, v___y_1016_);
v___x_1019_ = 281474976710656ULL;
v___x_1020_ = lean_uint64_dec_lt(v___x_1017_, v___x_1019_);
if (v___x_1020_ == 0)
{
v___y_999_ = v___x_1018_;
v___y_1000_ = v___x_1017_;
v___y_1001_ = v___y_1014_;
v___y_1002_ = v___y_1015_;
goto v___jp_998_;
}
else
{
uint64_t v___x_1021_; uint8_t v___x_1022_; 
v___x_1021_ = 123ULL;
v___x_1022_ = lean_uint64_dec_le(v___x_1018_, v___x_1021_);
if (v___x_1022_ == 0)
{
v___y_999_ = v___x_1018_;
v___y_1000_ = v___x_1017_;
v___y_1001_ = v___y_1014_;
v___y_1002_ = v___y_1015_;
goto v___jp_998_;
}
else
{
uint64_t v___x_1023_; uint8_t v___x_1024_; 
v___x_1023_ = 0ULL;
v___x_1024_ = lean_uint64_dec_eq(v___x_1017_, v___x_1023_);
if (v___x_1024_ == 0)
{
uint64_t v___x_1025_; uint64_t v___x_1026_; uint8_t v___x_1027_; 
v___x_1025_ = 149ULL;
v___x_1026_ = lean_uint64_sub(v___x_1025_, v___x_1018_);
v___x_1027_ = lean_uint64_dec_eq(v___x_1026_, v___x_1023_);
if (v___x_1027_ == 0)
{
uint64_t v___x_1028_; uint8_t v___x_1029_; 
v___x_1028_ = 64ULL;
v___x_1029_ = lean_uint64_dec_lt(v___x_1026_, v___x_1028_);
if (v___x_1029_ == 0)
{
uint8_t v___x_1030_; 
v___x_1030_ = lean_uint64_dec_eq(v___x_1026_, v___x_1028_);
if (v___x_1030_ == 0)
{
v___y_189_ = v___y_1014_;
v___y_190_ = v___y_1015_;
v___y_191_ = v___x_1023_;
v___y_192_ = v___x_1023_;
goto v___jp_188_;
}
else
{
uint64_t v___x_1031_; uint8_t v___x_1032_; 
v___x_1031_ = 9223372036854775808ULL;
v___x_1032_ = lean_uint64_dec_lt(v___x_1031_, v___x_1017_);
if (v___x_1032_ == 0)
{
v___y_189_ = v___y_1014_;
v___y_190_ = v___y_1015_;
v___y_191_ = v___x_1023_;
v___y_192_ = v___x_1023_;
goto v___jp_188_;
}
else
{
uint64_t v___x_1033_; 
v___x_1033_ = 1ULL;
v___y_189_ = v___y_1014_;
v___y_190_ = v___y_1015_;
v___y_191_ = v___x_1023_;
v___y_192_ = v___x_1033_;
goto v___jp_188_;
}
}
}
else
{
uint64_t v_quotient_1034_; uint64_t v___x_1035_; uint64_t v___x_1036_; uint64_t v___x_1037_; uint64_t v_remainder_1038_; uint64_t v___x_1039_; uint64_t v_half_1040_; uint8_t v___x_1041_; 
v_quotient_1034_ = lean_uint64_shift_right(v___x_1017_, v___x_1026_);
v___x_1035_ = 1ULL;
v___x_1036_ = lean_uint64_shift_left(v___x_1035_, v___x_1026_);
v___x_1037_ = lean_uint64_sub(v___x_1036_, v___x_1035_);
v_remainder_1038_ = lean_uint64_land(v___x_1017_, v___x_1037_);
v___x_1039_ = lean_uint64_sub(v___x_1026_, v___x_1035_);
v_half_1040_ = lean_uint64_shift_left(v___x_1035_, v___x_1039_);
v___x_1041_ = lean_uint64_dec_lt(v_remainder_1038_, v_half_1040_);
if (v___x_1041_ == 0)
{
uint8_t v___x_1042_; 
v___x_1042_ = lean_uint64_dec_lt(v_half_1040_, v_remainder_1038_);
if (v___x_1042_ == 0)
{
uint64_t v___x_1043_; uint8_t v___x_1044_; 
v___x_1043_ = lean_uint64_land(v_quotient_1034_, v___x_1035_);
v___x_1044_ = lean_uint64_dec_eq(v___x_1043_, v___x_1023_);
if (v___x_1044_ == 0)
{
uint64_t v___x_1045_; 
v___x_1045_ = lean_uint64_add(v_quotient_1034_, v___x_1035_);
v___y_189_ = v___y_1014_;
v___y_190_ = v___y_1015_;
v___y_191_ = v___x_1023_;
v___y_192_ = v___x_1045_;
goto v___jp_188_;
}
else
{
v___y_189_ = v___y_1014_;
v___y_190_ = v___y_1015_;
v___y_191_ = v___x_1023_;
v___y_192_ = v_quotient_1034_;
goto v___jp_188_;
}
}
else
{
uint64_t v___x_1046_; 
v___x_1046_ = lean_uint64_add(v_quotient_1034_, v___x_1035_);
v___y_189_ = v___y_1014_;
v___y_190_ = v___y_1015_;
v___y_191_ = v___x_1023_;
v___y_192_ = v___x_1046_;
goto v___jp_188_;
}
}
else
{
v___y_189_ = v___y_1014_;
v___y_190_ = v___y_1015_;
v___y_191_ = v___x_1023_;
v___y_192_ = v_quotient_1034_;
goto v___jp_188_;
}
}
}
else
{
v___y_189_ = v___y_1014_;
v___y_190_ = v___y_1015_;
v___y_191_ = v___x_1023_;
v___y_192_ = v___x_1017_;
goto v___jp_188_;
}
}
else
{
if (v___y_1014_ == 0)
{
uint32_t v___x_1047_; 
v___x_1047_ = 0;
return v___x_1047_;
}
else
{
uint32_t v___x_1048_; 
v___x_1048_ = 2147483648;
return v___x_1048_;
}
}
}
}
}
v___jp_1049_:
{
uint32_t v___x_1054_; uint32_t v___x_1055_; uint32_t v___x_1056_; uint32_t v___x_1057_; uint32_t v___x_1058_; 
v___x_1054_ = lean_uint32_land(v___y_1052_, v___x_484_);
v___x_1055_ = lean_uint32_shift_left(v___x_1054_, v___x_443_);
v___x_1056_ = lean_uint32_lor(v___y_1053_, v___x_1055_);
v___x_1057_ = lean_uint32_land(v___y_1051_, v___y_1050_);
v___x_1058_ = lean_uint32_lor(v___x_1056_, v___x_1057_);
return v___x_1058_;
}
v___jp_1059_:
{
if (v___y_1061_ == 0)
{
uint32_t v___x_1064_; 
v___x_1064_ = 0;
v___y_1050_ = v___y_1060_;
v___y_1051_ = v___y_1063_;
v___y_1052_ = v___y_1062_;
v___y_1053_ = v___x_1064_;
goto v___jp_1049_;
}
else
{
uint32_t v___x_1065_; 
v___x_1065_ = 2147483648;
v___y_1050_ = v___y_1060_;
v___y_1051_ = v___y_1063_;
v___y_1052_ = v___y_1062_;
v___y_1053_ = v___x_1065_;
goto v___jp_1049_;
}
}
v___jp_1066_:
{
uint64_t v___x_1072_; uint64_t v_encodedExponent_1073_; uint32_t v___x_1074_; uint64_t v___x_1075_; uint8_t v___x_1076_; 
v___x_1072_ = 171ULL;
v_encodedExponent_1073_ = lean_uint64_sub(v___y_1068_, v___x_1072_);
v___x_1074_ = lean_uint64_to_uint32(v_encodedExponent_1073_);
v___x_1075_ = 8388608ULL;
v___x_1076_ = lean_uint64_dec_lt(v___y_1071_, v___x_1075_);
if (v___x_1076_ == 0)
{
uint64_t v___x_1077_; uint32_t v___x_1078_; 
v___x_1077_ = lean_uint64_sub(v___y_1071_, v___x_1075_);
v___x_1078_ = lean_uint64_to_uint32(v___x_1077_);
v___y_1060_ = v___y_1067_;
v___y_1061_ = v___y_1069_;
v___y_1062_ = v___x_1074_;
v___y_1063_ = v___x_1078_;
goto v___jp_1059_;
}
else
{
uint32_t v___x_1079_; 
v___x_1079_ = lean_uint64_to_uint32(v___y_1070_);
v___y_1060_ = v___y_1067_;
v___y_1061_ = v___y_1069_;
v___y_1062_ = v___x_1074_;
v___y_1063_ = v___x_1079_;
goto v___jp_1059_;
}
}
v___jp_1080_:
{
uint64_t v___x_1087_; uint8_t v___x_1088_; 
v___x_1087_ = 425ULL;
v___x_1088_ = lean_uint64_dec_lt(v___x_1087_, v___y_1086_);
if (v___x_1088_ == 0)
{
if (v___y_1083_ == 0)
{
v___y_1067_ = v___y_1081_;
v___y_1068_ = v___y_1086_;
v___y_1069_ = v___y_1082_;
v___y_1070_ = v___y_1085_;
v___y_1071_ = v___y_1084_;
goto v___jp_1066_;
}
else
{
uint64_t v___x_1089_; 
v___x_1089_ = 8388608ULL;
v___y_1067_ = v___y_1081_;
v___y_1068_ = v___y_1086_;
v___y_1069_ = v___y_1082_;
v___y_1070_ = v___y_1085_;
v___y_1071_ = v___x_1089_;
goto v___jp_1066_;
}
}
else
{
if (v___y_1082_ == 0)
{
uint32_t v___x_1090_; 
v___x_1090_ = 2139095040;
return v___x_1090_;
}
else
{
uint32_t v___x_1091_; 
v___x_1091_ = 4286578688;
return v___x_1091_;
}
}
}
v___jp_1092_:
{
uint64_t v___x_1098_; uint8_t v_carry_1099_; 
v___x_1098_ = 16777216ULL;
v_carry_1099_ = lean_uint64_dec_eq(v___y_1097_, v___x_1098_);
if (v_carry_1099_ == 0)
{
v___y_1081_ = v___y_1094_;
v___y_1082_ = v___y_1095_;
v___y_1083_ = v_carry_1099_;
v___y_1084_ = v___y_1097_;
v___y_1085_ = v___y_1096_;
v___y_1086_ = v___y_1093_;
goto v___jp_1080_;
}
else
{
uint64_t v___x_1100_; uint64_t v___x_1101_; 
v___x_1100_ = 1ULL;
v___x_1101_ = lean_uint64_add(v___y_1093_, v___x_1100_);
v___y_1081_ = v___y_1094_;
v___y_1082_ = v___y_1095_;
v___y_1083_ = v_carry_1099_;
v___y_1084_ = v___y_1097_;
v___y_1085_ = v___y_1096_;
v___y_1086_ = v___x_1101_;
goto v___jp_1080_;
}
}
v___jp_1102_:
{
uint64_t v_position_1109_; uint64_t v___x_1110_; uint8_t v___x_1111_; 
v_position_1109_ = lean_uint64_add(v___y_1108_, v___y_1106_);
v___x_1110_ = 172ULL;
v___x_1111_ = lean_uint64_dec_lt(v_position_1109_, v___x_1110_);
if (v___x_1111_ == 0)
{
uint64_t v___x_1112_; uint8_t v___x_1113_; 
v___x_1112_ = 23ULL;
v___x_1113_ = lean_uint64_dec_lt(v___y_1108_, v___x_1112_);
if (v___x_1113_ == 0)
{
uint64_t v___x_1114_; uint8_t v___x_1115_; 
v___x_1114_ = lean_uint64_sub(v___y_1108_, v___x_1112_);
v___x_1115_ = lean_uint64_dec_eq(v___x_1114_, v___y_1107_);
if (v___x_1115_ == 0)
{
uint64_t v___x_1116_; uint8_t v___x_1117_; 
v___x_1116_ = 64ULL;
v___x_1117_ = lean_uint64_dec_lt(v___x_1114_, v___x_1116_);
if (v___x_1117_ == 0)
{
uint8_t v___x_1118_; 
v___x_1118_ = lean_uint64_dec_eq(v___x_1114_, v___x_1116_);
if (v___x_1118_ == 0)
{
v___y_1093_ = v_position_1109_;
v___y_1094_ = v___y_1103_;
v___y_1095_ = v___y_1104_;
v___y_1096_ = v___y_1107_;
v___y_1097_ = v___y_1107_;
goto v___jp_1092_;
}
else
{
uint64_t v___x_1119_; uint8_t v___x_1120_; 
v___x_1119_ = 9223372036854775808ULL;
v___x_1120_ = lean_uint64_dec_lt(v___x_1119_, v___y_1105_);
if (v___x_1120_ == 0)
{
v___y_1093_ = v_position_1109_;
v___y_1094_ = v___y_1103_;
v___y_1095_ = v___y_1104_;
v___y_1096_ = v___y_1107_;
v___y_1097_ = v___y_1107_;
goto v___jp_1092_;
}
else
{
uint64_t v___x_1121_; 
v___x_1121_ = 1ULL;
v___y_1093_ = v_position_1109_;
v___y_1094_ = v___y_1103_;
v___y_1095_ = v___y_1104_;
v___y_1096_ = v___y_1107_;
v___y_1097_ = v___x_1121_;
goto v___jp_1092_;
}
}
}
else
{
uint64_t v_quotient_1122_; uint64_t v___x_1123_; uint64_t v___x_1124_; uint64_t v___x_1125_; uint64_t v_remainder_1126_; uint64_t v___x_1127_; uint64_t v_half_1128_; uint8_t v___x_1129_; 
v_quotient_1122_ = lean_uint64_shift_right(v___y_1105_, v___x_1114_);
v___x_1123_ = 1ULL;
v___x_1124_ = lean_uint64_shift_left(v___x_1123_, v___x_1114_);
v___x_1125_ = lean_uint64_sub(v___x_1124_, v___x_1123_);
v_remainder_1126_ = lean_uint64_land(v___y_1105_, v___x_1125_);
v___x_1127_ = lean_uint64_sub(v___x_1114_, v___x_1123_);
v_half_1128_ = lean_uint64_shift_left(v___x_1123_, v___x_1127_);
v___x_1129_ = lean_uint64_dec_lt(v_remainder_1126_, v_half_1128_);
if (v___x_1129_ == 0)
{
uint8_t v___x_1130_; 
v___x_1130_ = lean_uint64_dec_lt(v_half_1128_, v_remainder_1126_);
if (v___x_1130_ == 0)
{
uint64_t v___x_1131_; uint8_t v___x_1132_; 
v___x_1131_ = lean_uint64_land(v_quotient_1122_, v___x_1123_);
v___x_1132_ = lean_uint64_dec_eq(v___x_1131_, v___y_1107_);
if (v___x_1132_ == 0)
{
uint64_t v___x_1133_; 
v___x_1133_ = lean_uint64_add(v_quotient_1122_, v___x_1123_);
v___y_1093_ = v_position_1109_;
v___y_1094_ = v___y_1103_;
v___y_1095_ = v___y_1104_;
v___y_1096_ = v___y_1107_;
v___y_1097_ = v___x_1133_;
goto v___jp_1092_;
}
else
{
v___y_1093_ = v_position_1109_;
v___y_1094_ = v___y_1103_;
v___y_1095_ = v___y_1104_;
v___y_1096_ = v___y_1107_;
v___y_1097_ = v_quotient_1122_;
goto v___jp_1092_;
}
}
else
{
uint64_t v___x_1134_; 
v___x_1134_ = lean_uint64_add(v_quotient_1122_, v___x_1123_);
v___y_1093_ = v_position_1109_;
v___y_1094_ = v___y_1103_;
v___y_1095_ = v___y_1104_;
v___y_1096_ = v___y_1107_;
v___y_1097_ = v___x_1134_;
goto v___jp_1092_;
}
}
else
{
v___y_1093_ = v_position_1109_;
v___y_1094_ = v___y_1103_;
v___y_1095_ = v___y_1104_;
v___y_1096_ = v___y_1107_;
v___y_1097_ = v_quotient_1122_;
goto v___jp_1092_;
}
}
}
else
{
v___y_1093_ = v_position_1109_;
v___y_1094_ = v___y_1103_;
v___y_1095_ = v___y_1104_;
v___y_1096_ = v___y_1107_;
v___y_1097_ = v___y_1105_;
goto v___jp_1092_;
}
}
else
{
uint64_t v___x_1135_; uint64_t v___x_1136_; 
v___x_1135_ = lean_uint64_sub(v___x_1112_, v___y_1108_);
v___x_1136_ = lean_uint64_shift_left(v___y_1105_, v___x_1135_);
v___y_1093_ = v_position_1109_;
v___y_1094_ = v___y_1103_;
v___y_1095_ = v___y_1104_;
v___y_1096_ = v___y_1107_;
v___y_1097_ = v___x_1136_;
goto v___jp_1092_;
}
}
else
{
uint64_t v___x_1137_; uint8_t v___x_1138_; 
v___x_1137_ = 149ULL;
v___x_1138_ = lean_uint64_dec_lt(v___y_1106_, v___x_1137_);
if (v___x_1138_ == 0)
{
uint64_t v___x_1139_; uint64_t v___x_1140_; 
v___x_1139_ = lean_uint64_sub(v___y_1106_, v___x_1137_);
v___x_1140_ = lean_uint64_shift_left(v___y_1105_, v___x_1139_);
v___y_313_ = v___y_1103_;
v___y_314_ = v___y_1104_;
v___y_315_ = v___y_1107_;
v___y_316_ = v___x_1140_;
goto v___jp_312_;
}
else
{
uint64_t v___x_1141_; uint8_t v___x_1142_; 
v___x_1141_ = lean_uint64_sub(v___x_1137_, v___y_1106_);
v___x_1142_ = lean_uint64_dec_eq(v___x_1141_, v___y_1107_);
if (v___x_1142_ == 0)
{
uint64_t v___x_1143_; uint8_t v___x_1144_; 
v___x_1143_ = 64ULL;
v___x_1144_ = lean_uint64_dec_lt(v___x_1141_, v___x_1143_);
if (v___x_1144_ == 0)
{
uint8_t v___x_1145_; 
v___x_1145_ = lean_uint64_dec_eq(v___x_1141_, v___x_1143_);
if (v___x_1145_ == 0)
{
v___y_313_ = v___y_1103_;
v___y_314_ = v___y_1104_;
v___y_315_ = v___y_1107_;
v___y_316_ = v___y_1107_;
goto v___jp_312_;
}
else
{
uint64_t v___x_1146_; uint8_t v___x_1147_; 
v___x_1146_ = 9223372036854775808ULL;
v___x_1147_ = lean_uint64_dec_lt(v___x_1146_, v___y_1105_);
if (v___x_1147_ == 0)
{
v___y_313_ = v___y_1103_;
v___y_314_ = v___y_1104_;
v___y_315_ = v___y_1107_;
v___y_316_ = v___y_1107_;
goto v___jp_312_;
}
else
{
uint64_t v___x_1148_; 
v___x_1148_ = 1ULL;
v___y_313_ = v___y_1103_;
v___y_314_ = v___y_1104_;
v___y_315_ = v___y_1107_;
v___y_316_ = v___x_1148_;
goto v___jp_312_;
}
}
}
else
{
uint64_t v_quotient_1149_; uint64_t v___x_1150_; uint64_t v___x_1151_; uint64_t v___x_1152_; uint64_t v_remainder_1153_; uint64_t v___x_1154_; uint64_t v_half_1155_; uint8_t v___x_1156_; 
v_quotient_1149_ = lean_uint64_shift_right(v___y_1105_, v___x_1141_);
v___x_1150_ = 1ULL;
v___x_1151_ = lean_uint64_shift_left(v___x_1150_, v___x_1141_);
v___x_1152_ = lean_uint64_sub(v___x_1151_, v___x_1150_);
v_remainder_1153_ = lean_uint64_land(v___y_1105_, v___x_1152_);
v___x_1154_ = lean_uint64_sub(v___x_1141_, v___x_1150_);
v_half_1155_ = lean_uint64_shift_left(v___x_1150_, v___x_1154_);
v___x_1156_ = lean_uint64_dec_lt(v_remainder_1153_, v_half_1155_);
if (v___x_1156_ == 0)
{
uint8_t v___x_1157_; 
v___x_1157_ = lean_uint64_dec_lt(v_half_1155_, v_remainder_1153_);
if (v___x_1157_ == 0)
{
uint64_t v___x_1158_; uint8_t v___x_1159_; 
v___x_1158_ = lean_uint64_land(v_quotient_1149_, v___x_1150_);
v___x_1159_ = lean_uint64_dec_eq(v___x_1158_, v___y_1107_);
if (v___x_1159_ == 0)
{
uint64_t v___x_1160_; 
v___x_1160_ = lean_uint64_add(v_quotient_1149_, v___x_1150_);
v___y_313_ = v___y_1103_;
v___y_314_ = v___y_1104_;
v___y_315_ = v___y_1107_;
v___y_316_ = v___x_1160_;
goto v___jp_312_;
}
else
{
v___y_313_ = v___y_1103_;
v___y_314_ = v___y_1104_;
v___y_315_ = v___y_1107_;
v___y_316_ = v_quotient_1149_;
goto v___jp_312_;
}
}
else
{
uint64_t v___x_1161_; 
v___x_1161_ = lean_uint64_add(v_quotient_1149_, v___x_1150_);
v___y_313_ = v___y_1103_;
v___y_314_ = v___y_1104_;
v___y_315_ = v___y_1107_;
v___y_316_ = v___x_1161_;
goto v___jp_312_;
}
}
else
{
v___y_313_ = v___y_1103_;
v___y_314_ = v___y_1104_;
v___y_315_ = v___y_1107_;
v___y_316_ = v_quotient_1149_;
goto v___jp_312_;
}
}
}
else
{
v___y_313_ = v___y_1103_;
v___y_314_ = v___y_1104_;
v___y_315_ = v___y_1107_;
v___y_316_ = v___y_1105_;
goto v___jp_312_;
}
}
}
}
v___jp_1162_:
{
uint64_t v___x_1170_; uint64_t v___x_1171_; uint8_t v___x_1172_; 
v___x_1170_ = 1ULL;
v___x_1171_ = lean_uint64_shift_right(v___y_1167_, v___x_1170_);
v___x_1172_ = lean_uint64_dec_eq(v___x_1171_, v___y_1168_);
if (v___x_1172_ == 0)
{
uint64_t v___x_1173_; 
v___x_1173_ = lean_uint64_add(v___y_1169_, v___x_1170_);
v___y_1103_ = v___y_1163_;
v___y_1104_ = v___y_1164_;
v___y_1105_ = v___y_1165_;
v___y_1106_ = v___y_1166_;
v___y_1107_ = v___y_1168_;
v___y_1108_ = v___x_1173_;
goto v___jp_1102_;
}
else
{
v___y_1103_ = v___y_1163_;
v___y_1104_ = v___y_1164_;
v___y_1105_ = v___y_1165_;
v___y_1106_ = v___y_1166_;
v___y_1107_ = v___y_1168_;
v___y_1108_ = v___y_1169_;
goto v___jp_1102_;
}
}
v___jp_1174_:
{
uint64_t v___x_1184_; uint8_t v___x_1185_; 
v___x_1184_ = lean_uint64_shift_right(v___y_1176_, v___y_1179_);
v___x_1185_ = lean_uint64_dec_eq(v___x_1184_, v___y_1182_);
if (v___x_1185_ == 0)
{
uint64_t v___x_1186_; 
v___x_1186_ = lean_uint64_add(v___y_1181_, v___y_1179_);
v___y_1163_ = v___y_1175_;
v___y_1164_ = v___y_1177_;
v___y_1165_ = v___y_1178_;
v___y_1166_ = v___y_1180_;
v___y_1167_ = v___y_1183_;
v___y_1168_ = v___y_1182_;
v___y_1169_ = v___x_1186_;
goto v___jp_1162_;
}
else
{
v___y_1163_ = v___y_1175_;
v___y_1164_ = v___y_1177_;
v___y_1165_ = v___y_1178_;
v___y_1166_ = v___y_1180_;
v___y_1167_ = v___y_1183_;
v___y_1168_ = v___y_1182_;
v___y_1169_ = v___y_1181_;
goto v___jp_1162_;
}
}
v___jp_1187_:
{
uint64_t v___x_1195_; uint64_t v___x_1196_; uint8_t v___x_1197_; 
v___x_1195_ = 2ULL;
v___x_1196_ = lean_uint64_shift_right(v___y_1190_, v___x_1195_);
v___x_1197_ = lean_uint64_dec_eq(v___x_1196_, v___y_1193_);
if (v___x_1197_ == 0)
{
v___y_1175_ = v___y_1188_;
v___y_1176_ = v___y_1190_;
v___y_1177_ = v___y_1189_;
v___y_1178_ = v___y_1191_;
v___y_1179_ = v___x_1195_;
v___y_1180_ = v___y_1192_;
v___y_1181_ = v___y_1194_;
v___y_1182_ = v___y_1193_;
v___y_1183_ = v___x_1196_;
goto v___jp_1174_;
}
else
{
v___y_1175_ = v___y_1188_;
v___y_1176_ = v___y_1190_;
v___y_1177_ = v___y_1189_;
v___y_1178_ = v___y_1191_;
v___y_1179_ = v___x_1195_;
v___y_1180_ = v___y_1192_;
v___y_1181_ = v___y_1194_;
v___y_1182_ = v___y_1193_;
v___y_1183_ = v___y_1190_;
goto v___jp_1174_;
}
}
v___jp_1198_:
{
uint64_t v___x_1208_; uint8_t v___x_1209_; 
v___x_1208_ = lean_uint64_shift_right(v___y_1205_, v___y_1199_);
v___x_1209_ = lean_uint64_dec_eq(v___x_1208_, v___y_1206_);
if (v___x_1209_ == 0)
{
uint64_t v___x_1210_; 
v___x_1210_ = lean_uint64_add(v___y_1202_, v___y_1199_);
v___y_1188_ = v___y_1200_;
v___y_1189_ = v___y_1201_;
v___y_1190_ = v___y_1207_;
v___y_1191_ = v___y_1203_;
v___y_1192_ = v___y_1204_;
v___y_1193_ = v___y_1206_;
v___y_1194_ = v___x_1210_;
goto v___jp_1187_;
}
else
{
v___y_1188_ = v___y_1200_;
v___y_1189_ = v___y_1201_;
v___y_1190_ = v___y_1207_;
v___y_1191_ = v___y_1203_;
v___y_1192_ = v___y_1204_;
v___y_1193_ = v___y_1206_;
v___y_1194_ = v___y_1202_;
goto v___jp_1187_;
}
}
v___jp_1211_:
{
uint64_t v___x_1219_; uint64_t v___x_1220_; uint8_t v___x_1221_; 
v___x_1219_ = 4ULL;
v___x_1220_ = lean_uint64_shift_right(v___y_1217_, v___x_1219_);
v___x_1221_ = lean_uint64_dec_eq(v___x_1220_, v___y_1216_);
if (v___x_1221_ == 0)
{
v___y_1199_ = v___x_1219_;
v___y_1200_ = v___y_1212_;
v___y_1201_ = v___y_1213_;
v___y_1202_ = v___y_1218_;
v___y_1203_ = v___y_1214_;
v___y_1204_ = v___y_1215_;
v___y_1205_ = v___y_1217_;
v___y_1206_ = v___y_1216_;
v___y_1207_ = v___x_1220_;
goto v___jp_1198_;
}
else
{
v___y_1199_ = v___x_1219_;
v___y_1200_ = v___y_1212_;
v___y_1201_ = v___y_1213_;
v___y_1202_ = v___y_1218_;
v___y_1203_ = v___y_1214_;
v___y_1204_ = v___y_1215_;
v___y_1205_ = v___y_1217_;
v___y_1206_ = v___y_1216_;
v___y_1207_ = v___y_1217_;
goto v___jp_1198_;
}
}
v___jp_1222_:
{
uint64_t v___x_1232_; uint8_t v___x_1233_; 
v___x_1232_ = lean_uint64_shift_right(v___y_1223_, v___y_1227_);
v___x_1233_ = lean_uint64_dec_eq(v___x_1232_, v___y_1230_);
if (v___x_1233_ == 0)
{
uint64_t v___x_1234_; 
v___x_1234_ = lean_uint64_add(v___y_1229_, v___y_1227_);
v___y_1212_ = v___y_1224_;
v___y_1213_ = v___y_1225_;
v___y_1214_ = v___y_1226_;
v___y_1215_ = v___y_1228_;
v___y_1216_ = v___y_1230_;
v___y_1217_ = v___y_1231_;
v___y_1218_ = v___x_1234_;
goto v___jp_1211_;
}
else
{
v___y_1212_ = v___y_1224_;
v___y_1213_ = v___y_1225_;
v___y_1214_ = v___y_1226_;
v___y_1215_ = v___y_1228_;
v___y_1216_ = v___y_1230_;
v___y_1217_ = v___y_1231_;
v___y_1218_ = v___y_1229_;
goto v___jp_1211_;
}
}
v___jp_1235_:
{
uint64_t v___x_1243_; uint64_t v___x_1244_; uint8_t v___x_1245_; 
v___x_1243_ = 8ULL;
v___x_1244_ = lean_uint64_shift_right(v___y_1236_, v___x_1243_);
v___x_1245_ = lean_uint64_dec_eq(v___x_1244_, v___y_1241_);
if (v___x_1245_ == 0)
{
v___y_1223_ = v___y_1236_;
v___y_1224_ = v___y_1237_;
v___y_1225_ = v___y_1238_;
v___y_1226_ = v___y_1239_;
v___y_1227_ = v___x_1243_;
v___y_1228_ = v___y_1240_;
v___y_1229_ = v___y_1242_;
v___y_1230_ = v___y_1241_;
v___y_1231_ = v___x_1244_;
goto v___jp_1222_;
}
else
{
v___y_1223_ = v___y_1236_;
v___y_1224_ = v___y_1237_;
v___y_1225_ = v___y_1238_;
v___y_1226_ = v___y_1239_;
v___y_1227_ = v___x_1243_;
v___y_1228_ = v___y_1240_;
v___y_1229_ = v___y_1242_;
v___y_1230_ = v___y_1241_;
v___y_1231_ = v___y_1236_;
goto v___jp_1222_;
}
}
v___jp_1246_:
{
uint64_t v___x_1256_; uint8_t v___x_1257_; 
v___x_1256_ = lean_uint64_shift_right(v___y_1249_, v___y_1252_);
v___x_1257_ = lean_uint64_dec_eq(v___x_1256_, v___y_1254_);
if (v___x_1257_ == 0)
{
uint64_t v___x_1258_; 
v___x_1258_ = lean_uint64_add(v___y_1250_, v___y_1252_);
v___y_1236_ = v___y_1255_;
v___y_1237_ = v___y_1247_;
v___y_1238_ = v___y_1248_;
v___y_1239_ = v___y_1251_;
v___y_1240_ = v___y_1253_;
v___y_1241_ = v___y_1254_;
v___y_1242_ = v___x_1258_;
goto v___jp_1235_;
}
else
{
v___y_1236_ = v___y_1255_;
v___y_1237_ = v___y_1247_;
v___y_1238_ = v___y_1248_;
v___y_1239_ = v___y_1251_;
v___y_1240_ = v___y_1253_;
v___y_1241_ = v___y_1254_;
v___y_1242_ = v___y_1250_;
goto v___jp_1235_;
}
}
v___jp_1259_:
{
uint64_t v___x_1267_; uint64_t v___x_1268_; uint8_t v___x_1269_; 
v___x_1267_ = 16ULL;
v___x_1268_ = lean_uint64_shift_right(v___y_1262_, v___x_1267_);
v___x_1269_ = lean_uint64_dec_eq(v___x_1268_, v___y_1265_);
if (v___x_1269_ == 0)
{
v___y_1247_ = v___y_1260_;
v___y_1248_ = v___y_1261_;
v___y_1249_ = v___y_1262_;
v___y_1250_ = v___y_1266_;
v___y_1251_ = v___y_1263_;
v___y_1252_ = v___x_1267_;
v___y_1253_ = v___y_1264_;
v___y_1254_ = v___y_1265_;
v___y_1255_ = v___x_1268_;
goto v___jp_1246_;
}
else
{
v___y_1247_ = v___y_1260_;
v___y_1248_ = v___y_1261_;
v___y_1249_ = v___y_1262_;
v___y_1250_ = v___y_1266_;
v___y_1251_ = v___y_1263_;
v___y_1252_ = v___x_1267_;
v___y_1253_ = v___y_1264_;
v___y_1254_ = v___y_1265_;
v___y_1255_ = v___y_1262_;
goto v___jp_1246_;
}
}
v___jp_1270_:
{
uint64_t v___x_1278_; uint8_t v___x_1279_; 
v___x_1278_ = lean_uint64_shift_right(v___y_1273_, v___y_1274_);
v___x_1279_ = lean_uint64_dec_eq(v___x_1278_, v___y_1276_);
if (v___x_1279_ == 0)
{
v___y_1260_ = v___y_1271_;
v___y_1261_ = v___y_1272_;
v___y_1262_ = v___y_1277_;
v___y_1263_ = v___y_1273_;
v___y_1264_ = v___y_1275_;
v___y_1265_ = v___y_1276_;
v___y_1266_ = v___y_1274_;
goto v___jp_1259_;
}
else
{
v___y_1260_ = v___y_1271_;
v___y_1261_ = v___y_1272_;
v___y_1262_ = v___y_1277_;
v___y_1263_ = v___y_1273_;
v___y_1264_ = v___y_1275_;
v___y_1265_ = v___y_1276_;
v___y_1266_ = v___y_1276_;
goto v___jp_1259_;
}
}
v___jp_1280_:
{
uint64_t v___x_1285_; uint8_t v___x_1286_; 
v___x_1285_ = 0ULL;
v___x_1286_ = lean_uint64_dec_eq(v___y_1283_, v___x_1285_);
if (v___x_1286_ == 0)
{
uint64_t v___x_1287_; uint64_t v___x_1288_; uint8_t v___x_1289_; 
v___x_1287_ = 32ULL;
v___x_1288_ = lean_uint64_shift_right(v___y_1283_, v___x_1287_);
v___x_1289_ = lean_uint64_dec_eq(v___x_1288_, v___x_1285_);
if (v___x_1289_ == 0)
{
v___y_1271_ = v___y_1281_;
v___y_1272_ = v___y_1282_;
v___y_1273_ = v___y_1283_;
v___y_1274_ = v___x_1287_;
v___y_1275_ = v___y_1284_;
v___y_1276_ = v___x_1285_;
v___y_1277_ = v___x_1288_;
goto v___jp_1270_;
}
else
{
v___y_1271_ = v___y_1281_;
v___y_1272_ = v___y_1282_;
v___y_1273_ = v___y_1283_;
v___y_1274_ = v___x_1287_;
v___y_1275_ = v___y_1284_;
v___y_1276_ = v___x_1285_;
v___y_1277_ = v___y_1283_;
goto v___jp_1270_;
}
}
else
{
if (v___y_1282_ == 0)
{
uint32_t v___x_1290_; 
v___x_1290_ = 0;
return v___x_1290_;
}
else
{
uint32_t v___x_1291_; 
v___x_1291_ = 2147483648;
return v___x_1291_;
}
}
}
v___jp_1292_:
{
uint64_t v___x_1299_; uint64_t v___x_1300_; uint64_t v___x_1301_; uint8_t v___x_1302_; 
v___x_1299_ = lean_uint64_mul(v___y_1293_, v___y_1296_);
v___x_1300_ = lean_uint64_add(v___y_1297_, v___y_1298_);
v___x_1301_ = 281474976710656ULL;
v___x_1302_ = lean_uint64_dec_lt(v___x_1299_, v___x_1301_);
if (v___x_1302_ == 0)
{
v___y_1281_ = v___y_1294_;
v___y_1282_ = v___y_1295_;
v___y_1283_ = v___x_1299_;
v___y_1284_ = v___x_1300_;
goto v___jp_1280_;
}
else
{
uint64_t v___x_1303_; uint8_t v___x_1304_; 
v___x_1303_ = 123ULL;
v___x_1304_ = lean_uint64_dec_le(v___x_1300_, v___x_1303_);
if (v___x_1304_ == 0)
{
v___y_1281_ = v___y_1294_;
v___y_1282_ = v___y_1295_;
v___y_1283_ = v___x_1299_;
v___y_1284_ = v___x_1300_;
goto v___jp_1280_;
}
else
{
uint64_t v___x_1305_; uint8_t v___x_1306_; 
v___x_1305_ = 0ULL;
v___x_1306_ = lean_uint64_dec_eq(v___x_1299_, v___x_1305_);
if (v___x_1306_ == 0)
{
uint64_t v___x_1307_; uint64_t v___x_1308_; uint8_t v___x_1309_; 
v___x_1307_ = 149ULL;
v___x_1308_ = lean_uint64_sub(v___x_1307_, v___x_1300_);
v___x_1309_ = lean_uint64_dec_eq(v___x_1308_, v___x_1305_);
if (v___x_1309_ == 0)
{
uint64_t v___x_1310_; uint8_t v___x_1311_; 
v___x_1310_ = 64ULL;
v___x_1311_ = lean_uint64_dec_lt(v___x_1308_, v___x_1310_);
if (v___x_1311_ == 0)
{
uint8_t v___x_1312_; 
v___x_1312_ = lean_uint64_dec_eq(v___x_1308_, v___x_1310_);
if (v___x_1312_ == 0)
{
v___y_334_ = v___x_1305_;
v___y_335_ = v___y_1294_;
v___y_336_ = v___y_1295_;
v___y_337_ = v___x_1305_;
goto v___jp_333_;
}
else
{
uint64_t v___x_1313_; uint8_t v___x_1314_; 
v___x_1313_ = 9223372036854775808ULL;
v___x_1314_ = lean_uint64_dec_lt(v___x_1313_, v___x_1299_);
if (v___x_1314_ == 0)
{
v___y_334_ = v___x_1305_;
v___y_335_ = v___y_1294_;
v___y_336_ = v___y_1295_;
v___y_337_ = v___x_1305_;
goto v___jp_333_;
}
else
{
uint64_t v___x_1315_; 
v___x_1315_ = 1ULL;
v___y_334_ = v___x_1305_;
v___y_335_ = v___y_1294_;
v___y_336_ = v___y_1295_;
v___y_337_ = v___x_1315_;
goto v___jp_333_;
}
}
}
else
{
uint64_t v_quotient_1316_; uint64_t v___x_1317_; uint64_t v___x_1318_; uint64_t v___x_1319_; uint64_t v_remainder_1320_; uint64_t v___x_1321_; uint64_t v_half_1322_; uint8_t v___x_1323_; 
v_quotient_1316_ = lean_uint64_shift_right(v___x_1299_, v___x_1308_);
v___x_1317_ = 1ULL;
v___x_1318_ = lean_uint64_shift_left(v___x_1317_, v___x_1308_);
v___x_1319_ = lean_uint64_sub(v___x_1318_, v___x_1317_);
v_remainder_1320_ = lean_uint64_land(v___x_1299_, v___x_1319_);
v___x_1321_ = lean_uint64_sub(v___x_1308_, v___x_1317_);
v_half_1322_ = lean_uint64_shift_left(v___x_1317_, v___x_1321_);
v___x_1323_ = lean_uint64_dec_lt(v_remainder_1320_, v_half_1322_);
if (v___x_1323_ == 0)
{
uint8_t v___x_1324_; 
v___x_1324_ = lean_uint64_dec_lt(v_half_1322_, v_remainder_1320_);
if (v___x_1324_ == 0)
{
uint64_t v___x_1325_; uint8_t v___x_1326_; 
v___x_1325_ = lean_uint64_land(v_quotient_1316_, v___x_1317_);
v___x_1326_ = lean_uint64_dec_eq(v___x_1325_, v___x_1305_);
if (v___x_1326_ == 0)
{
uint64_t v___x_1327_; 
v___x_1327_ = lean_uint64_add(v_quotient_1316_, v___x_1317_);
v___y_334_ = v___x_1305_;
v___y_335_ = v___y_1294_;
v___y_336_ = v___y_1295_;
v___y_337_ = v___x_1327_;
goto v___jp_333_;
}
else
{
v___y_334_ = v___x_1305_;
v___y_335_ = v___y_1294_;
v___y_336_ = v___y_1295_;
v___y_337_ = v_quotient_1316_;
goto v___jp_333_;
}
}
else
{
uint64_t v___x_1328_; 
v___x_1328_ = lean_uint64_add(v_quotient_1316_, v___x_1317_);
v___y_334_ = v___x_1305_;
v___y_335_ = v___y_1294_;
v___y_336_ = v___y_1295_;
v___y_337_ = v___x_1328_;
goto v___jp_333_;
}
}
else
{
v___y_334_ = v___x_1305_;
v___y_335_ = v___y_1294_;
v___y_336_ = v___y_1295_;
v___y_337_ = v_quotient_1316_;
goto v___jp_333_;
}
}
}
else
{
v___y_334_ = v___x_1305_;
v___y_335_ = v___y_1294_;
v___y_336_ = v___y_1295_;
v___y_337_ = v___x_1299_;
goto v___jp_333_;
}
}
else
{
if (v___y_1295_ == 0)
{
uint32_t v___x_1329_; 
v___x_1329_ = 0;
return v___x_1329_;
}
else
{
uint32_t v___x_1330_; 
v___x_1330_ = 2147483648;
return v___x_1330_;
}
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_r22CostInlineOldMul___boxed(lean_object* v_x_1635_, lean_object* v_y_1636_){
_start:
{
uint32_t v_x_boxed_1637_; uint32_t v_y_boxed_1638_; uint32_t v_res_1639_; lean_object* v_r_1640_; 
v_x_boxed_1637_ = lean_unbox_uint32(v_x_1635_);
lean_dec(v_x_1635_);
v_y_boxed_1638_ = lean_unbox_uint32(v_y_1636_);
lean_dec(v_y_1636_);
v_res_1639_ = lp_competition_r22CostInlineOldMul(v_x_boxed_1637_, v_y_boxed_1638_);
v_r_1640_ = lean_box_uint32(v_res_1639_);
return v_r_1640_;
}
}
LEAN_EXPORT uint32_t lp_competition_r22CostOutlinedMul(uint32_t v_x_1641_, uint32_t v_y_1642_){
_start:
{
uint32_t v___x_1643_; uint32_t v___x_1644_; uint32_t v___x_1645_; uint32_t v_eu_1646_; uint32_t v___x_1647_; uint32_t v___x_1648_; uint32_t v___x_1649_; uint8_t v___x_1650_; 
v___x_1643_ = 23;
v___x_1644_ = lean_uint32_shift_right(v_x_1641_, v___x_1643_);
v___x_1645_ = 255;
v_eu_1646_ = lean_uint32_land(v___x_1644_, v___x_1645_);
v___x_1647_ = 1;
v___x_1648_ = lean_uint32_sub(v_eu_1646_, v___x_1647_);
v___x_1649_ = 253;
v___x_1650_ = lean_uint32_dec_le(v___x_1648_, v___x_1649_);
if (v___x_1650_ == 0)
{
uint32_t v___x_1651_; 
v___x_1651_ = lp_competition_Submission_R22OutlineMul_retainedMul(v_x_1641_, v_y_1642_);
return v___x_1651_;
}
else
{
uint32_t v___x_1652_; uint32_t v_ev_1653_; uint32_t v___x_1654_; uint8_t v___x_1655_; 
v___x_1652_ = lean_uint32_shift_right(v_y_1642_, v___x_1643_);
v_ev_1653_ = lean_uint32_land(v___x_1652_, v___x_1645_);
v___x_1654_ = lean_uint32_sub(v_ev_1653_, v___x_1647_);
v___x_1655_ = lean_uint32_dec_le(v___x_1654_, v___x_1649_);
if (v___x_1655_ == 0)
{
uint32_t v___x_1656_; 
v___x_1656_ = lp_competition_Submission_R22OutlineMul_retainedMul(v_x_1641_, v_y_1642_);
return v___x_1656_;
}
else
{
uint32_t v_s_1657_; uint32_t v___x_1658_; uint32_t v___x_1659_; uint32_t v___x_1660_; uint8_t v___x_1661_; 
v_s_1657_ = lean_uint32_add(v_eu_1646_, v_ev_1653_);
v___x_1658_ = 128;
v___x_1659_ = lean_uint32_sub(v_s_1657_, v___x_1658_);
v___x_1660_ = 252;
v___x_1661_ = lean_uint32_dec_le(v___x_1659_, v___x_1660_);
if (v___x_1661_ == 0)
{
uint32_t v___x_1662_; 
v___x_1662_ = lp_competition_Submission_R22OutlineMul_retainedMul(v_x_1641_, v_y_1642_);
return v___x_1662_;
}
else
{
uint32_t v___x_1663_; uint32_t v___x_1664_; uint32_t v___x_1665_; uint64_t v___y_1667_; uint32_t v_a_1685_; uint32_t v___x_1686_; uint32_t v_b_1687_; uint64_t v___x_1688_; uint64_t v___x_1689_; uint64_t v_p_1690_; uint64_t v___x_1691_; uint8_t v___x_1692_; 
v___x_1663_ = 8388607;
v___x_1664_ = lean_uint32_land(v_x_1641_, v___x_1663_);
v___x_1665_ = 8388608;
v_a_1685_ = lean_uint32_lor(v___x_1664_, v___x_1665_);
v___x_1686_ = lean_uint32_land(v_y_1642_, v___x_1663_);
v_b_1687_ = lean_uint32_lor(v___x_1686_, v___x_1665_);
v___x_1688_ = lean_uint32_to_uint64(v_a_1685_);
v___x_1689_ = lean_uint32_to_uint64(v_b_1687_);
v_p_1690_ = lean_uint64_mul(v___x_1688_, v___x_1689_);
v___x_1691_ = 140737488355328ULL;
v___x_1692_ = lean_uint64_dec_lt(v_p_1690_, v___x_1691_);
if (v___x_1692_ == 0)
{
uint64_t v___x_1693_; uint64_t v___x_1694_; uint64_t v___x_1695_; uint64_t v___x_1696_; uint64_t v___x_1697_; uint64_t v___x_1698_; uint64_t v___x_1699_; 
v___x_1693_ = 8388607ULL;
v___x_1694_ = lean_uint64_add(v_p_1690_, v___x_1693_);
v___x_1695_ = 24ULL;
v___x_1696_ = lean_uint64_shift_right(v_p_1690_, v___x_1695_);
v___x_1697_ = 1ULL;
v___x_1698_ = lean_uint64_land(v___x_1696_, v___x_1697_);
v___x_1699_ = lean_uint64_add(v___x_1694_, v___x_1698_);
v___y_1667_ = v___x_1699_;
goto v___jp_1666_;
}
else
{
uint64_t v___x_1700_; uint64_t v___x_1701_; uint64_t v___x_1702_; uint64_t v___x_1703_; uint64_t v___x_1704_; uint64_t v___x_1705_; uint64_t v___x_1706_; 
v___x_1700_ = 4194303ULL;
v___x_1701_ = lean_uint64_add(v_p_1690_, v___x_1700_);
v___x_1702_ = 23ULL;
v___x_1703_ = lean_uint64_shift_right(v_p_1690_, v___x_1702_);
v___x_1704_ = 1ULL;
v___x_1705_ = lean_uint64_land(v___x_1703_, v___x_1704_);
v___x_1706_ = lean_uint64_add(v___x_1701_, v___x_1705_);
v___y_1667_ = v___x_1706_;
goto v___jp_1666_;
}
v___jp_1666_:
{
uint64_t v___x_1668_; uint64_t v_high_1669_; uint64_t v___x_1670_; uint64_t v___x_1671_; uint64_t v___x_1672_; uint32_t v_q_1673_; uint32_t v___x_1674_; uint32_t v___x_1675_; uint32_t v___x_1676_; uint32_t v_e_1677_; uint32_t v___x_1678_; uint32_t v___x_1679_; uint32_t v___x_1680_; uint32_t v___x_1681_; uint32_t v___x_1682_; uint32_t v___x_1683_; uint32_t v___x_1684_; 
v___x_1668_ = 47ULL;
v_high_1669_ = lean_uint64_shift_right(v___y_1667_, v___x_1668_);
v___x_1670_ = 23ULL;
v___x_1671_ = lean_uint64_add(v___x_1670_, v_high_1669_);
v___x_1672_ = lean_uint64_shift_right(v___y_1667_, v___x_1671_);
v_q_1673_ = lean_uint64_to_uint32(v___x_1672_);
v___x_1674_ = 127;
v___x_1675_ = lean_uint32_sub(v_s_1657_, v___x_1674_);
v___x_1676_ = lean_uint64_to_uint32(v_high_1669_);
v_e_1677_ = lean_uint32_add(v___x_1675_, v___x_1676_);
v___x_1678_ = lean_uint32_xor(v_x_1641_, v_y_1642_);
v___x_1679_ = 2147483648;
v___x_1680_ = lean_uint32_land(v___x_1678_, v___x_1679_);
v___x_1681_ = lean_uint32_shift_left(v_e_1677_, v___x_1643_);
v___x_1682_ = lean_uint32_lor(v___x_1680_, v___x_1681_);
v___x_1683_ = lean_uint32_sub(v_q_1673_, v___x_1665_);
v___x_1684_ = lean_uint32_lor(v___x_1682_, v___x_1683_);
return v___x_1684_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_r22CostOutlinedMul___boxed(lean_object* v_x_1707_, lean_object* v_y_1708_){
_start:
{
uint32_t v_x_boxed_1709_; uint32_t v_y_boxed_1710_; uint32_t v_res_1711_; lean_object* v_r_1712_; 
v_x_boxed_1709_ = lean_unbox_uint32(v_x_1707_);
lean_dec(v_x_1707_);
v_y_boxed_1710_ = lean_unbox_uint32(v_y_1708_);
lean_dec(v_y_1708_);
v_res_1711_ = lp_competition_r22CostOutlinedMul(v_x_boxed_1709_, v_y_boxed_1710_);
v_r_1712_ = lean_box_uint32(v_res_1711_);
return v_r_1712_;
}
}
LEAN_EXPORT uint32_t lp_competition_runControl___lam__0(uint32_t v___y_1713_, uint32_t v___y_1714_){
_start:
{
uint8_t v___y_1721_; uint8_t v___y_1735_; uint8_t v___y_1749_; uint8_t v___y_1766_; float v___y_1773_; float v___y_1774_; float v___y_1788_; uint8_t v___y_1789_; float v___y_1804_; uint8_t v___y_1814_; uint32_t v___x_1828_; uint32_t v_a_1829_; uint32_t v___x_1830_; uint32_t v___x_1831_; uint32_t v___x_1832_; uint8_t v___x_1833_; 
v___x_1828_ = 2147483647;
v_a_1829_ = lean_uint32_land(v___y_1713_, v___x_1828_);
v___x_1830_ = 201326591;
v___x_1831_ = 1;
v___x_1832_ = lean_uint32_sub(v_a_1829_, v___x_1831_);
v___x_1833_ = lean_uint32_dec_le(v___x_1830_, v___x_1832_);
if (v___x_1833_ == 0)
{
v___y_1814_ = v___x_1833_;
goto v___jp_1813_;
}
else
{
uint32_t v___x_1834_; uint8_t v___x_1835_; 
v___x_1834_ = 2139095040;
v___x_1835_ = lean_uint32_dec_lt(v_a_1829_, v___x_1834_);
v___y_1814_ = v___x_1835_;
goto v___jp_1813_;
}
v___jp_1715_:
{
lean_object* v___x_1716_; lean_object* v___x_1717_; lean_object* v___x_1718_; uint32_t v___x_1719_; 
v___x_1716_ = lean_uint32_to_nat(v___y_1713_);
v___x_1717_ = lean_uint32_to_nat(v___y_1714_);
v___x_1718_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_1716_, v___x_1717_);
v___x_1719_ = lean_uint32_of_nat(v___x_1718_);
lean_dec(v___x_1718_);
return v___x_1719_;
}
v___jp_1720_:
{
if (v___y_1721_ == 0)
{
goto v___jp_1715_;
}
else
{
uint32_t v___x_1722_; uint32_t v___x_1723_; 
v___x_1722_ = 4194304;
v___x_1723_ = lean_uint32_lor(v___y_1714_, v___x_1722_);
return v___x_1723_;
}
}
v___jp_1724_:
{
uint32_t v___x_1725_; uint32_t v___x_1726_; uint32_t v___x_1727_; uint32_t v___x_1728_; uint8_t v___x_1729_; 
v___x_1725_ = 23;
v___x_1726_ = lean_uint32_shift_right(v___y_1714_, v___x_1725_);
v___x_1727_ = 255;
v___x_1728_ = lean_uint32_land(v___x_1726_, v___x_1727_);
v___x_1729_ = lean_uint32_dec_eq(v___x_1728_, v___x_1727_);
if (v___x_1729_ == 0)
{
v___y_1721_ = v___x_1729_;
goto v___jp_1720_;
}
else
{
uint32_t v___x_1730_; uint32_t v___x_1731_; uint32_t v___x_1732_; uint8_t v___x_1733_; 
v___x_1730_ = 8388607;
v___x_1731_ = lean_uint32_land(v___y_1714_, v___x_1730_);
v___x_1732_ = 0;
v___x_1733_ = lean_uint32_dec_eq(v___x_1731_, v___x_1732_);
if (v___x_1733_ == 0)
{
v___y_1721_ = v___x_1729_;
goto v___jp_1720_;
}
else
{
goto v___jp_1715_;
}
}
}
v___jp_1734_:
{
if (v___y_1735_ == 0)
{
goto v___jp_1724_;
}
else
{
uint32_t v___x_1736_; uint32_t v___x_1737_; 
v___x_1736_ = 4194304;
v___x_1737_ = lean_uint32_lor(v___y_1713_, v___x_1736_);
return v___x_1737_;
}
}
v___jp_1738_:
{
uint32_t v___x_1739_; uint32_t v___x_1740_; uint32_t v___x_1741_; uint32_t v___x_1742_; uint8_t v___x_1743_; 
v___x_1739_ = 23;
v___x_1740_ = lean_uint32_shift_right(v___y_1713_, v___x_1739_);
v___x_1741_ = 255;
v___x_1742_ = lean_uint32_land(v___x_1740_, v___x_1741_);
v___x_1743_ = lean_uint32_dec_eq(v___x_1742_, v___x_1741_);
if (v___x_1743_ == 0)
{
v___y_1735_ = v___x_1743_;
goto v___jp_1734_;
}
else
{
uint32_t v___x_1744_; uint32_t v___x_1745_; uint32_t v___x_1746_; uint8_t v___x_1747_; 
v___x_1744_ = 8388607;
v___x_1745_ = lean_uint32_land(v___y_1713_, v___x_1744_);
v___x_1746_ = 0;
v___x_1747_ = lean_uint32_dec_eq(v___x_1745_, v___x_1746_);
if (v___x_1747_ == 0)
{
v___y_1735_ = v___x_1743_;
goto v___jp_1734_;
}
else
{
goto v___jp_1724_;
}
}
}
v___jp_1748_:
{
if (v___y_1749_ == 0)
{
goto v___jp_1738_;
}
else
{
uint32_t v___x_1750_; uint32_t v___x_1751_; uint32_t v___x_1752_; uint8_t v___x_1753_; 
v___x_1750_ = 4194304;
v___x_1751_ = lean_uint32_land(v___y_1714_, v___x_1750_);
v___x_1752_ = 0;
v___x_1753_ = lean_uint32_dec_eq(v___x_1751_, v___x_1752_);
if (v___x_1753_ == 0)
{
goto v___jp_1738_;
}
else
{
uint32_t v___x_1754_; 
v___x_1754_ = lean_uint32_lor(v___y_1714_, v___x_1750_);
return v___x_1754_;
}
}
}
v___jp_1755_:
{
uint32_t v___x_1756_; uint32_t v___x_1757_; uint32_t v___x_1758_; uint32_t v___x_1759_; uint8_t v___x_1760_; 
v___x_1756_ = 23;
v___x_1757_ = lean_uint32_shift_right(v___y_1714_, v___x_1756_);
v___x_1758_ = 255;
v___x_1759_ = lean_uint32_land(v___x_1757_, v___x_1758_);
v___x_1760_ = lean_uint32_dec_eq(v___x_1759_, v___x_1758_);
if (v___x_1760_ == 0)
{
v___y_1749_ = v___x_1760_;
goto v___jp_1748_;
}
else
{
uint32_t v___x_1761_; uint32_t v___x_1762_; uint32_t v___x_1763_; uint8_t v___x_1764_; 
v___x_1761_ = 8388607;
v___x_1762_ = lean_uint32_land(v___y_1714_, v___x_1761_);
v___x_1763_ = 0;
v___x_1764_ = lean_uint32_dec_eq(v___x_1762_, v___x_1763_);
if (v___x_1764_ == 0)
{
v___y_1749_ = v___x_1760_;
goto v___jp_1748_;
}
else
{
goto v___jp_1738_;
}
}
}
v___jp_1765_:
{
if (v___y_1766_ == 0)
{
goto v___jp_1755_;
}
else
{
uint32_t v___x_1767_; uint32_t v___x_1768_; uint32_t v___x_1769_; uint8_t v___x_1770_; 
v___x_1767_ = 4194304;
v___x_1768_ = lean_uint32_land(v___y_1713_, v___x_1767_);
v___x_1769_ = 0;
v___x_1770_ = lean_uint32_dec_eq(v___x_1768_, v___x_1769_);
if (v___x_1770_ == 0)
{
goto v___jp_1755_;
}
else
{
uint32_t v___x_1771_; 
v___x_1771_ = lean_uint32_lor(v___y_1713_, v___x_1767_);
return v___x_1771_;
}
}
}
v___jp_1772_:
{
float v_result_1775_; uint8_t v___x_1776_; 
v_result_1775_ = lean_float32_add(v___y_1773_, v___y_1774_);
v___x_1776_ = lean_float32_beq(v_result_1775_, v_result_1775_);
if (v___x_1776_ == 0)
{
uint32_t v___x_1777_; uint32_t v___x_1778_; uint32_t v___x_1779_; uint32_t v___x_1780_; uint8_t v___x_1781_; 
v___x_1777_ = 23;
v___x_1778_ = lean_uint32_shift_right(v___y_1713_, v___x_1777_);
v___x_1779_ = 255;
v___x_1780_ = lean_uint32_land(v___x_1778_, v___x_1779_);
v___x_1781_ = lean_uint32_dec_eq(v___x_1780_, v___x_1779_);
if (v___x_1781_ == 0)
{
v___y_1766_ = v___x_1781_;
goto v___jp_1765_;
}
else
{
uint32_t v___x_1782_; uint32_t v___x_1783_; uint32_t v___x_1784_; uint8_t v___x_1785_; 
v___x_1782_ = 8388607;
v___x_1783_ = lean_uint32_land(v___y_1713_, v___x_1782_);
v___x_1784_ = 0;
v___x_1785_ = lean_uint32_dec_eq(v___x_1783_, v___x_1784_);
if (v___x_1785_ == 0)
{
v___y_1766_ = v___x_1781_;
goto v___jp_1765_;
}
else
{
goto v___jp_1755_;
}
}
}
else
{
uint32_t v___x_1786_; 
v___x_1786_ = lean_float32_to_bits(v_result_1775_);
return v___x_1786_;
}
}
v___jp_1787_:
{
if (v___y_1789_ == 0)
{
float v___x_1790_; 
v___x_1790_ = lean_float32_of_bits(v___y_1714_);
v___y_1773_ = v___y_1788_;
v___y_1774_ = v___x_1790_;
goto v___jp_1772_;
}
else
{
uint32_t v___x_1791_; uint32_t v___x_1792_; uint32_t v___x_1793_; uint32_t v___x_1794_; float v___x_1795_; lean_object* v___x_1796_; uint32_t v___x_1797_; uint32_t v___x_1798_; lean_object* v___x_1799_; lean_object* v___x_1800_; float v___x_1801_; float v___x_1802_; 
v___x_1791_ = 8388607;
v___x_1792_ = lean_uint32_land(v___y_1714_, v___x_1791_);
v___x_1793_ = 8388608;
v___x_1794_ = lean_uint32_lor(v___x_1792_, v___x_1793_);
v___x_1795_ = lean_uint32_to_float32(v___x_1794_);
v___x_1796_ = lp_competition_R2W01b_scaleTable;
v___x_1797_ = 23;
v___x_1798_ = lean_uint32_shift_right(v___y_1714_, v___x_1797_);
v___x_1799_ = lean_uint32_to_nat(v___x_1798_);
v___x_1800_ = lean_array_fget_borrowed(v___x_1796_, v___x_1799_);
lean_dec(v___x_1799_);
v___x_1801_ = lean_unbox_float32(v___x_1800_);
v___x_1802_ = lean_float32_mul(v___x_1795_, v___x_1801_);
v___y_1773_ = v___y_1788_;
v___y_1774_ = v___x_1802_;
goto v___jp_1772_;
}
}
v___jp_1803_:
{
uint32_t v___x_1805_; uint32_t v_a_1806_; uint32_t v___x_1807_; uint32_t v___x_1808_; uint32_t v___x_1809_; uint8_t v___x_1810_; 
v___x_1805_ = 2147483647;
v_a_1806_ = lean_uint32_land(v___y_1714_, v___x_1805_);
v___x_1807_ = 201326591;
v___x_1808_ = 1;
v___x_1809_ = lean_uint32_sub(v_a_1806_, v___x_1808_);
v___x_1810_ = lean_uint32_dec_le(v___x_1807_, v___x_1809_);
if (v___x_1810_ == 0)
{
v___y_1788_ = v___y_1804_;
v___y_1789_ = v___x_1810_;
goto v___jp_1787_;
}
else
{
uint32_t v___x_1811_; uint8_t v___x_1812_; 
v___x_1811_ = 2139095040;
v___x_1812_ = lean_uint32_dec_lt(v_a_1806_, v___x_1811_);
v___y_1788_ = v___y_1804_;
v___y_1789_ = v___x_1812_;
goto v___jp_1787_;
}
}
v___jp_1813_:
{
if (v___y_1814_ == 0)
{
float v___x_1815_; 
v___x_1815_ = lean_float32_of_bits(v___y_1713_);
v___y_1804_ = v___x_1815_;
goto v___jp_1803_;
}
else
{
uint32_t v___x_1816_; uint32_t v___x_1817_; uint32_t v___x_1818_; uint32_t v___x_1819_; float v___x_1820_; lean_object* v___x_1821_; uint32_t v___x_1822_; uint32_t v___x_1823_; lean_object* v___x_1824_; lean_object* v___x_1825_; float v___x_1826_; float v___x_1827_; 
v___x_1816_ = 8388607;
v___x_1817_ = lean_uint32_land(v___y_1713_, v___x_1816_);
v___x_1818_ = 8388608;
v___x_1819_ = lean_uint32_lor(v___x_1817_, v___x_1818_);
v___x_1820_ = lean_uint32_to_float32(v___x_1819_);
v___x_1821_ = lp_competition_R2W01b_scaleTable;
v___x_1822_ = 23;
v___x_1823_ = lean_uint32_shift_right(v___y_1713_, v___x_1822_);
v___x_1824_ = lean_uint32_to_nat(v___x_1823_);
v___x_1825_ = lean_array_fget_borrowed(v___x_1821_, v___x_1824_);
lean_dec(v___x_1824_);
v___x_1826_ = lean_unbox_float32(v___x_1825_);
v___x_1827_ = lean_float32_mul(v___x_1820_, v___x_1826_);
v___y_1804_ = v___x_1827_;
goto v___jp_1803_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_runControl___lam__0___boxed(lean_object* v___y_1836_, lean_object* v___y_1837_){
_start:
{
uint32_t v___y_2190__boxed_1838_; uint32_t v___y_2191__boxed_1839_; uint32_t v_res_1840_; lean_object* v_r_1841_; 
v___y_2190__boxed_1838_ = lean_unbox_uint32(v___y_1836_);
lean_dec(v___y_1836_);
v___y_2191__boxed_1839_ = lean_unbox_uint32(v___y_1837_);
lean_dec(v___y_1837_);
v_res_1840_ = lp_competition_runControl___lam__0(v___y_2190__boxed_1838_, v___y_2191__boxed_1839_);
v_r_1841_ = lean_box_uint32(v_res_1840_);
return v_r_1841_;
}
}
LEAN_EXPORT uint32_t lp_competition_runControl___lam__1(uint32_t v___y_1842_, uint32_t v___y_1843_){
_start:
{
uint32_t v___y_1845_; uint32_t v___y_1849_; uint32_t v___y_1853_; uint32_t v___y_1854_; uint32_t v___y_1855_; uint32_t v___y_1859_; uint8_t v___y_1860_; uint64_t v___y_1861_; uint64_t v___y_1862_; uint32_t v___y_1874_; uint32_t v___y_1875_; uint32_t v___y_1876_; uint32_t v___y_1880_; uint8_t v___y_1881_; uint64_t v___y_1882_; uint64_t v___y_1883_; uint8_t v___y_1895_; uint8_t v___y_1911_; uint8_t v___y_1925_; uint8_t v___y_1942_; float v___y_1949_; float v___y_1950_; float v___y_1964_; uint8_t v___y_1965_; float v___y_1980_; uint32_t v___x_1989_; uint32_t v___x_1990_; uint8_t v___y_1992_; uint32_t v___x_2004_; uint32_t v___y_2006_; uint32_t v___y_2007_; uint32_t v___y_2008_; uint32_t v___y_2009_; uint32_t v___y_2016_; uint32_t v___y_2017_; uint8_t v___y_2018_; uint32_t v___y_2019_; uint32_t v___y_2023_; uint64_t v___y_2024_; uint8_t v___y_2025_; uint64_t v___y_2026_; uint64_t v___y_2027_; uint64_t v___y_2037_; uint32_t v___y_2038_; uint8_t v___y_2039_; uint64_t v___y_2040_; uint8_t v___y_2041_; uint64_t v___y_2042_; uint32_t v___y_2049_; uint8_t v___y_2050_; uint64_t v___y_2051_; uint64_t v___y_2052_; uint64_t v___y_2053_; uint64_t v___y_2059_; uint32_t v___y_2060_; uint64_t v___y_2061_; uint8_t v___y_2062_; uint64_t v___y_2063_; uint64_t v___y_2064_; uint64_t v___y_2119_; uint32_t v___y_2120_; uint64_t v___y_2121_; uint8_t v___y_2122_; uint64_t v___y_2123_; uint64_t v___y_2124_; uint64_t v___y_2125_; uint64_t v___y_2131_; uint64_t v___y_2132_; uint64_t v___y_2133_; uint32_t v___y_2134_; uint64_t v___y_2135_; uint8_t v___y_2136_; uint64_t v___y_2137_; uint64_t v___y_2138_; uint64_t v___y_2139_; uint64_t v___y_2144_; uint64_t v___y_2145_; uint32_t v___y_2146_; uint64_t v___y_2147_; uint8_t v___y_2148_; uint64_t v___y_2149_; uint64_t v___y_2150_; uint64_t v___y_2155_; uint64_t v___y_2156_; uint64_t v___y_2157_; uint64_t v___y_2158_; uint32_t v___y_2159_; uint64_t v___y_2160_; uint8_t v___y_2161_; uint64_t v___y_2162_; uint64_t v___y_2163_; uint64_t v___y_2168_; uint64_t v___y_2169_; uint32_t v___y_2170_; uint64_t v___y_2171_; uint8_t v___y_2172_; uint64_t v___y_2173_; uint64_t v___y_2174_; uint64_t v___y_2179_; uint64_t v___y_2180_; uint64_t v___y_2181_; uint32_t v___y_2182_; uint64_t v___y_2183_; uint8_t v___y_2184_; uint64_t v___y_2185_; uint64_t v___y_2186_; uint64_t v___y_2187_; uint64_t v___y_2192_; uint32_t v___y_2193_; uint64_t v___y_2194_; uint8_t v___y_2195_; uint64_t v___y_2196_; uint64_t v___y_2197_; uint64_t v___y_2198_; uint64_t v___y_2203_; uint64_t v___y_2204_; uint64_t v___y_2205_; uint64_t v___y_2206_; uint32_t v___y_2207_; uint64_t v___y_2208_; uint8_t v___y_2209_; uint64_t v___y_2210_; uint64_t v___y_2211_; uint64_t v___y_2216_; uint64_t v___y_2217_; uint32_t v___y_2218_; uint64_t v___y_2219_; uint8_t v___y_2220_; uint64_t v___y_2221_; uint64_t v___y_2222_; uint64_t v___y_2227_; uint32_t v___y_2228_; uint64_t v___y_2229_; uint8_t v___y_2230_; uint64_t v___y_2231_; uint64_t v___y_2232_; uint64_t v___y_2233_; uint64_t v___y_2237_; uint32_t v___y_2238_; uint64_t v___y_2239_; uint8_t v___y_2240_; uint64_t v___y_2249_; uint64_t v___y_2250_; uint32_t v___y_2251_; uint8_t v___y_2252_; uint64_t v___y_2253_; uint64_t v___y_2254_; uint32_t v_ex_2287_; uint32_t v___x_2288_; uint32_t v_ey_2289_; uint64_t v___y_2291_; uint64_t v___y_2292_; uint32_t v___y_2293_; uint8_t v___y_2294_; uint64_t v___y_2295_; uint64_t v___y_2302_; uint32_t v___y_2303_; uint8_t v___y_2304_; uint64_t v___y_2305_; uint32_t v___y_2312_; uint32_t v___y_2313_; uint8_t v___y_2314_; uint64_t v___y_2315_; uint8_t v___y_2323_; uint32_t v___x_2333_; uint32_t v___x_2334_; uint8_t v___x_2335_; uint8_t v___y_2337_; uint8_t v___y_2338_; uint8_t v___y_2340_; uint8_t v___y_2341_; uint8_t v___y_2342_; uint8_t v___y_2344_; uint8_t v___y_2345_; uint8_t v___y_2351_; 
v___x_1989_ = 23;
v___x_1990_ = lean_uint32_shift_right(v___y_1842_, v___x_1989_);
v___x_2004_ = 255;
v_ex_2287_ = lean_uint32_land(v___x_1990_, v___x_2004_);
v___x_2288_ = lean_uint32_shift_right(v___y_1843_, v___x_1989_);
v_ey_2289_ = lean_uint32_land(v___x_2288_, v___x_2004_);
v___x_2333_ = lean_uint32_add(v_ex_2287_, v_ey_2289_);
v___x_2334_ = 128;
v___x_2335_ = lean_uint32_dec_lt(v___x_2333_, v___x_2334_);
if (v___x_2335_ == 0)
{
uint32_t v___x_2360_; uint32_t v_a_2361_; uint32_t v___x_2362_; uint32_t v___x_2363_; uint32_t v___x_2364_; uint8_t v___x_2365_; 
v___x_2360_ = 2147483647;
v_a_2361_ = lean_uint32_land(v___y_1842_, v___x_2360_);
v___x_2362_ = 201326591;
v___x_2363_ = 1;
v___x_2364_ = lean_uint32_sub(v_a_2361_, v___x_2363_);
v___x_2365_ = lean_uint32_dec_le(v___x_2362_, v___x_2364_);
if (v___x_2365_ == 0)
{
v___y_1992_ = v___x_2365_;
goto v___jp_1991_;
}
else
{
uint32_t v___x_2366_; uint8_t v___x_2367_; 
v___x_2366_ = 2139095040;
v___x_2367_ = lean_uint32_dec_lt(v_a_2361_, v___x_2366_);
v___y_1992_ = v___x_2367_;
goto v___jp_1991_;
}
}
else
{
uint32_t v___x_2368_; uint32_t v___x_2369_; uint32_t v___x_2370_; uint8_t v___x_2371_; 
v___x_2368_ = 4278190080;
v___x_2369_ = 1;
v___x_2370_ = lean_uint32_shift_left(v___y_1842_, v___x_2369_);
v___x_2371_ = lean_uint32_dec_le(v___x_2368_, v___x_2370_);
if (v___x_2371_ == 0)
{
uint32_t v___x_2372_; uint8_t v___x_2373_; 
v___x_2372_ = lean_uint32_shift_left(v___y_1843_, v___x_2369_);
v___x_2373_ = lean_uint32_dec_le(v___x_2368_, v___x_2372_);
v___y_2351_ = v___x_2373_;
goto v___jp_2350_;
}
else
{
v___y_2351_ = v___x_2371_;
goto v___jp_2350_;
}
}
v___jp_1844_:
{
uint32_t v___x_1846_; uint32_t v___x_1847_; 
v___x_1846_ = 8388608;
v___x_1847_ = lean_uint32_lor(v___y_1845_, v___x_1846_);
return v___x_1847_;
}
v___jp_1848_:
{
uint32_t v___x_1850_; uint32_t v___x_1851_; 
v___x_1850_ = 8388608;
v___x_1851_ = lean_uint32_lor(v___y_1849_, v___x_1850_);
return v___x_1851_;
}
v___jp_1852_:
{
uint32_t v___x_1856_; uint32_t v___x_1857_; 
v___x_1856_ = lean_uint32_land(v___y_1853_, v___y_1854_);
v___x_1857_ = lean_uint32_lor(v___y_1855_, v___x_1856_);
return v___x_1857_;
}
v___jp_1858_:
{
uint8_t v___x_1863_; 
v___x_1863_ = lean_uint64_dec_eq(v___y_1862_, v___y_1861_);
if (v___x_1863_ == 0)
{
uint64_t v___x_1864_; uint8_t v___x_1865_; 
v___x_1864_ = 8388608ULL;
v___x_1865_ = lean_uint64_dec_eq(v___y_1862_, v___x_1864_);
if (v___x_1865_ == 0)
{
uint32_t v___x_1866_; 
v___x_1866_ = lean_uint64_to_uint32(v___y_1862_);
if (v___y_1860_ == 0)
{
uint32_t v___x_1867_; 
v___x_1867_ = 0;
v___y_1853_ = v___x_1866_;
v___y_1854_ = v___y_1859_;
v___y_1855_ = v___x_1867_;
goto v___jp_1852_;
}
else
{
uint32_t v___x_1868_; 
v___x_1868_ = 2147483648;
v___y_1853_ = v___x_1866_;
v___y_1854_ = v___y_1859_;
v___y_1855_ = v___x_1868_;
goto v___jp_1852_;
}
}
else
{
if (v___y_1860_ == 0)
{
uint32_t v___x_1869_; 
v___x_1869_ = 0;
v___y_1849_ = v___x_1869_;
goto v___jp_1848_;
}
else
{
uint32_t v___x_1870_; 
v___x_1870_ = 2147483648;
v___y_1849_ = v___x_1870_;
goto v___jp_1848_;
}
}
}
else
{
if (v___y_1860_ == 0)
{
uint32_t v___x_1871_; 
v___x_1871_ = 0;
return v___x_1871_;
}
else
{
uint32_t v___x_1872_; 
v___x_1872_ = 2147483648;
return v___x_1872_;
}
}
}
v___jp_1873_:
{
uint32_t v___x_1877_; uint32_t v___x_1878_; 
v___x_1877_ = lean_uint32_land(v___y_1874_, v___y_1875_);
v___x_1878_ = lean_uint32_lor(v___y_1876_, v___x_1877_);
return v___x_1878_;
}
v___jp_1879_:
{
uint8_t v___x_1884_; 
v___x_1884_ = lean_uint64_dec_eq(v___y_1883_, v___y_1882_);
if (v___x_1884_ == 0)
{
uint64_t v___x_1885_; uint8_t v___x_1886_; 
v___x_1885_ = 8388608ULL;
v___x_1886_ = lean_uint64_dec_eq(v___y_1883_, v___x_1885_);
if (v___x_1886_ == 0)
{
uint32_t v___x_1887_; 
v___x_1887_ = lean_uint64_to_uint32(v___y_1883_);
if (v___y_1881_ == 0)
{
uint32_t v___x_1888_; 
v___x_1888_ = 0;
v___y_1874_ = v___x_1887_;
v___y_1875_ = v___y_1880_;
v___y_1876_ = v___x_1888_;
goto v___jp_1873_;
}
else
{
uint32_t v___x_1889_; 
v___x_1889_ = 2147483648;
v___y_1874_ = v___x_1887_;
v___y_1875_ = v___y_1880_;
v___y_1876_ = v___x_1889_;
goto v___jp_1873_;
}
}
else
{
if (v___y_1881_ == 0)
{
uint32_t v___x_1890_; 
v___x_1890_ = 0;
v___y_1845_ = v___x_1890_;
goto v___jp_1844_;
}
else
{
uint32_t v___x_1891_; 
v___x_1891_ = 2147483648;
v___y_1845_ = v___x_1891_;
goto v___jp_1844_;
}
}
}
else
{
if (v___y_1881_ == 0)
{
uint32_t v___x_1892_; 
v___x_1892_ = 0;
return v___x_1892_;
}
else
{
uint32_t v___x_1893_; 
v___x_1893_ = 2147483648;
return v___x_1893_;
}
}
}
v___jp_1894_:
{
if (v___y_1895_ == 0)
{
uint32_t v___x_1896_; 
v___x_1896_ = lp_competition_Submission_FastMul_mul(v___y_1842_, v___y_1843_);
return v___x_1896_;
}
else
{
uint32_t v___x_1897_; uint32_t v___x_1898_; 
v___x_1897_ = 4194304;
v___x_1898_ = lean_uint32_lor(v___y_1843_, v___x_1897_);
return v___x_1898_;
}
}
v___jp_1899_:
{
uint32_t v___x_1900_; uint32_t v___x_1901_; uint32_t v___x_1902_; uint32_t v___x_1903_; uint8_t v___x_1904_; 
v___x_1900_ = 23;
v___x_1901_ = lean_uint32_shift_right(v___y_1843_, v___x_1900_);
v___x_1902_ = 255;
v___x_1903_ = lean_uint32_land(v___x_1901_, v___x_1902_);
v___x_1904_ = lean_uint32_dec_eq(v___x_1903_, v___x_1902_);
if (v___x_1904_ == 0)
{
v___y_1895_ = v___x_1904_;
goto v___jp_1894_;
}
else
{
uint32_t v___x_1905_; uint32_t v___x_1906_; uint32_t v___x_1907_; uint8_t v___x_1908_; 
v___x_1905_ = 8388607;
v___x_1906_ = lean_uint32_land(v___y_1843_, v___x_1905_);
v___x_1907_ = 0;
v___x_1908_ = lean_uint32_dec_eq(v___x_1906_, v___x_1907_);
if (v___x_1908_ == 0)
{
v___y_1895_ = v___x_1904_;
goto v___jp_1894_;
}
else
{
uint32_t v___x_1909_; 
v___x_1909_ = lp_competition_Submission_FastMul_mul(v___y_1842_, v___y_1843_);
return v___x_1909_;
}
}
}
v___jp_1910_:
{
if (v___y_1911_ == 0)
{
goto v___jp_1899_;
}
else
{
uint32_t v___x_1912_; uint32_t v___x_1913_; 
v___x_1912_ = 4194304;
v___x_1913_ = lean_uint32_lor(v___y_1842_, v___x_1912_);
return v___x_1913_;
}
}
v___jp_1914_:
{
uint32_t v___x_1915_; uint32_t v___x_1916_; uint32_t v___x_1917_; uint32_t v___x_1918_; uint8_t v___x_1919_; 
v___x_1915_ = 23;
v___x_1916_ = lean_uint32_shift_right(v___y_1842_, v___x_1915_);
v___x_1917_ = 255;
v___x_1918_ = lean_uint32_land(v___x_1916_, v___x_1917_);
v___x_1919_ = lean_uint32_dec_eq(v___x_1918_, v___x_1917_);
if (v___x_1919_ == 0)
{
v___y_1911_ = v___x_1919_;
goto v___jp_1910_;
}
else
{
uint32_t v___x_1920_; uint32_t v___x_1921_; uint32_t v___x_1922_; uint8_t v___x_1923_; 
v___x_1920_ = 8388607;
v___x_1921_ = lean_uint32_land(v___y_1842_, v___x_1920_);
v___x_1922_ = 0;
v___x_1923_ = lean_uint32_dec_eq(v___x_1921_, v___x_1922_);
if (v___x_1923_ == 0)
{
v___y_1911_ = v___x_1919_;
goto v___jp_1910_;
}
else
{
goto v___jp_1899_;
}
}
}
v___jp_1924_:
{
if (v___y_1925_ == 0)
{
goto v___jp_1914_;
}
else
{
uint32_t v___x_1926_; uint32_t v___x_1927_; uint32_t v___x_1928_; uint8_t v___x_1929_; 
v___x_1926_ = 4194304;
v___x_1927_ = lean_uint32_land(v___y_1843_, v___x_1926_);
v___x_1928_ = 0;
v___x_1929_ = lean_uint32_dec_eq(v___x_1927_, v___x_1928_);
if (v___x_1929_ == 0)
{
goto v___jp_1914_;
}
else
{
uint32_t v___x_1930_; 
v___x_1930_ = lean_uint32_lor(v___y_1843_, v___x_1926_);
return v___x_1930_;
}
}
}
v___jp_1931_:
{
uint32_t v___x_1932_; uint32_t v___x_1933_; uint32_t v___x_1934_; uint32_t v___x_1935_; uint8_t v___x_1936_; 
v___x_1932_ = 23;
v___x_1933_ = lean_uint32_shift_right(v___y_1843_, v___x_1932_);
v___x_1934_ = 255;
v___x_1935_ = lean_uint32_land(v___x_1933_, v___x_1934_);
v___x_1936_ = lean_uint32_dec_eq(v___x_1935_, v___x_1934_);
if (v___x_1936_ == 0)
{
v___y_1925_ = v___x_1936_;
goto v___jp_1924_;
}
else
{
uint32_t v___x_1937_; uint32_t v___x_1938_; uint32_t v___x_1939_; uint8_t v___x_1940_; 
v___x_1937_ = 8388607;
v___x_1938_ = lean_uint32_land(v___y_1843_, v___x_1937_);
v___x_1939_ = 0;
v___x_1940_ = lean_uint32_dec_eq(v___x_1938_, v___x_1939_);
if (v___x_1940_ == 0)
{
v___y_1925_ = v___x_1936_;
goto v___jp_1924_;
}
else
{
goto v___jp_1914_;
}
}
}
v___jp_1941_:
{
if (v___y_1942_ == 0)
{
goto v___jp_1931_;
}
else
{
uint32_t v___x_1943_; uint32_t v___x_1944_; uint32_t v___x_1945_; uint8_t v___x_1946_; 
v___x_1943_ = 4194304;
v___x_1944_ = lean_uint32_land(v___y_1842_, v___x_1943_);
v___x_1945_ = 0;
v___x_1946_ = lean_uint32_dec_eq(v___x_1944_, v___x_1945_);
if (v___x_1946_ == 0)
{
goto v___jp_1931_;
}
else
{
uint32_t v___x_1947_; 
v___x_1947_ = lean_uint32_lor(v___y_1842_, v___x_1943_);
return v___x_1947_;
}
}
}
v___jp_1948_:
{
float v_result_1951_; uint8_t v___x_1952_; 
v_result_1951_ = lean_float32_mul(v___y_1949_, v___y_1950_);
v___x_1952_ = lean_float32_beq(v_result_1951_, v_result_1951_);
if (v___x_1952_ == 0)
{
uint32_t v___x_1953_; uint32_t v___x_1954_; uint32_t v___x_1955_; uint32_t v___x_1956_; uint8_t v___x_1957_; 
v___x_1953_ = 23;
v___x_1954_ = lean_uint32_shift_right(v___y_1842_, v___x_1953_);
v___x_1955_ = 255;
v___x_1956_ = lean_uint32_land(v___x_1954_, v___x_1955_);
v___x_1957_ = lean_uint32_dec_eq(v___x_1956_, v___x_1955_);
if (v___x_1957_ == 0)
{
v___y_1942_ = v___x_1957_;
goto v___jp_1941_;
}
else
{
uint32_t v___x_1958_; uint32_t v___x_1959_; uint32_t v___x_1960_; uint8_t v___x_1961_; 
v___x_1958_ = 8388607;
v___x_1959_ = lean_uint32_land(v___y_1842_, v___x_1958_);
v___x_1960_ = 0;
v___x_1961_ = lean_uint32_dec_eq(v___x_1959_, v___x_1960_);
if (v___x_1961_ == 0)
{
v___y_1942_ = v___x_1957_;
goto v___jp_1941_;
}
else
{
goto v___jp_1931_;
}
}
}
else
{
uint32_t v___x_1962_; 
v___x_1962_ = lean_float32_to_bits(v_result_1951_);
return v___x_1962_;
}
}
v___jp_1963_:
{
if (v___y_1965_ == 0)
{
float v___x_1966_; 
v___x_1966_ = lean_float32_of_bits(v___y_1843_);
v___y_1949_ = v___y_1964_;
v___y_1950_ = v___x_1966_;
goto v___jp_1948_;
}
else
{
uint32_t v___x_1967_; uint32_t v___x_1968_; uint32_t v___x_1969_; uint32_t v___x_1970_; float v___x_1971_; lean_object* v___x_1972_; uint32_t v___x_1973_; uint32_t v___x_1974_; lean_object* v___x_1975_; lean_object* v___x_1976_; float v___x_1977_; float v___x_1978_; 
v___x_1967_ = 8388607;
v___x_1968_ = lean_uint32_land(v___y_1843_, v___x_1967_);
v___x_1969_ = 8388608;
v___x_1970_ = lean_uint32_lor(v___x_1968_, v___x_1969_);
v___x_1971_ = lean_uint32_to_float32(v___x_1970_);
v___x_1972_ = lp_competition_R2W01b_scaleTable;
v___x_1973_ = 23;
v___x_1974_ = lean_uint32_shift_right(v___y_1843_, v___x_1973_);
v___x_1975_ = lean_uint32_to_nat(v___x_1974_);
v___x_1976_ = lean_array_fget_borrowed(v___x_1972_, v___x_1975_);
lean_dec(v___x_1975_);
v___x_1977_ = lean_unbox_float32(v___x_1976_);
v___x_1978_ = lean_float32_mul(v___x_1971_, v___x_1977_);
v___y_1949_ = v___y_1964_;
v___y_1950_ = v___x_1978_;
goto v___jp_1948_;
}
}
v___jp_1979_:
{
uint32_t v___x_1981_; uint32_t v_a_1982_; uint32_t v___x_1983_; uint32_t v___x_1984_; uint32_t v___x_1985_; uint8_t v___x_1986_; 
v___x_1981_ = 2147483647;
v_a_1982_ = lean_uint32_land(v___y_1843_, v___x_1981_);
v___x_1983_ = 201326591;
v___x_1984_ = 1;
v___x_1985_ = lean_uint32_sub(v_a_1982_, v___x_1984_);
v___x_1986_ = lean_uint32_dec_le(v___x_1983_, v___x_1985_);
if (v___x_1986_ == 0)
{
v___y_1964_ = v___y_1980_;
v___y_1965_ = v___x_1986_;
goto v___jp_1963_;
}
else
{
uint32_t v___x_1987_; uint8_t v___x_1988_; 
v___x_1987_ = 2139095040;
v___x_1988_ = lean_uint32_dec_lt(v_a_1982_, v___x_1987_);
v___y_1964_ = v___y_1980_;
v___y_1965_ = v___x_1988_;
goto v___jp_1963_;
}
}
v___jp_1991_:
{
if (v___y_1992_ == 0)
{
float v___x_1993_; 
v___x_1993_ = lean_float32_of_bits(v___y_1842_);
v___y_1980_ = v___x_1993_;
goto v___jp_1979_;
}
else
{
uint32_t v___x_1994_; uint32_t v___x_1995_; uint32_t v___x_1996_; uint32_t v___x_1997_; float v___x_1998_; lean_object* v___x_1999_; lean_object* v___x_2000_; lean_object* v___x_2001_; float v___x_2002_; float v___x_2003_; 
v___x_1994_ = 8388607;
v___x_1995_ = lean_uint32_land(v___y_1842_, v___x_1994_);
v___x_1996_ = 8388608;
v___x_1997_ = lean_uint32_lor(v___x_1995_, v___x_1996_);
v___x_1998_ = lean_uint32_to_float32(v___x_1997_);
v___x_1999_ = lp_competition_R2W01b_scaleTable;
v___x_2000_ = lean_uint32_to_nat(v___x_1990_);
v___x_2001_ = lean_array_fget_borrowed(v___x_1999_, v___x_2000_);
lean_dec(v___x_2000_);
v___x_2002_ = lean_unbox_float32(v___x_2001_);
v___x_2003_ = lean_float32_mul(v___x_1998_, v___x_2002_);
v___y_1980_ = v___x_2003_;
goto v___jp_1979_;
}
}
v___jp_2005_:
{
uint32_t v___x_2010_; uint32_t v___x_2011_; uint32_t v___x_2012_; uint32_t v___x_2013_; uint32_t v___x_2014_; 
v___x_2010_ = lean_uint32_land(v___y_2007_, v___x_2004_);
v___x_2011_ = lean_uint32_shift_left(v___x_2010_, v___x_1989_);
v___x_2012_ = lean_uint32_lor(v___y_2009_, v___x_2011_);
v___x_2013_ = lean_uint32_land(v___y_2008_, v___y_2006_);
v___x_2014_ = lean_uint32_lor(v___x_2012_, v___x_2013_);
return v___x_2014_;
}
v___jp_2015_:
{
if (v___y_2018_ == 0)
{
uint32_t v___x_2020_; 
v___x_2020_ = 0;
v___y_2006_ = v___y_2017_;
v___y_2007_ = v___y_2016_;
v___y_2008_ = v___y_2019_;
v___y_2009_ = v___x_2020_;
goto v___jp_2005_;
}
else
{
uint32_t v___x_2021_; 
v___x_2021_ = 2147483648;
v___y_2006_ = v___y_2017_;
v___y_2007_ = v___y_2016_;
v___y_2008_ = v___y_2019_;
v___y_2009_ = v___x_2021_;
goto v___jp_2005_;
}
}
v___jp_2022_:
{
uint64_t v___x_2028_; uint64_t v_encodedExponent_2029_; uint32_t v___x_2030_; uint64_t v___x_2031_; uint8_t v___x_2032_; 
v___x_2028_ = 171ULL;
v_encodedExponent_2029_ = lean_uint64_sub(v___y_2024_, v___x_2028_);
v___x_2030_ = lean_uint64_to_uint32(v_encodedExponent_2029_);
v___x_2031_ = 8388608ULL;
v___x_2032_ = lean_uint64_dec_lt(v___y_2027_, v___x_2031_);
if (v___x_2032_ == 0)
{
uint64_t v___x_2033_; uint32_t v___x_2034_; 
v___x_2033_ = lean_uint64_sub(v___y_2027_, v___x_2031_);
v___x_2034_ = lean_uint64_to_uint32(v___x_2033_);
v___y_2016_ = v___x_2030_;
v___y_2017_ = v___y_2023_;
v___y_2018_ = v___y_2025_;
v___y_2019_ = v___x_2034_;
goto v___jp_2015_;
}
else
{
uint32_t v___x_2035_; 
v___x_2035_ = lean_uint64_to_uint32(v___y_2026_);
v___y_2016_ = v___x_2030_;
v___y_2017_ = v___y_2023_;
v___y_2018_ = v___y_2025_;
v___y_2019_ = v___x_2035_;
goto v___jp_2015_;
}
}
v___jp_2036_:
{
uint64_t v___x_2043_; uint8_t v___x_2044_; 
v___x_2043_ = 425ULL;
v___x_2044_ = lean_uint64_dec_lt(v___x_2043_, v___y_2042_);
if (v___x_2044_ == 0)
{
if (v___y_2041_ == 0)
{
v___y_2023_ = v___y_2038_;
v___y_2024_ = v___y_2042_;
v___y_2025_ = v___y_2039_;
v___y_2026_ = v___y_2040_;
v___y_2027_ = v___y_2037_;
goto v___jp_2022_;
}
else
{
uint64_t v___x_2045_; 
v___x_2045_ = 8388608ULL;
v___y_2023_ = v___y_2038_;
v___y_2024_ = v___y_2042_;
v___y_2025_ = v___y_2039_;
v___y_2026_ = v___y_2040_;
v___y_2027_ = v___x_2045_;
goto v___jp_2022_;
}
}
else
{
if (v___y_2039_ == 0)
{
uint32_t v___x_2046_; 
v___x_2046_ = 2139095040;
return v___x_2046_;
}
else
{
uint32_t v___x_2047_; 
v___x_2047_ = 4286578688;
return v___x_2047_;
}
}
}
v___jp_2048_:
{
uint64_t v___x_2054_; uint8_t v_carry_2055_; 
v___x_2054_ = 16777216ULL;
v_carry_2055_ = lean_uint64_dec_eq(v___y_2053_, v___x_2054_);
if (v_carry_2055_ == 0)
{
v___y_2037_ = v___y_2053_;
v___y_2038_ = v___y_2049_;
v___y_2039_ = v___y_2050_;
v___y_2040_ = v___y_2052_;
v___y_2041_ = v_carry_2055_;
v___y_2042_ = v___y_2051_;
goto v___jp_2036_;
}
else
{
uint64_t v___x_2056_; uint64_t v___x_2057_; 
v___x_2056_ = 1ULL;
v___x_2057_ = lean_uint64_add(v___y_2051_, v___x_2056_);
v___y_2037_ = v___y_2053_;
v___y_2038_ = v___y_2049_;
v___y_2039_ = v___y_2050_;
v___y_2040_ = v___y_2052_;
v___y_2041_ = v_carry_2055_;
v___y_2042_ = v___x_2057_;
goto v___jp_2036_;
}
}
v___jp_2058_:
{
uint64_t v_position_2065_; uint64_t v___x_2066_; uint8_t v___x_2067_; 
v_position_2065_ = lean_uint64_add(v___y_2064_, v___y_2061_);
v___x_2066_ = 172ULL;
v___x_2067_ = lean_uint64_dec_lt(v_position_2065_, v___x_2066_);
if (v___x_2067_ == 0)
{
uint64_t v___x_2068_; uint8_t v___x_2069_; 
v___x_2068_ = 23ULL;
v___x_2069_ = lean_uint64_dec_lt(v___y_2064_, v___x_2068_);
if (v___x_2069_ == 0)
{
uint64_t v___x_2070_; uint8_t v___x_2071_; 
v___x_2070_ = lean_uint64_sub(v___y_2064_, v___x_2068_);
v___x_2071_ = lean_uint64_dec_eq(v___x_2070_, v___y_2063_);
if (v___x_2071_ == 0)
{
uint64_t v___x_2072_; uint8_t v___x_2073_; 
v___x_2072_ = 64ULL;
v___x_2073_ = lean_uint64_dec_lt(v___x_2070_, v___x_2072_);
if (v___x_2073_ == 0)
{
uint8_t v___x_2074_; 
v___x_2074_ = lean_uint64_dec_eq(v___x_2070_, v___x_2072_);
if (v___x_2074_ == 0)
{
v___y_2049_ = v___y_2060_;
v___y_2050_ = v___y_2062_;
v___y_2051_ = v_position_2065_;
v___y_2052_ = v___y_2063_;
v___y_2053_ = v___y_2063_;
goto v___jp_2048_;
}
else
{
uint64_t v___x_2075_; uint8_t v___x_2076_; 
v___x_2075_ = 9223372036854775808ULL;
v___x_2076_ = lean_uint64_dec_lt(v___x_2075_, v___y_2059_);
if (v___x_2076_ == 0)
{
v___y_2049_ = v___y_2060_;
v___y_2050_ = v___y_2062_;
v___y_2051_ = v_position_2065_;
v___y_2052_ = v___y_2063_;
v___y_2053_ = v___y_2063_;
goto v___jp_2048_;
}
else
{
uint64_t v___x_2077_; 
v___x_2077_ = 1ULL;
v___y_2049_ = v___y_2060_;
v___y_2050_ = v___y_2062_;
v___y_2051_ = v_position_2065_;
v___y_2052_ = v___y_2063_;
v___y_2053_ = v___x_2077_;
goto v___jp_2048_;
}
}
}
else
{
uint64_t v_quotient_2078_; uint64_t v___x_2079_; uint64_t v___x_2080_; uint64_t v___x_2081_; uint64_t v_remainder_2082_; uint64_t v___x_2083_; uint64_t v_half_2084_; uint8_t v___x_2085_; 
v_quotient_2078_ = lean_uint64_shift_right(v___y_2059_, v___x_2070_);
v___x_2079_ = 1ULL;
v___x_2080_ = lean_uint64_shift_left(v___x_2079_, v___x_2070_);
v___x_2081_ = lean_uint64_sub(v___x_2080_, v___x_2079_);
v_remainder_2082_ = lean_uint64_land(v___y_2059_, v___x_2081_);
v___x_2083_ = lean_uint64_sub(v___x_2070_, v___x_2079_);
v_half_2084_ = lean_uint64_shift_left(v___x_2079_, v___x_2083_);
v___x_2085_ = lean_uint64_dec_lt(v_remainder_2082_, v_half_2084_);
if (v___x_2085_ == 0)
{
uint8_t v___x_2086_; 
v___x_2086_ = lean_uint64_dec_lt(v_half_2084_, v_remainder_2082_);
if (v___x_2086_ == 0)
{
uint64_t v___x_2087_; uint8_t v___x_2088_; 
v___x_2087_ = lean_uint64_land(v_quotient_2078_, v___x_2079_);
v___x_2088_ = lean_uint64_dec_eq(v___x_2087_, v___y_2063_);
if (v___x_2088_ == 0)
{
uint64_t v___x_2089_; 
v___x_2089_ = lean_uint64_add(v_quotient_2078_, v___x_2079_);
v___y_2049_ = v___y_2060_;
v___y_2050_ = v___y_2062_;
v___y_2051_ = v_position_2065_;
v___y_2052_ = v___y_2063_;
v___y_2053_ = v___x_2089_;
goto v___jp_2048_;
}
else
{
v___y_2049_ = v___y_2060_;
v___y_2050_ = v___y_2062_;
v___y_2051_ = v_position_2065_;
v___y_2052_ = v___y_2063_;
v___y_2053_ = v_quotient_2078_;
goto v___jp_2048_;
}
}
else
{
uint64_t v___x_2090_; 
v___x_2090_ = lean_uint64_add(v_quotient_2078_, v___x_2079_);
v___y_2049_ = v___y_2060_;
v___y_2050_ = v___y_2062_;
v___y_2051_ = v_position_2065_;
v___y_2052_ = v___y_2063_;
v___y_2053_ = v___x_2090_;
goto v___jp_2048_;
}
}
else
{
v___y_2049_ = v___y_2060_;
v___y_2050_ = v___y_2062_;
v___y_2051_ = v_position_2065_;
v___y_2052_ = v___y_2063_;
v___y_2053_ = v_quotient_2078_;
goto v___jp_2048_;
}
}
}
else
{
v___y_2049_ = v___y_2060_;
v___y_2050_ = v___y_2062_;
v___y_2051_ = v_position_2065_;
v___y_2052_ = v___y_2063_;
v___y_2053_ = v___y_2059_;
goto v___jp_2048_;
}
}
else
{
uint64_t v___x_2091_; uint64_t v___x_2092_; 
v___x_2091_ = lean_uint64_sub(v___x_2068_, v___y_2064_);
v___x_2092_ = lean_uint64_shift_left(v___y_2059_, v___x_2091_);
v___y_2049_ = v___y_2060_;
v___y_2050_ = v___y_2062_;
v___y_2051_ = v_position_2065_;
v___y_2052_ = v___y_2063_;
v___y_2053_ = v___x_2092_;
goto v___jp_2048_;
}
}
else
{
uint64_t v___x_2093_; uint8_t v___x_2094_; 
v___x_2093_ = 149ULL;
v___x_2094_ = lean_uint64_dec_lt(v___y_2061_, v___x_2093_);
if (v___x_2094_ == 0)
{
uint64_t v___x_2095_; uint64_t v___x_2096_; 
v___x_2095_ = lean_uint64_sub(v___y_2061_, v___x_2093_);
v___x_2096_ = lean_uint64_shift_left(v___y_2059_, v___x_2095_);
v___y_1859_ = v___y_2060_;
v___y_1860_ = v___y_2062_;
v___y_1861_ = v___y_2063_;
v___y_1862_ = v___x_2096_;
goto v___jp_1858_;
}
else
{
uint64_t v___x_2097_; uint8_t v___x_2098_; 
v___x_2097_ = lean_uint64_sub(v___x_2093_, v___y_2061_);
v___x_2098_ = lean_uint64_dec_eq(v___x_2097_, v___y_2063_);
if (v___x_2098_ == 0)
{
uint64_t v___x_2099_; uint8_t v___x_2100_; 
v___x_2099_ = 64ULL;
v___x_2100_ = lean_uint64_dec_lt(v___x_2097_, v___x_2099_);
if (v___x_2100_ == 0)
{
uint8_t v___x_2101_; 
v___x_2101_ = lean_uint64_dec_eq(v___x_2097_, v___x_2099_);
if (v___x_2101_ == 0)
{
v___y_1859_ = v___y_2060_;
v___y_1860_ = v___y_2062_;
v___y_1861_ = v___y_2063_;
v___y_1862_ = v___y_2063_;
goto v___jp_1858_;
}
else
{
uint64_t v___x_2102_; uint8_t v___x_2103_; 
v___x_2102_ = 9223372036854775808ULL;
v___x_2103_ = lean_uint64_dec_lt(v___x_2102_, v___y_2059_);
if (v___x_2103_ == 0)
{
v___y_1859_ = v___y_2060_;
v___y_1860_ = v___y_2062_;
v___y_1861_ = v___y_2063_;
v___y_1862_ = v___y_2063_;
goto v___jp_1858_;
}
else
{
uint64_t v___x_2104_; 
v___x_2104_ = 1ULL;
v___y_1859_ = v___y_2060_;
v___y_1860_ = v___y_2062_;
v___y_1861_ = v___y_2063_;
v___y_1862_ = v___x_2104_;
goto v___jp_1858_;
}
}
}
else
{
uint64_t v_quotient_2105_; uint64_t v___x_2106_; uint64_t v___x_2107_; uint64_t v___x_2108_; uint64_t v_remainder_2109_; uint64_t v___x_2110_; uint64_t v_half_2111_; uint8_t v___x_2112_; 
v_quotient_2105_ = lean_uint64_shift_right(v___y_2059_, v___x_2097_);
v___x_2106_ = 1ULL;
v___x_2107_ = lean_uint64_shift_left(v___x_2106_, v___x_2097_);
v___x_2108_ = lean_uint64_sub(v___x_2107_, v___x_2106_);
v_remainder_2109_ = lean_uint64_land(v___y_2059_, v___x_2108_);
v___x_2110_ = lean_uint64_sub(v___x_2097_, v___x_2106_);
v_half_2111_ = lean_uint64_shift_left(v___x_2106_, v___x_2110_);
v___x_2112_ = lean_uint64_dec_lt(v_remainder_2109_, v_half_2111_);
if (v___x_2112_ == 0)
{
uint8_t v___x_2113_; 
v___x_2113_ = lean_uint64_dec_lt(v_half_2111_, v_remainder_2109_);
if (v___x_2113_ == 0)
{
uint64_t v___x_2114_; uint8_t v___x_2115_; 
v___x_2114_ = lean_uint64_land(v_quotient_2105_, v___x_2106_);
v___x_2115_ = lean_uint64_dec_eq(v___x_2114_, v___y_2063_);
if (v___x_2115_ == 0)
{
uint64_t v___x_2116_; 
v___x_2116_ = lean_uint64_add(v_quotient_2105_, v___x_2106_);
v___y_1859_ = v___y_2060_;
v___y_1860_ = v___y_2062_;
v___y_1861_ = v___y_2063_;
v___y_1862_ = v___x_2116_;
goto v___jp_1858_;
}
else
{
v___y_1859_ = v___y_2060_;
v___y_1860_ = v___y_2062_;
v___y_1861_ = v___y_2063_;
v___y_1862_ = v_quotient_2105_;
goto v___jp_1858_;
}
}
else
{
uint64_t v___x_2117_; 
v___x_2117_ = lean_uint64_add(v_quotient_2105_, v___x_2106_);
v___y_1859_ = v___y_2060_;
v___y_1860_ = v___y_2062_;
v___y_1861_ = v___y_2063_;
v___y_1862_ = v___x_2117_;
goto v___jp_1858_;
}
}
else
{
v___y_1859_ = v___y_2060_;
v___y_1860_ = v___y_2062_;
v___y_1861_ = v___y_2063_;
v___y_1862_ = v_quotient_2105_;
goto v___jp_1858_;
}
}
}
else
{
v___y_1859_ = v___y_2060_;
v___y_1860_ = v___y_2062_;
v___y_1861_ = v___y_2063_;
v___y_1862_ = v___y_2059_;
goto v___jp_1858_;
}
}
}
}
v___jp_2118_:
{
uint64_t v___x_2126_; uint64_t v___x_2127_; uint8_t v___x_2128_; 
v___x_2126_ = 1ULL;
v___x_2127_ = lean_uint64_shift_right(v___y_2124_, v___x_2126_);
v___x_2128_ = lean_uint64_dec_eq(v___x_2127_, v___y_2123_);
if (v___x_2128_ == 0)
{
uint64_t v___x_2129_; 
v___x_2129_ = lean_uint64_add(v___y_2125_, v___x_2126_);
v___y_2059_ = v___y_2119_;
v___y_2060_ = v___y_2120_;
v___y_2061_ = v___y_2121_;
v___y_2062_ = v___y_2122_;
v___y_2063_ = v___y_2123_;
v___y_2064_ = v___x_2129_;
goto v___jp_2058_;
}
else
{
v___y_2059_ = v___y_2119_;
v___y_2060_ = v___y_2120_;
v___y_2061_ = v___y_2121_;
v___y_2062_ = v___y_2122_;
v___y_2063_ = v___y_2123_;
v___y_2064_ = v___y_2125_;
goto v___jp_2058_;
}
}
v___jp_2130_:
{
uint64_t v___x_2140_; uint8_t v___x_2141_; 
v___x_2140_ = lean_uint64_shift_right(v___y_2131_, v___y_2138_);
v___x_2141_ = lean_uint64_dec_eq(v___x_2140_, v___y_2137_);
if (v___x_2141_ == 0)
{
uint64_t v___x_2142_; 
v___x_2142_ = lean_uint64_add(v___y_2133_, v___y_2138_);
v___y_2119_ = v___y_2132_;
v___y_2120_ = v___y_2134_;
v___y_2121_ = v___y_2135_;
v___y_2122_ = v___y_2136_;
v___y_2123_ = v___y_2137_;
v___y_2124_ = v___y_2139_;
v___y_2125_ = v___x_2142_;
goto v___jp_2118_;
}
else
{
v___y_2119_ = v___y_2132_;
v___y_2120_ = v___y_2134_;
v___y_2121_ = v___y_2135_;
v___y_2122_ = v___y_2136_;
v___y_2123_ = v___y_2137_;
v___y_2124_ = v___y_2139_;
v___y_2125_ = v___y_2133_;
goto v___jp_2118_;
}
}
v___jp_2143_:
{
uint64_t v___x_2151_; uint64_t v___x_2152_; uint8_t v___x_2153_; 
v___x_2151_ = 2ULL;
v___x_2152_ = lean_uint64_shift_right(v___y_2144_, v___x_2151_);
v___x_2153_ = lean_uint64_dec_eq(v___x_2152_, v___y_2149_);
if (v___x_2153_ == 0)
{
v___y_2131_ = v___y_2144_;
v___y_2132_ = v___y_2145_;
v___y_2133_ = v___y_2150_;
v___y_2134_ = v___y_2146_;
v___y_2135_ = v___y_2147_;
v___y_2136_ = v___y_2148_;
v___y_2137_ = v___y_2149_;
v___y_2138_ = v___x_2151_;
v___y_2139_ = v___x_2152_;
goto v___jp_2130_;
}
else
{
v___y_2131_ = v___y_2144_;
v___y_2132_ = v___y_2145_;
v___y_2133_ = v___y_2150_;
v___y_2134_ = v___y_2146_;
v___y_2135_ = v___y_2147_;
v___y_2136_ = v___y_2148_;
v___y_2137_ = v___y_2149_;
v___y_2138_ = v___x_2151_;
v___y_2139_ = v___y_2144_;
goto v___jp_2130_;
}
}
v___jp_2154_:
{
uint64_t v___x_2164_; uint8_t v___x_2165_; 
v___x_2164_ = lean_uint64_shift_right(v___y_2155_, v___y_2158_);
v___x_2165_ = lean_uint64_dec_eq(v___x_2164_, v___y_2162_);
if (v___x_2165_ == 0)
{
uint64_t v___x_2166_; 
v___x_2166_ = lean_uint64_add(v___y_2157_, v___y_2158_);
v___y_2144_ = v___y_2163_;
v___y_2145_ = v___y_2156_;
v___y_2146_ = v___y_2159_;
v___y_2147_ = v___y_2160_;
v___y_2148_ = v___y_2161_;
v___y_2149_ = v___y_2162_;
v___y_2150_ = v___x_2166_;
goto v___jp_2143_;
}
else
{
v___y_2144_ = v___y_2163_;
v___y_2145_ = v___y_2156_;
v___y_2146_ = v___y_2159_;
v___y_2147_ = v___y_2160_;
v___y_2148_ = v___y_2161_;
v___y_2149_ = v___y_2162_;
v___y_2150_ = v___y_2157_;
goto v___jp_2143_;
}
}
v___jp_2167_:
{
uint64_t v___x_2175_; uint64_t v___x_2176_; uint8_t v___x_2177_; 
v___x_2175_ = 4ULL;
v___x_2176_ = lean_uint64_shift_right(v___y_2168_, v___x_2175_);
v___x_2177_ = lean_uint64_dec_eq(v___x_2176_, v___y_2173_);
if (v___x_2177_ == 0)
{
v___y_2155_ = v___y_2168_;
v___y_2156_ = v___y_2169_;
v___y_2157_ = v___y_2174_;
v___y_2158_ = v___x_2175_;
v___y_2159_ = v___y_2170_;
v___y_2160_ = v___y_2171_;
v___y_2161_ = v___y_2172_;
v___y_2162_ = v___y_2173_;
v___y_2163_ = v___x_2176_;
goto v___jp_2154_;
}
else
{
v___y_2155_ = v___y_2168_;
v___y_2156_ = v___y_2169_;
v___y_2157_ = v___y_2174_;
v___y_2158_ = v___x_2175_;
v___y_2159_ = v___y_2170_;
v___y_2160_ = v___y_2171_;
v___y_2161_ = v___y_2172_;
v___y_2162_ = v___y_2173_;
v___y_2163_ = v___y_2168_;
goto v___jp_2154_;
}
}
v___jp_2178_:
{
uint64_t v___x_2188_; uint8_t v___x_2189_; 
v___x_2188_ = lean_uint64_shift_right(v___y_2185_, v___y_2179_);
v___x_2189_ = lean_uint64_dec_eq(v___x_2188_, v___y_2186_);
if (v___x_2189_ == 0)
{
uint64_t v___x_2190_; 
v___x_2190_ = lean_uint64_add(v___y_2180_, v___y_2179_);
v___y_2168_ = v___y_2187_;
v___y_2169_ = v___y_2181_;
v___y_2170_ = v___y_2182_;
v___y_2171_ = v___y_2183_;
v___y_2172_ = v___y_2184_;
v___y_2173_ = v___y_2186_;
v___y_2174_ = v___x_2190_;
goto v___jp_2167_;
}
else
{
v___y_2168_ = v___y_2187_;
v___y_2169_ = v___y_2181_;
v___y_2170_ = v___y_2182_;
v___y_2171_ = v___y_2183_;
v___y_2172_ = v___y_2184_;
v___y_2173_ = v___y_2186_;
v___y_2174_ = v___y_2180_;
goto v___jp_2167_;
}
}
v___jp_2191_:
{
uint64_t v___x_2199_; uint64_t v___x_2200_; uint8_t v___x_2201_; 
v___x_2199_ = 8ULL;
v___x_2200_ = lean_uint64_shift_right(v___y_2196_, v___x_2199_);
v___x_2201_ = lean_uint64_dec_eq(v___x_2200_, v___y_2197_);
if (v___x_2201_ == 0)
{
v___y_2179_ = v___x_2199_;
v___y_2180_ = v___y_2198_;
v___y_2181_ = v___y_2192_;
v___y_2182_ = v___y_2193_;
v___y_2183_ = v___y_2194_;
v___y_2184_ = v___y_2195_;
v___y_2185_ = v___y_2196_;
v___y_2186_ = v___y_2197_;
v___y_2187_ = v___x_2200_;
goto v___jp_2178_;
}
else
{
v___y_2179_ = v___x_2199_;
v___y_2180_ = v___y_2198_;
v___y_2181_ = v___y_2192_;
v___y_2182_ = v___y_2193_;
v___y_2183_ = v___y_2194_;
v___y_2184_ = v___y_2195_;
v___y_2185_ = v___y_2196_;
v___y_2186_ = v___y_2197_;
v___y_2187_ = v___y_2196_;
goto v___jp_2178_;
}
}
v___jp_2202_:
{
uint64_t v___x_2212_; uint8_t v___x_2213_; 
v___x_2212_ = lean_uint64_shift_right(v___y_2203_, v___y_2204_);
v___x_2213_ = lean_uint64_dec_eq(v___x_2212_, v___y_2210_);
if (v___x_2213_ == 0)
{
uint64_t v___x_2214_; 
v___x_2214_ = lean_uint64_add(v___y_2206_, v___y_2204_);
v___y_2192_ = v___y_2205_;
v___y_2193_ = v___y_2207_;
v___y_2194_ = v___y_2208_;
v___y_2195_ = v___y_2209_;
v___y_2196_ = v___y_2211_;
v___y_2197_ = v___y_2210_;
v___y_2198_ = v___x_2214_;
goto v___jp_2191_;
}
else
{
v___y_2192_ = v___y_2205_;
v___y_2193_ = v___y_2207_;
v___y_2194_ = v___y_2208_;
v___y_2195_ = v___y_2209_;
v___y_2196_ = v___y_2211_;
v___y_2197_ = v___y_2210_;
v___y_2198_ = v___y_2206_;
goto v___jp_2191_;
}
}
v___jp_2215_:
{
uint64_t v___x_2223_; uint64_t v___x_2224_; uint8_t v___x_2225_; 
v___x_2223_ = 16ULL;
v___x_2224_ = lean_uint64_shift_right(v___y_2216_, v___x_2223_);
v___x_2225_ = lean_uint64_dec_eq(v___x_2224_, v___y_2221_);
if (v___x_2225_ == 0)
{
v___y_2203_ = v___y_2216_;
v___y_2204_ = v___x_2223_;
v___y_2205_ = v___y_2217_;
v___y_2206_ = v___y_2222_;
v___y_2207_ = v___y_2218_;
v___y_2208_ = v___y_2219_;
v___y_2209_ = v___y_2220_;
v___y_2210_ = v___y_2221_;
v___y_2211_ = v___x_2224_;
goto v___jp_2202_;
}
else
{
v___y_2203_ = v___y_2216_;
v___y_2204_ = v___x_2223_;
v___y_2205_ = v___y_2217_;
v___y_2206_ = v___y_2222_;
v___y_2207_ = v___y_2218_;
v___y_2208_ = v___y_2219_;
v___y_2209_ = v___y_2220_;
v___y_2210_ = v___y_2221_;
v___y_2211_ = v___y_2216_;
goto v___jp_2202_;
}
}
v___jp_2226_:
{
uint64_t v___x_2234_; uint8_t v___x_2235_; 
v___x_2234_ = lean_uint64_shift_right(v___y_2227_, v___y_2231_);
v___x_2235_ = lean_uint64_dec_eq(v___x_2234_, v___y_2232_);
if (v___x_2235_ == 0)
{
v___y_2216_ = v___y_2233_;
v___y_2217_ = v___y_2227_;
v___y_2218_ = v___y_2228_;
v___y_2219_ = v___y_2229_;
v___y_2220_ = v___y_2230_;
v___y_2221_ = v___y_2232_;
v___y_2222_ = v___y_2231_;
goto v___jp_2215_;
}
else
{
v___y_2216_ = v___y_2233_;
v___y_2217_ = v___y_2227_;
v___y_2218_ = v___y_2228_;
v___y_2219_ = v___y_2229_;
v___y_2220_ = v___y_2230_;
v___y_2221_ = v___y_2232_;
v___y_2222_ = v___y_2232_;
goto v___jp_2215_;
}
}
v___jp_2236_:
{
uint64_t v___x_2241_; uint8_t v___x_2242_; 
v___x_2241_ = 0ULL;
v___x_2242_ = lean_uint64_dec_eq(v___y_2237_, v___x_2241_);
if (v___x_2242_ == 0)
{
uint64_t v___x_2243_; uint64_t v___x_2244_; uint8_t v___x_2245_; 
v___x_2243_ = 32ULL;
v___x_2244_ = lean_uint64_shift_right(v___y_2237_, v___x_2243_);
v___x_2245_ = lean_uint64_dec_eq(v___x_2244_, v___x_2241_);
if (v___x_2245_ == 0)
{
v___y_2227_ = v___y_2237_;
v___y_2228_ = v___y_2238_;
v___y_2229_ = v___y_2239_;
v___y_2230_ = v___y_2240_;
v___y_2231_ = v___x_2243_;
v___y_2232_ = v___x_2241_;
v___y_2233_ = v___x_2244_;
goto v___jp_2226_;
}
else
{
v___y_2227_ = v___y_2237_;
v___y_2228_ = v___y_2238_;
v___y_2229_ = v___y_2239_;
v___y_2230_ = v___y_2240_;
v___y_2231_ = v___x_2243_;
v___y_2232_ = v___x_2241_;
v___y_2233_ = v___y_2237_;
goto v___jp_2226_;
}
}
else
{
if (v___y_2240_ == 0)
{
uint32_t v___x_2246_; 
v___x_2246_ = 0;
return v___x_2246_;
}
else
{
uint32_t v___x_2247_; 
v___x_2247_ = 2147483648;
return v___x_2247_;
}
}
}
v___jp_2248_:
{
uint64_t v___x_2255_; uint64_t v___x_2256_; uint64_t v___x_2257_; uint8_t v___x_2258_; 
v___x_2255_ = lean_uint64_mul(v___y_2250_, v___y_2249_);
v___x_2256_ = lean_uint64_add(v___y_2253_, v___y_2254_);
v___x_2257_ = 281474976710656ULL;
v___x_2258_ = lean_uint64_dec_lt(v___x_2255_, v___x_2257_);
if (v___x_2258_ == 0)
{
v___y_2237_ = v___x_2255_;
v___y_2238_ = v___y_2251_;
v___y_2239_ = v___x_2256_;
v___y_2240_ = v___y_2252_;
goto v___jp_2236_;
}
else
{
uint64_t v___x_2259_; uint8_t v___x_2260_; 
v___x_2259_ = 123ULL;
v___x_2260_ = lean_uint64_dec_le(v___x_2256_, v___x_2259_);
if (v___x_2260_ == 0)
{
v___y_2237_ = v___x_2255_;
v___y_2238_ = v___y_2251_;
v___y_2239_ = v___x_2256_;
v___y_2240_ = v___y_2252_;
goto v___jp_2236_;
}
else
{
uint64_t v___x_2261_; uint8_t v___x_2262_; 
v___x_2261_ = 0ULL;
v___x_2262_ = lean_uint64_dec_eq(v___x_2255_, v___x_2261_);
if (v___x_2262_ == 0)
{
uint64_t v___x_2263_; uint64_t v___x_2264_; uint8_t v___x_2265_; 
v___x_2263_ = 149ULL;
v___x_2264_ = lean_uint64_sub(v___x_2263_, v___x_2256_);
v___x_2265_ = lean_uint64_dec_eq(v___x_2264_, v___x_2261_);
if (v___x_2265_ == 0)
{
uint64_t v___x_2266_; uint8_t v___x_2267_; 
v___x_2266_ = 64ULL;
v___x_2267_ = lean_uint64_dec_lt(v___x_2264_, v___x_2266_);
if (v___x_2267_ == 0)
{
uint8_t v___x_2268_; 
v___x_2268_ = lean_uint64_dec_eq(v___x_2264_, v___x_2266_);
if (v___x_2268_ == 0)
{
v___y_1880_ = v___y_2251_;
v___y_1881_ = v___y_2252_;
v___y_1882_ = v___x_2261_;
v___y_1883_ = v___x_2261_;
goto v___jp_1879_;
}
else
{
uint64_t v___x_2269_; uint8_t v___x_2270_; 
v___x_2269_ = 9223372036854775808ULL;
v___x_2270_ = lean_uint64_dec_lt(v___x_2269_, v___x_2255_);
if (v___x_2270_ == 0)
{
v___y_1880_ = v___y_2251_;
v___y_1881_ = v___y_2252_;
v___y_1882_ = v___x_2261_;
v___y_1883_ = v___x_2261_;
goto v___jp_1879_;
}
else
{
uint64_t v___x_2271_; 
v___x_2271_ = 1ULL;
v___y_1880_ = v___y_2251_;
v___y_1881_ = v___y_2252_;
v___y_1882_ = v___x_2261_;
v___y_1883_ = v___x_2271_;
goto v___jp_1879_;
}
}
}
else
{
uint64_t v_quotient_2272_; uint64_t v___x_2273_; uint64_t v___x_2274_; uint64_t v___x_2275_; uint64_t v_remainder_2276_; uint64_t v___x_2277_; uint64_t v_half_2278_; uint8_t v___x_2279_; 
v_quotient_2272_ = lean_uint64_shift_right(v___x_2255_, v___x_2264_);
v___x_2273_ = 1ULL;
v___x_2274_ = lean_uint64_shift_left(v___x_2273_, v___x_2264_);
v___x_2275_ = lean_uint64_sub(v___x_2274_, v___x_2273_);
v_remainder_2276_ = lean_uint64_land(v___x_2255_, v___x_2275_);
v___x_2277_ = lean_uint64_sub(v___x_2264_, v___x_2273_);
v_half_2278_ = lean_uint64_shift_left(v___x_2273_, v___x_2277_);
v___x_2279_ = lean_uint64_dec_lt(v_remainder_2276_, v_half_2278_);
if (v___x_2279_ == 0)
{
uint8_t v___x_2280_; 
v___x_2280_ = lean_uint64_dec_lt(v_half_2278_, v_remainder_2276_);
if (v___x_2280_ == 0)
{
uint64_t v___x_2281_; uint8_t v___x_2282_; 
v___x_2281_ = lean_uint64_land(v_quotient_2272_, v___x_2273_);
v___x_2282_ = lean_uint64_dec_eq(v___x_2281_, v___x_2261_);
if (v___x_2282_ == 0)
{
uint64_t v___x_2283_; 
v___x_2283_ = lean_uint64_add(v_quotient_2272_, v___x_2273_);
v___y_1880_ = v___y_2251_;
v___y_1881_ = v___y_2252_;
v___y_1882_ = v___x_2261_;
v___y_1883_ = v___x_2283_;
goto v___jp_1879_;
}
else
{
v___y_1880_ = v___y_2251_;
v___y_1881_ = v___y_2252_;
v___y_1882_ = v___x_2261_;
v___y_1883_ = v_quotient_2272_;
goto v___jp_1879_;
}
}
else
{
uint64_t v___x_2284_; 
v___x_2284_ = lean_uint64_add(v_quotient_2272_, v___x_2273_);
v___y_1880_ = v___y_2251_;
v___y_1881_ = v___y_2252_;
v___y_1882_ = v___x_2261_;
v___y_1883_ = v___x_2284_;
goto v___jp_1879_;
}
}
else
{
v___y_1880_ = v___y_2251_;
v___y_1881_ = v___y_2252_;
v___y_1882_ = v___x_2261_;
v___y_1883_ = v_quotient_2272_;
goto v___jp_1879_;
}
}
}
else
{
v___y_1880_ = v___y_2251_;
v___y_1881_ = v___y_2252_;
v___y_1882_ = v___x_2261_;
v___y_1883_ = v___x_2255_;
goto v___jp_1879_;
}
}
else
{
if (v___y_2252_ == 0)
{
uint32_t v___x_2285_; 
v___x_2285_ = 0;
return v___x_2285_;
}
else
{
uint32_t v___x_2286_; 
v___x_2286_ = 2147483648;
return v___x_2286_;
}
}
}
}
}
v___jp_2290_:
{
uint64_t v___x_2296_; uint64_t v___x_2297_; uint8_t v___x_2298_; 
v___x_2296_ = lean_uint32_to_uint64(v_ey_2289_);
v___x_2297_ = 0ULL;
v___x_2298_ = lean_uint64_dec_eq(v___x_2296_, v___x_2297_);
if (v___x_2298_ == 0)
{
uint64_t v___x_2299_; uint64_t v___x_2300_; 
v___x_2299_ = 1ULL;
v___x_2300_ = lean_uint64_sub(v___x_2296_, v___x_2299_);
v___y_2249_ = v___y_2292_;
v___y_2250_ = v___y_2291_;
v___y_2251_ = v___y_2293_;
v___y_2252_ = v___y_2294_;
v___y_2253_ = v___y_2295_;
v___y_2254_ = v___x_2300_;
goto v___jp_2248_;
}
else
{
v___y_2249_ = v___y_2292_;
v___y_2250_ = v___y_2291_;
v___y_2251_ = v___y_2293_;
v___y_2252_ = v___y_2294_;
v___y_2253_ = v___y_2295_;
v___y_2254_ = v___x_2297_;
goto v___jp_2248_;
}
}
v___jp_2301_:
{
uint64_t v___x_2306_; uint64_t v___x_2307_; uint8_t v___x_2308_; 
v___x_2306_ = lean_uint32_to_uint64(v_ex_2287_);
v___x_2307_ = 0ULL;
v___x_2308_ = lean_uint64_dec_eq(v___x_2306_, v___x_2307_);
if (v___x_2308_ == 0)
{
uint64_t v___x_2309_; uint64_t v___x_2310_; 
v___x_2309_ = 1ULL;
v___x_2310_ = lean_uint64_sub(v___x_2306_, v___x_2309_);
v___y_2291_ = v___y_2302_;
v___y_2292_ = v___y_2305_;
v___y_2293_ = v___y_2303_;
v___y_2294_ = v___y_2304_;
v___y_2295_ = v___x_2310_;
goto v___jp_2290_;
}
else
{
v___y_2291_ = v___y_2302_;
v___y_2292_ = v___y_2305_;
v___y_2293_ = v___y_2303_;
v___y_2294_ = v___y_2304_;
v___y_2295_ = v___x_2307_;
goto v___jp_2290_;
}
}
v___jp_2311_:
{
uint32_t v___x_2316_; uint8_t v___x_2317_; 
v___x_2316_ = 0;
v___x_2317_ = lean_uint32_dec_eq(v_ey_2289_, v___x_2316_);
if (v___x_2317_ == 0)
{
uint64_t v___x_2318_; uint64_t v___x_2319_; uint64_t v___x_2320_; 
v___x_2318_ = lean_uint32_to_uint64(v___y_2312_);
v___x_2319_ = 8388608ULL;
v___x_2320_ = lean_uint64_lor(v___x_2318_, v___x_2319_);
v___y_2302_ = v___y_2315_;
v___y_2303_ = v___y_2313_;
v___y_2304_ = v___y_2314_;
v___y_2305_ = v___x_2320_;
goto v___jp_2301_;
}
else
{
uint64_t v___x_2321_; 
v___x_2321_ = lean_uint32_to_uint64(v___y_2312_);
v___y_2302_ = v___y_2315_;
v___y_2303_ = v___y_2313_;
v___y_2304_ = v___y_2314_;
v___y_2305_ = v___x_2321_;
goto v___jp_2301_;
}
}
v___jp_2322_:
{
uint32_t v___x_2324_; uint32_t v_xFraction_2325_; uint32_t v_yFraction_2326_; uint32_t v___x_2327_; uint8_t v___x_2328_; 
v___x_2324_ = 8388607;
v_xFraction_2325_ = lean_uint32_land(v___y_1842_, v___x_2324_);
v_yFraction_2326_ = lean_uint32_land(v___y_1843_, v___x_2324_);
v___x_2327_ = 0;
v___x_2328_ = lean_uint32_dec_eq(v_ex_2287_, v___x_2327_);
if (v___x_2328_ == 0)
{
uint64_t v___x_2329_; uint64_t v___x_2330_; uint64_t v___x_2331_; 
v___x_2329_ = lean_uint32_to_uint64(v_xFraction_2325_);
v___x_2330_ = 8388608ULL;
v___x_2331_ = lean_uint64_lor(v___x_2329_, v___x_2330_);
v___y_2312_ = v_yFraction_2326_;
v___y_2313_ = v___x_2324_;
v___y_2314_ = v___y_2323_;
v___y_2315_ = v___x_2331_;
goto v___jp_2311_;
}
else
{
uint64_t v___x_2332_; 
v___x_2332_ = lean_uint32_to_uint64(v_xFraction_2325_);
v___y_2312_ = v_yFraction_2326_;
v___y_2313_ = v___x_2324_;
v___y_2314_ = v___y_2323_;
v___y_2315_ = v___x_2332_;
goto v___jp_2311_;
}
}
v___jp_2336_:
{
if (v___y_2338_ == 0)
{
v___y_2323_ = v___x_2335_;
goto v___jp_2322_;
}
else
{
v___y_2323_ = v___y_2337_;
goto v___jp_2322_;
}
}
v___jp_2339_:
{
if (v___y_2340_ == 0)
{
if (v___y_2342_ == 0)
{
v___y_2337_ = v___y_2341_;
v___y_2338_ = v___x_2335_;
goto v___jp_2336_;
}
else
{
v___y_2323_ = v___x_2335_;
goto v___jp_2322_;
}
}
else
{
v___y_2337_ = v___y_2341_;
v___y_2338_ = v___y_2342_;
goto v___jp_2336_;
}
}
v___jp_2343_:
{
uint32_t v___x_2346_; uint32_t v___x_2347_; uint32_t v___x_2348_; uint8_t v___x_2349_; 
v___x_2346_ = 2147483648;
v___x_2347_ = lean_uint32_land(v___y_1843_, v___x_2346_);
v___x_2348_ = 0;
v___x_2349_ = lean_uint32_dec_eq(v___x_2347_, v___x_2348_);
if (v___x_2349_ == 0)
{
v___y_2340_ = v___y_2345_;
v___y_2341_ = v___y_2344_;
v___y_2342_ = v___x_2335_;
goto v___jp_2339_;
}
else
{
v___y_2340_ = v___y_2345_;
v___y_2341_ = v___y_2344_;
v___y_2342_ = v___y_2344_;
goto v___jp_2339_;
}
}
v___jp_2350_:
{
if (v___y_2351_ == 0)
{
uint32_t v___x_2352_; uint32_t v___x_2353_; uint32_t v___x_2354_; uint8_t v___x_2355_; 
v___x_2352_ = 2147483648;
v___x_2353_ = lean_uint32_land(v___y_1842_, v___x_2352_);
v___x_2354_ = 0;
v___x_2355_ = lean_uint32_dec_eq(v___x_2353_, v___x_2354_);
if (v___x_2355_ == 0)
{
v___y_2344_ = v___y_2351_;
v___y_2345_ = v___x_2335_;
goto v___jp_2343_;
}
else
{
v___y_2344_ = v___y_2351_;
v___y_2345_ = v___y_2351_;
goto v___jp_2343_;
}
}
else
{
lean_object* v___x_2356_; lean_object* v___x_2357_; lean_object* v___x_2358_; uint32_t v___x_2359_; 
v___x_2356_ = lean_uint32_to_nat(v___y_1842_);
v___x_2357_ = lean_uint32_to_nat(v___y_1843_);
v___x_2358_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_2356_, v___x_2357_);
v___x_2359_ = lean_uint32_of_nat(v___x_2358_);
lean_dec(v___x_2358_);
return v___x_2359_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_runControl___lam__1___boxed(lean_object* v___y_2374_, lean_object* v___y_2375_){
_start:
{
uint32_t v___y_2432__boxed_2376_; uint32_t v___y_2433__boxed_2377_; uint32_t v_res_2378_; lean_object* v_r_2379_; 
v___y_2432__boxed_2376_ = lean_unbox_uint32(v___y_2374_);
lean_dec(v___y_2374_);
v___y_2433__boxed_2377_ = lean_unbox_uint32(v___y_2375_);
lean_dec(v___y_2375_);
v_res_2378_ = lp_competition_runControl___lam__1(v___y_2432__boxed_2376_, v___y_2433__boxed_2377_);
v_r_2379_ = lean_box_uint32(v_res_2378_);
return v_r_2379_;
}
}
LEAN_EXPORT lean_object* lp_competition_runControl(){
_start:
{
lean_object* v___f_2385_; lean_object* v___f_2386_; lean_object* v___x_2387_; lean_object* v___x_2388_; lean_object* v___x_2389_; 
v___f_2385_ = ((lean_object*)(lp_competition_runControl___closed__0));
v___f_2386_ = ((lean_object*)(lp_competition_runControl___closed__1));
v___x_2387_ = ((lean_object*)(lp_competition_runControl___closed__2));
v___x_2388_ = ((lean_object*)(lp_competition_runControl___closed__3));
v___x_2389_ = lp_competition_Bench_Suite_run(v___f_2385_, v___f_2386_, v___x_2387_, v___x_2388_);
return v___x_2389_;
}
}
LEAN_EXPORT lean_object* lp_competition_runControl___boxed(lean_object* v_a_2390_){
_start:
{
lean_object* v_res_2391_; 
v_res_2391_ = lp_competition_runControl();
return v_res_2391_;
}
}
LEAN_EXPORT uint32_t lp_competition_runInlineOld___lam__1(uint32_t v___y_2392_, uint32_t v___y_2393_){
_start:
{
uint32_t v___y_2395_; uint32_t v___y_2399_; uint32_t v___y_2403_; uint32_t v___y_2404_; uint32_t v___y_2405_; uint64_t v___y_2409_; uint32_t v___y_2410_; uint8_t v___y_2411_; uint64_t v___y_2412_; uint32_t v___y_2424_; uint32_t v___y_2425_; uint32_t v___y_2426_; uint32_t v___y_2430_; uint64_t v___y_2431_; uint8_t v___y_2432_; uint64_t v___y_2433_; uint8_t v___y_2445_; uint8_t v___y_2461_; uint8_t v___y_2475_; uint8_t v___y_2492_; float v___y_2499_; float v___y_2500_; float v___y_2514_; uint8_t v___y_2515_; float v___y_2530_; uint32_t v___y_2540_; uint32_t v___y_2544_; uint32_t v___y_2548_; uint32_t v___y_2549_; uint32_t v___y_2550_; uint32_t v___y_2554_; uint64_t v___y_2555_; uint8_t v___y_2556_; uint64_t v___y_2557_; uint32_t v___y_2569_; uint32_t v___y_2570_; uint32_t v___y_2571_; uint64_t v___y_2575_; uint32_t v___y_2576_; uint8_t v___y_2577_; uint64_t v___y_2578_; uint8_t v___y_2590_; uint8_t v___y_2606_; uint8_t v___y_2620_; uint8_t v___y_2637_; float v___y_2644_; float v___y_2645_; float v___y_2659_; uint8_t v___y_2660_; float v___y_2675_; uint32_t v___y_2685_; uint32_t v___y_2689_; uint32_t v___y_2693_; uint32_t v___y_2694_; uint32_t v___y_2695_; uint8_t v___y_2699_; uint32_t v___y_2700_; uint64_t v___y_2701_; uint64_t v___y_2702_; uint32_t v___y_2714_; uint32_t v___y_2715_; uint32_t v___y_2716_; uint8_t v___y_2720_; uint64_t v___y_2721_; uint32_t v___y_2722_; uint64_t v___y_2723_; uint8_t v___y_2735_; uint8_t v___y_2751_; uint8_t v___y_2765_; uint8_t v___y_2782_; float v___y_2789_; float v___y_2790_; float v___y_2804_; uint8_t v___y_2805_; float v___y_2820_; uint32_t v___x_2829_; uint32_t v___x_2830_; uint8_t v___y_2832_; uint8_t v___y_2845_; uint8_t v___y_2858_; uint32_t v___x_2870_; uint32_t v___y_2872_; uint32_t v___y_2873_; uint32_t v___y_2874_; uint32_t v___y_2875_; uint32_t v___y_2882_; uint32_t v___y_2883_; uint8_t v___y_2884_; uint32_t v___y_2885_; uint64_t v___y_2889_; uint64_t v___y_2890_; uint32_t v___y_2891_; uint8_t v___y_2892_; uint64_t v___y_2893_; uint64_t v___y_2903_; uint8_t v___y_2904_; uint64_t v___y_2905_; uint32_t v___y_2906_; uint8_t v___y_2907_; uint64_t v___y_2908_; uint64_t v___y_2915_; uint64_t v___y_2916_; uint32_t v___y_2917_; uint8_t v___y_2918_; uint64_t v___y_2919_; uint64_t v___y_2925_; uint64_t v___y_2926_; uint32_t v___y_2927_; uint64_t v___y_2928_; uint8_t v___y_2929_; uint64_t v___y_2930_; uint64_t v___y_2985_; uint64_t v___y_2986_; uint32_t v___y_2987_; uint64_t v___y_2988_; uint64_t v___y_2989_; uint8_t v___y_2990_; uint64_t v___y_2991_; uint64_t v___y_2997_; uint64_t v___y_2998_; uint64_t v___y_2999_; uint32_t v___y_3000_; uint64_t v___y_3001_; uint64_t v___y_3002_; uint64_t v___y_3003_; uint8_t v___y_3004_; uint64_t v___y_3005_; uint64_t v___y_3010_; uint64_t v___y_3011_; uint32_t v___y_3012_; uint64_t v___y_3013_; uint64_t v___y_3014_; uint8_t v___y_3015_; uint64_t v___y_3016_; uint64_t v___y_3021_; uint64_t v___y_3022_; uint64_t v___y_3023_; uint64_t v___y_3024_; uint32_t v___y_3025_; uint64_t v___y_3026_; uint64_t v___y_3027_; uint8_t v___y_3028_; uint64_t v___y_3029_; uint64_t v___y_3034_; uint64_t v___y_3035_; uint32_t v___y_3036_; uint64_t v___y_3037_; uint64_t v___y_3038_; uint8_t v___y_3039_; uint64_t v___y_3040_; uint64_t v___y_3045_; uint64_t v___y_3046_; uint64_t v___y_3047_; uint64_t v___y_3048_; uint32_t v___y_3049_; uint64_t v___y_3050_; uint64_t v___y_3051_; uint8_t v___y_3052_; uint64_t v___y_3053_; uint64_t v___y_3058_; uint64_t v___y_3059_; uint32_t v___y_3060_; uint64_t v___y_3061_; uint8_t v___y_3062_; uint64_t v___y_3063_; uint64_t v___y_3064_; uint64_t v___y_3069_; uint64_t v___y_3070_; uint64_t v___y_3071_; uint64_t v___y_3072_; uint32_t v___y_3073_; uint64_t v___y_3074_; uint64_t v___y_3075_; uint8_t v___y_3076_; uint64_t v___y_3077_; uint64_t v___y_3082_; uint64_t v___y_3083_; uint64_t v___y_3084_; uint32_t v___y_3085_; uint64_t v___y_3086_; uint8_t v___y_3087_; uint64_t v___y_3088_; uint64_t v___y_3093_; uint64_t v___y_3094_; uint64_t v___y_3095_; uint32_t v___y_3096_; uint64_t v___y_3097_; uint8_t v___y_3098_; uint64_t v___y_3099_; uint64_t v___y_3103_; uint32_t v___y_3104_; uint64_t v___y_3105_; uint8_t v___y_3106_; uint64_t v___y_3115_; uint64_t v___y_3116_; uint64_t v___y_3117_; uint32_t v___y_3118_; uint8_t v___y_3119_; uint64_t v___y_3120_; uint32_t v___y_3154_; uint32_t v___y_3155_; uint32_t v___y_3156_; uint32_t v___y_3157_; uint32_t v___y_3164_; uint32_t v___y_3165_; uint8_t v___y_3166_; uint32_t v___y_3167_; uint32_t v___y_3171_; uint64_t v___y_3172_; uint64_t v___y_3173_; uint8_t v___y_3174_; uint64_t v___y_3175_; uint8_t v___y_3185_; uint32_t v___y_3186_; uint64_t v___y_3187_; uint64_t v___y_3188_; uint8_t v___y_3189_; uint64_t v___y_3190_; uint32_t v___y_3197_; uint64_t v___y_3198_; uint8_t v___y_3199_; uint64_t v___y_3200_; uint64_t v___y_3201_; uint64_t v___y_3207_; uint32_t v___y_3208_; uint64_t v___y_3209_; uint64_t v___y_3210_; uint8_t v___y_3211_; uint64_t v___y_3212_; uint64_t v___y_3267_; uint64_t v___y_3268_; uint32_t v___y_3269_; uint64_t v___y_3270_; uint64_t v___y_3271_; uint8_t v___y_3272_; uint64_t v___y_3273_; uint64_t v___y_3279_; uint64_t v___y_3280_; uint64_t v___y_3281_; uint64_t v___y_3282_; uint32_t v___y_3283_; uint64_t v___y_3284_; uint64_t v___y_3285_; uint8_t v___y_3286_; uint64_t v___y_3287_; uint64_t v___y_3292_; uint64_t v___y_3293_; uint32_t v___y_3294_; uint64_t v___y_3295_; uint64_t v___y_3296_; uint8_t v___y_3297_; uint64_t v___y_3298_; uint64_t v___y_3303_; uint64_t v___y_3304_; uint64_t v___y_3305_; uint64_t v___y_3306_; uint32_t v___y_3307_; uint64_t v___y_3308_; uint64_t v___y_3309_; uint8_t v___y_3310_; uint64_t v___y_3311_; uint64_t v___y_3316_; uint64_t v___y_3317_; uint32_t v___y_3318_; uint64_t v___y_3319_; uint64_t v___y_3320_; uint8_t v___y_3321_; uint64_t v___y_3322_; uint64_t v___y_3327_; uint32_t v___y_3328_; uint64_t v___y_3329_; uint64_t v___y_3330_; uint64_t v___y_3331_; uint64_t v___y_3332_; uint8_t v___y_3333_; uint64_t v___y_3334_; uint64_t v___y_3335_; uint64_t v___y_3340_; uint32_t v___y_3341_; uint64_t v___y_3342_; uint64_t v___y_3343_; uint8_t v___y_3344_; uint64_t v___y_3345_; uint64_t v___y_3346_; uint64_t v___y_3351_; uint64_t v___y_3352_; uint32_t v___y_3353_; uint64_t v___y_3354_; uint64_t v___y_3355_; uint64_t v___y_3356_; uint64_t v___y_3357_; uint8_t v___y_3358_; uint64_t v___y_3359_; uint64_t v___y_3364_; uint32_t v___y_3365_; uint64_t v___y_3366_; uint64_t v___y_3367_; uint64_t v___y_3368_; uint8_t v___y_3369_; uint64_t v___y_3370_; uint64_t v___y_3375_; uint32_t v___y_3376_; uint64_t v___y_3377_; uint64_t v___y_3378_; uint64_t v___y_3379_; uint8_t v___y_3380_; uint64_t v___y_3381_; uint64_t v___y_3385_; uint32_t v___y_3386_; uint64_t v___y_3387_; uint8_t v___y_3388_; uint64_t v___y_3397_; uint64_t v___y_3398_; uint64_t v___y_3399_; uint32_t v___y_3400_; uint8_t v___y_3401_; uint64_t v___y_3402_; uint32_t v___y_3436_; uint32_t v___y_3437_; uint32_t v___y_3438_; uint32_t v___y_3439_; uint8_t v___y_3446_; uint32_t v___y_3447_; uint32_t v___y_3448_; uint32_t v___y_3449_; uint8_t v___y_3453_; uint32_t v___y_3454_; uint64_t v___y_3455_; uint64_t v___y_3456_; uint64_t v___y_3457_; uint8_t v___y_3467_; uint8_t v___y_3468_; uint32_t v___y_3469_; uint64_t v___y_3470_; uint64_t v___y_3471_; uint64_t v___y_3472_; uint8_t v___y_3479_; uint64_t v___y_3480_; uint32_t v___y_3481_; uint64_t v___y_3482_; uint64_t v___y_3483_; uint8_t v___y_3489_; uint64_t v___y_3490_; uint32_t v___y_3491_; uint64_t v___y_3492_; uint64_t v___y_3493_; uint64_t v___y_3494_; uint8_t v___y_3549_; uint64_t v___y_3550_; uint32_t v___y_3551_; uint64_t v___y_3552_; uint64_t v___y_3553_; uint64_t v___y_3554_; uint64_t v___y_3555_; uint8_t v___y_3561_; uint64_t v___y_3562_; uint32_t v___y_3563_; uint64_t v___y_3564_; uint64_t v___y_3565_; uint64_t v___y_3566_; uint64_t v___y_3567_; uint64_t v___y_3568_; uint64_t v___y_3569_; uint8_t v___y_3574_; uint64_t v___y_3575_; uint32_t v___y_3576_; uint64_t v___y_3577_; uint64_t v___y_3578_; uint64_t v___y_3579_; uint64_t v___y_3580_; uint8_t v___y_3585_; uint64_t v___y_3586_; uint32_t v___y_3587_; uint64_t v___y_3588_; uint64_t v___y_3589_; uint64_t v___y_3590_; uint64_t v___y_3591_; uint64_t v___y_3592_; uint64_t v___y_3593_; uint8_t v___y_3598_; uint64_t v___y_3599_; uint32_t v___y_3600_; uint64_t v___y_3601_; uint64_t v___y_3602_; uint64_t v___y_3603_; uint64_t v___y_3604_; uint64_t v___y_3609_; uint8_t v___y_3610_; uint64_t v___y_3611_; uint64_t v___y_3612_; uint32_t v___y_3613_; uint64_t v___y_3614_; uint64_t v___y_3615_; uint64_t v___y_3616_; uint64_t v___y_3617_; uint8_t v___y_3622_; uint64_t v___y_3623_; uint64_t v___y_3624_; uint32_t v___y_3625_; uint64_t v___y_3626_; uint64_t v___y_3627_; uint64_t v___y_3628_; uint64_t v___y_3633_; uint64_t v___y_3634_; uint8_t v___y_3635_; uint64_t v___y_3636_; uint32_t v___y_3637_; uint64_t v___y_3638_; uint64_t v___y_3639_; uint64_t v___y_3640_; uint64_t v___y_3641_; uint8_t v___y_3646_; uint64_t v___y_3647_; uint32_t v___y_3648_; uint64_t v___y_3649_; uint64_t v___y_3650_; uint64_t v___y_3651_; uint64_t v___y_3652_; uint8_t v___y_3657_; uint64_t v___y_3658_; uint32_t v___y_3659_; uint64_t v___y_3660_; uint64_t v___y_3661_; uint64_t v___y_3662_; uint64_t v___y_3663_; uint8_t v___y_3667_; uint64_t v___y_3668_; uint64_t v___y_3669_; uint32_t v___y_3670_; uint8_t v___y_3679_; uint32_t v___y_3680_; uint64_t v___y_3681_; uint64_t v___y_3682_; uint64_t v___y_3683_; uint64_t v___y_3684_; uint32_t v_eu_3717_; uint32_t v___x_3718_; uint32_t v___x_3719_; uint32_t v___x_3720_; uint8_t v___x_3721_; 
v___x_2829_ = 23;
v___x_2830_ = lean_uint32_shift_right(v___y_2392_, v___x_2829_);
v___x_2870_ = 255;
v_eu_3717_ = lean_uint32_land(v___x_2830_, v___x_2870_);
v___x_3718_ = 1;
v___x_3719_ = lean_uint32_sub(v_eu_3717_, v___x_3718_);
v___x_3720_ = 253;
v___x_3721_ = lean_uint32_dec_le(v___x_3719_, v___x_3720_);
if (v___x_3721_ == 0)
{
uint32_t v___x_3722_; uint32_t v_ey_3723_; uint8_t v___y_3725_; uint32_t v___y_3726_; uint64_t v___y_3727_; uint64_t v___y_3728_; uint64_t v___y_3729_; uint8_t v___y_3736_; uint32_t v___y_3737_; uint64_t v___y_3738_; uint64_t v___y_3739_; uint8_t v___y_3746_; uint32_t v___y_3747_; uint32_t v___y_3748_; uint64_t v___y_3749_; uint8_t v___y_3757_; uint32_t v___x_3767_; uint32_t v___x_3768_; uint8_t v___x_3769_; uint8_t v___y_3771_; uint8_t v___y_3772_; uint8_t v___y_3773_; uint8_t v___y_3775_; uint8_t v___y_3776_; uint8_t v___y_3782_; 
v___x_3722_ = lean_uint32_shift_right(v___y_2393_, v___x_2829_);
v_ey_3723_ = lean_uint32_land(v___x_3722_, v___x_2870_);
v___x_3767_ = lean_uint32_add(v_eu_3717_, v_ey_3723_);
v___x_3768_ = 128;
v___x_3769_ = lean_uint32_dec_lt(v___x_3767_, v___x_3768_);
if (v___x_3769_ == 0)
{
uint32_t v___x_3791_; uint32_t v_a_3792_; uint32_t v___x_3793_; uint32_t v___x_3794_; uint8_t v___x_3795_; 
v___x_3791_ = 2147483647;
v_a_3792_ = lean_uint32_land(v___y_2392_, v___x_3791_);
v___x_3793_ = 201326591;
v___x_3794_ = lean_uint32_sub(v_a_3792_, v___x_3718_);
v___x_3795_ = lean_uint32_dec_le(v___x_3793_, v___x_3794_);
if (v___x_3795_ == 0)
{
v___y_2858_ = v___x_3795_;
goto v___jp_2857_;
}
else
{
uint32_t v___x_3796_; uint8_t v___x_3797_; 
v___x_3796_ = 2139095040;
v___x_3797_ = lean_uint32_dec_lt(v_a_3792_, v___x_3796_);
v___y_2858_ = v___x_3797_;
goto v___jp_2857_;
}
}
else
{
uint32_t v___x_3798_; uint32_t v___x_3799_; uint8_t v___x_3800_; 
v___x_3798_ = 4278190080;
v___x_3799_ = lean_uint32_shift_left(v___y_2392_, v___x_3718_);
v___x_3800_ = lean_uint32_dec_le(v___x_3798_, v___x_3799_);
if (v___x_3800_ == 0)
{
uint32_t v___x_3801_; uint8_t v___x_3802_; 
v___x_3801_ = lean_uint32_shift_left(v___y_2393_, v___x_3718_);
v___x_3802_ = lean_uint32_dec_le(v___x_3798_, v___x_3801_);
v___y_3782_ = v___x_3802_;
goto v___jp_3781_;
}
else
{
v___y_3782_ = v___x_3800_;
goto v___jp_3781_;
}
}
v___jp_3724_:
{
uint64_t v___x_3730_; uint64_t v___x_3731_; uint8_t v___x_3732_; 
v___x_3730_ = lean_uint32_to_uint64(v_ey_3723_);
v___x_3731_ = 0ULL;
v___x_3732_ = lean_uint64_dec_eq(v___x_3730_, v___x_3731_);
if (v___x_3732_ == 0)
{
uint64_t v___x_3733_; uint64_t v___x_3734_; 
v___x_3733_ = 1ULL;
v___x_3734_ = lean_uint64_sub(v___x_3730_, v___x_3733_);
v___y_3679_ = v___y_3725_;
v___y_3680_ = v___y_3726_;
v___y_3681_ = v___y_3729_;
v___y_3682_ = v___y_3727_;
v___y_3683_ = v___y_3728_;
v___y_3684_ = v___x_3734_;
goto v___jp_3678_;
}
else
{
v___y_3679_ = v___y_3725_;
v___y_3680_ = v___y_3726_;
v___y_3681_ = v___y_3729_;
v___y_3682_ = v___y_3727_;
v___y_3683_ = v___y_3728_;
v___y_3684_ = v___x_3731_;
goto v___jp_3678_;
}
}
v___jp_3735_:
{
uint64_t v___x_3740_; uint64_t v___x_3741_; uint8_t v___x_3742_; 
v___x_3740_ = lean_uint32_to_uint64(v_eu_3717_);
v___x_3741_ = 0ULL;
v___x_3742_ = lean_uint64_dec_eq(v___x_3740_, v___x_3741_);
if (v___x_3742_ == 0)
{
uint64_t v___x_3743_; uint64_t v___x_3744_; 
v___x_3743_ = 1ULL;
v___x_3744_ = lean_uint64_sub(v___x_3740_, v___x_3743_);
v___y_3725_ = v___y_3736_;
v___y_3726_ = v___y_3737_;
v___y_3727_ = v___y_3738_;
v___y_3728_ = v___y_3739_;
v___y_3729_ = v___x_3744_;
goto v___jp_3724_;
}
else
{
v___y_3725_ = v___y_3736_;
v___y_3726_ = v___y_3737_;
v___y_3727_ = v___y_3738_;
v___y_3728_ = v___y_3739_;
v___y_3729_ = v___x_3741_;
goto v___jp_3724_;
}
}
v___jp_3745_:
{
uint32_t v___x_3750_; uint8_t v___x_3751_; 
v___x_3750_ = 0;
v___x_3751_ = lean_uint32_dec_eq(v_ey_3723_, v___x_3750_);
if (v___x_3751_ == 0)
{
uint64_t v___x_3752_; uint64_t v___x_3753_; uint64_t v___x_3754_; 
v___x_3752_ = lean_uint32_to_uint64(v___y_3748_);
v___x_3753_ = 8388608ULL;
v___x_3754_ = lean_uint64_lor(v___x_3752_, v___x_3753_);
v___y_3736_ = v___y_3746_;
v___y_3737_ = v___y_3747_;
v___y_3738_ = v___y_3749_;
v___y_3739_ = v___x_3754_;
goto v___jp_3735_;
}
else
{
uint64_t v___x_3755_; 
v___x_3755_ = lean_uint32_to_uint64(v___y_3748_);
v___y_3736_ = v___y_3746_;
v___y_3737_ = v___y_3747_;
v___y_3738_ = v___y_3749_;
v___y_3739_ = v___x_3755_;
goto v___jp_3735_;
}
}
v___jp_3756_:
{
uint32_t v___x_3758_; uint32_t v_xFraction_3759_; uint32_t v_yFraction_3760_; uint32_t v___x_3761_; uint8_t v___x_3762_; 
v___x_3758_ = 8388607;
v_xFraction_3759_ = lean_uint32_land(v___y_2392_, v___x_3758_);
v_yFraction_3760_ = lean_uint32_land(v___y_2393_, v___x_3758_);
v___x_3761_ = 0;
v___x_3762_ = lean_uint32_dec_eq(v_eu_3717_, v___x_3761_);
if (v___x_3762_ == 0)
{
uint64_t v___x_3763_; uint64_t v___x_3764_; uint64_t v___x_3765_; 
v___x_3763_ = lean_uint32_to_uint64(v_xFraction_3759_);
v___x_3764_ = 8388608ULL;
v___x_3765_ = lean_uint64_lor(v___x_3763_, v___x_3764_);
v___y_3746_ = v___y_3757_;
v___y_3747_ = v___x_3758_;
v___y_3748_ = v_yFraction_3760_;
v___y_3749_ = v___x_3765_;
goto v___jp_3745_;
}
else
{
uint64_t v___x_3766_; 
v___x_3766_ = lean_uint32_to_uint64(v_xFraction_3759_);
v___y_3746_ = v___y_3757_;
v___y_3747_ = v___x_3758_;
v___y_3748_ = v_yFraction_3760_;
v___y_3749_ = v___x_3766_;
goto v___jp_3745_;
}
}
v___jp_3770_:
{
if (v___y_3771_ == 0)
{
if (v___y_3773_ == 0)
{
v___y_3757_ = v___y_3772_;
goto v___jp_3756_;
}
else
{
v___y_3757_ = v___x_3769_;
goto v___jp_3756_;
}
}
else
{
if (v___y_3773_ == 0)
{
v___y_3757_ = v___x_3769_;
goto v___jp_3756_;
}
else
{
v___y_3757_ = v___y_3772_;
goto v___jp_3756_;
}
}
}
v___jp_3774_:
{
uint32_t v___x_3777_; uint32_t v___x_3778_; uint32_t v___x_3779_; uint8_t v___x_3780_; 
v___x_3777_ = 2147483648;
v___x_3778_ = lean_uint32_land(v___y_2393_, v___x_3777_);
v___x_3779_ = 0;
v___x_3780_ = lean_uint32_dec_eq(v___x_3778_, v___x_3779_);
if (v___x_3780_ == 0)
{
v___y_3771_ = v___y_3776_;
v___y_3772_ = v___y_3775_;
v___y_3773_ = v___x_3769_;
goto v___jp_3770_;
}
else
{
v___y_3771_ = v___y_3776_;
v___y_3772_ = v___y_3775_;
v___y_3773_ = v___y_3775_;
goto v___jp_3770_;
}
}
v___jp_3781_:
{
if (v___y_3782_ == 0)
{
uint32_t v___x_3783_; uint32_t v___x_3784_; uint32_t v___x_3785_; uint8_t v___x_3786_; 
v___x_3783_ = 2147483648;
v___x_3784_ = lean_uint32_land(v___y_2392_, v___x_3783_);
v___x_3785_ = 0;
v___x_3786_ = lean_uint32_dec_eq(v___x_3784_, v___x_3785_);
if (v___x_3786_ == 0)
{
v___y_3775_ = v___y_3782_;
v___y_3776_ = v___x_3769_;
goto v___jp_3774_;
}
else
{
v___y_3775_ = v___y_3782_;
v___y_3776_ = v___y_3782_;
goto v___jp_3774_;
}
}
else
{
lean_object* v___x_3787_; lean_object* v___x_3788_; lean_object* v___x_3789_; uint32_t v___x_3790_; 
v___x_3787_ = lean_uint32_to_nat(v___y_2392_);
v___x_3788_ = lean_uint32_to_nat(v___y_2393_);
v___x_3789_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_3787_, v___x_3788_);
v___x_3790_ = lean_uint32_of_nat(v___x_3789_);
lean_dec(v___x_3789_);
return v___x_3790_;
}
}
}
else
{
uint32_t v___x_3803_; uint32_t v_ev_3804_; uint64_t v___y_3806_; uint64_t v___y_3807_; uint32_t v___y_3808_; uint8_t v___y_3809_; uint64_t v___y_3810_; uint64_t v___y_3817_; uint32_t v___y_3818_; uint8_t v___y_3819_; uint64_t v___y_3820_; uint32_t v___y_3827_; uint32_t v___y_3828_; uint8_t v___y_3829_; uint64_t v___y_3830_; uint8_t v___y_3838_; uint64_t v___y_3849_; uint64_t v___y_3850_; uint32_t v___y_3851_; uint8_t v___y_3852_; uint64_t v___y_3853_; uint64_t v___y_3860_; uint32_t v___y_3861_; uint8_t v___y_3862_; uint64_t v___y_3863_; uint32_t v___y_3870_; uint32_t v___y_3871_; uint8_t v___y_3872_; uint64_t v___y_3873_; uint8_t v___y_3881_; uint8_t v___y_3892_; uint8_t v___y_3893_; uint8_t v___y_3895_; uint8_t v___y_3896_; uint8_t v___y_3897_; uint8_t v___y_3899_; uint8_t v___y_3900_; uint8_t v___y_3906_; uint32_t v___x_3915_; uint8_t v___x_3916_; uint8_t v___y_3918_; uint8_t v___y_3919_; uint8_t v___y_3921_; uint8_t v___y_3922_; uint8_t v___y_3923_; uint8_t v___y_3925_; uint8_t v___y_3926_; uint8_t v___y_3932_; 
v___x_3803_ = lean_uint32_shift_right(v___y_2393_, v___x_2829_);
v_ev_3804_ = lean_uint32_land(v___x_3803_, v___x_2870_);
v___x_3915_ = lean_uint32_sub(v_ev_3804_, v___x_3718_);
v___x_3916_ = lean_uint32_dec_le(v___x_3915_, v___x_3720_);
if (v___x_3916_ == 0)
{
uint32_t v___x_3941_; uint32_t v___x_3942_; uint8_t v___x_3943_; 
v___x_3941_ = lean_uint32_add(v_eu_3717_, v_ev_3804_);
v___x_3942_ = 128;
v___x_3943_ = lean_uint32_dec_lt(v___x_3941_, v___x_3942_);
if (v___x_3943_ == 0)
{
uint32_t v___x_3944_; uint32_t v_a_3945_; uint32_t v___x_3946_; uint32_t v___x_3947_; uint8_t v___x_3948_; 
v___x_3944_ = 2147483647;
v_a_3945_ = lean_uint32_land(v___y_2392_, v___x_3944_);
v___x_3946_ = 201326591;
v___x_3947_ = lean_uint32_sub(v_a_3945_, v___x_3718_);
v___x_3948_ = lean_uint32_dec_le(v___x_3946_, v___x_3947_);
if (v___x_3948_ == 0)
{
v___y_2845_ = v___x_3948_;
goto v___jp_2844_;
}
else
{
uint32_t v___x_3949_; uint8_t v___x_3950_; 
v___x_3949_ = 2139095040;
v___x_3950_ = lean_uint32_dec_lt(v_a_3945_, v___x_3949_);
v___y_2845_ = v___x_3950_;
goto v___jp_2844_;
}
}
else
{
uint32_t v___x_3951_; uint32_t v___x_3952_; uint8_t v___x_3953_; 
v___x_3951_ = 4278190080;
v___x_3952_ = lean_uint32_shift_left(v___y_2392_, v___x_3718_);
v___x_3953_ = lean_uint32_dec_le(v___x_3951_, v___x_3952_);
if (v___x_3953_ == 0)
{
uint32_t v___x_3954_; uint8_t v___x_3955_; 
v___x_3954_ = lean_uint32_shift_left(v___y_2393_, v___x_3718_);
v___x_3955_ = lean_uint32_dec_le(v___x_3951_, v___x_3954_);
v___y_3906_ = v___x_3955_;
goto v___jp_3905_;
}
else
{
v___y_3906_ = v___x_3953_;
goto v___jp_3905_;
}
}
}
else
{
uint32_t v_s_3956_; uint32_t v___x_3957_; uint32_t v___x_3958_; uint32_t v___x_3959_; uint8_t v___x_3960_; 
v_s_3956_ = lean_uint32_add(v_eu_3717_, v_ev_3804_);
v___x_3957_ = 128;
v___x_3958_ = lean_uint32_sub(v_s_3956_, v___x_3957_);
v___x_3959_ = 252;
v___x_3960_ = lean_uint32_dec_le(v___x_3958_, v___x_3959_);
if (v___x_3960_ == 0)
{
uint8_t v___x_3961_; 
v___x_3961_ = lean_uint32_dec_lt(v_s_3956_, v___x_3957_);
if (v___x_3961_ == 0)
{
uint32_t v___x_3962_; uint32_t v_a_3963_; uint32_t v___x_3964_; uint32_t v___x_3965_; uint8_t v___x_3966_; 
v___x_3962_ = 2147483647;
v_a_3963_ = lean_uint32_land(v___y_2392_, v___x_3962_);
v___x_3964_ = 201326591;
v___x_3965_ = lean_uint32_sub(v_a_3963_, v___x_3718_);
v___x_3966_ = lean_uint32_dec_le(v___x_3964_, v___x_3965_);
if (v___x_3966_ == 0)
{
v___y_2832_ = v___x_3966_;
goto v___jp_2831_;
}
else
{
uint32_t v___x_3967_; uint8_t v___x_3968_; 
v___x_3967_ = 2139095040;
v___x_3968_ = lean_uint32_dec_lt(v_a_3963_, v___x_3967_);
v___y_2832_ = v___x_3968_;
goto v___jp_2831_;
}
}
else
{
uint32_t v___x_3969_; uint32_t v___x_3970_; uint8_t v___x_3971_; 
v___x_3969_ = 4278190080;
v___x_3970_ = lean_uint32_shift_left(v___y_2392_, v___x_3718_);
v___x_3971_ = lean_uint32_dec_le(v___x_3969_, v___x_3970_);
if (v___x_3971_ == 0)
{
uint32_t v___x_3972_; uint8_t v___x_3973_; 
v___x_3972_ = lean_uint32_shift_left(v___y_2393_, v___x_3718_);
v___x_3973_ = lean_uint32_dec_le(v___x_3969_, v___x_3972_);
v___y_3932_ = v___x_3973_;
goto v___jp_3931_;
}
else
{
v___y_3932_ = v___x_3971_;
goto v___jp_3931_;
}
}
}
else
{
uint32_t v___x_3974_; uint32_t v___x_3975_; uint32_t v___x_3976_; uint64_t v___y_3978_; uint32_t v_a_3996_; uint32_t v___x_3997_; uint32_t v_b_3998_; uint64_t v___x_3999_; uint64_t v___x_4000_; uint64_t v_p_4001_; uint64_t v___x_4002_; uint8_t v___x_4003_; 
v___x_3974_ = 8388607;
v___x_3975_ = lean_uint32_land(v___y_2392_, v___x_3974_);
v___x_3976_ = 8388608;
v_a_3996_ = lean_uint32_lor(v___x_3975_, v___x_3976_);
v___x_3997_ = lean_uint32_land(v___y_2393_, v___x_3974_);
v_b_3998_ = lean_uint32_lor(v___x_3997_, v___x_3976_);
v___x_3999_ = lean_uint32_to_uint64(v_a_3996_);
v___x_4000_ = lean_uint32_to_uint64(v_b_3998_);
v_p_4001_ = lean_uint64_mul(v___x_3999_, v___x_4000_);
v___x_4002_ = 140737488355328ULL;
v___x_4003_ = lean_uint64_dec_lt(v_p_4001_, v___x_4002_);
if (v___x_4003_ == 0)
{
uint64_t v___x_4004_; uint64_t v___x_4005_; uint64_t v___x_4006_; uint64_t v___x_4007_; uint64_t v___x_4008_; uint64_t v___x_4009_; uint64_t v___x_4010_; 
v___x_4004_ = 8388607ULL;
v___x_4005_ = lean_uint64_add(v_p_4001_, v___x_4004_);
v___x_4006_ = 24ULL;
v___x_4007_ = lean_uint64_shift_right(v_p_4001_, v___x_4006_);
v___x_4008_ = 1ULL;
v___x_4009_ = lean_uint64_land(v___x_4007_, v___x_4008_);
v___x_4010_ = lean_uint64_add(v___x_4005_, v___x_4009_);
v___y_3978_ = v___x_4010_;
goto v___jp_3977_;
}
else
{
uint64_t v___x_4011_; uint64_t v___x_4012_; uint64_t v___x_4013_; uint64_t v___x_4014_; uint64_t v___x_4015_; uint64_t v___x_4016_; uint64_t v___x_4017_; 
v___x_4011_ = 4194303ULL;
v___x_4012_ = lean_uint64_add(v_p_4001_, v___x_4011_);
v___x_4013_ = 23ULL;
v___x_4014_ = lean_uint64_shift_right(v_p_4001_, v___x_4013_);
v___x_4015_ = 1ULL;
v___x_4016_ = lean_uint64_land(v___x_4014_, v___x_4015_);
v___x_4017_ = lean_uint64_add(v___x_4012_, v___x_4016_);
v___y_3978_ = v___x_4017_;
goto v___jp_3977_;
}
v___jp_3977_:
{
uint64_t v___x_3979_; uint64_t v_high_3980_; uint64_t v___x_3981_; uint64_t v___x_3982_; uint64_t v___x_3983_; uint32_t v_q_3984_; uint32_t v___x_3985_; uint32_t v___x_3986_; uint32_t v___x_3987_; uint32_t v_e_3988_; uint32_t v___x_3989_; uint32_t v___x_3990_; uint32_t v___x_3991_; uint32_t v___x_3992_; uint32_t v___x_3993_; uint32_t v___x_3994_; uint32_t v___x_3995_; 
v___x_3979_ = 47ULL;
v_high_3980_ = lean_uint64_shift_right(v___y_3978_, v___x_3979_);
v___x_3981_ = 23ULL;
v___x_3982_ = lean_uint64_add(v___x_3981_, v_high_3980_);
v___x_3983_ = lean_uint64_shift_right(v___y_3978_, v___x_3982_);
v_q_3984_ = lean_uint64_to_uint32(v___x_3983_);
v___x_3985_ = 127;
v___x_3986_ = lean_uint32_sub(v_s_3956_, v___x_3985_);
v___x_3987_ = lean_uint64_to_uint32(v_high_3980_);
v_e_3988_ = lean_uint32_add(v___x_3986_, v___x_3987_);
v___x_3989_ = lean_uint32_xor(v___y_2392_, v___y_2393_);
v___x_3990_ = 2147483648;
v___x_3991_ = lean_uint32_land(v___x_3989_, v___x_3990_);
v___x_3992_ = lean_uint32_shift_left(v_e_3988_, v___x_2829_);
v___x_3993_ = lean_uint32_lor(v___x_3991_, v___x_3992_);
v___x_3994_ = lean_uint32_sub(v_q_3984_, v___x_3976_);
v___x_3995_ = lean_uint32_lor(v___x_3993_, v___x_3994_);
return v___x_3995_;
}
}
}
v___jp_3805_:
{
uint64_t v___x_3811_; uint64_t v___x_3812_; uint8_t v___x_3813_; 
v___x_3811_ = lean_uint32_to_uint64(v_ev_3804_);
v___x_3812_ = 0ULL;
v___x_3813_ = lean_uint64_dec_eq(v___x_3811_, v___x_3812_);
if (v___x_3813_ == 0)
{
uint64_t v___x_3814_; uint64_t v___x_3815_; 
v___x_3814_ = 1ULL;
v___x_3815_ = lean_uint64_sub(v___x_3811_, v___x_3814_);
v___y_3115_ = v___y_3806_;
v___y_3116_ = v___y_3807_;
v___y_3117_ = v___y_3810_;
v___y_3118_ = v___y_3808_;
v___y_3119_ = v___y_3809_;
v___y_3120_ = v___x_3815_;
goto v___jp_3114_;
}
else
{
v___y_3115_ = v___y_3806_;
v___y_3116_ = v___y_3807_;
v___y_3117_ = v___y_3810_;
v___y_3118_ = v___y_3808_;
v___y_3119_ = v___y_3809_;
v___y_3120_ = v___x_3812_;
goto v___jp_3114_;
}
}
v___jp_3816_:
{
uint64_t v___x_3821_; uint64_t v___x_3822_; uint8_t v___x_3823_; 
v___x_3821_ = lean_uint32_to_uint64(v_eu_3717_);
v___x_3822_ = 0ULL;
v___x_3823_ = lean_uint64_dec_eq(v___x_3821_, v___x_3822_);
if (v___x_3823_ == 0)
{
uint64_t v___x_3824_; uint64_t v___x_3825_; 
v___x_3824_ = 1ULL;
v___x_3825_ = lean_uint64_sub(v___x_3821_, v___x_3824_);
v___y_3806_ = v___y_3820_;
v___y_3807_ = v___y_3817_;
v___y_3808_ = v___y_3818_;
v___y_3809_ = v___y_3819_;
v___y_3810_ = v___x_3825_;
goto v___jp_3805_;
}
else
{
v___y_3806_ = v___y_3820_;
v___y_3807_ = v___y_3817_;
v___y_3808_ = v___y_3818_;
v___y_3809_ = v___y_3819_;
v___y_3810_ = v___x_3822_;
goto v___jp_3805_;
}
}
v___jp_3826_:
{
uint32_t v___x_3831_; uint8_t v___x_3832_; 
v___x_3831_ = 0;
v___x_3832_ = lean_uint32_dec_eq(v_ev_3804_, v___x_3831_);
if (v___x_3832_ == 0)
{
uint64_t v___x_3833_; uint64_t v___x_3834_; uint64_t v___x_3835_; 
v___x_3833_ = lean_uint32_to_uint64(v___y_3827_);
v___x_3834_ = 8388608ULL;
v___x_3835_ = lean_uint64_lor(v___x_3833_, v___x_3834_);
v___y_3817_ = v___y_3830_;
v___y_3818_ = v___y_3828_;
v___y_3819_ = v___y_3829_;
v___y_3820_ = v___x_3835_;
goto v___jp_3816_;
}
else
{
uint64_t v___x_3836_; 
v___x_3836_ = lean_uint32_to_uint64(v___y_3827_);
v___y_3817_ = v___y_3830_;
v___y_3818_ = v___y_3828_;
v___y_3819_ = v___y_3829_;
v___y_3820_ = v___x_3836_;
goto v___jp_3816_;
}
}
v___jp_3837_:
{
uint32_t v___x_3839_; uint32_t v_xFraction_3840_; uint32_t v_yFraction_3841_; uint32_t v___x_3842_; uint8_t v___x_3843_; 
v___x_3839_ = 8388607;
v_xFraction_3840_ = lean_uint32_land(v___y_2392_, v___x_3839_);
v_yFraction_3841_ = lean_uint32_land(v___y_2393_, v___x_3839_);
v___x_3842_ = 0;
v___x_3843_ = lean_uint32_dec_eq(v_eu_3717_, v___x_3842_);
if (v___x_3843_ == 0)
{
uint64_t v___x_3844_; uint64_t v___x_3845_; uint64_t v___x_3846_; 
v___x_3844_ = lean_uint32_to_uint64(v_xFraction_3840_);
v___x_3845_ = 8388608ULL;
v___x_3846_ = lean_uint64_lor(v___x_3844_, v___x_3845_);
v___y_3827_ = v_yFraction_3841_;
v___y_3828_ = v___x_3839_;
v___y_3829_ = v___y_3838_;
v___y_3830_ = v___x_3846_;
goto v___jp_3826_;
}
else
{
uint64_t v___x_3847_; 
v___x_3847_ = lean_uint32_to_uint64(v_xFraction_3840_);
v___y_3827_ = v_yFraction_3841_;
v___y_3828_ = v___x_3839_;
v___y_3829_ = v___y_3838_;
v___y_3830_ = v___x_3847_;
goto v___jp_3826_;
}
}
v___jp_3848_:
{
uint64_t v___x_3854_; uint64_t v___x_3855_; uint8_t v___x_3856_; 
v___x_3854_ = lean_uint32_to_uint64(v_ev_3804_);
v___x_3855_ = 0ULL;
v___x_3856_ = lean_uint64_dec_eq(v___x_3854_, v___x_3855_);
if (v___x_3856_ == 0)
{
uint64_t v___x_3857_; uint64_t v___x_3858_; 
v___x_3857_ = 1ULL;
v___x_3858_ = lean_uint64_sub(v___x_3854_, v___x_3857_);
v___y_3397_ = v___y_3850_;
v___y_3398_ = v___y_3849_;
v___y_3399_ = v___y_3853_;
v___y_3400_ = v___y_3851_;
v___y_3401_ = v___y_3852_;
v___y_3402_ = v___x_3858_;
goto v___jp_3396_;
}
else
{
v___y_3397_ = v___y_3850_;
v___y_3398_ = v___y_3849_;
v___y_3399_ = v___y_3853_;
v___y_3400_ = v___y_3851_;
v___y_3401_ = v___y_3852_;
v___y_3402_ = v___x_3855_;
goto v___jp_3396_;
}
}
v___jp_3859_:
{
uint64_t v___x_3864_; uint64_t v___x_3865_; uint8_t v___x_3866_; 
v___x_3864_ = lean_uint32_to_uint64(v_eu_3717_);
v___x_3865_ = 0ULL;
v___x_3866_ = lean_uint64_dec_eq(v___x_3864_, v___x_3865_);
if (v___x_3866_ == 0)
{
uint64_t v___x_3867_; uint64_t v___x_3868_; 
v___x_3867_ = 1ULL;
v___x_3868_ = lean_uint64_sub(v___x_3864_, v___x_3867_);
v___y_3849_ = v___y_3860_;
v___y_3850_ = v___y_3863_;
v___y_3851_ = v___y_3861_;
v___y_3852_ = v___y_3862_;
v___y_3853_ = v___x_3868_;
goto v___jp_3848_;
}
else
{
v___y_3849_ = v___y_3860_;
v___y_3850_ = v___y_3863_;
v___y_3851_ = v___y_3861_;
v___y_3852_ = v___y_3862_;
v___y_3853_ = v___x_3865_;
goto v___jp_3848_;
}
}
v___jp_3869_:
{
uint32_t v___x_3874_; uint8_t v___x_3875_; 
v___x_3874_ = 0;
v___x_3875_ = lean_uint32_dec_eq(v_ev_3804_, v___x_3874_);
if (v___x_3875_ == 0)
{
uint64_t v___x_3876_; uint64_t v___x_3877_; uint64_t v___x_3878_; 
v___x_3876_ = lean_uint32_to_uint64(v___y_3871_);
v___x_3877_ = 8388608ULL;
v___x_3878_ = lean_uint64_lor(v___x_3876_, v___x_3877_);
v___y_3860_ = v___y_3873_;
v___y_3861_ = v___y_3870_;
v___y_3862_ = v___y_3872_;
v___y_3863_ = v___x_3878_;
goto v___jp_3859_;
}
else
{
uint64_t v___x_3879_; 
v___x_3879_ = lean_uint32_to_uint64(v___y_3871_);
v___y_3860_ = v___y_3873_;
v___y_3861_ = v___y_3870_;
v___y_3862_ = v___y_3872_;
v___y_3863_ = v___x_3879_;
goto v___jp_3859_;
}
}
v___jp_3880_:
{
uint32_t v___x_3882_; uint32_t v_xFraction_3883_; uint32_t v_yFraction_3884_; uint32_t v___x_3885_; uint8_t v___x_3886_; 
v___x_3882_ = 8388607;
v_xFraction_3883_ = lean_uint32_land(v___y_2392_, v___x_3882_);
v_yFraction_3884_ = lean_uint32_land(v___y_2393_, v___x_3882_);
v___x_3885_ = 0;
v___x_3886_ = lean_uint32_dec_eq(v_eu_3717_, v___x_3885_);
if (v___x_3886_ == 0)
{
uint64_t v___x_3887_; uint64_t v___x_3888_; uint64_t v___x_3889_; 
v___x_3887_ = lean_uint32_to_uint64(v_xFraction_3883_);
v___x_3888_ = 8388608ULL;
v___x_3889_ = lean_uint64_lor(v___x_3887_, v___x_3888_);
v___y_3870_ = v___x_3882_;
v___y_3871_ = v_yFraction_3884_;
v___y_3872_ = v___y_3881_;
v___y_3873_ = v___x_3889_;
goto v___jp_3869_;
}
else
{
uint64_t v___x_3890_; 
v___x_3890_ = lean_uint32_to_uint64(v_xFraction_3883_);
v___y_3870_ = v___x_3882_;
v___y_3871_ = v_yFraction_3884_;
v___y_3872_ = v___y_3881_;
v___y_3873_ = v___x_3890_;
goto v___jp_3869_;
}
}
v___jp_3891_:
{
if (v___y_3893_ == 0)
{
v___y_3881_ = v___x_3721_;
goto v___jp_3880_;
}
else
{
v___y_3881_ = v___y_3892_;
goto v___jp_3880_;
}
}
v___jp_3894_:
{
if (v___y_3895_ == 0)
{
if (v___y_3897_ == 0)
{
v___y_3892_ = v___y_3896_;
v___y_3893_ = v___x_3721_;
goto v___jp_3891_;
}
else
{
v___y_3881_ = v___x_3721_;
goto v___jp_3880_;
}
}
else
{
v___y_3892_ = v___y_3896_;
v___y_3893_ = v___y_3897_;
goto v___jp_3891_;
}
}
v___jp_3898_:
{
uint32_t v___x_3901_; uint32_t v___x_3902_; uint32_t v___x_3903_; uint8_t v___x_3904_; 
v___x_3901_ = 2147483648;
v___x_3902_ = lean_uint32_land(v___y_2393_, v___x_3901_);
v___x_3903_ = 0;
v___x_3904_ = lean_uint32_dec_eq(v___x_3902_, v___x_3903_);
if (v___x_3904_ == 0)
{
v___y_3895_ = v___y_3900_;
v___y_3896_ = v___y_3899_;
v___y_3897_ = v___x_3721_;
goto v___jp_3894_;
}
else
{
v___y_3895_ = v___y_3900_;
v___y_3896_ = v___y_3899_;
v___y_3897_ = v___y_3899_;
goto v___jp_3894_;
}
}
v___jp_3905_:
{
if (v___y_3906_ == 0)
{
uint32_t v___x_3907_; uint32_t v___x_3908_; uint32_t v___x_3909_; uint8_t v___x_3910_; 
v___x_3907_ = 2147483648;
v___x_3908_ = lean_uint32_land(v___y_2392_, v___x_3907_);
v___x_3909_ = 0;
v___x_3910_ = lean_uint32_dec_eq(v___x_3908_, v___x_3909_);
if (v___x_3910_ == 0)
{
v___y_3899_ = v___y_3906_;
v___y_3900_ = v___x_3721_;
goto v___jp_3898_;
}
else
{
v___y_3899_ = v___y_3906_;
v___y_3900_ = v___y_3906_;
goto v___jp_3898_;
}
}
else
{
lean_object* v___x_3911_; lean_object* v___x_3912_; lean_object* v___x_3913_; uint32_t v___x_3914_; 
v___x_3911_ = lean_uint32_to_nat(v___y_2392_);
v___x_3912_ = lean_uint32_to_nat(v___y_2393_);
v___x_3913_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_3911_, v___x_3912_);
v___x_3914_ = lean_uint32_of_nat(v___x_3913_);
lean_dec(v___x_3913_);
return v___x_3914_;
}
}
v___jp_3917_:
{
if (v___y_3919_ == 0)
{
v___y_3838_ = v___x_3916_;
goto v___jp_3837_;
}
else
{
v___y_3838_ = v___y_3918_;
goto v___jp_3837_;
}
}
v___jp_3920_:
{
if (v___y_3922_ == 0)
{
if (v___y_3923_ == 0)
{
v___y_3918_ = v___y_3921_;
v___y_3919_ = v___x_3916_;
goto v___jp_3917_;
}
else
{
v___y_3838_ = v___x_3916_;
goto v___jp_3837_;
}
}
else
{
v___y_3918_ = v___y_3921_;
v___y_3919_ = v___y_3923_;
goto v___jp_3917_;
}
}
v___jp_3924_:
{
uint32_t v___x_3927_; uint32_t v___x_3928_; uint32_t v___x_3929_; uint8_t v___x_3930_; 
v___x_3927_ = 2147483648;
v___x_3928_ = lean_uint32_land(v___y_2393_, v___x_3927_);
v___x_3929_ = 0;
v___x_3930_ = lean_uint32_dec_eq(v___x_3928_, v___x_3929_);
if (v___x_3930_ == 0)
{
v___y_3921_ = v___y_3925_;
v___y_3922_ = v___y_3926_;
v___y_3923_ = v___x_3916_;
goto v___jp_3920_;
}
else
{
v___y_3921_ = v___y_3925_;
v___y_3922_ = v___y_3926_;
v___y_3923_ = v___y_3925_;
goto v___jp_3920_;
}
}
v___jp_3931_:
{
if (v___y_3932_ == 0)
{
uint32_t v___x_3933_; uint32_t v___x_3934_; uint32_t v___x_3935_; uint8_t v___x_3936_; 
v___x_3933_ = 2147483648;
v___x_3934_ = lean_uint32_land(v___y_2392_, v___x_3933_);
v___x_3935_ = 0;
v___x_3936_ = lean_uint32_dec_eq(v___x_3934_, v___x_3935_);
if (v___x_3936_ == 0)
{
v___y_3925_ = v___y_3932_;
v___y_3926_ = v___x_3916_;
goto v___jp_3924_;
}
else
{
v___y_3925_ = v___y_3932_;
v___y_3926_ = v___y_3932_;
goto v___jp_3924_;
}
}
else
{
lean_object* v___x_3937_; lean_object* v___x_3938_; lean_object* v___x_3939_; uint32_t v___x_3940_; 
v___x_3937_ = lean_uint32_to_nat(v___y_2392_);
v___x_3938_ = lean_uint32_to_nat(v___y_2393_);
v___x_3939_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_3937_, v___x_3938_);
v___x_3940_ = lean_uint32_of_nat(v___x_3939_);
lean_dec(v___x_3939_);
return v___x_3940_;
}
}
}
v___jp_2394_:
{
uint32_t v___x_2396_; uint32_t v___x_2397_; 
v___x_2396_ = 8388608;
v___x_2397_ = lean_uint32_lor(v___y_2395_, v___x_2396_);
return v___x_2397_;
}
v___jp_2398_:
{
uint32_t v___x_2400_; uint32_t v___x_2401_; 
v___x_2400_ = 8388608;
v___x_2401_ = lean_uint32_lor(v___y_2399_, v___x_2400_);
return v___x_2401_;
}
v___jp_2402_:
{
uint32_t v___x_2406_; uint32_t v___x_2407_; 
v___x_2406_ = lean_uint32_land(v___y_2403_, v___y_2404_);
v___x_2407_ = lean_uint32_lor(v___y_2405_, v___x_2406_);
return v___x_2407_;
}
v___jp_2408_:
{
uint8_t v___x_2413_; 
v___x_2413_ = lean_uint64_dec_eq(v___y_2412_, v___y_2409_);
if (v___x_2413_ == 0)
{
uint64_t v___x_2414_; uint8_t v___x_2415_; 
v___x_2414_ = 8388608ULL;
v___x_2415_ = lean_uint64_dec_eq(v___y_2412_, v___x_2414_);
if (v___x_2415_ == 0)
{
uint32_t v___x_2416_; 
v___x_2416_ = lean_uint64_to_uint32(v___y_2412_);
if (v___y_2411_ == 0)
{
uint32_t v___x_2417_; 
v___x_2417_ = 0;
v___y_2403_ = v___x_2416_;
v___y_2404_ = v___y_2410_;
v___y_2405_ = v___x_2417_;
goto v___jp_2402_;
}
else
{
uint32_t v___x_2418_; 
v___x_2418_ = 2147483648;
v___y_2403_ = v___x_2416_;
v___y_2404_ = v___y_2410_;
v___y_2405_ = v___x_2418_;
goto v___jp_2402_;
}
}
else
{
if (v___y_2411_ == 0)
{
uint32_t v___x_2419_; 
v___x_2419_ = 0;
v___y_2399_ = v___x_2419_;
goto v___jp_2398_;
}
else
{
uint32_t v___x_2420_; 
v___x_2420_ = 2147483648;
v___y_2399_ = v___x_2420_;
goto v___jp_2398_;
}
}
}
else
{
if (v___y_2411_ == 0)
{
uint32_t v___x_2421_; 
v___x_2421_ = 0;
return v___x_2421_;
}
else
{
uint32_t v___x_2422_; 
v___x_2422_ = 2147483648;
return v___x_2422_;
}
}
}
v___jp_2423_:
{
uint32_t v___x_2427_; uint32_t v___x_2428_; 
v___x_2427_ = lean_uint32_land(v___y_2424_, v___y_2425_);
v___x_2428_ = lean_uint32_lor(v___y_2426_, v___x_2427_);
return v___x_2428_;
}
v___jp_2429_:
{
uint8_t v___x_2434_; 
v___x_2434_ = lean_uint64_dec_eq(v___y_2433_, v___y_2431_);
if (v___x_2434_ == 0)
{
uint64_t v___x_2435_; uint8_t v___x_2436_; 
v___x_2435_ = 8388608ULL;
v___x_2436_ = lean_uint64_dec_eq(v___y_2433_, v___x_2435_);
if (v___x_2436_ == 0)
{
uint32_t v___x_2437_; 
v___x_2437_ = lean_uint64_to_uint32(v___y_2433_);
if (v___y_2432_ == 0)
{
uint32_t v___x_2438_; 
v___x_2438_ = 0;
v___y_2424_ = v___x_2437_;
v___y_2425_ = v___y_2430_;
v___y_2426_ = v___x_2438_;
goto v___jp_2423_;
}
else
{
uint32_t v___x_2439_; 
v___x_2439_ = 2147483648;
v___y_2424_ = v___x_2437_;
v___y_2425_ = v___y_2430_;
v___y_2426_ = v___x_2439_;
goto v___jp_2423_;
}
}
else
{
if (v___y_2432_ == 0)
{
uint32_t v___x_2440_; 
v___x_2440_ = 0;
v___y_2395_ = v___x_2440_;
goto v___jp_2394_;
}
else
{
uint32_t v___x_2441_; 
v___x_2441_ = 2147483648;
v___y_2395_ = v___x_2441_;
goto v___jp_2394_;
}
}
}
else
{
if (v___y_2432_ == 0)
{
uint32_t v___x_2442_; 
v___x_2442_ = 0;
return v___x_2442_;
}
else
{
uint32_t v___x_2443_; 
v___x_2443_ = 2147483648;
return v___x_2443_;
}
}
}
v___jp_2444_:
{
if (v___y_2445_ == 0)
{
uint32_t v___x_2446_; 
v___x_2446_ = lp_competition_Submission_FastMul_mul(v___y_2392_, v___y_2393_);
return v___x_2446_;
}
else
{
uint32_t v___x_2447_; uint32_t v___x_2448_; 
v___x_2447_ = 4194304;
v___x_2448_ = lean_uint32_lor(v___y_2393_, v___x_2447_);
return v___x_2448_;
}
}
v___jp_2449_:
{
uint32_t v___x_2450_; uint32_t v___x_2451_; uint32_t v___x_2452_; uint32_t v___x_2453_; uint8_t v___x_2454_; 
v___x_2450_ = 23;
v___x_2451_ = lean_uint32_shift_right(v___y_2393_, v___x_2450_);
v___x_2452_ = 255;
v___x_2453_ = lean_uint32_land(v___x_2451_, v___x_2452_);
v___x_2454_ = lean_uint32_dec_eq(v___x_2453_, v___x_2452_);
if (v___x_2454_ == 0)
{
v___y_2445_ = v___x_2454_;
goto v___jp_2444_;
}
else
{
uint32_t v___x_2455_; uint32_t v___x_2456_; uint32_t v___x_2457_; uint8_t v___x_2458_; 
v___x_2455_ = 8388607;
v___x_2456_ = lean_uint32_land(v___y_2393_, v___x_2455_);
v___x_2457_ = 0;
v___x_2458_ = lean_uint32_dec_eq(v___x_2456_, v___x_2457_);
if (v___x_2458_ == 0)
{
v___y_2445_ = v___x_2454_;
goto v___jp_2444_;
}
else
{
uint32_t v___x_2459_; 
v___x_2459_ = lp_competition_Submission_FastMul_mul(v___y_2392_, v___y_2393_);
return v___x_2459_;
}
}
}
v___jp_2460_:
{
if (v___y_2461_ == 0)
{
goto v___jp_2449_;
}
else
{
uint32_t v___x_2462_; uint32_t v___x_2463_; 
v___x_2462_ = 4194304;
v___x_2463_ = lean_uint32_lor(v___y_2392_, v___x_2462_);
return v___x_2463_;
}
}
v___jp_2464_:
{
uint32_t v___x_2465_; uint32_t v___x_2466_; uint32_t v___x_2467_; uint32_t v___x_2468_; uint8_t v___x_2469_; 
v___x_2465_ = 23;
v___x_2466_ = lean_uint32_shift_right(v___y_2392_, v___x_2465_);
v___x_2467_ = 255;
v___x_2468_ = lean_uint32_land(v___x_2466_, v___x_2467_);
v___x_2469_ = lean_uint32_dec_eq(v___x_2468_, v___x_2467_);
if (v___x_2469_ == 0)
{
v___y_2461_ = v___x_2469_;
goto v___jp_2460_;
}
else
{
uint32_t v___x_2470_; uint32_t v___x_2471_; uint32_t v___x_2472_; uint8_t v___x_2473_; 
v___x_2470_ = 8388607;
v___x_2471_ = lean_uint32_land(v___y_2392_, v___x_2470_);
v___x_2472_ = 0;
v___x_2473_ = lean_uint32_dec_eq(v___x_2471_, v___x_2472_);
if (v___x_2473_ == 0)
{
v___y_2461_ = v___x_2469_;
goto v___jp_2460_;
}
else
{
goto v___jp_2449_;
}
}
}
v___jp_2474_:
{
if (v___y_2475_ == 0)
{
goto v___jp_2464_;
}
else
{
uint32_t v___x_2476_; uint32_t v___x_2477_; uint32_t v___x_2478_; uint8_t v___x_2479_; 
v___x_2476_ = 4194304;
v___x_2477_ = lean_uint32_land(v___y_2393_, v___x_2476_);
v___x_2478_ = 0;
v___x_2479_ = lean_uint32_dec_eq(v___x_2477_, v___x_2478_);
if (v___x_2479_ == 0)
{
goto v___jp_2464_;
}
else
{
uint32_t v___x_2480_; 
v___x_2480_ = lean_uint32_lor(v___y_2393_, v___x_2476_);
return v___x_2480_;
}
}
}
v___jp_2481_:
{
uint32_t v___x_2482_; uint32_t v___x_2483_; uint32_t v___x_2484_; uint32_t v___x_2485_; uint8_t v___x_2486_; 
v___x_2482_ = 23;
v___x_2483_ = lean_uint32_shift_right(v___y_2393_, v___x_2482_);
v___x_2484_ = 255;
v___x_2485_ = lean_uint32_land(v___x_2483_, v___x_2484_);
v___x_2486_ = lean_uint32_dec_eq(v___x_2485_, v___x_2484_);
if (v___x_2486_ == 0)
{
v___y_2475_ = v___x_2486_;
goto v___jp_2474_;
}
else
{
uint32_t v___x_2487_; uint32_t v___x_2488_; uint32_t v___x_2489_; uint8_t v___x_2490_; 
v___x_2487_ = 8388607;
v___x_2488_ = lean_uint32_land(v___y_2393_, v___x_2487_);
v___x_2489_ = 0;
v___x_2490_ = lean_uint32_dec_eq(v___x_2488_, v___x_2489_);
if (v___x_2490_ == 0)
{
v___y_2475_ = v___x_2486_;
goto v___jp_2474_;
}
else
{
goto v___jp_2464_;
}
}
}
v___jp_2491_:
{
if (v___y_2492_ == 0)
{
goto v___jp_2481_;
}
else
{
uint32_t v___x_2493_; uint32_t v___x_2494_; uint32_t v___x_2495_; uint8_t v___x_2496_; 
v___x_2493_ = 4194304;
v___x_2494_ = lean_uint32_land(v___y_2392_, v___x_2493_);
v___x_2495_ = 0;
v___x_2496_ = lean_uint32_dec_eq(v___x_2494_, v___x_2495_);
if (v___x_2496_ == 0)
{
goto v___jp_2481_;
}
else
{
uint32_t v___x_2497_; 
v___x_2497_ = lean_uint32_lor(v___y_2392_, v___x_2493_);
return v___x_2497_;
}
}
}
v___jp_2498_:
{
float v_result_2501_; uint8_t v___x_2502_; 
v_result_2501_ = lean_float32_mul(v___y_2499_, v___y_2500_);
v___x_2502_ = lean_float32_beq(v_result_2501_, v_result_2501_);
if (v___x_2502_ == 0)
{
uint32_t v___x_2503_; uint32_t v___x_2504_; uint32_t v___x_2505_; uint32_t v___x_2506_; uint8_t v___x_2507_; 
v___x_2503_ = 23;
v___x_2504_ = lean_uint32_shift_right(v___y_2392_, v___x_2503_);
v___x_2505_ = 255;
v___x_2506_ = lean_uint32_land(v___x_2504_, v___x_2505_);
v___x_2507_ = lean_uint32_dec_eq(v___x_2506_, v___x_2505_);
if (v___x_2507_ == 0)
{
v___y_2492_ = v___x_2507_;
goto v___jp_2491_;
}
else
{
uint32_t v___x_2508_; uint32_t v___x_2509_; uint32_t v___x_2510_; uint8_t v___x_2511_; 
v___x_2508_ = 8388607;
v___x_2509_ = lean_uint32_land(v___y_2392_, v___x_2508_);
v___x_2510_ = 0;
v___x_2511_ = lean_uint32_dec_eq(v___x_2509_, v___x_2510_);
if (v___x_2511_ == 0)
{
v___y_2492_ = v___x_2507_;
goto v___jp_2491_;
}
else
{
goto v___jp_2481_;
}
}
}
else
{
uint32_t v___x_2512_; 
v___x_2512_ = lean_float32_to_bits(v_result_2501_);
return v___x_2512_;
}
}
v___jp_2513_:
{
if (v___y_2515_ == 0)
{
float v___x_2516_; 
v___x_2516_ = lean_float32_of_bits(v___y_2393_);
v___y_2499_ = v___y_2514_;
v___y_2500_ = v___x_2516_;
goto v___jp_2498_;
}
else
{
uint32_t v___x_2517_; uint32_t v___x_2518_; uint32_t v___x_2519_; uint32_t v___x_2520_; float v___x_2521_; lean_object* v___x_2522_; uint32_t v___x_2523_; uint32_t v___x_2524_; lean_object* v___x_2525_; lean_object* v___x_2526_; float v___x_2527_; float v___x_2528_; 
v___x_2517_ = 8388607;
v___x_2518_ = lean_uint32_land(v___y_2393_, v___x_2517_);
v___x_2519_ = 8388608;
v___x_2520_ = lean_uint32_lor(v___x_2518_, v___x_2519_);
v___x_2521_ = lean_uint32_to_float32(v___x_2520_);
v___x_2522_ = lp_competition_R2W01b_scaleTable;
v___x_2523_ = 23;
v___x_2524_ = lean_uint32_shift_right(v___y_2393_, v___x_2523_);
v___x_2525_ = lean_uint32_to_nat(v___x_2524_);
v___x_2526_ = lean_array_fget_borrowed(v___x_2522_, v___x_2525_);
lean_dec(v___x_2525_);
v___x_2527_ = lean_unbox_float32(v___x_2526_);
v___x_2528_ = lean_float32_mul(v___x_2521_, v___x_2527_);
v___y_2499_ = v___y_2514_;
v___y_2500_ = v___x_2528_;
goto v___jp_2498_;
}
}
v___jp_2529_:
{
uint32_t v___x_2531_; uint32_t v_a_2532_; uint32_t v___x_2533_; uint32_t v___x_2534_; uint32_t v___x_2535_; uint8_t v___x_2536_; 
v___x_2531_ = 2147483647;
v_a_2532_ = lean_uint32_land(v___y_2393_, v___x_2531_);
v___x_2533_ = 201326591;
v___x_2534_ = 1;
v___x_2535_ = lean_uint32_sub(v_a_2532_, v___x_2534_);
v___x_2536_ = lean_uint32_dec_le(v___x_2533_, v___x_2535_);
if (v___x_2536_ == 0)
{
v___y_2514_ = v___y_2530_;
v___y_2515_ = v___x_2536_;
goto v___jp_2513_;
}
else
{
uint32_t v___x_2537_; uint8_t v___x_2538_; 
v___x_2537_ = 2139095040;
v___x_2538_ = lean_uint32_dec_lt(v_a_2532_, v___x_2537_);
v___y_2514_ = v___y_2530_;
v___y_2515_ = v___x_2538_;
goto v___jp_2513_;
}
}
v___jp_2539_:
{
uint32_t v___x_2541_; uint32_t v___x_2542_; 
v___x_2541_ = 8388608;
v___x_2542_ = lean_uint32_lor(v___y_2540_, v___x_2541_);
return v___x_2542_;
}
v___jp_2543_:
{
uint32_t v___x_2545_; uint32_t v___x_2546_; 
v___x_2545_ = 8388608;
v___x_2546_ = lean_uint32_lor(v___y_2544_, v___x_2545_);
return v___x_2546_;
}
v___jp_2547_:
{
uint32_t v___x_2551_; uint32_t v___x_2552_; 
v___x_2551_ = lean_uint32_land(v___y_2548_, v___y_2549_);
v___x_2552_ = lean_uint32_lor(v___y_2550_, v___x_2551_);
return v___x_2552_;
}
v___jp_2553_:
{
uint8_t v___x_2558_; 
v___x_2558_ = lean_uint64_dec_eq(v___y_2557_, v___y_2555_);
if (v___x_2558_ == 0)
{
uint64_t v___x_2559_; uint8_t v___x_2560_; 
v___x_2559_ = 8388608ULL;
v___x_2560_ = lean_uint64_dec_eq(v___y_2557_, v___x_2559_);
if (v___x_2560_ == 0)
{
uint32_t v___x_2561_; 
v___x_2561_ = lean_uint64_to_uint32(v___y_2557_);
if (v___y_2556_ == 0)
{
uint32_t v___x_2562_; 
v___x_2562_ = 0;
v___y_2548_ = v___x_2561_;
v___y_2549_ = v___y_2554_;
v___y_2550_ = v___x_2562_;
goto v___jp_2547_;
}
else
{
uint32_t v___x_2563_; 
v___x_2563_ = 2147483648;
v___y_2548_ = v___x_2561_;
v___y_2549_ = v___y_2554_;
v___y_2550_ = v___x_2563_;
goto v___jp_2547_;
}
}
else
{
if (v___y_2556_ == 0)
{
uint32_t v___x_2564_; 
v___x_2564_ = 0;
v___y_2540_ = v___x_2564_;
goto v___jp_2539_;
}
else
{
uint32_t v___x_2565_; 
v___x_2565_ = 2147483648;
v___y_2540_ = v___x_2565_;
goto v___jp_2539_;
}
}
}
else
{
if (v___y_2556_ == 0)
{
uint32_t v___x_2566_; 
v___x_2566_ = 0;
return v___x_2566_;
}
else
{
uint32_t v___x_2567_; 
v___x_2567_ = 2147483648;
return v___x_2567_;
}
}
}
v___jp_2568_:
{
uint32_t v___x_2572_; uint32_t v___x_2573_; 
v___x_2572_ = lean_uint32_land(v___y_2570_, v___y_2569_);
v___x_2573_ = lean_uint32_lor(v___y_2571_, v___x_2572_);
return v___x_2573_;
}
v___jp_2574_:
{
uint8_t v___x_2579_; 
v___x_2579_ = lean_uint64_dec_eq(v___y_2578_, v___y_2575_);
if (v___x_2579_ == 0)
{
uint64_t v___x_2580_; uint8_t v___x_2581_; 
v___x_2580_ = 8388608ULL;
v___x_2581_ = lean_uint64_dec_eq(v___y_2578_, v___x_2580_);
if (v___x_2581_ == 0)
{
uint32_t v___x_2582_; 
v___x_2582_ = lean_uint64_to_uint32(v___y_2578_);
if (v___y_2577_ == 0)
{
uint32_t v___x_2583_; 
v___x_2583_ = 0;
v___y_2569_ = v___y_2576_;
v___y_2570_ = v___x_2582_;
v___y_2571_ = v___x_2583_;
goto v___jp_2568_;
}
else
{
uint32_t v___x_2584_; 
v___x_2584_ = 2147483648;
v___y_2569_ = v___y_2576_;
v___y_2570_ = v___x_2582_;
v___y_2571_ = v___x_2584_;
goto v___jp_2568_;
}
}
else
{
if (v___y_2577_ == 0)
{
uint32_t v___x_2585_; 
v___x_2585_ = 0;
v___y_2544_ = v___x_2585_;
goto v___jp_2543_;
}
else
{
uint32_t v___x_2586_; 
v___x_2586_ = 2147483648;
v___y_2544_ = v___x_2586_;
goto v___jp_2543_;
}
}
}
else
{
if (v___y_2577_ == 0)
{
uint32_t v___x_2587_; 
v___x_2587_ = 0;
return v___x_2587_;
}
else
{
uint32_t v___x_2588_; 
v___x_2588_ = 2147483648;
return v___x_2588_;
}
}
}
v___jp_2589_:
{
if (v___y_2590_ == 0)
{
uint32_t v___x_2591_; 
v___x_2591_ = lp_competition_Submission_FastMul_mul(v___y_2392_, v___y_2393_);
return v___x_2591_;
}
else
{
uint32_t v___x_2592_; uint32_t v___x_2593_; 
v___x_2592_ = 4194304;
v___x_2593_ = lean_uint32_lor(v___y_2393_, v___x_2592_);
return v___x_2593_;
}
}
v___jp_2594_:
{
uint32_t v___x_2595_; uint32_t v___x_2596_; uint32_t v___x_2597_; uint32_t v___x_2598_; uint8_t v___x_2599_; 
v___x_2595_ = 23;
v___x_2596_ = lean_uint32_shift_right(v___y_2393_, v___x_2595_);
v___x_2597_ = 255;
v___x_2598_ = lean_uint32_land(v___x_2596_, v___x_2597_);
v___x_2599_ = lean_uint32_dec_eq(v___x_2598_, v___x_2597_);
if (v___x_2599_ == 0)
{
v___y_2590_ = v___x_2599_;
goto v___jp_2589_;
}
else
{
uint32_t v___x_2600_; uint32_t v___x_2601_; uint32_t v___x_2602_; uint8_t v___x_2603_; 
v___x_2600_ = 8388607;
v___x_2601_ = lean_uint32_land(v___y_2393_, v___x_2600_);
v___x_2602_ = 0;
v___x_2603_ = lean_uint32_dec_eq(v___x_2601_, v___x_2602_);
if (v___x_2603_ == 0)
{
v___y_2590_ = v___x_2599_;
goto v___jp_2589_;
}
else
{
uint32_t v___x_2604_; 
v___x_2604_ = lp_competition_Submission_FastMul_mul(v___y_2392_, v___y_2393_);
return v___x_2604_;
}
}
}
v___jp_2605_:
{
if (v___y_2606_ == 0)
{
goto v___jp_2594_;
}
else
{
uint32_t v___x_2607_; uint32_t v___x_2608_; 
v___x_2607_ = 4194304;
v___x_2608_ = lean_uint32_lor(v___y_2392_, v___x_2607_);
return v___x_2608_;
}
}
v___jp_2609_:
{
uint32_t v___x_2610_; uint32_t v___x_2611_; uint32_t v___x_2612_; uint32_t v___x_2613_; uint8_t v___x_2614_; 
v___x_2610_ = 23;
v___x_2611_ = lean_uint32_shift_right(v___y_2392_, v___x_2610_);
v___x_2612_ = 255;
v___x_2613_ = lean_uint32_land(v___x_2611_, v___x_2612_);
v___x_2614_ = lean_uint32_dec_eq(v___x_2613_, v___x_2612_);
if (v___x_2614_ == 0)
{
v___y_2606_ = v___x_2614_;
goto v___jp_2605_;
}
else
{
uint32_t v___x_2615_; uint32_t v___x_2616_; uint32_t v___x_2617_; uint8_t v___x_2618_; 
v___x_2615_ = 8388607;
v___x_2616_ = lean_uint32_land(v___y_2392_, v___x_2615_);
v___x_2617_ = 0;
v___x_2618_ = lean_uint32_dec_eq(v___x_2616_, v___x_2617_);
if (v___x_2618_ == 0)
{
v___y_2606_ = v___x_2614_;
goto v___jp_2605_;
}
else
{
goto v___jp_2594_;
}
}
}
v___jp_2619_:
{
if (v___y_2620_ == 0)
{
goto v___jp_2609_;
}
else
{
uint32_t v___x_2621_; uint32_t v___x_2622_; uint32_t v___x_2623_; uint8_t v___x_2624_; 
v___x_2621_ = 4194304;
v___x_2622_ = lean_uint32_land(v___y_2393_, v___x_2621_);
v___x_2623_ = 0;
v___x_2624_ = lean_uint32_dec_eq(v___x_2622_, v___x_2623_);
if (v___x_2624_ == 0)
{
goto v___jp_2609_;
}
else
{
uint32_t v___x_2625_; 
v___x_2625_ = lean_uint32_lor(v___y_2393_, v___x_2621_);
return v___x_2625_;
}
}
}
v___jp_2626_:
{
uint32_t v___x_2627_; uint32_t v___x_2628_; uint32_t v___x_2629_; uint32_t v___x_2630_; uint8_t v___x_2631_; 
v___x_2627_ = 23;
v___x_2628_ = lean_uint32_shift_right(v___y_2393_, v___x_2627_);
v___x_2629_ = 255;
v___x_2630_ = lean_uint32_land(v___x_2628_, v___x_2629_);
v___x_2631_ = lean_uint32_dec_eq(v___x_2630_, v___x_2629_);
if (v___x_2631_ == 0)
{
v___y_2620_ = v___x_2631_;
goto v___jp_2619_;
}
else
{
uint32_t v___x_2632_; uint32_t v___x_2633_; uint32_t v___x_2634_; uint8_t v___x_2635_; 
v___x_2632_ = 8388607;
v___x_2633_ = lean_uint32_land(v___y_2393_, v___x_2632_);
v___x_2634_ = 0;
v___x_2635_ = lean_uint32_dec_eq(v___x_2633_, v___x_2634_);
if (v___x_2635_ == 0)
{
v___y_2620_ = v___x_2631_;
goto v___jp_2619_;
}
else
{
goto v___jp_2609_;
}
}
}
v___jp_2636_:
{
if (v___y_2637_ == 0)
{
goto v___jp_2626_;
}
else
{
uint32_t v___x_2638_; uint32_t v___x_2639_; uint32_t v___x_2640_; uint8_t v___x_2641_; 
v___x_2638_ = 4194304;
v___x_2639_ = lean_uint32_land(v___y_2392_, v___x_2638_);
v___x_2640_ = 0;
v___x_2641_ = lean_uint32_dec_eq(v___x_2639_, v___x_2640_);
if (v___x_2641_ == 0)
{
goto v___jp_2626_;
}
else
{
uint32_t v___x_2642_; 
v___x_2642_ = lean_uint32_lor(v___y_2392_, v___x_2638_);
return v___x_2642_;
}
}
}
v___jp_2643_:
{
float v_result_2646_; uint8_t v___x_2647_; 
v_result_2646_ = lean_float32_mul(v___y_2644_, v___y_2645_);
v___x_2647_ = lean_float32_beq(v_result_2646_, v_result_2646_);
if (v___x_2647_ == 0)
{
uint32_t v___x_2648_; uint32_t v___x_2649_; uint32_t v___x_2650_; uint32_t v___x_2651_; uint8_t v___x_2652_; 
v___x_2648_ = 23;
v___x_2649_ = lean_uint32_shift_right(v___y_2392_, v___x_2648_);
v___x_2650_ = 255;
v___x_2651_ = lean_uint32_land(v___x_2649_, v___x_2650_);
v___x_2652_ = lean_uint32_dec_eq(v___x_2651_, v___x_2650_);
if (v___x_2652_ == 0)
{
v___y_2637_ = v___x_2652_;
goto v___jp_2636_;
}
else
{
uint32_t v___x_2653_; uint32_t v___x_2654_; uint32_t v___x_2655_; uint8_t v___x_2656_; 
v___x_2653_ = 8388607;
v___x_2654_ = lean_uint32_land(v___y_2392_, v___x_2653_);
v___x_2655_ = 0;
v___x_2656_ = lean_uint32_dec_eq(v___x_2654_, v___x_2655_);
if (v___x_2656_ == 0)
{
v___y_2637_ = v___x_2652_;
goto v___jp_2636_;
}
else
{
goto v___jp_2626_;
}
}
}
else
{
uint32_t v___x_2657_; 
v___x_2657_ = lean_float32_to_bits(v_result_2646_);
return v___x_2657_;
}
}
v___jp_2658_:
{
if (v___y_2660_ == 0)
{
float v___x_2661_; 
v___x_2661_ = lean_float32_of_bits(v___y_2393_);
v___y_2644_ = v___y_2659_;
v___y_2645_ = v___x_2661_;
goto v___jp_2643_;
}
else
{
uint32_t v___x_2662_; uint32_t v___x_2663_; uint32_t v___x_2664_; uint32_t v___x_2665_; float v___x_2666_; lean_object* v___x_2667_; uint32_t v___x_2668_; uint32_t v___x_2669_; lean_object* v___x_2670_; lean_object* v___x_2671_; float v___x_2672_; float v___x_2673_; 
v___x_2662_ = 8388607;
v___x_2663_ = lean_uint32_land(v___y_2393_, v___x_2662_);
v___x_2664_ = 8388608;
v___x_2665_ = lean_uint32_lor(v___x_2663_, v___x_2664_);
v___x_2666_ = lean_uint32_to_float32(v___x_2665_);
v___x_2667_ = lp_competition_R2W01b_scaleTable;
v___x_2668_ = 23;
v___x_2669_ = lean_uint32_shift_right(v___y_2393_, v___x_2668_);
v___x_2670_ = lean_uint32_to_nat(v___x_2669_);
v___x_2671_ = lean_array_fget_borrowed(v___x_2667_, v___x_2670_);
lean_dec(v___x_2670_);
v___x_2672_ = lean_unbox_float32(v___x_2671_);
v___x_2673_ = lean_float32_mul(v___x_2666_, v___x_2672_);
v___y_2644_ = v___y_2659_;
v___y_2645_ = v___x_2673_;
goto v___jp_2643_;
}
}
v___jp_2674_:
{
uint32_t v___x_2676_; uint32_t v_a_2677_; uint32_t v___x_2678_; uint32_t v___x_2679_; uint32_t v___x_2680_; uint8_t v___x_2681_; 
v___x_2676_ = 2147483647;
v_a_2677_ = lean_uint32_land(v___y_2393_, v___x_2676_);
v___x_2678_ = 201326591;
v___x_2679_ = 1;
v___x_2680_ = lean_uint32_sub(v_a_2677_, v___x_2679_);
v___x_2681_ = lean_uint32_dec_le(v___x_2678_, v___x_2680_);
if (v___x_2681_ == 0)
{
v___y_2659_ = v___y_2675_;
v___y_2660_ = v___x_2681_;
goto v___jp_2658_;
}
else
{
uint32_t v___x_2682_; uint8_t v___x_2683_; 
v___x_2682_ = 2139095040;
v___x_2683_ = lean_uint32_dec_lt(v_a_2677_, v___x_2682_);
v___y_2659_ = v___y_2675_;
v___y_2660_ = v___x_2683_;
goto v___jp_2658_;
}
}
v___jp_2684_:
{
uint32_t v___x_2686_; uint32_t v___x_2687_; 
v___x_2686_ = 8388608;
v___x_2687_ = lean_uint32_lor(v___y_2685_, v___x_2686_);
return v___x_2687_;
}
v___jp_2688_:
{
uint32_t v___x_2690_; uint32_t v___x_2691_; 
v___x_2690_ = 8388608;
v___x_2691_ = lean_uint32_lor(v___y_2689_, v___x_2690_);
return v___x_2691_;
}
v___jp_2692_:
{
uint32_t v___x_2696_; uint32_t v___x_2697_; 
v___x_2696_ = lean_uint32_land(v___y_2693_, v___y_2694_);
v___x_2697_ = lean_uint32_lor(v___y_2695_, v___x_2696_);
return v___x_2697_;
}
v___jp_2698_:
{
uint8_t v___x_2703_; 
v___x_2703_ = lean_uint64_dec_eq(v___y_2702_, v___y_2701_);
if (v___x_2703_ == 0)
{
uint64_t v___x_2704_; uint8_t v___x_2705_; 
v___x_2704_ = 8388608ULL;
v___x_2705_ = lean_uint64_dec_eq(v___y_2702_, v___x_2704_);
if (v___x_2705_ == 0)
{
uint32_t v___x_2706_; 
v___x_2706_ = lean_uint64_to_uint32(v___y_2702_);
if (v___y_2699_ == 0)
{
uint32_t v___x_2707_; 
v___x_2707_ = 0;
v___y_2693_ = v___x_2706_;
v___y_2694_ = v___y_2700_;
v___y_2695_ = v___x_2707_;
goto v___jp_2692_;
}
else
{
uint32_t v___x_2708_; 
v___x_2708_ = 2147483648;
v___y_2693_ = v___x_2706_;
v___y_2694_ = v___y_2700_;
v___y_2695_ = v___x_2708_;
goto v___jp_2692_;
}
}
else
{
if (v___y_2699_ == 0)
{
uint32_t v___x_2709_; 
v___x_2709_ = 0;
v___y_2689_ = v___x_2709_;
goto v___jp_2688_;
}
else
{
uint32_t v___x_2710_; 
v___x_2710_ = 2147483648;
v___y_2689_ = v___x_2710_;
goto v___jp_2688_;
}
}
}
else
{
if (v___y_2699_ == 0)
{
uint32_t v___x_2711_; 
v___x_2711_ = 0;
return v___x_2711_;
}
else
{
uint32_t v___x_2712_; 
v___x_2712_ = 2147483648;
return v___x_2712_;
}
}
}
v___jp_2713_:
{
uint32_t v___x_2717_; uint32_t v___x_2718_; 
v___x_2717_ = lean_uint32_land(v___y_2714_, v___y_2715_);
v___x_2718_ = lean_uint32_lor(v___y_2716_, v___x_2717_);
return v___x_2718_;
}
v___jp_2719_:
{
uint8_t v___x_2724_; 
v___x_2724_ = lean_uint64_dec_eq(v___y_2723_, v___y_2721_);
if (v___x_2724_ == 0)
{
uint64_t v___x_2725_; uint8_t v___x_2726_; 
v___x_2725_ = 8388608ULL;
v___x_2726_ = lean_uint64_dec_eq(v___y_2723_, v___x_2725_);
if (v___x_2726_ == 0)
{
uint32_t v___x_2727_; 
v___x_2727_ = lean_uint64_to_uint32(v___y_2723_);
if (v___y_2720_ == 0)
{
uint32_t v___x_2728_; 
v___x_2728_ = 0;
v___y_2714_ = v___x_2727_;
v___y_2715_ = v___y_2722_;
v___y_2716_ = v___x_2728_;
goto v___jp_2713_;
}
else
{
uint32_t v___x_2729_; 
v___x_2729_ = 2147483648;
v___y_2714_ = v___x_2727_;
v___y_2715_ = v___y_2722_;
v___y_2716_ = v___x_2729_;
goto v___jp_2713_;
}
}
else
{
if (v___y_2720_ == 0)
{
uint32_t v___x_2730_; 
v___x_2730_ = 0;
v___y_2685_ = v___x_2730_;
goto v___jp_2684_;
}
else
{
uint32_t v___x_2731_; 
v___x_2731_ = 2147483648;
v___y_2685_ = v___x_2731_;
goto v___jp_2684_;
}
}
}
else
{
if (v___y_2720_ == 0)
{
uint32_t v___x_2732_; 
v___x_2732_ = 0;
return v___x_2732_;
}
else
{
uint32_t v___x_2733_; 
v___x_2733_ = 2147483648;
return v___x_2733_;
}
}
}
v___jp_2734_:
{
if (v___y_2735_ == 0)
{
uint32_t v___x_2736_; 
v___x_2736_ = lp_competition_Submission_FastMul_mul(v___y_2392_, v___y_2393_);
return v___x_2736_;
}
else
{
uint32_t v___x_2737_; uint32_t v___x_2738_; 
v___x_2737_ = 4194304;
v___x_2738_ = lean_uint32_lor(v___y_2393_, v___x_2737_);
return v___x_2738_;
}
}
v___jp_2739_:
{
uint32_t v___x_2740_; uint32_t v___x_2741_; uint32_t v___x_2742_; uint32_t v___x_2743_; uint8_t v___x_2744_; 
v___x_2740_ = 23;
v___x_2741_ = lean_uint32_shift_right(v___y_2393_, v___x_2740_);
v___x_2742_ = 255;
v___x_2743_ = lean_uint32_land(v___x_2741_, v___x_2742_);
v___x_2744_ = lean_uint32_dec_eq(v___x_2743_, v___x_2742_);
if (v___x_2744_ == 0)
{
v___y_2735_ = v___x_2744_;
goto v___jp_2734_;
}
else
{
uint32_t v___x_2745_; uint32_t v___x_2746_; uint32_t v___x_2747_; uint8_t v___x_2748_; 
v___x_2745_ = 8388607;
v___x_2746_ = lean_uint32_land(v___y_2393_, v___x_2745_);
v___x_2747_ = 0;
v___x_2748_ = lean_uint32_dec_eq(v___x_2746_, v___x_2747_);
if (v___x_2748_ == 0)
{
v___y_2735_ = v___x_2744_;
goto v___jp_2734_;
}
else
{
uint32_t v___x_2749_; 
v___x_2749_ = lp_competition_Submission_FastMul_mul(v___y_2392_, v___y_2393_);
return v___x_2749_;
}
}
}
v___jp_2750_:
{
if (v___y_2751_ == 0)
{
goto v___jp_2739_;
}
else
{
uint32_t v___x_2752_; uint32_t v___x_2753_; 
v___x_2752_ = 4194304;
v___x_2753_ = lean_uint32_lor(v___y_2392_, v___x_2752_);
return v___x_2753_;
}
}
v___jp_2754_:
{
uint32_t v___x_2755_; uint32_t v___x_2756_; uint32_t v___x_2757_; uint32_t v___x_2758_; uint8_t v___x_2759_; 
v___x_2755_ = 23;
v___x_2756_ = lean_uint32_shift_right(v___y_2392_, v___x_2755_);
v___x_2757_ = 255;
v___x_2758_ = lean_uint32_land(v___x_2756_, v___x_2757_);
v___x_2759_ = lean_uint32_dec_eq(v___x_2758_, v___x_2757_);
if (v___x_2759_ == 0)
{
v___y_2751_ = v___x_2759_;
goto v___jp_2750_;
}
else
{
uint32_t v___x_2760_; uint32_t v___x_2761_; uint32_t v___x_2762_; uint8_t v___x_2763_; 
v___x_2760_ = 8388607;
v___x_2761_ = lean_uint32_land(v___y_2392_, v___x_2760_);
v___x_2762_ = 0;
v___x_2763_ = lean_uint32_dec_eq(v___x_2761_, v___x_2762_);
if (v___x_2763_ == 0)
{
v___y_2751_ = v___x_2759_;
goto v___jp_2750_;
}
else
{
goto v___jp_2739_;
}
}
}
v___jp_2764_:
{
if (v___y_2765_ == 0)
{
goto v___jp_2754_;
}
else
{
uint32_t v___x_2766_; uint32_t v___x_2767_; uint32_t v___x_2768_; uint8_t v___x_2769_; 
v___x_2766_ = 4194304;
v___x_2767_ = lean_uint32_land(v___y_2393_, v___x_2766_);
v___x_2768_ = 0;
v___x_2769_ = lean_uint32_dec_eq(v___x_2767_, v___x_2768_);
if (v___x_2769_ == 0)
{
goto v___jp_2754_;
}
else
{
uint32_t v___x_2770_; 
v___x_2770_ = lean_uint32_lor(v___y_2393_, v___x_2766_);
return v___x_2770_;
}
}
}
v___jp_2771_:
{
uint32_t v___x_2772_; uint32_t v___x_2773_; uint32_t v___x_2774_; uint32_t v___x_2775_; uint8_t v___x_2776_; 
v___x_2772_ = 23;
v___x_2773_ = lean_uint32_shift_right(v___y_2393_, v___x_2772_);
v___x_2774_ = 255;
v___x_2775_ = lean_uint32_land(v___x_2773_, v___x_2774_);
v___x_2776_ = lean_uint32_dec_eq(v___x_2775_, v___x_2774_);
if (v___x_2776_ == 0)
{
v___y_2765_ = v___x_2776_;
goto v___jp_2764_;
}
else
{
uint32_t v___x_2777_; uint32_t v___x_2778_; uint32_t v___x_2779_; uint8_t v___x_2780_; 
v___x_2777_ = 8388607;
v___x_2778_ = lean_uint32_land(v___y_2393_, v___x_2777_);
v___x_2779_ = 0;
v___x_2780_ = lean_uint32_dec_eq(v___x_2778_, v___x_2779_);
if (v___x_2780_ == 0)
{
v___y_2765_ = v___x_2776_;
goto v___jp_2764_;
}
else
{
goto v___jp_2754_;
}
}
}
v___jp_2781_:
{
if (v___y_2782_ == 0)
{
goto v___jp_2771_;
}
else
{
uint32_t v___x_2783_; uint32_t v___x_2784_; uint32_t v___x_2785_; uint8_t v___x_2786_; 
v___x_2783_ = 4194304;
v___x_2784_ = lean_uint32_land(v___y_2392_, v___x_2783_);
v___x_2785_ = 0;
v___x_2786_ = lean_uint32_dec_eq(v___x_2784_, v___x_2785_);
if (v___x_2786_ == 0)
{
goto v___jp_2771_;
}
else
{
uint32_t v___x_2787_; 
v___x_2787_ = lean_uint32_lor(v___y_2392_, v___x_2783_);
return v___x_2787_;
}
}
}
v___jp_2788_:
{
float v_result_2791_; uint8_t v___x_2792_; 
v_result_2791_ = lean_float32_mul(v___y_2789_, v___y_2790_);
v___x_2792_ = lean_float32_beq(v_result_2791_, v_result_2791_);
if (v___x_2792_ == 0)
{
uint32_t v___x_2793_; uint32_t v___x_2794_; uint32_t v___x_2795_; uint32_t v___x_2796_; uint8_t v___x_2797_; 
v___x_2793_ = 23;
v___x_2794_ = lean_uint32_shift_right(v___y_2392_, v___x_2793_);
v___x_2795_ = 255;
v___x_2796_ = lean_uint32_land(v___x_2794_, v___x_2795_);
v___x_2797_ = lean_uint32_dec_eq(v___x_2796_, v___x_2795_);
if (v___x_2797_ == 0)
{
v___y_2782_ = v___x_2797_;
goto v___jp_2781_;
}
else
{
uint32_t v___x_2798_; uint32_t v___x_2799_; uint32_t v___x_2800_; uint8_t v___x_2801_; 
v___x_2798_ = 8388607;
v___x_2799_ = lean_uint32_land(v___y_2392_, v___x_2798_);
v___x_2800_ = 0;
v___x_2801_ = lean_uint32_dec_eq(v___x_2799_, v___x_2800_);
if (v___x_2801_ == 0)
{
v___y_2782_ = v___x_2797_;
goto v___jp_2781_;
}
else
{
goto v___jp_2771_;
}
}
}
else
{
uint32_t v___x_2802_; 
v___x_2802_ = lean_float32_to_bits(v_result_2791_);
return v___x_2802_;
}
}
v___jp_2803_:
{
if (v___y_2805_ == 0)
{
float v___x_2806_; 
v___x_2806_ = lean_float32_of_bits(v___y_2393_);
v___y_2789_ = v___y_2804_;
v___y_2790_ = v___x_2806_;
goto v___jp_2788_;
}
else
{
uint32_t v___x_2807_; uint32_t v___x_2808_; uint32_t v___x_2809_; uint32_t v___x_2810_; float v___x_2811_; lean_object* v___x_2812_; uint32_t v___x_2813_; uint32_t v___x_2814_; lean_object* v___x_2815_; lean_object* v___x_2816_; float v___x_2817_; float v___x_2818_; 
v___x_2807_ = 8388607;
v___x_2808_ = lean_uint32_land(v___y_2393_, v___x_2807_);
v___x_2809_ = 8388608;
v___x_2810_ = lean_uint32_lor(v___x_2808_, v___x_2809_);
v___x_2811_ = lean_uint32_to_float32(v___x_2810_);
v___x_2812_ = lp_competition_R2W01b_scaleTable;
v___x_2813_ = 23;
v___x_2814_ = lean_uint32_shift_right(v___y_2393_, v___x_2813_);
v___x_2815_ = lean_uint32_to_nat(v___x_2814_);
v___x_2816_ = lean_array_fget_borrowed(v___x_2812_, v___x_2815_);
lean_dec(v___x_2815_);
v___x_2817_ = lean_unbox_float32(v___x_2816_);
v___x_2818_ = lean_float32_mul(v___x_2811_, v___x_2817_);
v___y_2789_ = v___y_2804_;
v___y_2790_ = v___x_2818_;
goto v___jp_2788_;
}
}
v___jp_2819_:
{
uint32_t v___x_2821_; uint32_t v_a_2822_; uint32_t v___x_2823_; uint32_t v___x_2824_; uint32_t v___x_2825_; uint8_t v___x_2826_; 
v___x_2821_ = 2147483647;
v_a_2822_ = lean_uint32_land(v___y_2393_, v___x_2821_);
v___x_2823_ = 201326591;
v___x_2824_ = 1;
v___x_2825_ = lean_uint32_sub(v_a_2822_, v___x_2824_);
v___x_2826_ = lean_uint32_dec_le(v___x_2823_, v___x_2825_);
if (v___x_2826_ == 0)
{
v___y_2804_ = v___y_2820_;
v___y_2805_ = v___x_2826_;
goto v___jp_2803_;
}
else
{
uint32_t v___x_2827_; uint8_t v___x_2828_; 
v___x_2827_ = 2139095040;
v___x_2828_ = lean_uint32_dec_lt(v_a_2822_, v___x_2827_);
v___y_2804_ = v___y_2820_;
v___y_2805_ = v___x_2828_;
goto v___jp_2803_;
}
}
v___jp_2831_:
{
if (v___y_2832_ == 0)
{
float v___x_2833_; 
v___x_2833_ = lean_float32_of_bits(v___y_2392_);
v___y_2530_ = v___x_2833_;
goto v___jp_2529_;
}
else
{
uint32_t v___x_2834_; uint32_t v___x_2835_; uint32_t v___x_2836_; uint32_t v___x_2837_; float v___x_2838_; lean_object* v___x_2839_; lean_object* v___x_2840_; lean_object* v___x_2841_; float v___x_2842_; float v___x_2843_; 
v___x_2834_ = 8388607;
v___x_2835_ = lean_uint32_land(v___y_2392_, v___x_2834_);
v___x_2836_ = 8388608;
v___x_2837_ = lean_uint32_lor(v___x_2835_, v___x_2836_);
v___x_2838_ = lean_uint32_to_float32(v___x_2837_);
v___x_2839_ = lp_competition_R2W01b_scaleTable;
v___x_2840_ = lean_uint32_to_nat(v___x_2830_);
v___x_2841_ = lean_array_fget_borrowed(v___x_2839_, v___x_2840_);
lean_dec(v___x_2840_);
v___x_2842_ = lean_unbox_float32(v___x_2841_);
v___x_2843_ = lean_float32_mul(v___x_2838_, v___x_2842_);
v___y_2530_ = v___x_2843_;
goto v___jp_2529_;
}
}
v___jp_2844_:
{
if (v___y_2845_ == 0)
{
float v___x_2846_; 
v___x_2846_ = lean_float32_of_bits(v___y_2392_);
v___y_2675_ = v___x_2846_;
goto v___jp_2674_;
}
else
{
uint32_t v___x_2847_; uint32_t v___x_2848_; uint32_t v___x_2849_; uint32_t v___x_2850_; float v___x_2851_; lean_object* v___x_2852_; lean_object* v___x_2853_; lean_object* v___x_2854_; float v___x_2855_; float v___x_2856_; 
v___x_2847_ = 8388607;
v___x_2848_ = lean_uint32_land(v___y_2392_, v___x_2847_);
v___x_2849_ = 8388608;
v___x_2850_ = lean_uint32_lor(v___x_2848_, v___x_2849_);
v___x_2851_ = lean_uint32_to_float32(v___x_2850_);
v___x_2852_ = lp_competition_R2W01b_scaleTable;
v___x_2853_ = lean_uint32_to_nat(v___x_2830_);
v___x_2854_ = lean_array_fget_borrowed(v___x_2852_, v___x_2853_);
lean_dec(v___x_2853_);
v___x_2855_ = lean_unbox_float32(v___x_2854_);
v___x_2856_ = lean_float32_mul(v___x_2851_, v___x_2855_);
v___y_2675_ = v___x_2856_;
goto v___jp_2674_;
}
}
v___jp_2857_:
{
if (v___y_2858_ == 0)
{
float v___x_2859_; 
v___x_2859_ = lean_float32_of_bits(v___y_2392_);
v___y_2820_ = v___x_2859_;
goto v___jp_2819_;
}
else
{
uint32_t v___x_2860_; uint32_t v___x_2861_; uint32_t v___x_2862_; uint32_t v___x_2863_; float v___x_2864_; lean_object* v___x_2865_; lean_object* v___x_2866_; lean_object* v___x_2867_; float v___x_2868_; float v___x_2869_; 
v___x_2860_ = 8388607;
v___x_2861_ = lean_uint32_land(v___y_2392_, v___x_2860_);
v___x_2862_ = 8388608;
v___x_2863_ = lean_uint32_lor(v___x_2861_, v___x_2862_);
v___x_2864_ = lean_uint32_to_float32(v___x_2863_);
v___x_2865_ = lp_competition_R2W01b_scaleTable;
v___x_2866_ = lean_uint32_to_nat(v___x_2830_);
v___x_2867_ = lean_array_fget_borrowed(v___x_2865_, v___x_2866_);
lean_dec(v___x_2866_);
v___x_2868_ = lean_unbox_float32(v___x_2867_);
v___x_2869_ = lean_float32_mul(v___x_2864_, v___x_2868_);
v___y_2820_ = v___x_2869_;
goto v___jp_2819_;
}
}
v___jp_2871_:
{
uint32_t v___x_2876_; uint32_t v___x_2877_; uint32_t v___x_2878_; uint32_t v___x_2879_; uint32_t v___x_2880_; 
v___x_2876_ = lean_uint32_land(v___y_2872_, v___x_2870_);
v___x_2877_ = lean_uint32_shift_left(v___x_2876_, v___x_2829_);
v___x_2878_ = lean_uint32_lor(v___y_2875_, v___x_2877_);
v___x_2879_ = lean_uint32_land(v___y_2873_, v___y_2874_);
v___x_2880_ = lean_uint32_lor(v___x_2878_, v___x_2879_);
return v___x_2880_;
}
v___jp_2881_:
{
if (v___y_2884_ == 0)
{
uint32_t v___x_2886_; 
v___x_2886_ = 0;
v___y_2872_ = v___y_2882_;
v___y_2873_ = v___y_2885_;
v___y_2874_ = v___y_2883_;
v___y_2875_ = v___x_2886_;
goto v___jp_2871_;
}
else
{
uint32_t v___x_2887_; 
v___x_2887_ = 2147483648;
v___y_2872_ = v___y_2882_;
v___y_2873_ = v___y_2885_;
v___y_2874_ = v___y_2883_;
v___y_2875_ = v___x_2887_;
goto v___jp_2871_;
}
}
v___jp_2888_:
{
uint64_t v___x_2894_; uint64_t v_encodedExponent_2895_; uint32_t v___x_2896_; uint64_t v___x_2897_; uint8_t v___x_2898_; 
v___x_2894_ = 171ULL;
v_encodedExponent_2895_ = lean_uint64_sub(v___y_2889_, v___x_2894_);
v___x_2896_ = lean_uint64_to_uint32(v_encodedExponent_2895_);
v___x_2897_ = 8388608ULL;
v___x_2898_ = lean_uint64_dec_lt(v___y_2893_, v___x_2897_);
if (v___x_2898_ == 0)
{
uint64_t v___x_2899_; uint32_t v___x_2900_; 
v___x_2899_ = lean_uint64_sub(v___y_2893_, v___x_2897_);
v___x_2900_ = lean_uint64_to_uint32(v___x_2899_);
v___y_2882_ = v___x_2896_;
v___y_2883_ = v___y_2891_;
v___y_2884_ = v___y_2892_;
v___y_2885_ = v___x_2900_;
goto v___jp_2881_;
}
else
{
uint32_t v___x_2901_; 
v___x_2901_ = lean_uint64_to_uint32(v___y_2890_);
v___y_2882_ = v___x_2896_;
v___y_2883_ = v___y_2891_;
v___y_2884_ = v___y_2892_;
v___y_2885_ = v___x_2901_;
goto v___jp_2881_;
}
}
v___jp_2902_:
{
uint64_t v___x_2909_; uint8_t v___x_2910_; 
v___x_2909_ = 425ULL;
v___x_2910_ = lean_uint64_dec_lt(v___x_2909_, v___y_2908_);
if (v___x_2910_ == 0)
{
if (v___y_2904_ == 0)
{
v___y_2889_ = v___y_2908_;
v___y_2890_ = v___y_2905_;
v___y_2891_ = v___y_2906_;
v___y_2892_ = v___y_2907_;
v___y_2893_ = v___y_2903_;
goto v___jp_2888_;
}
else
{
uint64_t v___x_2911_; 
v___x_2911_ = 8388608ULL;
v___y_2889_ = v___y_2908_;
v___y_2890_ = v___y_2905_;
v___y_2891_ = v___y_2906_;
v___y_2892_ = v___y_2907_;
v___y_2893_ = v___x_2911_;
goto v___jp_2888_;
}
}
else
{
if (v___y_2907_ == 0)
{
uint32_t v___x_2912_; 
v___x_2912_ = 2139095040;
return v___x_2912_;
}
else
{
uint32_t v___x_2913_; 
v___x_2913_ = 4286578688;
return v___x_2913_;
}
}
}
v___jp_2914_:
{
uint64_t v___x_2920_; uint8_t v_carry_2921_; 
v___x_2920_ = 16777216ULL;
v_carry_2921_ = lean_uint64_dec_eq(v___y_2919_, v___x_2920_);
if (v_carry_2921_ == 0)
{
v___y_2903_ = v___y_2919_;
v___y_2904_ = v_carry_2921_;
v___y_2905_ = v___y_2916_;
v___y_2906_ = v___y_2917_;
v___y_2907_ = v___y_2918_;
v___y_2908_ = v___y_2915_;
goto v___jp_2902_;
}
else
{
uint64_t v___x_2922_; uint64_t v___x_2923_; 
v___x_2922_ = 1ULL;
v___x_2923_ = lean_uint64_add(v___y_2915_, v___x_2922_);
v___y_2903_ = v___y_2919_;
v___y_2904_ = v_carry_2921_;
v___y_2905_ = v___y_2916_;
v___y_2906_ = v___y_2917_;
v___y_2907_ = v___y_2918_;
v___y_2908_ = v___x_2923_;
goto v___jp_2902_;
}
}
v___jp_2924_:
{
uint64_t v_position_2931_; uint64_t v___x_2932_; uint8_t v___x_2933_; 
v_position_2931_ = lean_uint64_add(v___y_2930_, v___y_2928_);
v___x_2932_ = 172ULL;
v___x_2933_ = lean_uint64_dec_lt(v_position_2931_, v___x_2932_);
if (v___x_2933_ == 0)
{
uint64_t v___x_2934_; uint8_t v___x_2935_; 
v___x_2934_ = 23ULL;
v___x_2935_ = lean_uint64_dec_lt(v___y_2930_, v___x_2934_);
if (v___x_2935_ == 0)
{
uint64_t v___x_2936_; uint8_t v___x_2937_; 
v___x_2936_ = lean_uint64_sub(v___y_2930_, v___x_2934_);
v___x_2937_ = lean_uint64_dec_eq(v___x_2936_, v___y_2926_);
if (v___x_2937_ == 0)
{
uint64_t v___x_2938_; uint8_t v___x_2939_; 
v___x_2938_ = 64ULL;
v___x_2939_ = lean_uint64_dec_lt(v___x_2936_, v___x_2938_);
if (v___x_2939_ == 0)
{
uint8_t v___x_2940_; 
v___x_2940_ = lean_uint64_dec_eq(v___x_2936_, v___x_2938_);
if (v___x_2940_ == 0)
{
v___y_2915_ = v_position_2931_;
v___y_2916_ = v___y_2926_;
v___y_2917_ = v___y_2927_;
v___y_2918_ = v___y_2929_;
v___y_2919_ = v___y_2926_;
goto v___jp_2914_;
}
else
{
uint64_t v___x_2941_; uint8_t v___x_2942_; 
v___x_2941_ = 9223372036854775808ULL;
v___x_2942_ = lean_uint64_dec_lt(v___x_2941_, v___y_2925_);
if (v___x_2942_ == 0)
{
v___y_2915_ = v_position_2931_;
v___y_2916_ = v___y_2926_;
v___y_2917_ = v___y_2927_;
v___y_2918_ = v___y_2929_;
v___y_2919_ = v___y_2926_;
goto v___jp_2914_;
}
else
{
uint64_t v___x_2943_; 
v___x_2943_ = 1ULL;
v___y_2915_ = v_position_2931_;
v___y_2916_ = v___y_2926_;
v___y_2917_ = v___y_2927_;
v___y_2918_ = v___y_2929_;
v___y_2919_ = v___x_2943_;
goto v___jp_2914_;
}
}
}
else
{
uint64_t v_quotient_2944_; uint64_t v___x_2945_; uint64_t v___x_2946_; uint64_t v___x_2947_; uint64_t v_remainder_2948_; uint64_t v___x_2949_; uint64_t v_half_2950_; uint8_t v___x_2951_; 
v_quotient_2944_ = lean_uint64_shift_right(v___y_2925_, v___x_2936_);
v___x_2945_ = 1ULL;
v___x_2946_ = lean_uint64_shift_left(v___x_2945_, v___x_2936_);
v___x_2947_ = lean_uint64_sub(v___x_2946_, v___x_2945_);
v_remainder_2948_ = lean_uint64_land(v___y_2925_, v___x_2947_);
v___x_2949_ = lean_uint64_sub(v___x_2936_, v___x_2945_);
v_half_2950_ = lean_uint64_shift_left(v___x_2945_, v___x_2949_);
v___x_2951_ = lean_uint64_dec_lt(v_remainder_2948_, v_half_2950_);
if (v___x_2951_ == 0)
{
uint8_t v___x_2952_; 
v___x_2952_ = lean_uint64_dec_lt(v_half_2950_, v_remainder_2948_);
if (v___x_2952_ == 0)
{
uint64_t v___x_2953_; uint8_t v___x_2954_; 
v___x_2953_ = lean_uint64_land(v_quotient_2944_, v___x_2945_);
v___x_2954_ = lean_uint64_dec_eq(v___x_2953_, v___y_2926_);
if (v___x_2954_ == 0)
{
uint64_t v___x_2955_; 
v___x_2955_ = lean_uint64_add(v_quotient_2944_, v___x_2945_);
v___y_2915_ = v_position_2931_;
v___y_2916_ = v___y_2926_;
v___y_2917_ = v___y_2927_;
v___y_2918_ = v___y_2929_;
v___y_2919_ = v___x_2955_;
goto v___jp_2914_;
}
else
{
v___y_2915_ = v_position_2931_;
v___y_2916_ = v___y_2926_;
v___y_2917_ = v___y_2927_;
v___y_2918_ = v___y_2929_;
v___y_2919_ = v_quotient_2944_;
goto v___jp_2914_;
}
}
else
{
uint64_t v___x_2956_; 
v___x_2956_ = lean_uint64_add(v_quotient_2944_, v___x_2945_);
v___y_2915_ = v_position_2931_;
v___y_2916_ = v___y_2926_;
v___y_2917_ = v___y_2927_;
v___y_2918_ = v___y_2929_;
v___y_2919_ = v___x_2956_;
goto v___jp_2914_;
}
}
else
{
v___y_2915_ = v_position_2931_;
v___y_2916_ = v___y_2926_;
v___y_2917_ = v___y_2927_;
v___y_2918_ = v___y_2929_;
v___y_2919_ = v_quotient_2944_;
goto v___jp_2914_;
}
}
}
else
{
v___y_2915_ = v_position_2931_;
v___y_2916_ = v___y_2926_;
v___y_2917_ = v___y_2927_;
v___y_2918_ = v___y_2929_;
v___y_2919_ = v___y_2925_;
goto v___jp_2914_;
}
}
else
{
uint64_t v___x_2957_; uint64_t v___x_2958_; 
v___x_2957_ = lean_uint64_sub(v___x_2934_, v___y_2930_);
v___x_2958_ = lean_uint64_shift_left(v___y_2925_, v___x_2957_);
v___y_2915_ = v_position_2931_;
v___y_2916_ = v___y_2926_;
v___y_2917_ = v___y_2927_;
v___y_2918_ = v___y_2929_;
v___y_2919_ = v___x_2958_;
goto v___jp_2914_;
}
}
else
{
uint64_t v___x_2959_; uint8_t v___x_2960_; 
v___x_2959_ = 149ULL;
v___x_2960_ = lean_uint64_dec_lt(v___y_2928_, v___x_2959_);
if (v___x_2960_ == 0)
{
uint64_t v___x_2961_; uint64_t v___x_2962_; 
v___x_2961_ = lean_uint64_sub(v___y_2928_, v___x_2959_);
v___x_2962_ = lean_uint64_shift_left(v___y_2925_, v___x_2961_);
v___y_2409_ = v___y_2926_;
v___y_2410_ = v___y_2927_;
v___y_2411_ = v___y_2929_;
v___y_2412_ = v___x_2962_;
goto v___jp_2408_;
}
else
{
uint64_t v___x_2963_; uint8_t v___x_2964_; 
v___x_2963_ = lean_uint64_sub(v___x_2959_, v___y_2928_);
v___x_2964_ = lean_uint64_dec_eq(v___x_2963_, v___y_2926_);
if (v___x_2964_ == 0)
{
uint64_t v___x_2965_; uint8_t v___x_2966_; 
v___x_2965_ = 64ULL;
v___x_2966_ = lean_uint64_dec_lt(v___x_2963_, v___x_2965_);
if (v___x_2966_ == 0)
{
uint8_t v___x_2967_; 
v___x_2967_ = lean_uint64_dec_eq(v___x_2963_, v___x_2965_);
if (v___x_2967_ == 0)
{
v___y_2409_ = v___y_2926_;
v___y_2410_ = v___y_2927_;
v___y_2411_ = v___y_2929_;
v___y_2412_ = v___y_2926_;
goto v___jp_2408_;
}
else
{
uint64_t v___x_2968_; uint8_t v___x_2969_; 
v___x_2968_ = 9223372036854775808ULL;
v___x_2969_ = lean_uint64_dec_lt(v___x_2968_, v___y_2925_);
if (v___x_2969_ == 0)
{
v___y_2409_ = v___y_2926_;
v___y_2410_ = v___y_2927_;
v___y_2411_ = v___y_2929_;
v___y_2412_ = v___y_2926_;
goto v___jp_2408_;
}
else
{
uint64_t v___x_2970_; 
v___x_2970_ = 1ULL;
v___y_2409_ = v___y_2926_;
v___y_2410_ = v___y_2927_;
v___y_2411_ = v___y_2929_;
v___y_2412_ = v___x_2970_;
goto v___jp_2408_;
}
}
}
else
{
uint64_t v_quotient_2971_; uint64_t v___x_2972_; uint64_t v___x_2973_; uint64_t v___x_2974_; uint64_t v_remainder_2975_; uint64_t v___x_2976_; uint64_t v_half_2977_; uint8_t v___x_2978_; 
v_quotient_2971_ = lean_uint64_shift_right(v___y_2925_, v___x_2963_);
v___x_2972_ = 1ULL;
v___x_2973_ = lean_uint64_shift_left(v___x_2972_, v___x_2963_);
v___x_2974_ = lean_uint64_sub(v___x_2973_, v___x_2972_);
v_remainder_2975_ = lean_uint64_land(v___y_2925_, v___x_2974_);
v___x_2976_ = lean_uint64_sub(v___x_2963_, v___x_2972_);
v_half_2977_ = lean_uint64_shift_left(v___x_2972_, v___x_2976_);
v___x_2978_ = lean_uint64_dec_lt(v_remainder_2975_, v_half_2977_);
if (v___x_2978_ == 0)
{
uint8_t v___x_2979_; 
v___x_2979_ = lean_uint64_dec_lt(v_half_2977_, v_remainder_2975_);
if (v___x_2979_ == 0)
{
uint64_t v___x_2980_; uint8_t v___x_2981_; 
v___x_2980_ = lean_uint64_land(v_quotient_2971_, v___x_2972_);
v___x_2981_ = lean_uint64_dec_eq(v___x_2980_, v___y_2926_);
if (v___x_2981_ == 0)
{
uint64_t v___x_2982_; 
v___x_2982_ = lean_uint64_add(v_quotient_2971_, v___x_2972_);
v___y_2409_ = v___y_2926_;
v___y_2410_ = v___y_2927_;
v___y_2411_ = v___y_2929_;
v___y_2412_ = v___x_2982_;
goto v___jp_2408_;
}
else
{
v___y_2409_ = v___y_2926_;
v___y_2410_ = v___y_2927_;
v___y_2411_ = v___y_2929_;
v___y_2412_ = v_quotient_2971_;
goto v___jp_2408_;
}
}
else
{
uint64_t v___x_2983_; 
v___x_2983_ = lean_uint64_add(v_quotient_2971_, v___x_2972_);
v___y_2409_ = v___y_2926_;
v___y_2410_ = v___y_2927_;
v___y_2411_ = v___y_2929_;
v___y_2412_ = v___x_2983_;
goto v___jp_2408_;
}
}
else
{
v___y_2409_ = v___y_2926_;
v___y_2410_ = v___y_2927_;
v___y_2411_ = v___y_2929_;
v___y_2412_ = v_quotient_2971_;
goto v___jp_2408_;
}
}
}
else
{
v___y_2409_ = v___y_2926_;
v___y_2410_ = v___y_2927_;
v___y_2411_ = v___y_2929_;
v___y_2412_ = v___y_2925_;
goto v___jp_2408_;
}
}
}
}
v___jp_2984_:
{
uint64_t v___x_2992_; uint64_t v___x_2993_; uint8_t v___x_2994_; 
v___x_2992_ = 1ULL;
v___x_2993_ = lean_uint64_shift_right(v___y_2989_, v___x_2992_);
v___x_2994_ = lean_uint64_dec_eq(v___x_2993_, v___y_2986_);
if (v___x_2994_ == 0)
{
uint64_t v___x_2995_; 
v___x_2995_ = lean_uint64_add(v___y_2991_, v___x_2992_);
v___y_2925_ = v___y_2985_;
v___y_2926_ = v___y_2986_;
v___y_2927_ = v___y_2987_;
v___y_2928_ = v___y_2988_;
v___y_2929_ = v___y_2990_;
v___y_2930_ = v___x_2995_;
goto v___jp_2924_;
}
else
{
v___y_2925_ = v___y_2985_;
v___y_2926_ = v___y_2986_;
v___y_2927_ = v___y_2987_;
v___y_2928_ = v___y_2988_;
v___y_2929_ = v___y_2990_;
v___y_2930_ = v___y_2991_;
goto v___jp_2924_;
}
}
v___jp_2996_:
{
uint64_t v___x_3006_; uint8_t v___x_3007_; 
v___x_3006_ = lean_uint64_shift_right(v___y_3002_, v___y_3003_);
v___x_3007_ = lean_uint64_dec_eq(v___x_3006_, v___y_2999_);
if (v___x_3007_ == 0)
{
uint64_t v___x_3008_; 
v___x_3008_ = lean_uint64_add(v___y_2998_, v___y_3003_);
v___y_2985_ = v___y_2997_;
v___y_2986_ = v___y_2999_;
v___y_2987_ = v___y_3000_;
v___y_2988_ = v___y_3001_;
v___y_2989_ = v___y_3005_;
v___y_2990_ = v___y_3004_;
v___y_2991_ = v___x_3008_;
goto v___jp_2984_;
}
else
{
v___y_2985_ = v___y_2997_;
v___y_2986_ = v___y_2999_;
v___y_2987_ = v___y_3000_;
v___y_2988_ = v___y_3001_;
v___y_2989_ = v___y_3005_;
v___y_2990_ = v___y_3004_;
v___y_2991_ = v___y_2998_;
goto v___jp_2984_;
}
}
v___jp_3009_:
{
uint64_t v___x_3017_; uint64_t v___x_3018_; uint8_t v___x_3019_; 
v___x_3017_ = 2ULL;
v___x_3018_ = lean_uint64_shift_right(v___y_3014_, v___x_3017_);
v___x_3019_ = lean_uint64_dec_eq(v___x_3018_, v___y_3011_);
if (v___x_3019_ == 0)
{
v___y_2997_ = v___y_3010_;
v___y_2998_ = v___y_3016_;
v___y_2999_ = v___y_3011_;
v___y_3000_ = v___y_3012_;
v___y_3001_ = v___y_3013_;
v___y_3002_ = v___y_3014_;
v___y_3003_ = v___x_3017_;
v___y_3004_ = v___y_3015_;
v___y_3005_ = v___x_3018_;
goto v___jp_2996_;
}
else
{
v___y_2997_ = v___y_3010_;
v___y_2998_ = v___y_3016_;
v___y_2999_ = v___y_3011_;
v___y_3000_ = v___y_3012_;
v___y_3001_ = v___y_3013_;
v___y_3002_ = v___y_3014_;
v___y_3003_ = v___x_3017_;
v___y_3004_ = v___y_3015_;
v___y_3005_ = v___y_3014_;
goto v___jp_2996_;
}
}
v___jp_3020_:
{
uint64_t v___x_3030_; uint8_t v___x_3031_; 
v___x_3030_ = lean_uint64_shift_right(v___y_3024_, v___y_3021_);
v___x_3031_ = lean_uint64_dec_eq(v___x_3030_, v___y_3023_);
if (v___x_3031_ == 0)
{
uint64_t v___x_3032_; 
v___x_3032_ = lean_uint64_add(v___y_3027_, v___y_3021_);
v___y_3010_ = v___y_3022_;
v___y_3011_ = v___y_3023_;
v___y_3012_ = v___y_3025_;
v___y_3013_ = v___y_3026_;
v___y_3014_ = v___y_3029_;
v___y_3015_ = v___y_3028_;
v___y_3016_ = v___x_3032_;
goto v___jp_3009_;
}
else
{
v___y_3010_ = v___y_3022_;
v___y_3011_ = v___y_3023_;
v___y_3012_ = v___y_3025_;
v___y_3013_ = v___y_3026_;
v___y_3014_ = v___y_3029_;
v___y_3015_ = v___y_3028_;
v___y_3016_ = v___y_3027_;
goto v___jp_3009_;
}
}
v___jp_3033_:
{
uint64_t v___x_3041_; uint64_t v___x_3042_; uint8_t v___x_3043_; 
v___x_3041_ = 4ULL;
v___x_3042_ = lean_uint64_shift_right(v___y_3037_, v___x_3041_);
v___x_3043_ = lean_uint64_dec_eq(v___x_3042_, v___y_3035_);
if (v___x_3043_ == 0)
{
v___y_3021_ = v___x_3041_;
v___y_3022_ = v___y_3034_;
v___y_3023_ = v___y_3035_;
v___y_3024_ = v___y_3037_;
v___y_3025_ = v___y_3036_;
v___y_3026_ = v___y_3038_;
v___y_3027_ = v___y_3040_;
v___y_3028_ = v___y_3039_;
v___y_3029_ = v___x_3042_;
goto v___jp_3020_;
}
else
{
v___y_3021_ = v___x_3041_;
v___y_3022_ = v___y_3034_;
v___y_3023_ = v___y_3035_;
v___y_3024_ = v___y_3037_;
v___y_3025_ = v___y_3036_;
v___y_3026_ = v___y_3038_;
v___y_3027_ = v___y_3040_;
v___y_3028_ = v___y_3039_;
v___y_3029_ = v___y_3037_;
goto v___jp_3020_;
}
}
v___jp_3044_:
{
uint64_t v___x_3054_; uint8_t v___x_3055_; 
v___x_3054_ = lean_uint64_shift_right(v___y_3051_, v___y_3047_);
v___x_3055_ = lean_uint64_dec_eq(v___x_3054_, v___y_3048_);
if (v___x_3055_ == 0)
{
uint64_t v___x_3056_; 
v___x_3056_ = lean_uint64_add(v___y_3046_, v___y_3047_);
v___y_3034_ = v___y_3045_;
v___y_3035_ = v___y_3048_;
v___y_3036_ = v___y_3049_;
v___y_3037_ = v___y_3053_;
v___y_3038_ = v___y_3050_;
v___y_3039_ = v___y_3052_;
v___y_3040_ = v___x_3056_;
goto v___jp_3033_;
}
else
{
v___y_3034_ = v___y_3045_;
v___y_3035_ = v___y_3048_;
v___y_3036_ = v___y_3049_;
v___y_3037_ = v___y_3053_;
v___y_3038_ = v___y_3050_;
v___y_3039_ = v___y_3052_;
v___y_3040_ = v___y_3046_;
goto v___jp_3033_;
}
}
v___jp_3057_:
{
uint64_t v___x_3065_; uint64_t v___x_3066_; uint8_t v___x_3067_; 
v___x_3065_ = 8ULL;
v___x_3066_ = lean_uint64_shift_right(v___y_3063_, v___x_3065_);
v___x_3067_ = lean_uint64_dec_eq(v___x_3066_, v___y_3059_);
if (v___x_3067_ == 0)
{
v___y_3045_ = v___y_3058_;
v___y_3046_ = v___y_3064_;
v___y_3047_ = v___x_3065_;
v___y_3048_ = v___y_3059_;
v___y_3049_ = v___y_3060_;
v___y_3050_ = v___y_3061_;
v___y_3051_ = v___y_3063_;
v___y_3052_ = v___y_3062_;
v___y_3053_ = v___x_3066_;
goto v___jp_3044_;
}
else
{
v___y_3045_ = v___y_3058_;
v___y_3046_ = v___y_3064_;
v___y_3047_ = v___x_3065_;
v___y_3048_ = v___y_3059_;
v___y_3049_ = v___y_3060_;
v___y_3050_ = v___y_3061_;
v___y_3051_ = v___y_3063_;
v___y_3052_ = v___y_3062_;
v___y_3053_ = v___y_3063_;
goto v___jp_3044_;
}
}
v___jp_3068_:
{
uint64_t v___x_3078_; uint8_t v___x_3079_; 
v___x_3078_ = lean_uint64_shift_right(v___y_3071_, v___y_3070_);
v___x_3079_ = lean_uint64_dec_eq(v___x_3078_, v___y_3072_);
if (v___x_3079_ == 0)
{
uint64_t v___x_3080_; 
v___x_3080_ = lean_uint64_add(v___y_3075_, v___y_3070_);
v___y_3058_ = v___y_3069_;
v___y_3059_ = v___y_3072_;
v___y_3060_ = v___y_3073_;
v___y_3061_ = v___y_3074_;
v___y_3062_ = v___y_3076_;
v___y_3063_ = v___y_3077_;
v___y_3064_ = v___x_3080_;
goto v___jp_3057_;
}
else
{
v___y_3058_ = v___y_3069_;
v___y_3059_ = v___y_3072_;
v___y_3060_ = v___y_3073_;
v___y_3061_ = v___y_3074_;
v___y_3062_ = v___y_3076_;
v___y_3063_ = v___y_3077_;
v___y_3064_ = v___y_3075_;
goto v___jp_3057_;
}
}
v___jp_3081_:
{
uint64_t v___x_3089_; uint64_t v___x_3090_; uint8_t v___x_3091_; 
v___x_3089_ = 16ULL;
v___x_3090_ = lean_uint64_shift_right(v___y_3084_, v___x_3089_);
v___x_3091_ = lean_uint64_dec_eq(v___x_3090_, v___y_3083_);
if (v___x_3091_ == 0)
{
v___y_3069_ = v___y_3082_;
v___y_3070_ = v___x_3089_;
v___y_3071_ = v___y_3084_;
v___y_3072_ = v___y_3083_;
v___y_3073_ = v___y_3085_;
v___y_3074_ = v___y_3086_;
v___y_3075_ = v___y_3088_;
v___y_3076_ = v___y_3087_;
v___y_3077_ = v___x_3090_;
goto v___jp_3068_;
}
else
{
v___y_3069_ = v___y_3082_;
v___y_3070_ = v___x_3089_;
v___y_3071_ = v___y_3084_;
v___y_3072_ = v___y_3083_;
v___y_3073_ = v___y_3085_;
v___y_3074_ = v___y_3086_;
v___y_3075_ = v___y_3088_;
v___y_3076_ = v___y_3087_;
v___y_3077_ = v___y_3084_;
goto v___jp_3068_;
}
}
v___jp_3092_:
{
uint64_t v___x_3100_; uint8_t v___x_3101_; 
v___x_3100_ = lean_uint64_shift_right(v___y_3094_, v___y_3093_);
v___x_3101_ = lean_uint64_dec_eq(v___x_3100_, v___y_3095_);
if (v___x_3101_ == 0)
{
v___y_3082_ = v___y_3094_;
v___y_3083_ = v___y_3095_;
v___y_3084_ = v___y_3099_;
v___y_3085_ = v___y_3096_;
v___y_3086_ = v___y_3097_;
v___y_3087_ = v___y_3098_;
v___y_3088_ = v___y_3093_;
goto v___jp_3081_;
}
else
{
v___y_3082_ = v___y_3094_;
v___y_3083_ = v___y_3095_;
v___y_3084_ = v___y_3099_;
v___y_3085_ = v___y_3096_;
v___y_3086_ = v___y_3097_;
v___y_3087_ = v___y_3098_;
v___y_3088_ = v___y_3095_;
goto v___jp_3081_;
}
}
v___jp_3102_:
{
uint64_t v___x_3107_; uint8_t v___x_3108_; 
v___x_3107_ = 0ULL;
v___x_3108_ = lean_uint64_dec_eq(v___y_3103_, v___x_3107_);
if (v___x_3108_ == 0)
{
uint64_t v___x_3109_; uint64_t v___x_3110_; uint8_t v___x_3111_; 
v___x_3109_ = 32ULL;
v___x_3110_ = lean_uint64_shift_right(v___y_3103_, v___x_3109_);
v___x_3111_ = lean_uint64_dec_eq(v___x_3110_, v___x_3107_);
if (v___x_3111_ == 0)
{
v___y_3093_ = v___x_3109_;
v___y_3094_ = v___y_3103_;
v___y_3095_ = v___x_3107_;
v___y_3096_ = v___y_3104_;
v___y_3097_ = v___y_3105_;
v___y_3098_ = v___y_3106_;
v___y_3099_ = v___x_3110_;
goto v___jp_3092_;
}
else
{
v___y_3093_ = v___x_3109_;
v___y_3094_ = v___y_3103_;
v___y_3095_ = v___x_3107_;
v___y_3096_ = v___y_3104_;
v___y_3097_ = v___y_3105_;
v___y_3098_ = v___y_3106_;
v___y_3099_ = v___y_3103_;
goto v___jp_3092_;
}
}
else
{
if (v___y_3106_ == 0)
{
uint32_t v___x_3112_; 
v___x_3112_ = 0;
return v___x_3112_;
}
else
{
uint32_t v___x_3113_; 
v___x_3113_ = 2147483648;
return v___x_3113_;
}
}
}
v___jp_3114_:
{
uint64_t v___x_3121_; uint64_t v___x_3122_; uint64_t v___x_3123_; uint8_t v___x_3124_; 
v___x_3121_ = lean_uint64_mul(v___y_3116_, v___y_3115_);
v___x_3122_ = lean_uint64_add(v___y_3117_, v___y_3120_);
v___x_3123_ = 281474976710656ULL;
v___x_3124_ = lean_uint64_dec_lt(v___x_3121_, v___x_3123_);
if (v___x_3124_ == 0)
{
v___y_3103_ = v___x_3121_;
v___y_3104_ = v___y_3118_;
v___y_3105_ = v___x_3122_;
v___y_3106_ = v___y_3119_;
goto v___jp_3102_;
}
else
{
uint64_t v___x_3125_; uint8_t v___x_3126_; 
v___x_3125_ = 123ULL;
v___x_3126_ = lean_uint64_dec_le(v___x_3122_, v___x_3125_);
if (v___x_3126_ == 0)
{
v___y_3103_ = v___x_3121_;
v___y_3104_ = v___y_3118_;
v___y_3105_ = v___x_3122_;
v___y_3106_ = v___y_3119_;
goto v___jp_3102_;
}
else
{
uint64_t v___x_3127_; uint8_t v___x_3128_; 
v___x_3127_ = 0ULL;
v___x_3128_ = lean_uint64_dec_eq(v___x_3121_, v___x_3127_);
if (v___x_3128_ == 0)
{
uint64_t v___x_3129_; uint64_t v___x_3130_; uint8_t v___x_3131_; 
v___x_3129_ = 149ULL;
v___x_3130_ = lean_uint64_sub(v___x_3129_, v___x_3122_);
v___x_3131_ = lean_uint64_dec_eq(v___x_3130_, v___x_3127_);
if (v___x_3131_ == 0)
{
uint64_t v___x_3132_; uint8_t v___x_3133_; 
v___x_3132_ = 64ULL;
v___x_3133_ = lean_uint64_dec_lt(v___x_3130_, v___x_3132_);
if (v___x_3133_ == 0)
{
uint8_t v___x_3134_; 
v___x_3134_ = lean_uint64_dec_eq(v___x_3130_, v___x_3132_);
if (v___x_3134_ == 0)
{
v___y_2430_ = v___y_3118_;
v___y_2431_ = v___x_3127_;
v___y_2432_ = v___y_3119_;
v___y_2433_ = v___x_3127_;
goto v___jp_2429_;
}
else
{
uint64_t v___x_3135_; uint8_t v___x_3136_; 
v___x_3135_ = 9223372036854775808ULL;
v___x_3136_ = lean_uint64_dec_lt(v___x_3135_, v___x_3121_);
if (v___x_3136_ == 0)
{
v___y_2430_ = v___y_3118_;
v___y_2431_ = v___x_3127_;
v___y_2432_ = v___y_3119_;
v___y_2433_ = v___x_3127_;
goto v___jp_2429_;
}
else
{
uint64_t v___x_3137_; 
v___x_3137_ = 1ULL;
v___y_2430_ = v___y_3118_;
v___y_2431_ = v___x_3127_;
v___y_2432_ = v___y_3119_;
v___y_2433_ = v___x_3137_;
goto v___jp_2429_;
}
}
}
else
{
uint64_t v_quotient_3138_; uint64_t v___x_3139_; uint64_t v___x_3140_; uint64_t v___x_3141_; uint64_t v_remainder_3142_; uint64_t v___x_3143_; uint64_t v_half_3144_; uint8_t v___x_3145_; 
v_quotient_3138_ = lean_uint64_shift_right(v___x_3121_, v___x_3130_);
v___x_3139_ = 1ULL;
v___x_3140_ = lean_uint64_shift_left(v___x_3139_, v___x_3130_);
v___x_3141_ = lean_uint64_sub(v___x_3140_, v___x_3139_);
v_remainder_3142_ = lean_uint64_land(v___x_3121_, v___x_3141_);
v___x_3143_ = lean_uint64_sub(v___x_3130_, v___x_3139_);
v_half_3144_ = lean_uint64_shift_left(v___x_3139_, v___x_3143_);
v___x_3145_ = lean_uint64_dec_lt(v_remainder_3142_, v_half_3144_);
if (v___x_3145_ == 0)
{
uint8_t v___x_3146_; 
v___x_3146_ = lean_uint64_dec_lt(v_half_3144_, v_remainder_3142_);
if (v___x_3146_ == 0)
{
uint64_t v___x_3147_; uint8_t v___x_3148_; 
v___x_3147_ = lean_uint64_land(v_quotient_3138_, v___x_3139_);
v___x_3148_ = lean_uint64_dec_eq(v___x_3147_, v___x_3127_);
if (v___x_3148_ == 0)
{
uint64_t v___x_3149_; 
v___x_3149_ = lean_uint64_add(v_quotient_3138_, v___x_3139_);
v___y_2430_ = v___y_3118_;
v___y_2431_ = v___x_3127_;
v___y_2432_ = v___y_3119_;
v___y_2433_ = v___x_3149_;
goto v___jp_2429_;
}
else
{
v___y_2430_ = v___y_3118_;
v___y_2431_ = v___x_3127_;
v___y_2432_ = v___y_3119_;
v___y_2433_ = v_quotient_3138_;
goto v___jp_2429_;
}
}
else
{
uint64_t v___x_3150_; 
v___x_3150_ = lean_uint64_add(v_quotient_3138_, v___x_3139_);
v___y_2430_ = v___y_3118_;
v___y_2431_ = v___x_3127_;
v___y_2432_ = v___y_3119_;
v___y_2433_ = v___x_3150_;
goto v___jp_2429_;
}
}
else
{
v___y_2430_ = v___y_3118_;
v___y_2431_ = v___x_3127_;
v___y_2432_ = v___y_3119_;
v___y_2433_ = v_quotient_3138_;
goto v___jp_2429_;
}
}
}
else
{
v___y_2430_ = v___y_3118_;
v___y_2431_ = v___x_3127_;
v___y_2432_ = v___y_3119_;
v___y_2433_ = v___x_3121_;
goto v___jp_2429_;
}
}
else
{
if (v___y_3119_ == 0)
{
uint32_t v___x_3151_; 
v___x_3151_ = 0;
return v___x_3151_;
}
else
{
uint32_t v___x_3152_; 
v___x_3152_ = 2147483648;
return v___x_3152_;
}
}
}
}
}
v___jp_3153_:
{
uint32_t v___x_3158_; uint32_t v___x_3159_; uint32_t v___x_3160_; uint32_t v___x_3161_; uint32_t v___x_3162_; 
v___x_3158_ = lean_uint32_land(v___y_3155_, v___x_2870_);
v___x_3159_ = lean_uint32_shift_left(v___x_3158_, v___x_2829_);
v___x_3160_ = lean_uint32_lor(v___y_3157_, v___x_3159_);
v___x_3161_ = lean_uint32_land(v___y_3156_, v___y_3154_);
v___x_3162_ = lean_uint32_lor(v___x_3160_, v___x_3161_);
return v___x_3162_;
}
v___jp_3163_:
{
if (v___y_3166_ == 0)
{
uint32_t v___x_3168_; 
v___x_3168_ = 0;
v___y_3154_ = v___y_3164_;
v___y_3155_ = v___y_3165_;
v___y_3156_ = v___y_3167_;
v___y_3157_ = v___x_3168_;
goto v___jp_3153_;
}
else
{
uint32_t v___x_3169_; 
v___x_3169_ = 2147483648;
v___y_3154_ = v___y_3164_;
v___y_3155_ = v___y_3165_;
v___y_3156_ = v___y_3167_;
v___y_3157_ = v___x_3169_;
goto v___jp_3153_;
}
}
v___jp_3170_:
{
uint64_t v___x_3176_; uint64_t v_encodedExponent_3177_; uint32_t v___x_3178_; uint64_t v___x_3179_; uint8_t v___x_3180_; 
v___x_3176_ = 171ULL;
v_encodedExponent_3177_ = lean_uint64_sub(v___y_3173_, v___x_3176_);
v___x_3178_ = lean_uint64_to_uint32(v_encodedExponent_3177_);
v___x_3179_ = 8388608ULL;
v___x_3180_ = lean_uint64_dec_lt(v___y_3175_, v___x_3179_);
if (v___x_3180_ == 0)
{
uint64_t v___x_3181_; uint32_t v___x_3182_; 
v___x_3181_ = lean_uint64_sub(v___y_3175_, v___x_3179_);
v___x_3182_ = lean_uint64_to_uint32(v___x_3181_);
v___y_3164_ = v___y_3171_;
v___y_3165_ = v___x_3178_;
v___y_3166_ = v___y_3174_;
v___y_3167_ = v___x_3182_;
goto v___jp_3163_;
}
else
{
uint32_t v___x_3183_; 
v___x_3183_ = lean_uint64_to_uint32(v___y_3172_);
v___y_3164_ = v___y_3171_;
v___y_3165_ = v___x_3178_;
v___y_3166_ = v___y_3174_;
v___y_3167_ = v___x_3183_;
goto v___jp_3163_;
}
}
v___jp_3184_:
{
uint64_t v___x_3191_; uint8_t v___x_3192_; 
v___x_3191_ = 425ULL;
v___x_3192_ = lean_uint64_dec_lt(v___x_3191_, v___y_3190_);
if (v___x_3192_ == 0)
{
if (v___y_3185_ == 0)
{
v___y_3171_ = v___y_3186_;
v___y_3172_ = v___y_3187_;
v___y_3173_ = v___y_3190_;
v___y_3174_ = v___y_3189_;
v___y_3175_ = v___y_3188_;
goto v___jp_3170_;
}
else
{
uint64_t v___x_3193_; 
v___x_3193_ = 8388608ULL;
v___y_3171_ = v___y_3186_;
v___y_3172_ = v___y_3187_;
v___y_3173_ = v___y_3190_;
v___y_3174_ = v___y_3189_;
v___y_3175_ = v___x_3193_;
goto v___jp_3170_;
}
}
else
{
if (v___y_3189_ == 0)
{
uint32_t v___x_3194_; 
v___x_3194_ = 2139095040;
return v___x_3194_;
}
else
{
uint32_t v___x_3195_; 
v___x_3195_ = 4286578688;
return v___x_3195_;
}
}
}
v___jp_3196_:
{
uint64_t v___x_3202_; uint8_t v_carry_3203_; 
v___x_3202_ = 16777216ULL;
v_carry_3203_ = lean_uint64_dec_eq(v___y_3201_, v___x_3202_);
if (v_carry_3203_ == 0)
{
v___y_3185_ = v_carry_3203_;
v___y_3186_ = v___y_3197_;
v___y_3187_ = v___y_3198_;
v___y_3188_ = v___y_3201_;
v___y_3189_ = v___y_3199_;
v___y_3190_ = v___y_3200_;
goto v___jp_3184_;
}
else
{
uint64_t v___x_3204_; uint64_t v___x_3205_; 
v___x_3204_ = 1ULL;
v___x_3205_ = lean_uint64_add(v___y_3200_, v___x_3204_);
v___y_3185_ = v_carry_3203_;
v___y_3186_ = v___y_3197_;
v___y_3187_ = v___y_3198_;
v___y_3188_ = v___y_3201_;
v___y_3189_ = v___y_3199_;
v___y_3190_ = v___x_3205_;
goto v___jp_3184_;
}
}
v___jp_3206_:
{
uint64_t v_position_3213_; uint64_t v___x_3214_; uint8_t v___x_3215_; 
v_position_3213_ = lean_uint64_add(v___y_3212_, v___y_3210_);
v___x_3214_ = 172ULL;
v___x_3215_ = lean_uint64_dec_lt(v_position_3213_, v___x_3214_);
if (v___x_3215_ == 0)
{
uint64_t v___x_3216_; uint8_t v___x_3217_; 
v___x_3216_ = 23ULL;
v___x_3217_ = lean_uint64_dec_lt(v___y_3212_, v___x_3216_);
if (v___x_3217_ == 0)
{
uint64_t v___x_3218_; uint8_t v___x_3219_; 
v___x_3218_ = lean_uint64_sub(v___y_3212_, v___x_3216_);
v___x_3219_ = lean_uint64_dec_eq(v___x_3218_, v___y_3209_);
if (v___x_3219_ == 0)
{
uint64_t v___x_3220_; uint8_t v___x_3221_; 
v___x_3220_ = 64ULL;
v___x_3221_ = lean_uint64_dec_lt(v___x_3218_, v___x_3220_);
if (v___x_3221_ == 0)
{
uint8_t v___x_3222_; 
v___x_3222_ = lean_uint64_dec_eq(v___x_3218_, v___x_3220_);
if (v___x_3222_ == 0)
{
v___y_3197_ = v___y_3208_;
v___y_3198_ = v___y_3209_;
v___y_3199_ = v___y_3211_;
v___y_3200_ = v_position_3213_;
v___y_3201_ = v___y_3209_;
goto v___jp_3196_;
}
else
{
uint64_t v___x_3223_; uint8_t v___x_3224_; 
v___x_3223_ = 9223372036854775808ULL;
v___x_3224_ = lean_uint64_dec_lt(v___x_3223_, v___y_3207_);
if (v___x_3224_ == 0)
{
v___y_3197_ = v___y_3208_;
v___y_3198_ = v___y_3209_;
v___y_3199_ = v___y_3211_;
v___y_3200_ = v_position_3213_;
v___y_3201_ = v___y_3209_;
goto v___jp_3196_;
}
else
{
uint64_t v___x_3225_; 
v___x_3225_ = 1ULL;
v___y_3197_ = v___y_3208_;
v___y_3198_ = v___y_3209_;
v___y_3199_ = v___y_3211_;
v___y_3200_ = v_position_3213_;
v___y_3201_ = v___x_3225_;
goto v___jp_3196_;
}
}
}
else
{
uint64_t v_quotient_3226_; uint64_t v___x_3227_; uint64_t v___x_3228_; uint64_t v___x_3229_; uint64_t v_remainder_3230_; uint64_t v___x_3231_; uint64_t v_half_3232_; uint8_t v___x_3233_; 
v_quotient_3226_ = lean_uint64_shift_right(v___y_3207_, v___x_3218_);
v___x_3227_ = 1ULL;
v___x_3228_ = lean_uint64_shift_left(v___x_3227_, v___x_3218_);
v___x_3229_ = lean_uint64_sub(v___x_3228_, v___x_3227_);
v_remainder_3230_ = lean_uint64_land(v___y_3207_, v___x_3229_);
v___x_3231_ = lean_uint64_sub(v___x_3218_, v___x_3227_);
v_half_3232_ = lean_uint64_shift_left(v___x_3227_, v___x_3231_);
v___x_3233_ = lean_uint64_dec_lt(v_remainder_3230_, v_half_3232_);
if (v___x_3233_ == 0)
{
uint8_t v___x_3234_; 
v___x_3234_ = lean_uint64_dec_lt(v_half_3232_, v_remainder_3230_);
if (v___x_3234_ == 0)
{
uint64_t v___x_3235_; uint8_t v___x_3236_; 
v___x_3235_ = lean_uint64_land(v_quotient_3226_, v___x_3227_);
v___x_3236_ = lean_uint64_dec_eq(v___x_3235_, v___y_3209_);
if (v___x_3236_ == 0)
{
uint64_t v___x_3237_; 
v___x_3237_ = lean_uint64_add(v_quotient_3226_, v___x_3227_);
v___y_3197_ = v___y_3208_;
v___y_3198_ = v___y_3209_;
v___y_3199_ = v___y_3211_;
v___y_3200_ = v_position_3213_;
v___y_3201_ = v___x_3237_;
goto v___jp_3196_;
}
else
{
v___y_3197_ = v___y_3208_;
v___y_3198_ = v___y_3209_;
v___y_3199_ = v___y_3211_;
v___y_3200_ = v_position_3213_;
v___y_3201_ = v_quotient_3226_;
goto v___jp_3196_;
}
}
else
{
uint64_t v___x_3238_; 
v___x_3238_ = lean_uint64_add(v_quotient_3226_, v___x_3227_);
v___y_3197_ = v___y_3208_;
v___y_3198_ = v___y_3209_;
v___y_3199_ = v___y_3211_;
v___y_3200_ = v_position_3213_;
v___y_3201_ = v___x_3238_;
goto v___jp_3196_;
}
}
else
{
v___y_3197_ = v___y_3208_;
v___y_3198_ = v___y_3209_;
v___y_3199_ = v___y_3211_;
v___y_3200_ = v_position_3213_;
v___y_3201_ = v_quotient_3226_;
goto v___jp_3196_;
}
}
}
else
{
v___y_3197_ = v___y_3208_;
v___y_3198_ = v___y_3209_;
v___y_3199_ = v___y_3211_;
v___y_3200_ = v_position_3213_;
v___y_3201_ = v___y_3207_;
goto v___jp_3196_;
}
}
else
{
uint64_t v___x_3239_; uint64_t v___x_3240_; 
v___x_3239_ = lean_uint64_sub(v___x_3216_, v___y_3212_);
v___x_3240_ = lean_uint64_shift_left(v___y_3207_, v___x_3239_);
v___y_3197_ = v___y_3208_;
v___y_3198_ = v___y_3209_;
v___y_3199_ = v___y_3211_;
v___y_3200_ = v_position_3213_;
v___y_3201_ = v___x_3240_;
goto v___jp_3196_;
}
}
else
{
uint64_t v___x_3241_; uint8_t v___x_3242_; 
v___x_3241_ = 149ULL;
v___x_3242_ = lean_uint64_dec_lt(v___y_3210_, v___x_3241_);
if (v___x_3242_ == 0)
{
uint64_t v___x_3243_; uint64_t v___x_3244_; 
v___x_3243_ = lean_uint64_sub(v___y_3210_, v___x_3241_);
v___x_3244_ = lean_uint64_shift_left(v___y_3207_, v___x_3243_);
v___y_2554_ = v___y_3208_;
v___y_2555_ = v___y_3209_;
v___y_2556_ = v___y_3211_;
v___y_2557_ = v___x_3244_;
goto v___jp_2553_;
}
else
{
uint64_t v___x_3245_; uint8_t v___x_3246_; 
v___x_3245_ = lean_uint64_sub(v___x_3241_, v___y_3210_);
v___x_3246_ = lean_uint64_dec_eq(v___x_3245_, v___y_3209_);
if (v___x_3246_ == 0)
{
uint64_t v___x_3247_; uint8_t v___x_3248_; 
v___x_3247_ = 64ULL;
v___x_3248_ = lean_uint64_dec_lt(v___x_3245_, v___x_3247_);
if (v___x_3248_ == 0)
{
uint8_t v___x_3249_; 
v___x_3249_ = lean_uint64_dec_eq(v___x_3245_, v___x_3247_);
if (v___x_3249_ == 0)
{
v___y_2554_ = v___y_3208_;
v___y_2555_ = v___y_3209_;
v___y_2556_ = v___y_3211_;
v___y_2557_ = v___y_3209_;
goto v___jp_2553_;
}
else
{
uint64_t v___x_3250_; uint8_t v___x_3251_; 
v___x_3250_ = 9223372036854775808ULL;
v___x_3251_ = lean_uint64_dec_lt(v___x_3250_, v___y_3207_);
if (v___x_3251_ == 0)
{
v___y_2554_ = v___y_3208_;
v___y_2555_ = v___y_3209_;
v___y_2556_ = v___y_3211_;
v___y_2557_ = v___y_3209_;
goto v___jp_2553_;
}
else
{
uint64_t v___x_3252_; 
v___x_3252_ = 1ULL;
v___y_2554_ = v___y_3208_;
v___y_2555_ = v___y_3209_;
v___y_2556_ = v___y_3211_;
v___y_2557_ = v___x_3252_;
goto v___jp_2553_;
}
}
}
else
{
uint64_t v_quotient_3253_; uint64_t v___x_3254_; uint64_t v___x_3255_; uint64_t v___x_3256_; uint64_t v_remainder_3257_; uint64_t v___x_3258_; uint64_t v_half_3259_; uint8_t v___x_3260_; 
v_quotient_3253_ = lean_uint64_shift_right(v___y_3207_, v___x_3245_);
v___x_3254_ = 1ULL;
v___x_3255_ = lean_uint64_shift_left(v___x_3254_, v___x_3245_);
v___x_3256_ = lean_uint64_sub(v___x_3255_, v___x_3254_);
v_remainder_3257_ = lean_uint64_land(v___y_3207_, v___x_3256_);
v___x_3258_ = lean_uint64_sub(v___x_3245_, v___x_3254_);
v_half_3259_ = lean_uint64_shift_left(v___x_3254_, v___x_3258_);
v___x_3260_ = lean_uint64_dec_lt(v_remainder_3257_, v_half_3259_);
if (v___x_3260_ == 0)
{
uint8_t v___x_3261_; 
v___x_3261_ = lean_uint64_dec_lt(v_half_3259_, v_remainder_3257_);
if (v___x_3261_ == 0)
{
uint64_t v___x_3262_; uint8_t v___x_3263_; 
v___x_3262_ = lean_uint64_land(v_quotient_3253_, v___x_3254_);
v___x_3263_ = lean_uint64_dec_eq(v___x_3262_, v___y_3209_);
if (v___x_3263_ == 0)
{
uint64_t v___x_3264_; 
v___x_3264_ = lean_uint64_add(v_quotient_3253_, v___x_3254_);
v___y_2554_ = v___y_3208_;
v___y_2555_ = v___y_3209_;
v___y_2556_ = v___y_3211_;
v___y_2557_ = v___x_3264_;
goto v___jp_2553_;
}
else
{
v___y_2554_ = v___y_3208_;
v___y_2555_ = v___y_3209_;
v___y_2556_ = v___y_3211_;
v___y_2557_ = v_quotient_3253_;
goto v___jp_2553_;
}
}
else
{
uint64_t v___x_3265_; 
v___x_3265_ = lean_uint64_add(v_quotient_3253_, v___x_3254_);
v___y_2554_ = v___y_3208_;
v___y_2555_ = v___y_3209_;
v___y_2556_ = v___y_3211_;
v___y_2557_ = v___x_3265_;
goto v___jp_2553_;
}
}
else
{
v___y_2554_ = v___y_3208_;
v___y_2555_ = v___y_3209_;
v___y_2556_ = v___y_3211_;
v___y_2557_ = v_quotient_3253_;
goto v___jp_2553_;
}
}
}
else
{
v___y_2554_ = v___y_3208_;
v___y_2555_ = v___y_3209_;
v___y_2556_ = v___y_3211_;
v___y_2557_ = v___y_3207_;
goto v___jp_2553_;
}
}
}
}
v___jp_3266_:
{
uint64_t v___x_3274_; uint64_t v___x_3275_; uint8_t v___x_3276_; 
v___x_3274_ = 1ULL;
v___x_3275_ = lean_uint64_shift_right(v___y_3267_, v___x_3274_);
v___x_3276_ = lean_uint64_dec_eq(v___x_3275_, v___y_3270_);
if (v___x_3276_ == 0)
{
uint64_t v___x_3277_; 
v___x_3277_ = lean_uint64_add(v___y_3273_, v___x_3274_);
v___y_3207_ = v___y_3268_;
v___y_3208_ = v___y_3269_;
v___y_3209_ = v___y_3270_;
v___y_3210_ = v___y_3271_;
v___y_3211_ = v___y_3272_;
v___y_3212_ = v___x_3277_;
goto v___jp_3206_;
}
else
{
v___y_3207_ = v___y_3268_;
v___y_3208_ = v___y_3269_;
v___y_3209_ = v___y_3270_;
v___y_3210_ = v___y_3271_;
v___y_3211_ = v___y_3272_;
v___y_3212_ = v___y_3273_;
goto v___jp_3206_;
}
}
v___jp_3278_:
{
uint64_t v___x_3288_; uint8_t v___x_3289_; 
v___x_3288_ = lean_uint64_shift_right(v___y_3279_, v___y_3282_);
v___x_3289_ = lean_uint64_dec_eq(v___x_3288_, v___y_3284_);
if (v___x_3289_ == 0)
{
uint64_t v___x_3290_; 
v___x_3290_ = lean_uint64_add(v___y_3281_, v___y_3282_);
v___y_3267_ = v___y_3287_;
v___y_3268_ = v___y_3280_;
v___y_3269_ = v___y_3283_;
v___y_3270_ = v___y_3284_;
v___y_3271_ = v___y_3285_;
v___y_3272_ = v___y_3286_;
v___y_3273_ = v___x_3290_;
goto v___jp_3266_;
}
else
{
v___y_3267_ = v___y_3287_;
v___y_3268_ = v___y_3280_;
v___y_3269_ = v___y_3283_;
v___y_3270_ = v___y_3284_;
v___y_3271_ = v___y_3285_;
v___y_3272_ = v___y_3286_;
v___y_3273_ = v___y_3281_;
goto v___jp_3266_;
}
}
v___jp_3291_:
{
uint64_t v___x_3299_; uint64_t v___x_3300_; uint8_t v___x_3301_; 
v___x_3299_ = 2ULL;
v___x_3300_ = lean_uint64_shift_right(v___y_3292_, v___x_3299_);
v___x_3301_ = lean_uint64_dec_eq(v___x_3300_, v___y_3295_);
if (v___x_3301_ == 0)
{
v___y_3279_ = v___y_3292_;
v___y_3280_ = v___y_3293_;
v___y_3281_ = v___y_3298_;
v___y_3282_ = v___x_3299_;
v___y_3283_ = v___y_3294_;
v___y_3284_ = v___y_3295_;
v___y_3285_ = v___y_3296_;
v___y_3286_ = v___y_3297_;
v___y_3287_ = v___x_3300_;
goto v___jp_3278_;
}
else
{
v___y_3279_ = v___y_3292_;
v___y_3280_ = v___y_3293_;
v___y_3281_ = v___y_3298_;
v___y_3282_ = v___x_3299_;
v___y_3283_ = v___y_3294_;
v___y_3284_ = v___y_3295_;
v___y_3285_ = v___y_3296_;
v___y_3286_ = v___y_3297_;
v___y_3287_ = v___y_3292_;
goto v___jp_3278_;
}
}
v___jp_3302_:
{
uint64_t v___x_3312_; uint8_t v___x_3313_; 
v___x_3312_ = lean_uint64_shift_right(v___y_3303_, v___y_3304_);
v___x_3313_ = lean_uint64_dec_eq(v___x_3312_, v___y_3308_);
if (v___x_3313_ == 0)
{
uint64_t v___x_3314_; 
v___x_3314_ = lean_uint64_add(v___y_3305_, v___y_3304_);
v___y_3292_ = v___y_3311_;
v___y_3293_ = v___y_3306_;
v___y_3294_ = v___y_3307_;
v___y_3295_ = v___y_3308_;
v___y_3296_ = v___y_3309_;
v___y_3297_ = v___y_3310_;
v___y_3298_ = v___x_3314_;
goto v___jp_3291_;
}
else
{
v___y_3292_ = v___y_3311_;
v___y_3293_ = v___y_3306_;
v___y_3294_ = v___y_3307_;
v___y_3295_ = v___y_3308_;
v___y_3296_ = v___y_3309_;
v___y_3297_ = v___y_3310_;
v___y_3298_ = v___y_3305_;
goto v___jp_3291_;
}
}
v___jp_3315_:
{
uint64_t v___x_3323_; uint64_t v___x_3324_; uint8_t v___x_3325_; 
v___x_3323_ = 4ULL;
v___x_3324_ = lean_uint64_shift_right(v___y_3316_, v___x_3323_);
v___x_3325_ = lean_uint64_dec_eq(v___x_3324_, v___y_3319_);
if (v___x_3325_ == 0)
{
v___y_3303_ = v___y_3316_;
v___y_3304_ = v___x_3323_;
v___y_3305_ = v___y_3322_;
v___y_3306_ = v___y_3317_;
v___y_3307_ = v___y_3318_;
v___y_3308_ = v___y_3319_;
v___y_3309_ = v___y_3320_;
v___y_3310_ = v___y_3321_;
v___y_3311_ = v___x_3324_;
goto v___jp_3302_;
}
else
{
v___y_3303_ = v___y_3316_;
v___y_3304_ = v___x_3323_;
v___y_3305_ = v___y_3322_;
v___y_3306_ = v___y_3317_;
v___y_3307_ = v___y_3318_;
v___y_3308_ = v___y_3319_;
v___y_3309_ = v___y_3320_;
v___y_3310_ = v___y_3321_;
v___y_3311_ = v___y_3316_;
goto v___jp_3302_;
}
}
v___jp_3326_:
{
uint64_t v___x_3336_; uint8_t v___x_3337_; 
v___x_3336_ = lean_uint64_shift_right(v___y_3334_, v___y_3332_);
v___x_3337_ = lean_uint64_dec_eq(v___x_3336_, v___y_3329_);
if (v___x_3337_ == 0)
{
uint64_t v___x_3338_; 
v___x_3338_ = lean_uint64_add(v___y_3331_, v___y_3332_);
v___y_3316_ = v___y_3335_;
v___y_3317_ = v___y_3327_;
v___y_3318_ = v___y_3328_;
v___y_3319_ = v___y_3329_;
v___y_3320_ = v___y_3330_;
v___y_3321_ = v___y_3333_;
v___y_3322_ = v___x_3338_;
goto v___jp_3315_;
}
else
{
v___y_3316_ = v___y_3335_;
v___y_3317_ = v___y_3327_;
v___y_3318_ = v___y_3328_;
v___y_3319_ = v___y_3329_;
v___y_3320_ = v___y_3330_;
v___y_3321_ = v___y_3333_;
v___y_3322_ = v___y_3331_;
goto v___jp_3315_;
}
}
v___jp_3339_:
{
uint64_t v___x_3347_; uint64_t v___x_3348_; uint8_t v___x_3349_; 
v___x_3347_ = 8ULL;
v___x_3348_ = lean_uint64_shift_right(v___y_3345_, v___x_3347_);
v___x_3349_ = lean_uint64_dec_eq(v___x_3348_, v___y_3342_);
if (v___x_3349_ == 0)
{
v___y_3327_ = v___y_3340_;
v___y_3328_ = v___y_3341_;
v___y_3329_ = v___y_3342_;
v___y_3330_ = v___y_3343_;
v___y_3331_ = v___y_3346_;
v___y_3332_ = v___x_3347_;
v___y_3333_ = v___y_3344_;
v___y_3334_ = v___y_3345_;
v___y_3335_ = v___x_3348_;
goto v___jp_3326_;
}
else
{
v___y_3327_ = v___y_3340_;
v___y_3328_ = v___y_3341_;
v___y_3329_ = v___y_3342_;
v___y_3330_ = v___y_3343_;
v___y_3331_ = v___y_3346_;
v___y_3332_ = v___x_3347_;
v___y_3333_ = v___y_3344_;
v___y_3334_ = v___y_3345_;
v___y_3335_ = v___y_3345_;
goto v___jp_3326_;
}
}
v___jp_3350_:
{
uint64_t v___x_3360_; uint8_t v___x_3361_; 
v___x_3360_ = lean_uint64_shift_right(v___y_3357_, v___y_3351_);
v___x_3361_ = lean_uint64_dec_eq(v___x_3360_, v___y_3354_);
if (v___x_3361_ == 0)
{
uint64_t v___x_3362_; 
v___x_3362_ = lean_uint64_add(v___y_3355_, v___y_3351_);
v___y_3340_ = v___y_3352_;
v___y_3341_ = v___y_3353_;
v___y_3342_ = v___y_3354_;
v___y_3343_ = v___y_3356_;
v___y_3344_ = v___y_3358_;
v___y_3345_ = v___y_3359_;
v___y_3346_ = v___x_3362_;
goto v___jp_3339_;
}
else
{
v___y_3340_ = v___y_3352_;
v___y_3341_ = v___y_3353_;
v___y_3342_ = v___y_3354_;
v___y_3343_ = v___y_3356_;
v___y_3344_ = v___y_3358_;
v___y_3345_ = v___y_3359_;
v___y_3346_ = v___y_3355_;
goto v___jp_3339_;
}
}
v___jp_3363_:
{
uint64_t v___x_3371_; uint64_t v___x_3372_; uint8_t v___x_3373_; 
v___x_3371_ = 16ULL;
v___x_3372_ = lean_uint64_shift_right(v___y_3368_, v___x_3371_);
v___x_3373_ = lean_uint64_dec_eq(v___x_3372_, v___y_3366_);
if (v___x_3373_ == 0)
{
v___y_3351_ = v___x_3371_;
v___y_3352_ = v___y_3364_;
v___y_3353_ = v___y_3365_;
v___y_3354_ = v___y_3366_;
v___y_3355_ = v___y_3370_;
v___y_3356_ = v___y_3367_;
v___y_3357_ = v___y_3368_;
v___y_3358_ = v___y_3369_;
v___y_3359_ = v___x_3372_;
goto v___jp_3350_;
}
else
{
v___y_3351_ = v___x_3371_;
v___y_3352_ = v___y_3364_;
v___y_3353_ = v___y_3365_;
v___y_3354_ = v___y_3366_;
v___y_3355_ = v___y_3370_;
v___y_3356_ = v___y_3367_;
v___y_3357_ = v___y_3368_;
v___y_3358_ = v___y_3369_;
v___y_3359_ = v___y_3368_;
goto v___jp_3350_;
}
}
v___jp_3374_:
{
uint64_t v___x_3382_; uint8_t v___x_3383_; 
v___x_3382_ = lean_uint64_shift_right(v___y_3375_, v___y_3377_);
v___x_3383_ = lean_uint64_dec_eq(v___x_3382_, v___y_3378_);
if (v___x_3383_ == 0)
{
v___y_3364_ = v___y_3375_;
v___y_3365_ = v___y_3376_;
v___y_3366_ = v___y_3378_;
v___y_3367_ = v___y_3379_;
v___y_3368_ = v___y_3381_;
v___y_3369_ = v___y_3380_;
v___y_3370_ = v___y_3377_;
goto v___jp_3363_;
}
else
{
v___y_3364_ = v___y_3375_;
v___y_3365_ = v___y_3376_;
v___y_3366_ = v___y_3378_;
v___y_3367_ = v___y_3379_;
v___y_3368_ = v___y_3381_;
v___y_3369_ = v___y_3380_;
v___y_3370_ = v___y_3378_;
goto v___jp_3363_;
}
}
v___jp_3384_:
{
uint64_t v___x_3389_; uint8_t v___x_3390_; 
v___x_3389_ = 0ULL;
v___x_3390_ = lean_uint64_dec_eq(v___y_3385_, v___x_3389_);
if (v___x_3390_ == 0)
{
uint64_t v___x_3391_; uint64_t v___x_3392_; uint8_t v___x_3393_; 
v___x_3391_ = 32ULL;
v___x_3392_ = lean_uint64_shift_right(v___y_3385_, v___x_3391_);
v___x_3393_ = lean_uint64_dec_eq(v___x_3392_, v___x_3389_);
if (v___x_3393_ == 0)
{
v___y_3375_ = v___y_3385_;
v___y_3376_ = v___y_3386_;
v___y_3377_ = v___x_3391_;
v___y_3378_ = v___x_3389_;
v___y_3379_ = v___y_3387_;
v___y_3380_ = v___y_3388_;
v___y_3381_ = v___x_3392_;
goto v___jp_3374_;
}
else
{
v___y_3375_ = v___y_3385_;
v___y_3376_ = v___y_3386_;
v___y_3377_ = v___x_3391_;
v___y_3378_ = v___x_3389_;
v___y_3379_ = v___y_3387_;
v___y_3380_ = v___y_3388_;
v___y_3381_ = v___y_3385_;
goto v___jp_3374_;
}
}
else
{
if (v___y_3388_ == 0)
{
uint32_t v___x_3394_; 
v___x_3394_ = 0;
return v___x_3394_;
}
else
{
uint32_t v___x_3395_; 
v___x_3395_ = 2147483648;
return v___x_3395_;
}
}
}
v___jp_3396_:
{
uint64_t v___x_3403_; uint64_t v___x_3404_; uint64_t v___x_3405_; uint8_t v___x_3406_; 
v___x_3403_ = lean_uint64_mul(v___y_3398_, v___y_3397_);
v___x_3404_ = lean_uint64_add(v___y_3399_, v___y_3402_);
v___x_3405_ = 281474976710656ULL;
v___x_3406_ = lean_uint64_dec_lt(v___x_3403_, v___x_3405_);
if (v___x_3406_ == 0)
{
v___y_3385_ = v___x_3403_;
v___y_3386_ = v___y_3400_;
v___y_3387_ = v___x_3404_;
v___y_3388_ = v___y_3401_;
goto v___jp_3384_;
}
else
{
uint64_t v___x_3407_; uint8_t v___x_3408_; 
v___x_3407_ = 123ULL;
v___x_3408_ = lean_uint64_dec_le(v___x_3404_, v___x_3407_);
if (v___x_3408_ == 0)
{
v___y_3385_ = v___x_3403_;
v___y_3386_ = v___y_3400_;
v___y_3387_ = v___x_3404_;
v___y_3388_ = v___y_3401_;
goto v___jp_3384_;
}
else
{
uint64_t v___x_3409_; uint8_t v___x_3410_; 
v___x_3409_ = 0ULL;
v___x_3410_ = lean_uint64_dec_eq(v___x_3403_, v___x_3409_);
if (v___x_3410_ == 0)
{
uint64_t v___x_3411_; uint64_t v___x_3412_; uint8_t v___x_3413_; 
v___x_3411_ = 149ULL;
v___x_3412_ = lean_uint64_sub(v___x_3411_, v___x_3404_);
v___x_3413_ = lean_uint64_dec_eq(v___x_3412_, v___x_3409_);
if (v___x_3413_ == 0)
{
uint64_t v___x_3414_; uint8_t v___x_3415_; 
v___x_3414_ = 64ULL;
v___x_3415_ = lean_uint64_dec_lt(v___x_3412_, v___x_3414_);
if (v___x_3415_ == 0)
{
uint8_t v___x_3416_; 
v___x_3416_ = lean_uint64_dec_eq(v___x_3412_, v___x_3414_);
if (v___x_3416_ == 0)
{
v___y_2575_ = v___x_3409_;
v___y_2576_ = v___y_3400_;
v___y_2577_ = v___y_3401_;
v___y_2578_ = v___x_3409_;
goto v___jp_2574_;
}
else
{
uint64_t v___x_3417_; uint8_t v___x_3418_; 
v___x_3417_ = 9223372036854775808ULL;
v___x_3418_ = lean_uint64_dec_lt(v___x_3417_, v___x_3403_);
if (v___x_3418_ == 0)
{
v___y_2575_ = v___x_3409_;
v___y_2576_ = v___y_3400_;
v___y_2577_ = v___y_3401_;
v___y_2578_ = v___x_3409_;
goto v___jp_2574_;
}
else
{
uint64_t v___x_3419_; 
v___x_3419_ = 1ULL;
v___y_2575_ = v___x_3409_;
v___y_2576_ = v___y_3400_;
v___y_2577_ = v___y_3401_;
v___y_2578_ = v___x_3419_;
goto v___jp_2574_;
}
}
}
else
{
uint64_t v_quotient_3420_; uint64_t v___x_3421_; uint64_t v___x_3422_; uint64_t v___x_3423_; uint64_t v_remainder_3424_; uint64_t v___x_3425_; uint64_t v_half_3426_; uint8_t v___x_3427_; 
v_quotient_3420_ = lean_uint64_shift_right(v___x_3403_, v___x_3412_);
v___x_3421_ = 1ULL;
v___x_3422_ = lean_uint64_shift_left(v___x_3421_, v___x_3412_);
v___x_3423_ = lean_uint64_sub(v___x_3422_, v___x_3421_);
v_remainder_3424_ = lean_uint64_land(v___x_3403_, v___x_3423_);
v___x_3425_ = lean_uint64_sub(v___x_3412_, v___x_3421_);
v_half_3426_ = lean_uint64_shift_left(v___x_3421_, v___x_3425_);
v___x_3427_ = lean_uint64_dec_lt(v_remainder_3424_, v_half_3426_);
if (v___x_3427_ == 0)
{
uint8_t v___x_3428_; 
v___x_3428_ = lean_uint64_dec_lt(v_half_3426_, v_remainder_3424_);
if (v___x_3428_ == 0)
{
uint64_t v___x_3429_; uint8_t v___x_3430_; 
v___x_3429_ = lean_uint64_land(v_quotient_3420_, v___x_3421_);
v___x_3430_ = lean_uint64_dec_eq(v___x_3429_, v___x_3409_);
if (v___x_3430_ == 0)
{
uint64_t v___x_3431_; 
v___x_3431_ = lean_uint64_add(v_quotient_3420_, v___x_3421_);
v___y_2575_ = v___x_3409_;
v___y_2576_ = v___y_3400_;
v___y_2577_ = v___y_3401_;
v___y_2578_ = v___x_3431_;
goto v___jp_2574_;
}
else
{
v___y_2575_ = v___x_3409_;
v___y_2576_ = v___y_3400_;
v___y_2577_ = v___y_3401_;
v___y_2578_ = v_quotient_3420_;
goto v___jp_2574_;
}
}
else
{
uint64_t v___x_3432_; 
v___x_3432_ = lean_uint64_add(v_quotient_3420_, v___x_3421_);
v___y_2575_ = v___x_3409_;
v___y_2576_ = v___y_3400_;
v___y_2577_ = v___y_3401_;
v___y_2578_ = v___x_3432_;
goto v___jp_2574_;
}
}
else
{
v___y_2575_ = v___x_3409_;
v___y_2576_ = v___y_3400_;
v___y_2577_ = v___y_3401_;
v___y_2578_ = v_quotient_3420_;
goto v___jp_2574_;
}
}
}
else
{
v___y_2575_ = v___x_3409_;
v___y_2576_ = v___y_3400_;
v___y_2577_ = v___y_3401_;
v___y_2578_ = v___x_3403_;
goto v___jp_2574_;
}
}
else
{
if (v___y_3401_ == 0)
{
uint32_t v___x_3433_; 
v___x_3433_ = 0;
return v___x_3433_;
}
else
{
uint32_t v___x_3434_; 
v___x_3434_ = 2147483648;
return v___x_3434_;
}
}
}
}
}
v___jp_3435_:
{
uint32_t v___x_3440_; uint32_t v___x_3441_; uint32_t v___x_3442_; uint32_t v___x_3443_; uint32_t v___x_3444_; 
v___x_3440_ = lean_uint32_land(v___y_3437_, v___x_2870_);
v___x_3441_ = lean_uint32_shift_left(v___x_3440_, v___x_2829_);
v___x_3442_ = lean_uint32_lor(v___y_3439_, v___x_3441_);
v___x_3443_ = lean_uint32_land(v___y_3438_, v___y_3436_);
v___x_3444_ = lean_uint32_lor(v___x_3442_, v___x_3443_);
return v___x_3444_;
}
v___jp_3445_:
{
if (v___y_3446_ == 0)
{
uint32_t v___x_3450_; 
v___x_3450_ = 0;
v___y_3436_ = v___y_3448_;
v___y_3437_ = v___y_3447_;
v___y_3438_ = v___y_3449_;
v___y_3439_ = v___x_3450_;
goto v___jp_3435_;
}
else
{
uint32_t v___x_3451_; 
v___x_3451_ = 2147483648;
v___y_3436_ = v___y_3448_;
v___y_3437_ = v___y_3447_;
v___y_3438_ = v___y_3449_;
v___y_3439_ = v___x_3451_;
goto v___jp_3435_;
}
}
v___jp_3452_:
{
uint64_t v___x_3458_; uint64_t v_encodedExponent_3459_; uint32_t v___x_3460_; uint64_t v___x_3461_; uint8_t v___x_3462_; 
v___x_3458_ = 171ULL;
v_encodedExponent_3459_ = lean_uint64_sub(v___y_3456_, v___x_3458_);
v___x_3460_ = lean_uint64_to_uint32(v_encodedExponent_3459_);
v___x_3461_ = 8388608ULL;
v___x_3462_ = lean_uint64_dec_lt(v___y_3457_, v___x_3461_);
if (v___x_3462_ == 0)
{
uint64_t v___x_3463_; uint32_t v___x_3464_; 
v___x_3463_ = lean_uint64_sub(v___y_3457_, v___x_3461_);
v___x_3464_ = lean_uint64_to_uint32(v___x_3463_);
v___y_3446_ = v___y_3453_;
v___y_3447_ = v___x_3460_;
v___y_3448_ = v___y_3454_;
v___y_3449_ = v___x_3464_;
goto v___jp_3445_;
}
else
{
uint32_t v___x_3465_; 
v___x_3465_ = lean_uint64_to_uint32(v___y_3455_);
v___y_3446_ = v___y_3453_;
v___y_3447_ = v___x_3460_;
v___y_3448_ = v___y_3454_;
v___y_3449_ = v___x_3465_;
goto v___jp_3445_;
}
}
v___jp_3466_:
{
uint64_t v___x_3473_; uint8_t v___x_3474_; 
v___x_3473_ = 425ULL;
v___x_3474_ = lean_uint64_dec_lt(v___x_3473_, v___y_3472_);
if (v___x_3474_ == 0)
{
if (v___y_3468_ == 0)
{
v___y_3453_ = v___y_3467_;
v___y_3454_ = v___y_3469_;
v___y_3455_ = v___y_3470_;
v___y_3456_ = v___y_3472_;
v___y_3457_ = v___y_3471_;
goto v___jp_3452_;
}
else
{
uint64_t v___x_3475_; 
v___x_3475_ = 8388608ULL;
v___y_3453_ = v___y_3467_;
v___y_3454_ = v___y_3469_;
v___y_3455_ = v___y_3470_;
v___y_3456_ = v___y_3472_;
v___y_3457_ = v___x_3475_;
goto v___jp_3452_;
}
}
else
{
if (v___y_3467_ == 0)
{
uint32_t v___x_3476_; 
v___x_3476_ = 2139095040;
return v___x_3476_;
}
else
{
uint32_t v___x_3477_; 
v___x_3477_ = 4286578688;
return v___x_3477_;
}
}
}
v___jp_3478_:
{
uint64_t v___x_3484_; uint8_t v_carry_3485_; 
v___x_3484_ = 16777216ULL;
v_carry_3485_ = lean_uint64_dec_eq(v___y_3483_, v___x_3484_);
if (v_carry_3485_ == 0)
{
v___y_3467_ = v___y_3479_;
v___y_3468_ = v_carry_3485_;
v___y_3469_ = v___y_3481_;
v___y_3470_ = v___y_3482_;
v___y_3471_ = v___y_3483_;
v___y_3472_ = v___y_3480_;
goto v___jp_3466_;
}
else
{
uint64_t v___x_3486_; uint64_t v___x_3487_; 
v___x_3486_ = 1ULL;
v___x_3487_ = lean_uint64_add(v___y_3480_, v___x_3486_);
v___y_3467_ = v___y_3479_;
v___y_3468_ = v_carry_3485_;
v___y_3469_ = v___y_3481_;
v___y_3470_ = v___y_3482_;
v___y_3471_ = v___y_3483_;
v___y_3472_ = v___x_3487_;
goto v___jp_3466_;
}
}
v___jp_3488_:
{
uint64_t v_position_3495_; uint64_t v___x_3496_; uint8_t v___x_3497_; 
v_position_3495_ = lean_uint64_add(v___y_3494_, v___y_3492_);
v___x_3496_ = 172ULL;
v___x_3497_ = lean_uint64_dec_lt(v_position_3495_, v___x_3496_);
if (v___x_3497_ == 0)
{
uint64_t v___x_3498_; uint8_t v___x_3499_; 
v___x_3498_ = 23ULL;
v___x_3499_ = lean_uint64_dec_lt(v___y_3494_, v___x_3498_);
if (v___x_3499_ == 0)
{
uint64_t v___x_3500_; uint8_t v___x_3501_; 
v___x_3500_ = lean_uint64_sub(v___y_3494_, v___x_3498_);
v___x_3501_ = lean_uint64_dec_eq(v___x_3500_, v___y_3493_);
if (v___x_3501_ == 0)
{
uint64_t v___x_3502_; uint8_t v___x_3503_; 
v___x_3502_ = 64ULL;
v___x_3503_ = lean_uint64_dec_lt(v___x_3500_, v___x_3502_);
if (v___x_3503_ == 0)
{
uint8_t v___x_3504_; 
v___x_3504_ = lean_uint64_dec_eq(v___x_3500_, v___x_3502_);
if (v___x_3504_ == 0)
{
v___y_3479_ = v___y_3489_;
v___y_3480_ = v_position_3495_;
v___y_3481_ = v___y_3491_;
v___y_3482_ = v___y_3493_;
v___y_3483_ = v___y_3493_;
goto v___jp_3478_;
}
else
{
uint64_t v___x_3505_; uint8_t v___x_3506_; 
v___x_3505_ = 9223372036854775808ULL;
v___x_3506_ = lean_uint64_dec_lt(v___x_3505_, v___y_3490_);
if (v___x_3506_ == 0)
{
v___y_3479_ = v___y_3489_;
v___y_3480_ = v_position_3495_;
v___y_3481_ = v___y_3491_;
v___y_3482_ = v___y_3493_;
v___y_3483_ = v___y_3493_;
goto v___jp_3478_;
}
else
{
uint64_t v___x_3507_; 
v___x_3507_ = 1ULL;
v___y_3479_ = v___y_3489_;
v___y_3480_ = v_position_3495_;
v___y_3481_ = v___y_3491_;
v___y_3482_ = v___y_3493_;
v___y_3483_ = v___x_3507_;
goto v___jp_3478_;
}
}
}
else
{
uint64_t v_quotient_3508_; uint64_t v___x_3509_; uint64_t v___x_3510_; uint64_t v___x_3511_; uint64_t v_remainder_3512_; uint64_t v___x_3513_; uint64_t v_half_3514_; uint8_t v___x_3515_; 
v_quotient_3508_ = lean_uint64_shift_right(v___y_3490_, v___x_3500_);
v___x_3509_ = 1ULL;
v___x_3510_ = lean_uint64_shift_left(v___x_3509_, v___x_3500_);
v___x_3511_ = lean_uint64_sub(v___x_3510_, v___x_3509_);
v_remainder_3512_ = lean_uint64_land(v___y_3490_, v___x_3511_);
v___x_3513_ = lean_uint64_sub(v___x_3500_, v___x_3509_);
v_half_3514_ = lean_uint64_shift_left(v___x_3509_, v___x_3513_);
v___x_3515_ = lean_uint64_dec_lt(v_remainder_3512_, v_half_3514_);
if (v___x_3515_ == 0)
{
uint8_t v___x_3516_; 
v___x_3516_ = lean_uint64_dec_lt(v_half_3514_, v_remainder_3512_);
if (v___x_3516_ == 0)
{
uint64_t v___x_3517_; uint8_t v___x_3518_; 
v___x_3517_ = lean_uint64_land(v_quotient_3508_, v___x_3509_);
v___x_3518_ = lean_uint64_dec_eq(v___x_3517_, v___y_3493_);
if (v___x_3518_ == 0)
{
uint64_t v___x_3519_; 
v___x_3519_ = lean_uint64_add(v_quotient_3508_, v___x_3509_);
v___y_3479_ = v___y_3489_;
v___y_3480_ = v_position_3495_;
v___y_3481_ = v___y_3491_;
v___y_3482_ = v___y_3493_;
v___y_3483_ = v___x_3519_;
goto v___jp_3478_;
}
else
{
v___y_3479_ = v___y_3489_;
v___y_3480_ = v_position_3495_;
v___y_3481_ = v___y_3491_;
v___y_3482_ = v___y_3493_;
v___y_3483_ = v_quotient_3508_;
goto v___jp_3478_;
}
}
else
{
uint64_t v___x_3520_; 
v___x_3520_ = lean_uint64_add(v_quotient_3508_, v___x_3509_);
v___y_3479_ = v___y_3489_;
v___y_3480_ = v_position_3495_;
v___y_3481_ = v___y_3491_;
v___y_3482_ = v___y_3493_;
v___y_3483_ = v___x_3520_;
goto v___jp_3478_;
}
}
else
{
v___y_3479_ = v___y_3489_;
v___y_3480_ = v_position_3495_;
v___y_3481_ = v___y_3491_;
v___y_3482_ = v___y_3493_;
v___y_3483_ = v_quotient_3508_;
goto v___jp_3478_;
}
}
}
else
{
v___y_3479_ = v___y_3489_;
v___y_3480_ = v_position_3495_;
v___y_3481_ = v___y_3491_;
v___y_3482_ = v___y_3493_;
v___y_3483_ = v___y_3490_;
goto v___jp_3478_;
}
}
else
{
uint64_t v___x_3521_; uint64_t v___x_3522_; 
v___x_3521_ = lean_uint64_sub(v___x_3498_, v___y_3494_);
v___x_3522_ = lean_uint64_shift_left(v___y_3490_, v___x_3521_);
v___y_3479_ = v___y_3489_;
v___y_3480_ = v_position_3495_;
v___y_3481_ = v___y_3491_;
v___y_3482_ = v___y_3493_;
v___y_3483_ = v___x_3522_;
goto v___jp_3478_;
}
}
else
{
uint64_t v___x_3523_; uint8_t v___x_3524_; 
v___x_3523_ = 149ULL;
v___x_3524_ = lean_uint64_dec_lt(v___y_3492_, v___x_3523_);
if (v___x_3524_ == 0)
{
uint64_t v___x_3525_; uint64_t v___x_3526_; 
v___x_3525_ = lean_uint64_sub(v___y_3492_, v___x_3523_);
v___x_3526_ = lean_uint64_shift_left(v___y_3490_, v___x_3525_);
v___y_2699_ = v___y_3489_;
v___y_2700_ = v___y_3491_;
v___y_2701_ = v___y_3493_;
v___y_2702_ = v___x_3526_;
goto v___jp_2698_;
}
else
{
uint64_t v___x_3527_; uint8_t v___x_3528_; 
v___x_3527_ = lean_uint64_sub(v___x_3523_, v___y_3492_);
v___x_3528_ = lean_uint64_dec_eq(v___x_3527_, v___y_3493_);
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
v___y_2699_ = v___y_3489_;
v___y_2700_ = v___y_3491_;
v___y_2701_ = v___y_3493_;
v___y_2702_ = v___y_3493_;
goto v___jp_2698_;
}
else
{
uint64_t v___x_3532_; uint8_t v___x_3533_; 
v___x_3532_ = 9223372036854775808ULL;
v___x_3533_ = lean_uint64_dec_lt(v___x_3532_, v___y_3490_);
if (v___x_3533_ == 0)
{
v___y_2699_ = v___y_3489_;
v___y_2700_ = v___y_3491_;
v___y_2701_ = v___y_3493_;
v___y_2702_ = v___y_3493_;
goto v___jp_2698_;
}
else
{
uint64_t v___x_3534_; 
v___x_3534_ = 1ULL;
v___y_2699_ = v___y_3489_;
v___y_2700_ = v___y_3491_;
v___y_2701_ = v___y_3493_;
v___y_2702_ = v___x_3534_;
goto v___jp_2698_;
}
}
}
else
{
uint64_t v_quotient_3535_; uint64_t v___x_3536_; uint64_t v___x_3537_; uint64_t v___x_3538_; uint64_t v_remainder_3539_; uint64_t v___x_3540_; uint64_t v_half_3541_; uint8_t v___x_3542_; 
v_quotient_3535_ = lean_uint64_shift_right(v___y_3490_, v___x_3527_);
v___x_3536_ = 1ULL;
v___x_3537_ = lean_uint64_shift_left(v___x_3536_, v___x_3527_);
v___x_3538_ = lean_uint64_sub(v___x_3537_, v___x_3536_);
v_remainder_3539_ = lean_uint64_land(v___y_3490_, v___x_3538_);
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
v___x_3545_ = lean_uint64_dec_eq(v___x_3544_, v___y_3493_);
if (v___x_3545_ == 0)
{
uint64_t v___x_3546_; 
v___x_3546_ = lean_uint64_add(v_quotient_3535_, v___x_3536_);
v___y_2699_ = v___y_3489_;
v___y_2700_ = v___y_3491_;
v___y_2701_ = v___y_3493_;
v___y_2702_ = v___x_3546_;
goto v___jp_2698_;
}
else
{
v___y_2699_ = v___y_3489_;
v___y_2700_ = v___y_3491_;
v___y_2701_ = v___y_3493_;
v___y_2702_ = v_quotient_3535_;
goto v___jp_2698_;
}
}
else
{
uint64_t v___x_3547_; 
v___x_3547_ = lean_uint64_add(v_quotient_3535_, v___x_3536_);
v___y_2699_ = v___y_3489_;
v___y_2700_ = v___y_3491_;
v___y_2701_ = v___y_3493_;
v___y_2702_ = v___x_3547_;
goto v___jp_2698_;
}
}
else
{
v___y_2699_ = v___y_3489_;
v___y_2700_ = v___y_3491_;
v___y_2701_ = v___y_3493_;
v___y_2702_ = v_quotient_3535_;
goto v___jp_2698_;
}
}
}
else
{
v___y_2699_ = v___y_3489_;
v___y_2700_ = v___y_3491_;
v___y_2701_ = v___y_3493_;
v___y_2702_ = v___y_3490_;
goto v___jp_2698_;
}
}
}
}
v___jp_3548_:
{
uint64_t v___x_3556_; uint64_t v___x_3557_; uint8_t v___x_3558_; 
v___x_3556_ = 1ULL;
v___x_3557_ = lean_uint64_shift_right(v___y_3554_, v___x_3556_);
v___x_3558_ = lean_uint64_dec_eq(v___x_3557_, v___y_3553_);
if (v___x_3558_ == 0)
{
uint64_t v___x_3559_; 
v___x_3559_ = lean_uint64_add(v___y_3555_, v___x_3556_);
v___y_3489_ = v___y_3549_;
v___y_3490_ = v___y_3552_;
v___y_3491_ = v___y_3551_;
v___y_3492_ = v___y_3550_;
v___y_3493_ = v___y_3553_;
v___y_3494_ = v___x_3559_;
goto v___jp_3488_;
}
else
{
v___y_3489_ = v___y_3549_;
v___y_3490_ = v___y_3552_;
v___y_3491_ = v___y_3551_;
v___y_3492_ = v___y_3550_;
v___y_3493_ = v___y_3553_;
v___y_3494_ = v___y_3555_;
goto v___jp_3488_;
}
}
v___jp_3560_:
{
uint64_t v___x_3570_; uint8_t v___x_3571_; 
v___x_3570_ = lean_uint64_shift_right(v___y_3568_, v___y_3566_);
v___x_3571_ = lean_uint64_dec_eq(v___x_3570_, v___y_3565_);
if (v___x_3571_ == 0)
{
uint64_t v___x_3572_; 
v___x_3572_ = lean_uint64_add(v___y_3567_, v___y_3566_);
v___y_3549_ = v___y_3561_;
v___y_3550_ = v___y_3564_;
v___y_3551_ = v___y_3563_;
v___y_3552_ = v___y_3562_;
v___y_3553_ = v___y_3565_;
v___y_3554_ = v___y_3569_;
v___y_3555_ = v___x_3572_;
goto v___jp_3548_;
}
else
{
v___y_3549_ = v___y_3561_;
v___y_3550_ = v___y_3564_;
v___y_3551_ = v___y_3563_;
v___y_3552_ = v___y_3562_;
v___y_3553_ = v___y_3565_;
v___y_3554_ = v___y_3569_;
v___y_3555_ = v___y_3567_;
goto v___jp_3548_;
}
}
v___jp_3573_:
{
uint64_t v___x_3581_; uint64_t v___x_3582_; uint8_t v___x_3583_; 
v___x_3581_ = 2ULL;
v___x_3582_ = lean_uint64_shift_right(v___y_3579_, v___x_3581_);
v___x_3583_ = lean_uint64_dec_eq(v___x_3582_, v___y_3578_);
if (v___x_3583_ == 0)
{
v___y_3561_ = v___y_3574_;
v___y_3562_ = v___y_3577_;
v___y_3563_ = v___y_3576_;
v___y_3564_ = v___y_3575_;
v___y_3565_ = v___y_3578_;
v___y_3566_ = v___x_3581_;
v___y_3567_ = v___y_3580_;
v___y_3568_ = v___y_3579_;
v___y_3569_ = v___x_3582_;
goto v___jp_3560_;
}
else
{
v___y_3561_ = v___y_3574_;
v___y_3562_ = v___y_3577_;
v___y_3563_ = v___y_3576_;
v___y_3564_ = v___y_3575_;
v___y_3565_ = v___y_3578_;
v___y_3566_ = v___x_3581_;
v___y_3567_ = v___y_3580_;
v___y_3568_ = v___y_3579_;
v___y_3569_ = v___y_3579_;
goto v___jp_3560_;
}
}
v___jp_3584_:
{
uint64_t v___x_3594_; uint8_t v___x_3595_; 
v___x_3594_ = lean_uint64_shift_right(v___y_3591_, v___y_3589_);
v___x_3595_ = lean_uint64_dec_eq(v___x_3594_, v___y_3590_);
if (v___x_3595_ == 0)
{
uint64_t v___x_3596_; 
v___x_3596_ = lean_uint64_add(v___y_3592_, v___y_3589_);
v___y_3574_ = v___y_3585_;
v___y_3575_ = v___y_3588_;
v___y_3576_ = v___y_3587_;
v___y_3577_ = v___y_3586_;
v___y_3578_ = v___y_3590_;
v___y_3579_ = v___y_3593_;
v___y_3580_ = v___x_3596_;
goto v___jp_3573_;
}
else
{
v___y_3574_ = v___y_3585_;
v___y_3575_ = v___y_3588_;
v___y_3576_ = v___y_3587_;
v___y_3577_ = v___y_3586_;
v___y_3578_ = v___y_3590_;
v___y_3579_ = v___y_3593_;
v___y_3580_ = v___y_3592_;
goto v___jp_3573_;
}
}
v___jp_3597_:
{
uint64_t v___x_3605_; uint64_t v___x_3606_; uint8_t v___x_3607_; 
v___x_3605_ = 4ULL;
v___x_3606_ = lean_uint64_shift_right(v___y_3603_, v___x_3605_);
v___x_3607_ = lean_uint64_dec_eq(v___x_3606_, v___y_3602_);
if (v___x_3607_ == 0)
{
v___y_3585_ = v___y_3598_;
v___y_3586_ = v___y_3601_;
v___y_3587_ = v___y_3600_;
v___y_3588_ = v___y_3599_;
v___y_3589_ = v___x_3605_;
v___y_3590_ = v___y_3602_;
v___y_3591_ = v___y_3603_;
v___y_3592_ = v___y_3604_;
v___y_3593_ = v___x_3606_;
goto v___jp_3584_;
}
else
{
v___y_3585_ = v___y_3598_;
v___y_3586_ = v___y_3601_;
v___y_3587_ = v___y_3600_;
v___y_3588_ = v___y_3599_;
v___y_3589_ = v___x_3605_;
v___y_3590_ = v___y_3602_;
v___y_3591_ = v___y_3603_;
v___y_3592_ = v___y_3604_;
v___y_3593_ = v___y_3603_;
goto v___jp_3584_;
}
}
v___jp_3608_:
{
uint64_t v___x_3618_; uint8_t v___x_3619_; 
v___x_3618_ = lean_uint64_shift_right(v___y_3611_, v___y_3616_);
v___x_3619_ = lean_uint64_dec_eq(v___x_3618_, v___y_3615_);
if (v___x_3619_ == 0)
{
uint64_t v___x_3620_; 
v___x_3620_ = lean_uint64_add(v___y_3609_, v___y_3616_);
v___y_3598_ = v___y_3610_;
v___y_3599_ = v___y_3614_;
v___y_3600_ = v___y_3613_;
v___y_3601_ = v___y_3612_;
v___y_3602_ = v___y_3615_;
v___y_3603_ = v___y_3617_;
v___y_3604_ = v___x_3620_;
goto v___jp_3597_;
}
else
{
v___y_3598_ = v___y_3610_;
v___y_3599_ = v___y_3614_;
v___y_3600_ = v___y_3613_;
v___y_3601_ = v___y_3612_;
v___y_3602_ = v___y_3615_;
v___y_3603_ = v___y_3617_;
v___y_3604_ = v___y_3609_;
goto v___jp_3597_;
}
}
v___jp_3621_:
{
uint64_t v___x_3629_; uint64_t v___x_3630_; uint8_t v___x_3631_; 
v___x_3629_ = 8ULL;
v___x_3630_ = lean_uint64_shift_right(v___y_3623_, v___x_3629_);
v___x_3631_ = lean_uint64_dec_eq(v___x_3630_, v___y_3627_);
if (v___x_3631_ == 0)
{
v___y_3609_ = v___y_3628_;
v___y_3610_ = v___y_3622_;
v___y_3611_ = v___y_3623_;
v___y_3612_ = v___y_3626_;
v___y_3613_ = v___y_3625_;
v___y_3614_ = v___y_3624_;
v___y_3615_ = v___y_3627_;
v___y_3616_ = v___x_3629_;
v___y_3617_ = v___x_3630_;
goto v___jp_3608_;
}
else
{
v___y_3609_ = v___y_3628_;
v___y_3610_ = v___y_3622_;
v___y_3611_ = v___y_3623_;
v___y_3612_ = v___y_3626_;
v___y_3613_ = v___y_3625_;
v___y_3614_ = v___y_3624_;
v___y_3615_ = v___y_3627_;
v___y_3616_ = v___x_3629_;
v___y_3617_ = v___y_3623_;
goto v___jp_3608_;
}
}
v___jp_3632_:
{
uint64_t v___x_3642_; uint8_t v___x_3643_; 
v___x_3642_ = lean_uint64_shift_right(v___y_3640_, v___y_3633_);
v___x_3643_ = lean_uint64_dec_eq(v___x_3642_, v___y_3639_);
if (v___x_3643_ == 0)
{
uint64_t v___x_3644_; 
v___x_3644_ = lean_uint64_add(v___y_3634_, v___y_3633_);
v___y_3622_ = v___y_3635_;
v___y_3623_ = v___y_3641_;
v___y_3624_ = v___y_3638_;
v___y_3625_ = v___y_3637_;
v___y_3626_ = v___y_3636_;
v___y_3627_ = v___y_3639_;
v___y_3628_ = v___x_3644_;
goto v___jp_3621_;
}
else
{
v___y_3622_ = v___y_3635_;
v___y_3623_ = v___y_3641_;
v___y_3624_ = v___y_3638_;
v___y_3625_ = v___y_3637_;
v___y_3626_ = v___y_3636_;
v___y_3627_ = v___y_3639_;
v___y_3628_ = v___y_3634_;
goto v___jp_3621_;
}
}
v___jp_3645_:
{
uint64_t v___x_3653_; uint64_t v___x_3654_; uint8_t v___x_3655_; 
v___x_3653_ = 16ULL;
v___x_3654_ = lean_uint64_shift_right(v___y_3651_, v___x_3653_);
v___x_3655_ = lean_uint64_dec_eq(v___x_3654_, v___y_3650_);
if (v___x_3655_ == 0)
{
v___y_3633_ = v___x_3653_;
v___y_3634_ = v___y_3652_;
v___y_3635_ = v___y_3646_;
v___y_3636_ = v___y_3649_;
v___y_3637_ = v___y_3648_;
v___y_3638_ = v___y_3647_;
v___y_3639_ = v___y_3650_;
v___y_3640_ = v___y_3651_;
v___y_3641_ = v___x_3654_;
goto v___jp_3632_;
}
else
{
v___y_3633_ = v___x_3653_;
v___y_3634_ = v___y_3652_;
v___y_3635_ = v___y_3646_;
v___y_3636_ = v___y_3649_;
v___y_3637_ = v___y_3648_;
v___y_3638_ = v___y_3647_;
v___y_3639_ = v___y_3650_;
v___y_3640_ = v___y_3651_;
v___y_3641_ = v___y_3651_;
goto v___jp_3632_;
}
}
v___jp_3656_:
{
uint64_t v___x_3664_; uint8_t v___x_3665_; 
v___x_3664_ = lean_uint64_shift_right(v___y_3658_, v___y_3662_);
v___x_3665_ = lean_uint64_dec_eq(v___x_3664_, v___y_3661_);
if (v___x_3665_ == 0)
{
v___y_3646_ = v___y_3657_;
v___y_3647_ = v___y_3660_;
v___y_3648_ = v___y_3659_;
v___y_3649_ = v___y_3658_;
v___y_3650_ = v___y_3661_;
v___y_3651_ = v___y_3663_;
v___y_3652_ = v___y_3662_;
goto v___jp_3645_;
}
else
{
v___y_3646_ = v___y_3657_;
v___y_3647_ = v___y_3660_;
v___y_3648_ = v___y_3659_;
v___y_3649_ = v___y_3658_;
v___y_3650_ = v___y_3661_;
v___y_3651_ = v___y_3663_;
v___y_3652_ = v___y_3661_;
goto v___jp_3645_;
}
}
v___jp_3666_:
{
uint64_t v___x_3671_; uint8_t v___x_3672_; 
v___x_3671_ = 0ULL;
v___x_3672_ = lean_uint64_dec_eq(v___y_3669_, v___x_3671_);
if (v___x_3672_ == 0)
{
uint64_t v___x_3673_; uint64_t v___x_3674_; uint8_t v___x_3675_; 
v___x_3673_ = 32ULL;
v___x_3674_ = lean_uint64_shift_right(v___y_3669_, v___x_3673_);
v___x_3675_ = lean_uint64_dec_eq(v___x_3674_, v___x_3671_);
if (v___x_3675_ == 0)
{
v___y_3657_ = v___y_3667_;
v___y_3658_ = v___y_3669_;
v___y_3659_ = v___y_3670_;
v___y_3660_ = v___y_3668_;
v___y_3661_ = v___x_3671_;
v___y_3662_ = v___x_3673_;
v___y_3663_ = v___x_3674_;
goto v___jp_3656_;
}
else
{
v___y_3657_ = v___y_3667_;
v___y_3658_ = v___y_3669_;
v___y_3659_ = v___y_3670_;
v___y_3660_ = v___y_3668_;
v___y_3661_ = v___x_3671_;
v___y_3662_ = v___x_3673_;
v___y_3663_ = v___y_3669_;
goto v___jp_3656_;
}
}
else
{
if (v___y_3667_ == 0)
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
v___jp_3678_:
{
uint64_t v___x_3685_; uint64_t v___x_3686_; uint64_t v___x_3687_; uint8_t v___x_3688_; 
v___x_3685_ = lean_uint64_mul(v___y_3682_, v___y_3683_);
v___x_3686_ = lean_uint64_add(v___y_3681_, v___y_3684_);
v___x_3687_ = 281474976710656ULL;
v___x_3688_ = lean_uint64_dec_lt(v___x_3685_, v___x_3687_);
if (v___x_3688_ == 0)
{
v___y_3667_ = v___y_3679_;
v___y_3668_ = v___x_3686_;
v___y_3669_ = v___x_3685_;
v___y_3670_ = v___y_3680_;
goto v___jp_3666_;
}
else
{
uint64_t v___x_3689_; uint8_t v___x_3690_; 
v___x_3689_ = 123ULL;
v___x_3690_ = lean_uint64_dec_le(v___x_3686_, v___x_3689_);
if (v___x_3690_ == 0)
{
v___y_3667_ = v___y_3679_;
v___y_3668_ = v___x_3686_;
v___y_3669_ = v___x_3685_;
v___y_3670_ = v___y_3680_;
goto v___jp_3666_;
}
else
{
uint64_t v___x_3691_; uint8_t v___x_3692_; 
v___x_3691_ = 0ULL;
v___x_3692_ = lean_uint64_dec_eq(v___x_3685_, v___x_3691_);
if (v___x_3692_ == 0)
{
uint64_t v___x_3693_; uint64_t v___x_3694_; uint8_t v___x_3695_; 
v___x_3693_ = 149ULL;
v___x_3694_ = lean_uint64_sub(v___x_3693_, v___x_3686_);
v___x_3695_ = lean_uint64_dec_eq(v___x_3694_, v___x_3691_);
if (v___x_3695_ == 0)
{
uint64_t v___x_3696_; uint8_t v___x_3697_; 
v___x_3696_ = 64ULL;
v___x_3697_ = lean_uint64_dec_lt(v___x_3694_, v___x_3696_);
if (v___x_3697_ == 0)
{
uint8_t v___x_3698_; 
v___x_3698_ = lean_uint64_dec_eq(v___x_3694_, v___x_3696_);
if (v___x_3698_ == 0)
{
v___y_2720_ = v___y_3679_;
v___y_2721_ = v___x_3691_;
v___y_2722_ = v___y_3680_;
v___y_2723_ = v___x_3691_;
goto v___jp_2719_;
}
else
{
uint64_t v___x_3699_; uint8_t v___x_3700_; 
v___x_3699_ = 9223372036854775808ULL;
v___x_3700_ = lean_uint64_dec_lt(v___x_3699_, v___x_3685_);
if (v___x_3700_ == 0)
{
v___y_2720_ = v___y_3679_;
v___y_2721_ = v___x_3691_;
v___y_2722_ = v___y_3680_;
v___y_2723_ = v___x_3691_;
goto v___jp_2719_;
}
else
{
uint64_t v___x_3701_; 
v___x_3701_ = 1ULL;
v___y_2720_ = v___y_3679_;
v___y_2721_ = v___x_3691_;
v___y_2722_ = v___y_3680_;
v___y_2723_ = v___x_3701_;
goto v___jp_2719_;
}
}
}
else
{
uint64_t v_quotient_3702_; uint64_t v___x_3703_; uint64_t v___x_3704_; uint64_t v___x_3705_; uint64_t v_remainder_3706_; uint64_t v___x_3707_; uint64_t v_half_3708_; uint8_t v___x_3709_; 
v_quotient_3702_ = lean_uint64_shift_right(v___x_3685_, v___x_3694_);
v___x_3703_ = 1ULL;
v___x_3704_ = lean_uint64_shift_left(v___x_3703_, v___x_3694_);
v___x_3705_ = lean_uint64_sub(v___x_3704_, v___x_3703_);
v_remainder_3706_ = lean_uint64_land(v___x_3685_, v___x_3705_);
v___x_3707_ = lean_uint64_sub(v___x_3694_, v___x_3703_);
v_half_3708_ = lean_uint64_shift_left(v___x_3703_, v___x_3707_);
v___x_3709_ = lean_uint64_dec_lt(v_remainder_3706_, v_half_3708_);
if (v___x_3709_ == 0)
{
uint8_t v___x_3710_; 
v___x_3710_ = lean_uint64_dec_lt(v_half_3708_, v_remainder_3706_);
if (v___x_3710_ == 0)
{
uint64_t v___x_3711_; uint8_t v___x_3712_; 
v___x_3711_ = lean_uint64_land(v_quotient_3702_, v___x_3703_);
v___x_3712_ = lean_uint64_dec_eq(v___x_3711_, v___x_3691_);
if (v___x_3712_ == 0)
{
uint64_t v___x_3713_; 
v___x_3713_ = lean_uint64_add(v_quotient_3702_, v___x_3703_);
v___y_2720_ = v___y_3679_;
v___y_2721_ = v___x_3691_;
v___y_2722_ = v___y_3680_;
v___y_2723_ = v___x_3713_;
goto v___jp_2719_;
}
else
{
v___y_2720_ = v___y_3679_;
v___y_2721_ = v___x_3691_;
v___y_2722_ = v___y_3680_;
v___y_2723_ = v_quotient_3702_;
goto v___jp_2719_;
}
}
else
{
uint64_t v___x_3714_; 
v___x_3714_ = lean_uint64_add(v_quotient_3702_, v___x_3703_);
v___y_2720_ = v___y_3679_;
v___y_2721_ = v___x_3691_;
v___y_2722_ = v___y_3680_;
v___y_2723_ = v___x_3714_;
goto v___jp_2719_;
}
}
else
{
v___y_2720_ = v___y_3679_;
v___y_2721_ = v___x_3691_;
v___y_2722_ = v___y_3680_;
v___y_2723_ = v_quotient_3702_;
goto v___jp_2719_;
}
}
}
else
{
v___y_2720_ = v___y_3679_;
v___y_2721_ = v___x_3691_;
v___y_2722_ = v___y_3680_;
v___y_2723_ = v___x_3685_;
goto v___jp_2719_;
}
}
else
{
if (v___y_3679_ == 0)
{
uint32_t v___x_3715_; 
v___x_3715_ = 0;
return v___x_3715_;
}
else
{
uint32_t v___x_3716_; 
v___x_3716_ = 2147483648;
return v___x_3716_;
}
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_runInlineOld___lam__1___boxed(lean_object* v___y_4018_, lean_object* v___y_4019_){
_start:
{
uint32_t v___y_5372__boxed_4020_; uint32_t v___y_5373__boxed_4021_; uint32_t v_res_4022_; lean_object* v_r_4023_; 
v___y_5372__boxed_4020_ = lean_unbox_uint32(v___y_4018_);
lean_dec(v___y_4018_);
v___y_5373__boxed_4021_ = lean_unbox_uint32(v___y_4019_);
lean_dec(v___y_4019_);
v_res_4022_ = lp_competition_runInlineOld___lam__1(v___y_5372__boxed_4020_, v___y_5373__boxed_4021_);
v_r_4023_ = lean_box_uint32(v_res_4022_);
return v_r_4023_;
}
}
LEAN_EXPORT lean_object* lp_competition_runInlineOld(){
_start:
{
lean_object* v___f_4026_; lean_object* v___f_4027_; lean_object* v___x_4028_; lean_object* v___x_4029_; lean_object* v___x_4030_; 
v___f_4026_ = ((lean_object*)(lp_competition_runControl___closed__0));
v___f_4027_ = ((lean_object*)(lp_competition_runInlineOld___closed__0));
v___x_4028_ = ((lean_object*)(lp_competition_runControl___closed__2));
v___x_4029_ = ((lean_object*)(lp_competition_runControl___closed__3));
v___x_4030_ = lp_competition_Bench_Suite_run(v___f_4026_, v___f_4027_, v___x_4028_, v___x_4029_);
return v___x_4030_;
}
}
LEAN_EXPORT lean_object* lp_competition_runInlineOld___boxed(lean_object* v_a_4031_){
_start:
{
lean_object* v_res_4032_; 
v_res_4032_ = lp_competition_runInlineOld();
return v_res_4032_;
}
}
LEAN_EXPORT uint32_t lp_competition_runOutline___lam__1(uint32_t v___y_4033_, uint32_t v___y_4034_){
_start:
{
uint32_t v___x_4035_; uint32_t v___x_4036_; uint32_t v___x_4037_; uint32_t v_eu_4038_; uint32_t v___x_4039_; uint32_t v___x_4040_; uint32_t v___x_4041_; uint8_t v___x_4042_; 
v___x_4035_ = 23;
v___x_4036_ = lean_uint32_shift_right(v___y_4033_, v___x_4035_);
v___x_4037_ = 255;
v_eu_4038_ = lean_uint32_land(v___x_4036_, v___x_4037_);
v___x_4039_ = 1;
v___x_4040_ = lean_uint32_sub(v_eu_4038_, v___x_4039_);
v___x_4041_ = 253;
v___x_4042_ = lean_uint32_dec_le(v___x_4040_, v___x_4041_);
if (v___x_4042_ == 0)
{
uint32_t v___x_4043_; 
v___x_4043_ = lp_competition_Submission_R22OutlineMul_retainedMul(v___y_4033_, v___y_4034_);
return v___x_4043_;
}
else
{
uint32_t v___x_4044_; uint32_t v_ev_4045_; uint32_t v___x_4046_; uint8_t v___x_4047_; 
v___x_4044_ = lean_uint32_shift_right(v___y_4034_, v___x_4035_);
v_ev_4045_ = lean_uint32_land(v___x_4044_, v___x_4037_);
v___x_4046_ = lean_uint32_sub(v_ev_4045_, v___x_4039_);
v___x_4047_ = lean_uint32_dec_le(v___x_4046_, v___x_4041_);
if (v___x_4047_ == 0)
{
uint32_t v___x_4048_; 
v___x_4048_ = lp_competition_Submission_R22OutlineMul_retainedMul(v___y_4033_, v___y_4034_);
return v___x_4048_;
}
else
{
uint32_t v_s_4049_; uint32_t v___x_4050_; uint32_t v___x_4051_; uint32_t v___x_4052_; uint8_t v___x_4053_; 
v_s_4049_ = lean_uint32_add(v_eu_4038_, v_ev_4045_);
v___x_4050_ = 128;
v___x_4051_ = lean_uint32_sub(v_s_4049_, v___x_4050_);
v___x_4052_ = 252;
v___x_4053_ = lean_uint32_dec_le(v___x_4051_, v___x_4052_);
if (v___x_4053_ == 0)
{
uint32_t v___x_4054_; 
v___x_4054_ = lp_competition_Submission_R22OutlineMul_retainedMul(v___y_4033_, v___y_4034_);
return v___x_4054_;
}
else
{
uint32_t v___x_4055_; uint32_t v___x_4056_; uint32_t v___x_4057_; uint64_t v___y_4059_; uint32_t v_a_4077_; uint32_t v___x_4078_; uint32_t v_b_4079_; uint64_t v___x_4080_; uint64_t v___x_4081_; uint64_t v_p_4082_; uint64_t v___x_4083_; uint8_t v___x_4084_; 
v___x_4055_ = 8388607;
v___x_4056_ = lean_uint32_land(v___y_4033_, v___x_4055_);
v___x_4057_ = 8388608;
v_a_4077_ = lean_uint32_lor(v___x_4056_, v___x_4057_);
v___x_4078_ = lean_uint32_land(v___y_4034_, v___x_4055_);
v_b_4079_ = lean_uint32_lor(v___x_4078_, v___x_4057_);
v___x_4080_ = lean_uint32_to_uint64(v_a_4077_);
v___x_4081_ = lean_uint32_to_uint64(v_b_4079_);
v_p_4082_ = lean_uint64_mul(v___x_4080_, v___x_4081_);
v___x_4083_ = 140737488355328ULL;
v___x_4084_ = lean_uint64_dec_lt(v_p_4082_, v___x_4083_);
if (v___x_4084_ == 0)
{
uint64_t v___x_4085_; uint64_t v___x_4086_; uint64_t v___x_4087_; uint64_t v___x_4088_; uint64_t v___x_4089_; uint64_t v___x_4090_; uint64_t v___x_4091_; 
v___x_4085_ = 8388607ULL;
v___x_4086_ = lean_uint64_add(v_p_4082_, v___x_4085_);
v___x_4087_ = 24ULL;
v___x_4088_ = lean_uint64_shift_right(v_p_4082_, v___x_4087_);
v___x_4089_ = 1ULL;
v___x_4090_ = lean_uint64_land(v___x_4088_, v___x_4089_);
v___x_4091_ = lean_uint64_add(v___x_4086_, v___x_4090_);
v___y_4059_ = v___x_4091_;
goto v___jp_4058_;
}
else
{
uint64_t v___x_4092_; uint64_t v___x_4093_; uint64_t v___x_4094_; uint64_t v___x_4095_; uint64_t v___x_4096_; uint64_t v___x_4097_; uint64_t v___x_4098_; 
v___x_4092_ = 4194303ULL;
v___x_4093_ = lean_uint64_add(v_p_4082_, v___x_4092_);
v___x_4094_ = 23ULL;
v___x_4095_ = lean_uint64_shift_right(v_p_4082_, v___x_4094_);
v___x_4096_ = 1ULL;
v___x_4097_ = lean_uint64_land(v___x_4095_, v___x_4096_);
v___x_4098_ = lean_uint64_add(v___x_4093_, v___x_4097_);
v___y_4059_ = v___x_4098_;
goto v___jp_4058_;
}
v___jp_4058_:
{
uint64_t v___x_4060_; uint64_t v_high_4061_; uint64_t v___x_4062_; uint64_t v___x_4063_; uint64_t v___x_4064_; uint32_t v_q_4065_; uint32_t v___x_4066_; uint32_t v___x_4067_; uint32_t v___x_4068_; uint32_t v_e_4069_; uint32_t v___x_4070_; uint32_t v___x_4071_; uint32_t v___x_4072_; uint32_t v___x_4073_; uint32_t v___x_4074_; uint32_t v___x_4075_; uint32_t v___x_4076_; 
v___x_4060_ = 47ULL;
v_high_4061_ = lean_uint64_shift_right(v___y_4059_, v___x_4060_);
v___x_4062_ = 23ULL;
v___x_4063_ = lean_uint64_add(v___x_4062_, v_high_4061_);
v___x_4064_ = lean_uint64_shift_right(v___y_4059_, v___x_4063_);
v_q_4065_ = lean_uint64_to_uint32(v___x_4064_);
v___x_4066_ = 127;
v___x_4067_ = lean_uint32_sub(v_s_4049_, v___x_4066_);
v___x_4068_ = lean_uint64_to_uint32(v_high_4061_);
v_e_4069_ = lean_uint32_add(v___x_4067_, v___x_4068_);
v___x_4070_ = lean_uint32_xor(v___y_4033_, v___y_4034_);
v___x_4071_ = 2147483648;
v___x_4072_ = lean_uint32_land(v___x_4070_, v___x_4071_);
v___x_4073_ = lean_uint32_shift_left(v_e_4069_, v___x_4035_);
v___x_4074_ = lean_uint32_lor(v___x_4072_, v___x_4073_);
v___x_4075_ = lean_uint32_sub(v_q_4065_, v___x_4057_);
v___x_4076_ = lean_uint32_lor(v___x_4074_, v___x_4075_);
return v___x_4076_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_runOutline___lam__1___boxed(lean_object* v___y_4099_, lean_object* v___y_4100_){
_start:
{
uint32_t v___y_754__boxed_4101_; uint32_t v___y_755__boxed_4102_; uint32_t v_res_4103_; lean_object* v_r_4104_; 
v___y_754__boxed_4101_ = lean_unbox_uint32(v___y_4099_);
lean_dec(v___y_4099_);
v___y_755__boxed_4102_ = lean_unbox_uint32(v___y_4100_);
lean_dec(v___y_4100_);
v_res_4103_ = lp_competition_runOutline___lam__1(v___y_754__boxed_4101_, v___y_755__boxed_4102_);
v_r_4104_ = lean_box_uint32(v_res_4103_);
return v_r_4104_;
}
}
LEAN_EXPORT lean_object* lp_competition_runOutline(){
_start:
{
lean_object* v___f_4107_; lean_object* v___f_4108_; lean_object* v___x_4109_; lean_object* v___x_4110_; lean_object* v___x_4111_; 
v___f_4107_ = ((lean_object*)(lp_competition_runControl___closed__0));
v___f_4108_ = ((lean_object*)(lp_competition_runOutline___closed__0));
v___x_4109_ = ((lean_object*)(lp_competition_runControl___closed__2));
v___x_4110_ = ((lean_object*)(lp_competition_runControl___closed__3));
v___x_4111_ = lp_competition_Bench_Suite_run(v___f_4107_, v___f_4108_, v___x_4109_, v___x_4110_);
return v___x_4111_;
}
}
LEAN_EXPORT lean_object* lp_competition_runOutline___boxed(lean_object* v_a_4112_){
_start:
{
lean_object* v_res_4113_; 
v_res_4113_ = lp_competition_runOutline();
return v_res_4113_;
}
}
LEAN_EXPORT uint32_t lp_competition_r22CostNativeProductMul(uint32_t v_x_4114_, uint32_t v_y_4115_){
_start:
{
uint8_t v___y_4117_; uint8_t v___y_4133_; uint8_t v___y_4147_; uint8_t v___y_4164_; float v___y_4171_; float v___y_4172_; float v___y_4186_; uint8_t v___y_4187_; float v___y_4202_; uint32_t v___y_4212_; uint32_t v___y_4216_; uint32_t v___y_4220_; uint32_t v___y_4221_; uint32_t v___y_4222_; uint8_t v___y_4226_; uint32_t v___y_4227_; uint64_t v___y_4228_; uint64_t v___y_4229_; uint32_t v___y_4241_; uint32_t v___y_4242_; uint32_t v___y_4243_; uint8_t v___y_4247_; uint32_t v___y_4248_; uint64_t v___y_4249_; uint64_t v___y_4250_; uint8_t v___y_4262_; uint8_t v___y_4278_; uint8_t v___y_4292_; uint8_t v___y_4309_; float v___y_4316_; float v___y_4317_; float v___y_4331_; uint8_t v___y_4332_; float v___y_4347_; uint32_t v___y_4357_; uint32_t v___y_4361_; uint32_t v___y_4365_; uint32_t v___y_4366_; uint32_t v___y_4367_; uint64_t v___y_4371_; uint8_t v___y_4372_; uint32_t v___y_4373_; uint64_t v___y_4374_; uint32_t v___y_4386_; uint32_t v___y_4387_; uint32_t v___y_4388_; uint8_t v___y_4392_; uint32_t v___y_4393_; uint64_t v___y_4394_; uint64_t v___y_4395_; uint8_t v___y_4407_; uint8_t v___y_4423_; uint8_t v___y_4437_; uint8_t v___y_4454_; float v___y_4461_; float v___y_4462_; float v___y_4476_; uint8_t v___y_4477_; float v___y_4492_; uint32_t v___y_4502_; uint32_t v___y_4506_; uint32_t v___y_4510_; uint32_t v___y_4511_; uint32_t v___y_4512_; uint32_t v___y_4516_; uint8_t v___y_4517_; uint64_t v___y_4518_; uint64_t v___y_4519_; uint32_t v___y_4531_; uint32_t v___y_4532_; uint32_t v___y_4533_; uint32_t v___y_4537_; uint8_t v___y_4538_; uint64_t v___y_4539_; uint64_t v___y_4540_; uint32_t v___x_4551_; uint32_t v___x_4552_; uint8_t v___y_4554_; uint8_t v___y_4567_; uint8_t v___y_4580_; uint32_t v___x_4592_; uint32_t v___y_4594_; uint32_t v___y_4595_; uint32_t v___y_4596_; uint32_t v___y_4597_; uint8_t v___y_4604_; uint32_t v___y_4605_; uint32_t v___y_4606_; uint32_t v___y_4607_; uint64_t v___y_4611_; uint8_t v___y_4612_; uint32_t v___y_4613_; uint64_t v___y_4614_; uint64_t v___y_4615_; uint64_t v___y_4625_; uint8_t v___y_4626_; uint8_t v___y_4627_; uint32_t v___y_4628_; uint64_t v___y_4629_; uint64_t v___y_4630_; uint8_t v___y_4637_; uint32_t v___y_4638_; uint64_t v___y_4639_; uint64_t v___y_4640_; uint64_t v___y_4641_; uint8_t v___y_4647_; uint32_t v___y_4648_; uint64_t v___y_4649_; uint64_t v___y_4650_; uint64_t v___y_4651_; uint64_t v___y_4652_; uint8_t v___y_4707_; uint32_t v___y_4708_; uint64_t v___y_4709_; uint64_t v___y_4710_; uint64_t v___y_4711_; uint64_t v___y_4712_; uint64_t v___y_4713_; uint64_t v___y_4719_; uint64_t v___y_4720_; uint64_t v___y_4721_; uint8_t v___y_4722_; uint32_t v___y_4723_; uint64_t v___y_4724_; uint64_t v___y_4725_; uint64_t v___y_4726_; uint64_t v___y_4727_; uint64_t v___y_4732_; uint8_t v___y_4733_; uint32_t v___y_4734_; uint64_t v___y_4735_; uint64_t v___y_4736_; uint64_t v___y_4737_; uint64_t v___y_4738_; uint64_t v___y_4743_; uint64_t v___y_4744_; uint64_t v___y_4745_; uint8_t v___y_4746_; uint32_t v___y_4747_; uint64_t v___y_4748_; uint64_t v___y_4749_; uint64_t v___y_4750_; uint64_t v___y_4751_; uint8_t v___y_4756_; uint64_t v___y_4757_; uint32_t v___y_4758_; uint64_t v___y_4759_; uint64_t v___y_4760_; uint64_t v___y_4761_; uint64_t v___y_4762_; uint64_t v___y_4767_; uint8_t v___y_4768_; uint32_t v___y_4769_; uint64_t v___y_4770_; uint64_t v___y_4771_; uint64_t v___y_4772_; uint64_t v___y_4773_; uint64_t v___y_4774_; uint64_t v___y_4775_; uint8_t v___y_4780_; uint32_t v___y_4781_; uint64_t v___y_4782_; uint64_t v___y_4783_; uint64_t v___y_4784_; uint64_t v___y_4785_; uint64_t v___y_4786_; uint64_t v___y_4791_; uint64_t v___y_4792_; uint64_t v___y_4793_; uint8_t v___y_4794_; uint32_t v___y_4795_; uint64_t v___y_4796_; uint64_t v___y_4797_; uint64_t v___y_4798_; uint64_t v___y_4799_; uint64_t v___y_4804_; uint8_t v___y_4805_; uint32_t v___y_4806_; uint64_t v___y_4807_; uint64_t v___y_4808_; uint64_t v___y_4809_; uint64_t v___y_4810_; uint8_t v___y_4815_; uint32_t v___y_4816_; uint64_t v___y_4817_; uint64_t v___y_4818_; uint64_t v___y_4819_; uint64_t v___y_4820_; uint64_t v___y_4821_; uint8_t v___y_4825_; uint32_t v___y_4826_; uint64_t v___y_4827_; uint64_t v___y_4828_; uint64_t v___y_4837_; uint8_t v___y_4838_; uint32_t v___y_4839_; uint64_t v___y_4840_; uint64_t v___y_4841_; uint64_t v___y_4842_; uint32_t v___y_4876_; uint32_t v___y_4877_; uint32_t v___y_4878_; uint32_t v___y_4879_; uint8_t v___y_4886_; uint32_t v___y_4887_; uint32_t v___y_4888_; uint32_t v___y_4889_; uint64_t v___y_4893_; uint64_t v___y_4894_; uint32_t v___y_4895_; uint8_t v___y_4896_; uint64_t v___y_4897_; uint8_t v___y_4907_; uint64_t v___y_4908_; uint64_t v___y_4909_; uint8_t v___y_4910_; uint32_t v___y_4911_; uint64_t v___y_4912_; uint64_t v___y_4919_; uint64_t v___y_4920_; uint32_t v___y_4921_; uint8_t v___y_4922_; uint64_t v___y_4923_; uint64_t v___y_4929_; uint64_t v___y_4930_; uint8_t v___y_4931_; uint32_t v___y_4932_; uint64_t v___y_4933_; uint64_t v___y_4934_; uint64_t v___y_4989_; uint64_t v___y_4990_; uint32_t v___y_4991_; uint8_t v___y_4992_; uint64_t v___y_4993_; uint64_t v___y_4994_; uint64_t v___y_4995_; uint64_t v___y_5001_; uint64_t v___y_5002_; uint64_t v___y_5003_; uint64_t v___y_5004_; uint64_t v___y_5005_; uint8_t v___y_5006_; uint32_t v___y_5007_; uint64_t v___y_5008_; uint64_t v___y_5009_; uint64_t v___y_5014_; uint64_t v___y_5015_; uint64_t v___y_5016_; uint32_t v___y_5017_; uint8_t v___y_5018_; uint64_t v___y_5019_; uint64_t v___y_5020_; uint64_t v___y_5025_; uint64_t v___y_5026_; uint64_t v___y_5027_; uint64_t v___y_5028_; uint8_t v___y_5029_; uint32_t v___y_5030_; uint64_t v___y_5031_; uint64_t v___y_5032_; uint64_t v___y_5033_; uint64_t v___y_5038_; uint64_t v___y_5039_; uint64_t v___y_5040_; uint32_t v___y_5041_; uint8_t v___y_5042_; uint64_t v___y_5043_; uint64_t v___y_5044_; uint64_t v___y_5049_; uint64_t v___y_5050_; uint64_t v___y_5051_; uint64_t v___y_5052_; uint8_t v___y_5053_; uint32_t v___y_5054_; uint64_t v___y_5055_; uint64_t v___y_5056_; uint64_t v___y_5057_; uint64_t v___y_5062_; uint64_t v___y_5063_; uint64_t v___y_5064_; uint32_t v___y_5065_; uint8_t v___y_5066_; uint64_t v___y_5067_; uint64_t v___y_5068_; uint64_t v___y_5073_; uint64_t v___y_5074_; uint64_t v___y_5075_; uint8_t v___y_5076_; uint32_t v___y_5077_; uint64_t v___y_5078_; uint64_t v___y_5079_; uint64_t v___y_5080_; uint64_t v___y_5081_; uint64_t v___y_5086_; uint64_t v___y_5087_; uint64_t v___y_5088_; uint32_t v___y_5089_; uint8_t v___y_5090_; uint64_t v___y_5091_; uint64_t v___y_5092_; uint64_t v___y_5097_; uint64_t v___y_5098_; uint8_t v___y_5099_; uint32_t v___y_5100_; uint64_t v___y_5101_; uint64_t v___y_5102_; uint64_t v___y_5103_; uint64_t v___y_5107_; uint32_t v___y_5108_; uint8_t v___y_5109_; uint64_t v___y_5110_; uint64_t v___y_5119_; uint64_t v___y_5120_; uint64_t v___y_5121_; uint8_t v___y_5122_; uint32_t v___y_5123_; uint64_t v___y_5124_; uint32_t v___y_5158_; uint32_t v___y_5159_; uint32_t v___y_5160_; uint32_t v___y_5161_; uint32_t v___y_5168_; uint8_t v___y_5169_; uint32_t v___y_5170_; uint32_t v___y_5171_; uint64_t v___y_5175_; uint32_t v___y_5176_; uint8_t v___y_5177_; uint64_t v___y_5178_; uint64_t v___y_5179_; uint64_t v___y_5189_; uint32_t v___y_5190_; uint8_t v___y_5191_; uint64_t v___y_5192_; uint8_t v___y_5193_; uint64_t v___y_5194_; uint32_t v___y_5201_; uint8_t v___y_5202_; uint64_t v___y_5203_; uint64_t v___y_5204_; uint64_t v___y_5205_; uint32_t v___y_5211_; uint8_t v___y_5212_; uint64_t v___y_5213_; uint64_t v___y_5214_; uint64_t v___y_5215_; uint64_t v___y_5216_; uint32_t v___y_5271_; uint8_t v___y_5272_; uint64_t v___y_5273_; uint64_t v___y_5274_; uint64_t v___y_5275_; uint64_t v___y_5276_; uint64_t v___y_5277_; uint32_t v___y_5283_; uint8_t v___y_5284_; uint64_t v___y_5285_; uint64_t v___y_5286_; uint64_t v___y_5287_; uint64_t v___y_5288_; uint64_t v___y_5289_; uint64_t v___y_5290_; uint64_t v___y_5291_; uint32_t v___y_5296_; uint8_t v___y_5297_; uint64_t v___y_5298_; uint64_t v___y_5299_; uint64_t v___y_5300_; uint64_t v___y_5301_; uint64_t v___y_5302_; uint32_t v___y_5307_; uint64_t v___y_5308_; uint8_t v___y_5309_; uint64_t v___y_5310_; uint64_t v___y_5311_; uint64_t v___y_5312_; uint64_t v___y_5313_; uint64_t v___y_5314_; uint64_t v___y_5315_; uint32_t v___y_5320_; uint8_t v___y_5321_; uint64_t v___y_5322_; uint64_t v___y_5323_; uint64_t v___y_5324_; uint64_t v___y_5325_; uint64_t v___y_5326_; uint32_t v___y_5331_; uint8_t v___y_5332_; uint64_t v___y_5333_; uint64_t v___y_5334_; uint64_t v___y_5335_; uint64_t v___y_5336_; uint64_t v___y_5337_; uint64_t v___y_5338_; uint64_t v___y_5339_; uint32_t v___y_5344_; uint8_t v___y_5345_; uint64_t v___y_5346_; uint64_t v___y_5347_; uint64_t v___y_5348_; uint64_t v___y_5349_; uint64_t v___y_5350_; uint64_t v___y_5355_; uint64_t v___y_5356_; uint32_t v___y_5357_; uint8_t v___y_5358_; uint64_t v___y_5359_; uint64_t v___y_5360_; uint64_t v___y_5361_; uint64_t v___y_5362_; uint64_t v___y_5363_; uint32_t v___y_5368_; uint8_t v___y_5369_; uint64_t v___y_5370_; uint64_t v___y_5371_; uint64_t v___y_5372_; uint64_t v___y_5373_; uint64_t v___y_5374_; uint32_t v___y_5379_; uint8_t v___y_5380_; uint64_t v___y_5381_; uint64_t v___y_5382_; uint64_t v___y_5383_; uint64_t v___y_5384_; uint64_t v___y_5385_; uint32_t v___y_5389_; uint8_t v___y_5390_; uint64_t v___y_5391_; uint64_t v___y_5392_; uint32_t v___y_5401_; uint8_t v___y_5402_; uint64_t v___y_5403_; uint64_t v___y_5404_; uint64_t v___y_5405_; uint64_t v___y_5406_; uint32_t v_eu_5439_; uint32_t v___x_5440_; uint32_t v___x_5441_; uint32_t v___x_5442_; uint8_t v___x_5443_; 
v___x_4551_ = 23;
v___x_4552_ = lean_uint32_shift_right(v_x_4114_, v___x_4551_);
v___x_4592_ = 255;
v_eu_5439_ = lean_uint32_land(v___x_4552_, v___x_4592_);
v___x_5440_ = 1;
v___x_5441_ = lean_uint32_sub(v_eu_5439_, v___x_5440_);
v___x_5442_ = 253;
v___x_5443_ = lean_uint32_dec_le(v___x_5441_, v___x_5442_);
if (v___x_5443_ == 0)
{
uint32_t v___x_5444_; uint32_t v_ey_5445_; uint64_t v___y_5447_; uint8_t v___y_5448_; uint32_t v___y_5449_; uint64_t v___y_5450_; uint64_t v___y_5451_; uint64_t v___y_5458_; uint8_t v___y_5459_; uint32_t v___y_5460_; uint64_t v___y_5461_; uint32_t v___y_5468_; uint8_t v___y_5469_; uint32_t v___y_5470_; uint64_t v___y_5471_; uint8_t v___y_5479_; uint32_t v___x_5489_; uint32_t v___x_5490_; uint8_t v___x_5491_; uint8_t v___y_5493_; uint8_t v___y_5494_; uint8_t v___y_5495_; uint8_t v___y_5497_; uint8_t v___y_5498_; uint8_t v___y_5504_; 
v___x_5444_ = lean_uint32_shift_right(v_y_4115_, v___x_4551_);
v_ey_5445_ = lean_uint32_land(v___x_5444_, v___x_4592_);
v___x_5489_ = lean_uint32_add(v_eu_5439_, v_ey_5445_);
v___x_5490_ = 128;
v___x_5491_ = lean_uint32_dec_lt(v___x_5489_, v___x_5490_);
if (v___x_5491_ == 0)
{
uint32_t v___x_5514_; uint32_t v_a_5515_; uint32_t v___x_5516_; uint32_t v___x_5517_; uint8_t v___x_5518_; 
v___x_5514_ = 2147483647;
v_a_5515_ = lean_uint32_land(v_x_4114_, v___x_5514_);
v___x_5516_ = 201326591;
v___x_5517_ = lean_uint32_sub(v_a_5515_, v___x_5440_);
v___x_5518_ = lean_uint32_dec_le(v___x_5516_, v___x_5517_);
if (v___x_5518_ == 0)
{
v___y_4554_ = v___x_5518_;
goto v___jp_4553_;
}
else
{
uint32_t v___x_5519_; uint8_t v___x_5520_; 
v___x_5519_ = 2139095040;
v___x_5520_ = lean_uint32_dec_lt(v_a_5515_, v___x_5519_);
v___y_4554_ = v___x_5520_;
goto v___jp_4553_;
}
}
else
{
uint32_t v___x_5521_; uint32_t v___x_5522_; uint8_t v___x_5523_; 
v___x_5521_ = 4278190080;
v___x_5522_ = lean_uint32_shift_left(v_x_4114_, v___x_5440_);
v___x_5523_ = lean_uint32_dec_le(v___x_5521_, v___x_5522_);
if (v___x_5523_ == 0)
{
uint32_t v___x_5524_; uint8_t v___x_5525_; 
v___x_5524_ = lean_uint32_shift_left(v_y_4115_, v___x_5440_);
v___x_5525_ = lean_uint32_dec_le(v___x_5521_, v___x_5524_);
v___y_5504_ = v___x_5525_;
goto v___jp_5503_;
}
else
{
v___y_5504_ = v___x_5523_;
goto v___jp_5503_;
}
}
v___jp_5446_:
{
uint64_t v___x_5452_; uint64_t v___x_5453_; uint8_t v___x_5454_; 
v___x_5452_ = lean_uint32_to_uint64(v_ey_5445_);
v___x_5453_ = 0ULL;
v___x_5454_ = lean_uint64_dec_eq(v___x_5452_, v___x_5453_);
if (v___x_5454_ == 0)
{
uint64_t v___x_5455_; uint64_t v___x_5456_; 
v___x_5455_ = 1ULL;
v___x_5456_ = lean_uint64_sub(v___x_5452_, v___x_5455_);
v___y_4837_ = v___y_5447_;
v___y_4838_ = v___y_5448_;
v___y_4839_ = v___y_5449_;
v___y_4840_ = v___y_5451_;
v___y_4841_ = v___y_5450_;
v___y_4842_ = v___x_5456_;
goto v___jp_4836_;
}
else
{
v___y_4837_ = v___y_5447_;
v___y_4838_ = v___y_5448_;
v___y_4839_ = v___y_5449_;
v___y_4840_ = v___y_5451_;
v___y_4841_ = v___y_5450_;
v___y_4842_ = v___x_5453_;
goto v___jp_4836_;
}
}
v___jp_5457_:
{
uint64_t v___x_5462_; uint64_t v___x_5463_; uint8_t v___x_5464_; 
v___x_5462_ = lean_uint32_to_uint64(v_eu_5439_);
v___x_5463_ = 0ULL;
v___x_5464_ = lean_uint64_dec_eq(v___x_5462_, v___x_5463_);
if (v___x_5464_ == 0)
{
uint64_t v___x_5465_; uint64_t v___x_5466_; 
v___x_5465_ = 1ULL;
v___x_5466_ = lean_uint64_sub(v___x_5462_, v___x_5465_);
v___y_5447_ = v___y_5458_;
v___y_5448_ = v___y_5459_;
v___y_5449_ = v___y_5460_;
v___y_5450_ = v___y_5461_;
v___y_5451_ = v___x_5466_;
goto v___jp_5446_;
}
else
{
v___y_5447_ = v___y_5458_;
v___y_5448_ = v___y_5459_;
v___y_5449_ = v___y_5460_;
v___y_5450_ = v___y_5461_;
v___y_5451_ = v___x_5463_;
goto v___jp_5446_;
}
}
v___jp_5467_:
{
uint32_t v___x_5472_; uint8_t v___x_5473_; 
v___x_5472_ = 0;
v___x_5473_ = lean_uint32_dec_eq(v_ey_5445_, v___x_5472_);
if (v___x_5473_ == 0)
{
uint64_t v___x_5474_; uint64_t v___x_5475_; uint64_t v___x_5476_; 
v___x_5474_ = lean_uint32_to_uint64(v___y_5468_);
v___x_5475_ = 8388608ULL;
v___x_5476_ = lean_uint64_lor(v___x_5474_, v___x_5475_);
v___y_5458_ = v___y_5471_;
v___y_5459_ = v___y_5469_;
v___y_5460_ = v___y_5470_;
v___y_5461_ = v___x_5476_;
goto v___jp_5457_;
}
else
{
uint64_t v___x_5477_; 
v___x_5477_ = lean_uint32_to_uint64(v___y_5468_);
v___y_5458_ = v___y_5471_;
v___y_5459_ = v___y_5469_;
v___y_5460_ = v___y_5470_;
v___y_5461_ = v___x_5477_;
goto v___jp_5457_;
}
}
v___jp_5478_:
{
uint32_t v___x_5480_; uint32_t v_xFraction_5481_; uint32_t v_yFraction_5482_; uint32_t v___x_5483_; uint8_t v___x_5484_; 
v___x_5480_ = 8388607;
v_xFraction_5481_ = lean_uint32_land(v_x_4114_, v___x_5480_);
v_yFraction_5482_ = lean_uint32_land(v_y_4115_, v___x_5480_);
v___x_5483_ = 0;
v___x_5484_ = lean_uint32_dec_eq(v_eu_5439_, v___x_5483_);
if (v___x_5484_ == 0)
{
uint64_t v___x_5485_; uint64_t v___x_5486_; uint64_t v___x_5487_; 
v___x_5485_ = lean_uint32_to_uint64(v_xFraction_5481_);
v___x_5486_ = 8388608ULL;
v___x_5487_ = lean_uint64_lor(v___x_5485_, v___x_5486_);
v___y_5468_ = v_yFraction_5482_;
v___y_5469_ = v___y_5479_;
v___y_5470_ = v___x_5480_;
v___y_5471_ = v___x_5487_;
goto v___jp_5467_;
}
else
{
uint64_t v___x_5488_; 
v___x_5488_ = lean_uint32_to_uint64(v_xFraction_5481_);
v___y_5468_ = v_yFraction_5482_;
v___y_5469_ = v___y_5479_;
v___y_5470_ = v___x_5480_;
v___y_5471_ = v___x_5488_;
goto v___jp_5467_;
}
}
v___jp_5492_:
{
if (v___y_5494_ == 0)
{
if (v___y_5495_ == 0)
{
v___y_5479_ = v___y_5493_;
goto v___jp_5478_;
}
else
{
v___y_5479_ = v___x_5491_;
goto v___jp_5478_;
}
}
else
{
if (v___y_5495_ == 0)
{
v___y_5479_ = v___x_5491_;
goto v___jp_5478_;
}
else
{
v___y_5479_ = v___y_5493_;
goto v___jp_5478_;
}
}
}
v___jp_5496_:
{
uint32_t v___x_5499_; uint32_t v___x_5500_; uint32_t v___x_5501_; uint8_t v___x_5502_; 
v___x_5499_ = 2147483648;
v___x_5500_ = lean_uint32_land(v_y_4115_, v___x_5499_);
v___x_5501_ = 0;
v___x_5502_ = lean_uint32_dec_eq(v___x_5500_, v___x_5501_);
if (v___x_5502_ == 0)
{
v___y_5493_ = v___y_5497_;
v___y_5494_ = v___y_5498_;
v___y_5495_ = v___x_5491_;
goto v___jp_5492_;
}
else
{
v___y_5493_ = v___y_5497_;
v___y_5494_ = v___y_5498_;
v___y_5495_ = v___y_5497_;
goto v___jp_5492_;
}
}
v___jp_5503_:
{
if (v___y_5504_ == 0)
{
uint32_t v___x_5505_; uint32_t v___x_5506_; uint32_t v___x_5507_; uint8_t v___x_5508_; 
v___x_5505_ = 2147483648;
v___x_5506_ = lean_uint32_land(v_x_4114_, v___x_5505_);
v___x_5507_ = 0;
v___x_5508_ = lean_uint32_dec_eq(v___x_5506_, v___x_5507_);
if (v___x_5508_ == 0)
{
v___y_5497_ = v___y_5504_;
v___y_5498_ = v___x_5491_;
goto v___jp_5496_;
}
else
{
v___y_5497_ = v___y_5504_;
v___y_5498_ = v___y_5504_;
goto v___jp_5496_;
}
}
else
{
lean_object* v___x_5509_; lean_object* v___x_5510_; lean_object* v___x_5511_; lean_object* v___x_5512_; uint32_t v___x_5513_; 
v___x_5509_ = ((lean_object*)(lp_competition_r22CostInlineOldMul___closed__0));
v___x_5510_ = lean_uint32_to_nat(v_x_4114_);
v___x_5511_ = lean_uint32_to_nat(v_y_4115_);
v___x_5512_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word(v___x_5509_, v___x_5510_, v___x_5511_);
v___x_5513_ = lean_uint32_of_nat(v___x_5512_);
lean_dec(v___x_5512_);
return v___x_5513_;
}
}
}
else
{
uint32_t v___x_5526_; uint32_t v_ev_5527_; uint64_t v___y_5529_; uint64_t v___y_5530_; uint32_t v___y_5531_; uint8_t v___y_5532_; uint64_t v___y_5533_; uint64_t v___y_5540_; uint8_t v___y_5541_; uint32_t v___y_5542_; uint64_t v___y_5543_; uint32_t v___y_5550_; uint8_t v___y_5551_; uint32_t v___y_5552_; uint64_t v___y_5553_; uint8_t v___y_5561_; uint8_t v___y_5572_; uint8_t v___y_5573_; uint8_t v___y_5575_; uint8_t v___y_5576_; uint8_t v___y_5577_; uint8_t v___y_5579_; uint8_t v___y_5580_; uint8_t v___y_5586_; uint32_t v___y_5597_; uint8_t v___y_5598_; uint64_t v___y_5599_; uint64_t v___y_5600_; uint64_t v___y_5601_; uint32_t v___y_5608_; uint8_t v___y_5609_; uint64_t v___y_5610_; uint64_t v___y_5611_; uint32_t v___y_5618_; uint8_t v___y_5619_; uint32_t v___y_5620_; uint64_t v___y_5621_; uint8_t v___y_5629_; uint32_t v___x_5639_; uint8_t v___x_5640_; uint8_t v___y_5642_; uint8_t v___y_5643_; uint8_t v___y_5645_; uint8_t v___y_5646_; uint8_t v___y_5647_; uint8_t v___y_5649_; uint8_t v___y_5650_; uint8_t v___y_5656_; 
v___x_5526_ = lean_uint32_shift_right(v_y_4115_, v___x_4551_);
v_ev_5527_ = lean_uint32_land(v___x_5526_, v___x_4592_);
v___x_5639_ = lean_uint32_sub(v_ev_5527_, v___x_5440_);
v___x_5640_ = lean_uint32_dec_le(v___x_5639_, v___x_5442_);
if (v___x_5640_ == 0)
{
uint32_t v___x_5666_; uint32_t v___x_5667_; uint8_t v___x_5668_; 
v___x_5666_ = lean_uint32_add(v_eu_5439_, v_ev_5527_);
v___x_5667_ = 128;
v___x_5668_ = lean_uint32_dec_lt(v___x_5666_, v___x_5667_);
if (v___x_5668_ == 0)
{
uint32_t v___x_5669_; uint32_t v_a_5670_; uint32_t v___x_5671_; uint32_t v___x_5672_; uint8_t v___x_5673_; 
v___x_5669_ = 2147483647;
v_a_5670_ = lean_uint32_land(v_x_4114_, v___x_5669_);
v___x_5671_ = 201326591;
v___x_5672_ = lean_uint32_sub(v_a_5670_, v___x_5440_);
v___x_5673_ = lean_uint32_dec_le(v___x_5671_, v___x_5672_);
if (v___x_5673_ == 0)
{
v___y_4567_ = v___x_5673_;
goto v___jp_4566_;
}
else
{
uint32_t v___x_5674_; uint8_t v___x_5675_; 
v___x_5674_ = 2139095040;
v___x_5675_ = lean_uint32_dec_lt(v_a_5670_, v___x_5674_);
v___y_4567_ = v___x_5675_;
goto v___jp_4566_;
}
}
else
{
uint32_t v___x_5676_; uint32_t v___x_5677_; uint8_t v___x_5678_; 
v___x_5676_ = 4278190080;
v___x_5677_ = lean_uint32_shift_left(v_x_4114_, v___x_5440_);
v___x_5678_ = lean_uint32_dec_le(v___x_5676_, v___x_5677_);
if (v___x_5678_ == 0)
{
uint32_t v___x_5679_; uint8_t v___x_5680_; 
v___x_5679_ = lean_uint32_shift_left(v_y_4115_, v___x_5440_);
v___x_5680_ = lean_uint32_dec_le(v___x_5676_, v___x_5679_);
v___y_5586_ = v___x_5680_;
goto v___jp_5585_;
}
else
{
v___y_5586_ = v___x_5678_;
goto v___jp_5585_;
}
}
}
else
{
uint32_t v_s_5681_; uint32_t v___x_5682_; uint32_t v___x_5683_; uint32_t v___x_5684_; uint8_t v___x_5685_; 
v_s_5681_ = lean_uint32_add(v_eu_5439_, v_ev_5527_);
v___x_5682_ = 174;
v___x_5683_ = lean_uint32_sub(v_s_5681_, v___x_5682_);
v___x_5684_ = 206;
v___x_5685_ = lean_uint32_dec_le(v___x_5683_, v___x_5684_);
if (v___x_5685_ == 0)
{
uint32_t v___x_5686_; uint8_t v___x_5687_; 
v___x_5686_ = 128;
v___x_5687_ = lean_uint32_dec_lt(v_s_5681_, v___x_5686_);
if (v___x_5687_ == 0)
{
uint32_t v___x_5688_; uint32_t v_a_5689_; uint32_t v___x_5690_; uint32_t v___x_5691_; uint8_t v___x_5692_; 
v___x_5688_ = 2147483647;
v_a_5689_ = lean_uint32_land(v_x_4114_, v___x_5688_);
v___x_5690_ = 201326591;
v___x_5691_ = lean_uint32_sub(v_a_5689_, v___x_5440_);
v___x_5692_ = lean_uint32_dec_le(v___x_5690_, v___x_5691_);
if (v___x_5692_ == 0)
{
v___y_4580_ = v___x_5692_;
goto v___jp_4579_;
}
else
{
uint32_t v___x_5693_; uint8_t v___x_5694_; 
v___x_5693_ = 2139095040;
v___x_5694_ = lean_uint32_dec_lt(v_a_5689_, v___x_5693_);
v___y_4580_ = v___x_5694_;
goto v___jp_4579_;
}
}
else
{
uint32_t v___x_5695_; uint32_t v___x_5696_; uint8_t v___x_5697_; 
v___x_5695_ = 4278190080;
v___x_5696_ = lean_uint32_shift_left(v_x_4114_, v___x_5440_);
v___x_5697_ = lean_uint32_dec_le(v___x_5695_, v___x_5696_);
if (v___x_5697_ == 0)
{
uint32_t v___x_5698_; uint8_t v___x_5699_; 
v___x_5698_ = lean_uint32_shift_left(v_y_4115_, v___x_5440_);
v___x_5699_ = lean_uint32_dec_le(v___x_5695_, v___x_5698_);
v___y_5656_ = v___x_5699_;
goto v___jp_5655_;
}
else
{
v___y_5656_ = v___x_5697_;
goto v___jp_5655_;
}
}
}
else
{
uint32_t v___x_5700_; uint32_t v___x_5701_; uint32_t v___x_5702_; uint32_t v_a_5703_; uint32_t v___x_5704_; uint32_t v_b_5705_; uint64_t v___x_5706_; uint64_t v___x_5707_; uint64_t v_p_5708_; uint32_t v___x_5709_; uint32_t v___x_5710_; uint32_t v___x_5711_; uint32_t v___x_5712_; uint32_t v___x_5713_; uint32_t v___x_5714_; uint32_t v_w_5715_; float v___x_5716_; lean_object* v___x_5717_; uint32_t v___x_5718_; lean_object* v___x_5719_; lean_object* v___x_5720_; float v___x_5721_; float v___x_5722_; uint32_t v___x_5723_; 
v___x_5700_ = 8388607;
v___x_5701_ = lean_uint32_land(v_x_4114_, v___x_5700_);
v___x_5702_ = 8388608;
v_a_5703_ = lean_uint32_lor(v___x_5701_, v___x_5702_);
v___x_5704_ = lean_uint32_land(v_y_4115_, v___x_5700_);
v_b_5705_ = lean_uint32_lor(v___x_5704_, v___x_5702_);
v___x_5706_ = lean_uint32_to_uint64(v_a_5703_);
v___x_5707_ = lean_uint32_to_uint64(v_b_5705_);
v_p_5708_ = lean_uint64_mul(v___x_5706_, v___x_5707_);
v___x_5709_ = 150;
v___x_5710_ = lean_uint32_sub(v_s_5681_, v___x_5709_);
v___x_5711_ = lean_uint32_shift_left(v___x_5710_, v___x_4551_);
v___x_5712_ = lean_uint32_xor(v_x_4114_, v_y_4115_);
v___x_5713_ = 2147483648;
v___x_5714_ = lean_uint32_land(v___x_5712_, v___x_5713_);
v_w_5715_ = lean_uint32_lor(v___x_5711_, v___x_5714_);
v___x_5716_ = lean_uint64_to_float32(v_p_5708_);
v___x_5717_ = lp_competition_R2W01b_scaleTable;
v___x_5718_ = lean_uint32_shift_right(v_w_5715_, v___x_4551_);
v___x_5719_ = lean_uint32_to_nat(v___x_5718_);
v___x_5720_ = lean_array_fget_borrowed(v___x_5717_, v___x_5719_);
lean_dec(v___x_5719_);
v___x_5721_ = lean_unbox_float32(v___x_5720_);
v___x_5722_ = lean_float32_mul(v___x_5716_, v___x_5721_);
v___x_5723_ = lean_float32_to_bits(v___x_5722_);
return v___x_5723_;
}
}
v___jp_5528_:
{
uint64_t v___x_5534_; uint64_t v___x_5535_; uint8_t v___x_5536_; 
v___x_5534_ = lean_uint32_to_uint64(v_ev_5527_);
v___x_5535_ = 0ULL;
v___x_5536_ = lean_uint64_dec_eq(v___x_5534_, v___x_5535_);
if (v___x_5536_ == 0)
{
uint64_t v___x_5537_; uint64_t v___x_5538_; 
v___x_5537_ = 1ULL;
v___x_5538_ = lean_uint64_sub(v___x_5534_, v___x_5537_);
v___y_5119_ = v___y_5533_;
v___y_5120_ = v___y_5529_;
v___y_5121_ = v___y_5530_;
v___y_5122_ = v___y_5532_;
v___y_5123_ = v___y_5531_;
v___y_5124_ = v___x_5538_;
goto v___jp_5118_;
}
else
{
v___y_5119_ = v___y_5533_;
v___y_5120_ = v___y_5529_;
v___y_5121_ = v___y_5530_;
v___y_5122_ = v___y_5532_;
v___y_5123_ = v___y_5531_;
v___y_5124_ = v___x_5535_;
goto v___jp_5118_;
}
}
v___jp_5539_:
{
uint64_t v___x_5544_; uint64_t v___x_5545_; uint8_t v___x_5546_; 
v___x_5544_ = lean_uint32_to_uint64(v_eu_5439_);
v___x_5545_ = 0ULL;
v___x_5546_ = lean_uint64_dec_eq(v___x_5544_, v___x_5545_);
if (v___x_5546_ == 0)
{
uint64_t v___x_5547_; uint64_t v___x_5548_; 
v___x_5547_ = 1ULL;
v___x_5548_ = lean_uint64_sub(v___x_5544_, v___x_5547_);
v___y_5529_ = v___y_5540_;
v___y_5530_ = v___y_5543_;
v___y_5531_ = v___y_5542_;
v___y_5532_ = v___y_5541_;
v___y_5533_ = v___x_5548_;
goto v___jp_5528_;
}
else
{
v___y_5529_ = v___y_5540_;
v___y_5530_ = v___y_5543_;
v___y_5531_ = v___y_5542_;
v___y_5532_ = v___y_5541_;
v___y_5533_ = v___x_5545_;
goto v___jp_5528_;
}
}
v___jp_5549_:
{
uint32_t v___x_5554_; uint8_t v___x_5555_; 
v___x_5554_ = 0;
v___x_5555_ = lean_uint32_dec_eq(v_ev_5527_, v___x_5554_);
if (v___x_5555_ == 0)
{
uint64_t v___x_5556_; uint64_t v___x_5557_; uint64_t v___x_5558_; 
v___x_5556_ = lean_uint32_to_uint64(v___y_5552_);
v___x_5557_ = 8388608ULL;
v___x_5558_ = lean_uint64_lor(v___x_5556_, v___x_5557_);
v___y_5540_ = v___y_5553_;
v___y_5541_ = v___y_5551_;
v___y_5542_ = v___y_5550_;
v___y_5543_ = v___x_5558_;
goto v___jp_5539_;
}
else
{
uint64_t v___x_5559_; 
v___x_5559_ = lean_uint32_to_uint64(v___y_5552_);
v___y_5540_ = v___y_5553_;
v___y_5541_ = v___y_5551_;
v___y_5542_ = v___y_5550_;
v___y_5543_ = v___x_5559_;
goto v___jp_5539_;
}
}
v___jp_5560_:
{
uint32_t v___x_5562_; uint32_t v_xFraction_5563_; uint32_t v_yFraction_5564_; uint32_t v___x_5565_; uint8_t v___x_5566_; 
v___x_5562_ = 8388607;
v_xFraction_5563_ = lean_uint32_land(v_x_4114_, v___x_5562_);
v_yFraction_5564_ = lean_uint32_land(v_y_4115_, v___x_5562_);
v___x_5565_ = 0;
v___x_5566_ = lean_uint32_dec_eq(v_eu_5439_, v___x_5565_);
if (v___x_5566_ == 0)
{
uint64_t v___x_5567_; uint64_t v___x_5568_; uint64_t v___x_5569_; 
v___x_5567_ = lean_uint32_to_uint64(v_xFraction_5563_);
v___x_5568_ = 8388608ULL;
v___x_5569_ = lean_uint64_lor(v___x_5567_, v___x_5568_);
v___y_5550_ = v___x_5562_;
v___y_5551_ = v___y_5561_;
v___y_5552_ = v_yFraction_5564_;
v___y_5553_ = v___x_5569_;
goto v___jp_5549_;
}
else
{
uint64_t v___x_5570_; 
v___x_5570_ = lean_uint32_to_uint64(v_xFraction_5563_);
v___y_5550_ = v___x_5562_;
v___y_5551_ = v___y_5561_;
v___y_5552_ = v_yFraction_5564_;
v___y_5553_ = v___x_5570_;
goto v___jp_5549_;
}
}
v___jp_5571_:
{
if (v___y_5573_ == 0)
{
v___y_5561_ = v___x_5443_;
goto v___jp_5560_;
}
else
{
v___y_5561_ = v___y_5572_;
goto v___jp_5560_;
}
}
v___jp_5574_:
{
if (v___y_5576_ == 0)
{
if (v___y_5577_ == 0)
{
v___y_5572_ = v___y_5575_;
v___y_5573_ = v___x_5443_;
goto v___jp_5571_;
}
else
{
v___y_5561_ = v___x_5443_;
goto v___jp_5560_;
}
}
else
{
v___y_5572_ = v___y_5575_;
v___y_5573_ = v___y_5577_;
goto v___jp_5571_;
}
}
v___jp_5578_:
{
uint32_t v___x_5581_; uint32_t v___x_5582_; uint32_t v___x_5583_; uint8_t v___x_5584_; 
v___x_5581_ = 2147483648;
v___x_5582_ = lean_uint32_land(v_y_4115_, v___x_5581_);
v___x_5583_ = 0;
v___x_5584_ = lean_uint32_dec_eq(v___x_5582_, v___x_5583_);
if (v___x_5584_ == 0)
{
v___y_5575_ = v___y_5579_;
v___y_5576_ = v___y_5580_;
v___y_5577_ = v___x_5443_;
goto v___jp_5574_;
}
else
{
v___y_5575_ = v___y_5579_;
v___y_5576_ = v___y_5580_;
v___y_5577_ = v___y_5579_;
goto v___jp_5574_;
}
}
v___jp_5585_:
{
if (v___y_5586_ == 0)
{
uint32_t v___x_5587_; uint32_t v___x_5588_; uint32_t v___x_5589_; uint8_t v___x_5590_; 
v___x_5587_ = 2147483648;
v___x_5588_ = lean_uint32_land(v_x_4114_, v___x_5587_);
v___x_5589_ = 0;
v___x_5590_ = lean_uint32_dec_eq(v___x_5588_, v___x_5589_);
if (v___x_5590_ == 0)
{
v___y_5579_ = v___y_5586_;
v___y_5580_ = v___x_5443_;
goto v___jp_5578_;
}
else
{
v___y_5579_ = v___y_5586_;
v___y_5580_ = v___y_5586_;
goto v___jp_5578_;
}
}
else
{
lean_object* v___x_5591_; lean_object* v___x_5592_; lean_object* v___x_5593_; lean_object* v___x_5594_; uint32_t v___x_5595_; 
v___x_5591_ = ((lean_object*)(lp_competition_r22CostInlineOldMul___closed__0));
v___x_5592_ = lean_uint32_to_nat(v_x_4114_);
v___x_5593_ = lean_uint32_to_nat(v_y_4115_);
v___x_5594_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word(v___x_5591_, v___x_5592_, v___x_5593_);
v___x_5595_ = lean_uint32_of_nat(v___x_5594_);
lean_dec(v___x_5594_);
return v___x_5595_;
}
}
v___jp_5596_:
{
uint64_t v___x_5602_; uint64_t v___x_5603_; uint8_t v___x_5604_; 
v___x_5602_ = lean_uint32_to_uint64(v_ev_5527_);
v___x_5603_ = 0ULL;
v___x_5604_ = lean_uint64_dec_eq(v___x_5602_, v___x_5603_);
if (v___x_5604_ == 0)
{
uint64_t v___x_5605_; uint64_t v___x_5606_; 
v___x_5605_ = 1ULL;
v___x_5606_ = lean_uint64_sub(v___x_5602_, v___x_5605_);
v___y_5401_ = v___y_5597_;
v___y_5402_ = v___y_5598_;
v___y_5403_ = v___y_5599_;
v___y_5404_ = v___y_5601_;
v___y_5405_ = v___y_5600_;
v___y_5406_ = v___x_5606_;
goto v___jp_5400_;
}
else
{
v___y_5401_ = v___y_5597_;
v___y_5402_ = v___y_5598_;
v___y_5403_ = v___y_5599_;
v___y_5404_ = v___y_5601_;
v___y_5405_ = v___y_5600_;
v___y_5406_ = v___x_5603_;
goto v___jp_5400_;
}
}
v___jp_5607_:
{
uint64_t v___x_5612_; uint64_t v___x_5613_; uint8_t v___x_5614_; 
v___x_5612_ = lean_uint32_to_uint64(v_eu_5439_);
v___x_5613_ = 0ULL;
v___x_5614_ = lean_uint64_dec_eq(v___x_5612_, v___x_5613_);
if (v___x_5614_ == 0)
{
uint64_t v___x_5615_; uint64_t v___x_5616_; 
v___x_5615_ = 1ULL;
v___x_5616_ = lean_uint64_sub(v___x_5612_, v___x_5615_);
v___y_5597_ = v___y_5608_;
v___y_5598_ = v___y_5609_;
v___y_5599_ = v___y_5610_;
v___y_5600_ = v___y_5611_;
v___y_5601_ = v___x_5616_;
goto v___jp_5596_;
}
else
{
v___y_5597_ = v___y_5608_;
v___y_5598_ = v___y_5609_;
v___y_5599_ = v___y_5610_;
v___y_5600_ = v___y_5611_;
v___y_5601_ = v___x_5613_;
goto v___jp_5596_;
}
}
v___jp_5617_:
{
uint32_t v___x_5622_; uint8_t v___x_5623_; 
v___x_5622_ = 0;
v___x_5623_ = lean_uint32_dec_eq(v_ev_5527_, v___x_5622_);
if (v___x_5623_ == 0)
{
uint64_t v___x_5624_; uint64_t v___x_5625_; uint64_t v___x_5626_; 
v___x_5624_ = lean_uint32_to_uint64(v___y_5620_);
v___x_5625_ = 8388608ULL;
v___x_5626_ = lean_uint64_lor(v___x_5624_, v___x_5625_);
v___y_5608_ = v___y_5618_;
v___y_5609_ = v___y_5619_;
v___y_5610_ = v___y_5621_;
v___y_5611_ = v___x_5626_;
goto v___jp_5607_;
}
else
{
uint64_t v___x_5627_; 
v___x_5627_ = lean_uint32_to_uint64(v___y_5620_);
v___y_5608_ = v___y_5618_;
v___y_5609_ = v___y_5619_;
v___y_5610_ = v___y_5621_;
v___y_5611_ = v___x_5627_;
goto v___jp_5607_;
}
}
v___jp_5628_:
{
uint32_t v___x_5630_; uint32_t v_xFraction_5631_; uint32_t v_yFraction_5632_; uint32_t v___x_5633_; uint8_t v___x_5634_; 
v___x_5630_ = 8388607;
v_xFraction_5631_ = lean_uint32_land(v_x_4114_, v___x_5630_);
v_yFraction_5632_ = lean_uint32_land(v_y_4115_, v___x_5630_);
v___x_5633_ = 0;
v___x_5634_ = lean_uint32_dec_eq(v_eu_5439_, v___x_5633_);
if (v___x_5634_ == 0)
{
uint64_t v___x_5635_; uint64_t v___x_5636_; uint64_t v___x_5637_; 
v___x_5635_ = lean_uint32_to_uint64(v_xFraction_5631_);
v___x_5636_ = 8388608ULL;
v___x_5637_ = lean_uint64_lor(v___x_5635_, v___x_5636_);
v___y_5618_ = v___x_5630_;
v___y_5619_ = v___y_5629_;
v___y_5620_ = v_yFraction_5632_;
v___y_5621_ = v___x_5637_;
goto v___jp_5617_;
}
else
{
uint64_t v___x_5638_; 
v___x_5638_ = lean_uint32_to_uint64(v_xFraction_5631_);
v___y_5618_ = v___x_5630_;
v___y_5619_ = v___y_5629_;
v___y_5620_ = v_yFraction_5632_;
v___y_5621_ = v___x_5638_;
goto v___jp_5617_;
}
}
v___jp_5641_:
{
if (v___y_5643_ == 0)
{
v___y_5629_ = v___x_5640_;
goto v___jp_5628_;
}
else
{
v___y_5629_ = v___y_5642_;
goto v___jp_5628_;
}
}
v___jp_5644_:
{
if (v___y_5645_ == 0)
{
if (v___y_5647_ == 0)
{
v___y_5642_ = v___y_5646_;
v___y_5643_ = v___x_5640_;
goto v___jp_5641_;
}
else
{
v___y_5629_ = v___x_5640_;
goto v___jp_5628_;
}
}
else
{
v___y_5642_ = v___y_5646_;
v___y_5643_ = v___y_5647_;
goto v___jp_5641_;
}
}
v___jp_5648_:
{
uint32_t v___x_5651_; uint32_t v___x_5652_; uint32_t v___x_5653_; uint8_t v___x_5654_; 
v___x_5651_ = 2147483648;
v___x_5652_ = lean_uint32_land(v_y_4115_, v___x_5651_);
v___x_5653_ = 0;
v___x_5654_ = lean_uint32_dec_eq(v___x_5652_, v___x_5653_);
if (v___x_5654_ == 0)
{
v___y_5645_ = v___y_5650_;
v___y_5646_ = v___y_5649_;
v___y_5647_ = v___x_5640_;
goto v___jp_5644_;
}
else
{
v___y_5645_ = v___y_5650_;
v___y_5646_ = v___y_5649_;
v___y_5647_ = v___y_5649_;
goto v___jp_5644_;
}
}
v___jp_5655_:
{
if (v___y_5656_ == 0)
{
uint32_t v___x_5657_; uint32_t v___x_5658_; uint32_t v___x_5659_; uint8_t v___x_5660_; 
v___x_5657_ = 2147483648;
v___x_5658_ = lean_uint32_land(v_x_4114_, v___x_5657_);
v___x_5659_ = 0;
v___x_5660_ = lean_uint32_dec_eq(v___x_5658_, v___x_5659_);
if (v___x_5660_ == 0)
{
v___y_5649_ = v___y_5656_;
v___y_5650_ = v___x_5640_;
goto v___jp_5648_;
}
else
{
v___y_5649_ = v___y_5656_;
v___y_5650_ = v___y_5656_;
goto v___jp_5648_;
}
}
else
{
lean_object* v___x_5661_; lean_object* v___x_5662_; lean_object* v___x_5663_; lean_object* v___x_5664_; uint32_t v___x_5665_; 
v___x_5661_ = ((lean_object*)(lp_competition_r22CostInlineOldMul___closed__0));
v___x_5662_ = lean_uint32_to_nat(v_x_4114_);
v___x_5663_ = lean_uint32_to_nat(v_y_4115_);
v___x_5664_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word(v___x_5661_, v___x_5662_, v___x_5663_);
v___x_5665_ = lean_uint32_of_nat(v___x_5664_);
lean_dec(v___x_5664_);
return v___x_5665_;
}
}
}
v___jp_4116_:
{
if (v___y_4117_ == 0)
{
uint32_t v___x_4118_; 
v___x_4118_ = lp_competition_Submission_FastMul_mul(v_x_4114_, v_y_4115_);
return v___x_4118_;
}
else
{
uint32_t v___x_4119_; uint32_t v___x_4120_; 
v___x_4119_ = 4194304;
v___x_4120_ = lean_uint32_lor(v_y_4115_, v___x_4119_);
return v___x_4120_;
}
}
v___jp_4121_:
{
uint32_t v___x_4122_; uint32_t v___x_4123_; uint32_t v___x_4124_; uint32_t v___x_4125_; uint8_t v___x_4126_; 
v___x_4122_ = 23;
v___x_4123_ = lean_uint32_shift_right(v_y_4115_, v___x_4122_);
v___x_4124_ = 255;
v___x_4125_ = lean_uint32_land(v___x_4123_, v___x_4124_);
v___x_4126_ = lean_uint32_dec_eq(v___x_4125_, v___x_4124_);
if (v___x_4126_ == 0)
{
v___y_4117_ = v___x_4126_;
goto v___jp_4116_;
}
else
{
uint32_t v___x_4127_; uint32_t v___x_4128_; uint32_t v___x_4129_; uint8_t v___x_4130_; 
v___x_4127_ = 8388607;
v___x_4128_ = lean_uint32_land(v_y_4115_, v___x_4127_);
v___x_4129_ = 0;
v___x_4130_ = lean_uint32_dec_eq(v___x_4128_, v___x_4129_);
if (v___x_4130_ == 0)
{
v___y_4117_ = v___x_4126_;
goto v___jp_4116_;
}
else
{
uint32_t v___x_4131_; 
v___x_4131_ = lp_competition_Submission_FastMul_mul(v_x_4114_, v_y_4115_);
return v___x_4131_;
}
}
}
v___jp_4132_:
{
if (v___y_4133_ == 0)
{
goto v___jp_4121_;
}
else
{
uint32_t v___x_4134_; uint32_t v___x_4135_; 
v___x_4134_ = 4194304;
v___x_4135_ = lean_uint32_lor(v_x_4114_, v___x_4134_);
return v___x_4135_;
}
}
v___jp_4136_:
{
uint32_t v___x_4137_; uint32_t v___x_4138_; uint32_t v___x_4139_; uint32_t v___x_4140_; uint8_t v___x_4141_; 
v___x_4137_ = 23;
v___x_4138_ = lean_uint32_shift_right(v_x_4114_, v___x_4137_);
v___x_4139_ = 255;
v___x_4140_ = lean_uint32_land(v___x_4138_, v___x_4139_);
v___x_4141_ = lean_uint32_dec_eq(v___x_4140_, v___x_4139_);
if (v___x_4141_ == 0)
{
v___y_4133_ = v___x_4141_;
goto v___jp_4132_;
}
else
{
uint32_t v___x_4142_; uint32_t v___x_4143_; uint32_t v___x_4144_; uint8_t v___x_4145_; 
v___x_4142_ = 8388607;
v___x_4143_ = lean_uint32_land(v_x_4114_, v___x_4142_);
v___x_4144_ = 0;
v___x_4145_ = lean_uint32_dec_eq(v___x_4143_, v___x_4144_);
if (v___x_4145_ == 0)
{
v___y_4133_ = v___x_4141_;
goto v___jp_4132_;
}
else
{
goto v___jp_4121_;
}
}
}
v___jp_4146_:
{
if (v___y_4147_ == 0)
{
goto v___jp_4136_;
}
else
{
uint32_t v___x_4148_; uint32_t v___x_4149_; uint32_t v___x_4150_; uint8_t v___x_4151_; 
v___x_4148_ = 4194304;
v___x_4149_ = lean_uint32_land(v_y_4115_, v___x_4148_);
v___x_4150_ = 0;
v___x_4151_ = lean_uint32_dec_eq(v___x_4149_, v___x_4150_);
if (v___x_4151_ == 0)
{
goto v___jp_4136_;
}
else
{
uint32_t v___x_4152_; 
v___x_4152_ = lean_uint32_lor(v_y_4115_, v___x_4148_);
return v___x_4152_;
}
}
}
v___jp_4153_:
{
uint32_t v___x_4154_; uint32_t v___x_4155_; uint32_t v___x_4156_; uint32_t v___x_4157_; uint8_t v___x_4158_; 
v___x_4154_ = 23;
v___x_4155_ = lean_uint32_shift_right(v_y_4115_, v___x_4154_);
v___x_4156_ = 255;
v___x_4157_ = lean_uint32_land(v___x_4155_, v___x_4156_);
v___x_4158_ = lean_uint32_dec_eq(v___x_4157_, v___x_4156_);
if (v___x_4158_ == 0)
{
v___y_4147_ = v___x_4158_;
goto v___jp_4146_;
}
else
{
uint32_t v___x_4159_; uint32_t v___x_4160_; uint32_t v___x_4161_; uint8_t v___x_4162_; 
v___x_4159_ = 8388607;
v___x_4160_ = lean_uint32_land(v_y_4115_, v___x_4159_);
v___x_4161_ = 0;
v___x_4162_ = lean_uint32_dec_eq(v___x_4160_, v___x_4161_);
if (v___x_4162_ == 0)
{
v___y_4147_ = v___x_4158_;
goto v___jp_4146_;
}
else
{
goto v___jp_4136_;
}
}
}
v___jp_4163_:
{
if (v___y_4164_ == 0)
{
goto v___jp_4153_;
}
else
{
uint32_t v___x_4165_; uint32_t v___x_4166_; uint32_t v___x_4167_; uint8_t v___x_4168_; 
v___x_4165_ = 4194304;
v___x_4166_ = lean_uint32_land(v_x_4114_, v___x_4165_);
v___x_4167_ = 0;
v___x_4168_ = lean_uint32_dec_eq(v___x_4166_, v___x_4167_);
if (v___x_4168_ == 0)
{
goto v___jp_4153_;
}
else
{
uint32_t v___x_4169_; 
v___x_4169_ = lean_uint32_lor(v_x_4114_, v___x_4165_);
return v___x_4169_;
}
}
}
v___jp_4170_:
{
float v_result_4173_; uint8_t v___x_4174_; 
v_result_4173_ = lean_float32_mul(v___y_4171_, v___y_4172_);
v___x_4174_ = lean_float32_beq(v_result_4173_, v_result_4173_);
if (v___x_4174_ == 0)
{
uint32_t v___x_4175_; uint32_t v___x_4176_; uint32_t v___x_4177_; uint32_t v___x_4178_; uint8_t v___x_4179_; 
v___x_4175_ = 23;
v___x_4176_ = lean_uint32_shift_right(v_x_4114_, v___x_4175_);
v___x_4177_ = 255;
v___x_4178_ = lean_uint32_land(v___x_4176_, v___x_4177_);
v___x_4179_ = lean_uint32_dec_eq(v___x_4178_, v___x_4177_);
if (v___x_4179_ == 0)
{
v___y_4164_ = v___x_4179_;
goto v___jp_4163_;
}
else
{
uint32_t v___x_4180_; uint32_t v___x_4181_; uint32_t v___x_4182_; uint8_t v___x_4183_; 
v___x_4180_ = 8388607;
v___x_4181_ = lean_uint32_land(v_x_4114_, v___x_4180_);
v___x_4182_ = 0;
v___x_4183_ = lean_uint32_dec_eq(v___x_4181_, v___x_4182_);
if (v___x_4183_ == 0)
{
v___y_4164_ = v___x_4179_;
goto v___jp_4163_;
}
else
{
goto v___jp_4153_;
}
}
}
else
{
uint32_t v___x_4184_; 
v___x_4184_ = lean_float32_to_bits(v_result_4173_);
return v___x_4184_;
}
}
v___jp_4185_:
{
if (v___y_4187_ == 0)
{
float v___x_4188_; 
v___x_4188_ = lean_float32_of_bits(v_y_4115_);
v___y_4171_ = v___y_4186_;
v___y_4172_ = v___x_4188_;
goto v___jp_4170_;
}
else
{
uint32_t v___x_4189_; uint32_t v___x_4190_; uint32_t v___x_4191_; uint32_t v___x_4192_; float v___x_4193_; lean_object* v___x_4194_; uint32_t v___x_4195_; uint32_t v___x_4196_; lean_object* v___x_4197_; lean_object* v___x_4198_; float v___x_4199_; float v___x_4200_; 
v___x_4189_ = 8388607;
v___x_4190_ = lean_uint32_land(v_y_4115_, v___x_4189_);
v___x_4191_ = 8388608;
v___x_4192_ = lean_uint32_lor(v___x_4190_, v___x_4191_);
v___x_4193_ = lean_uint32_to_float32(v___x_4192_);
v___x_4194_ = lp_competition_R2W01b_scaleTable;
v___x_4195_ = 23;
v___x_4196_ = lean_uint32_shift_right(v_y_4115_, v___x_4195_);
v___x_4197_ = lean_uint32_to_nat(v___x_4196_);
v___x_4198_ = lean_array_fget_borrowed(v___x_4194_, v___x_4197_);
lean_dec(v___x_4197_);
v___x_4199_ = lean_unbox_float32(v___x_4198_);
v___x_4200_ = lean_float32_mul(v___x_4193_, v___x_4199_);
v___y_4171_ = v___y_4186_;
v___y_4172_ = v___x_4200_;
goto v___jp_4170_;
}
}
v___jp_4201_:
{
uint32_t v___x_4203_; uint32_t v_a_4204_; uint32_t v___x_4205_; uint32_t v___x_4206_; uint32_t v___x_4207_; uint8_t v___x_4208_; 
v___x_4203_ = 2147483647;
v_a_4204_ = lean_uint32_land(v_y_4115_, v___x_4203_);
v___x_4205_ = 201326591;
v___x_4206_ = 1;
v___x_4207_ = lean_uint32_sub(v_a_4204_, v___x_4206_);
v___x_4208_ = lean_uint32_dec_le(v___x_4205_, v___x_4207_);
if (v___x_4208_ == 0)
{
v___y_4186_ = v___y_4202_;
v___y_4187_ = v___x_4208_;
goto v___jp_4185_;
}
else
{
uint32_t v___x_4209_; uint8_t v___x_4210_; 
v___x_4209_ = 2139095040;
v___x_4210_ = lean_uint32_dec_lt(v_a_4204_, v___x_4209_);
v___y_4186_ = v___y_4202_;
v___y_4187_ = v___x_4210_;
goto v___jp_4185_;
}
}
v___jp_4211_:
{
uint32_t v___x_4213_; uint32_t v___x_4214_; 
v___x_4213_ = 8388608;
v___x_4214_ = lean_uint32_lor(v___y_4212_, v___x_4213_);
return v___x_4214_;
}
v___jp_4215_:
{
uint32_t v___x_4217_; uint32_t v___x_4218_; 
v___x_4217_ = 8388608;
v___x_4218_ = lean_uint32_lor(v___y_4216_, v___x_4217_);
return v___x_4218_;
}
v___jp_4219_:
{
uint32_t v___x_4223_; uint32_t v___x_4224_; 
v___x_4223_ = lean_uint32_land(v___y_4220_, v___y_4221_);
v___x_4224_ = lean_uint32_lor(v___y_4222_, v___x_4223_);
return v___x_4224_;
}
v___jp_4225_:
{
uint8_t v___x_4230_; 
v___x_4230_ = lean_uint64_dec_eq(v___y_4229_, v___y_4228_);
if (v___x_4230_ == 0)
{
uint64_t v___x_4231_; uint8_t v___x_4232_; 
v___x_4231_ = 8388608ULL;
v___x_4232_ = lean_uint64_dec_eq(v___y_4229_, v___x_4231_);
if (v___x_4232_ == 0)
{
uint32_t v___x_4233_; 
v___x_4233_ = lean_uint64_to_uint32(v___y_4229_);
if (v___y_4226_ == 0)
{
uint32_t v___x_4234_; 
v___x_4234_ = 0;
v___y_4220_ = v___x_4233_;
v___y_4221_ = v___y_4227_;
v___y_4222_ = v___x_4234_;
goto v___jp_4219_;
}
else
{
uint32_t v___x_4235_; 
v___x_4235_ = 2147483648;
v___y_4220_ = v___x_4233_;
v___y_4221_ = v___y_4227_;
v___y_4222_ = v___x_4235_;
goto v___jp_4219_;
}
}
else
{
if (v___y_4226_ == 0)
{
uint32_t v___x_4236_; 
v___x_4236_ = 0;
v___y_4212_ = v___x_4236_;
goto v___jp_4211_;
}
else
{
uint32_t v___x_4237_; 
v___x_4237_ = 2147483648;
v___y_4212_ = v___x_4237_;
goto v___jp_4211_;
}
}
}
else
{
if (v___y_4226_ == 0)
{
uint32_t v___x_4238_; 
v___x_4238_ = 0;
return v___x_4238_;
}
else
{
uint32_t v___x_4239_; 
v___x_4239_ = 2147483648;
return v___x_4239_;
}
}
}
v___jp_4240_:
{
uint32_t v___x_4244_; uint32_t v___x_4245_; 
v___x_4244_ = lean_uint32_land(v___y_4242_, v___y_4241_);
v___x_4245_ = lean_uint32_lor(v___y_4243_, v___x_4244_);
return v___x_4245_;
}
v___jp_4246_:
{
uint8_t v___x_4251_; 
v___x_4251_ = lean_uint64_dec_eq(v___y_4250_, v___y_4249_);
if (v___x_4251_ == 0)
{
uint64_t v___x_4252_; uint8_t v___x_4253_; 
v___x_4252_ = 8388608ULL;
v___x_4253_ = lean_uint64_dec_eq(v___y_4250_, v___x_4252_);
if (v___x_4253_ == 0)
{
uint32_t v___x_4254_; 
v___x_4254_ = lean_uint64_to_uint32(v___y_4250_);
if (v___y_4247_ == 0)
{
uint32_t v___x_4255_; 
v___x_4255_ = 0;
v___y_4241_ = v___y_4248_;
v___y_4242_ = v___x_4254_;
v___y_4243_ = v___x_4255_;
goto v___jp_4240_;
}
else
{
uint32_t v___x_4256_; 
v___x_4256_ = 2147483648;
v___y_4241_ = v___y_4248_;
v___y_4242_ = v___x_4254_;
v___y_4243_ = v___x_4256_;
goto v___jp_4240_;
}
}
else
{
if (v___y_4247_ == 0)
{
uint32_t v___x_4257_; 
v___x_4257_ = 0;
v___y_4216_ = v___x_4257_;
goto v___jp_4215_;
}
else
{
uint32_t v___x_4258_; 
v___x_4258_ = 2147483648;
v___y_4216_ = v___x_4258_;
goto v___jp_4215_;
}
}
}
else
{
if (v___y_4247_ == 0)
{
uint32_t v___x_4259_; 
v___x_4259_ = 0;
return v___x_4259_;
}
else
{
uint32_t v___x_4260_; 
v___x_4260_ = 2147483648;
return v___x_4260_;
}
}
}
v___jp_4261_:
{
if (v___y_4262_ == 0)
{
uint32_t v___x_4263_; 
v___x_4263_ = lp_competition_Submission_FastMul_mul(v_x_4114_, v_y_4115_);
return v___x_4263_;
}
else
{
uint32_t v___x_4264_; uint32_t v___x_4265_; 
v___x_4264_ = 4194304;
v___x_4265_ = lean_uint32_lor(v_y_4115_, v___x_4264_);
return v___x_4265_;
}
}
v___jp_4266_:
{
uint32_t v___x_4267_; uint32_t v___x_4268_; uint32_t v___x_4269_; uint32_t v___x_4270_; uint8_t v___x_4271_; 
v___x_4267_ = 23;
v___x_4268_ = lean_uint32_shift_right(v_y_4115_, v___x_4267_);
v___x_4269_ = 255;
v___x_4270_ = lean_uint32_land(v___x_4268_, v___x_4269_);
v___x_4271_ = lean_uint32_dec_eq(v___x_4270_, v___x_4269_);
if (v___x_4271_ == 0)
{
v___y_4262_ = v___x_4271_;
goto v___jp_4261_;
}
else
{
uint32_t v___x_4272_; uint32_t v___x_4273_; uint32_t v___x_4274_; uint8_t v___x_4275_; 
v___x_4272_ = 8388607;
v___x_4273_ = lean_uint32_land(v_y_4115_, v___x_4272_);
v___x_4274_ = 0;
v___x_4275_ = lean_uint32_dec_eq(v___x_4273_, v___x_4274_);
if (v___x_4275_ == 0)
{
v___y_4262_ = v___x_4271_;
goto v___jp_4261_;
}
else
{
uint32_t v___x_4276_; 
v___x_4276_ = lp_competition_Submission_FastMul_mul(v_x_4114_, v_y_4115_);
return v___x_4276_;
}
}
}
v___jp_4277_:
{
if (v___y_4278_ == 0)
{
goto v___jp_4266_;
}
else
{
uint32_t v___x_4279_; uint32_t v___x_4280_; 
v___x_4279_ = 4194304;
v___x_4280_ = lean_uint32_lor(v_x_4114_, v___x_4279_);
return v___x_4280_;
}
}
v___jp_4281_:
{
uint32_t v___x_4282_; uint32_t v___x_4283_; uint32_t v___x_4284_; uint32_t v___x_4285_; uint8_t v___x_4286_; 
v___x_4282_ = 23;
v___x_4283_ = lean_uint32_shift_right(v_x_4114_, v___x_4282_);
v___x_4284_ = 255;
v___x_4285_ = lean_uint32_land(v___x_4283_, v___x_4284_);
v___x_4286_ = lean_uint32_dec_eq(v___x_4285_, v___x_4284_);
if (v___x_4286_ == 0)
{
v___y_4278_ = v___x_4286_;
goto v___jp_4277_;
}
else
{
uint32_t v___x_4287_; uint32_t v___x_4288_; uint32_t v___x_4289_; uint8_t v___x_4290_; 
v___x_4287_ = 8388607;
v___x_4288_ = lean_uint32_land(v_x_4114_, v___x_4287_);
v___x_4289_ = 0;
v___x_4290_ = lean_uint32_dec_eq(v___x_4288_, v___x_4289_);
if (v___x_4290_ == 0)
{
v___y_4278_ = v___x_4286_;
goto v___jp_4277_;
}
else
{
goto v___jp_4266_;
}
}
}
v___jp_4291_:
{
if (v___y_4292_ == 0)
{
goto v___jp_4281_;
}
else
{
uint32_t v___x_4293_; uint32_t v___x_4294_; uint32_t v___x_4295_; uint8_t v___x_4296_; 
v___x_4293_ = 4194304;
v___x_4294_ = lean_uint32_land(v_y_4115_, v___x_4293_);
v___x_4295_ = 0;
v___x_4296_ = lean_uint32_dec_eq(v___x_4294_, v___x_4295_);
if (v___x_4296_ == 0)
{
goto v___jp_4281_;
}
else
{
uint32_t v___x_4297_; 
v___x_4297_ = lean_uint32_lor(v_y_4115_, v___x_4293_);
return v___x_4297_;
}
}
}
v___jp_4298_:
{
uint32_t v___x_4299_; uint32_t v___x_4300_; uint32_t v___x_4301_; uint32_t v___x_4302_; uint8_t v___x_4303_; 
v___x_4299_ = 23;
v___x_4300_ = lean_uint32_shift_right(v_y_4115_, v___x_4299_);
v___x_4301_ = 255;
v___x_4302_ = lean_uint32_land(v___x_4300_, v___x_4301_);
v___x_4303_ = lean_uint32_dec_eq(v___x_4302_, v___x_4301_);
if (v___x_4303_ == 0)
{
v___y_4292_ = v___x_4303_;
goto v___jp_4291_;
}
else
{
uint32_t v___x_4304_; uint32_t v___x_4305_; uint32_t v___x_4306_; uint8_t v___x_4307_; 
v___x_4304_ = 8388607;
v___x_4305_ = lean_uint32_land(v_y_4115_, v___x_4304_);
v___x_4306_ = 0;
v___x_4307_ = lean_uint32_dec_eq(v___x_4305_, v___x_4306_);
if (v___x_4307_ == 0)
{
v___y_4292_ = v___x_4303_;
goto v___jp_4291_;
}
else
{
goto v___jp_4281_;
}
}
}
v___jp_4308_:
{
if (v___y_4309_ == 0)
{
goto v___jp_4298_;
}
else
{
uint32_t v___x_4310_; uint32_t v___x_4311_; uint32_t v___x_4312_; uint8_t v___x_4313_; 
v___x_4310_ = 4194304;
v___x_4311_ = lean_uint32_land(v_x_4114_, v___x_4310_);
v___x_4312_ = 0;
v___x_4313_ = lean_uint32_dec_eq(v___x_4311_, v___x_4312_);
if (v___x_4313_ == 0)
{
goto v___jp_4298_;
}
else
{
uint32_t v___x_4314_; 
v___x_4314_ = lean_uint32_lor(v_x_4114_, v___x_4310_);
return v___x_4314_;
}
}
}
v___jp_4315_:
{
float v_result_4318_; uint8_t v___x_4319_; 
v_result_4318_ = lean_float32_mul(v___y_4316_, v___y_4317_);
v___x_4319_ = lean_float32_beq(v_result_4318_, v_result_4318_);
if (v___x_4319_ == 0)
{
uint32_t v___x_4320_; uint32_t v___x_4321_; uint32_t v___x_4322_; uint32_t v___x_4323_; uint8_t v___x_4324_; 
v___x_4320_ = 23;
v___x_4321_ = lean_uint32_shift_right(v_x_4114_, v___x_4320_);
v___x_4322_ = 255;
v___x_4323_ = lean_uint32_land(v___x_4321_, v___x_4322_);
v___x_4324_ = lean_uint32_dec_eq(v___x_4323_, v___x_4322_);
if (v___x_4324_ == 0)
{
v___y_4309_ = v___x_4324_;
goto v___jp_4308_;
}
else
{
uint32_t v___x_4325_; uint32_t v___x_4326_; uint32_t v___x_4327_; uint8_t v___x_4328_; 
v___x_4325_ = 8388607;
v___x_4326_ = lean_uint32_land(v_x_4114_, v___x_4325_);
v___x_4327_ = 0;
v___x_4328_ = lean_uint32_dec_eq(v___x_4326_, v___x_4327_);
if (v___x_4328_ == 0)
{
v___y_4309_ = v___x_4324_;
goto v___jp_4308_;
}
else
{
goto v___jp_4298_;
}
}
}
else
{
uint32_t v___x_4329_; 
v___x_4329_ = lean_float32_to_bits(v_result_4318_);
return v___x_4329_;
}
}
v___jp_4330_:
{
if (v___y_4332_ == 0)
{
float v___x_4333_; 
v___x_4333_ = lean_float32_of_bits(v_y_4115_);
v___y_4316_ = v___y_4331_;
v___y_4317_ = v___x_4333_;
goto v___jp_4315_;
}
else
{
uint32_t v___x_4334_; uint32_t v___x_4335_; uint32_t v___x_4336_; uint32_t v___x_4337_; float v___x_4338_; lean_object* v___x_4339_; uint32_t v___x_4340_; uint32_t v___x_4341_; lean_object* v___x_4342_; lean_object* v___x_4343_; float v___x_4344_; float v___x_4345_; 
v___x_4334_ = 8388607;
v___x_4335_ = lean_uint32_land(v_y_4115_, v___x_4334_);
v___x_4336_ = 8388608;
v___x_4337_ = lean_uint32_lor(v___x_4335_, v___x_4336_);
v___x_4338_ = lean_uint32_to_float32(v___x_4337_);
v___x_4339_ = lp_competition_R2W01b_scaleTable;
v___x_4340_ = 23;
v___x_4341_ = lean_uint32_shift_right(v_y_4115_, v___x_4340_);
v___x_4342_ = lean_uint32_to_nat(v___x_4341_);
v___x_4343_ = lean_array_fget_borrowed(v___x_4339_, v___x_4342_);
lean_dec(v___x_4342_);
v___x_4344_ = lean_unbox_float32(v___x_4343_);
v___x_4345_ = lean_float32_mul(v___x_4338_, v___x_4344_);
v___y_4316_ = v___y_4331_;
v___y_4317_ = v___x_4345_;
goto v___jp_4315_;
}
}
v___jp_4346_:
{
uint32_t v___x_4348_; uint32_t v_a_4349_; uint32_t v___x_4350_; uint32_t v___x_4351_; uint32_t v___x_4352_; uint8_t v___x_4353_; 
v___x_4348_ = 2147483647;
v_a_4349_ = lean_uint32_land(v_y_4115_, v___x_4348_);
v___x_4350_ = 201326591;
v___x_4351_ = 1;
v___x_4352_ = lean_uint32_sub(v_a_4349_, v___x_4351_);
v___x_4353_ = lean_uint32_dec_le(v___x_4350_, v___x_4352_);
if (v___x_4353_ == 0)
{
v___y_4331_ = v___y_4347_;
v___y_4332_ = v___x_4353_;
goto v___jp_4330_;
}
else
{
uint32_t v___x_4354_; uint8_t v___x_4355_; 
v___x_4354_ = 2139095040;
v___x_4355_ = lean_uint32_dec_lt(v_a_4349_, v___x_4354_);
v___y_4331_ = v___y_4347_;
v___y_4332_ = v___x_4355_;
goto v___jp_4330_;
}
}
v___jp_4356_:
{
uint32_t v___x_4358_; uint32_t v___x_4359_; 
v___x_4358_ = 8388608;
v___x_4359_ = lean_uint32_lor(v___y_4357_, v___x_4358_);
return v___x_4359_;
}
v___jp_4360_:
{
uint32_t v___x_4362_; uint32_t v___x_4363_; 
v___x_4362_ = 8388608;
v___x_4363_ = lean_uint32_lor(v___y_4361_, v___x_4362_);
return v___x_4363_;
}
v___jp_4364_:
{
uint32_t v___x_4368_; uint32_t v___x_4369_; 
v___x_4368_ = lean_uint32_land(v___y_4365_, v___y_4366_);
v___x_4369_ = lean_uint32_lor(v___y_4367_, v___x_4368_);
return v___x_4369_;
}
v___jp_4370_:
{
uint8_t v___x_4375_; 
v___x_4375_ = lean_uint64_dec_eq(v___y_4374_, v___y_4371_);
if (v___x_4375_ == 0)
{
uint64_t v___x_4376_; uint8_t v___x_4377_; 
v___x_4376_ = 8388608ULL;
v___x_4377_ = lean_uint64_dec_eq(v___y_4374_, v___x_4376_);
if (v___x_4377_ == 0)
{
uint32_t v___x_4378_; 
v___x_4378_ = lean_uint64_to_uint32(v___y_4374_);
if (v___y_4372_ == 0)
{
uint32_t v___x_4379_; 
v___x_4379_ = 0;
v___y_4365_ = v___x_4378_;
v___y_4366_ = v___y_4373_;
v___y_4367_ = v___x_4379_;
goto v___jp_4364_;
}
else
{
uint32_t v___x_4380_; 
v___x_4380_ = 2147483648;
v___y_4365_ = v___x_4378_;
v___y_4366_ = v___y_4373_;
v___y_4367_ = v___x_4380_;
goto v___jp_4364_;
}
}
else
{
if (v___y_4372_ == 0)
{
uint32_t v___x_4381_; 
v___x_4381_ = 0;
v___y_4361_ = v___x_4381_;
goto v___jp_4360_;
}
else
{
uint32_t v___x_4382_; 
v___x_4382_ = 2147483648;
v___y_4361_ = v___x_4382_;
goto v___jp_4360_;
}
}
}
else
{
if (v___y_4372_ == 0)
{
uint32_t v___x_4383_; 
v___x_4383_ = 0;
return v___x_4383_;
}
else
{
uint32_t v___x_4384_; 
v___x_4384_ = 2147483648;
return v___x_4384_;
}
}
}
v___jp_4385_:
{
uint32_t v___x_4389_; uint32_t v___x_4390_; 
v___x_4389_ = lean_uint32_land(v___y_4386_, v___y_4387_);
v___x_4390_ = lean_uint32_lor(v___y_4388_, v___x_4389_);
return v___x_4390_;
}
v___jp_4391_:
{
uint8_t v___x_4396_; 
v___x_4396_ = lean_uint64_dec_eq(v___y_4395_, v___y_4394_);
if (v___x_4396_ == 0)
{
uint64_t v___x_4397_; uint8_t v___x_4398_; 
v___x_4397_ = 8388608ULL;
v___x_4398_ = lean_uint64_dec_eq(v___y_4395_, v___x_4397_);
if (v___x_4398_ == 0)
{
uint32_t v___x_4399_; 
v___x_4399_ = lean_uint64_to_uint32(v___y_4395_);
if (v___y_4392_ == 0)
{
uint32_t v___x_4400_; 
v___x_4400_ = 0;
v___y_4386_ = v___x_4399_;
v___y_4387_ = v___y_4393_;
v___y_4388_ = v___x_4400_;
goto v___jp_4385_;
}
else
{
uint32_t v___x_4401_; 
v___x_4401_ = 2147483648;
v___y_4386_ = v___x_4399_;
v___y_4387_ = v___y_4393_;
v___y_4388_ = v___x_4401_;
goto v___jp_4385_;
}
}
else
{
if (v___y_4392_ == 0)
{
uint32_t v___x_4402_; 
v___x_4402_ = 0;
v___y_4357_ = v___x_4402_;
goto v___jp_4356_;
}
else
{
uint32_t v___x_4403_; 
v___x_4403_ = 2147483648;
v___y_4357_ = v___x_4403_;
goto v___jp_4356_;
}
}
}
else
{
if (v___y_4392_ == 0)
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
if (v___y_4407_ == 0)
{
uint32_t v___x_4408_; 
v___x_4408_ = lp_competition_Submission_FastMul_mul(v_x_4114_, v_y_4115_);
return v___x_4408_;
}
else
{
uint32_t v___x_4409_; uint32_t v___x_4410_; 
v___x_4409_ = 4194304;
v___x_4410_ = lean_uint32_lor(v_y_4115_, v___x_4409_);
return v___x_4410_;
}
}
v___jp_4411_:
{
uint32_t v___x_4412_; uint32_t v___x_4413_; uint32_t v___x_4414_; uint32_t v___x_4415_; uint8_t v___x_4416_; 
v___x_4412_ = 23;
v___x_4413_ = lean_uint32_shift_right(v_y_4115_, v___x_4412_);
v___x_4414_ = 255;
v___x_4415_ = lean_uint32_land(v___x_4413_, v___x_4414_);
v___x_4416_ = lean_uint32_dec_eq(v___x_4415_, v___x_4414_);
if (v___x_4416_ == 0)
{
v___y_4407_ = v___x_4416_;
goto v___jp_4406_;
}
else
{
uint32_t v___x_4417_; uint32_t v___x_4418_; uint32_t v___x_4419_; uint8_t v___x_4420_; 
v___x_4417_ = 8388607;
v___x_4418_ = lean_uint32_land(v_y_4115_, v___x_4417_);
v___x_4419_ = 0;
v___x_4420_ = lean_uint32_dec_eq(v___x_4418_, v___x_4419_);
if (v___x_4420_ == 0)
{
v___y_4407_ = v___x_4416_;
goto v___jp_4406_;
}
else
{
uint32_t v___x_4421_; 
v___x_4421_ = lp_competition_Submission_FastMul_mul(v_x_4114_, v_y_4115_);
return v___x_4421_;
}
}
}
v___jp_4422_:
{
if (v___y_4423_ == 0)
{
goto v___jp_4411_;
}
else
{
uint32_t v___x_4424_; uint32_t v___x_4425_; 
v___x_4424_ = 4194304;
v___x_4425_ = lean_uint32_lor(v_x_4114_, v___x_4424_);
return v___x_4425_;
}
}
v___jp_4426_:
{
uint32_t v___x_4427_; uint32_t v___x_4428_; uint32_t v___x_4429_; uint32_t v___x_4430_; uint8_t v___x_4431_; 
v___x_4427_ = 23;
v___x_4428_ = lean_uint32_shift_right(v_x_4114_, v___x_4427_);
v___x_4429_ = 255;
v___x_4430_ = lean_uint32_land(v___x_4428_, v___x_4429_);
v___x_4431_ = lean_uint32_dec_eq(v___x_4430_, v___x_4429_);
if (v___x_4431_ == 0)
{
v___y_4423_ = v___x_4431_;
goto v___jp_4422_;
}
else
{
uint32_t v___x_4432_; uint32_t v___x_4433_; uint32_t v___x_4434_; uint8_t v___x_4435_; 
v___x_4432_ = 8388607;
v___x_4433_ = lean_uint32_land(v_x_4114_, v___x_4432_);
v___x_4434_ = 0;
v___x_4435_ = lean_uint32_dec_eq(v___x_4433_, v___x_4434_);
if (v___x_4435_ == 0)
{
v___y_4423_ = v___x_4431_;
goto v___jp_4422_;
}
else
{
goto v___jp_4411_;
}
}
}
v___jp_4436_:
{
if (v___y_4437_ == 0)
{
goto v___jp_4426_;
}
else
{
uint32_t v___x_4438_; uint32_t v___x_4439_; uint32_t v___x_4440_; uint8_t v___x_4441_; 
v___x_4438_ = 4194304;
v___x_4439_ = lean_uint32_land(v_y_4115_, v___x_4438_);
v___x_4440_ = 0;
v___x_4441_ = lean_uint32_dec_eq(v___x_4439_, v___x_4440_);
if (v___x_4441_ == 0)
{
goto v___jp_4426_;
}
else
{
uint32_t v___x_4442_; 
v___x_4442_ = lean_uint32_lor(v_y_4115_, v___x_4438_);
return v___x_4442_;
}
}
}
v___jp_4443_:
{
uint32_t v___x_4444_; uint32_t v___x_4445_; uint32_t v___x_4446_; uint32_t v___x_4447_; uint8_t v___x_4448_; 
v___x_4444_ = 23;
v___x_4445_ = lean_uint32_shift_right(v_y_4115_, v___x_4444_);
v___x_4446_ = 255;
v___x_4447_ = lean_uint32_land(v___x_4445_, v___x_4446_);
v___x_4448_ = lean_uint32_dec_eq(v___x_4447_, v___x_4446_);
if (v___x_4448_ == 0)
{
v___y_4437_ = v___x_4448_;
goto v___jp_4436_;
}
else
{
uint32_t v___x_4449_; uint32_t v___x_4450_; uint32_t v___x_4451_; uint8_t v___x_4452_; 
v___x_4449_ = 8388607;
v___x_4450_ = lean_uint32_land(v_y_4115_, v___x_4449_);
v___x_4451_ = 0;
v___x_4452_ = lean_uint32_dec_eq(v___x_4450_, v___x_4451_);
if (v___x_4452_ == 0)
{
v___y_4437_ = v___x_4448_;
goto v___jp_4436_;
}
else
{
goto v___jp_4426_;
}
}
}
v___jp_4453_:
{
if (v___y_4454_ == 0)
{
goto v___jp_4443_;
}
else
{
uint32_t v___x_4455_; uint32_t v___x_4456_; uint32_t v___x_4457_; uint8_t v___x_4458_; 
v___x_4455_ = 4194304;
v___x_4456_ = lean_uint32_land(v_x_4114_, v___x_4455_);
v___x_4457_ = 0;
v___x_4458_ = lean_uint32_dec_eq(v___x_4456_, v___x_4457_);
if (v___x_4458_ == 0)
{
goto v___jp_4443_;
}
else
{
uint32_t v___x_4459_; 
v___x_4459_ = lean_uint32_lor(v_x_4114_, v___x_4455_);
return v___x_4459_;
}
}
}
v___jp_4460_:
{
float v_result_4463_; uint8_t v___x_4464_; 
v_result_4463_ = lean_float32_mul(v___y_4461_, v___y_4462_);
v___x_4464_ = lean_float32_beq(v_result_4463_, v_result_4463_);
if (v___x_4464_ == 0)
{
uint32_t v___x_4465_; uint32_t v___x_4466_; uint32_t v___x_4467_; uint32_t v___x_4468_; uint8_t v___x_4469_; 
v___x_4465_ = 23;
v___x_4466_ = lean_uint32_shift_right(v_x_4114_, v___x_4465_);
v___x_4467_ = 255;
v___x_4468_ = lean_uint32_land(v___x_4466_, v___x_4467_);
v___x_4469_ = lean_uint32_dec_eq(v___x_4468_, v___x_4467_);
if (v___x_4469_ == 0)
{
v___y_4454_ = v___x_4469_;
goto v___jp_4453_;
}
else
{
uint32_t v___x_4470_; uint32_t v___x_4471_; uint32_t v___x_4472_; uint8_t v___x_4473_; 
v___x_4470_ = 8388607;
v___x_4471_ = lean_uint32_land(v_x_4114_, v___x_4470_);
v___x_4472_ = 0;
v___x_4473_ = lean_uint32_dec_eq(v___x_4471_, v___x_4472_);
if (v___x_4473_ == 0)
{
v___y_4454_ = v___x_4469_;
goto v___jp_4453_;
}
else
{
goto v___jp_4443_;
}
}
}
else
{
uint32_t v___x_4474_; 
v___x_4474_ = lean_float32_to_bits(v_result_4463_);
return v___x_4474_;
}
}
v___jp_4475_:
{
if (v___y_4477_ == 0)
{
float v___x_4478_; 
v___x_4478_ = lean_float32_of_bits(v_y_4115_);
v___y_4461_ = v___y_4476_;
v___y_4462_ = v___x_4478_;
goto v___jp_4460_;
}
else
{
uint32_t v___x_4479_; uint32_t v___x_4480_; uint32_t v___x_4481_; uint32_t v___x_4482_; float v___x_4483_; lean_object* v___x_4484_; uint32_t v___x_4485_; uint32_t v___x_4486_; lean_object* v___x_4487_; lean_object* v___x_4488_; float v___x_4489_; float v___x_4490_; 
v___x_4479_ = 8388607;
v___x_4480_ = lean_uint32_land(v_y_4115_, v___x_4479_);
v___x_4481_ = 8388608;
v___x_4482_ = lean_uint32_lor(v___x_4480_, v___x_4481_);
v___x_4483_ = lean_uint32_to_float32(v___x_4482_);
v___x_4484_ = lp_competition_R2W01b_scaleTable;
v___x_4485_ = 23;
v___x_4486_ = lean_uint32_shift_right(v_y_4115_, v___x_4485_);
v___x_4487_ = lean_uint32_to_nat(v___x_4486_);
v___x_4488_ = lean_array_fget_borrowed(v___x_4484_, v___x_4487_);
lean_dec(v___x_4487_);
v___x_4489_ = lean_unbox_float32(v___x_4488_);
v___x_4490_ = lean_float32_mul(v___x_4483_, v___x_4489_);
v___y_4461_ = v___y_4476_;
v___y_4462_ = v___x_4490_;
goto v___jp_4460_;
}
}
v___jp_4491_:
{
uint32_t v___x_4493_; uint32_t v_a_4494_; uint32_t v___x_4495_; uint32_t v___x_4496_; uint32_t v___x_4497_; uint8_t v___x_4498_; 
v___x_4493_ = 2147483647;
v_a_4494_ = lean_uint32_land(v_y_4115_, v___x_4493_);
v___x_4495_ = 201326591;
v___x_4496_ = 1;
v___x_4497_ = lean_uint32_sub(v_a_4494_, v___x_4496_);
v___x_4498_ = lean_uint32_dec_le(v___x_4495_, v___x_4497_);
if (v___x_4498_ == 0)
{
v___y_4476_ = v___y_4492_;
v___y_4477_ = v___x_4498_;
goto v___jp_4475_;
}
else
{
uint32_t v___x_4499_; uint8_t v___x_4500_; 
v___x_4499_ = 2139095040;
v___x_4500_ = lean_uint32_dec_lt(v_a_4494_, v___x_4499_);
v___y_4476_ = v___y_4492_;
v___y_4477_ = v___x_4500_;
goto v___jp_4475_;
}
}
v___jp_4501_:
{
uint32_t v___x_4503_; uint32_t v___x_4504_; 
v___x_4503_ = 8388608;
v___x_4504_ = lean_uint32_lor(v___y_4502_, v___x_4503_);
return v___x_4504_;
}
v___jp_4505_:
{
uint32_t v___x_4507_; uint32_t v___x_4508_; 
v___x_4507_ = 8388608;
v___x_4508_ = lean_uint32_lor(v___y_4506_, v___x_4507_);
return v___x_4508_;
}
v___jp_4509_:
{
uint32_t v___x_4513_; uint32_t v___x_4514_; 
v___x_4513_ = lean_uint32_land(v___y_4511_, v___y_4510_);
v___x_4514_ = lean_uint32_lor(v___y_4512_, v___x_4513_);
return v___x_4514_;
}
v___jp_4515_:
{
uint8_t v___x_4520_; 
v___x_4520_ = lean_uint64_dec_eq(v___y_4519_, v___y_4518_);
if (v___x_4520_ == 0)
{
uint64_t v___x_4521_; uint8_t v___x_4522_; 
v___x_4521_ = 8388608ULL;
v___x_4522_ = lean_uint64_dec_eq(v___y_4519_, v___x_4521_);
if (v___x_4522_ == 0)
{
uint32_t v___x_4523_; 
v___x_4523_ = lean_uint64_to_uint32(v___y_4519_);
if (v___y_4517_ == 0)
{
uint32_t v___x_4524_; 
v___x_4524_ = 0;
v___y_4510_ = v___y_4516_;
v___y_4511_ = v___x_4523_;
v___y_4512_ = v___x_4524_;
goto v___jp_4509_;
}
else
{
uint32_t v___x_4525_; 
v___x_4525_ = 2147483648;
v___y_4510_ = v___y_4516_;
v___y_4511_ = v___x_4523_;
v___y_4512_ = v___x_4525_;
goto v___jp_4509_;
}
}
else
{
if (v___y_4517_ == 0)
{
uint32_t v___x_4526_; 
v___x_4526_ = 0;
v___y_4502_ = v___x_4526_;
goto v___jp_4501_;
}
else
{
uint32_t v___x_4527_; 
v___x_4527_ = 2147483648;
v___y_4502_ = v___x_4527_;
goto v___jp_4501_;
}
}
}
else
{
if (v___y_4517_ == 0)
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
}
v___jp_4530_:
{
uint32_t v___x_4534_; uint32_t v___x_4535_; 
v___x_4534_ = lean_uint32_land(v___y_4532_, v___y_4531_);
v___x_4535_ = lean_uint32_lor(v___y_4533_, v___x_4534_);
return v___x_4535_;
}
v___jp_4536_:
{
uint8_t v___x_4541_; 
v___x_4541_ = lean_uint64_dec_eq(v___y_4540_, v___y_4539_);
if (v___x_4541_ == 0)
{
uint64_t v___x_4542_; uint8_t v___x_4543_; 
v___x_4542_ = 8388608ULL;
v___x_4543_ = lean_uint64_dec_eq(v___y_4540_, v___x_4542_);
if (v___x_4543_ == 0)
{
uint32_t v___x_4544_; 
v___x_4544_ = lean_uint64_to_uint32(v___y_4540_);
if (v___y_4538_ == 0)
{
uint32_t v___x_4545_; 
v___x_4545_ = 0;
v___y_4531_ = v___y_4537_;
v___y_4532_ = v___x_4544_;
v___y_4533_ = v___x_4545_;
goto v___jp_4530_;
}
else
{
uint32_t v___x_4546_; 
v___x_4546_ = 2147483648;
v___y_4531_ = v___y_4537_;
v___y_4532_ = v___x_4544_;
v___y_4533_ = v___x_4546_;
goto v___jp_4530_;
}
}
else
{
if (v___y_4538_ == 0)
{
uint32_t v___x_4547_; 
v___x_4547_ = 0;
v___y_4506_ = v___x_4547_;
goto v___jp_4505_;
}
else
{
uint32_t v___x_4548_; 
v___x_4548_ = 2147483648;
v___y_4506_ = v___x_4548_;
goto v___jp_4505_;
}
}
}
else
{
if (v___y_4538_ == 0)
{
uint32_t v___x_4549_; 
v___x_4549_ = 0;
return v___x_4549_;
}
else
{
uint32_t v___x_4550_; 
v___x_4550_ = 2147483648;
return v___x_4550_;
}
}
}
v___jp_4553_:
{
if (v___y_4554_ == 0)
{
float v___x_4555_; 
v___x_4555_ = lean_float32_of_bits(v_x_4114_);
v___y_4202_ = v___x_4555_;
goto v___jp_4201_;
}
else
{
uint32_t v___x_4556_; uint32_t v___x_4557_; uint32_t v___x_4558_; uint32_t v___x_4559_; float v___x_4560_; lean_object* v___x_4561_; lean_object* v___x_4562_; lean_object* v___x_4563_; float v___x_4564_; float v___x_4565_; 
v___x_4556_ = 8388607;
v___x_4557_ = lean_uint32_land(v_x_4114_, v___x_4556_);
v___x_4558_ = 8388608;
v___x_4559_ = lean_uint32_lor(v___x_4557_, v___x_4558_);
v___x_4560_ = lean_uint32_to_float32(v___x_4559_);
v___x_4561_ = lp_competition_R2W01b_scaleTable;
v___x_4562_ = lean_uint32_to_nat(v___x_4552_);
v___x_4563_ = lean_array_fget_borrowed(v___x_4561_, v___x_4562_);
lean_dec(v___x_4562_);
v___x_4564_ = lean_unbox_float32(v___x_4563_);
v___x_4565_ = lean_float32_mul(v___x_4560_, v___x_4564_);
v___y_4202_ = v___x_4565_;
goto v___jp_4201_;
}
}
v___jp_4566_:
{
if (v___y_4567_ == 0)
{
float v___x_4568_; 
v___x_4568_ = lean_float32_of_bits(v_x_4114_);
v___y_4347_ = v___x_4568_;
goto v___jp_4346_;
}
else
{
uint32_t v___x_4569_; uint32_t v___x_4570_; uint32_t v___x_4571_; uint32_t v___x_4572_; float v___x_4573_; lean_object* v___x_4574_; lean_object* v___x_4575_; lean_object* v___x_4576_; float v___x_4577_; float v___x_4578_; 
v___x_4569_ = 8388607;
v___x_4570_ = lean_uint32_land(v_x_4114_, v___x_4569_);
v___x_4571_ = 8388608;
v___x_4572_ = lean_uint32_lor(v___x_4570_, v___x_4571_);
v___x_4573_ = lean_uint32_to_float32(v___x_4572_);
v___x_4574_ = lp_competition_R2W01b_scaleTable;
v___x_4575_ = lean_uint32_to_nat(v___x_4552_);
v___x_4576_ = lean_array_fget_borrowed(v___x_4574_, v___x_4575_);
lean_dec(v___x_4575_);
v___x_4577_ = lean_unbox_float32(v___x_4576_);
v___x_4578_ = lean_float32_mul(v___x_4573_, v___x_4577_);
v___y_4347_ = v___x_4578_;
goto v___jp_4346_;
}
}
v___jp_4579_:
{
if (v___y_4580_ == 0)
{
float v___x_4581_; 
v___x_4581_ = lean_float32_of_bits(v_x_4114_);
v___y_4492_ = v___x_4581_;
goto v___jp_4491_;
}
else
{
uint32_t v___x_4582_; uint32_t v___x_4583_; uint32_t v___x_4584_; uint32_t v___x_4585_; float v___x_4586_; lean_object* v___x_4587_; lean_object* v___x_4588_; lean_object* v___x_4589_; float v___x_4590_; float v___x_4591_; 
v___x_4582_ = 8388607;
v___x_4583_ = lean_uint32_land(v_x_4114_, v___x_4582_);
v___x_4584_ = 8388608;
v___x_4585_ = lean_uint32_lor(v___x_4583_, v___x_4584_);
v___x_4586_ = lean_uint32_to_float32(v___x_4585_);
v___x_4587_ = lp_competition_R2W01b_scaleTable;
v___x_4588_ = lean_uint32_to_nat(v___x_4552_);
v___x_4589_ = lean_array_fget_borrowed(v___x_4587_, v___x_4588_);
lean_dec(v___x_4588_);
v___x_4590_ = lean_unbox_float32(v___x_4589_);
v___x_4591_ = lean_float32_mul(v___x_4586_, v___x_4590_);
v___y_4492_ = v___x_4591_;
goto v___jp_4491_;
}
}
v___jp_4593_:
{
uint32_t v___x_4598_; uint32_t v___x_4599_; uint32_t v___x_4600_; uint32_t v___x_4601_; uint32_t v___x_4602_; 
v___x_4598_ = lean_uint32_land(v___y_4596_, v___x_4592_);
v___x_4599_ = lean_uint32_shift_left(v___x_4598_, v___x_4551_);
v___x_4600_ = lean_uint32_lor(v___y_4597_, v___x_4599_);
v___x_4601_ = lean_uint32_land(v___y_4594_, v___y_4595_);
v___x_4602_ = lean_uint32_lor(v___x_4600_, v___x_4601_);
return v___x_4602_;
}
v___jp_4603_:
{
if (v___y_4604_ == 0)
{
uint32_t v___x_4608_; 
v___x_4608_ = 0;
v___y_4594_ = v___y_4607_;
v___y_4595_ = v___y_4605_;
v___y_4596_ = v___y_4606_;
v___y_4597_ = v___x_4608_;
goto v___jp_4593_;
}
else
{
uint32_t v___x_4609_; 
v___x_4609_ = 2147483648;
v___y_4594_ = v___y_4607_;
v___y_4595_ = v___y_4605_;
v___y_4596_ = v___y_4606_;
v___y_4597_ = v___x_4609_;
goto v___jp_4593_;
}
}
v___jp_4610_:
{
uint64_t v___x_4616_; uint64_t v_encodedExponent_4617_; uint32_t v___x_4618_; uint64_t v___x_4619_; uint8_t v___x_4620_; 
v___x_4616_ = 171ULL;
v_encodedExponent_4617_ = lean_uint64_sub(v___y_4611_, v___x_4616_);
v___x_4618_ = lean_uint64_to_uint32(v_encodedExponent_4617_);
v___x_4619_ = 8388608ULL;
v___x_4620_ = lean_uint64_dec_lt(v___y_4615_, v___x_4619_);
if (v___x_4620_ == 0)
{
uint64_t v___x_4621_; uint32_t v___x_4622_; 
v___x_4621_ = lean_uint64_sub(v___y_4615_, v___x_4619_);
v___x_4622_ = lean_uint64_to_uint32(v___x_4621_);
v___y_4604_ = v___y_4612_;
v___y_4605_ = v___y_4613_;
v___y_4606_ = v___x_4618_;
v___y_4607_ = v___x_4622_;
goto v___jp_4603_;
}
else
{
uint32_t v___x_4623_; 
v___x_4623_ = lean_uint64_to_uint32(v___y_4614_);
v___y_4604_ = v___y_4612_;
v___y_4605_ = v___y_4613_;
v___y_4606_ = v___x_4618_;
v___y_4607_ = v___x_4623_;
goto v___jp_4603_;
}
}
v___jp_4624_:
{
uint64_t v___x_4631_; uint8_t v___x_4632_; 
v___x_4631_ = 425ULL;
v___x_4632_ = lean_uint64_dec_lt(v___x_4631_, v___y_4630_);
if (v___x_4632_ == 0)
{
if (v___y_4626_ == 0)
{
v___y_4611_ = v___y_4630_;
v___y_4612_ = v___y_4627_;
v___y_4613_ = v___y_4628_;
v___y_4614_ = v___y_4629_;
v___y_4615_ = v___y_4625_;
goto v___jp_4610_;
}
else
{
uint64_t v___x_4633_; 
v___x_4633_ = 8388608ULL;
v___y_4611_ = v___y_4630_;
v___y_4612_ = v___y_4627_;
v___y_4613_ = v___y_4628_;
v___y_4614_ = v___y_4629_;
v___y_4615_ = v___x_4633_;
goto v___jp_4610_;
}
}
else
{
if (v___y_4627_ == 0)
{
uint32_t v___x_4634_; 
v___x_4634_ = 2139095040;
return v___x_4634_;
}
else
{
uint32_t v___x_4635_; 
v___x_4635_ = 4286578688;
return v___x_4635_;
}
}
}
v___jp_4636_:
{
uint64_t v___x_4642_; uint8_t v_carry_4643_; 
v___x_4642_ = 16777216ULL;
v_carry_4643_ = lean_uint64_dec_eq(v___y_4641_, v___x_4642_);
if (v_carry_4643_ == 0)
{
v___y_4625_ = v___y_4641_;
v___y_4626_ = v_carry_4643_;
v___y_4627_ = v___y_4637_;
v___y_4628_ = v___y_4638_;
v___y_4629_ = v___y_4640_;
v___y_4630_ = v___y_4639_;
goto v___jp_4624_;
}
else
{
uint64_t v___x_4644_; uint64_t v___x_4645_; 
v___x_4644_ = 1ULL;
v___x_4645_ = lean_uint64_add(v___y_4639_, v___x_4644_);
v___y_4625_ = v___y_4641_;
v___y_4626_ = v_carry_4643_;
v___y_4627_ = v___y_4637_;
v___y_4628_ = v___y_4638_;
v___y_4629_ = v___y_4640_;
v___y_4630_ = v___x_4645_;
goto v___jp_4624_;
}
}
v___jp_4646_:
{
uint64_t v_position_4653_; uint64_t v___x_4654_; uint8_t v___x_4655_; 
v_position_4653_ = lean_uint64_add(v___y_4652_, v___y_4649_);
v___x_4654_ = 172ULL;
v___x_4655_ = lean_uint64_dec_lt(v_position_4653_, v___x_4654_);
if (v___x_4655_ == 0)
{
uint64_t v___x_4656_; uint8_t v___x_4657_; 
v___x_4656_ = 23ULL;
v___x_4657_ = lean_uint64_dec_lt(v___y_4652_, v___x_4656_);
if (v___x_4657_ == 0)
{
uint64_t v___x_4658_; uint8_t v___x_4659_; 
v___x_4658_ = lean_uint64_sub(v___y_4652_, v___x_4656_);
v___x_4659_ = lean_uint64_dec_eq(v___x_4658_, v___y_4651_);
if (v___x_4659_ == 0)
{
uint64_t v___x_4660_; uint8_t v___x_4661_; 
v___x_4660_ = 64ULL;
v___x_4661_ = lean_uint64_dec_lt(v___x_4658_, v___x_4660_);
if (v___x_4661_ == 0)
{
uint8_t v___x_4662_; 
v___x_4662_ = lean_uint64_dec_eq(v___x_4658_, v___x_4660_);
if (v___x_4662_ == 0)
{
v___y_4637_ = v___y_4647_;
v___y_4638_ = v___y_4648_;
v___y_4639_ = v_position_4653_;
v___y_4640_ = v___y_4651_;
v___y_4641_ = v___y_4651_;
goto v___jp_4636_;
}
else
{
uint64_t v___x_4663_; uint8_t v___x_4664_; 
v___x_4663_ = 9223372036854775808ULL;
v___x_4664_ = lean_uint64_dec_lt(v___x_4663_, v___y_4650_);
if (v___x_4664_ == 0)
{
v___y_4637_ = v___y_4647_;
v___y_4638_ = v___y_4648_;
v___y_4639_ = v_position_4653_;
v___y_4640_ = v___y_4651_;
v___y_4641_ = v___y_4651_;
goto v___jp_4636_;
}
else
{
uint64_t v___x_4665_; 
v___x_4665_ = 1ULL;
v___y_4637_ = v___y_4647_;
v___y_4638_ = v___y_4648_;
v___y_4639_ = v_position_4653_;
v___y_4640_ = v___y_4651_;
v___y_4641_ = v___x_4665_;
goto v___jp_4636_;
}
}
}
else
{
uint64_t v_quotient_4666_; uint64_t v___x_4667_; uint64_t v___x_4668_; uint64_t v___x_4669_; uint64_t v_remainder_4670_; uint64_t v___x_4671_; uint64_t v_half_4672_; uint8_t v___x_4673_; 
v_quotient_4666_ = lean_uint64_shift_right(v___y_4650_, v___x_4658_);
v___x_4667_ = 1ULL;
v___x_4668_ = lean_uint64_shift_left(v___x_4667_, v___x_4658_);
v___x_4669_ = lean_uint64_sub(v___x_4668_, v___x_4667_);
v_remainder_4670_ = lean_uint64_land(v___y_4650_, v___x_4669_);
v___x_4671_ = lean_uint64_sub(v___x_4658_, v___x_4667_);
v_half_4672_ = lean_uint64_shift_left(v___x_4667_, v___x_4671_);
v___x_4673_ = lean_uint64_dec_lt(v_remainder_4670_, v_half_4672_);
if (v___x_4673_ == 0)
{
uint8_t v___x_4674_; 
v___x_4674_ = lean_uint64_dec_lt(v_half_4672_, v_remainder_4670_);
if (v___x_4674_ == 0)
{
uint64_t v___x_4675_; uint8_t v___x_4676_; 
v___x_4675_ = lean_uint64_land(v_quotient_4666_, v___x_4667_);
v___x_4676_ = lean_uint64_dec_eq(v___x_4675_, v___y_4651_);
if (v___x_4676_ == 0)
{
uint64_t v___x_4677_; 
v___x_4677_ = lean_uint64_add(v_quotient_4666_, v___x_4667_);
v___y_4637_ = v___y_4647_;
v___y_4638_ = v___y_4648_;
v___y_4639_ = v_position_4653_;
v___y_4640_ = v___y_4651_;
v___y_4641_ = v___x_4677_;
goto v___jp_4636_;
}
else
{
v___y_4637_ = v___y_4647_;
v___y_4638_ = v___y_4648_;
v___y_4639_ = v_position_4653_;
v___y_4640_ = v___y_4651_;
v___y_4641_ = v_quotient_4666_;
goto v___jp_4636_;
}
}
else
{
uint64_t v___x_4678_; 
v___x_4678_ = lean_uint64_add(v_quotient_4666_, v___x_4667_);
v___y_4637_ = v___y_4647_;
v___y_4638_ = v___y_4648_;
v___y_4639_ = v_position_4653_;
v___y_4640_ = v___y_4651_;
v___y_4641_ = v___x_4678_;
goto v___jp_4636_;
}
}
else
{
v___y_4637_ = v___y_4647_;
v___y_4638_ = v___y_4648_;
v___y_4639_ = v_position_4653_;
v___y_4640_ = v___y_4651_;
v___y_4641_ = v_quotient_4666_;
goto v___jp_4636_;
}
}
}
else
{
v___y_4637_ = v___y_4647_;
v___y_4638_ = v___y_4648_;
v___y_4639_ = v_position_4653_;
v___y_4640_ = v___y_4651_;
v___y_4641_ = v___y_4650_;
goto v___jp_4636_;
}
}
else
{
uint64_t v___x_4679_; uint64_t v___x_4680_; 
v___x_4679_ = lean_uint64_sub(v___x_4656_, v___y_4652_);
v___x_4680_ = lean_uint64_shift_left(v___y_4650_, v___x_4679_);
v___y_4637_ = v___y_4647_;
v___y_4638_ = v___y_4648_;
v___y_4639_ = v_position_4653_;
v___y_4640_ = v___y_4651_;
v___y_4641_ = v___x_4680_;
goto v___jp_4636_;
}
}
else
{
uint64_t v___x_4681_; uint8_t v___x_4682_; 
v___x_4681_ = 149ULL;
v___x_4682_ = lean_uint64_dec_lt(v___y_4649_, v___x_4681_);
if (v___x_4682_ == 0)
{
uint64_t v___x_4683_; uint64_t v___x_4684_; 
v___x_4683_ = lean_uint64_sub(v___y_4649_, v___x_4681_);
v___x_4684_ = lean_uint64_shift_left(v___y_4650_, v___x_4683_);
v___y_4226_ = v___y_4647_;
v___y_4227_ = v___y_4648_;
v___y_4228_ = v___y_4651_;
v___y_4229_ = v___x_4684_;
goto v___jp_4225_;
}
else
{
uint64_t v___x_4685_; uint8_t v___x_4686_; 
v___x_4685_ = lean_uint64_sub(v___x_4681_, v___y_4649_);
v___x_4686_ = lean_uint64_dec_eq(v___x_4685_, v___y_4651_);
if (v___x_4686_ == 0)
{
uint64_t v___x_4687_; uint8_t v___x_4688_; 
v___x_4687_ = 64ULL;
v___x_4688_ = lean_uint64_dec_lt(v___x_4685_, v___x_4687_);
if (v___x_4688_ == 0)
{
uint8_t v___x_4689_; 
v___x_4689_ = lean_uint64_dec_eq(v___x_4685_, v___x_4687_);
if (v___x_4689_ == 0)
{
v___y_4226_ = v___y_4647_;
v___y_4227_ = v___y_4648_;
v___y_4228_ = v___y_4651_;
v___y_4229_ = v___y_4651_;
goto v___jp_4225_;
}
else
{
uint64_t v___x_4690_; uint8_t v___x_4691_; 
v___x_4690_ = 9223372036854775808ULL;
v___x_4691_ = lean_uint64_dec_lt(v___x_4690_, v___y_4650_);
if (v___x_4691_ == 0)
{
v___y_4226_ = v___y_4647_;
v___y_4227_ = v___y_4648_;
v___y_4228_ = v___y_4651_;
v___y_4229_ = v___y_4651_;
goto v___jp_4225_;
}
else
{
uint64_t v___x_4692_; 
v___x_4692_ = 1ULL;
v___y_4226_ = v___y_4647_;
v___y_4227_ = v___y_4648_;
v___y_4228_ = v___y_4651_;
v___y_4229_ = v___x_4692_;
goto v___jp_4225_;
}
}
}
else
{
uint64_t v_quotient_4693_; uint64_t v___x_4694_; uint64_t v___x_4695_; uint64_t v___x_4696_; uint64_t v_remainder_4697_; uint64_t v___x_4698_; uint64_t v_half_4699_; uint8_t v___x_4700_; 
v_quotient_4693_ = lean_uint64_shift_right(v___y_4650_, v___x_4685_);
v___x_4694_ = 1ULL;
v___x_4695_ = lean_uint64_shift_left(v___x_4694_, v___x_4685_);
v___x_4696_ = lean_uint64_sub(v___x_4695_, v___x_4694_);
v_remainder_4697_ = lean_uint64_land(v___y_4650_, v___x_4696_);
v___x_4698_ = lean_uint64_sub(v___x_4685_, v___x_4694_);
v_half_4699_ = lean_uint64_shift_left(v___x_4694_, v___x_4698_);
v___x_4700_ = lean_uint64_dec_lt(v_remainder_4697_, v_half_4699_);
if (v___x_4700_ == 0)
{
uint8_t v___x_4701_; 
v___x_4701_ = lean_uint64_dec_lt(v_half_4699_, v_remainder_4697_);
if (v___x_4701_ == 0)
{
uint64_t v___x_4702_; uint8_t v___x_4703_; 
v___x_4702_ = lean_uint64_land(v_quotient_4693_, v___x_4694_);
v___x_4703_ = lean_uint64_dec_eq(v___x_4702_, v___y_4651_);
if (v___x_4703_ == 0)
{
uint64_t v___x_4704_; 
v___x_4704_ = lean_uint64_add(v_quotient_4693_, v___x_4694_);
v___y_4226_ = v___y_4647_;
v___y_4227_ = v___y_4648_;
v___y_4228_ = v___y_4651_;
v___y_4229_ = v___x_4704_;
goto v___jp_4225_;
}
else
{
v___y_4226_ = v___y_4647_;
v___y_4227_ = v___y_4648_;
v___y_4228_ = v___y_4651_;
v___y_4229_ = v_quotient_4693_;
goto v___jp_4225_;
}
}
else
{
uint64_t v___x_4705_; 
v___x_4705_ = lean_uint64_add(v_quotient_4693_, v___x_4694_);
v___y_4226_ = v___y_4647_;
v___y_4227_ = v___y_4648_;
v___y_4228_ = v___y_4651_;
v___y_4229_ = v___x_4705_;
goto v___jp_4225_;
}
}
else
{
v___y_4226_ = v___y_4647_;
v___y_4227_ = v___y_4648_;
v___y_4228_ = v___y_4651_;
v___y_4229_ = v_quotient_4693_;
goto v___jp_4225_;
}
}
}
else
{
v___y_4226_ = v___y_4647_;
v___y_4227_ = v___y_4648_;
v___y_4228_ = v___y_4651_;
v___y_4229_ = v___y_4650_;
goto v___jp_4225_;
}
}
}
}
v___jp_4706_:
{
uint64_t v___x_4714_; uint64_t v___x_4715_; uint8_t v___x_4716_; 
v___x_4714_ = 1ULL;
v___x_4715_ = lean_uint64_shift_right(v___y_4711_, v___x_4714_);
v___x_4716_ = lean_uint64_dec_eq(v___x_4715_, v___y_4712_);
if (v___x_4716_ == 0)
{
uint64_t v___x_4717_; 
v___x_4717_ = lean_uint64_add(v___y_4713_, v___x_4714_);
v___y_4647_ = v___y_4707_;
v___y_4648_ = v___y_4708_;
v___y_4649_ = v___y_4709_;
v___y_4650_ = v___y_4710_;
v___y_4651_ = v___y_4712_;
v___y_4652_ = v___x_4717_;
goto v___jp_4646_;
}
else
{
v___y_4647_ = v___y_4707_;
v___y_4648_ = v___y_4708_;
v___y_4649_ = v___y_4709_;
v___y_4650_ = v___y_4710_;
v___y_4651_ = v___y_4712_;
v___y_4652_ = v___y_4713_;
goto v___jp_4646_;
}
}
v___jp_4718_:
{
uint64_t v___x_4728_; uint8_t v___x_4729_; 
v___x_4728_ = lean_uint64_shift_right(v___y_4720_, v___y_4719_);
v___x_4729_ = lean_uint64_dec_eq(v___x_4728_, v___y_4726_);
if (v___x_4729_ == 0)
{
uint64_t v___x_4730_; 
v___x_4730_ = lean_uint64_add(v___y_4721_, v___y_4719_);
v___y_4707_ = v___y_4722_;
v___y_4708_ = v___y_4723_;
v___y_4709_ = v___y_4724_;
v___y_4710_ = v___y_4725_;
v___y_4711_ = v___y_4727_;
v___y_4712_ = v___y_4726_;
v___y_4713_ = v___x_4730_;
goto v___jp_4706_;
}
else
{
v___y_4707_ = v___y_4722_;
v___y_4708_ = v___y_4723_;
v___y_4709_ = v___y_4724_;
v___y_4710_ = v___y_4725_;
v___y_4711_ = v___y_4727_;
v___y_4712_ = v___y_4726_;
v___y_4713_ = v___y_4721_;
goto v___jp_4706_;
}
}
v___jp_4731_:
{
uint64_t v___x_4739_; uint64_t v___x_4740_; uint8_t v___x_4741_; 
v___x_4739_ = 2ULL;
v___x_4740_ = lean_uint64_shift_right(v___y_4732_, v___x_4739_);
v___x_4741_ = lean_uint64_dec_eq(v___x_4740_, v___y_4737_);
if (v___x_4741_ == 0)
{
v___y_4719_ = v___x_4739_;
v___y_4720_ = v___y_4732_;
v___y_4721_ = v___y_4738_;
v___y_4722_ = v___y_4733_;
v___y_4723_ = v___y_4734_;
v___y_4724_ = v___y_4735_;
v___y_4725_ = v___y_4736_;
v___y_4726_ = v___y_4737_;
v___y_4727_ = v___x_4740_;
goto v___jp_4718_;
}
else
{
v___y_4719_ = v___x_4739_;
v___y_4720_ = v___y_4732_;
v___y_4721_ = v___y_4738_;
v___y_4722_ = v___y_4733_;
v___y_4723_ = v___y_4734_;
v___y_4724_ = v___y_4735_;
v___y_4725_ = v___y_4736_;
v___y_4726_ = v___y_4737_;
v___y_4727_ = v___y_4732_;
goto v___jp_4718_;
}
}
v___jp_4742_:
{
uint64_t v___x_4752_; uint8_t v___x_4753_; 
v___x_4752_ = lean_uint64_shift_right(v___y_4745_, v___y_4743_);
v___x_4753_ = lean_uint64_dec_eq(v___x_4752_, v___y_4750_);
if (v___x_4753_ == 0)
{
uint64_t v___x_4754_; 
v___x_4754_ = lean_uint64_add(v___y_4744_, v___y_4743_);
v___y_4732_ = v___y_4751_;
v___y_4733_ = v___y_4746_;
v___y_4734_ = v___y_4747_;
v___y_4735_ = v___y_4748_;
v___y_4736_ = v___y_4749_;
v___y_4737_ = v___y_4750_;
v___y_4738_ = v___x_4754_;
goto v___jp_4731_;
}
else
{
v___y_4732_ = v___y_4751_;
v___y_4733_ = v___y_4746_;
v___y_4734_ = v___y_4747_;
v___y_4735_ = v___y_4748_;
v___y_4736_ = v___y_4749_;
v___y_4737_ = v___y_4750_;
v___y_4738_ = v___y_4744_;
goto v___jp_4731_;
}
}
v___jp_4755_:
{
uint64_t v___x_4763_; uint64_t v___x_4764_; uint8_t v___x_4765_; 
v___x_4763_ = 4ULL;
v___x_4764_ = lean_uint64_shift_right(v___y_4757_, v___x_4763_);
v___x_4765_ = lean_uint64_dec_eq(v___x_4764_, v___y_4761_);
if (v___x_4765_ == 0)
{
v___y_4743_ = v___x_4763_;
v___y_4744_ = v___y_4762_;
v___y_4745_ = v___y_4757_;
v___y_4746_ = v___y_4756_;
v___y_4747_ = v___y_4758_;
v___y_4748_ = v___y_4759_;
v___y_4749_ = v___y_4760_;
v___y_4750_ = v___y_4761_;
v___y_4751_ = v___x_4764_;
goto v___jp_4742_;
}
else
{
v___y_4743_ = v___x_4763_;
v___y_4744_ = v___y_4762_;
v___y_4745_ = v___y_4757_;
v___y_4746_ = v___y_4756_;
v___y_4747_ = v___y_4758_;
v___y_4748_ = v___y_4759_;
v___y_4749_ = v___y_4760_;
v___y_4750_ = v___y_4761_;
v___y_4751_ = v___y_4757_;
goto v___jp_4742_;
}
}
v___jp_4766_:
{
uint64_t v___x_4776_; uint8_t v___x_4777_; 
v___x_4776_ = lean_uint64_shift_right(v___y_4773_, v___y_4767_);
v___x_4777_ = lean_uint64_dec_eq(v___x_4776_, v___y_4774_);
if (v___x_4777_ == 0)
{
uint64_t v___x_4778_; 
v___x_4778_ = lean_uint64_add(v___y_4772_, v___y_4767_);
v___y_4756_ = v___y_4768_;
v___y_4757_ = v___y_4775_;
v___y_4758_ = v___y_4769_;
v___y_4759_ = v___y_4770_;
v___y_4760_ = v___y_4771_;
v___y_4761_ = v___y_4774_;
v___y_4762_ = v___x_4778_;
goto v___jp_4755_;
}
else
{
v___y_4756_ = v___y_4768_;
v___y_4757_ = v___y_4775_;
v___y_4758_ = v___y_4769_;
v___y_4759_ = v___y_4770_;
v___y_4760_ = v___y_4771_;
v___y_4761_ = v___y_4774_;
v___y_4762_ = v___y_4772_;
goto v___jp_4755_;
}
}
v___jp_4779_:
{
uint64_t v___x_4787_; uint64_t v___x_4788_; uint8_t v___x_4789_; 
v___x_4787_ = 8ULL;
v___x_4788_ = lean_uint64_shift_right(v___y_4785_, v___x_4787_);
v___x_4789_ = lean_uint64_dec_eq(v___x_4788_, v___y_4784_);
if (v___x_4789_ == 0)
{
v___y_4767_ = v___x_4787_;
v___y_4768_ = v___y_4780_;
v___y_4769_ = v___y_4781_;
v___y_4770_ = v___y_4782_;
v___y_4771_ = v___y_4783_;
v___y_4772_ = v___y_4786_;
v___y_4773_ = v___y_4785_;
v___y_4774_ = v___y_4784_;
v___y_4775_ = v___x_4788_;
goto v___jp_4766_;
}
else
{
v___y_4767_ = v___x_4787_;
v___y_4768_ = v___y_4780_;
v___y_4769_ = v___y_4781_;
v___y_4770_ = v___y_4782_;
v___y_4771_ = v___y_4783_;
v___y_4772_ = v___y_4786_;
v___y_4773_ = v___y_4785_;
v___y_4774_ = v___y_4784_;
v___y_4775_ = v___y_4785_;
goto v___jp_4766_;
}
}
v___jp_4790_:
{
uint64_t v___x_4800_; uint8_t v___x_4801_; 
v___x_4800_ = lean_uint64_shift_right(v___y_4792_, v___y_4793_);
v___x_4801_ = lean_uint64_dec_eq(v___x_4800_, v___y_4798_);
if (v___x_4801_ == 0)
{
uint64_t v___x_4802_; 
v___x_4802_ = lean_uint64_add(v___y_4791_, v___y_4793_);
v___y_4780_ = v___y_4794_;
v___y_4781_ = v___y_4795_;
v___y_4782_ = v___y_4796_;
v___y_4783_ = v___y_4797_;
v___y_4784_ = v___y_4798_;
v___y_4785_ = v___y_4799_;
v___y_4786_ = v___x_4802_;
goto v___jp_4779_;
}
else
{
v___y_4780_ = v___y_4794_;
v___y_4781_ = v___y_4795_;
v___y_4782_ = v___y_4796_;
v___y_4783_ = v___y_4797_;
v___y_4784_ = v___y_4798_;
v___y_4785_ = v___y_4799_;
v___y_4786_ = v___y_4791_;
goto v___jp_4779_;
}
}
v___jp_4803_:
{
uint64_t v___x_4811_; uint64_t v___x_4812_; uint8_t v___x_4813_; 
v___x_4811_ = 16ULL;
v___x_4812_ = lean_uint64_shift_right(v___y_4804_, v___x_4811_);
v___x_4813_ = lean_uint64_dec_eq(v___x_4812_, v___y_4809_);
if (v___x_4813_ == 0)
{
v___y_4791_ = v___y_4810_;
v___y_4792_ = v___y_4804_;
v___y_4793_ = v___x_4811_;
v___y_4794_ = v___y_4805_;
v___y_4795_ = v___y_4806_;
v___y_4796_ = v___y_4807_;
v___y_4797_ = v___y_4808_;
v___y_4798_ = v___y_4809_;
v___y_4799_ = v___x_4812_;
goto v___jp_4790_;
}
else
{
v___y_4791_ = v___y_4810_;
v___y_4792_ = v___y_4804_;
v___y_4793_ = v___x_4811_;
v___y_4794_ = v___y_4805_;
v___y_4795_ = v___y_4806_;
v___y_4796_ = v___y_4807_;
v___y_4797_ = v___y_4808_;
v___y_4798_ = v___y_4809_;
v___y_4799_ = v___y_4804_;
goto v___jp_4790_;
}
}
v___jp_4814_:
{
uint64_t v___x_4822_; uint8_t v___x_4823_; 
v___x_4822_ = lean_uint64_shift_right(v___y_4819_, v___y_4818_);
v___x_4823_ = lean_uint64_dec_eq(v___x_4822_, v___y_4820_);
if (v___x_4823_ == 0)
{
v___y_4804_ = v___y_4821_;
v___y_4805_ = v___y_4815_;
v___y_4806_ = v___y_4816_;
v___y_4807_ = v___y_4817_;
v___y_4808_ = v___y_4819_;
v___y_4809_ = v___y_4820_;
v___y_4810_ = v___y_4818_;
goto v___jp_4803_;
}
else
{
v___y_4804_ = v___y_4821_;
v___y_4805_ = v___y_4815_;
v___y_4806_ = v___y_4816_;
v___y_4807_ = v___y_4817_;
v___y_4808_ = v___y_4819_;
v___y_4809_ = v___y_4820_;
v___y_4810_ = v___y_4820_;
goto v___jp_4803_;
}
}
v___jp_4824_:
{
uint64_t v___x_4829_; uint8_t v___x_4830_; 
v___x_4829_ = 0ULL;
v___x_4830_ = lean_uint64_dec_eq(v___y_4828_, v___x_4829_);
if (v___x_4830_ == 0)
{
uint64_t v___x_4831_; uint64_t v___x_4832_; uint8_t v___x_4833_; 
v___x_4831_ = 32ULL;
v___x_4832_ = lean_uint64_shift_right(v___y_4828_, v___x_4831_);
v___x_4833_ = lean_uint64_dec_eq(v___x_4832_, v___x_4829_);
if (v___x_4833_ == 0)
{
v___y_4815_ = v___y_4825_;
v___y_4816_ = v___y_4826_;
v___y_4817_ = v___y_4827_;
v___y_4818_ = v___x_4831_;
v___y_4819_ = v___y_4828_;
v___y_4820_ = v___x_4829_;
v___y_4821_ = v___x_4832_;
goto v___jp_4814_;
}
else
{
v___y_4815_ = v___y_4825_;
v___y_4816_ = v___y_4826_;
v___y_4817_ = v___y_4827_;
v___y_4818_ = v___x_4831_;
v___y_4819_ = v___y_4828_;
v___y_4820_ = v___x_4829_;
v___y_4821_ = v___y_4828_;
goto v___jp_4814_;
}
}
else
{
if (v___y_4825_ == 0)
{
uint32_t v___x_4834_; 
v___x_4834_ = 0;
return v___x_4834_;
}
else
{
uint32_t v___x_4835_; 
v___x_4835_ = 2147483648;
return v___x_4835_;
}
}
}
v___jp_4836_:
{
uint64_t v___x_4843_; uint64_t v___x_4844_; uint64_t v___x_4845_; uint8_t v___x_4846_; 
v___x_4843_ = lean_uint64_mul(v___y_4837_, v___y_4841_);
v___x_4844_ = lean_uint64_add(v___y_4840_, v___y_4842_);
v___x_4845_ = 281474976710656ULL;
v___x_4846_ = lean_uint64_dec_lt(v___x_4843_, v___x_4845_);
if (v___x_4846_ == 0)
{
v___y_4825_ = v___y_4838_;
v___y_4826_ = v___y_4839_;
v___y_4827_ = v___x_4844_;
v___y_4828_ = v___x_4843_;
goto v___jp_4824_;
}
else
{
uint64_t v___x_4847_; uint8_t v___x_4848_; 
v___x_4847_ = 123ULL;
v___x_4848_ = lean_uint64_dec_le(v___x_4844_, v___x_4847_);
if (v___x_4848_ == 0)
{
v___y_4825_ = v___y_4838_;
v___y_4826_ = v___y_4839_;
v___y_4827_ = v___x_4844_;
v___y_4828_ = v___x_4843_;
goto v___jp_4824_;
}
else
{
uint64_t v___x_4849_; uint8_t v___x_4850_; 
v___x_4849_ = 0ULL;
v___x_4850_ = lean_uint64_dec_eq(v___x_4843_, v___x_4849_);
if (v___x_4850_ == 0)
{
uint64_t v___x_4851_; uint64_t v___x_4852_; uint8_t v___x_4853_; 
v___x_4851_ = 149ULL;
v___x_4852_ = lean_uint64_sub(v___x_4851_, v___x_4844_);
v___x_4853_ = lean_uint64_dec_eq(v___x_4852_, v___x_4849_);
if (v___x_4853_ == 0)
{
uint64_t v___x_4854_; uint8_t v___x_4855_; 
v___x_4854_ = 64ULL;
v___x_4855_ = lean_uint64_dec_lt(v___x_4852_, v___x_4854_);
if (v___x_4855_ == 0)
{
uint8_t v___x_4856_; 
v___x_4856_ = lean_uint64_dec_eq(v___x_4852_, v___x_4854_);
if (v___x_4856_ == 0)
{
v___y_4247_ = v___y_4838_;
v___y_4248_ = v___y_4839_;
v___y_4249_ = v___x_4849_;
v___y_4250_ = v___x_4849_;
goto v___jp_4246_;
}
else
{
uint64_t v___x_4857_; uint8_t v___x_4858_; 
v___x_4857_ = 9223372036854775808ULL;
v___x_4858_ = lean_uint64_dec_lt(v___x_4857_, v___x_4843_);
if (v___x_4858_ == 0)
{
v___y_4247_ = v___y_4838_;
v___y_4248_ = v___y_4839_;
v___y_4249_ = v___x_4849_;
v___y_4250_ = v___x_4849_;
goto v___jp_4246_;
}
else
{
uint64_t v___x_4859_; 
v___x_4859_ = 1ULL;
v___y_4247_ = v___y_4838_;
v___y_4248_ = v___y_4839_;
v___y_4249_ = v___x_4849_;
v___y_4250_ = v___x_4859_;
goto v___jp_4246_;
}
}
}
else
{
uint64_t v_quotient_4860_; uint64_t v___x_4861_; uint64_t v___x_4862_; uint64_t v___x_4863_; uint64_t v_remainder_4864_; uint64_t v___x_4865_; uint64_t v_half_4866_; uint8_t v___x_4867_; 
v_quotient_4860_ = lean_uint64_shift_right(v___x_4843_, v___x_4852_);
v___x_4861_ = 1ULL;
v___x_4862_ = lean_uint64_shift_left(v___x_4861_, v___x_4852_);
v___x_4863_ = lean_uint64_sub(v___x_4862_, v___x_4861_);
v_remainder_4864_ = lean_uint64_land(v___x_4843_, v___x_4863_);
v___x_4865_ = lean_uint64_sub(v___x_4852_, v___x_4861_);
v_half_4866_ = lean_uint64_shift_left(v___x_4861_, v___x_4865_);
v___x_4867_ = lean_uint64_dec_lt(v_remainder_4864_, v_half_4866_);
if (v___x_4867_ == 0)
{
uint8_t v___x_4868_; 
v___x_4868_ = lean_uint64_dec_lt(v_half_4866_, v_remainder_4864_);
if (v___x_4868_ == 0)
{
uint64_t v___x_4869_; uint8_t v___x_4870_; 
v___x_4869_ = lean_uint64_land(v_quotient_4860_, v___x_4861_);
v___x_4870_ = lean_uint64_dec_eq(v___x_4869_, v___x_4849_);
if (v___x_4870_ == 0)
{
uint64_t v___x_4871_; 
v___x_4871_ = lean_uint64_add(v_quotient_4860_, v___x_4861_);
v___y_4247_ = v___y_4838_;
v___y_4248_ = v___y_4839_;
v___y_4249_ = v___x_4849_;
v___y_4250_ = v___x_4871_;
goto v___jp_4246_;
}
else
{
v___y_4247_ = v___y_4838_;
v___y_4248_ = v___y_4839_;
v___y_4249_ = v___x_4849_;
v___y_4250_ = v_quotient_4860_;
goto v___jp_4246_;
}
}
else
{
uint64_t v___x_4872_; 
v___x_4872_ = lean_uint64_add(v_quotient_4860_, v___x_4861_);
v___y_4247_ = v___y_4838_;
v___y_4248_ = v___y_4839_;
v___y_4249_ = v___x_4849_;
v___y_4250_ = v___x_4872_;
goto v___jp_4246_;
}
}
else
{
v___y_4247_ = v___y_4838_;
v___y_4248_ = v___y_4839_;
v___y_4249_ = v___x_4849_;
v___y_4250_ = v_quotient_4860_;
goto v___jp_4246_;
}
}
}
else
{
v___y_4247_ = v___y_4838_;
v___y_4248_ = v___y_4839_;
v___y_4249_ = v___x_4849_;
v___y_4250_ = v___x_4843_;
goto v___jp_4246_;
}
}
else
{
if (v___y_4838_ == 0)
{
uint32_t v___x_4873_; 
v___x_4873_ = 0;
return v___x_4873_;
}
else
{
uint32_t v___x_4874_; 
v___x_4874_ = 2147483648;
return v___x_4874_;
}
}
}
}
}
v___jp_4875_:
{
uint32_t v___x_4880_; uint32_t v___x_4881_; uint32_t v___x_4882_; uint32_t v___x_4883_; uint32_t v___x_4884_; 
v___x_4880_ = lean_uint32_land(v___y_4878_, v___x_4592_);
v___x_4881_ = lean_uint32_shift_left(v___x_4880_, v___x_4551_);
v___x_4882_ = lean_uint32_lor(v___y_4879_, v___x_4881_);
v___x_4883_ = lean_uint32_land(v___y_4876_, v___y_4877_);
v___x_4884_ = lean_uint32_lor(v___x_4882_, v___x_4883_);
return v___x_4884_;
}
v___jp_4885_:
{
if (v___y_4886_ == 0)
{
uint32_t v___x_4890_; 
v___x_4890_ = 0;
v___y_4876_ = v___y_4889_;
v___y_4877_ = v___y_4887_;
v___y_4878_ = v___y_4888_;
v___y_4879_ = v___x_4890_;
goto v___jp_4875_;
}
else
{
uint32_t v___x_4891_; 
v___x_4891_ = 2147483648;
v___y_4876_ = v___y_4889_;
v___y_4877_ = v___y_4887_;
v___y_4878_ = v___y_4888_;
v___y_4879_ = v___x_4891_;
goto v___jp_4875_;
}
}
v___jp_4892_:
{
uint64_t v___x_4898_; uint64_t v_encodedExponent_4899_; uint32_t v___x_4900_; uint64_t v___x_4901_; uint8_t v___x_4902_; 
v___x_4898_ = 171ULL;
v_encodedExponent_4899_ = lean_uint64_sub(v___y_4893_, v___x_4898_);
v___x_4900_ = lean_uint64_to_uint32(v_encodedExponent_4899_);
v___x_4901_ = 8388608ULL;
v___x_4902_ = lean_uint64_dec_lt(v___y_4897_, v___x_4901_);
if (v___x_4902_ == 0)
{
uint64_t v___x_4903_; uint32_t v___x_4904_; 
v___x_4903_ = lean_uint64_sub(v___y_4897_, v___x_4901_);
v___x_4904_ = lean_uint64_to_uint32(v___x_4903_);
v___y_4886_ = v___y_4896_;
v___y_4887_ = v___y_4895_;
v___y_4888_ = v___x_4900_;
v___y_4889_ = v___x_4904_;
goto v___jp_4885_;
}
else
{
uint32_t v___x_4905_; 
v___x_4905_ = lean_uint64_to_uint32(v___y_4894_);
v___y_4886_ = v___y_4896_;
v___y_4887_ = v___y_4895_;
v___y_4888_ = v___x_4900_;
v___y_4889_ = v___x_4905_;
goto v___jp_4885_;
}
}
v___jp_4906_:
{
uint64_t v___x_4913_; uint8_t v___x_4914_; 
v___x_4913_ = 425ULL;
v___x_4914_ = lean_uint64_dec_lt(v___x_4913_, v___y_4912_);
if (v___x_4914_ == 0)
{
if (v___y_4907_ == 0)
{
v___y_4893_ = v___y_4912_;
v___y_4894_ = v___y_4909_;
v___y_4895_ = v___y_4911_;
v___y_4896_ = v___y_4910_;
v___y_4897_ = v___y_4908_;
goto v___jp_4892_;
}
else
{
uint64_t v___x_4915_; 
v___x_4915_ = 8388608ULL;
v___y_4893_ = v___y_4912_;
v___y_4894_ = v___y_4909_;
v___y_4895_ = v___y_4911_;
v___y_4896_ = v___y_4910_;
v___y_4897_ = v___x_4915_;
goto v___jp_4892_;
}
}
else
{
if (v___y_4910_ == 0)
{
uint32_t v___x_4916_; 
v___x_4916_ = 2139095040;
return v___x_4916_;
}
else
{
uint32_t v___x_4917_; 
v___x_4917_ = 4286578688;
return v___x_4917_;
}
}
}
v___jp_4918_:
{
uint64_t v___x_4924_; uint8_t v_carry_4925_; 
v___x_4924_ = 16777216ULL;
v_carry_4925_ = lean_uint64_dec_eq(v___y_4923_, v___x_4924_);
if (v_carry_4925_ == 0)
{
v___y_4907_ = v_carry_4925_;
v___y_4908_ = v___y_4923_;
v___y_4909_ = v___y_4920_;
v___y_4910_ = v___y_4922_;
v___y_4911_ = v___y_4921_;
v___y_4912_ = v___y_4919_;
goto v___jp_4906_;
}
else
{
uint64_t v___x_4926_; uint64_t v___x_4927_; 
v___x_4926_ = 1ULL;
v___x_4927_ = lean_uint64_add(v___y_4919_, v___x_4926_);
v___y_4907_ = v_carry_4925_;
v___y_4908_ = v___y_4923_;
v___y_4909_ = v___y_4920_;
v___y_4910_ = v___y_4922_;
v___y_4911_ = v___y_4921_;
v___y_4912_ = v___x_4927_;
goto v___jp_4906_;
}
}
v___jp_4928_:
{
uint64_t v_position_4935_; uint64_t v___x_4936_; uint8_t v___x_4937_; 
v_position_4935_ = lean_uint64_add(v___y_4934_, v___y_4933_);
v___x_4936_ = 172ULL;
v___x_4937_ = lean_uint64_dec_lt(v_position_4935_, v___x_4936_);
if (v___x_4937_ == 0)
{
uint64_t v___x_4938_; uint8_t v___x_4939_; 
v___x_4938_ = 23ULL;
v___x_4939_ = lean_uint64_dec_lt(v___y_4934_, v___x_4938_);
if (v___x_4939_ == 0)
{
uint64_t v___x_4940_; uint8_t v___x_4941_; 
v___x_4940_ = lean_uint64_sub(v___y_4934_, v___x_4938_);
v___x_4941_ = lean_uint64_dec_eq(v___x_4940_, v___y_4930_);
if (v___x_4941_ == 0)
{
uint64_t v___x_4942_; uint8_t v___x_4943_; 
v___x_4942_ = 64ULL;
v___x_4943_ = lean_uint64_dec_lt(v___x_4940_, v___x_4942_);
if (v___x_4943_ == 0)
{
uint8_t v___x_4944_; 
v___x_4944_ = lean_uint64_dec_eq(v___x_4940_, v___x_4942_);
if (v___x_4944_ == 0)
{
v___y_4919_ = v_position_4935_;
v___y_4920_ = v___y_4930_;
v___y_4921_ = v___y_4932_;
v___y_4922_ = v___y_4931_;
v___y_4923_ = v___y_4930_;
goto v___jp_4918_;
}
else
{
uint64_t v___x_4945_; uint8_t v___x_4946_; 
v___x_4945_ = 9223372036854775808ULL;
v___x_4946_ = lean_uint64_dec_lt(v___x_4945_, v___y_4929_);
if (v___x_4946_ == 0)
{
v___y_4919_ = v_position_4935_;
v___y_4920_ = v___y_4930_;
v___y_4921_ = v___y_4932_;
v___y_4922_ = v___y_4931_;
v___y_4923_ = v___y_4930_;
goto v___jp_4918_;
}
else
{
uint64_t v___x_4947_; 
v___x_4947_ = 1ULL;
v___y_4919_ = v_position_4935_;
v___y_4920_ = v___y_4930_;
v___y_4921_ = v___y_4932_;
v___y_4922_ = v___y_4931_;
v___y_4923_ = v___x_4947_;
goto v___jp_4918_;
}
}
}
else
{
uint64_t v_quotient_4948_; uint64_t v___x_4949_; uint64_t v___x_4950_; uint64_t v___x_4951_; uint64_t v_remainder_4952_; uint64_t v___x_4953_; uint64_t v_half_4954_; uint8_t v___x_4955_; 
v_quotient_4948_ = lean_uint64_shift_right(v___y_4929_, v___x_4940_);
v___x_4949_ = 1ULL;
v___x_4950_ = lean_uint64_shift_left(v___x_4949_, v___x_4940_);
v___x_4951_ = lean_uint64_sub(v___x_4950_, v___x_4949_);
v_remainder_4952_ = lean_uint64_land(v___y_4929_, v___x_4951_);
v___x_4953_ = lean_uint64_sub(v___x_4940_, v___x_4949_);
v_half_4954_ = lean_uint64_shift_left(v___x_4949_, v___x_4953_);
v___x_4955_ = lean_uint64_dec_lt(v_remainder_4952_, v_half_4954_);
if (v___x_4955_ == 0)
{
uint8_t v___x_4956_; 
v___x_4956_ = lean_uint64_dec_lt(v_half_4954_, v_remainder_4952_);
if (v___x_4956_ == 0)
{
uint64_t v___x_4957_; uint8_t v___x_4958_; 
v___x_4957_ = lean_uint64_land(v_quotient_4948_, v___x_4949_);
v___x_4958_ = lean_uint64_dec_eq(v___x_4957_, v___y_4930_);
if (v___x_4958_ == 0)
{
uint64_t v___x_4959_; 
v___x_4959_ = lean_uint64_add(v_quotient_4948_, v___x_4949_);
v___y_4919_ = v_position_4935_;
v___y_4920_ = v___y_4930_;
v___y_4921_ = v___y_4932_;
v___y_4922_ = v___y_4931_;
v___y_4923_ = v___x_4959_;
goto v___jp_4918_;
}
else
{
v___y_4919_ = v_position_4935_;
v___y_4920_ = v___y_4930_;
v___y_4921_ = v___y_4932_;
v___y_4922_ = v___y_4931_;
v___y_4923_ = v_quotient_4948_;
goto v___jp_4918_;
}
}
else
{
uint64_t v___x_4960_; 
v___x_4960_ = lean_uint64_add(v_quotient_4948_, v___x_4949_);
v___y_4919_ = v_position_4935_;
v___y_4920_ = v___y_4930_;
v___y_4921_ = v___y_4932_;
v___y_4922_ = v___y_4931_;
v___y_4923_ = v___x_4960_;
goto v___jp_4918_;
}
}
else
{
v___y_4919_ = v_position_4935_;
v___y_4920_ = v___y_4930_;
v___y_4921_ = v___y_4932_;
v___y_4922_ = v___y_4931_;
v___y_4923_ = v_quotient_4948_;
goto v___jp_4918_;
}
}
}
else
{
v___y_4919_ = v_position_4935_;
v___y_4920_ = v___y_4930_;
v___y_4921_ = v___y_4932_;
v___y_4922_ = v___y_4931_;
v___y_4923_ = v___y_4929_;
goto v___jp_4918_;
}
}
else
{
uint64_t v___x_4961_; uint64_t v___x_4962_; 
v___x_4961_ = lean_uint64_sub(v___x_4938_, v___y_4934_);
v___x_4962_ = lean_uint64_shift_left(v___y_4929_, v___x_4961_);
v___y_4919_ = v_position_4935_;
v___y_4920_ = v___y_4930_;
v___y_4921_ = v___y_4932_;
v___y_4922_ = v___y_4931_;
v___y_4923_ = v___x_4962_;
goto v___jp_4918_;
}
}
else
{
uint64_t v___x_4963_; uint8_t v___x_4964_; 
v___x_4963_ = 149ULL;
v___x_4964_ = lean_uint64_dec_lt(v___y_4933_, v___x_4963_);
if (v___x_4964_ == 0)
{
uint64_t v___x_4965_; uint64_t v___x_4966_; 
v___x_4965_ = lean_uint64_sub(v___y_4933_, v___x_4963_);
v___x_4966_ = lean_uint64_shift_left(v___y_4929_, v___x_4965_);
v___y_4371_ = v___y_4930_;
v___y_4372_ = v___y_4931_;
v___y_4373_ = v___y_4932_;
v___y_4374_ = v___x_4966_;
goto v___jp_4370_;
}
else
{
uint64_t v___x_4967_; uint8_t v___x_4968_; 
v___x_4967_ = lean_uint64_sub(v___x_4963_, v___y_4933_);
v___x_4968_ = lean_uint64_dec_eq(v___x_4967_, v___y_4930_);
if (v___x_4968_ == 0)
{
uint64_t v___x_4969_; uint8_t v___x_4970_; 
v___x_4969_ = 64ULL;
v___x_4970_ = lean_uint64_dec_lt(v___x_4967_, v___x_4969_);
if (v___x_4970_ == 0)
{
uint8_t v___x_4971_; 
v___x_4971_ = lean_uint64_dec_eq(v___x_4967_, v___x_4969_);
if (v___x_4971_ == 0)
{
v___y_4371_ = v___y_4930_;
v___y_4372_ = v___y_4931_;
v___y_4373_ = v___y_4932_;
v___y_4374_ = v___y_4930_;
goto v___jp_4370_;
}
else
{
uint64_t v___x_4972_; uint8_t v___x_4973_; 
v___x_4972_ = 9223372036854775808ULL;
v___x_4973_ = lean_uint64_dec_lt(v___x_4972_, v___y_4929_);
if (v___x_4973_ == 0)
{
v___y_4371_ = v___y_4930_;
v___y_4372_ = v___y_4931_;
v___y_4373_ = v___y_4932_;
v___y_4374_ = v___y_4930_;
goto v___jp_4370_;
}
else
{
uint64_t v___x_4974_; 
v___x_4974_ = 1ULL;
v___y_4371_ = v___y_4930_;
v___y_4372_ = v___y_4931_;
v___y_4373_ = v___y_4932_;
v___y_4374_ = v___x_4974_;
goto v___jp_4370_;
}
}
}
else
{
uint64_t v_quotient_4975_; uint64_t v___x_4976_; uint64_t v___x_4977_; uint64_t v___x_4978_; uint64_t v_remainder_4979_; uint64_t v___x_4980_; uint64_t v_half_4981_; uint8_t v___x_4982_; 
v_quotient_4975_ = lean_uint64_shift_right(v___y_4929_, v___x_4967_);
v___x_4976_ = 1ULL;
v___x_4977_ = lean_uint64_shift_left(v___x_4976_, v___x_4967_);
v___x_4978_ = lean_uint64_sub(v___x_4977_, v___x_4976_);
v_remainder_4979_ = lean_uint64_land(v___y_4929_, v___x_4978_);
v___x_4980_ = lean_uint64_sub(v___x_4967_, v___x_4976_);
v_half_4981_ = lean_uint64_shift_left(v___x_4976_, v___x_4980_);
v___x_4982_ = lean_uint64_dec_lt(v_remainder_4979_, v_half_4981_);
if (v___x_4982_ == 0)
{
uint8_t v___x_4983_; 
v___x_4983_ = lean_uint64_dec_lt(v_half_4981_, v_remainder_4979_);
if (v___x_4983_ == 0)
{
uint64_t v___x_4984_; uint8_t v___x_4985_; 
v___x_4984_ = lean_uint64_land(v_quotient_4975_, v___x_4976_);
v___x_4985_ = lean_uint64_dec_eq(v___x_4984_, v___y_4930_);
if (v___x_4985_ == 0)
{
uint64_t v___x_4986_; 
v___x_4986_ = lean_uint64_add(v_quotient_4975_, v___x_4976_);
v___y_4371_ = v___y_4930_;
v___y_4372_ = v___y_4931_;
v___y_4373_ = v___y_4932_;
v___y_4374_ = v___x_4986_;
goto v___jp_4370_;
}
else
{
v___y_4371_ = v___y_4930_;
v___y_4372_ = v___y_4931_;
v___y_4373_ = v___y_4932_;
v___y_4374_ = v_quotient_4975_;
goto v___jp_4370_;
}
}
else
{
uint64_t v___x_4987_; 
v___x_4987_ = lean_uint64_add(v_quotient_4975_, v___x_4976_);
v___y_4371_ = v___y_4930_;
v___y_4372_ = v___y_4931_;
v___y_4373_ = v___y_4932_;
v___y_4374_ = v___x_4987_;
goto v___jp_4370_;
}
}
else
{
v___y_4371_ = v___y_4930_;
v___y_4372_ = v___y_4931_;
v___y_4373_ = v___y_4932_;
v___y_4374_ = v_quotient_4975_;
goto v___jp_4370_;
}
}
}
else
{
v___y_4371_ = v___y_4930_;
v___y_4372_ = v___y_4931_;
v___y_4373_ = v___y_4932_;
v___y_4374_ = v___y_4929_;
goto v___jp_4370_;
}
}
}
}
v___jp_4988_:
{
uint64_t v___x_4996_; uint64_t v___x_4997_; uint8_t v___x_4998_; 
v___x_4996_ = 1ULL;
v___x_4997_ = lean_uint64_shift_right(v___y_4993_, v___x_4996_);
v___x_4998_ = lean_uint64_dec_eq(v___x_4997_, v___y_4990_);
if (v___x_4998_ == 0)
{
uint64_t v___x_4999_; 
v___x_4999_ = lean_uint64_add(v___y_4995_, v___x_4996_);
v___y_4929_ = v___y_4989_;
v___y_4930_ = v___y_4990_;
v___y_4931_ = v___y_4992_;
v___y_4932_ = v___y_4991_;
v___y_4933_ = v___y_4994_;
v___y_4934_ = v___x_4999_;
goto v___jp_4928_;
}
else
{
v___y_4929_ = v___y_4989_;
v___y_4930_ = v___y_4990_;
v___y_4931_ = v___y_4992_;
v___y_4932_ = v___y_4991_;
v___y_4933_ = v___y_4994_;
v___y_4934_ = v___y_4995_;
goto v___jp_4928_;
}
}
v___jp_5000_:
{
uint64_t v___x_5010_; uint8_t v___x_5011_; 
v___x_5010_ = lean_uint64_shift_right(v___y_5005_, v___y_5003_);
v___x_5011_ = lean_uint64_dec_eq(v___x_5010_, v___y_5004_);
if (v___x_5011_ == 0)
{
uint64_t v___x_5012_; 
v___x_5012_ = lean_uint64_add(v___y_5002_, v___y_5003_);
v___y_4989_ = v___y_5001_;
v___y_4990_ = v___y_5004_;
v___y_4991_ = v___y_5007_;
v___y_4992_ = v___y_5006_;
v___y_4993_ = v___y_5009_;
v___y_4994_ = v___y_5008_;
v___y_4995_ = v___x_5012_;
goto v___jp_4988_;
}
else
{
v___y_4989_ = v___y_5001_;
v___y_4990_ = v___y_5004_;
v___y_4991_ = v___y_5007_;
v___y_4992_ = v___y_5006_;
v___y_4993_ = v___y_5009_;
v___y_4994_ = v___y_5008_;
v___y_4995_ = v___y_5002_;
goto v___jp_4988_;
}
}
v___jp_5013_:
{
uint64_t v___x_5021_; uint64_t v___x_5022_; uint8_t v___x_5023_; 
v___x_5021_ = 2ULL;
v___x_5022_ = lean_uint64_shift_right(v___y_5016_, v___x_5021_);
v___x_5023_ = lean_uint64_dec_eq(v___x_5022_, v___y_5015_);
if (v___x_5023_ == 0)
{
v___y_5001_ = v___y_5014_;
v___y_5002_ = v___y_5020_;
v___y_5003_ = v___x_5021_;
v___y_5004_ = v___y_5015_;
v___y_5005_ = v___y_5016_;
v___y_5006_ = v___y_5018_;
v___y_5007_ = v___y_5017_;
v___y_5008_ = v___y_5019_;
v___y_5009_ = v___x_5022_;
goto v___jp_5000_;
}
else
{
v___y_5001_ = v___y_5014_;
v___y_5002_ = v___y_5020_;
v___y_5003_ = v___x_5021_;
v___y_5004_ = v___y_5015_;
v___y_5005_ = v___y_5016_;
v___y_5006_ = v___y_5018_;
v___y_5007_ = v___y_5017_;
v___y_5008_ = v___y_5019_;
v___y_5009_ = v___y_5016_;
goto v___jp_5000_;
}
}
v___jp_5024_:
{
uint64_t v___x_5034_; uint8_t v___x_5035_; 
v___x_5034_ = lean_uint64_shift_right(v___y_5027_, v___y_5031_);
v___x_5035_ = lean_uint64_dec_eq(v___x_5034_, v___y_5026_);
if (v___x_5035_ == 0)
{
uint64_t v___x_5036_; 
v___x_5036_ = lean_uint64_add(v___y_5028_, v___y_5031_);
v___y_5014_ = v___y_5025_;
v___y_5015_ = v___y_5026_;
v___y_5016_ = v___y_5033_;
v___y_5017_ = v___y_5030_;
v___y_5018_ = v___y_5029_;
v___y_5019_ = v___y_5032_;
v___y_5020_ = v___x_5036_;
goto v___jp_5013_;
}
else
{
v___y_5014_ = v___y_5025_;
v___y_5015_ = v___y_5026_;
v___y_5016_ = v___y_5033_;
v___y_5017_ = v___y_5030_;
v___y_5018_ = v___y_5029_;
v___y_5019_ = v___y_5032_;
v___y_5020_ = v___y_5028_;
goto v___jp_5013_;
}
}
v___jp_5037_:
{
uint64_t v___x_5045_; uint64_t v___x_5046_; uint8_t v___x_5047_; 
v___x_5045_ = 4ULL;
v___x_5046_ = lean_uint64_shift_right(v___y_5040_, v___x_5045_);
v___x_5047_ = lean_uint64_dec_eq(v___x_5046_, v___y_5039_);
if (v___x_5047_ == 0)
{
v___y_5025_ = v___y_5038_;
v___y_5026_ = v___y_5039_;
v___y_5027_ = v___y_5040_;
v___y_5028_ = v___y_5044_;
v___y_5029_ = v___y_5042_;
v___y_5030_ = v___y_5041_;
v___y_5031_ = v___x_5045_;
v___y_5032_ = v___y_5043_;
v___y_5033_ = v___x_5046_;
goto v___jp_5024_;
}
else
{
v___y_5025_ = v___y_5038_;
v___y_5026_ = v___y_5039_;
v___y_5027_ = v___y_5040_;
v___y_5028_ = v___y_5044_;
v___y_5029_ = v___y_5042_;
v___y_5030_ = v___y_5041_;
v___y_5031_ = v___x_5045_;
v___y_5032_ = v___y_5043_;
v___y_5033_ = v___y_5040_;
goto v___jp_5024_;
}
}
v___jp_5048_:
{
uint64_t v___x_5058_; uint8_t v___x_5059_; 
v___x_5058_ = lean_uint64_shift_right(v___y_5050_, v___y_5055_);
v___x_5059_ = lean_uint64_dec_eq(v___x_5058_, v___y_5051_);
if (v___x_5059_ == 0)
{
uint64_t v___x_5060_; 
v___x_5060_ = lean_uint64_add(v___y_5052_, v___y_5055_);
v___y_5038_ = v___y_5049_;
v___y_5039_ = v___y_5051_;
v___y_5040_ = v___y_5057_;
v___y_5041_ = v___y_5054_;
v___y_5042_ = v___y_5053_;
v___y_5043_ = v___y_5056_;
v___y_5044_ = v___x_5060_;
goto v___jp_5037_;
}
else
{
v___y_5038_ = v___y_5049_;
v___y_5039_ = v___y_5051_;
v___y_5040_ = v___y_5057_;
v___y_5041_ = v___y_5054_;
v___y_5042_ = v___y_5053_;
v___y_5043_ = v___y_5056_;
v___y_5044_ = v___y_5052_;
goto v___jp_5037_;
}
}
v___jp_5061_:
{
uint64_t v___x_5069_; uint64_t v___x_5070_; uint8_t v___x_5071_; 
v___x_5069_ = 8ULL;
v___x_5070_ = lean_uint64_shift_right(v___y_5063_, v___x_5069_);
v___x_5071_ = lean_uint64_dec_eq(v___x_5070_, v___y_5064_);
if (v___x_5071_ == 0)
{
v___y_5049_ = v___y_5062_;
v___y_5050_ = v___y_5063_;
v___y_5051_ = v___y_5064_;
v___y_5052_ = v___y_5068_;
v___y_5053_ = v___y_5066_;
v___y_5054_ = v___y_5065_;
v___y_5055_ = v___x_5069_;
v___y_5056_ = v___y_5067_;
v___y_5057_ = v___x_5070_;
goto v___jp_5048_;
}
else
{
v___y_5049_ = v___y_5062_;
v___y_5050_ = v___y_5063_;
v___y_5051_ = v___y_5064_;
v___y_5052_ = v___y_5068_;
v___y_5053_ = v___y_5066_;
v___y_5054_ = v___y_5065_;
v___y_5055_ = v___x_5069_;
v___y_5056_ = v___y_5067_;
v___y_5057_ = v___y_5063_;
goto v___jp_5048_;
}
}
v___jp_5072_:
{
uint64_t v___x_5082_; uint8_t v___x_5083_; 
v___x_5082_ = lean_uint64_shift_right(v___y_5073_, v___y_5078_);
v___x_5083_ = lean_uint64_dec_eq(v___x_5082_, v___y_5075_);
if (v___x_5083_ == 0)
{
uint64_t v___x_5084_; 
v___x_5084_ = lean_uint64_add(v___y_5079_, v___y_5078_);
v___y_5062_ = v___y_5074_;
v___y_5063_ = v___y_5081_;
v___y_5064_ = v___y_5075_;
v___y_5065_ = v___y_5077_;
v___y_5066_ = v___y_5076_;
v___y_5067_ = v___y_5080_;
v___y_5068_ = v___x_5084_;
goto v___jp_5061_;
}
else
{
v___y_5062_ = v___y_5074_;
v___y_5063_ = v___y_5081_;
v___y_5064_ = v___y_5075_;
v___y_5065_ = v___y_5077_;
v___y_5066_ = v___y_5076_;
v___y_5067_ = v___y_5080_;
v___y_5068_ = v___y_5079_;
goto v___jp_5061_;
}
}
v___jp_5085_:
{
uint64_t v___x_5093_; uint64_t v___x_5094_; uint8_t v___x_5095_; 
v___x_5093_ = 16ULL;
v___x_5094_ = lean_uint64_shift_right(v___y_5086_, v___x_5093_);
v___x_5095_ = lean_uint64_dec_eq(v___x_5094_, v___y_5088_);
if (v___x_5095_ == 0)
{
v___y_5073_ = v___y_5086_;
v___y_5074_ = v___y_5087_;
v___y_5075_ = v___y_5088_;
v___y_5076_ = v___y_5090_;
v___y_5077_ = v___y_5089_;
v___y_5078_ = v___x_5093_;
v___y_5079_ = v___y_5092_;
v___y_5080_ = v___y_5091_;
v___y_5081_ = v___x_5094_;
goto v___jp_5072_;
}
else
{
v___y_5073_ = v___y_5086_;
v___y_5074_ = v___y_5087_;
v___y_5075_ = v___y_5088_;
v___y_5076_ = v___y_5090_;
v___y_5077_ = v___y_5089_;
v___y_5078_ = v___x_5093_;
v___y_5079_ = v___y_5092_;
v___y_5080_ = v___y_5091_;
v___y_5081_ = v___y_5086_;
goto v___jp_5072_;
}
}
v___jp_5096_:
{
uint64_t v___x_5104_; uint8_t v___x_5105_; 
v___x_5104_ = lean_uint64_shift_right(v___y_5097_, v___y_5101_);
v___x_5105_ = lean_uint64_dec_eq(v___x_5104_, v___y_5098_);
if (v___x_5105_ == 0)
{
v___y_5086_ = v___y_5103_;
v___y_5087_ = v___y_5097_;
v___y_5088_ = v___y_5098_;
v___y_5089_ = v___y_5100_;
v___y_5090_ = v___y_5099_;
v___y_5091_ = v___y_5102_;
v___y_5092_ = v___y_5101_;
goto v___jp_5085_;
}
else
{
v___y_5086_ = v___y_5103_;
v___y_5087_ = v___y_5097_;
v___y_5088_ = v___y_5098_;
v___y_5089_ = v___y_5100_;
v___y_5090_ = v___y_5099_;
v___y_5091_ = v___y_5102_;
v___y_5092_ = v___y_5098_;
goto v___jp_5085_;
}
}
v___jp_5106_:
{
uint64_t v___x_5111_; uint8_t v___x_5112_; 
v___x_5111_ = 0ULL;
v___x_5112_ = lean_uint64_dec_eq(v___y_5107_, v___x_5111_);
if (v___x_5112_ == 0)
{
uint64_t v___x_5113_; uint64_t v___x_5114_; uint8_t v___x_5115_; 
v___x_5113_ = 32ULL;
v___x_5114_ = lean_uint64_shift_right(v___y_5107_, v___x_5113_);
v___x_5115_ = lean_uint64_dec_eq(v___x_5114_, v___x_5111_);
if (v___x_5115_ == 0)
{
v___y_5097_ = v___y_5107_;
v___y_5098_ = v___x_5111_;
v___y_5099_ = v___y_5109_;
v___y_5100_ = v___y_5108_;
v___y_5101_ = v___x_5113_;
v___y_5102_ = v___y_5110_;
v___y_5103_ = v___x_5114_;
goto v___jp_5096_;
}
else
{
v___y_5097_ = v___y_5107_;
v___y_5098_ = v___x_5111_;
v___y_5099_ = v___y_5109_;
v___y_5100_ = v___y_5108_;
v___y_5101_ = v___x_5113_;
v___y_5102_ = v___y_5110_;
v___y_5103_ = v___y_5107_;
goto v___jp_5096_;
}
}
else
{
if (v___y_5109_ == 0)
{
uint32_t v___x_5116_; 
v___x_5116_ = 0;
return v___x_5116_;
}
else
{
uint32_t v___x_5117_; 
v___x_5117_ = 2147483648;
return v___x_5117_;
}
}
}
v___jp_5118_:
{
uint64_t v___x_5125_; uint64_t v___x_5126_; uint64_t v___x_5127_; uint8_t v___x_5128_; 
v___x_5125_ = lean_uint64_mul(v___y_5120_, v___y_5121_);
v___x_5126_ = lean_uint64_add(v___y_5119_, v___y_5124_);
v___x_5127_ = 281474976710656ULL;
v___x_5128_ = lean_uint64_dec_lt(v___x_5125_, v___x_5127_);
if (v___x_5128_ == 0)
{
v___y_5107_ = v___x_5125_;
v___y_5108_ = v___y_5123_;
v___y_5109_ = v___y_5122_;
v___y_5110_ = v___x_5126_;
goto v___jp_5106_;
}
else
{
uint64_t v___x_5129_; uint8_t v___x_5130_; 
v___x_5129_ = 123ULL;
v___x_5130_ = lean_uint64_dec_le(v___x_5126_, v___x_5129_);
if (v___x_5130_ == 0)
{
v___y_5107_ = v___x_5125_;
v___y_5108_ = v___y_5123_;
v___y_5109_ = v___y_5122_;
v___y_5110_ = v___x_5126_;
goto v___jp_5106_;
}
else
{
uint64_t v___x_5131_; uint8_t v___x_5132_; 
v___x_5131_ = 0ULL;
v___x_5132_ = lean_uint64_dec_eq(v___x_5125_, v___x_5131_);
if (v___x_5132_ == 0)
{
uint64_t v___x_5133_; uint64_t v___x_5134_; uint8_t v___x_5135_; 
v___x_5133_ = 149ULL;
v___x_5134_ = lean_uint64_sub(v___x_5133_, v___x_5126_);
v___x_5135_ = lean_uint64_dec_eq(v___x_5134_, v___x_5131_);
if (v___x_5135_ == 0)
{
uint64_t v___x_5136_; uint8_t v___x_5137_; 
v___x_5136_ = 64ULL;
v___x_5137_ = lean_uint64_dec_lt(v___x_5134_, v___x_5136_);
if (v___x_5137_ == 0)
{
uint8_t v___x_5138_; 
v___x_5138_ = lean_uint64_dec_eq(v___x_5134_, v___x_5136_);
if (v___x_5138_ == 0)
{
v___y_4392_ = v___y_5122_;
v___y_4393_ = v___y_5123_;
v___y_4394_ = v___x_5131_;
v___y_4395_ = v___x_5131_;
goto v___jp_4391_;
}
else
{
uint64_t v___x_5139_; uint8_t v___x_5140_; 
v___x_5139_ = 9223372036854775808ULL;
v___x_5140_ = lean_uint64_dec_lt(v___x_5139_, v___x_5125_);
if (v___x_5140_ == 0)
{
v___y_4392_ = v___y_5122_;
v___y_4393_ = v___y_5123_;
v___y_4394_ = v___x_5131_;
v___y_4395_ = v___x_5131_;
goto v___jp_4391_;
}
else
{
uint64_t v___x_5141_; 
v___x_5141_ = 1ULL;
v___y_4392_ = v___y_5122_;
v___y_4393_ = v___y_5123_;
v___y_4394_ = v___x_5131_;
v___y_4395_ = v___x_5141_;
goto v___jp_4391_;
}
}
}
else
{
uint64_t v_quotient_5142_; uint64_t v___x_5143_; uint64_t v___x_5144_; uint64_t v___x_5145_; uint64_t v_remainder_5146_; uint64_t v___x_5147_; uint64_t v_half_5148_; uint8_t v___x_5149_; 
v_quotient_5142_ = lean_uint64_shift_right(v___x_5125_, v___x_5134_);
v___x_5143_ = 1ULL;
v___x_5144_ = lean_uint64_shift_left(v___x_5143_, v___x_5134_);
v___x_5145_ = lean_uint64_sub(v___x_5144_, v___x_5143_);
v_remainder_5146_ = lean_uint64_land(v___x_5125_, v___x_5145_);
v___x_5147_ = lean_uint64_sub(v___x_5134_, v___x_5143_);
v_half_5148_ = lean_uint64_shift_left(v___x_5143_, v___x_5147_);
v___x_5149_ = lean_uint64_dec_lt(v_remainder_5146_, v_half_5148_);
if (v___x_5149_ == 0)
{
uint8_t v___x_5150_; 
v___x_5150_ = lean_uint64_dec_lt(v_half_5148_, v_remainder_5146_);
if (v___x_5150_ == 0)
{
uint64_t v___x_5151_; uint8_t v___x_5152_; 
v___x_5151_ = lean_uint64_land(v_quotient_5142_, v___x_5143_);
v___x_5152_ = lean_uint64_dec_eq(v___x_5151_, v___x_5131_);
if (v___x_5152_ == 0)
{
uint64_t v___x_5153_; 
v___x_5153_ = lean_uint64_add(v_quotient_5142_, v___x_5143_);
v___y_4392_ = v___y_5122_;
v___y_4393_ = v___y_5123_;
v___y_4394_ = v___x_5131_;
v___y_4395_ = v___x_5153_;
goto v___jp_4391_;
}
else
{
v___y_4392_ = v___y_5122_;
v___y_4393_ = v___y_5123_;
v___y_4394_ = v___x_5131_;
v___y_4395_ = v_quotient_5142_;
goto v___jp_4391_;
}
}
else
{
uint64_t v___x_5154_; 
v___x_5154_ = lean_uint64_add(v_quotient_5142_, v___x_5143_);
v___y_4392_ = v___y_5122_;
v___y_4393_ = v___y_5123_;
v___y_4394_ = v___x_5131_;
v___y_4395_ = v___x_5154_;
goto v___jp_4391_;
}
}
else
{
v___y_4392_ = v___y_5122_;
v___y_4393_ = v___y_5123_;
v___y_4394_ = v___x_5131_;
v___y_4395_ = v_quotient_5142_;
goto v___jp_4391_;
}
}
}
else
{
v___y_4392_ = v___y_5122_;
v___y_4393_ = v___y_5123_;
v___y_4394_ = v___x_5131_;
v___y_4395_ = v___x_5125_;
goto v___jp_4391_;
}
}
else
{
if (v___y_5122_ == 0)
{
uint32_t v___x_5155_; 
v___x_5155_ = 0;
return v___x_5155_;
}
else
{
uint32_t v___x_5156_; 
v___x_5156_ = 2147483648;
return v___x_5156_;
}
}
}
}
}
v___jp_5157_:
{
uint32_t v___x_5162_; uint32_t v___x_5163_; uint32_t v___x_5164_; uint32_t v___x_5165_; uint32_t v___x_5166_; 
v___x_5162_ = lean_uint32_land(v___y_5159_, v___x_4592_);
v___x_5163_ = lean_uint32_shift_left(v___x_5162_, v___x_4551_);
v___x_5164_ = lean_uint32_lor(v___y_5161_, v___x_5163_);
v___x_5165_ = lean_uint32_land(v___y_5160_, v___y_5158_);
v___x_5166_ = lean_uint32_lor(v___x_5164_, v___x_5165_);
return v___x_5166_;
}
v___jp_5167_:
{
if (v___y_5169_ == 0)
{
uint32_t v___x_5172_; 
v___x_5172_ = 0;
v___y_5158_ = v___y_5168_;
v___y_5159_ = v___y_5170_;
v___y_5160_ = v___y_5171_;
v___y_5161_ = v___x_5172_;
goto v___jp_5157_;
}
else
{
uint32_t v___x_5173_; 
v___x_5173_ = 2147483648;
v___y_5158_ = v___y_5168_;
v___y_5159_ = v___y_5170_;
v___y_5160_ = v___y_5171_;
v___y_5161_ = v___x_5173_;
goto v___jp_5157_;
}
}
v___jp_5174_:
{
uint64_t v___x_5180_; uint64_t v_encodedExponent_5181_; uint32_t v___x_5182_; uint64_t v___x_5183_; uint8_t v___x_5184_; 
v___x_5180_ = 171ULL;
v_encodedExponent_5181_ = lean_uint64_sub(v___y_5175_, v___x_5180_);
v___x_5182_ = lean_uint64_to_uint32(v_encodedExponent_5181_);
v___x_5183_ = 8388608ULL;
v___x_5184_ = lean_uint64_dec_lt(v___y_5179_, v___x_5183_);
if (v___x_5184_ == 0)
{
uint64_t v___x_5185_; uint32_t v___x_5186_; 
v___x_5185_ = lean_uint64_sub(v___y_5179_, v___x_5183_);
v___x_5186_ = lean_uint64_to_uint32(v___x_5185_);
v___y_5168_ = v___y_5176_;
v___y_5169_ = v___y_5177_;
v___y_5170_ = v___x_5182_;
v___y_5171_ = v___x_5186_;
goto v___jp_5167_;
}
else
{
uint32_t v___x_5187_; 
v___x_5187_ = lean_uint64_to_uint32(v___y_5178_);
v___y_5168_ = v___y_5176_;
v___y_5169_ = v___y_5177_;
v___y_5170_ = v___x_5182_;
v___y_5171_ = v___x_5187_;
goto v___jp_5167_;
}
}
v___jp_5188_:
{
uint64_t v___x_5195_; uint8_t v___x_5196_; 
v___x_5195_ = 425ULL;
v___x_5196_ = lean_uint64_dec_lt(v___x_5195_, v___y_5194_);
if (v___x_5196_ == 0)
{
if (v___y_5193_ == 0)
{
v___y_5175_ = v___y_5194_;
v___y_5176_ = v___y_5190_;
v___y_5177_ = v___y_5191_;
v___y_5178_ = v___y_5192_;
v___y_5179_ = v___y_5189_;
goto v___jp_5174_;
}
else
{
uint64_t v___x_5197_; 
v___x_5197_ = 8388608ULL;
v___y_5175_ = v___y_5194_;
v___y_5176_ = v___y_5190_;
v___y_5177_ = v___y_5191_;
v___y_5178_ = v___y_5192_;
v___y_5179_ = v___x_5197_;
goto v___jp_5174_;
}
}
else
{
if (v___y_5191_ == 0)
{
uint32_t v___x_5198_; 
v___x_5198_ = 2139095040;
return v___x_5198_;
}
else
{
uint32_t v___x_5199_; 
v___x_5199_ = 4286578688;
return v___x_5199_;
}
}
}
v___jp_5200_:
{
uint64_t v___x_5206_; uint8_t v_carry_5207_; 
v___x_5206_ = 16777216ULL;
v_carry_5207_ = lean_uint64_dec_eq(v___y_5205_, v___x_5206_);
if (v_carry_5207_ == 0)
{
v___y_5189_ = v___y_5205_;
v___y_5190_ = v___y_5201_;
v___y_5191_ = v___y_5202_;
v___y_5192_ = v___y_5204_;
v___y_5193_ = v_carry_5207_;
v___y_5194_ = v___y_5203_;
goto v___jp_5188_;
}
else
{
uint64_t v___x_5208_; uint64_t v___x_5209_; 
v___x_5208_ = 1ULL;
v___x_5209_ = lean_uint64_add(v___y_5203_, v___x_5208_);
v___y_5189_ = v___y_5205_;
v___y_5190_ = v___y_5201_;
v___y_5191_ = v___y_5202_;
v___y_5192_ = v___y_5204_;
v___y_5193_ = v_carry_5207_;
v___y_5194_ = v___x_5209_;
goto v___jp_5188_;
}
}
v___jp_5210_:
{
uint64_t v_position_5217_; uint64_t v___x_5218_; uint8_t v___x_5219_; 
v_position_5217_ = lean_uint64_add(v___y_5216_, v___y_5215_);
v___x_5218_ = 172ULL;
v___x_5219_ = lean_uint64_dec_lt(v_position_5217_, v___x_5218_);
if (v___x_5219_ == 0)
{
uint64_t v___x_5220_; uint8_t v___x_5221_; 
v___x_5220_ = 23ULL;
v___x_5221_ = lean_uint64_dec_lt(v___y_5216_, v___x_5220_);
if (v___x_5221_ == 0)
{
uint64_t v___x_5222_; uint8_t v___x_5223_; 
v___x_5222_ = lean_uint64_sub(v___y_5216_, v___x_5220_);
v___x_5223_ = lean_uint64_dec_eq(v___x_5222_, v___y_5214_);
if (v___x_5223_ == 0)
{
uint64_t v___x_5224_; uint8_t v___x_5225_; 
v___x_5224_ = 64ULL;
v___x_5225_ = lean_uint64_dec_lt(v___x_5222_, v___x_5224_);
if (v___x_5225_ == 0)
{
uint8_t v___x_5226_; 
v___x_5226_ = lean_uint64_dec_eq(v___x_5222_, v___x_5224_);
if (v___x_5226_ == 0)
{
v___y_5201_ = v___y_5211_;
v___y_5202_ = v___y_5212_;
v___y_5203_ = v_position_5217_;
v___y_5204_ = v___y_5214_;
v___y_5205_ = v___y_5214_;
goto v___jp_5200_;
}
else
{
uint64_t v___x_5227_; uint8_t v___x_5228_; 
v___x_5227_ = 9223372036854775808ULL;
v___x_5228_ = lean_uint64_dec_lt(v___x_5227_, v___y_5213_);
if (v___x_5228_ == 0)
{
v___y_5201_ = v___y_5211_;
v___y_5202_ = v___y_5212_;
v___y_5203_ = v_position_5217_;
v___y_5204_ = v___y_5214_;
v___y_5205_ = v___y_5214_;
goto v___jp_5200_;
}
else
{
uint64_t v___x_5229_; 
v___x_5229_ = 1ULL;
v___y_5201_ = v___y_5211_;
v___y_5202_ = v___y_5212_;
v___y_5203_ = v_position_5217_;
v___y_5204_ = v___y_5214_;
v___y_5205_ = v___x_5229_;
goto v___jp_5200_;
}
}
}
else
{
uint64_t v_quotient_5230_; uint64_t v___x_5231_; uint64_t v___x_5232_; uint64_t v___x_5233_; uint64_t v_remainder_5234_; uint64_t v___x_5235_; uint64_t v_half_5236_; uint8_t v___x_5237_; 
v_quotient_5230_ = lean_uint64_shift_right(v___y_5213_, v___x_5222_);
v___x_5231_ = 1ULL;
v___x_5232_ = lean_uint64_shift_left(v___x_5231_, v___x_5222_);
v___x_5233_ = lean_uint64_sub(v___x_5232_, v___x_5231_);
v_remainder_5234_ = lean_uint64_land(v___y_5213_, v___x_5233_);
v___x_5235_ = lean_uint64_sub(v___x_5222_, v___x_5231_);
v_half_5236_ = lean_uint64_shift_left(v___x_5231_, v___x_5235_);
v___x_5237_ = lean_uint64_dec_lt(v_remainder_5234_, v_half_5236_);
if (v___x_5237_ == 0)
{
uint8_t v___x_5238_; 
v___x_5238_ = lean_uint64_dec_lt(v_half_5236_, v_remainder_5234_);
if (v___x_5238_ == 0)
{
uint64_t v___x_5239_; uint8_t v___x_5240_; 
v___x_5239_ = lean_uint64_land(v_quotient_5230_, v___x_5231_);
v___x_5240_ = lean_uint64_dec_eq(v___x_5239_, v___y_5214_);
if (v___x_5240_ == 0)
{
uint64_t v___x_5241_; 
v___x_5241_ = lean_uint64_add(v_quotient_5230_, v___x_5231_);
v___y_5201_ = v___y_5211_;
v___y_5202_ = v___y_5212_;
v___y_5203_ = v_position_5217_;
v___y_5204_ = v___y_5214_;
v___y_5205_ = v___x_5241_;
goto v___jp_5200_;
}
else
{
v___y_5201_ = v___y_5211_;
v___y_5202_ = v___y_5212_;
v___y_5203_ = v_position_5217_;
v___y_5204_ = v___y_5214_;
v___y_5205_ = v_quotient_5230_;
goto v___jp_5200_;
}
}
else
{
uint64_t v___x_5242_; 
v___x_5242_ = lean_uint64_add(v_quotient_5230_, v___x_5231_);
v___y_5201_ = v___y_5211_;
v___y_5202_ = v___y_5212_;
v___y_5203_ = v_position_5217_;
v___y_5204_ = v___y_5214_;
v___y_5205_ = v___x_5242_;
goto v___jp_5200_;
}
}
else
{
v___y_5201_ = v___y_5211_;
v___y_5202_ = v___y_5212_;
v___y_5203_ = v_position_5217_;
v___y_5204_ = v___y_5214_;
v___y_5205_ = v_quotient_5230_;
goto v___jp_5200_;
}
}
}
else
{
v___y_5201_ = v___y_5211_;
v___y_5202_ = v___y_5212_;
v___y_5203_ = v_position_5217_;
v___y_5204_ = v___y_5214_;
v___y_5205_ = v___y_5213_;
goto v___jp_5200_;
}
}
else
{
uint64_t v___x_5243_; uint64_t v___x_5244_; 
v___x_5243_ = lean_uint64_sub(v___x_5220_, v___y_5216_);
v___x_5244_ = lean_uint64_shift_left(v___y_5213_, v___x_5243_);
v___y_5201_ = v___y_5211_;
v___y_5202_ = v___y_5212_;
v___y_5203_ = v_position_5217_;
v___y_5204_ = v___y_5214_;
v___y_5205_ = v___x_5244_;
goto v___jp_5200_;
}
}
else
{
uint64_t v___x_5245_; uint8_t v___x_5246_; 
v___x_5245_ = 149ULL;
v___x_5246_ = lean_uint64_dec_lt(v___y_5215_, v___x_5245_);
if (v___x_5246_ == 0)
{
uint64_t v___x_5247_; uint64_t v___x_5248_; 
v___x_5247_ = lean_uint64_sub(v___y_5215_, v___x_5245_);
v___x_5248_ = lean_uint64_shift_left(v___y_5213_, v___x_5247_);
v___y_4516_ = v___y_5211_;
v___y_4517_ = v___y_5212_;
v___y_4518_ = v___y_5214_;
v___y_4519_ = v___x_5248_;
goto v___jp_4515_;
}
else
{
uint64_t v___x_5249_; uint8_t v___x_5250_; 
v___x_5249_ = lean_uint64_sub(v___x_5245_, v___y_5215_);
v___x_5250_ = lean_uint64_dec_eq(v___x_5249_, v___y_5214_);
if (v___x_5250_ == 0)
{
uint64_t v___x_5251_; uint8_t v___x_5252_; 
v___x_5251_ = 64ULL;
v___x_5252_ = lean_uint64_dec_lt(v___x_5249_, v___x_5251_);
if (v___x_5252_ == 0)
{
uint8_t v___x_5253_; 
v___x_5253_ = lean_uint64_dec_eq(v___x_5249_, v___x_5251_);
if (v___x_5253_ == 0)
{
v___y_4516_ = v___y_5211_;
v___y_4517_ = v___y_5212_;
v___y_4518_ = v___y_5214_;
v___y_4519_ = v___y_5214_;
goto v___jp_4515_;
}
else
{
uint64_t v___x_5254_; uint8_t v___x_5255_; 
v___x_5254_ = 9223372036854775808ULL;
v___x_5255_ = lean_uint64_dec_lt(v___x_5254_, v___y_5213_);
if (v___x_5255_ == 0)
{
v___y_4516_ = v___y_5211_;
v___y_4517_ = v___y_5212_;
v___y_4518_ = v___y_5214_;
v___y_4519_ = v___y_5214_;
goto v___jp_4515_;
}
else
{
uint64_t v___x_5256_; 
v___x_5256_ = 1ULL;
v___y_4516_ = v___y_5211_;
v___y_4517_ = v___y_5212_;
v___y_4518_ = v___y_5214_;
v___y_4519_ = v___x_5256_;
goto v___jp_4515_;
}
}
}
else
{
uint64_t v_quotient_5257_; uint64_t v___x_5258_; uint64_t v___x_5259_; uint64_t v___x_5260_; uint64_t v_remainder_5261_; uint64_t v___x_5262_; uint64_t v_half_5263_; uint8_t v___x_5264_; 
v_quotient_5257_ = lean_uint64_shift_right(v___y_5213_, v___x_5249_);
v___x_5258_ = 1ULL;
v___x_5259_ = lean_uint64_shift_left(v___x_5258_, v___x_5249_);
v___x_5260_ = lean_uint64_sub(v___x_5259_, v___x_5258_);
v_remainder_5261_ = lean_uint64_land(v___y_5213_, v___x_5260_);
v___x_5262_ = lean_uint64_sub(v___x_5249_, v___x_5258_);
v_half_5263_ = lean_uint64_shift_left(v___x_5258_, v___x_5262_);
v___x_5264_ = lean_uint64_dec_lt(v_remainder_5261_, v_half_5263_);
if (v___x_5264_ == 0)
{
uint8_t v___x_5265_; 
v___x_5265_ = lean_uint64_dec_lt(v_half_5263_, v_remainder_5261_);
if (v___x_5265_ == 0)
{
uint64_t v___x_5266_; uint8_t v___x_5267_; 
v___x_5266_ = lean_uint64_land(v_quotient_5257_, v___x_5258_);
v___x_5267_ = lean_uint64_dec_eq(v___x_5266_, v___y_5214_);
if (v___x_5267_ == 0)
{
uint64_t v___x_5268_; 
v___x_5268_ = lean_uint64_add(v_quotient_5257_, v___x_5258_);
v___y_4516_ = v___y_5211_;
v___y_4517_ = v___y_5212_;
v___y_4518_ = v___y_5214_;
v___y_4519_ = v___x_5268_;
goto v___jp_4515_;
}
else
{
v___y_4516_ = v___y_5211_;
v___y_4517_ = v___y_5212_;
v___y_4518_ = v___y_5214_;
v___y_4519_ = v_quotient_5257_;
goto v___jp_4515_;
}
}
else
{
uint64_t v___x_5269_; 
v___x_5269_ = lean_uint64_add(v_quotient_5257_, v___x_5258_);
v___y_4516_ = v___y_5211_;
v___y_4517_ = v___y_5212_;
v___y_4518_ = v___y_5214_;
v___y_4519_ = v___x_5269_;
goto v___jp_4515_;
}
}
else
{
v___y_4516_ = v___y_5211_;
v___y_4517_ = v___y_5212_;
v___y_4518_ = v___y_5214_;
v___y_4519_ = v_quotient_5257_;
goto v___jp_4515_;
}
}
}
else
{
v___y_4516_ = v___y_5211_;
v___y_4517_ = v___y_5212_;
v___y_4518_ = v___y_5214_;
v___y_4519_ = v___y_5213_;
goto v___jp_4515_;
}
}
}
}
v___jp_5270_:
{
uint64_t v___x_5278_; uint64_t v___x_5279_; uint8_t v___x_5280_; 
v___x_5278_ = 1ULL;
v___x_5279_ = lean_uint64_shift_right(v___y_5275_, v___x_5278_);
v___x_5280_ = lean_uint64_dec_eq(v___x_5279_, v___y_5274_);
if (v___x_5280_ == 0)
{
uint64_t v___x_5281_; 
v___x_5281_ = lean_uint64_add(v___y_5277_, v___x_5278_);
v___y_5211_ = v___y_5271_;
v___y_5212_ = v___y_5272_;
v___y_5213_ = v___y_5273_;
v___y_5214_ = v___y_5274_;
v___y_5215_ = v___y_5276_;
v___y_5216_ = v___x_5281_;
goto v___jp_5210_;
}
else
{
v___y_5211_ = v___y_5271_;
v___y_5212_ = v___y_5272_;
v___y_5213_ = v___y_5273_;
v___y_5214_ = v___y_5274_;
v___y_5215_ = v___y_5276_;
v___y_5216_ = v___y_5277_;
goto v___jp_5210_;
}
}
v___jp_5282_:
{
uint64_t v___x_5292_; uint8_t v___x_5293_; 
v___x_5292_ = lean_uint64_shift_right(v___y_5290_, v___y_5286_);
v___x_5293_ = lean_uint64_dec_eq(v___x_5292_, v___y_5287_);
if (v___x_5293_ == 0)
{
uint64_t v___x_5294_; 
v___x_5294_ = lean_uint64_add(v___y_5289_, v___y_5286_);
v___y_5271_ = v___y_5283_;
v___y_5272_ = v___y_5284_;
v___y_5273_ = v___y_5285_;
v___y_5274_ = v___y_5287_;
v___y_5275_ = v___y_5291_;
v___y_5276_ = v___y_5288_;
v___y_5277_ = v___x_5294_;
goto v___jp_5270_;
}
else
{
v___y_5271_ = v___y_5283_;
v___y_5272_ = v___y_5284_;
v___y_5273_ = v___y_5285_;
v___y_5274_ = v___y_5287_;
v___y_5275_ = v___y_5291_;
v___y_5276_ = v___y_5288_;
v___y_5277_ = v___y_5289_;
goto v___jp_5270_;
}
}
v___jp_5295_:
{
uint64_t v___x_5303_; uint64_t v___x_5304_; uint8_t v___x_5305_; 
v___x_5303_ = 2ULL;
v___x_5304_ = lean_uint64_shift_right(v___y_5301_, v___x_5303_);
v___x_5305_ = lean_uint64_dec_eq(v___x_5304_, v___y_5299_);
if (v___x_5305_ == 0)
{
v___y_5283_ = v___y_5296_;
v___y_5284_ = v___y_5297_;
v___y_5285_ = v___y_5298_;
v___y_5286_ = v___x_5303_;
v___y_5287_ = v___y_5299_;
v___y_5288_ = v___y_5300_;
v___y_5289_ = v___y_5302_;
v___y_5290_ = v___y_5301_;
v___y_5291_ = v___x_5304_;
goto v___jp_5282_;
}
else
{
v___y_5283_ = v___y_5296_;
v___y_5284_ = v___y_5297_;
v___y_5285_ = v___y_5298_;
v___y_5286_ = v___x_5303_;
v___y_5287_ = v___y_5299_;
v___y_5288_ = v___y_5300_;
v___y_5289_ = v___y_5302_;
v___y_5290_ = v___y_5301_;
v___y_5291_ = v___y_5301_;
goto v___jp_5282_;
}
}
v___jp_5306_:
{
uint64_t v___x_5316_; uint8_t v___x_5317_; 
v___x_5316_ = lean_uint64_shift_right(v___y_5313_, v___y_5308_);
v___x_5317_ = lean_uint64_dec_eq(v___x_5316_, v___y_5311_);
if (v___x_5317_ == 0)
{
uint64_t v___x_5318_; 
v___x_5318_ = lean_uint64_add(v___y_5314_, v___y_5308_);
v___y_5296_ = v___y_5307_;
v___y_5297_ = v___y_5309_;
v___y_5298_ = v___y_5310_;
v___y_5299_ = v___y_5311_;
v___y_5300_ = v___y_5312_;
v___y_5301_ = v___y_5315_;
v___y_5302_ = v___x_5318_;
goto v___jp_5295_;
}
else
{
v___y_5296_ = v___y_5307_;
v___y_5297_ = v___y_5309_;
v___y_5298_ = v___y_5310_;
v___y_5299_ = v___y_5311_;
v___y_5300_ = v___y_5312_;
v___y_5301_ = v___y_5315_;
v___y_5302_ = v___y_5314_;
goto v___jp_5295_;
}
}
v___jp_5319_:
{
uint64_t v___x_5327_; uint64_t v___x_5328_; uint8_t v___x_5329_; 
v___x_5327_ = 4ULL;
v___x_5328_ = lean_uint64_shift_right(v___y_5325_, v___x_5327_);
v___x_5329_ = lean_uint64_dec_eq(v___x_5328_, v___y_5323_);
if (v___x_5329_ == 0)
{
v___y_5307_ = v___y_5320_;
v___y_5308_ = v___x_5327_;
v___y_5309_ = v___y_5321_;
v___y_5310_ = v___y_5322_;
v___y_5311_ = v___y_5323_;
v___y_5312_ = v___y_5324_;
v___y_5313_ = v___y_5325_;
v___y_5314_ = v___y_5326_;
v___y_5315_ = v___x_5328_;
goto v___jp_5306_;
}
else
{
v___y_5307_ = v___y_5320_;
v___y_5308_ = v___x_5327_;
v___y_5309_ = v___y_5321_;
v___y_5310_ = v___y_5322_;
v___y_5311_ = v___y_5323_;
v___y_5312_ = v___y_5324_;
v___y_5313_ = v___y_5325_;
v___y_5314_ = v___y_5326_;
v___y_5315_ = v___y_5325_;
goto v___jp_5306_;
}
}
v___jp_5330_:
{
uint64_t v___x_5340_; uint8_t v___x_5341_; 
v___x_5340_ = lean_uint64_shift_right(v___y_5335_, v___y_5334_);
v___x_5341_ = lean_uint64_dec_eq(v___x_5340_, v___y_5336_);
if (v___x_5341_ == 0)
{
uint64_t v___x_5342_; 
v___x_5342_ = lean_uint64_add(v___y_5338_, v___y_5334_);
v___y_5320_ = v___y_5331_;
v___y_5321_ = v___y_5332_;
v___y_5322_ = v___y_5333_;
v___y_5323_ = v___y_5336_;
v___y_5324_ = v___y_5337_;
v___y_5325_ = v___y_5339_;
v___y_5326_ = v___x_5342_;
goto v___jp_5319_;
}
else
{
v___y_5320_ = v___y_5331_;
v___y_5321_ = v___y_5332_;
v___y_5322_ = v___y_5333_;
v___y_5323_ = v___y_5336_;
v___y_5324_ = v___y_5337_;
v___y_5325_ = v___y_5339_;
v___y_5326_ = v___y_5338_;
goto v___jp_5319_;
}
}
v___jp_5343_:
{
uint64_t v___x_5351_; uint64_t v___x_5352_; uint8_t v___x_5353_; 
v___x_5351_ = 8ULL;
v___x_5352_ = lean_uint64_shift_right(v___y_5347_, v___x_5351_);
v___x_5353_ = lean_uint64_dec_eq(v___x_5352_, v___y_5348_);
if (v___x_5353_ == 0)
{
v___y_5331_ = v___y_5344_;
v___y_5332_ = v___y_5345_;
v___y_5333_ = v___y_5346_;
v___y_5334_ = v___x_5351_;
v___y_5335_ = v___y_5347_;
v___y_5336_ = v___y_5348_;
v___y_5337_ = v___y_5349_;
v___y_5338_ = v___y_5350_;
v___y_5339_ = v___x_5352_;
goto v___jp_5330_;
}
else
{
v___y_5331_ = v___y_5344_;
v___y_5332_ = v___y_5345_;
v___y_5333_ = v___y_5346_;
v___y_5334_ = v___x_5351_;
v___y_5335_ = v___y_5347_;
v___y_5336_ = v___y_5348_;
v___y_5337_ = v___y_5349_;
v___y_5338_ = v___y_5350_;
v___y_5339_ = v___y_5347_;
goto v___jp_5330_;
}
}
v___jp_5354_:
{
uint64_t v___x_5364_; uint8_t v___x_5365_; 
v___x_5364_ = lean_uint64_shift_right(v___y_5360_, v___y_5356_);
v___x_5365_ = lean_uint64_dec_eq(v___x_5364_, v___y_5361_);
if (v___x_5365_ == 0)
{
uint64_t v___x_5366_; 
v___x_5366_ = lean_uint64_add(v___y_5355_, v___y_5356_);
v___y_5344_ = v___y_5357_;
v___y_5345_ = v___y_5358_;
v___y_5346_ = v___y_5359_;
v___y_5347_ = v___y_5363_;
v___y_5348_ = v___y_5361_;
v___y_5349_ = v___y_5362_;
v___y_5350_ = v___x_5366_;
goto v___jp_5343_;
}
else
{
v___y_5344_ = v___y_5357_;
v___y_5345_ = v___y_5358_;
v___y_5346_ = v___y_5359_;
v___y_5347_ = v___y_5363_;
v___y_5348_ = v___y_5361_;
v___y_5349_ = v___y_5362_;
v___y_5350_ = v___y_5355_;
goto v___jp_5343_;
}
}
v___jp_5367_:
{
uint64_t v___x_5375_; uint64_t v___x_5376_; uint8_t v___x_5377_; 
v___x_5375_ = 16ULL;
v___x_5376_ = lean_uint64_shift_right(v___y_5372_, v___x_5375_);
v___x_5377_ = lean_uint64_dec_eq(v___x_5376_, v___y_5371_);
if (v___x_5377_ == 0)
{
v___y_5355_ = v___y_5374_;
v___y_5356_ = v___x_5375_;
v___y_5357_ = v___y_5368_;
v___y_5358_ = v___y_5369_;
v___y_5359_ = v___y_5370_;
v___y_5360_ = v___y_5372_;
v___y_5361_ = v___y_5371_;
v___y_5362_ = v___y_5373_;
v___y_5363_ = v___x_5376_;
goto v___jp_5354_;
}
else
{
v___y_5355_ = v___y_5374_;
v___y_5356_ = v___x_5375_;
v___y_5357_ = v___y_5368_;
v___y_5358_ = v___y_5369_;
v___y_5359_ = v___y_5370_;
v___y_5360_ = v___y_5372_;
v___y_5361_ = v___y_5371_;
v___y_5362_ = v___y_5373_;
v___y_5363_ = v___y_5372_;
goto v___jp_5354_;
}
}
v___jp_5378_:
{
uint64_t v___x_5386_; uint8_t v___x_5387_; 
v___x_5386_ = lean_uint64_shift_right(v___y_5381_, v___y_5384_);
v___x_5387_ = lean_uint64_dec_eq(v___x_5386_, v___y_5382_);
if (v___x_5387_ == 0)
{
v___y_5368_ = v___y_5379_;
v___y_5369_ = v___y_5380_;
v___y_5370_ = v___y_5381_;
v___y_5371_ = v___y_5382_;
v___y_5372_ = v___y_5385_;
v___y_5373_ = v___y_5383_;
v___y_5374_ = v___y_5384_;
goto v___jp_5367_;
}
else
{
v___y_5368_ = v___y_5379_;
v___y_5369_ = v___y_5380_;
v___y_5370_ = v___y_5381_;
v___y_5371_ = v___y_5382_;
v___y_5372_ = v___y_5385_;
v___y_5373_ = v___y_5383_;
v___y_5374_ = v___y_5382_;
goto v___jp_5367_;
}
}
v___jp_5388_:
{
uint64_t v___x_5393_; uint8_t v___x_5394_; 
v___x_5393_ = 0ULL;
v___x_5394_ = lean_uint64_dec_eq(v___y_5391_, v___x_5393_);
if (v___x_5394_ == 0)
{
uint64_t v___x_5395_; uint64_t v___x_5396_; uint8_t v___x_5397_; 
v___x_5395_ = 32ULL;
v___x_5396_ = lean_uint64_shift_right(v___y_5391_, v___x_5395_);
v___x_5397_ = lean_uint64_dec_eq(v___x_5396_, v___x_5393_);
if (v___x_5397_ == 0)
{
v___y_5379_ = v___y_5389_;
v___y_5380_ = v___y_5390_;
v___y_5381_ = v___y_5391_;
v___y_5382_ = v___x_5393_;
v___y_5383_ = v___y_5392_;
v___y_5384_ = v___x_5395_;
v___y_5385_ = v___x_5396_;
goto v___jp_5378_;
}
else
{
v___y_5379_ = v___y_5389_;
v___y_5380_ = v___y_5390_;
v___y_5381_ = v___y_5391_;
v___y_5382_ = v___x_5393_;
v___y_5383_ = v___y_5392_;
v___y_5384_ = v___x_5395_;
v___y_5385_ = v___y_5391_;
goto v___jp_5378_;
}
}
else
{
if (v___y_5390_ == 0)
{
uint32_t v___x_5398_; 
v___x_5398_ = 0;
return v___x_5398_;
}
else
{
uint32_t v___x_5399_; 
v___x_5399_ = 2147483648;
return v___x_5399_;
}
}
}
v___jp_5400_:
{
uint64_t v___x_5407_; uint64_t v___x_5408_; uint64_t v___x_5409_; uint8_t v___x_5410_; 
v___x_5407_ = lean_uint64_mul(v___y_5403_, v___y_5405_);
v___x_5408_ = lean_uint64_add(v___y_5404_, v___y_5406_);
v___x_5409_ = 281474976710656ULL;
v___x_5410_ = lean_uint64_dec_lt(v___x_5407_, v___x_5409_);
if (v___x_5410_ == 0)
{
v___y_5389_ = v___y_5401_;
v___y_5390_ = v___y_5402_;
v___y_5391_ = v___x_5407_;
v___y_5392_ = v___x_5408_;
goto v___jp_5388_;
}
else
{
uint64_t v___x_5411_; uint8_t v___x_5412_; 
v___x_5411_ = 123ULL;
v___x_5412_ = lean_uint64_dec_le(v___x_5408_, v___x_5411_);
if (v___x_5412_ == 0)
{
v___y_5389_ = v___y_5401_;
v___y_5390_ = v___y_5402_;
v___y_5391_ = v___x_5407_;
v___y_5392_ = v___x_5408_;
goto v___jp_5388_;
}
else
{
uint64_t v___x_5413_; uint8_t v___x_5414_; 
v___x_5413_ = 0ULL;
v___x_5414_ = lean_uint64_dec_eq(v___x_5407_, v___x_5413_);
if (v___x_5414_ == 0)
{
uint64_t v___x_5415_; uint64_t v___x_5416_; uint8_t v___x_5417_; 
v___x_5415_ = 149ULL;
v___x_5416_ = lean_uint64_sub(v___x_5415_, v___x_5408_);
v___x_5417_ = lean_uint64_dec_eq(v___x_5416_, v___x_5413_);
if (v___x_5417_ == 0)
{
uint64_t v___x_5418_; uint8_t v___x_5419_; 
v___x_5418_ = 64ULL;
v___x_5419_ = lean_uint64_dec_lt(v___x_5416_, v___x_5418_);
if (v___x_5419_ == 0)
{
uint8_t v___x_5420_; 
v___x_5420_ = lean_uint64_dec_eq(v___x_5416_, v___x_5418_);
if (v___x_5420_ == 0)
{
v___y_4537_ = v___y_5401_;
v___y_4538_ = v___y_5402_;
v___y_4539_ = v___x_5413_;
v___y_4540_ = v___x_5413_;
goto v___jp_4536_;
}
else
{
uint64_t v___x_5421_; uint8_t v___x_5422_; 
v___x_5421_ = 9223372036854775808ULL;
v___x_5422_ = lean_uint64_dec_lt(v___x_5421_, v___x_5407_);
if (v___x_5422_ == 0)
{
v___y_4537_ = v___y_5401_;
v___y_4538_ = v___y_5402_;
v___y_4539_ = v___x_5413_;
v___y_4540_ = v___x_5413_;
goto v___jp_4536_;
}
else
{
uint64_t v___x_5423_; 
v___x_5423_ = 1ULL;
v___y_4537_ = v___y_5401_;
v___y_4538_ = v___y_5402_;
v___y_4539_ = v___x_5413_;
v___y_4540_ = v___x_5423_;
goto v___jp_4536_;
}
}
}
else
{
uint64_t v_quotient_5424_; uint64_t v___x_5425_; uint64_t v___x_5426_; uint64_t v___x_5427_; uint64_t v_remainder_5428_; uint64_t v___x_5429_; uint64_t v_half_5430_; uint8_t v___x_5431_; 
v_quotient_5424_ = lean_uint64_shift_right(v___x_5407_, v___x_5416_);
v___x_5425_ = 1ULL;
v___x_5426_ = lean_uint64_shift_left(v___x_5425_, v___x_5416_);
v___x_5427_ = lean_uint64_sub(v___x_5426_, v___x_5425_);
v_remainder_5428_ = lean_uint64_land(v___x_5407_, v___x_5427_);
v___x_5429_ = lean_uint64_sub(v___x_5416_, v___x_5425_);
v_half_5430_ = lean_uint64_shift_left(v___x_5425_, v___x_5429_);
v___x_5431_ = lean_uint64_dec_lt(v_remainder_5428_, v_half_5430_);
if (v___x_5431_ == 0)
{
uint8_t v___x_5432_; 
v___x_5432_ = lean_uint64_dec_lt(v_half_5430_, v_remainder_5428_);
if (v___x_5432_ == 0)
{
uint64_t v___x_5433_; uint8_t v___x_5434_; 
v___x_5433_ = lean_uint64_land(v_quotient_5424_, v___x_5425_);
v___x_5434_ = lean_uint64_dec_eq(v___x_5433_, v___x_5413_);
if (v___x_5434_ == 0)
{
uint64_t v___x_5435_; 
v___x_5435_ = lean_uint64_add(v_quotient_5424_, v___x_5425_);
v___y_4537_ = v___y_5401_;
v___y_4538_ = v___y_5402_;
v___y_4539_ = v___x_5413_;
v___y_4540_ = v___x_5435_;
goto v___jp_4536_;
}
else
{
v___y_4537_ = v___y_5401_;
v___y_4538_ = v___y_5402_;
v___y_4539_ = v___x_5413_;
v___y_4540_ = v_quotient_5424_;
goto v___jp_4536_;
}
}
else
{
uint64_t v___x_5436_; 
v___x_5436_ = lean_uint64_add(v_quotient_5424_, v___x_5425_);
v___y_4537_ = v___y_5401_;
v___y_4538_ = v___y_5402_;
v___y_4539_ = v___x_5413_;
v___y_4540_ = v___x_5436_;
goto v___jp_4536_;
}
}
else
{
v___y_4537_ = v___y_5401_;
v___y_4538_ = v___y_5402_;
v___y_4539_ = v___x_5413_;
v___y_4540_ = v_quotient_5424_;
goto v___jp_4536_;
}
}
}
else
{
v___y_4537_ = v___y_5401_;
v___y_4538_ = v___y_5402_;
v___y_4539_ = v___x_5413_;
v___y_4540_ = v___x_5407_;
goto v___jp_4536_;
}
}
else
{
if (v___y_5402_ == 0)
{
uint32_t v___x_5437_; 
v___x_5437_ = 0;
return v___x_5437_;
}
else
{
uint32_t v___x_5438_; 
v___x_5438_ = 2147483648;
return v___x_5438_;
}
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_r22CostNativeProductMul___boxed(lean_object* v_x_5724_, lean_object* v_y_5725_){
_start:
{
uint32_t v_x_boxed_5726_; uint32_t v_y_boxed_5727_; uint32_t v_res_5728_; lean_object* v_r_5729_; 
v_x_boxed_5726_ = lean_unbox_uint32(v_x_5724_);
lean_dec(v_x_5724_);
v_y_boxed_5727_ = lean_unbox_uint32(v_y_5725_);
lean_dec(v_y_5725_);
v_res_5728_ = lp_competition_r22CostNativeProductMul(v_x_boxed_5726_, v_y_boxed_5727_);
v_r_5729_ = lean_box_uint32(v_res_5728_);
return v_r_5729_;
}
}
LEAN_EXPORT uint32_t lp_competition_runNativeProduct___lam__1(uint32_t v___y_5730_, uint32_t v___y_5731_){
_start:
{
uint8_t v___y_5733_; uint8_t v___y_5749_; uint8_t v___y_5763_; uint8_t v___y_5780_; float v___y_5787_; float v___y_5788_; float v___y_5802_; uint8_t v___y_5803_; float v___y_5818_; uint32_t v___y_5828_; uint32_t v___y_5832_; uint32_t v___y_5836_; uint32_t v___y_5837_; uint32_t v___y_5838_; uint32_t v___y_5842_; uint64_t v___y_5843_; uint8_t v___y_5844_; uint64_t v___y_5845_; uint32_t v___y_5857_; uint32_t v___y_5858_; uint32_t v___y_5859_; uint32_t v___y_5863_; uint64_t v___y_5864_; uint8_t v___y_5865_; uint64_t v___y_5866_; uint8_t v___y_5878_; uint8_t v___y_5894_; uint8_t v___y_5908_; uint8_t v___y_5925_; float v___y_5932_; float v___y_5933_; float v___y_5947_; uint8_t v___y_5948_; float v___y_5963_; uint32_t v___y_5973_; uint32_t v___y_5977_; uint32_t v___y_5981_; uint32_t v___y_5982_; uint32_t v___y_5983_; uint32_t v___y_5987_; uint64_t v___y_5988_; uint8_t v___y_5989_; uint64_t v___y_5990_; uint32_t v___y_6002_; uint32_t v___y_6003_; uint32_t v___y_6004_; uint32_t v___y_6008_; uint8_t v___y_6009_; uint64_t v___y_6010_; uint64_t v___y_6011_; uint8_t v___y_6023_; uint8_t v___y_6039_; uint8_t v___y_6053_; uint8_t v___y_6070_; float v___y_6077_; float v___y_6078_; float v___y_6092_; uint8_t v___y_6093_; float v___y_6108_; uint32_t v___y_6118_; uint32_t v___y_6122_; uint32_t v___y_6126_; uint32_t v___y_6127_; uint32_t v___y_6128_; uint32_t v___y_6132_; uint64_t v___y_6133_; uint8_t v___y_6134_; uint64_t v___y_6135_; uint32_t v___y_6147_; uint32_t v___y_6148_; uint32_t v___y_6149_; uint32_t v___y_6153_; uint64_t v___y_6154_; uint8_t v___y_6155_; uint64_t v___y_6156_; uint32_t v___x_6167_; uint32_t v___x_6168_; uint8_t v___y_6170_; uint8_t v___y_6183_; uint8_t v___y_6196_; uint32_t v___x_6208_; uint32_t v___y_6210_; uint32_t v___y_6211_; uint32_t v___y_6212_; uint32_t v___y_6213_; uint32_t v___y_6220_; uint32_t v___y_6221_; uint8_t v___y_6222_; uint32_t v___y_6223_; uint32_t v___y_6227_; uint64_t v___y_6228_; uint64_t v___y_6229_; uint8_t v___y_6230_; uint64_t v___y_6231_; uint32_t v___y_6241_; uint64_t v___y_6242_; uint64_t v___y_6243_; uint8_t v___y_6244_; uint8_t v___y_6245_; uint64_t v___y_6246_; uint32_t v___y_6253_; uint64_t v___y_6254_; uint64_t v___y_6255_; uint8_t v___y_6256_; uint64_t v___y_6257_; uint64_t v___y_6263_; uint32_t v___y_6264_; uint64_t v___y_6265_; uint64_t v___y_6266_; uint8_t v___y_6267_; uint64_t v___y_6268_; uint64_t v___y_6323_; uint32_t v___y_6324_; uint64_t v___y_6325_; uint64_t v___y_6326_; uint64_t v___y_6327_; uint8_t v___y_6328_; uint64_t v___y_6329_; uint64_t v___y_6335_; uint32_t v___y_6336_; uint64_t v___y_6337_; uint64_t v___y_6338_; uint64_t v___y_6339_; uint64_t v___y_6340_; uint64_t v___y_6341_; uint8_t v___y_6342_; uint64_t v___y_6343_; uint64_t v___y_6348_; uint32_t v___y_6349_; uint64_t v___y_6350_; uint64_t v___y_6351_; uint64_t v___y_6352_; uint8_t v___y_6353_; uint64_t v___y_6354_; uint64_t v___y_6359_; uint64_t v___y_6360_; uint32_t v___y_6361_; uint64_t v___y_6362_; uint64_t v___y_6363_; uint64_t v___y_6364_; uint64_t v___y_6365_; uint8_t v___y_6366_; uint64_t v___y_6367_; uint64_t v___y_6372_; uint64_t v___y_6373_; uint32_t v___y_6374_; uint64_t v___y_6375_; uint64_t v___y_6376_; uint8_t v___y_6377_; uint64_t v___y_6378_; uint64_t v___y_6383_; uint32_t v___y_6384_; uint64_t v___y_6385_; uint64_t v___y_6386_; uint64_t v___y_6387_; uint64_t v___y_6388_; uint8_t v___y_6389_; uint64_t v___y_6390_; uint64_t v___y_6391_; uint64_t v___y_6396_; uint32_t v___y_6397_; uint64_t v___y_6398_; uint64_t v___y_6399_; uint64_t v___y_6400_; uint8_t v___y_6401_; uint64_t v___y_6402_; uint64_t v___y_6407_; uint32_t v___y_6408_; uint64_t v___y_6409_; uint64_t v___y_6410_; uint64_t v___y_6411_; uint64_t v___y_6412_; uint64_t v___y_6413_; uint8_t v___y_6414_; uint64_t v___y_6415_; uint64_t v___y_6420_; uint32_t v___y_6421_; uint64_t v___y_6422_; uint64_t v___y_6423_; uint64_t v___y_6424_; uint8_t v___y_6425_; uint64_t v___y_6426_; uint64_t v___y_6431_; uint32_t v___y_6432_; uint64_t v___y_6433_; uint64_t v___y_6434_; uint64_t v___y_6435_; uint8_t v___y_6436_; uint64_t v___y_6437_; uint64_t v___y_6441_; uint32_t v___y_6442_; uint64_t v___y_6443_; uint8_t v___y_6444_; uint32_t v___y_6453_; uint64_t v___y_6454_; uint64_t v___y_6455_; uint8_t v___y_6456_; uint64_t v___y_6457_; uint64_t v___y_6458_; uint32_t v___y_6492_; uint32_t v___y_6493_; uint32_t v___y_6494_; uint32_t v___y_6495_; uint32_t v___y_6502_; uint32_t v___y_6503_; uint8_t v___y_6504_; uint32_t v___y_6505_; uint32_t v___y_6509_; uint64_t v___y_6510_; uint8_t v___y_6511_; uint64_t v___y_6512_; uint64_t v___y_6513_; uint32_t v___y_6523_; uint64_t v___y_6524_; uint64_t v___y_6525_; uint8_t v___y_6526_; uint8_t v___y_6527_; uint64_t v___y_6528_; uint64_t v___y_6535_; uint32_t v___y_6536_; uint64_t v___y_6537_; uint8_t v___y_6538_; uint64_t v___y_6539_; uint32_t v___y_6545_; uint64_t v___y_6546_; uint64_t v___y_6547_; uint8_t v___y_6548_; uint64_t v___y_6549_; uint64_t v___y_6550_; uint32_t v___y_6605_; uint64_t v___y_6606_; uint64_t v___y_6607_; uint8_t v___y_6608_; uint64_t v___y_6609_; uint64_t v___y_6610_; uint64_t v___y_6611_; uint32_t v___y_6617_; uint64_t v___y_6618_; uint64_t v___y_6619_; uint64_t v___y_6620_; uint64_t v___y_6621_; uint8_t v___y_6622_; uint64_t v___y_6623_; uint64_t v___y_6624_; uint64_t v___y_6625_; uint32_t v___y_6630_; uint64_t v___y_6631_; uint64_t v___y_6632_; uint8_t v___y_6633_; uint64_t v___y_6634_; uint64_t v___y_6635_; uint64_t v___y_6636_; uint32_t v___y_6641_; uint64_t v___y_6642_; uint64_t v___y_6643_; uint64_t v___y_6644_; uint64_t v___y_6645_; uint8_t v___y_6646_; uint64_t v___y_6647_; uint64_t v___y_6648_; uint64_t v___y_6649_; uint32_t v___y_6654_; uint64_t v___y_6655_; uint64_t v___y_6656_; uint8_t v___y_6657_; uint64_t v___y_6658_; uint64_t v___y_6659_; uint64_t v___y_6660_; uint32_t v___y_6665_; uint64_t v___y_6666_; uint64_t v___y_6667_; uint64_t v___y_6668_; uint64_t v___y_6669_; uint8_t v___y_6670_; uint64_t v___y_6671_; uint64_t v___y_6672_; uint64_t v___y_6673_; uint32_t v___y_6678_; uint64_t v___y_6679_; uint64_t v___y_6680_; uint64_t v___y_6681_; uint8_t v___y_6682_; uint64_t v___y_6683_; uint64_t v___y_6684_; uint64_t v___y_6689_; uint32_t v___y_6690_; uint64_t v___y_6691_; uint64_t v___y_6692_; uint64_t v___y_6693_; uint64_t v___y_6694_; uint8_t v___y_6695_; uint64_t v___y_6696_; uint64_t v___y_6697_; uint64_t v___y_6702_; uint32_t v___y_6703_; uint64_t v___y_6704_; uint64_t v___y_6705_; uint8_t v___y_6706_; uint64_t v___y_6707_; uint64_t v___y_6708_; uint32_t v___y_6713_; uint64_t v___y_6714_; uint64_t v___y_6715_; uint64_t v___y_6716_; uint8_t v___y_6717_; uint64_t v___y_6718_; uint64_t v___y_6719_; uint32_t v___y_6723_; uint64_t v___y_6724_; uint8_t v___y_6725_; uint64_t v___y_6726_; uint32_t v___y_6735_; uint64_t v___y_6736_; uint64_t v___y_6737_; uint64_t v___y_6738_; uint8_t v___y_6739_; uint64_t v___y_6740_; uint32_t v___y_6774_; uint32_t v___y_6775_; uint32_t v___y_6776_; uint32_t v___y_6777_; uint32_t v___y_6784_; uint32_t v___y_6785_; uint8_t v___y_6786_; uint32_t v___y_6787_; uint32_t v___y_6791_; uint64_t v___y_6792_; uint64_t v___y_6793_; uint8_t v___y_6794_; uint64_t v___y_6795_; uint32_t v___y_6805_; uint64_t v___y_6806_; uint64_t v___y_6807_; uint8_t v___y_6808_; uint8_t v___y_6809_; uint64_t v___y_6810_; uint32_t v___y_6817_; uint64_t v___y_6818_; uint8_t v___y_6819_; uint64_t v___y_6820_; uint64_t v___y_6821_; uint32_t v___y_6827_; uint64_t v___y_6828_; uint64_t v___y_6829_; uint64_t v___y_6830_; uint8_t v___y_6831_; uint64_t v___y_6832_; uint32_t v___y_6887_; uint64_t v___y_6888_; uint64_t v___y_6889_; uint64_t v___y_6890_; uint64_t v___y_6891_; uint8_t v___y_6892_; uint64_t v___y_6893_; uint64_t v___y_6899_; uint32_t v___y_6900_; uint64_t v___y_6901_; uint64_t v___y_6902_; uint64_t v___y_6903_; uint64_t v___y_6904_; uint64_t v___y_6905_; uint8_t v___y_6906_; uint64_t v___y_6907_; uint32_t v___y_6912_; uint64_t v___y_6913_; uint64_t v___y_6914_; uint64_t v___y_6915_; uint64_t v___y_6916_; uint8_t v___y_6917_; uint64_t v___y_6918_; uint64_t v___y_6923_; uint32_t v___y_6924_; uint64_t v___y_6925_; uint64_t v___y_6926_; uint64_t v___y_6927_; uint64_t v___y_6928_; uint8_t v___y_6929_; uint64_t v___y_6930_; uint64_t v___y_6931_; uint32_t v___y_6936_; uint64_t v___y_6937_; uint64_t v___y_6938_; uint64_t v___y_6939_; uint8_t v___y_6940_; uint64_t v___y_6941_; uint64_t v___y_6942_; uint64_t v___y_6947_; uint32_t v___y_6948_; uint64_t v___y_6949_; uint64_t v___y_6950_; uint64_t v___y_6951_; uint64_t v___y_6952_; uint8_t v___y_6953_; uint64_t v___y_6954_; uint64_t v___y_6955_; uint64_t v___y_6960_; uint32_t v___y_6961_; uint64_t v___y_6962_; uint64_t v___y_6963_; uint64_t v___y_6964_; uint8_t v___y_6965_; uint64_t v___y_6966_; uint32_t v___y_6971_; uint64_t v___y_6972_; uint64_t v___y_6973_; uint64_t v___y_6974_; uint64_t v___y_6975_; uint64_t v___y_6976_; uint64_t v___y_6977_; uint8_t v___y_6978_; uint64_t v___y_6979_; uint32_t v___y_6984_; uint64_t v___y_6985_; uint64_t v___y_6986_; uint64_t v___y_6987_; uint8_t v___y_6988_; uint64_t v___y_6989_; uint64_t v___y_6990_; uint32_t v___y_6995_; uint64_t v___y_6996_; uint64_t v___y_6997_; uint64_t v___y_6998_; uint8_t v___y_6999_; uint64_t v___y_7000_; uint64_t v___y_7001_; uint32_t v___y_7005_; uint64_t v___y_7006_; uint64_t v___y_7007_; uint8_t v___y_7008_; uint32_t v___y_7017_; uint64_t v___y_7018_; uint64_t v___y_7019_; uint8_t v___y_7020_; uint64_t v___y_7021_; uint64_t v___y_7022_; uint32_t v_eu_7055_; uint32_t v___x_7056_; uint32_t v___x_7057_; uint32_t v___x_7058_; uint8_t v___x_7059_; 
v___x_6167_ = 23;
v___x_6168_ = lean_uint32_shift_right(v___y_5730_, v___x_6167_);
v___x_6208_ = 255;
v_eu_7055_ = lean_uint32_land(v___x_6168_, v___x_6208_);
v___x_7056_ = 1;
v___x_7057_ = lean_uint32_sub(v_eu_7055_, v___x_7056_);
v___x_7058_ = 253;
v___x_7059_ = lean_uint32_dec_le(v___x_7057_, v___x_7058_);
if (v___x_7059_ == 0)
{
uint32_t v___x_7060_; uint32_t v_ey_7061_; uint32_t v___y_7063_; uint64_t v___y_7064_; uint8_t v___y_7065_; uint64_t v___y_7066_; uint64_t v___y_7067_; uint32_t v___y_7074_; uint64_t v___y_7075_; uint8_t v___y_7076_; uint64_t v___y_7077_; uint32_t v___y_7084_; uint32_t v___y_7085_; uint8_t v___y_7086_; uint64_t v___y_7087_; uint8_t v___y_7095_; uint32_t v___x_7105_; uint32_t v___x_7106_; uint8_t v___x_7107_; uint8_t v___y_7109_; uint8_t v___y_7110_; uint8_t v___y_7111_; uint8_t v___y_7113_; uint8_t v___y_7114_; uint8_t v___y_7120_; 
v___x_7060_ = lean_uint32_shift_right(v___y_5731_, v___x_6167_);
v_ey_7061_ = lean_uint32_land(v___x_7060_, v___x_6208_);
v___x_7105_ = lean_uint32_add(v_eu_7055_, v_ey_7061_);
v___x_7106_ = 128;
v___x_7107_ = lean_uint32_dec_lt(v___x_7105_, v___x_7106_);
if (v___x_7107_ == 0)
{
uint32_t v___x_7129_; uint32_t v_a_7130_; uint32_t v___x_7131_; uint32_t v___x_7132_; uint8_t v___x_7133_; 
v___x_7129_ = 2147483647;
v_a_7130_ = lean_uint32_land(v___y_5730_, v___x_7129_);
v___x_7131_ = 201326591;
v___x_7132_ = lean_uint32_sub(v_a_7130_, v___x_7056_);
v___x_7133_ = lean_uint32_dec_le(v___x_7131_, v___x_7132_);
if (v___x_7133_ == 0)
{
v___y_6170_ = v___x_7133_;
goto v___jp_6169_;
}
else
{
uint32_t v___x_7134_; uint8_t v___x_7135_; 
v___x_7134_ = 2139095040;
v___x_7135_ = lean_uint32_dec_lt(v_a_7130_, v___x_7134_);
v___y_6170_ = v___x_7135_;
goto v___jp_6169_;
}
}
else
{
uint32_t v___x_7136_; uint32_t v___x_7137_; uint8_t v___x_7138_; 
v___x_7136_ = 4278190080;
v___x_7137_ = lean_uint32_shift_left(v___y_5730_, v___x_7056_);
v___x_7138_ = lean_uint32_dec_le(v___x_7136_, v___x_7137_);
if (v___x_7138_ == 0)
{
uint32_t v___x_7139_; uint8_t v___x_7140_; 
v___x_7139_ = lean_uint32_shift_left(v___y_5731_, v___x_7056_);
v___x_7140_ = lean_uint32_dec_le(v___x_7136_, v___x_7139_);
v___y_7120_ = v___x_7140_;
goto v___jp_7119_;
}
else
{
v___y_7120_ = v___x_7138_;
goto v___jp_7119_;
}
}
v___jp_7062_:
{
uint64_t v___x_7068_; uint64_t v___x_7069_; uint8_t v___x_7070_; 
v___x_7068_ = lean_uint32_to_uint64(v_ey_7061_);
v___x_7069_ = 0ULL;
v___x_7070_ = lean_uint64_dec_eq(v___x_7068_, v___x_7069_);
if (v___x_7070_ == 0)
{
uint64_t v___x_7071_; uint64_t v___x_7072_; 
v___x_7071_ = 1ULL;
v___x_7072_ = lean_uint64_sub(v___x_7068_, v___x_7071_);
v___y_6453_ = v___y_7063_;
v___y_6454_ = v___y_7067_;
v___y_6455_ = v___y_7064_;
v___y_6456_ = v___y_7065_;
v___y_6457_ = v___y_7066_;
v___y_6458_ = v___x_7072_;
goto v___jp_6452_;
}
else
{
v___y_6453_ = v___y_7063_;
v___y_6454_ = v___y_7067_;
v___y_6455_ = v___y_7064_;
v___y_6456_ = v___y_7065_;
v___y_6457_ = v___y_7066_;
v___y_6458_ = v___x_7069_;
goto v___jp_6452_;
}
}
v___jp_7073_:
{
uint64_t v___x_7078_; uint64_t v___x_7079_; uint8_t v___x_7080_; 
v___x_7078_ = lean_uint32_to_uint64(v_eu_7055_);
v___x_7079_ = 0ULL;
v___x_7080_ = lean_uint64_dec_eq(v___x_7078_, v___x_7079_);
if (v___x_7080_ == 0)
{
uint64_t v___x_7081_; uint64_t v___x_7082_; 
v___x_7081_ = 1ULL;
v___x_7082_ = lean_uint64_sub(v___x_7078_, v___x_7081_);
v___y_7063_ = v___y_7074_;
v___y_7064_ = v___y_7075_;
v___y_7065_ = v___y_7076_;
v___y_7066_ = v___y_7077_;
v___y_7067_ = v___x_7082_;
goto v___jp_7062_;
}
else
{
v___y_7063_ = v___y_7074_;
v___y_7064_ = v___y_7075_;
v___y_7065_ = v___y_7076_;
v___y_7066_ = v___y_7077_;
v___y_7067_ = v___x_7079_;
goto v___jp_7062_;
}
}
v___jp_7083_:
{
uint32_t v___x_7088_; uint8_t v___x_7089_; 
v___x_7088_ = 0;
v___x_7089_ = lean_uint32_dec_eq(v_ey_7061_, v___x_7088_);
if (v___x_7089_ == 0)
{
uint64_t v___x_7090_; uint64_t v___x_7091_; uint64_t v___x_7092_; 
v___x_7090_ = lean_uint32_to_uint64(v___y_7085_);
v___x_7091_ = 8388608ULL;
v___x_7092_ = lean_uint64_lor(v___x_7090_, v___x_7091_);
v___y_7074_ = v___y_7084_;
v___y_7075_ = v___y_7087_;
v___y_7076_ = v___y_7086_;
v___y_7077_ = v___x_7092_;
goto v___jp_7073_;
}
else
{
uint64_t v___x_7093_; 
v___x_7093_ = lean_uint32_to_uint64(v___y_7085_);
v___y_7074_ = v___y_7084_;
v___y_7075_ = v___y_7087_;
v___y_7076_ = v___y_7086_;
v___y_7077_ = v___x_7093_;
goto v___jp_7073_;
}
}
v___jp_7094_:
{
uint32_t v___x_7096_; uint32_t v_xFraction_7097_; uint32_t v_yFraction_7098_; uint32_t v___x_7099_; uint8_t v___x_7100_; 
v___x_7096_ = 8388607;
v_xFraction_7097_ = lean_uint32_land(v___y_5730_, v___x_7096_);
v_yFraction_7098_ = lean_uint32_land(v___y_5731_, v___x_7096_);
v___x_7099_ = 0;
v___x_7100_ = lean_uint32_dec_eq(v_eu_7055_, v___x_7099_);
if (v___x_7100_ == 0)
{
uint64_t v___x_7101_; uint64_t v___x_7102_; uint64_t v___x_7103_; 
v___x_7101_ = lean_uint32_to_uint64(v_xFraction_7097_);
v___x_7102_ = 8388608ULL;
v___x_7103_ = lean_uint64_lor(v___x_7101_, v___x_7102_);
v___y_7084_ = v___x_7096_;
v___y_7085_ = v_yFraction_7098_;
v___y_7086_ = v___y_7095_;
v___y_7087_ = v___x_7103_;
goto v___jp_7083_;
}
else
{
uint64_t v___x_7104_; 
v___x_7104_ = lean_uint32_to_uint64(v_xFraction_7097_);
v___y_7084_ = v___x_7096_;
v___y_7085_ = v_yFraction_7098_;
v___y_7086_ = v___y_7095_;
v___y_7087_ = v___x_7104_;
goto v___jp_7083_;
}
}
v___jp_7108_:
{
if (v___y_7110_ == 0)
{
if (v___y_7111_ == 0)
{
v___y_7095_ = v___y_7109_;
goto v___jp_7094_;
}
else
{
v___y_7095_ = v___x_7107_;
goto v___jp_7094_;
}
}
else
{
if (v___y_7111_ == 0)
{
v___y_7095_ = v___x_7107_;
goto v___jp_7094_;
}
else
{
v___y_7095_ = v___y_7109_;
goto v___jp_7094_;
}
}
}
v___jp_7112_:
{
uint32_t v___x_7115_; uint32_t v___x_7116_; uint32_t v___x_7117_; uint8_t v___x_7118_; 
v___x_7115_ = 2147483648;
v___x_7116_ = lean_uint32_land(v___y_5731_, v___x_7115_);
v___x_7117_ = 0;
v___x_7118_ = lean_uint32_dec_eq(v___x_7116_, v___x_7117_);
if (v___x_7118_ == 0)
{
v___y_7109_ = v___y_7113_;
v___y_7110_ = v___y_7114_;
v___y_7111_ = v___x_7107_;
goto v___jp_7108_;
}
else
{
v___y_7109_ = v___y_7113_;
v___y_7110_ = v___y_7114_;
v___y_7111_ = v___y_7113_;
goto v___jp_7108_;
}
}
v___jp_7119_:
{
if (v___y_7120_ == 0)
{
uint32_t v___x_7121_; uint32_t v___x_7122_; uint32_t v___x_7123_; uint8_t v___x_7124_; 
v___x_7121_ = 2147483648;
v___x_7122_ = lean_uint32_land(v___y_5730_, v___x_7121_);
v___x_7123_ = 0;
v___x_7124_ = lean_uint32_dec_eq(v___x_7122_, v___x_7123_);
if (v___x_7124_ == 0)
{
v___y_7113_ = v___y_7120_;
v___y_7114_ = v___x_7107_;
goto v___jp_7112_;
}
else
{
v___y_7113_ = v___y_7120_;
v___y_7114_ = v___y_7120_;
goto v___jp_7112_;
}
}
else
{
lean_object* v___x_7125_; lean_object* v___x_7126_; lean_object* v___x_7127_; uint32_t v___x_7128_; 
v___x_7125_ = lean_uint32_to_nat(v___y_5730_);
v___x_7126_ = lean_uint32_to_nat(v___y_5731_);
v___x_7127_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_7125_, v___x_7126_);
v___x_7128_ = lean_uint32_of_nat(v___x_7127_);
lean_dec(v___x_7127_);
return v___x_7128_;
}
}
}
else
{
uint32_t v___x_7141_; uint32_t v_ev_7142_; uint32_t v___y_7144_; uint64_t v___y_7145_; uint64_t v___y_7146_; uint8_t v___y_7147_; uint64_t v___y_7148_; uint32_t v___y_7155_; uint64_t v___y_7156_; uint8_t v___y_7157_; uint64_t v___y_7158_; uint32_t v___y_7165_; uint32_t v___y_7166_; uint8_t v___y_7167_; uint64_t v___y_7168_; uint8_t v___y_7176_; uint8_t v___y_7187_; uint8_t v___y_7188_; uint8_t v___y_7190_; uint8_t v___y_7191_; uint8_t v___y_7192_; uint8_t v___y_7194_; uint8_t v___y_7195_; uint8_t v___y_7201_; uint32_t v___y_7211_; uint64_t v___y_7212_; uint64_t v___y_7213_; uint8_t v___y_7214_; uint64_t v___y_7215_; uint32_t v___y_7222_; uint64_t v___y_7223_; uint8_t v___y_7224_; uint64_t v___y_7225_; uint32_t v___y_7232_; uint32_t v___y_7233_; uint8_t v___y_7234_; uint64_t v___y_7235_; uint8_t v___y_7243_; uint32_t v___x_7253_; uint8_t v___x_7254_; uint8_t v___y_7256_; uint8_t v___y_7257_; uint8_t v___y_7259_; uint8_t v___y_7260_; uint8_t v___y_7261_; uint8_t v___y_7263_; uint8_t v___y_7264_; uint8_t v___y_7270_; 
v___x_7141_ = lean_uint32_shift_right(v___y_5731_, v___x_6167_);
v_ev_7142_ = lean_uint32_land(v___x_7141_, v___x_6208_);
v___x_7253_ = lean_uint32_sub(v_ev_7142_, v___x_7056_);
v___x_7254_ = lean_uint32_dec_le(v___x_7253_, v___x_7058_);
if (v___x_7254_ == 0)
{
uint32_t v___x_7279_; uint32_t v___x_7280_; uint8_t v___x_7281_; 
v___x_7279_ = lean_uint32_add(v_eu_7055_, v_ev_7142_);
v___x_7280_ = 128;
v___x_7281_ = lean_uint32_dec_lt(v___x_7279_, v___x_7280_);
if (v___x_7281_ == 0)
{
uint32_t v___x_7282_; uint32_t v_a_7283_; uint32_t v___x_7284_; uint32_t v___x_7285_; uint8_t v___x_7286_; 
v___x_7282_ = 2147483647;
v_a_7283_ = lean_uint32_land(v___y_5730_, v___x_7282_);
v___x_7284_ = 201326591;
v___x_7285_ = lean_uint32_sub(v_a_7283_, v___x_7056_);
v___x_7286_ = lean_uint32_dec_le(v___x_7284_, v___x_7285_);
if (v___x_7286_ == 0)
{
v___y_6183_ = v___x_7286_;
goto v___jp_6182_;
}
else
{
uint32_t v___x_7287_; uint8_t v___x_7288_; 
v___x_7287_ = 2139095040;
v___x_7288_ = lean_uint32_dec_lt(v_a_7283_, v___x_7287_);
v___y_6183_ = v___x_7288_;
goto v___jp_6182_;
}
}
else
{
uint32_t v___x_7289_; uint32_t v___x_7290_; uint8_t v___x_7291_; 
v___x_7289_ = 4278190080;
v___x_7290_ = lean_uint32_shift_left(v___y_5730_, v___x_7056_);
v___x_7291_ = lean_uint32_dec_le(v___x_7289_, v___x_7290_);
if (v___x_7291_ == 0)
{
uint32_t v___x_7292_; uint8_t v___x_7293_; 
v___x_7292_ = lean_uint32_shift_left(v___y_5731_, v___x_7056_);
v___x_7293_ = lean_uint32_dec_le(v___x_7289_, v___x_7292_);
v___y_7201_ = v___x_7293_;
goto v___jp_7200_;
}
else
{
v___y_7201_ = v___x_7291_;
goto v___jp_7200_;
}
}
}
else
{
uint32_t v_s_7294_; uint32_t v___x_7295_; uint32_t v___x_7296_; uint32_t v___x_7297_; uint8_t v___x_7298_; 
v_s_7294_ = lean_uint32_add(v_eu_7055_, v_ev_7142_);
v___x_7295_ = 174;
v___x_7296_ = lean_uint32_sub(v_s_7294_, v___x_7295_);
v___x_7297_ = 206;
v___x_7298_ = lean_uint32_dec_le(v___x_7296_, v___x_7297_);
if (v___x_7298_ == 0)
{
uint32_t v___x_7299_; uint8_t v___x_7300_; 
v___x_7299_ = 128;
v___x_7300_ = lean_uint32_dec_lt(v_s_7294_, v___x_7299_);
if (v___x_7300_ == 0)
{
uint32_t v___x_7301_; uint32_t v_a_7302_; uint32_t v___x_7303_; uint32_t v___x_7304_; uint8_t v___x_7305_; 
v___x_7301_ = 2147483647;
v_a_7302_ = lean_uint32_land(v___y_5730_, v___x_7301_);
v___x_7303_ = 201326591;
v___x_7304_ = lean_uint32_sub(v_a_7302_, v___x_7056_);
v___x_7305_ = lean_uint32_dec_le(v___x_7303_, v___x_7304_);
if (v___x_7305_ == 0)
{
v___y_6196_ = v___x_7305_;
goto v___jp_6195_;
}
else
{
uint32_t v___x_7306_; uint8_t v___x_7307_; 
v___x_7306_ = 2139095040;
v___x_7307_ = lean_uint32_dec_lt(v_a_7302_, v___x_7306_);
v___y_6196_ = v___x_7307_;
goto v___jp_6195_;
}
}
else
{
uint32_t v___x_7308_; uint32_t v___x_7309_; uint8_t v___x_7310_; 
v___x_7308_ = 4278190080;
v___x_7309_ = lean_uint32_shift_left(v___y_5730_, v___x_7056_);
v___x_7310_ = lean_uint32_dec_le(v___x_7308_, v___x_7309_);
if (v___x_7310_ == 0)
{
uint32_t v___x_7311_; uint8_t v___x_7312_; 
v___x_7311_ = lean_uint32_shift_left(v___y_5731_, v___x_7056_);
v___x_7312_ = lean_uint32_dec_le(v___x_7308_, v___x_7311_);
v___y_7270_ = v___x_7312_;
goto v___jp_7269_;
}
else
{
v___y_7270_ = v___x_7310_;
goto v___jp_7269_;
}
}
}
else
{
uint32_t v___x_7313_; uint32_t v___x_7314_; uint32_t v___x_7315_; uint32_t v_a_7316_; uint32_t v___x_7317_; uint32_t v_b_7318_; uint64_t v___x_7319_; uint64_t v___x_7320_; uint64_t v_p_7321_; uint32_t v___x_7322_; uint32_t v___x_7323_; uint32_t v___x_7324_; uint32_t v___x_7325_; uint32_t v___x_7326_; uint32_t v___x_7327_; uint32_t v_w_7328_; float v___x_7329_; lean_object* v___x_7330_; uint32_t v___x_7331_; lean_object* v___x_7332_; lean_object* v___x_7333_; float v___x_7334_; float v___x_7335_; uint32_t v___x_7336_; 
v___x_7313_ = 8388607;
v___x_7314_ = lean_uint32_land(v___y_5730_, v___x_7313_);
v___x_7315_ = 8388608;
v_a_7316_ = lean_uint32_lor(v___x_7314_, v___x_7315_);
v___x_7317_ = lean_uint32_land(v___y_5731_, v___x_7313_);
v_b_7318_ = lean_uint32_lor(v___x_7317_, v___x_7315_);
v___x_7319_ = lean_uint32_to_uint64(v_a_7316_);
v___x_7320_ = lean_uint32_to_uint64(v_b_7318_);
v_p_7321_ = lean_uint64_mul(v___x_7319_, v___x_7320_);
v___x_7322_ = 150;
v___x_7323_ = lean_uint32_sub(v_s_7294_, v___x_7322_);
v___x_7324_ = lean_uint32_shift_left(v___x_7323_, v___x_6167_);
v___x_7325_ = lean_uint32_xor(v___y_5730_, v___y_5731_);
v___x_7326_ = 2147483648;
v___x_7327_ = lean_uint32_land(v___x_7325_, v___x_7326_);
v_w_7328_ = lean_uint32_lor(v___x_7324_, v___x_7327_);
v___x_7329_ = lean_uint64_to_float32(v_p_7321_);
v___x_7330_ = lp_competition_R2W01b_scaleTable;
v___x_7331_ = lean_uint32_shift_right(v_w_7328_, v___x_6167_);
v___x_7332_ = lean_uint32_to_nat(v___x_7331_);
v___x_7333_ = lean_array_fget_borrowed(v___x_7330_, v___x_7332_);
lean_dec(v___x_7332_);
v___x_7334_ = lean_unbox_float32(v___x_7333_);
v___x_7335_ = lean_float32_mul(v___x_7329_, v___x_7334_);
v___x_7336_ = lean_float32_to_bits(v___x_7335_);
return v___x_7336_;
}
}
v___jp_7143_:
{
uint64_t v___x_7149_; uint64_t v___x_7150_; uint8_t v___x_7151_; 
v___x_7149_ = lean_uint32_to_uint64(v_ev_7142_);
v___x_7150_ = 0ULL;
v___x_7151_ = lean_uint64_dec_eq(v___x_7149_, v___x_7150_);
if (v___x_7151_ == 0)
{
uint64_t v___x_7152_; uint64_t v___x_7153_; 
v___x_7152_ = 1ULL;
v___x_7153_ = lean_uint64_sub(v___x_7149_, v___x_7152_);
v___y_6735_ = v___y_7144_;
v___y_6736_ = v___y_7145_;
v___y_6737_ = v___y_7148_;
v___y_6738_ = v___y_7146_;
v___y_6739_ = v___y_7147_;
v___y_6740_ = v___x_7153_;
goto v___jp_6734_;
}
else
{
v___y_6735_ = v___y_7144_;
v___y_6736_ = v___y_7145_;
v___y_6737_ = v___y_7148_;
v___y_6738_ = v___y_7146_;
v___y_6739_ = v___y_7147_;
v___y_6740_ = v___x_7150_;
goto v___jp_6734_;
}
}
v___jp_7154_:
{
uint64_t v___x_7159_; uint64_t v___x_7160_; uint8_t v___x_7161_; 
v___x_7159_ = lean_uint32_to_uint64(v_eu_7055_);
v___x_7160_ = 0ULL;
v___x_7161_ = lean_uint64_dec_eq(v___x_7159_, v___x_7160_);
if (v___x_7161_ == 0)
{
uint64_t v___x_7162_; uint64_t v___x_7163_; 
v___x_7162_ = 1ULL;
v___x_7163_ = lean_uint64_sub(v___x_7159_, v___x_7162_);
v___y_7144_ = v___y_7155_;
v___y_7145_ = v___y_7158_;
v___y_7146_ = v___y_7156_;
v___y_7147_ = v___y_7157_;
v___y_7148_ = v___x_7163_;
goto v___jp_7143_;
}
else
{
v___y_7144_ = v___y_7155_;
v___y_7145_ = v___y_7158_;
v___y_7146_ = v___y_7156_;
v___y_7147_ = v___y_7157_;
v___y_7148_ = v___x_7160_;
goto v___jp_7143_;
}
}
v___jp_7164_:
{
uint32_t v___x_7169_; uint8_t v___x_7170_; 
v___x_7169_ = 0;
v___x_7170_ = lean_uint32_dec_eq(v_ev_7142_, v___x_7169_);
if (v___x_7170_ == 0)
{
uint64_t v___x_7171_; uint64_t v___x_7172_; uint64_t v___x_7173_; 
v___x_7171_ = lean_uint32_to_uint64(v___y_7166_);
v___x_7172_ = 8388608ULL;
v___x_7173_ = lean_uint64_lor(v___x_7171_, v___x_7172_);
v___y_7155_ = v___y_7165_;
v___y_7156_ = v___y_7168_;
v___y_7157_ = v___y_7167_;
v___y_7158_ = v___x_7173_;
goto v___jp_7154_;
}
else
{
uint64_t v___x_7174_; 
v___x_7174_ = lean_uint32_to_uint64(v___y_7166_);
v___y_7155_ = v___y_7165_;
v___y_7156_ = v___y_7168_;
v___y_7157_ = v___y_7167_;
v___y_7158_ = v___x_7174_;
goto v___jp_7154_;
}
}
v___jp_7175_:
{
uint32_t v___x_7177_; uint32_t v_xFraction_7178_; uint32_t v_yFraction_7179_; uint32_t v___x_7180_; uint8_t v___x_7181_; 
v___x_7177_ = 8388607;
v_xFraction_7178_ = lean_uint32_land(v___y_5730_, v___x_7177_);
v_yFraction_7179_ = lean_uint32_land(v___y_5731_, v___x_7177_);
v___x_7180_ = 0;
v___x_7181_ = lean_uint32_dec_eq(v_eu_7055_, v___x_7180_);
if (v___x_7181_ == 0)
{
uint64_t v___x_7182_; uint64_t v___x_7183_; uint64_t v___x_7184_; 
v___x_7182_ = lean_uint32_to_uint64(v_xFraction_7178_);
v___x_7183_ = 8388608ULL;
v___x_7184_ = lean_uint64_lor(v___x_7182_, v___x_7183_);
v___y_7165_ = v___x_7177_;
v___y_7166_ = v_yFraction_7179_;
v___y_7167_ = v___y_7176_;
v___y_7168_ = v___x_7184_;
goto v___jp_7164_;
}
else
{
uint64_t v___x_7185_; 
v___x_7185_ = lean_uint32_to_uint64(v_xFraction_7178_);
v___y_7165_ = v___x_7177_;
v___y_7166_ = v_yFraction_7179_;
v___y_7167_ = v___y_7176_;
v___y_7168_ = v___x_7185_;
goto v___jp_7164_;
}
}
v___jp_7186_:
{
if (v___y_7188_ == 0)
{
v___y_7176_ = v___x_7059_;
goto v___jp_7175_;
}
else
{
v___y_7176_ = v___y_7187_;
goto v___jp_7175_;
}
}
v___jp_7189_:
{
if (v___y_7190_ == 0)
{
if (v___y_7192_ == 0)
{
v___y_7187_ = v___y_7191_;
v___y_7188_ = v___x_7059_;
goto v___jp_7186_;
}
else
{
v___y_7176_ = v___x_7059_;
goto v___jp_7175_;
}
}
else
{
v___y_7187_ = v___y_7191_;
v___y_7188_ = v___y_7192_;
goto v___jp_7186_;
}
}
v___jp_7193_:
{
uint32_t v___x_7196_; uint32_t v___x_7197_; uint32_t v___x_7198_; uint8_t v___x_7199_; 
v___x_7196_ = 2147483648;
v___x_7197_ = lean_uint32_land(v___y_5731_, v___x_7196_);
v___x_7198_ = 0;
v___x_7199_ = lean_uint32_dec_eq(v___x_7197_, v___x_7198_);
if (v___x_7199_ == 0)
{
v___y_7190_ = v___y_7195_;
v___y_7191_ = v___y_7194_;
v___y_7192_ = v___x_7059_;
goto v___jp_7189_;
}
else
{
v___y_7190_ = v___y_7195_;
v___y_7191_ = v___y_7194_;
v___y_7192_ = v___y_7194_;
goto v___jp_7189_;
}
}
v___jp_7200_:
{
if (v___y_7201_ == 0)
{
uint32_t v___x_7202_; uint32_t v___x_7203_; uint32_t v___x_7204_; uint8_t v___x_7205_; 
v___x_7202_ = 2147483648;
v___x_7203_ = lean_uint32_land(v___y_5730_, v___x_7202_);
v___x_7204_ = 0;
v___x_7205_ = lean_uint32_dec_eq(v___x_7203_, v___x_7204_);
if (v___x_7205_ == 0)
{
v___y_7194_ = v___y_7201_;
v___y_7195_ = v___x_7059_;
goto v___jp_7193_;
}
else
{
v___y_7194_ = v___y_7201_;
v___y_7195_ = v___y_7201_;
goto v___jp_7193_;
}
}
else
{
lean_object* v___x_7206_; lean_object* v___x_7207_; lean_object* v___x_7208_; uint32_t v___x_7209_; 
v___x_7206_ = lean_uint32_to_nat(v___y_5730_);
v___x_7207_ = lean_uint32_to_nat(v___y_5731_);
v___x_7208_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_7206_, v___x_7207_);
v___x_7209_ = lean_uint32_of_nat(v___x_7208_);
lean_dec(v___x_7208_);
return v___x_7209_;
}
}
v___jp_7210_:
{
uint64_t v___x_7216_; uint64_t v___x_7217_; uint8_t v___x_7218_; 
v___x_7216_ = lean_uint32_to_uint64(v_ev_7142_);
v___x_7217_ = 0ULL;
v___x_7218_ = lean_uint64_dec_eq(v___x_7216_, v___x_7217_);
if (v___x_7218_ == 0)
{
uint64_t v___x_7219_; uint64_t v___x_7220_; 
v___x_7219_ = 1ULL;
v___x_7220_ = lean_uint64_sub(v___x_7216_, v___x_7219_);
v___y_7017_ = v___y_7211_;
v___y_7018_ = v___y_7212_;
v___y_7019_ = v___y_7213_;
v___y_7020_ = v___y_7214_;
v___y_7021_ = v___y_7215_;
v___y_7022_ = v___x_7220_;
goto v___jp_7016_;
}
else
{
v___y_7017_ = v___y_7211_;
v___y_7018_ = v___y_7212_;
v___y_7019_ = v___y_7213_;
v___y_7020_ = v___y_7214_;
v___y_7021_ = v___y_7215_;
v___y_7022_ = v___x_7217_;
goto v___jp_7016_;
}
}
v___jp_7221_:
{
uint64_t v___x_7226_; uint64_t v___x_7227_; uint8_t v___x_7228_; 
v___x_7226_ = lean_uint32_to_uint64(v_eu_7055_);
v___x_7227_ = 0ULL;
v___x_7228_ = lean_uint64_dec_eq(v___x_7226_, v___x_7227_);
if (v___x_7228_ == 0)
{
uint64_t v___x_7229_; uint64_t v___x_7230_; 
v___x_7229_ = 1ULL;
v___x_7230_ = lean_uint64_sub(v___x_7226_, v___x_7229_);
v___y_7211_ = v___y_7222_;
v___y_7212_ = v___y_7223_;
v___y_7213_ = v___y_7225_;
v___y_7214_ = v___y_7224_;
v___y_7215_ = v___x_7230_;
goto v___jp_7210_;
}
else
{
v___y_7211_ = v___y_7222_;
v___y_7212_ = v___y_7223_;
v___y_7213_ = v___y_7225_;
v___y_7214_ = v___y_7224_;
v___y_7215_ = v___x_7227_;
goto v___jp_7210_;
}
}
v___jp_7231_:
{
uint32_t v___x_7236_; uint8_t v___x_7237_; 
v___x_7236_ = 0;
v___x_7237_ = lean_uint32_dec_eq(v_ev_7142_, v___x_7236_);
if (v___x_7237_ == 0)
{
uint64_t v___x_7238_; uint64_t v___x_7239_; uint64_t v___x_7240_; 
v___x_7238_ = lean_uint32_to_uint64(v___y_7233_);
v___x_7239_ = 8388608ULL;
v___x_7240_ = lean_uint64_lor(v___x_7238_, v___x_7239_);
v___y_7222_ = v___y_7232_;
v___y_7223_ = v___y_7235_;
v___y_7224_ = v___y_7234_;
v___y_7225_ = v___x_7240_;
goto v___jp_7221_;
}
else
{
uint64_t v___x_7241_; 
v___x_7241_ = lean_uint32_to_uint64(v___y_7233_);
v___y_7222_ = v___y_7232_;
v___y_7223_ = v___y_7235_;
v___y_7224_ = v___y_7234_;
v___y_7225_ = v___x_7241_;
goto v___jp_7221_;
}
}
v___jp_7242_:
{
uint32_t v___x_7244_; uint32_t v_xFraction_7245_; uint32_t v_yFraction_7246_; uint32_t v___x_7247_; uint8_t v___x_7248_; 
v___x_7244_ = 8388607;
v_xFraction_7245_ = lean_uint32_land(v___y_5730_, v___x_7244_);
v_yFraction_7246_ = lean_uint32_land(v___y_5731_, v___x_7244_);
v___x_7247_ = 0;
v___x_7248_ = lean_uint32_dec_eq(v_eu_7055_, v___x_7247_);
if (v___x_7248_ == 0)
{
uint64_t v___x_7249_; uint64_t v___x_7250_; uint64_t v___x_7251_; 
v___x_7249_ = lean_uint32_to_uint64(v_xFraction_7245_);
v___x_7250_ = 8388608ULL;
v___x_7251_ = lean_uint64_lor(v___x_7249_, v___x_7250_);
v___y_7232_ = v___x_7244_;
v___y_7233_ = v_yFraction_7246_;
v___y_7234_ = v___y_7243_;
v___y_7235_ = v___x_7251_;
goto v___jp_7231_;
}
else
{
uint64_t v___x_7252_; 
v___x_7252_ = lean_uint32_to_uint64(v_xFraction_7245_);
v___y_7232_ = v___x_7244_;
v___y_7233_ = v_yFraction_7246_;
v___y_7234_ = v___y_7243_;
v___y_7235_ = v___x_7252_;
goto v___jp_7231_;
}
}
v___jp_7255_:
{
if (v___y_7257_ == 0)
{
v___y_7243_ = v___x_7254_;
goto v___jp_7242_;
}
else
{
v___y_7243_ = v___y_7256_;
goto v___jp_7242_;
}
}
v___jp_7258_:
{
if (v___y_7259_ == 0)
{
if (v___y_7261_ == 0)
{
v___y_7256_ = v___y_7260_;
v___y_7257_ = v___x_7254_;
goto v___jp_7255_;
}
else
{
v___y_7243_ = v___x_7254_;
goto v___jp_7242_;
}
}
else
{
v___y_7256_ = v___y_7260_;
v___y_7257_ = v___y_7261_;
goto v___jp_7255_;
}
}
v___jp_7262_:
{
uint32_t v___x_7265_; uint32_t v___x_7266_; uint32_t v___x_7267_; uint8_t v___x_7268_; 
v___x_7265_ = 2147483648;
v___x_7266_ = lean_uint32_land(v___y_5731_, v___x_7265_);
v___x_7267_ = 0;
v___x_7268_ = lean_uint32_dec_eq(v___x_7266_, v___x_7267_);
if (v___x_7268_ == 0)
{
v___y_7259_ = v___y_7264_;
v___y_7260_ = v___y_7263_;
v___y_7261_ = v___x_7254_;
goto v___jp_7258_;
}
else
{
v___y_7259_ = v___y_7264_;
v___y_7260_ = v___y_7263_;
v___y_7261_ = v___y_7263_;
goto v___jp_7258_;
}
}
v___jp_7269_:
{
if (v___y_7270_ == 0)
{
uint32_t v___x_7271_; uint32_t v___x_7272_; uint32_t v___x_7273_; uint8_t v___x_7274_; 
v___x_7271_ = 2147483648;
v___x_7272_ = lean_uint32_land(v___y_5730_, v___x_7271_);
v___x_7273_ = 0;
v___x_7274_ = lean_uint32_dec_eq(v___x_7272_, v___x_7273_);
if (v___x_7274_ == 0)
{
v___y_7263_ = v___y_7270_;
v___y_7264_ = v___x_7254_;
goto v___jp_7262_;
}
else
{
v___y_7263_ = v___y_7270_;
v___y_7264_ = v___y_7270_;
goto v___jp_7262_;
}
}
else
{
lean_object* v___x_7275_; lean_object* v___x_7276_; lean_object* v___x_7277_; uint32_t v___x_7278_; 
v___x_7275_ = lean_uint32_to_nat(v___y_5730_);
v___x_7276_ = lean_uint32_to_nat(v___y_5731_);
v___x_7277_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_7275_, v___x_7276_);
v___x_7278_ = lean_uint32_of_nat(v___x_7277_);
lean_dec(v___x_7277_);
return v___x_7278_;
}
}
}
v___jp_5732_:
{
if (v___y_5733_ == 0)
{
uint32_t v___x_5734_; 
v___x_5734_ = lp_competition_Submission_FastMul_mul(v___y_5730_, v___y_5731_);
return v___x_5734_;
}
else
{
uint32_t v___x_5735_; uint32_t v___x_5736_; 
v___x_5735_ = 4194304;
v___x_5736_ = lean_uint32_lor(v___y_5731_, v___x_5735_);
return v___x_5736_;
}
}
v___jp_5737_:
{
uint32_t v___x_5738_; uint32_t v___x_5739_; uint32_t v___x_5740_; uint32_t v___x_5741_; uint8_t v___x_5742_; 
v___x_5738_ = 23;
v___x_5739_ = lean_uint32_shift_right(v___y_5731_, v___x_5738_);
v___x_5740_ = 255;
v___x_5741_ = lean_uint32_land(v___x_5739_, v___x_5740_);
v___x_5742_ = lean_uint32_dec_eq(v___x_5741_, v___x_5740_);
if (v___x_5742_ == 0)
{
v___y_5733_ = v___x_5742_;
goto v___jp_5732_;
}
else
{
uint32_t v___x_5743_; uint32_t v___x_5744_; uint32_t v___x_5745_; uint8_t v___x_5746_; 
v___x_5743_ = 8388607;
v___x_5744_ = lean_uint32_land(v___y_5731_, v___x_5743_);
v___x_5745_ = 0;
v___x_5746_ = lean_uint32_dec_eq(v___x_5744_, v___x_5745_);
if (v___x_5746_ == 0)
{
v___y_5733_ = v___x_5742_;
goto v___jp_5732_;
}
else
{
uint32_t v___x_5747_; 
v___x_5747_ = lp_competition_Submission_FastMul_mul(v___y_5730_, v___y_5731_);
return v___x_5747_;
}
}
}
v___jp_5748_:
{
if (v___y_5749_ == 0)
{
goto v___jp_5737_;
}
else
{
uint32_t v___x_5750_; uint32_t v___x_5751_; 
v___x_5750_ = 4194304;
v___x_5751_ = lean_uint32_lor(v___y_5730_, v___x_5750_);
return v___x_5751_;
}
}
v___jp_5752_:
{
uint32_t v___x_5753_; uint32_t v___x_5754_; uint32_t v___x_5755_; uint32_t v___x_5756_; uint8_t v___x_5757_; 
v___x_5753_ = 23;
v___x_5754_ = lean_uint32_shift_right(v___y_5730_, v___x_5753_);
v___x_5755_ = 255;
v___x_5756_ = lean_uint32_land(v___x_5754_, v___x_5755_);
v___x_5757_ = lean_uint32_dec_eq(v___x_5756_, v___x_5755_);
if (v___x_5757_ == 0)
{
v___y_5749_ = v___x_5757_;
goto v___jp_5748_;
}
else
{
uint32_t v___x_5758_; uint32_t v___x_5759_; uint32_t v___x_5760_; uint8_t v___x_5761_; 
v___x_5758_ = 8388607;
v___x_5759_ = lean_uint32_land(v___y_5730_, v___x_5758_);
v___x_5760_ = 0;
v___x_5761_ = lean_uint32_dec_eq(v___x_5759_, v___x_5760_);
if (v___x_5761_ == 0)
{
v___y_5749_ = v___x_5757_;
goto v___jp_5748_;
}
else
{
goto v___jp_5737_;
}
}
}
v___jp_5762_:
{
if (v___y_5763_ == 0)
{
goto v___jp_5752_;
}
else
{
uint32_t v___x_5764_; uint32_t v___x_5765_; uint32_t v___x_5766_; uint8_t v___x_5767_; 
v___x_5764_ = 4194304;
v___x_5765_ = lean_uint32_land(v___y_5731_, v___x_5764_);
v___x_5766_ = 0;
v___x_5767_ = lean_uint32_dec_eq(v___x_5765_, v___x_5766_);
if (v___x_5767_ == 0)
{
goto v___jp_5752_;
}
else
{
uint32_t v___x_5768_; 
v___x_5768_ = lean_uint32_lor(v___y_5731_, v___x_5764_);
return v___x_5768_;
}
}
}
v___jp_5769_:
{
uint32_t v___x_5770_; uint32_t v___x_5771_; uint32_t v___x_5772_; uint32_t v___x_5773_; uint8_t v___x_5774_; 
v___x_5770_ = 23;
v___x_5771_ = lean_uint32_shift_right(v___y_5731_, v___x_5770_);
v___x_5772_ = 255;
v___x_5773_ = lean_uint32_land(v___x_5771_, v___x_5772_);
v___x_5774_ = lean_uint32_dec_eq(v___x_5773_, v___x_5772_);
if (v___x_5774_ == 0)
{
v___y_5763_ = v___x_5774_;
goto v___jp_5762_;
}
else
{
uint32_t v___x_5775_; uint32_t v___x_5776_; uint32_t v___x_5777_; uint8_t v___x_5778_; 
v___x_5775_ = 8388607;
v___x_5776_ = lean_uint32_land(v___y_5731_, v___x_5775_);
v___x_5777_ = 0;
v___x_5778_ = lean_uint32_dec_eq(v___x_5776_, v___x_5777_);
if (v___x_5778_ == 0)
{
v___y_5763_ = v___x_5774_;
goto v___jp_5762_;
}
else
{
goto v___jp_5752_;
}
}
}
v___jp_5779_:
{
if (v___y_5780_ == 0)
{
goto v___jp_5769_;
}
else
{
uint32_t v___x_5781_; uint32_t v___x_5782_; uint32_t v___x_5783_; uint8_t v___x_5784_; 
v___x_5781_ = 4194304;
v___x_5782_ = lean_uint32_land(v___y_5730_, v___x_5781_);
v___x_5783_ = 0;
v___x_5784_ = lean_uint32_dec_eq(v___x_5782_, v___x_5783_);
if (v___x_5784_ == 0)
{
goto v___jp_5769_;
}
else
{
uint32_t v___x_5785_; 
v___x_5785_ = lean_uint32_lor(v___y_5730_, v___x_5781_);
return v___x_5785_;
}
}
}
v___jp_5786_:
{
float v_result_5789_; uint8_t v___x_5790_; 
v_result_5789_ = lean_float32_mul(v___y_5787_, v___y_5788_);
v___x_5790_ = lean_float32_beq(v_result_5789_, v_result_5789_);
if (v___x_5790_ == 0)
{
uint32_t v___x_5791_; uint32_t v___x_5792_; uint32_t v___x_5793_; uint32_t v___x_5794_; uint8_t v___x_5795_; 
v___x_5791_ = 23;
v___x_5792_ = lean_uint32_shift_right(v___y_5730_, v___x_5791_);
v___x_5793_ = 255;
v___x_5794_ = lean_uint32_land(v___x_5792_, v___x_5793_);
v___x_5795_ = lean_uint32_dec_eq(v___x_5794_, v___x_5793_);
if (v___x_5795_ == 0)
{
v___y_5780_ = v___x_5795_;
goto v___jp_5779_;
}
else
{
uint32_t v___x_5796_; uint32_t v___x_5797_; uint32_t v___x_5798_; uint8_t v___x_5799_; 
v___x_5796_ = 8388607;
v___x_5797_ = lean_uint32_land(v___y_5730_, v___x_5796_);
v___x_5798_ = 0;
v___x_5799_ = lean_uint32_dec_eq(v___x_5797_, v___x_5798_);
if (v___x_5799_ == 0)
{
v___y_5780_ = v___x_5795_;
goto v___jp_5779_;
}
else
{
goto v___jp_5769_;
}
}
}
else
{
uint32_t v___x_5800_; 
v___x_5800_ = lean_float32_to_bits(v_result_5789_);
return v___x_5800_;
}
}
v___jp_5801_:
{
if (v___y_5803_ == 0)
{
float v___x_5804_; 
v___x_5804_ = lean_float32_of_bits(v___y_5731_);
v___y_5787_ = v___y_5802_;
v___y_5788_ = v___x_5804_;
goto v___jp_5786_;
}
else
{
uint32_t v___x_5805_; uint32_t v___x_5806_; uint32_t v___x_5807_; uint32_t v___x_5808_; float v___x_5809_; lean_object* v___x_5810_; uint32_t v___x_5811_; uint32_t v___x_5812_; lean_object* v___x_5813_; lean_object* v___x_5814_; float v___x_5815_; float v___x_5816_; 
v___x_5805_ = 8388607;
v___x_5806_ = lean_uint32_land(v___y_5731_, v___x_5805_);
v___x_5807_ = 8388608;
v___x_5808_ = lean_uint32_lor(v___x_5806_, v___x_5807_);
v___x_5809_ = lean_uint32_to_float32(v___x_5808_);
v___x_5810_ = lp_competition_R2W01b_scaleTable;
v___x_5811_ = 23;
v___x_5812_ = lean_uint32_shift_right(v___y_5731_, v___x_5811_);
v___x_5813_ = lean_uint32_to_nat(v___x_5812_);
v___x_5814_ = lean_array_fget_borrowed(v___x_5810_, v___x_5813_);
lean_dec(v___x_5813_);
v___x_5815_ = lean_unbox_float32(v___x_5814_);
v___x_5816_ = lean_float32_mul(v___x_5809_, v___x_5815_);
v___y_5787_ = v___y_5802_;
v___y_5788_ = v___x_5816_;
goto v___jp_5786_;
}
}
v___jp_5817_:
{
uint32_t v___x_5819_; uint32_t v_a_5820_; uint32_t v___x_5821_; uint32_t v___x_5822_; uint32_t v___x_5823_; uint8_t v___x_5824_; 
v___x_5819_ = 2147483647;
v_a_5820_ = lean_uint32_land(v___y_5731_, v___x_5819_);
v___x_5821_ = 201326591;
v___x_5822_ = 1;
v___x_5823_ = lean_uint32_sub(v_a_5820_, v___x_5822_);
v___x_5824_ = lean_uint32_dec_le(v___x_5821_, v___x_5823_);
if (v___x_5824_ == 0)
{
v___y_5802_ = v___y_5818_;
v___y_5803_ = v___x_5824_;
goto v___jp_5801_;
}
else
{
uint32_t v___x_5825_; uint8_t v___x_5826_; 
v___x_5825_ = 2139095040;
v___x_5826_ = lean_uint32_dec_lt(v_a_5820_, v___x_5825_);
v___y_5802_ = v___y_5818_;
v___y_5803_ = v___x_5826_;
goto v___jp_5801_;
}
}
v___jp_5827_:
{
uint32_t v___x_5829_; uint32_t v___x_5830_; 
v___x_5829_ = 8388608;
v___x_5830_ = lean_uint32_lor(v___y_5828_, v___x_5829_);
return v___x_5830_;
}
v___jp_5831_:
{
uint32_t v___x_5833_; uint32_t v___x_5834_; 
v___x_5833_ = 8388608;
v___x_5834_ = lean_uint32_lor(v___y_5832_, v___x_5833_);
return v___x_5834_;
}
v___jp_5835_:
{
uint32_t v___x_5839_; uint32_t v___x_5840_; 
v___x_5839_ = lean_uint32_land(v___y_5837_, v___y_5836_);
v___x_5840_ = lean_uint32_lor(v___y_5838_, v___x_5839_);
return v___x_5840_;
}
v___jp_5841_:
{
uint8_t v___x_5846_; 
v___x_5846_ = lean_uint64_dec_eq(v___y_5845_, v___y_5843_);
if (v___x_5846_ == 0)
{
uint64_t v___x_5847_; uint8_t v___x_5848_; 
v___x_5847_ = 8388608ULL;
v___x_5848_ = lean_uint64_dec_eq(v___y_5845_, v___x_5847_);
if (v___x_5848_ == 0)
{
uint32_t v___x_5849_; 
v___x_5849_ = lean_uint64_to_uint32(v___y_5845_);
if (v___y_5844_ == 0)
{
uint32_t v___x_5850_; 
v___x_5850_ = 0;
v___y_5836_ = v___y_5842_;
v___y_5837_ = v___x_5849_;
v___y_5838_ = v___x_5850_;
goto v___jp_5835_;
}
else
{
uint32_t v___x_5851_; 
v___x_5851_ = 2147483648;
v___y_5836_ = v___y_5842_;
v___y_5837_ = v___x_5849_;
v___y_5838_ = v___x_5851_;
goto v___jp_5835_;
}
}
else
{
if (v___y_5844_ == 0)
{
uint32_t v___x_5852_; 
v___x_5852_ = 0;
v___y_5828_ = v___x_5852_;
goto v___jp_5827_;
}
else
{
uint32_t v___x_5853_; 
v___x_5853_ = 2147483648;
v___y_5828_ = v___x_5853_;
goto v___jp_5827_;
}
}
}
else
{
if (v___y_5844_ == 0)
{
uint32_t v___x_5854_; 
v___x_5854_ = 0;
return v___x_5854_;
}
else
{
uint32_t v___x_5855_; 
v___x_5855_ = 2147483648;
return v___x_5855_;
}
}
}
v___jp_5856_:
{
uint32_t v___x_5860_; uint32_t v___x_5861_; 
v___x_5860_ = lean_uint32_land(v___y_5858_, v___y_5857_);
v___x_5861_ = lean_uint32_lor(v___y_5859_, v___x_5860_);
return v___x_5861_;
}
v___jp_5862_:
{
uint8_t v___x_5867_; 
v___x_5867_ = lean_uint64_dec_eq(v___y_5866_, v___y_5864_);
if (v___x_5867_ == 0)
{
uint64_t v___x_5868_; uint8_t v___x_5869_; 
v___x_5868_ = 8388608ULL;
v___x_5869_ = lean_uint64_dec_eq(v___y_5866_, v___x_5868_);
if (v___x_5869_ == 0)
{
uint32_t v___x_5870_; 
v___x_5870_ = lean_uint64_to_uint32(v___y_5866_);
if (v___y_5865_ == 0)
{
uint32_t v___x_5871_; 
v___x_5871_ = 0;
v___y_5857_ = v___y_5863_;
v___y_5858_ = v___x_5870_;
v___y_5859_ = v___x_5871_;
goto v___jp_5856_;
}
else
{
uint32_t v___x_5872_; 
v___x_5872_ = 2147483648;
v___y_5857_ = v___y_5863_;
v___y_5858_ = v___x_5870_;
v___y_5859_ = v___x_5872_;
goto v___jp_5856_;
}
}
else
{
if (v___y_5865_ == 0)
{
uint32_t v___x_5873_; 
v___x_5873_ = 0;
v___y_5832_ = v___x_5873_;
goto v___jp_5831_;
}
else
{
uint32_t v___x_5874_; 
v___x_5874_ = 2147483648;
v___y_5832_ = v___x_5874_;
goto v___jp_5831_;
}
}
}
else
{
if (v___y_5865_ == 0)
{
uint32_t v___x_5875_; 
v___x_5875_ = 0;
return v___x_5875_;
}
else
{
uint32_t v___x_5876_; 
v___x_5876_ = 2147483648;
return v___x_5876_;
}
}
}
v___jp_5877_:
{
if (v___y_5878_ == 0)
{
uint32_t v___x_5879_; 
v___x_5879_ = lp_competition_Submission_FastMul_mul(v___y_5730_, v___y_5731_);
return v___x_5879_;
}
else
{
uint32_t v___x_5880_; uint32_t v___x_5881_; 
v___x_5880_ = 4194304;
v___x_5881_ = lean_uint32_lor(v___y_5731_, v___x_5880_);
return v___x_5881_;
}
}
v___jp_5882_:
{
uint32_t v___x_5883_; uint32_t v___x_5884_; uint32_t v___x_5885_; uint32_t v___x_5886_; uint8_t v___x_5887_; 
v___x_5883_ = 23;
v___x_5884_ = lean_uint32_shift_right(v___y_5731_, v___x_5883_);
v___x_5885_ = 255;
v___x_5886_ = lean_uint32_land(v___x_5884_, v___x_5885_);
v___x_5887_ = lean_uint32_dec_eq(v___x_5886_, v___x_5885_);
if (v___x_5887_ == 0)
{
v___y_5878_ = v___x_5887_;
goto v___jp_5877_;
}
else
{
uint32_t v___x_5888_; uint32_t v___x_5889_; uint32_t v___x_5890_; uint8_t v___x_5891_; 
v___x_5888_ = 8388607;
v___x_5889_ = lean_uint32_land(v___y_5731_, v___x_5888_);
v___x_5890_ = 0;
v___x_5891_ = lean_uint32_dec_eq(v___x_5889_, v___x_5890_);
if (v___x_5891_ == 0)
{
v___y_5878_ = v___x_5887_;
goto v___jp_5877_;
}
else
{
uint32_t v___x_5892_; 
v___x_5892_ = lp_competition_Submission_FastMul_mul(v___y_5730_, v___y_5731_);
return v___x_5892_;
}
}
}
v___jp_5893_:
{
if (v___y_5894_ == 0)
{
goto v___jp_5882_;
}
else
{
uint32_t v___x_5895_; uint32_t v___x_5896_; 
v___x_5895_ = 4194304;
v___x_5896_ = lean_uint32_lor(v___y_5730_, v___x_5895_);
return v___x_5896_;
}
}
v___jp_5897_:
{
uint32_t v___x_5898_; uint32_t v___x_5899_; uint32_t v___x_5900_; uint32_t v___x_5901_; uint8_t v___x_5902_; 
v___x_5898_ = 23;
v___x_5899_ = lean_uint32_shift_right(v___y_5730_, v___x_5898_);
v___x_5900_ = 255;
v___x_5901_ = lean_uint32_land(v___x_5899_, v___x_5900_);
v___x_5902_ = lean_uint32_dec_eq(v___x_5901_, v___x_5900_);
if (v___x_5902_ == 0)
{
v___y_5894_ = v___x_5902_;
goto v___jp_5893_;
}
else
{
uint32_t v___x_5903_; uint32_t v___x_5904_; uint32_t v___x_5905_; uint8_t v___x_5906_; 
v___x_5903_ = 8388607;
v___x_5904_ = lean_uint32_land(v___y_5730_, v___x_5903_);
v___x_5905_ = 0;
v___x_5906_ = lean_uint32_dec_eq(v___x_5904_, v___x_5905_);
if (v___x_5906_ == 0)
{
v___y_5894_ = v___x_5902_;
goto v___jp_5893_;
}
else
{
goto v___jp_5882_;
}
}
}
v___jp_5907_:
{
if (v___y_5908_ == 0)
{
goto v___jp_5897_;
}
else
{
uint32_t v___x_5909_; uint32_t v___x_5910_; uint32_t v___x_5911_; uint8_t v___x_5912_; 
v___x_5909_ = 4194304;
v___x_5910_ = lean_uint32_land(v___y_5731_, v___x_5909_);
v___x_5911_ = 0;
v___x_5912_ = lean_uint32_dec_eq(v___x_5910_, v___x_5911_);
if (v___x_5912_ == 0)
{
goto v___jp_5897_;
}
else
{
uint32_t v___x_5913_; 
v___x_5913_ = lean_uint32_lor(v___y_5731_, v___x_5909_);
return v___x_5913_;
}
}
}
v___jp_5914_:
{
uint32_t v___x_5915_; uint32_t v___x_5916_; uint32_t v___x_5917_; uint32_t v___x_5918_; uint8_t v___x_5919_; 
v___x_5915_ = 23;
v___x_5916_ = lean_uint32_shift_right(v___y_5731_, v___x_5915_);
v___x_5917_ = 255;
v___x_5918_ = lean_uint32_land(v___x_5916_, v___x_5917_);
v___x_5919_ = lean_uint32_dec_eq(v___x_5918_, v___x_5917_);
if (v___x_5919_ == 0)
{
v___y_5908_ = v___x_5919_;
goto v___jp_5907_;
}
else
{
uint32_t v___x_5920_; uint32_t v___x_5921_; uint32_t v___x_5922_; uint8_t v___x_5923_; 
v___x_5920_ = 8388607;
v___x_5921_ = lean_uint32_land(v___y_5731_, v___x_5920_);
v___x_5922_ = 0;
v___x_5923_ = lean_uint32_dec_eq(v___x_5921_, v___x_5922_);
if (v___x_5923_ == 0)
{
v___y_5908_ = v___x_5919_;
goto v___jp_5907_;
}
else
{
goto v___jp_5897_;
}
}
}
v___jp_5924_:
{
if (v___y_5925_ == 0)
{
goto v___jp_5914_;
}
else
{
uint32_t v___x_5926_; uint32_t v___x_5927_; uint32_t v___x_5928_; uint8_t v___x_5929_; 
v___x_5926_ = 4194304;
v___x_5927_ = lean_uint32_land(v___y_5730_, v___x_5926_);
v___x_5928_ = 0;
v___x_5929_ = lean_uint32_dec_eq(v___x_5927_, v___x_5928_);
if (v___x_5929_ == 0)
{
goto v___jp_5914_;
}
else
{
uint32_t v___x_5930_; 
v___x_5930_ = lean_uint32_lor(v___y_5730_, v___x_5926_);
return v___x_5930_;
}
}
}
v___jp_5931_:
{
float v_result_5934_; uint8_t v___x_5935_; 
v_result_5934_ = lean_float32_mul(v___y_5932_, v___y_5933_);
v___x_5935_ = lean_float32_beq(v_result_5934_, v_result_5934_);
if (v___x_5935_ == 0)
{
uint32_t v___x_5936_; uint32_t v___x_5937_; uint32_t v___x_5938_; uint32_t v___x_5939_; uint8_t v___x_5940_; 
v___x_5936_ = 23;
v___x_5937_ = lean_uint32_shift_right(v___y_5730_, v___x_5936_);
v___x_5938_ = 255;
v___x_5939_ = lean_uint32_land(v___x_5937_, v___x_5938_);
v___x_5940_ = lean_uint32_dec_eq(v___x_5939_, v___x_5938_);
if (v___x_5940_ == 0)
{
v___y_5925_ = v___x_5940_;
goto v___jp_5924_;
}
else
{
uint32_t v___x_5941_; uint32_t v___x_5942_; uint32_t v___x_5943_; uint8_t v___x_5944_; 
v___x_5941_ = 8388607;
v___x_5942_ = lean_uint32_land(v___y_5730_, v___x_5941_);
v___x_5943_ = 0;
v___x_5944_ = lean_uint32_dec_eq(v___x_5942_, v___x_5943_);
if (v___x_5944_ == 0)
{
v___y_5925_ = v___x_5940_;
goto v___jp_5924_;
}
else
{
goto v___jp_5914_;
}
}
}
else
{
uint32_t v___x_5945_; 
v___x_5945_ = lean_float32_to_bits(v_result_5934_);
return v___x_5945_;
}
}
v___jp_5946_:
{
if (v___y_5948_ == 0)
{
float v___x_5949_; 
v___x_5949_ = lean_float32_of_bits(v___y_5731_);
v___y_5932_ = v___y_5947_;
v___y_5933_ = v___x_5949_;
goto v___jp_5931_;
}
else
{
uint32_t v___x_5950_; uint32_t v___x_5951_; uint32_t v___x_5952_; uint32_t v___x_5953_; float v___x_5954_; lean_object* v___x_5955_; uint32_t v___x_5956_; uint32_t v___x_5957_; lean_object* v___x_5958_; lean_object* v___x_5959_; float v___x_5960_; float v___x_5961_; 
v___x_5950_ = 8388607;
v___x_5951_ = lean_uint32_land(v___y_5731_, v___x_5950_);
v___x_5952_ = 8388608;
v___x_5953_ = lean_uint32_lor(v___x_5951_, v___x_5952_);
v___x_5954_ = lean_uint32_to_float32(v___x_5953_);
v___x_5955_ = lp_competition_R2W01b_scaleTable;
v___x_5956_ = 23;
v___x_5957_ = lean_uint32_shift_right(v___y_5731_, v___x_5956_);
v___x_5958_ = lean_uint32_to_nat(v___x_5957_);
v___x_5959_ = lean_array_fget_borrowed(v___x_5955_, v___x_5958_);
lean_dec(v___x_5958_);
v___x_5960_ = lean_unbox_float32(v___x_5959_);
v___x_5961_ = lean_float32_mul(v___x_5954_, v___x_5960_);
v___y_5932_ = v___y_5947_;
v___y_5933_ = v___x_5961_;
goto v___jp_5931_;
}
}
v___jp_5962_:
{
uint32_t v___x_5964_; uint32_t v_a_5965_; uint32_t v___x_5966_; uint32_t v___x_5967_; uint32_t v___x_5968_; uint8_t v___x_5969_; 
v___x_5964_ = 2147483647;
v_a_5965_ = lean_uint32_land(v___y_5731_, v___x_5964_);
v___x_5966_ = 201326591;
v___x_5967_ = 1;
v___x_5968_ = lean_uint32_sub(v_a_5965_, v___x_5967_);
v___x_5969_ = lean_uint32_dec_le(v___x_5966_, v___x_5968_);
if (v___x_5969_ == 0)
{
v___y_5947_ = v___y_5963_;
v___y_5948_ = v___x_5969_;
goto v___jp_5946_;
}
else
{
uint32_t v___x_5970_; uint8_t v___x_5971_; 
v___x_5970_ = 2139095040;
v___x_5971_ = lean_uint32_dec_lt(v_a_5965_, v___x_5970_);
v___y_5947_ = v___y_5963_;
v___y_5948_ = v___x_5971_;
goto v___jp_5946_;
}
}
v___jp_5972_:
{
uint32_t v___x_5974_; uint32_t v___x_5975_; 
v___x_5974_ = 8388608;
v___x_5975_ = lean_uint32_lor(v___y_5973_, v___x_5974_);
return v___x_5975_;
}
v___jp_5976_:
{
uint32_t v___x_5978_; uint32_t v___x_5979_; 
v___x_5978_ = 8388608;
v___x_5979_ = lean_uint32_lor(v___y_5977_, v___x_5978_);
return v___x_5979_;
}
v___jp_5980_:
{
uint32_t v___x_5984_; uint32_t v___x_5985_; 
v___x_5984_ = lean_uint32_land(v___y_5982_, v___y_5981_);
v___x_5985_ = lean_uint32_lor(v___y_5983_, v___x_5984_);
return v___x_5985_;
}
v___jp_5986_:
{
uint8_t v___x_5991_; 
v___x_5991_ = lean_uint64_dec_eq(v___y_5990_, v___y_5988_);
if (v___x_5991_ == 0)
{
uint64_t v___x_5992_; uint8_t v___x_5993_; 
v___x_5992_ = 8388608ULL;
v___x_5993_ = lean_uint64_dec_eq(v___y_5990_, v___x_5992_);
if (v___x_5993_ == 0)
{
uint32_t v___x_5994_; 
v___x_5994_ = lean_uint64_to_uint32(v___y_5990_);
if (v___y_5989_ == 0)
{
uint32_t v___x_5995_; 
v___x_5995_ = 0;
v___y_5981_ = v___y_5987_;
v___y_5982_ = v___x_5994_;
v___y_5983_ = v___x_5995_;
goto v___jp_5980_;
}
else
{
uint32_t v___x_5996_; 
v___x_5996_ = 2147483648;
v___y_5981_ = v___y_5987_;
v___y_5982_ = v___x_5994_;
v___y_5983_ = v___x_5996_;
goto v___jp_5980_;
}
}
else
{
if (v___y_5989_ == 0)
{
uint32_t v___x_5997_; 
v___x_5997_ = 0;
v___y_5977_ = v___x_5997_;
goto v___jp_5976_;
}
else
{
uint32_t v___x_5998_; 
v___x_5998_ = 2147483648;
v___y_5977_ = v___x_5998_;
goto v___jp_5976_;
}
}
}
else
{
if (v___y_5989_ == 0)
{
uint32_t v___x_5999_; 
v___x_5999_ = 0;
return v___x_5999_;
}
else
{
uint32_t v___x_6000_; 
v___x_6000_ = 2147483648;
return v___x_6000_;
}
}
}
v___jp_6001_:
{
uint32_t v___x_6005_; uint32_t v___x_6006_; 
v___x_6005_ = lean_uint32_land(v___y_6002_, v___y_6003_);
v___x_6006_ = lean_uint32_lor(v___y_6004_, v___x_6005_);
return v___x_6006_;
}
v___jp_6007_:
{
uint8_t v___x_6012_; 
v___x_6012_ = lean_uint64_dec_eq(v___y_6011_, v___y_6010_);
if (v___x_6012_ == 0)
{
uint64_t v___x_6013_; uint8_t v___x_6014_; 
v___x_6013_ = 8388608ULL;
v___x_6014_ = lean_uint64_dec_eq(v___y_6011_, v___x_6013_);
if (v___x_6014_ == 0)
{
uint32_t v___x_6015_; 
v___x_6015_ = lean_uint64_to_uint32(v___y_6011_);
if (v___y_6009_ == 0)
{
uint32_t v___x_6016_; 
v___x_6016_ = 0;
v___y_6002_ = v___x_6015_;
v___y_6003_ = v___y_6008_;
v___y_6004_ = v___x_6016_;
goto v___jp_6001_;
}
else
{
uint32_t v___x_6017_; 
v___x_6017_ = 2147483648;
v___y_6002_ = v___x_6015_;
v___y_6003_ = v___y_6008_;
v___y_6004_ = v___x_6017_;
goto v___jp_6001_;
}
}
else
{
if (v___y_6009_ == 0)
{
uint32_t v___x_6018_; 
v___x_6018_ = 0;
v___y_5973_ = v___x_6018_;
goto v___jp_5972_;
}
else
{
uint32_t v___x_6019_; 
v___x_6019_ = 2147483648;
v___y_5973_ = v___x_6019_;
goto v___jp_5972_;
}
}
}
else
{
if (v___y_6009_ == 0)
{
uint32_t v___x_6020_; 
v___x_6020_ = 0;
return v___x_6020_;
}
else
{
uint32_t v___x_6021_; 
v___x_6021_ = 2147483648;
return v___x_6021_;
}
}
}
v___jp_6022_:
{
if (v___y_6023_ == 0)
{
uint32_t v___x_6024_; 
v___x_6024_ = lp_competition_Submission_FastMul_mul(v___y_5730_, v___y_5731_);
return v___x_6024_;
}
else
{
uint32_t v___x_6025_; uint32_t v___x_6026_; 
v___x_6025_ = 4194304;
v___x_6026_ = lean_uint32_lor(v___y_5731_, v___x_6025_);
return v___x_6026_;
}
}
v___jp_6027_:
{
uint32_t v___x_6028_; uint32_t v___x_6029_; uint32_t v___x_6030_; uint32_t v___x_6031_; uint8_t v___x_6032_; 
v___x_6028_ = 23;
v___x_6029_ = lean_uint32_shift_right(v___y_5731_, v___x_6028_);
v___x_6030_ = 255;
v___x_6031_ = lean_uint32_land(v___x_6029_, v___x_6030_);
v___x_6032_ = lean_uint32_dec_eq(v___x_6031_, v___x_6030_);
if (v___x_6032_ == 0)
{
v___y_6023_ = v___x_6032_;
goto v___jp_6022_;
}
else
{
uint32_t v___x_6033_; uint32_t v___x_6034_; uint32_t v___x_6035_; uint8_t v___x_6036_; 
v___x_6033_ = 8388607;
v___x_6034_ = lean_uint32_land(v___y_5731_, v___x_6033_);
v___x_6035_ = 0;
v___x_6036_ = lean_uint32_dec_eq(v___x_6034_, v___x_6035_);
if (v___x_6036_ == 0)
{
v___y_6023_ = v___x_6032_;
goto v___jp_6022_;
}
else
{
uint32_t v___x_6037_; 
v___x_6037_ = lp_competition_Submission_FastMul_mul(v___y_5730_, v___y_5731_);
return v___x_6037_;
}
}
}
v___jp_6038_:
{
if (v___y_6039_ == 0)
{
goto v___jp_6027_;
}
else
{
uint32_t v___x_6040_; uint32_t v___x_6041_; 
v___x_6040_ = 4194304;
v___x_6041_ = lean_uint32_lor(v___y_5730_, v___x_6040_);
return v___x_6041_;
}
}
v___jp_6042_:
{
uint32_t v___x_6043_; uint32_t v___x_6044_; uint32_t v___x_6045_; uint32_t v___x_6046_; uint8_t v___x_6047_; 
v___x_6043_ = 23;
v___x_6044_ = lean_uint32_shift_right(v___y_5730_, v___x_6043_);
v___x_6045_ = 255;
v___x_6046_ = lean_uint32_land(v___x_6044_, v___x_6045_);
v___x_6047_ = lean_uint32_dec_eq(v___x_6046_, v___x_6045_);
if (v___x_6047_ == 0)
{
v___y_6039_ = v___x_6047_;
goto v___jp_6038_;
}
else
{
uint32_t v___x_6048_; uint32_t v___x_6049_; uint32_t v___x_6050_; uint8_t v___x_6051_; 
v___x_6048_ = 8388607;
v___x_6049_ = lean_uint32_land(v___y_5730_, v___x_6048_);
v___x_6050_ = 0;
v___x_6051_ = lean_uint32_dec_eq(v___x_6049_, v___x_6050_);
if (v___x_6051_ == 0)
{
v___y_6039_ = v___x_6047_;
goto v___jp_6038_;
}
else
{
goto v___jp_6027_;
}
}
}
v___jp_6052_:
{
if (v___y_6053_ == 0)
{
goto v___jp_6042_;
}
else
{
uint32_t v___x_6054_; uint32_t v___x_6055_; uint32_t v___x_6056_; uint8_t v___x_6057_; 
v___x_6054_ = 4194304;
v___x_6055_ = lean_uint32_land(v___y_5731_, v___x_6054_);
v___x_6056_ = 0;
v___x_6057_ = lean_uint32_dec_eq(v___x_6055_, v___x_6056_);
if (v___x_6057_ == 0)
{
goto v___jp_6042_;
}
else
{
uint32_t v___x_6058_; 
v___x_6058_ = lean_uint32_lor(v___y_5731_, v___x_6054_);
return v___x_6058_;
}
}
}
v___jp_6059_:
{
uint32_t v___x_6060_; uint32_t v___x_6061_; uint32_t v___x_6062_; uint32_t v___x_6063_; uint8_t v___x_6064_; 
v___x_6060_ = 23;
v___x_6061_ = lean_uint32_shift_right(v___y_5731_, v___x_6060_);
v___x_6062_ = 255;
v___x_6063_ = lean_uint32_land(v___x_6061_, v___x_6062_);
v___x_6064_ = lean_uint32_dec_eq(v___x_6063_, v___x_6062_);
if (v___x_6064_ == 0)
{
v___y_6053_ = v___x_6064_;
goto v___jp_6052_;
}
else
{
uint32_t v___x_6065_; uint32_t v___x_6066_; uint32_t v___x_6067_; uint8_t v___x_6068_; 
v___x_6065_ = 8388607;
v___x_6066_ = lean_uint32_land(v___y_5731_, v___x_6065_);
v___x_6067_ = 0;
v___x_6068_ = lean_uint32_dec_eq(v___x_6066_, v___x_6067_);
if (v___x_6068_ == 0)
{
v___y_6053_ = v___x_6064_;
goto v___jp_6052_;
}
else
{
goto v___jp_6042_;
}
}
}
v___jp_6069_:
{
if (v___y_6070_ == 0)
{
goto v___jp_6059_;
}
else
{
uint32_t v___x_6071_; uint32_t v___x_6072_; uint32_t v___x_6073_; uint8_t v___x_6074_; 
v___x_6071_ = 4194304;
v___x_6072_ = lean_uint32_land(v___y_5730_, v___x_6071_);
v___x_6073_ = 0;
v___x_6074_ = lean_uint32_dec_eq(v___x_6072_, v___x_6073_);
if (v___x_6074_ == 0)
{
goto v___jp_6059_;
}
else
{
uint32_t v___x_6075_; 
v___x_6075_ = lean_uint32_lor(v___y_5730_, v___x_6071_);
return v___x_6075_;
}
}
}
v___jp_6076_:
{
float v_result_6079_; uint8_t v___x_6080_; 
v_result_6079_ = lean_float32_mul(v___y_6077_, v___y_6078_);
v___x_6080_ = lean_float32_beq(v_result_6079_, v_result_6079_);
if (v___x_6080_ == 0)
{
uint32_t v___x_6081_; uint32_t v___x_6082_; uint32_t v___x_6083_; uint32_t v___x_6084_; uint8_t v___x_6085_; 
v___x_6081_ = 23;
v___x_6082_ = lean_uint32_shift_right(v___y_5730_, v___x_6081_);
v___x_6083_ = 255;
v___x_6084_ = lean_uint32_land(v___x_6082_, v___x_6083_);
v___x_6085_ = lean_uint32_dec_eq(v___x_6084_, v___x_6083_);
if (v___x_6085_ == 0)
{
v___y_6070_ = v___x_6085_;
goto v___jp_6069_;
}
else
{
uint32_t v___x_6086_; uint32_t v___x_6087_; uint32_t v___x_6088_; uint8_t v___x_6089_; 
v___x_6086_ = 8388607;
v___x_6087_ = lean_uint32_land(v___y_5730_, v___x_6086_);
v___x_6088_ = 0;
v___x_6089_ = lean_uint32_dec_eq(v___x_6087_, v___x_6088_);
if (v___x_6089_ == 0)
{
v___y_6070_ = v___x_6085_;
goto v___jp_6069_;
}
else
{
goto v___jp_6059_;
}
}
}
else
{
uint32_t v___x_6090_; 
v___x_6090_ = lean_float32_to_bits(v_result_6079_);
return v___x_6090_;
}
}
v___jp_6091_:
{
if (v___y_6093_ == 0)
{
float v___x_6094_; 
v___x_6094_ = lean_float32_of_bits(v___y_5731_);
v___y_6077_ = v___y_6092_;
v___y_6078_ = v___x_6094_;
goto v___jp_6076_;
}
else
{
uint32_t v___x_6095_; uint32_t v___x_6096_; uint32_t v___x_6097_; uint32_t v___x_6098_; float v___x_6099_; lean_object* v___x_6100_; uint32_t v___x_6101_; uint32_t v___x_6102_; lean_object* v___x_6103_; lean_object* v___x_6104_; float v___x_6105_; float v___x_6106_; 
v___x_6095_ = 8388607;
v___x_6096_ = lean_uint32_land(v___y_5731_, v___x_6095_);
v___x_6097_ = 8388608;
v___x_6098_ = lean_uint32_lor(v___x_6096_, v___x_6097_);
v___x_6099_ = lean_uint32_to_float32(v___x_6098_);
v___x_6100_ = lp_competition_R2W01b_scaleTable;
v___x_6101_ = 23;
v___x_6102_ = lean_uint32_shift_right(v___y_5731_, v___x_6101_);
v___x_6103_ = lean_uint32_to_nat(v___x_6102_);
v___x_6104_ = lean_array_fget_borrowed(v___x_6100_, v___x_6103_);
lean_dec(v___x_6103_);
v___x_6105_ = lean_unbox_float32(v___x_6104_);
v___x_6106_ = lean_float32_mul(v___x_6099_, v___x_6105_);
v___y_6077_ = v___y_6092_;
v___y_6078_ = v___x_6106_;
goto v___jp_6076_;
}
}
v___jp_6107_:
{
uint32_t v___x_6109_; uint32_t v_a_6110_; uint32_t v___x_6111_; uint32_t v___x_6112_; uint32_t v___x_6113_; uint8_t v___x_6114_; 
v___x_6109_ = 2147483647;
v_a_6110_ = lean_uint32_land(v___y_5731_, v___x_6109_);
v___x_6111_ = 201326591;
v___x_6112_ = 1;
v___x_6113_ = lean_uint32_sub(v_a_6110_, v___x_6112_);
v___x_6114_ = lean_uint32_dec_le(v___x_6111_, v___x_6113_);
if (v___x_6114_ == 0)
{
v___y_6092_ = v___y_6108_;
v___y_6093_ = v___x_6114_;
goto v___jp_6091_;
}
else
{
uint32_t v___x_6115_; uint8_t v___x_6116_; 
v___x_6115_ = 2139095040;
v___x_6116_ = lean_uint32_dec_lt(v_a_6110_, v___x_6115_);
v___y_6092_ = v___y_6108_;
v___y_6093_ = v___x_6116_;
goto v___jp_6091_;
}
}
v___jp_6117_:
{
uint32_t v___x_6119_; uint32_t v___x_6120_; 
v___x_6119_ = 8388608;
v___x_6120_ = lean_uint32_lor(v___y_6118_, v___x_6119_);
return v___x_6120_;
}
v___jp_6121_:
{
uint32_t v___x_6123_; uint32_t v___x_6124_; 
v___x_6123_ = 8388608;
v___x_6124_ = lean_uint32_lor(v___y_6122_, v___x_6123_);
return v___x_6124_;
}
v___jp_6125_:
{
uint32_t v___x_6129_; uint32_t v___x_6130_; 
v___x_6129_ = lean_uint32_land(v___y_6127_, v___y_6126_);
v___x_6130_ = lean_uint32_lor(v___y_6128_, v___x_6129_);
return v___x_6130_;
}
v___jp_6131_:
{
uint8_t v___x_6136_; 
v___x_6136_ = lean_uint64_dec_eq(v___y_6135_, v___y_6133_);
if (v___x_6136_ == 0)
{
uint64_t v___x_6137_; uint8_t v___x_6138_; 
v___x_6137_ = 8388608ULL;
v___x_6138_ = lean_uint64_dec_eq(v___y_6135_, v___x_6137_);
if (v___x_6138_ == 0)
{
uint32_t v___x_6139_; 
v___x_6139_ = lean_uint64_to_uint32(v___y_6135_);
if (v___y_6134_ == 0)
{
uint32_t v___x_6140_; 
v___x_6140_ = 0;
v___y_6126_ = v___y_6132_;
v___y_6127_ = v___x_6139_;
v___y_6128_ = v___x_6140_;
goto v___jp_6125_;
}
else
{
uint32_t v___x_6141_; 
v___x_6141_ = 2147483648;
v___y_6126_ = v___y_6132_;
v___y_6127_ = v___x_6139_;
v___y_6128_ = v___x_6141_;
goto v___jp_6125_;
}
}
else
{
if (v___y_6134_ == 0)
{
uint32_t v___x_6142_; 
v___x_6142_ = 0;
v___y_6118_ = v___x_6142_;
goto v___jp_6117_;
}
else
{
uint32_t v___x_6143_; 
v___x_6143_ = 2147483648;
v___y_6118_ = v___x_6143_;
goto v___jp_6117_;
}
}
}
else
{
if (v___y_6134_ == 0)
{
uint32_t v___x_6144_; 
v___x_6144_ = 0;
return v___x_6144_;
}
else
{
uint32_t v___x_6145_; 
v___x_6145_ = 2147483648;
return v___x_6145_;
}
}
}
v___jp_6146_:
{
uint32_t v___x_6150_; uint32_t v___x_6151_; 
v___x_6150_ = lean_uint32_land(v___y_6148_, v___y_6147_);
v___x_6151_ = lean_uint32_lor(v___y_6149_, v___x_6150_);
return v___x_6151_;
}
v___jp_6152_:
{
uint8_t v___x_6157_; 
v___x_6157_ = lean_uint64_dec_eq(v___y_6156_, v___y_6154_);
if (v___x_6157_ == 0)
{
uint64_t v___x_6158_; uint8_t v___x_6159_; 
v___x_6158_ = 8388608ULL;
v___x_6159_ = lean_uint64_dec_eq(v___y_6156_, v___x_6158_);
if (v___x_6159_ == 0)
{
uint32_t v___x_6160_; 
v___x_6160_ = lean_uint64_to_uint32(v___y_6156_);
if (v___y_6155_ == 0)
{
uint32_t v___x_6161_; 
v___x_6161_ = 0;
v___y_6147_ = v___y_6153_;
v___y_6148_ = v___x_6160_;
v___y_6149_ = v___x_6161_;
goto v___jp_6146_;
}
else
{
uint32_t v___x_6162_; 
v___x_6162_ = 2147483648;
v___y_6147_ = v___y_6153_;
v___y_6148_ = v___x_6160_;
v___y_6149_ = v___x_6162_;
goto v___jp_6146_;
}
}
else
{
if (v___y_6155_ == 0)
{
uint32_t v___x_6163_; 
v___x_6163_ = 0;
v___y_6122_ = v___x_6163_;
goto v___jp_6121_;
}
else
{
uint32_t v___x_6164_; 
v___x_6164_ = 2147483648;
v___y_6122_ = v___x_6164_;
goto v___jp_6121_;
}
}
}
else
{
if (v___y_6155_ == 0)
{
uint32_t v___x_6165_; 
v___x_6165_ = 0;
return v___x_6165_;
}
else
{
uint32_t v___x_6166_; 
v___x_6166_ = 2147483648;
return v___x_6166_;
}
}
}
v___jp_6169_:
{
if (v___y_6170_ == 0)
{
float v___x_6171_; 
v___x_6171_ = lean_float32_of_bits(v___y_5730_);
v___y_5818_ = v___x_6171_;
goto v___jp_5817_;
}
else
{
uint32_t v___x_6172_; uint32_t v___x_6173_; uint32_t v___x_6174_; uint32_t v___x_6175_; float v___x_6176_; lean_object* v___x_6177_; lean_object* v___x_6178_; lean_object* v___x_6179_; float v___x_6180_; float v___x_6181_; 
v___x_6172_ = 8388607;
v___x_6173_ = lean_uint32_land(v___y_5730_, v___x_6172_);
v___x_6174_ = 8388608;
v___x_6175_ = lean_uint32_lor(v___x_6173_, v___x_6174_);
v___x_6176_ = lean_uint32_to_float32(v___x_6175_);
v___x_6177_ = lp_competition_R2W01b_scaleTable;
v___x_6178_ = lean_uint32_to_nat(v___x_6168_);
v___x_6179_ = lean_array_fget_borrowed(v___x_6177_, v___x_6178_);
lean_dec(v___x_6178_);
v___x_6180_ = lean_unbox_float32(v___x_6179_);
v___x_6181_ = lean_float32_mul(v___x_6176_, v___x_6180_);
v___y_5818_ = v___x_6181_;
goto v___jp_5817_;
}
}
v___jp_6182_:
{
if (v___y_6183_ == 0)
{
float v___x_6184_; 
v___x_6184_ = lean_float32_of_bits(v___y_5730_);
v___y_5963_ = v___x_6184_;
goto v___jp_5962_;
}
else
{
uint32_t v___x_6185_; uint32_t v___x_6186_; uint32_t v___x_6187_; uint32_t v___x_6188_; float v___x_6189_; lean_object* v___x_6190_; lean_object* v___x_6191_; lean_object* v___x_6192_; float v___x_6193_; float v___x_6194_; 
v___x_6185_ = 8388607;
v___x_6186_ = lean_uint32_land(v___y_5730_, v___x_6185_);
v___x_6187_ = 8388608;
v___x_6188_ = lean_uint32_lor(v___x_6186_, v___x_6187_);
v___x_6189_ = lean_uint32_to_float32(v___x_6188_);
v___x_6190_ = lp_competition_R2W01b_scaleTable;
v___x_6191_ = lean_uint32_to_nat(v___x_6168_);
v___x_6192_ = lean_array_fget_borrowed(v___x_6190_, v___x_6191_);
lean_dec(v___x_6191_);
v___x_6193_ = lean_unbox_float32(v___x_6192_);
v___x_6194_ = lean_float32_mul(v___x_6189_, v___x_6193_);
v___y_5963_ = v___x_6194_;
goto v___jp_5962_;
}
}
v___jp_6195_:
{
if (v___y_6196_ == 0)
{
float v___x_6197_; 
v___x_6197_ = lean_float32_of_bits(v___y_5730_);
v___y_6108_ = v___x_6197_;
goto v___jp_6107_;
}
else
{
uint32_t v___x_6198_; uint32_t v___x_6199_; uint32_t v___x_6200_; uint32_t v___x_6201_; float v___x_6202_; lean_object* v___x_6203_; lean_object* v___x_6204_; lean_object* v___x_6205_; float v___x_6206_; float v___x_6207_; 
v___x_6198_ = 8388607;
v___x_6199_ = lean_uint32_land(v___y_5730_, v___x_6198_);
v___x_6200_ = 8388608;
v___x_6201_ = lean_uint32_lor(v___x_6199_, v___x_6200_);
v___x_6202_ = lean_uint32_to_float32(v___x_6201_);
v___x_6203_ = lp_competition_R2W01b_scaleTable;
v___x_6204_ = lean_uint32_to_nat(v___x_6168_);
v___x_6205_ = lean_array_fget_borrowed(v___x_6203_, v___x_6204_);
lean_dec(v___x_6204_);
v___x_6206_ = lean_unbox_float32(v___x_6205_);
v___x_6207_ = lean_float32_mul(v___x_6202_, v___x_6206_);
v___y_6108_ = v___x_6207_;
goto v___jp_6107_;
}
}
v___jp_6209_:
{
uint32_t v___x_6214_; uint32_t v___x_6215_; uint32_t v___x_6216_; uint32_t v___x_6217_; uint32_t v___x_6218_; 
v___x_6214_ = lean_uint32_land(v___y_6212_, v___x_6208_);
v___x_6215_ = lean_uint32_shift_left(v___x_6214_, v___x_6167_);
v___x_6216_ = lean_uint32_lor(v___y_6213_, v___x_6215_);
v___x_6217_ = lean_uint32_land(v___y_6210_, v___y_6211_);
v___x_6218_ = lean_uint32_lor(v___x_6216_, v___x_6217_);
return v___x_6218_;
}
v___jp_6219_:
{
if (v___y_6222_ == 0)
{
uint32_t v___x_6224_; 
v___x_6224_ = 0;
v___y_6210_ = v___y_6223_;
v___y_6211_ = v___y_6220_;
v___y_6212_ = v___y_6221_;
v___y_6213_ = v___x_6224_;
goto v___jp_6209_;
}
else
{
uint32_t v___x_6225_; 
v___x_6225_ = 2147483648;
v___y_6210_ = v___y_6223_;
v___y_6211_ = v___y_6220_;
v___y_6212_ = v___y_6221_;
v___y_6213_ = v___x_6225_;
goto v___jp_6209_;
}
}
v___jp_6226_:
{
uint64_t v___x_6232_; uint64_t v_encodedExponent_6233_; uint32_t v___x_6234_; uint64_t v___x_6235_; uint8_t v___x_6236_; 
v___x_6232_ = 171ULL;
v_encodedExponent_6233_ = lean_uint64_sub(v___y_6229_, v___x_6232_);
v___x_6234_ = lean_uint64_to_uint32(v_encodedExponent_6233_);
v___x_6235_ = 8388608ULL;
v___x_6236_ = lean_uint64_dec_lt(v___y_6231_, v___x_6235_);
if (v___x_6236_ == 0)
{
uint64_t v___x_6237_; uint32_t v___x_6238_; 
v___x_6237_ = lean_uint64_sub(v___y_6231_, v___x_6235_);
v___x_6238_ = lean_uint64_to_uint32(v___x_6237_);
v___y_6220_ = v___y_6227_;
v___y_6221_ = v___x_6234_;
v___y_6222_ = v___y_6230_;
v___y_6223_ = v___x_6238_;
goto v___jp_6219_;
}
else
{
uint32_t v___x_6239_; 
v___x_6239_ = lean_uint64_to_uint32(v___y_6228_);
v___y_6220_ = v___y_6227_;
v___y_6221_ = v___x_6234_;
v___y_6222_ = v___y_6230_;
v___y_6223_ = v___x_6239_;
goto v___jp_6219_;
}
}
v___jp_6240_:
{
uint64_t v___x_6247_; uint8_t v___x_6248_; 
v___x_6247_ = 425ULL;
v___x_6248_ = lean_uint64_dec_lt(v___x_6247_, v___y_6246_);
if (v___x_6248_ == 0)
{
if (v___y_6245_ == 0)
{
v___y_6227_ = v___y_6241_;
v___y_6228_ = v___y_6243_;
v___y_6229_ = v___y_6246_;
v___y_6230_ = v___y_6244_;
v___y_6231_ = v___y_6242_;
goto v___jp_6226_;
}
else
{
uint64_t v___x_6249_; 
v___x_6249_ = 8388608ULL;
v___y_6227_ = v___y_6241_;
v___y_6228_ = v___y_6243_;
v___y_6229_ = v___y_6246_;
v___y_6230_ = v___y_6244_;
v___y_6231_ = v___x_6249_;
goto v___jp_6226_;
}
}
else
{
if (v___y_6244_ == 0)
{
uint32_t v___x_6250_; 
v___x_6250_ = 2139095040;
return v___x_6250_;
}
else
{
uint32_t v___x_6251_; 
v___x_6251_ = 4286578688;
return v___x_6251_;
}
}
}
v___jp_6252_:
{
uint64_t v___x_6258_; uint8_t v_carry_6259_; 
v___x_6258_ = 16777216ULL;
v_carry_6259_ = lean_uint64_dec_eq(v___y_6257_, v___x_6258_);
if (v_carry_6259_ == 0)
{
v___y_6241_ = v___y_6253_;
v___y_6242_ = v___y_6257_;
v___y_6243_ = v___y_6255_;
v___y_6244_ = v___y_6256_;
v___y_6245_ = v_carry_6259_;
v___y_6246_ = v___y_6254_;
goto v___jp_6240_;
}
else
{
uint64_t v___x_6260_; uint64_t v___x_6261_; 
v___x_6260_ = 1ULL;
v___x_6261_ = lean_uint64_add(v___y_6254_, v___x_6260_);
v___y_6241_ = v___y_6253_;
v___y_6242_ = v___y_6257_;
v___y_6243_ = v___y_6255_;
v___y_6244_ = v___y_6256_;
v___y_6245_ = v_carry_6259_;
v___y_6246_ = v___x_6261_;
goto v___jp_6240_;
}
}
v___jp_6262_:
{
uint64_t v_position_6269_; uint64_t v___x_6270_; uint8_t v___x_6271_; 
v_position_6269_ = lean_uint64_add(v___y_6268_, v___y_6265_);
v___x_6270_ = 172ULL;
v___x_6271_ = lean_uint64_dec_lt(v_position_6269_, v___x_6270_);
if (v___x_6271_ == 0)
{
uint64_t v___x_6272_; uint8_t v___x_6273_; 
v___x_6272_ = 23ULL;
v___x_6273_ = lean_uint64_dec_lt(v___y_6268_, v___x_6272_);
if (v___x_6273_ == 0)
{
uint64_t v___x_6274_; uint8_t v___x_6275_; 
v___x_6274_ = lean_uint64_sub(v___y_6268_, v___x_6272_);
v___x_6275_ = lean_uint64_dec_eq(v___x_6274_, v___y_6266_);
if (v___x_6275_ == 0)
{
uint64_t v___x_6276_; uint8_t v___x_6277_; 
v___x_6276_ = 64ULL;
v___x_6277_ = lean_uint64_dec_lt(v___x_6274_, v___x_6276_);
if (v___x_6277_ == 0)
{
uint8_t v___x_6278_; 
v___x_6278_ = lean_uint64_dec_eq(v___x_6274_, v___x_6276_);
if (v___x_6278_ == 0)
{
v___y_6253_ = v___y_6264_;
v___y_6254_ = v_position_6269_;
v___y_6255_ = v___y_6266_;
v___y_6256_ = v___y_6267_;
v___y_6257_ = v___y_6266_;
goto v___jp_6252_;
}
else
{
uint64_t v___x_6279_; uint8_t v___x_6280_; 
v___x_6279_ = 9223372036854775808ULL;
v___x_6280_ = lean_uint64_dec_lt(v___x_6279_, v___y_6263_);
if (v___x_6280_ == 0)
{
v___y_6253_ = v___y_6264_;
v___y_6254_ = v_position_6269_;
v___y_6255_ = v___y_6266_;
v___y_6256_ = v___y_6267_;
v___y_6257_ = v___y_6266_;
goto v___jp_6252_;
}
else
{
uint64_t v___x_6281_; 
v___x_6281_ = 1ULL;
v___y_6253_ = v___y_6264_;
v___y_6254_ = v_position_6269_;
v___y_6255_ = v___y_6266_;
v___y_6256_ = v___y_6267_;
v___y_6257_ = v___x_6281_;
goto v___jp_6252_;
}
}
}
else
{
uint64_t v_quotient_6282_; uint64_t v___x_6283_; uint64_t v___x_6284_; uint64_t v___x_6285_; uint64_t v_remainder_6286_; uint64_t v___x_6287_; uint64_t v_half_6288_; uint8_t v___x_6289_; 
v_quotient_6282_ = lean_uint64_shift_right(v___y_6263_, v___x_6274_);
v___x_6283_ = 1ULL;
v___x_6284_ = lean_uint64_shift_left(v___x_6283_, v___x_6274_);
v___x_6285_ = lean_uint64_sub(v___x_6284_, v___x_6283_);
v_remainder_6286_ = lean_uint64_land(v___y_6263_, v___x_6285_);
v___x_6287_ = lean_uint64_sub(v___x_6274_, v___x_6283_);
v_half_6288_ = lean_uint64_shift_left(v___x_6283_, v___x_6287_);
v___x_6289_ = lean_uint64_dec_lt(v_remainder_6286_, v_half_6288_);
if (v___x_6289_ == 0)
{
uint8_t v___x_6290_; 
v___x_6290_ = lean_uint64_dec_lt(v_half_6288_, v_remainder_6286_);
if (v___x_6290_ == 0)
{
uint64_t v___x_6291_; uint8_t v___x_6292_; 
v___x_6291_ = lean_uint64_land(v_quotient_6282_, v___x_6283_);
v___x_6292_ = lean_uint64_dec_eq(v___x_6291_, v___y_6266_);
if (v___x_6292_ == 0)
{
uint64_t v___x_6293_; 
v___x_6293_ = lean_uint64_add(v_quotient_6282_, v___x_6283_);
v___y_6253_ = v___y_6264_;
v___y_6254_ = v_position_6269_;
v___y_6255_ = v___y_6266_;
v___y_6256_ = v___y_6267_;
v___y_6257_ = v___x_6293_;
goto v___jp_6252_;
}
else
{
v___y_6253_ = v___y_6264_;
v___y_6254_ = v_position_6269_;
v___y_6255_ = v___y_6266_;
v___y_6256_ = v___y_6267_;
v___y_6257_ = v_quotient_6282_;
goto v___jp_6252_;
}
}
else
{
uint64_t v___x_6294_; 
v___x_6294_ = lean_uint64_add(v_quotient_6282_, v___x_6283_);
v___y_6253_ = v___y_6264_;
v___y_6254_ = v_position_6269_;
v___y_6255_ = v___y_6266_;
v___y_6256_ = v___y_6267_;
v___y_6257_ = v___x_6294_;
goto v___jp_6252_;
}
}
else
{
v___y_6253_ = v___y_6264_;
v___y_6254_ = v_position_6269_;
v___y_6255_ = v___y_6266_;
v___y_6256_ = v___y_6267_;
v___y_6257_ = v_quotient_6282_;
goto v___jp_6252_;
}
}
}
else
{
v___y_6253_ = v___y_6264_;
v___y_6254_ = v_position_6269_;
v___y_6255_ = v___y_6266_;
v___y_6256_ = v___y_6267_;
v___y_6257_ = v___y_6263_;
goto v___jp_6252_;
}
}
else
{
uint64_t v___x_6295_; uint64_t v___x_6296_; 
v___x_6295_ = lean_uint64_sub(v___x_6272_, v___y_6268_);
v___x_6296_ = lean_uint64_shift_left(v___y_6263_, v___x_6295_);
v___y_6253_ = v___y_6264_;
v___y_6254_ = v_position_6269_;
v___y_6255_ = v___y_6266_;
v___y_6256_ = v___y_6267_;
v___y_6257_ = v___x_6296_;
goto v___jp_6252_;
}
}
else
{
uint64_t v___x_6297_; uint8_t v___x_6298_; 
v___x_6297_ = 149ULL;
v___x_6298_ = lean_uint64_dec_lt(v___y_6265_, v___x_6297_);
if (v___x_6298_ == 0)
{
uint64_t v___x_6299_; uint64_t v___x_6300_; 
v___x_6299_ = lean_uint64_sub(v___y_6265_, v___x_6297_);
v___x_6300_ = lean_uint64_shift_left(v___y_6263_, v___x_6299_);
v___y_5842_ = v___y_6264_;
v___y_5843_ = v___y_6266_;
v___y_5844_ = v___y_6267_;
v___y_5845_ = v___x_6300_;
goto v___jp_5841_;
}
else
{
uint64_t v___x_6301_; uint8_t v___x_6302_; 
v___x_6301_ = lean_uint64_sub(v___x_6297_, v___y_6265_);
v___x_6302_ = lean_uint64_dec_eq(v___x_6301_, v___y_6266_);
if (v___x_6302_ == 0)
{
uint64_t v___x_6303_; uint8_t v___x_6304_; 
v___x_6303_ = 64ULL;
v___x_6304_ = lean_uint64_dec_lt(v___x_6301_, v___x_6303_);
if (v___x_6304_ == 0)
{
uint8_t v___x_6305_; 
v___x_6305_ = lean_uint64_dec_eq(v___x_6301_, v___x_6303_);
if (v___x_6305_ == 0)
{
v___y_5842_ = v___y_6264_;
v___y_5843_ = v___y_6266_;
v___y_5844_ = v___y_6267_;
v___y_5845_ = v___y_6266_;
goto v___jp_5841_;
}
else
{
uint64_t v___x_6306_; uint8_t v___x_6307_; 
v___x_6306_ = 9223372036854775808ULL;
v___x_6307_ = lean_uint64_dec_lt(v___x_6306_, v___y_6263_);
if (v___x_6307_ == 0)
{
v___y_5842_ = v___y_6264_;
v___y_5843_ = v___y_6266_;
v___y_5844_ = v___y_6267_;
v___y_5845_ = v___y_6266_;
goto v___jp_5841_;
}
else
{
uint64_t v___x_6308_; 
v___x_6308_ = 1ULL;
v___y_5842_ = v___y_6264_;
v___y_5843_ = v___y_6266_;
v___y_5844_ = v___y_6267_;
v___y_5845_ = v___x_6308_;
goto v___jp_5841_;
}
}
}
else
{
uint64_t v_quotient_6309_; uint64_t v___x_6310_; uint64_t v___x_6311_; uint64_t v___x_6312_; uint64_t v_remainder_6313_; uint64_t v___x_6314_; uint64_t v_half_6315_; uint8_t v___x_6316_; 
v_quotient_6309_ = lean_uint64_shift_right(v___y_6263_, v___x_6301_);
v___x_6310_ = 1ULL;
v___x_6311_ = lean_uint64_shift_left(v___x_6310_, v___x_6301_);
v___x_6312_ = lean_uint64_sub(v___x_6311_, v___x_6310_);
v_remainder_6313_ = lean_uint64_land(v___y_6263_, v___x_6312_);
v___x_6314_ = lean_uint64_sub(v___x_6301_, v___x_6310_);
v_half_6315_ = lean_uint64_shift_left(v___x_6310_, v___x_6314_);
v___x_6316_ = lean_uint64_dec_lt(v_remainder_6313_, v_half_6315_);
if (v___x_6316_ == 0)
{
uint8_t v___x_6317_; 
v___x_6317_ = lean_uint64_dec_lt(v_half_6315_, v_remainder_6313_);
if (v___x_6317_ == 0)
{
uint64_t v___x_6318_; uint8_t v___x_6319_; 
v___x_6318_ = lean_uint64_land(v_quotient_6309_, v___x_6310_);
v___x_6319_ = lean_uint64_dec_eq(v___x_6318_, v___y_6266_);
if (v___x_6319_ == 0)
{
uint64_t v___x_6320_; 
v___x_6320_ = lean_uint64_add(v_quotient_6309_, v___x_6310_);
v___y_5842_ = v___y_6264_;
v___y_5843_ = v___y_6266_;
v___y_5844_ = v___y_6267_;
v___y_5845_ = v___x_6320_;
goto v___jp_5841_;
}
else
{
v___y_5842_ = v___y_6264_;
v___y_5843_ = v___y_6266_;
v___y_5844_ = v___y_6267_;
v___y_5845_ = v_quotient_6309_;
goto v___jp_5841_;
}
}
else
{
uint64_t v___x_6321_; 
v___x_6321_ = lean_uint64_add(v_quotient_6309_, v___x_6310_);
v___y_5842_ = v___y_6264_;
v___y_5843_ = v___y_6266_;
v___y_5844_ = v___y_6267_;
v___y_5845_ = v___x_6321_;
goto v___jp_5841_;
}
}
else
{
v___y_5842_ = v___y_6264_;
v___y_5843_ = v___y_6266_;
v___y_5844_ = v___y_6267_;
v___y_5845_ = v_quotient_6309_;
goto v___jp_5841_;
}
}
}
else
{
v___y_5842_ = v___y_6264_;
v___y_5843_ = v___y_6266_;
v___y_5844_ = v___y_6267_;
v___y_5845_ = v___y_6263_;
goto v___jp_5841_;
}
}
}
}
v___jp_6322_:
{
uint64_t v___x_6330_; uint64_t v___x_6331_; uint8_t v___x_6332_; 
v___x_6330_ = 1ULL;
v___x_6331_ = lean_uint64_shift_right(v___y_6327_, v___x_6330_);
v___x_6332_ = lean_uint64_dec_eq(v___x_6331_, v___y_6326_);
if (v___x_6332_ == 0)
{
uint64_t v___x_6333_; 
v___x_6333_ = lean_uint64_add(v___y_6329_, v___x_6330_);
v___y_6263_ = v___y_6323_;
v___y_6264_ = v___y_6324_;
v___y_6265_ = v___y_6325_;
v___y_6266_ = v___y_6326_;
v___y_6267_ = v___y_6328_;
v___y_6268_ = v___x_6333_;
goto v___jp_6262_;
}
else
{
v___y_6263_ = v___y_6323_;
v___y_6264_ = v___y_6324_;
v___y_6265_ = v___y_6325_;
v___y_6266_ = v___y_6326_;
v___y_6267_ = v___y_6328_;
v___y_6268_ = v___y_6329_;
goto v___jp_6262_;
}
}
v___jp_6334_:
{
uint64_t v___x_6344_; uint8_t v___x_6345_; 
v___x_6344_ = lean_uint64_shift_right(v___y_6338_, v___y_6340_);
v___x_6345_ = lean_uint64_dec_eq(v___x_6344_, v___y_6339_);
if (v___x_6345_ == 0)
{
uint64_t v___x_6346_; 
v___x_6346_ = lean_uint64_add(v___y_6341_, v___y_6340_);
v___y_6323_ = v___y_6335_;
v___y_6324_ = v___y_6336_;
v___y_6325_ = v___y_6337_;
v___y_6326_ = v___y_6339_;
v___y_6327_ = v___y_6343_;
v___y_6328_ = v___y_6342_;
v___y_6329_ = v___x_6346_;
goto v___jp_6322_;
}
else
{
v___y_6323_ = v___y_6335_;
v___y_6324_ = v___y_6336_;
v___y_6325_ = v___y_6337_;
v___y_6326_ = v___y_6339_;
v___y_6327_ = v___y_6343_;
v___y_6328_ = v___y_6342_;
v___y_6329_ = v___y_6341_;
goto v___jp_6322_;
}
}
v___jp_6347_:
{
uint64_t v___x_6355_; uint64_t v___x_6356_; uint8_t v___x_6357_; 
v___x_6355_ = 2ULL;
v___x_6356_ = lean_uint64_shift_right(v___y_6352_, v___x_6355_);
v___x_6357_ = lean_uint64_dec_eq(v___x_6356_, v___y_6351_);
if (v___x_6357_ == 0)
{
v___y_6335_ = v___y_6348_;
v___y_6336_ = v___y_6349_;
v___y_6337_ = v___y_6350_;
v___y_6338_ = v___y_6352_;
v___y_6339_ = v___y_6351_;
v___y_6340_ = v___x_6355_;
v___y_6341_ = v___y_6354_;
v___y_6342_ = v___y_6353_;
v___y_6343_ = v___x_6356_;
goto v___jp_6334_;
}
else
{
v___y_6335_ = v___y_6348_;
v___y_6336_ = v___y_6349_;
v___y_6337_ = v___y_6350_;
v___y_6338_ = v___y_6352_;
v___y_6339_ = v___y_6351_;
v___y_6340_ = v___x_6355_;
v___y_6341_ = v___y_6354_;
v___y_6342_ = v___y_6353_;
v___y_6343_ = v___y_6352_;
goto v___jp_6334_;
}
}
v___jp_6358_:
{
uint64_t v___x_6368_; uint8_t v___x_6369_; 
v___x_6368_ = lean_uint64_shift_right(v___y_6360_, v___y_6362_);
v___x_6369_ = lean_uint64_dec_eq(v___x_6368_, v___y_6364_);
if (v___x_6369_ == 0)
{
uint64_t v___x_6370_; 
v___x_6370_ = lean_uint64_add(v___y_6365_, v___y_6362_);
v___y_6348_ = v___y_6359_;
v___y_6349_ = v___y_6361_;
v___y_6350_ = v___y_6363_;
v___y_6351_ = v___y_6364_;
v___y_6352_ = v___y_6367_;
v___y_6353_ = v___y_6366_;
v___y_6354_ = v___x_6370_;
goto v___jp_6347_;
}
else
{
v___y_6348_ = v___y_6359_;
v___y_6349_ = v___y_6361_;
v___y_6350_ = v___y_6363_;
v___y_6351_ = v___y_6364_;
v___y_6352_ = v___y_6367_;
v___y_6353_ = v___y_6366_;
v___y_6354_ = v___y_6365_;
goto v___jp_6347_;
}
}
v___jp_6371_:
{
uint64_t v___x_6379_; uint64_t v___x_6380_; uint8_t v___x_6381_; 
v___x_6379_ = 4ULL;
v___x_6380_ = lean_uint64_shift_right(v___y_6373_, v___x_6379_);
v___x_6381_ = lean_uint64_dec_eq(v___x_6380_, v___y_6376_);
if (v___x_6381_ == 0)
{
v___y_6359_ = v___y_6372_;
v___y_6360_ = v___y_6373_;
v___y_6361_ = v___y_6374_;
v___y_6362_ = v___x_6379_;
v___y_6363_ = v___y_6375_;
v___y_6364_ = v___y_6376_;
v___y_6365_ = v___y_6378_;
v___y_6366_ = v___y_6377_;
v___y_6367_ = v___x_6380_;
goto v___jp_6358_;
}
else
{
v___y_6359_ = v___y_6372_;
v___y_6360_ = v___y_6373_;
v___y_6361_ = v___y_6374_;
v___y_6362_ = v___x_6379_;
v___y_6363_ = v___y_6375_;
v___y_6364_ = v___y_6376_;
v___y_6365_ = v___y_6378_;
v___y_6366_ = v___y_6377_;
v___y_6367_ = v___y_6373_;
goto v___jp_6358_;
}
}
v___jp_6382_:
{
uint64_t v___x_6392_; uint8_t v___x_6393_; 
v___x_6392_ = lean_uint64_shift_right(v___y_6388_, v___y_6387_);
v___x_6393_ = lean_uint64_dec_eq(v___x_6392_, v___y_6386_);
if (v___x_6393_ == 0)
{
uint64_t v___x_6394_; 
v___x_6394_ = lean_uint64_add(v___y_6390_, v___y_6387_);
v___y_6372_ = v___y_6383_;
v___y_6373_ = v___y_6391_;
v___y_6374_ = v___y_6384_;
v___y_6375_ = v___y_6385_;
v___y_6376_ = v___y_6386_;
v___y_6377_ = v___y_6389_;
v___y_6378_ = v___x_6394_;
goto v___jp_6371_;
}
else
{
v___y_6372_ = v___y_6383_;
v___y_6373_ = v___y_6391_;
v___y_6374_ = v___y_6384_;
v___y_6375_ = v___y_6385_;
v___y_6376_ = v___y_6386_;
v___y_6377_ = v___y_6389_;
v___y_6378_ = v___y_6390_;
goto v___jp_6371_;
}
}
v___jp_6395_:
{
uint64_t v___x_6403_; uint64_t v___x_6404_; uint8_t v___x_6405_; 
v___x_6403_ = 8ULL;
v___x_6404_ = lean_uint64_shift_right(v___y_6400_, v___x_6403_);
v___x_6405_ = lean_uint64_dec_eq(v___x_6404_, v___y_6399_);
if (v___x_6405_ == 0)
{
v___y_6383_ = v___y_6396_;
v___y_6384_ = v___y_6397_;
v___y_6385_ = v___y_6398_;
v___y_6386_ = v___y_6399_;
v___y_6387_ = v___x_6403_;
v___y_6388_ = v___y_6400_;
v___y_6389_ = v___y_6401_;
v___y_6390_ = v___y_6402_;
v___y_6391_ = v___x_6404_;
goto v___jp_6382_;
}
else
{
v___y_6383_ = v___y_6396_;
v___y_6384_ = v___y_6397_;
v___y_6385_ = v___y_6398_;
v___y_6386_ = v___y_6399_;
v___y_6387_ = v___x_6403_;
v___y_6388_ = v___y_6400_;
v___y_6389_ = v___y_6401_;
v___y_6390_ = v___y_6402_;
v___y_6391_ = v___y_6400_;
goto v___jp_6382_;
}
}
v___jp_6406_:
{
uint64_t v___x_6416_; uint8_t v___x_6417_; 
v___x_6416_ = lean_uint64_shift_right(v___y_6409_, v___y_6410_);
v___x_6417_ = lean_uint64_dec_eq(v___x_6416_, v___y_6412_);
if (v___x_6417_ == 0)
{
uint64_t v___x_6418_; 
v___x_6418_ = lean_uint64_add(v___y_6413_, v___y_6410_);
v___y_6396_ = v___y_6407_;
v___y_6397_ = v___y_6408_;
v___y_6398_ = v___y_6411_;
v___y_6399_ = v___y_6412_;
v___y_6400_ = v___y_6415_;
v___y_6401_ = v___y_6414_;
v___y_6402_ = v___x_6418_;
goto v___jp_6395_;
}
else
{
v___y_6396_ = v___y_6407_;
v___y_6397_ = v___y_6408_;
v___y_6398_ = v___y_6411_;
v___y_6399_ = v___y_6412_;
v___y_6400_ = v___y_6415_;
v___y_6401_ = v___y_6414_;
v___y_6402_ = v___y_6413_;
goto v___jp_6395_;
}
}
v___jp_6419_:
{
uint64_t v___x_6427_; uint64_t v___x_6428_; uint8_t v___x_6429_; 
v___x_6427_ = 16ULL;
v___x_6428_ = lean_uint64_shift_right(v___y_6422_, v___x_6427_);
v___x_6429_ = lean_uint64_dec_eq(v___x_6428_, v___y_6424_);
if (v___x_6429_ == 0)
{
v___y_6407_ = v___y_6420_;
v___y_6408_ = v___y_6421_;
v___y_6409_ = v___y_6422_;
v___y_6410_ = v___x_6427_;
v___y_6411_ = v___y_6423_;
v___y_6412_ = v___y_6424_;
v___y_6413_ = v___y_6426_;
v___y_6414_ = v___y_6425_;
v___y_6415_ = v___x_6428_;
goto v___jp_6406_;
}
else
{
v___y_6407_ = v___y_6420_;
v___y_6408_ = v___y_6421_;
v___y_6409_ = v___y_6422_;
v___y_6410_ = v___x_6427_;
v___y_6411_ = v___y_6423_;
v___y_6412_ = v___y_6424_;
v___y_6413_ = v___y_6426_;
v___y_6414_ = v___y_6425_;
v___y_6415_ = v___y_6422_;
goto v___jp_6406_;
}
}
v___jp_6430_:
{
uint64_t v___x_6438_; uint8_t v___x_6439_; 
v___x_6438_ = lean_uint64_shift_right(v___y_6431_, v___y_6434_);
v___x_6439_ = lean_uint64_dec_eq(v___x_6438_, v___y_6435_);
if (v___x_6439_ == 0)
{
v___y_6420_ = v___y_6431_;
v___y_6421_ = v___y_6432_;
v___y_6422_ = v___y_6437_;
v___y_6423_ = v___y_6433_;
v___y_6424_ = v___y_6435_;
v___y_6425_ = v___y_6436_;
v___y_6426_ = v___y_6434_;
goto v___jp_6419_;
}
else
{
v___y_6420_ = v___y_6431_;
v___y_6421_ = v___y_6432_;
v___y_6422_ = v___y_6437_;
v___y_6423_ = v___y_6433_;
v___y_6424_ = v___y_6435_;
v___y_6425_ = v___y_6436_;
v___y_6426_ = v___y_6435_;
goto v___jp_6419_;
}
}
v___jp_6440_:
{
uint64_t v___x_6445_; uint8_t v___x_6446_; 
v___x_6445_ = 0ULL;
v___x_6446_ = lean_uint64_dec_eq(v___y_6441_, v___x_6445_);
if (v___x_6446_ == 0)
{
uint64_t v___x_6447_; uint64_t v___x_6448_; uint8_t v___x_6449_; 
v___x_6447_ = 32ULL;
v___x_6448_ = lean_uint64_shift_right(v___y_6441_, v___x_6447_);
v___x_6449_ = lean_uint64_dec_eq(v___x_6448_, v___x_6445_);
if (v___x_6449_ == 0)
{
v___y_6431_ = v___y_6441_;
v___y_6432_ = v___y_6442_;
v___y_6433_ = v___y_6443_;
v___y_6434_ = v___x_6447_;
v___y_6435_ = v___x_6445_;
v___y_6436_ = v___y_6444_;
v___y_6437_ = v___x_6448_;
goto v___jp_6430_;
}
else
{
v___y_6431_ = v___y_6441_;
v___y_6432_ = v___y_6442_;
v___y_6433_ = v___y_6443_;
v___y_6434_ = v___x_6447_;
v___y_6435_ = v___x_6445_;
v___y_6436_ = v___y_6444_;
v___y_6437_ = v___y_6441_;
goto v___jp_6430_;
}
}
else
{
if (v___y_6444_ == 0)
{
uint32_t v___x_6450_; 
v___x_6450_ = 0;
return v___x_6450_;
}
else
{
uint32_t v___x_6451_; 
v___x_6451_ = 2147483648;
return v___x_6451_;
}
}
}
v___jp_6452_:
{
uint64_t v___x_6459_; uint64_t v___x_6460_; uint64_t v___x_6461_; uint8_t v___x_6462_; 
v___x_6459_ = lean_uint64_mul(v___y_6455_, v___y_6457_);
v___x_6460_ = lean_uint64_add(v___y_6454_, v___y_6458_);
v___x_6461_ = 281474976710656ULL;
v___x_6462_ = lean_uint64_dec_lt(v___x_6459_, v___x_6461_);
if (v___x_6462_ == 0)
{
v___y_6441_ = v___x_6459_;
v___y_6442_ = v___y_6453_;
v___y_6443_ = v___x_6460_;
v___y_6444_ = v___y_6456_;
goto v___jp_6440_;
}
else
{
uint64_t v___x_6463_; uint8_t v___x_6464_; 
v___x_6463_ = 123ULL;
v___x_6464_ = lean_uint64_dec_le(v___x_6460_, v___x_6463_);
if (v___x_6464_ == 0)
{
v___y_6441_ = v___x_6459_;
v___y_6442_ = v___y_6453_;
v___y_6443_ = v___x_6460_;
v___y_6444_ = v___y_6456_;
goto v___jp_6440_;
}
else
{
uint64_t v___x_6465_; uint8_t v___x_6466_; 
v___x_6465_ = 0ULL;
v___x_6466_ = lean_uint64_dec_eq(v___x_6459_, v___x_6465_);
if (v___x_6466_ == 0)
{
uint64_t v___x_6467_; uint64_t v___x_6468_; uint8_t v___x_6469_; 
v___x_6467_ = 149ULL;
v___x_6468_ = lean_uint64_sub(v___x_6467_, v___x_6460_);
v___x_6469_ = lean_uint64_dec_eq(v___x_6468_, v___x_6465_);
if (v___x_6469_ == 0)
{
uint64_t v___x_6470_; uint8_t v___x_6471_; 
v___x_6470_ = 64ULL;
v___x_6471_ = lean_uint64_dec_lt(v___x_6468_, v___x_6470_);
if (v___x_6471_ == 0)
{
uint8_t v___x_6472_; 
v___x_6472_ = lean_uint64_dec_eq(v___x_6468_, v___x_6470_);
if (v___x_6472_ == 0)
{
v___y_5863_ = v___y_6453_;
v___y_5864_ = v___x_6465_;
v___y_5865_ = v___y_6456_;
v___y_5866_ = v___x_6465_;
goto v___jp_5862_;
}
else
{
uint64_t v___x_6473_; uint8_t v___x_6474_; 
v___x_6473_ = 9223372036854775808ULL;
v___x_6474_ = lean_uint64_dec_lt(v___x_6473_, v___x_6459_);
if (v___x_6474_ == 0)
{
v___y_5863_ = v___y_6453_;
v___y_5864_ = v___x_6465_;
v___y_5865_ = v___y_6456_;
v___y_5866_ = v___x_6465_;
goto v___jp_5862_;
}
else
{
uint64_t v___x_6475_; 
v___x_6475_ = 1ULL;
v___y_5863_ = v___y_6453_;
v___y_5864_ = v___x_6465_;
v___y_5865_ = v___y_6456_;
v___y_5866_ = v___x_6475_;
goto v___jp_5862_;
}
}
}
else
{
uint64_t v_quotient_6476_; uint64_t v___x_6477_; uint64_t v___x_6478_; uint64_t v___x_6479_; uint64_t v_remainder_6480_; uint64_t v___x_6481_; uint64_t v_half_6482_; uint8_t v___x_6483_; 
v_quotient_6476_ = lean_uint64_shift_right(v___x_6459_, v___x_6468_);
v___x_6477_ = 1ULL;
v___x_6478_ = lean_uint64_shift_left(v___x_6477_, v___x_6468_);
v___x_6479_ = lean_uint64_sub(v___x_6478_, v___x_6477_);
v_remainder_6480_ = lean_uint64_land(v___x_6459_, v___x_6479_);
v___x_6481_ = lean_uint64_sub(v___x_6468_, v___x_6477_);
v_half_6482_ = lean_uint64_shift_left(v___x_6477_, v___x_6481_);
v___x_6483_ = lean_uint64_dec_lt(v_remainder_6480_, v_half_6482_);
if (v___x_6483_ == 0)
{
uint8_t v___x_6484_; 
v___x_6484_ = lean_uint64_dec_lt(v_half_6482_, v_remainder_6480_);
if (v___x_6484_ == 0)
{
uint64_t v___x_6485_; uint8_t v___x_6486_; 
v___x_6485_ = lean_uint64_land(v_quotient_6476_, v___x_6477_);
v___x_6486_ = lean_uint64_dec_eq(v___x_6485_, v___x_6465_);
if (v___x_6486_ == 0)
{
uint64_t v___x_6487_; 
v___x_6487_ = lean_uint64_add(v_quotient_6476_, v___x_6477_);
v___y_5863_ = v___y_6453_;
v___y_5864_ = v___x_6465_;
v___y_5865_ = v___y_6456_;
v___y_5866_ = v___x_6487_;
goto v___jp_5862_;
}
else
{
v___y_5863_ = v___y_6453_;
v___y_5864_ = v___x_6465_;
v___y_5865_ = v___y_6456_;
v___y_5866_ = v_quotient_6476_;
goto v___jp_5862_;
}
}
else
{
uint64_t v___x_6488_; 
v___x_6488_ = lean_uint64_add(v_quotient_6476_, v___x_6477_);
v___y_5863_ = v___y_6453_;
v___y_5864_ = v___x_6465_;
v___y_5865_ = v___y_6456_;
v___y_5866_ = v___x_6488_;
goto v___jp_5862_;
}
}
else
{
v___y_5863_ = v___y_6453_;
v___y_5864_ = v___x_6465_;
v___y_5865_ = v___y_6456_;
v___y_5866_ = v_quotient_6476_;
goto v___jp_5862_;
}
}
}
else
{
v___y_5863_ = v___y_6453_;
v___y_5864_ = v___x_6465_;
v___y_5865_ = v___y_6456_;
v___y_5866_ = v___x_6459_;
goto v___jp_5862_;
}
}
else
{
if (v___y_6456_ == 0)
{
uint32_t v___x_6489_; 
v___x_6489_ = 0;
return v___x_6489_;
}
else
{
uint32_t v___x_6490_; 
v___x_6490_ = 2147483648;
return v___x_6490_;
}
}
}
}
}
v___jp_6491_:
{
uint32_t v___x_6496_; uint32_t v___x_6497_; uint32_t v___x_6498_; uint32_t v___x_6499_; uint32_t v___x_6500_; 
v___x_6496_ = lean_uint32_land(v___y_6494_, v___x_6208_);
v___x_6497_ = lean_uint32_shift_left(v___x_6496_, v___x_6167_);
v___x_6498_ = lean_uint32_lor(v___y_6495_, v___x_6497_);
v___x_6499_ = lean_uint32_land(v___y_6493_, v___y_6492_);
v___x_6500_ = lean_uint32_lor(v___x_6498_, v___x_6499_);
return v___x_6500_;
}
v___jp_6501_:
{
if (v___y_6504_ == 0)
{
uint32_t v___x_6506_; 
v___x_6506_ = 0;
v___y_6492_ = v___y_6502_;
v___y_6493_ = v___y_6505_;
v___y_6494_ = v___y_6503_;
v___y_6495_ = v___x_6506_;
goto v___jp_6491_;
}
else
{
uint32_t v___x_6507_; 
v___x_6507_ = 2147483648;
v___y_6492_ = v___y_6502_;
v___y_6493_ = v___y_6505_;
v___y_6494_ = v___y_6503_;
v___y_6495_ = v___x_6507_;
goto v___jp_6491_;
}
}
v___jp_6508_:
{
uint64_t v___x_6514_; uint64_t v_encodedExponent_6515_; uint32_t v___x_6516_; uint64_t v___x_6517_; uint8_t v___x_6518_; 
v___x_6514_ = 171ULL;
v_encodedExponent_6515_ = lean_uint64_sub(v___y_6512_, v___x_6514_);
v___x_6516_ = lean_uint64_to_uint32(v_encodedExponent_6515_);
v___x_6517_ = 8388608ULL;
v___x_6518_ = lean_uint64_dec_lt(v___y_6513_, v___x_6517_);
if (v___x_6518_ == 0)
{
uint64_t v___x_6519_; uint32_t v___x_6520_; 
v___x_6519_ = lean_uint64_sub(v___y_6513_, v___x_6517_);
v___x_6520_ = lean_uint64_to_uint32(v___x_6519_);
v___y_6502_ = v___y_6509_;
v___y_6503_ = v___x_6516_;
v___y_6504_ = v___y_6511_;
v___y_6505_ = v___x_6520_;
goto v___jp_6501_;
}
else
{
uint32_t v___x_6521_; 
v___x_6521_ = lean_uint64_to_uint32(v___y_6510_);
v___y_6502_ = v___y_6509_;
v___y_6503_ = v___x_6516_;
v___y_6504_ = v___y_6511_;
v___y_6505_ = v___x_6521_;
goto v___jp_6501_;
}
}
v___jp_6522_:
{
uint64_t v___x_6529_; uint8_t v___x_6530_; 
v___x_6529_ = 425ULL;
v___x_6530_ = lean_uint64_dec_lt(v___x_6529_, v___y_6528_);
if (v___x_6530_ == 0)
{
if (v___y_6526_ == 0)
{
v___y_6509_ = v___y_6523_;
v___y_6510_ = v___y_6525_;
v___y_6511_ = v___y_6527_;
v___y_6512_ = v___y_6528_;
v___y_6513_ = v___y_6524_;
goto v___jp_6508_;
}
else
{
uint64_t v___x_6531_; 
v___x_6531_ = 8388608ULL;
v___y_6509_ = v___y_6523_;
v___y_6510_ = v___y_6525_;
v___y_6511_ = v___y_6527_;
v___y_6512_ = v___y_6528_;
v___y_6513_ = v___x_6531_;
goto v___jp_6508_;
}
}
else
{
if (v___y_6527_ == 0)
{
uint32_t v___x_6532_; 
v___x_6532_ = 2139095040;
return v___x_6532_;
}
else
{
uint32_t v___x_6533_; 
v___x_6533_ = 4286578688;
return v___x_6533_;
}
}
}
v___jp_6534_:
{
uint64_t v___x_6540_; uint8_t v_carry_6541_; 
v___x_6540_ = 16777216ULL;
v_carry_6541_ = lean_uint64_dec_eq(v___y_6539_, v___x_6540_);
if (v_carry_6541_ == 0)
{
v___y_6523_ = v___y_6536_;
v___y_6524_ = v___y_6539_;
v___y_6525_ = v___y_6537_;
v___y_6526_ = v_carry_6541_;
v___y_6527_ = v___y_6538_;
v___y_6528_ = v___y_6535_;
goto v___jp_6522_;
}
else
{
uint64_t v___x_6542_; uint64_t v___x_6543_; 
v___x_6542_ = 1ULL;
v___x_6543_ = lean_uint64_add(v___y_6535_, v___x_6542_);
v___y_6523_ = v___y_6536_;
v___y_6524_ = v___y_6539_;
v___y_6525_ = v___y_6537_;
v___y_6526_ = v_carry_6541_;
v___y_6527_ = v___y_6538_;
v___y_6528_ = v___x_6543_;
goto v___jp_6522_;
}
}
v___jp_6544_:
{
uint64_t v_position_6551_; uint64_t v___x_6552_; uint8_t v___x_6553_; 
v_position_6551_ = lean_uint64_add(v___y_6550_, v___y_6547_);
v___x_6552_ = 172ULL;
v___x_6553_ = lean_uint64_dec_lt(v_position_6551_, v___x_6552_);
if (v___x_6553_ == 0)
{
uint64_t v___x_6554_; uint8_t v___x_6555_; 
v___x_6554_ = 23ULL;
v___x_6555_ = lean_uint64_dec_lt(v___y_6550_, v___x_6554_);
if (v___x_6555_ == 0)
{
uint64_t v___x_6556_; uint8_t v___x_6557_; 
v___x_6556_ = lean_uint64_sub(v___y_6550_, v___x_6554_);
v___x_6557_ = lean_uint64_dec_eq(v___x_6556_, v___y_6546_);
if (v___x_6557_ == 0)
{
uint64_t v___x_6558_; uint8_t v___x_6559_; 
v___x_6558_ = 64ULL;
v___x_6559_ = lean_uint64_dec_lt(v___x_6556_, v___x_6558_);
if (v___x_6559_ == 0)
{
uint8_t v___x_6560_; 
v___x_6560_ = lean_uint64_dec_eq(v___x_6556_, v___x_6558_);
if (v___x_6560_ == 0)
{
v___y_6535_ = v_position_6551_;
v___y_6536_ = v___y_6545_;
v___y_6537_ = v___y_6546_;
v___y_6538_ = v___y_6548_;
v___y_6539_ = v___y_6546_;
goto v___jp_6534_;
}
else
{
uint64_t v___x_6561_; uint8_t v___x_6562_; 
v___x_6561_ = 9223372036854775808ULL;
v___x_6562_ = lean_uint64_dec_lt(v___x_6561_, v___y_6549_);
if (v___x_6562_ == 0)
{
v___y_6535_ = v_position_6551_;
v___y_6536_ = v___y_6545_;
v___y_6537_ = v___y_6546_;
v___y_6538_ = v___y_6548_;
v___y_6539_ = v___y_6546_;
goto v___jp_6534_;
}
else
{
uint64_t v___x_6563_; 
v___x_6563_ = 1ULL;
v___y_6535_ = v_position_6551_;
v___y_6536_ = v___y_6545_;
v___y_6537_ = v___y_6546_;
v___y_6538_ = v___y_6548_;
v___y_6539_ = v___x_6563_;
goto v___jp_6534_;
}
}
}
else
{
uint64_t v_quotient_6564_; uint64_t v___x_6565_; uint64_t v___x_6566_; uint64_t v___x_6567_; uint64_t v_remainder_6568_; uint64_t v___x_6569_; uint64_t v_half_6570_; uint8_t v___x_6571_; 
v_quotient_6564_ = lean_uint64_shift_right(v___y_6549_, v___x_6556_);
v___x_6565_ = 1ULL;
v___x_6566_ = lean_uint64_shift_left(v___x_6565_, v___x_6556_);
v___x_6567_ = lean_uint64_sub(v___x_6566_, v___x_6565_);
v_remainder_6568_ = lean_uint64_land(v___y_6549_, v___x_6567_);
v___x_6569_ = lean_uint64_sub(v___x_6556_, v___x_6565_);
v_half_6570_ = lean_uint64_shift_left(v___x_6565_, v___x_6569_);
v___x_6571_ = lean_uint64_dec_lt(v_remainder_6568_, v_half_6570_);
if (v___x_6571_ == 0)
{
uint8_t v___x_6572_; 
v___x_6572_ = lean_uint64_dec_lt(v_half_6570_, v_remainder_6568_);
if (v___x_6572_ == 0)
{
uint64_t v___x_6573_; uint8_t v___x_6574_; 
v___x_6573_ = lean_uint64_land(v_quotient_6564_, v___x_6565_);
v___x_6574_ = lean_uint64_dec_eq(v___x_6573_, v___y_6546_);
if (v___x_6574_ == 0)
{
uint64_t v___x_6575_; 
v___x_6575_ = lean_uint64_add(v_quotient_6564_, v___x_6565_);
v___y_6535_ = v_position_6551_;
v___y_6536_ = v___y_6545_;
v___y_6537_ = v___y_6546_;
v___y_6538_ = v___y_6548_;
v___y_6539_ = v___x_6575_;
goto v___jp_6534_;
}
else
{
v___y_6535_ = v_position_6551_;
v___y_6536_ = v___y_6545_;
v___y_6537_ = v___y_6546_;
v___y_6538_ = v___y_6548_;
v___y_6539_ = v_quotient_6564_;
goto v___jp_6534_;
}
}
else
{
uint64_t v___x_6576_; 
v___x_6576_ = lean_uint64_add(v_quotient_6564_, v___x_6565_);
v___y_6535_ = v_position_6551_;
v___y_6536_ = v___y_6545_;
v___y_6537_ = v___y_6546_;
v___y_6538_ = v___y_6548_;
v___y_6539_ = v___x_6576_;
goto v___jp_6534_;
}
}
else
{
v___y_6535_ = v_position_6551_;
v___y_6536_ = v___y_6545_;
v___y_6537_ = v___y_6546_;
v___y_6538_ = v___y_6548_;
v___y_6539_ = v_quotient_6564_;
goto v___jp_6534_;
}
}
}
else
{
v___y_6535_ = v_position_6551_;
v___y_6536_ = v___y_6545_;
v___y_6537_ = v___y_6546_;
v___y_6538_ = v___y_6548_;
v___y_6539_ = v___y_6549_;
goto v___jp_6534_;
}
}
else
{
uint64_t v___x_6577_; uint64_t v___x_6578_; 
v___x_6577_ = lean_uint64_sub(v___x_6554_, v___y_6550_);
v___x_6578_ = lean_uint64_shift_left(v___y_6549_, v___x_6577_);
v___y_6535_ = v_position_6551_;
v___y_6536_ = v___y_6545_;
v___y_6537_ = v___y_6546_;
v___y_6538_ = v___y_6548_;
v___y_6539_ = v___x_6578_;
goto v___jp_6534_;
}
}
else
{
uint64_t v___x_6579_; uint8_t v___x_6580_; 
v___x_6579_ = 149ULL;
v___x_6580_ = lean_uint64_dec_lt(v___y_6547_, v___x_6579_);
if (v___x_6580_ == 0)
{
uint64_t v___x_6581_; uint64_t v___x_6582_; 
v___x_6581_ = lean_uint64_sub(v___y_6547_, v___x_6579_);
v___x_6582_ = lean_uint64_shift_left(v___y_6549_, v___x_6581_);
v___y_5987_ = v___y_6545_;
v___y_5988_ = v___y_6546_;
v___y_5989_ = v___y_6548_;
v___y_5990_ = v___x_6582_;
goto v___jp_5986_;
}
else
{
uint64_t v___x_6583_; uint8_t v___x_6584_; 
v___x_6583_ = lean_uint64_sub(v___x_6579_, v___y_6547_);
v___x_6584_ = lean_uint64_dec_eq(v___x_6583_, v___y_6546_);
if (v___x_6584_ == 0)
{
uint64_t v___x_6585_; uint8_t v___x_6586_; 
v___x_6585_ = 64ULL;
v___x_6586_ = lean_uint64_dec_lt(v___x_6583_, v___x_6585_);
if (v___x_6586_ == 0)
{
uint8_t v___x_6587_; 
v___x_6587_ = lean_uint64_dec_eq(v___x_6583_, v___x_6585_);
if (v___x_6587_ == 0)
{
v___y_5987_ = v___y_6545_;
v___y_5988_ = v___y_6546_;
v___y_5989_ = v___y_6548_;
v___y_5990_ = v___y_6546_;
goto v___jp_5986_;
}
else
{
uint64_t v___x_6588_; uint8_t v___x_6589_; 
v___x_6588_ = 9223372036854775808ULL;
v___x_6589_ = lean_uint64_dec_lt(v___x_6588_, v___y_6549_);
if (v___x_6589_ == 0)
{
v___y_5987_ = v___y_6545_;
v___y_5988_ = v___y_6546_;
v___y_5989_ = v___y_6548_;
v___y_5990_ = v___y_6546_;
goto v___jp_5986_;
}
else
{
uint64_t v___x_6590_; 
v___x_6590_ = 1ULL;
v___y_5987_ = v___y_6545_;
v___y_5988_ = v___y_6546_;
v___y_5989_ = v___y_6548_;
v___y_5990_ = v___x_6590_;
goto v___jp_5986_;
}
}
}
else
{
uint64_t v_quotient_6591_; uint64_t v___x_6592_; uint64_t v___x_6593_; uint64_t v___x_6594_; uint64_t v_remainder_6595_; uint64_t v___x_6596_; uint64_t v_half_6597_; uint8_t v___x_6598_; 
v_quotient_6591_ = lean_uint64_shift_right(v___y_6549_, v___x_6583_);
v___x_6592_ = 1ULL;
v___x_6593_ = lean_uint64_shift_left(v___x_6592_, v___x_6583_);
v___x_6594_ = lean_uint64_sub(v___x_6593_, v___x_6592_);
v_remainder_6595_ = lean_uint64_land(v___y_6549_, v___x_6594_);
v___x_6596_ = lean_uint64_sub(v___x_6583_, v___x_6592_);
v_half_6597_ = lean_uint64_shift_left(v___x_6592_, v___x_6596_);
v___x_6598_ = lean_uint64_dec_lt(v_remainder_6595_, v_half_6597_);
if (v___x_6598_ == 0)
{
uint8_t v___x_6599_; 
v___x_6599_ = lean_uint64_dec_lt(v_half_6597_, v_remainder_6595_);
if (v___x_6599_ == 0)
{
uint64_t v___x_6600_; uint8_t v___x_6601_; 
v___x_6600_ = lean_uint64_land(v_quotient_6591_, v___x_6592_);
v___x_6601_ = lean_uint64_dec_eq(v___x_6600_, v___y_6546_);
if (v___x_6601_ == 0)
{
uint64_t v___x_6602_; 
v___x_6602_ = lean_uint64_add(v_quotient_6591_, v___x_6592_);
v___y_5987_ = v___y_6545_;
v___y_5988_ = v___y_6546_;
v___y_5989_ = v___y_6548_;
v___y_5990_ = v___x_6602_;
goto v___jp_5986_;
}
else
{
v___y_5987_ = v___y_6545_;
v___y_5988_ = v___y_6546_;
v___y_5989_ = v___y_6548_;
v___y_5990_ = v_quotient_6591_;
goto v___jp_5986_;
}
}
else
{
uint64_t v___x_6603_; 
v___x_6603_ = lean_uint64_add(v_quotient_6591_, v___x_6592_);
v___y_5987_ = v___y_6545_;
v___y_5988_ = v___y_6546_;
v___y_5989_ = v___y_6548_;
v___y_5990_ = v___x_6603_;
goto v___jp_5986_;
}
}
else
{
v___y_5987_ = v___y_6545_;
v___y_5988_ = v___y_6546_;
v___y_5989_ = v___y_6548_;
v___y_5990_ = v_quotient_6591_;
goto v___jp_5986_;
}
}
}
else
{
v___y_5987_ = v___y_6545_;
v___y_5988_ = v___y_6546_;
v___y_5989_ = v___y_6548_;
v___y_5990_ = v___y_6549_;
goto v___jp_5986_;
}
}
}
}
v___jp_6604_:
{
uint64_t v___x_6612_; uint64_t v___x_6613_; uint8_t v___x_6614_; 
v___x_6612_ = 1ULL;
v___x_6613_ = lean_uint64_shift_right(v___y_6609_, v___x_6612_);
v___x_6614_ = lean_uint64_dec_eq(v___x_6613_, v___y_6607_);
if (v___x_6614_ == 0)
{
uint64_t v___x_6615_; 
v___x_6615_ = lean_uint64_add(v___y_6611_, v___x_6612_);
v___y_6545_ = v___y_6605_;
v___y_6546_ = v___y_6607_;
v___y_6547_ = v___y_6606_;
v___y_6548_ = v___y_6608_;
v___y_6549_ = v___y_6610_;
v___y_6550_ = v___x_6615_;
goto v___jp_6544_;
}
else
{
v___y_6545_ = v___y_6605_;
v___y_6546_ = v___y_6607_;
v___y_6547_ = v___y_6606_;
v___y_6548_ = v___y_6608_;
v___y_6549_ = v___y_6610_;
v___y_6550_ = v___y_6611_;
goto v___jp_6544_;
}
}
v___jp_6616_:
{
uint64_t v___x_6626_; uint8_t v___x_6627_; 
v___x_6626_ = lean_uint64_shift_right(v___y_6624_, v___y_6619_);
v___x_6627_ = lean_uint64_dec_eq(v___x_6626_, v___y_6620_);
if (v___x_6627_ == 0)
{
uint64_t v___x_6628_; 
v___x_6628_ = lean_uint64_add(v___y_6618_, v___y_6619_);
v___y_6605_ = v___y_6617_;
v___y_6606_ = v___y_6621_;
v___y_6607_ = v___y_6620_;
v___y_6608_ = v___y_6622_;
v___y_6609_ = v___y_6625_;
v___y_6610_ = v___y_6623_;
v___y_6611_ = v___x_6628_;
goto v___jp_6604_;
}
else
{
v___y_6605_ = v___y_6617_;
v___y_6606_ = v___y_6621_;
v___y_6607_ = v___y_6620_;
v___y_6608_ = v___y_6622_;
v___y_6609_ = v___y_6625_;
v___y_6610_ = v___y_6623_;
v___y_6611_ = v___y_6618_;
goto v___jp_6604_;
}
}
v___jp_6629_:
{
uint64_t v___x_6637_; uint64_t v___x_6638_; uint8_t v___x_6639_; 
v___x_6637_ = 2ULL;
v___x_6638_ = lean_uint64_shift_right(v___y_6635_, v___x_6637_);
v___x_6639_ = lean_uint64_dec_eq(v___x_6638_, v___y_6632_);
if (v___x_6639_ == 0)
{
v___y_6617_ = v___y_6630_;
v___y_6618_ = v___y_6636_;
v___y_6619_ = v___x_6637_;
v___y_6620_ = v___y_6632_;
v___y_6621_ = v___y_6631_;
v___y_6622_ = v___y_6633_;
v___y_6623_ = v___y_6634_;
v___y_6624_ = v___y_6635_;
v___y_6625_ = v___x_6638_;
goto v___jp_6616_;
}
else
{
v___y_6617_ = v___y_6630_;
v___y_6618_ = v___y_6636_;
v___y_6619_ = v___x_6637_;
v___y_6620_ = v___y_6632_;
v___y_6621_ = v___y_6631_;
v___y_6622_ = v___y_6633_;
v___y_6623_ = v___y_6634_;
v___y_6624_ = v___y_6635_;
v___y_6625_ = v___y_6635_;
goto v___jp_6616_;
}
}
v___jp_6640_:
{
uint64_t v___x_6650_; uint8_t v___x_6651_; 
v___x_6650_ = lean_uint64_shift_right(v___y_6648_, v___y_6642_);
v___x_6651_ = lean_uint64_dec_eq(v___x_6650_, v___y_6644_);
if (v___x_6651_ == 0)
{
uint64_t v___x_6652_; 
v___x_6652_ = lean_uint64_add(v___y_6643_, v___y_6642_);
v___y_6630_ = v___y_6641_;
v___y_6631_ = v___y_6645_;
v___y_6632_ = v___y_6644_;
v___y_6633_ = v___y_6646_;
v___y_6634_ = v___y_6647_;
v___y_6635_ = v___y_6649_;
v___y_6636_ = v___x_6652_;
goto v___jp_6629_;
}
else
{
v___y_6630_ = v___y_6641_;
v___y_6631_ = v___y_6645_;
v___y_6632_ = v___y_6644_;
v___y_6633_ = v___y_6646_;
v___y_6634_ = v___y_6647_;
v___y_6635_ = v___y_6649_;
v___y_6636_ = v___y_6643_;
goto v___jp_6629_;
}
}
v___jp_6653_:
{
uint64_t v___x_6661_; uint64_t v___x_6662_; uint8_t v___x_6663_; 
v___x_6661_ = 4ULL;
v___x_6662_ = lean_uint64_shift_right(v___y_6659_, v___x_6661_);
v___x_6663_ = lean_uint64_dec_eq(v___x_6662_, v___y_6656_);
if (v___x_6663_ == 0)
{
v___y_6641_ = v___y_6654_;
v___y_6642_ = v___x_6661_;
v___y_6643_ = v___y_6660_;
v___y_6644_ = v___y_6656_;
v___y_6645_ = v___y_6655_;
v___y_6646_ = v___y_6657_;
v___y_6647_ = v___y_6658_;
v___y_6648_ = v___y_6659_;
v___y_6649_ = v___x_6662_;
goto v___jp_6640_;
}
else
{
v___y_6641_ = v___y_6654_;
v___y_6642_ = v___x_6661_;
v___y_6643_ = v___y_6660_;
v___y_6644_ = v___y_6656_;
v___y_6645_ = v___y_6655_;
v___y_6646_ = v___y_6657_;
v___y_6647_ = v___y_6658_;
v___y_6648_ = v___y_6659_;
v___y_6649_ = v___y_6659_;
goto v___jp_6640_;
}
}
v___jp_6664_:
{
uint64_t v___x_6674_; uint8_t v___x_6675_; 
v___x_6674_ = lean_uint64_shift_right(v___y_6667_, v___y_6672_);
v___x_6675_ = lean_uint64_dec_eq(v___x_6674_, v___y_6668_);
if (v___x_6675_ == 0)
{
uint64_t v___x_6676_; 
v___x_6676_ = lean_uint64_add(v___y_6666_, v___y_6672_);
v___y_6654_ = v___y_6665_;
v___y_6655_ = v___y_6669_;
v___y_6656_ = v___y_6668_;
v___y_6657_ = v___y_6670_;
v___y_6658_ = v___y_6671_;
v___y_6659_ = v___y_6673_;
v___y_6660_ = v___x_6676_;
goto v___jp_6653_;
}
else
{
v___y_6654_ = v___y_6665_;
v___y_6655_ = v___y_6669_;
v___y_6656_ = v___y_6668_;
v___y_6657_ = v___y_6670_;
v___y_6658_ = v___y_6671_;
v___y_6659_ = v___y_6673_;
v___y_6660_ = v___y_6666_;
goto v___jp_6653_;
}
}
v___jp_6677_:
{
uint64_t v___x_6685_; uint64_t v___x_6686_; uint8_t v___x_6687_; 
v___x_6685_ = 8ULL;
v___x_6686_ = lean_uint64_shift_right(v___y_6679_, v___x_6685_);
v___x_6687_ = lean_uint64_dec_eq(v___x_6686_, v___y_6681_);
if (v___x_6687_ == 0)
{
v___y_6665_ = v___y_6678_;
v___y_6666_ = v___y_6684_;
v___y_6667_ = v___y_6679_;
v___y_6668_ = v___y_6681_;
v___y_6669_ = v___y_6680_;
v___y_6670_ = v___y_6682_;
v___y_6671_ = v___y_6683_;
v___y_6672_ = v___x_6685_;
v___y_6673_ = v___x_6686_;
goto v___jp_6664_;
}
else
{
v___y_6665_ = v___y_6678_;
v___y_6666_ = v___y_6684_;
v___y_6667_ = v___y_6679_;
v___y_6668_ = v___y_6681_;
v___y_6669_ = v___y_6680_;
v___y_6670_ = v___y_6682_;
v___y_6671_ = v___y_6683_;
v___y_6672_ = v___x_6685_;
v___y_6673_ = v___y_6679_;
goto v___jp_6664_;
}
}
v___jp_6688_:
{
uint64_t v___x_6698_; uint8_t v___x_6699_; 
v___x_6698_ = lean_uint64_shift_right(v___y_6689_, v___y_6692_);
v___x_6699_ = lean_uint64_dec_eq(v___x_6698_, v___y_6693_);
if (v___x_6699_ == 0)
{
uint64_t v___x_6700_; 
v___x_6700_ = lean_uint64_add(v___y_6691_, v___y_6692_);
v___y_6678_ = v___y_6690_;
v___y_6679_ = v___y_6697_;
v___y_6680_ = v___y_6694_;
v___y_6681_ = v___y_6693_;
v___y_6682_ = v___y_6695_;
v___y_6683_ = v___y_6696_;
v___y_6684_ = v___x_6700_;
goto v___jp_6677_;
}
else
{
v___y_6678_ = v___y_6690_;
v___y_6679_ = v___y_6697_;
v___y_6680_ = v___y_6694_;
v___y_6681_ = v___y_6693_;
v___y_6682_ = v___y_6695_;
v___y_6683_ = v___y_6696_;
v___y_6684_ = v___y_6691_;
goto v___jp_6677_;
}
}
v___jp_6701_:
{
uint64_t v___x_6709_; uint64_t v___x_6710_; uint8_t v___x_6711_; 
v___x_6709_ = 16ULL;
v___x_6710_ = lean_uint64_shift_right(v___y_6702_, v___x_6709_);
v___x_6711_ = lean_uint64_dec_eq(v___x_6710_, v___y_6705_);
if (v___x_6711_ == 0)
{
v___y_6689_ = v___y_6702_;
v___y_6690_ = v___y_6703_;
v___y_6691_ = v___y_6708_;
v___y_6692_ = v___x_6709_;
v___y_6693_ = v___y_6705_;
v___y_6694_ = v___y_6704_;
v___y_6695_ = v___y_6706_;
v___y_6696_ = v___y_6707_;
v___y_6697_ = v___x_6710_;
goto v___jp_6688_;
}
else
{
v___y_6689_ = v___y_6702_;
v___y_6690_ = v___y_6703_;
v___y_6691_ = v___y_6708_;
v___y_6692_ = v___x_6709_;
v___y_6693_ = v___y_6705_;
v___y_6694_ = v___y_6704_;
v___y_6695_ = v___y_6706_;
v___y_6696_ = v___y_6707_;
v___y_6697_ = v___y_6702_;
goto v___jp_6688_;
}
}
v___jp_6712_:
{
uint64_t v___x_6720_; uint8_t v___x_6721_; 
v___x_6720_ = lean_uint64_shift_right(v___y_6718_, v___y_6714_);
v___x_6721_ = lean_uint64_dec_eq(v___x_6720_, v___y_6715_);
if (v___x_6721_ == 0)
{
v___y_6702_ = v___y_6719_;
v___y_6703_ = v___y_6713_;
v___y_6704_ = v___y_6716_;
v___y_6705_ = v___y_6715_;
v___y_6706_ = v___y_6717_;
v___y_6707_ = v___y_6718_;
v___y_6708_ = v___y_6714_;
goto v___jp_6701_;
}
else
{
v___y_6702_ = v___y_6719_;
v___y_6703_ = v___y_6713_;
v___y_6704_ = v___y_6716_;
v___y_6705_ = v___y_6715_;
v___y_6706_ = v___y_6717_;
v___y_6707_ = v___y_6718_;
v___y_6708_ = v___y_6715_;
goto v___jp_6701_;
}
}
v___jp_6722_:
{
uint64_t v___x_6727_; uint8_t v___x_6728_; 
v___x_6727_ = 0ULL;
v___x_6728_ = lean_uint64_dec_eq(v___y_6726_, v___x_6727_);
if (v___x_6728_ == 0)
{
uint64_t v___x_6729_; uint64_t v___x_6730_; uint8_t v___x_6731_; 
v___x_6729_ = 32ULL;
v___x_6730_ = lean_uint64_shift_right(v___y_6726_, v___x_6729_);
v___x_6731_ = lean_uint64_dec_eq(v___x_6730_, v___x_6727_);
if (v___x_6731_ == 0)
{
v___y_6713_ = v___y_6723_;
v___y_6714_ = v___x_6729_;
v___y_6715_ = v___x_6727_;
v___y_6716_ = v___y_6724_;
v___y_6717_ = v___y_6725_;
v___y_6718_ = v___y_6726_;
v___y_6719_ = v___x_6730_;
goto v___jp_6712_;
}
else
{
v___y_6713_ = v___y_6723_;
v___y_6714_ = v___x_6729_;
v___y_6715_ = v___x_6727_;
v___y_6716_ = v___y_6724_;
v___y_6717_ = v___y_6725_;
v___y_6718_ = v___y_6726_;
v___y_6719_ = v___y_6726_;
goto v___jp_6712_;
}
}
else
{
if (v___y_6725_ == 0)
{
uint32_t v___x_6732_; 
v___x_6732_ = 0;
return v___x_6732_;
}
else
{
uint32_t v___x_6733_; 
v___x_6733_ = 2147483648;
return v___x_6733_;
}
}
}
v___jp_6734_:
{
uint64_t v___x_6741_; uint64_t v___x_6742_; uint64_t v___x_6743_; uint8_t v___x_6744_; 
v___x_6741_ = lean_uint64_mul(v___y_6738_, v___y_6736_);
v___x_6742_ = lean_uint64_add(v___y_6737_, v___y_6740_);
v___x_6743_ = 281474976710656ULL;
v___x_6744_ = lean_uint64_dec_lt(v___x_6741_, v___x_6743_);
if (v___x_6744_ == 0)
{
v___y_6723_ = v___y_6735_;
v___y_6724_ = v___x_6742_;
v___y_6725_ = v___y_6739_;
v___y_6726_ = v___x_6741_;
goto v___jp_6722_;
}
else
{
uint64_t v___x_6745_; uint8_t v___x_6746_; 
v___x_6745_ = 123ULL;
v___x_6746_ = lean_uint64_dec_le(v___x_6742_, v___x_6745_);
if (v___x_6746_ == 0)
{
v___y_6723_ = v___y_6735_;
v___y_6724_ = v___x_6742_;
v___y_6725_ = v___y_6739_;
v___y_6726_ = v___x_6741_;
goto v___jp_6722_;
}
else
{
uint64_t v___x_6747_; uint8_t v___x_6748_; 
v___x_6747_ = 0ULL;
v___x_6748_ = lean_uint64_dec_eq(v___x_6741_, v___x_6747_);
if (v___x_6748_ == 0)
{
uint64_t v___x_6749_; uint64_t v___x_6750_; uint8_t v___x_6751_; 
v___x_6749_ = 149ULL;
v___x_6750_ = lean_uint64_sub(v___x_6749_, v___x_6742_);
v___x_6751_ = lean_uint64_dec_eq(v___x_6750_, v___x_6747_);
if (v___x_6751_ == 0)
{
uint64_t v___x_6752_; uint8_t v___x_6753_; 
v___x_6752_ = 64ULL;
v___x_6753_ = lean_uint64_dec_lt(v___x_6750_, v___x_6752_);
if (v___x_6753_ == 0)
{
uint8_t v___x_6754_; 
v___x_6754_ = lean_uint64_dec_eq(v___x_6750_, v___x_6752_);
if (v___x_6754_ == 0)
{
v___y_6008_ = v___y_6735_;
v___y_6009_ = v___y_6739_;
v___y_6010_ = v___x_6747_;
v___y_6011_ = v___x_6747_;
goto v___jp_6007_;
}
else
{
uint64_t v___x_6755_; uint8_t v___x_6756_; 
v___x_6755_ = 9223372036854775808ULL;
v___x_6756_ = lean_uint64_dec_lt(v___x_6755_, v___x_6741_);
if (v___x_6756_ == 0)
{
v___y_6008_ = v___y_6735_;
v___y_6009_ = v___y_6739_;
v___y_6010_ = v___x_6747_;
v___y_6011_ = v___x_6747_;
goto v___jp_6007_;
}
else
{
uint64_t v___x_6757_; 
v___x_6757_ = 1ULL;
v___y_6008_ = v___y_6735_;
v___y_6009_ = v___y_6739_;
v___y_6010_ = v___x_6747_;
v___y_6011_ = v___x_6757_;
goto v___jp_6007_;
}
}
}
else
{
uint64_t v_quotient_6758_; uint64_t v___x_6759_; uint64_t v___x_6760_; uint64_t v___x_6761_; uint64_t v_remainder_6762_; uint64_t v___x_6763_; uint64_t v_half_6764_; uint8_t v___x_6765_; 
v_quotient_6758_ = lean_uint64_shift_right(v___x_6741_, v___x_6750_);
v___x_6759_ = 1ULL;
v___x_6760_ = lean_uint64_shift_left(v___x_6759_, v___x_6750_);
v___x_6761_ = lean_uint64_sub(v___x_6760_, v___x_6759_);
v_remainder_6762_ = lean_uint64_land(v___x_6741_, v___x_6761_);
v___x_6763_ = lean_uint64_sub(v___x_6750_, v___x_6759_);
v_half_6764_ = lean_uint64_shift_left(v___x_6759_, v___x_6763_);
v___x_6765_ = lean_uint64_dec_lt(v_remainder_6762_, v_half_6764_);
if (v___x_6765_ == 0)
{
uint8_t v___x_6766_; 
v___x_6766_ = lean_uint64_dec_lt(v_half_6764_, v_remainder_6762_);
if (v___x_6766_ == 0)
{
uint64_t v___x_6767_; uint8_t v___x_6768_; 
v___x_6767_ = lean_uint64_land(v_quotient_6758_, v___x_6759_);
v___x_6768_ = lean_uint64_dec_eq(v___x_6767_, v___x_6747_);
if (v___x_6768_ == 0)
{
uint64_t v___x_6769_; 
v___x_6769_ = lean_uint64_add(v_quotient_6758_, v___x_6759_);
v___y_6008_ = v___y_6735_;
v___y_6009_ = v___y_6739_;
v___y_6010_ = v___x_6747_;
v___y_6011_ = v___x_6769_;
goto v___jp_6007_;
}
else
{
v___y_6008_ = v___y_6735_;
v___y_6009_ = v___y_6739_;
v___y_6010_ = v___x_6747_;
v___y_6011_ = v_quotient_6758_;
goto v___jp_6007_;
}
}
else
{
uint64_t v___x_6770_; 
v___x_6770_ = lean_uint64_add(v_quotient_6758_, v___x_6759_);
v___y_6008_ = v___y_6735_;
v___y_6009_ = v___y_6739_;
v___y_6010_ = v___x_6747_;
v___y_6011_ = v___x_6770_;
goto v___jp_6007_;
}
}
else
{
v___y_6008_ = v___y_6735_;
v___y_6009_ = v___y_6739_;
v___y_6010_ = v___x_6747_;
v___y_6011_ = v_quotient_6758_;
goto v___jp_6007_;
}
}
}
else
{
v___y_6008_ = v___y_6735_;
v___y_6009_ = v___y_6739_;
v___y_6010_ = v___x_6747_;
v___y_6011_ = v___x_6741_;
goto v___jp_6007_;
}
}
else
{
if (v___y_6739_ == 0)
{
uint32_t v___x_6771_; 
v___x_6771_ = 0;
return v___x_6771_;
}
else
{
uint32_t v___x_6772_; 
v___x_6772_ = 2147483648;
return v___x_6772_;
}
}
}
}
}
v___jp_6773_:
{
uint32_t v___x_6778_; uint32_t v___x_6779_; uint32_t v___x_6780_; uint32_t v___x_6781_; uint32_t v___x_6782_; 
v___x_6778_ = lean_uint32_land(v___y_6775_, v___x_6208_);
v___x_6779_ = lean_uint32_shift_left(v___x_6778_, v___x_6167_);
v___x_6780_ = lean_uint32_lor(v___y_6777_, v___x_6779_);
v___x_6781_ = lean_uint32_land(v___y_6776_, v___y_6774_);
v___x_6782_ = lean_uint32_lor(v___x_6780_, v___x_6781_);
return v___x_6782_;
}
v___jp_6783_:
{
if (v___y_6786_ == 0)
{
uint32_t v___x_6788_; 
v___x_6788_ = 0;
v___y_6774_ = v___y_6784_;
v___y_6775_ = v___y_6785_;
v___y_6776_ = v___y_6787_;
v___y_6777_ = v___x_6788_;
goto v___jp_6773_;
}
else
{
uint32_t v___x_6789_; 
v___x_6789_ = 2147483648;
v___y_6774_ = v___y_6784_;
v___y_6775_ = v___y_6785_;
v___y_6776_ = v___y_6787_;
v___y_6777_ = v___x_6789_;
goto v___jp_6773_;
}
}
v___jp_6790_:
{
uint64_t v___x_6796_; uint64_t v_encodedExponent_6797_; uint32_t v___x_6798_; uint64_t v___x_6799_; uint8_t v___x_6800_; 
v___x_6796_ = 171ULL;
v_encodedExponent_6797_ = lean_uint64_sub(v___y_6793_, v___x_6796_);
v___x_6798_ = lean_uint64_to_uint32(v_encodedExponent_6797_);
v___x_6799_ = 8388608ULL;
v___x_6800_ = lean_uint64_dec_lt(v___y_6795_, v___x_6799_);
if (v___x_6800_ == 0)
{
uint64_t v___x_6801_; uint32_t v___x_6802_; 
v___x_6801_ = lean_uint64_sub(v___y_6795_, v___x_6799_);
v___x_6802_ = lean_uint64_to_uint32(v___x_6801_);
v___y_6784_ = v___y_6791_;
v___y_6785_ = v___x_6798_;
v___y_6786_ = v___y_6794_;
v___y_6787_ = v___x_6802_;
goto v___jp_6783_;
}
else
{
uint32_t v___x_6803_; 
v___x_6803_ = lean_uint64_to_uint32(v___y_6792_);
v___y_6784_ = v___y_6791_;
v___y_6785_ = v___x_6798_;
v___y_6786_ = v___y_6794_;
v___y_6787_ = v___x_6803_;
goto v___jp_6783_;
}
}
v___jp_6804_:
{
uint64_t v___x_6811_; uint8_t v___x_6812_; 
v___x_6811_ = 425ULL;
v___x_6812_ = lean_uint64_dec_lt(v___x_6811_, v___y_6810_);
if (v___x_6812_ == 0)
{
if (v___y_6808_ == 0)
{
v___y_6791_ = v___y_6805_;
v___y_6792_ = v___y_6807_;
v___y_6793_ = v___y_6810_;
v___y_6794_ = v___y_6809_;
v___y_6795_ = v___y_6806_;
goto v___jp_6790_;
}
else
{
uint64_t v___x_6813_; 
v___x_6813_ = 8388608ULL;
v___y_6791_ = v___y_6805_;
v___y_6792_ = v___y_6807_;
v___y_6793_ = v___y_6810_;
v___y_6794_ = v___y_6809_;
v___y_6795_ = v___x_6813_;
goto v___jp_6790_;
}
}
else
{
if (v___y_6809_ == 0)
{
uint32_t v___x_6814_; 
v___x_6814_ = 2139095040;
return v___x_6814_;
}
else
{
uint32_t v___x_6815_; 
v___x_6815_ = 4286578688;
return v___x_6815_;
}
}
}
v___jp_6816_:
{
uint64_t v___x_6822_; uint8_t v_carry_6823_; 
v___x_6822_ = 16777216ULL;
v_carry_6823_ = lean_uint64_dec_eq(v___y_6821_, v___x_6822_);
if (v_carry_6823_ == 0)
{
v___y_6805_ = v___y_6817_;
v___y_6806_ = v___y_6821_;
v___y_6807_ = v___y_6818_;
v___y_6808_ = v_carry_6823_;
v___y_6809_ = v___y_6819_;
v___y_6810_ = v___y_6820_;
goto v___jp_6804_;
}
else
{
uint64_t v___x_6824_; uint64_t v___x_6825_; 
v___x_6824_ = 1ULL;
v___x_6825_ = lean_uint64_add(v___y_6820_, v___x_6824_);
v___y_6805_ = v___y_6817_;
v___y_6806_ = v___y_6821_;
v___y_6807_ = v___y_6818_;
v___y_6808_ = v_carry_6823_;
v___y_6809_ = v___y_6819_;
v___y_6810_ = v___x_6825_;
goto v___jp_6804_;
}
}
v___jp_6826_:
{
uint64_t v_position_6833_; uint64_t v___x_6834_; uint8_t v___x_6835_; 
v_position_6833_ = lean_uint64_add(v___y_6832_, v___y_6829_);
v___x_6834_ = 172ULL;
v___x_6835_ = lean_uint64_dec_lt(v_position_6833_, v___x_6834_);
if (v___x_6835_ == 0)
{
uint64_t v___x_6836_; uint8_t v___x_6837_; 
v___x_6836_ = 23ULL;
v___x_6837_ = lean_uint64_dec_lt(v___y_6832_, v___x_6836_);
if (v___x_6837_ == 0)
{
uint64_t v___x_6838_; uint8_t v___x_6839_; 
v___x_6838_ = lean_uint64_sub(v___y_6832_, v___x_6836_);
v___x_6839_ = lean_uint64_dec_eq(v___x_6838_, v___y_6828_);
if (v___x_6839_ == 0)
{
uint64_t v___x_6840_; uint8_t v___x_6841_; 
v___x_6840_ = 64ULL;
v___x_6841_ = lean_uint64_dec_lt(v___x_6838_, v___x_6840_);
if (v___x_6841_ == 0)
{
uint8_t v___x_6842_; 
v___x_6842_ = lean_uint64_dec_eq(v___x_6838_, v___x_6840_);
if (v___x_6842_ == 0)
{
v___y_6817_ = v___y_6827_;
v___y_6818_ = v___y_6828_;
v___y_6819_ = v___y_6831_;
v___y_6820_ = v_position_6833_;
v___y_6821_ = v___y_6828_;
goto v___jp_6816_;
}
else
{
uint64_t v___x_6843_; uint8_t v___x_6844_; 
v___x_6843_ = 9223372036854775808ULL;
v___x_6844_ = lean_uint64_dec_lt(v___x_6843_, v___y_6830_);
if (v___x_6844_ == 0)
{
v___y_6817_ = v___y_6827_;
v___y_6818_ = v___y_6828_;
v___y_6819_ = v___y_6831_;
v___y_6820_ = v_position_6833_;
v___y_6821_ = v___y_6828_;
goto v___jp_6816_;
}
else
{
uint64_t v___x_6845_; 
v___x_6845_ = 1ULL;
v___y_6817_ = v___y_6827_;
v___y_6818_ = v___y_6828_;
v___y_6819_ = v___y_6831_;
v___y_6820_ = v_position_6833_;
v___y_6821_ = v___x_6845_;
goto v___jp_6816_;
}
}
}
else
{
uint64_t v_quotient_6846_; uint64_t v___x_6847_; uint64_t v___x_6848_; uint64_t v___x_6849_; uint64_t v_remainder_6850_; uint64_t v___x_6851_; uint64_t v_half_6852_; uint8_t v___x_6853_; 
v_quotient_6846_ = lean_uint64_shift_right(v___y_6830_, v___x_6838_);
v___x_6847_ = 1ULL;
v___x_6848_ = lean_uint64_shift_left(v___x_6847_, v___x_6838_);
v___x_6849_ = lean_uint64_sub(v___x_6848_, v___x_6847_);
v_remainder_6850_ = lean_uint64_land(v___y_6830_, v___x_6849_);
v___x_6851_ = lean_uint64_sub(v___x_6838_, v___x_6847_);
v_half_6852_ = lean_uint64_shift_left(v___x_6847_, v___x_6851_);
v___x_6853_ = lean_uint64_dec_lt(v_remainder_6850_, v_half_6852_);
if (v___x_6853_ == 0)
{
uint8_t v___x_6854_; 
v___x_6854_ = lean_uint64_dec_lt(v_half_6852_, v_remainder_6850_);
if (v___x_6854_ == 0)
{
uint64_t v___x_6855_; uint8_t v___x_6856_; 
v___x_6855_ = lean_uint64_land(v_quotient_6846_, v___x_6847_);
v___x_6856_ = lean_uint64_dec_eq(v___x_6855_, v___y_6828_);
if (v___x_6856_ == 0)
{
uint64_t v___x_6857_; 
v___x_6857_ = lean_uint64_add(v_quotient_6846_, v___x_6847_);
v___y_6817_ = v___y_6827_;
v___y_6818_ = v___y_6828_;
v___y_6819_ = v___y_6831_;
v___y_6820_ = v_position_6833_;
v___y_6821_ = v___x_6857_;
goto v___jp_6816_;
}
else
{
v___y_6817_ = v___y_6827_;
v___y_6818_ = v___y_6828_;
v___y_6819_ = v___y_6831_;
v___y_6820_ = v_position_6833_;
v___y_6821_ = v_quotient_6846_;
goto v___jp_6816_;
}
}
else
{
uint64_t v___x_6858_; 
v___x_6858_ = lean_uint64_add(v_quotient_6846_, v___x_6847_);
v___y_6817_ = v___y_6827_;
v___y_6818_ = v___y_6828_;
v___y_6819_ = v___y_6831_;
v___y_6820_ = v_position_6833_;
v___y_6821_ = v___x_6858_;
goto v___jp_6816_;
}
}
else
{
v___y_6817_ = v___y_6827_;
v___y_6818_ = v___y_6828_;
v___y_6819_ = v___y_6831_;
v___y_6820_ = v_position_6833_;
v___y_6821_ = v_quotient_6846_;
goto v___jp_6816_;
}
}
}
else
{
v___y_6817_ = v___y_6827_;
v___y_6818_ = v___y_6828_;
v___y_6819_ = v___y_6831_;
v___y_6820_ = v_position_6833_;
v___y_6821_ = v___y_6830_;
goto v___jp_6816_;
}
}
else
{
uint64_t v___x_6859_; uint64_t v___x_6860_; 
v___x_6859_ = lean_uint64_sub(v___x_6836_, v___y_6832_);
v___x_6860_ = lean_uint64_shift_left(v___y_6830_, v___x_6859_);
v___y_6817_ = v___y_6827_;
v___y_6818_ = v___y_6828_;
v___y_6819_ = v___y_6831_;
v___y_6820_ = v_position_6833_;
v___y_6821_ = v___x_6860_;
goto v___jp_6816_;
}
}
else
{
uint64_t v___x_6861_; uint8_t v___x_6862_; 
v___x_6861_ = 149ULL;
v___x_6862_ = lean_uint64_dec_lt(v___y_6829_, v___x_6861_);
if (v___x_6862_ == 0)
{
uint64_t v___x_6863_; uint64_t v___x_6864_; 
v___x_6863_ = lean_uint64_sub(v___y_6829_, v___x_6861_);
v___x_6864_ = lean_uint64_shift_left(v___y_6830_, v___x_6863_);
v___y_6132_ = v___y_6827_;
v___y_6133_ = v___y_6828_;
v___y_6134_ = v___y_6831_;
v___y_6135_ = v___x_6864_;
goto v___jp_6131_;
}
else
{
uint64_t v___x_6865_; uint8_t v___x_6866_; 
v___x_6865_ = lean_uint64_sub(v___x_6861_, v___y_6829_);
v___x_6866_ = lean_uint64_dec_eq(v___x_6865_, v___y_6828_);
if (v___x_6866_ == 0)
{
uint64_t v___x_6867_; uint8_t v___x_6868_; 
v___x_6867_ = 64ULL;
v___x_6868_ = lean_uint64_dec_lt(v___x_6865_, v___x_6867_);
if (v___x_6868_ == 0)
{
uint8_t v___x_6869_; 
v___x_6869_ = lean_uint64_dec_eq(v___x_6865_, v___x_6867_);
if (v___x_6869_ == 0)
{
v___y_6132_ = v___y_6827_;
v___y_6133_ = v___y_6828_;
v___y_6134_ = v___y_6831_;
v___y_6135_ = v___y_6828_;
goto v___jp_6131_;
}
else
{
uint64_t v___x_6870_; uint8_t v___x_6871_; 
v___x_6870_ = 9223372036854775808ULL;
v___x_6871_ = lean_uint64_dec_lt(v___x_6870_, v___y_6830_);
if (v___x_6871_ == 0)
{
v___y_6132_ = v___y_6827_;
v___y_6133_ = v___y_6828_;
v___y_6134_ = v___y_6831_;
v___y_6135_ = v___y_6828_;
goto v___jp_6131_;
}
else
{
uint64_t v___x_6872_; 
v___x_6872_ = 1ULL;
v___y_6132_ = v___y_6827_;
v___y_6133_ = v___y_6828_;
v___y_6134_ = v___y_6831_;
v___y_6135_ = v___x_6872_;
goto v___jp_6131_;
}
}
}
else
{
uint64_t v_quotient_6873_; uint64_t v___x_6874_; uint64_t v___x_6875_; uint64_t v___x_6876_; uint64_t v_remainder_6877_; uint64_t v___x_6878_; uint64_t v_half_6879_; uint8_t v___x_6880_; 
v_quotient_6873_ = lean_uint64_shift_right(v___y_6830_, v___x_6865_);
v___x_6874_ = 1ULL;
v___x_6875_ = lean_uint64_shift_left(v___x_6874_, v___x_6865_);
v___x_6876_ = lean_uint64_sub(v___x_6875_, v___x_6874_);
v_remainder_6877_ = lean_uint64_land(v___y_6830_, v___x_6876_);
v___x_6878_ = lean_uint64_sub(v___x_6865_, v___x_6874_);
v_half_6879_ = lean_uint64_shift_left(v___x_6874_, v___x_6878_);
v___x_6880_ = lean_uint64_dec_lt(v_remainder_6877_, v_half_6879_);
if (v___x_6880_ == 0)
{
uint8_t v___x_6881_; 
v___x_6881_ = lean_uint64_dec_lt(v_half_6879_, v_remainder_6877_);
if (v___x_6881_ == 0)
{
uint64_t v___x_6882_; uint8_t v___x_6883_; 
v___x_6882_ = lean_uint64_land(v_quotient_6873_, v___x_6874_);
v___x_6883_ = lean_uint64_dec_eq(v___x_6882_, v___y_6828_);
if (v___x_6883_ == 0)
{
uint64_t v___x_6884_; 
v___x_6884_ = lean_uint64_add(v_quotient_6873_, v___x_6874_);
v___y_6132_ = v___y_6827_;
v___y_6133_ = v___y_6828_;
v___y_6134_ = v___y_6831_;
v___y_6135_ = v___x_6884_;
goto v___jp_6131_;
}
else
{
v___y_6132_ = v___y_6827_;
v___y_6133_ = v___y_6828_;
v___y_6134_ = v___y_6831_;
v___y_6135_ = v_quotient_6873_;
goto v___jp_6131_;
}
}
else
{
uint64_t v___x_6885_; 
v___x_6885_ = lean_uint64_add(v_quotient_6873_, v___x_6874_);
v___y_6132_ = v___y_6827_;
v___y_6133_ = v___y_6828_;
v___y_6134_ = v___y_6831_;
v___y_6135_ = v___x_6885_;
goto v___jp_6131_;
}
}
else
{
v___y_6132_ = v___y_6827_;
v___y_6133_ = v___y_6828_;
v___y_6134_ = v___y_6831_;
v___y_6135_ = v_quotient_6873_;
goto v___jp_6131_;
}
}
}
else
{
v___y_6132_ = v___y_6827_;
v___y_6133_ = v___y_6828_;
v___y_6134_ = v___y_6831_;
v___y_6135_ = v___y_6830_;
goto v___jp_6131_;
}
}
}
}
v___jp_6886_:
{
uint64_t v___x_6894_; uint64_t v___x_6895_; uint8_t v___x_6896_; 
v___x_6894_ = 1ULL;
v___x_6895_ = lean_uint64_shift_right(v___y_6890_, v___x_6894_);
v___x_6896_ = lean_uint64_dec_eq(v___x_6895_, v___y_6888_);
if (v___x_6896_ == 0)
{
uint64_t v___x_6897_; 
v___x_6897_ = lean_uint64_add(v___y_6893_, v___x_6894_);
v___y_6827_ = v___y_6887_;
v___y_6828_ = v___y_6888_;
v___y_6829_ = v___y_6889_;
v___y_6830_ = v___y_6891_;
v___y_6831_ = v___y_6892_;
v___y_6832_ = v___x_6897_;
goto v___jp_6826_;
}
else
{
v___y_6827_ = v___y_6887_;
v___y_6828_ = v___y_6888_;
v___y_6829_ = v___y_6889_;
v___y_6830_ = v___y_6891_;
v___y_6831_ = v___y_6892_;
v___y_6832_ = v___y_6893_;
goto v___jp_6826_;
}
}
v___jp_6898_:
{
uint64_t v___x_6908_; uint8_t v___x_6909_; 
v___x_6908_ = lean_uint64_shift_right(v___y_6905_, v___y_6903_);
v___x_6909_ = lean_uint64_dec_eq(v___x_6908_, v___y_6901_);
if (v___x_6909_ == 0)
{
uint64_t v___x_6910_; 
v___x_6910_ = lean_uint64_add(v___y_6899_, v___y_6903_);
v___y_6887_ = v___y_6900_;
v___y_6888_ = v___y_6901_;
v___y_6889_ = v___y_6902_;
v___y_6890_ = v___y_6907_;
v___y_6891_ = v___y_6904_;
v___y_6892_ = v___y_6906_;
v___y_6893_ = v___x_6910_;
goto v___jp_6886_;
}
else
{
v___y_6887_ = v___y_6900_;
v___y_6888_ = v___y_6901_;
v___y_6889_ = v___y_6902_;
v___y_6890_ = v___y_6907_;
v___y_6891_ = v___y_6904_;
v___y_6892_ = v___y_6906_;
v___y_6893_ = v___y_6899_;
goto v___jp_6886_;
}
}
v___jp_6911_:
{
uint64_t v___x_6919_; uint64_t v___x_6920_; uint8_t v___x_6921_; 
v___x_6919_ = 2ULL;
v___x_6920_ = lean_uint64_shift_right(v___y_6916_, v___x_6919_);
v___x_6921_ = lean_uint64_dec_eq(v___x_6920_, v___y_6913_);
if (v___x_6921_ == 0)
{
v___y_6899_ = v___y_6918_;
v___y_6900_ = v___y_6912_;
v___y_6901_ = v___y_6913_;
v___y_6902_ = v___y_6914_;
v___y_6903_ = v___x_6919_;
v___y_6904_ = v___y_6915_;
v___y_6905_ = v___y_6916_;
v___y_6906_ = v___y_6917_;
v___y_6907_ = v___x_6920_;
goto v___jp_6898_;
}
else
{
v___y_6899_ = v___y_6918_;
v___y_6900_ = v___y_6912_;
v___y_6901_ = v___y_6913_;
v___y_6902_ = v___y_6914_;
v___y_6903_ = v___x_6919_;
v___y_6904_ = v___y_6915_;
v___y_6905_ = v___y_6916_;
v___y_6906_ = v___y_6917_;
v___y_6907_ = v___y_6916_;
goto v___jp_6898_;
}
}
v___jp_6922_:
{
uint64_t v___x_6932_; uint8_t v___x_6933_; 
v___x_6932_ = lean_uint64_shift_right(v___y_6930_, v___y_6927_);
v___x_6933_ = lean_uint64_dec_eq(v___x_6932_, v___y_6925_);
if (v___x_6933_ == 0)
{
uint64_t v___x_6934_; 
v___x_6934_ = lean_uint64_add(v___y_6923_, v___y_6927_);
v___y_6912_ = v___y_6924_;
v___y_6913_ = v___y_6925_;
v___y_6914_ = v___y_6926_;
v___y_6915_ = v___y_6928_;
v___y_6916_ = v___y_6931_;
v___y_6917_ = v___y_6929_;
v___y_6918_ = v___x_6934_;
goto v___jp_6911_;
}
else
{
v___y_6912_ = v___y_6924_;
v___y_6913_ = v___y_6925_;
v___y_6914_ = v___y_6926_;
v___y_6915_ = v___y_6928_;
v___y_6916_ = v___y_6931_;
v___y_6917_ = v___y_6929_;
v___y_6918_ = v___y_6923_;
goto v___jp_6911_;
}
}
v___jp_6935_:
{
uint64_t v___x_6943_; uint64_t v___x_6944_; uint8_t v___x_6945_; 
v___x_6943_ = 4ULL;
v___x_6944_ = lean_uint64_shift_right(v___y_6941_, v___x_6943_);
v___x_6945_ = lean_uint64_dec_eq(v___x_6944_, v___y_6937_);
if (v___x_6945_ == 0)
{
v___y_6923_ = v___y_6942_;
v___y_6924_ = v___y_6936_;
v___y_6925_ = v___y_6937_;
v___y_6926_ = v___y_6938_;
v___y_6927_ = v___x_6943_;
v___y_6928_ = v___y_6939_;
v___y_6929_ = v___y_6940_;
v___y_6930_ = v___y_6941_;
v___y_6931_ = v___x_6944_;
goto v___jp_6922_;
}
else
{
v___y_6923_ = v___y_6942_;
v___y_6924_ = v___y_6936_;
v___y_6925_ = v___y_6937_;
v___y_6926_ = v___y_6938_;
v___y_6927_ = v___x_6943_;
v___y_6928_ = v___y_6939_;
v___y_6929_ = v___y_6940_;
v___y_6930_ = v___y_6941_;
v___y_6931_ = v___y_6941_;
goto v___jp_6922_;
}
}
v___jp_6946_:
{
uint64_t v___x_6956_; uint8_t v___x_6957_; 
v___x_6956_ = lean_uint64_shift_right(v___y_6947_, v___y_6954_);
v___x_6957_ = lean_uint64_dec_eq(v___x_6956_, v___y_6949_);
if (v___x_6957_ == 0)
{
uint64_t v___x_6958_; 
v___x_6958_ = lean_uint64_add(v___y_6951_, v___y_6954_);
v___y_6936_ = v___y_6948_;
v___y_6937_ = v___y_6949_;
v___y_6938_ = v___y_6950_;
v___y_6939_ = v___y_6952_;
v___y_6940_ = v___y_6953_;
v___y_6941_ = v___y_6955_;
v___y_6942_ = v___x_6958_;
goto v___jp_6935_;
}
else
{
v___y_6936_ = v___y_6948_;
v___y_6937_ = v___y_6949_;
v___y_6938_ = v___y_6950_;
v___y_6939_ = v___y_6952_;
v___y_6940_ = v___y_6953_;
v___y_6941_ = v___y_6955_;
v___y_6942_ = v___y_6951_;
goto v___jp_6935_;
}
}
v___jp_6959_:
{
uint64_t v___x_6967_; uint64_t v___x_6968_; uint8_t v___x_6969_; 
v___x_6967_ = 8ULL;
v___x_6968_ = lean_uint64_shift_right(v___y_6960_, v___x_6967_);
v___x_6969_ = lean_uint64_dec_eq(v___x_6968_, v___y_6962_);
if (v___x_6969_ == 0)
{
v___y_6947_ = v___y_6960_;
v___y_6948_ = v___y_6961_;
v___y_6949_ = v___y_6962_;
v___y_6950_ = v___y_6963_;
v___y_6951_ = v___y_6966_;
v___y_6952_ = v___y_6964_;
v___y_6953_ = v___y_6965_;
v___y_6954_ = v___x_6967_;
v___y_6955_ = v___x_6968_;
goto v___jp_6946_;
}
else
{
v___y_6947_ = v___y_6960_;
v___y_6948_ = v___y_6961_;
v___y_6949_ = v___y_6962_;
v___y_6950_ = v___y_6963_;
v___y_6951_ = v___y_6966_;
v___y_6952_ = v___y_6964_;
v___y_6953_ = v___y_6965_;
v___y_6954_ = v___x_6967_;
v___y_6955_ = v___y_6960_;
goto v___jp_6946_;
}
}
v___jp_6970_:
{
uint64_t v___x_6980_; uint8_t v___x_6981_; 
v___x_6980_ = lean_uint64_shift_right(v___y_6977_, v___y_6973_);
v___x_6981_ = lean_uint64_dec_eq(v___x_6980_, v___y_6972_);
if (v___x_6981_ == 0)
{
uint64_t v___x_6982_; 
v___x_6982_ = lean_uint64_add(v___y_6975_, v___y_6973_);
v___y_6960_ = v___y_6979_;
v___y_6961_ = v___y_6971_;
v___y_6962_ = v___y_6972_;
v___y_6963_ = v___y_6974_;
v___y_6964_ = v___y_6976_;
v___y_6965_ = v___y_6978_;
v___y_6966_ = v___x_6982_;
goto v___jp_6959_;
}
else
{
v___y_6960_ = v___y_6979_;
v___y_6961_ = v___y_6971_;
v___y_6962_ = v___y_6972_;
v___y_6963_ = v___y_6974_;
v___y_6964_ = v___y_6976_;
v___y_6965_ = v___y_6978_;
v___y_6966_ = v___y_6975_;
goto v___jp_6959_;
}
}
v___jp_6983_:
{
uint64_t v___x_6991_; uint64_t v___x_6992_; uint8_t v___x_6993_; 
v___x_6991_ = 16ULL;
v___x_6992_ = lean_uint64_shift_right(v___y_6989_, v___x_6991_);
v___x_6993_ = lean_uint64_dec_eq(v___x_6992_, v___y_6985_);
if (v___x_6993_ == 0)
{
v___y_6971_ = v___y_6984_;
v___y_6972_ = v___y_6985_;
v___y_6973_ = v___x_6991_;
v___y_6974_ = v___y_6986_;
v___y_6975_ = v___y_6990_;
v___y_6976_ = v___y_6987_;
v___y_6977_ = v___y_6989_;
v___y_6978_ = v___y_6988_;
v___y_6979_ = v___x_6992_;
goto v___jp_6970_;
}
else
{
v___y_6971_ = v___y_6984_;
v___y_6972_ = v___y_6985_;
v___y_6973_ = v___x_6991_;
v___y_6974_ = v___y_6986_;
v___y_6975_ = v___y_6990_;
v___y_6976_ = v___y_6987_;
v___y_6977_ = v___y_6989_;
v___y_6978_ = v___y_6988_;
v___y_6979_ = v___y_6989_;
goto v___jp_6970_;
}
}
v___jp_6994_:
{
uint64_t v___x_7002_; uint8_t v___x_7003_; 
v___x_7002_ = lean_uint64_shift_right(v___y_6998_, v___y_7000_);
v___x_7003_ = lean_uint64_dec_eq(v___x_7002_, v___y_6996_);
if (v___x_7003_ == 0)
{
v___y_6984_ = v___y_6995_;
v___y_6985_ = v___y_6996_;
v___y_6986_ = v___y_6997_;
v___y_6987_ = v___y_6998_;
v___y_6988_ = v___y_6999_;
v___y_6989_ = v___y_7001_;
v___y_6990_ = v___y_7000_;
goto v___jp_6983_;
}
else
{
v___y_6984_ = v___y_6995_;
v___y_6985_ = v___y_6996_;
v___y_6986_ = v___y_6997_;
v___y_6987_ = v___y_6998_;
v___y_6988_ = v___y_6999_;
v___y_6989_ = v___y_7001_;
v___y_6990_ = v___y_6996_;
goto v___jp_6983_;
}
}
v___jp_7004_:
{
uint64_t v___x_7009_; uint8_t v___x_7010_; 
v___x_7009_ = 0ULL;
v___x_7010_ = lean_uint64_dec_eq(v___y_7007_, v___x_7009_);
if (v___x_7010_ == 0)
{
uint64_t v___x_7011_; uint64_t v___x_7012_; uint8_t v___x_7013_; 
v___x_7011_ = 32ULL;
v___x_7012_ = lean_uint64_shift_right(v___y_7007_, v___x_7011_);
v___x_7013_ = lean_uint64_dec_eq(v___x_7012_, v___x_7009_);
if (v___x_7013_ == 0)
{
v___y_6995_ = v___y_7005_;
v___y_6996_ = v___x_7009_;
v___y_6997_ = v___y_7006_;
v___y_6998_ = v___y_7007_;
v___y_6999_ = v___y_7008_;
v___y_7000_ = v___x_7011_;
v___y_7001_ = v___x_7012_;
goto v___jp_6994_;
}
else
{
v___y_6995_ = v___y_7005_;
v___y_6996_ = v___x_7009_;
v___y_6997_ = v___y_7006_;
v___y_6998_ = v___y_7007_;
v___y_6999_ = v___y_7008_;
v___y_7000_ = v___x_7011_;
v___y_7001_ = v___y_7007_;
goto v___jp_6994_;
}
}
else
{
if (v___y_7008_ == 0)
{
uint32_t v___x_7014_; 
v___x_7014_ = 0;
return v___x_7014_;
}
else
{
uint32_t v___x_7015_; 
v___x_7015_ = 2147483648;
return v___x_7015_;
}
}
}
v___jp_7016_:
{
uint64_t v___x_7023_; uint64_t v___x_7024_; uint64_t v___x_7025_; uint8_t v___x_7026_; 
v___x_7023_ = lean_uint64_mul(v___y_7018_, v___y_7019_);
v___x_7024_ = lean_uint64_add(v___y_7021_, v___y_7022_);
v___x_7025_ = 281474976710656ULL;
v___x_7026_ = lean_uint64_dec_lt(v___x_7023_, v___x_7025_);
if (v___x_7026_ == 0)
{
v___y_7005_ = v___y_7017_;
v___y_7006_ = v___x_7024_;
v___y_7007_ = v___x_7023_;
v___y_7008_ = v___y_7020_;
goto v___jp_7004_;
}
else
{
uint64_t v___x_7027_; uint8_t v___x_7028_; 
v___x_7027_ = 123ULL;
v___x_7028_ = lean_uint64_dec_le(v___x_7024_, v___x_7027_);
if (v___x_7028_ == 0)
{
v___y_7005_ = v___y_7017_;
v___y_7006_ = v___x_7024_;
v___y_7007_ = v___x_7023_;
v___y_7008_ = v___y_7020_;
goto v___jp_7004_;
}
else
{
uint64_t v___x_7029_; uint8_t v___x_7030_; 
v___x_7029_ = 0ULL;
v___x_7030_ = lean_uint64_dec_eq(v___x_7023_, v___x_7029_);
if (v___x_7030_ == 0)
{
uint64_t v___x_7031_; uint64_t v___x_7032_; uint8_t v___x_7033_; 
v___x_7031_ = 149ULL;
v___x_7032_ = lean_uint64_sub(v___x_7031_, v___x_7024_);
v___x_7033_ = lean_uint64_dec_eq(v___x_7032_, v___x_7029_);
if (v___x_7033_ == 0)
{
uint64_t v___x_7034_; uint8_t v___x_7035_; 
v___x_7034_ = 64ULL;
v___x_7035_ = lean_uint64_dec_lt(v___x_7032_, v___x_7034_);
if (v___x_7035_ == 0)
{
uint8_t v___x_7036_; 
v___x_7036_ = lean_uint64_dec_eq(v___x_7032_, v___x_7034_);
if (v___x_7036_ == 0)
{
v___y_6153_ = v___y_7017_;
v___y_6154_ = v___x_7029_;
v___y_6155_ = v___y_7020_;
v___y_6156_ = v___x_7029_;
goto v___jp_6152_;
}
else
{
uint64_t v___x_7037_; uint8_t v___x_7038_; 
v___x_7037_ = 9223372036854775808ULL;
v___x_7038_ = lean_uint64_dec_lt(v___x_7037_, v___x_7023_);
if (v___x_7038_ == 0)
{
v___y_6153_ = v___y_7017_;
v___y_6154_ = v___x_7029_;
v___y_6155_ = v___y_7020_;
v___y_6156_ = v___x_7029_;
goto v___jp_6152_;
}
else
{
uint64_t v___x_7039_; 
v___x_7039_ = 1ULL;
v___y_6153_ = v___y_7017_;
v___y_6154_ = v___x_7029_;
v___y_6155_ = v___y_7020_;
v___y_6156_ = v___x_7039_;
goto v___jp_6152_;
}
}
}
else
{
uint64_t v_quotient_7040_; uint64_t v___x_7041_; uint64_t v___x_7042_; uint64_t v___x_7043_; uint64_t v_remainder_7044_; uint64_t v___x_7045_; uint64_t v_half_7046_; uint8_t v___x_7047_; 
v_quotient_7040_ = lean_uint64_shift_right(v___x_7023_, v___x_7032_);
v___x_7041_ = 1ULL;
v___x_7042_ = lean_uint64_shift_left(v___x_7041_, v___x_7032_);
v___x_7043_ = lean_uint64_sub(v___x_7042_, v___x_7041_);
v_remainder_7044_ = lean_uint64_land(v___x_7023_, v___x_7043_);
v___x_7045_ = lean_uint64_sub(v___x_7032_, v___x_7041_);
v_half_7046_ = lean_uint64_shift_left(v___x_7041_, v___x_7045_);
v___x_7047_ = lean_uint64_dec_lt(v_remainder_7044_, v_half_7046_);
if (v___x_7047_ == 0)
{
uint8_t v___x_7048_; 
v___x_7048_ = lean_uint64_dec_lt(v_half_7046_, v_remainder_7044_);
if (v___x_7048_ == 0)
{
uint64_t v___x_7049_; uint8_t v___x_7050_; 
v___x_7049_ = lean_uint64_land(v_quotient_7040_, v___x_7041_);
v___x_7050_ = lean_uint64_dec_eq(v___x_7049_, v___x_7029_);
if (v___x_7050_ == 0)
{
uint64_t v___x_7051_; 
v___x_7051_ = lean_uint64_add(v_quotient_7040_, v___x_7041_);
v___y_6153_ = v___y_7017_;
v___y_6154_ = v___x_7029_;
v___y_6155_ = v___y_7020_;
v___y_6156_ = v___x_7051_;
goto v___jp_6152_;
}
else
{
v___y_6153_ = v___y_7017_;
v___y_6154_ = v___x_7029_;
v___y_6155_ = v___y_7020_;
v___y_6156_ = v_quotient_7040_;
goto v___jp_6152_;
}
}
else
{
uint64_t v___x_7052_; 
v___x_7052_ = lean_uint64_add(v_quotient_7040_, v___x_7041_);
v___y_6153_ = v___y_7017_;
v___y_6154_ = v___x_7029_;
v___y_6155_ = v___y_7020_;
v___y_6156_ = v___x_7052_;
goto v___jp_6152_;
}
}
else
{
v___y_6153_ = v___y_7017_;
v___y_6154_ = v___x_7029_;
v___y_6155_ = v___y_7020_;
v___y_6156_ = v_quotient_7040_;
goto v___jp_6152_;
}
}
}
else
{
v___y_6153_ = v___y_7017_;
v___y_6154_ = v___x_7029_;
v___y_6155_ = v___y_7020_;
v___y_6156_ = v___x_7023_;
goto v___jp_6152_;
}
}
else
{
if (v___y_7020_ == 0)
{
uint32_t v___x_7053_; 
v___x_7053_ = 0;
return v___x_7053_;
}
else
{
uint32_t v___x_7054_; 
v___x_7054_ = 2147483648;
return v___x_7054_;
}
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_runNativeProduct___lam__1___boxed(lean_object* v___y_7337_, lean_object* v___y_7338_){
_start:
{
uint32_t v___y_5334__boxed_7339_; uint32_t v___y_5335__boxed_7340_; uint32_t v_res_7341_; lean_object* v_r_7342_; 
v___y_5334__boxed_7339_ = lean_unbox_uint32(v___y_7337_);
lean_dec(v___y_7337_);
v___y_5335__boxed_7340_ = lean_unbox_uint32(v___y_7338_);
lean_dec(v___y_7338_);
v_res_7341_ = lp_competition_runNativeProduct___lam__1(v___y_5334__boxed_7339_, v___y_5335__boxed_7340_);
v_r_7342_ = lean_box_uint32(v_res_7341_);
return v_r_7342_;
}
}
LEAN_EXPORT lean_object* lp_competition_runNativeProduct(){
_start:
{
lean_object* v___f_7345_; lean_object* v___f_7346_; lean_object* v___x_7347_; lean_object* v___x_7348_; lean_object* v___x_7349_; 
v___f_7345_ = ((lean_object*)(lp_competition_runControl___closed__0));
v___f_7346_ = ((lean_object*)(lp_competition_runNativeProduct___closed__0));
v___x_7347_ = ((lean_object*)(lp_competition_runControl___closed__2));
v___x_7348_ = ((lean_object*)(lp_competition_runControl___closed__3));
v___x_7349_ = lp_competition_Bench_Suite_run(v___f_7345_, v___f_7346_, v___x_7347_, v___x_7348_);
return v___x_7349_;
}
}
LEAN_EXPORT lean_object* lp_competition_runNativeProduct___boxed(lean_object* v_a_7350_){
_start:
{
lean_object* v_res_7351_; 
v_res_7351_ = lp_competition_runNativeProduct();
return v_res_7351_;
}
}
LEAN_EXPORT uint32_t lp_competition_runResident16___lam__1(uint32_t v___y_7352_, uint32_t v___y_7353_){
_start:
{
uint32_t v___y_7355_; uint32_t v___y_7359_; uint32_t v___y_7363_; uint32_t v___y_7364_; uint32_t v___y_7365_; uint64_t v___y_7369_; uint8_t v___y_7370_; uint32_t v___y_7371_; uint64_t v___y_7372_; uint32_t v___y_7384_; uint32_t v___y_7385_; uint32_t v___y_7386_; uint8_t v___y_7390_; uint32_t v___y_7391_; uint64_t v___y_7392_; uint64_t v___y_7393_; uint8_t v___y_7405_; uint8_t v___y_7421_; uint8_t v___y_7435_; uint8_t v___y_7452_; float v___y_7459_; float v___y_7460_; float v___y_7474_; uint8_t v___y_7475_; float v___y_7490_; uint32_t v___x_7499_; uint32_t v___x_7500_; uint8_t v___y_7502_; uint32_t v___x_7514_; uint32_t v___y_7516_; uint32_t v___y_7517_; uint32_t v___y_7518_; uint32_t v___y_7519_; uint8_t v___y_7526_; uint32_t v___y_7527_; uint32_t v___y_7528_; uint32_t v___y_7529_; uint64_t v___y_7533_; uint64_t v___y_7534_; uint8_t v___y_7535_; uint32_t v___y_7536_; uint64_t v___y_7537_; uint64_t v___y_7547_; uint8_t v___y_7548_; uint8_t v___y_7549_; uint64_t v___y_7550_; uint32_t v___y_7551_; uint64_t v___y_7552_; uint64_t v___y_7559_; uint8_t v___y_7560_; uint64_t v___y_7561_; uint32_t v___y_7562_; uint64_t v___y_7563_; uint64_t v___y_7569_; uint8_t v___y_7570_; uint64_t v___y_7571_; uint32_t v___y_7572_; uint64_t v___y_7573_; uint64_t v___y_7574_; uint64_t v___y_7629_; uint8_t v___y_7630_; uint64_t v___y_7631_; uint32_t v___y_7632_; uint64_t v___y_7633_; uint64_t v___y_7634_; uint64_t v___y_7635_; uint64_t v___y_7641_; uint64_t v___y_7642_; uint8_t v___y_7643_; uint64_t v___y_7644_; uint64_t v___y_7645_; uint32_t v___y_7646_; uint64_t v___y_7647_; uint64_t v___y_7648_; uint64_t v___y_7649_; uint64_t v___y_7654_; uint8_t v___y_7655_; uint64_t v___y_7656_; uint64_t v___y_7657_; uint32_t v___y_7658_; uint64_t v___y_7659_; uint64_t v___y_7660_; uint64_t v___y_7665_; uint64_t v___y_7666_; uint64_t v___y_7667_; uint8_t v___y_7668_; uint64_t v___y_7669_; uint32_t v___y_7670_; uint64_t v___y_7671_; uint64_t v___y_7672_; uint64_t v___y_7673_; uint64_t v___y_7678_; uint8_t v___y_7679_; uint64_t v___y_7680_; uint32_t v___y_7681_; uint64_t v___y_7682_; uint64_t v___y_7683_; uint64_t v___y_7684_; uint64_t v___y_7689_; uint64_t v___y_7690_; uint64_t v___y_7691_; uint8_t v___y_7692_; uint64_t v___y_7693_; uint32_t v___y_7694_; uint64_t v___y_7695_; uint64_t v___y_7696_; uint64_t v___y_7697_; uint64_t v___y_7702_; uint64_t v___y_7703_; uint8_t v___y_7704_; uint64_t v___y_7705_; uint32_t v___y_7706_; uint64_t v___y_7707_; uint64_t v___y_7708_; uint64_t v___y_7713_; uint64_t v___y_7714_; uint64_t v___y_7715_; uint64_t v___y_7716_; uint8_t v___y_7717_; uint64_t v___y_7718_; uint32_t v___y_7719_; uint64_t v___y_7720_; uint64_t v___y_7721_; uint64_t v___y_7726_; uint64_t v___y_7727_; uint8_t v___y_7728_; uint64_t v___y_7729_; uint32_t v___y_7730_; uint64_t v___y_7731_; uint64_t v___y_7732_; uint64_t v___y_7737_; uint64_t v___y_7738_; uint8_t v___y_7739_; uint64_t v___y_7740_; uint32_t v___y_7741_; uint64_t v___y_7742_; uint64_t v___y_7743_; uint8_t v___y_7747_; uint64_t v___y_7748_; uint32_t v___y_7749_; uint64_t v___y_7750_; uint8_t v___y_7759_; uint64_t v___y_7760_; uint64_t v___y_7761_; uint32_t v___y_7762_; uint64_t v___y_7763_; uint64_t v___y_7764_; uint32_t v_ex_7797_; uint32_t v___x_7798_; uint32_t v_ey_7799_; uint64_t v___y_7801_; uint8_t v___y_7802_; uint64_t v___y_7803_; uint32_t v___y_7804_; uint64_t v___y_7805_; uint8_t v___y_7812_; uint32_t v___y_7813_; uint64_t v___y_7814_; uint64_t v___y_7815_; uint8_t v___y_7822_; uint32_t v___y_7823_; uint32_t v___y_7824_; uint64_t v___y_7825_; uint8_t v___y_7833_; uint32_t v___x_7843_; uint32_t v___x_7844_; uint8_t v___x_7845_; uint8_t v___y_7847_; uint8_t v___y_7848_; uint8_t v___y_7850_; uint8_t v___y_7851_; uint8_t v___y_7852_; uint8_t v___y_7854_; uint8_t v___y_7855_; uint8_t v___y_7861_; 
v___x_7499_ = 23;
v___x_7500_ = lean_uint32_shift_right(v___y_7352_, v___x_7499_);
v___x_7514_ = 255;
v_ex_7797_ = lean_uint32_land(v___x_7500_, v___x_7514_);
v___x_7798_ = lean_uint32_shift_right(v___y_7353_, v___x_7499_);
v_ey_7799_ = lean_uint32_land(v___x_7798_, v___x_7514_);
v___x_7843_ = lean_uint32_add(v_ex_7797_, v_ey_7799_);
v___x_7844_ = 128;
v___x_7845_ = lean_uint32_dec_lt(v___x_7843_, v___x_7844_);
if (v___x_7845_ == 0)
{
uint32_t v___x_7870_; uint32_t v_a_7871_; uint32_t v___x_7872_; uint32_t v___x_7873_; uint32_t v___x_7874_; uint8_t v___x_7875_; 
v___x_7870_ = 2147483647;
v_a_7871_ = lean_uint32_land(v___y_7352_, v___x_7870_);
v___x_7872_ = 201326591;
v___x_7873_ = 1;
v___x_7874_ = lean_uint32_sub(v_a_7871_, v___x_7873_);
v___x_7875_ = lean_uint32_dec_le(v___x_7872_, v___x_7874_);
if (v___x_7875_ == 0)
{
v___y_7502_ = v___x_7875_;
goto v___jp_7501_;
}
else
{
uint32_t v___x_7876_; uint8_t v___x_7877_; 
v___x_7876_ = 2139095040;
v___x_7877_ = lean_uint32_dec_lt(v_a_7871_, v___x_7876_);
v___y_7502_ = v___x_7877_;
goto v___jp_7501_;
}
}
else
{
uint32_t v___x_7878_; uint32_t v___x_7879_; uint32_t v___x_7880_; uint8_t v___x_7881_; 
v___x_7878_ = 4278190080;
v___x_7879_ = 1;
v___x_7880_ = lean_uint32_shift_left(v___y_7352_, v___x_7879_);
v___x_7881_ = lean_uint32_dec_le(v___x_7878_, v___x_7880_);
if (v___x_7881_ == 0)
{
uint32_t v___x_7882_; uint8_t v___x_7883_; 
v___x_7882_ = lean_uint32_shift_left(v___y_7353_, v___x_7879_);
v___x_7883_ = lean_uint32_dec_le(v___x_7878_, v___x_7882_);
v___y_7861_ = v___x_7883_;
goto v___jp_7860_;
}
else
{
v___y_7861_ = v___x_7881_;
goto v___jp_7860_;
}
}
v___jp_7354_:
{
uint32_t v___x_7356_; uint32_t v___x_7357_; 
v___x_7356_ = 8388608;
v___x_7357_ = lean_uint32_lor(v___y_7355_, v___x_7356_);
return v___x_7357_;
}
v___jp_7358_:
{
uint32_t v___x_7360_; uint32_t v___x_7361_; 
v___x_7360_ = 8388608;
v___x_7361_ = lean_uint32_lor(v___y_7359_, v___x_7360_);
return v___x_7361_;
}
v___jp_7362_:
{
uint32_t v___x_7366_; uint32_t v___x_7367_; 
v___x_7366_ = lean_uint32_land(v___y_7363_, v___y_7364_);
v___x_7367_ = lean_uint32_lor(v___y_7365_, v___x_7366_);
return v___x_7367_;
}
v___jp_7368_:
{
uint8_t v___x_7373_; 
v___x_7373_ = lean_uint64_dec_eq(v___y_7372_, v___y_7369_);
if (v___x_7373_ == 0)
{
uint64_t v___x_7374_; uint8_t v___x_7375_; 
v___x_7374_ = 8388608ULL;
v___x_7375_ = lean_uint64_dec_eq(v___y_7372_, v___x_7374_);
if (v___x_7375_ == 0)
{
uint32_t v___x_7376_; 
v___x_7376_ = lean_uint64_to_uint32(v___y_7372_);
if (v___y_7370_ == 0)
{
uint32_t v___x_7377_; 
v___x_7377_ = 0;
v___y_7363_ = v___x_7376_;
v___y_7364_ = v___y_7371_;
v___y_7365_ = v___x_7377_;
goto v___jp_7362_;
}
else
{
uint32_t v___x_7378_; 
v___x_7378_ = 2147483648;
v___y_7363_ = v___x_7376_;
v___y_7364_ = v___y_7371_;
v___y_7365_ = v___x_7378_;
goto v___jp_7362_;
}
}
else
{
if (v___y_7370_ == 0)
{
uint32_t v___x_7379_; 
v___x_7379_ = 0;
v___y_7359_ = v___x_7379_;
goto v___jp_7358_;
}
else
{
uint32_t v___x_7380_; 
v___x_7380_ = 2147483648;
v___y_7359_ = v___x_7380_;
goto v___jp_7358_;
}
}
}
else
{
if (v___y_7370_ == 0)
{
uint32_t v___x_7381_; 
v___x_7381_ = 0;
return v___x_7381_;
}
else
{
uint32_t v___x_7382_; 
v___x_7382_ = 2147483648;
return v___x_7382_;
}
}
}
v___jp_7383_:
{
uint32_t v___x_7387_; uint32_t v___x_7388_; 
v___x_7387_ = lean_uint32_land(v___y_7384_, v___y_7385_);
v___x_7388_ = lean_uint32_lor(v___y_7386_, v___x_7387_);
return v___x_7388_;
}
v___jp_7389_:
{
uint8_t v___x_7394_; 
v___x_7394_ = lean_uint64_dec_eq(v___y_7393_, v___y_7392_);
if (v___x_7394_ == 0)
{
uint64_t v___x_7395_; uint8_t v___x_7396_; 
v___x_7395_ = 8388608ULL;
v___x_7396_ = lean_uint64_dec_eq(v___y_7393_, v___x_7395_);
if (v___x_7396_ == 0)
{
uint32_t v___x_7397_; 
v___x_7397_ = lean_uint64_to_uint32(v___y_7393_);
if (v___y_7390_ == 0)
{
uint32_t v___x_7398_; 
v___x_7398_ = 0;
v___y_7384_ = v___x_7397_;
v___y_7385_ = v___y_7391_;
v___y_7386_ = v___x_7398_;
goto v___jp_7383_;
}
else
{
uint32_t v___x_7399_; 
v___x_7399_ = 2147483648;
v___y_7384_ = v___x_7397_;
v___y_7385_ = v___y_7391_;
v___y_7386_ = v___x_7399_;
goto v___jp_7383_;
}
}
else
{
if (v___y_7390_ == 0)
{
uint32_t v___x_7400_; 
v___x_7400_ = 0;
v___y_7355_ = v___x_7400_;
goto v___jp_7354_;
}
else
{
uint32_t v___x_7401_; 
v___x_7401_ = 2147483648;
v___y_7355_ = v___x_7401_;
goto v___jp_7354_;
}
}
}
else
{
if (v___y_7390_ == 0)
{
uint32_t v___x_7402_; 
v___x_7402_ = 0;
return v___x_7402_;
}
else
{
uint32_t v___x_7403_; 
v___x_7403_ = 2147483648;
return v___x_7403_;
}
}
}
v___jp_7404_:
{
if (v___y_7405_ == 0)
{
uint32_t v___x_7406_; 
v___x_7406_ = lp_competition_Submission_FastMul_mul(v___y_7352_, v___y_7353_);
return v___x_7406_;
}
else
{
uint32_t v___x_7407_; uint32_t v___x_7408_; 
v___x_7407_ = 4194304;
v___x_7408_ = lean_uint32_lor(v___y_7353_, v___x_7407_);
return v___x_7408_;
}
}
v___jp_7409_:
{
uint32_t v___x_7410_; uint32_t v___x_7411_; uint32_t v___x_7412_; uint32_t v___x_7413_; uint8_t v___x_7414_; 
v___x_7410_ = 23;
v___x_7411_ = lean_uint32_shift_right(v___y_7353_, v___x_7410_);
v___x_7412_ = 255;
v___x_7413_ = lean_uint32_land(v___x_7411_, v___x_7412_);
v___x_7414_ = lean_uint32_dec_eq(v___x_7413_, v___x_7412_);
if (v___x_7414_ == 0)
{
v___y_7405_ = v___x_7414_;
goto v___jp_7404_;
}
else
{
uint32_t v___x_7415_; uint32_t v___x_7416_; uint32_t v___x_7417_; uint8_t v___x_7418_; 
v___x_7415_ = 8388607;
v___x_7416_ = lean_uint32_land(v___y_7353_, v___x_7415_);
v___x_7417_ = 0;
v___x_7418_ = lean_uint32_dec_eq(v___x_7416_, v___x_7417_);
if (v___x_7418_ == 0)
{
v___y_7405_ = v___x_7414_;
goto v___jp_7404_;
}
else
{
uint32_t v___x_7419_; 
v___x_7419_ = lp_competition_Submission_FastMul_mul(v___y_7352_, v___y_7353_);
return v___x_7419_;
}
}
}
v___jp_7420_:
{
if (v___y_7421_ == 0)
{
goto v___jp_7409_;
}
else
{
uint32_t v___x_7422_; uint32_t v___x_7423_; 
v___x_7422_ = 4194304;
v___x_7423_ = lean_uint32_lor(v___y_7352_, v___x_7422_);
return v___x_7423_;
}
}
v___jp_7424_:
{
uint32_t v___x_7425_; uint32_t v___x_7426_; uint32_t v___x_7427_; uint32_t v___x_7428_; uint8_t v___x_7429_; 
v___x_7425_ = 23;
v___x_7426_ = lean_uint32_shift_right(v___y_7352_, v___x_7425_);
v___x_7427_ = 255;
v___x_7428_ = lean_uint32_land(v___x_7426_, v___x_7427_);
v___x_7429_ = lean_uint32_dec_eq(v___x_7428_, v___x_7427_);
if (v___x_7429_ == 0)
{
v___y_7421_ = v___x_7429_;
goto v___jp_7420_;
}
else
{
uint32_t v___x_7430_; uint32_t v___x_7431_; uint32_t v___x_7432_; uint8_t v___x_7433_; 
v___x_7430_ = 8388607;
v___x_7431_ = lean_uint32_land(v___y_7352_, v___x_7430_);
v___x_7432_ = 0;
v___x_7433_ = lean_uint32_dec_eq(v___x_7431_, v___x_7432_);
if (v___x_7433_ == 0)
{
v___y_7421_ = v___x_7429_;
goto v___jp_7420_;
}
else
{
goto v___jp_7409_;
}
}
}
v___jp_7434_:
{
if (v___y_7435_ == 0)
{
goto v___jp_7424_;
}
else
{
uint32_t v___x_7436_; uint32_t v___x_7437_; uint32_t v___x_7438_; uint8_t v___x_7439_; 
v___x_7436_ = 4194304;
v___x_7437_ = lean_uint32_land(v___y_7353_, v___x_7436_);
v___x_7438_ = 0;
v___x_7439_ = lean_uint32_dec_eq(v___x_7437_, v___x_7438_);
if (v___x_7439_ == 0)
{
goto v___jp_7424_;
}
else
{
uint32_t v___x_7440_; 
v___x_7440_ = lean_uint32_lor(v___y_7353_, v___x_7436_);
return v___x_7440_;
}
}
}
v___jp_7441_:
{
uint32_t v___x_7442_; uint32_t v___x_7443_; uint32_t v___x_7444_; uint32_t v___x_7445_; uint8_t v___x_7446_; 
v___x_7442_ = 23;
v___x_7443_ = lean_uint32_shift_right(v___y_7353_, v___x_7442_);
v___x_7444_ = 255;
v___x_7445_ = lean_uint32_land(v___x_7443_, v___x_7444_);
v___x_7446_ = lean_uint32_dec_eq(v___x_7445_, v___x_7444_);
if (v___x_7446_ == 0)
{
v___y_7435_ = v___x_7446_;
goto v___jp_7434_;
}
else
{
uint32_t v___x_7447_; uint32_t v___x_7448_; uint32_t v___x_7449_; uint8_t v___x_7450_; 
v___x_7447_ = 8388607;
v___x_7448_ = lean_uint32_land(v___y_7353_, v___x_7447_);
v___x_7449_ = 0;
v___x_7450_ = lean_uint32_dec_eq(v___x_7448_, v___x_7449_);
if (v___x_7450_ == 0)
{
v___y_7435_ = v___x_7446_;
goto v___jp_7434_;
}
else
{
goto v___jp_7424_;
}
}
}
v___jp_7451_:
{
if (v___y_7452_ == 0)
{
goto v___jp_7441_;
}
else
{
uint32_t v___x_7453_; uint32_t v___x_7454_; uint32_t v___x_7455_; uint8_t v___x_7456_; 
v___x_7453_ = 4194304;
v___x_7454_ = lean_uint32_land(v___y_7352_, v___x_7453_);
v___x_7455_ = 0;
v___x_7456_ = lean_uint32_dec_eq(v___x_7454_, v___x_7455_);
if (v___x_7456_ == 0)
{
goto v___jp_7441_;
}
else
{
uint32_t v___x_7457_; 
v___x_7457_ = lean_uint32_lor(v___y_7352_, v___x_7453_);
return v___x_7457_;
}
}
}
v___jp_7458_:
{
float v_result_7461_; uint8_t v___x_7462_; 
v_result_7461_ = lean_float32_mul(v___y_7459_, v___y_7460_);
v___x_7462_ = lean_float32_beq(v_result_7461_, v_result_7461_);
if (v___x_7462_ == 0)
{
uint32_t v___x_7463_; uint32_t v___x_7464_; uint32_t v___x_7465_; uint32_t v___x_7466_; uint8_t v___x_7467_; 
v___x_7463_ = 23;
v___x_7464_ = lean_uint32_shift_right(v___y_7352_, v___x_7463_);
v___x_7465_ = 255;
v___x_7466_ = lean_uint32_land(v___x_7464_, v___x_7465_);
v___x_7467_ = lean_uint32_dec_eq(v___x_7466_, v___x_7465_);
if (v___x_7467_ == 0)
{
v___y_7452_ = v___x_7467_;
goto v___jp_7451_;
}
else
{
uint32_t v___x_7468_; uint32_t v___x_7469_; uint32_t v___x_7470_; uint8_t v___x_7471_; 
v___x_7468_ = 8388607;
v___x_7469_ = lean_uint32_land(v___y_7352_, v___x_7468_);
v___x_7470_ = 0;
v___x_7471_ = lean_uint32_dec_eq(v___x_7469_, v___x_7470_);
if (v___x_7471_ == 0)
{
v___y_7452_ = v___x_7467_;
goto v___jp_7451_;
}
else
{
goto v___jp_7441_;
}
}
}
else
{
uint32_t v___x_7472_; 
v___x_7472_ = lean_float32_to_bits(v_result_7461_);
return v___x_7472_;
}
}
v___jp_7473_:
{
if (v___y_7475_ == 0)
{
float v___x_7476_; 
v___x_7476_ = lean_float32_of_bits(v___y_7353_);
v___y_7459_ = v___y_7474_;
v___y_7460_ = v___x_7476_;
goto v___jp_7458_;
}
else
{
uint32_t v___x_7477_; uint32_t v___x_7478_; uint32_t v___x_7479_; uint32_t v___x_7480_; float v___x_7481_; lean_object* v___x_7482_; uint32_t v___x_7483_; uint32_t v___x_7484_; lean_object* v___x_7485_; lean_object* v___x_7486_; float v___x_7487_; float v___x_7488_; 
v___x_7477_ = 8388607;
v___x_7478_ = lean_uint32_land(v___y_7353_, v___x_7477_);
v___x_7479_ = 8388608;
v___x_7480_ = lean_uint32_lor(v___x_7478_, v___x_7479_);
v___x_7481_ = lean_uint32_to_float32(v___x_7480_);
v___x_7482_ = lp_competition_R2W01b_scaleTable;
v___x_7483_ = 23;
v___x_7484_ = lean_uint32_shift_right(v___y_7353_, v___x_7483_);
v___x_7485_ = lean_uint32_to_nat(v___x_7484_);
v___x_7486_ = lean_array_fget_borrowed(v___x_7482_, v___x_7485_);
lean_dec(v___x_7485_);
v___x_7487_ = lean_unbox_float32(v___x_7486_);
v___x_7488_ = lean_float32_mul(v___x_7481_, v___x_7487_);
v___y_7459_ = v___y_7474_;
v___y_7460_ = v___x_7488_;
goto v___jp_7458_;
}
}
v___jp_7489_:
{
uint32_t v___x_7491_; uint32_t v_a_7492_; uint32_t v___x_7493_; uint32_t v___x_7494_; uint32_t v___x_7495_; uint8_t v___x_7496_; 
v___x_7491_ = 2147483647;
v_a_7492_ = lean_uint32_land(v___y_7353_, v___x_7491_);
v___x_7493_ = 201326591;
v___x_7494_ = 1;
v___x_7495_ = lean_uint32_sub(v_a_7492_, v___x_7494_);
v___x_7496_ = lean_uint32_dec_le(v___x_7493_, v___x_7495_);
if (v___x_7496_ == 0)
{
v___y_7474_ = v___y_7490_;
v___y_7475_ = v___x_7496_;
goto v___jp_7473_;
}
else
{
uint32_t v___x_7497_; uint8_t v___x_7498_; 
v___x_7497_ = 2139095040;
v___x_7498_ = lean_uint32_dec_lt(v_a_7492_, v___x_7497_);
v___y_7474_ = v___y_7490_;
v___y_7475_ = v___x_7498_;
goto v___jp_7473_;
}
}
v___jp_7501_:
{
if (v___y_7502_ == 0)
{
float v___x_7503_; 
v___x_7503_ = lean_float32_of_bits(v___y_7352_);
v___y_7490_ = v___x_7503_;
goto v___jp_7489_;
}
else
{
uint32_t v___x_7504_; uint32_t v___x_7505_; uint32_t v___x_7506_; uint32_t v___x_7507_; float v___x_7508_; lean_object* v___x_7509_; lean_object* v___x_7510_; lean_object* v___x_7511_; float v___x_7512_; float v___x_7513_; 
v___x_7504_ = 8388607;
v___x_7505_ = lean_uint32_land(v___y_7352_, v___x_7504_);
v___x_7506_ = 8388608;
v___x_7507_ = lean_uint32_lor(v___x_7505_, v___x_7506_);
v___x_7508_ = lean_uint32_to_float32(v___x_7507_);
v___x_7509_ = lp_competition_R2W01b_scaleTable;
v___x_7510_ = lean_uint32_to_nat(v___x_7500_);
v___x_7511_ = lean_array_fget_borrowed(v___x_7509_, v___x_7510_);
lean_dec(v___x_7510_);
v___x_7512_ = lean_unbox_float32(v___x_7511_);
v___x_7513_ = lean_float32_mul(v___x_7508_, v___x_7512_);
v___y_7490_ = v___x_7513_;
goto v___jp_7489_;
}
}
v___jp_7515_:
{
uint32_t v___x_7520_; uint32_t v___x_7521_; uint32_t v___x_7522_; uint32_t v___x_7523_; uint32_t v___x_7524_; 
v___x_7520_ = lean_uint32_land(v___y_7516_, v___x_7514_);
v___x_7521_ = lean_uint32_shift_left(v___x_7520_, v___x_7499_);
v___x_7522_ = lean_uint32_lor(v___y_7519_, v___x_7521_);
v___x_7523_ = lean_uint32_land(v___y_7518_, v___y_7517_);
v___x_7524_ = lean_uint32_lor(v___x_7522_, v___x_7523_);
return v___x_7524_;
}
v___jp_7525_:
{
if (v___y_7526_ == 0)
{
uint32_t v___x_7530_; 
v___x_7530_ = 0;
v___y_7516_ = v___y_7527_;
v___y_7517_ = v___y_7528_;
v___y_7518_ = v___y_7529_;
v___y_7519_ = v___x_7530_;
goto v___jp_7515_;
}
else
{
uint32_t v___x_7531_; 
v___x_7531_ = 2147483648;
v___y_7516_ = v___y_7527_;
v___y_7517_ = v___y_7528_;
v___y_7518_ = v___y_7529_;
v___y_7519_ = v___x_7531_;
goto v___jp_7515_;
}
}
v___jp_7532_:
{
uint64_t v___x_7538_; uint64_t v_encodedExponent_7539_; uint32_t v___x_7540_; uint64_t v___x_7541_; uint8_t v___x_7542_; 
v___x_7538_ = 171ULL;
v_encodedExponent_7539_ = lean_uint64_sub(v___y_7534_, v___x_7538_);
v___x_7540_ = lean_uint64_to_uint32(v_encodedExponent_7539_);
v___x_7541_ = 8388608ULL;
v___x_7542_ = lean_uint64_dec_lt(v___y_7537_, v___x_7541_);
if (v___x_7542_ == 0)
{
uint64_t v___x_7543_; uint32_t v___x_7544_; 
v___x_7543_ = lean_uint64_sub(v___y_7537_, v___x_7541_);
v___x_7544_ = lean_uint64_to_uint32(v___x_7543_);
v___y_7526_ = v___y_7535_;
v___y_7527_ = v___x_7540_;
v___y_7528_ = v___y_7536_;
v___y_7529_ = v___x_7544_;
goto v___jp_7525_;
}
else
{
uint32_t v___x_7545_; 
v___x_7545_ = lean_uint64_to_uint32(v___y_7533_);
v___y_7526_ = v___y_7535_;
v___y_7527_ = v___x_7540_;
v___y_7528_ = v___y_7536_;
v___y_7529_ = v___x_7545_;
goto v___jp_7525_;
}
}
v___jp_7546_:
{
uint64_t v___x_7553_; uint8_t v___x_7554_; 
v___x_7553_ = 425ULL;
v___x_7554_ = lean_uint64_dec_lt(v___x_7553_, v___y_7552_);
if (v___x_7554_ == 0)
{
if (v___y_7548_ == 0)
{
v___y_7533_ = v___y_7547_;
v___y_7534_ = v___y_7552_;
v___y_7535_ = v___y_7549_;
v___y_7536_ = v___y_7551_;
v___y_7537_ = v___y_7550_;
goto v___jp_7532_;
}
else
{
uint64_t v___x_7555_; 
v___x_7555_ = 8388608ULL;
v___y_7533_ = v___y_7547_;
v___y_7534_ = v___y_7552_;
v___y_7535_ = v___y_7549_;
v___y_7536_ = v___y_7551_;
v___y_7537_ = v___x_7555_;
goto v___jp_7532_;
}
}
else
{
if (v___y_7549_ == 0)
{
uint32_t v___x_7556_; 
v___x_7556_ = 2139095040;
return v___x_7556_;
}
else
{
uint32_t v___x_7557_; 
v___x_7557_ = 4286578688;
return v___x_7557_;
}
}
}
v___jp_7558_:
{
uint64_t v___x_7564_; uint8_t v_carry_7565_; 
v___x_7564_ = 16777216ULL;
v_carry_7565_ = lean_uint64_dec_eq(v___y_7563_, v___x_7564_);
if (v_carry_7565_ == 0)
{
v___y_7547_ = v___y_7559_;
v___y_7548_ = v_carry_7565_;
v___y_7549_ = v___y_7560_;
v___y_7550_ = v___y_7563_;
v___y_7551_ = v___y_7562_;
v___y_7552_ = v___y_7561_;
goto v___jp_7546_;
}
else
{
uint64_t v___x_7566_; uint64_t v___x_7567_; 
v___x_7566_ = 1ULL;
v___x_7567_ = lean_uint64_add(v___y_7561_, v___x_7566_);
v___y_7547_ = v___y_7559_;
v___y_7548_ = v_carry_7565_;
v___y_7549_ = v___y_7560_;
v___y_7550_ = v___y_7563_;
v___y_7551_ = v___y_7562_;
v___y_7552_ = v___x_7567_;
goto v___jp_7546_;
}
}
v___jp_7568_:
{
uint64_t v_position_7575_; uint64_t v___x_7576_; uint8_t v___x_7577_; 
v_position_7575_ = lean_uint64_add(v___y_7574_, v___y_7573_);
v___x_7576_ = 172ULL;
v___x_7577_ = lean_uint64_dec_lt(v_position_7575_, v___x_7576_);
if (v___x_7577_ == 0)
{
uint64_t v___x_7578_; uint8_t v___x_7579_; 
v___x_7578_ = 23ULL;
v___x_7579_ = lean_uint64_dec_lt(v___y_7574_, v___x_7578_);
if (v___x_7579_ == 0)
{
uint64_t v___x_7580_; uint8_t v___x_7581_; 
v___x_7580_ = lean_uint64_sub(v___y_7574_, v___x_7578_);
v___x_7581_ = lean_uint64_dec_eq(v___x_7580_, v___y_7569_);
if (v___x_7581_ == 0)
{
uint64_t v___x_7582_; uint8_t v___x_7583_; 
v___x_7582_ = 64ULL;
v___x_7583_ = lean_uint64_dec_lt(v___x_7580_, v___x_7582_);
if (v___x_7583_ == 0)
{
uint8_t v___x_7584_; 
v___x_7584_ = lean_uint64_dec_eq(v___x_7580_, v___x_7582_);
if (v___x_7584_ == 0)
{
v___y_7559_ = v___y_7569_;
v___y_7560_ = v___y_7570_;
v___y_7561_ = v_position_7575_;
v___y_7562_ = v___y_7572_;
v___y_7563_ = v___y_7569_;
goto v___jp_7558_;
}
else
{
uint64_t v___x_7585_; uint8_t v___x_7586_; 
v___x_7585_ = 9223372036854775808ULL;
v___x_7586_ = lean_uint64_dec_lt(v___x_7585_, v___y_7571_);
if (v___x_7586_ == 0)
{
v___y_7559_ = v___y_7569_;
v___y_7560_ = v___y_7570_;
v___y_7561_ = v_position_7575_;
v___y_7562_ = v___y_7572_;
v___y_7563_ = v___y_7569_;
goto v___jp_7558_;
}
else
{
uint64_t v___x_7587_; 
v___x_7587_ = 1ULL;
v___y_7559_ = v___y_7569_;
v___y_7560_ = v___y_7570_;
v___y_7561_ = v_position_7575_;
v___y_7562_ = v___y_7572_;
v___y_7563_ = v___x_7587_;
goto v___jp_7558_;
}
}
}
else
{
uint64_t v_quotient_7588_; uint64_t v___x_7589_; uint64_t v___x_7590_; uint64_t v___x_7591_; uint64_t v_remainder_7592_; uint64_t v___x_7593_; uint64_t v_half_7594_; uint8_t v___x_7595_; 
v_quotient_7588_ = lean_uint64_shift_right(v___y_7571_, v___x_7580_);
v___x_7589_ = 1ULL;
v___x_7590_ = lean_uint64_shift_left(v___x_7589_, v___x_7580_);
v___x_7591_ = lean_uint64_sub(v___x_7590_, v___x_7589_);
v_remainder_7592_ = lean_uint64_land(v___y_7571_, v___x_7591_);
v___x_7593_ = lean_uint64_sub(v___x_7580_, v___x_7589_);
v_half_7594_ = lean_uint64_shift_left(v___x_7589_, v___x_7593_);
v___x_7595_ = lean_uint64_dec_lt(v_remainder_7592_, v_half_7594_);
if (v___x_7595_ == 0)
{
uint8_t v___x_7596_; 
v___x_7596_ = lean_uint64_dec_lt(v_half_7594_, v_remainder_7592_);
if (v___x_7596_ == 0)
{
uint64_t v___x_7597_; uint8_t v___x_7598_; 
v___x_7597_ = lean_uint64_land(v_quotient_7588_, v___x_7589_);
v___x_7598_ = lean_uint64_dec_eq(v___x_7597_, v___y_7569_);
if (v___x_7598_ == 0)
{
uint64_t v___x_7599_; 
v___x_7599_ = lean_uint64_add(v_quotient_7588_, v___x_7589_);
v___y_7559_ = v___y_7569_;
v___y_7560_ = v___y_7570_;
v___y_7561_ = v_position_7575_;
v___y_7562_ = v___y_7572_;
v___y_7563_ = v___x_7599_;
goto v___jp_7558_;
}
else
{
v___y_7559_ = v___y_7569_;
v___y_7560_ = v___y_7570_;
v___y_7561_ = v_position_7575_;
v___y_7562_ = v___y_7572_;
v___y_7563_ = v_quotient_7588_;
goto v___jp_7558_;
}
}
else
{
uint64_t v___x_7600_; 
v___x_7600_ = lean_uint64_add(v_quotient_7588_, v___x_7589_);
v___y_7559_ = v___y_7569_;
v___y_7560_ = v___y_7570_;
v___y_7561_ = v_position_7575_;
v___y_7562_ = v___y_7572_;
v___y_7563_ = v___x_7600_;
goto v___jp_7558_;
}
}
else
{
v___y_7559_ = v___y_7569_;
v___y_7560_ = v___y_7570_;
v___y_7561_ = v_position_7575_;
v___y_7562_ = v___y_7572_;
v___y_7563_ = v_quotient_7588_;
goto v___jp_7558_;
}
}
}
else
{
v___y_7559_ = v___y_7569_;
v___y_7560_ = v___y_7570_;
v___y_7561_ = v_position_7575_;
v___y_7562_ = v___y_7572_;
v___y_7563_ = v___y_7571_;
goto v___jp_7558_;
}
}
else
{
uint64_t v___x_7601_; uint64_t v___x_7602_; 
v___x_7601_ = lean_uint64_sub(v___x_7578_, v___y_7574_);
v___x_7602_ = lean_uint64_shift_left(v___y_7571_, v___x_7601_);
v___y_7559_ = v___y_7569_;
v___y_7560_ = v___y_7570_;
v___y_7561_ = v_position_7575_;
v___y_7562_ = v___y_7572_;
v___y_7563_ = v___x_7602_;
goto v___jp_7558_;
}
}
else
{
uint64_t v___x_7603_; uint8_t v___x_7604_; 
v___x_7603_ = 149ULL;
v___x_7604_ = lean_uint64_dec_lt(v___y_7573_, v___x_7603_);
if (v___x_7604_ == 0)
{
uint64_t v___x_7605_; uint64_t v___x_7606_; 
v___x_7605_ = lean_uint64_sub(v___y_7573_, v___x_7603_);
v___x_7606_ = lean_uint64_shift_left(v___y_7571_, v___x_7605_);
v___y_7369_ = v___y_7569_;
v___y_7370_ = v___y_7570_;
v___y_7371_ = v___y_7572_;
v___y_7372_ = v___x_7606_;
goto v___jp_7368_;
}
else
{
uint64_t v___x_7607_; uint8_t v___x_7608_; 
v___x_7607_ = lean_uint64_sub(v___x_7603_, v___y_7573_);
v___x_7608_ = lean_uint64_dec_eq(v___x_7607_, v___y_7569_);
if (v___x_7608_ == 0)
{
uint64_t v___x_7609_; uint8_t v___x_7610_; 
v___x_7609_ = 64ULL;
v___x_7610_ = lean_uint64_dec_lt(v___x_7607_, v___x_7609_);
if (v___x_7610_ == 0)
{
uint8_t v___x_7611_; 
v___x_7611_ = lean_uint64_dec_eq(v___x_7607_, v___x_7609_);
if (v___x_7611_ == 0)
{
v___y_7369_ = v___y_7569_;
v___y_7370_ = v___y_7570_;
v___y_7371_ = v___y_7572_;
v___y_7372_ = v___y_7569_;
goto v___jp_7368_;
}
else
{
uint64_t v___x_7612_; uint8_t v___x_7613_; 
v___x_7612_ = 9223372036854775808ULL;
v___x_7613_ = lean_uint64_dec_lt(v___x_7612_, v___y_7571_);
if (v___x_7613_ == 0)
{
v___y_7369_ = v___y_7569_;
v___y_7370_ = v___y_7570_;
v___y_7371_ = v___y_7572_;
v___y_7372_ = v___y_7569_;
goto v___jp_7368_;
}
else
{
uint64_t v___x_7614_; 
v___x_7614_ = 1ULL;
v___y_7369_ = v___y_7569_;
v___y_7370_ = v___y_7570_;
v___y_7371_ = v___y_7572_;
v___y_7372_ = v___x_7614_;
goto v___jp_7368_;
}
}
}
else
{
uint64_t v_quotient_7615_; uint64_t v___x_7616_; uint64_t v___x_7617_; uint64_t v___x_7618_; uint64_t v_remainder_7619_; uint64_t v___x_7620_; uint64_t v_half_7621_; uint8_t v___x_7622_; 
v_quotient_7615_ = lean_uint64_shift_right(v___y_7571_, v___x_7607_);
v___x_7616_ = 1ULL;
v___x_7617_ = lean_uint64_shift_left(v___x_7616_, v___x_7607_);
v___x_7618_ = lean_uint64_sub(v___x_7617_, v___x_7616_);
v_remainder_7619_ = lean_uint64_land(v___y_7571_, v___x_7618_);
v___x_7620_ = lean_uint64_sub(v___x_7607_, v___x_7616_);
v_half_7621_ = lean_uint64_shift_left(v___x_7616_, v___x_7620_);
v___x_7622_ = lean_uint64_dec_lt(v_remainder_7619_, v_half_7621_);
if (v___x_7622_ == 0)
{
uint8_t v___x_7623_; 
v___x_7623_ = lean_uint64_dec_lt(v_half_7621_, v_remainder_7619_);
if (v___x_7623_ == 0)
{
uint64_t v___x_7624_; uint8_t v___x_7625_; 
v___x_7624_ = lean_uint64_land(v_quotient_7615_, v___x_7616_);
v___x_7625_ = lean_uint64_dec_eq(v___x_7624_, v___y_7569_);
if (v___x_7625_ == 0)
{
uint64_t v___x_7626_; 
v___x_7626_ = lean_uint64_add(v_quotient_7615_, v___x_7616_);
v___y_7369_ = v___y_7569_;
v___y_7370_ = v___y_7570_;
v___y_7371_ = v___y_7572_;
v___y_7372_ = v___x_7626_;
goto v___jp_7368_;
}
else
{
v___y_7369_ = v___y_7569_;
v___y_7370_ = v___y_7570_;
v___y_7371_ = v___y_7572_;
v___y_7372_ = v_quotient_7615_;
goto v___jp_7368_;
}
}
else
{
uint64_t v___x_7627_; 
v___x_7627_ = lean_uint64_add(v_quotient_7615_, v___x_7616_);
v___y_7369_ = v___y_7569_;
v___y_7370_ = v___y_7570_;
v___y_7371_ = v___y_7572_;
v___y_7372_ = v___x_7627_;
goto v___jp_7368_;
}
}
else
{
v___y_7369_ = v___y_7569_;
v___y_7370_ = v___y_7570_;
v___y_7371_ = v___y_7572_;
v___y_7372_ = v_quotient_7615_;
goto v___jp_7368_;
}
}
}
else
{
v___y_7369_ = v___y_7569_;
v___y_7370_ = v___y_7570_;
v___y_7371_ = v___y_7572_;
v___y_7372_ = v___y_7571_;
goto v___jp_7368_;
}
}
}
}
v___jp_7628_:
{
uint64_t v___x_7636_; uint64_t v___x_7637_; uint8_t v___x_7638_; 
v___x_7636_ = 1ULL;
v___x_7637_ = lean_uint64_shift_right(v___y_7634_, v___x_7636_);
v___x_7638_ = lean_uint64_dec_eq(v___x_7637_, v___y_7629_);
if (v___x_7638_ == 0)
{
uint64_t v___x_7639_; 
v___x_7639_ = lean_uint64_add(v___y_7635_, v___x_7636_);
v___y_7569_ = v___y_7629_;
v___y_7570_ = v___y_7630_;
v___y_7571_ = v___y_7631_;
v___y_7572_ = v___y_7632_;
v___y_7573_ = v___y_7633_;
v___y_7574_ = v___x_7639_;
goto v___jp_7568_;
}
else
{
v___y_7569_ = v___y_7629_;
v___y_7570_ = v___y_7630_;
v___y_7571_ = v___y_7631_;
v___y_7572_ = v___y_7632_;
v___y_7573_ = v___y_7633_;
v___y_7574_ = v___y_7635_;
goto v___jp_7568_;
}
}
v___jp_7640_:
{
uint64_t v___x_7650_; uint8_t v___x_7651_; 
v___x_7650_ = lean_uint64_shift_right(v___y_7644_, v___y_7647_);
v___x_7651_ = lean_uint64_dec_eq(v___x_7650_, v___y_7641_);
if (v___x_7651_ == 0)
{
uint64_t v___x_7652_; 
v___x_7652_ = lean_uint64_add(v___y_7642_, v___y_7647_);
v___y_7629_ = v___y_7641_;
v___y_7630_ = v___y_7643_;
v___y_7631_ = v___y_7645_;
v___y_7632_ = v___y_7646_;
v___y_7633_ = v___y_7648_;
v___y_7634_ = v___y_7649_;
v___y_7635_ = v___x_7652_;
goto v___jp_7628_;
}
else
{
v___y_7629_ = v___y_7641_;
v___y_7630_ = v___y_7643_;
v___y_7631_ = v___y_7645_;
v___y_7632_ = v___y_7646_;
v___y_7633_ = v___y_7648_;
v___y_7634_ = v___y_7649_;
v___y_7635_ = v___y_7642_;
goto v___jp_7628_;
}
}
v___jp_7653_:
{
uint64_t v___x_7661_; uint64_t v___x_7662_; uint8_t v___x_7663_; 
v___x_7661_ = 2ULL;
v___x_7662_ = lean_uint64_shift_right(v___y_7656_, v___x_7661_);
v___x_7663_ = lean_uint64_dec_eq(v___x_7662_, v___y_7654_);
if (v___x_7663_ == 0)
{
v___y_7641_ = v___y_7654_;
v___y_7642_ = v___y_7660_;
v___y_7643_ = v___y_7655_;
v___y_7644_ = v___y_7656_;
v___y_7645_ = v___y_7657_;
v___y_7646_ = v___y_7658_;
v___y_7647_ = v___x_7661_;
v___y_7648_ = v___y_7659_;
v___y_7649_ = v___x_7662_;
goto v___jp_7640_;
}
else
{
v___y_7641_ = v___y_7654_;
v___y_7642_ = v___y_7660_;
v___y_7643_ = v___y_7655_;
v___y_7644_ = v___y_7656_;
v___y_7645_ = v___y_7657_;
v___y_7646_ = v___y_7658_;
v___y_7647_ = v___x_7661_;
v___y_7648_ = v___y_7659_;
v___y_7649_ = v___y_7656_;
goto v___jp_7640_;
}
}
v___jp_7664_:
{
uint64_t v___x_7674_; uint8_t v___x_7675_; 
v___x_7674_ = lean_uint64_shift_right(v___y_7672_, v___y_7667_);
v___x_7675_ = lean_uint64_dec_eq(v___x_7674_, v___y_7665_);
if (v___x_7675_ == 0)
{
uint64_t v___x_7676_; 
v___x_7676_ = lean_uint64_add(v___y_7666_, v___y_7667_);
v___y_7654_ = v___y_7665_;
v___y_7655_ = v___y_7668_;
v___y_7656_ = v___y_7673_;
v___y_7657_ = v___y_7669_;
v___y_7658_ = v___y_7670_;
v___y_7659_ = v___y_7671_;
v___y_7660_ = v___x_7676_;
goto v___jp_7653_;
}
else
{
v___y_7654_ = v___y_7665_;
v___y_7655_ = v___y_7668_;
v___y_7656_ = v___y_7673_;
v___y_7657_ = v___y_7669_;
v___y_7658_ = v___y_7670_;
v___y_7659_ = v___y_7671_;
v___y_7660_ = v___y_7666_;
goto v___jp_7653_;
}
}
v___jp_7677_:
{
uint64_t v___x_7685_; uint64_t v___x_7686_; uint8_t v___x_7687_; 
v___x_7685_ = 4ULL;
v___x_7686_ = lean_uint64_shift_right(v___y_7683_, v___x_7685_);
v___x_7687_ = lean_uint64_dec_eq(v___x_7686_, v___y_7678_);
if (v___x_7687_ == 0)
{
v___y_7665_ = v___y_7678_;
v___y_7666_ = v___y_7684_;
v___y_7667_ = v___x_7685_;
v___y_7668_ = v___y_7679_;
v___y_7669_ = v___y_7680_;
v___y_7670_ = v___y_7681_;
v___y_7671_ = v___y_7682_;
v___y_7672_ = v___y_7683_;
v___y_7673_ = v___x_7686_;
goto v___jp_7664_;
}
else
{
v___y_7665_ = v___y_7678_;
v___y_7666_ = v___y_7684_;
v___y_7667_ = v___x_7685_;
v___y_7668_ = v___y_7679_;
v___y_7669_ = v___y_7680_;
v___y_7670_ = v___y_7681_;
v___y_7671_ = v___y_7682_;
v___y_7672_ = v___y_7683_;
v___y_7673_ = v___y_7683_;
goto v___jp_7664_;
}
}
v___jp_7688_:
{
uint64_t v___x_7698_; uint8_t v___x_7699_; 
v___x_7698_ = lean_uint64_shift_right(v___y_7690_, v___y_7689_);
v___x_7699_ = lean_uint64_dec_eq(v___x_7698_, v___y_7691_);
if (v___x_7699_ == 0)
{
uint64_t v___x_7700_; 
v___x_7700_ = lean_uint64_add(v___y_7695_, v___y_7689_);
v___y_7678_ = v___y_7691_;
v___y_7679_ = v___y_7692_;
v___y_7680_ = v___y_7693_;
v___y_7681_ = v___y_7694_;
v___y_7682_ = v___y_7696_;
v___y_7683_ = v___y_7697_;
v___y_7684_ = v___x_7700_;
goto v___jp_7677_;
}
else
{
v___y_7678_ = v___y_7691_;
v___y_7679_ = v___y_7692_;
v___y_7680_ = v___y_7693_;
v___y_7681_ = v___y_7694_;
v___y_7682_ = v___y_7696_;
v___y_7683_ = v___y_7697_;
v___y_7684_ = v___y_7695_;
goto v___jp_7677_;
}
}
v___jp_7701_:
{
uint64_t v___x_7709_; uint64_t v___x_7710_; uint8_t v___x_7711_; 
v___x_7709_ = 8ULL;
v___x_7710_ = lean_uint64_shift_right(v___y_7703_, v___x_7709_);
v___x_7711_ = lean_uint64_dec_eq(v___x_7710_, v___y_7702_);
if (v___x_7711_ == 0)
{
v___y_7689_ = v___x_7709_;
v___y_7690_ = v___y_7703_;
v___y_7691_ = v___y_7702_;
v___y_7692_ = v___y_7704_;
v___y_7693_ = v___y_7705_;
v___y_7694_ = v___y_7706_;
v___y_7695_ = v___y_7708_;
v___y_7696_ = v___y_7707_;
v___y_7697_ = v___x_7710_;
goto v___jp_7688_;
}
else
{
v___y_7689_ = v___x_7709_;
v___y_7690_ = v___y_7703_;
v___y_7691_ = v___y_7702_;
v___y_7692_ = v___y_7704_;
v___y_7693_ = v___y_7705_;
v___y_7694_ = v___y_7706_;
v___y_7695_ = v___y_7708_;
v___y_7696_ = v___y_7707_;
v___y_7697_ = v___y_7703_;
goto v___jp_7688_;
}
}
v___jp_7712_:
{
uint64_t v___x_7722_; uint8_t v___x_7723_; 
v___x_7722_ = lean_uint64_shift_right(v___y_7714_, v___y_7716_);
v___x_7723_ = lean_uint64_dec_eq(v___x_7722_, v___y_7713_);
if (v___x_7723_ == 0)
{
uint64_t v___x_7724_; 
v___x_7724_ = lean_uint64_add(v___y_7715_, v___y_7716_);
v___y_7702_ = v___y_7713_;
v___y_7703_ = v___y_7721_;
v___y_7704_ = v___y_7717_;
v___y_7705_ = v___y_7718_;
v___y_7706_ = v___y_7719_;
v___y_7707_ = v___y_7720_;
v___y_7708_ = v___x_7724_;
goto v___jp_7701_;
}
else
{
v___y_7702_ = v___y_7713_;
v___y_7703_ = v___y_7721_;
v___y_7704_ = v___y_7717_;
v___y_7705_ = v___y_7718_;
v___y_7706_ = v___y_7719_;
v___y_7707_ = v___y_7720_;
v___y_7708_ = v___y_7715_;
goto v___jp_7701_;
}
}
v___jp_7725_:
{
uint64_t v___x_7733_; uint64_t v___x_7734_; uint8_t v___x_7735_; 
v___x_7733_ = 16ULL;
v___x_7734_ = lean_uint64_shift_right(v___y_7727_, v___x_7733_);
v___x_7735_ = lean_uint64_dec_eq(v___x_7734_, v___y_7726_);
if (v___x_7735_ == 0)
{
v___y_7713_ = v___y_7726_;
v___y_7714_ = v___y_7727_;
v___y_7715_ = v___y_7732_;
v___y_7716_ = v___x_7733_;
v___y_7717_ = v___y_7728_;
v___y_7718_ = v___y_7729_;
v___y_7719_ = v___y_7730_;
v___y_7720_ = v___y_7731_;
v___y_7721_ = v___x_7734_;
goto v___jp_7712_;
}
else
{
v___y_7713_ = v___y_7726_;
v___y_7714_ = v___y_7727_;
v___y_7715_ = v___y_7732_;
v___y_7716_ = v___x_7733_;
v___y_7717_ = v___y_7728_;
v___y_7718_ = v___y_7729_;
v___y_7719_ = v___y_7730_;
v___y_7720_ = v___y_7731_;
v___y_7721_ = v___y_7727_;
goto v___jp_7712_;
}
}
v___jp_7736_:
{
uint64_t v___x_7744_; uint8_t v___x_7745_; 
v___x_7744_ = lean_uint64_shift_right(v___y_7740_, v___y_7738_);
v___x_7745_ = lean_uint64_dec_eq(v___x_7744_, v___y_7737_);
if (v___x_7745_ == 0)
{
v___y_7726_ = v___y_7737_;
v___y_7727_ = v___y_7743_;
v___y_7728_ = v___y_7739_;
v___y_7729_ = v___y_7740_;
v___y_7730_ = v___y_7741_;
v___y_7731_ = v___y_7742_;
v___y_7732_ = v___y_7738_;
goto v___jp_7725_;
}
else
{
v___y_7726_ = v___y_7737_;
v___y_7727_ = v___y_7743_;
v___y_7728_ = v___y_7739_;
v___y_7729_ = v___y_7740_;
v___y_7730_ = v___y_7741_;
v___y_7731_ = v___y_7742_;
v___y_7732_ = v___y_7737_;
goto v___jp_7725_;
}
}
v___jp_7746_:
{
uint64_t v___x_7751_; uint8_t v___x_7752_; 
v___x_7751_ = 0ULL;
v___x_7752_ = lean_uint64_dec_eq(v___y_7748_, v___x_7751_);
if (v___x_7752_ == 0)
{
uint64_t v___x_7753_; uint64_t v___x_7754_; uint8_t v___x_7755_; 
v___x_7753_ = 32ULL;
v___x_7754_ = lean_uint64_shift_right(v___y_7748_, v___x_7753_);
v___x_7755_ = lean_uint64_dec_eq(v___x_7754_, v___x_7751_);
if (v___x_7755_ == 0)
{
v___y_7737_ = v___x_7751_;
v___y_7738_ = v___x_7753_;
v___y_7739_ = v___y_7747_;
v___y_7740_ = v___y_7748_;
v___y_7741_ = v___y_7749_;
v___y_7742_ = v___y_7750_;
v___y_7743_ = v___x_7754_;
goto v___jp_7736_;
}
else
{
v___y_7737_ = v___x_7751_;
v___y_7738_ = v___x_7753_;
v___y_7739_ = v___y_7747_;
v___y_7740_ = v___y_7748_;
v___y_7741_ = v___y_7749_;
v___y_7742_ = v___y_7750_;
v___y_7743_ = v___y_7748_;
goto v___jp_7736_;
}
}
else
{
if (v___y_7747_ == 0)
{
uint32_t v___x_7756_; 
v___x_7756_ = 0;
return v___x_7756_;
}
else
{
uint32_t v___x_7757_; 
v___x_7757_ = 2147483648;
return v___x_7757_;
}
}
}
v___jp_7758_:
{
uint64_t v___x_7765_; uint64_t v___x_7766_; uint64_t v___x_7767_; uint8_t v___x_7768_; 
v___x_7765_ = lean_uint64_mul(v___y_7763_, v___y_7760_);
v___x_7766_ = lean_uint64_add(v___y_7761_, v___y_7764_);
v___x_7767_ = 281474976710656ULL;
v___x_7768_ = lean_uint64_dec_lt(v___x_7765_, v___x_7767_);
if (v___x_7768_ == 0)
{
v___y_7747_ = v___y_7759_;
v___y_7748_ = v___x_7765_;
v___y_7749_ = v___y_7762_;
v___y_7750_ = v___x_7766_;
goto v___jp_7746_;
}
else
{
uint64_t v___x_7769_; uint8_t v___x_7770_; 
v___x_7769_ = 123ULL;
v___x_7770_ = lean_uint64_dec_le(v___x_7766_, v___x_7769_);
if (v___x_7770_ == 0)
{
v___y_7747_ = v___y_7759_;
v___y_7748_ = v___x_7765_;
v___y_7749_ = v___y_7762_;
v___y_7750_ = v___x_7766_;
goto v___jp_7746_;
}
else
{
uint64_t v___x_7771_; uint8_t v___x_7772_; 
v___x_7771_ = 0ULL;
v___x_7772_ = lean_uint64_dec_eq(v___x_7765_, v___x_7771_);
if (v___x_7772_ == 0)
{
uint64_t v___x_7773_; uint64_t v___x_7774_; uint8_t v___x_7775_; 
v___x_7773_ = 149ULL;
v___x_7774_ = lean_uint64_sub(v___x_7773_, v___x_7766_);
v___x_7775_ = lean_uint64_dec_eq(v___x_7774_, v___x_7771_);
if (v___x_7775_ == 0)
{
uint64_t v___x_7776_; uint8_t v___x_7777_; 
v___x_7776_ = 64ULL;
v___x_7777_ = lean_uint64_dec_lt(v___x_7774_, v___x_7776_);
if (v___x_7777_ == 0)
{
uint8_t v___x_7778_; 
v___x_7778_ = lean_uint64_dec_eq(v___x_7774_, v___x_7776_);
if (v___x_7778_ == 0)
{
v___y_7390_ = v___y_7759_;
v___y_7391_ = v___y_7762_;
v___y_7392_ = v___x_7771_;
v___y_7393_ = v___x_7771_;
goto v___jp_7389_;
}
else
{
uint64_t v___x_7779_; uint8_t v___x_7780_; 
v___x_7779_ = 9223372036854775808ULL;
v___x_7780_ = lean_uint64_dec_lt(v___x_7779_, v___x_7765_);
if (v___x_7780_ == 0)
{
v___y_7390_ = v___y_7759_;
v___y_7391_ = v___y_7762_;
v___y_7392_ = v___x_7771_;
v___y_7393_ = v___x_7771_;
goto v___jp_7389_;
}
else
{
uint64_t v___x_7781_; 
v___x_7781_ = 1ULL;
v___y_7390_ = v___y_7759_;
v___y_7391_ = v___y_7762_;
v___y_7392_ = v___x_7771_;
v___y_7393_ = v___x_7781_;
goto v___jp_7389_;
}
}
}
else
{
uint64_t v_quotient_7782_; uint64_t v___x_7783_; uint64_t v___x_7784_; uint64_t v___x_7785_; uint64_t v_remainder_7786_; uint64_t v___x_7787_; uint64_t v_half_7788_; uint8_t v___x_7789_; 
v_quotient_7782_ = lean_uint64_shift_right(v___x_7765_, v___x_7774_);
v___x_7783_ = 1ULL;
v___x_7784_ = lean_uint64_shift_left(v___x_7783_, v___x_7774_);
v___x_7785_ = lean_uint64_sub(v___x_7784_, v___x_7783_);
v_remainder_7786_ = lean_uint64_land(v___x_7765_, v___x_7785_);
v___x_7787_ = lean_uint64_sub(v___x_7774_, v___x_7783_);
v_half_7788_ = lean_uint64_shift_left(v___x_7783_, v___x_7787_);
v___x_7789_ = lean_uint64_dec_lt(v_remainder_7786_, v_half_7788_);
if (v___x_7789_ == 0)
{
uint8_t v___x_7790_; 
v___x_7790_ = lean_uint64_dec_lt(v_half_7788_, v_remainder_7786_);
if (v___x_7790_ == 0)
{
uint64_t v___x_7791_; uint8_t v___x_7792_; 
v___x_7791_ = lean_uint64_land(v_quotient_7782_, v___x_7783_);
v___x_7792_ = lean_uint64_dec_eq(v___x_7791_, v___x_7771_);
if (v___x_7792_ == 0)
{
uint64_t v___x_7793_; 
v___x_7793_ = lean_uint64_add(v_quotient_7782_, v___x_7783_);
v___y_7390_ = v___y_7759_;
v___y_7391_ = v___y_7762_;
v___y_7392_ = v___x_7771_;
v___y_7393_ = v___x_7793_;
goto v___jp_7389_;
}
else
{
v___y_7390_ = v___y_7759_;
v___y_7391_ = v___y_7762_;
v___y_7392_ = v___x_7771_;
v___y_7393_ = v_quotient_7782_;
goto v___jp_7389_;
}
}
else
{
uint64_t v___x_7794_; 
v___x_7794_ = lean_uint64_add(v_quotient_7782_, v___x_7783_);
v___y_7390_ = v___y_7759_;
v___y_7391_ = v___y_7762_;
v___y_7392_ = v___x_7771_;
v___y_7393_ = v___x_7794_;
goto v___jp_7389_;
}
}
else
{
v___y_7390_ = v___y_7759_;
v___y_7391_ = v___y_7762_;
v___y_7392_ = v___x_7771_;
v___y_7393_ = v_quotient_7782_;
goto v___jp_7389_;
}
}
}
else
{
v___y_7390_ = v___y_7759_;
v___y_7391_ = v___y_7762_;
v___y_7392_ = v___x_7771_;
v___y_7393_ = v___x_7765_;
goto v___jp_7389_;
}
}
else
{
if (v___y_7759_ == 0)
{
uint32_t v___x_7795_; 
v___x_7795_ = 0;
return v___x_7795_;
}
else
{
uint32_t v___x_7796_; 
v___x_7796_ = 2147483648;
return v___x_7796_;
}
}
}
}
}
v___jp_7800_:
{
uint64_t v___x_7806_; uint64_t v___x_7807_; uint8_t v___x_7808_; 
v___x_7806_ = lean_uint32_to_uint64(v_ey_7799_);
v___x_7807_ = 0ULL;
v___x_7808_ = lean_uint64_dec_eq(v___x_7806_, v___x_7807_);
if (v___x_7808_ == 0)
{
uint64_t v___x_7809_; uint64_t v___x_7810_; 
v___x_7809_ = 1ULL;
v___x_7810_ = lean_uint64_sub(v___x_7806_, v___x_7809_);
v___y_7759_ = v___y_7802_;
v___y_7760_ = v___y_7801_;
v___y_7761_ = v___y_7805_;
v___y_7762_ = v___y_7804_;
v___y_7763_ = v___y_7803_;
v___y_7764_ = v___x_7810_;
goto v___jp_7758_;
}
else
{
v___y_7759_ = v___y_7802_;
v___y_7760_ = v___y_7801_;
v___y_7761_ = v___y_7805_;
v___y_7762_ = v___y_7804_;
v___y_7763_ = v___y_7803_;
v___y_7764_ = v___x_7807_;
goto v___jp_7758_;
}
}
v___jp_7811_:
{
uint64_t v___x_7816_; uint64_t v___x_7817_; uint8_t v___x_7818_; 
v___x_7816_ = lean_uint32_to_uint64(v_ex_7797_);
v___x_7817_ = 0ULL;
v___x_7818_ = lean_uint64_dec_eq(v___x_7816_, v___x_7817_);
if (v___x_7818_ == 0)
{
uint64_t v___x_7819_; uint64_t v___x_7820_; 
v___x_7819_ = 1ULL;
v___x_7820_ = lean_uint64_sub(v___x_7816_, v___x_7819_);
v___y_7801_ = v___y_7815_;
v___y_7802_ = v___y_7812_;
v___y_7803_ = v___y_7814_;
v___y_7804_ = v___y_7813_;
v___y_7805_ = v___x_7820_;
goto v___jp_7800_;
}
else
{
v___y_7801_ = v___y_7815_;
v___y_7802_ = v___y_7812_;
v___y_7803_ = v___y_7814_;
v___y_7804_ = v___y_7813_;
v___y_7805_ = v___x_7817_;
goto v___jp_7800_;
}
}
v___jp_7821_:
{
uint32_t v___x_7826_; uint8_t v___x_7827_; 
v___x_7826_ = 0;
v___x_7827_ = lean_uint32_dec_eq(v_ey_7799_, v___x_7826_);
if (v___x_7827_ == 0)
{
uint64_t v___x_7828_; uint64_t v___x_7829_; uint64_t v___x_7830_; 
v___x_7828_ = lean_uint32_to_uint64(v___y_7823_);
v___x_7829_ = 8388608ULL;
v___x_7830_ = lean_uint64_lor(v___x_7828_, v___x_7829_);
v___y_7812_ = v___y_7822_;
v___y_7813_ = v___y_7824_;
v___y_7814_ = v___y_7825_;
v___y_7815_ = v___x_7830_;
goto v___jp_7811_;
}
else
{
uint64_t v___x_7831_; 
v___x_7831_ = lean_uint32_to_uint64(v___y_7823_);
v___y_7812_ = v___y_7822_;
v___y_7813_ = v___y_7824_;
v___y_7814_ = v___y_7825_;
v___y_7815_ = v___x_7831_;
goto v___jp_7811_;
}
}
v___jp_7832_:
{
uint32_t v___x_7834_; uint32_t v_xFraction_7835_; uint32_t v_yFraction_7836_; uint32_t v___x_7837_; uint8_t v___x_7838_; 
v___x_7834_ = 8388607;
v_xFraction_7835_ = lean_uint32_land(v___y_7352_, v___x_7834_);
v_yFraction_7836_ = lean_uint32_land(v___y_7353_, v___x_7834_);
v___x_7837_ = 0;
v___x_7838_ = lean_uint32_dec_eq(v_ex_7797_, v___x_7837_);
if (v___x_7838_ == 0)
{
uint64_t v___x_7839_; uint64_t v___x_7840_; uint64_t v___x_7841_; 
v___x_7839_ = lean_uint32_to_uint64(v_xFraction_7835_);
v___x_7840_ = 8388608ULL;
v___x_7841_ = lean_uint64_lor(v___x_7839_, v___x_7840_);
v___y_7822_ = v___y_7833_;
v___y_7823_ = v_yFraction_7836_;
v___y_7824_ = v___x_7834_;
v___y_7825_ = v___x_7841_;
goto v___jp_7821_;
}
else
{
uint64_t v___x_7842_; 
v___x_7842_ = lean_uint32_to_uint64(v_xFraction_7835_);
v___y_7822_ = v___y_7833_;
v___y_7823_ = v_yFraction_7836_;
v___y_7824_ = v___x_7834_;
v___y_7825_ = v___x_7842_;
goto v___jp_7821_;
}
}
v___jp_7846_:
{
if (v___y_7848_ == 0)
{
v___y_7833_ = v___x_7845_;
goto v___jp_7832_;
}
else
{
v___y_7833_ = v___y_7847_;
goto v___jp_7832_;
}
}
v___jp_7849_:
{
if (v___y_7851_ == 0)
{
if (v___y_7852_ == 0)
{
v___y_7847_ = v___y_7850_;
v___y_7848_ = v___x_7845_;
goto v___jp_7846_;
}
else
{
v___y_7833_ = v___x_7845_;
goto v___jp_7832_;
}
}
else
{
v___y_7847_ = v___y_7850_;
v___y_7848_ = v___y_7852_;
goto v___jp_7846_;
}
}
v___jp_7853_:
{
uint32_t v___x_7856_; uint32_t v___x_7857_; uint32_t v___x_7858_; uint8_t v___x_7859_; 
v___x_7856_ = 2147483648;
v___x_7857_ = lean_uint32_land(v___y_7353_, v___x_7856_);
v___x_7858_ = 0;
v___x_7859_ = lean_uint32_dec_eq(v___x_7857_, v___x_7858_);
if (v___x_7859_ == 0)
{
v___y_7850_ = v___y_7854_;
v___y_7851_ = v___y_7855_;
v___y_7852_ = v___x_7845_;
goto v___jp_7849_;
}
else
{
v___y_7850_ = v___y_7854_;
v___y_7851_ = v___y_7855_;
v___y_7852_ = v___y_7854_;
goto v___jp_7849_;
}
}
v___jp_7860_:
{
if (v___y_7861_ == 0)
{
uint32_t v___x_7862_; uint32_t v___x_7863_; uint32_t v___x_7864_; uint8_t v___x_7865_; 
v___x_7862_ = 2147483648;
v___x_7863_ = lean_uint32_land(v___y_7352_, v___x_7862_);
v___x_7864_ = 0;
v___x_7865_ = lean_uint32_dec_eq(v___x_7863_, v___x_7864_);
if (v___x_7865_ == 0)
{
v___y_7854_ = v___y_7861_;
v___y_7855_ = v___x_7845_;
goto v___jp_7853_;
}
else
{
v___y_7854_ = v___y_7861_;
v___y_7855_ = v___y_7861_;
goto v___jp_7853_;
}
}
else
{
lean_object* v___x_7866_; lean_object* v___x_7867_; lean_object* v___x_7868_; uint32_t v___x_7869_; 
v___x_7866_ = lean_uint32_to_nat(v___y_7352_);
v___x_7867_ = lean_uint32_to_nat(v___y_7353_);
v___x_7868_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_7866_, v___x_7867_);
v___x_7869_ = lean_uint32_of_nat(v___x_7868_);
lean_dec(v___x_7868_);
return v___x_7869_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_runResident16___lam__1___boxed(lean_object* v___y_7884_, lean_object* v___y_7885_){
_start:
{
uint32_t v___y_2190__boxed_7886_; uint32_t v___y_2191__boxed_7887_; uint32_t v_res_7888_; lean_object* v_r_7889_; 
v___y_2190__boxed_7886_ = lean_unbox_uint32(v___y_7884_);
lean_dec(v___y_7884_);
v___y_2191__boxed_7887_ = lean_unbox_uint32(v___y_7885_);
lean_dec(v___y_7885_);
v_res_7888_ = lp_competition_runResident16___lam__1(v___y_2190__boxed_7886_, v___y_2191__boxed_7887_);
v_r_7889_ = lean_box_uint32(v_res_7888_);
return v_r_7889_;
}
}
LEAN_EXPORT lean_object* lp_competition_runResident16(){
_start:
{
lean_object* v___f_7893_; lean_object* v___f_7894_; lean_object* v___x_7895_; lean_object* v___x_7896_; lean_object* v___x_7897_; 
v___f_7893_ = ((lean_object*)(lp_competition_runControl___closed__0));
v___f_7894_ = ((lean_object*)(lp_competition_runResident16___closed__0));
v___x_7895_ = ((lean_object*)(lp_competition_runControl___closed__2));
v___x_7896_ = ((lean_object*)(lp_competition_runResident16___closed__1));
v___x_7897_ = lp_competition_Bench_Suite_run(v___f_7893_, v___f_7894_, v___x_7895_, v___x_7896_);
return v___x_7897_;
}
}
LEAN_EXPORT lean_object* lp_competition_runResident16___boxed(lean_object* v_a_7898_){
_start:
{
lean_object* v_res_7899_; 
v_res_7899_ = lp_competition_runResident16();
return v_res_7899_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_7920_; lean_object* v___x_7921_; lean_object* v___x_7922_; uint8_t v___x_7923_; 
v___x_7920_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_7921_ = lean_io_getenv(v___x_7920_);
v___x_7922_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_7923_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_7921_, v___x_7922_);
if (v___x_7923_ == 0)
{
lean_object* v___x_7924_; uint8_t v___x_7925_; 
v___x_7924_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_7925_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_7921_, v___x_7924_);
if (v___x_7925_ == 0)
{
lean_object* v___x_7926_; uint8_t v___x_7927_; 
v___x_7926_ = ((lean_object*)(lp_competition_main___closed__6));
v___x_7927_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_7921_, v___x_7926_);
if (v___x_7927_ == 0)
{
lean_object* v___x_7928_; uint8_t v___x_7929_; 
v___x_7928_ = ((lean_object*)(lp_competition_main___closed__8));
v___x_7929_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_7921_, v___x_7928_);
if (v___x_7929_ == 0)
{
lean_object* v___x_7930_; uint8_t v___x_7931_; 
v___x_7930_ = ((lean_object*)(lp_competition_main___closed__10));
v___x_7931_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_7921_, v___x_7930_);
lean_dec(v___x_7921_);
if (v___x_7931_ == 0)
{
lean_object* v___x_7932_; lean_object* v___x_7933_; 
v___x_7932_ = ((lean_object*)(lp_competition_main___closed__12));
v___x_7933_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_7933_, 0, v___x_7932_);
return v___x_7933_;
}
else
{
lean_object* v___x_7934_; 
v___x_7934_ = lp_competition_runResident16();
return v___x_7934_;
}
}
else
{
lean_object* v___x_7935_; 
lean_dec(v___x_7921_);
v___x_7935_ = lp_competition_runNativeProduct();
return v___x_7935_;
}
}
else
{
lean_object* v___x_7936_; 
lean_dec(v___x_7921_);
v___x_7936_ = lp_competition_runOutline();
return v___x_7936_;
}
}
else
{
lean_object* v___x_7937_; 
lean_dec(v___x_7921_);
v___x_7937_ = lp_competition_runInlineOld();
return v___x_7937_;
}
}
else
{
lean_object* v___x_7938_; 
lean_dec(v___x_7921_);
v___x_7938_ = lp_competition_runControl();
return v___x_7938_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_7939_){
_start:
{
lean_object* v_res_7940_; 
v_res_7940_ = _lean_main();
return v_res_7940_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_competition_BenchFull(uint8_t builtin);
lean_object* initialize_competition_BenchSuite(uint8_t builtin);
lean_object* initialize_competition_Submission(uint8_t builtin);
void lean_initialize();
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_competition_R22MultiStaticCostMain(uint8_t builtin) {
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
  res = initialize_competition_R22MultiStaticCostMain(1 /* builtin */);
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
