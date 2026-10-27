// Lean compiler output
// Module: R22RuntimeCostMain
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
lean_object* lean_uint32_to_nat(uint32_t);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(lean_object*, lean_object*);
uint32_t lean_uint32_of_nat(lean_object*);
uint32_t lean_uint32_lor(uint32_t, uint32_t);
uint32_t lean_uint32_shift_right(uint32_t, uint32_t);
uint32_t lean_uint32_land(uint32_t, uint32_t);
uint8_t lean_uint32_dec_eq(uint32_t, uint32_t);
float lean_float32_add(float, float);
uint8_t lean_float32_beq(float, float);
uint32_t lean_float32_to_bits(float);
float lean_float32_of_bits(uint32_t);
float lean_uint32_to_float32(uint32_t);
extern lean_object* lp_competition_R2W01b_scaleTable;
lean_object* lean_array_fget_borrowed(lean_object*, lean_object*);
float lean_float32_mul(float, float);
uint32_t lean_uint32_sub(uint32_t, uint32_t);
uint8_t lean_uint32_dec_le(uint32_t, uint32_t);
uint8_t lean_uint32_dec_lt(uint32_t, uint32_t);
uint32_t lp_competition_Submission_FastMul_mul(uint32_t, uint32_t);
uint8_t lean_uint64_dec_eq(uint64_t, uint64_t);
uint32_t lean_uint64_to_uint32(uint64_t);
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
lean_object* lp_competition_Submission_bmm(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word(lean_object*, lean_object*, lean_object*);
extern float lp_competition_Submission_R21ScaledU32_powNeg23;
float lean_uint64_to_float32(uint64_t);
uint32_t lean_float32_to_uint32(float);
uint32_t lean_uint32_xor(uint32_t, uint32_t);
lean_object* lean_io_getenv(lean_object*);
uint8_t l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(lean_object*, lean_object*);
lean_object* lp_competition_Submission_sum___boxed(lean_object*, lean_object*);
lean_object* lp_competition_Bench_Suite_run(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lp_competition_Submission_R22StreamingCost_guarded(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_ctor_object lp_competition_r22CostScaledMul___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*3 + 8, .m_other = 3, .m_tag = 0}, .m_objs = {((lean_object*)(((size_t)(8) << 1) | 1)),((lean_object*)(((size_t)(23) << 1) | 1)),((lean_object*)(((size_t)(127) << 1) | 1)),LEAN_SCALAR_PTR_LITERAL(0, 0, 0, 0, 0, 0, 0, 0)}};
static const lean_object* lp_competition_r22CostScaledMul___closed__0 = (const lean_object*)&lp_competition_r22CostScaledMul___closed__0_value;
LEAN_EXPORT uint32_t lp_competition_r22CostScaledMul(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_r22CostScaledMul___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint8_t, uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint8_t, uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__4(uint8_t, uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__4___boxed(lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition_main___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 14, .m_capacity = 14, .m_length = 13, .m_data = "BENCH_VARIANT"};
static const lean_object* lp_competition_main___closed__0 = (const lean_object*)&lp_competition_main___closed__0_value;
static const lean_string_object lp_competition_main___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 8, .m_capacity = 8, .m_length = 7, .m_data = "control"};
static const lean_object* lp_competition_main___closed__1 = (const lean_object*)&lp_competition_main___closed__1_value;
static const lean_ctor_object lp_competition_main___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__1_value)}};
static const lean_object* lp_competition_main___closed__2 = (const lean_object*)&lp_competition_main___closed__2_value;
static const lean_string_object lp_competition_main___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "streamed"};
static const lean_object* lp_competition_main___closed__3 = (const lean_object*)&lp_competition_main___closed__3_value;
static const lean_ctor_object lp_competition_main___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__3_value)}};
static const lean_object* lp_competition_main___closed__4 = (const lean_object*)&lp_competition_main___closed__4_value;
static const lean_string_object lp_competition_main___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 7, .m_capacity = 7, .m_length = 6, .m_data = "scaled"};
static const lean_object* lp_competition_main___closed__5 = (const lean_object*)&lp_competition_main___closed__5_value;
static const lean_ctor_object lp_competition_main___closed__6_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__5_value)}};
static const lean_object* lp_competition_main___closed__6 = (const lean_object*)&lp_competition_main___closed__6_value;
static const lean_string_object lp_competition_main___closed__7_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 50, .m_capacity = 50, .m_length = 49, .m_data = "BENCH_VARIANT must be control, streamed or scaled"};
static const lean_object* lp_competition_main___closed__7 = (const lean_object*)&lp_competition_main___closed__7_value;
static const lean_ctor_object lp_competition_main___closed__8_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_main___closed__7_value)}};
static const lean_object* lp_competition_main___closed__8 = (const lean_object*)&lp_competition_main___closed__8_value;
static const lean_closure_object lp_competition_main___closed__9_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_main___lam__0___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__9 = (const lean_object*)&lp_competition_main___closed__9_value;
static const lean_closure_object lp_competition_main___closed__10_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_sum___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__10 = (const lean_object*)&lp_competition_main___closed__10_value;
static const lean_closure_object lp_competition_main___closed__11_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_bmm, .m_arity = 6, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__11 = (const lean_object*)&lp_competition_main___closed__11_value;
static const lean_closure_object lp_competition_main___closed__12_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_R22StreamingCost_guarded, .m_arity = 6, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__12 = (const lean_object*)&lp_competition_main___closed__12_value;
LEAN_EXPORT lean_object* _lean_main();
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_r22CostScaledMul(uint32_t v_x_6_, uint32_t v_y_7_){
_start:
{
uint8_t v___y_9_; uint8_t v___y_25_; uint8_t v___y_39_; uint8_t v___y_56_; float v___y_63_; float v___y_64_; float v___y_78_; uint8_t v___y_79_; float v___y_94_; uint32_t v___y_104_; uint32_t v___y_108_; uint32_t v___y_112_; uint32_t v___y_113_; uint32_t v___y_114_; uint64_t v___y_118_; uint8_t v___y_119_; uint32_t v___y_120_; uint64_t v___y_121_; uint32_t v___y_133_; uint32_t v___y_134_; uint32_t v___y_135_; uint8_t v___y_139_; uint32_t v___y_140_; uint64_t v___y_141_; uint64_t v___y_142_; uint8_t v___y_154_; uint8_t v___y_170_; uint8_t v___y_184_; uint8_t v___y_201_; float v___y_208_; float v___y_209_; float v___y_223_; uint8_t v___y_224_; float v___y_239_; uint32_t v___y_249_; uint32_t v___y_253_; uint32_t v___y_257_; uint32_t v___y_258_; uint32_t v___y_259_; uint32_t v___y_263_; uint8_t v___y_264_; uint64_t v___y_265_; uint64_t v___y_266_; uint32_t v___y_278_; uint32_t v___y_279_; uint32_t v___y_280_; uint32_t v___y_284_; uint64_t v___y_285_; uint8_t v___y_286_; uint64_t v___y_287_; uint8_t v___y_299_; uint8_t v___y_315_; uint8_t v___y_329_; uint8_t v___y_346_; float v___y_353_; float v___y_354_; float v___y_368_; uint8_t v___y_369_; float v___y_384_; uint32_t v___y_394_; uint32_t v___y_398_; uint32_t v___y_402_; uint32_t v___y_403_; uint32_t v___y_404_; uint8_t v___y_408_; uint32_t v___y_409_; uint64_t v___y_410_; uint64_t v___y_411_; uint32_t v___y_423_; uint32_t v___y_424_; uint32_t v___y_425_; uint8_t v___y_429_; uint32_t v___y_430_; uint64_t v___y_431_; uint64_t v___y_432_; uint32_t v___x_443_; uint32_t v___x_444_; uint8_t v___y_446_; uint8_t v___y_459_; uint8_t v___y_472_; uint32_t v___x_484_; uint32_t v___y_486_; uint32_t v___y_487_; uint32_t v___y_488_; uint32_t v___y_489_; uint32_t v___y_496_; uint8_t v___y_497_; uint32_t v___y_498_; uint32_t v___y_499_; uint64_t v___y_503_; uint64_t v___y_504_; uint8_t v___y_505_; uint32_t v___y_506_; uint64_t v___y_507_; uint64_t v___y_517_; uint64_t v___y_518_; uint8_t v___y_519_; uint32_t v___y_520_; uint8_t v___y_521_; uint64_t v___y_522_; uint64_t v___y_529_; uint8_t v___y_530_; uint32_t v___y_531_; uint64_t v___y_532_; uint64_t v___y_533_; uint64_t v___y_539_; uint64_t v___y_540_; uint64_t v___y_541_; uint8_t v___y_542_; uint32_t v___y_543_; uint64_t v___y_544_; uint64_t v___y_599_; uint64_t v___y_600_; uint64_t v___y_601_; uint64_t v___y_602_; uint8_t v___y_603_; uint32_t v___y_604_; uint64_t v___y_605_; uint64_t v___y_611_; uint64_t v___y_612_; uint64_t v___y_613_; uint64_t v___y_614_; uint64_t v___y_615_; uint64_t v___y_616_; uint8_t v___y_617_; uint32_t v___y_618_; uint64_t v___y_619_; uint64_t v___y_624_; uint64_t v___y_625_; uint64_t v___y_626_; uint64_t v___y_627_; uint8_t v___y_628_; uint32_t v___y_629_; uint64_t v___y_630_; uint64_t v___y_635_; uint64_t v___y_636_; uint64_t v___y_637_; uint64_t v___y_638_; uint64_t v___y_639_; uint64_t v___y_640_; uint8_t v___y_641_; uint32_t v___y_642_; uint64_t v___y_643_; uint64_t v___y_648_; uint64_t v___y_649_; uint64_t v___y_650_; uint8_t v___y_651_; uint64_t v___y_652_; uint32_t v___y_653_; uint64_t v___y_654_; uint64_t v___y_659_; uint64_t v___y_660_; uint64_t v___y_661_; uint64_t v___y_662_; uint64_t v___y_663_; uint8_t v___y_664_; uint32_t v___y_665_; uint64_t v___y_666_; uint64_t v___y_667_; uint64_t v___y_672_; uint64_t v___y_673_; uint64_t v___y_674_; uint64_t v___y_675_; uint8_t v___y_676_; uint32_t v___y_677_; uint64_t v___y_678_; uint64_t v___y_683_; uint64_t v___y_684_; uint64_t v___y_685_; uint64_t v___y_686_; uint64_t v___y_687_; uint8_t v___y_688_; uint32_t v___y_689_; uint64_t v___y_690_; uint64_t v___y_691_; uint64_t v___y_696_; uint64_t v___y_697_; uint64_t v___y_698_; uint8_t v___y_699_; uint32_t v___y_700_; uint64_t v___y_701_; uint64_t v___y_702_; uint64_t v___y_707_; uint64_t v___y_708_; uint64_t v___y_709_; uint8_t v___y_710_; uint64_t v___y_711_; uint32_t v___y_712_; uint64_t v___y_713_; uint64_t v___y_717_; uint64_t v___y_718_; uint8_t v___y_719_; uint32_t v___y_720_; uint64_t v___y_729_; uint8_t v___y_730_; uint64_t v___y_731_; uint64_t v___y_732_; uint32_t v___y_733_; uint64_t v___y_734_; uint32_t v___y_768_; uint32_t v___y_769_; uint32_t v___y_770_; uint32_t v___y_771_; uint32_t v___y_778_; uint8_t v___y_779_; uint32_t v___y_780_; uint32_t v___y_781_; uint32_t v___y_785_; uint8_t v___y_786_; uint64_t v___y_787_; uint64_t v___y_788_; uint64_t v___y_789_; uint8_t v___y_799_; uint32_t v___y_800_; uint8_t v___y_801_; uint64_t v___y_802_; uint64_t v___y_803_; uint64_t v___y_804_; uint32_t v___y_811_; uint8_t v___y_812_; uint64_t v___y_813_; uint64_t v___y_814_; uint64_t v___y_815_; uint64_t v___y_821_; uint32_t v___y_822_; uint8_t v___y_823_; uint64_t v___y_824_; uint64_t v___y_825_; uint64_t v___y_826_; uint64_t v___y_881_; uint64_t v___y_882_; uint32_t v___y_883_; uint8_t v___y_884_; uint64_t v___y_885_; uint64_t v___y_886_; uint64_t v___y_887_; uint64_t v___y_893_; uint32_t v___y_894_; uint64_t v___y_895_; uint8_t v___y_896_; uint64_t v___y_897_; uint64_t v___y_898_; uint64_t v___y_899_; uint64_t v___y_900_; uint64_t v___y_901_; uint64_t v___y_906_; uint32_t v___y_907_; uint8_t v___y_908_; uint64_t v___y_909_; uint64_t v___y_910_; uint64_t v___y_911_; uint64_t v___y_912_; uint64_t v___y_917_; uint32_t v___y_918_; uint8_t v___y_919_; uint64_t v___y_920_; uint64_t v___y_921_; uint64_t v___y_922_; uint64_t v___y_923_; uint64_t v___y_924_; uint64_t v___y_925_; uint64_t v___y_930_; uint32_t v___y_931_; uint8_t v___y_932_; uint64_t v___y_933_; uint64_t v___y_934_; uint64_t v___y_935_; uint64_t v___y_936_; uint64_t v___y_941_; uint64_t v___y_942_; uint32_t v___y_943_; uint8_t v___y_944_; uint64_t v___y_945_; uint64_t v___y_946_; uint64_t v___y_947_; uint64_t v___y_948_; uint64_t v___y_949_; uint64_t v___y_954_; uint32_t v___y_955_; uint8_t v___y_956_; uint64_t v___y_957_; uint64_t v___y_958_; uint64_t v___y_959_; uint64_t v___y_960_; uint64_t v___y_965_; uint32_t v___y_966_; uint8_t v___y_967_; uint64_t v___y_968_; uint64_t v___y_969_; uint64_t v___y_970_; uint64_t v___y_971_; uint64_t v___y_972_; uint64_t v___y_973_; uint64_t v___y_978_; uint32_t v___y_979_; uint8_t v___y_980_; uint64_t v___y_981_; uint64_t v___y_982_; uint64_t v___y_983_; uint64_t v___y_984_; uint64_t v___y_989_; uint32_t v___y_990_; uint8_t v___y_991_; uint64_t v___y_992_; uint64_t v___y_993_; uint64_t v___y_994_; uint64_t v___y_995_; uint64_t v___y_999_; uint32_t v___y_1000_; uint8_t v___y_1001_; uint64_t v___y_1002_; uint64_t v___y_1011_; uint32_t v___y_1012_; uint8_t v___y_1013_; uint64_t v___y_1014_; uint64_t v___y_1015_; uint64_t v___y_1016_; uint32_t v___y_1050_; uint32_t v___y_1051_; uint32_t v___y_1052_; uint32_t v___y_1053_; uint32_t v___y_1060_; uint8_t v___y_1061_; uint32_t v___y_1062_; uint32_t v___y_1063_; uint8_t v___y_1067_; uint64_t v___y_1068_; uint32_t v___y_1069_; uint64_t v___y_1070_; uint64_t v___y_1071_; uint8_t v___y_1081_; uint8_t v___y_1082_; uint32_t v___y_1083_; uint64_t v___y_1084_; uint64_t v___y_1085_; uint64_t v___y_1086_; uint8_t v___y_1093_; uint64_t v___y_1094_; uint64_t v___y_1095_; uint32_t v___y_1096_; uint64_t v___y_1097_; uint64_t v___y_1103_; uint64_t v___y_1104_; uint8_t v___y_1105_; uint32_t v___y_1106_; uint64_t v___y_1107_; uint64_t v___y_1108_; uint64_t v___y_1163_; uint64_t v___y_1164_; uint8_t v___y_1165_; uint32_t v___y_1166_; uint64_t v___y_1167_; uint64_t v___y_1168_; uint64_t v___y_1169_; uint64_t v___y_1175_; uint64_t v___y_1176_; uint8_t v___y_1177_; uint64_t v___y_1178_; uint64_t v___y_1179_; uint64_t v___y_1180_; uint32_t v___y_1181_; uint64_t v___y_1182_; uint64_t v___y_1183_; uint64_t v___y_1188_; uint64_t v___y_1189_; uint8_t v___y_1190_; uint32_t v___y_1191_; uint64_t v___y_1192_; uint64_t v___y_1193_; uint64_t v___y_1194_; uint64_t v___y_1199_; uint64_t v___y_1200_; uint64_t v___y_1201_; uint8_t v___y_1202_; uint64_t v___y_1203_; uint64_t v___y_1204_; uint32_t v___y_1205_; uint64_t v___y_1206_; uint64_t v___y_1207_; uint64_t v___y_1212_; uint64_t v___y_1213_; uint8_t v___y_1214_; uint32_t v___y_1215_; uint64_t v___y_1216_; uint64_t v___y_1217_; uint64_t v___y_1218_; uint64_t v___y_1223_; uint64_t v___y_1224_; uint64_t v___y_1225_; uint64_t v___y_1226_; uint64_t v___y_1227_; uint8_t v___y_1228_; uint64_t v___y_1229_; uint32_t v___y_1230_; uint64_t v___y_1231_; uint64_t v___y_1236_; uint64_t v___y_1237_; uint64_t v___y_1238_; uint8_t v___y_1239_; uint32_t v___y_1240_; uint64_t v___y_1241_; uint64_t v___y_1242_; uint64_t v___y_1247_; uint64_t v___y_1248_; uint64_t v___y_1249_; uint64_t v___y_1250_; uint8_t v___y_1251_; uint64_t v___y_1252_; uint32_t v___y_1253_; uint64_t v___y_1254_; uint64_t v___y_1255_; uint64_t v___y_1260_; uint64_t v___y_1261_; uint8_t v___y_1262_; uint32_t v___y_1263_; uint64_t v___y_1264_; uint64_t v___y_1265_; uint64_t v___y_1266_; uint64_t v___y_1271_; uint64_t v___y_1272_; uint8_t v___y_1273_; uint64_t v___y_1274_; uint32_t v___y_1275_; uint64_t v___y_1276_; uint64_t v___y_1277_; uint64_t v___y_1281_; uint64_t v___y_1282_; uint8_t v___y_1283_; uint32_t v___y_1284_; uint64_t v___y_1293_; uint8_t v___y_1294_; uint64_t v___y_1295_; uint64_t v___y_1296_; uint32_t v___y_1297_; uint64_t v___y_1298_; uint32_t v_eu_1331_; uint32_t v___x_1332_; uint32_t v___x_1333_; uint32_t v___x_1334_; uint8_t v___x_1335_; 
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
uint32_t v___x_1336_; uint32_t v_ey_1337_; uint64_t v___y_1339_; uint64_t v___y_1340_; uint8_t v___y_1341_; uint32_t v___y_1342_; uint64_t v___y_1343_; uint64_t v___y_1350_; uint8_t v___y_1351_; uint32_t v___y_1352_; uint64_t v___y_1353_; uint8_t v___y_1360_; uint32_t v___y_1361_; uint32_t v___y_1362_; uint64_t v___y_1363_; uint8_t v___y_1371_; uint32_t v___x_1381_; uint32_t v___x_1382_; uint8_t v___x_1383_; uint8_t v___y_1385_; uint8_t v___y_1386_; uint8_t v___y_1387_; uint8_t v___y_1389_; uint8_t v___y_1390_; uint8_t v___y_1396_; 
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
v___y_446_ = v___x_1410_;
goto v___jp_445_;
}
else
{
uint32_t v___x_1411_; uint8_t v___x_1412_; 
v___x_1411_ = 2139095040;
v___x_1412_ = lean_uint32_dec_lt(v_a_1407_, v___x_1411_);
v___y_446_ = v___x_1412_;
goto v___jp_445_;
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
v___y_729_ = v___y_1339_;
v___y_730_ = v___y_1341_;
v___y_731_ = v___y_1340_;
v___y_732_ = v___y_1343_;
v___y_733_ = v___y_1342_;
v___y_734_ = v___x_1348_;
goto v___jp_728_;
}
else
{
v___y_729_ = v___y_1339_;
v___y_730_ = v___y_1341_;
v___y_731_ = v___y_1340_;
v___y_732_ = v___y_1343_;
v___y_733_ = v___y_1342_;
v___y_734_ = v___x_1345_;
goto v___jp_728_;
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
v___y_1340_ = v___y_1353_;
v___y_1341_ = v___y_1351_;
v___y_1342_ = v___y_1352_;
v___y_1343_ = v___x_1358_;
goto v___jp_1338_;
}
else
{
v___y_1339_ = v___y_1350_;
v___y_1340_ = v___y_1353_;
v___y_1341_ = v___y_1351_;
v___y_1342_ = v___y_1352_;
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
v___x_1366_ = lean_uint32_to_uint64(v___y_1361_);
v___x_1367_ = 8388608ULL;
v___x_1368_ = lean_uint64_lor(v___x_1366_, v___x_1367_);
v___y_1350_ = v___y_1363_;
v___y_1351_ = v___y_1360_;
v___y_1352_ = v___y_1362_;
v___y_1353_ = v___x_1368_;
goto v___jp_1349_;
}
else
{
uint64_t v___x_1369_; 
v___x_1369_ = lean_uint32_to_uint64(v___y_1361_);
v___y_1350_ = v___y_1363_;
v___y_1351_ = v___y_1360_;
v___y_1352_ = v___y_1362_;
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
v___y_1360_ = v___y_1371_;
v___y_1361_ = v_yFraction_1374_;
v___y_1362_ = v___x_1372_;
v___y_1363_ = v___x_1379_;
goto v___jp_1359_;
}
else
{
uint64_t v___x_1380_; 
v___x_1380_ = lean_uint32_to_uint64(v_xFraction_1373_);
v___y_1360_ = v___y_1371_;
v___y_1361_ = v_yFraction_1374_;
v___y_1362_ = v___x_1372_;
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
v___x_1401_ = ((lean_object*)(lp_competition_r22CostScaledMul___closed__0));
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
uint32_t v___x_1418_; uint32_t v_ev_1419_; uint32_t v___y_1421_; uint8_t v___y_1422_; uint64_t v___y_1423_; uint64_t v___y_1424_; uint64_t v___y_1425_; uint32_t v___y_1432_; uint8_t v___y_1433_; uint64_t v___y_1434_; uint64_t v___y_1435_; uint32_t v___y_1442_; uint32_t v___y_1443_; uint8_t v___y_1444_; uint64_t v___y_1445_; uint8_t v___y_1453_; uint8_t v___y_1464_; uint8_t v___y_1465_; uint8_t v___y_1467_; uint8_t v___y_1468_; uint8_t v___y_1469_; uint8_t v___y_1471_; uint8_t v___y_1472_; uint8_t v___y_1478_; uint64_t v___y_1489_; uint8_t v___y_1490_; uint64_t v___y_1491_; uint32_t v___y_1492_; uint64_t v___y_1493_; uint64_t v___y_1500_; uint8_t v___y_1501_; uint32_t v___y_1502_; uint64_t v___y_1503_; uint8_t v___y_1510_; uint32_t v___y_1511_; uint32_t v___y_1512_; uint64_t v___y_1513_; uint8_t v___y_1521_; uint32_t v___x_1531_; uint8_t v___x_1532_; uint8_t v___y_1534_; uint8_t v___y_1535_; uint8_t v___y_1537_; uint8_t v___y_1538_; uint8_t v___y_1539_; uint8_t v___y_1541_; uint8_t v___y_1542_; uint8_t v___y_1548_; 
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
v___y_1478_ = v___x_1572_;
goto v___jp_1477_;
}
else
{
v___y_1478_ = v___x_1570_;
goto v___jp_1477_;
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
v___y_472_ = v___x_1583_;
goto v___jp_471_;
}
else
{
uint32_t v___x_1584_; uint8_t v___x_1585_; 
v___x_1584_ = 2139095040;
v___x_1585_ = lean_uint32_dec_lt(v_a_1580_, v___x_1584_);
v___y_472_ = v___x_1585_;
goto v___jp_471_;
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
float v_scale_1591_; uint32_t v___x_1592_; uint32_t v___x_1593_; uint32_t v___x_1594_; uint32_t v_a_1595_; uint32_t v___x_1596_; uint32_t v_b_1597_; uint64_t v___x_1598_; uint64_t v___x_1599_; uint64_t v_p_1600_; float v___x_1601_; float v___x_1602_; uint32_t v_z_1603_; uint32_t v___x_1604_; uint32_t v_high_1605_; uint32_t v_q_1606_; uint32_t v___x_1607_; uint32_t v___x_1608_; uint32_t v_e_1609_; uint32_t v___x_1610_; uint32_t v___x_1611_; uint32_t v___x_1612_; uint32_t v___x_1613_; uint32_t v___x_1614_; uint32_t v___x_1615_; uint32_t v___x_1616_; 
v_scale_1591_ = lp_competition_Submission_R21ScaledU32_powNeg23;
v___x_1592_ = 8388607;
v___x_1593_ = lean_uint32_land(v_x_6_, v___x_1592_);
v___x_1594_ = 8388608;
v_a_1595_ = lean_uint32_lor(v___x_1593_, v___x_1594_);
v___x_1596_ = lean_uint32_land(v_y_7_, v___x_1592_);
v_b_1597_ = lean_uint32_lor(v___x_1596_, v___x_1594_);
v___x_1598_ = lean_uint32_to_uint64(v_a_1595_);
v___x_1599_ = lean_uint32_to_uint64(v_b_1597_);
v_p_1600_ = lean_uint64_mul(v___x_1598_, v___x_1599_);
v___x_1601_ = lean_uint64_to_float32(v_p_1600_);
v___x_1602_ = lean_float32_mul(v___x_1601_, v_scale_1591_);
v_z_1603_ = lean_float32_to_uint32(v___x_1602_);
v___x_1604_ = 24;
v_high_1605_ = lean_uint32_shift_right(v_z_1603_, v___x_1604_);
v_q_1606_ = lean_uint32_shift_right(v_z_1603_, v_high_1605_);
v___x_1607_ = 127;
v___x_1608_ = lean_uint32_sub(v_s_1573_, v___x_1607_);
v_e_1609_ = lean_uint32_add(v___x_1608_, v_high_1605_);
v___x_1610_ = lean_uint32_xor(v_x_6_, v_y_7_);
v___x_1611_ = 2147483648;
v___x_1612_ = lean_uint32_land(v___x_1610_, v___x_1611_);
v___x_1613_ = lean_uint32_shift_left(v_e_1609_, v___x_443_);
v___x_1614_ = lean_uint32_lor(v___x_1612_, v___x_1613_);
v___x_1615_ = lean_uint32_sub(v_q_1606_, v___x_1594_);
v___x_1616_ = lean_uint32_lor(v___x_1614_, v___x_1615_);
return v___x_1616_;
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
v___y_1011_ = v___y_1425_;
v___y_1012_ = v___y_1421_;
v___y_1013_ = v___y_1422_;
v___y_1014_ = v___y_1423_;
v___y_1015_ = v___y_1424_;
v___y_1016_ = v___x_1430_;
goto v___jp_1010_;
}
else
{
v___y_1011_ = v___y_1425_;
v___y_1012_ = v___y_1421_;
v___y_1013_ = v___y_1422_;
v___y_1014_ = v___y_1423_;
v___y_1015_ = v___y_1424_;
v___y_1016_ = v___x_1427_;
goto v___jp_1010_;
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
v___y_1421_ = v___y_1432_;
v___y_1422_ = v___y_1433_;
v___y_1423_ = v___y_1434_;
v___y_1424_ = v___y_1435_;
v___y_1425_ = v___x_1440_;
goto v___jp_1420_;
}
else
{
v___y_1421_ = v___y_1432_;
v___y_1422_ = v___y_1433_;
v___y_1423_ = v___y_1434_;
v___y_1424_ = v___y_1435_;
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
v___y_1432_ = v___y_1443_;
v___y_1433_ = v___y_1444_;
v___y_1434_ = v___y_1445_;
v___y_1435_ = v___x_1450_;
goto v___jp_1431_;
}
else
{
uint64_t v___x_1451_; 
v___x_1451_ = lean_uint32_to_uint64(v___y_1442_);
v___y_1432_ = v___y_1443_;
v___y_1433_ = v___y_1444_;
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
if (v___y_1465_ == 0)
{
v___y_1453_ = v___x_1335_;
goto v___jp_1452_;
}
else
{
v___y_1453_ = v___y_1464_;
goto v___jp_1452_;
}
}
v___jp_1466_:
{
if (v___y_1468_ == 0)
{
if (v___y_1469_ == 0)
{
v___y_1464_ = v___y_1467_;
v___y_1465_ = v___x_1335_;
goto v___jp_1463_;
}
else
{
v___y_1453_ = v___x_1335_;
goto v___jp_1452_;
}
}
else
{
v___y_1464_ = v___y_1467_;
v___y_1465_ = v___y_1469_;
goto v___jp_1463_;
}
}
v___jp_1470_:
{
uint32_t v___x_1473_; uint32_t v___x_1474_; uint32_t v___x_1475_; uint8_t v___x_1476_; 
v___x_1473_ = 2147483648;
v___x_1474_ = lean_uint32_land(v_y_7_, v___x_1473_);
v___x_1475_ = 0;
v___x_1476_ = lean_uint32_dec_eq(v___x_1474_, v___x_1475_);
if (v___x_1476_ == 0)
{
v___y_1467_ = v___y_1471_;
v___y_1468_ = v___y_1472_;
v___y_1469_ = v___x_1335_;
goto v___jp_1466_;
}
else
{
v___y_1467_ = v___y_1471_;
v___y_1468_ = v___y_1472_;
v___y_1469_ = v___y_1471_;
goto v___jp_1466_;
}
}
v___jp_1477_:
{
if (v___y_1478_ == 0)
{
uint32_t v___x_1479_; uint32_t v___x_1480_; uint32_t v___x_1481_; uint8_t v___x_1482_; 
v___x_1479_ = 2147483648;
v___x_1480_ = lean_uint32_land(v_x_6_, v___x_1479_);
v___x_1481_ = 0;
v___x_1482_ = lean_uint32_dec_eq(v___x_1480_, v___x_1481_);
if (v___x_1482_ == 0)
{
v___y_1471_ = v___y_1478_;
v___y_1472_ = v___x_1335_;
goto v___jp_1470_;
}
else
{
v___y_1471_ = v___y_1478_;
v___y_1472_ = v___y_1478_;
goto v___jp_1470_;
}
}
else
{
lean_object* v___x_1483_; lean_object* v___x_1484_; lean_object* v___x_1485_; lean_object* v___x_1486_; uint32_t v___x_1487_; 
v___x_1483_ = ((lean_object*)(lp_competition_r22CostScaledMul___closed__0));
v___x_1484_ = lean_uint32_to_nat(v_x_6_);
v___x_1485_ = lean_uint32_to_nat(v_y_7_);
v___x_1486_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word(v___x_1483_, v___x_1484_, v___x_1485_);
v___x_1487_ = lean_uint32_of_nat(v___x_1486_);
lean_dec(v___x_1486_);
return v___x_1487_;
}
}
v___jp_1488_:
{
uint64_t v___x_1494_; uint64_t v___x_1495_; uint8_t v___x_1496_; 
v___x_1494_ = lean_uint32_to_uint64(v_ev_1419_);
v___x_1495_ = 0ULL;
v___x_1496_ = lean_uint64_dec_eq(v___x_1494_, v___x_1495_);
if (v___x_1496_ == 0)
{
uint64_t v___x_1497_; uint64_t v___x_1498_; 
v___x_1497_ = 1ULL;
v___x_1498_ = lean_uint64_sub(v___x_1494_, v___x_1497_);
v___y_1293_ = v___y_1489_;
v___y_1294_ = v___y_1490_;
v___y_1295_ = v___y_1493_;
v___y_1296_ = v___y_1491_;
v___y_1297_ = v___y_1492_;
v___y_1298_ = v___x_1498_;
goto v___jp_1292_;
}
else
{
v___y_1293_ = v___y_1489_;
v___y_1294_ = v___y_1490_;
v___y_1295_ = v___y_1493_;
v___y_1296_ = v___y_1491_;
v___y_1297_ = v___y_1492_;
v___y_1298_ = v___x_1495_;
goto v___jp_1292_;
}
}
v___jp_1499_:
{
uint64_t v___x_1504_; uint64_t v___x_1505_; uint8_t v___x_1506_; 
v___x_1504_ = lean_uint32_to_uint64(v_eu_1331_);
v___x_1505_ = 0ULL;
v___x_1506_ = lean_uint64_dec_eq(v___x_1504_, v___x_1505_);
if (v___x_1506_ == 0)
{
uint64_t v___x_1507_; uint64_t v___x_1508_; 
v___x_1507_ = 1ULL;
v___x_1508_ = lean_uint64_sub(v___x_1504_, v___x_1507_);
v___y_1489_ = v___y_1500_;
v___y_1490_ = v___y_1501_;
v___y_1491_ = v___y_1503_;
v___y_1492_ = v___y_1502_;
v___y_1493_ = v___x_1508_;
goto v___jp_1488_;
}
else
{
v___y_1489_ = v___y_1500_;
v___y_1490_ = v___y_1501_;
v___y_1491_ = v___y_1503_;
v___y_1492_ = v___y_1502_;
v___y_1493_ = v___x_1505_;
goto v___jp_1488_;
}
}
v___jp_1509_:
{
uint32_t v___x_1514_; uint8_t v___x_1515_; 
v___x_1514_ = 0;
v___x_1515_ = lean_uint32_dec_eq(v_ev_1419_, v___x_1514_);
if (v___x_1515_ == 0)
{
uint64_t v___x_1516_; uint64_t v___x_1517_; uint64_t v___x_1518_; 
v___x_1516_ = lean_uint32_to_uint64(v___y_1512_);
v___x_1517_ = 8388608ULL;
v___x_1518_ = lean_uint64_lor(v___x_1516_, v___x_1517_);
v___y_1500_ = v___y_1513_;
v___y_1501_ = v___y_1510_;
v___y_1502_ = v___y_1511_;
v___y_1503_ = v___x_1518_;
goto v___jp_1499_;
}
else
{
uint64_t v___x_1519_; 
v___x_1519_ = lean_uint32_to_uint64(v___y_1512_);
v___y_1500_ = v___y_1513_;
v___y_1501_ = v___y_1510_;
v___y_1502_ = v___y_1511_;
v___y_1503_ = v___x_1519_;
goto v___jp_1499_;
}
}
v___jp_1520_:
{
uint32_t v___x_1522_; uint32_t v_xFraction_1523_; uint32_t v_yFraction_1524_; uint32_t v___x_1525_; uint8_t v___x_1526_; 
v___x_1522_ = 8388607;
v_xFraction_1523_ = lean_uint32_land(v_x_6_, v___x_1522_);
v_yFraction_1524_ = lean_uint32_land(v_y_7_, v___x_1522_);
v___x_1525_ = 0;
v___x_1526_ = lean_uint32_dec_eq(v_eu_1331_, v___x_1525_);
if (v___x_1526_ == 0)
{
uint64_t v___x_1527_; uint64_t v___x_1528_; uint64_t v___x_1529_; 
v___x_1527_ = lean_uint32_to_uint64(v_xFraction_1523_);
v___x_1528_ = 8388608ULL;
v___x_1529_ = lean_uint64_lor(v___x_1527_, v___x_1528_);
v___y_1510_ = v___y_1521_;
v___y_1511_ = v___x_1522_;
v___y_1512_ = v_yFraction_1524_;
v___y_1513_ = v___x_1529_;
goto v___jp_1509_;
}
else
{
uint64_t v___x_1530_; 
v___x_1530_ = lean_uint32_to_uint64(v_xFraction_1523_);
v___y_1510_ = v___y_1521_;
v___y_1511_ = v___x_1522_;
v___y_1512_ = v_yFraction_1524_;
v___y_1513_ = v___x_1530_;
goto v___jp_1509_;
}
}
v___jp_1533_:
{
if (v___y_1535_ == 0)
{
v___y_1521_ = v___x_1532_;
goto v___jp_1520_;
}
else
{
v___y_1521_ = v___y_1534_;
goto v___jp_1520_;
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
v___y_1521_ = v___x_1532_;
goto v___jp_1520_;
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
v___x_1553_ = ((lean_object*)(lp_competition_r22CostScaledMul___closed__0));
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
if (v___y_9_ == 0)
{
uint32_t v___x_10_; 
v___x_10_ = lp_competition_Submission_FastMul_mul(v_x_6_, v_y_7_);
return v___x_10_;
}
else
{
uint32_t v___x_11_; uint32_t v___x_12_; 
v___x_11_ = 4194304;
v___x_12_ = lean_uint32_lor(v_y_7_, v___x_11_);
return v___x_12_;
}
}
v___jp_13_:
{
uint32_t v___x_14_; uint32_t v___x_15_; uint32_t v___x_16_; uint32_t v___x_17_; uint8_t v___x_18_; 
v___x_14_ = 23;
v___x_15_ = lean_uint32_shift_right(v_y_7_, v___x_14_);
v___x_16_ = 255;
v___x_17_ = lean_uint32_land(v___x_15_, v___x_16_);
v___x_18_ = lean_uint32_dec_eq(v___x_17_, v___x_16_);
if (v___x_18_ == 0)
{
v___y_9_ = v___x_18_;
goto v___jp_8_;
}
else
{
uint32_t v___x_19_; uint32_t v___x_20_; uint32_t v___x_21_; uint8_t v___x_22_; 
v___x_19_ = 8388607;
v___x_20_ = lean_uint32_land(v_y_7_, v___x_19_);
v___x_21_ = 0;
v___x_22_ = lean_uint32_dec_eq(v___x_20_, v___x_21_);
if (v___x_22_ == 0)
{
v___y_9_ = v___x_18_;
goto v___jp_8_;
}
else
{
uint32_t v___x_23_; 
v___x_23_ = lp_competition_Submission_FastMul_mul(v_x_6_, v_y_7_);
return v___x_23_;
}
}
}
v___jp_24_:
{
if (v___y_25_ == 0)
{
goto v___jp_13_;
}
else
{
uint32_t v___x_26_; uint32_t v___x_27_; 
v___x_26_ = 4194304;
v___x_27_ = lean_uint32_lor(v_x_6_, v___x_26_);
return v___x_27_;
}
}
v___jp_28_:
{
uint32_t v___x_29_; uint32_t v___x_30_; uint32_t v___x_31_; uint32_t v___x_32_; uint8_t v___x_33_; 
v___x_29_ = 23;
v___x_30_ = lean_uint32_shift_right(v_x_6_, v___x_29_);
v___x_31_ = 255;
v___x_32_ = lean_uint32_land(v___x_30_, v___x_31_);
v___x_33_ = lean_uint32_dec_eq(v___x_32_, v___x_31_);
if (v___x_33_ == 0)
{
v___y_25_ = v___x_33_;
goto v___jp_24_;
}
else
{
uint32_t v___x_34_; uint32_t v___x_35_; uint32_t v___x_36_; uint8_t v___x_37_; 
v___x_34_ = 8388607;
v___x_35_ = lean_uint32_land(v_x_6_, v___x_34_);
v___x_36_ = 0;
v___x_37_ = lean_uint32_dec_eq(v___x_35_, v___x_36_);
if (v___x_37_ == 0)
{
v___y_25_ = v___x_33_;
goto v___jp_24_;
}
else
{
goto v___jp_13_;
}
}
}
v___jp_38_:
{
if (v___y_39_ == 0)
{
goto v___jp_28_;
}
else
{
uint32_t v___x_40_; uint32_t v___x_41_; uint32_t v___x_42_; uint8_t v___x_43_; 
v___x_40_ = 4194304;
v___x_41_ = lean_uint32_land(v_y_7_, v___x_40_);
v___x_42_ = 0;
v___x_43_ = lean_uint32_dec_eq(v___x_41_, v___x_42_);
if (v___x_43_ == 0)
{
goto v___jp_28_;
}
else
{
uint32_t v___x_44_; 
v___x_44_ = lean_uint32_lor(v_y_7_, v___x_40_);
return v___x_44_;
}
}
}
v___jp_45_:
{
uint32_t v___x_46_; uint32_t v___x_47_; uint32_t v___x_48_; uint32_t v___x_49_; uint8_t v___x_50_; 
v___x_46_ = 23;
v___x_47_ = lean_uint32_shift_right(v_y_7_, v___x_46_);
v___x_48_ = 255;
v___x_49_ = lean_uint32_land(v___x_47_, v___x_48_);
v___x_50_ = lean_uint32_dec_eq(v___x_49_, v___x_48_);
if (v___x_50_ == 0)
{
v___y_39_ = v___x_50_;
goto v___jp_38_;
}
else
{
uint32_t v___x_51_; uint32_t v___x_52_; uint32_t v___x_53_; uint8_t v___x_54_; 
v___x_51_ = 8388607;
v___x_52_ = lean_uint32_land(v_y_7_, v___x_51_);
v___x_53_ = 0;
v___x_54_ = lean_uint32_dec_eq(v___x_52_, v___x_53_);
if (v___x_54_ == 0)
{
v___y_39_ = v___x_50_;
goto v___jp_38_;
}
else
{
goto v___jp_28_;
}
}
}
v___jp_55_:
{
if (v___y_56_ == 0)
{
goto v___jp_45_;
}
else
{
uint32_t v___x_57_; uint32_t v___x_58_; uint32_t v___x_59_; uint8_t v___x_60_; 
v___x_57_ = 4194304;
v___x_58_ = lean_uint32_land(v_x_6_, v___x_57_);
v___x_59_ = 0;
v___x_60_ = lean_uint32_dec_eq(v___x_58_, v___x_59_);
if (v___x_60_ == 0)
{
goto v___jp_45_;
}
else
{
uint32_t v___x_61_; 
v___x_61_ = lean_uint32_lor(v_x_6_, v___x_57_);
return v___x_61_;
}
}
}
v___jp_62_:
{
float v_result_65_; uint8_t v___x_66_; 
v_result_65_ = lean_float32_mul(v___y_63_, v___y_64_);
v___x_66_ = lean_float32_beq(v_result_65_, v_result_65_);
if (v___x_66_ == 0)
{
uint32_t v___x_67_; uint32_t v___x_68_; uint32_t v___x_69_; uint32_t v___x_70_; uint8_t v___x_71_; 
v___x_67_ = 23;
v___x_68_ = lean_uint32_shift_right(v_x_6_, v___x_67_);
v___x_69_ = 255;
v___x_70_ = lean_uint32_land(v___x_68_, v___x_69_);
v___x_71_ = lean_uint32_dec_eq(v___x_70_, v___x_69_);
if (v___x_71_ == 0)
{
v___y_56_ = v___x_71_;
goto v___jp_55_;
}
else
{
uint32_t v___x_72_; uint32_t v___x_73_; uint32_t v___x_74_; uint8_t v___x_75_; 
v___x_72_ = 8388607;
v___x_73_ = lean_uint32_land(v_x_6_, v___x_72_);
v___x_74_ = 0;
v___x_75_ = lean_uint32_dec_eq(v___x_73_, v___x_74_);
if (v___x_75_ == 0)
{
v___y_56_ = v___x_71_;
goto v___jp_55_;
}
else
{
goto v___jp_45_;
}
}
}
else
{
uint32_t v___x_76_; 
v___x_76_ = lean_float32_to_bits(v_result_65_);
return v___x_76_;
}
}
v___jp_77_:
{
if (v___y_79_ == 0)
{
float v___x_80_; 
v___x_80_ = lean_float32_of_bits(v_y_7_);
v___y_63_ = v___y_78_;
v___y_64_ = v___x_80_;
goto v___jp_62_;
}
else
{
uint32_t v___x_81_; uint32_t v___x_82_; uint32_t v___x_83_; uint32_t v___x_84_; float v___x_85_; lean_object* v___x_86_; uint32_t v___x_87_; uint32_t v___x_88_; lean_object* v___x_89_; lean_object* v___x_90_; float v___x_91_; float v___x_92_; 
v___x_81_ = 8388607;
v___x_82_ = lean_uint32_land(v_y_7_, v___x_81_);
v___x_83_ = 8388608;
v___x_84_ = lean_uint32_lor(v___x_82_, v___x_83_);
v___x_85_ = lean_uint32_to_float32(v___x_84_);
v___x_86_ = lp_competition_R2W01b_scaleTable;
v___x_87_ = 23;
v___x_88_ = lean_uint32_shift_right(v_y_7_, v___x_87_);
v___x_89_ = lean_uint32_to_nat(v___x_88_);
v___x_90_ = lean_array_fget_borrowed(v___x_86_, v___x_89_);
lean_dec(v___x_89_);
v___x_91_ = lean_unbox_float32(v___x_90_);
v___x_92_ = lean_float32_mul(v___x_85_, v___x_91_);
v___y_63_ = v___y_78_;
v___y_64_ = v___x_92_;
goto v___jp_62_;
}
}
v___jp_93_:
{
uint32_t v___x_95_; uint32_t v_a_96_; uint32_t v___x_97_; uint32_t v___x_98_; uint32_t v___x_99_; uint8_t v___x_100_; 
v___x_95_ = 2147483647;
v_a_96_ = lean_uint32_land(v_y_7_, v___x_95_);
v___x_97_ = 201326591;
v___x_98_ = 1;
v___x_99_ = lean_uint32_sub(v_a_96_, v___x_98_);
v___x_100_ = lean_uint32_dec_le(v___x_97_, v___x_99_);
if (v___x_100_ == 0)
{
v___y_78_ = v___y_94_;
v___y_79_ = v___x_100_;
goto v___jp_77_;
}
else
{
uint32_t v___x_101_; uint8_t v___x_102_; 
v___x_101_ = 2139095040;
v___x_102_ = lean_uint32_dec_lt(v_a_96_, v___x_101_);
v___y_78_ = v___y_94_;
v___y_79_ = v___x_102_;
goto v___jp_77_;
}
}
v___jp_103_:
{
uint32_t v___x_105_; uint32_t v___x_106_; 
v___x_105_ = 8388608;
v___x_106_ = lean_uint32_lor(v___y_104_, v___x_105_);
return v___x_106_;
}
v___jp_107_:
{
uint32_t v___x_109_; uint32_t v___x_110_; 
v___x_109_ = 8388608;
v___x_110_ = lean_uint32_lor(v___y_108_, v___x_109_);
return v___x_110_;
}
v___jp_111_:
{
uint32_t v___x_115_; uint32_t v___x_116_; 
v___x_115_ = lean_uint32_land(v___y_112_, v___y_113_);
v___x_116_ = lean_uint32_lor(v___y_114_, v___x_115_);
return v___x_116_;
}
v___jp_117_:
{
uint8_t v___x_122_; 
v___x_122_ = lean_uint64_dec_eq(v___y_121_, v___y_118_);
if (v___x_122_ == 0)
{
uint64_t v___x_123_; uint8_t v___x_124_; 
v___x_123_ = 8388608ULL;
v___x_124_ = lean_uint64_dec_eq(v___y_121_, v___x_123_);
if (v___x_124_ == 0)
{
uint32_t v___x_125_; 
v___x_125_ = lean_uint64_to_uint32(v___y_121_);
if (v___y_119_ == 0)
{
uint32_t v___x_126_; 
v___x_126_ = 0;
v___y_112_ = v___x_125_;
v___y_113_ = v___y_120_;
v___y_114_ = v___x_126_;
goto v___jp_111_;
}
else
{
uint32_t v___x_127_; 
v___x_127_ = 2147483648;
v___y_112_ = v___x_125_;
v___y_113_ = v___y_120_;
v___y_114_ = v___x_127_;
goto v___jp_111_;
}
}
else
{
if (v___y_119_ == 0)
{
uint32_t v___x_128_; 
v___x_128_ = 0;
v___y_104_ = v___x_128_;
goto v___jp_103_;
}
else
{
uint32_t v___x_129_; 
v___x_129_ = 2147483648;
v___y_104_ = v___x_129_;
goto v___jp_103_;
}
}
}
else
{
if (v___y_119_ == 0)
{
uint32_t v___x_130_; 
v___x_130_ = 0;
return v___x_130_;
}
else
{
uint32_t v___x_131_; 
v___x_131_ = 2147483648;
return v___x_131_;
}
}
}
v___jp_132_:
{
uint32_t v___x_136_; uint32_t v___x_137_; 
v___x_136_ = lean_uint32_land(v___y_134_, v___y_133_);
v___x_137_ = lean_uint32_lor(v___y_135_, v___x_136_);
return v___x_137_;
}
v___jp_138_:
{
uint8_t v___x_143_; 
v___x_143_ = lean_uint64_dec_eq(v___y_142_, v___y_141_);
if (v___x_143_ == 0)
{
uint64_t v___x_144_; uint8_t v___x_145_; 
v___x_144_ = 8388608ULL;
v___x_145_ = lean_uint64_dec_eq(v___y_142_, v___x_144_);
if (v___x_145_ == 0)
{
uint32_t v___x_146_; 
v___x_146_ = lean_uint64_to_uint32(v___y_142_);
if (v___y_139_ == 0)
{
uint32_t v___x_147_; 
v___x_147_ = 0;
v___y_133_ = v___y_140_;
v___y_134_ = v___x_146_;
v___y_135_ = v___x_147_;
goto v___jp_132_;
}
else
{
uint32_t v___x_148_; 
v___x_148_ = 2147483648;
v___y_133_ = v___y_140_;
v___y_134_ = v___x_146_;
v___y_135_ = v___x_148_;
goto v___jp_132_;
}
}
else
{
if (v___y_139_ == 0)
{
uint32_t v___x_149_; 
v___x_149_ = 0;
v___y_108_ = v___x_149_;
goto v___jp_107_;
}
else
{
uint32_t v___x_150_; 
v___x_150_ = 2147483648;
v___y_108_ = v___x_150_;
goto v___jp_107_;
}
}
}
else
{
if (v___y_139_ == 0)
{
uint32_t v___x_151_; 
v___x_151_ = 0;
return v___x_151_;
}
else
{
uint32_t v___x_152_; 
v___x_152_ = 2147483648;
return v___x_152_;
}
}
}
v___jp_153_:
{
if (v___y_154_ == 0)
{
uint32_t v___x_155_; 
v___x_155_ = lp_competition_Submission_FastMul_mul(v_x_6_, v_y_7_);
return v___x_155_;
}
else
{
uint32_t v___x_156_; uint32_t v___x_157_; 
v___x_156_ = 4194304;
v___x_157_ = lean_uint32_lor(v_y_7_, v___x_156_);
return v___x_157_;
}
}
v___jp_158_:
{
uint32_t v___x_159_; uint32_t v___x_160_; uint32_t v___x_161_; uint32_t v___x_162_; uint8_t v___x_163_; 
v___x_159_ = 23;
v___x_160_ = lean_uint32_shift_right(v_y_7_, v___x_159_);
v___x_161_ = 255;
v___x_162_ = lean_uint32_land(v___x_160_, v___x_161_);
v___x_163_ = lean_uint32_dec_eq(v___x_162_, v___x_161_);
if (v___x_163_ == 0)
{
v___y_154_ = v___x_163_;
goto v___jp_153_;
}
else
{
uint32_t v___x_164_; uint32_t v___x_165_; uint32_t v___x_166_; uint8_t v___x_167_; 
v___x_164_ = 8388607;
v___x_165_ = lean_uint32_land(v_y_7_, v___x_164_);
v___x_166_ = 0;
v___x_167_ = lean_uint32_dec_eq(v___x_165_, v___x_166_);
if (v___x_167_ == 0)
{
v___y_154_ = v___x_163_;
goto v___jp_153_;
}
else
{
uint32_t v___x_168_; 
v___x_168_ = lp_competition_Submission_FastMul_mul(v_x_6_, v_y_7_);
return v___x_168_;
}
}
}
v___jp_169_:
{
if (v___y_170_ == 0)
{
goto v___jp_158_;
}
else
{
uint32_t v___x_171_; uint32_t v___x_172_; 
v___x_171_ = 4194304;
v___x_172_ = lean_uint32_lor(v_x_6_, v___x_171_);
return v___x_172_;
}
}
v___jp_173_:
{
uint32_t v___x_174_; uint32_t v___x_175_; uint32_t v___x_176_; uint32_t v___x_177_; uint8_t v___x_178_; 
v___x_174_ = 23;
v___x_175_ = lean_uint32_shift_right(v_x_6_, v___x_174_);
v___x_176_ = 255;
v___x_177_ = lean_uint32_land(v___x_175_, v___x_176_);
v___x_178_ = lean_uint32_dec_eq(v___x_177_, v___x_176_);
if (v___x_178_ == 0)
{
v___y_170_ = v___x_178_;
goto v___jp_169_;
}
else
{
uint32_t v___x_179_; uint32_t v___x_180_; uint32_t v___x_181_; uint8_t v___x_182_; 
v___x_179_ = 8388607;
v___x_180_ = lean_uint32_land(v_x_6_, v___x_179_);
v___x_181_ = 0;
v___x_182_ = lean_uint32_dec_eq(v___x_180_, v___x_181_);
if (v___x_182_ == 0)
{
v___y_170_ = v___x_178_;
goto v___jp_169_;
}
else
{
goto v___jp_158_;
}
}
}
v___jp_183_:
{
if (v___y_184_ == 0)
{
goto v___jp_173_;
}
else
{
uint32_t v___x_185_; uint32_t v___x_186_; uint32_t v___x_187_; uint8_t v___x_188_; 
v___x_185_ = 4194304;
v___x_186_ = lean_uint32_land(v_y_7_, v___x_185_);
v___x_187_ = 0;
v___x_188_ = lean_uint32_dec_eq(v___x_186_, v___x_187_);
if (v___x_188_ == 0)
{
goto v___jp_173_;
}
else
{
uint32_t v___x_189_; 
v___x_189_ = lean_uint32_lor(v_y_7_, v___x_185_);
return v___x_189_;
}
}
}
v___jp_190_:
{
uint32_t v___x_191_; uint32_t v___x_192_; uint32_t v___x_193_; uint32_t v___x_194_; uint8_t v___x_195_; 
v___x_191_ = 23;
v___x_192_ = lean_uint32_shift_right(v_y_7_, v___x_191_);
v___x_193_ = 255;
v___x_194_ = lean_uint32_land(v___x_192_, v___x_193_);
v___x_195_ = lean_uint32_dec_eq(v___x_194_, v___x_193_);
if (v___x_195_ == 0)
{
v___y_184_ = v___x_195_;
goto v___jp_183_;
}
else
{
uint32_t v___x_196_; uint32_t v___x_197_; uint32_t v___x_198_; uint8_t v___x_199_; 
v___x_196_ = 8388607;
v___x_197_ = lean_uint32_land(v_y_7_, v___x_196_);
v___x_198_ = 0;
v___x_199_ = lean_uint32_dec_eq(v___x_197_, v___x_198_);
if (v___x_199_ == 0)
{
v___y_184_ = v___x_195_;
goto v___jp_183_;
}
else
{
goto v___jp_173_;
}
}
}
v___jp_200_:
{
if (v___y_201_ == 0)
{
goto v___jp_190_;
}
else
{
uint32_t v___x_202_; uint32_t v___x_203_; uint32_t v___x_204_; uint8_t v___x_205_; 
v___x_202_ = 4194304;
v___x_203_ = lean_uint32_land(v_x_6_, v___x_202_);
v___x_204_ = 0;
v___x_205_ = lean_uint32_dec_eq(v___x_203_, v___x_204_);
if (v___x_205_ == 0)
{
goto v___jp_190_;
}
else
{
uint32_t v___x_206_; 
v___x_206_ = lean_uint32_lor(v_x_6_, v___x_202_);
return v___x_206_;
}
}
}
v___jp_207_:
{
float v_result_210_; uint8_t v___x_211_; 
v_result_210_ = lean_float32_mul(v___y_208_, v___y_209_);
v___x_211_ = lean_float32_beq(v_result_210_, v_result_210_);
if (v___x_211_ == 0)
{
uint32_t v___x_212_; uint32_t v___x_213_; uint32_t v___x_214_; uint32_t v___x_215_; uint8_t v___x_216_; 
v___x_212_ = 23;
v___x_213_ = lean_uint32_shift_right(v_x_6_, v___x_212_);
v___x_214_ = 255;
v___x_215_ = lean_uint32_land(v___x_213_, v___x_214_);
v___x_216_ = lean_uint32_dec_eq(v___x_215_, v___x_214_);
if (v___x_216_ == 0)
{
v___y_201_ = v___x_216_;
goto v___jp_200_;
}
else
{
uint32_t v___x_217_; uint32_t v___x_218_; uint32_t v___x_219_; uint8_t v___x_220_; 
v___x_217_ = 8388607;
v___x_218_ = lean_uint32_land(v_x_6_, v___x_217_);
v___x_219_ = 0;
v___x_220_ = lean_uint32_dec_eq(v___x_218_, v___x_219_);
if (v___x_220_ == 0)
{
v___y_201_ = v___x_216_;
goto v___jp_200_;
}
else
{
goto v___jp_190_;
}
}
}
else
{
uint32_t v___x_221_; 
v___x_221_ = lean_float32_to_bits(v_result_210_);
return v___x_221_;
}
}
v___jp_222_:
{
if (v___y_224_ == 0)
{
float v___x_225_; 
v___x_225_ = lean_float32_of_bits(v_y_7_);
v___y_208_ = v___y_223_;
v___y_209_ = v___x_225_;
goto v___jp_207_;
}
else
{
uint32_t v___x_226_; uint32_t v___x_227_; uint32_t v___x_228_; uint32_t v___x_229_; float v___x_230_; lean_object* v___x_231_; uint32_t v___x_232_; uint32_t v___x_233_; lean_object* v___x_234_; lean_object* v___x_235_; float v___x_236_; float v___x_237_; 
v___x_226_ = 8388607;
v___x_227_ = lean_uint32_land(v_y_7_, v___x_226_);
v___x_228_ = 8388608;
v___x_229_ = lean_uint32_lor(v___x_227_, v___x_228_);
v___x_230_ = lean_uint32_to_float32(v___x_229_);
v___x_231_ = lp_competition_R2W01b_scaleTable;
v___x_232_ = 23;
v___x_233_ = lean_uint32_shift_right(v_y_7_, v___x_232_);
v___x_234_ = lean_uint32_to_nat(v___x_233_);
v___x_235_ = lean_array_fget_borrowed(v___x_231_, v___x_234_);
lean_dec(v___x_234_);
v___x_236_ = lean_unbox_float32(v___x_235_);
v___x_237_ = lean_float32_mul(v___x_230_, v___x_236_);
v___y_208_ = v___y_223_;
v___y_209_ = v___x_237_;
goto v___jp_207_;
}
}
v___jp_238_:
{
uint32_t v___x_240_; uint32_t v_a_241_; uint32_t v___x_242_; uint32_t v___x_243_; uint32_t v___x_244_; uint8_t v___x_245_; 
v___x_240_ = 2147483647;
v_a_241_ = lean_uint32_land(v_y_7_, v___x_240_);
v___x_242_ = 201326591;
v___x_243_ = 1;
v___x_244_ = lean_uint32_sub(v_a_241_, v___x_243_);
v___x_245_ = lean_uint32_dec_le(v___x_242_, v___x_244_);
if (v___x_245_ == 0)
{
v___y_223_ = v___y_239_;
v___y_224_ = v___x_245_;
goto v___jp_222_;
}
else
{
uint32_t v___x_246_; uint8_t v___x_247_; 
v___x_246_ = 2139095040;
v___x_247_ = lean_uint32_dec_lt(v_a_241_, v___x_246_);
v___y_223_ = v___y_239_;
v___y_224_ = v___x_247_;
goto v___jp_222_;
}
}
v___jp_248_:
{
uint32_t v___x_250_; uint32_t v___x_251_; 
v___x_250_ = 8388608;
v___x_251_ = lean_uint32_lor(v___y_249_, v___x_250_);
return v___x_251_;
}
v___jp_252_:
{
uint32_t v___x_254_; uint32_t v___x_255_; 
v___x_254_ = 8388608;
v___x_255_ = lean_uint32_lor(v___y_253_, v___x_254_);
return v___x_255_;
}
v___jp_256_:
{
uint32_t v___x_260_; uint32_t v___x_261_; 
v___x_260_ = lean_uint32_land(v___y_258_, v___y_257_);
v___x_261_ = lean_uint32_lor(v___y_259_, v___x_260_);
return v___x_261_;
}
v___jp_262_:
{
uint8_t v___x_267_; 
v___x_267_ = lean_uint64_dec_eq(v___y_266_, v___y_265_);
if (v___x_267_ == 0)
{
uint64_t v___x_268_; uint8_t v___x_269_; 
v___x_268_ = 8388608ULL;
v___x_269_ = lean_uint64_dec_eq(v___y_266_, v___x_268_);
if (v___x_269_ == 0)
{
uint32_t v___x_270_; 
v___x_270_ = lean_uint64_to_uint32(v___y_266_);
if (v___y_264_ == 0)
{
uint32_t v___x_271_; 
v___x_271_ = 0;
v___y_257_ = v___y_263_;
v___y_258_ = v___x_270_;
v___y_259_ = v___x_271_;
goto v___jp_256_;
}
else
{
uint32_t v___x_272_; 
v___x_272_ = 2147483648;
v___y_257_ = v___y_263_;
v___y_258_ = v___x_270_;
v___y_259_ = v___x_272_;
goto v___jp_256_;
}
}
else
{
if (v___y_264_ == 0)
{
uint32_t v___x_273_; 
v___x_273_ = 0;
v___y_253_ = v___x_273_;
goto v___jp_252_;
}
else
{
uint32_t v___x_274_; 
v___x_274_ = 2147483648;
v___y_253_ = v___x_274_;
goto v___jp_252_;
}
}
}
else
{
if (v___y_264_ == 0)
{
uint32_t v___x_275_; 
v___x_275_ = 0;
return v___x_275_;
}
else
{
uint32_t v___x_276_; 
v___x_276_ = 2147483648;
return v___x_276_;
}
}
}
v___jp_277_:
{
uint32_t v___x_281_; uint32_t v___x_282_; 
v___x_281_ = lean_uint32_land(v___y_278_, v___y_279_);
v___x_282_ = lean_uint32_lor(v___y_280_, v___x_281_);
return v___x_282_;
}
v___jp_283_:
{
uint8_t v___x_288_; 
v___x_288_ = lean_uint64_dec_eq(v___y_287_, v___y_285_);
if (v___x_288_ == 0)
{
uint64_t v___x_289_; uint8_t v___x_290_; 
v___x_289_ = 8388608ULL;
v___x_290_ = lean_uint64_dec_eq(v___y_287_, v___x_289_);
if (v___x_290_ == 0)
{
uint32_t v___x_291_; 
v___x_291_ = lean_uint64_to_uint32(v___y_287_);
if (v___y_286_ == 0)
{
uint32_t v___x_292_; 
v___x_292_ = 0;
v___y_278_ = v___x_291_;
v___y_279_ = v___y_284_;
v___y_280_ = v___x_292_;
goto v___jp_277_;
}
else
{
uint32_t v___x_293_; 
v___x_293_ = 2147483648;
v___y_278_ = v___x_291_;
v___y_279_ = v___y_284_;
v___y_280_ = v___x_293_;
goto v___jp_277_;
}
}
else
{
if (v___y_286_ == 0)
{
uint32_t v___x_294_; 
v___x_294_ = 0;
v___y_249_ = v___x_294_;
goto v___jp_248_;
}
else
{
uint32_t v___x_295_; 
v___x_295_ = 2147483648;
v___y_249_ = v___x_295_;
goto v___jp_248_;
}
}
}
else
{
if (v___y_286_ == 0)
{
uint32_t v___x_296_; 
v___x_296_ = 0;
return v___x_296_;
}
else
{
uint32_t v___x_297_; 
v___x_297_ = 2147483648;
return v___x_297_;
}
}
}
v___jp_298_:
{
if (v___y_299_ == 0)
{
uint32_t v___x_300_; 
v___x_300_ = lp_competition_Submission_FastMul_mul(v_x_6_, v_y_7_);
return v___x_300_;
}
else
{
uint32_t v___x_301_; uint32_t v___x_302_; 
v___x_301_ = 4194304;
v___x_302_ = lean_uint32_lor(v_y_7_, v___x_301_);
return v___x_302_;
}
}
v___jp_303_:
{
uint32_t v___x_304_; uint32_t v___x_305_; uint32_t v___x_306_; uint32_t v___x_307_; uint8_t v___x_308_; 
v___x_304_ = 23;
v___x_305_ = lean_uint32_shift_right(v_y_7_, v___x_304_);
v___x_306_ = 255;
v___x_307_ = lean_uint32_land(v___x_305_, v___x_306_);
v___x_308_ = lean_uint32_dec_eq(v___x_307_, v___x_306_);
if (v___x_308_ == 0)
{
v___y_299_ = v___x_308_;
goto v___jp_298_;
}
else
{
uint32_t v___x_309_; uint32_t v___x_310_; uint32_t v___x_311_; uint8_t v___x_312_; 
v___x_309_ = 8388607;
v___x_310_ = lean_uint32_land(v_y_7_, v___x_309_);
v___x_311_ = 0;
v___x_312_ = lean_uint32_dec_eq(v___x_310_, v___x_311_);
if (v___x_312_ == 0)
{
v___y_299_ = v___x_308_;
goto v___jp_298_;
}
else
{
uint32_t v___x_313_; 
v___x_313_ = lp_competition_Submission_FastMul_mul(v_x_6_, v_y_7_);
return v___x_313_;
}
}
}
v___jp_314_:
{
if (v___y_315_ == 0)
{
goto v___jp_303_;
}
else
{
uint32_t v___x_316_; uint32_t v___x_317_; 
v___x_316_ = 4194304;
v___x_317_ = lean_uint32_lor(v_x_6_, v___x_316_);
return v___x_317_;
}
}
v___jp_318_:
{
uint32_t v___x_319_; uint32_t v___x_320_; uint32_t v___x_321_; uint32_t v___x_322_; uint8_t v___x_323_; 
v___x_319_ = 23;
v___x_320_ = lean_uint32_shift_right(v_x_6_, v___x_319_);
v___x_321_ = 255;
v___x_322_ = lean_uint32_land(v___x_320_, v___x_321_);
v___x_323_ = lean_uint32_dec_eq(v___x_322_, v___x_321_);
if (v___x_323_ == 0)
{
v___y_315_ = v___x_323_;
goto v___jp_314_;
}
else
{
uint32_t v___x_324_; uint32_t v___x_325_; uint32_t v___x_326_; uint8_t v___x_327_; 
v___x_324_ = 8388607;
v___x_325_ = lean_uint32_land(v_x_6_, v___x_324_);
v___x_326_ = 0;
v___x_327_ = lean_uint32_dec_eq(v___x_325_, v___x_326_);
if (v___x_327_ == 0)
{
v___y_315_ = v___x_323_;
goto v___jp_314_;
}
else
{
goto v___jp_303_;
}
}
}
v___jp_328_:
{
if (v___y_329_ == 0)
{
goto v___jp_318_;
}
else
{
uint32_t v___x_330_; uint32_t v___x_331_; uint32_t v___x_332_; uint8_t v___x_333_; 
v___x_330_ = 4194304;
v___x_331_ = lean_uint32_land(v_y_7_, v___x_330_);
v___x_332_ = 0;
v___x_333_ = lean_uint32_dec_eq(v___x_331_, v___x_332_);
if (v___x_333_ == 0)
{
goto v___jp_318_;
}
else
{
uint32_t v___x_334_; 
v___x_334_ = lean_uint32_lor(v_y_7_, v___x_330_);
return v___x_334_;
}
}
}
v___jp_335_:
{
uint32_t v___x_336_; uint32_t v___x_337_; uint32_t v___x_338_; uint32_t v___x_339_; uint8_t v___x_340_; 
v___x_336_ = 23;
v___x_337_ = lean_uint32_shift_right(v_y_7_, v___x_336_);
v___x_338_ = 255;
v___x_339_ = lean_uint32_land(v___x_337_, v___x_338_);
v___x_340_ = lean_uint32_dec_eq(v___x_339_, v___x_338_);
if (v___x_340_ == 0)
{
v___y_329_ = v___x_340_;
goto v___jp_328_;
}
else
{
uint32_t v___x_341_; uint32_t v___x_342_; uint32_t v___x_343_; uint8_t v___x_344_; 
v___x_341_ = 8388607;
v___x_342_ = lean_uint32_land(v_y_7_, v___x_341_);
v___x_343_ = 0;
v___x_344_ = lean_uint32_dec_eq(v___x_342_, v___x_343_);
if (v___x_344_ == 0)
{
v___y_329_ = v___x_340_;
goto v___jp_328_;
}
else
{
goto v___jp_318_;
}
}
}
v___jp_345_:
{
if (v___y_346_ == 0)
{
goto v___jp_335_;
}
else
{
uint32_t v___x_347_; uint32_t v___x_348_; uint32_t v___x_349_; uint8_t v___x_350_; 
v___x_347_ = 4194304;
v___x_348_ = lean_uint32_land(v_x_6_, v___x_347_);
v___x_349_ = 0;
v___x_350_ = lean_uint32_dec_eq(v___x_348_, v___x_349_);
if (v___x_350_ == 0)
{
goto v___jp_335_;
}
else
{
uint32_t v___x_351_; 
v___x_351_ = lean_uint32_lor(v_x_6_, v___x_347_);
return v___x_351_;
}
}
}
v___jp_352_:
{
float v_result_355_; uint8_t v___x_356_; 
v_result_355_ = lean_float32_mul(v___y_353_, v___y_354_);
v___x_356_ = lean_float32_beq(v_result_355_, v_result_355_);
if (v___x_356_ == 0)
{
uint32_t v___x_357_; uint32_t v___x_358_; uint32_t v___x_359_; uint32_t v___x_360_; uint8_t v___x_361_; 
v___x_357_ = 23;
v___x_358_ = lean_uint32_shift_right(v_x_6_, v___x_357_);
v___x_359_ = 255;
v___x_360_ = lean_uint32_land(v___x_358_, v___x_359_);
v___x_361_ = lean_uint32_dec_eq(v___x_360_, v___x_359_);
if (v___x_361_ == 0)
{
v___y_346_ = v___x_361_;
goto v___jp_345_;
}
else
{
uint32_t v___x_362_; uint32_t v___x_363_; uint32_t v___x_364_; uint8_t v___x_365_; 
v___x_362_ = 8388607;
v___x_363_ = lean_uint32_land(v_x_6_, v___x_362_);
v___x_364_ = 0;
v___x_365_ = lean_uint32_dec_eq(v___x_363_, v___x_364_);
if (v___x_365_ == 0)
{
v___y_346_ = v___x_361_;
goto v___jp_345_;
}
else
{
goto v___jp_335_;
}
}
}
else
{
uint32_t v___x_366_; 
v___x_366_ = lean_float32_to_bits(v_result_355_);
return v___x_366_;
}
}
v___jp_367_:
{
if (v___y_369_ == 0)
{
float v___x_370_; 
v___x_370_ = lean_float32_of_bits(v_y_7_);
v___y_353_ = v___y_368_;
v___y_354_ = v___x_370_;
goto v___jp_352_;
}
else
{
uint32_t v___x_371_; uint32_t v___x_372_; uint32_t v___x_373_; uint32_t v___x_374_; float v___x_375_; lean_object* v___x_376_; uint32_t v___x_377_; uint32_t v___x_378_; lean_object* v___x_379_; lean_object* v___x_380_; float v___x_381_; float v___x_382_; 
v___x_371_ = 8388607;
v___x_372_ = lean_uint32_land(v_y_7_, v___x_371_);
v___x_373_ = 8388608;
v___x_374_ = lean_uint32_lor(v___x_372_, v___x_373_);
v___x_375_ = lean_uint32_to_float32(v___x_374_);
v___x_376_ = lp_competition_R2W01b_scaleTable;
v___x_377_ = 23;
v___x_378_ = lean_uint32_shift_right(v_y_7_, v___x_377_);
v___x_379_ = lean_uint32_to_nat(v___x_378_);
v___x_380_ = lean_array_fget_borrowed(v___x_376_, v___x_379_);
lean_dec(v___x_379_);
v___x_381_ = lean_unbox_float32(v___x_380_);
v___x_382_ = lean_float32_mul(v___x_375_, v___x_381_);
v___y_353_ = v___y_368_;
v___y_354_ = v___x_382_;
goto v___jp_352_;
}
}
v___jp_383_:
{
uint32_t v___x_385_; uint32_t v_a_386_; uint32_t v___x_387_; uint32_t v___x_388_; uint32_t v___x_389_; uint8_t v___x_390_; 
v___x_385_ = 2147483647;
v_a_386_ = lean_uint32_land(v_y_7_, v___x_385_);
v___x_387_ = 201326591;
v___x_388_ = 1;
v___x_389_ = lean_uint32_sub(v_a_386_, v___x_388_);
v___x_390_ = lean_uint32_dec_le(v___x_387_, v___x_389_);
if (v___x_390_ == 0)
{
v___y_368_ = v___y_384_;
v___y_369_ = v___x_390_;
goto v___jp_367_;
}
else
{
uint32_t v___x_391_; uint8_t v___x_392_; 
v___x_391_ = 2139095040;
v___x_392_ = lean_uint32_dec_lt(v_a_386_, v___x_391_);
v___y_368_ = v___y_384_;
v___y_369_ = v___x_392_;
goto v___jp_367_;
}
}
v___jp_393_:
{
uint32_t v___x_395_; uint32_t v___x_396_; 
v___x_395_ = 8388608;
v___x_396_ = lean_uint32_lor(v___y_394_, v___x_395_);
return v___x_396_;
}
v___jp_397_:
{
uint32_t v___x_399_; uint32_t v___x_400_; 
v___x_399_ = 8388608;
v___x_400_ = lean_uint32_lor(v___y_398_, v___x_399_);
return v___x_400_;
}
v___jp_401_:
{
uint32_t v___x_405_; uint32_t v___x_406_; 
v___x_405_ = lean_uint32_land(v___y_403_, v___y_402_);
v___x_406_ = lean_uint32_lor(v___y_404_, v___x_405_);
return v___x_406_;
}
v___jp_407_:
{
uint8_t v___x_412_; 
v___x_412_ = lean_uint64_dec_eq(v___y_411_, v___y_410_);
if (v___x_412_ == 0)
{
uint64_t v___x_413_; uint8_t v___x_414_; 
v___x_413_ = 8388608ULL;
v___x_414_ = lean_uint64_dec_eq(v___y_411_, v___x_413_);
if (v___x_414_ == 0)
{
uint32_t v___x_415_; 
v___x_415_ = lean_uint64_to_uint32(v___y_411_);
if (v___y_408_ == 0)
{
uint32_t v___x_416_; 
v___x_416_ = 0;
v___y_402_ = v___y_409_;
v___y_403_ = v___x_415_;
v___y_404_ = v___x_416_;
goto v___jp_401_;
}
else
{
uint32_t v___x_417_; 
v___x_417_ = 2147483648;
v___y_402_ = v___y_409_;
v___y_403_ = v___x_415_;
v___y_404_ = v___x_417_;
goto v___jp_401_;
}
}
else
{
if (v___y_408_ == 0)
{
uint32_t v___x_418_; 
v___x_418_ = 0;
v___y_394_ = v___x_418_;
goto v___jp_393_;
}
else
{
uint32_t v___x_419_; 
v___x_419_ = 2147483648;
v___y_394_ = v___x_419_;
goto v___jp_393_;
}
}
}
else
{
if (v___y_408_ == 0)
{
uint32_t v___x_420_; 
v___x_420_ = 0;
return v___x_420_;
}
else
{
uint32_t v___x_421_; 
v___x_421_ = 2147483648;
return v___x_421_;
}
}
}
v___jp_422_:
{
uint32_t v___x_426_; uint32_t v___x_427_; 
v___x_426_ = lean_uint32_land(v___y_423_, v___y_424_);
v___x_427_ = lean_uint32_lor(v___y_425_, v___x_426_);
return v___x_427_;
}
v___jp_428_:
{
uint8_t v___x_433_; 
v___x_433_ = lean_uint64_dec_eq(v___y_432_, v___y_431_);
if (v___x_433_ == 0)
{
uint64_t v___x_434_; uint8_t v___x_435_; 
v___x_434_ = 8388608ULL;
v___x_435_ = lean_uint64_dec_eq(v___y_432_, v___x_434_);
if (v___x_435_ == 0)
{
uint32_t v___x_436_; 
v___x_436_ = lean_uint64_to_uint32(v___y_432_);
if (v___y_429_ == 0)
{
uint32_t v___x_437_; 
v___x_437_ = 0;
v___y_423_ = v___x_436_;
v___y_424_ = v___y_430_;
v___y_425_ = v___x_437_;
goto v___jp_422_;
}
else
{
uint32_t v___x_438_; 
v___x_438_ = 2147483648;
v___y_423_ = v___x_436_;
v___y_424_ = v___y_430_;
v___y_425_ = v___x_438_;
goto v___jp_422_;
}
}
else
{
if (v___y_429_ == 0)
{
uint32_t v___x_439_; 
v___x_439_ = 0;
v___y_398_ = v___x_439_;
goto v___jp_397_;
}
else
{
uint32_t v___x_440_; 
v___x_440_ = 2147483648;
v___y_398_ = v___x_440_;
goto v___jp_397_;
}
}
}
else
{
if (v___y_429_ == 0)
{
uint32_t v___x_441_; 
v___x_441_ = 0;
return v___x_441_;
}
else
{
uint32_t v___x_442_; 
v___x_442_ = 2147483648;
return v___x_442_;
}
}
}
v___jp_445_:
{
if (v___y_446_ == 0)
{
float v___x_447_; 
v___x_447_ = lean_float32_of_bits(v_x_6_);
v___y_94_ = v___x_447_;
goto v___jp_93_;
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
v___y_94_ = v___x_457_;
goto v___jp_93_;
}
}
v___jp_458_:
{
if (v___y_459_ == 0)
{
float v___x_460_; 
v___x_460_ = lean_float32_of_bits(v_x_6_);
v___y_239_ = v___x_460_;
goto v___jp_238_;
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
v___y_239_ = v___x_470_;
goto v___jp_238_;
}
}
v___jp_471_:
{
if (v___y_472_ == 0)
{
float v___x_473_; 
v___x_473_ = lean_float32_of_bits(v_x_6_);
v___y_384_ = v___x_473_;
goto v___jp_383_;
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
v___y_384_ = v___x_483_;
goto v___jp_383_;
}
}
v___jp_485_:
{
uint32_t v___x_490_; uint32_t v___x_491_; uint32_t v___x_492_; uint32_t v___x_493_; uint32_t v___x_494_; 
v___x_490_ = lean_uint32_land(v___y_487_, v___x_484_);
v___x_491_ = lean_uint32_shift_left(v___x_490_, v___x_443_);
v___x_492_ = lean_uint32_lor(v___y_489_, v___x_491_);
v___x_493_ = lean_uint32_land(v___y_486_, v___y_488_);
v___x_494_ = lean_uint32_lor(v___x_492_, v___x_493_);
return v___x_494_;
}
v___jp_495_:
{
if (v___y_497_ == 0)
{
uint32_t v___x_500_; 
v___x_500_ = 0;
v___y_486_ = v___y_499_;
v___y_487_ = v___y_496_;
v___y_488_ = v___y_498_;
v___y_489_ = v___x_500_;
goto v___jp_485_;
}
else
{
uint32_t v___x_501_; 
v___x_501_ = 2147483648;
v___y_486_ = v___y_499_;
v___y_487_ = v___y_496_;
v___y_488_ = v___y_498_;
v___y_489_ = v___x_501_;
goto v___jp_485_;
}
}
v___jp_502_:
{
uint64_t v___x_508_; uint64_t v_encodedExponent_509_; uint32_t v___x_510_; uint64_t v___x_511_; uint8_t v___x_512_; 
v___x_508_ = 171ULL;
v_encodedExponent_509_ = lean_uint64_sub(v___y_504_, v___x_508_);
v___x_510_ = lean_uint64_to_uint32(v_encodedExponent_509_);
v___x_511_ = 8388608ULL;
v___x_512_ = lean_uint64_dec_lt(v___y_507_, v___x_511_);
if (v___x_512_ == 0)
{
uint64_t v___x_513_; uint32_t v___x_514_; 
v___x_513_ = lean_uint64_sub(v___y_507_, v___x_511_);
v___x_514_ = lean_uint64_to_uint32(v___x_513_);
v___y_496_ = v___x_510_;
v___y_497_ = v___y_505_;
v___y_498_ = v___y_506_;
v___y_499_ = v___x_514_;
goto v___jp_495_;
}
else
{
uint32_t v___x_515_; 
v___x_515_ = lean_uint64_to_uint32(v___y_503_);
v___y_496_ = v___x_510_;
v___y_497_ = v___y_505_;
v___y_498_ = v___y_506_;
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
if (v___y_521_ == 0)
{
v___y_503_ = v___y_518_;
v___y_504_ = v___y_522_;
v___y_505_ = v___y_519_;
v___y_506_ = v___y_520_;
v___y_507_ = v___y_517_;
goto v___jp_502_;
}
else
{
uint64_t v___x_525_; 
v___x_525_ = 8388608ULL;
v___y_503_ = v___y_518_;
v___y_504_ = v___y_522_;
v___y_505_ = v___y_519_;
v___y_506_ = v___y_520_;
v___y_507_ = v___x_525_;
goto v___jp_502_;
}
}
else
{
if (v___y_519_ == 0)
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
v___y_517_ = v___y_533_;
v___y_518_ = v___y_529_;
v___y_519_ = v___y_530_;
v___y_520_ = v___y_531_;
v___y_521_ = v_carry_535_;
v___y_522_ = v___y_532_;
goto v___jp_516_;
}
else
{
uint64_t v___x_536_; uint64_t v___x_537_; 
v___x_536_ = 1ULL;
v___x_537_ = lean_uint64_add(v___y_532_, v___x_536_);
v___y_517_ = v___y_533_;
v___y_518_ = v___y_529_;
v___y_519_ = v___y_530_;
v___y_520_ = v___y_531_;
v___y_521_ = v_carry_535_;
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
v___x_551_ = lean_uint64_dec_eq(v___x_550_, v___y_540_);
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
v___y_529_ = v___y_540_;
v___y_530_ = v___y_542_;
v___y_531_ = v___y_543_;
v___y_532_ = v_position_545_;
v___y_533_ = v___y_540_;
goto v___jp_528_;
}
else
{
uint64_t v___x_555_; uint8_t v___x_556_; 
v___x_555_ = 9223372036854775808ULL;
v___x_556_ = lean_uint64_dec_lt(v___x_555_, v___y_539_);
if (v___x_556_ == 0)
{
v___y_529_ = v___y_540_;
v___y_530_ = v___y_542_;
v___y_531_ = v___y_543_;
v___y_532_ = v_position_545_;
v___y_533_ = v___y_540_;
goto v___jp_528_;
}
else
{
uint64_t v___x_557_; 
v___x_557_ = 1ULL;
v___y_529_ = v___y_540_;
v___y_530_ = v___y_542_;
v___y_531_ = v___y_543_;
v___y_532_ = v_position_545_;
v___y_533_ = v___x_557_;
goto v___jp_528_;
}
}
}
else
{
uint64_t v_quotient_558_; uint64_t v___x_559_; uint64_t v___x_560_; uint64_t v___x_561_; uint64_t v_remainder_562_; uint64_t v___x_563_; uint64_t v_half_564_; uint8_t v___x_565_; 
v_quotient_558_ = lean_uint64_shift_right(v___y_539_, v___x_550_);
v___x_559_ = 1ULL;
v___x_560_ = lean_uint64_shift_left(v___x_559_, v___x_550_);
v___x_561_ = lean_uint64_sub(v___x_560_, v___x_559_);
v_remainder_562_ = lean_uint64_land(v___y_539_, v___x_561_);
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
v___x_568_ = lean_uint64_dec_eq(v___x_567_, v___y_540_);
if (v___x_568_ == 0)
{
uint64_t v___x_569_; 
v___x_569_ = lean_uint64_add(v_quotient_558_, v___x_559_);
v___y_529_ = v___y_540_;
v___y_530_ = v___y_542_;
v___y_531_ = v___y_543_;
v___y_532_ = v_position_545_;
v___y_533_ = v___x_569_;
goto v___jp_528_;
}
else
{
v___y_529_ = v___y_540_;
v___y_530_ = v___y_542_;
v___y_531_ = v___y_543_;
v___y_532_ = v_position_545_;
v___y_533_ = v_quotient_558_;
goto v___jp_528_;
}
}
else
{
uint64_t v___x_570_; 
v___x_570_ = lean_uint64_add(v_quotient_558_, v___x_559_);
v___y_529_ = v___y_540_;
v___y_530_ = v___y_542_;
v___y_531_ = v___y_543_;
v___y_532_ = v_position_545_;
v___y_533_ = v___x_570_;
goto v___jp_528_;
}
}
else
{
v___y_529_ = v___y_540_;
v___y_530_ = v___y_542_;
v___y_531_ = v___y_543_;
v___y_532_ = v_position_545_;
v___y_533_ = v_quotient_558_;
goto v___jp_528_;
}
}
}
else
{
v___y_529_ = v___y_540_;
v___y_530_ = v___y_542_;
v___y_531_ = v___y_543_;
v___y_532_ = v_position_545_;
v___y_533_ = v___y_539_;
goto v___jp_528_;
}
}
else
{
uint64_t v___x_571_; uint64_t v___x_572_; 
v___x_571_ = lean_uint64_sub(v___x_548_, v___y_544_);
v___x_572_ = lean_uint64_shift_left(v___y_539_, v___x_571_);
v___y_529_ = v___y_540_;
v___y_530_ = v___y_542_;
v___y_531_ = v___y_543_;
v___y_532_ = v_position_545_;
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
v___x_576_ = lean_uint64_shift_left(v___y_539_, v___x_575_);
v___y_118_ = v___y_540_;
v___y_119_ = v___y_542_;
v___y_120_ = v___y_543_;
v___y_121_ = v___x_576_;
goto v___jp_117_;
}
else
{
uint64_t v___x_577_; uint8_t v___x_578_; 
v___x_577_ = lean_uint64_sub(v___x_573_, v___y_541_);
v___x_578_ = lean_uint64_dec_eq(v___x_577_, v___y_540_);
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
v___y_118_ = v___y_540_;
v___y_119_ = v___y_542_;
v___y_120_ = v___y_543_;
v___y_121_ = v___y_540_;
goto v___jp_117_;
}
else
{
uint64_t v___x_582_; uint8_t v___x_583_; 
v___x_582_ = 9223372036854775808ULL;
v___x_583_ = lean_uint64_dec_lt(v___x_582_, v___y_539_);
if (v___x_583_ == 0)
{
v___y_118_ = v___y_540_;
v___y_119_ = v___y_542_;
v___y_120_ = v___y_543_;
v___y_121_ = v___y_540_;
goto v___jp_117_;
}
else
{
uint64_t v___x_584_; 
v___x_584_ = 1ULL;
v___y_118_ = v___y_540_;
v___y_119_ = v___y_542_;
v___y_120_ = v___y_543_;
v___y_121_ = v___x_584_;
goto v___jp_117_;
}
}
}
else
{
uint64_t v_quotient_585_; uint64_t v___x_586_; uint64_t v___x_587_; uint64_t v___x_588_; uint64_t v_remainder_589_; uint64_t v___x_590_; uint64_t v_half_591_; uint8_t v___x_592_; 
v_quotient_585_ = lean_uint64_shift_right(v___y_539_, v___x_577_);
v___x_586_ = 1ULL;
v___x_587_ = lean_uint64_shift_left(v___x_586_, v___x_577_);
v___x_588_ = lean_uint64_sub(v___x_587_, v___x_586_);
v_remainder_589_ = lean_uint64_land(v___y_539_, v___x_588_);
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
v___x_595_ = lean_uint64_dec_eq(v___x_594_, v___y_540_);
if (v___x_595_ == 0)
{
uint64_t v___x_596_; 
v___x_596_ = lean_uint64_add(v_quotient_585_, v___x_586_);
v___y_118_ = v___y_540_;
v___y_119_ = v___y_542_;
v___y_120_ = v___y_543_;
v___y_121_ = v___x_596_;
goto v___jp_117_;
}
else
{
v___y_118_ = v___y_540_;
v___y_119_ = v___y_542_;
v___y_120_ = v___y_543_;
v___y_121_ = v_quotient_585_;
goto v___jp_117_;
}
}
else
{
uint64_t v___x_597_; 
v___x_597_ = lean_uint64_add(v_quotient_585_, v___x_586_);
v___y_118_ = v___y_540_;
v___y_119_ = v___y_542_;
v___y_120_ = v___y_543_;
v___y_121_ = v___x_597_;
goto v___jp_117_;
}
}
else
{
v___y_118_ = v___y_540_;
v___y_119_ = v___y_542_;
v___y_120_ = v___y_543_;
v___y_121_ = v_quotient_585_;
goto v___jp_117_;
}
}
}
else
{
v___y_118_ = v___y_540_;
v___y_119_ = v___y_542_;
v___y_120_ = v___y_543_;
v___y_121_ = v___y_539_;
goto v___jp_117_;
}
}
}
}
v___jp_598_:
{
uint64_t v___x_606_; uint64_t v___x_607_; uint8_t v___x_608_; 
v___x_606_ = 1ULL;
v___x_607_ = lean_uint64_shift_right(v___y_600_, v___x_606_);
v___x_608_ = lean_uint64_dec_eq(v___x_607_, v___y_602_);
if (v___x_608_ == 0)
{
uint64_t v___x_609_; 
v___x_609_ = lean_uint64_add(v___y_605_, v___x_606_);
v___y_539_ = v___y_599_;
v___y_540_ = v___y_602_;
v___y_541_ = v___y_601_;
v___y_542_ = v___y_603_;
v___y_543_ = v___y_604_;
v___y_544_ = v___x_609_;
goto v___jp_538_;
}
else
{
v___y_539_ = v___y_599_;
v___y_540_ = v___y_602_;
v___y_541_ = v___y_601_;
v___y_542_ = v___y_603_;
v___y_543_ = v___y_604_;
v___y_544_ = v___y_605_;
goto v___jp_538_;
}
}
v___jp_610_:
{
uint64_t v___x_620_; uint8_t v___x_621_; 
v___x_620_ = lean_uint64_shift_right(v___y_614_, v___y_613_);
v___x_621_ = lean_uint64_dec_eq(v___x_620_, v___y_615_);
if (v___x_621_ == 0)
{
uint64_t v___x_622_; 
v___x_622_ = lean_uint64_add(v___y_612_, v___y_613_);
v___y_599_ = v___y_611_;
v___y_600_ = v___y_619_;
v___y_601_ = v___y_616_;
v___y_602_ = v___y_615_;
v___y_603_ = v___y_617_;
v___y_604_ = v___y_618_;
v___y_605_ = v___x_622_;
goto v___jp_598_;
}
else
{
v___y_599_ = v___y_611_;
v___y_600_ = v___y_619_;
v___y_601_ = v___y_616_;
v___y_602_ = v___y_615_;
v___y_603_ = v___y_617_;
v___y_604_ = v___y_618_;
v___y_605_ = v___y_612_;
goto v___jp_598_;
}
}
v___jp_623_:
{
uint64_t v___x_631_; uint64_t v___x_632_; uint8_t v___x_633_; 
v___x_631_ = 2ULL;
v___x_632_ = lean_uint64_shift_right(v___y_625_, v___x_631_);
v___x_633_ = lean_uint64_dec_eq(v___x_632_, v___y_627_);
if (v___x_633_ == 0)
{
v___y_611_ = v___y_624_;
v___y_612_ = v___y_630_;
v___y_613_ = v___x_631_;
v___y_614_ = v___y_625_;
v___y_615_ = v___y_627_;
v___y_616_ = v___y_626_;
v___y_617_ = v___y_628_;
v___y_618_ = v___y_629_;
v___y_619_ = v___x_632_;
goto v___jp_610_;
}
else
{
v___y_611_ = v___y_624_;
v___y_612_ = v___y_630_;
v___y_613_ = v___x_631_;
v___y_614_ = v___y_625_;
v___y_615_ = v___y_627_;
v___y_616_ = v___y_626_;
v___y_617_ = v___y_628_;
v___y_618_ = v___y_629_;
v___y_619_ = v___y_625_;
goto v___jp_610_;
}
}
v___jp_634_:
{
uint64_t v___x_644_; uint8_t v___x_645_; 
v___x_644_ = lean_uint64_shift_right(v___y_640_, v___y_636_);
v___x_645_ = lean_uint64_dec_eq(v___x_644_, v___y_638_);
if (v___x_645_ == 0)
{
uint64_t v___x_646_; 
v___x_646_ = lean_uint64_add(v___y_637_, v___y_636_);
v___y_624_ = v___y_635_;
v___y_625_ = v___y_643_;
v___y_626_ = v___y_639_;
v___y_627_ = v___y_638_;
v___y_628_ = v___y_641_;
v___y_629_ = v___y_642_;
v___y_630_ = v___x_646_;
goto v___jp_623_;
}
else
{
v___y_624_ = v___y_635_;
v___y_625_ = v___y_643_;
v___y_626_ = v___y_639_;
v___y_627_ = v___y_638_;
v___y_628_ = v___y_641_;
v___y_629_ = v___y_642_;
v___y_630_ = v___y_637_;
goto v___jp_623_;
}
}
v___jp_647_:
{
uint64_t v___x_655_; uint64_t v___x_656_; uint8_t v___x_657_; 
v___x_655_ = 4ULL;
v___x_656_ = lean_uint64_shift_right(v___y_652_, v___x_655_);
v___x_657_ = lean_uint64_dec_eq(v___x_656_, v___y_650_);
if (v___x_657_ == 0)
{
v___y_635_ = v___y_648_;
v___y_636_ = v___x_655_;
v___y_637_ = v___y_654_;
v___y_638_ = v___y_650_;
v___y_639_ = v___y_649_;
v___y_640_ = v___y_652_;
v___y_641_ = v___y_651_;
v___y_642_ = v___y_653_;
v___y_643_ = v___x_656_;
goto v___jp_634_;
}
else
{
v___y_635_ = v___y_648_;
v___y_636_ = v___x_655_;
v___y_637_ = v___y_654_;
v___y_638_ = v___y_650_;
v___y_639_ = v___y_649_;
v___y_640_ = v___y_652_;
v___y_641_ = v___y_651_;
v___y_642_ = v___y_653_;
v___y_643_ = v___y_652_;
goto v___jp_634_;
}
}
v___jp_658_:
{
uint64_t v___x_668_; uint8_t v___x_669_; 
v___x_668_ = lean_uint64_shift_right(v___y_661_, v___y_666_);
v___x_669_ = lean_uint64_dec_eq(v___x_668_, v___y_662_);
if (v___x_669_ == 0)
{
uint64_t v___x_670_; 
v___x_670_ = lean_uint64_add(v___y_660_, v___y_666_);
v___y_648_ = v___y_659_;
v___y_649_ = v___y_663_;
v___y_650_ = v___y_662_;
v___y_651_ = v___y_664_;
v___y_652_ = v___y_667_;
v___y_653_ = v___y_665_;
v___y_654_ = v___x_670_;
goto v___jp_647_;
}
else
{
v___y_648_ = v___y_659_;
v___y_649_ = v___y_663_;
v___y_650_ = v___y_662_;
v___y_651_ = v___y_664_;
v___y_652_ = v___y_667_;
v___y_653_ = v___y_665_;
v___y_654_ = v___y_660_;
goto v___jp_647_;
}
}
v___jp_671_:
{
uint64_t v___x_679_; uint64_t v___x_680_; uint8_t v___x_681_; 
v___x_679_ = 8ULL;
v___x_680_ = lean_uint64_shift_right(v___y_675_, v___x_679_);
v___x_681_ = lean_uint64_dec_eq(v___x_680_, v___y_674_);
if (v___x_681_ == 0)
{
v___y_659_ = v___y_672_;
v___y_660_ = v___y_678_;
v___y_661_ = v___y_675_;
v___y_662_ = v___y_674_;
v___y_663_ = v___y_673_;
v___y_664_ = v___y_676_;
v___y_665_ = v___y_677_;
v___y_666_ = v___x_679_;
v___y_667_ = v___x_680_;
goto v___jp_658_;
}
else
{
v___y_659_ = v___y_672_;
v___y_660_ = v___y_678_;
v___y_661_ = v___y_675_;
v___y_662_ = v___y_674_;
v___y_663_ = v___y_673_;
v___y_664_ = v___y_676_;
v___y_665_ = v___y_677_;
v___y_666_ = v___x_679_;
v___y_667_ = v___y_675_;
goto v___jp_658_;
}
}
v___jp_682_:
{
uint64_t v___x_692_; uint8_t v___x_693_; 
v___x_692_ = lean_uint64_shift_right(v___y_690_, v___y_685_);
v___x_693_ = lean_uint64_dec_eq(v___x_692_, v___y_686_);
if (v___x_693_ == 0)
{
uint64_t v___x_694_; 
v___x_694_ = lean_uint64_add(v___y_684_, v___y_685_);
v___y_672_ = v___y_683_;
v___y_673_ = v___y_687_;
v___y_674_ = v___y_686_;
v___y_675_ = v___y_691_;
v___y_676_ = v___y_688_;
v___y_677_ = v___y_689_;
v___y_678_ = v___x_694_;
goto v___jp_671_;
}
else
{
v___y_672_ = v___y_683_;
v___y_673_ = v___y_687_;
v___y_674_ = v___y_686_;
v___y_675_ = v___y_691_;
v___y_676_ = v___y_688_;
v___y_677_ = v___y_689_;
v___y_678_ = v___y_684_;
goto v___jp_671_;
}
}
v___jp_695_:
{
uint64_t v___x_703_; uint64_t v___x_704_; uint8_t v___x_705_; 
v___x_703_ = 16ULL;
v___x_704_ = lean_uint64_shift_right(v___y_701_, v___x_703_);
v___x_705_ = lean_uint64_dec_eq(v___x_704_, v___y_698_);
if (v___x_705_ == 0)
{
v___y_683_ = v___y_696_;
v___y_684_ = v___y_702_;
v___y_685_ = v___x_703_;
v___y_686_ = v___y_698_;
v___y_687_ = v___y_697_;
v___y_688_ = v___y_699_;
v___y_689_ = v___y_700_;
v___y_690_ = v___y_701_;
v___y_691_ = v___x_704_;
goto v___jp_682_;
}
else
{
v___y_683_ = v___y_696_;
v___y_684_ = v___y_702_;
v___y_685_ = v___x_703_;
v___y_686_ = v___y_698_;
v___y_687_ = v___y_697_;
v___y_688_ = v___y_699_;
v___y_689_ = v___y_700_;
v___y_690_ = v___y_701_;
v___y_691_ = v___y_701_;
goto v___jp_682_;
}
}
v___jp_706_:
{
uint64_t v___x_714_; uint8_t v___x_715_; 
v___x_714_ = lean_uint64_shift_right(v___y_707_, v___y_711_);
v___x_715_ = lean_uint64_dec_eq(v___x_714_, v___y_708_);
if (v___x_715_ == 0)
{
v___y_696_ = v___y_707_;
v___y_697_ = v___y_709_;
v___y_698_ = v___y_708_;
v___y_699_ = v___y_710_;
v___y_700_ = v___y_712_;
v___y_701_ = v___y_713_;
v___y_702_ = v___y_711_;
goto v___jp_695_;
}
else
{
v___y_696_ = v___y_707_;
v___y_697_ = v___y_709_;
v___y_698_ = v___y_708_;
v___y_699_ = v___y_710_;
v___y_700_ = v___y_712_;
v___y_701_ = v___y_713_;
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
v___y_707_ = v___y_717_;
v___y_708_ = v___x_721_;
v___y_709_ = v___y_718_;
v___y_710_ = v___y_719_;
v___y_711_ = v___x_723_;
v___y_712_ = v___y_720_;
v___y_713_ = v___x_724_;
goto v___jp_706_;
}
else
{
v___y_707_ = v___y_717_;
v___y_708_ = v___x_721_;
v___y_709_ = v___y_718_;
v___y_710_ = v___y_719_;
v___y_711_ = v___x_723_;
v___y_712_ = v___y_720_;
v___y_713_ = v___y_717_;
goto v___jp_706_;
}
}
else
{
if (v___y_719_ == 0)
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
v___x_735_ = lean_uint64_mul(v___y_729_, v___y_731_);
v___x_736_ = lean_uint64_add(v___y_732_, v___y_734_);
v___x_737_ = 281474976710656ULL;
v___x_738_ = lean_uint64_dec_lt(v___x_735_, v___x_737_);
if (v___x_738_ == 0)
{
v___y_717_ = v___x_735_;
v___y_718_ = v___x_736_;
v___y_719_ = v___y_730_;
v___y_720_ = v___y_733_;
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
v___y_719_ = v___y_730_;
v___y_720_ = v___y_733_;
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
v___y_139_ = v___y_730_;
v___y_140_ = v___y_733_;
v___y_141_ = v___x_741_;
v___y_142_ = v___x_741_;
goto v___jp_138_;
}
else
{
uint64_t v___x_749_; uint8_t v___x_750_; 
v___x_749_ = 9223372036854775808ULL;
v___x_750_ = lean_uint64_dec_lt(v___x_749_, v___x_735_);
if (v___x_750_ == 0)
{
v___y_139_ = v___y_730_;
v___y_140_ = v___y_733_;
v___y_141_ = v___x_741_;
v___y_142_ = v___x_741_;
goto v___jp_138_;
}
else
{
uint64_t v___x_751_; 
v___x_751_ = 1ULL;
v___y_139_ = v___y_730_;
v___y_140_ = v___y_733_;
v___y_141_ = v___x_741_;
v___y_142_ = v___x_751_;
goto v___jp_138_;
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
v___y_139_ = v___y_730_;
v___y_140_ = v___y_733_;
v___y_141_ = v___x_741_;
v___y_142_ = v___x_763_;
goto v___jp_138_;
}
else
{
v___y_139_ = v___y_730_;
v___y_140_ = v___y_733_;
v___y_141_ = v___x_741_;
v___y_142_ = v_quotient_752_;
goto v___jp_138_;
}
}
else
{
uint64_t v___x_764_; 
v___x_764_ = lean_uint64_add(v_quotient_752_, v___x_753_);
v___y_139_ = v___y_730_;
v___y_140_ = v___y_733_;
v___y_141_ = v___x_741_;
v___y_142_ = v___x_764_;
goto v___jp_138_;
}
}
else
{
v___y_139_ = v___y_730_;
v___y_140_ = v___y_733_;
v___y_141_ = v___x_741_;
v___y_142_ = v_quotient_752_;
goto v___jp_138_;
}
}
}
else
{
v___y_139_ = v___y_730_;
v___y_140_ = v___y_733_;
v___y_141_ = v___x_741_;
v___y_142_ = v___x_735_;
goto v___jp_138_;
}
}
else
{
if (v___y_730_ == 0)
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
v___x_775_ = lean_uint32_land(v___y_770_, v___y_768_);
v___x_776_ = lean_uint32_lor(v___x_774_, v___x_775_);
return v___x_776_;
}
v___jp_777_:
{
if (v___y_779_ == 0)
{
uint32_t v___x_782_; 
v___x_782_ = 0;
v___y_768_ = v___y_778_;
v___y_769_ = v___y_780_;
v___y_770_ = v___y_781_;
v___y_771_ = v___x_782_;
goto v___jp_767_;
}
else
{
uint32_t v___x_783_; 
v___x_783_ = 2147483648;
v___y_768_ = v___y_778_;
v___y_769_ = v___y_780_;
v___y_770_ = v___y_781_;
v___y_771_ = v___x_783_;
goto v___jp_767_;
}
}
v___jp_784_:
{
uint64_t v___x_790_; uint64_t v_encodedExponent_791_; uint32_t v___x_792_; uint64_t v___x_793_; uint8_t v___x_794_; 
v___x_790_ = 171ULL;
v_encodedExponent_791_ = lean_uint64_sub(v___y_788_, v___x_790_);
v___x_792_ = lean_uint64_to_uint32(v_encodedExponent_791_);
v___x_793_ = 8388608ULL;
v___x_794_ = lean_uint64_dec_lt(v___y_789_, v___x_793_);
if (v___x_794_ == 0)
{
uint64_t v___x_795_; uint32_t v___x_796_; 
v___x_795_ = lean_uint64_sub(v___y_789_, v___x_793_);
v___x_796_ = lean_uint64_to_uint32(v___x_795_);
v___y_778_ = v___y_785_;
v___y_779_ = v___y_786_;
v___y_780_ = v___x_792_;
v___y_781_ = v___x_796_;
goto v___jp_777_;
}
else
{
uint32_t v___x_797_; 
v___x_797_ = lean_uint64_to_uint32(v___y_787_);
v___y_778_ = v___y_785_;
v___y_779_ = v___y_786_;
v___y_780_ = v___x_792_;
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
v___y_786_ = v___y_801_;
v___y_787_ = v___y_802_;
v___y_788_ = v___y_804_;
v___y_789_ = v___y_803_;
goto v___jp_784_;
}
else
{
uint64_t v___x_807_; 
v___x_807_ = 8388608ULL;
v___y_785_ = v___y_800_;
v___y_786_ = v___y_801_;
v___y_787_ = v___y_802_;
v___y_788_ = v___y_804_;
v___y_789_ = v___x_807_;
goto v___jp_784_;
}
}
else
{
if (v___y_801_ == 0)
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
v___y_801_ = v___y_812_;
v___y_802_ = v___y_814_;
v___y_803_ = v___y_815_;
v___y_804_ = v___y_813_;
goto v___jp_798_;
}
else
{
uint64_t v___x_818_; uint64_t v___x_819_; 
v___x_818_ = 1ULL;
v___x_819_ = lean_uint64_add(v___y_813_, v___x_818_);
v___y_799_ = v_carry_817_;
v___y_800_ = v___y_811_;
v___y_801_ = v___y_812_;
v___y_802_ = v___y_814_;
v___y_803_ = v___y_815_;
v___y_804_ = v___x_819_;
goto v___jp_798_;
}
}
v___jp_820_:
{
uint64_t v_position_827_; uint64_t v___x_828_; uint8_t v___x_829_; 
v_position_827_ = lean_uint64_add(v___y_826_, v___y_824_);
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
v___x_833_ = lean_uint64_dec_eq(v___x_832_, v___y_825_);
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
v___y_811_ = v___y_822_;
v___y_812_ = v___y_823_;
v___y_813_ = v_position_827_;
v___y_814_ = v___y_825_;
v___y_815_ = v___y_825_;
goto v___jp_810_;
}
else
{
uint64_t v___x_837_; uint8_t v___x_838_; 
v___x_837_ = 9223372036854775808ULL;
v___x_838_ = lean_uint64_dec_lt(v___x_837_, v___y_821_);
if (v___x_838_ == 0)
{
v___y_811_ = v___y_822_;
v___y_812_ = v___y_823_;
v___y_813_ = v_position_827_;
v___y_814_ = v___y_825_;
v___y_815_ = v___y_825_;
goto v___jp_810_;
}
else
{
uint64_t v___x_839_; 
v___x_839_ = 1ULL;
v___y_811_ = v___y_822_;
v___y_812_ = v___y_823_;
v___y_813_ = v_position_827_;
v___y_814_ = v___y_825_;
v___y_815_ = v___x_839_;
goto v___jp_810_;
}
}
}
else
{
uint64_t v_quotient_840_; uint64_t v___x_841_; uint64_t v___x_842_; uint64_t v___x_843_; uint64_t v_remainder_844_; uint64_t v___x_845_; uint64_t v_half_846_; uint8_t v___x_847_; 
v_quotient_840_ = lean_uint64_shift_right(v___y_821_, v___x_832_);
v___x_841_ = 1ULL;
v___x_842_ = lean_uint64_shift_left(v___x_841_, v___x_832_);
v___x_843_ = lean_uint64_sub(v___x_842_, v___x_841_);
v_remainder_844_ = lean_uint64_land(v___y_821_, v___x_843_);
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
v___x_850_ = lean_uint64_dec_eq(v___x_849_, v___y_825_);
if (v___x_850_ == 0)
{
uint64_t v___x_851_; 
v___x_851_ = lean_uint64_add(v_quotient_840_, v___x_841_);
v___y_811_ = v___y_822_;
v___y_812_ = v___y_823_;
v___y_813_ = v_position_827_;
v___y_814_ = v___y_825_;
v___y_815_ = v___x_851_;
goto v___jp_810_;
}
else
{
v___y_811_ = v___y_822_;
v___y_812_ = v___y_823_;
v___y_813_ = v_position_827_;
v___y_814_ = v___y_825_;
v___y_815_ = v_quotient_840_;
goto v___jp_810_;
}
}
else
{
uint64_t v___x_852_; 
v___x_852_ = lean_uint64_add(v_quotient_840_, v___x_841_);
v___y_811_ = v___y_822_;
v___y_812_ = v___y_823_;
v___y_813_ = v_position_827_;
v___y_814_ = v___y_825_;
v___y_815_ = v___x_852_;
goto v___jp_810_;
}
}
else
{
v___y_811_ = v___y_822_;
v___y_812_ = v___y_823_;
v___y_813_ = v_position_827_;
v___y_814_ = v___y_825_;
v___y_815_ = v_quotient_840_;
goto v___jp_810_;
}
}
}
else
{
v___y_811_ = v___y_822_;
v___y_812_ = v___y_823_;
v___y_813_ = v_position_827_;
v___y_814_ = v___y_825_;
v___y_815_ = v___y_821_;
goto v___jp_810_;
}
}
else
{
uint64_t v___x_853_; uint64_t v___x_854_; 
v___x_853_ = lean_uint64_sub(v___x_830_, v___y_826_);
v___x_854_ = lean_uint64_shift_left(v___y_821_, v___x_853_);
v___y_811_ = v___y_822_;
v___y_812_ = v___y_823_;
v___y_813_ = v_position_827_;
v___y_814_ = v___y_825_;
v___y_815_ = v___x_854_;
goto v___jp_810_;
}
}
else
{
uint64_t v___x_855_; uint8_t v___x_856_; 
v___x_855_ = 149ULL;
v___x_856_ = lean_uint64_dec_lt(v___y_824_, v___x_855_);
if (v___x_856_ == 0)
{
uint64_t v___x_857_; uint64_t v___x_858_; 
v___x_857_ = lean_uint64_sub(v___y_824_, v___x_855_);
v___x_858_ = lean_uint64_shift_left(v___y_821_, v___x_857_);
v___y_263_ = v___y_822_;
v___y_264_ = v___y_823_;
v___y_265_ = v___y_825_;
v___y_266_ = v___x_858_;
goto v___jp_262_;
}
else
{
uint64_t v___x_859_; uint8_t v___x_860_; 
v___x_859_ = lean_uint64_sub(v___x_855_, v___y_824_);
v___x_860_ = lean_uint64_dec_eq(v___x_859_, v___y_825_);
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
v___y_263_ = v___y_822_;
v___y_264_ = v___y_823_;
v___y_265_ = v___y_825_;
v___y_266_ = v___y_825_;
goto v___jp_262_;
}
else
{
uint64_t v___x_864_; uint8_t v___x_865_; 
v___x_864_ = 9223372036854775808ULL;
v___x_865_ = lean_uint64_dec_lt(v___x_864_, v___y_821_);
if (v___x_865_ == 0)
{
v___y_263_ = v___y_822_;
v___y_264_ = v___y_823_;
v___y_265_ = v___y_825_;
v___y_266_ = v___y_825_;
goto v___jp_262_;
}
else
{
uint64_t v___x_866_; 
v___x_866_ = 1ULL;
v___y_263_ = v___y_822_;
v___y_264_ = v___y_823_;
v___y_265_ = v___y_825_;
v___y_266_ = v___x_866_;
goto v___jp_262_;
}
}
}
else
{
uint64_t v_quotient_867_; uint64_t v___x_868_; uint64_t v___x_869_; uint64_t v___x_870_; uint64_t v_remainder_871_; uint64_t v___x_872_; uint64_t v_half_873_; uint8_t v___x_874_; 
v_quotient_867_ = lean_uint64_shift_right(v___y_821_, v___x_859_);
v___x_868_ = 1ULL;
v___x_869_ = lean_uint64_shift_left(v___x_868_, v___x_859_);
v___x_870_ = lean_uint64_sub(v___x_869_, v___x_868_);
v_remainder_871_ = lean_uint64_land(v___y_821_, v___x_870_);
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
v___x_877_ = lean_uint64_dec_eq(v___x_876_, v___y_825_);
if (v___x_877_ == 0)
{
uint64_t v___x_878_; 
v___x_878_ = lean_uint64_add(v_quotient_867_, v___x_868_);
v___y_263_ = v___y_822_;
v___y_264_ = v___y_823_;
v___y_265_ = v___y_825_;
v___y_266_ = v___x_878_;
goto v___jp_262_;
}
else
{
v___y_263_ = v___y_822_;
v___y_264_ = v___y_823_;
v___y_265_ = v___y_825_;
v___y_266_ = v_quotient_867_;
goto v___jp_262_;
}
}
else
{
uint64_t v___x_879_; 
v___x_879_ = lean_uint64_add(v_quotient_867_, v___x_868_);
v___y_263_ = v___y_822_;
v___y_264_ = v___y_823_;
v___y_265_ = v___y_825_;
v___y_266_ = v___x_879_;
goto v___jp_262_;
}
}
else
{
v___y_263_ = v___y_822_;
v___y_264_ = v___y_823_;
v___y_265_ = v___y_825_;
v___y_266_ = v_quotient_867_;
goto v___jp_262_;
}
}
}
else
{
v___y_263_ = v___y_822_;
v___y_264_ = v___y_823_;
v___y_265_ = v___y_825_;
v___y_266_ = v___y_821_;
goto v___jp_262_;
}
}
}
}
v___jp_880_:
{
uint64_t v___x_888_; uint64_t v___x_889_; uint8_t v___x_890_; 
v___x_888_ = 1ULL;
v___x_889_ = lean_uint64_shift_right(v___y_881_, v___x_888_);
v___x_890_ = lean_uint64_dec_eq(v___x_889_, v___y_886_);
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
v___x_902_ = lean_uint64_shift_right(v___y_897_, v___y_895_);
v___x_903_ = lean_uint64_dec_eq(v___x_902_, v___y_899_);
if (v___x_903_ == 0)
{
uint64_t v___x_904_; 
v___x_904_ = lean_uint64_add(v___y_900_, v___y_895_);
v___y_881_ = v___y_901_;
v___y_882_ = v___y_893_;
v___y_883_ = v___y_894_;
v___y_884_ = v___y_896_;
v___y_885_ = v___y_898_;
v___y_886_ = v___y_899_;
v___y_887_ = v___x_904_;
goto v___jp_880_;
}
else
{
v___y_881_ = v___y_901_;
v___y_882_ = v___y_893_;
v___y_883_ = v___y_894_;
v___y_884_ = v___y_896_;
v___y_885_ = v___y_898_;
v___y_886_ = v___y_899_;
v___y_887_ = v___y_900_;
goto v___jp_880_;
}
}
v___jp_905_:
{
uint64_t v___x_913_; uint64_t v___x_914_; uint8_t v___x_915_; 
v___x_913_ = 2ULL;
v___x_914_ = lean_uint64_shift_right(v___y_910_, v___x_913_);
v___x_915_ = lean_uint64_dec_eq(v___x_914_, v___y_911_);
if (v___x_915_ == 0)
{
v___y_893_ = v___y_906_;
v___y_894_ = v___y_907_;
v___y_895_ = v___x_913_;
v___y_896_ = v___y_908_;
v___y_897_ = v___y_910_;
v___y_898_ = v___y_909_;
v___y_899_ = v___y_911_;
v___y_900_ = v___y_912_;
v___y_901_ = v___x_914_;
goto v___jp_892_;
}
else
{
v___y_893_ = v___y_906_;
v___y_894_ = v___y_907_;
v___y_895_ = v___x_913_;
v___y_896_ = v___y_908_;
v___y_897_ = v___y_910_;
v___y_898_ = v___y_909_;
v___y_899_ = v___y_911_;
v___y_900_ = v___y_912_;
v___y_901_ = v___y_910_;
goto v___jp_892_;
}
}
v___jp_916_:
{
uint64_t v___x_926_; uint8_t v___x_927_; 
v___x_926_ = lean_uint64_shift_right(v___y_922_, v___y_924_);
v___x_927_ = lean_uint64_dec_eq(v___x_926_, v___y_921_);
if (v___x_927_ == 0)
{
uint64_t v___x_928_; 
v___x_928_ = lean_uint64_add(v___y_923_, v___y_924_);
v___y_906_ = v___y_917_;
v___y_907_ = v___y_918_;
v___y_908_ = v___y_919_;
v___y_909_ = v___y_920_;
v___y_910_ = v___y_925_;
v___y_911_ = v___y_921_;
v___y_912_ = v___x_928_;
goto v___jp_905_;
}
else
{
v___y_906_ = v___y_917_;
v___y_907_ = v___y_918_;
v___y_908_ = v___y_919_;
v___y_909_ = v___y_920_;
v___y_910_ = v___y_925_;
v___y_911_ = v___y_921_;
v___y_912_ = v___y_923_;
goto v___jp_905_;
}
}
v___jp_929_:
{
uint64_t v___x_937_; uint64_t v___x_938_; uint8_t v___x_939_; 
v___x_937_ = 4ULL;
v___x_938_ = lean_uint64_shift_right(v___y_935_, v___x_937_);
v___x_939_ = lean_uint64_dec_eq(v___x_938_, v___y_934_);
if (v___x_939_ == 0)
{
v___y_917_ = v___y_930_;
v___y_918_ = v___y_931_;
v___y_919_ = v___y_932_;
v___y_920_ = v___y_933_;
v___y_921_ = v___y_934_;
v___y_922_ = v___y_935_;
v___y_923_ = v___y_936_;
v___y_924_ = v___x_937_;
v___y_925_ = v___x_938_;
goto v___jp_916_;
}
else
{
v___y_917_ = v___y_930_;
v___y_918_ = v___y_931_;
v___y_919_ = v___y_932_;
v___y_920_ = v___y_933_;
v___y_921_ = v___y_934_;
v___y_922_ = v___y_935_;
v___y_923_ = v___y_936_;
v___y_924_ = v___x_937_;
v___y_925_ = v___y_935_;
goto v___jp_916_;
}
}
v___jp_940_:
{
uint64_t v___x_950_; uint8_t v___x_951_; 
v___x_950_ = lean_uint64_shift_right(v___y_947_, v___y_948_);
v___x_951_ = lean_uint64_dec_eq(v___x_950_, v___y_946_);
if (v___x_951_ == 0)
{
uint64_t v___x_952_; 
v___x_952_ = lean_uint64_add(v___y_941_, v___y_948_);
v___y_930_ = v___y_942_;
v___y_931_ = v___y_943_;
v___y_932_ = v___y_944_;
v___y_933_ = v___y_945_;
v___y_934_ = v___y_946_;
v___y_935_ = v___y_949_;
v___y_936_ = v___x_952_;
goto v___jp_929_;
}
else
{
v___y_930_ = v___y_942_;
v___y_931_ = v___y_943_;
v___y_932_ = v___y_944_;
v___y_933_ = v___y_945_;
v___y_934_ = v___y_946_;
v___y_935_ = v___y_949_;
v___y_936_ = v___y_941_;
goto v___jp_929_;
}
}
v___jp_953_:
{
uint64_t v___x_961_; uint64_t v___x_962_; uint8_t v___x_963_; 
v___x_961_ = 8ULL;
v___x_962_ = lean_uint64_shift_right(v___y_959_, v___x_961_);
v___x_963_ = lean_uint64_dec_eq(v___x_962_, v___y_958_);
if (v___x_963_ == 0)
{
v___y_941_ = v___y_960_;
v___y_942_ = v___y_954_;
v___y_943_ = v___y_955_;
v___y_944_ = v___y_956_;
v___y_945_ = v___y_957_;
v___y_946_ = v___y_958_;
v___y_947_ = v___y_959_;
v___y_948_ = v___x_961_;
v___y_949_ = v___x_962_;
goto v___jp_940_;
}
else
{
v___y_941_ = v___y_960_;
v___y_942_ = v___y_954_;
v___y_943_ = v___y_955_;
v___y_944_ = v___y_956_;
v___y_945_ = v___y_957_;
v___y_946_ = v___y_958_;
v___y_947_ = v___y_959_;
v___y_948_ = v___x_961_;
v___y_949_ = v___y_959_;
goto v___jp_940_;
}
}
v___jp_964_:
{
uint64_t v___x_974_; uint8_t v___x_975_; 
v___x_974_ = lean_uint64_shift_right(v___y_968_, v___y_972_);
v___x_975_ = lean_uint64_dec_eq(v___x_974_, v___y_971_);
if (v___x_975_ == 0)
{
uint64_t v___x_976_; 
v___x_976_ = lean_uint64_add(v___y_969_, v___y_972_);
v___y_954_ = v___y_965_;
v___y_955_ = v___y_966_;
v___y_956_ = v___y_967_;
v___y_957_ = v___y_970_;
v___y_958_ = v___y_971_;
v___y_959_ = v___y_973_;
v___y_960_ = v___x_976_;
goto v___jp_953_;
}
else
{
v___y_954_ = v___y_965_;
v___y_955_ = v___y_966_;
v___y_956_ = v___y_967_;
v___y_957_ = v___y_970_;
v___y_958_ = v___y_971_;
v___y_959_ = v___y_973_;
v___y_960_ = v___y_969_;
goto v___jp_953_;
}
}
v___jp_977_:
{
uint64_t v___x_985_; uint64_t v___x_986_; uint8_t v___x_987_; 
v___x_985_ = 16ULL;
v___x_986_ = lean_uint64_shift_right(v___y_981_, v___x_985_);
v___x_987_ = lean_uint64_dec_eq(v___x_986_, v___y_983_);
if (v___x_987_ == 0)
{
v___y_965_ = v___y_978_;
v___y_966_ = v___y_979_;
v___y_967_ = v___y_980_;
v___y_968_ = v___y_981_;
v___y_969_ = v___y_984_;
v___y_970_ = v___y_982_;
v___y_971_ = v___y_983_;
v___y_972_ = v___x_985_;
v___y_973_ = v___x_986_;
goto v___jp_964_;
}
else
{
v___y_965_ = v___y_978_;
v___y_966_ = v___y_979_;
v___y_967_ = v___y_980_;
v___y_968_ = v___y_981_;
v___y_969_ = v___y_984_;
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
v___x_996_ = lean_uint64_shift_right(v___y_989_, v___y_992_);
v___x_997_ = lean_uint64_dec_eq(v___x_996_, v___y_994_);
if (v___x_997_ == 0)
{
v___y_978_ = v___y_989_;
v___y_979_ = v___y_990_;
v___y_980_ = v___y_991_;
v___y_981_ = v___y_995_;
v___y_982_ = v___y_993_;
v___y_983_ = v___y_994_;
v___y_984_ = v___y_992_;
goto v___jp_977_;
}
else
{
v___y_978_ = v___y_989_;
v___y_979_ = v___y_990_;
v___y_980_ = v___y_991_;
v___y_981_ = v___y_995_;
v___y_982_ = v___y_993_;
v___y_983_ = v___y_994_;
v___y_984_ = v___y_994_;
goto v___jp_977_;
}
}
v___jp_998_:
{
uint64_t v___x_1003_; uint8_t v___x_1004_; 
v___x_1003_ = 0ULL;
v___x_1004_ = lean_uint64_dec_eq(v___y_999_, v___x_1003_);
if (v___x_1004_ == 0)
{
uint64_t v___x_1005_; uint64_t v___x_1006_; uint8_t v___x_1007_; 
v___x_1005_ = 32ULL;
v___x_1006_ = lean_uint64_shift_right(v___y_999_, v___x_1005_);
v___x_1007_ = lean_uint64_dec_eq(v___x_1006_, v___x_1003_);
if (v___x_1007_ == 0)
{
v___y_989_ = v___y_999_;
v___y_990_ = v___y_1000_;
v___y_991_ = v___y_1001_;
v___y_992_ = v___x_1005_;
v___y_993_ = v___y_1002_;
v___y_994_ = v___x_1003_;
v___y_995_ = v___x_1006_;
goto v___jp_988_;
}
else
{
v___y_989_ = v___y_999_;
v___y_990_ = v___y_1000_;
v___y_991_ = v___y_1001_;
v___y_992_ = v___x_1005_;
v___y_993_ = v___y_1002_;
v___y_994_ = v___x_1003_;
v___y_995_ = v___y_999_;
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
v___x_1017_ = lean_uint64_mul(v___y_1014_, v___y_1015_);
v___x_1018_ = lean_uint64_add(v___y_1011_, v___y_1016_);
v___x_1019_ = 281474976710656ULL;
v___x_1020_ = lean_uint64_dec_lt(v___x_1017_, v___x_1019_);
if (v___x_1020_ == 0)
{
v___y_999_ = v___x_1017_;
v___y_1000_ = v___y_1012_;
v___y_1001_ = v___y_1013_;
v___y_1002_ = v___x_1018_;
goto v___jp_998_;
}
else
{
uint64_t v___x_1021_; uint8_t v___x_1022_; 
v___x_1021_ = 123ULL;
v___x_1022_ = lean_uint64_dec_le(v___x_1018_, v___x_1021_);
if (v___x_1022_ == 0)
{
v___y_999_ = v___x_1017_;
v___y_1000_ = v___y_1012_;
v___y_1001_ = v___y_1013_;
v___y_1002_ = v___x_1018_;
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
v___y_284_ = v___y_1012_;
v___y_285_ = v___x_1023_;
v___y_286_ = v___y_1013_;
v___y_287_ = v___x_1023_;
goto v___jp_283_;
}
else
{
uint64_t v___x_1031_; uint8_t v___x_1032_; 
v___x_1031_ = 9223372036854775808ULL;
v___x_1032_ = lean_uint64_dec_lt(v___x_1031_, v___x_1017_);
if (v___x_1032_ == 0)
{
v___y_284_ = v___y_1012_;
v___y_285_ = v___x_1023_;
v___y_286_ = v___y_1013_;
v___y_287_ = v___x_1023_;
goto v___jp_283_;
}
else
{
uint64_t v___x_1033_; 
v___x_1033_ = 1ULL;
v___y_284_ = v___y_1012_;
v___y_285_ = v___x_1023_;
v___y_286_ = v___y_1013_;
v___y_287_ = v___x_1033_;
goto v___jp_283_;
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
v___y_284_ = v___y_1012_;
v___y_285_ = v___x_1023_;
v___y_286_ = v___y_1013_;
v___y_287_ = v___x_1045_;
goto v___jp_283_;
}
else
{
v___y_284_ = v___y_1012_;
v___y_285_ = v___x_1023_;
v___y_286_ = v___y_1013_;
v___y_287_ = v_quotient_1034_;
goto v___jp_283_;
}
}
else
{
uint64_t v___x_1046_; 
v___x_1046_ = lean_uint64_add(v_quotient_1034_, v___x_1035_);
v___y_284_ = v___y_1012_;
v___y_285_ = v___x_1023_;
v___y_286_ = v___y_1013_;
v___y_287_ = v___x_1046_;
goto v___jp_283_;
}
}
else
{
v___y_284_ = v___y_1012_;
v___y_285_ = v___x_1023_;
v___y_286_ = v___y_1013_;
v___y_287_ = v_quotient_1034_;
goto v___jp_283_;
}
}
}
else
{
v___y_284_ = v___y_1012_;
v___y_285_ = v___x_1023_;
v___y_286_ = v___y_1013_;
v___y_287_ = v___x_1017_;
goto v___jp_283_;
}
}
else
{
if (v___y_1013_ == 0)
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
v___x_1054_ = lean_uint32_land(v___y_1050_, v___x_484_);
v___x_1055_ = lean_uint32_shift_left(v___x_1054_, v___x_443_);
v___x_1056_ = lean_uint32_lor(v___y_1053_, v___x_1055_);
v___x_1057_ = lean_uint32_land(v___y_1052_, v___y_1051_);
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
v___y_1051_ = v___y_1062_;
v___y_1052_ = v___y_1063_;
v___y_1053_ = v___x_1064_;
goto v___jp_1049_;
}
else
{
uint32_t v___x_1065_; 
v___x_1065_ = 2147483648;
v___y_1050_ = v___y_1060_;
v___y_1051_ = v___y_1062_;
v___y_1052_ = v___y_1063_;
v___y_1053_ = v___x_1065_;
goto v___jp_1049_;
}
}
v___jp_1066_:
{
uint64_t v___x_1072_; uint64_t v_encodedExponent_1073_; uint32_t v___x_1074_; uint64_t v___x_1075_; uint8_t v___x_1076_; 
v___x_1072_ = 171ULL;
v_encodedExponent_1073_ = lean_uint64_sub(v___y_1070_, v___x_1072_);
v___x_1074_ = lean_uint64_to_uint32(v_encodedExponent_1073_);
v___x_1075_ = 8388608ULL;
v___x_1076_ = lean_uint64_dec_lt(v___y_1071_, v___x_1075_);
if (v___x_1076_ == 0)
{
uint64_t v___x_1077_; uint32_t v___x_1078_; 
v___x_1077_ = lean_uint64_sub(v___y_1071_, v___x_1075_);
v___x_1078_ = lean_uint64_to_uint32(v___x_1077_);
v___y_1060_ = v___x_1074_;
v___y_1061_ = v___y_1067_;
v___y_1062_ = v___y_1069_;
v___y_1063_ = v___x_1078_;
goto v___jp_1059_;
}
else
{
uint32_t v___x_1079_; 
v___x_1079_ = lean_uint64_to_uint32(v___y_1068_);
v___y_1060_ = v___x_1074_;
v___y_1061_ = v___y_1067_;
v___y_1062_ = v___y_1069_;
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
if (v___y_1082_ == 0)
{
v___y_1067_ = v___y_1081_;
v___y_1068_ = v___y_1084_;
v___y_1069_ = v___y_1083_;
v___y_1070_ = v___y_1086_;
v___y_1071_ = v___y_1085_;
goto v___jp_1066_;
}
else
{
uint64_t v___x_1089_; 
v___x_1089_ = 8388608ULL;
v___y_1067_ = v___y_1081_;
v___y_1068_ = v___y_1084_;
v___y_1069_ = v___y_1083_;
v___y_1070_ = v___y_1086_;
v___y_1071_ = v___x_1089_;
goto v___jp_1066_;
}
}
else
{
if (v___y_1081_ == 0)
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
v___y_1081_ = v___y_1093_;
v___y_1082_ = v_carry_1099_;
v___y_1083_ = v___y_1096_;
v___y_1084_ = v___y_1095_;
v___y_1085_ = v___y_1097_;
v___y_1086_ = v___y_1094_;
goto v___jp_1080_;
}
else
{
uint64_t v___x_1100_; uint64_t v___x_1101_; 
v___x_1100_ = 1ULL;
v___x_1101_ = lean_uint64_add(v___y_1094_, v___x_1100_);
v___y_1081_ = v___y_1093_;
v___y_1082_ = v_carry_1099_;
v___y_1083_ = v___y_1096_;
v___y_1084_ = v___y_1095_;
v___y_1085_ = v___y_1097_;
v___y_1086_ = v___x_1101_;
goto v___jp_1080_;
}
}
v___jp_1102_:
{
uint64_t v_position_1109_; uint64_t v___x_1110_; uint8_t v___x_1111_; 
v_position_1109_ = lean_uint64_add(v___y_1108_, v___y_1103_);
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
v___y_1093_ = v___y_1105_;
v___y_1094_ = v_position_1109_;
v___y_1095_ = v___y_1107_;
v___y_1096_ = v___y_1106_;
v___y_1097_ = v___y_1107_;
goto v___jp_1092_;
}
else
{
uint64_t v___x_1119_; uint8_t v___x_1120_; 
v___x_1119_ = 9223372036854775808ULL;
v___x_1120_ = lean_uint64_dec_lt(v___x_1119_, v___y_1104_);
if (v___x_1120_ == 0)
{
v___y_1093_ = v___y_1105_;
v___y_1094_ = v_position_1109_;
v___y_1095_ = v___y_1107_;
v___y_1096_ = v___y_1106_;
v___y_1097_ = v___y_1107_;
goto v___jp_1092_;
}
else
{
uint64_t v___x_1121_; 
v___x_1121_ = 1ULL;
v___y_1093_ = v___y_1105_;
v___y_1094_ = v_position_1109_;
v___y_1095_ = v___y_1107_;
v___y_1096_ = v___y_1106_;
v___y_1097_ = v___x_1121_;
goto v___jp_1092_;
}
}
}
else
{
uint64_t v_quotient_1122_; uint64_t v___x_1123_; uint64_t v___x_1124_; uint64_t v___x_1125_; uint64_t v_remainder_1126_; uint64_t v___x_1127_; uint64_t v_half_1128_; uint8_t v___x_1129_; 
v_quotient_1122_ = lean_uint64_shift_right(v___y_1104_, v___x_1114_);
v___x_1123_ = 1ULL;
v___x_1124_ = lean_uint64_shift_left(v___x_1123_, v___x_1114_);
v___x_1125_ = lean_uint64_sub(v___x_1124_, v___x_1123_);
v_remainder_1126_ = lean_uint64_land(v___y_1104_, v___x_1125_);
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
v___y_1093_ = v___y_1105_;
v___y_1094_ = v_position_1109_;
v___y_1095_ = v___y_1107_;
v___y_1096_ = v___y_1106_;
v___y_1097_ = v___x_1133_;
goto v___jp_1092_;
}
else
{
v___y_1093_ = v___y_1105_;
v___y_1094_ = v_position_1109_;
v___y_1095_ = v___y_1107_;
v___y_1096_ = v___y_1106_;
v___y_1097_ = v_quotient_1122_;
goto v___jp_1092_;
}
}
else
{
uint64_t v___x_1134_; 
v___x_1134_ = lean_uint64_add(v_quotient_1122_, v___x_1123_);
v___y_1093_ = v___y_1105_;
v___y_1094_ = v_position_1109_;
v___y_1095_ = v___y_1107_;
v___y_1096_ = v___y_1106_;
v___y_1097_ = v___x_1134_;
goto v___jp_1092_;
}
}
else
{
v___y_1093_ = v___y_1105_;
v___y_1094_ = v_position_1109_;
v___y_1095_ = v___y_1107_;
v___y_1096_ = v___y_1106_;
v___y_1097_ = v_quotient_1122_;
goto v___jp_1092_;
}
}
}
else
{
v___y_1093_ = v___y_1105_;
v___y_1094_ = v_position_1109_;
v___y_1095_ = v___y_1107_;
v___y_1096_ = v___y_1106_;
v___y_1097_ = v___y_1104_;
goto v___jp_1092_;
}
}
else
{
uint64_t v___x_1135_; uint64_t v___x_1136_; 
v___x_1135_ = lean_uint64_sub(v___x_1112_, v___y_1108_);
v___x_1136_ = lean_uint64_shift_left(v___y_1104_, v___x_1135_);
v___y_1093_ = v___y_1105_;
v___y_1094_ = v_position_1109_;
v___y_1095_ = v___y_1107_;
v___y_1096_ = v___y_1106_;
v___y_1097_ = v___x_1136_;
goto v___jp_1092_;
}
}
else
{
uint64_t v___x_1137_; uint8_t v___x_1138_; 
v___x_1137_ = 149ULL;
v___x_1138_ = lean_uint64_dec_lt(v___y_1103_, v___x_1137_);
if (v___x_1138_ == 0)
{
uint64_t v___x_1139_; uint64_t v___x_1140_; 
v___x_1139_ = lean_uint64_sub(v___y_1103_, v___x_1137_);
v___x_1140_ = lean_uint64_shift_left(v___y_1104_, v___x_1139_);
v___y_408_ = v___y_1105_;
v___y_409_ = v___y_1106_;
v___y_410_ = v___y_1107_;
v___y_411_ = v___x_1140_;
goto v___jp_407_;
}
else
{
uint64_t v___x_1141_; uint8_t v___x_1142_; 
v___x_1141_ = lean_uint64_sub(v___x_1137_, v___y_1103_);
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
v___y_408_ = v___y_1105_;
v___y_409_ = v___y_1106_;
v___y_410_ = v___y_1107_;
v___y_411_ = v___y_1107_;
goto v___jp_407_;
}
else
{
uint64_t v___x_1146_; uint8_t v___x_1147_; 
v___x_1146_ = 9223372036854775808ULL;
v___x_1147_ = lean_uint64_dec_lt(v___x_1146_, v___y_1104_);
if (v___x_1147_ == 0)
{
v___y_408_ = v___y_1105_;
v___y_409_ = v___y_1106_;
v___y_410_ = v___y_1107_;
v___y_411_ = v___y_1107_;
goto v___jp_407_;
}
else
{
uint64_t v___x_1148_; 
v___x_1148_ = 1ULL;
v___y_408_ = v___y_1105_;
v___y_409_ = v___y_1106_;
v___y_410_ = v___y_1107_;
v___y_411_ = v___x_1148_;
goto v___jp_407_;
}
}
}
else
{
uint64_t v_quotient_1149_; uint64_t v___x_1150_; uint64_t v___x_1151_; uint64_t v___x_1152_; uint64_t v_remainder_1153_; uint64_t v___x_1154_; uint64_t v_half_1155_; uint8_t v___x_1156_; 
v_quotient_1149_ = lean_uint64_shift_right(v___y_1104_, v___x_1141_);
v___x_1150_ = 1ULL;
v___x_1151_ = lean_uint64_shift_left(v___x_1150_, v___x_1141_);
v___x_1152_ = lean_uint64_sub(v___x_1151_, v___x_1150_);
v_remainder_1153_ = lean_uint64_land(v___y_1104_, v___x_1152_);
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
v___y_408_ = v___y_1105_;
v___y_409_ = v___y_1106_;
v___y_410_ = v___y_1107_;
v___y_411_ = v___x_1160_;
goto v___jp_407_;
}
else
{
v___y_408_ = v___y_1105_;
v___y_409_ = v___y_1106_;
v___y_410_ = v___y_1107_;
v___y_411_ = v_quotient_1149_;
goto v___jp_407_;
}
}
else
{
uint64_t v___x_1161_; 
v___x_1161_ = lean_uint64_add(v_quotient_1149_, v___x_1150_);
v___y_408_ = v___y_1105_;
v___y_409_ = v___y_1106_;
v___y_410_ = v___y_1107_;
v___y_411_ = v___x_1161_;
goto v___jp_407_;
}
}
else
{
v___y_408_ = v___y_1105_;
v___y_409_ = v___y_1106_;
v___y_410_ = v___y_1107_;
v___y_411_ = v_quotient_1149_;
goto v___jp_407_;
}
}
}
else
{
v___y_408_ = v___y_1105_;
v___y_409_ = v___y_1106_;
v___y_410_ = v___y_1107_;
v___y_411_ = v___y_1104_;
goto v___jp_407_;
}
}
}
}
v___jp_1162_:
{
uint64_t v___x_1170_; uint64_t v___x_1171_; uint8_t v___x_1172_; 
v___x_1170_ = 1ULL;
v___x_1171_ = lean_uint64_shift_right(v___y_1168_, v___x_1170_);
v___x_1172_ = lean_uint64_dec_eq(v___x_1171_, v___y_1167_);
if (v___x_1172_ == 0)
{
uint64_t v___x_1173_; 
v___x_1173_ = lean_uint64_add(v___y_1169_, v___x_1170_);
v___y_1103_ = v___y_1163_;
v___y_1104_ = v___y_1164_;
v___y_1105_ = v___y_1165_;
v___y_1106_ = v___y_1166_;
v___y_1107_ = v___y_1167_;
v___y_1108_ = v___x_1173_;
goto v___jp_1102_;
}
else
{
v___y_1103_ = v___y_1163_;
v___y_1104_ = v___y_1164_;
v___y_1105_ = v___y_1165_;
v___y_1106_ = v___y_1166_;
v___y_1107_ = v___y_1167_;
v___y_1108_ = v___y_1169_;
goto v___jp_1102_;
}
}
v___jp_1174_:
{
uint64_t v___x_1184_; uint8_t v___x_1185_; 
v___x_1184_ = lean_uint64_shift_right(v___y_1182_, v___y_1178_);
v___x_1185_ = lean_uint64_dec_eq(v___x_1184_, v___y_1180_);
if (v___x_1185_ == 0)
{
uint64_t v___x_1186_; 
v___x_1186_ = lean_uint64_add(v___y_1179_, v___y_1178_);
v___y_1163_ = v___y_1175_;
v___y_1164_ = v___y_1176_;
v___y_1165_ = v___y_1177_;
v___y_1166_ = v___y_1181_;
v___y_1167_ = v___y_1180_;
v___y_1168_ = v___y_1183_;
v___y_1169_ = v___x_1186_;
goto v___jp_1162_;
}
else
{
v___y_1163_ = v___y_1175_;
v___y_1164_ = v___y_1176_;
v___y_1165_ = v___y_1177_;
v___y_1166_ = v___y_1181_;
v___y_1167_ = v___y_1180_;
v___y_1168_ = v___y_1183_;
v___y_1169_ = v___y_1179_;
goto v___jp_1162_;
}
}
v___jp_1187_:
{
uint64_t v___x_1195_; uint64_t v___x_1196_; uint8_t v___x_1197_; 
v___x_1195_ = 2ULL;
v___x_1196_ = lean_uint64_shift_right(v___y_1193_, v___x_1195_);
v___x_1197_ = lean_uint64_dec_eq(v___x_1196_, v___y_1192_);
if (v___x_1197_ == 0)
{
v___y_1175_ = v___y_1188_;
v___y_1176_ = v___y_1189_;
v___y_1177_ = v___y_1190_;
v___y_1178_ = v___x_1195_;
v___y_1179_ = v___y_1194_;
v___y_1180_ = v___y_1192_;
v___y_1181_ = v___y_1191_;
v___y_1182_ = v___y_1193_;
v___y_1183_ = v___x_1196_;
goto v___jp_1174_;
}
else
{
v___y_1175_ = v___y_1188_;
v___y_1176_ = v___y_1189_;
v___y_1177_ = v___y_1190_;
v___y_1178_ = v___x_1195_;
v___y_1179_ = v___y_1194_;
v___y_1180_ = v___y_1192_;
v___y_1181_ = v___y_1191_;
v___y_1182_ = v___y_1193_;
v___y_1183_ = v___y_1193_;
goto v___jp_1174_;
}
}
v___jp_1198_:
{
uint64_t v___x_1208_; uint8_t v___x_1209_; 
v___x_1208_ = lean_uint64_shift_right(v___y_1206_, v___y_1203_);
v___x_1209_ = lean_uint64_dec_eq(v___x_1208_, v___y_1204_);
if (v___x_1209_ == 0)
{
uint64_t v___x_1210_; 
v___x_1210_ = lean_uint64_add(v___y_1200_, v___y_1203_);
v___y_1188_ = v___y_1199_;
v___y_1189_ = v___y_1201_;
v___y_1190_ = v___y_1202_;
v___y_1191_ = v___y_1205_;
v___y_1192_ = v___y_1204_;
v___y_1193_ = v___y_1207_;
v___y_1194_ = v___x_1210_;
goto v___jp_1187_;
}
else
{
v___y_1188_ = v___y_1199_;
v___y_1189_ = v___y_1201_;
v___y_1190_ = v___y_1202_;
v___y_1191_ = v___y_1205_;
v___y_1192_ = v___y_1204_;
v___y_1193_ = v___y_1207_;
v___y_1194_ = v___y_1200_;
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
v___y_1199_ = v___y_1212_;
v___y_1200_ = v___y_1218_;
v___y_1201_ = v___y_1213_;
v___y_1202_ = v___y_1214_;
v___y_1203_ = v___x_1219_;
v___y_1204_ = v___y_1216_;
v___y_1205_ = v___y_1215_;
v___y_1206_ = v___y_1217_;
v___y_1207_ = v___x_1220_;
goto v___jp_1198_;
}
else
{
v___y_1199_ = v___y_1212_;
v___y_1200_ = v___y_1218_;
v___y_1201_ = v___y_1213_;
v___y_1202_ = v___y_1214_;
v___y_1203_ = v___x_1219_;
v___y_1204_ = v___y_1216_;
v___y_1205_ = v___y_1215_;
v___y_1206_ = v___y_1217_;
v___y_1207_ = v___y_1217_;
goto v___jp_1198_;
}
}
v___jp_1222_:
{
uint64_t v___x_1232_; uint8_t v___x_1233_; 
v___x_1232_ = lean_uint64_shift_right(v___y_1227_, v___y_1224_);
v___x_1233_ = lean_uint64_dec_eq(v___x_1232_, v___y_1229_);
if (v___x_1233_ == 0)
{
uint64_t v___x_1234_; 
v___x_1234_ = lean_uint64_add(v___y_1223_, v___y_1224_);
v___y_1212_ = v___y_1225_;
v___y_1213_ = v___y_1226_;
v___y_1214_ = v___y_1228_;
v___y_1215_ = v___y_1230_;
v___y_1216_ = v___y_1229_;
v___y_1217_ = v___y_1231_;
v___y_1218_ = v___x_1234_;
goto v___jp_1211_;
}
else
{
v___y_1212_ = v___y_1225_;
v___y_1213_ = v___y_1226_;
v___y_1214_ = v___y_1228_;
v___y_1215_ = v___y_1230_;
v___y_1216_ = v___y_1229_;
v___y_1217_ = v___y_1231_;
v___y_1218_ = v___y_1223_;
goto v___jp_1211_;
}
}
v___jp_1235_:
{
uint64_t v___x_1243_; uint64_t v___x_1244_; uint8_t v___x_1245_; 
v___x_1243_ = 8ULL;
v___x_1244_ = lean_uint64_shift_right(v___y_1238_, v___x_1243_);
v___x_1245_ = lean_uint64_dec_eq(v___x_1244_, v___y_1241_);
if (v___x_1245_ == 0)
{
v___y_1223_ = v___y_1242_;
v___y_1224_ = v___x_1243_;
v___y_1225_ = v___y_1236_;
v___y_1226_ = v___y_1237_;
v___y_1227_ = v___y_1238_;
v___y_1228_ = v___y_1239_;
v___y_1229_ = v___y_1241_;
v___y_1230_ = v___y_1240_;
v___y_1231_ = v___x_1244_;
goto v___jp_1222_;
}
else
{
v___y_1223_ = v___y_1242_;
v___y_1224_ = v___x_1243_;
v___y_1225_ = v___y_1236_;
v___y_1226_ = v___y_1237_;
v___y_1227_ = v___y_1238_;
v___y_1228_ = v___y_1239_;
v___y_1229_ = v___y_1241_;
v___y_1230_ = v___y_1240_;
v___y_1231_ = v___y_1238_;
goto v___jp_1222_;
}
}
v___jp_1246_:
{
uint64_t v___x_1256_; uint8_t v___x_1257_; 
v___x_1256_ = lean_uint64_shift_right(v___y_1254_, v___y_1249_);
v___x_1257_ = lean_uint64_dec_eq(v___x_1256_, v___y_1252_);
if (v___x_1257_ == 0)
{
uint64_t v___x_1258_; 
v___x_1258_ = lean_uint64_add(v___y_1247_, v___y_1249_);
v___y_1236_ = v___y_1248_;
v___y_1237_ = v___y_1250_;
v___y_1238_ = v___y_1255_;
v___y_1239_ = v___y_1251_;
v___y_1240_ = v___y_1253_;
v___y_1241_ = v___y_1252_;
v___y_1242_ = v___x_1258_;
goto v___jp_1235_;
}
else
{
v___y_1236_ = v___y_1248_;
v___y_1237_ = v___y_1250_;
v___y_1238_ = v___y_1255_;
v___y_1239_ = v___y_1251_;
v___y_1240_ = v___y_1253_;
v___y_1241_ = v___y_1252_;
v___y_1242_ = v___y_1247_;
goto v___jp_1235_;
}
}
v___jp_1259_:
{
uint64_t v___x_1267_; uint64_t v___x_1268_; uint8_t v___x_1269_; 
v___x_1267_ = 16ULL;
v___x_1268_ = lean_uint64_shift_right(v___y_1265_, v___x_1267_);
v___x_1269_ = lean_uint64_dec_eq(v___x_1268_, v___y_1264_);
if (v___x_1269_ == 0)
{
v___y_1247_ = v___y_1266_;
v___y_1248_ = v___y_1260_;
v___y_1249_ = v___x_1267_;
v___y_1250_ = v___y_1261_;
v___y_1251_ = v___y_1262_;
v___y_1252_ = v___y_1264_;
v___y_1253_ = v___y_1263_;
v___y_1254_ = v___y_1265_;
v___y_1255_ = v___x_1268_;
goto v___jp_1246_;
}
else
{
v___y_1247_ = v___y_1266_;
v___y_1248_ = v___y_1260_;
v___y_1249_ = v___x_1267_;
v___y_1250_ = v___y_1261_;
v___y_1251_ = v___y_1262_;
v___y_1252_ = v___y_1264_;
v___y_1253_ = v___y_1263_;
v___y_1254_ = v___y_1265_;
v___y_1255_ = v___y_1265_;
goto v___jp_1246_;
}
}
v___jp_1270_:
{
uint64_t v___x_1278_; uint8_t v___x_1279_; 
v___x_1278_ = lean_uint64_shift_right(v___y_1272_, v___y_1276_);
v___x_1279_ = lean_uint64_dec_eq(v___x_1278_, v___y_1274_);
if (v___x_1279_ == 0)
{
v___y_1260_ = v___y_1271_;
v___y_1261_ = v___y_1272_;
v___y_1262_ = v___y_1273_;
v___y_1263_ = v___y_1275_;
v___y_1264_ = v___y_1274_;
v___y_1265_ = v___y_1277_;
v___y_1266_ = v___y_1276_;
goto v___jp_1259_;
}
else
{
v___y_1260_ = v___y_1271_;
v___y_1261_ = v___y_1272_;
v___y_1262_ = v___y_1273_;
v___y_1263_ = v___y_1275_;
v___y_1264_ = v___y_1274_;
v___y_1265_ = v___y_1277_;
v___y_1266_ = v___y_1274_;
goto v___jp_1259_;
}
}
v___jp_1280_:
{
uint64_t v___x_1285_; uint8_t v___x_1286_; 
v___x_1285_ = 0ULL;
v___x_1286_ = lean_uint64_dec_eq(v___y_1282_, v___x_1285_);
if (v___x_1286_ == 0)
{
uint64_t v___x_1287_; uint64_t v___x_1288_; uint8_t v___x_1289_; 
v___x_1287_ = 32ULL;
v___x_1288_ = lean_uint64_shift_right(v___y_1282_, v___x_1287_);
v___x_1289_ = lean_uint64_dec_eq(v___x_1288_, v___x_1285_);
if (v___x_1289_ == 0)
{
v___y_1271_ = v___y_1281_;
v___y_1272_ = v___y_1282_;
v___y_1273_ = v___y_1283_;
v___y_1274_ = v___x_1285_;
v___y_1275_ = v___y_1284_;
v___y_1276_ = v___x_1287_;
v___y_1277_ = v___x_1288_;
goto v___jp_1270_;
}
else
{
v___y_1271_ = v___y_1281_;
v___y_1272_ = v___y_1282_;
v___y_1273_ = v___y_1283_;
v___y_1274_ = v___x_1285_;
v___y_1275_ = v___y_1284_;
v___y_1276_ = v___x_1287_;
v___y_1277_ = v___y_1282_;
goto v___jp_1270_;
}
}
else
{
if (v___y_1283_ == 0)
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
v___x_1300_ = lean_uint64_add(v___y_1295_, v___y_1298_);
v___x_1301_ = 281474976710656ULL;
v___x_1302_ = lean_uint64_dec_lt(v___x_1299_, v___x_1301_);
if (v___x_1302_ == 0)
{
v___y_1281_ = v___x_1300_;
v___y_1282_ = v___x_1299_;
v___y_1283_ = v___y_1294_;
v___y_1284_ = v___y_1297_;
goto v___jp_1280_;
}
else
{
uint64_t v___x_1303_; uint8_t v___x_1304_; 
v___x_1303_ = 123ULL;
v___x_1304_ = lean_uint64_dec_le(v___x_1300_, v___x_1303_);
if (v___x_1304_ == 0)
{
v___y_1281_ = v___x_1300_;
v___y_1282_ = v___x_1299_;
v___y_1283_ = v___y_1294_;
v___y_1284_ = v___y_1297_;
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
v___y_429_ = v___y_1294_;
v___y_430_ = v___y_1297_;
v___y_431_ = v___x_1305_;
v___y_432_ = v___x_1305_;
goto v___jp_428_;
}
else
{
uint64_t v___x_1313_; uint8_t v___x_1314_; 
v___x_1313_ = 9223372036854775808ULL;
v___x_1314_ = lean_uint64_dec_lt(v___x_1313_, v___x_1299_);
if (v___x_1314_ == 0)
{
v___y_429_ = v___y_1294_;
v___y_430_ = v___y_1297_;
v___y_431_ = v___x_1305_;
v___y_432_ = v___x_1305_;
goto v___jp_428_;
}
else
{
uint64_t v___x_1315_; 
v___x_1315_ = 1ULL;
v___y_429_ = v___y_1294_;
v___y_430_ = v___y_1297_;
v___y_431_ = v___x_1305_;
v___y_432_ = v___x_1315_;
goto v___jp_428_;
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
v___y_429_ = v___y_1294_;
v___y_430_ = v___y_1297_;
v___y_431_ = v___x_1305_;
v___y_432_ = v___x_1327_;
goto v___jp_428_;
}
else
{
v___y_429_ = v___y_1294_;
v___y_430_ = v___y_1297_;
v___y_431_ = v___x_1305_;
v___y_432_ = v_quotient_1316_;
goto v___jp_428_;
}
}
else
{
uint64_t v___x_1328_; 
v___x_1328_ = lean_uint64_add(v_quotient_1316_, v___x_1317_);
v___y_429_ = v___y_1294_;
v___y_430_ = v___y_1297_;
v___y_431_ = v___x_1305_;
v___y_432_ = v___x_1328_;
goto v___jp_428_;
}
}
else
{
v___y_429_ = v___y_1294_;
v___y_430_ = v___y_1297_;
v___y_431_ = v___x_1305_;
v___y_432_ = v_quotient_1316_;
goto v___jp_428_;
}
}
}
else
{
v___y_429_ = v___y_1294_;
v___y_430_ = v___y_1297_;
v___y_431_ = v___x_1305_;
v___y_432_ = v___x_1299_;
goto v___jp_428_;
}
}
else
{
if (v___y_1294_ == 0)
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
LEAN_EXPORT lean_object* lp_competition_r22CostScaledMul___boxed(lean_object* v_x_1617_, lean_object* v_y_1618_){
_start:
{
uint32_t v_x_boxed_1619_; uint32_t v_y_boxed_1620_; uint32_t v_res_1621_; lean_object* v_r_1622_; 
v_x_boxed_1619_ = lean_unbox_uint32(v_x_1617_);
lean_dec(v_x_1617_);
v_y_boxed_1620_ = lean_unbox_uint32(v_y_1618_);
lean_dec(v_y_1618_);
v_res_1621_ = lp_competition_r22CostScaledMul(v_x_boxed_1619_, v_y_boxed_1620_);
v_r_1622_ = lean_box_uint32(v_res_1621_);
return v_r_1622_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t v___y_1623_, uint32_t v___y_1624_){
_start:
{
uint8_t v___y_1631_; uint8_t v___y_1645_; uint8_t v___y_1659_; uint8_t v___y_1676_; float v___y_1683_; float v___y_1684_; float v___y_1698_; uint8_t v___y_1699_; float v___y_1714_; uint8_t v___y_1724_; uint32_t v___x_1738_; uint32_t v_a_1739_; uint32_t v___x_1740_; uint32_t v___x_1741_; uint32_t v___x_1742_; uint8_t v___x_1743_; 
v___x_1738_ = 2147483647;
v_a_1739_ = lean_uint32_land(v___y_1623_, v___x_1738_);
v___x_1740_ = 201326591;
v___x_1741_ = 1;
v___x_1742_ = lean_uint32_sub(v_a_1739_, v___x_1741_);
v___x_1743_ = lean_uint32_dec_le(v___x_1740_, v___x_1742_);
if (v___x_1743_ == 0)
{
v___y_1724_ = v___x_1743_;
goto v___jp_1723_;
}
else
{
uint32_t v___x_1744_; uint8_t v___x_1745_; 
v___x_1744_ = 2139095040;
v___x_1745_ = lean_uint32_dec_lt(v_a_1739_, v___x_1744_);
v___y_1724_ = v___x_1745_;
goto v___jp_1723_;
}
v___jp_1625_:
{
lean_object* v___x_1626_; lean_object* v___x_1627_; lean_object* v___x_1628_; uint32_t v___x_1629_; 
v___x_1626_ = lean_uint32_to_nat(v___y_1623_);
v___x_1627_ = lean_uint32_to_nat(v___y_1624_);
v___x_1628_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_1626_, v___x_1627_);
v___x_1629_ = lean_uint32_of_nat(v___x_1628_);
lean_dec(v___x_1628_);
return v___x_1629_;
}
v___jp_1630_:
{
if (v___y_1631_ == 0)
{
goto v___jp_1625_;
}
else
{
uint32_t v___x_1632_; uint32_t v___x_1633_; 
v___x_1632_ = 4194304;
v___x_1633_ = lean_uint32_lor(v___y_1624_, v___x_1632_);
return v___x_1633_;
}
}
v___jp_1634_:
{
uint32_t v___x_1635_; uint32_t v___x_1636_; uint32_t v___x_1637_; uint32_t v___x_1638_; uint8_t v___x_1639_; 
v___x_1635_ = 23;
v___x_1636_ = lean_uint32_shift_right(v___y_1624_, v___x_1635_);
v___x_1637_ = 255;
v___x_1638_ = lean_uint32_land(v___x_1636_, v___x_1637_);
v___x_1639_ = lean_uint32_dec_eq(v___x_1638_, v___x_1637_);
if (v___x_1639_ == 0)
{
v___y_1631_ = v___x_1639_;
goto v___jp_1630_;
}
else
{
uint32_t v___x_1640_; uint32_t v___x_1641_; uint32_t v___x_1642_; uint8_t v___x_1643_; 
v___x_1640_ = 8388607;
v___x_1641_ = lean_uint32_land(v___y_1624_, v___x_1640_);
v___x_1642_ = 0;
v___x_1643_ = lean_uint32_dec_eq(v___x_1641_, v___x_1642_);
if (v___x_1643_ == 0)
{
v___y_1631_ = v___x_1639_;
goto v___jp_1630_;
}
else
{
goto v___jp_1625_;
}
}
}
v___jp_1644_:
{
if (v___y_1645_ == 0)
{
goto v___jp_1634_;
}
else
{
uint32_t v___x_1646_; uint32_t v___x_1647_; 
v___x_1646_ = 4194304;
v___x_1647_ = lean_uint32_lor(v___y_1623_, v___x_1646_);
return v___x_1647_;
}
}
v___jp_1648_:
{
uint32_t v___x_1649_; uint32_t v___x_1650_; uint32_t v___x_1651_; uint32_t v___x_1652_; uint8_t v___x_1653_; 
v___x_1649_ = 23;
v___x_1650_ = lean_uint32_shift_right(v___y_1623_, v___x_1649_);
v___x_1651_ = 255;
v___x_1652_ = lean_uint32_land(v___x_1650_, v___x_1651_);
v___x_1653_ = lean_uint32_dec_eq(v___x_1652_, v___x_1651_);
if (v___x_1653_ == 0)
{
v___y_1645_ = v___x_1653_;
goto v___jp_1644_;
}
else
{
uint32_t v___x_1654_; uint32_t v___x_1655_; uint32_t v___x_1656_; uint8_t v___x_1657_; 
v___x_1654_ = 8388607;
v___x_1655_ = lean_uint32_land(v___y_1623_, v___x_1654_);
v___x_1656_ = 0;
v___x_1657_ = lean_uint32_dec_eq(v___x_1655_, v___x_1656_);
if (v___x_1657_ == 0)
{
v___y_1645_ = v___x_1653_;
goto v___jp_1644_;
}
else
{
goto v___jp_1634_;
}
}
}
v___jp_1658_:
{
if (v___y_1659_ == 0)
{
goto v___jp_1648_;
}
else
{
uint32_t v___x_1660_; uint32_t v___x_1661_; uint32_t v___x_1662_; uint8_t v___x_1663_; 
v___x_1660_ = 4194304;
v___x_1661_ = lean_uint32_land(v___y_1624_, v___x_1660_);
v___x_1662_ = 0;
v___x_1663_ = lean_uint32_dec_eq(v___x_1661_, v___x_1662_);
if (v___x_1663_ == 0)
{
goto v___jp_1648_;
}
else
{
uint32_t v___x_1664_; 
v___x_1664_ = lean_uint32_lor(v___y_1624_, v___x_1660_);
return v___x_1664_;
}
}
}
v___jp_1665_:
{
uint32_t v___x_1666_; uint32_t v___x_1667_; uint32_t v___x_1668_; uint32_t v___x_1669_; uint8_t v___x_1670_; 
v___x_1666_ = 23;
v___x_1667_ = lean_uint32_shift_right(v___y_1624_, v___x_1666_);
v___x_1668_ = 255;
v___x_1669_ = lean_uint32_land(v___x_1667_, v___x_1668_);
v___x_1670_ = lean_uint32_dec_eq(v___x_1669_, v___x_1668_);
if (v___x_1670_ == 0)
{
v___y_1659_ = v___x_1670_;
goto v___jp_1658_;
}
else
{
uint32_t v___x_1671_; uint32_t v___x_1672_; uint32_t v___x_1673_; uint8_t v___x_1674_; 
v___x_1671_ = 8388607;
v___x_1672_ = lean_uint32_land(v___y_1624_, v___x_1671_);
v___x_1673_ = 0;
v___x_1674_ = lean_uint32_dec_eq(v___x_1672_, v___x_1673_);
if (v___x_1674_ == 0)
{
v___y_1659_ = v___x_1670_;
goto v___jp_1658_;
}
else
{
goto v___jp_1648_;
}
}
}
v___jp_1675_:
{
if (v___y_1676_ == 0)
{
goto v___jp_1665_;
}
else
{
uint32_t v___x_1677_; uint32_t v___x_1678_; uint32_t v___x_1679_; uint8_t v___x_1680_; 
v___x_1677_ = 4194304;
v___x_1678_ = lean_uint32_land(v___y_1623_, v___x_1677_);
v___x_1679_ = 0;
v___x_1680_ = lean_uint32_dec_eq(v___x_1678_, v___x_1679_);
if (v___x_1680_ == 0)
{
goto v___jp_1665_;
}
else
{
uint32_t v___x_1681_; 
v___x_1681_ = lean_uint32_lor(v___y_1623_, v___x_1677_);
return v___x_1681_;
}
}
}
v___jp_1682_:
{
float v_result_1685_; uint8_t v___x_1686_; 
v_result_1685_ = lean_float32_add(v___y_1683_, v___y_1684_);
v___x_1686_ = lean_float32_beq(v_result_1685_, v_result_1685_);
if (v___x_1686_ == 0)
{
uint32_t v___x_1687_; uint32_t v___x_1688_; uint32_t v___x_1689_; uint32_t v___x_1690_; uint8_t v___x_1691_; 
v___x_1687_ = 23;
v___x_1688_ = lean_uint32_shift_right(v___y_1623_, v___x_1687_);
v___x_1689_ = 255;
v___x_1690_ = lean_uint32_land(v___x_1688_, v___x_1689_);
v___x_1691_ = lean_uint32_dec_eq(v___x_1690_, v___x_1689_);
if (v___x_1691_ == 0)
{
v___y_1676_ = v___x_1691_;
goto v___jp_1675_;
}
else
{
uint32_t v___x_1692_; uint32_t v___x_1693_; uint32_t v___x_1694_; uint8_t v___x_1695_; 
v___x_1692_ = 8388607;
v___x_1693_ = lean_uint32_land(v___y_1623_, v___x_1692_);
v___x_1694_ = 0;
v___x_1695_ = lean_uint32_dec_eq(v___x_1693_, v___x_1694_);
if (v___x_1695_ == 0)
{
v___y_1676_ = v___x_1691_;
goto v___jp_1675_;
}
else
{
goto v___jp_1665_;
}
}
}
else
{
uint32_t v___x_1696_; 
v___x_1696_ = lean_float32_to_bits(v_result_1685_);
return v___x_1696_;
}
}
v___jp_1697_:
{
if (v___y_1699_ == 0)
{
float v___x_1700_; 
v___x_1700_ = lean_float32_of_bits(v___y_1624_);
v___y_1683_ = v___y_1698_;
v___y_1684_ = v___x_1700_;
goto v___jp_1682_;
}
else
{
uint32_t v___x_1701_; uint32_t v___x_1702_; uint32_t v___x_1703_; uint32_t v___x_1704_; float v___x_1705_; lean_object* v___x_1706_; uint32_t v___x_1707_; uint32_t v___x_1708_; lean_object* v___x_1709_; lean_object* v___x_1710_; float v___x_1711_; float v___x_1712_; 
v___x_1701_ = 8388607;
v___x_1702_ = lean_uint32_land(v___y_1624_, v___x_1701_);
v___x_1703_ = 8388608;
v___x_1704_ = lean_uint32_lor(v___x_1702_, v___x_1703_);
v___x_1705_ = lean_uint32_to_float32(v___x_1704_);
v___x_1706_ = lp_competition_R2W01b_scaleTable;
v___x_1707_ = 23;
v___x_1708_ = lean_uint32_shift_right(v___y_1624_, v___x_1707_);
v___x_1709_ = lean_uint32_to_nat(v___x_1708_);
v___x_1710_ = lean_array_fget_borrowed(v___x_1706_, v___x_1709_);
lean_dec(v___x_1709_);
v___x_1711_ = lean_unbox_float32(v___x_1710_);
v___x_1712_ = lean_float32_mul(v___x_1705_, v___x_1711_);
v___y_1683_ = v___y_1698_;
v___y_1684_ = v___x_1712_;
goto v___jp_1682_;
}
}
v___jp_1713_:
{
uint32_t v___x_1715_; uint32_t v_a_1716_; uint32_t v___x_1717_; uint32_t v___x_1718_; uint32_t v___x_1719_; uint8_t v___x_1720_; 
v___x_1715_ = 2147483647;
v_a_1716_ = lean_uint32_land(v___y_1624_, v___x_1715_);
v___x_1717_ = 201326591;
v___x_1718_ = 1;
v___x_1719_ = lean_uint32_sub(v_a_1716_, v___x_1718_);
v___x_1720_ = lean_uint32_dec_le(v___x_1717_, v___x_1719_);
if (v___x_1720_ == 0)
{
v___y_1698_ = v___y_1714_;
v___y_1699_ = v___x_1720_;
goto v___jp_1697_;
}
else
{
uint32_t v___x_1721_; uint8_t v___x_1722_; 
v___x_1721_ = 2139095040;
v___x_1722_ = lean_uint32_dec_lt(v_a_1716_, v___x_1721_);
v___y_1698_ = v___y_1714_;
v___y_1699_ = v___x_1722_;
goto v___jp_1697_;
}
}
v___jp_1723_:
{
if (v___y_1724_ == 0)
{
float v___x_1725_; 
v___x_1725_ = lean_float32_of_bits(v___y_1623_);
v___y_1714_ = v___x_1725_;
goto v___jp_1713_;
}
else
{
uint32_t v___x_1726_; uint32_t v___x_1727_; uint32_t v___x_1728_; uint32_t v___x_1729_; float v___x_1730_; lean_object* v___x_1731_; uint32_t v___x_1732_; uint32_t v___x_1733_; lean_object* v___x_1734_; lean_object* v___x_1735_; float v___x_1736_; float v___x_1737_; 
v___x_1726_ = 8388607;
v___x_1727_ = lean_uint32_land(v___y_1623_, v___x_1726_);
v___x_1728_ = 8388608;
v___x_1729_ = lean_uint32_lor(v___x_1727_, v___x_1728_);
v___x_1730_ = lean_uint32_to_float32(v___x_1729_);
v___x_1731_ = lp_competition_R2W01b_scaleTable;
v___x_1732_ = 23;
v___x_1733_ = lean_uint32_shift_right(v___y_1623_, v___x_1732_);
v___x_1734_ = lean_uint32_to_nat(v___x_1733_);
v___x_1735_ = lean_array_fget_borrowed(v___x_1731_, v___x_1734_);
lean_dec(v___x_1734_);
v___x_1736_ = lean_unbox_float32(v___x_1735_);
v___x_1737_ = lean_float32_mul(v___x_1730_, v___x_1736_);
v___y_1714_ = v___x_1737_;
goto v___jp_1713_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object* v___y_1746_, lean_object* v___y_1747_){
_start:
{
uint32_t v___y_10500__boxed_1748_; uint32_t v___y_10501__boxed_1749_; uint32_t v_res_1750_; lean_object* v_r_1751_; 
v___y_10500__boxed_1748_ = lean_unbox_uint32(v___y_1746_);
lean_dec(v___y_1746_);
v___y_10501__boxed_1749_ = lean_unbox_uint32(v___y_1747_);
lean_dec(v___y_1747_);
v_res_1750_ = lp_competition_main___lam__0(v___y_10500__boxed_1748_, v___y_10501__boxed_1749_);
v_r_1751_ = lean_box_uint32(v_res_1750_);
return v_r_1751_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint8_t v___x_1752_, uint32_t v___y_1753_, uint32_t v___y_1754_){
_start:
{
uint32_t v___y_1756_; uint32_t v___y_1760_; uint32_t v___y_1764_; uint32_t v___y_1765_; uint32_t v___y_1766_; uint64_t v___y_1770_; uint8_t v___y_1771_; uint32_t v___y_1772_; uint64_t v___y_1773_; uint32_t v___y_1785_; uint32_t v___y_1786_; uint32_t v___y_1787_; uint8_t v___y_1791_; uint64_t v___y_1792_; uint32_t v___y_1793_; uint64_t v___y_1794_; uint8_t v___y_1806_; uint8_t v___y_1822_; uint8_t v___y_1836_; uint8_t v___y_1853_; float v___y_1860_; float v___y_1861_; float v___y_1875_; uint8_t v___y_1876_; float v___y_1891_; uint32_t v___y_1901_; uint32_t v___y_1905_; uint32_t v___y_1909_; uint32_t v___y_1910_; uint32_t v___y_1911_; uint8_t v___y_1915_; uint32_t v___y_1916_; uint64_t v___y_1917_; uint64_t v___y_1918_; uint32_t v___y_1930_; uint32_t v___y_1931_; uint32_t v___y_1932_; uint8_t v___y_1936_; uint32_t v___y_1937_; uint64_t v___y_1938_; uint64_t v___y_1939_; uint8_t v___y_1951_; uint8_t v___y_1967_; uint8_t v___y_1981_; uint8_t v___y_1998_; float v___y_2005_; float v___y_2006_; float v___y_2020_; uint8_t v___y_2021_; float v___y_2036_; uint32_t v___y_2046_; uint32_t v___y_2050_; uint32_t v___y_2054_; uint32_t v___y_2055_; uint32_t v___y_2056_; uint32_t v___y_2060_; uint64_t v___y_2061_; uint8_t v___y_2062_; uint64_t v___y_2063_; uint32_t v___y_2075_; uint32_t v___y_2076_; uint32_t v___y_2077_; uint32_t v___y_2081_; uint64_t v___y_2082_; uint8_t v___y_2083_; uint64_t v___y_2084_; uint8_t v___y_2096_; uint8_t v___y_2112_; uint8_t v___y_2126_; uint8_t v___y_2143_; float v___y_2150_; float v___y_2151_; float v___y_2165_; uint8_t v___y_2166_; float v___y_2181_; uint32_t v___x_2190_; uint32_t v___x_2191_; uint8_t v___y_2193_; uint8_t v___y_2206_; uint8_t v___y_2219_; uint32_t v___x_2231_; uint32_t v___y_2233_; uint32_t v___y_2234_; uint32_t v___y_2235_; uint32_t v___y_2236_; uint8_t v___y_2243_; uint32_t v___y_2244_; uint32_t v___y_2245_; uint32_t v___y_2246_; uint64_t v___y_2250_; uint8_t v___y_2251_; uint64_t v___y_2252_; uint32_t v___y_2253_; uint64_t v___y_2254_; uint64_t v___y_2264_; uint8_t v___y_2265_; uint64_t v___y_2266_; uint8_t v___y_2267_; uint32_t v___y_2268_; uint64_t v___y_2269_; uint64_t v___y_2276_; uint8_t v___y_2277_; uint64_t v___y_2278_; uint32_t v___y_2279_; uint64_t v___y_2280_; uint64_t v___y_2286_; uint8_t v___y_2287_; uint64_t v___y_2288_; uint64_t v___y_2289_; uint32_t v___y_2290_; uint64_t v___y_2291_; uint64_t v___y_2346_; uint64_t v___y_2347_; uint8_t v___y_2348_; uint64_t v___y_2349_; uint64_t v___y_2350_; uint32_t v___y_2351_; uint64_t v___y_2352_; uint64_t v___y_2358_; uint64_t v___y_2359_; uint8_t v___y_2360_; uint64_t v___y_2361_; uint64_t v___y_2362_; uint64_t v___y_2363_; uint64_t v___y_2364_; uint32_t v___y_2365_; uint64_t v___y_2366_; uint64_t v___y_2371_; uint8_t v___y_2372_; uint64_t v___y_2373_; uint64_t v___y_2374_; uint64_t v___y_2375_; uint32_t v___y_2376_; uint64_t v___y_2377_; uint64_t v___y_2382_; uint64_t v___y_2383_; uint64_t v___y_2384_; uint8_t v___y_2385_; uint64_t v___y_2386_; uint64_t v___y_2387_; uint64_t v___y_2388_; uint32_t v___y_2389_; uint64_t v___y_2390_; uint64_t v___y_2395_; uint8_t v___y_2396_; uint64_t v___y_2397_; uint64_t v___y_2398_; uint64_t v___y_2399_; uint32_t v___y_2400_; uint64_t v___y_2401_; uint64_t v___y_2406_; uint64_t v___y_2407_; uint8_t v___y_2408_; uint64_t v___y_2409_; uint64_t v___y_2410_; uint64_t v___y_2411_; uint64_t v___y_2412_; uint32_t v___y_2413_; uint64_t v___y_2414_; uint64_t v___y_2419_; uint64_t v___y_2420_; uint8_t v___y_2421_; uint64_t v___y_2422_; uint64_t v___y_2423_; uint32_t v___y_2424_; uint64_t v___y_2425_; uint64_t v___y_2430_; uint64_t v___y_2431_; uint8_t v___y_2432_; uint64_t v___y_2433_; uint64_t v___y_2434_; uint64_t v___y_2435_; uint64_t v___y_2436_; uint32_t v___y_2437_; uint64_t v___y_2438_; uint64_t v___y_2443_; uint8_t v___y_2444_; uint64_t v___y_2445_; uint64_t v___y_2446_; uint64_t v___y_2447_; uint32_t v___y_2448_; uint64_t v___y_2449_; uint64_t v___y_2454_; uint8_t v___y_2455_; uint64_t v___y_2456_; uint64_t v___y_2457_; uint64_t v___y_2458_; uint32_t v___y_2459_; uint64_t v___y_2460_; uint8_t v___y_2464_; uint64_t v___y_2465_; uint64_t v___y_2466_; uint32_t v___y_2467_; uint64_t v___y_2476_; uint8_t v___y_2477_; uint64_t v___y_2478_; uint64_t v___y_2479_; uint32_t v___y_2480_; uint64_t v___y_2481_; uint32_t v___y_2515_; uint32_t v___y_2516_; uint32_t v___y_2517_; uint32_t v___y_2518_; uint32_t v___y_2525_; uint8_t v___y_2526_; uint32_t v___y_2527_; uint32_t v___y_2528_; uint8_t v___y_2532_; uint32_t v___y_2533_; uint64_t v___y_2534_; uint64_t v___y_2535_; uint64_t v___y_2536_; uint8_t v___y_2546_; uint32_t v___y_2547_; uint64_t v___y_2548_; uint8_t v___y_2549_; uint64_t v___y_2550_; uint64_t v___y_2551_; uint8_t v___y_2558_; uint32_t v___y_2559_; uint64_t v___y_2560_; uint64_t v___y_2561_; uint64_t v___y_2562_; uint64_t v___y_2568_; uint8_t v___y_2569_; uint32_t v___y_2570_; uint64_t v___y_2571_; uint64_t v___y_2572_; uint64_t v___y_2573_; uint8_t v___y_2628_; uint64_t v___y_2629_; uint32_t v___y_2630_; uint64_t v___y_2631_; uint64_t v___y_2632_; uint64_t v___y_2633_; uint64_t v___y_2634_; uint64_t v___y_2640_; uint64_t v___y_2641_; uint64_t v___y_2642_; uint8_t v___y_2643_; uint64_t v___y_2644_; uint32_t v___y_2645_; uint64_t v___y_2646_; uint64_t v___y_2647_; uint64_t v___y_2648_; uint64_t v___y_2653_; uint8_t v___y_2654_; uint64_t v___y_2655_; uint32_t v___y_2656_; uint64_t v___y_2657_; uint64_t v___y_2658_; uint64_t v___y_2659_; uint64_t v___y_2664_; uint8_t v___y_2665_; uint64_t v___y_2666_; uint32_t v___y_2667_; uint64_t v___y_2668_; uint64_t v___y_2669_; uint64_t v___y_2670_; uint64_t v___y_2671_; uint64_t v___y_2672_; uint8_t v___y_2677_; uint64_t v___y_2678_; uint32_t v___y_2679_; uint64_t v___y_2680_; uint64_t v___y_2681_; uint64_t v___y_2682_; uint64_t v___y_2683_; uint64_t v___y_2688_; uint8_t v___y_2689_; uint32_t v___y_2690_; uint64_t v___y_2691_; uint64_t v___y_2692_; uint64_t v___y_2693_; uint64_t v___y_2694_; uint64_t v___y_2695_; uint64_t v___y_2696_; uint8_t v___y_2701_; uint64_t v___y_2702_; uint32_t v___y_2703_; uint64_t v___y_2704_; uint64_t v___y_2705_; uint64_t v___y_2706_; uint64_t v___y_2707_; uint64_t v___y_2712_; uint64_t v___y_2713_; uint8_t v___y_2714_; uint64_t v___y_2715_; uint32_t v___y_2716_; uint64_t v___y_2717_; uint64_t v___y_2718_; uint64_t v___y_2719_; uint64_t v___y_2720_; uint8_t v___y_2725_; uint64_t v___y_2726_; uint64_t v___y_2727_; uint32_t v___y_2728_; uint64_t v___y_2729_; uint64_t v___y_2730_; uint64_t v___y_2731_; uint64_t v___y_2736_; uint8_t v___y_2737_; uint32_t v___y_2738_; uint64_t v___y_2739_; uint64_t v___y_2740_; uint64_t v___y_2741_; uint64_t v___y_2742_; uint64_t v___y_2746_; uint8_t v___y_2747_; uint32_t v___y_2748_; uint64_t v___y_2749_; uint8_t v___y_2758_; uint64_t v___y_2759_; uint32_t v___y_2760_; uint64_t v___y_2761_; uint64_t v___y_2762_; uint64_t v___y_2763_; uint32_t v___y_2797_; uint32_t v___y_2798_; uint32_t v___y_2799_; uint32_t v___y_2800_; uint32_t v___y_2807_; uint32_t v___y_2808_; uint8_t v___y_2809_; uint32_t v___y_2810_; uint64_t v___y_2814_; uint32_t v___y_2815_; uint64_t v___y_2816_; uint8_t v___y_2817_; uint64_t v___y_2818_; uint8_t v___y_2828_; uint32_t v___y_2829_; uint64_t v___y_2830_; uint64_t v___y_2831_; uint8_t v___y_2832_; uint64_t v___y_2833_; uint64_t v___y_2840_; uint32_t v___y_2841_; uint64_t v___y_2842_; uint8_t v___y_2843_; uint64_t v___y_2844_; uint64_t v___y_2850_; uint32_t v___y_2851_; uint64_t v___y_2852_; uint64_t v___y_2853_; uint8_t v___y_2854_; uint64_t v___y_2855_; uint64_t v___y_2910_; uint32_t v___y_2911_; uint64_t v___y_2912_; uint64_t v___y_2913_; uint64_t v___y_2914_; uint8_t v___y_2915_; uint64_t v___y_2916_; uint64_t v___y_2922_; uint64_t v___y_2923_; uint64_t v___y_2924_; uint64_t v___y_2925_; uint32_t v___y_2926_; uint64_t v___y_2927_; uint64_t v___y_2928_; uint8_t v___y_2929_; uint64_t v___y_2930_; uint64_t v___y_2935_; uint32_t v___y_2936_; uint64_t v___y_2937_; uint64_t v___y_2938_; uint64_t v___y_2939_; uint8_t v___y_2940_; uint64_t v___y_2941_; uint64_t v___y_2946_; uint64_t v___y_2947_; uint64_t v___y_2948_; uint64_t v___y_2949_; uint32_t v___y_2950_; uint64_t v___y_2951_; uint64_t v___y_2952_; uint8_t v___y_2953_; uint64_t v___y_2954_; uint32_t v___y_2959_; uint64_t v___y_2960_; uint64_t v___y_2961_; uint64_t v___y_2962_; uint64_t v___y_2963_; uint8_t v___y_2964_; uint64_t v___y_2965_; uint64_t v___y_2970_; uint64_t v___y_2971_; uint64_t v___y_2972_; uint64_t v___y_2973_; uint32_t v___y_2974_; uint64_t v___y_2975_; uint64_t v___y_2976_; uint8_t v___y_2977_; uint64_t v___y_2978_; uint64_t v___y_2983_; uint32_t v___y_2984_; uint64_t v___y_2985_; uint64_t v___y_2986_; uint64_t v___y_2987_; uint8_t v___y_2988_; uint64_t v___y_2989_; uint64_t v___y_2994_; uint64_t v___y_2995_; uint64_t v___y_2996_; uint64_t v___y_2997_; uint64_t v___y_2998_; uint32_t v___y_2999_; uint64_t v___y_3000_; uint8_t v___y_3001_; uint64_t v___y_3002_; uint64_t v___y_3007_; uint32_t v___y_3008_; uint64_t v___y_3009_; uint64_t v___y_3010_; uint64_t v___y_3011_; uint8_t v___y_3012_; uint64_t v___y_3013_; uint64_t v___y_3018_; uint64_t v___y_3019_; uint64_t v___y_3020_; uint32_t v___y_3021_; uint64_t v___y_3022_; uint8_t v___y_3023_; uint64_t v___y_3024_; uint64_t v___y_3028_; uint32_t v___y_3029_; uint64_t v___y_3030_; uint8_t v___y_3031_; uint64_t v___y_3040_; uint32_t v___y_3041_; uint64_t v___y_3042_; uint8_t v___y_3043_; uint64_t v___y_3044_; uint64_t v___y_3045_; uint32_t v_eu_3078_; uint32_t v___x_3079_; uint32_t v___x_3080_; uint32_t v___x_3081_; uint8_t v___x_3082_; 
v___x_2190_ = 23;
v___x_2191_ = lean_uint32_shift_right(v___y_1753_, v___x_2190_);
v___x_2231_ = 255;
v_eu_3078_ = lean_uint32_land(v___x_2191_, v___x_2231_);
v___x_3079_ = 1;
v___x_3080_ = lean_uint32_sub(v_eu_3078_, v___x_3079_);
v___x_3081_ = 253;
v___x_3082_ = lean_uint32_dec_le(v___x_3080_, v___x_3081_);
if (v___x_3082_ == 0)
{
uint32_t v___x_3083_; uint32_t v_ey_3084_; uint64_t v___y_3086_; uint32_t v___y_3087_; uint64_t v___y_3088_; uint8_t v___y_3089_; uint64_t v___y_3090_; uint32_t v___y_3097_; uint8_t v___y_3098_; uint64_t v___y_3099_; uint64_t v___y_3100_; uint32_t v___y_3107_; uint32_t v___y_3108_; uint8_t v___y_3109_; uint64_t v___y_3110_; uint8_t v___y_3118_; uint8_t v___y_3129_; uint8_t v___y_3130_; uint8_t v___y_3132_; uint8_t v___y_3133_; uint8_t v___y_3134_; uint8_t v___y_3136_; uint8_t v___y_3137_; uint8_t v___y_3143_; uint32_t v___x_3152_; uint32_t v___x_3153_; uint8_t v___x_3154_; 
v___x_3083_ = lean_uint32_shift_right(v___y_1754_, v___x_2190_);
v_ey_3084_ = lean_uint32_land(v___x_3083_, v___x_2231_);
v___x_3152_ = lean_uint32_add(v_eu_3078_, v_ey_3084_);
v___x_3153_ = 128;
v___x_3154_ = lean_uint32_dec_lt(v___x_3152_, v___x_3153_);
if (v___x_3154_ == 0)
{
uint32_t v___x_3155_; uint32_t v_a_3156_; uint32_t v___x_3157_; uint32_t v___x_3158_; uint8_t v___x_3159_; 
v___x_3155_ = 2147483647;
v_a_3156_ = lean_uint32_land(v___y_1753_, v___x_3155_);
v___x_3157_ = 201326591;
v___x_3158_ = lean_uint32_sub(v_a_3156_, v___x_3079_);
v___x_3159_ = lean_uint32_dec_le(v___x_3157_, v___x_3158_);
if (v___x_3159_ == 0)
{
v___y_2219_ = v___x_3159_;
goto v___jp_2218_;
}
else
{
uint32_t v___x_3160_; uint8_t v___x_3161_; 
v___x_3160_ = 2139095040;
v___x_3161_ = lean_uint32_dec_lt(v_a_3156_, v___x_3160_);
v___y_2219_ = v___x_3161_;
goto v___jp_2218_;
}
}
else
{
uint32_t v___x_3162_; uint32_t v___x_3163_; uint8_t v___x_3164_; 
v___x_3162_ = 4278190080;
v___x_3163_ = lean_uint32_shift_left(v___y_1753_, v___x_3079_);
v___x_3164_ = lean_uint32_dec_le(v___x_3162_, v___x_3163_);
if (v___x_3164_ == 0)
{
uint32_t v___x_3165_; uint8_t v___x_3166_; 
v___x_3165_ = lean_uint32_shift_left(v___y_1754_, v___x_3079_);
v___x_3166_ = lean_uint32_dec_le(v___x_3162_, v___x_3165_);
v___y_3143_ = v___x_3166_;
goto v___jp_3142_;
}
else
{
v___y_3143_ = v___x_3164_;
goto v___jp_3142_;
}
}
v___jp_3085_:
{
uint64_t v___x_3091_; uint64_t v___x_3092_; uint8_t v___x_3093_; 
v___x_3091_ = lean_uint32_to_uint64(v_ey_3084_);
v___x_3092_ = 0ULL;
v___x_3093_ = lean_uint64_dec_eq(v___x_3091_, v___x_3092_);
if (v___x_3093_ == 0)
{
uint64_t v___x_3094_; uint64_t v___x_3095_; 
v___x_3094_ = 1ULL;
v___x_3095_ = lean_uint64_sub(v___x_3091_, v___x_3094_);
v___y_3040_ = v___y_3086_;
v___y_3041_ = v___y_3087_;
v___y_3042_ = v___y_3090_;
v___y_3043_ = v___y_3089_;
v___y_3044_ = v___y_3088_;
v___y_3045_ = v___x_3095_;
goto v___jp_3039_;
}
else
{
v___y_3040_ = v___y_3086_;
v___y_3041_ = v___y_3087_;
v___y_3042_ = v___y_3090_;
v___y_3043_ = v___y_3089_;
v___y_3044_ = v___y_3088_;
v___y_3045_ = v___x_3092_;
goto v___jp_3039_;
}
}
v___jp_3096_:
{
uint64_t v___x_3101_; uint64_t v___x_3102_; uint8_t v___x_3103_; 
v___x_3101_ = lean_uint32_to_uint64(v_eu_3078_);
v___x_3102_ = 0ULL;
v___x_3103_ = lean_uint64_dec_eq(v___x_3101_, v___x_3102_);
if (v___x_3103_ == 0)
{
uint64_t v___x_3104_; uint64_t v___x_3105_; 
v___x_3104_ = 1ULL;
v___x_3105_ = lean_uint64_sub(v___x_3101_, v___x_3104_);
v___y_3086_ = v___y_3100_;
v___y_3087_ = v___y_3097_;
v___y_3088_ = v___y_3099_;
v___y_3089_ = v___y_3098_;
v___y_3090_ = v___x_3105_;
goto v___jp_3085_;
}
else
{
v___y_3086_ = v___y_3100_;
v___y_3087_ = v___y_3097_;
v___y_3088_ = v___y_3099_;
v___y_3089_ = v___y_3098_;
v___y_3090_ = v___x_3102_;
goto v___jp_3085_;
}
}
v___jp_3106_:
{
uint32_t v___x_3111_; uint8_t v___x_3112_; 
v___x_3111_ = 0;
v___x_3112_ = lean_uint32_dec_eq(v_ey_3084_, v___x_3111_);
if (v___x_3112_ == 0)
{
uint64_t v___x_3113_; uint64_t v___x_3114_; uint64_t v___x_3115_; 
v___x_3113_ = lean_uint32_to_uint64(v___y_3107_);
v___x_3114_ = 8388608ULL;
v___x_3115_ = lean_uint64_lor(v___x_3113_, v___x_3114_);
v___y_3097_ = v___y_3108_;
v___y_3098_ = v___y_3109_;
v___y_3099_ = v___y_3110_;
v___y_3100_ = v___x_3115_;
goto v___jp_3096_;
}
else
{
uint64_t v___x_3116_; 
v___x_3116_ = lean_uint32_to_uint64(v___y_3107_);
v___y_3097_ = v___y_3108_;
v___y_3098_ = v___y_3109_;
v___y_3099_ = v___y_3110_;
v___y_3100_ = v___x_3116_;
goto v___jp_3096_;
}
}
v___jp_3117_:
{
uint32_t v___x_3119_; uint32_t v_xFraction_3120_; uint32_t v_yFraction_3121_; uint32_t v___x_3122_; uint8_t v___x_3123_; 
v___x_3119_ = 8388607;
v_xFraction_3120_ = lean_uint32_land(v___y_1753_, v___x_3119_);
v_yFraction_3121_ = lean_uint32_land(v___y_1754_, v___x_3119_);
v___x_3122_ = 0;
v___x_3123_ = lean_uint32_dec_eq(v_eu_3078_, v___x_3122_);
if (v___x_3123_ == 0)
{
uint64_t v___x_3124_; uint64_t v___x_3125_; uint64_t v___x_3126_; 
v___x_3124_ = lean_uint32_to_uint64(v_xFraction_3120_);
v___x_3125_ = 8388608ULL;
v___x_3126_ = lean_uint64_lor(v___x_3124_, v___x_3125_);
v___y_3107_ = v_yFraction_3121_;
v___y_3108_ = v___x_3119_;
v___y_3109_ = v___y_3118_;
v___y_3110_ = v___x_3126_;
goto v___jp_3106_;
}
else
{
uint64_t v___x_3127_; 
v___x_3127_ = lean_uint32_to_uint64(v_xFraction_3120_);
v___y_3107_ = v_yFraction_3121_;
v___y_3108_ = v___x_3119_;
v___y_3109_ = v___y_3118_;
v___y_3110_ = v___x_3127_;
goto v___jp_3106_;
}
}
v___jp_3128_:
{
if (v___y_3130_ == 0)
{
v___y_3118_ = v___x_1752_;
goto v___jp_3117_;
}
else
{
v___y_3118_ = v___y_3129_;
goto v___jp_3117_;
}
}
v___jp_3131_:
{
if (v___y_3133_ == 0)
{
if (v___y_3134_ == 0)
{
v___y_3129_ = v___y_3132_;
v___y_3130_ = v___x_1752_;
goto v___jp_3128_;
}
else
{
v___y_3118_ = v___x_1752_;
goto v___jp_3117_;
}
}
else
{
v___y_3129_ = v___y_3132_;
v___y_3130_ = v___y_3134_;
goto v___jp_3128_;
}
}
v___jp_3135_:
{
uint32_t v___x_3138_; uint32_t v___x_3139_; uint32_t v___x_3140_; uint8_t v___x_3141_; 
v___x_3138_ = 2147483648;
v___x_3139_ = lean_uint32_land(v___y_1754_, v___x_3138_);
v___x_3140_ = 0;
v___x_3141_ = lean_uint32_dec_eq(v___x_3139_, v___x_3140_);
if (v___x_3141_ == 0)
{
v___y_3132_ = v___y_3136_;
v___y_3133_ = v___y_3137_;
v___y_3134_ = v___x_1752_;
goto v___jp_3131_;
}
else
{
v___y_3132_ = v___y_3136_;
v___y_3133_ = v___y_3137_;
v___y_3134_ = v___y_3136_;
goto v___jp_3131_;
}
}
v___jp_3142_:
{
if (v___y_3143_ == 0)
{
uint32_t v___x_3144_; uint32_t v___x_3145_; uint32_t v___x_3146_; uint8_t v___x_3147_; 
v___x_3144_ = 2147483648;
v___x_3145_ = lean_uint32_land(v___y_1753_, v___x_3144_);
v___x_3146_ = 0;
v___x_3147_ = lean_uint32_dec_eq(v___x_3145_, v___x_3146_);
if (v___x_3147_ == 0)
{
v___y_3136_ = v___y_3143_;
v___y_3137_ = v___x_1752_;
goto v___jp_3135_;
}
else
{
v___y_3136_ = v___y_3143_;
v___y_3137_ = v___y_3143_;
goto v___jp_3135_;
}
}
else
{
lean_object* v___x_3148_; lean_object* v___x_3149_; lean_object* v___x_3150_; uint32_t v___x_3151_; 
v___x_3148_ = lean_uint32_to_nat(v___y_1753_);
v___x_3149_ = lean_uint32_to_nat(v___y_1754_);
v___x_3150_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_3148_, v___x_3149_);
v___x_3151_ = lean_uint32_of_nat(v___x_3150_);
lean_dec(v___x_3150_);
return v___x_3151_;
}
}
}
else
{
uint32_t v___x_3167_; uint32_t v_ev_3168_; uint8_t v___y_3170_; uint32_t v___y_3171_; uint64_t v___y_3172_; uint64_t v___y_3173_; uint64_t v___y_3174_; uint8_t v___y_3181_; uint32_t v___y_3182_; uint64_t v___y_3183_; uint64_t v___y_3184_; uint8_t v___y_3191_; uint32_t v___y_3192_; uint32_t v___y_3193_; uint64_t v___y_3194_; uint8_t v___y_3202_; uint8_t v___y_3213_; uint8_t v___y_3214_; uint8_t v___y_3216_; uint8_t v___y_3217_; uint8_t v___y_3218_; uint8_t v___y_3220_; uint8_t v___y_3221_; uint8_t v___y_3227_; uint8_t v___y_3237_; uint64_t v___y_3238_; uint64_t v___y_3239_; uint32_t v___y_3240_; uint64_t v___y_3241_; uint8_t v___y_3248_; uint64_t v___y_3249_; uint32_t v___y_3250_; uint64_t v___y_3251_; uint8_t v___y_3258_; uint32_t v___y_3259_; uint32_t v___y_3260_; uint64_t v___y_3261_; uint8_t v___y_3269_; uint8_t v___y_3280_; uint8_t v___y_3281_; uint32_t v___x_3282_; uint8_t v___x_3283_; uint8_t v___y_3285_; uint8_t v___y_3286_; uint8_t v___y_3287_; uint8_t v___y_3289_; uint8_t v___y_3290_; uint8_t v___y_3296_; 
v___x_3167_ = lean_uint32_shift_right(v___y_1754_, v___x_2190_);
v_ev_3168_ = lean_uint32_land(v___x_3167_, v___x_2231_);
v___x_3282_ = lean_uint32_sub(v_ev_3168_, v___x_3079_);
v___x_3283_ = lean_uint32_dec_le(v___x_3282_, v___x_3081_);
if (v___x_3283_ == 0)
{
uint32_t v___x_3305_; uint32_t v___x_3306_; uint8_t v___x_3307_; 
v___x_3305_ = lean_uint32_add(v_eu_3078_, v_ev_3168_);
v___x_3306_ = 128;
v___x_3307_ = lean_uint32_dec_lt(v___x_3305_, v___x_3306_);
if (v___x_3307_ == 0)
{
uint32_t v___x_3308_; uint32_t v_a_3309_; uint32_t v___x_3310_; uint32_t v___x_3311_; uint8_t v___x_3312_; 
v___x_3308_ = 2147483647;
v_a_3309_ = lean_uint32_land(v___y_1753_, v___x_3308_);
v___x_3310_ = 201326591;
v___x_3311_ = lean_uint32_sub(v_a_3309_, v___x_3079_);
v___x_3312_ = lean_uint32_dec_le(v___x_3310_, v___x_3311_);
if (v___x_3312_ == 0)
{
v___y_2206_ = v___x_3312_;
goto v___jp_2205_;
}
else
{
uint32_t v___x_3313_; uint8_t v___x_3314_; 
v___x_3313_ = 2139095040;
v___x_3314_ = lean_uint32_dec_lt(v_a_3309_, v___x_3313_);
v___y_2206_ = v___x_3314_;
goto v___jp_2205_;
}
}
else
{
uint32_t v___x_3315_; uint32_t v___x_3316_; uint8_t v___x_3317_; 
v___x_3315_ = 4278190080;
v___x_3316_ = lean_uint32_shift_left(v___y_1753_, v___x_3079_);
v___x_3317_ = lean_uint32_dec_le(v___x_3315_, v___x_3316_);
if (v___x_3317_ == 0)
{
uint32_t v___x_3318_; uint8_t v___x_3319_; 
v___x_3318_ = lean_uint32_shift_left(v___y_1754_, v___x_3079_);
v___x_3319_ = lean_uint32_dec_le(v___x_3315_, v___x_3318_);
v___y_3227_ = v___x_3319_;
goto v___jp_3226_;
}
else
{
v___y_3227_ = v___x_3317_;
goto v___jp_3226_;
}
}
}
else
{
uint32_t v_s_3320_; uint32_t v___x_3321_; uint32_t v___x_3322_; uint32_t v___x_3323_; uint8_t v___x_3324_; 
v_s_3320_ = lean_uint32_add(v_eu_3078_, v_ev_3168_);
v___x_3321_ = 128;
v___x_3322_ = lean_uint32_sub(v_s_3320_, v___x_3321_);
v___x_3323_ = 252;
v___x_3324_ = lean_uint32_dec_le(v___x_3322_, v___x_3323_);
if (v___x_3324_ == 0)
{
uint8_t v___x_3325_; 
v___x_3325_ = lean_uint32_dec_lt(v_s_3320_, v___x_3321_);
if (v___x_3325_ == 0)
{
uint32_t v___x_3326_; uint32_t v_a_3327_; uint32_t v___x_3328_; uint32_t v___x_3329_; uint8_t v___x_3330_; 
v___x_3326_ = 2147483647;
v_a_3327_ = lean_uint32_land(v___y_1753_, v___x_3326_);
v___x_3328_ = 201326591;
v___x_3329_ = lean_uint32_sub(v_a_3327_, v___x_3079_);
v___x_3330_ = lean_uint32_dec_le(v___x_3328_, v___x_3329_);
if (v___x_3330_ == 0)
{
v___y_2193_ = v___x_3330_;
goto v___jp_2192_;
}
else
{
uint32_t v___x_3331_; uint8_t v___x_3332_; 
v___x_3331_ = 2139095040;
v___x_3332_ = lean_uint32_dec_lt(v_a_3327_, v___x_3331_);
v___y_2193_ = v___x_3332_;
goto v___jp_2192_;
}
}
else
{
uint32_t v___x_3333_; uint32_t v___x_3334_; uint8_t v___x_3335_; 
v___x_3333_ = 4278190080;
v___x_3334_ = lean_uint32_shift_left(v___y_1753_, v___x_3079_);
v___x_3335_ = lean_uint32_dec_le(v___x_3333_, v___x_3334_);
if (v___x_3335_ == 0)
{
uint32_t v___x_3336_; uint8_t v___x_3337_; 
v___x_3336_ = lean_uint32_shift_left(v___y_1754_, v___x_3079_);
v___x_3337_ = lean_uint32_dec_le(v___x_3333_, v___x_3336_);
v___y_3296_ = v___x_3337_;
goto v___jp_3295_;
}
else
{
v___y_3296_ = v___x_3335_;
goto v___jp_3295_;
}
}
}
else
{
float v_scale_3338_; uint32_t v___x_3339_; uint32_t v___x_3340_; uint32_t v___x_3341_; uint32_t v_a_3342_; uint32_t v___x_3343_; uint32_t v_b_3344_; uint64_t v___x_3345_; uint64_t v___x_3346_; uint64_t v_p_3347_; float v___x_3348_; float v___x_3349_; uint32_t v_z_3350_; uint32_t v___x_3351_; uint32_t v_high_3352_; uint32_t v_q_3353_; uint32_t v___x_3354_; uint32_t v___x_3355_; uint32_t v_e_3356_; uint32_t v___x_3357_; uint32_t v___x_3358_; uint32_t v___x_3359_; uint32_t v___x_3360_; uint32_t v___x_3361_; uint32_t v___x_3362_; uint32_t v___x_3363_; 
v_scale_3338_ = lp_competition_Submission_R21ScaledU32_powNeg23;
v___x_3339_ = 8388607;
v___x_3340_ = lean_uint32_land(v___y_1753_, v___x_3339_);
v___x_3341_ = 8388608;
v_a_3342_ = lean_uint32_lor(v___x_3340_, v___x_3341_);
v___x_3343_ = lean_uint32_land(v___y_1754_, v___x_3339_);
v_b_3344_ = lean_uint32_lor(v___x_3343_, v___x_3341_);
v___x_3345_ = lean_uint32_to_uint64(v_a_3342_);
v___x_3346_ = lean_uint32_to_uint64(v_b_3344_);
v_p_3347_ = lean_uint64_mul(v___x_3345_, v___x_3346_);
v___x_3348_ = lean_uint64_to_float32(v_p_3347_);
v___x_3349_ = lean_float32_mul(v___x_3348_, v_scale_3338_);
v_z_3350_ = lean_float32_to_uint32(v___x_3349_);
v___x_3351_ = 24;
v_high_3352_ = lean_uint32_shift_right(v_z_3350_, v___x_3351_);
v_q_3353_ = lean_uint32_shift_right(v_z_3350_, v_high_3352_);
v___x_3354_ = 127;
v___x_3355_ = lean_uint32_sub(v_s_3320_, v___x_3354_);
v_e_3356_ = lean_uint32_add(v___x_3355_, v_high_3352_);
v___x_3357_ = lean_uint32_xor(v___y_1753_, v___y_1754_);
v___x_3358_ = 2147483648;
v___x_3359_ = lean_uint32_land(v___x_3357_, v___x_3358_);
v___x_3360_ = lean_uint32_shift_left(v_e_3356_, v___x_2190_);
v___x_3361_ = lean_uint32_lor(v___x_3359_, v___x_3360_);
v___x_3362_ = lean_uint32_sub(v_q_3353_, v___x_3341_);
v___x_3363_ = lean_uint32_lor(v___x_3361_, v___x_3362_);
return v___x_3363_;
}
}
v___jp_3169_:
{
uint64_t v___x_3175_; uint64_t v___x_3176_; uint8_t v___x_3177_; 
v___x_3175_ = lean_uint32_to_uint64(v_ev_3168_);
v___x_3176_ = 0ULL;
v___x_3177_ = lean_uint64_dec_eq(v___x_3175_, v___x_3176_);
if (v___x_3177_ == 0)
{
uint64_t v___x_3178_; uint64_t v___x_3179_; 
v___x_3178_ = 1ULL;
v___x_3179_ = lean_uint64_sub(v___x_3175_, v___x_3178_);
v___y_2758_ = v___y_3170_;
v___y_2759_ = v___y_3174_;
v___y_2760_ = v___y_3171_;
v___y_2761_ = v___y_3172_;
v___y_2762_ = v___y_3173_;
v___y_2763_ = v___x_3179_;
goto v___jp_2757_;
}
else
{
v___y_2758_ = v___y_3170_;
v___y_2759_ = v___y_3174_;
v___y_2760_ = v___y_3171_;
v___y_2761_ = v___y_3172_;
v___y_2762_ = v___y_3173_;
v___y_2763_ = v___x_3176_;
goto v___jp_2757_;
}
}
v___jp_3180_:
{
uint64_t v___x_3185_; uint64_t v___x_3186_; uint8_t v___x_3187_; 
v___x_3185_ = lean_uint32_to_uint64(v_eu_3078_);
v___x_3186_ = 0ULL;
v___x_3187_ = lean_uint64_dec_eq(v___x_3185_, v___x_3186_);
if (v___x_3187_ == 0)
{
uint64_t v___x_3188_; uint64_t v___x_3189_; 
v___x_3188_ = 1ULL;
v___x_3189_ = lean_uint64_sub(v___x_3185_, v___x_3188_);
v___y_3170_ = v___y_3181_;
v___y_3171_ = v___y_3182_;
v___y_3172_ = v___y_3183_;
v___y_3173_ = v___y_3184_;
v___y_3174_ = v___x_3189_;
goto v___jp_3169_;
}
else
{
v___y_3170_ = v___y_3181_;
v___y_3171_ = v___y_3182_;
v___y_3172_ = v___y_3183_;
v___y_3173_ = v___y_3184_;
v___y_3174_ = v___x_3186_;
goto v___jp_3169_;
}
}
v___jp_3190_:
{
uint32_t v___x_3195_; uint8_t v___x_3196_; 
v___x_3195_ = 0;
v___x_3196_ = lean_uint32_dec_eq(v_ev_3168_, v___x_3195_);
if (v___x_3196_ == 0)
{
uint64_t v___x_3197_; uint64_t v___x_3198_; uint64_t v___x_3199_; 
v___x_3197_ = lean_uint32_to_uint64(v___y_3193_);
v___x_3198_ = 8388608ULL;
v___x_3199_ = lean_uint64_lor(v___x_3197_, v___x_3198_);
v___y_3181_ = v___y_3191_;
v___y_3182_ = v___y_3192_;
v___y_3183_ = v___y_3194_;
v___y_3184_ = v___x_3199_;
goto v___jp_3180_;
}
else
{
uint64_t v___x_3200_; 
v___x_3200_ = lean_uint32_to_uint64(v___y_3193_);
v___y_3181_ = v___y_3191_;
v___y_3182_ = v___y_3192_;
v___y_3183_ = v___y_3194_;
v___y_3184_ = v___x_3200_;
goto v___jp_3180_;
}
}
v___jp_3201_:
{
uint32_t v___x_3203_; uint32_t v_xFraction_3204_; uint32_t v_yFraction_3205_; uint32_t v___x_3206_; uint8_t v___x_3207_; 
v___x_3203_ = 8388607;
v_xFraction_3204_ = lean_uint32_land(v___y_1753_, v___x_3203_);
v_yFraction_3205_ = lean_uint32_land(v___y_1754_, v___x_3203_);
v___x_3206_ = 0;
v___x_3207_ = lean_uint32_dec_eq(v_eu_3078_, v___x_3206_);
if (v___x_3207_ == 0)
{
uint64_t v___x_3208_; uint64_t v___x_3209_; uint64_t v___x_3210_; 
v___x_3208_ = lean_uint32_to_uint64(v_xFraction_3204_);
v___x_3209_ = 8388608ULL;
v___x_3210_ = lean_uint64_lor(v___x_3208_, v___x_3209_);
v___y_3191_ = v___y_3202_;
v___y_3192_ = v___x_3203_;
v___y_3193_ = v_yFraction_3205_;
v___y_3194_ = v___x_3210_;
goto v___jp_3190_;
}
else
{
uint64_t v___x_3211_; 
v___x_3211_ = lean_uint32_to_uint64(v_xFraction_3204_);
v___y_3191_ = v___y_3202_;
v___y_3192_ = v___x_3203_;
v___y_3193_ = v_yFraction_3205_;
v___y_3194_ = v___x_3211_;
goto v___jp_3190_;
}
}
v___jp_3212_:
{
if (v___y_3214_ == 0)
{
v___y_3202_ = v___x_1752_;
goto v___jp_3201_;
}
else
{
v___y_3202_ = v___y_3213_;
goto v___jp_3201_;
}
}
v___jp_3215_:
{
if (v___y_3216_ == 0)
{
if (v___y_3218_ == 0)
{
v___y_3213_ = v___y_3217_;
v___y_3214_ = v___x_3082_;
goto v___jp_3212_;
}
else
{
v___y_3202_ = v___x_1752_;
goto v___jp_3201_;
}
}
else
{
v___y_3213_ = v___y_3217_;
v___y_3214_ = v___y_3218_;
goto v___jp_3212_;
}
}
v___jp_3219_:
{
uint32_t v___x_3222_; uint32_t v___x_3223_; uint32_t v___x_3224_; uint8_t v___x_3225_; 
v___x_3222_ = 2147483648;
v___x_3223_ = lean_uint32_land(v___y_1754_, v___x_3222_);
v___x_3224_ = 0;
v___x_3225_ = lean_uint32_dec_eq(v___x_3223_, v___x_3224_);
if (v___x_3225_ == 0)
{
v___y_3216_ = v___y_3221_;
v___y_3217_ = v___y_3220_;
v___y_3218_ = v___x_1752_;
goto v___jp_3215_;
}
else
{
v___y_3216_ = v___y_3221_;
v___y_3217_ = v___y_3220_;
v___y_3218_ = v___y_3220_;
goto v___jp_3215_;
}
}
v___jp_3226_:
{
if (v___y_3227_ == 0)
{
uint32_t v___x_3228_; uint32_t v___x_3229_; uint32_t v___x_3230_; uint8_t v___x_3231_; 
v___x_3228_ = 2147483648;
v___x_3229_ = lean_uint32_land(v___y_1753_, v___x_3228_);
v___x_3230_ = 0;
v___x_3231_ = lean_uint32_dec_eq(v___x_3229_, v___x_3230_);
if (v___x_3231_ == 0)
{
v___y_3220_ = v___y_3227_;
v___y_3221_ = v___x_1752_;
goto v___jp_3219_;
}
else
{
v___y_3220_ = v___y_3227_;
v___y_3221_ = v___y_3227_;
goto v___jp_3219_;
}
}
else
{
lean_object* v___x_3232_; lean_object* v___x_3233_; lean_object* v___x_3234_; uint32_t v___x_3235_; 
v___x_3232_ = lean_uint32_to_nat(v___y_1753_);
v___x_3233_ = lean_uint32_to_nat(v___y_1754_);
v___x_3234_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_3232_, v___x_3233_);
v___x_3235_ = lean_uint32_of_nat(v___x_3234_);
lean_dec(v___x_3234_);
return v___x_3235_;
}
}
v___jp_3236_:
{
uint64_t v___x_3242_; uint64_t v___x_3243_; uint8_t v___x_3244_; 
v___x_3242_ = lean_uint32_to_uint64(v_ev_3168_);
v___x_3243_ = 0ULL;
v___x_3244_ = lean_uint64_dec_eq(v___x_3242_, v___x_3243_);
if (v___x_3244_ == 0)
{
uint64_t v___x_3245_; uint64_t v___x_3246_; 
v___x_3245_ = 1ULL;
v___x_3246_ = lean_uint64_sub(v___x_3242_, v___x_3245_);
v___y_2476_ = v___y_3241_;
v___y_2477_ = v___y_3237_;
v___y_2478_ = v___y_3238_;
v___y_2479_ = v___y_3239_;
v___y_2480_ = v___y_3240_;
v___y_2481_ = v___x_3246_;
goto v___jp_2475_;
}
else
{
v___y_2476_ = v___y_3241_;
v___y_2477_ = v___y_3237_;
v___y_2478_ = v___y_3238_;
v___y_2479_ = v___y_3239_;
v___y_2480_ = v___y_3240_;
v___y_2481_ = v___x_3243_;
goto v___jp_2475_;
}
}
v___jp_3247_:
{
uint64_t v___x_3252_; uint64_t v___x_3253_; uint8_t v___x_3254_; 
v___x_3252_ = lean_uint32_to_uint64(v_eu_3078_);
v___x_3253_ = 0ULL;
v___x_3254_ = lean_uint64_dec_eq(v___x_3252_, v___x_3253_);
if (v___x_3254_ == 0)
{
uint64_t v___x_3255_; uint64_t v___x_3256_; 
v___x_3255_ = 1ULL;
v___x_3256_ = lean_uint64_sub(v___x_3252_, v___x_3255_);
v___y_3237_ = v___y_3248_;
v___y_3238_ = v___y_3251_;
v___y_3239_ = v___y_3249_;
v___y_3240_ = v___y_3250_;
v___y_3241_ = v___x_3256_;
goto v___jp_3236_;
}
else
{
v___y_3237_ = v___y_3248_;
v___y_3238_ = v___y_3251_;
v___y_3239_ = v___y_3249_;
v___y_3240_ = v___y_3250_;
v___y_3241_ = v___x_3253_;
goto v___jp_3236_;
}
}
v___jp_3257_:
{
uint32_t v___x_3262_; uint8_t v___x_3263_; 
v___x_3262_ = 0;
v___x_3263_ = lean_uint32_dec_eq(v_ev_3168_, v___x_3262_);
if (v___x_3263_ == 0)
{
uint64_t v___x_3264_; uint64_t v___x_3265_; uint64_t v___x_3266_; 
v___x_3264_ = lean_uint32_to_uint64(v___y_3259_);
v___x_3265_ = 8388608ULL;
v___x_3266_ = lean_uint64_lor(v___x_3264_, v___x_3265_);
v___y_3248_ = v___y_3258_;
v___y_3249_ = v___y_3261_;
v___y_3250_ = v___y_3260_;
v___y_3251_ = v___x_3266_;
goto v___jp_3247_;
}
else
{
uint64_t v___x_3267_; 
v___x_3267_ = lean_uint32_to_uint64(v___y_3259_);
v___y_3248_ = v___y_3258_;
v___y_3249_ = v___y_3261_;
v___y_3250_ = v___y_3260_;
v___y_3251_ = v___x_3267_;
goto v___jp_3247_;
}
}
v___jp_3268_:
{
uint32_t v___x_3270_; uint32_t v_xFraction_3271_; uint32_t v_yFraction_3272_; uint32_t v___x_3273_; uint8_t v___x_3274_; 
v___x_3270_ = 8388607;
v_xFraction_3271_ = lean_uint32_land(v___y_1753_, v___x_3270_);
v_yFraction_3272_ = lean_uint32_land(v___y_1754_, v___x_3270_);
v___x_3273_ = 0;
v___x_3274_ = lean_uint32_dec_eq(v_eu_3078_, v___x_3273_);
if (v___x_3274_ == 0)
{
uint64_t v___x_3275_; uint64_t v___x_3276_; uint64_t v___x_3277_; 
v___x_3275_ = lean_uint32_to_uint64(v_xFraction_3271_);
v___x_3276_ = 8388608ULL;
v___x_3277_ = lean_uint64_lor(v___x_3275_, v___x_3276_);
v___y_3258_ = v___y_3269_;
v___y_3259_ = v_yFraction_3272_;
v___y_3260_ = v___x_3270_;
v___y_3261_ = v___x_3277_;
goto v___jp_3257_;
}
else
{
uint64_t v___x_3278_; 
v___x_3278_ = lean_uint32_to_uint64(v_xFraction_3271_);
v___y_3258_ = v___y_3269_;
v___y_3259_ = v_yFraction_3272_;
v___y_3260_ = v___x_3270_;
v___y_3261_ = v___x_3278_;
goto v___jp_3257_;
}
}
v___jp_3279_:
{
if (v___y_3281_ == 0)
{
v___y_3269_ = v___x_1752_;
goto v___jp_3268_;
}
else
{
v___y_3269_ = v___y_3280_;
goto v___jp_3268_;
}
}
v___jp_3284_:
{
if (v___y_3285_ == 0)
{
if (v___y_3287_ == 0)
{
v___y_3280_ = v___y_3286_;
v___y_3281_ = v___x_3283_;
goto v___jp_3279_;
}
else
{
v___y_3269_ = v___x_1752_;
goto v___jp_3268_;
}
}
else
{
v___y_3280_ = v___y_3286_;
v___y_3281_ = v___y_3287_;
goto v___jp_3279_;
}
}
v___jp_3288_:
{
uint32_t v___x_3291_; uint32_t v___x_3292_; uint32_t v___x_3293_; uint8_t v___x_3294_; 
v___x_3291_ = 2147483648;
v___x_3292_ = lean_uint32_land(v___y_1754_, v___x_3291_);
v___x_3293_ = 0;
v___x_3294_ = lean_uint32_dec_eq(v___x_3292_, v___x_3293_);
if (v___x_3294_ == 0)
{
v___y_3285_ = v___y_3290_;
v___y_3286_ = v___y_3289_;
v___y_3287_ = v___x_1752_;
goto v___jp_3284_;
}
else
{
v___y_3285_ = v___y_3290_;
v___y_3286_ = v___y_3289_;
v___y_3287_ = v___y_3289_;
goto v___jp_3284_;
}
}
v___jp_3295_:
{
if (v___y_3296_ == 0)
{
uint32_t v___x_3297_; uint32_t v___x_3298_; uint32_t v___x_3299_; uint8_t v___x_3300_; 
v___x_3297_ = 2147483648;
v___x_3298_ = lean_uint32_land(v___y_1753_, v___x_3297_);
v___x_3299_ = 0;
v___x_3300_ = lean_uint32_dec_eq(v___x_3298_, v___x_3299_);
if (v___x_3300_ == 0)
{
v___y_3289_ = v___y_3296_;
v___y_3290_ = v___x_1752_;
goto v___jp_3288_;
}
else
{
v___y_3289_ = v___y_3296_;
v___y_3290_ = v___y_3296_;
goto v___jp_3288_;
}
}
else
{
lean_object* v___x_3301_; lean_object* v___x_3302_; lean_object* v___x_3303_; uint32_t v___x_3304_; 
v___x_3301_ = lean_uint32_to_nat(v___y_1753_);
v___x_3302_ = lean_uint32_to_nat(v___y_1754_);
v___x_3303_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_3301_, v___x_3302_);
v___x_3304_ = lean_uint32_of_nat(v___x_3303_);
lean_dec(v___x_3303_);
return v___x_3304_;
}
}
}
v___jp_1755_:
{
uint32_t v___x_1757_; uint32_t v___x_1758_; 
v___x_1757_ = 8388608;
v___x_1758_ = lean_uint32_lor(v___y_1756_, v___x_1757_);
return v___x_1758_;
}
v___jp_1759_:
{
uint32_t v___x_1761_; uint32_t v___x_1762_; 
v___x_1761_ = 8388608;
v___x_1762_ = lean_uint32_lor(v___y_1760_, v___x_1761_);
return v___x_1762_;
}
v___jp_1763_:
{
uint32_t v___x_1767_; uint32_t v___x_1768_; 
v___x_1767_ = lean_uint32_land(v___y_1764_, v___y_1765_);
v___x_1768_ = lean_uint32_lor(v___y_1766_, v___x_1767_);
return v___x_1768_;
}
v___jp_1769_:
{
uint8_t v___x_1774_; 
v___x_1774_ = lean_uint64_dec_eq(v___y_1773_, v___y_1770_);
if (v___x_1774_ == 0)
{
uint64_t v___x_1775_; uint8_t v___x_1776_; 
v___x_1775_ = 8388608ULL;
v___x_1776_ = lean_uint64_dec_eq(v___y_1773_, v___x_1775_);
if (v___x_1776_ == 0)
{
uint32_t v___x_1777_; 
v___x_1777_ = lean_uint64_to_uint32(v___y_1773_);
if (v___y_1771_ == 0)
{
uint32_t v___x_1778_; 
v___x_1778_ = 0;
v___y_1764_ = v___x_1777_;
v___y_1765_ = v___y_1772_;
v___y_1766_ = v___x_1778_;
goto v___jp_1763_;
}
else
{
uint32_t v___x_1779_; 
v___x_1779_ = 2147483648;
v___y_1764_ = v___x_1777_;
v___y_1765_ = v___y_1772_;
v___y_1766_ = v___x_1779_;
goto v___jp_1763_;
}
}
else
{
if (v___y_1771_ == 0)
{
uint32_t v___x_1780_; 
v___x_1780_ = 0;
v___y_1756_ = v___x_1780_;
goto v___jp_1755_;
}
else
{
uint32_t v___x_1781_; 
v___x_1781_ = 2147483648;
v___y_1756_ = v___x_1781_;
goto v___jp_1755_;
}
}
}
else
{
if (v___y_1771_ == 0)
{
uint32_t v___x_1782_; 
v___x_1782_ = 0;
return v___x_1782_;
}
else
{
uint32_t v___x_1783_; 
v___x_1783_ = 2147483648;
return v___x_1783_;
}
}
}
v___jp_1784_:
{
uint32_t v___x_1788_; uint32_t v___x_1789_; 
v___x_1788_ = lean_uint32_land(v___y_1786_, v___y_1785_);
v___x_1789_ = lean_uint32_lor(v___y_1787_, v___x_1788_);
return v___x_1789_;
}
v___jp_1790_:
{
uint8_t v___x_1795_; 
v___x_1795_ = lean_uint64_dec_eq(v___y_1794_, v___y_1792_);
if (v___x_1795_ == 0)
{
uint64_t v___x_1796_; uint8_t v___x_1797_; 
v___x_1796_ = 8388608ULL;
v___x_1797_ = lean_uint64_dec_eq(v___y_1794_, v___x_1796_);
if (v___x_1797_ == 0)
{
uint32_t v___x_1798_; 
v___x_1798_ = lean_uint64_to_uint32(v___y_1794_);
if (v___y_1791_ == 0)
{
uint32_t v___x_1799_; 
v___x_1799_ = 0;
v___y_1785_ = v___y_1793_;
v___y_1786_ = v___x_1798_;
v___y_1787_ = v___x_1799_;
goto v___jp_1784_;
}
else
{
uint32_t v___x_1800_; 
v___x_1800_ = 2147483648;
v___y_1785_ = v___y_1793_;
v___y_1786_ = v___x_1798_;
v___y_1787_ = v___x_1800_;
goto v___jp_1784_;
}
}
else
{
if (v___y_1791_ == 0)
{
uint32_t v___x_1801_; 
v___x_1801_ = 0;
v___y_1760_ = v___x_1801_;
goto v___jp_1759_;
}
else
{
uint32_t v___x_1802_; 
v___x_1802_ = 2147483648;
v___y_1760_ = v___x_1802_;
goto v___jp_1759_;
}
}
}
else
{
if (v___y_1791_ == 0)
{
uint32_t v___x_1803_; 
v___x_1803_ = 0;
return v___x_1803_;
}
else
{
uint32_t v___x_1804_; 
v___x_1804_ = 2147483648;
return v___x_1804_;
}
}
}
v___jp_1805_:
{
if (v___y_1806_ == 0)
{
uint32_t v___x_1807_; 
v___x_1807_ = lp_competition_Submission_FastMul_mul(v___y_1753_, v___y_1754_);
return v___x_1807_;
}
else
{
uint32_t v___x_1808_; uint32_t v___x_1809_; 
v___x_1808_ = 4194304;
v___x_1809_ = lean_uint32_lor(v___y_1754_, v___x_1808_);
return v___x_1809_;
}
}
v___jp_1810_:
{
uint32_t v___x_1811_; uint32_t v___x_1812_; uint32_t v___x_1813_; uint32_t v___x_1814_; uint8_t v___x_1815_; 
v___x_1811_ = 23;
v___x_1812_ = lean_uint32_shift_right(v___y_1754_, v___x_1811_);
v___x_1813_ = 255;
v___x_1814_ = lean_uint32_land(v___x_1812_, v___x_1813_);
v___x_1815_ = lean_uint32_dec_eq(v___x_1814_, v___x_1813_);
if (v___x_1815_ == 0)
{
v___y_1806_ = v___x_1815_;
goto v___jp_1805_;
}
else
{
uint32_t v___x_1816_; uint32_t v___x_1817_; uint32_t v___x_1818_; uint8_t v___x_1819_; 
v___x_1816_ = 8388607;
v___x_1817_ = lean_uint32_land(v___y_1754_, v___x_1816_);
v___x_1818_ = 0;
v___x_1819_ = lean_uint32_dec_eq(v___x_1817_, v___x_1818_);
if (v___x_1819_ == 0)
{
v___y_1806_ = v___x_1815_;
goto v___jp_1805_;
}
else
{
uint32_t v___x_1820_; 
v___x_1820_ = lp_competition_Submission_FastMul_mul(v___y_1753_, v___y_1754_);
return v___x_1820_;
}
}
}
v___jp_1821_:
{
if (v___y_1822_ == 0)
{
goto v___jp_1810_;
}
else
{
uint32_t v___x_1823_; uint32_t v___x_1824_; 
v___x_1823_ = 4194304;
v___x_1824_ = lean_uint32_lor(v___y_1753_, v___x_1823_);
return v___x_1824_;
}
}
v___jp_1825_:
{
uint32_t v___x_1826_; uint32_t v___x_1827_; uint32_t v___x_1828_; uint32_t v___x_1829_; uint8_t v___x_1830_; 
v___x_1826_ = 23;
v___x_1827_ = lean_uint32_shift_right(v___y_1753_, v___x_1826_);
v___x_1828_ = 255;
v___x_1829_ = lean_uint32_land(v___x_1827_, v___x_1828_);
v___x_1830_ = lean_uint32_dec_eq(v___x_1829_, v___x_1828_);
if (v___x_1830_ == 0)
{
v___y_1822_ = v___x_1830_;
goto v___jp_1821_;
}
else
{
uint32_t v___x_1831_; uint32_t v___x_1832_; uint32_t v___x_1833_; uint8_t v___x_1834_; 
v___x_1831_ = 8388607;
v___x_1832_ = lean_uint32_land(v___y_1753_, v___x_1831_);
v___x_1833_ = 0;
v___x_1834_ = lean_uint32_dec_eq(v___x_1832_, v___x_1833_);
if (v___x_1834_ == 0)
{
v___y_1822_ = v___x_1830_;
goto v___jp_1821_;
}
else
{
goto v___jp_1810_;
}
}
}
v___jp_1835_:
{
if (v___y_1836_ == 0)
{
goto v___jp_1825_;
}
else
{
uint32_t v___x_1837_; uint32_t v___x_1838_; uint32_t v___x_1839_; uint8_t v___x_1840_; 
v___x_1837_ = 4194304;
v___x_1838_ = lean_uint32_land(v___y_1754_, v___x_1837_);
v___x_1839_ = 0;
v___x_1840_ = lean_uint32_dec_eq(v___x_1838_, v___x_1839_);
if (v___x_1840_ == 0)
{
goto v___jp_1825_;
}
else
{
uint32_t v___x_1841_; 
v___x_1841_ = lean_uint32_lor(v___y_1754_, v___x_1837_);
return v___x_1841_;
}
}
}
v___jp_1842_:
{
uint32_t v___x_1843_; uint32_t v___x_1844_; uint32_t v___x_1845_; uint32_t v___x_1846_; uint8_t v___x_1847_; 
v___x_1843_ = 23;
v___x_1844_ = lean_uint32_shift_right(v___y_1754_, v___x_1843_);
v___x_1845_ = 255;
v___x_1846_ = lean_uint32_land(v___x_1844_, v___x_1845_);
v___x_1847_ = lean_uint32_dec_eq(v___x_1846_, v___x_1845_);
if (v___x_1847_ == 0)
{
v___y_1836_ = v___x_1847_;
goto v___jp_1835_;
}
else
{
uint32_t v___x_1848_; uint32_t v___x_1849_; uint32_t v___x_1850_; uint8_t v___x_1851_; 
v___x_1848_ = 8388607;
v___x_1849_ = lean_uint32_land(v___y_1754_, v___x_1848_);
v___x_1850_ = 0;
v___x_1851_ = lean_uint32_dec_eq(v___x_1849_, v___x_1850_);
if (v___x_1851_ == 0)
{
v___y_1836_ = v___x_1847_;
goto v___jp_1835_;
}
else
{
goto v___jp_1825_;
}
}
}
v___jp_1852_:
{
if (v___y_1853_ == 0)
{
goto v___jp_1842_;
}
else
{
uint32_t v___x_1854_; uint32_t v___x_1855_; uint32_t v___x_1856_; uint8_t v___x_1857_; 
v___x_1854_ = 4194304;
v___x_1855_ = lean_uint32_land(v___y_1753_, v___x_1854_);
v___x_1856_ = 0;
v___x_1857_ = lean_uint32_dec_eq(v___x_1855_, v___x_1856_);
if (v___x_1857_ == 0)
{
goto v___jp_1842_;
}
else
{
uint32_t v___x_1858_; 
v___x_1858_ = lean_uint32_lor(v___y_1753_, v___x_1854_);
return v___x_1858_;
}
}
}
v___jp_1859_:
{
float v_result_1862_; uint8_t v___x_1863_; 
v_result_1862_ = lean_float32_mul(v___y_1860_, v___y_1861_);
v___x_1863_ = lean_float32_beq(v_result_1862_, v_result_1862_);
if (v___x_1863_ == 0)
{
uint32_t v___x_1864_; uint32_t v___x_1865_; uint32_t v___x_1866_; uint32_t v___x_1867_; uint8_t v___x_1868_; 
v___x_1864_ = 23;
v___x_1865_ = lean_uint32_shift_right(v___y_1753_, v___x_1864_);
v___x_1866_ = 255;
v___x_1867_ = lean_uint32_land(v___x_1865_, v___x_1866_);
v___x_1868_ = lean_uint32_dec_eq(v___x_1867_, v___x_1866_);
if (v___x_1868_ == 0)
{
v___y_1853_ = v___x_1868_;
goto v___jp_1852_;
}
else
{
uint32_t v___x_1869_; uint32_t v___x_1870_; uint32_t v___x_1871_; uint8_t v___x_1872_; 
v___x_1869_ = 8388607;
v___x_1870_ = lean_uint32_land(v___y_1753_, v___x_1869_);
v___x_1871_ = 0;
v___x_1872_ = lean_uint32_dec_eq(v___x_1870_, v___x_1871_);
if (v___x_1872_ == 0)
{
v___y_1853_ = v___x_1868_;
goto v___jp_1852_;
}
else
{
goto v___jp_1842_;
}
}
}
else
{
uint32_t v___x_1873_; 
v___x_1873_ = lean_float32_to_bits(v_result_1862_);
return v___x_1873_;
}
}
v___jp_1874_:
{
if (v___y_1876_ == 0)
{
float v___x_1877_; 
v___x_1877_ = lean_float32_of_bits(v___y_1754_);
v___y_1860_ = v___y_1875_;
v___y_1861_ = v___x_1877_;
goto v___jp_1859_;
}
else
{
uint32_t v___x_1878_; uint32_t v___x_1879_; uint32_t v___x_1880_; uint32_t v___x_1881_; float v___x_1882_; lean_object* v___x_1883_; uint32_t v___x_1884_; uint32_t v___x_1885_; lean_object* v___x_1886_; lean_object* v___x_1887_; float v___x_1888_; float v___x_1889_; 
v___x_1878_ = 8388607;
v___x_1879_ = lean_uint32_land(v___y_1754_, v___x_1878_);
v___x_1880_ = 8388608;
v___x_1881_ = lean_uint32_lor(v___x_1879_, v___x_1880_);
v___x_1882_ = lean_uint32_to_float32(v___x_1881_);
v___x_1883_ = lp_competition_R2W01b_scaleTable;
v___x_1884_ = 23;
v___x_1885_ = lean_uint32_shift_right(v___y_1754_, v___x_1884_);
v___x_1886_ = lean_uint32_to_nat(v___x_1885_);
v___x_1887_ = lean_array_fget_borrowed(v___x_1883_, v___x_1886_);
lean_dec(v___x_1886_);
v___x_1888_ = lean_unbox_float32(v___x_1887_);
v___x_1889_ = lean_float32_mul(v___x_1882_, v___x_1888_);
v___y_1860_ = v___y_1875_;
v___y_1861_ = v___x_1889_;
goto v___jp_1859_;
}
}
v___jp_1890_:
{
uint32_t v___x_1892_; uint32_t v_a_1893_; uint32_t v___x_1894_; uint32_t v___x_1895_; uint32_t v___x_1896_; uint8_t v___x_1897_; 
v___x_1892_ = 2147483647;
v_a_1893_ = lean_uint32_land(v___y_1754_, v___x_1892_);
v___x_1894_ = 201326591;
v___x_1895_ = 1;
v___x_1896_ = lean_uint32_sub(v_a_1893_, v___x_1895_);
v___x_1897_ = lean_uint32_dec_le(v___x_1894_, v___x_1896_);
if (v___x_1897_ == 0)
{
v___y_1875_ = v___y_1891_;
v___y_1876_ = v___x_1897_;
goto v___jp_1874_;
}
else
{
uint32_t v___x_1898_; uint8_t v___x_1899_; 
v___x_1898_ = 2139095040;
v___x_1899_ = lean_uint32_dec_lt(v_a_1893_, v___x_1898_);
v___y_1875_ = v___y_1891_;
v___y_1876_ = v___x_1899_;
goto v___jp_1874_;
}
}
v___jp_1900_:
{
uint32_t v___x_1902_; uint32_t v___x_1903_; 
v___x_1902_ = 8388608;
v___x_1903_ = lean_uint32_lor(v___y_1901_, v___x_1902_);
return v___x_1903_;
}
v___jp_1904_:
{
uint32_t v___x_1906_; uint32_t v___x_1907_; 
v___x_1906_ = 8388608;
v___x_1907_ = lean_uint32_lor(v___y_1905_, v___x_1906_);
return v___x_1907_;
}
v___jp_1908_:
{
uint32_t v___x_1912_; uint32_t v___x_1913_; 
v___x_1912_ = lean_uint32_land(v___y_1909_, v___y_1910_);
v___x_1913_ = lean_uint32_lor(v___y_1911_, v___x_1912_);
return v___x_1913_;
}
v___jp_1914_:
{
uint8_t v___x_1919_; 
v___x_1919_ = lean_uint64_dec_eq(v___y_1918_, v___y_1917_);
if (v___x_1919_ == 0)
{
uint64_t v___x_1920_; uint8_t v___x_1921_; 
v___x_1920_ = 8388608ULL;
v___x_1921_ = lean_uint64_dec_eq(v___y_1918_, v___x_1920_);
if (v___x_1921_ == 0)
{
uint32_t v___x_1922_; 
v___x_1922_ = lean_uint64_to_uint32(v___y_1918_);
if (v___y_1915_ == 0)
{
uint32_t v___x_1923_; 
v___x_1923_ = 0;
v___y_1909_ = v___x_1922_;
v___y_1910_ = v___y_1916_;
v___y_1911_ = v___x_1923_;
goto v___jp_1908_;
}
else
{
uint32_t v___x_1924_; 
v___x_1924_ = 2147483648;
v___y_1909_ = v___x_1922_;
v___y_1910_ = v___y_1916_;
v___y_1911_ = v___x_1924_;
goto v___jp_1908_;
}
}
else
{
if (v___y_1915_ == 0)
{
uint32_t v___x_1925_; 
v___x_1925_ = 0;
v___y_1905_ = v___x_1925_;
goto v___jp_1904_;
}
else
{
uint32_t v___x_1926_; 
v___x_1926_ = 2147483648;
v___y_1905_ = v___x_1926_;
goto v___jp_1904_;
}
}
}
else
{
if (v___y_1915_ == 0)
{
uint32_t v___x_1927_; 
v___x_1927_ = 0;
return v___x_1927_;
}
else
{
uint32_t v___x_1928_; 
v___x_1928_ = 2147483648;
return v___x_1928_;
}
}
}
v___jp_1929_:
{
uint32_t v___x_1933_; uint32_t v___x_1934_; 
v___x_1933_ = lean_uint32_land(v___y_1931_, v___y_1930_);
v___x_1934_ = lean_uint32_lor(v___y_1932_, v___x_1933_);
return v___x_1934_;
}
v___jp_1935_:
{
uint8_t v___x_1940_; 
v___x_1940_ = lean_uint64_dec_eq(v___y_1939_, v___y_1938_);
if (v___x_1940_ == 0)
{
uint64_t v___x_1941_; uint8_t v___x_1942_; 
v___x_1941_ = 8388608ULL;
v___x_1942_ = lean_uint64_dec_eq(v___y_1939_, v___x_1941_);
if (v___x_1942_ == 0)
{
uint32_t v___x_1943_; 
v___x_1943_ = lean_uint64_to_uint32(v___y_1939_);
if (v___y_1936_ == 0)
{
uint32_t v___x_1944_; 
v___x_1944_ = 0;
v___y_1930_ = v___y_1937_;
v___y_1931_ = v___x_1943_;
v___y_1932_ = v___x_1944_;
goto v___jp_1929_;
}
else
{
uint32_t v___x_1945_; 
v___x_1945_ = 2147483648;
v___y_1930_ = v___y_1937_;
v___y_1931_ = v___x_1943_;
v___y_1932_ = v___x_1945_;
goto v___jp_1929_;
}
}
else
{
if (v___y_1936_ == 0)
{
uint32_t v___x_1946_; 
v___x_1946_ = 0;
v___y_1901_ = v___x_1946_;
goto v___jp_1900_;
}
else
{
uint32_t v___x_1947_; 
v___x_1947_ = 2147483648;
v___y_1901_ = v___x_1947_;
goto v___jp_1900_;
}
}
}
else
{
if (v___y_1936_ == 0)
{
uint32_t v___x_1948_; 
v___x_1948_ = 0;
return v___x_1948_;
}
else
{
uint32_t v___x_1949_; 
v___x_1949_ = 2147483648;
return v___x_1949_;
}
}
}
v___jp_1950_:
{
if (v___y_1951_ == 0)
{
uint32_t v___x_1952_; 
v___x_1952_ = lp_competition_Submission_FastMul_mul(v___y_1753_, v___y_1754_);
return v___x_1952_;
}
else
{
uint32_t v___x_1953_; uint32_t v___x_1954_; 
v___x_1953_ = 4194304;
v___x_1954_ = lean_uint32_lor(v___y_1754_, v___x_1953_);
return v___x_1954_;
}
}
v___jp_1955_:
{
uint32_t v___x_1956_; uint32_t v___x_1957_; uint32_t v___x_1958_; uint32_t v___x_1959_; uint8_t v___x_1960_; 
v___x_1956_ = 23;
v___x_1957_ = lean_uint32_shift_right(v___y_1754_, v___x_1956_);
v___x_1958_ = 255;
v___x_1959_ = lean_uint32_land(v___x_1957_, v___x_1958_);
v___x_1960_ = lean_uint32_dec_eq(v___x_1959_, v___x_1958_);
if (v___x_1960_ == 0)
{
v___y_1951_ = v___x_1960_;
goto v___jp_1950_;
}
else
{
uint32_t v___x_1961_; uint32_t v___x_1962_; uint32_t v___x_1963_; uint8_t v___x_1964_; 
v___x_1961_ = 8388607;
v___x_1962_ = lean_uint32_land(v___y_1754_, v___x_1961_);
v___x_1963_ = 0;
v___x_1964_ = lean_uint32_dec_eq(v___x_1962_, v___x_1963_);
if (v___x_1964_ == 0)
{
v___y_1951_ = v___x_1960_;
goto v___jp_1950_;
}
else
{
uint32_t v___x_1965_; 
v___x_1965_ = lp_competition_Submission_FastMul_mul(v___y_1753_, v___y_1754_);
return v___x_1965_;
}
}
}
v___jp_1966_:
{
if (v___y_1967_ == 0)
{
goto v___jp_1955_;
}
else
{
uint32_t v___x_1968_; uint32_t v___x_1969_; 
v___x_1968_ = 4194304;
v___x_1969_ = lean_uint32_lor(v___y_1753_, v___x_1968_);
return v___x_1969_;
}
}
v___jp_1970_:
{
uint32_t v___x_1971_; uint32_t v___x_1972_; uint32_t v___x_1973_; uint32_t v___x_1974_; uint8_t v___x_1975_; 
v___x_1971_ = 23;
v___x_1972_ = lean_uint32_shift_right(v___y_1753_, v___x_1971_);
v___x_1973_ = 255;
v___x_1974_ = lean_uint32_land(v___x_1972_, v___x_1973_);
v___x_1975_ = lean_uint32_dec_eq(v___x_1974_, v___x_1973_);
if (v___x_1975_ == 0)
{
v___y_1967_ = v___x_1975_;
goto v___jp_1966_;
}
else
{
uint32_t v___x_1976_; uint32_t v___x_1977_; uint32_t v___x_1978_; uint8_t v___x_1979_; 
v___x_1976_ = 8388607;
v___x_1977_ = lean_uint32_land(v___y_1753_, v___x_1976_);
v___x_1978_ = 0;
v___x_1979_ = lean_uint32_dec_eq(v___x_1977_, v___x_1978_);
if (v___x_1979_ == 0)
{
v___y_1967_ = v___x_1975_;
goto v___jp_1966_;
}
else
{
goto v___jp_1955_;
}
}
}
v___jp_1980_:
{
if (v___y_1981_ == 0)
{
goto v___jp_1970_;
}
else
{
uint32_t v___x_1982_; uint32_t v___x_1983_; uint32_t v___x_1984_; uint8_t v___x_1985_; 
v___x_1982_ = 4194304;
v___x_1983_ = lean_uint32_land(v___y_1754_, v___x_1982_);
v___x_1984_ = 0;
v___x_1985_ = lean_uint32_dec_eq(v___x_1983_, v___x_1984_);
if (v___x_1985_ == 0)
{
goto v___jp_1970_;
}
else
{
uint32_t v___x_1986_; 
v___x_1986_ = lean_uint32_lor(v___y_1754_, v___x_1982_);
return v___x_1986_;
}
}
}
v___jp_1987_:
{
uint32_t v___x_1988_; uint32_t v___x_1989_; uint32_t v___x_1990_; uint32_t v___x_1991_; uint8_t v___x_1992_; 
v___x_1988_ = 23;
v___x_1989_ = lean_uint32_shift_right(v___y_1754_, v___x_1988_);
v___x_1990_ = 255;
v___x_1991_ = lean_uint32_land(v___x_1989_, v___x_1990_);
v___x_1992_ = lean_uint32_dec_eq(v___x_1991_, v___x_1990_);
if (v___x_1992_ == 0)
{
v___y_1981_ = v___x_1992_;
goto v___jp_1980_;
}
else
{
uint32_t v___x_1993_; uint32_t v___x_1994_; uint32_t v___x_1995_; uint8_t v___x_1996_; 
v___x_1993_ = 8388607;
v___x_1994_ = lean_uint32_land(v___y_1754_, v___x_1993_);
v___x_1995_ = 0;
v___x_1996_ = lean_uint32_dec_eq(v___x_1994_, v___x_1995_);
if (v___x_1996_ == 0)
{
v___y_1981_ = v___x_1992_;
goto v___jp_1980_;
}
else
{
goto v___jp_1970_;
}
}
}
v___jp_1997_:
{
if (v___y_1998_ == 0)
{
goto v___jp_1987_;
}
else
{
uint32_t v___x_1999_; uint32_t v___x_2000_; uint32_t v___x_2001_; uint8_t v___x_2002_; 
v___x_1999_ = 4194304;
v___x_2000_ = lean_uint32_land(v___y_1753_, v___x_1999_);
v___x_2001_ = 0;
v___x_2002_ = lean_uint32_dec_eq(v___x_2000_, v___x_2001_);
if (v___x_2002_ == 0)
{
goto v___jp_1987_;
}
else
{
uint32_t v___x_2003_; 
v___x_2003_ = lean_uint32_lor(v___y_1753_, v___x_1999_);
return v___x_2003_;
}
}
}
v___jp_2004_:
{
float v_result_2007_; uint8_t v___x_2008_; 
v_result_2007_ = lean_float32_mul(v___y_2005_, v___y_2006_);
v___x_2008_ = lean_float32_beq(v_result_2007_, v_result_2007_);
if (v___x_2008_ == 0)
{
uint32_t v___x_2009_; uint32_t v___x_2010_; uint32_t v___x_2011_; uint32_t v___x_2012_; uint8_t v___x_2013_; 
v___x_2009_ = 23;
v___x_2010_ = lean_uint32_shift_right(v___y_1753_, v___x_2009_);
v___x_2011_ = 255;
v___x_2012_ = lean_uint32_land(v___x_2010_, v___x_2011_);
v___x_2013_ = lean_uint32_dec_eq(v___x_2012_, v___x_2011_);
if (v___x_2013_ == 0)
{
v___y_1998_ = v___x_2013_;
goto v___jp_1997_;
}
else
{
uint32_t v___x_2014_; uint32_t v___x_2015_; uint32_t v___x_2016_; uint8_t v___x_2017_; 
v___x_2014_ = 8388607;
v___x_2015_ = lean_uint32_land(v___y_1753_, v___x_2014_);
v___x_2016_ = 0;
v___x_2017_ = lean_uint32_dec_eq(v___x_2015_, v___x_2016_);
if (v___x_2017_ == 0)
{
v___y_1998_ = v___x_2013_;
goto v___jp_1997_;
}
else
{
goto v___jp_1987_;
}
}
}
else
{
uint32_t v___x_2018_; 
v___x_2018_ = lean_float32_to_bits(v_result_2007_);
return v___x_2018_;
}
}
v___jp_2019_:
{
if (v___y_2021_ == 0)
{
float v___x_2022_; 
v___x_2022_ = lean_float32_of_bits(v___y_1754_);
v___y_2005_ = v___y_2020_;
v___y_2006_ = v___x_2022_;
goto v___jp_2004_;
}
else
{
uint32_t v___x_2023_; uint32_t v___x_2024_; uint32_t v___x_2025_; uint32_t v___x_2026_; float v___x_2027_; lean_object* v___x_2028_; uint32_t v___x_2029_; uint32_t v___x_2030_; lean_object* v___x_2031_; lean_object* v___x_2032_; float v___x_2033_; float v___x_2034_; 
v___x_2023_ = 8388607;
v___x_2024_ = lean_uint32_land(v___y_1754_, v___x_2023_);
v___x_2025_ = 8388608;
v___x_2026_ = lean_uint32_lor(v___x_2024_, v___x_2025_);
v___x_2027_ = lean_uint32_to_float32(v___x_2026_);
v___x_2028_ = lp_competition_R2W01b_scaleTable;
v___x_2029_ = 23;
v___x_2030_ = lean_uint32_shift_right(v___y_1754_, v___x_2029_);
v___x_2031_ = lean_uint32_to_nat(v___x_2030_);
v___x_2032_ = lean_array_fget_borrowed(v___x_2028_, v___x_2031_);
lean_dec(v___x_2031_);
v___x_2033_ = lean_unbox_float32(v___x_2032_);
v___x_2034_ = lean_float32_mul(v___x_2027_, v___x_2033_);
v___y_2005_ = v___y_2020_;
v___y_2006_ = v___x_2034_;
goto v___jp_2004_;
}
}
v___jp_2035_:
{
uint32_t v___x_2037_; uint32_t v_a_2038_; uint32_t v___x_2039_; uint32_t v___x_2040_; uint32_t v___x_2041_; uint8_t v___x_2042_; 
v___x_2037_ = 2147483647;
v_a_2038_ = lean_uint32_land(v___y_1754_, v___x_2037_);
v___x_2039_ = 201326591;
v___x_2040_ = 1;
v___x_2041_ = lean_uint32_sub(v_a_2038_, v___x_2040_);
v___x_2042_ = lean_uint32_dec_le(v___x_2039_, v___x_2041_);
if (v___x_2042_ == 0)
{
v___y_2020_ = v___y_2036_;
v___y_2021_ = v___x_2042_;
goto v___jp_2019_;
}
else
{
uint32_t v___x_2043_; uint8_t v___x_2044_; 
v___x_2043_ = 2139095040;
v___x_2044_ = lean_uint32_dec_lt(v_a_2038_, v___x_2043_);
v___y_2020_ = v___y_2036_;
v___y_2021_ = v___x_2044_;
goto v___jp_2019_;
}
}
v___jp_2045_:
{
uint32_t v___x_2047_; uint32_t v___x_2048_; 
v___x_2047_ = 8388608;
v___x_2048_ = lean_uint32_lor(v___y_2046_, v___x_2047_);
return v___x_2048_;
}
v___jp_2049_:
{
uint32_t v___x_2051_; uint32_t v___x_2052_; 
v___x_2051_ = 8388608;
v___x_2052_ = lean_uint32_lor(v___y_2050_, v___x_2051_);
return v___x_2052_;
}
v___jp_2053_:
{
uint32_t v___x_2057_; uint32_t v___x_2058_; 
v___x_2057_ = lean_uint32_land(v___y_2054_, v___y_2055_);
v___x_2058_ = lean_uint32_lor(v___y_2056_, v___x_2057_);
return v___x_2058_;
}
v___jp_2059_:
{
uint8_t v___x_2064_; 
v___x_2064_ = lean_uint64_dec_eq(v___y_2063_, v___y_2061_);
if (v___x_2064_ == 0)
{
uint64_t v___x_2065_; uint8_t v___x_2066_; 
v___x_2065_ = 8388608ULL;
v___x_2066_ = lean_uint64_dec_eq(v___y_2063_, v___x_2065_);
if (v___x_2066_ == 0)
{
uint32_t v___x_2067_; 
v___x_2067_ = lean_uint64_to_uint32(v___y_2063_);
if (v___y_2062_ == 0)
{
uint32_t v___x_2068_; 
v___x_2068_ = 0;
v___y_2054_ = v___x_2067_;
v___y_2055_ = v___y_2060_;
v___y_2056_ = v___x_2068_;
goto v___jp_2053_;
}
else
{
uint32_t v___x_2069_; 
v___x_2069_ = 2147483648;
v___y_2054_ = v___x_2067_;
v___y_2055_ = v___y_2060_;
v___y_2056_ = v___x_2069_;
goto v___jp_2053_;
}
}
else
{
if (v___y_2062_ == 0)
{
uint32_t v___x_2070_; 
v___x_2070_ = 0;
v___y_2046_ = v___x_2070_;
goto v___jp_2045_;
}
else
{
uint32_t v___x_2071_; 
v___x_2071_ = 2147483648;
v___y_2046_ = v___x_2071_;
goto v___jp_2045_;
}
}
}
else
{
if (v___y_2062_ == 0)
{
uint32_t v___x_2072_; 
v___x_2072_ = 0;
return v___x_2072_;
}
else
{
uint32_t v___x_2073_; 
v___x_2073_ = 2147483648;
return v___x_2073_;
}
}
}
v___jp_2074_:
{
uint32_t v___x_2078_; uint32_t v___x_2079_; 
v___x_2078_ = lean_uint32_land(v___y_2076_, v___y_2075_);
v___x_2079_ = lean_uint32_lor(v___y_2077_, v___x_2078_);
return v___x_2079_;
}
v___jp_2080_:
{
uint8_t v___x_2085_; 
v___x_2085_ = lean_uint64_dec_eq(v___y_2084_, v___y_2082_);
if (v___x_2085_ == 0)
{
uint64_t v___x_2086_; uint8_t v___x_2087_; 
v___x_2086_ = 8388608ULL;
v___x_2087_ = lean_uint64_dec_eq(v___y_2084_, v___x_2086_);
if (v___x_2087_ == 0)
{
uint32_t v___x_2088_; 
v___x_2088_ = lean_uint64_to_uint32(v___y_2084_);
if (v___y_2083_ == 0)
{
uint32_t v___x_2089_; 
v___x_2089_ = 0;
v___y_2075_ = v___y_2081_;
v___y_2076_ = v___x_2088_;
v___y_2077_ = v___x_2089_;
goto v___jp_2074_;
}
else
{
uint32_t v___x_2090_; 
v___x_2090_ = 2147483648;
v___y_2075_ = v___y_2081_;
v___y_2076_ = v___x_2088_;
v___y_2077_ = v___x_2090_;
goto v___jp_2074_;
}
}
else
{
if (v___y_2083_ == 0)
{
uint32_t v___x_2091_; 
v___x_2091_ = 0;
v___y_2050_ = v___x_2091_;
goto v___jp_2049_;
}
else
{
uint32_t v___x_2092_; 
v___x_2092_ = 2147483648;
v___y_2050_ = v___x_2092_;
goto v___jp_2049_;
}
}
}
else
{
if (v___y_2083_ == 0)
{
uint32_t v___x_2093_; 
v___x_2093_ = 0;
return v___x_2093_;
}
else
{
uint32_t v___x_2094_; 
v___x_2094_ = 2147483648;
return v___x_2094_;
}
}
}
v___jp_2095_:
{
if (v___y_2096_ == 0)
{
uint32_t v___x_2097_; 
v___x_2097_ = lp_competition_Submission_FastMul_mul(v___y_1753_, v___y_1754_);
return v___x_2097_;
}
else
{
uint32_t v___x_2098_; uint32_t v___x_2099_; 
v___x_2098_ = 4194304;
v___x_2099_ = lean_uint32_lor(v___y_1754_, v___x_2098_);
return v___x_2099_;
}
}
v___jp_2100_:
{
uint32_t v___x_2101_; uint32_t v___x_2102_; uint32_t v___x_2103_; uint32_t v___x_2104_; uint8_t v___x_2105_; 
v___x_2101_ = 23;
v___x_2102_ = lean_uint32_shift_right(v___y_1754_, v___x_2101_);
v___x_2103_ = 255;
v___x_2104_ = lean_uint32_land(v___x_2102_, v___x_2103_);
v___x_2105_ = lean_uint32_dec_eq(v___x_2104_, v___x_2103_);
if (v___x_2105_ == 0)
{
v___y_2096_ = v___x_2105_;
goto v___jp_2095_;
}
else
{
uint32_t v___x_2106_; uint32_t v___x_2107_; uint32_t v___x_2108_; uint8_t v___x_2109_; 
v___x_2106_ = 8388607;
v___x_2107_ = lean_uint32_land(v___y_1754_, v___x_2106_);
v___x_2108_ = 0;
v___x_2109_ = lean_uint32_dec_eq(v___x_2107_, v___x_2108_);
if (v___x_2109_ == 0)
{
v___y_2096_ = v___x_2105_;
goto v___jp_2095_;
}
else
{
uint32_t v___x_2110_; 
v___x_2110_ = lp_competition_Submission_FastMul_mul(v___y_1753_, v___y_1754_);
return v___x_2110_;
}
}
}
v___jp_2111_:
{
if (v___y_2112_ == 0)
{
goto v___jp_2100_;
}
else
{
uint32_t v___x_2113_; uint32_t v___x_2114_; 
v___x_2113_ = 4194304;
v___x_2114_ = lean_uint32_lor(v___y_1753_, v___x_2113_);
return v___x_2114_;
}
}
v___jp_2115_:
{
uint32_t v___x_2116_; uint32_t v___x_2117_; uint32_t v___x_2118_; uint32_t v___x_2119_; uint8_t v___x_2120_; 
v___x_2116_ = 23;
v___x_2117_ = lean_uint32_shift_right(v___y_1753_, v___x_2116_);
v___x_2118_ = 255;
v___x_2119_ = lean_uint32_land(v___x_2117_, v___x_2118_);
v___x_2120_ = lean_uint32_dec_eq(v___x_2119_, v___x_2118_);
if (v___x_2120_ == 0)
{
v___y_2112_ = v___x_2120_;
goto v___jp_2111_;
}
else
{
uint32_t v___x_2121_; uint32_t v___x_2122_; uint32_t v___x_2123_; uint8_t v___x_2124_; 
v___x_2121_ = 8388607;
v___x_2122_ = lean_uint32_land(v___y_1753_, v___x_2121_);
v___x_2123_ = 0;
v___x_2124_ = lean_uint32_dec_eq(v___x_2122_, v___x_2123_);
if (v___x_2124_ == 0)
{
v___y_2112_ = v___x_2120_;
goto v___jp_2111_;
}
else
{
goto v___jp_2100_;
}
}
}
v___jp_2125_:
{
if (v___y_2126_ == 0)
{
goto v___jp_2115_;
}
else
{
uint32_t v___x_2127_; uint32_t v___x_2128_; uint32_t v___x_2129_; uint8_t v___x_2130_; 
v___x_2127_ = 4194304;
v___x_2128_ = lean_uint32_land(v___y_1754_, v___x_2127_);
v___x_2129_ = 0;
v___x_2130_ = lean_uint32_dec_eq(v___x_2128_, v___x_2129_);
if (v___x_2130_ == 0)
{
goto v___jp_2115_;
}
else
{
uint32_t v___x_2131_; 
v___x_2131_ = lean_uint32_lor(v___y_1754_, v___x_2127_);
return v___x_2131_;
}
}
}
v___jp_2132_:
{
uint32_t v___x_2133_; uint32_t v___x_2134_; uint32_t v___x_2135_; uint32_t v___x_2136_; uint8_t v___x_2137_; 
v___x_2133_ = 23;
v___x_2134_ = lean_uint32_shift_right(v___y_1754_, v___x_2133_);
v___x_2135_ = 255;
v___x_2136_ = lean_uint32_land(v___x_2134_, v___x_2135_);
v___x_2137_ = lean_uint32_dec_eq(v___x_2136_, v___x_2135_);
if (v___x_2137_ == 0)
{
v___y_2126_ = v___x_2137_;
goto v___jp_2125_;
}
else
{
uint32_t v___x_2138_; uint32_t v___x_2139_; uint32_t v___x_2140_; uint8_t v___x_2141_; 
v___x_2138_ = 8388607;
v___x_2139_ = lean_uint32_land(v___y_1754_, v___x_2138_);
v___x_2140_ = 0;
v___x_2141_ = lean_uint32_dec_eq(v___x_2139_, v___x_2140_);
if (v___x_2141_ == 0)
{
v___y_2126_ = v___x_2137_;
goto v___jp_2125_;
}
else
{
goto v___jp_2115_;
}
}
}
v___jp_2142_:
{
if (v___y_2143_ == 0)
{
goto v___jp_2132_;
}
else
{
uint32_t v___x_2144_; uint32_t v___x_2145_; uint32_t v___x_2146_; uint8_t v___x_2147_; 
v___x_2144_ = 4194304;
v___x_2145_ = lean_uint32_land(v___y_1753_, v___x_2144_);
v___x_2146_ = 0;
v___x_2147_ = lean_uint32_dec_eq(v___x_2145_, v___x_2146_);
if (v___x_2147_ == 0)
{
goto v___jp_2132_;
}
else
{
uint32_t v___x_2148_; 
v___x_2148_ = lean_uint32_lor(v___y_1753_, v___x_2144_);
return v___x_2148_;
}
}
}
v___jp_2149_:
{
float v_result_2152_; uint8_t v___x_2153_; 
v_result_2152_ = lean_float32_mul(v___y_2150_, v___y_2151_);
v___x_2153_ = lean_float32_beq(v_result_2152_, v_result_2152_);
if (v___x_2153_ == 0)
{
uint32_t v___x_2154_; uint32_t v___x_2155_; uint32_t v___x_2156_; uint32_t v___x_2157_; uint8_t v___x_2158_; 
v___x_2154_ = 23;
v___x_2155_ = lean_uint32_shift_right(v___y_1753_, v___x_2154_);
v___x_2156_ = 255;
v___x_2157_ = lean_uint32_land(v___x_2155_, v___x_2156_);
v___x_2158_ = lean_uint32_dec_eq(v___x_2157_, v___x_2156_);
if (v___x_2158_ == 0)
{
v___y_2143_ = v___x_2158_;
goto v___jp_2142_;
}
else
{
uint32_t v___x_2159_; uint32_t v___x_2160_; uint32_t v___x_2161_; uint8_t v___x_2162_; 
v___x_2159_ = 8388607;
v___x_2160_ = lean_uint32_land(v___y_1753_, v___x_2159_);
v___x_2161_ = 0;
v___x_2162_ = lean_uint32_dec_eq(v___x_2160_, v___x_2161_);
if (v___x_2162_ == 0)
{
v___y_2143_ = v___x_2158_;
goto v___jp_2142_;
}
else
{
goto v___jp_2132_;
}
}
}
else
{
uint32_t v___x_2163_; 
v___x_2163_ = lean_float32_to_bits(v_result_2152_);
return v___x_2163_;
}
}
v___jp_2164_:
{
if (v___y_2166_ == 0)
{
float v___x_2167_; 
v___x_2167_ = lean_float32_of_bits(v___y_1754_);
v___y_2150_ = v___y_2165_;
v___y_2151_ = v___x_2167_;
goto v___jp_2149_;
}
else
{
uint32_t v___x_2168_; uint32_t v___x_2169_; uint32_t v___x_2170_; uint32_t v___x_2171_; float v___x_2172_; lean_object* v___x_2173_; uint32_t v___x_2174_; uint32_t v___x_2175_; lean_object* v___x_2176_; lean_object* v___x_2177_; float v___x_2178_; float v___x_2179_; 
v___x_2168_ = 8388607;
v___x_2169_ = lean_uint32_land(v___y_1754_, v___x_2168_);
v___x_2170_ = 8388608;
v___x_2171_ = lean_uint32_lor(v___x_2169_, v___x_2170_);
v___x_2172_ = lean_uint32_to_float32(v___x_2171_);
v___x_2173_ = lp_competition_R2W01b_scaleTable;
v___x_2174_ = 23;
v___x_2175_ = lean_uint32_shift_right(v___y_1754_, v___x_2174_);
v___x_2176_ = lean_uint32_to_nat(v___x_2175_);
v___x_2177_ = lean_array_fget_borrowed(v___x_2173_, v___x_2176_);
lean_dec(v___x_2176_);
v___x_2178_ = lean_unbox_float32(v___x_2177_);
v___x_2179_ = lean_float32_mul(v___x_2172_, v___x_2178_);
v___y_2150_ = v___y_2165_;
v___y_2151_ = v___x_2179_;
goto v___jp_2149_;
}
}
v___jp_2180_:
{
uint32_t v___x_2182_; uint32_t v_a_2183_; uint32_t v___x_2184_; uint32_t v___x_2185_; uint32_t v___x_2186_; uint8_t v___x_2187_; 
v___x_2182_ = 2147483647;
v_a_2183_ = lean_uint32_land(v___y_1754_, v___x_2182_);
v___x_2184_ = 201326591;
v___x_2185_ = 1;
v___x_2186_ = lean_uint32_sub(v_a_2183_, v___x_2185_);
v___x_2187_ = lean_uint32_dec_le(v___x_2184_, v___x_2186_);
if (v___x_2187_ == 0)
{
v___y_2165_ = v___y_2181_;
v___y_2166_ = v___x_2187_;
goto v___jp_2164_;
}
else
{
uint32_t v___x_2188_; uint8_t v___x_2189_; 
v___x_2188_ = 2139095040;
v___x_2189_ = lean_uint32_dec_lt(v_a_2183_, v___x_2188_);
v___y_2165_ = v___y_2181_;
v___y_2166_ = v___x_2189_;
goto v___jp_2164_;
}
}
v___jp_2192_:
{
if (v___y_2193_ == 0)
{
float v___x_2194_; 
v___x_2194_ = lean_float32_of_bits(v___y_1753_);
v___y_1891_ = v___x_2194_;
goto v___jp_1890_;
}
else
{
uint32_t v___x_2195_; uint32_t v___x_2196_; uint32_t v___x_2197_; uint32_t v___x_2198_; float v___x_2199_; lean_object* v___x_2200_; lean_object* v___x_2201_; lean_object* v___x_2202_; float v___x_2203_; float v___x_2204_; 
v___x_2195_ = 8388607;
v___x_2196_ = lean_uint32_land(v___y_1753_, v___x_2195_);
v___x_2197_ = 8388608;
v___x_2198_ = lean_uint32_lor(v___x_2196_, v___x_2197_);
v___x_2199_ = lean_uint32_to_float32(v___x_2198_);
v___x_2200_ = lp_competition_R2W01b_scaleTable;
v___x_2201_ = lean_uint32_to_nat(v___x_2191_);
v___x_2202_ = lean_array_fget_borrowed(v___x_2200_, v___x_2201_);
lean_dec(v___x_2201_);
v___x_2203_ = lean_unbox_float32(v___x_2202_);
v___x_2204_ = lean_float32_mul(v___x_2199_, v___x_2203_);
v___y_1891_ = v___x_2204_;
goto v___jp_1890_;
}
}
v___jp_2205_:
{
if (v___y_2206_ == 0)
{
float v___x_2207_; 
v___x_2207_ = lean_float32_of_bits(v___y_1753_);
v___y_2036_ = v___x_2207_;
goto v___jp_2035_;
}
else
{
uint32_t v___x_2208_; uint32_t v___x_2209_; uint32_t v___x_2210_; uint32_t v___x_2211_; float v___x_2212_; lean_object* v___x_2213_; lean_object* v___x_2214_; lean_object* v___x_2215_; float v___x_2216_; float v___x_2217_; 
v___x_2208_ = 8388607;
v___x_2209_ = lean_uint32_land(v___y_1753_, v___x_2208_);
v___x_2210_ = 8388608;
v___x_2211_ = lean_uint32_lor(v___x_2209_, v___x_2210_);
v___x_2212_ = lean_uint32_to_float32(v___x_2211_);
v___x_2213_ = lp_competition_R2W01b_scaleTable;
v___x_2214_ = lean_uint32_to_nat(v___x_2191_);
v___x_2215_ = lean_array_fget_borrowed(v___x_2213_, v___x_2214_);
lean_dec(v___x_2214_);
v___x_2216_ = lean_unbox_float32(v___x_2215_);
v___x_2217_ = lean_float32_mul(v___x_2212_, v___x_2216_);
v___y_2036_ = v___x_2217_;
goto v___jp_2035_;
}
}
v___jp_2218_:
{
if (v___y_2219_ == 0)
{
float v___x_2220_; 
v___x_2220_ = lean_float32_of_bits(v___y_1753_);
v___y_2181_ = v___x_2220_;
goto v___jp_2180_;
}
else
{
uint32_t v___x_2221_; uint32_t v___x_2222_; uint32_t v___x_2223_; uint32_t v___x_2224_; float v___x_2225_; lean_object* v___x_2226_; lean_object* v___x_2227_; lean_object* v___x_2228_; float v___x_2229_; float v___x_2230_; 
v___x_2221_ = 8388607;
v___x_2222_ = lean_uint32_land(v___y_1753_, v___x_2221_);
v___x_2223_ = 8388608;
v___x_2224_ = lean_uint32_lor(v___x_2222_, v___x_2223_);
v___x_2225_ = lean_uint32_to_float32(v___x_2224_);
v___x_2226_ = lp_competition_R2W01b_scaleTable;
v___x_2227_ = lean_uint32_to_nat(v___x_2191_);
v___x_2228_ = lean_array_fget_borrowed(v___x_2226_, v___x_2227_);
lean_dec(v___x_2227_);
v___x_2229_ = lean_unbox_float32(v___x_2228_);
v___x_2230_ = lean_float32_mul(v___x_2225_, v___x_2229_);
v___y_2181_ = v___x_2230_;
goto v___jp_2180_;
}
}
v___jp_2232_:
{
uint32_t v___x_2237_; uint32_t v___x_2238_; uint32_t v___x_2239_; uint32_t v___x_2240_; uint32_t v___x_2241_; 
v___x_2237_ = lean_uint32_land(v___y_2233_, v___x_2231_);
v___x_2238_ = lean_uint32_shift_left(v___x_2237_, v___x_2190_);
v___x_2239_ = lean_uint32_lor(v___y_2236_, v___x_2238_);
v___x_2240_ = lean_uint32_land(v___y_2235_, v___y_2234_);
v___x_2241_ = lean_uint32_lor(v___x_2239_, v___x_2240_);
return v___x_2241_;
}
v___jp_2242_:
{
if (v___y_2243_ == 0)
{
uint32_t v___x_2247_; 
v___x_2247_ = 0;
v___y_2233_ = v___y_2244_;
v___y_2234_ = v___y_2245_;
v___y_2235_ = v___y_2246_;
v___y_2236_ = v___x_2247_;
goto v___jp_2232_;
}
else
{
uint32_t v___x_2248_; 
v___x_2248_ = 2147483648;
v___y_2233_ = v___y_2244_;
v___y_2234_ = v___y_2245_;
v___y_2235_ = v___y_2246_;
v___y_2236_ = v___x_2248_;
goto v___jp_2232_;
}
}
v___jp_2249_:
{
uint64_t v___x_2255_; uint64_t v_encodedExponent_2256_; uint32_t v___x_2257_; uint64_t v___x_2258_; uint8_t v___x_2259_; 
v___x_2255_ = 171ULL;
v_encodedExponent_2256_ = lean_uint64_sub(v___y_2252_, v___x_2255_);
v___x_2257_ = lean_uint64_to_uint32(v_encodedExponent_2256_);
v___x_2258_ = 8388608ULL;
v___x_2259_ = lean_uint64_dec_lt(v___y_2254_, v___x_2258_);
if (v___x_2259_ == 0)
{
uint64_t v___x_2260_; uint32_t v___x_2261_; 
v___x_2260_ = lean_uint64_sub(v___y_2254_, v___x_2258_);
v___x_2261_ = lean_uint64_to_uint32(v___x_2260_);
v___y_2243_ = v___y_2251_;
v___y_2244_ = v___x_2257_;
v___y_2245_ = v___y_2253_;
v___y_2246_ = v___x_2261_;
goto v___jp_2242_;
}
else
{
uint32_t v___x_2262_; 
v___x_2262_ = lean_uint64_to_uint32(v___y_2250_);
v___y_2243_ = v___y_2251_;
v___y_2244_ = v___x_2257_;
v___y_2245_ = v___y_2253_;
v___y_2246_ = v___x_2262_;
goto v___jp_2242_;
}
}
v___jp_2263_:
{
uint64_t v___x_2270_; uint8_t v___x_2271_; 
v___x_2270_ = 425ULL;
v___x_2271_ = lean_uint64_dec_lt(v___x_2270_, v___y_2269_);
if (v___x_2271_ == 0)
{
if (v___y_2267_ == 0)
{
v___y_2250_ = v___y_2264_;
v___y_2251_ = v___y_2265_;
v___y_2252_ = v___y_2269_;
v___y_2253_ = v___y_2268_;
v___y_2254_ = v___y_2266_;
goto v___jp_2249_;
}
else
{
uint64_t v___x_2272_; 
v___x_2272_ = 8388608ULL;
v___y_2250_ = v___y_2264_;
v___y_2251_ = v___y_2265_;
v___y_2252_ = v___y_2269_;
v___y_2253_ = v___y_2268_;
v___y_2254_ = v___x_2272_;
goto v___jp_2249_;
}
}
else
{
if (v___y_2265_ == 0)
{
uint32_t v___x_2273_; 
v___x_2273_ = 2139095040;
return v___x_2273_;
}
else
{
uint32_t v___x_2274_; 
v___x_2274_ = 4286578688;
return v___x_2274_;
}
}
}
v___jp_2275_:
{
uint64_t v___x_2281_; uint8_t v_carry_2282_; 
v___x_2281_ = 16777216ULL;
v_carry_2282_ = lean_uint64_dec_eq(v___y_2280_, v___x_2281_);
if (v_carry_2282_ == 0)
{
v___y_2264_ = v___y_2276_;
v___y_2265_ = v___y_2277_;
v___y_2266_ = v___y_2280_;
v___y_2267_ = v_carry_2282_;
v___y_2268_ = v___y_2279_;
v___y_2269_ = v___y_2278_;
goto v___jp_2263_;
}
else
{
uint64_t v___x_2283_; uint64_t v___x_2284_; 
v___x_2283_ = 1ULL;
v___x_2284_ = lean_uint64_add(v___y_2278_, v___x_2283_);
v___y_2264_ = v___y_2276_;
v___y_2265_ = v___y_2277_;
v___y_2266_ = v___y_2280_;
v___y_2267_ = v_carry_2282_;
v___y_2268_ = v___y_2279_;
v___y_2269_ = v___x_2284_;
goto v___jp_2263_;
}
}
v___jp_2285_:
{
uint64_t v_position_2292_; uint64_t v___x_2293_; uint8_t v___x_2294_; 
v_position_2292_ = lean_uint64_add(v___y_2291_, v___y_2289_);
v___x_2293_ = 172ULL;
v___x_2294_ = lean_uint64_dec_lt(v_position_2292_, v___x_2293_);
if (v___x_2294_ == 0)
{
uint64_t v___x_2295_; uint8_t v___x_2296_; 
v___x_2295_ = 23ULL;
v___x_2296_ = lean_uint64_dec_lt(v___y_2291_, v___x_2295_);
if (v___x_2296_ == 0)
{
uint64_t v___x_2297_; uint8_t v___x_2298_; 
v___x_2297_ = lean_uint64_sub(v___y_2291_, v___x_2295_);
v___x_2298_ = lean_uint64_dec_eq(v___x_2297_, v___y_2286_);
if (v___x_2298_ == 0)
{
uint64_t v___x_2299_; uint8_t v___x_2300_; 
v___x_2299_ = 64ULL;
v___x_2300_ = lean_uint64_dec_lt(v___x_2297_, v___x_2299_);
if (v___x_2300_ == 0)
{
uint8_t v___x_2301_; 
v___x_2301_ = lean_uint64_dec_eq(v___x_2297_, v___x_2299_);
if (v___x_2301_ == 0)
{
v___y_2276_ = v___y_2286_;
v___y_2277_ = v___y_2287_;
v___y_2278_ = v_position_2292_;
v___y_2279_ = v___y_2290_;
v___y_2280_ = v___y_2286_;
goto v___jp_2275_;
}
else
{
uint64_t v___x_2302_; uint8_t v___x_2303_; 
v___x_2302_ = 9223372036854775808ULL;
v___x_2303_ = lean_uint64_dec_lt(v___x_2302_, v___y_2288_);
if (v___x_2303_ == 0)
{
v___y_2276_ = v___y_2286_;
v___y_2277_ = v___y_2287_;
v___y_2278_ = v_position_2292_;
v___y_2279_ = v___y_2290_;
v___y_2280_ = v___y_2286_;
goto v___jp_2275_;
}
else
{
uint64_t v___x_2304_; 
v___x_2304_ = 1ULL;
v___y_2276_ = v___y_2286_;
v___y_2277_ = v___y_2287_;
v___y_2278_ = v_position_2292_;
v___y_2279_ = v___y_2290_;
v___y_2280_ = v___x_2304_;
goto v___jp_2275_;
}
}
}
else
{
uint64_t v_quotient_2305_; uint64_t v___x_2306_; uint64_t v___x_2307_; uint64_t v___x_2308_; uint64_t v_remainder_2309_; uint64_t v___x_2310_; uint64_t v_half_2311_; uint8_t v___x_2312_; 
v_quotient_2305_ = lean_uint64_shift_right(v___y_2288_, v___x_2297_);
v___x_2306_ = 1ULL;
v___x_2307_ = lean_uint64_shift_left(v___x_2306_, v___x_2297_);
v___x_2308_ = lean_uint64_sub(v___x_2307_, v___x_2306_);
v_remainder_2309_ = lean_uint64_land(v___y_2288_, v___x_2308_);
v___x_2310_ = lean_uint64_sub(v___x_2297_, v___x_2306_);
v_half_2311_ = lean_uint64_shift_left(v___x_2306_, v___x_2310_);
v___x_2312_ = lean_uint64_dec_lt(v_remainder_2309_, v_half_2311_);
if (v___x_2312_ == 0)
{
uint8_t v___x_2313_; 
v___x_2313_ = lean_uint64_dec_lt(v_half_2311_, v_remainder_2309_);
if (v___x_2313_ == 0)
{
uint64_t v___x_2314_; uint8_t v___x_2315_; 
v___x_2314_ = lean_uint64_land(v_quotient_2305_, v___x_2306_);
v___x_2315_ = lean_uint64_dec_eq(v___x_2314_, v___y_2286_);
if (v___x_2315_ == 0)
{
uint64_t v___x_2316_; 
v___x_2316_ = lean_uint64_add(v_quotient_2305_, v___x_2306_);
v___y_2276_ = v___y_2286_;
v___y_2277_ = v___y_2287_;
v___y_2278_ = v_position_2292_;
v___y_2279_ = v___y_2290_;
v___y_2280_ = v___x_2316_;
goto v___jp_2275_;
}
else
{
v___y_2276_ = v___y_2286_;
v___y_2277_ = v___y_2287_;
v___y_2278_ = v_position_2292_;
v___y_2279_ = v___y_2290_;
v___y_2280_ = v_quotient_2305_;
goto v___jp_2275_;
}
}
else
{
uint64_t v___x_2317_; 
v___x_2317_ = lean_uint64_add(v_quotient_2305_, v___x_2306_);
v___y_2276_ = v___y_2286_;
v___y_2277_ = v___y_2287_;
v___y_2278_ = v_position_2292_;
v___y_2279_ = v___y_2290_;
v___y_2280_ = v___x_2317_;
goto v___jp_2275_;
}
}
else
{
v___y_2276_ = v___y_2286_;
v___y_2277_ = v___y_2287_;
v___y_2278_ = v_position_2292_;
v___y_2279_ = v___y_2290_;
v___y_2280_ = v_quotient_2305_;
goto v___jp_2275_;
}
}
}
else
{
v___y_2276_ = v___y_2286_;
v___y_2277_ = v___y_2287_;
v___y_2278_ = v_position_2292_;
v___y_2279_ = v___y_2290_;
v___y_2280_ = v___y_2288_;
goto v___jp_2275_;
}
}
else
{
uint64_t v___x_2318_; uint64_t v___x_2319_; 
v___x_2318_ = lean_uint64_sub(v___x_2295_, v___y_2291_);
v___x_2319_ = lean_uint64_shift_left(v___y_2288_, v___x_2318_);
v___y_2276_ = v___y_2286_;
v___y_2277_ = v___y_2287_;
v___y_2278_ = v_position_2292_;
v___y_2279_ = v___y_2290_;
v___y_2280_ = v___x_2319_;
goto v___jp_2275_;
}
}
else
{
uint64_t v___x_2320_; uint8_t v___x_2321_; 
v___x_2320_ = 149ULL;
v___x_2321_ = lean_uint64_dec_lt(v___y_2289_, v___x_2320_);
if (v___x_2321_ == 0)
{
uint64_t v___x_2322_; uint64_t v___x_2323_; 
v___x_2322_ = lean_uint64_sub(v___y_2289_, v___x_2320_);
v___x_2323_ = lean_uint64_shift_left(v___y_2288_, v___x_2322_);
v___y_1770_ = v___y_2286_;
v___y_1771_ = v___y_2287_;
v___y_1772_ = v___y_2290_;
v___y_1773_ = v___x_2323_;
goto v___jp_1769_;
}
else
{
uint64_t v___x_2324_; uint8_t v___x_2325_; 
v___x_2324_ = lean_uint64_sub(v___x_2320_, v___y_2289_);
v___x_2325_ = lean_uint64_dec_eq(v___x_2324_, v___y_2286_);
if (v___x_2325_ == 0)
{
uint64_t v___x_2326_; uint8_t v___x_2327_; 
v___x_2326_ = 64ULL;
v___x_2327_ = lean_uint64_dec_lt(v___x_2324_, v___x_2326_);
if (v___x_2327_ == 0)
{
uint8_t v___x_2328_; 
v___x_2328_ = lean_uint64_dec_eq(v___x_2324_, v___x_2326_);
if (v___x_2328_ == 0)
{
v___y_1770_ = v___y_2286_;
v___y_1771_ = v___y_2287_;
v___y_1772_ = v___y_2290_;
v___y_1773_ = v___y_2286_;
goto v___jp_1769_;
}
else
{
uint64_t v___x_2329_; uint8_t v___x_2330_; 
v___x_2329_ = 9223372036854775808ULL;
v___x_2330_ = lean_uint64_dec_lt(v___x_2329_, v___y_2288_);
if (v___x_2330_ == 0)
{
v___y_1770_ = v___y_2286_;
v___y_1771_ = v___y_2287_;
v___y_1772_ = v___y_2290_;
v___y_1773_ = v___y_2286_;
goto v___jp_1769_;
}
else
{
uint64_t v___x_2331_; 
v___x_2331_ = 1ULL;
v___y_1770_ = v___y_2286_;
v___y_1771_ = v___y_2287_;
v___y_1772_ = v___y_2290_;
v___y_1773_ = v___x_2331_;
goto v___jp_1769_;
}
}
}
else
{
uint64_t v_quotient_2332_; uint64_t v___x_2333_; uint64_t v___x_2334_; uint64_t v___x_2335_; uint64_t v_remainder_2336_; uint64_t v___x_2337_; uint64_t v_half_2338_; uint8_t v___x_2339_; 
v_quotient_2332_ = lean_uint64_shift_right(v___y_2288_, v___x_2324_);
v___x_2333_ = 1ULL;
v___x_2334_ = lean_uint64_shift_left(v___x_2333_, v___x_2324_);
v___x_2335_ = lean_uint64_sub(v___x_2334_, v___x_2333_);
v_remainder_2336_ = lean_uint64_land(v___y_2288_, v___x_2335_);
v___x_2337_ = lean_uint64_sub(v___x_2324_, v___x_2333_);
v_half_2338_ = lean_uint64_shift_left(v___x_2333_, v___x_2337_);
v___x_2339_ = lean_uint64_dec_lt(v_remainder_2336_, v_half_2338_);
if (v___x_2339_ == 0)
{
uint8_t v___x_2340_; 
v___x_2340_ = lean_uint64_dec_lt(v_half_2338_, v_remainder_2336_);
if (v___x_2340_ == 0)
{
uint64_t v___x_2341_; uint8_t v___x_2342_; 
v___x_2341_ = lean_uint64_land(v_quotient_2332_, v___x_2333_);
v___x_2342_ = lean_uint64_dec_eq(v___x_2341_, v___y_2286_);
if (v___x_2342_ == 0)
{
uint64_t v___x_2343_; 
v___x_2343_ = lean_uint64_add(v_quotient_2332_, v___x_2333_);
v___y_1770_ = v___y_2286_;
v___y_1771_ = v___y_2287_;
v___y_1772_ = v___y_2290_;
v___y_1773_ = v___x_2343_;
goto v___jp_1769_;
}
else
{
v___y_1770_ = v___y_2286_;
v___y_1771_ = v___y_2287_;
v___y_1772_ = v___y_2290_;
v___y_1773_ = v_quotient_2332_;
goto v___jp_1769_;
}
}
else
{
uint64_t v___x_2344_; 
v___x_2344_ = lean_uint64_add(v_quotient_2332_, v___x_2333_);
v___y_1770_ = v___y_2286_;
v___y_1771_ = v___y_2287_;
v___y_1772_ = v___y_2290_;
v___y_1773_ = v___x_2344_;
goto v___jp_1769_;
}
}
else
{
v___y_1770_ = v___y_2286_;
v___y_1771_ = v___y_2287_;
v___y_1772_ = v___y_2290_;
v___y_1773_ = v_quotient_2332_;
goto v___jp_1769_;
}
}
}
else
{
v___y_1770_ = v___y_2286_;
v___y_1771_ = v___y_2287_;
v___y_1772_ = v___y_2290_;
v___y_1773_ = v___y_2288_;
goto v___jp_1769_;
}
}
}
}
v___jp_2345_:
{
uint64_t v___x_2353_; uint64_t v___x_2354_; uint8_t v___x_2355_; 
v___x_2353_ = 1ULL;
v___x_2354_ = lean_uint64_shift_right(v___y_2346_, v___x_2353_);
v___x_2355_ = lean_uint64_dec_eq(v___x_2354_, v___y_2347_);
if (v___x_2355_ == 0)
{
uint64_t v___x_2356_; 
v___x_2356_ = lean_uint64_add(v___y_2352_, v___x_2353_);
v___y_2286_ = v___y_2347_;
v___y_2287_ = v___y_2348_;
v___y_2288_ = v___y_2350_;
v___y_2289_ = v___y_2349_;
v___y_2290_ = v___y_2351_;
v___y_2291_ = v___x_2356_;
goto v___jp_2285_;
}
else
{
v___y_2286_ = v___y_2347_;
v___y_2287_ = v___y_2348_;
v___y_2288_ = v___y_2350_;
v___y_2289_ = v___y_2349_;
v___y_2290_ = v___y_2351_;
v___y_2291_ = v___y_2352_;
goto v___jp_2285_;
}
}
v___jp_2357_:
{
uint64_t v___x_2367_; uint8_t v___x_2368_; 
v___x_2367_ = lean_uint64_shift_right(v___y_2362_, v___y_2358_);
v___x_2368_ = lean_uint64_dec_eq(v___x_2367_, v___y_2359_);
if (v___x_2368_ == 0)
{
uint64_t v___x_2369_; 
v___x_2369_ = lean_uint64_add(v___y_2361_, v___y_2358_);
v___y_2346_ = v___y_2366_;
v___y_2347_ = v___y_2359_;
v___y_2348_ = v___y_2360_;
v___y_2349_ = v___y_2364_;
v___y_2350_ = v___y_2363_;
v___y_2351_ = v___y_2365_;
v___y_2352_ = v___x_2369_;
goto v___jp_2345_;
}
else
{
v___y_2346_ = v___y_2366_;
v___y_2347_ = v___y_2359_;
v___y_2348_ = v___y_2360_;
v___y_2349_ = v___y_2364_;
v___y_2350_ = v___y_2363_;
v___y_2351_ = v___y_2365_;
v___y_2352_ = v___y_2361_;
goto v___jp_2345_;
}
}
v___jp_2370_:
{
uint64_t v___x_2378_; uint64_t v___x_2379_; uint8_t v___x_2380_; 
v___x_2378_ = 2ULL;
v___x_2379_ = lean_uint64_shift_right(v___y_2373_, v___x_2378_);
v___x_2380_ = lean_uint64_dec_eq(v___x_2379_, v___y_2371_);
if (v___x_2380_ == 0)
{
v___y_2358_ = v___x_2378_;
v___y_2359_ = v___y_2371_;
v___y_2360_ = v___y_2372_;
v___y_2361_ = v___y_2377_;
v___y_2362_ = v___y_2373_;
v___y_2363_ = v___y_2375_;
v___y_2364_ = v___y_2374_;
v___y_2365_ = v___y_2376_;
v___y_2366_ = v___x_2379_;
goto v___jp_2357_;
}
else
{
v___y_2358_ = v___x_2378_;
v___y_2359_ = v___y_2371_;
v___y_2360_ = v___y_2372_;
v___y_2361_ = v___y_2377_;
v___y_2362_ = v___y_2373_;
v___y_2363_ = v___y_2375_;
v___y_2364_ = v___y_2374_;
v___y_2365_ = v___y_2376_;
v___y_2366_ = v___y_2373_;
goto v___jp_2357_;
}
}
v___jp_2381_:
{
uint64_t v___x_2391_; uint8_t v___x_2392_; 
v___x_2391_ = lean_uint64_shift_right(v___y_2386_, v___y_2382_);
v___x_2392_ = lean_uint64_dec_eq(v___x_2391_, v___y_2384_);
if (v___x_2392_ == 0)
{
uint64_t v___x_2393_; 
v___x_2393_ = lean_uint64_add(v___y_2383_, v___y_2382_);
v___y_2371_ = v___y_2384_;
v___y_2372_ = v___y_2385_;
v___y_2373_ = v___y_2390_;
v___y_2374_ = v___y_2388_;
v___y_2375_ = v___y_2387_;
v___y_2376_ = v___y_2389_;
v___y_2377_ = v___x_2393_;
goto v___jp_2370_;
}
else
{
v___y_2371_ = v___y_2384_;
v___y_2372_ = v___y_2385_;
v___y_2373_ = v___y_2390_;
v___y_2374_ = v___y_2388_;
v___y_2375_ = v___y_2387_;
v___y_2376_ = v___y_2389_;
v___y_2377_ = v___y_2383_;
goto v___jp_2370_;
}
}
v___jp_2394_:
{
uint64_t v___x_2402_; uint64_t v___x_2403_; uint8_t v___x_2404_; 
v___x_2402_ = 4ULL;
v___x_2403_ = lean_uint64_shift_right(v___y_2397_, v___x_2402_);
v___x_2404_ = lean_uint64_dec_eq(v___x_2403_, v___y_2395_);
if (v___x_2404_ == 0)
{
v___y_2382_ = v___x_2402_;
v___y_2383_ = v___y_2401_;
v___y_2384_ = v___y_2395_;
v___y_2385_ = v___y_2396_;
v___y_2386_ = v___y_2397_;
v___y_2387_ = v___y_2399_;
v___y_2388_ = v___y_2398_;
v___y_2389_ = v___y_2400_;
v___y_2390_ = v___x_2403_;
goto v___jp_2381_;
}
else
{
v___y_2382_ = v___x_2402_;
v___y_2383_ = v___y_2401_;
v___y_2384_ = v___y_2395_;
v___y_2385_ = v___y_2396_;
v___y_2386_ = v___y_2397_;
v___y_2387_ = v___y_2399_;
v___y_2388_ = v___y_2398_;
v___y_2389_ = v___y_2400_;
v___y_2390_ = v___y_2397_;
goto v___jp_2381_;
}
}
v___jp_2405_:
{
uint64_t v___x_2415_; uint8_t v___x_2416_; 
v___x_2415_ = lean_uint64_shift_right(v___y_2406_, v___y_2410_);
v___x_2416_ = lean_uint64_dec_eq(v___x_2415_, v___y_2407_);
if (v___x_2416_ == 0)
{
uint64_t v___x_2417_; 
v___x_2417_ = lean_uint64_add(v___y_2409_, v___y_2410_);
v___y_2395_ = v___y_2407_;
v___y_2396_ = v___y_2408_;
v___y_2397_ = v___y_2414_;
v___y_2398_ = v___y_2412_;
v___y_2399_ = v___y_2411_;
v___y_2400_ = v___y_2413_;
v___y_2401_ = v___x_2417_;
goto v___jp_2394_;
}
else
{
v___y_2395_ = v___y_2407_;
v___y_2396_ = v___y_2408_;
v___y_2397_ = v___y_2414_;
v___y_2398_ = v___y_2412_;
v___y_2399_ = v___y_2411_;
v___y_2400_ = v___y_2413_;
v___y_2401_ = v___y_2409_;
goto v___jp_2394_;
}
}
v___jp_2418_:
{
uint64_t v___x_2426_; uint64_t v___x_2427_; uint8_t v___x_2428_; 
v___x_2426_ = 8ULL;
v___x_2427_ = lean_uint64_shift_right(v___y_2419_, v___x_2426_);
v___x_2428_ = lean_uint64_dec_eq(v___x_2427_, v___y_2420_);
if (v___x_2428_ == 0)
{
v___y_2406_ = v___y_2419_;
v___y_2407_ = v___y_2420_;
v___y_2408_ = v___y_2421_;
v___y_2409_ = v___y_2425_;
v___y_2410_ = v___x_2426_;
v___y_2411_ = v___y_2423_;
v___y_2412_ = v___y_2422_;
v___y_2413_ = v___y_2424_;
v___y_2414_ = v___x_2427_;
goto v___jp_2405_;
}
else
{
v___y_2406_ = v___y_2419_;
v___y_2407_ = v___y_2420_;
v___y_2408_ = v___y_2421_;
v___y_2409_ = v___y_2425_;
v___y_2410_ = v___x_2426_;
v___y_2411_ = v___y_2423_;
v___y_2412_ = v___y_2422_;
v___y_2413_ = v___y_2424_;
v___y_2414_ = v___y_2419_;
goto v___jp_2405_;
}
}
v___jp_2429_:
{
uint64_t v___x_2439_; uint8_t v___x_2440_; 
v___x_2439_ = lean_uint64_shift_right(v___y_2434_, v___y_2430_);
v___x_2440_ = lean_uint64_dec_eq(v___x_2439_, v___y_2431_);
if (v___x_2440_ == 0)
{
uint64_t v___x_2441_; 
v___x_2441_ = lean_uint64_add(v___y_2433_, v___y_2430_);
v___y_2419_ = v___y_2438_;
v___y_2420_ = v___y_2431_;
v___y_2421_ = v___y_2432_;
v___y_2422_ = v___y_2436_;
v___y_2423_ = v___y_2435_;
v___y_2424_ = v___y_2437_;
v___y_2425_ = v___x_2441_;
goto v___jp_2418_;
}
else
{
v___y_2419_ = v___y_2438_;
v___y_2420_ = v___y_2431_;
v___y_2421_ = v___y_2432_;
v___y_2422_ = v___y_2436_;
v___y_2423_ = v___y_2435_;
v___y_2424_ = v___y_2437_;
v___y_2425_ = v___y_2433_;
goto v___jp_2418_;
}
}
v___jp_2442_:
{
uint64_t v___x_2450_; uint64_t v___x_2451_; uint8_t v___x_2452_; 
v___x_2450_ = 16ULL;
v___x_2451_ = lean_uint64_shift_right(v___y_2445_, v___x_2450_);
v___x_2452_ = lean_uint64_dec_eq(v___x_2451_, v___y_2443_);
if (v___x_2452_ == 0)
{
v___y_2430_ = v___x_2450_;
v___y_2431_ = v___y_2443_;
v___y_2432_ = v___y_2444_;
v___y_2433_ = v___y_2449_;
v___y_2434_ = v___y_2445_;
v___y_2435_ = v___y_2447_;
v___y_2436_ = v___y_2446_;
v___y_2437_ = v___y_2448_;
v___y_2438_ = v___x_2451_;
goto v___jp_2429_;
}
else
{
v___y_2430_ = v___x_2450_;
v___y_2431_ = v___y_2443_;
v___y_2432_ = v___y_2444_;
v___y_2433_ = v___y_2449_;
v___y_2434_ = v___y_2445_;
v___y_2435_ = v___y_2447_;
v___y_2436_ = v___y_2446_;
v___y_2437_ = v___y_2448_;
v___y_2438_ = v___y_2445_;
goto v___jp_2429_;
}
}
v___jp_2453_:
{
uint64_t v___x_2461_; uint8_t v___x_2462_; 
v___x_2461_ = lean_uint64_shift_right(v___y_2457_, v___y_2456_);
v___x_2462_ = lean_uint64_dec_eq(v___x_2461_, v___y_2454_);
if (v___x_2462_ == 0)
{
v___y_2443_ = v___y_2454_;
v___y_2444_ = v___y_2455_;
v___y_2445_ = v___y_2460_;
v___y_2446_ = v___y_2458_;
v___y_2447_ = v___y_2457_;
v___y_2448_ = v___y_2459_;
v___y_2449_ = v___y_2456_;
goto v___jp_2442_;
}
else
{
v___y_2443_ = v___y_2454_;
v___y_2444_ = v___y_2455_;
v___y_2445_ = v___y_2460_;
v___y_2446_ = v___y_2458_;
v___y_2447_ = v___y_2457_;
v___y_2448_ = v___y_2459_;
v___y_2449_ = v___y_2454_;
goto v___jp_2442_;
}
}
v___jp_2463_:
{
uint64_t v___x_2468_; uint8_t v___x_2469_; 
v___x_2468_ = 0ULL;
v___x_2469_ = lean_uint64_dec_eq(v___y_2466_, v___x_2468_);
if (v___x_2469_ == 0)
{
uint64_t v___x_2470_; uint64_t v___x_2471_; uint8_t v___x_2472_; 
v___x_2470_ = 32ULL;
v___x_2471_ = lean_uint64_shift_right(v___y_2466_, v___x_2470_);
v___x_2472_ = lean_uint64_dec_eq(v___x_2471_, v___x_2468_);
if (v___x_2472_ == 0)
{
v___y_2454_ = v___x_2468_;
v___y_2455_ = v___y_2464_;
v___y_2456_ = v___x_2470_;
v___y_2457_ = v___y_2466_;
v___y_2458_ = v___y_2465_;
v___y_2459_ = v___y_2467_;
v___y_2460_ = v___x_2471_;
goto v___jp_2453_;
}
else
{
v___y_2454_ = v___x_2468_;
v___y_2455_ = v___y_2464_;
v___y_2456_ = v___x_2470_;
v___y_2457_ = v___y_2466_;
v___y_2458_ = v___y_2465_;
v___y_2459_ = v___y_2467_;
v___y_2460_ = v___y_2466_;
goto v___jp_2453_;
}
}
else
{
if (v___y_2464_ == 0)
{
uint32_t v___x_2473_; 
v___x_2473_ = 0;
return v___x_2473_;
}
else
{
uint32_t v___x_2474_; 
v___x_2474_ = 2147483648;
return v___x_2474_;
}
}
}
v___jp_2475_:
{
uint64_t v___x_2482_; uint64_t v___x_2483_; uint64_t v___x_2484_; uint8_t v___x_2485_; 
v___x_2482_ = lean_uint64_mul(v___y_2479_, v___y_2478_);
v___x_2483_ = lean_uint64_add(v___y_2476_, v___y_2481_);
v___x_2484_ = 281474976710656ULL;
v___x_2485_ = lean_uint64_dec_lt(v___x_2482_, v___x_2484_);
if (v___x_2485_ == 0)
{
v___y_2464_ = v___y_2477_;
v___y_2465_ = v___x_2483_;
v___y_2466_ = v___x_2482_;
v___y_2467_ = v___y_2480_;
goto v___jp_2463_;
}
else
{
uint64_t v___x_2486_; uint8_t v___x_2487_; 
v___x_2486_ = 123ULL;
v___x_2487_ = lean_uint64_dec_le(v___x_2483_, v___x_2486_);
if (v___x_2487_ == 0)
{
v___y_2464_ = v___y_2477_;
v___y_2465_ = v___x_2483_;
v___y_2466_ = v___x_2482_;
v___y_2467_ = v___y_2480_;
goto v___jp_2463_;
}
else
{
uint64_t v___x_2488_; uint8_t v___x_2489_; 
v___x_2488_ = 0ULL;
v___x_2489_ = lean_uint64_dec_eq(v___x_2482_, v___x_2488_);
if (v___x_2489_ == 0)
{
uint64_t v___x_2490_; uint64_t v___x_2491_; uint8_t v___x_2492_; 
v___x_2490_ = 149ULL;
v___x_2491_ = lean_uint64_sub(v___x_2490_, v___x_2483_);
v___x_2492_ = lean_uint64_dec_eq(v___x_2491_, v___x_2488_);
if (v___x_2492_ == 0)
{
uint64_t v___x_2493_; uint8_t v___x_2494_; 
v___x_2493_ = 64ULL;
v___x_2494_ = lean_uint64_dec_lt(v___x_2491_, v___x_2493_);
if (v___x_2494_ == 0)
{
uint8_t v___x_2495_; 
v___x_2495_ = lean_uint64_dec_eq(v___x_2491_, v___x_2493_);
if (v___x_2495_ == 0)
{
v___y_1791_ = v___y_2477_;
v___y_1792_ = v___x_2488_;
v___y_1793_ = v___y_2480_;
v___y_1794_ = v___x_2488_;
goto v___jp_1790_;
}
else
{
uint64_t v___x_2496_; uint8_t v___x_2497_; 
v___x_2496_ = 9223372036854775808ULL;
v___x_2497_ = lean_uint64_dec_lt(v___x_2496_, v___x_2482_);
if (v___x_2497_ == 0)
{
v___y_1791_ = v___y_2477_;
v___y_1792_ = v___x_2488_;
v___y_1793_ = v___y_2480_;
v___y_1794_ = v___x_2488_;
goto v___jp_1790_;
}
else
{
uint64_t v___x_2498_; 
v___x_2498_ = 1ULL;
v___y_1791_ = v___y_2477_;
v___y_1792_ = v___x_2488_;
v___y_1793_ = v___y_2480_;
v___y_1794_ = v___x_2498_;
goto v___jp_1790_;
}
}
}
else
{
uint64_t v_quotient_2499_; uint64_t v___x_2500_; uint64_t v___x_2501_; uint64_t v___x_2502_; uint64_t v_remainder_2503_; uint64_t v___x_2504_; uint64_t v_half_2505_; uint8_t v___x_2506_; 
v_quotient_2499_ = lean_uint64_shift_right(v___x_2482_, v___x_2491_);
v___x_2500_ = 1ULL;
v___x_2501_ = lean_uint64_shift_left(v___x_2500_, v___x_2491_);
v___x_2502_ = lean_uint64_sub(v___x_2501_, v___x_2500_);
v_remainder_2503_ = lean_uint64_land(v___x_2482_, v___x_2502_);
v___x_2504_ = lean_uint64_sub(v___x_2491_, v___x_2500_);
v_half_2505_ = lean_uint64_shift_left(v___x_2500_, v___x_2504_);
v___x_2506_ = lean_uint64_dec_lt(v_remainder_2503_, v_half_2505_);
if (v___x_2506_ == 0)
{
uint8_t v___x_2507_; 
v___x_2507_ = lean_uint64_dec_lt(v_half_2505_, v_remainder_2503_);
if (v___x_2507_ == 0)
{
uint64_t v___x_2508_; uint8_t v___x_2509_; 
v___x_2508_ = lean_uint64_land(v_quotient_2499_, v___x_2500_);
v___x_2509_ = lean_uint64_dec_eq(v___x_2508_, v___x_2488_);
if (v___x_2509_ == 0)
{
uint64_t v___x_2510_; 
v___x_2510_ = lean_uint64_add(v_quotient_2499_, v___x_2500_);
v___y_1791_ = v___y_2477_;
v___y_1792_ = v___x_2488_;
v___y_1793_ = v___y_2480_;
v___y_1794_ = v___x_2510_;
goto v___jp_1790_;
}
else
{
v___y_1791_ = v___y_2477_;
v___y_1792_ = v___x_2488_;
v___y_1793_ = v___y_2480_;
v___y_1794_ = v_quotient_2499_;
goto v___jp_1790_;
}
}
else
{
uint64_t v___x_2511_; 
v___x_2511_ = lean_uint64_add(v_quotient_2499_, v___x_2500_);
v___y_1791_ = v___y_2477_;
v___y_1792_ = v___x_2488_;
v___y_1793_ = v___y_2480_;
v___y_1794_ = v___x_2511_;
goto v___jp_1790_;
}
}
else
{
v___y_1791_ = v___y_2477_;
v___y_1792_ = v___x_2488_;
v___y_1793_ = v___y_2480_;
v___y_1794_ = v_quotient_2499_;
goto v___jp_1790_;
}
}
}
else
{
v___y_1791_ = v___y_2477_;
v___y_1792_ = v___x_2488_;
v___y_1793_ = v___y_2480_;
v___y_1794_ = v___x_2482_;
goto v___jp_1790_;
}
}
else
{
if (v___y_2477_ == 0)
{
uint32_t v___x_2512_; 
v___x_2512_ = 0;
return v___x_2512_;
}
else
{
uint32_t v___x_2513_; 
v___x_2513_ = 2147483648;
return v___x_2513_;
}
}
}
}
}
v___jp_2514_:
{
uint32_t v___x_2519_; uint32_t v___x_2520_; uint32_t v___x_2521_; uint32_t v___x_2522_; uint32_t v___x_2523_; 
v___x_2519_ = lean_uint32_land(v___y_2515_, v___x_2231_);
v___x_2520_ = lean_uint32_shift_left(v___x_2519_, v___x_2190_);
v___x_2521_ = lean_uint32_lor(v___y_2518_, v___x_2520_);
v___x_2522_ = lean_uint32_land(v___y_2517_, v___y_2516_);
v___x_2523_ = lean_uint32_lor(v___x_2521_, v___x_2522_);
return v___x_2523_;
}
v___jp_2524_:
{
if (v___y_2526_ == 0)
{
uint32_t v___x_2529_; 
v___x_2529_ = 0;
v___y_2515_ = v___y_2525_;
v___y_2516_ = v___y_2527_;
v___y_2517_ = v___y_2528_;
v___y_2518_ = v___x_2529_;
goto v___jp_2514_;
}
else
{
uint32_t v___x_2530_; 
v___x_2530_ = 2147483648;
v___y_2515_ = v___y_2525_;
v___y_2516_ = v___y_2527_;
v___y_2517_ = v___y_2528_;
v___y_2518_ = v___x_2530_;
goto v___jp_2514_;
}
}
v___jp_2531_:
{
uint64_t v___x_2537_; uint64_t v_encodedExponent_2538_; uint32_t v___x_2539_; uint64_t v___x_2540_; uint8_t v___x_2541_; 
v___x_2537_ = 171ULL;
v_encodedExponent_2538_ = lean_uint64_sub(v___y_2535_, v___x_2537_);
v___x_2539_ = lean_uint64_to_uint32(v_encodedExponent_2538_);
v___x_2540_ = 8388608ULL;
v___x_2541_ = lean_uint64_dec_lt(v___y_2536_, v___x_2540_);
if (v___x_2541_ == 0)
{
uint64_t v___x_2542_; uint32_t v___x_2543_; 
v___x_2542_ = lean_uint64_sub(v___y_2536_, v___x_2540_);
v___x_2543_ = lean_uint64_to_uint32(v___x_2542_);
v___y_2525_ = v___x_2539_;
v___y_2526_ = v___y_2532_;
v___y_2527_ = v___y_2533_;
v___y_2528_ = v___x_2543_;
goto v___jp_2524_;
}
else
{
uint32_t v___x_2544_; 
v___x_2544_ = lean_uint64_to_uint32(v___y_2534_);
v___y_2525_ = v___x_2539_;
v___y_2526_ = v___y_2532_;
v___y_2527_ = v___y_2533_;
v___y_2528_ = v___x_2544_;
goto v___jp_2524_;
}
}
v___jp_2545_:
{
uint64_t v___x_2552_; uint8_t v___x_2553_; 
v___x_2552_ = 425ULL;
v___x_2553_ = lean_uint64_dec_lt(v___x_2552_, v___y_2551_);
if (v___x_2553_ == 0)
{
if (v___y_2549_ == 0)
{
v___y_2532_ = v___y_2546_;
v___y_2533_ = v___y_2547_;
v___y_2534_ = v___y_2548_;
v___y_2535_ = v___y_2551_;
v___y_2536_ = v___y_2550_;
goto v___jp_2531_;
}
else
{
uint64_t v___x_2554_; 
v___x_2554_ = 8388608ULL;
v___y_2532_ = v___y_2546_;
v___y_2533_ = v___y_2547_;
v___y_2534_ = v___y_2548_;
v___y_2535_ = v___y_2551_;
v___y_2536_ = v___x_2554_;
goto v___jp_2531_;
}
}
else
{
if (v___y_2546_ == 0)
{
uint32_t v___x_2555_; 
v___x_2555_ = 2139095040;
return v___x_2555_;
}
else
{
uint32_t v___x_2556_; 
v___x_2556_ = 4286578688;
return v___x_2556_;
}
}
}
v___jp_2557_:
{
uint64_t v___x_2563_; uint8_t v_carry_2564_; 
v___x_2563_ = 16777216ULL;
v_carry_2564_ = lean_uint64_dec_eq(v___y_2562_, v___x_2563_);
if (v_carry_2564_ == 0)
{
v___y_2546_ = v___y_2558_;
v___y_2547_ = v___y_2559_;
v___y_2548_ = v___y_2560_;
v___y_2549_ = v_carry_2564_;
v___y_2550_ = v___y_2562_;
v___y_2551_ = v___y_2561_;
goto v___jp_2545_;
}
else
{
uint64_t v___x_2565_; uint64_t v___x_2566_; 
v___x_2565_ = 1ULL;
v___x_2566_ = lean_uint64_add(v___y_2561_, v___x_2565_);
v___y_2546_ = v___y_2558_;
v___y_2547_ = v___y_2559_;
v___y_2548_ = v___y_2560_;
v___y_2549_ = v_carry_2564_;
v___y_2550_ = v___y_2562_;
v___y_2551_ = v___x_2566_;
goto v___jp_2545_;
}
}
v___jp_2567_:
{
uint64_t v_position_2574_; uint64_t v___x_2575_; uint8_t v___x_2576_; 
v_position_2574_ = lean_uint64_add(v___y_2573_, v___y_2572_);
v___x_2575_ = 172ULL;
v___x_2576_ = lean_uint64_dec_lt(v_position_2574_, v___x_2575_);
if (v___x_2576_ == 0)
{
uint64_t v___x_2577_; uint8_t v___x_2578_; 
v___x_2577_ = 23ULL;
v___x_2578_ = lean_uint64_dec_lt(v___y_2573_, v___x_2577_);
if (v___x_2578_ == 0)
{
uint64_t v___x_2579_; uint8_t v___x_2580_; 
v___x_2579_ = lean_uint64_sub(v___y_2573_, v___x_2577_);
v___x_2580_ = lean_uint64_dec_eq(v___x_2579_, v___y_2571_);
if (v___x_2580_ == 0)
{
uint64_t v___x_2581_; uint8_t v___x_2582_; 
v___x_2581_ = 64ULL;
v___x_2582_ = lean_uint64_dec_lt(v___x_2579_, v___x_2581_);
if (v___x_2582_ == 0)
{
uint8_t v___x_2583_; 
v___x_2583_ = lean_uint64_dec_eq(v___x_2579_, v___x_2581_);
if (v___x_2583_ == 0)
{
v___y_2558_ = v___y_2569_;
v___y_2559_ = v___y_2570_;
v___y_2560_ = v___y_2571_;
v___y_2561_ = v_position_2574_;
v___y_2562_ = v___y_2571_;
goto v___jp_2557_;
}
else
{
uint64_t v___x_2584_; uint8_t v___x_2585_; 
v___x_2584_ = 9223372036854775808ULL;
v___x_2585_ = lean_uint64_dec_lt(v___x_2584_, v___y_2568_);
if (v___x_2585_ == 0)
{
v___y_2558_ = v___y_2569_;
v___y_2559_ = v___y_2570_;
v___y_2560_ = v___y_2571_;
v___y_2561_ = v_position_2574_;
v___y_2562_ = v___y_2571_;
goto v___jp_2557_;
}
else
{
uint64_t v___x_2586_; 
v___x_2586_ = 1ULL;
v___y_2558_ = v___y_2569_;
v___y_2559_ = v___y_2570_;
v___y_2560_ = v___y_2571_;
v___y_2561_ = v_position_2574_;
v___y_2562_ = v___x_2586_;
goto v___jp_2557_;
}
}
}
else
{
uint64_t v_quotient_2587_; uint64_t v___x_2588_; uint64_t v___x_2589_; uint64_t v___x_2590_; uint64_t v_remainder_2591_; uint64_t v___x_2592_; uint64_t v_half_2593_; uint8_t v___x_2594_; 
v_quotient_2587_ = lean_uint64_shift_right(v___y_2568_, v___x_2579_);
v___x_2588_ = 1ULL;
v___x_2589_ = lean_uint64_shift_left(v___x_2588_, v___x_2579_);
v___x_2590_ = lean_uint64_sub(v___x_2589_, v___x_2588_);
v_remainder_2591_ = lean_uint64_land(v___y_2568_, v___x_2590_);
v___x_2592_ = lean_uint64_sub(v___x_2579_, v___x_2588_);
v_half_2593_ = lean_uint64_shift_left(v___x_2588_, v___x_2592_);
v___x_2594_ = lean_uint64_dec_lt(v_remainder_2591_, v_half_2593_);
if (v___x_2594_ == 0)
{
uint8_t v___x_2595_; 
v___x_2595_ = lean_uint64_dec_lt(v_half_2593_, v_remainder_2591_);
if (v___x_2595_ == 0)
{
uint64_t v___x_2596_; uint8_t v___x_2597_; 
v___x_2596_ = lean_uint64_land(v_quotient_2587_, v___x_2588_);
v___x_2597_ = lean_uint64_dec_eq(v___x_2596_, v___y_2571_);
if (v___x_2597_ == 0)
{
uint64_t v___x_2598_; 
v___x_2598_ = lean_uint64_add(v_quotient_2587_, v___x_2588_);
v___y_2558_ = v___y_2569_;
v___y_2559_ = v___y_2570_;
v___y_2560_ = v___y_2571_;
v___y_2561_ = v_position_2574_;
v___y_2562_ = v___x_2598_;
goto v___jp_2557_;
}
else
{
v___y_2558_ = v___y_2569_;
v___y_2559_ = v___y_2570_;
v___y_2560_ = v___y_2571_;
v___y_2561_ = v_position_2574_;
v___y_2562_ = v_quotient_2587_;
goto v___jp_2557_;
}
}
else
{
uint64_t v___x_2599_; 
v___x_2599_ = lean_uint64_add(v_quotient_2587_, v___x_2588_);
v___y_2558_ = v___y_2569_;
v___y_2559_ = v___y_2570_;
v___y_2560_ = v___y_2571_;
v___y_2561_ = v_position_2574_;
v___y_2562_ = v___x_2599_;
goto v___jp_2557_;
}
}
else
{
v___y_2558_ = v___y_2569_;
v___y_2559_ = v___y_2570_;
v___y_2560_ = v___y_2571_;
v___y_2561_ = v_position_2574_;
v___y_2562_ = v_quotient_2587_;
goto v___jp_2557_;
}
}
}
else
{
v___y_2558_ = v___y_2569_;
v___y_2559_ = v___y_2570_;
v___y_2560_ = v___y_2571_;
v___y_2561_ = v_position_2574_;
v___y_2562_ = v___y_2568_;
goto v___jp_2557_;
}
}
else
{
uint64_t v___x_2600_; uint64_t v___x_2601_; 
v___x_2600_ = lean_uint64_sub(v___x_2577_, v___y_2573_);
v___x_2601_ = lean_uint64_shift_left(v___y_2568_, v___x_2600_);
v___y_2558_ = v___y_2569_;
v___y_2559_ = v___y_2570_;
v___y_2560_ = v___y_2571_;
v___y_2561_ = v_position_2574_;
v___y_2562_ = v___x_2601_;
goto v___jp_2557_;
}
}
else
{
uint64_t v___x_2602_; uint8_t v___x_2603_; 
v___x_2602_ = 149ULL;
v___x_2603_ = lean_uint64_dec_lt(v___y_2572_, v___x_2602_);
if (v___x_2603_ == 0)
{
uint64_t v___x_2604_; uint64_t v___x_2605_; 
v___x_2604_ = lean_uint64_sub(v___y_2572_, v___x_2602_);
v___x_2605_ = lean_uint64_shift_left(v___y_2568_, v___x_2604_);
v___y_1915_ = v___y_2569_;
v___y_1916_ = v___y_2570_;
v___y_1917_ = v___y_2571_;
v___y_1918_ = v___x_2605_;
goto v___jp_1914_;
}
else
{
uint64_t v___x_2606_; uint8_t v___x_2607_; 
v___x_2606_ = lean_uint64_sub(v___x_2602_, v___y_2572_);
v___x_2607_ = lean_uint64_dec_eq(v___x_2606_, v___y_2571_);
if (v___x_2607_ == 0)
{
uint64_t v___x_2608_; uint8_t v___x_2609_; 
v___x_2608_ = 64ULL;
v___x_2609_ = lean_uint64_dec_lt(v___x_2606_, v___x_2608_);
if (v___x_2609_ == 0)
{
uint8_t v___x_2610_; 
v___x_2610_ = lean_uint64_dec_eq(v___x_2606_, v___x_2608_);
if (v___x_2610_ == 0)
{
v___y_1915_ = v___y_2569_;
v___y_1916_ = v___y_2570_;
v___y_1917_ = v___y_2571_;
v___y_1918_ = v___y_2571_;
goto v___jp_1914_;
}
else
{
uint64_t v___x_2611_; uint8_t v___x_2612_; 
v___x_2611_ = 9223372036854775808ULL;
v___x_2612_ = lean_uint64_dec_lt(v___x_2611_, v___y_2568_);
if (v___x_2612_ == 0)
{
v___y_1915_ = v___y_2569_;
v___y_1916_ = v___y_2570_;
v___y_1917_ = v___y_2571_;
v___y_1918_ = v___y_2571_;
goto v___jp_1914_;
}
else
{
uint64_t v___x_2613_; 
v___x_2613_ = 1ULL;
v___y_1915_ = v___y_2569_;
v___y_1916_ = v___y_2570_;
v___y_1917_ = v___y_2571_;
v___y_1918_ = v___x_2613_;
goto v___jp_1914_;
}
}
}
else
{
uint64_t v_quotient_2614_; uint64_t v___x_2615_; uint64_t v___x_2616_; uint64_t v___x_2617_; uint64_t v_remainder_2618_; uint64_t v___x_2619_; uint64_t v_half_2620_; uint8_t v___x_2621_; 
v_quotient_2614_ = lean_uint64_shift_right(v___y_2568_, v___x_2606_);
v___x_2615_ = 1ULL;
v___x_2616_ = lean_uint64_shift_left(v___x_2615_, v___x_2606_);
v___x_2617_ = lean_uint64_sub(v___x_2616_, v___x_2615_);
v_remainder_2618_ = lean_uint64_land(v___y_2568_, v___x_2617_);
v___x_2619_ = lean_uint64_sub(v___x_2606_, v___x_2615_);
v_half_2620_ = lean_uint64_shift_left(v___x_2615_, v___x_2619_);
v___x_2621_ = lean_uint64_dec_lt(v_remainder_2618_, v_half_2620_);
if (v___x_2621_ == 0)
{
uint8_t v___x_2622_; 
v___x_2622_ = lean_uint64_dec_lt(v_half_2620_, v_remainder_2618_);
if (v___x_2622_ == 0)
{
uint64_t v___x_2623_; uint8_t v___x_2624_; 
v___x_2623_ = lean_uint64_land(v_quotient_2614_, v___x_2615_);
v___x_2624_ = lean_uint64_dec_eq(v___x_2623_, v___y_2571_);
if (v___x_2624_ == 0)
{
uint64_t v___x_2625_; 
v___x_2625_ = lean_uint64_add(v_quotient_2614_, v___x_2615_);
v___y_1915_ = v___y_2569_;
v___y_1916_ = v___y_2570_;
v___y_1917_ = v___y_2571_;
v___y_1918_ = v___x_2625_;
goto v___jp_1914_;
}
else
{
v___y_1915_ = v___y_2569_;
v___y_1916_ = v___y_2570_;
v___y_1917_ = v___y_2571_;
v___y_1918_ = v_quotient_2614_;
goto v___jp_1914_;
}
}
else
{
uint64_t v___x_2626_; 
v___x_2626_ = lean_uint64_add(v_quotient_2614_, v___x_2615_);
v___y_1915_ = v___y_2569_;
v___y_1916_ = v___y_2570_;
v___y_1917_ = v___y_2571_;
v___y_1918_ = v___x_2626_;
goto v___jp_1914_;
}
}
else
{
v___y_1915_ = v___y_2569_;
v___y_1916_ = v___y_2570_;
v___y_1917_ = v___y_2571_;
v___y_1918_ = v_quotient_2614_;
goto v___jp_1914_;
}
}
}
else
{
v___y_1915_ = v___y_2569_;
v___y_1916_ = v___y_2570_;
v___y_1917_ = v___y_2571_;
v___y_1918_ = v___y_2568_;
goto v___jp_1914_;
}
}
}
}
v___jp_2627_:
{
uint64_t v___x_2635_; uint64_t v___x_2636_; uint8_t v___x_2637_; 
v___x_2635_ = 1ULL;
v___x_2636_ = lean_uint64_shift_right(v___y_2632_, v___x_2635_);
v___x_2637_ = lean_uint64_dec_eq(v___x_2636_, v___y_2631_);
if (v___x_2637_ == 0)
{
uint64_t v___x_2638_; 
v___x_2638_ = lean_uint64_add(v___y_2634_, v___x_2635_);
v___y_2568_ = v___y_2629_;
v___y_2569_ = v___y_2628_;
v___y_2570_ = v___y_2630_;
v___y_2571_ = v___y_2631_;
v___y_2572_ = v___y_2633_;
v___y_2573_ = v___x_2638_;
goto v___jp_2567_;
}
else
{
v___y_2568_ = v___y_2629_;
v___y_2569_ = v___y_2628_;
v___y_2570_ = v___y_2630_;
v___y_2571_ = v___y_2631_;
v___y_2572_ = v___y_2633_;
v___y_2573_ = v___y_2634_;
goto v___jp_2567_;
}
}
v___jp_2639_:
{
uint64_t v___x_2649_; uint8_t v___x_2650_; 
v___x_2649_ = lean_uint64_shift_right(v___y_2640_, v___y_2644_);
v___x_2650_ = lean_uint64_dec_eq(v___x_2649_, v___y_2646_);
if (v___x_2650_ == 0)
{
uint64_t v___x_2651_; 
v___x_2651_ = lean_uint64_add(v___y_2641_, v___y_2644_);
v___y_2628_ = v___y_2643_;
v___y_2629_ = v___y_2642_;
v___y_2630_ = v___y_2645_;
v___y_2631_ = v___y_2646_;
v___y_2632_ = v___y_2648_;
v___y_2633_ = v___y_2647_;
v___y_2634_ = v___x_2651_;
goto v___jp_2627_;
}
else
{
v___y_2628_ = v___y_2643_;
v___y_2629_ = v___y_2642_;
v___y_2630_ = v___y_2645_;
v___y_2631_ = v___y_2646_;
v___y_2632_ = v___y_2648_;
v___y_2633_ = v___y_2647_;
v___y_2634_ = v___y_2641_;
goto v___jp_2627_;
}
}
v___jp_2652_:
{
uint64_t v___x_2660_; uint64_t v___x_2661_; uint8_t v___x_2662_; 
v___x_2660_ = 2ULL;
v___x_2661_ = lean_uint64_shift_right(v___y_2653_, v___x_2660_);
v___x_2662_ = lean_uint64_dec_eq(v___x_2661_, v___y_2657_);
if (v___x_2662_ == 0)
{
v___y_2640_ = v___y_2653_;
v___y_2641_ = v___y_2659_;
v___y_2642_ = v___y_2655_;
v___y_2643_ = v___y_2654_;
v___y_2644_ = v___x_2660_;
v___y_2645_ = v___y_2656_;
v___y_2646_ = v___y_2657_;
v___y_2647_ = v___y_2658_;
v___y_2648_ = v___x_2661_;
goto v___jp_2639_;
}
else
{
v___y_2640_ = v___y_2653_;
v___y_2641_ = v___y_2659_;
v___y_2642_ = v___y_2655_;
v___y_2643_ = v___y_2654_;
v___y_2644_ = v___x_2660_;
v___y_2645_ = v___y_2656_;
v___y_2646_ = v___y_2657_;
v___y_2647_ = v___y_2658_;
v___y_2648_ = v___y_2653_;
goto v___jp_2639_;
}
}
v___jp_2663_:
{
uint64_t v___x_2673_; uint8_t v___x_2674_; 
v___x_2673_ = lean_uint64_shift_right(v___y_2669_, v___y_2666_);
v___x_2674_ = lean_uint64_dec_eq(v___x_2673_, v___y_2668_);
if (v___x_2674_ == 0)
{
uint64_t v___x_2675_; 
v___x_2675_ = lean_uint64_add(v___y_2670_, v___y_2666_);
v___y_2653_ = v___y_2672_;
v___y_2654_ = v___y_2665_;
v___y_2655_ = v___y_2664_;
v___y_2656_ = v___y_2667_;
v___y_2657_ = v___y_2668_;
v___y_2658_ = v___y_2671_;
v___y_2659_ = v___x_2675_;
goto v___jp_2652_;
}
else
{
v___y_2653_ = v___y_2672_;
v___y_2654_ = v___y_2665_;
v___y_2655_ = v___y_2664_;
v___y_2656_ = v___y_2667_;
v___y_2657_ = v___y_2668_;
v___y_2658_ = v___y_2671_;
v___y_2659_ = v___y_2670_;
goto v___jp_2652_;
}
}
v___jp_2676_:
{
uint64_t v___x_2684_; uint64_t v___x_2685_; uint8_t v___x_2686_; 
v___x_2684_ = 4ULL;
v___x_2685_ = lean_uint64_shift_right(v___y_2681_, v___x_2684_);
v___x_2686_ = lean_uint64_dec_eq(v___x_2685_, v___y_2680_);
if (v___x_2686_ == 0)
{
v___y_2664_ = v___y_2678_;
v___y_2665_ = v___y_2677_;
v___y_2666_ = v___x_2684_;
v___y_2667_ = v___y_2679_;
v___y_2668_ = v___y_2680_;
v___y_2669_ = v___y_2681_;
v___y_2670_ = v___y_2683_;
v___y_2671_ = v___y_2682_;
v___y_2672_ = v___x_2685_;
goto v___jp_2663_;
}
else
{
v___y_2664_ = v___y_2678_;
v___y_2665_ = v___y_2677_;
v___y_2666_ = v___x_2684_;
v___y_2667_ = v___y_2679_;
v___y_2668_ = v___y_2680_;
v___y_2669_ = v___y_2681_;
v___y_2670_ = v___y_2683_;
v___y_2671_ = v___y_2682_;
v___y_2672_ = v___y_2681_;
goto v___jp_2663_;
}
}
v___jp_2687_:
{
uint64_t v___x_2697_; uint8_t v___x_2698_; 
v___x_2697_ = lean_uint64_shift_right(v___y_2692_, v___y_2694_);
v___x_2698_ = lean_uint64_dec_eq(v___x_2697_, v___y_2691_);
if (v___x_2698_ == 0)
{
uint64_t v___x_2699_; 
v___x_2699_ = lean_uint64_add(v___y_2693_, v___y_2694_);
v___y_2677_ = v___y_2689_;
v___y_2678_ = v___y_2688_;
v___y_2679_ = v___y_2690_;
v___y_2680_ = v___y_2691_;
v___y_2681_ = v___y_2696_;
v___y_2682_ = v___y_2695_;
v___y_2683_ = v___x_2699_;
goto v___jp_2676_;
}
else
{
v___y_2677_ = v___y_2689_;
v___y_2678_ = v___y_2688_;
v___y_2679_ = v___y_2690_;
v___y_2680_ = v___y_2691_;
v___y_2681_ = v___y_2696_;
v___y_2682_ = v___y_2695_;
v___y_2683_ = v___y_2693_;
goto v___jp_2676_;
}
}
v___jp_2700_:
{
uint64_t v___x_2708_; uint64_t v___x_2709_; uint8_t v___x_2710_; 
v___x_2708_ = 8ULL;
v___x_2709_ = lean_uint64_shift_right(v___y_2705_, v___x_2708_);
v___x_2710_ = lean_uint64_dec_eq(v___x_2709_, v___y_2704_);
if (v___x_2710_ == 0)
{
v___y_2688_ = v___y_2702_;
v___y_2689_ = v___y_2701_;
v___y_2690_ = v___y_2703_;
v___y_2691_ = v___y_2704_;
v___y_2692_ = v___y_2705_;
v___y_2693_ = v___y_2707_;
v___y_2694_ = v___x_2708_;
v___y_2695_ = v___y_2706_;
v___y_2696_ = v___x_2709_;
goto v___jp_2687_;
}
else
{
v___y_2688_ = v___y_2702_;
v___y_2689_ = v___y_2701_;
v___y_2690_ = v___y_2703_;
v___y_2691_ = v___y_2704_;
v___y_2692_ = v___y_2705_;
v___y_2693_ = v___y_2707_;
v___y_2694_ = v___x_2708_;
v___y_2695_ = v___y_2706_;
v___y_2696_ = v___y_2705_;
goto v___jp_2687_;
}
}
v___jp_2711_:
{
uint64_t v___x_2721_; uint8_t v___x_2722_; 
v___x_2721_ = lean_uint64_shift_right(v___y_2712_, v___y_2718_);
v___x_2722_ = lean_uint64_dec_eq(v___x_2721_, v___y_2717_);
if (v___x_2722_ == 0)
{
uint64_t v___x_2723_; 
v___x_2723_ = lean_uint64_add(v___y_2715_, v___y_2718_);
v___y_2701_ = v___y_2714_;
v___y_2702_ = v___y_2713_;
v___y_2703_ = v___y_2716_;
v___y_2704_ = v___y_2717_;
v___y_2705_ = v___y_2720_;
v___y_2706_ = v___y_2719_;
v___y_2707_ = v___x_2723_;
goto v___jp_2700_;
}
else
{
v___y_2701_ = v___y_2714_;
v___y_2702_ = v___y_2713_;
v___y_2703_ = v___y_2716_;
v___y_2704_ = v___y_2717_;
v___y_2705_ = v___y_2720_;
v___y_2706_ = v___y_2719_;
v___y_2707_ = v___y_2715_;
goto v___jp_2700_;
}
}
v___jp_2724_:
{
uint64_t v___x_2732_; uint64_t v___x_2733_; uint8_t v___x_2734_; 
v___x_2732_ = 16ULL;
v___x_2733_ = lean_uint64_shift_right(v___y_2727_, v___x_2732_);
v___x_2734_ = lean_uint64_dec_eq(v___x_2733_, v___y_2729_);
if (v___x_2734_ == 0)
{
v___y_2712_ = v___y_2727_;
v___y_2713_ = v___y_2726_;
v___y_2714_ = v___y_2725_;
v___y_2715_ = v___y_2731_;
v___y_2716_ = v___y_2728_;
v___y_2717_ = v___y_2729_;
v___y_2718_ = v___x_2732_;
v___y_2719_ = v___y_2730_;
v___y_2720_ = v___x_2733_;
goto v___jp_2711_;
}
else
{
v___y_2712_ = v___y_2727_;
v___y_2713_ = v___y_2726_;
v___y_2714_ = v___y_2725_;
v___y_2715_ = v___y_2731_;
v___y_2716_ = v___y_2728_;
v___y_2717_ = v___y_2729_;
v___y_2718_ = v___x_2732_;
v___y_2719_ = v___y_2730_;
v___y_2720_ = v___y_2727_;
goto v___jp_2711_;
}
}
v___jp_2735_:
{
uint64_t v___x_2743_; uint8_t v___x_2744_; 
v___x_2743_ = lean_uint64_shift_right(v___y_2736_, v___y_2740_);
v___x_2744_ = lean_uint64_dec_eq(v___x_2743_, v___y_2739_);
if (v___x_2744_ == 0)
{
v___y_2725_ = v___y_2737_;
v___y_2726_ = v___y_2736_;
v___y_2727_ = v___y_2742_;
v___y_2728_ = v___y_2738_;
v___y_2729_ = v___y_2739_;
v___y_2730_ = v___y_2741_;
v___y_2731_ = v___y_2740_;
goto v___jp_2724_;
}
else
{
v___y_2725_ = v___y_2737_;
v___y_2726_ = v___y_2736_;
v___y_2727_ = v___y_2742_;
v___y_2728_ = v___y_2738_;
v___y_2729_ = v___y_2739_;
v___y_2730_ = v___y_2741_;
v___y_2731_ = v___y_2739_;
goto v___jp_2724_;
}
}
v___jp_2745_:
{
uint64_t v___x_2750_; uint8_t v___x_2751_; 
v___x_2750_ = 0ULL;
v___x_2751_ = lean_uint64_dec_eq(v___y_2746_, v___x_2750_);
if (v___x_2751_ == 0)
{
uint64_t v___x_2752_; uint64_t v___x_2753_; uint8_t v___x_2754_; 
v___x_2752_ = 32ULL;
v___x_2753_ = lean_uint64_shift_right(v___y_2746_, v___x_2752_);
v___x_2754_ = lean_uint64_dec_eq(v___x_2753_, v___x_2750_);
if (v___x_2754_ == 0)
{
v___y_2736_ = v___y_2746_;
v___y_2737_ = v___y_2747_;
v___y_2738_ = v___y_2748_;
v___y_2739_ = v___x_2750_;
v___y_2740_ = v___x_2752_;
v___y_2741_ = v___y_2749_;
v___y_2742_ = v___x_2753_;
goto v___jp_2735_;
}
else
{
v___y_2736_ = v___y_2746_;
v___y_2737_ = v___y_2747_;
v___y_2738_ = v___y_2748_;
v___y_2739_ = v___x_2750_;
v___y_2740_ = v___x_2752_;
v___y_2741_ = v___y_2749_;
v___y_2742_ = v___y_2746_;
goto v___jp_2735_;
}
}
else
{
if (v___y_2747_ == 0)
{
uint32_t v___x_2755_; 
v___x_2755_ = 0;
return v___x_2755_;
}
else
{
uint32_t v___x_2756_; 
v___x_2756_ = 2147483648;
return v___x_2756_;
}
}
}
v___jp_2757_:
{
uint64_t v___x_2764_; uint64_t v___x_2765_; uint64_t v___x_2766_; uint8_t v___x_2767_; 
v___x_2764_ = lean_uint64_mul(v___y_2761_, v___y_2762_);
v___x_2765_ = lean_uint64_add(v___y_2759_, v___y_2763_);
v___x_2766_ = 281474976710656ULL;
v___x_2767_ = lean_uint64_dec_lt(v___x_2764_, v___x_2766_);
if (v___x_2767_ == 0)
{
v___y_2746_ = v___x_2764_;
v___y_2747_ = v___y_2758_;
v___y_2748_ = v___y_2760_;
v___y_2749_ = v___x_2765_;
goto v___jp_2745_;
}
else
{
uint64_t v___x_2768_; uint8_t v___x_2769_; 
v___x_2768_ = 123ULL;
v___x_2769_ = lean_uint64_dec_le(v___x_2765_, v___x_2768_);
if (v___x_2769_ == 0)
{
v___y_2746_ = v___x_2764_;
v___y_2747_ = v___y_2758_;
v___y_2748_ = v___y_2760_;
v___y_2749_ = v___x_2765_;
goto v___jp_2745_;
}
else
{
uint64_t v___x_2770_; uint8_t v___x_2771_; 
v___x_2770_ = 0ULL;
v___x_2771_ = lean_uint64_dec_eq(v___x_2764_, v___x_2770_);
if (v___x_2771_ == 0)
{
uint64_t v___x_2772_; uint64_t v___x_2773_; uint8_t v___x_2774_; 
v___x_2772_ = 149ULL;
v___x_2773_ = lean_uint64_sub(v___x_2772_, v___x_2765_);
v___x_2774_ = lean_uint64_dec_eq(v___x_2773_, v___x_2770_);
if (v___x_2774_ == 0)
{
uint64_t v___x_2775_; uint8_t v___x_2776_; 
v___x_2775_ = 64ULL;
v___x_2776_ = lean_uint64_dec_lt(v___x_2773_, v___x_2775_);
if (v___x_2776_ == 0)
{
uint8_t v___x_2777_; 
v___x_2777_ = lean_uint64_dec_eq(v___x_2773_, v___x_2775_);
if (v___x_2777_ == 0)
{
v___y_1936_ = v___y_2758_;
v___y_1937_ = v___y_2760_;
v___y_1938_ = v___x_2770_;
v___y_1939_ = v___x_2770_;
goto v___jp_1935_;
}
else
{
uint64_t v___x_2778_; uint8_t v___x_2779_; 
v___x_2778_ = 9223372036854775808ULL;
v___x_2779_ = lean_uint64_dec_lt(v___x_2778_, v___x_2764_);
if (v___x_2779_ == 0)
{
v___y_1936_ = v___y_2758_;
v___y_1937_ = v___y_2760_;
v___y_1938_ = v___x_2770_;
v___y_1939_ = v___x_2770_;
goto v___jp_1935_;
}
else
{
uint64_t v___x_2780_; 
v___x_2780_ = 1ULL;
v___y_1936_ = v___y_2758_;
v___y_1937_ = v___y_2760_;
v___y_1938_ = v___x_2770_;
v___y_1939_ = v___x_2780_;
goto v___jp_1935_;
}
}
}
else
{
uint64_t v_quotient_2781_; uint64_t v___x_2782_; uint64_t v___x_2783_; uint64_t v___x_2784_; uint64_t v_remainder_2785_; uint64_t v___x_2786_; uint64_t v_half_2787_; uint8_t v___x_2788_; 
v_quotient_2781_ = lean_uint64_shift_right(v___x_2764_, v___x_2773_);
v___x_2782_ = 1ULL;
v___x_2783_ = lean_uint64_shift_left(v___x_2782_, v___x_2773_);
v___x_2784_ = lean_uint64_sub(v___x_2783_, v___x_2782_);
v_remainder_2785_ = lean_uint64_land(v___x_2764_, v___x_2784_);
v___x_2786_ = lean_uint64_sub(v___x_2773_, v___x_2782_);
v_half_2787_ = lean_uint64_shift_left(v___x_2782_, v___x_2786_);
v___x_2788_ = lean_uint64_dec_lt(v_remainder_2785_, v_half_2787_);
if (v___x_2788_ == 0)
{
uint8_t v___x_2789_; 
v___x_2789_ = lean_uint64_dec_lt(v_half_2787_, v_remainder_2785_);
if (v___x_2789_ == 0)
{
uint64_t v___x_2790_; uint8_t v___x_2791_; 
v___x_2790_ = lean_uint64_land(v_quotient_2781_, v___x_2782_);
v___x_2791_ = lean_uint64_dec_eq(v___x_2790_, v___x_2770_);
if (v___x_2791_ == 0)
{
uint64_t v___x_2792_; 
v___x_2792_ = lean_uint64_add(v_quotient_2781_, v___x_2782_);
v___y_1936_ = v___y_2758_;
v___y_1937_ = v___y_2760_;
v___y_1938_ = v___x_2770_;
v___y_1939_ = v___x_2792_;
goto v___jp_1935_;
}
else
{
v___y_1936_ = v___y_2758_;
v___y_1937_ = v___y_2760_;
v___y_1938_ = v___x_2770_;
v___y_1939_ = v_quotient_2781_;
goto v___jp_1935_;
}
}
else
{
uint64_t v___x_2793_; 
v___x_2793_ = lean_uint64_add(v_quotient_2781_, v___x_2782_);
v___y_1936_ = v___y_2758_;
v___y_1937_ = v___y_2760_;
v___y_1938_ = v___x_2770_;
v___y_1939_ = v___x_2793_;
goto v___jp_1935_;
}
}
else
{
v___y_1936_ = v___y_2758_;
v___y_1937_ = v___y_2760_;
v___y_1938_ = v___x_2770_;
v___y_1939_ = v_quotient_2781_;
goto v___jp_1935_;
}
}
}
else
{
v___y_1936_ = v___y_2758_;
v___y_1937_ = v___y_2760_;
v___y_1938_ = v___x_2770_;
v___y_1939_ = v___x_2764_;
goto v___jp_1935_;
}
}
else
{
if (v___y_2758_ == 0)
{
uint32_t v___x_2794_; 
v___x_2794_ = 0;
return v___x_2794_;
}
else
{
uint32_t v___x_2795_; 
v___x_2795_ = 2147483648;
return v___x_2795_;
}
}
}
}
}
v___jp_2796_:
{
uint32_t v___x_2801_; uint32_t v___x_2802_; uint32_t v___x_2803_; uint32_t v___x_2804_; uint32_t v___x_2805_; 
v___x_2801_ = lean_uint32_land(v___y_2797_, v___x_2231_);
v___x_2802_ = lean_uint32_shift_left(v___x_2801_, v___x_2190_);
v___x_2803_ = lean_uint32_lor(v___y_2800_, v___x_2802_);
v___x_2804_ = lean_uint32_land(v___y_2798_, v___y_2799_);
v___x_2805_ = lean_uint32_lor(v___x_2803_, v___x_2804_);
return v___x_2805_;
}
v___jp_2806_:
{
if (v___y_2809_ == 0)
{
uint32_t v___x_2811_; 
v___x_2811_ = 0;
v___y_2797_ = v___y_2807_;
v___y_2798_ = v___y_2810_;
v___y_2799_ = v___y_2808_;
v___y_2800_ = v___x_2811_;
goto v___jp_2796_;
}
else
{
uint32_t v___x_2812_; 
v___x_2812_ = 2147483648;
v___y_2797_ = v___y_2807_;
v___y_2798_ = v___y_2810_;
v___y_2799_ = v___y_2808_;
v___y_2800_ = v___x_2812_;
goto v___jp_2796_;
}
}
v___jp_2813_:
{
uint64_t v___x_2819_; uint64_t v_encodedExponent_2820_; uint32_t v___x_2821_; uint64_t v___x_2822_; uint8_t v___x_2823_; 
v___x_2819_ = 171ULL;
v_encodedExponent_2820_ = lean_uint64_sub(v___y_2816_, v___x_2819_);
v___x_2821_ = lean_uint64_to_uint32(v_encodedExponent_2820_);
v___x_2822_ = 8388608ULL;
v___x_2823_ = lean_uint64_dec_lt(v___y_2818_, v___x_2822_);
if (v___x_2823_ == 0)
{
uint64_t v___x_2824_; uint32_t v___x_2825_; 
v___x_2824_ = lean_uint64_sub(v___y_2818_, v___x_2822_);
v___x_2825_ = lean_uint64_to_uint32(v___x_2824_);
v___y_2807_ = v___x_2821_;
v___y_2808_ = v___y_2815_;
v___y_2809_ = v___y_2817_;
v___y_2810_ = v___x_2825_;
goto v___jp_2806_;
}
else
{
uint32_t v___x_2826_; 
v___x_2826_ = lean_uint64_to_uint32(v___y_2814_);
v___y_2807_ = v___x_2821_;
v___y_2808_ = v___y_2815_;
v___y_2809_ = v___y_2817_;
v___y_2810_ = v___x_2826_;
goto v___jp_2806_;
}
}
v___jp_2827_:
{
uint64_t v___x_2834_; uint8_t v___x_2835_; 
v___x_2834_ = 425ULL;
v___x_2835_ = lean_uint64_dec_lt(v___x_2834_, v___y_2833_);
if (v___x_2835_ == 0)
{
if (v___y_2828_ == 0)
{
v___y_2814_ = v___y_2830_;
v___y_2815_ = v___y_2829_;
v___y_2816_ = v___y_2833_;
v___y_2817_ = v___y_2832_;
v___y_2818_ = v___y_2831_;
goto v___jp_2813_;
}
else
{
uint64_t v___x_2836_; 
v___x_2836_ = 8388608ULL;
v___y_2814_ = v___y_2830_;
v___y_2815_ = v___y_2829_;
v___y_2816_ = v___y_2833_;
v___y_2817_ = v___y_2832_;
v___y_2818_ = v___x_2836_;
goto v___jp_2813_;
}
}
else
{
if (v___y_2832_ == 0)
{
uint32_t v___x_2837_; 
v___x_2837_ = 2139095040;
return v___x_2837_;
}
else
{
uint32_t v___x_2838_; 
v___x_2838_ = 4286578688;
return v___x_2838_;
}
}
}
v___jp_2839_:
{
uint64_t v___x_2845_; uint8_t v_carry_2846_; 
v___x_2845_ = 16777216ULL;
v_carry_2846_ = lean_uint64_dec_eq(v___y_2844_, v___x_2845_);
if (v_carry_2846_ == 0)
{
v___y_2828_ = v_carry_2846_;
v___y_2829_ = v___y_2841_;
v___y_2830_ = v___y_2840_;
v___y_2831_ = v___y_2844_;
v___y_2832_ = v___y_2843_;
v___y_2833_ = v___y_2842_;
goto v___jp_2827_;
}
else
{
uint64_t v___x_2847_; uint64_t v___x_2848_; 
v___x_2847_ = 1ULL;
v___x_2848_ = lean_uint64_add(v___y_2842_, v___x_2847_);
v___y_2828_ = v_carry_2846_;
v___y_2829_ = v___y_2841_;
v___y_2830_ = v___y_2840_;
v___y_2831_ = v___y_2844_;
v___y_2832_ = v___y_2843_;
v___y_2833_ = v___x_2848_;
goto v___jp_2827_;
}
}
v___jp_2849_:
{
uint64_t v_position_2856_; uint64_t v___x_2857_; uint8_t v___x_2858_; 
v_position_2856_ = lean_uint64_add(v___y_2855_, v___y_2853_);
v___x_2857_ = 172ULL;
v___x_2858_ = lean_uint64_dec_lt(v_position_2856_, v___x_2857_);
if (v___x_2858_ == 0)
{
uint64_t v___x_2859_; uint8_t v___x_2860_; 
v___x_2859_ = 23ULL;
v___x_2860_ = lean_uint64_dec_lt(v___y_2855_, v___x_2859_);
if (v___x_2860_ == 0)
{
uint64_t v___x_2861_; uint8_t v___x_2862_; 
v___x_2861_ = lean_uint64_sub(v___y_2855_, v___x_2859_);
v___x_2862_ = lean_uint64_dec_eq(v___x_2861_, v___y_2852_);
if (v___x_2862_ == 0)
{
uint64_t v___x_2863_; uint8_t v___x_2864_; 
v___x_2863_ = 64ULL;
v___x_2864_ = lean_uint64_dec_lt(v___x_2861_, v___x_2863_);
if (v___x_2864_ == 0)
{
uint8_t v___x_2865_; 
v___x_2865_ = lean_uint64_dec_eq(v___x_2861_, v___x_2863_);
if (v___x_2865_ == 0)
{
v___y_2840_ = v___y_2852_;
v___y_2841_ = v___y_2851_;
v___y_2842_ = v_position_2856_;
v___y_2843_ = v___y_2854_;
v___y_2844_ = v___y_2852_;
goto v___jp_2839_;
}
else
{
uint64_t v___x_2866_; uint8_t v___x_2867_; 
v___x_2866_ = 9223372036854775808ULL;
v___x_2867_ = lean_uint64_dec_lt(v___x_2866_, v___y_2850_);
if (v___x_2867_ == 0)
{
v___y_2840_ = v___y_2852_;
v___y_2841_ = v___y_2851_;
v___y_2842_ = v_position_2856_;
v___y_2843_ = v___y_2854_;
v___y_2844_ = v___y_2852_;
goto v___jp_2839_;
}
else
{
uint64_t v___x_2868_; 
v___x_2868_ = 1ULL;
v___y_2840_ = v___y_2852_;
v___y_2841_ = v___y_2851_;
v___y_2842_ = v_position_2856_;
v___y_2843_ = v___y_2854_;
v___y_2844_ = v___x_2868_;
goto v___jp_2839_;
}
}
}
else
{
uint64_t v_quotient_2869_; uint64_t v___x_2870_; uint64_t v___x_2871_; uint64_t v___x_2872_; uint64_t v_remainder_2873_; uint64_t v___x_2874_; uint64_t v_half_2875_; uint8_t v___x_2876_; 
v_quotient_2869_ = lean_uint64_shift_right(v___y_2850_, v___x_2861_);
v___x_2870_ = 1ULL;
v___x_2871_ = lean_uint64_shift_left(v___x_2870_, v___x_2861_);
v___x_2872_ = lean_uint64_sub(v___x_2871_, v___x_2870_);
v_remainder_2873_ = lean_uint64_land(v___y_2850_, v___x_2872_);
v___x_2874_ = lean_uint64_sub(v___x_2861_, v___x_2870_);
v_half_2875_ = lean_uint64_shift_left(v___x_2870_, v___x_2874_);
v___x_2876_ = lean_uint64_dec_lt(v_remainder_2873_, v_half_2875_);
if (v___x_2876_ == 0)
{
uint8_t v___x_2877_; 
v___x_2877_ = lean_uint64_dec_lt(v_half_2875_, v_remainder_2873_);
if (v___x_2877_ == 0)
{
uint64_t v___x_2878_; uint8_t v___x_2879_; 
v___x_2878_ = lean_uint64_land(v_quotient_2869_, v___x_2870_);
v___x_2879_ = lean_uint64_dec_eq(v___x_2878_, v___y_2852_);
if (v___x_2879_ == 0)
{
uint64_t v___x_2880_; 
v___x_2880_ = lean_uint64_add(v_quotient_2869_, v___x_2870_);
v___y_2840_ = v___y_2852_;
v___y_2841_ = v___y_2851_;
v___y_2842_ = v_position_2856_;
v___y_2843_ = v___y_2854_;
v___y_2844_ = v___x_2880_;
goto v___jp_2839_;
}
else
{
v___y_2840_ = v___y_2852_;
v___y_2841_ = v___y_2851_;
v___y_2842_ = v_position_2856_;
v___y_2843_ = v___y_2854_;
v___y_2844_ = v_quotient_2869_;
goto v___jp_2839_;
}
}
else
{
uint64_t v___x_2881_; 
v___x_2881_ = lean_uint64_add(v_quotient_2869_, v___x_2870_);
v___y_2840_ = v___y_2852_;
v___y_2841_ = v___y_2851_;
v___y_2842_ = v_position_2856_;
v___y_2843_ = v___y_2854_;
v___y_2844_ = v___x_2881_;
goto v___jp_2839_;
}
}
else
{
v___y_2840_ = v___y_2852_;
v___y_2841_ = v___y_2851_;
v___y_2842_ = v_position_2856_;
v___y_2843_ = v___y_2854_;
v___y_2844_ = v_quotient_2869_;
goto v___jp_2839_;
}
}
}
else
{
v___y_2840_ = v___y_2852_;
v___y_2841_ = v___y_2851_;
v___y_2842_ = v_position_2856_;
v___y_2843_ = v___y_2854_;
v___y_2844_ = v___y_2850_;
goto v___jp_2839_;
}
}
else
{
uint64_t v___x_2882_; uint64_t v___x_2883_; 
v___x_2882_ = lean_uint64_sub(v___x_2859_, v___y_2855_);
v___x_2883_ = lean_uint64_shift_left(v___y_2850_, v___x_2882_);
v___y_2840_ = v___y_2852_;
v___y_2841_ = v___y_2851_;
v___y_2842_ = v_position_2856_;
v___y_2843_ = v___y_2854_;
v___y_2844_ = v___x_2883_;
goto v___jp_2839_;
}
}
else
{
uint64_t v___x_2884_; uint8_t v___x_2885_; 
v___x_2884_ = 149ULL;
v___x_2885_ = lean_uint64_dec_lt(v___y_2853_, v___x_2884_);
if (v___x_2885_ == 0)
{
uint64_t v___x_2886_; uint64_t v___x_2887_; 
v___x_2886_ = lean_uint64_sub(v___y_2853_, v___x_2884_);
v___x_2887_ = lean_uint64_shift_left(v___y_2850_, v___x_2886_);
v___y_2060_ = v___y_2851_;
v___y_2061_ = v___y_2852_;
v___y_2062_ = v___y_2854_;
v___y_2063_ = v___x_2887_;
goto v___jp_2059_;
}
else
{
uint64_t v___x_2888_; uint8_t v___x_2889_; 
v___x_2888_ = lean_uint64_sub(v___x_2884_, v___y_2853_);
v___x_2889_ = lean_uint64_dec_eq(v___x_2888_, v___y_2852_);
if (v___x_2889_ == 0)
{
uint64_t v___x_2890_; uint8_t v___x_2891_; 
v___x_2890_ = 64ULL;
v___x_2891_ = lean_uint64_dec_lt(v___x_2888_, v___x_2890_);
if (v___x_2891_ == 0)
{
uint8_t v___x_2892_; 
v___x_2892_ = lean_uint64_dec_eq(v___x_2888_, v___x_2890_);
if (v___x_2892_ == 0)
{
v___y_2060_ = v___y_2851_;
v___y_2061_ = v___y_2852_;
v___y_2062_ = v___y_2854_;
v___y_2063_ = v___y_2852_;
goto v___jp_2059_;
}
else
{
uint64_t v___x_2893_; uint8_t v___x_2894_; 
v___x_2893_ = 9223372036854775808ULL;
v___x_2894_ = lean_uint64_dec_lt(v___x_2893_, v___y_2850_);
if (v___x_2894_ == 0)
{
v___y_2060_ = v___y_2851_;
v___y_2061_ = v___y_2852_;
v___y_2062_ = v___y_2854_;
v___y_2063_ = v___y_2852_;
goto v___jp_2059_;
}
else
{
uint64_t v___x_2895_; 
v___x_2895_ = 1ULL;
v___y_2060_ = v___y_2851_;
v___y_2061_ = v___y_2852_;
v___y_2062_ = v___y_2854_;
v___y_2063_ = v___x_2895_;
goto v___jp_2059_;
}
}
}
else
{
uint64_t v_quotient_2896_; uint64_t v___x_2897_; uint64_t v___x_2898_; uint64_t v___x_2899_; uint64_t v_remainder_2900_; uint64_t v___x_2901_; uint64_t v_half_2902_; uint8_t v___x_2903_; 
v_quotient_2896_ = lean_uint64_shift_right(v___y_2850_, v___x_2888_);
v___x_2897_ = 1ULL;
v___x_2898_ = lean_uint64_shift_left(v___x_2897_, v___x_2888_);
v___x_2899_ = lean_uint64_sub(v___x_2898_, v___x_2897_);
v_remainder_2900_ = lean_uint64_land(v___y_2850_, v___x_2899_);
v___x_2901_ = lean_uint64_sub(v___x_2888_, v___x_2897_);
v_half_2902_ = lean_uint64_shift_left(v___x_2897_, v___x_2901_);
v___x_2903_ = lean_uint64_dec_lt(v_remainder_2900_, v_half_2902_);
if (v___x_2903_ == 0)
{
uint8_t v___x_2904_; 
v___x_2904_ = lean_uint64_dec_lt(v_half_2902_, v_remainder_2900_);
if (v___x_2904_ == 0)
{
uint64_t v___x_2905_; uint8_t v___x_2906_; 
v___x_2905_ = lean_uint64_land(v_quotient_2896_, v___x_2897_);
v___x_2906_ = lean_uint64_dec_eq(v___x_2905_, v___y_2852_);
if (v___x_2906_ == 0)
{
uint64_t v___x_2907_; 
v___x_2907_ = lean_uint64_add(v_quotient_2896_, v___x_2897_);
v___y_2060_ = v___y_2851_;
v___y_2061_ = v___y_2852_;
v___y_2062_ = v___y_2854_;
v___y_2063_ = v___x_2907_;
goto v___jp_2059_;
}
else
{
v___y_2060_ = v___y_2851_;
v___y_2061_ = v___y_2852_;
v___y_2062_ = v___y_2854_;
v___y_2063_ = v_quotient_2896_;
goto v___jp_2059_;
}
}
else
{
uint64_t v___x_2908_; 
v___x_2908_ = lean_uint64_add(v_quotient_2896_, v___x_2897_);
v___y_2060_ = v___y_2851_;
v___y_2061_ = v___y_2852_;
v___y_2062_ = v___y_2854_;
v___y_2063_ = v___x_2908_;
goto v___jp_2059_;
}
}
else
{
v___y_2060_ = v___y_2851_;
v___y_2061_ = v___y_2852_;
v___y_2062_ = v___y_2854_;
v___y_2063_ = v_quotient_2896_;
goto v___jp_2059_;
}
}
}
else
{
v___y_2060_ = v___y_2851_;
v___y_2061_ = v___y_2852_;
v___y_2062_ = v___y_2854_;
v___y_2063_ = v___y_2850_;
goto v___jp_2059_;
}
}
}
}
v___jp_2909_:
{
uint64_t v___x_2917_; uint64_t v___x_2918_; uint8_t v___x_2919_; 
v___x_2917_ = 1ULL;
v___x_2918_ = lean_uint64_shift_right(v___y_2910_, v___x_2917_);
v___x_2919_ = lean_uint64_dec_eq(v___x_2918_, v___y_2913_);
if (v___x_2919_ == 0)
{
uint64_t v___x_2920_; 
v___x_2920_ = lean_uint64_add(v___y_2916_, v___x_2917_);
v___y_2850_ = v___y_2912_;
v___y_2851_ = v___y_2911_;
v___y_2852_ = v___y_2913_;
v___y_2853_ = v___y_2914_;
v___y_2854_ = v___y_2915_;
v___y_2855_ = v___x_2920_;
goto v___jp_2849_;
}
else
{
v___y_2850_ = v___y_2912_;
v___y_2851_ = v___y_2911_;
v___y_2852_ = v___y_2913_;
v___y_2853_ = v___y_2914_;
v___y_2854_ = v___y_2915_;
v___y_2855_ = v___y_2916_;
goto v___jp_2849_;
}
}
v___jp_2921_:
{
uint64_t v___x_2931_; uint8_t v___x_2932_; 
v___x_2931_ = lean_uint64_shift_right(v___y_2923_, v___y_2922_);
v___x_2932_ = lean_uint64_dec_eq(v___x_2931_, v___y_2924_);
if (v___x_2932_ == 0)
{
uint64_t v___x_2933_; 
v___x_2933_ = lean_uint64_add(v___y_2928_, v___y_2922_);
v___y_2910_ = v___y_2930_;
v___y_2911_ = v___y_2926_;
v___y_2912_ = v___y_2925_;
v___y_2913_ = v___y_2924_;
v___y_2914_ = v___y_2927_;
v___y_2915_ = v___y_2929_;
v___y_2916_ = v___x_2933_;
goto v___jp_2909_;
}
else
{
v___y_2910_ = v___y_2930_;
v___y_2911_ = v___y_2926_;
v___y_2912_ = v___y_2925_;
v___y_2913_ = v___y_2924_;
v___y_2914_ = v___y_2927_;
v___y_2915_ = v___y_2929_;
v___y_2916_ = v___y_2928_;
goto v___jp_2909_;
}
}
v___jp_2934_:
{
uint64_t v___x_2942_; uint64_t v___x_2943_; uint8_t v___x_2944_; 
v___x_2942_ = 2ULL;
v___x_2943_ = lean_uint64_shift_right(v___y_2935_, v___x_2942_);
v___x_2944_ = lean_uint64_dec_eq(v___x_2943_, v___y_2938_);
if (v___x_2944_ == 0)
{
v___y_2922_ = v___x_2942_;
v___y_2923_ = v___y_2935_;
v___y_2924_ = v___y_2938_;
v___y_2925_ = v___y_2937_;
v___y_2926_ = v___y_2936_;
v___y_2927_ = v___y_2939_;
v___y_2928_ = v___y_2941_;
v___y_2929_ = v___y_2940_;
v___y_2930_ = v___x_2943_;
goto v___jp_2921_;
}
else
{
v___y_2922_ = v___x_2942_;
v___y_2923_ = v___y_2935_;
v___y_2924_ = v___y_2938_;
v___y_2925_ = v___y_2937_;
v___y_2926_ = v___y_2936_;
v___y_2927_ = v___y_2939_;
v___y_2928_ = v___y_2941_;
v___y_2929_ = v___y_2940_;
v___y_2930_ = v___y_2935_;
goto v___jp_2921_;
}
}
v___jp_2945_:
{
uint64_t v___x_2955_; uint8_t v___x_2956_; 
v___x_2955_ = lean_uint64_shift_right(v___y_2952_, v___y_2947_);
v___x_2956_ = lean_uint64_dec_eq(v___x_2955_, v___y_2948_);
if (v___x_2956_ == 0)
{
uint64_t v___x_2957_; 
v___x_2957_ = lean_uint64_add(v___y_2946_, v___y_2947_);
v___y_2935_ = v___y_2954_;
v___y_2936_ = v___y_2950_;
v___y_2937_ = v___y_2949_;
v___y_2938_ = v___y_2948_;
v___y_2939_ = v___y_2951_;
v___y_2940_ = v___y_2953_;
v___y_2941_ = v___x_2957_;
goto v___jp_2934_;
}
else
{
v___y_2935_ = v___y_2954_;
v___y_2936_ = v___y_2950_;
v___y_2937_ = v___y_2949_;
v___y_2938_ = v___y_2948_;
v___y_2939_ = v___y_2951_;
v___y_2940_ = v___y_2953_;
v___y_2941_ = v___y_2946_;
goto v___jp_2934_;
}
}
v___jp_2958_:
{
uint64_t v___x_2966_; uint64_t v___x_2967_; uint8_t v___x_2968_; 
v___x_2966_ = 4ULL;
v___x_2967_ = lean_uint64_shift_right(v___y_2963_, v___x_2966_);
v___x_2968_ = lean_uint64_dec_eq(v___x_2967_, v___y_2961_);
if (v___x_2968_ == 0)
{
v___y_2946_ = v___y_2965_;
v___y_2947_ = v___x_2966_;
v___y_2948_ = v___y_2961_;
v___y_2949_ = v___y_2960_;
v___y_2950_ = v___y_2959_;
v___y_2951_ = v___y_2962_;
v___y_2952_ = v___y_2963_;
v___y_2953_ = v___y_2964_;
v___y_2954_ = v___x_2967_;
goto v___jp_2945_;
}
else
{
v___y_2946_ = v___y_2965_;
v___y_2947_ = v___x_2966_;
v___y_2948_ = v___y_2961_;
v___y_2949_ = v___y_2960_;
v___y_2950_ = v___y_2959_;
v___y_2951_ = v___y_2962_;
v___y_2952_ = v___y_2963_;
v___y_2953_ = v___y_2964_;
v___y_2954_ = v___y_2963_;
goto v___jp_2945_;
}
}
v___jp_2969_:
{
uint64_t v___x_2979_; uint8_t v___x_2980_; 
v___x_2979_ = lean_uint64_shift_right(v___y_2970_, v___y_2971_);
v___x_2980_ = lean_uint64_dec_eq(v___x_2979_, v___y_2972_);
if (v___x_2980_ == 0)
{
uint64_t v___x_2981_; 
v___x_2981_ = lean_uint64_add(v___y_2976_, v___y_2971_);
v___y_2959_ = v___y_2974_;
v___y_2960_ = v___y_2973_;
v___y_2961_ = v___y_2972_;
v___y_2962_ = v___y_2975_;
v___y_2963_ = v___y_2978_;
v___y_2964_ = v___y_2977_;
v___y_2965_ = v___x_2981_;
goto v___jp_2958_;
}
else
{
v___y_2959_ = v___y_2974_;
v___y_2960_ = v___y_2973_;
v___y_2961_ = v___y_2972_;
v___y_2962_ = v___y_2975_;
v___y_2963_ = v___y_2978_;
v___y_2964_ = v___y_2977_;
v___y_2965_ = v___y_2976_;
goto v___jp_2958_;
}
}
v___jp_2982_:
{
uint64_t v___x_2990_; uint64_t v___x_2991_; uint8_t v___x_2992_; 
v___x_2990_ = 8ULL;
v___x_2991_ = lean_uint64_shift_right(v___y_2983_, v___x_2990_);
v___x_2992_ = lean_uint64_dec_eq(v___x_2991_, v___y_2986_);
if (v___x_2992_ == 0)
{
v___y_2970_ = v___y_2983_;
v___y_2971_ = v___x_2990_;
v___y_2972_ = v___y_2986_;
v___y_2973_ = v___y_2985_;
v___y_2974_ = v___y_2984_;
v___y_2975_ = v___y_2987_;
v___y_2976_ = v___y_2989_;
v___y_2977_ = v___y_2988_;
v___y_2978_ = v___x_2991_;
goto v___jp_2969_;
}
else
{
v___y_2970_ = v___y_2983_;
v___y_2971_ = v___x_2990_;
v___y_2972_ = v___y_2986_;
v___y_2973_ = v___y_2985_;
v___y_2974_ = v___y_2984_;
v___y_2975_ = v___y_2987_;
v___y_2976_ = v___y_2989_;
v___y_2977_ = v___y_2988_;
v___y_2978_ = v___y_2983_;
goto v___jp_2969_;
}
}
v___jp_2993_:
{
uint64_t v___x_3003_; uint8_t v___x_3004_; 
v___x_3003_ = lean_uint64_shift_right(v___y_2994_, v___y_2996_);
v___x_3004_ = lean_uint64_dec_eq(v___x_3003_, v___y_2997_);
if (v___x_3004_ == 0)
{
uint64_t v___x_3005_; 
v___x_3005_ = lean_uint64_add(v___y_2995_, v___y_2996_);
v___y_2983_ = v___y_3002_;
v___y_2984_ = v___y_2999_;
v___y_2985_ = v___y_2998_;
v___y_2986_ = v___y_2997_;
v___y_2987_ = v___y_3000_;
v___y_2988_ = v___y_3001_;
v___y_2989_ = v___x_3005_;
goto v___jp_2982_;
}
else
{
v___y_2983_ = v___y_3002_;
v___y_2984_ = v___y_2999_;
v___y_2985_ = v___y_2998_;
v___y_2986_ = v___y_2997_;
v___y_2987_ = v___y_3000_;
v___y_2988_ = v___y_3001_;
v___y_2989_ = v___y_2995_;
goto v___jp_2982_;
}
}
v___jp_3006_:
{
uint64_t v___x_3014_; uint64_t v___x_3015_; uint8_t v___x_3016_; 
v___x_3014_ = 16ULL;
v___x_3015_ = lean_uint64_shift_right(v___y_3007_, v___x_3014_);
v___x_3016_ = lean_uint64_dec_eq(v___x_3015_, v___y_3010_);
if (v___x_3016_ == 0)
{
v___y_2994_ = v___y_3007_;
v___y_2995_ = v___y_3013_;
v___y_2996_ = v___x_3014_;
v___y_2997_ = v___y_3010_;
v___y_2998_ = v___y_3009_;
v___y_2999_ = v___y_3008_;
v___y_3000_ = v___y_3011_;
v___y_3001_ = v___y_3012_;
v___y_3002_ = v___x_3015_;
goto v___jp_2993_;
}
else
{
v___y_2994_ = v___y_3007_;
v___y_2995_ = v___y_3013_;
v___y_2996_ = v___x_3014_;
v___y_2997_ = v___y_3010_;
v___y_2998_ = v___y_3009_;
v___y_2999_ = v___y_3008_;
v___y_3000_ = v___y_3011_;
v___y_3001_ = v___y_3012_;
v___y_3002_ = v___y_3007_;
goto v___jp_2993_;
}
}
v___jp_3017_:
{
uint64_t v___x_3025_; uint8_t v___x_3026_; 
v___x_3025_ = lean_uint64_shift_right(v___y_3020_, v___y_3018_);
v___x_3026_ = lean_uint64_dec_eq(v___x_3025_, v___y_3019_);
if (v___x_3026_ == 0)
{
v___y_3007_ = v___y_3024_;
v___y_3008_ = v___y_3021_;
v___y_3009_ = v___y_3020_;
v___y_3010_ = v___y_3019_;
v___y_3011_ = v___y_3022_;
v___y_3012_ = v___y_3023_;
v___y_3013_ = v___y_3018_;
goto v___jp_3006_;
}
else
{
v___y_3007_ = v___y_3024_;
v___y_3008_ = v___y_3021_;
v___y_3009_ = v___y_3020_;
v___y_3010_ = v___y_3019_;
v___y_3011_ = v___y_3022_;
v___y_3012_ = v___y_3023_;
v___y_3013_ = v___y_3019_;
goto v___jp_3006_;
}
}
v___jp_3027_:
{
uint64_t v___x_3032_; uint8_t v___x_3033_; 
v___x_3032_ = 0ULL;
v___x_3033_ = lean_uint64_dec_eq(v___y_3028_, v___x_3032_);
if (v___x_3033_ == 0)
{
uint64_t v___x_3034_; uint64_t v___x_3035_; uint8_t v___x_3036_; 
v___x_3034_ = 32ULL;
v___x_3035_ = lean_uint64_shift_right(v___y_3028_, v___x_3034_);
v___x_3036_ = lean_uint64_dec_eq(v___x_3035_, v___x_3032_);
if (v___x_3036_ == 0)
{
v___y_3018_ = v___x_3034_;
v___y_3019_ = v___x_3032_;
v___y_3020_ = v___y_3028_;
v___y_3021_ = v___y_3029_;
v___y_3022_ = v___y_3030_;
v___y_3023_ = v___y_3031_;
v___y_3024_ = v___x_3035_;
goto v___jp_3017_;
}
else
{
v___y_3018_ = v___x_3034_;
v___y_3019_ = v___x_3032_;
v___y_3020_ = v___y_3028_;
v___y_3021_ = v___y_3029_;
v___y_3022_ = v___y_3030_;
v___y_3023_ = v___y_3031_;
v___y_3024_ = v___y_3028_;
goto v___jp_3017_;
}
}
else
{
if (v___y_3031_ == 0)
{
uint32_t v___x_3037_; 
v___x_3037_ = 0;
return v___x_3037_;
}
else
{
uint32_t v___x_3038_; 
v___x_3038_ = 2147483648;
return v___x_3038_;
}
}
}
v___jp_3039_:
{
uint64_t v___x_3046_; uint64_t v___x_3047_; uint64_t v___x_3048_; uint8_t v___x_3049_; 
v___x_3046_ = lean_uint64_mul(v___y_3044_, v___y_3040_);
v___x_3047_ = lean_uint64_add(v___y_3042_, v___y_3045_);
v___x_3048_ = 281474976710656ULL;
v___x_3049_ = lean_uint64_dec_lt(v___x_3046_, v___x_3048_);
if (v___x_3049_ == 0)
{
v___y_3028_ = v___x_3046_;
v___y_3029_ = v___y_3041_;
v___y_3030_ = v___x_3047_;
v___y_3031_ = v___y_3043_;
goto v___jp_3027_;
}
else
{
uint64_t v___x_3050_; uint8_t v___x_3051_; 
v___x_3050_ = 123ULL;
v___x_3051_ = lean_uint64_dec_le(v___x_3047_, v___x_3050_);
if (v___x_3051_ == 0)
{
v___y_3028_ = v___x_3046_;
v___y_3029_ = v___y_3041_;
v___y_3030_ = v___x_3047_;
v___y_3031_ = v___y_3043_;
goto v___jp_3027_;
}
else
{
uint64_t v___x_3052_; uint8_t v___x_3053_; 
v___x_3052_ = 0ULL;
v___x_3053_ = lean_uint64_dec_eq(v___x_3046_, v___x_3052_);
if (v___x_3053_ == 0)
{
uint64_t v___x_3054_; uint64_t v___x_3055_; uint8_t v___x_3056_; 
v___x_3054_ = 149ULL;
v___x_3055_ = lean_uint64_sub(v___x_3054_, v___x_3047_);
v___x_3056_ = lean_uint64_dec_eq(v___x_3055_, v___x_3052_);
if (v___x_3056_ == 0)
{
uint64_t v___x_3057_; uint8_t v___x_3058_; 
v___x_3057_ = 64ULL;
v___x_3058_ = lean_uint64_dec_lt(v___x_3055_, v___x_3057_);
if (v___x_3058_ == 0)
{
uint8_t v___x_3059_; 
v___x_3059_ = lean_uint64_dec_eq(v___x_3055_, v___x_3057_);
if (v___x_3059_ == 0)
{
v___y_2081_ = v___y_3041_;
v___y_2082_ = v___x_3052_;
v___y_2083_ = v___y_3043_;
v___y_2084_ = v___x_3052_;
goto v___jp_2080_;
}
else
{
uint64_t v___x_3060_; uint8_t v___x_3061_; 
v___x_3060_ = 9223372036854775808ULL;
v___x_3061_ = lean_uint64_dec_lt(v___x_3060_, v___x_3046_);
if (v___x_3061_ == 0)
{
v___y_2081_ = v___y_3041_;
v___y_2082_ = v___x_3052_;
v___y_2083_ = v___y_3043_;
v___y_2084_ = v___x_3052_;
goto v___jp_2080_;
}
else
{
uint64_t v___x_3062_; 
v___x_3062_ = 1ULL;
v___y_2081_ = v___y_3041_;
v___y_2082_ = v___x_3052_;
v___y_2083_ = v___y_3043_;
v___y_2084_ = v___x_3062_;
goto v___jp_2080_;
}
}
}
else
{
uint64_t v_quotient_3063_; uint64_t v___x_3064_; uint64_t v___x_3065_; uint64_t v___x_3066_; uint64_t v_remainder_3067_; uint64_t v___x_3068_; uint64_t v_half_3069_; uint8_t v___x_3070_; 
v_quotient_3063_ = lean_uint64_shift_right(v___x_3046_, v___x_3055_);
v___x_3064_ = 1ULL;
v___x_3065_ = lean_uint64_shift_left(v___x_3064_, v___x_3055_);
v___x_3066_ = lean_uint64_sub(v___x_3065_, v___x_3064_);
v_remainder_3067_ = lean_uint64_land(v___x_3046_, v___x_3066_);
v___x_3068_ = lean_uint64_sub(v___x_3055_, v___x_3064_);
v_half_3069_ = lean_uint64_shift_left(v___x_3064_, v___x_3068_);
v___x_3070_ = lean_uint64_dec_lt(v_remainder_3067_, v_half_3069_);
if (v___x_3070_ == 0)
{
uint8_t v___x_3071_; 
v___x_3071_ = lean_uint64_dec_lt(v_half_3069_, v_remainder_3067_);
if (v___x_3071_ == 0)
{
uint64_t v___x_3072_; uint8_t v___x_3073_; 
v___x_3072_ = lean_uint64_land(v_quotient_3063_, v___x_3064_);
v___x_3073_ = lean_uint64_dec_eq(v___x_3072_, v___x_3052_);
if (v___x_3073_ == 0)
{
uint64_t v___x_3074_; 
v___x_3074_ = lean_uint64_add(v_quotient_3063_, v___x_3064_);
v___y_2081_ = v___y_3041_;
v___y_2082_ = v___x_3052_;
v___y_2083_ = v___y_3043_;
v___y_2084_ = v___x_3074_;
goto v___jp_2080_;
}
else
{
v___y_2081_ = v___y_3041_;
v___y_2082_ = v___x_3052_;
v___y_2083_ = v___y_3043_;
v___y_2084_ = v_quotient_3063_;
goto v___jp_2080_;
}
}
else
{
uint64_t v___x_3075_; 
v___x_3075_ = lean_uint64_add(v_quotient_3063_, v___x_3064_);
v___y_2081_ = v___y_3041_;
v___y_2082_ = v___x_3052_;
v___y_2083_ = v___y_3043_;
v___y_2084_ = v___x_3075_;
goto v___jp_2080_;
}
}
else
{
v___y_2081_ = v___y_3041_;
v___y_2082_ = v___x_3052_;
v___y_2083_ = v___y_3043_;
v___y_2084_ = v_quotient_3063_;
goto v___jp_2080_;
}
}
}
else
{
v___y_2081_ = v___y_3041_;
v___y_2082_ = v___x_3052_;
v___y_2083_ = v___y_3043_;
v___y_2084_ = v___x_3046_;
goto v___jp_2080_;
}
}
else
{
if (v___y_3043_ == 0)
{
uint32_t v___x_3076_; 
v___x_3076_ = 0;
return v___x_3076_;
}
else
{
uint32_t v___x_3077_; 
v___x_3077_ = 2147483648;
return v___x_3077_;
}
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___x_3364_, lean_object* v___y_3365_, lean_object* v___y_3366_){
_start:
{
uint8_t v___x_10742__boxed_3367_; uint32_t v___y_10743__boxed_3368_; uint32_t v___y_10744__boxed_3369_; uint32_t v_res_3370_; lean_object* v_r_3371_; 
v___x_10742__boxed_3367_ = lean_unbox(v___x_3364_);
v___y_10743__boxed_3368_ = lean_unbox_uint32(v___y_3365_);
lean_dec(v___y_3365_);
v___y_10744__boxed_3369_ = lean_unbox_uint32(v___y_3366_);
lean_dec(v___y_3366_);
v_res_3370_ = lp_competition_main___lam__1(v___x_10742__boxed_3367_, v___y_10743__boxed_3368_, v___y_10744__boxed_3369_);
v_r_3371_ = lean_box_uint32(v_res_3370_);
return v_r_3371_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint8_t v___x_3372_, uint32_t v___y_3373_, uint32_t v___y_3374_){
_start:
{
uint8_t v___y_3376_; uint8_t v___y_3392_; uint8_t v___y_3406_; uint8_t v___y_3423_; float v___y_3430_; float v___y_3431_; float v___y_3445_; uint8_t v___y_3446_; float v___y_3461_; uint32_t v___y_3471_; uint32_t v___y_3475_; uint32_t v___y_3479_; uint32_t v___y_3480_; uint32_t v___y_3481_; uint64_t v___y_3485_; uint8_t v___y_3486_; uint32_t v___y_3487_; uint64_t v___y_3488_; uint32_t v___y_3500_; uint32_t v___y_3501_; uint32_t v___y_3502_; uint8_t v___y_3506_; uint64_t v___y_3507_; uint32_t v___y_3508_; uint64_t v___y_3509_; uint32_t v___x_3520_; uint32_t v___x_3521_; uint8_t v___y_3523_; uint32_t v___x_3535_; uint32_t v___y_3537_; uint32_t v___y_3538_; uint32_t v___y_3539_; uint32_t v___y_3540_; uint8_t v___y_3547_; uint32_t v___y_3548_; uint32_t v___y_3549_; uint32_t v___y_3550_; uint64_t v___y_3554_; uint8_t v___y_3555_; uint64_t v___y_3556_; uint32_t v___y_3557_; uint64_t v___y_3558_; uint64_t v___y_3568_; uint8_t v___y_3569_; uint64_t v___y_3570_; uint8_t v___y_3571_; uint32_t v___y_3572_; uint64_t v___y_3573_; uint64_t v___y_3580_; uint64_t v___y_3581_; uint8_t v___y_3582_; uint32_t v___y_3583_; uint64_t v___y_3584_; uint64_t v___y_3590_; uint8_t v___y_3591_; uint64_t v___y_3592_; uint64_t v___y_3593_; uint32_t v___y_3594_; uint64_t v___y_3595_; uint64_t v___y_3650_; uint8_t v___y_3651_; uint64_t v___y_3652_; uint64_t v___y_3653_; uint64_t v___y_3654_; uint32_t v___y_3655_; uint64_t v___y_3656_; uint64_t v___y_3662_; uint64_t v___y_3663_; uint8_t v___y_3664_; uint64_t v___y_3665_; uint64_t v___y_3666_; uint64_t v___y_3667_; uint64_t v___y_3668_; uint32_t v___y_3669_; uint64_t v___y_3670_; uint64_t v___y_3675_; uint8_t v___y_3676_; uint64_t v___y_3677_; uint64_t v___y_3678_; uint64_t v___y_3679_; uint32_t v___y_3680_; uint64_t v___y_3681_; uint64_t v___y_3686_; uint64_t v___y_3687_; uint8_t v___y_3688_; uint64_t v___y_3689_; uint64_t v___y_3690_; uint64_t v___y_3691_; uint64_t v___y_3692_; uint32_t v___y_3693_; uint64_t v___y_3694_; uint64_t v___y_3699_; uint8_t v___y_3700_; uint64_t v___y_3701_; uint64_t v___y_3702_; uint64_t v___y_3703_; uint32_t v___y_3704_; uint64_t v___y_3705_; uint64_t v___y_3710_; uint8_t v___y_3711_; uint64_t v___y_3712_; uint64_t v___y_3713_; uint64_t v___y_3714_; uint64_t v___y_3715_; uint64_t v___y_3716_; uint32_t v___y_3717_; uint64_t v___y_3718_; uint64_t v___y_3723_; uint8_t v___y_3724_; uint64_t v___y_3725_; uint64_t v___y_3726_; uint64_t v___y_3727_; uint32_t v___y_3728_; uint64_t v___y_3729_; uint64_t v___y_3734_; uint64_t v___y_3735_; uint8_t v___y_3736_; uint64_t v___y_3737_; uint64_t v___y_3738_; uint64_t v___y_3739_; uint64_t v___y_3740_; uint32_t v___y_3741_; uint64_t v___y_3742_; uint64_t v___y_3747_; uint8_t v___y_3748_; uint64_t v___y_3749_; uint64_t v___y_3750_; uint64_t v___y_3751_; uint32_t v___y_3752_; uint64_t v___y_3753_; uint64_t v___y_3758_; uint8_t v___y_3759_; uint64_t v___y_3760_; uint64_t v___y_3761_; uint64_t v___y_3762_; uint32_t v___y_3763_; uint64_t v___y_3764_; uint8_t v___y_3768_; uint64_t v___y_3769_; uint64_t v___y_3770_; uint32_t v___y_3771_; uint8_t v___y_3780_; uint64_t v___y_3781_; uint64_t v___y_3782_; uint64_t v___y_3783_; uint32_t v___y_3784_; uint64_t v___y_3785_; uint32_t v_ex_3818_; uint32_t v___x_3819_; uint32_t v_ey_3820_; uint8_t v___y_3822_; uint64_t v___y_3823_; uint64_t v___y_3824_; uint32_t v___y_3825_; uint64_t v___y_3826_; uint8_t v___y_3833_; uint64_t v___y_3834_; uint32_t v___y_3835_; uint64_t v___y_3836_; uint8_t v___y_3843_; uint32_t v___y_3844_; uint32_t v___y_3845_; uint64_t v___y_3846_; uint8_t v___y_3854_; uint8_t v___y_3865_; uint8_t v___y_3866_; uint32_t v___x_3867_; uint32_t v___x_3868_; uint8_t v___x_3869_; uint8_t v___y_3871_; uint8_t v___y_3872_; uint8_t v___y_3873_; uint8_t v___y_3875_; uint8_t v___y_3876_; uint8_t v___y_3882_; 
v___x_3520_ = 23;
v___x_3521_ = lean_uint32_shift_right(v___y_3373_, v___x_3520_);
v___x_3535_ = 255;
v_ex_3818_ = lean_uint32_land(v___x_3521_, v___x_3535_);
v___x_3819_ = lean_uint32_shift_right(v___y_3374_, v___x_3520_);
v_ey_3820_ = lean_uint32_land(v___x_3819_, v___x_3535_);
v___x_3867_ = lean_uint32_add(v_ex_3818_, v_ey_3820_);
v___x_3868_ = 128;
v___x_3869_ = lean_uint32_dec_lt(v___x_3867_, v___x_3868_);
if (v___x_3869_ == 0)
{
uint32_t v___x_3891_; uint32_t v_a_3892_; uint32_t v___x_3893_; uint32_t v___x_3894_; uint32_t v___x_3895_; uint8_t v___x_3896_; 
v___x_3891_ = 2147483647;
v_a_3892_ = lean_uint32_land(v___y_3373_, v___x_3891_);
v___x_3893_ = 201326591;
v___x_3894_ = 1;
v___x_3895_ = lean_uint32_sub(v_a_3892_, v___x_3894_);
v___x_3896_ = lean_uint32_dec_le(v___x_3893_, v___x_3895_);
if (v___x_3896_ == 0)
{
v___y_3523_ = v___x_3896_;
goto v___jp_3522_;
}
else
{
uint32_t v___x_3897_; uint8_t v___x_3898_; 
v___x_3897_ = 2139095040;
v___x_3898_ = lean_uint32_dec_lt(v_a_3892_, v___x_3897_);
v___y_3523_ = v___x_3898_;
goto v___jp_3522_;
}
}
else
{
uint32_t v___x_3899_; uint32_t v___x_3900_; uint32_t v___x_3901_; uint8_t v___x_3902_; 
v___x_3899_ = 4278190080;
v___x_3900_ = 1;
v___x_3901_ = lean_uint32_shift_left(v___y_3373_, v___x_3900_);
v___x_3902_ = lean_uint32_dec_le(v___x_3899_, v___x_3901_);
if (v___x_3902_ == 0)
{
uint32_t v___x_3903_; uint8_t v___x_3904_; 
v___x_3903_ = lean_uint32_shift_left(v___y_3374_, v___x_3900_);
v___x_3904_ = lean_uint32_dec_le(v___x_3899_, v___x_3903_);
v___y_3882_ = v___x_3904_;
goto v___jp_3881_;
}
else
{
v___y_3882_ = v___x_3902_;
goto v___jp_3881_;
}
}
v___jp_3375_:
{
if (v___y_3376_ == 0)
{
uint32_t v___x_3377_; 
v___x_3377_ = lp_competition_Submission_FastMul_mul(v___y_3373_, v___y_3374_);
return v___x_3377_;
}
else
{
uint32_t v___x_3378_; uint32_t v___x_3379_; 
v___x_3378_ = 4194304;
v___x_3379_ = lean_uint32_lor(v___y_3374_, v___x_3378_);
return v___x_3379_;
}
}
v___jp_3380_:
{
uint32_t v___x_3381_; uint32_t v___x_3382_; uint32_t v___x_3383_; uint32_t v___x_3384_; uint8_t v___x_3385_; 
v___x_3381_ = 23;
v___x_3382_ = lean_uint32_shift_right(v___y_3374_, v___x_3381_);
v___x_3383_ = 255;
v___x_3384_ = lean_uint32_land(v___x_3382_, v___x_3383_);
v___x_3385_ = lean_uint32_dec_eq(v___x_3384_, v___x_3383_);
if (v___x_3385_ == 0)
{
v___y_3376_ = v___x_3385_;
goto v___jp_3375_;
}
else
{
uint32_t v___x_3386_; uint32_t v___x_3387_; uint32_t v___x_3388_; uint8_t v___x_3389_; 
v___x_3386_ = 8388607;
v___x_3387_ = lean_uint32_land(v___y_3374_, v___x_3386_);
v___x_3388_ = 0;
v___x_3389_ = lean_uint32_dec_eq(v___x_3387_, v___x_3388_);
if (v___x_3389_ == 0)
{
v___y_3376_ = v___x_3385_;
goto v___jp_3375_;
}
else
{
uint32_t v___x_3390_; 
v___x_3390_ = lp_competition_Submission_FastMul_mul(v___y_3373_, v___y_3374_);
return v___x_3390_;
}
}
}
v___jp_3391_:
{
if (v___y_3392_ == 0)
{
goto v___jp_3380_;
}
else
{
uint32_t v___x_3393_; uint32_t v___x_3394_; 
v___x_3393_ = 4194304;
v___x_3394_ = lean_uint32_lor(v___y_3373_, v___x_3393_);
return v___x_3394_;
}
}
v___jp_3395_:
{
uint32_t v___x_3396_; uint32_t v___x_3397_; uint32_t v___x_3398_; uint32_t v___x_3399_; uint8_t v___x_3400_; 
v___x_3396_ = 23;
v___x_3397_ = lean_uint32_shift_right(v___y_3373_, v___x_3396_);
v___x_3398_ = 255;
v___x_3399_ = lean_uint32_land(v___x_3397_, v___x_3398_);
v___x_3400_ = lean_uint32_dec_eq(v___x_3399_, v___x_3398_);
if (v___x_3400_ == 0)
{
v___y_3392_ = v___x_3400_;
goto v___jp_3391_;
}
else
{
uint32_t v___x_3401_; uint32_t v___x_3402_; uint32_t v___x_3403_; uint8_t v___x_3404_; 
v___x_3401_ = 8388607;
v___x_3402_ = lean_uint32_land(v___y_3373_, v___x_3401_);
v___x_3403_ = 0;
v___x_3404_ = lean_uint32_dec_eq(v___x_3402_, v___x_3403_);
if (v___x_3404_ == 0)
{
v___y_3392_ = v___x_3400_;
goto v___jp_3391_;
}
else
{
goto v___jp_3380_;
}
}
}
v___jp_3405_:
{
if (v___y_3406_ == 0)
{
goto v___jp_3395_;
}
else
{
uint32_t v___x_3407_; uint32_t v___x_3408_; uint32_t v___x_3409_; uint8_t v___x_3410_; 
v___x_3407_ = 4194304;
v___x_3408_ = lean_uint32_land(v___y_3374_, v___x_3407_);
v___x_3409_ = 0;
v___x_3410_ = lean_uint32_dec_eq(v___x_3408_, v___x_3409_);
if (v___x_3410_ == 0)
{
goto v___jp_3395_;
}
else
{
uint32_t v___x_3411_; 
v___x_3411_ = lean_uint32_lor(v___y_3374_, v___x_3407_);
return v___x_3411_;
}
}
}
v___jp_3412_:
{
uint32_t v___x_3413_; uint32_t v___x_3414_; uint32_t v___x_3415_; uint32_t v___x_3416_; uint8_t v___x_3417_; 
v___x_3413_ = 23;
v___x_3414_ = lean_uint32_shift_right(v___y_3374_, v___x_3413_);
v___x_3415_ = 255;
v___x_3416_ = lean_uint32_land(v___x_3414_, v___x_3415_);
v___x_3417_ = lean_uint32_dec_eq(v___x_3416_, v___x_3415_);
if (v___x_3417_ == 0)
{
v___y_3406_ = v___x_3417_;
goto v___jp_3405_;
}
else
{
uint32_t v___x_3418_; uint32_t v___x_3419_; uint32_t v___x_3420_; uint8_t v___x_3421_; 
v___x_3418_ = 8388607;
v___x_3419_ = lean_uint32_land(v___y_3374_, v___x_3418_);
v___x_3420_ = 0;
v___x_3421_ = lean_uint32_dec_eq(v___x_3419_, v___x_3420_);
if (v___x_3421_ == 0)
{
v___y_3406_ = v___x_3417_;
goto v___jp_3405_;
}
else
{
goto v___jp_3395_;
}
}
}
v___jp_3422_:
{
if (v___y_3423_ == 0)
{
goto v___jp_3412_;
}
else
{
uint32_t v___x_3424_; uint32_t v___x_3425_; uint32_t v___x_3426_; uint8_t v___x_3427_; 
v___x_3424_ = 4194304;
v___x_3425_ = lean_uint32_land(v___y_3373_, v___x_3424_);
v___x_3426_ = 0;
v___x_3427_ = lean_uint32_dec_eq(v___x_3425_, v___x_3426_);
if (v___x_3427_ == 0)
{
goto v___jp_3412_;
}
else
{
uint32_t v___x_3428_; 
v___x_3428_ = lean_uint32_lor(v___y_3373_, v___x_3424_);
return v___x_3428_;
}
}
}
v___jp_3429_:
{
float v_result_3432_; uint8_t v___x_3433_; 
v_result_3432_ = lean_float32_mul(v___y_3430_, v___y_3431_);
v___x_3433_ = lean_float32_beq(v_result_3432_, v_result_3432_);
if (v___x_3433_ == 0)
{
uint32_t v___x_3434_; uint32_t v___x_3435_; uint32_t v___x_3436_; uint32_t v___x_3437_; uint8_t v___x_3438_; 
v___x_3434_ = 23;
v___x_3435_ = lean_uint32_shift_right(v___y_3373_, v___x_3434_);
v___x_3436_ = 255;
v___x_3437_ = lean_uint32_land(v___x_3435_, v___x_3436_);
v___x_3438_ = lean_uint32_dec_eq(v___x_3437_, v___x_3436_);
if (v___x_3438_ == 0)
{
v___y_3423_ = v___x_3438_;
goto v___jp_3422_;
}
else
{
uint32_t v___x_3439_; uint32_t v___x_3440_; uint32_t v___x_3441_; uint8_t v___x_3442_; 
v___x_3439_ = 8388607;
v___x_3440_ = lean_uint32_land(v___y_3373_, v___x_3439_);
v___x_3441_ = 0;
v___x_3442_ = lean_uint32_dec_eq(v___x_3440_, v___x_3441_);
if (v___x_3442_ == 0)
{
v___y_3423_ = v___x_3438_;
goto v___jp_3422_;
}
else
{
goto v___jp_3412_;
}
}
}
else
{
uint32_t v___x_3443_; 
v___x_3443_ = lean_float32_to_bits(v_result_3432_);
return v___x_3443_;
}
}
v___jp_3444_:
{
if (v___y_3446_ == 0)
{
float v___x_3447_; 
v___x_3447_ = lean_float32_of_bits(v___y_3374_);
v___y_3430_ = v___y_3445_;
v___y_3431_ = v___x_3447_;
goto v___jp_3429_;
}
else
{
uint32_t v___x_3448_; uint32_t v___x_3449_; uint32_t v___x_3450_; uint32_t v___x_3451_; float v___x_3452_; lean_object* v___x_3453_; uint32_t v___x_3454_; uint32_t v___x_3455_; lean_object* v___x_3456_; lean_object* v___x_3457_; float v___x_3458_; float v___x_3459_; 
v___x_3448_ = 8388607;
v___x_3449_ = lean_uint32_land(v___y_3374_, v___x_3448_);
v___x_3450_ = 8388608;
v___x_3451_ = lean_uint32_lor(v___x_3449_, v___x_3450_);
v___x_3452_ = lean_uint32_to_float32(v___x_3451_);
v___x_3453_ = lp_competition_R2W01b_scaleTable;
v___x_3454_ = 23;
v___x_3455_ = lean_uint32_shift_right(v___y_3374_, v___x_3454_);
v___x_3456_ = lean_uint32_to_nat(v___x_3455_);
v___x_3457_ = lean_array_fget_borrowed(v___x_3453_, v___x_3456_);
lean_dec(v___x_3456_);
v___x_3458_ = lean_unbox_float32(v___x_3457_);
v___x_3459_ = lean_float32_mul(v___x_3452_, v___x_3458_);
v___y_3430_ = v___y_3445_;
v___y_3431_ = v___x_3459_;
goto v___jp_3429_;
}
}
v___jp_3460_:
{
uint32_t v___x_3462_; uint32_t v_a_3463_; uint32_t v___x_3464_; uint32_t v___x_3465_; uint32_t v___x_3466_; uint8_t v___x_3467_; 
v___x_3462_ = 2147483647;
v_a_3463_ = lean_uint32_land(v___y_3374_, v___x_3462_);
v___x_3464_ = 201326591;
v___x_3465_ = 1;
v___x_3466_ = lean_uint32_sub(v_a_3463_, v___x_3465_);
v___x_3467_ = lean_uint32_dec_le(v___x_3464_, v___x_3466_);
if (v___x_3467_ == 0)
{
v___y_3445_ = v___y_3461_;
v___y_3446_ = v___x_3467_;
goto v___jp_3444_;
}
else
{
uint32_t v___x_3468_; uint8_t v___x_3469_; 
v___x_3468_ = 2139095040;
v___x_3469_ = lean_uint32_dec_lt(v_a_3463_, v___x_3468_);
v___y_3445_ = v___y_3461_;
v___y_3446_ = v___x_3469_;
goto v___jp_3444_;
}
}
v___jp_3470_:
{
uint32_t v___x_3472_; uint32_t v___x_3473_; 
v___x_3472_ = 8388608;
v___x_3473_ = lean_uint32_lor(v___y_3471_, v___x_3472_);
return v___x_3473_;
}
v___jp_3474_:
{
uint32_t v___x_3476_; uint32_t v___x_3477_; 
v___x_3476_ = 8388608;
v___x_3477_ = lean_uint32_lor(v___y_3475_, v___x_3476_);
return v___x_3477_;
}
v___jp_3478_:
{
uint32_t v___x_3482_; uint32_t v___x_3483_; 
v___x_3482_ = lean_uint32_land(v___y_3479_, v___y_3480_);
v___x_3483_ = lean_uint32_lor(v___y_3481_, v___x_3482_);
return v___x_3483_;
}
v___jp_3484_:
{
uint8_t v___x_3489_; 
v___x_3489_ = lean_uint64_dec_eq(v___y_3488_, v___y_3485_);
if (v___x_3489_ == 0)
{
uint64_t v___x_3490_; uint8_t v___x_3491_; 
v___x_3490_ = 8388608ULL;
v___x_3491_ = lean_uint64_dec_eq(v___y_3488_, v___x_3490_);
if (v___x_3491_ == 0)
{
uint32_t v___x_3492_; 
v___x_3492_ = lean_uint64_to_uint32(v___y_3488_);
if (v___y_3486_ == 0)
{
uint32_t v___x_3493_; 
v___x_3493_ = 0;
v___y_3479_ = v___x_3492_;
v___y_3480_ = v___y_3487_;
v___y_3481_ = v___x_3493_;
goto v___jp_3478_;
}
else
{
uint32_t v___x_3494_; 
v___x_3494_ = 2147483648;
v___y_3479_ = v___x_3492_;
v___y_3480_ = v___y_3487_;
v___y_3481_ = v___x_3494_;
goto v___jp_3478_;
}
}
else
{
if (v___y_3486_ == 0)
{
uint32_t v___x_3495_; 
v___x_3495_ = 0;
v___y_3475_ = v___x_3495_;
goto v___jp_3474_;
}
else
{
uint32_t v___x_3496_; 
v___x_3496_ = 2147483648;
v___y_3475_ = v___x_3496_;
goto v___jp_3474_;
}
}
}
else
{
if (v___y_3486_ == 0)
{
uint32_t v___x_3497_; 
v___x_3497_ = 0;
return v___x_3497_;
}
else
{
uint32_t v___x_3498_; 
v___x_3498_ = 2147483648;
return v___x_3498_;
}
}
}
v___jp_3499_:
{
uint32_t v___x_3503_; uint32_t v___x_3504_; 
v___x_3503_ = lean_uint32_land(v___y_3500_, v___y_3501_);
v___x_3504_ = lean_uint32_lor(v___y_3502_, v___x_3503_);
return v___x_3504_;
}
v___jp_3505_:
{
uint8_t v___x_3510_; 
v___x_3510_ = lean_uint64_dec_eq(v___y_3509_, v___y_3507_);
if (v___x_3510_ == 0)
{
uint64_t v___x_3511_; uint8_t v___x_3512_; 
v___x_3511_ = 8388608ULL;
v___x_3512_ = lean_uint64_dec_eq(v___y_3509_, v___x_3511_);
if (v___x_3512_ == 0)
{
uint32_t v___x_3513_; 
v___x_3513_ = lean_uint64_to_uint32(v___y_3509_);
if (v___y_3506_ == 0)
{
uint32_t v___x_3514_; 
v___x_3514_ = 0;
v___y_3500_ = v___x_3513_;
v___y_3501_ = v___y_3508_;
v___y_3502_ = v___x_3514_;
goto v___jp_3499_;
}
else
{
uint32_t v___x_3515_; 
v___x_3515_ = 2147483648;
v___y_3500_ = v___x_3513_;
v___y_3501_ = v___y_3508_;
v___y_3502_ = v___x_3515_;
goto v___jp_3499_;
}
}
else
{
if (v___y_3506_ == 0)
{
uint32_t v___x_3516_; 
v___x_3516_ = 0;
v___y_3471_ = v___x_3516_;
goto v___jp_3470_;
}
else
{
uint32_t v___x_3517_; 
v___x_3517_ = 2147483648;
v___y_3471_ = v___x_3517_;
goto v___jp_3470_;
}
}
}
else
{
if (v___y_3506_ == 0)
{
uint32_t v___x_3518_; 
v___x_3518_ = 0;
return v___x_3518_;
}
else
{
uint32_t v___x_3519_; 
v___x_3519_ = 2147483648;
return v___x_3519_;
}
}
}
v___jp_3522_:
{
if (v___y_3523_ == 0)
{
float v___x_3524_; 
v___x_3524_ = lean_float32_of_bits(v___y_3373_);
v___y_3461_ = v___x_3524_;
goto v___jp_3460_;
}
else
{
uint32_t v___x_3525_; uint32_t v___x_3526_; uint32_t v___x_3527_; uint32_t v___x_3528_; float v___x_3529_; lean_object* v___x_3530_; lean_object* v___x_3531_; lean_object* v___x_3532_; float v___x_3533_; float v___x_3534_; 
v___x_3525_ = 8388607;
v___x_3526_ = lean_uint32_land(v___y_3373_, v___x_3525_);
v___x_3527_ = 8388608;
v___x_3528_ = lean_uint32_lor(v___x_3526_, v___x_3527_);
v___x_3529_ = lean_uint32_to_float32(v___x_3528_);
v___x_3530_ = lp_competition_R2W01b_scaleTable;
v___x_3531_ = lean_uint32_to_nat(v___x_3521_);
v___x_3532_ = lean_array_fget_borrowed(v___x_3530_, v___x_3531_);
lean_dec(v___x_3531_);
v___x_3533_ = lean_unbox_float32(v___x_3532_);
v___x_3534_ = lean_float32_mul(v___x_3529_, v___x_3533_);
v___y_3461_ = v___x_3534_;
goto v___jp_3460_;
}
}
v___jp_3536_:
{
uint32_t v___x_3541_; uint32_t v___x_3542_; uint32_t v___x_3543_; uint32_t v___x_3544_; uint32_t v___x_3545_; 
v___x_3541_ = lean_uint32_land(v___y_3539_, v___x_3535_);
v___x_3542_ = lean_uint32_shift_left(v___x_3541_, v___x_3520_);
v___x_3543_ = lean_uint32_lor(v___y_3540_, v___x_3542_);
v___x_3544_ = lean_uint32_land(v___y_3537_, v___y_3538_);
v___x_3545_ = lean_uint32_lor(v___x_3543_, v___x_3544_);
return v___x_3545_;
}
v___jp_3546_:
{
if (v___y_3547_ == 0)
{
uint32_t v___x_3551_; 
v___x_3551_ = 0;
v___y_3537_ = v___y_3550_;
v___y_3538_ = v___y_3549_;
v___y_3539_ = v___y_3548_;
v___y_3540_ = v___x_3551_;
goto v___jp_3536_;
}
else
{
uint32_t v___x_3552_; 
v___x_3552_ = 2147483648;
v___y_3537_ = v___y_3550_;
v___y_3538_ = v___y_3549_;
v___y_3539_ = v___y_3548_;
v___y_3540_ = v___x_3552_;
goto v___jp_3536_;
}
}
v___jp_3553_:
{
uint64_t v___x_3559_; uint64_t v_encodedExponent_3560_; uint32_t v___x_3561_; uint64_t v___x_3562_; uint8_t v___x_3563_; 
v___x_3559_ = 171ULL;
v_encodedExponent_3560_ = lean_uint64_sub(v___y_3556_, v___x_3559_);
v___x_3561_ = lean_uint64_to_uint32(v_encodedExponent_3560_);
v___x_3562_ = 8388608ULL;
v___x_3563_ = lean_uint64_dec_lt(v___y_3558_, v___x_3562_);
if (v___x_3563_ == 0)
{
uint64_t v___x_3564_; uint32_t v___x_3565_; 
v___x_3564_ = lean_uint64_sub(v___y_3558_, v___x_3562_);
v___x_3565_ = lean_uint64_to_uint32(v___x_3564_);
v___y_3547_ = v___y_3555_;
v___y_3548_ = v___x_3561_;
v___y_3549_ = v___y_3557_;
v___y_3550_ = v___x_3565_;
goto v___jp_3546_;
}
else
{
uint32_t v___x_3566_; 
v___x_3566_ = lean_uint64_to_uint32(v___y_3554_);
v___y_3547_ = v___y_3555_;
v___y_3548_ = v___x_3561_;
v___y_3549_ = v___y_3557_;
v___y_3550_ = v___x_3566_;
goto v___jp_3546_;
}
}
v___jp_3567_:
{
uint64_t v___x_3574_; uint8_t v___x_3575_; 
v___x_3574_ = 425ULL;
v___x_3575_ = lean_uint64_dec_lt(v___x_3574_, v___y_3573_);
if (v___x_3575_ == 0)
{
if (v___y_3569_ == 0)
{
v___y_3554_ = v___y_3568_;
v___y_3555_ = v___y_3571_;
v___y_3556_ = v___y_3573_;
v___y_3557_ = v___y_3572_;
v___y_3558_ = v___y_3570_;
goto v___jp_3553_;
}
else
{
uint64_t v___x_3576_; 
v___x_3576_ = 8388608ULL;
v___y_3554_ = v___y_3568_;
v___y_3555_ = v___y_3571_;
v___y_3556_ = v___y_3573_;
v___y_3557_ = v___y_3572_;
v___y_3558_ = v___x_3576_;
goto v___jp_3553_;
}
}
else
{
if (v___y_3571_ == 0)
{
uint32_t v___x_3577_; 
v___x_3577_ = 2139095040;
return v___x_3577_;
}
else
{
uint32_t v___x_3578_; 
v___x_3578_ = 4286578688;
return v___x_3578_;
}
}
}
v___jp_3579_:
{
uint64_t v___x_3585_; uint8_t v_carry_3586_; 
v___x_3585_ = 16777216ULL;
v_carry_3586_ = lean_uint64_dec_eq(v___y_3584_, v___x_3585_);
if (v_carry_3586_ == 0)
{
v___y_3568_ = v___y_3580_;
v___y_3569_ = v_carry_3586_;
v___y_3570_ = v___y_3584_;
v___y_3571_ = v___y_3582_;
v___y_3572_ = v___y_3583_;
v___y_3573_ = v___y_3581_;
goto v___jp_3567_;
}
else
{
uint64_t v___x_3587_; uint64_t v___x_3588_; 
v___x_3587_ = 1ULL;
v___x_3588_ = lean_uint64_add(v___y_3581_, v___x_3587_);
v___y_3568_ = v___y_3580_;
v___y_3569_ = v_carry_3586_;
v___y_3570_ = v___y_3584_;
v___y_3571_ = v___y_3582_;
v___y_3572_ = v___y_3583_;
v___y_3573_ = v___x_3588_;
goto v___jp_3567_;
}
}
v___jp_3589_:
{
uint64_t v_position_3596_; uint64_t v___x_3597_; uint8_t v___x_3598_; 
v_position_3596_ = lean_uint64_add(v___y_3595_, v___y_3592_);
v___x_3597_ = 172ULL;
v___x_3598_ = lean_uint64_dec_lt(v_position_3596_, v___x_3597_);
if (v___x_3598_ == 0)
{
uint64_t v___x_3599_; uint8_t v___x_3600_; 
v___x_3599_ = 23ULL;
v___x_3600_ = lean_uint64_dec_lt(v___y_3595_, v___x_3599_);
if (v___x_3600_ == 0)
{
uint64_t v___x_3601_; uint8_t v___x_3602_; 
v___x_3601_ = lean_uint64_sub(v___y_3595_, v___x_3599_);
v___x_3602_ = lean_uint64_dec_eq(v___x_3601_, v___y_3590_);
if (v___x_3602_ == 0)
{
uint64_t v___x_3603_; uint8_t v___x_3604_; 
v___x_3603_ = 64ULL;
v___x_3604_ = lean_uint64_dec_lt(v___x_3601_, v___x_3603_);
if (v___x_3604_ == 0)
{
uint8_t v___x_3605_; 
v___x_3605_ = lean_uint64_dec_eq(v___x_3601_, v___x_3603_);
if (v___x_3605_ == 0)
{
v___y_3580_ = v___y_3590_;
v___y_3581_ = v_position_3596_;
v___y_3582_ = v___y_3591_;
v___y_3583_ = v___y_3594_;
v___y_3584_ = v___y_3590_;
goto v___jp_3579_;
}
else
{
uint64_t v___x_3606_; uint8_t v___x_3607_; 
v___x_3606_ = 9223372036854775808ULL;
v___x_3607_ = lean_uint64_dec_lt(v___x_3606_, v___y_3593_);
if (v___x_3607_ == 0)
{
v___y_3580_ = v___y_3590_;
v___y_3581_ = v_position_3596_;
v___y_3582_ = v___y_3591_;
v___y_3583_ = v___y_3594_;
v___y_3584_ = v___y_3590_;
goto v___jp_3579_;
}
else
{
uint64_t v___x_3608_; 
v___x_3608_ = 1ULL;
v___y_3580_ = v___y_3590_;
v___y_3581_ = v_position_3596_;
v___y_3582_ = v___y_3591_;
v___y_3583_ = v___y_3594_;
v___y_3584_ = v___x_3608_;
goto v___jp_3579_;
}
}
}
else
{
uint64_t v_quotient_3609_; uint64_t v___x_3610_; uint64_t v___x_3611_; uint64_t v___x_3612_; uint64_t v_remainder_3613_; uint64_t v___x_3614_; uint64_t v_half_3615_; uint8_t v___x_3616_; 
v_quotient_3609_ = lean_uint64_shift_right(v___y_3593_, v___x_3601_);
v___x_3610_ = 1ULL;
v___x_3611_ = lean_uint64_shift_left(v___x_3610_, v___x_3601_);
v___x_3612_ = lean_uint64_sub(v___x_3611_, v___x_3610_);
v_remainder_3613_ = lean_uint64_land(v___y_3593_, v___x_3612_);
v___x_3614_ = lean_uint64_sub(v___x_3601_, v___x_3610_);
v_half_3615_ = lean_uint64_shift_left(v___x_3610_, v___x_3614_);
v___x_3616_ = lean_uint64_dec_lt(v_remainder_3613_, v_half_3615_);
if (v___x_3616_ == 0)
{
uint8_t v___x_3617_; 
v___x_3617_ = lean_uint64_dec_lt(v_half_3615_, v_remainder_3613_);
if (v___x_3617_ == 0)
{
uint64_t v___x_3618_; uint8_t v___x_3619_; 
v___x_3618_ = lean_uint64_land(v_quotient_3609_, v___x_3610_);
v___x_3619_ = lean_uint64_dec_eq(v___x_3618_, v___y_3590_);
if (v___x_3619_ == 0)
{
uint64_t v___x_3620_; 
v___x_3620_ = lean_uint64_add(v_quotient_3609_, v___x_3610_);
v___y_3580_ = v___y_3590_;
v___y_3581_ = v_position_3596_;
v___y_3582_ = v___y_3591_;
v___y_3583_ = v___y_3594_;
v___y_3584_ = v___x_3620_;
goto v___jp_3579_;
}
else
{
v___y_3580_ = v___y_3590_;
v___y_3581_ = v_position_3596_;
v___y_3582_ = v___y_3591_;
v___y_3583_ = v___y_3594_;
v___y_3584_ = v_quotient_3609_;
goto v___jp_3579_;
}
}
else
{
uint64_t v___x_3621_; 
v___x_3621_ = lean_uint64_add(v_quotient_3609_, v___x_3610_);
v___y_3580_ = v___y_3590_;
v___y_3581_ = v_position_3596_;
v___y_3582_ = v___y_3591_;
v___y_3583_ = v___y_3594_;
v___y_3584_ = v___x_3621_;
goto v___jp_3579_;
}
}
else
{
v___y_3580_ = v___y_3590_;
v___y_3581_ = v_position_3596_;
v___y_3582_ = v___y_3591_;
v___y_3583_ = v___y_3594_;
v___y_3584_ = v_quotient_3609_;
goto v___jp_3579_;
}
}
}
else
{
v___y_3580_ = v___y_3590_;
v___y_3581_ = v_position_3596_;
v___y_3582_ = v___y_3591_;
v___y_3583_ = v___y_3594_;
v___y_3584_ = v___y_3593_;
goto v___jp_3579_;
}
}
else
{
uint64_t v___x_3622_; uint64_t v___x_3623_; 
v___x_3622_ = lean_uint64_sub(v___x_3599_, v___y_3595_);
v___x_3623_ = lean_uint64_shift_left(v___y_3593_, v___x_3622_);
v___y_3580_ = v___y_3590_;
v___y_3581_ = v_position_3596_;
v___y_3582_ = v___y_3591_;
v___y_3583_ = v___y_3594_;
v___y_3584_ = v___x_3623_;
goto v___jp_3579_;
}
}
else
{
uint64_t v___x_3624_; uint8_t v___x_3625_; 
v___x_3624_ = 149ULL;
v___x_3625_ = lean_uint64_dec_lt(v___y_3592_, v___x_3624_);
if (v___x_3625_ == 0)
{
uint64_t v___x_3626_; uint64_t v___x_3627_; 
v___x_3626_ = lean_uint64_sub(v___y_3592_, v___x_3624_);
v___x_3627_ = lean_uint64_shift_left(v___y_3593_, v___x_3626_);
v___y_3485_ = v___y_3590_;
v___y_3486_ = v___y_3591_;
v___y_3487_ = v___y_3594_;
v___y_3488_ = v___x_3627_;
goto v___jp_3484_;
}
else
{
uint64_t v___x_3628_; uint8_t v___x_3629_; 
v___x_3628_ = lean_uint64_sub(v___x_3624_, v___y_3592_);
v___x_3629_ = lean_uint64_dec_eq(v___x_3628_, v___y_3590_);
if (v___x_3629_ == 0)
{
uint64_t v___x_3630_; uint8_t v___x_3631_; 
v___x_3630_ = 64ULL;
v___x_3631_ = lean_uint64_dec_lt(v___x_3628_, v___x_3630_);
if (v___x_3631_ == 0)
{
uint8_t v___x_3632_; 
v___x_3632_ = lean_uint64_dec_eq(v___x_3628_, v___x_3630_);
if (v___x_3632_ == 0)
{
v___y_3485_ = v___y_3590_;
v___y_3486_ = v___y_3591_;
v___y_3487_ = v___y_3594_;
v___y_3488_ = v___y_3590_;
goto v___jp_3484_;
}
else
{
uint64_t v___x_3633_; uint8_t v___x_3634_; 
v___x_3633_ = 9223372036854775808ULL;
v___x_3634_ = lean_uint64_dec_lt(v___x_3633_, v___y_3593_);
if (v___x_3634_ == 0)
{
v___y_3485_ = v___y_3590_;
v___y_3486_ = v___y_3591_;
v___y_3487_ = v___y_3594_;
v___y_3488_ = v___y_3590_;
goto v___jp_3484_;
}
else
{
uint64_t v___x_3635_; 
v___x_3635_ = 1ULL;
v___y_3485_ = v___y_3590_;
v___y_3486_ = v___y_3591_;
v___y_3487_ = v___y_3594_;
v___y_3488_ = v___x_3635_;
goto v___jp_3484_;
}
}
}
else
{
uint64_t v_quotient_3636_; uint64_t v___x_3637_; uint64_t v___x_3638_; uint64_t v___x_3639_; uint64_t v_remainder_3640_; uint64_t v___x_3641_; uint64_t v_half_3642_; uint8_t v___x_3643_; 
v_quotient_3636_ = lean_uint64_shift_right(v___y_3593_, v___x_3628_);
v___x_3637_ = 1ULL;
v___x_3638_ = lean_uint64_shift_left(v___x_3637_, v___x_3628_);
v___x_3639_ = lean_uint64_sub(v___x_3638_, v___x_3637_);
v_remainder_3640_ = lean_uint64_land(v___y_3593_, v___x_3639_);
v___x_3641_ = lean_uint64_sub(v___x_3628_, v___x_3637_);
v_half_3642_ = lean_uint64_shift_left(v___x_3637_, v___x_3641_);
v___x_3643_ = lean_uint64_dec_lt(v_remainder_3640_, v_half_3642_);
if (v___x_3643_ == 0)
{
uint8_t v___x_3644_; 
v___x_3644_ = lean_uint64_dec_lt(v_half_3642_, v_remainder_3640_);
if (v___x_3644_ == 0)
{
uint64_t v___x_3645_; uint8_t v___x_3646_; 
v___x_3645_ = lean_uint64_land(v_quotient_3636_, v___x_3637_);
v___x_3646_ = lean_uint64_dec_eq(v___x_3645_, v___y_3590_);
if (v___x_3646_ == 0)
{
uint64_t v___x_3647_; 
v___x_3647_ = lean_uint64_add(v_quotient_3636_, v___x_3637_);
v___y_3485_ = v___y_3590_;
v___y_3486_ = v___y_3591_;
v___y_3487_ = v___y_3594_;
v___y_3488_ = v___x_3647_;
goto v___jp_3484_;
}
else
{
v___y_3485_ = v___y_3590_;
v___y_3486_ = v___y_3591_;
v___y_3487_ = v___y_3594_;
v___y_3488_ = v_quotient_3636_;
goto v___jp_3484_;
}
}
else
{
uint64_t v___x_3648_; 
v___x_3648_ = lean_uint64_add(v_quotient_3636_, v___x_3637_);
v___y_3485_ = v___y_3590_;
v___y_3486_ = v___y_3591_;
v___y_3487_ = v___y_3594_;
v___y_3488_ = v___x_3648_;
goto v___jp_3484_;
}
}
else
{
v___y_3485_ = v___y_3590_;
v___y_3486_ = v___y_3591_;
v___y_3487_ = v___y_3594_;
v___y_3488_ = v_quotient_3636_;
goto v___jp_3484_;
}
}
}
else
{
v___y_3485_ = v___y_3590_;
v___y_3486_ = v___y_3591_;
v___y_3487_ = v___y_3594_;
v___y_3488_ = v___y_3593_;
goto v___jp_3484_;
}
}
}
}
v___jp_3649_:
{
uint64_t v___x_3657_; uint64_t v___x_3658_; uint8_t v___x_3659_; 
v___x_3657_ = 1ULL;
v___x_3658_ = lean_uint64_shift_right(v___y_3652_, v___x_3657_);
v___x_3659_ = lean_uint64_dec_eq(v___x_3658_, v___y_3650_);
if (v___x_3659_ == 0)
{
uint64_t v___x_3660_; 
v___x_3660_ = lean_uint64_add(v___y_3656_, v___x_3657_);
v___y_3590_ = v___y_3650_;
v___y_3591_ = v___y_3651_;
v___y_3592_ = v___y_3653_;
v___y_3593_ = v___y_3654_;
v___y_3594_ = v___y_3655_;
v___y_3595_ = v___x_3660_;
goto v___jp_3589_;
}
else
{
v___y_3590_ = v___y_3650_;
v___y_3591_ = v___y_3651_;
v___y_3592_ = v___y_3653_;
v___y_3593_ = v___y_3654_;
v___y_3594_ = v___y_3655_;
v___y_3595_ = v___y_3656_;
goto v___jp_3589_;
}
}
v___jp_3661_:
{
uint64_t v___x_3671_; uint8_t v___x_3672_; 
v___x_3671_ = lean_uint64_shift_right(v___y_3666_, v___y_3663_);
v___x_3672_ = lean_uint64_dec_eq(v___x_3671_, v___y_3662_);
if (v___x_3672_ == 0)
{
uint64_t v___x_3673_; 
v___x_3673_ = lean_uint64_add(v___y_3665_, v___y_3663_);
v___y_3650_ = v___y_3662_;
v___y_3651_ = v___y_3664_;
v___y_3652_ = v___y_3670_;
v___y_3653_ = v___y_3667_;
v___y_3654_ = v___y_3668_;
v___y_3655_ = v___y_3669_;
v___y_3656_ = v___x_3673_;
goto v___jp_3649_;
}
else
{
v___y_3650_ = v___y_3662_;
v___y_3651_ = v___y_3664_;
v___y_3652_ = v___y_3670_;
v___y_3653_ = v___y_3667_;
v___y_3654_ = v___y_3668_;
v___y_3655_ = v___y_3669_;
v___y_3656_ = v___y_3665_;
goto v___jp_3649_;
}
}
v___jp_3674_:
{
uint64_t v___x_3682_; uint64_t v___x_3683_; uint8_t v___x_3684_; 
v___x_3682_ = 2ULL;
v___x_3683_ = lean_uint64_shift_right(v___y_3678_, v___x_3682_);
v___x_3684_ = lean_uint64_dec_eq(v___x_3683_, v___y_3675_);
if (v___x_3684_ == 0)
{
v___y_3662_ = v___y_3675_;
v___y_3663_ = v___x_3682_;
v___y_3664_ = v___y_3676_;
v___y_3665_ = v___y_3681_;
v___y_3666_ = v___y_3678_;
v___y_3667_ = v___y_3677_;
v___y_3668_ = v___y_3679_;
v___y_3669_ = v___y_3680_;
v___y_3670_ = v___x_3683_;
goto v___jp_3661_;
}
else
{
v___y_3662_ = v___y_3675_;
v___y_3663_ = v___x_3682_;
v___y_3664_ = v___y_3676_;
v___y_3665_ = v___y_3681_;
v___y_3666_ = v___y_3678_;
v___y_3667_ = v___y_3677_;
v___y_3668_ = v___y_3679_;
v___y_3669_ = v___y_3680_;
v___y_3670_ = v___y_3678_;
goto v___jp_3661_;
}
}
v___jp_3685_:
{
uint64_t v___x_3695_; uint8_t v___x_3696_; 
v___x_3695_ = lean_uint64_shift_right(v___y_3689_, v___y_3687_);
v___x_3696_ = lean_uint64_dec_eq(v___x_3695_, v___y_3686_);
if (v___x_3696_ == 0)
{
uint64_t v___x_3697_; 
v___x_3697_ = lean_uint64_add(v___y_3690_, v___y_3687_);
v___y_3675_ = v___y_3686_;
v___y_3676_ = v___y_3688_;
v___y_3677_ = v___y_3691_;
v___y_3678_ = v___y_3694_;
v___y_3679_ = v___y_3692_;
v___y_3680_ = v___y_3693_;
v___y_3681_ = v___x_3697_;
goto v___jp_3674_;
}
else
{
v___y_3675_ = v___y_3686_;
v___y_3676_ = v___y_3688_;
v___y_3677_ = v___y_3691_;
v___y_3678_ = v___y_3694_;
v___y_3679_ = v___y_3692_;
v___y_3680_ = v___y_3693_;
v___y_3681_ = v___y_3690_;
goto v___jp_3674_;
}
}
v___jp_3698_:
{
uint64_t v___x_3706_; uint64_t v___x_3707_; uint8_t v___x_3708_; 
v___x_3706_ = 4ULL;
v___x_3707_ = lean_uint64_shift_right(v___y_3701_, v___x_3706_);
v___x_3708_ = lean_uint64_dec_eq(v___x_3707_, v___y_3699_);
if (v___x_3708_ == 0)
{
v___y_3686_ = v___y_3699_;
v___y_3687_ = v___x_3706_;
v___y_3688_ = v___y_3700_;
v___y_3689_ = v___y_3701_;
v___y_3690_ = v___y_3705_;
v___y_3691_ = v___y_3702_;
v___y_3692_ = v___y_3703_;
v___y_3693_ = v___y_3704_;
v___y_3694_ = v___x_3707_;
goto v___jp_3685_;
}
else
{
v___y_3686_ = v___y_3699_;
v___y_3687_ = v___x_3706_;
v___y_3688_ = v___y_3700_;
v___y_3689_ = v___y_3701_;
v___y_3690_ = v___y_3705_;
v___y_3691_ = v___y_3702_;
v___y_3692_ = v___y_3703_;
v___y_3693_ = v___y_3704_;
v___y_3694_ = v___y_3701_;
goto v___jp_3685_;
}
}
v___jp_3709_:
{
uint64_t v___x_3719_; uint8_t v___x_3720_; 
v___x_3719_ = lean_uint64_shift_right(v___y_3713_, v___y_3714_);
v___x_3720_ = lean_uint64_dec_eq(v___x_3719_, v___y_3710_);
if (v___x_3720_ == 0)
{
uint64_t v___x_3721_; 
v___x_3721_ = lean_uint64_add(v___y_3712_, v___y_3714_);
v___y_3699_ = v___y_3710_;
v___y_3700_ = v___y_3711_;
v___y_3701_ = v___y_3718_;
v___y_3702_ = v___y_3715_;
v___y_3703_ = v___y_3716_;
v___y_3704_ = v___y_3717_;
v___y_3705_ = v___x_3721_;
goto v___jp_3698_;
}
else
{
v___y_3699_ = v___y_3710_;
v___y_3700_ = v___y_3711_;
v___y_3701_ = v___y_3718_;
v___y_3702_ = v___y_3715_;
v___y_3703_ = v___y_3716_;
v___y_3704_ = v___y_3717_;
v___y_3705_ = v___y_3712_;
goto v___jp_3698_;
}
}
v___jp_3722_:
{
uint64_t v___x_3730_; uint64_t v___x_3731_; uint8_t v___x_3732_; 
v___x_3730_ = 8ULL;
v___x_3731_ = lean_uint64_shift_right(v___y_3725_, v___x_3730_);
v___x_3732_ = lean_uint64_dec_eq(v___x_3731_, v___y_3723_);
if (v___x_3732_ == 0)
{
v___y_3710_ = v___y_3723_;
v___y_3711_ = v___y_3724_;
v___y_3712_ = v___y_3729_;
v___y_3713_ = v___y_3725_;
v___y_3714_ = v___x_3730_;
v___y_3715_ = v___y_3726_;
v___y_3716_ = v___y_3727_;
v___y_3717_ = v___y_3728_;
v___y_3718_ = v___x_3731_;
goto v___jp_3709_;
}
else
{
v___y_3710_ = v___y_3723_;
v___y_3711_ = v___y_3724_;
v___y_3712_ = v___y_3729_;
v___y_3713_ = v___y_3725_;
v___y_3714_ = v___x_3730_;
v___y_3715_ = v___y_3726_;
v___y_3716_ = v___y_3727_;
v___y_3717_ = v___y_3728_;
v___y_3718_ = v___y_3725_;
goto v___jp_3709_;
}
}
v___jp_3733_:
{
uint64_t v___x_3743_; uint8_t v___x_3744_; 
v___x_3743_ = lean_uint64_shift_right(v___y_3737_, v___y_3738_);
v___x_3744_ = lean_uint64_dec_eq(v___x_3743_, v___y_3734_);
if (v___x_3744_ == 0)
{
uint64_t v___x_3745_; 
v___x_3745_ = lean_uint64_add(v___y_3735_, v___y_3738_);
v___y_3723_ = v___y_3734_;
v___y_3724_ = v___y_3736_;
v___y_3725_ = v___y_3742_;
v___y_3726_ = v___y_3739_;
v___y_3727_ = v___y_3740_;
v___y_3728_ = v___y_3741_;
v___y_3729_ = v___x_3745_;
goto v___jp_3722_;
}
else
{
v___y_3723_ = v___y_3734_;
v___y_3724_ = v___y_3736_;
v___y_3725_ = v___y_3742_;
v___y_3726_ = v___y_3739_;
v___y_3727_ = v___y_3740_;
v___y_3728_ = v___y_3741_;
v___y_3729_ = v___y_3735_;
goto v___jp_3722_;
}
}
v___jp_3746_:
{
uint64_t v___x_3754_; uint64_t v___x_3755_; uint8_t v___x_3756_; 
v___x_3754_ = 16ULL;
v___x_3755_ = lean_uint64_shift_right(v___y_3749_, v___x_3754_);
v___x_3756_ = lean_uint64_dec_eq(v___x_3755_, v___y_3747_);
if (v___x_3756_ == 0)
{
v___y_3734_ = v___y_3747_;
v___y_3735_ = v___y_3753_;
v___y_3736_ = v___y_3748_;
v___y_3737_ = v___y_3749_;
v___y_3738_ = v___x_3754_;
v___y_3739_ = v___y_3750_;
v___y_3740_ = v___y_3751_;
v___y_3741_ = v___y_3752_;
v___y_3742_ = v___x_3755_;
goto v___jp_3733_;
}
else
{
v___y_3734_ = v___y_3747_;
v___y_3735_ = v___y_3753_;
v___y_3736_ = v___y_3748_;
v___y_3737_ = v___y_3749_;
v___y_3738_ = v___x_3754_;
v___y_3739_ = v___y_3750_;
v___y_3740_ = v___y_3751_;
v___y_3741_ = v___y_3752_;
v___y_3742_ = v___y_3749_;
goto v___jp_3733_;
}
}
v___jp_3757_:
{
uint64_t v___x_3765_; uint8_t v___x_3766_; 
v___x_3765_ = lean_uint64_shift_right(v___y_3762_, v___y_3760_);
v___x_3766_ = lean_uint64_dec_eq(v___x_3765_, v___y_3758_);
if (v___x_3766_ == 0)
{
v___y_3747_ = v___y_3758_;
v___y_3748_ = v___y_3759_;
v___y_3749_ = v___y_3764_;
v___y_3750_ = v___y_3761_;
v___y_3751_ = v___y_3762_;
v___y_3752_ = v___y_3763_;
v___y_3753_ = v___y_3760_;
goto v___jp_3746_;
}
else
{
v___y_3747_ = v___y_3758_;
v___y_3748_ = v___y_3759_;
v___y_3749_ = v___y_3764_;
v___y_3750_ = v___y_3761_;
v___y_3751_ = v___y_3762_;
v___y_3752_ = v___y_3763_;
v___y_3753_ = v___y_3758_;
goto v___jp_3746_;
}
}
v___jp_3767_:
{
uint64_t v___x_3772_; uint8_t v___x_3773_; 
v___x_3772_ = 0ULL;
v___x_3773_ = lean_uint64_dec_eq(v___y_3770_, v___x_3772_);
if (v___x_3773_ == 0)
{
uint64_t v___x_3774_; uint64_t v___x_3775_; uint8_t v___x_3776_; 
v___x_3774_ = 32ULL;
v___x_3775_ = lean_uint64_shift_right(v___y_3770_, v___x_3774_);
v___x_3776_ = lean_uint64_dec_eq(v___x_3775_, v___x_3772_);
if (v___x_3776_ == 0)
{
v___y_3758_ = v___x_3772_;
v___y_3759_ = v___y_3768_;
v___y_3760_ = v___x_3774_;
v___y_3761_ = v___y_3769_;
v___y_3762_ = v___y_3770_;
v___y_3763_ = v___y_3771_;
v___y_3764_ = v___x_3775_;
goto v___jp_3757_;
}
else
{
v___y_3758_ = v___x_3772_;
v___y_3759_ = v___y_3768_;
v___y_3760_ = v___x_3774_;
v___y_3761_ = v___y_3769_;
v___y_3762_ = v___y_3770_;
v___y_3763_ = v___y_3771_;
v___y_3764_ = v___y_3770_;
goto v___jp_3757_;
}
}
else
{
if (v___y_3768_ == 0)
{
uint32_t v___x_3777_; 
v___x_3777_ = 0;
return v___x_3777_;
}
else
{
uint32_t v___x_3778_; 
v___x_3778_ = 2147483648;
return v___x_3778_;
}
}
}
v___jp_3779_:
{
uint64_t v___x_3786_; uint64_t v___x_3787_; uint64_t v___x_3788_; uint8_t v___x_3789_; 
v___x_3786_ = lean_uint64_mul(v___y_3782_, v___y_3783_);
v___x_3787_ = lean_uint64_add(v___y_3781_, v___y_3785_);
v___x_3788_ = 281474976710656ULL;
v___x_3789_ = lean_uint64_dec_lt(v___x_3786_, v___x_3788_);
if (v___x_3789_ == 0)
{
v___y_3768_ = v___y_3780_;
v___y_3769_ = v___x_3787_;
v___y_3770_ = v___x_3786_;
v___y_3771_ = v___y_3784_;
goto v___jp_3767_;
}
else
{
uint64_t v___x_3790_; uint8_t v___x_3791_; 
v___x_3790_ = 123ULL;
v___x_3791_ = lean_uint64_dec_le(v___x_3787_, v___x_3790_);
if (v___x_3791_ == 0)
{
v___y_3768_ = v___y_3780_;
v___y_3769_ = v___x_3787_;
v___y_3770_ = v___x_3786_;
v___y_3771_ = v___y_3784_;
goto v___jp_3767_;
}
else
{
uint64_t v___x_3792_; uint8_t v___x_3793_; 
v___x_3792_ = 0ULL;
v___x_3793_ = lean_uint64_dec_eq(v___x_3786_, v___x_3792_);
if (v___x_3793_ == 0)
{
uint64_t v___x_3794_; uint64_t v___x_3795_; uint8_t v___x_3796_; 
v___x_3794_ = 149ULL;
v___x_3795_ = lean_uint64_sub(v___x_3794_, v___x_3787_);
v___x_3796_ = lean_uint64_dec_eq(v___x_3795_, v___x_3792_);
if (v___x_3796_ == 0)
{
uint64_t v___x_3797_; uint8_t v___x_3798_; 
v___x_3797_ = 64ULL;
v___x_3798_ = lean_uint64_dec_lt(v___x_3795_, v___x_3797_);
if (v___x_3798_ == 0)
{
uint8_t v___x_3799_; 
v___x_3799_ = lean_uint64_dec_eq(v___x_3795_, v___x_3797_);
if (v___x_3799_ == 0)
{
v___y_3506_ = v___y_3780_;
v___y_3507_ = v___x_3792_;
v___y_3508_ = v___y_3784_;
v___y_3509_ = v___x_3792_;
goto v___jp_3505_;
}
else
{
uint64_t v___x_3800_; uint8_t v___x_3801_; 
v___x_3800_ = 9223372036854775808ULL;
v___x_3801_ = lean_uint64_dec_lt(v___x_3800_, v___x_3786_);
if (v___x_3801_ == 0)
{
v___y_3506_ = v___y_3780_;
v___y_3507_ = v___x_3792_;
v___y_3508_ = v___y_3784_;
v___y_3509_ = v___x_3792_;
goto v___jp_3505_;
}
else
{
uint64_t v___x_3802_; 
v___x_3802_ = 1ULL;
v___y_3506_ = v___y_3780_;
v___y_3507_ = v___x_3792_;
v___y_3508_ = v___y_3784_;
v___y_3509_ = v___x_3802_;
goto v___jp_3505_;
}
}
}
else
{
uint64_t v_quotient_3803_; uint64_t v___x_3804_; uint64_t v___x_3805_; uint64_t v___x_3806_; uint64_t v_remainder_3807_; uint64_t v___x_3808_; uint64_t v_half_3809_; uint8_t v___x_3810_; 
v_quotient_3803_ = lean_uint64_shift_right(v___x_3786_, v___x_3795_);
v___x_3804_ = 1ULL;
v___x_3805_ = lean_uint64_shift_left(v___x_3804_, v___x_3795_);
v___x_3806_ = lean_uint64_sub(v___x_3805_, v___x_3804_);
v_remainder_3807_ = lean_uint64_land(v___x_3786_, v___x_3806_);
v___x_3808_ = lean_uint64_sub(v___x_3795_, v___x_3804_);
v_half_3809_ = lean_uint64_shift_left(v___x_3804_, v___x_3808_);
v___x_3810_ = lean_uint64_dec_lt(v_remainder_3807_, v_half_3809_);
if (v___x_3810_ == 0)
{
uint8_t v___x_3811_; 
v___x_3811_ = lean_uint64_dec_lt(v_half_3809_, v_remainder_3807_);
if (v___x_3811_ == 0)
{
uint64_t v___x_3812_; uint8_t v___x_3813_; 
v___x_3812_ = lean_uint64_land(v_quotient_3803_, v___x_3804_);
v___x_3813_ = lean_uint64_dec_eq(v___x_3812_, v___x_3792_);
if (v___x_3813_ == 0)
{
uint64_t v___x_3814_; 
v___x_3814_ = lean_uint64_add(v_quotient_3803_, v___x_3804_);
v___y_3506_ = v___y_3780_;
v___y_3507_ = v___x_3792_;
v___y_3508_ = v___y_3784_;
v___y_3509_ = v___x_3814_;
goto v___jp_3505_;
}
else
{
v___y_3506_ = v___y_3780_;
v___y_3507_ = v___x_3792_;
v___y_3508_ = v___y_3784_;
v___y_3509_ = v_quotient_3803_;
goto v___jp_3505_;
}
}
else
{
uint64_t v___x_3815_; 
v___x_3815_ = lean_uint64_add(v_quotient_3803_, v___x_3804_);
v___y_3506_ = v___y_3780_;
v___y_3507_ = v___x_3792_;
v___y_3508_ = v___y_3784_;
v___y_3509_ = v___x_3815_;
goto v___jp_3505_;
}
}
else
{
v___y_3506_ = v___y_3780_;
v___y_3507_ = v___x_3792_;
v___y_3508_ = v___y_3784_;
v___y_3509_ = v_quotient_3803_;
goto v___jp_3505_;
}
}
}
else
{
v___y_3506_ = v___y_3780_;
v___y_3507_ = v___x_3792_;
v___y_3508_ = v___y_3784_;
v___y_3509_ = v___x_3786_;
goto v___jp_3505_;
}
}
else
{
if (v___y_3780_ == 0)
{
uint32_t v___x_3816_; 
v___x_3816_ = 0;
return v___x_3816_;
}
else
{
uint32_t v___x_3817_; 
v___x_3817_ = 2147483648;
return v___x_3817_;
}
}
}
}
}
v___jp_3821_:
{
uint64_t v___x_3827_; uint64_t v___x_3828_; uint8_t v___x_3829_; 
v___x_3827_ = lean_uint32_to_uint64(v_ey_3820_);
v___x_3828_ = 0ULL;
v___x_3829_ = lean_uint64_dec_eq(v___x_3827_, v___x_3828_);
if (v___x_3829_ == 0)
{
uint64_t v___x_3830_; uint64_t v___x_3831_; 
v___x_3830_ = 1ULL;
v___x_3831_ = lean_uint64_sub(v___x_3827_, v___x_3830_);
v___y_3780_ = v___y_3822_;
v___y_3781_ = v___y_3826_;
v___y_3782_ = v___y_3823_;
v___y_3783_ = v___y_3824_;
v___y_3784_ = v___y_3825_;
v___y_3785_ = v___x_3831_;
goto v___jp_3779_;
}
else
{
v___y_3780_ = v___y_3822_;
v___y_3781_ = v___y_3826_;
v___y_3782_ = v___y_3823_;
v___y_3783_ = v___y_3824_;
v___y_3784_ = v___y_3825_;
v___y_3785_ = v___x_3828_;
goto v___jp_3779_;
}
}
v___jp_3832_:
{
uint64_t v___x_3837_; uint64_t v___x_3838_; uint8_t v___x_3839_; 
v___x_3837_ = lean_uint32_to_uint64(v_ex_3818_);
v___x_3838_ = 0ULL;
v___x_3839_ = lean_uint64_dec_eq(v___x_3837_, v___x_3838_);
if (v___x_3839_ == 0)
{
uint64_t v___x_3840_; uint64_t v___x_3841_; 
v___x_3840_ = 1ULL;
v___x_3841_ = lean_uint64_sub(v___x_3837_, v___x_3840_);
v___y_3822_ = v___y_3833_;
v___y_3823_ = v___y_3834_;
v___y_3824_ = v___y_3836_;
v___y_3825_ = v___y_3835_;
v___y_3826_ = v___x_3841_;
goto v___jp_3821_;
}
else
{
v___y_3822_ = v___y_3833_;
v___y_3823_ = v___y_3834_;
v___y_3824_ = v___y_3836_;
v___y_3825_ = v___y_3835_;
v___y_3826_ = v___x_3838_;
goto v___jp_3821_;
}
}
v___jp_3842_:
{
uint32_t v___x_3847_; uint8_t v___x_3848_; 
v___x_3847_ = 0;
v___x_3848_ = lean_uint32_dec_eq(v_ey_3820_, v___x_3847_);
if (v___x_3848_ == 0)
{
uint64_t v___x_3849_; uint64_t v___x_3850_; uint64_t v___x_3851_; 
v___x_3849_ = lean_uint32_to_uint64(v___y_3844_);
v___x_3850_ = 8388608ULL;
v___x_3851_ = lean_uint64_lor(v___x_3849_, v___x_3850_);
v___y_3833_ = v___y_3843_;
v___y_3834_ = v___y_3846_;
v___y_3835_ = v___y_3845_;
v___y_3836_ = v___x_3851_;
goto v___jp_3832_;
}
else
{
uint64_t v___x_3852_; 
v___x_3852_ = lean_uint32_to_uint64(v___y_3844_);
v___y_3833_ = v___y_3843_;
v___y_3834_ = v___y_3846_;
v___y_3835_ = v___y_3845_;
v___y_3836_ = v___x_3852_;
goto v___jp_3832_;
}
}
v___jp_3853_:
{
uint32_t v___x_3855_; uint32_t v_xFraction_3856_; uint32_t v_yFraction_3857_; uint32_t v___x_3858_; uint8_t v___x_3859_; 
v___x_3855_ = 8388607;
v_xFraction_3856_ = lean_uint32_land(v___y_3373_, v___x_3855_);
v_yFraction_3857_ = lean_uint32_land(v___y_3374_, v___x_3855_);
v___x_3858_ = 0;
v___x_3859_ = lean_uint32_dec_eq(v_ex_3818_, v___x_3858_);
if (v___x_3859_ == 0)
{
uint64_t v___x_3860_; uint64_t v___x_3861_; uint64_t v___x_3862_; 
v___x_3860_ = lean_uint32_to_uint64(v_xFraction_3856_);
v___x_3861_ = 8388608ULL;
v___x_3862_ = lean_uint64_lor(v___x_3860_, v___x_3861_);
v___y_3843_ = v___y_3854_;
v___y_3844_ = v_yFraction_3857_;
v___y_3845_ = v___x_3855_;
v___y_3846_ = v___x_3862_;
goto v___jp_3842_;
}
else
{
uint64_t v___x_3863_; 
v___x_3863_ = lean_uint32_to_uint64(v_xFraction_3856_);
v___y_3843_ = v___y_3854_;
v___y_3844_ = v_yFraction_3857_;
v___y_3845_ = v___x_3855_;
v___y_3846_ = v___x_3863_;
goto v___jp_3842_;
}
}
v___jp_3864_:
{
if (v___y_3866_ == 0)
{
v___y_3854_ = v___x_3372_;
goto v___jp_3853_;
}
else
{
v___y_3854_ = v___y_3865_;
goto v___jp_3853_;
}
}
v___jp_3870_:
{
if (v___y_3871_ == 0)
{
if (v___y_3873_ == 0)
{
v___y_3865_ = v___y_3872_;
v___y_3866_ = v___x_3869_;
goto v___jp_3864_;
}
else
{
v___y_3854_ = v___x_3372_;
goto v___jp_3853_;
}
}
else
{
v___y_3865_ = v___y_3872_;
v___y_3866_ = v___y_3873_;
goto v___jp_3864_;
}
}
v___jp_3874_:
{
uint32_t v___x_3877_; uint32_t v___x_3878_; uint32_t v___x_3879_; uint8_t v___x_3880_; 
v___x_3877_ = 2147483648;
v___x_3878_ = lean_uint32_land(v___y_3374_, v___x_3877_);
v___x_3879_ = 0;
v___x_3880_ = lean_uint32_dec_eq(v___x_3878_, v___x_3879_);
if (v___x_3880_ == 0)
{
v___y_3871_ = v___y_3876_;
v___y_3872_ = v___y_3875_;
v___y_3873_ = v___x_3372_;
goto v___jp_3870_;
}
else
{
v___y_3871_ = v___y_3876_;
v___y_3872_ = v___y_3875_;
v___y_3873_ = v___y_3875_;
goto v___jp_3870_;
}
}
v___jp_3881_:
{
if (v___y_3882_ == 0)
{
uint32_t v___x_3883_; uint32_t v___x_3884_; uint32_t v___x_3885_; uint8_t v___x_3886_; 
v___x_3883_ = 2147483648;
v___x_3884_ = lean_uint32_land(v___y_3373_, v___x_3883_);
v___x_3885_ = 0;
v___x_3886_ = lean_uint32_dec_eq(v___x_3884_, v___x_3885_);
if (v___x_3886_ == 0)
{
v___y_3875_ = v___y_3882_;
v___y_3876_ = v___x_3372_;
goto v___jp_3874_;
}
else
{
v___y_3875_ = v___y_3882_;
v___y_3876_ = v___y_3882_;
goto v___jp_3874_;
}
}
else
{
lean_object* v___x_3887_; lean_object* v___x_3888_; lean_object* v___x_3889_; uint32_t v___x_3890_; 
v___x_3887_ = lean_uint32_to_nat(v___y_3373_);
v___x_3888_ = lean_uint32_to_nat(v___y_3374_);
v___x_3889_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_3887_, v___x_3888_);
v___x_3890_ = lean_uint32_of_nat(v___x_3889_);
lean_dec(v___x_3889_);
return v___x_3890_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object* v___x_3905_, lean_object* v___y_3906_, lean_object* v___y_3907_){
_start:
{
uint8_t v___x_13843__boxed_3908_; uint32_t v___y_13844__boxed_3909_; uint32_t v___y_13845__boxed_3910_; uint32_t v_res_3911_; lean_object* v_r_3912_; 
v___x_13843__boxed_3908_ = lean_unbox(v___x_3905_);
v___y_13844__boxed_3909_ = lean_unbox_uint32(v___y_3906_);
lean_dec(v___y_3906_);
v___y_13845__boxed_3910_ = lean_unbox_uint32(v___y_3907_);
lean_dec(v___y_3907_);
v_res_3911_ = lp_competition_main___lam__3(v___x_13843__boxed_3908_, v___y_13844__boxed_3909_, v___y_13845__boxed_3910_);
v_r_3912_ = lean_box_uint32(v_res_3911_);
return v_r_3912_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__4(uint8_t v___x_3913_, uint32_t v___y_3914_, uint32_t v___y_3915_){
_start:
{
uint8_t v___y_3917_; uint8_t v___y_3933_; uint8_t v___y_3947_; uint8_t v___y_3964_; float v___y_3971_; float v___y_3972_; float v___y_3986_; uint8_t v___y_3987_; float v___y_4002_; uint32_t v___y_4012_; uint32_t v___y_4016_; uint32_t v___y_4020_; uint32_t v___y_4021_; uint32_t v___y_4022_; uint8_t v___y_4026_; uint32_t v___y_4027_; uint64_t v___y_4028_; uint64_t v___y_4029_; uint32_t v___y_4041_; uint32_t v___y_4042_; uint32_t v___y_4043_; uint64_t v___y_4047_; uint8_t v___y_4048_; uint32_t v___y_4049_; uint64_t v___y_4050_; uint32_t v___x_4061_; uint32_t v___x_4062_; uint8_t v___y_4064_; uint32_t v___x_4076_; uint32_t v___y_4078_; uint32_t v___y_4079_; uint32_t v___y_4080_; uint32_t v___y_4081_; uint8_t v___y_4088_; uint32_t v___y_4089_; uint32_t v___y_4090_; uint32_t v___y_4091_; uint64_t v___y_4095_; uint32_t v___y_4096_; uint8_t v___y_4097_; uint64_t v___y_4098_; uint64_t v___y_4099_; uint8_t v___y_4109_; uint8_t v___y_4110_; uint32_t v___y_4111_; uint64_t v___y_4112_; uint64_t v___y_4113_; uint64_t v___y_4114_; uint64_t v___y_4121_; uint32_t v___y_4122_; uint8_t v___y_4123_; uint64_t v___y_4124_; uint64_t v___y_4125_; uint64_t v___y_4131_; uint8_t v___y_4132_; uint32_t v___y_4133_; uint64_t v___y_4134_; uint64_t v___y_4135_; uint64_t v___y_4136_; uint64_t v___y_4191_; uint32_t v___y_4192_; uint8_t v___y_4193_; uint64_t v___y_4194_; uint64_t v___y_4195_; uint64_t v___y_4196_; uint64_t v___y_4197_; uint64_t v___y_4203_; uint8_t v___y_4204_; uint32_t v___y_4205_; uint64_t v___y_4206_; uint64_t v___y_4207_; uint64_t v___y_4208_; uint64_t v___y_4209_; uint64_t v___y_4210_; uint64_t v___y_4211_; uint64_t v___y_4216_; uint32_t v___y_4217_; uint8_t v___y_4218_; uint64_t v___y_4219_; uint64_t v___y_4220_; uint64_t v___y_4221_; uint64_t v___y_4222_; uint64_t v___y_4227_; uint64_t v___y_4228_; uint64_t v___y_4229_; uint8_t v___y_4230_; uint32_t v___y_4231_; uint64_t v___y_4232_; uint64_t v___y_4233_; uint64_t v___y_4234_; uint64_t v___y_4235_; uint64_t v___y_4240_; uint32_t v___y_4241_; uint8_t v___y_4242_; uint64_t v___y_4243_; uint64_t v___y_4244_; uint64_t v___y_4245_; uint64_t v___y_4246_; uint64_t v___y_4251_; uint64_t v___y_4252_; uint64_t v___y_4253_; uint8_t v___y_4254_; uint32_t v___y_4255_; uint64_t v___y_4256_; uint64_t v___y_4257_; uint64_t v___y_4258_; uint64_t v___y_4259_; uint64_t v___y_4264_; uint64_t v___y_4265_; uint32_t v___y_4266_; uint8_t v___y_4267_; uint64_t v___y_4268_; uint64_t v___y_4269_; uint64_t v___y_4270_; uint64_t v___y_4275_; uint64_t v___y_4276_; uint64_t v___y_4277_; uint64_t v___y_4278_; uint8_t v___y_4279_; uint32_t v___y_4280_; uint64_t v___y_4281_; uint64_t v___y_4282_; uint64_t v___y_4283_; uint64_t v___y_4288_; uint64_t v___y_4289_; uint32_t v___y_4290_; uint8_t v___y_4291_; uint64_t v___y_4292_; uint64_t v___y_4293_; uint64_t v___y_4294_; uint64_t v___y_4299_; uint64_t v___y_4300_; uint8_t v___y_4301_; uint32_t v___y_4302_; uint64_t v___y_4303_; uint64_t v___y_4304_; uint64_t v___y_4305_; uint64_t v___y_4309_; uint32_t v___y_4310_; uint8_t v___y_4311_; uint64_t v___y_4312_; uint64_t v___y_4321_; uint8_t v___y_4322_; uint32_t v___y_4323_; uint64_t v___y_4324_; uint64_t v___y_4325_; uint64_t v___y_4326_; uint32_t v_ex_4359_; uint32_t v___x_4360_; uint32_t v_ey_4361_; uint64_t v___y_4363_; uint32_t v___y_4364_; uint8_t v___y_4365_; uint64_t v___y_4366_; uint64_t v___y_4367_; uint8_t v___y_4374_; uint32_t v___y_4375_; uint64_t v___y_4376_; uint64_t v___y_4377_; uint32_t v___y_4384_; uint32_t v___y_4385_; uint8_t v___y_4386_; uint64_t v___y_4387_; uint8_t v___y_4395_; uint8_t v___y_4406_; uint8_t v___y_4407_; uint32_t v___x_4408_; uint32_t v___x_4409_; uint8_t v___x_4410_; uint8_t v___y_4412_; uint8_t v___y_4413_; uint8_t v___y_4414_; uint8_t v___y_4416_; uint8_t v___y_4417_; uint8_t v___y_4423_; 
v___x_4061_ = 23;
v___x_4062_ = lean_uint32_shift_right(v___y_3914_, v___x_4061_);
v___x_4076_ = 255;
v_ex_4359_ = lean_uint32_land(v___x_4062_, v___x_4076_);
v___x_4360_ = lean_uint32_shift_right(v___y_3915_, v___x_4061_);
v_ey_4361_ = lean_uint32_land(v___x_4360_, v___x_4076_);
v___x_4408_ = lean_uint32_add(v_ex_4359_, v_ey_4361_);
v___x_4409_ = 128;
v___x_4410_ = lean_uint32_dec_lt(v___x_4408_, v___x_4409_);
if (v___x_4410_ == 0)
{
uint32_t v___x_4432_; uint32_t v_a_4433_; uint32_t v___x_4434_; uint32_t v___x_4435_; uint32_t v___x_4436_; uint8_t v___x_4437_; 
v___x_4432_ = 2147483647;
v_a_4433_ = lean_uint32_land(v___y_3914_, v___x_4432_);
v___x_4434_ = 201326591;
v___x_4435_ = 1;
v___x_4436_ = lean_uint32_sub(v_a_4433_, v___x_4435_);
v___x_4437_ = lean_uint32_dec_le(v___x_4434_, v___x_4436_);
if (v___x_4437_ == 0)
{
v___y_4064_ = v___x_4437_;
goto v___jp_4063_;
}
else
{
uint32_t v___x_4438_; uint8_t v___x_4439_; 
v___x_4438_ = 2139095040;
v___x_4439_ = lean_uint32_dec_lt(v_a_4433_, v___x_4438_);
v___y_4064_ = v___x_4439_;
goto v___jp_4063_;
}
}
else
{
uint32_t v___x_4440_; uint32_t v___x_4441_; uint32_t v___x_4442_; uint8_t v___x_4443_; 
v___x_4440_ = 4278190080;
v___x_4441_ = 1;
v___x_4442_ = lean_uint32_shift_left(v___y_3914_, v___x_4441_);
v___x_4443_ = lean_uint32_dec_le(v___x_4440_, v___x_4442_);
if (v___x_4443_ == 0)
{
uint32_t v___x_4444_; uint8_t v___x_4445_; 
v___x_4444_ = lean_uint32_shift_left(v___y_3915_, v___x_4441_);
v___x_4445_ = lean_uint32_dec_le(v___x_4440_, v___x_4444_);
v___y_4423_ = v___x_4445_;
goto v___jp_4422_;
}
else
{
v___y_4423_ = v___x_4443_;
goto v___jp_4422_;
}
}
v___jp_3916_:
{
if (v___y_3917_ == 0)
{
uint32_t v___x_3918_; 
v___x_3918_ = lp_competition_Submission_FastMul_mul(v___y_3914_, v___y_3915_);
return v___x_3918_;
}
else
{
uint32_t v___x_3919_; uint32_t v___x_3920_; 
v___x_3919_ = 4194304;
v___x_3920_ = lean_uint32_lor(v___y_3915_, v___x_3919_);
return v___x_3920_;
}
}
v___jp_3921_:
{
uint32_t v___x_3922_; uint32_t v___x_3923_; uint32_t v___x_3924_; uint32_t v___x_3925_; uint8_t v___x_3926_; 
v___x_3922_ = 23;
v___x_3923_ = lean_uint32_shift_right(v___y_3915_, v___x_3922_);
v___x_3924_ = 255;
v___x_3925_ = lean_uint32_land(v___x_3923_, v___x_3924_);
v___x_3926_ = lean_uint32_dec_eq(v___x_3925_, v___x_3924_);
if (v___x_3926_ == 0)
{
v___y_3917_ = v___x_3926_;
goto v___jp_3916_;
}
else
{
uint32_t v___x_3927_; uint32_t v___x_3928_; uint32_t v___x_3929_; uint8_t v___x_3930_; 
v___x_3927_ = 8388607;
v___x_3928_ = lean_uint32_land(v___y_3915_, v___x_3927_);
v___x_3929_ = 0;
v___x_3930_ = lean_uint32_dec_eq(v___x_3928_, v___x_3929_);
if (v___x_3930_ == 0)
{
v___y_3917_ = v___x_3926_;
goto v___jp_3916_;
}
else
{
uint32_t v___x_3931_; 
v___x_3931_ = lp_competition_Submission_FastMul_mul(v___y_3914_, v___y_3915_);
return v___x_3931_;
}
}
}
v___jp_3932_:
{
if (v___y_3933_ == 0)
{
goto v___jp_3921_;
}
else
{
uint32_t v___x_3934_; uint32_t v___x_3935_; 
v___x_3934_ = 4194304;
v___x_3935_ = lean_uint32_lor(v___y_3914_, v___x_3934_);
return v___x_3935_;
}
}
v___jp_3936_:
{
uint32_t v___x_3937_; uint32_t v___x_3938_; uint32_t v___x_3939_; uint32_t v___x_3940_; uint8_t v___x_3941_; 
v___x_3937_ = 23;
v___x_3938_ = lean_uint32_shift_right(v___y_3914_, v___x_3937_);
v___x_3939_ = 255;
v___x_3940_ = lean_uint32_land(v___x_3938_, v___x_3939_);
v___x_3941_ = lean_uint32_dec_eq(v___x_3940_, v___x_3939_);
if (v___x_3941_ == 0)
{
v___y_3933_ = v___x_3941_;
goto v___jp_3932_;
}
else
{
uint32_t v___x_3942_; uint32_t v___x_3943_; uint32_t v___x_3944_; uint8_t v___x_3945_; 
v___x_3942_ = 8388607;
v___x_3943_ = lean_uint32_land(v___y_3914_, v___x_3942_);
v___x_3944_ = 0;
v___x_3945_ = lean_uint32_dec_eq(v___x_3943_, v___x_3944_);
if (v___x_3945_ == 0)
{
v___y_3933_ = v___x_3941_;
goto v___jp_3932_;
}
else
{
goto v___jp_3921_;
}
}
}
v___jp_3946_:
{
if (v___y_3947_ == 0)
{
goto v___jp_3936_;
}
else
{
uint32_t v___x_3948_; uint32_t v___x_3949_; uint32_t v___x_3950_; uint8_t v___x_3951_; 
v___x_3948_ = 4194304;
v___x_3949_ = lean_uint32_land(v___y_3915_, v___x_3948_);
v___x_3950_ = 0;
v___x_3951_ = lean_uint32_dec_eq(v___x_3949_, v___x_3950_);
if (v___x_3951_ == 0)
{
goto v___jp_3936_;
}
else
{
uint32_t v___x_3952_; 
v___x_3952_ = lean_uint32_lor(v___y_3915_, v___x_3948_);
return v___x_3952_;
}
}
}
v___jp_3953_:
{
uint32_t v___x_3954_; uint32_t v___x_3955_; uint32_t v___x_3956_; uint32_t v___x_3957_; uint8_t v___x_3958_; 
v___x_3954_ = 23;
v___x_3955_ = lean_uint32_shift_right(v___y_3915_, v___x_3954_);
v___x_3956_ = 255;
v___x_3957_ = lean_uint32_land(v___x_3955_, v___x_3956_);
v___x_3958_ = lean_uint32_dec_eq(v___x_3957_, v___x_3956_);
if (v___x_3958_ == 0)
{
v___y_3947_ = v___x_3958_;
goto v___jp_3946_;
}
else
{
uint32_t v___x_3959_; uint32_t v___x_3960_; uint32_t v___x_3961_; uint8_t v___x_3962_; 
v___x_3959_ = 8388607;
v___x_3960_ = lean_uint32_land(v___y_3915_, v___x_3959_);
v___x_3961_ = 0;
v___x_3962_ = lean_uint32_dec_eq(v___x_3960_, v___x_3961_);
if (v___x_3962_ == 0)
{
v___y_3947_ = v___x_3958_;
goto v___jp_3946_;
}
else
{
goto v___jp_3936_;
}
}
}
v___jp_3963_:
{
if (v___y_3964_ == 0)
{
goto v___jp_3953_;
}
else
{
uint32_t v___x_3965_; uint32_t v___x_3966_; uint32_t v___x_3967_; uint8_t v___x_3968_; 
v___x_3965_ = 4194304;
v___x_3966_ = lean_uint32_land(v___y_3914_, v___x_3965_);
v___x_3967_ = 0;
v___x_3968_ = lean_uint32_dec_eq(v___x_3966_, v___x_3967_);
if (v___x_3968_ == 0)
{
goto v___jp_3953_;
}
else
{
uint32_t v___x_3969_; 
v___x_3969_ = lean_uint32_lor(v___y_3914_, v___x_3965_);
return v___x_3969_;
}
}
}
v___jp_3970_:
{
float v_result_3973_; uint8_t v___x_3974_; 
v_result_3973_ = lean_float32_mul(v___y_3971_, v___y_3972_);
v___x_3974_ = lean_float32_beq(v_result_3973_, v_result_3973_);
if (v___x_3974_ == 0)
{
uint32_t v___x_3975_; uint32_t v___x_3976_; uint32_t v___x_3977_; uint32_t v___x_3978_; uint8_t v___x_3979_; 
v___x_3975_ = 23;
v___x_3976_ = lean_uint32_shift_right(v___y_3914_, v___x_3975_);
v___x_3977_ = 255;
v___x_3978_ = lean_uint32_land(v___x_3976_, v___x_3977_);
v___x_3979_ = lean_uint32_dec_eq(v___x_3978_, v___x_3977_);
if (v___x_3979_ == 0)
{
v___y_3964_ = v___x_3979_;
goto v___jp_3963_;
}
else
{
uint32_t v___x_3980_; uint32_t v___x_3981_; uint32_t v___x_3982_; uint8_t v___x_3983_; 
v___x_3980_ = 8388607;
v___x_3981_ = lean_uint32_land(v___y_3914_, v___x_3980_);
v___x_3982_ = 0;
v___x_3983_ = lean_uint32_dec_eq(v___x_3981_, v___x_3982_);
if (v___x_3983_ == 0)
{
v___y_3964_ = v___x_3979_;
goto v___jp_3963_;
}
else
{
goto v___jp_3953_;
}
}
}
else
{
uint32_t v___x_3984_; 
v___x_3984_ = lean_float32_to_bits(v_result_3973_);
return v___x_3984_;
}
}
v___jp_3985_:
{
if (v___y_3987_ == 0)
{
float v___x_3988_; 
v___x_3988_ = lean_float32_of_bits(v___y_3915_);
v___y_3971_ = v___y_3986_;
v___y_3972_ = v___x_3988_;
goto v___jp_3970_;
}
else
{
uint32_t v___x_3989_; uint32_t v___x_3990_; uint32_t v___x_3991_; uint32_t v___x_3992_; float v___x_3993_; lean_object* v___x_3994_; uint32_t v___x_3995_; uint32_t v___x_3996_; lean_object* v___x_3997_; lean_object* v___x_3998_; float v___x_3999_; float v___x_4000_; 
v___x_3989_ = 8388607;
v___x_3990_ = lean_uint32_land(v___y_3915_, v___x_3989_);
v___x_3991_ = 8388608;
v___x_3992_ = lean_uint32_lor(v___x_3990_, v___x_3991_);
v___x_3993_ = lean_uint32_to_float32(v___x_3992_);
v___x_3994_ = lp_competition_R2W01b_scaleTable;
v___x_3995_ = 23;
v___x_3996_ = lean_uint32_shift_right(v___y_3915_, v___x_3995_);
v___x_3997_ = lean_uint32_to_nat(v___x_3996_);
v___x_3998_ = lean_array_fget_borrowed(v___x_3994_, v___x_3997_);
lean_dec(v___x_3997_);
v___x_3999_ = lean_unbox_float32(v___x_3998_);
v___x_4000_ = lean_float32_mul(v___x_3993_, v___x_3999_);
v___y_3971_ = v___y_3986_;
v___y_3972_ = v___x_4000_;
goto v___jp_3970_;
}
}
v___jp_4001_:
{
uint32_t v___x_4003_; uint32_t v_a_4004_; uint32_t v___x_4005_; uint32_t v___x_4006_; uint32_t v___x_4007_; uint8_t v___x_4008_; 
v___x_4003_ = 2147483647;
v_a_4004_ = lean_uint32_land(v___y_3915_, v___x_4003_);
v___x_4005_ = 201326591;
v___x_4006_ = 1;
v___x_4007_ = lean_uint32_sub(v_a_4004_, v___x_4006_);
v___x_4008_ = lean_uint32_dec_le(v___x_4005_, v___x_4007_);
if (v___x_4008_ == 0)
{
v___y_3986_ = v___y_4002_;
v___y_3987_ = v___x_4008_;
goto v___jp_3985_;
}
else
{
uint32_t v___x_4009_; uint8_t v___x_4010_; 
v___x_4009_ = 2139095040;
v___x_4010_ = lean_uint32_dec_lt(v_a_4004_, v___x_4009_);
v___y_3986_ = v___y_4002_;
v___y_3987_ = v___x_4010_;
goto v___jp_3985_;
}
}
v___jp_4011_:
{
uint32_t v___x_4013_; uint32_t v___x_4014_; 
v___x_4013_ = 8388608;
v___x_4014_ = lean_uint32_lor(v___y_4012_, v___x_4013_);
return v___x_4014_;
}
v___jp_4015_:
{
uint32_t v___x_4017_; uint32_t v___x_4018_; 
v___x_4017_ = 8388608;
v___x_4018_ = lean_uint32_lor(v___y_4016_, v___x_4017_);
return v___x_4018_;
}
v___jp_4019_:
{
uint32_t v___x_4023_; uint32_t v___x_4024_; 
v___x_4023_ = lean_uint32_land(v___y_4020_, v___y_4021_);
v___x_4024_ = lean_uint32_lor(v___y_4022_, v___x_4023_);
return v___x_4024_;
}
v___jp_4025_:
{
uint8_t v___x_4030_; 
v___x_4030_ = lean_uint64_dec_eq(v___y_4029_, v___y_4028_);
if (v___x_4030_ == 0)
{
uint64_t v___x_4031_; uint8_t v___x_4032_; 
v___x_4031_ = 8388608ULL;
v___x_4032_ = lean_uint64_dec_eq(v___y_4029_, v___x_4031_);
if (v___x_4032_ == 0)
{
uint32_t v___x_4033_; 
v___x_4033_ = lean_uint64_to_uint32(v___y_4029_);
if (v___y_4026_ == 0)
{
uint32_t v___x_4034_; 
v___x_4034_ = 0;
v___y_4020_ = v___x_4033_;
v___y_4021_ = v___y_4027_;
v___y_4022_ = v___x_4034_;
goto v___jp_4019_;
}
else
{
uint32_t v___x_4035_; 
v___x_4035_ = 2147483648;
v___y_4020_ = v___x_4033_;
v___y_4021_ = v___y_4027_;
v___y_4022_ = v___x_4035_;
goto v___jp_4019_;
}
}
else
{
if (v___y_4026_ == 0)
{
uint32_t v___x_4036_; 
v___x_4036_ = 0;
v___y_4016_ = v___x_4036_;
goto v___jp_4015_;
}
else
{
uint32_t v___x_4037_; 
v___x_4037_ = 2147483648;
v___y_4016_ = v___x_4037_;
goto v___jp_4015_;
}
}
}
else
{
if (v___y_4026_ == 0)
{
uint32_t v___x_4038_; 
v___x_4038_ = 0;
return v___x_4038_;
}
else
{
uint32_t v___x_4039_; 
v___x_4039_ = 2147483648;
return v___x_4039_;
}
}
}
v___jp_4040_:
{
uint32_t v___x_4044_; uint32_t v___x_4045_; 
v___x_4044_ = lean_uint32_land(v___y_4042_, v___y_4041_);
v___x_4045_ = lean_uint32_lor(v___y_4043_, v___x_4044_);
return v___x_4045_;
}
v___jp_4046_:
{
uint8_t v___x_4051_; 
v___x_4051_ = lean_uint64_dec_eq(v___y_4050_, v___y_4047_);
if (v___x_4051_ == 0)
{
uint64_t v___x_4052_; uint8_t v___x_4053_; 
v___x_4052_ = 8388608ULL;
v___x_4053_ = lean_uint64_dec_eq(v___y_4050_, v___x_4052_);
if (v___x_4053_ == 0)
{
uint32_t v___x_4054_; 
v___x_4054_ = lean_uint64_to_uint32(v___y_4050_);
if (v___y_4048_ == 0)
{
uint32_t v___x_4055_; 
v___x_4055_ = 0;
v___y_4041_ = v___y_4049_;
v___y_4042_ = v___x_4054_;
v___y_4043_ = v___x_4055_;
goto v___jp_4040_;
}
else
{
uint32_t v___x_4056_; 
v___x_4056_ = 2147483648;
v___y_4041_ = v___y_4049_;
v___y_4042_ = v___x_4054_;
v___y_4043_ = v___x_4056_;
goto v___jp_4040_;
}
}
else
{
if (v___y_4048_ == 0)
{
uint32_t v___x_4057_; 
v___x_4057_ = 0;
v___y_4012_ = v___x_4057_;
goto v___jp_4011_;
}
else
{
uint32_t v___x_4058_; 
v___x_4058_ = 2147483648;
v___y_4012_ = v___x_4058_;
goto v___jp_4011_;
}
}
}
else
{
if (v___y_4048_ == 0)
{
uint32_t v___x_4059_; 
v___x_4059_ = 0;
return v___x_4059_;
}
else
{
uint32_t v___x_4060_; 
v___x_4060_ = 2147483648;
return v___x_4060_;
}
}
}
v___jp_4063_:
{
if (v___y_4064_ == 0)
{
float v___x_4065_; 
v___x_4065_ = lean_float32_of_bits(v___y_3914_);
v___y_4002_ = v___x_4065_;
goto v___jp_4001_;
}
else
{
uint32_t v___x_4066_; uint32_t v___x_4067_; uint32_t v___x_4068_; uint32_t v___x_4069_; float v___x_4070_; lean_object* v___x_4071_; lean_object* v___x_4072_; lean_object* v___x_4073_; float v___x_4074_; float v___x_4075_; 
v___x_4066_ = 8388607;
v___x_4067_ = lean_uint32_land(v___y_3914_, v___x_4066_);
v___x_4068_ = 8388608;
v___x_4069_ = lean_uint32_lor(v___x_4067_, v___x_4068_);
v___x_4070_ = lean_uint32_to_float32(v___x_4069_);
v___x_4071_ = lp_competition_R2W01b_scaleTable;
v___x_4072_ = lean_uint32_to_nat(v___x_4062_);
v___x_4073_ = lean_array_fget_borrowed(v___x_4071_, v___x_4072_);
lean_dec(v___x_4072_);
v___x_4074_ = lean_unbox_float32(v___x_4073_);
v___x_4075_ = lean_float32_mul(v___x_4070_, v___x_4074_);
v___y_4002_ = v___x_4075_;
goto v___jp_4001_;
}
}
v___jp_4077_:
{
uint32_t v___x_4082_; uint32_t v___x_4083_; uint32_t v___x_4084_; uint32_t v___x_4085_; uint32_t v___x_4086_; 
v___x_4082_ = lean_uint32_land(v___y_4080_, v___x_4076_);
v___x_4083_ = lean_uint32_shift_left(v___x_4082_, v___x_4061_);
v___x_4084_ = lean_uint32_lor(v___y_4081_, v___x_4083_);
v___x_4085_ = lean_uint32_land(v___y_4078_, v___y_4079_);
v___x_4086_ = lean_uint32_lor(v___x_4084_, v___x_4085_);
return v___x_4086_;
}
v___jp_4087_:
{
if (v___y_4088_ == 0)
{
uint32_t v___x_4092_; 
v___x_4092_ = 0;
v___y_4078_ = v___y_4091_;
v___y_4079_ = v___y_4089_;
v___y_4080_ = v___y_4090_;
v___y_4081_ = v___x_4092_;
goto v___jp_4077_;
}
else
{
uint32_t v___x_4093_; 
v___x_4093_ = 2147483648;
v___y_4078_ = v___y_4091_;
v___y_4079_ = v___y_4089_;
v___y_4080_ = v___y_4090_;
v___y_4081_ = v___x_4093_;
goto v___jp_4077_;
}
}
v___jp_4094_:
{
uint64_t v___x_4100_; uint64_t v_encodedExponent_4101_; uint32_t v___x_4102_; uint64_t v___x_4103_; uint8_t v___x_4104_; 
v___x_4100_ = 171ULL;
v_encodedExponent_4101_ = lean_uint64_sub(v___y_4095_, v___x_4100_);
v___x_4102_ = lean_uint64_to_uint32(v_encodedExponent_4101_);
v___x_4103_ = 8388608ULL;
v___x_4104_ = lean_uint64_dec_lt(v___y_4099_, v___x_4103_);
if (v___x_4104_ == 0)
{
uint64_t v___x_4105_; uint32_t v___x_4106_; 
v___x_4105_ = lean_uint64_sub(v___y_4099_, v___x_4103_);
v___x_4106_ = lean_uint64_to_uint32(v___x_4105_);
v___y_4088_ = v___y_4097_;
v___y_4089_ = v___y_4096_;
v___y_4090_ = v___x_4102_;
v___y_4091_ = v___x_4106_;
goto v___jp_4087_;
}
else
{
uint32_t v___x_4107_; 
v___x_4107_ = lean_uint64_to_uint32(v___y_4098_);
v___y_4088_ = v___y_4097_;
v___y_4089_ = v___y_4096_;
v___y_4090_ = v___x_4102_;
v___y_4091_ = v___x_4107_;
goto v___jp_4087_;
}
}
v___jp_4108_:
{
uint64_t v___x_4115_; uint8_t v___x_4116_; 
v___x_4115_ = 425ULL;
v___x_4116_ = lean_uint64_dec_lt(v___x_4115_, v___y_4114_);
if (v___x_4116_ == 0)
{
if (v___y_4109_ == 0)
{
v___y_4095_ = v___y_4114_;
v___y_4096_ = v___y_4111_;
v___y_4097_ = v___y_4110_;
v___y_4098_ = v___y_4113_;
v___y_4099_ = v___y_4112_;
goto v___jp_4094_;
}
else
{
uint64_t v___x_4117_; 
v___x_4117_ = 8388608ULL;
v___y_4095_ = v___y_4114_;
v___y_4096_ = v___y_4111_;
v___y_4097_ = v___y_4110_;
v___y_4098_ = v___y_4113_;
v___y_4099_ = v___x_4117_;
goto v___jp_4094_;
}
}
else
{
if (v___y_4110_ == 0)
{
uint32_t v___x_4118_; 
v___x_4118_ = 2139095040;
return v___x_4118_;
}
else
{
uint32_t v___x_4119_; 
v___x_4119_ = 4286578688;
return v___x_4119_;
}
}
}
v___jp_4120_:
{
uint64_t v___x_4126_; uint8_t v_carry_4127_; 
v___x_4126_ = 16777216ULL;
v_carry_4127_ = lean_uint64_dec_eq(v___y_4125_, v___x_4126_);
if (v_carry_4127_ == 0)
{
v___y_4109_ = v_carry_4127_;
v___y_4110_ = v___y_4123_;
v___y_4111_ = v___y_4122_;
v___y_4112_ = v___y_4125_;
v___y_4113_ = v___y_4124_;
v___y_4114_ = v___y_4121_;
goto v___jp_4108_;
}
else
{
uint64_t v___x_4128_; uint64_t v___x_4129_; 
v___x_4128_ = 1ULL;
v___x_4129_ = lean_uint64_add(v___y_4121_, v___x_4128_);
v___y_4109_ = v_carry_4127_;
v___y_4110_ = v___y_4123_;
v___y_4111_ = v___y_4122_;
v___y_4112_ = v___y_4125_;
v___y_4113_ = v___y_4124_;
v___y_4114_ = v___x_4129_;
goto v___jp_4108_;
}
}
v___jp_4130_:
{
uint64_t v_position_4137_; uint64_t v___x_4138_; uint8_t v___x_4139_; 
v_position_4137_ = lean_uint64_add(v___y_4136_, v___y_4134_);
v___x_4138_ = 172ULL;
v___x_4139_ = lean_uint64_dec_lt(v_position_4137_, v___x_4138_);
if (v___x_4139_ == 0)
{
uint64_t v___x_4140_; uint8_t v___x_4141_; 
v___x_4140_ = 23ULL;
v___x_4141_ = lean_uint64_dec_lt(v___y_4136_, v___x_4140_);
if (v___x_4141_ == 0)
{
uint64_t v___x_4142_; uint8_t v___x_4143_; 
v___x_4142_ = lean_uint64_sub(v___y_4136_, v___x_4140_);
v___x_4143_ = lean_uint64_dec_eq(v___x_4142_, v___y_4135_);
if (v___x_4143_ == 0)
{
uint64_t v___x_4144_; uint8_t v___x_4145_; 
v___x_4144_ = 64ULL;
v___x_4145_ = lean_uint64_dec_lt(v___x_4142_, v___x_4144_);
if (v___x_4145_ == 0)
{
uint8_t v___x_4146_; 
v___x_4146_ = lean_uint64_dec_eq(v___x_4142_, v___x_4144_);
if (v___x_4146_ == 0)
{
v___y_4121_ = v_position_4137_;
v___y_4122_ = v___y_4133_;
v___y_4123_ = v___y_4132_;
v___y_4124_ = v___y_4135_;
v___y_4125_ = v___y_4135_;
goto v___jp_4120_;
}
else
{
uint64_t v___x_4147_; uint8_t v___x_4148_; 
v___x_4147_ = 9223372036854775808ULL;
v___x_4148_ = lean_uint64_dec_lt(v___x_4147_, v___y_4131_);
if (v___x_4148_ == 0)
{
v___y_4121_ = v_position_4137_;
v___y_4122_ = v___y_4133_;
v___y_4123_ = v___y_4132_;
v___y_4124_ = v___y_4135_;
v___y_4125_ = v___y_4135_;
goto v___jp_4120_;
}
else
{
uint64_t v___x_4149_; 
v___x_4149_ = 1ULL;
v___y_4121_ = v_position_4137_;
v___y_4122_ = v___y_4133_;
v___y_4123_ = v___y_4132_;
v___y_4124_ = v___y_4135_;
v___y_4125_ = v___x_4149_;
goto v___jp_4120_;
}
}
}
else
{
uint64_t v_quotient_4150_; uint64_t v___x_4151_; uint64_t v___x_4152_; uint64_t v___x_4153_; uint64_t v_remainder_4154_; uint64_t v___x_4155_; uint64_t v_half_4156_; uint8_t v___x_4157_; 
v_quotient_4150_ = lean_uint64_shift_right(v___y_4131_, v___x_4142_);
v___x_4151_ = 1ULL;
v___x_4152_ = lean_uint64_shift_left(v___x_4151_, v___x_4142_);
v___x_4153_ = lean_uint64_sub(v___x_4152_, v___x_4151_);
v_remainder_4154_ = lean_uint64_land(v___y_4131_, v___x_4153_);
v___x_4155_ = lean_uint64_sub(v___x_4142_, v___x_4151_);
v_half_4156_ = lean_uint64_shift_left(v___x_4151_, v___x_4155_);
v___x_4157_ = lean_uint64_dec_lt(v_remainder_4154_, v_half_4156_);
if (v___x_4157_ == 0)
{
uint8_t v___x_4158_; 
v___x_4158_ = lean_uint64_dec_lt(v_half_4156_, v_remainder_4154_);
if (v___x_4158_ == 0)
{
uint64_t v___x_4159_; uint8_t v___x_4160_; 
v___x_4159_ = lean_uint64_land(v_quotient_4150_, v___x_4151_);
v___x_4160_ = lean_uint64_dec_eq(v___x_4159_, v___y_4135_);
if (v___x_4160_ == 0)
{
uint64_t v___x_4161_; 
v___x_4161_ = lean_uint64_add(v_quotient_4150_, v___x_4151_);
v___y_4121_ = v_position_4137_;
v___y_4122_ = v___y_4133_;
v___y_4123_ = v___y_4132_;
v___y_4124_ = v___y_4135_;
v___y_4125_ = v___x_4161_;
goto v___jp_4120_;
}
else
{
v___y_4121_ = v_position_4137_;
v___y_4122_ = v___y_4133_;
v___y_4123_ = v___y_4132_;
v___y_4124_ = v___y_4135_;
v___y_4125_ = v_quotient_4150_;
goto v___jp_4120_;
}
}
else
{
uint64_t v___x_4162_; 
v___x_4162_ = lean_uint64_add(v_quotient_4150_, v___x_4151_);
v___y_4121_ = v_position_4137_;
v___y_4122_ = v___y_4133_;
v___y_4123_ = v___y_4132_;
v___y_4124_ = v___y_4135_;
v___y_4125_ = v___x_4162_;
goto v___jp_4120_;
}
}
else
{
v___y_4121_ = v_position_4137_;
v___y_4122_ = v___y_4133_;
v___y_4123_ = v___y_4132_;
v___y_4124_ = v___y_4135_;
v___y_4125_ = v_quotient_4150_;
goto v___jp_4120_;
}
}
}
else
{
v___y_4121_ = v_position_4137_;
v___y_4122_ = v___y_4133_;
v___y_4123_ = v___y_4132_;
v___y_4124_ = v___y_4135_;
v___y_4125_ = v___y_4131_;
goto v___jp_4120_;
}
}
else
{
uint64_t v___x_4163_; uint64_t v___x_4164_; 
v___x_4163_ = lean_uint64_sub(v___x_4140_, v___y_4136_);
v___x_4164_ = lean_uint64_shift_left(v___y_4131_, v___x_4163_);
v___y_4121_ = v_position_4137_;
v___y_4122_ = v___y_4133_;
v___y_4123_ = v___y_4132_;
v___y_4124_ = v___y_4135_;
v___y_4125_ = v___x_4164_;
goto v___jp_4120_;
}
}
else
{
uint64_t v___x_4165_; uint8_t v___x_4166_; 
v___x_4165_ = 149ULL;
v___x_4166_ = lean_uint64_dec_lt(v___y_4134_, v___x_4165_);
if (v___x_4166_ == 0)
{
uint64_t v___x_4167_; uint64_t v___x_4168_; 
v___x_4167_ = lean_uint64_sub(v___y_4134_, v___x_4165_);
v___x_4168_ = lean_uint64_shift_left(v___y_4131_, v___x_4167_);
v___y_4026_ = v___y_4132_;
v___y_4027_ = v___y_4133_;
v___y_4028_ = v___y_4135_;
v___y_4029_ = v___x_4168_;
goto v___jp_4025_;
}
else
{
uint64_t v___x_4169_; uint8_t v___x_4170_; 
v___x_4169_ = lean_uint64_sub(v___x_4165_, v___y_4134_);
v___x_4170_ = lean_uint64_dec_eq(v___x_4169_, v___y_4135_);
if (v___x_4170_ == 0)
{
uint64_t v___x_4171_; uint8_t v___x_4172_; 
v___x_4171_ = 64ULL;
v___x_4172_ = lean_uint64_dec_lt(v___x_4169_, v___x_4171_);
if (v___x_4172_ == 0)
{
uint8_t v___x_4173_; 
v___x_4173_ = lean_uint64_dec_eq(v___x_4169_, v___x_4171_);
if (v___x_4173_ == 0)
{
v___y_4026_ = v___y_4132_;
v___y_4027_ = v___y_4133_;
v___y_4028_ = v___y_4135_;
v___y_4029_ = v___y_4135_;
goto v___jp_4025_;
}
else
{
uint64_t v___x_4174_; uint8_t v___x_4175_; 
v___x_4174_ = 9223372036854775808ULL;
v___x_4175_ = lean_uint64_dec_lt(v___x_4174_, v___y_4131_);
if (v___x_4175_ == 0)
{
v___y_4026_ = v___y_4132_;
v___y_4027_ = v___y_4133_;
v___y_4028_ = v___y_4135_;
v___y_4029_ = v___y_4135_;
goto v___jp_4025_;
}
else
{
uint64_t v___x_4176_; 
v___x_4176_ = 1ULL;
v___y_4026_ = v___y_4132_;
v___y_4027_ = v___y_4133_;
v___y_4028_ = v___y_4135_;
v___y_4029_ = v___x_4176_;
goto v___jp_4025_;
}
}
}
else
{
uint64_t v_quotient_4177_; uint64_t v___x_4178_; uint64_t v___x_4179_; uint64_t v___x_4180_; uint64_t v_remainder_4181_; uint64_t v___x_4182_; uint64_t v_half_4183_; uint8_t v___x_4184_; 
v_quotient_4177_ = lean_uint64_shift_right(v___y_4131_, v___x_4169_);
v___x_4178_ = 1ULL;
v___x_4179_ = lean_uint64_shift_left(v___x_4178_, v___x_4169_);
v___x_4180_ = lean_uint64_sub(v___x_4179_, v___x_4178_);
v_remainder_4181_ = lean_uint64_land(v___y_4131_, v___x_4180_);
v___x_4182_ = lean_uint64_sub(v___x_4169_, v___x_4178_);
v_half_4183_ = lean_uint64_shift_left(v___x_4178_, v___x_4182_);
v___x_4184_ = lean_uint64_dec_lt(v_remainder_4181_, v_half_4183_);
if (v___x_4184_ == 0)
{
uint8_t v___x_4185_; 
v___x_4185_ = lean_uint64_dec_lt(v_half_4183_, v_remainder_4181_);
if (v___x_4185_ == 0)
{
uint64_t v___x_4186_; uint8_t v___x_4187_; 
v___x_4186_ = lean_uint64_land(v_quotient_4177_, v___x_4178_);
v___x_4187_ = lean_uint64_dec_eq(v___x_4186_, v___y_4135_);
if (v___x_4187_ == 0)
{
uint64_t v___x_4188_; 
v___x_4188_ = lean_uint64_add(v_quotient_4177_, v___x_4178_);
v___y_4026_ = v___y_4132_;
v___y_4027_ = v___y_4133_;
v___y_4028_ = v___y_4135_;
v___y_4029_ = v___x_4188_;
goto v___jp_4025_;
}
else
{
v___y_4026_ = v___y_4132_;
v___y_4027_ = v___y_4133_;
v___y_4028_ = v___y_4135_;
v___y_4029_ = v_quotient_4177_;
goto v___jp_4025_;
}
}
else
{
uint64_t v___x_4189_; 
v___x_4189_ = lean_uint64_add(v_quotient_4177_, v___x_4178_);
v___y_4026_ = v___y_4132_;
v___y_4027_ = v___y_4133_;
v___y_4028_ = v___y_4135_;
v___y_4029_ = v___x_4189_;
goto v___jp_4025_;
}
}
else
{
v___y_4026_ = v___y_4132_;
v___y_4027_ = v___y_4133_;
v___y_4028_ = v___y_4135_;
v___y_4029_ = v_quotient_4177_;
goto v___jp_4025_;
}
}
}
else
{
v___y_4026_ = v___y_4132_;
v___y_4027_ = v___y_4133_;
v___y_4028_ = v___y_4135_;
v___y_4029_ = v___y_4131_;
goto v___jp_4025_;
}
}
}
}
v___jp_4190_:
{
uint64_t v___x_4198_; uint64_t v___x_4199_; uint8_t v___x_4200_; 
v___x_4198_ = 1ULL;
v___x_4199_ = lean_uint64_shift_right(v___y_4196_, v___x_4198_);
v___x_4200_ = lean_uint64_dec_eq(v___x_4199_, v___y_4195_);
if (v___x_4200_ == 0)
{
uint64_t v___x_4201_; 
v___x_4201_ = lean_uint64_add(v___y_4197_, v___x_4198_);
v___y_4131_ = v___y_4191_;
v___y_4132_ = v___y_4193_;
v___y_4133_ = v___y_4192_;
v___y_4134_ = v___y_4194_;
v___y_4135_ = v___y_4195_;
v___y_4136_ = v___x_4201_;
goto v___jp_4130_;
}
else
{
v___y_4131_ = v___y_4191_;
v___y_4132_ = v___y_4193_;
v___y_4133_ = v___y_4192_;
v___y_4134_ = v___y_4194_;
v___y_4135_ = v___y_4195_;
v___y_4136_ = v___y_4197_;
goto v___jp_4130_;
}
}
v___jp_4202_:
{
uint64_t v___x_4212_; uint8_t v___x_4213_; 
v___x_4212_ = lean_uint64_shift_right(v___y_4206_, v___y_4209_);
v___x_4213_ = lean_uint64_dec_eq(v___x_4212_, v___y_4208_);
if (v___x_4213_ == 0)
{
uint64_t v___x_4214_; 
v___x_4214_ = lean_uint64_add(v___y_4210_, v___y_4209_);
v___y_4191_ = v___y_4203_;
v___y_4192_ = v___y_4205_;
v___y_4193_ = v___y_4204_;
v___y_4194_ = v___y_4207_;
v___y_4195_ = v___y_4208_;
v___y_4196_ = v___y_4211_;
v___y_4197_ = v___x_4214_;
goto v___jp_4190_;
}
else
{
v___y_4191_ = v___y_4203_;
v___y_4192_ = v___y_4205_;
v___y_4193_ = v___y_4204_;
v___y_4194_ = v___y_4207_;
v___y_4195_ = v___y_4208_;
v___y_4196_ = v___y_4211_;
v___y_4197_ = v___y_4210_;
goto v___jp_4190_;
}
}
v___jp_4215_:
{
uint64_t v___x_4223_; uint64_t v___x_4224_; uint8_t v___x_4225_; 
v___x_4223_ = 2ULL;
v___x_4224_ = lean_uint64_shift_right(v___y_4220_, v___x_4223_);
v___x_4225_ = lean_uint64_dec_eq(v___x_4224_, v___y_4221_);
if (v___x_4225_ == 0)
{
v___y_4203_ = v___y_4216_;
v___y_4204_ = v___y_4218_;
v___y_4205_ = v___y_4217_;
v___y_4206_ = v___y_4220_;
v___y_4207_ = v___y_4219_;
v___y_4208_ = v___y_4221_;
v___y_4209_ = v___x_4223_;
v___y_4210_ = v___y_4222_;
v___y_4211_ = v___x_4224_;
goto v___jp_4202_;
}
else
{
v___y_4203_ = v___y_4216_;
v___y_4204_ = v___y_4218_;
v___y_4205_ = v___y_4217_;
v___y_4206_ = v___y_4220_;
v___y_4207_ = v___y_4219_;
v___y_4208_ = v___y_4221_;
v___y_4209_ = v___x_4223_;
v___y_4210_ = v___y_4222_;
v___y_4211_ = v___y_4220_;
goto v___jp_4202_;
}
}
v___jp_4226_:
{
uint64_t v___x_4236_; uint8_t v___x_4237_; 
v___x_4236_ = lean_uint64_shift_right(v___y_4234_, v___y_4228_);
v___x_4237_ = lean_uint64_dec_eq(v___x_4236_, v___y_4233_);
if (v___x_4237_ == 0)
{
uint64_t v___x_4238_; 
v___x_4238_ = lean_uint64_add(v___y_4229_, v___y_4228_);
v___y_4216_ = v___y_4227_;
v___y_4217_ = v___y_4231_;
v___y_4218_ = v___y_4230_;
v___y_4219_ = v___y_4232_;
v___y_4220_ = v___y_4235_;
v___y_4221_ = v___y_4233_;
v___y_4222_ = v___x_4238_;
goto v___jp_4215_;
}
else
{
v___y_4216_ = v___y_4227_;
v___y_4217_ = v___y_4231_;
v___y_4218_ = v___y_4230_;
v___y_4219_ = v___y_4232_;
v___y_4220_ = v___y_4235_;
v___y_4221_ = v___y_4233_;
v___y_4222_ = v___y_4229_;
goto v___jp_4215_;
}
}
v___jp_4239_:
{
uint64_t v___x_4247_; uint64_t v___x_4248_; uint8_t v___x_4249_; 
v___x_4247_ = 4ULL;
v___x_4248_ = lean_uint64_shift_right(v___y_4245_, v___x_4247_);
v___x_4249_ = lean_uint64_dec_eq(v___x_4248_, v___y_4244_);
if (v___x_4249_ == 0)
{
v___y_4227_ = v___y_4240_;
v___y_4228_ = v___x_4247_;
v___y_4229_ = v___y_4246_;
v___y_4230_ = v___y_4242_;
v___y_4231_ = v___y_4241_;
v___y_4232_ = v___y_4243_;
v___y_4233_ = v___y_4244_;
v___y_4234_ = v___y_4245_;
v___y_4235_ = v___x_4248_;
goto v___jp_4226_;
}
else
{
v___y_4227_ = v___y_4240_;
v___y_4228_ = v___x_4247_;
v___y_4229_ = v___y_4246_;
v___y_4230_ = v___y_4242_;
v___y_4231_ = v___y_4241_;
v___y_4232_ = v___y_4243_;
v___y_4233_ = v___y_4244_;
v___y_4234_ = v___y_4245_;
v___y_4235_ = v___y_4245_;
goto v___jp_4226_;
}
}
v___jp_4250_:
{
uint64_t v___x_4260_; uint8_t v___x_4261_; 
v___x_4260_ = lean_uint64_shift_right(v___y_4252_, v___y_4251_);
v___x_4261_ = lean_uint64_dec_eq(v___x_4260_, v___y_4258_);
if (v___x_4261_ == 0)
{
uint64_t v___x_4262_; 
v___x_4262_ = lean_uint64_add(v___y_4257_, v___y_4251_);
v___y_4240_ = v___y_4253_;
v___y_4241_ = v___y_4255_;
v___y_4242_ = v___y_4254_;
v___y_4243_ = v___y_4256_;
v___y_4244_ = v___y_4258_;
v___y_4245_ = v___y_4259_;
v___y_4246_ = v___x_4262_;
goto v___jp_4239_;
}
else
{
v___y_4240_ = v___y_4253_;
v___y_4241_ = v___y_4255_;
v___y_4242_ = v___y_4254_;
v___y_4243_ = v___y_4256_;
v___y_4244_ = v___y_4258_;
v___y_4245_ = v___y_4259_;
v___y_4246_ = v___y_4257_;
goto v___jp_4239_;
}
}
v___jp_4263_:
{
uint64_t v___x_4271_; uint64_t v___x_4272_; uint8_t v___x_4273_; 
v___x_4271_ = 8ULL;
v___x_4272_ = lean_uint64_shift_right(v___y_4265_, v___x_4271_);
v___x_4273_ = lean_uint64_dec_eq(v___x_4272_, v___y_4269_);
if (v___x_4273_ == 0)
{
v___y_4251_ = v___x_4271_;
v___y_4252_ = v___y_4265_;
v___y_4253_ = v___y_4264_;
v___y_4254_ = v___y_4267_;
v___y_4255_ = v___y_4266_;
v___y_4256_ = v___y_4268_;
v___y_4257_ = v___y_4270_;
v___y_4258_ = v___y_4269_;
v___y_4259_ = v___x_4272_;
goto v___jp_4250_;
}
else
{
v___y_4251_ = v___x_4271_;
v___y_4252_ = v___y_4265_;
v___y_4253_ = v___y_4264_;
v___y_4254_ = v___y_4267_;
v___y_4255_ = v___y_4266_;
v___y_4256_ = v___y_4268_;
v___y_4257_ = v___y_4270_;
v___y_4258_ = v___y_4269_;
v___y_4259_ = v___y_4265_;
goto v___jp_4250_;
}
}
v___jp_4274_:
{
uint64_t v___x_4284_; uint8_t v___x_4285_; 
v___x_4284_ = lean_uint64_shift_right(v___y_4275_, v___y_4277_);
v___x_4285_ = lean_uint64_dec_eq(v___x_4284_, v___y_4282_);
if (v___x_4285_ == 0)
{
uint64_t v___x_4286_; 
v___x_4286_ = lean_uint64_add(v___y_4276_, v___y_4277_);
v___y_4264_ = v___y_4278_;
v___y_4265_ = v___y_4283_;
v___y_4266_ = v___y_4280_;
v___y_4267_ = v___y_4279_;
v___y_4268_ = v___y_4281_;
v___y_4269_ = v___y_4282_;
v___y_4270_ = v___x_4286_;
goto v___jp_4263_;
}
else
{
v___y_4264_ = v___y_4278_;
v___y_4265_ = v___y_4283_;
v___y_4266_ = v___y_4280_;
v___y_4267_ = v___y_4279_;
v___y_4268_ = v___y_4281_;
v___y_4269_ = v___y_4282_;
v___y_4270_ = v___y_4276_;
goto v___jp_4263_;
}
}
v___jp_4287_:
{
uint64_t v___x_4295_; uint64_t v___x_4296_; uint8_t v___x_4297_; 
v___x_4295_ = 16ULL;
v___x_4296_ = lean_uint64_shift_right(v___y_4288_, v___x_4295_);
v___x_4297_ = lean_uint64_dec_eq(v___x_4296_, v___y_4293_);
if (v___x_4297_ == 0)
{
v___y_4275_ = v___y_4288_;
v___y_4276_ = v___y_4294_;
v___y_4277_ = v___x_4295_;
v___y_4278_ = v___y_4289_;
v___y_4279_ = v___y_4291_;
v___y_4280_ = v___y_4290_;
v___y_4281_ = v___y_4292_;
v___y_4282_ = v___y_4293_;
v___y_4283_ = v___x_4296_;
goto v___jp_4274_;
}
else
{
v___y_4275_ = v___y_4288_;
v___y_4276_ = v___y_4294_;
v___y_4277_ = v___x_4295_;
v___y_4278_ = v___y_4289_;
v___y_4279_ = v___y_4291_;
v___y_4280_ = v___y_4290_;
v___y_4281_ = v___y_4292_;
v___y_4282_ = v___y_4293_;
v___y_4283_ = v___y_4288_;
goto v___jp_4274_;
}
}
v___jp_4298_:
{
uint64_t v___x_4306_; uint8_t v___x_4307_; 
v___x_4306_ = lean_uint64_shift_right(v___y_4300_, v___y_4299_);
v___x_4307_ = lean_uint64_dec_eq(v___x_4306_, v___y_4304_);
if (v___x_4307_ == 0)
{
v___y_4288_ = v___y_4305_;
v___y_4289_ = v___y_4300_;
v___y_4290_ = v___y_4302_;
v___y_4291_ = v___y_4301_;
v___y_4292_ = v___y_4303_;
v___y_4293_ = v___y_4304_;
v___y_4294_ = v___y_4299_;
goto v___jp_4287_;
}
else
{
v___y_4288_ = v___y_4305_;
v___y_4289_ = v___y_4300_;
v___y_4290_ = v___y_4302_;
v___y_4291_ = v___y_4301_;
v___y_4292_ = v___y_4303_;
v___y_4293_ = v___y_4304_;
v___y_4294_ = v___y_4304_;
goto v___jp_4287_;
}
}
v___jp_4308_:
{
uint64_t v___x_4313_; uint8_t v___x_4314_; 
v___x_4313_ = 0ULL;
v___x_4314_ = lean_uint64_dec_eq(v___y_4309_, v___x_4313_);
if (v___x_4314_ == 0)
{
uint64_t v___x_4315_; uint64_t v___x_4316_; uint8_t v___x_4317_; 
v___x_4315_ = 32ULL;
v___x_4316_ = lean_uint64_shift_right(v___y_4309_, v___x_4315_);
v___x_4317_ = lean_uint64_dec_eq(v___x_4316_, v___x_4313_);
if (v___x_4317_ == 0)
{
v___y_4299_ = v___x_4315_;
v___y_4300_ = v___y_4309_;
v___y_4301_ = v___y_4311_;
v___y_4302_ = v___y_4310_;
v___y_4303_ = v___y_4312_;
v___y_4304_ = v___x_4313_;
v___y_4305_ = v___x_4316_;
goto v___jp_4298_;
}
else
{
v___y_4299_ = v___x_4315_;
v___y_4300_ = v___y_4309_;
v___y_4301_ = v___y_4311_;
v___y_4302_ = v___y_4310_;
v___y_4303_ = v___y_4312_;
v___y_4304_ = v___x_4313_;
v___y_4305_ = v___y_4309_;
goto v___jp_4298_;
}
}
else
{
if (v___y_4311_ == 0)
{
uint32_t v___x_4318_; 
v___x_4318_ = 0;
return v___x_4318_;
}
else
{
uint32_t v___x_4319_; 
v___x_4319_ = 2147483648;
return v___x_4319_;
}
}
}
v___jp_4320_:
{
uint64_t v___x_4327_; uint64_t v___x_4328_; uint64_t v___x_4329_; uint8_t v___x_4330_; 
v___x_4327_ = lean_uint64_mul(v___y_4324_, v___y_4325_);
v___x_4328_ = lean_uint64_add(v___y_4321_, v___y_4326_);
v___x_4329_ = 281474976710656ULL;
v___x_4330_ = lean_uint64_dec_lt(v___x_4327_, v___x_4329_);
if (v___x_4330_ == 0)
{
v___y_4309_ = v___x_4327_;
v___y_4310_ = v___y_4323_;
v___y_4311_ = v___y_4322_;
v___y_4312_ = v___x_4328_;
goto v___jp_4308_;
}
else
{
uint64_t v___x_4331_; uint8_t v___x_4332_; 
v___x_4331_ = 123ULL;
v___x_4332_ = lean_uint64_dec_le(v___x_4328_, v___x_4331_);
if (v___x_4332_ == 0)
{
v___y_4309_ = v___x_4327_;
v___y_4310_ = v___y_4323_;
v___y_4311_ = v___y_4322_;
v___y_4312_ = v___x_4328_;
goto v___jp_4308_;
}
else
{
uint64_t v___x_4333_; uint8_t v___x_4334_; 
v___x_4333_ = 0ULL;
v___x_4334_ = lean_uint64_dec_eq(v___x_4327_, v___x_4333_);
if (v___x_4334_ == 0)
{
uint64_t v___x_4335_; uint64_t v___x_4336_; uint8_t v___x_4337_; 
v___x_4335_ = 149ULL;
v___x_4336_ = lean_uint64_sub(v___x_4335_, v___x_4328_);
v___x_4337_ = lean_uint64_dec_eq(v___x_4336_, v___x_4333_);
if (v___x_4337_ == 0)
{
uint64_t v___x_4338_; uint8_t v___x_4339_; 
v___x_4338_ = 64ULL;
v___x_4339_ = lean_uint64_dec_lt(v___x_4336_, v___x_4338_);
if (v___x_4339_ == 0)
{
uint8_t v___x_4340_; 
v___x_4340_ = lean_uint64_dec_eq(v___x_4336_, v___x_4338_);
if (v___x_4340_ == 0)
{
v___y_4047_ = v___x_4333_;
v___y_4048_ = v___y_4322_;
v___y_4049_ = v___y_4323_;
v___y_4050_ = v___x_4333_;
goto v___jp_4046_;
}
else
{
uint64_t v___x_4341_; uint8_t v___x_4342_; 
v___x_4341_ = 9223372036854775808ULL;
v___x_4342_ = lean_uint64_dec_lt(v___x_4341_, v___x_4327_);
if (v___x_4342_ == 0)
{
v___y_4047_ = v___x_4333_;
v___y_4048_ = v___y_4322_;
v___y_4049_ = v___y_4323_;
v___y_4050_ = v___x_4333_;
goto v___jp_4046_;
}
else
{
uint64_t v___x_4343_; 
v___x_4343_ = 1ULL;
v___y_4047_ = v___x_4333_;
v___y_4048_ = v___y_4322_;
v___y_4049_ = v___y_4323_;
v___y_4050_ = v___x_4343_;
goto v___jp_4046_;
}
}
}
else
{
uint64_t v_quotient_4344_; uint64_t v___x_4345_; uint64_t v___x_4346_; uint64_t v___x_4347_; uint64_t v_remainder_4348_; uint64_t v___x_4349_; uint64_t v_half_4350_; uint8_t v___x_4351_; 
v_quotient_4344_ = lean_uint64_shift_right(v___x_4327_, v___x_4336_);
v___x_4345_ = 1ULL;
v___x_4346_ = lean_uint64_shift_left(v___x_4345_, v___x_4336_);
v___x_4347_ = lean_uint64_sub(v___x_4346_, v___x_4345_);
v_remainder_4348_ = lean_uint64_land(v___x_4327_, v___x_4347_);
v___x_4349_ = lean_uint64_sub(v___x_4336_, v___x_4345_);
v_half_4350_ = lean_uint64_shift_left(v___x_4345_, v___x_4349_);
v___x_4351_ = lean_uint64_dec_lt(v_remainder_4348_, v_half_4350_);
if (v___x_4351_ == 0)
{
uint8_t v___x_4352_; 
v___x_4352_ = lean_uint64_dec_lt(v_half_4350_, v_remainder_4348_);
if (v___x_4352_ == 0)
{
uint64_t v___x_4353_; uint8_t v___x_4354_; 
v___x_4353_ = lean_uint64_land(v_quotient_4344_, v___x_4345_);
v___x_4354_ = lean_uint64_dec_eq(v___x_4353_, v___x_4333_);
if (v___x_4354_ == 0)
{
uint64_t v___x_4355_; 
v___x_4355_ = lean_uint64_add(v_quotient_4344_, v___x_4345_);
v___y_4047_ = v___x_4333_;
v___y_4048_ = v___y_4322_;
v___y_4049_ = v___y_4323_;
v___y_4050_ = v___x_4355_;
goto v___jp_4046_;
}
else
{
v___y_4047_ = v___x_4333_;
v___y_4048_ = v___y_4322_;
v___y_4049_ = v___y_4323_;
v___y_4050_ = v_quotient_4344_;
goto v___jp_4046_;
}
}
else
{
uint64_t v___x_4356_; 
v___x_4356_ = lean_uint64_add(v_quotient_4344_, v___x_4345_);
v___y_4047_ = v___x_4333_;
v___y_4048_ = v___y_4322_;
v___y_4049_ = v___y_4323_;
v___y_4050_ = v___x_4356_;
goto v___jp_4046_;
}
}
else
{
v___y_4047_ = v___x_4333_;
v___y_4048_ = v___y_4322_;
v___y_4049_ = v___y_4323_;
v___y_4050_ = v_quotient_4344_;
goto v___jp_4046_;
}
}
}
else
{
v___y_4047_ = v___x_4333_;
v___y_4048_ = v___y_4322_;
v___y_4049_ = v___y_4323_;
v___y_4050_ = v___x_4327_;
goto v___jp_4046_;
}
}
else
{
if (v___y_4322_ == 0)
{
uint32_t v___x_4357_; 
v___x_4357_ = 0;
return v___x_4357_;
}
else
{
uint32_t v___x_4358_; 
v___x_4358_ = 2147483648;
return v___x_4358_;
}
}
}
}
}
v___jp_4362_:
{
uint64_t v___x_4368_; uint64_t v___x_4369_; uint8_t v___x_4370_; 
v___x_4368_ = lean_uint32_to_uint64(v_ey_4361_);
v___x_4369_ = 0ULL;
v___x_4370_ = lean_uint64_dec_eq(v___x_4368_, v___x_4369_);
if (v___x_4370_ == 0)
{
uint64_t v___x_4371_; uint64_t v___x_4372_; 
v___x_4371_ = 1ULL;
v___x_4372_ = lean_uint64_sub(v___x_4368_, v___x_4371_);
v___y_4321_ = v___y_4367_;
v___y_4322_ = v___y_4365_;
v___y_4323_ = v___y_4364_;
v___y_4324_ = v___y_4363_;
v___y_4325_ = v___y_4366_;
v___y_4326_ = v___x_4372_;
goto v___jp_4320_;
}
else
{
v___y_4321_ = v___y_4367_;
v___y_4322_ = v___y_4365_;
v___y_4323_ = v___y_4364_;
v___y_4324_ = v___y_4363_;
v___y_4325_ = v___y_4366_;
v___y_4326_ = v___x_4369_;
goto v___jp_4320_;
}
}
v___jp_4373_:
{
uint64_t v___x_4378_; uint64_t v___x_4379_; uint8_t v___x_4380_; 
v___x_4378_ = lean_uint32_to_uint64(v_ex_4359_);
v___x_4379_ = 0ULL;
v___x_4380_ = lean_uint64_dec_eq(v___x_4378_, v___x_4379_);
if (v___x_4380_ == 0)
{
uint64_t v___x_4381_; uint64_t v___x_4382_; 
v___x_4381_ = 1ULL;
v___x_4382_ = lean_uint64_sub(v___x_4378_, v___x_4381_);
v___y_4363_ = v___y_4376_;
v___y_4364_ = v___y_4375_;
v___y_4365_ = v___y_4374_;
v___y_4366_ = v___y_4377_;
v___y_4367_ = v___x_4382_;
goto v___jp_4362_;
}
else
{
v___y_4363_ = v___y_4376_;
v___y_4364_ = v___y_4375_;
v___y_4365_ = v___y_4374_;
v___y_4366_ = v___y_4377_;
v___y_4367_ = v___x_4379_;
goto v___jp_4362_;
}
}
v___jp_4383_:
{
uint32_t v___x_4388_; uint8_t v___x_4389_; 
v___x_4388_ = 0;
v___x_4389_ = lean_uint32_dec_eq(v_ey_4361_, v___x_4388_);
if (v___x_4389_ == 0)
{
uint64_t v___x_4390_; uint64_t v___x_4391_; uint64_t v___x_4392_; 
v___x_4390_ = lean_uint32_to_uint64(v___y_4384_);
v___x_4391_ = 8388608ULL;
v___x_4392_ = lean_uint64_lor(v___x_4390_, v___x_4391_);
v___y_4374_ = v___y_4386_;
v___y_4375_ = v___y_4385_;
v___y_4376_ = v___y_4387_;
v___y_4377_ = v___x_4392_;
goto v___jp_4373_;
}
else
{
uint64_t v___x_4393_; 
v___x_4393_ = lean_uint32_to_uint64(v___y_4384_);
v___y_4374_ = v___y_4386_;
v___y_4375_ = v___y_4385_;
v___y_4376_ = v___y_4387_;
v___y_4377_ = v___x_4393_;
goto v___jp_4373_;
}
}
v___jp_4394_:
{
uint32_t v___x_4396_; uint32_t v_xFraction_4397_; uint32_t v_yFraction_4398_; uint32_t v___x_4399_; uint8_t v___x_4400_; 
v___x_4396_ = 8388607;
v_xFraction_4397_ = lean_uint32_land(v___y_3914_, v___x_4396_);
v_yFraction_4398_ = lean_uint32_land(v___y_3915_, v___x_4396_);
v___x_4399_ = 0;
v___x_4400_ = lean_uint32_dec_eq(v_ex_4359_, v___x_4399_);
if (v___x_4400_ == 0)
{
uint64_t v___x_4401_; uint64_t v___x_4402_; uint64_t v___x_4403_; 
v___x_4401_ = lean_uint32_to_uint64(v_xFraction_4397_);
v___x_4402_ = 8388608ULL;
v___x_4403_ = lean_uint64_lor(v___x_4401_, v___x_4402_);
v___y_4384_ = v_yFraction_4398_;
v___y_4385_ = v___x_4396_;
v___y_4386_ = v___y_4395_;
v___y_4387_ = v___x_4403_;
goto v___jp_4383_;
}
else
{
uint64_t v___x_4404_; 
v___x_4404_ = lean_uint32_to_uint64(v_xFraction_4397_);
v___y_4384_ = v_yFraction_4398_;
v___y_4385_ = v___x_4396_;
v___y_4386_ = v___y_4395_;
v___y_4387_ = v___x_4404_;
goto v___jp_4383_;
}
}
v___jp_4405_:
{
if (v___y_4407_ == 0)
{
v___y_4395_ = v___x_3913_;
goto v___jp_4394_;
}
else
{
v___y_4395_ = v___y_4406_;
goto v___jp_4394_;
}
}
v___jp_4411_:
{
if (v___y_4412_ == 0)
{
if (v___y_4414_ == 0)
{
v___y_4406_ = v___y_4413_;
v___y_4407_ = v___x_4410_;
goto v___jp_4405_;
}
else
{
v___y_4395_ = v___x_3913_;
goto v___jp_4394_;
}
}
else
{
v___y_4406_ = v___y_4413_;
v___y_4407_ = v___y_4414_;
goto v___jp_4405_;
}
}
v___jp_4415_:
{
uint32_t v___x_4418_; uint32_t v___x_4419_; uint32_t v___x_4420_; uint8_t v___x_4421_; 
v___x_4418_ = 2147483648;
v___x_4419_ = lean_uint32_land(v___y_3915_, v___x_4418_);
v___x_4420_ = 0;
v___x_4421_ = lean_uint32_dec_eq(v___x_4419_, v___x_4420_);
if (v___x_4421_ == 0)
{
v___y_4412_ = v___y_4417_;
v___y_4413_ = v___y_4416_;
v___y_4414_ = v___x_3913_;
goto v___jp_4411_;
}
else
{
v___y_4412_ = v___y_4417_;
v___y_4413_ = v___y_4416_;
v___y_4414_ = v___y_4416_;
goto v___jp_4411_;
}
}
v___jp_4422_:
{
if (v___y_4423_ == 0)
{
uint32_t v___x_4424_; uint32_t v___x_4425_; uint32_t v___x_4426_; uint8_t v___x_4427_; 
v___x_4424_ = 2147483648;
v___x_4425_ = lean_uint32_land(v___y_3914_, v___x_4424_);
v___x_4426_ = 0;
v___x_4427_ = lean_uint32_dec_eq(v___x_4425_, v___x_4426_);
if (v___x_4427_ == 0)
{
v___y_4416_ = v___y_4423_;
v___y_4417_ = v___x_3913_;
goto v___jp_4415_;
}
else
{
v___y_4416_ = v___y_4423_;
v___y_4417_ = v___y_4423_;
goto v___jp_4415_;
}
}
else
{
lean_object* v___x_4428_; lean_object* v___x_4429_; lean_object* v___x_4430_; uint32_t v___x_4431_; 
v___x_4428_ = lean_uint32_to_nat(v___y_3914_);
v___x_4429_ = lean_uint32_to_nat(v___y_3915_);
v___x_4430_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_4428_, v___x_4429_);
v___x_4431_ = lean_uint32_of_nat(v___x_4430_);
lean_dec(v___x_4430_);
return v___x_4431_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__4___boxed(lean_object* v___x_4446_, lean_object* v___y_4447_, lean_object* v___y_4448_){
_start:
{
uint8_t v___x_14874__boxed_4449_; uint32_t v___y_14875__boxed_4450_; uint32_t v___y_14876__boxed_4451_; uint32_t v_res_4452_; lean_object* v_r_4453_; 
v___x_14874__boxed_4449_ = lean_unbox(v___x_4446_);
v___y_14875__boxed_4450_ = lean_unbox_uint32(v___y_4447_);
lean_dec(v___y_4447_);
v___y_14876__boxed_4451_ = lean_unbox_uint32(v___y_4448_);
lean_dec(v___y_4448_);
v_res_4452_ = lp_competition_main___lam__4(v___x_14874__boxed_4449_, v___y_14875__boxed_4450_, v___y_14876__boxed_4451_);
v_r_4453_ = lean_box_uint32(v_res_4452_);
return v_r_4453_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_4472_; lean_object* v___x_4473_; lean_object* v___x_4474_; uint8_t v___x_4475_; 
v___x_4472_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_4473_ = lean_io_getenv(v___x_4472_);
v___x_4474_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_4475_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_4473_, v___x_4474_);
if (v___x_4475_ == 0)
{
lean_object* v___x_4476_; uint8_t v___x_4477_; 
v___x_4476_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_4477_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_4473_, v___x_4476_);
if (v___x_4477_ == 0)
{
lean_object* v___x_4478_; uint8_t v___x_4479_; 
v___x_4478_ = ((lean_object*)(lp_competition_main___closed__6));
v___x_4479_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_4473_, v___x_4478_);
lean_dec(v___x_4473_);
if (v___x_4479_ == 0)
{
lean_object* v___x_4480_; lean_object* v___x_4481_; 
v___x_4480_ = ((lean_object*)(lp_competition_main___closed__8));
v___x_4481_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_4481_, 0, v___x_4480_);
return v___x_4481_;
}
else
{
lean_object* v___f_4482_; lean_object* v___x_4483_; lean_object* v___f_4484_; lean_object* v___x_4485_; lean_object* v___x_4486_; lean_object* v___x_4487_; 
v___f_4482_ = ((lean_object*)(lp_competition_main___closed__9));
v___x_4483_ = lean_box(v___x_4479_);
v___f_4484_ = lean_alloc_closure((void*)(lp_competition_main___lam__1___boxed), 3, 1);
lean_closure_set(v___f_4484_, 0, v___x_4483_);
v___x_4485_ = ((lean_object*)(lp_competition_main___closed__10));
v___x_4486_ = ((lean_object*)(lp_competition_main___closed__11));
v___x_4487_ = lp_competition_Bench_Suite_run(v___f_4482_, v___f_4484_, v___x_4485_, v___x_4486_);
return v___x_4487_;
}
}
else
{
lean_object* v___f_4488_; lean_object* v___x_4489_; lean_object* v___f_4490_; lean_object* v___x_4491_; lean_object* v___x_4492_; lean_object* v___x_4493_; 
lean_dec(v___x_4473_);
v___f_4488_ = ((lean_object*)(lp_competition_main___closed__9));
v___x_4489_ = lean_box(v___x_4477_);
v___f_4490_ = lean_alloc_closure((void*)(lp_competition_main___lam__3___boxed), 3, 1);
lean_closure_set(v___f_4490_, 0, v___x_4489_);
v___x_4491_ = ((lean_object*)(lp_competition_main___closed__10));
v___x_4492_ = ((lean_object*)(lp_competition_main___closed__12));
v___x_4493_ = lp_competition_Bench_Suite_run(v___f_4488_, v___f_4490_, v___x_4491_, v___x_4492_);
return v___x_4493_;
}
}
else
{
lean_object* v___f_4494_; lean_object* v___x_4495_; lean_object* v___f_4496_; lean_object* v___x_4497_; lean_object* v___x_4498_; lean_object* v___x_4499_; 
lean_dec(v___x_4473_);
v___f_4494_ = ((lean_object*)(lp_competition_main___closed__9));
v___x_4495_ = lean_box(v___x_4475_);
v___f_4496_ = lean_alloc_closure((void*)(lp_competition_main___lam__4___boxed), 3, 1);
lean_closure_set(v___f_4496_, 0, v___x_4495_);
v___x_4497_ = ((lean_object*)(lp_competition_main___closed__10));
v___x_4498_ = ((lean_object*)(lp_competition_main___closed__11));
v___x_4499_ = lp_competition_Bench_Suite_run(v___f_4494_, v___f_4496_, v___x_4497_, v___x_4498_);
return v___x_4499_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_4500_){
_start:
{
lean_object* v_res_4501_; 
v_res_4501_ = _lean_main();
return v_res_4501_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_competition_BenchFull(uint8_t builtin);
lean_object* initialize_competition_BenchSuite(uint8_t builtin);
lean_object* initialize_competition_Submission(uint8_t builtin);
void lean_initialize();
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_competition_R22RuntimeCostMain(uint8_t builtin) {
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
  res = initialize_competition_R22RuntimeCostMain(1 /* builtin */);
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
