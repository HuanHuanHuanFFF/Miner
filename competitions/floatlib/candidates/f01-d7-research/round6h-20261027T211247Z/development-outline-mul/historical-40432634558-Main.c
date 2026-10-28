// Lean compiler output
// Module: R19RuntimeCostMain
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
lean_object* lp_competition_Submission_sum___boxed(lean_object*, lean_object*);
uint8_t lean_uint64_dec_eq(uint64_t, uint64_t);
uint32_t lean_uint64_to_uint32(uint64_t);
uint32_t lp_competition_Submission_FastMul_mul(uint32_t, uint32_t);
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
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word(lean_object*, lean_object*, lean_object*);
uint32_t lean_uint32_xor(uint32_t, uint32_t);
lean_object* lp_competition_Submission_bmm(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lean_io_getenv(lean_object*);
uint8_t l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(lean_object*, lean_object*);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(lean_object*, lean_object*);
lean_object* lp_competition_Bench_Suite_run(lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_ctor_object lp_competition_r19CostGuardedMul___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*3 + 8, .m_other = 3, .m_tag = 0}, .m_objs = {((lean_object*)(((size_t)(8) << 1) | 1)),((lean_object*)(((size_t)(23) << 1) | 1)),((lean_object*)(((size_t)(127) << 1) | 1)),LEAN_SCALAR_PTR_LITERAL(0, 0, 0, 0, 0, 0, 0, 0)}};
static const lean_object* lp_competition_r19CostGuardedMul___closed__0 = (const lean_object*)&lp_competition_r19CostGuardedMul___closed__0_value;
LEAN_EXPORT uint32_t lp_competition_r19CostGuardedMul(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_r19CostGuardedMul___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint8_t, uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint8_t, uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition_main___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 14, .m_capacity = 14, .m_length = 13, .m_data = "BENCH_VARIANT"};
static const lean_object* lp_competition_main___closed__0 = (const lean_object*)&lp_competition_main___closed__0_value;
static const lean_string_object lp_competition_main___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 8, .m_capacity = 8, .m_length = 7, .m_data = "control"};
static const lean_object* lp_competition_main___closed__1 = (const lean_object*)&lp_competition_main___closed__1_value;
static const lean_ctor_object lp_competition_main___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__1_value)}};
static const lean_object* lp_competition_main___closed__2 = (const lean_object*)&lp_competition_main___closed__2_value;
static const lean_string_object lp_competition_main___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 8, .m_capacity = 8, .m_length = 7, .m_data = "guarded"};
static const lean_object* lp_competition_main___closed__3 = (const lean_object*)&lp_competition_main___closed__3_value;
static const lean_ctor_object lp_competition_main___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__3_value)}};
static const lean_object* lp_competition_main___closed__4 = (const lean_object*)&lp_competition_main___closed__4_value;
static const lean_string_object lp_competition_main___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 41, .m_capacity = 41, .m_length = 40, .m_data = "BENCH_VARIANT must be control or guarded"};
static const lean_object* lp_competition_main___closed__5 = (const lean_object*)&lp_competition_main___closed__5_value;
static const lean_ctor_object lp_competition_main___closed__6_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_main___closed__5_value)}};
static const lean_object* lp_competition_main___closed__6 = (const lean_object*)&lp_competition_main___closed__6_value;
static const lean_closure_object lp_competition_main___closed__7_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_main___lam__0___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__7 = (const lean_object*)&lp_competition_main___closed__7_value;
static const lean_closure_object lp_competition_main___closed__8_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_sum___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__8 = (const lean_object*)&lp_competition_main___closed__8_value;
static const lean_closure_object lp_competition_main___closed__9_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_bmm, .m_arity = 6, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__9 = (const lean_object*)&lp_competition_main___closed__9_value;
LEAN_EXPORT lean_object* _lean_main();
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_r19CostGuardedMul(uint32_t v_x_6_, uint32_t v_y_7_){
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
v___x_1401_ = ((lean_object*)(lp_competition_r19CostGuardedMul___closed__0));
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
v___x_1526_ = ((lean_object*)(lp_competition_r19CostGuardedMul___closed__0));
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
v___x_1553_ = ((lean_object*)(lp_competition_r19CostGuardedMul___closed__0));
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
LEAN_EXPORT lean_object* lp_competition_r19CostGuardedMul___boxed(lean_object* v_x_1635_, lean_object* v_y_1636_){
_start:
{
uint32_t v_x_boxed_1637_; uint32_t v_y_boxed_1638_; uint32_t v_res_1639_; lean_object* v_r_1640_; 
v_x_boxed_1637_ = lean_unbox_uint32(v_x_1635_);
lean_dec(v_x_1635_);
v_y_boxed_1638_ = lean_unbox_uint32(v_y_1636_);
lean_dec(v_y_1636_);
v_res_1639_ = lp_competition_r19CostGuardedMul(v_x_boxed_1637_, v_y_boxed_1638_);
v_r_1640_ = lean_box_uint32(v_res_1639_);
return v_r_1640_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t v___y_1641_, uint32_t v___y_1642_){
_start:
{
uint8_t v___y_1649_; uint8_t v___y_1663_; uint8_t v___y_1677_; uint8_t v___y_1694_; float v___y_1701_; float v___y_1702_; float v___y_1716_; uint8_t v___y_1717_; float v___y_1732_; uint8_t v___y_1742_; uint32_t v___x_1756_; uint32_t v_a_1757_; uint32_t v___x_1758_; uint32_t v___x_1759_; uint32_t v___x_1760_; uint8_t v___x_1761_; 
v___x_1756_ = 2147483647;
v_a_1757_ = lean_uint32_land(v___y_1641_, v___x_1756_);
v___x_1758_ = 201326591;
v___x_1759_ = 1;
v___x_1760_ = lean_uint32_sub(v_a_1757_, v___x_1759_);
v___x_1761_ = lean_uint32_dec_le(v___x_1758_, v___x_1760_);
if (v___x_1761_ == 0)
{
v___y_1742_ = v___x_1761_;
goto v___jp_1741_;
}
else
{
uint32_t v___x_1762_; uint8_t v___x_1763_; 
v___x_1762_ = 2139095040;
v___x_1763_ = lean_uint32_dec_lt(v_a_1757_, v___x_1762_);
v___y_1742_ = v___x_1763_;
goto v___jp_1741_;
}
v___jp_1643_:
{
lean_object* v___x_1644_; lean_object* v___x_1645_; lean_object* v___x_1646_; uint32_t v___x_1647_; 
v___x_1644_ = lean_uint32_to_nat(v___y_1641_);
v___x_1645_ = lean_uint32_to_nat(v___y_1642_);
v___x_1646_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_1644_, v___x_1645_);
v___x_1647_ = lean_uint32_of_nat(v___x_1646_);
lean_dec(v___x_1646_);
return v___x_1647_;
}
v___jp_1648_:
{
if (v___y_1649_ == 0)
{
goto v___jp_1643_;
}
else
{
uint32_t v___x_1650_; uint32_t v___x_1651_; 
v___x_1650_ = 4194304;
v___x_1651_ = lean_uint32_lor(v___y_1642_, v___x_1650_);
return v___x_1651_;
}
}
v___jp_1652_:
{
uint32_t v___x_1653_; uint32_t v___x_1654_; uint32_t v___x_1655_; uint32_t v___x_1656_; uint8_t v___x_1657_; 
v___x_1653_ = 23;
v___x_1654_ = lean_uint32_shift_right(v___y_1642_, v___x_1653_);
v___x_1655_ = 255;
v___x_1656_ = lean_uint32_land(v___x_1654_, v___x_1655_);
v___x_1657_ = lean_uint32_dec_eq(v___x_1656_, v___x_1655_);
if (v___x_1657_ == 0)
{
v___y_1649_ = v___x_1657_;
goto v___jp_1648_;
}
else
{
uint32_t v___x_1658_; uint32_t v___x_1659_; uint32_t v___x_1660_; uint8_t v___x_1661_; 
v___x_1658_ = 8388607;
v___x_1659_ = lean_uint32_land(v___y_1642_, v___x_1658_);
v___x_1660_ = 0;
v___x_1661_ = lean_uint32_dec_eq(v___x_1659_, v___x_1660_);
if (v___x_1661_ == 0)
{
v___y_1649_ = v___x_1657_;
goto v___jp_1648_;
}
else
{
goto v___jp_1643_;
}
}
}
v___jp_1662_:
{
if (v___y_1663_ == 0)
{
goto v___jp_1652_;
}
else
{
uint32_t v___x_1664_; uint32_t v___x_1665_; 
v___x_1664_ = 4194304;
v___x_1665_ = lean_uint32_lor(v___y_1641_, v___x_1664_);
return v___x_1665_;
}
}
v___jp_1666_:
{
uint32_t v___x_1667_; uint32_t v___x_1668_; uint32_t v___x_1669_; uint32_t v___x_1670_; uint8_t v___x_1671_; 
v___x_1667_ = 23;
v___x_1668_ = lean_uint32_shift_right(v___y_1641_, v___x_1667_);
v___x_1669_ = 255;
v___x_1670_ = lean_uint32_land(v___x_1668_, v___x_1669_);
v___x_1671_ = lean_uint32_dec_eq(v___x_1670_, v___x_1669_);
if (v___x_1671_ == 0)
{
v___y_1663_ = v___x_1671_;
goto v___jp_1662_;
}
else
{
uint32_t v___x_1672_; uint32_t v___x_1673_; uint32_t v___x_1674_; uint8_t v___x_1675_; 
v___x_1672_ = 8388607;
v___x_1673_ = lean_uint32_land(v___y_1641_, v___x_1672_);
v___x_1674_ = 0;
v___x_1675_ = lean_uint32_dec_eq(v___x_1673_, v___x_1674_);
if (v___x_1675_ == 0)
{
v___y_1663_ = v___x_1671_;
goto v___jp_1662_;
}
else
{
goto v___jp_1652_;
}
}
}
v___jp_1676_:
{
if (v___y_1677_ == 0)
{
goto v___jp_1666_;
}
else
{
uint32_t v___x_1678_; uint32_t v___x_1679_; uint32_t v___x_1680_; uint8_t v___x_1681_; 
v___x_1678_ = 4194304;
v___x_1679_ = lean_uint32_land(v___y_1642_, v___x_1678_);
v___x_1680_ = 0;
v___x_1681_ = lean_uint32_dec_eq(v___x_1679_, v___x_1680_);
if (v___x_1681_ == 0)
{
goto v___jp_1666_;
}
else
{
uint32_t v___x_1682_; 
v___x_1682_ = lean_uint32_lor(v___y_1642_, v___x_1678_);
return v___x_1682_;
}
}
}
v___jp_1683_:
{
uint32_t v___x_1684_; uint32_t v___x_1685_; uint32_t v___x_1686_; uint32_t v___x_1687_; uint8_t v___x_1688_; 
v___x_1684_ = 23;
v___x_1685_ = lean_uint32_shift_right(v___y_1642_, v___x_1684_);
v___x_1686_ = 255;
v___x_1687_ = lean_uint32_land(v___x_1685_, v___x_1686_);
v___x_1688_ = lean_uint32_dec_eq(v___x_1687_, v___x_1686_);
if (v___x_1688_ == 0)
{
v___y_1677_ = v___x_1688_;
goto v___jp_1676_;
}
else
{
uint32_t v___x_1689_; uint32_t v___x_1690_; uint32_t v___x_1691_; uint8_t v___x_1692_; 
v___x_1689_ = 8388607;
v___x_1690_ = lean_uint32_land(v___y_1642_, v___x_1689_);
v___x_1691_ = 0;
v___x_1692_ = lean_uint32_dec_eq(v___x_1690_, v___x_1691_);
if (v___x_1692_ == 0)
{
v___y_1677_ = v___x_1688_;
goto v___jp_1676_;
}
else
{
goto v___jp_1666_;
}
}
}
v___jp_1693_:
{
if (v___y_1694_ == 0)
{
goto v___jp_1683_;
}
else
{
uint32_t v___x_1695_; uint32_t v___x_1696_; uint32_t v___x_1697_; uint8_t v___x_1698_; 
v___x_1695_ = 4194304;
v___x_1696_ = lean_uint32_land(v___y_1641_, v___x_1695_);
v___x_1697_ = 0;
v___x_1698_ = lean_uint32_dec_eq(v___x_1696_, v___x_1697_);
if (v___x_1698_ == 0)
{
goto v___jp_1683_;
}
else
{
uint32_t v___x_1699_; 
v___x_1699_ = lean_uint32_lor(v___y_1641_, v___x_1695_);
return v___x_1699_;
}
}
}
v___jp_1700_:
{
float v_result_1703_; uint8_t v___x_1704_; 
v_result_1703_ = lean_float32_add(v___y_1701_, v___y_1702_);
v___x_1704_ = lean_float32_beq(v_result_1703_, v_result_1703_);
if (v___x_1704_ == 0)
{
uint32_t v___x_1705_; uint32_t v___x_1706_; uint32_t v___x_1707_; uint32_t v___x_1708_; uint8_t v___x_1709_; 
v___x_1705_ = 23;
v___x_1706_ = lean_uint32_shift_right(v___y_1641_, v___x_1705_);
v___x_1707_ = 255;
v___x_1708_ = lean_uint32_land(v___x_1706_, v___x_1707_);
v___x_1709_ = lean_uint32_dec_eq(v___x_1708_, v___x_1707_);
if (v___x_1709_ == 0)
{
v___y_1694_ = v___x_1709_;
goto v___jp_1693_;
}
else
{
uint32_t v___x_1710_; uint32_t v___x_1711_; uint32_t v___x_1712_; uint8_t v___x_1713_; 
v___x_1710_ = 8388607;
v___x_1711_ = lean_uint32_land(v___y_1641_, v___x_1710_);
v___x_1712_ = 0;
v___x_1713_ = lean_uint32_dec_eq(v___x_1711_, v___x_1712_);
if (v___x_1713_ == 0)
{
v___y_1694_ = v___x_1709_;
goto v___jp_1693_;
}
else
{
goto v___jp_1683_;
}
}
}
else
{
uint32_t v___x_1714_; 
v___x_1714_ = lean_float32_to_bits(v_result_1703_);
return v___x_1714_;
}
}
v___jp_1715_:
{
if (v___y_1717_ == 0)
{
float v___x_1718_; 
v___x_1718_ = lean_float32_of_bits(v___y_1642_);
v___y_1701_ = v___y_1716_;
v___y_1702_ = v___x_1718_;
goto v___jp_1700_;
}
else
{
uint32_t v___x_1719_; uint32_t v___x_1720_; uint32_t v___x_1721_; uint32_t v___x_1722_; float v___x_1723_; lean_object* v___x_1724_; uint32_t v___x_1725_; uint32_t v___x_1726_; lean_object* v___x_1727_; lean_object* v___x_1728_; float v___x_1729_; float v___x_1730_; 
v___x_1719_ = 8388607;
v___x_1720_ = lean_uint32_land(v___y_1642_, v___x_1719_);
v___x_1721_ = 8388608;
v___x_1722_ = lean_uint32_lor(v___x_1720_, v___x_1721_);
v___x_1723_ = lean_uint32_to_float32(v___x_1722_);
v___x_1724_ = lp_competition_R2W01b_scaleTable;
v___x_1725_ = 23;
v___x_1726_ = lean_uint32_shift_right(v___y_1642_, v___x_1725_);
v___x_1727_ = lean_uint32_to_nat(v___x_1726_);
v___x_1728_ = lean_array_fget_borrowed(v___x_1724_, v___x_1727_);
lean_dec(v___x_1727_);
v___x_1729_ = lean_unbox_float32(v___x_1728_);
v___x_1730_ = lean_float32_mul(v___x_1723_, v___x_1729_);
v___y_1701_ = v___y_1716_;
v___y_1702_ = v___x_1730_;
goto v___jp_1700_;
}
}
v___jp_1731_:
{
uint32_t v___x_1733_; uint32_t v_a_1734_; uint32_t v___x_1735_; uint32_t v___x_1736_; uint32_t v___x_1737_; uint8_t v___x_1738_; 
v___x_1733_ = 2147483647;
v_a_1734_ = lean_uint32_land(v___y_1642_, v___x_1733_);
v___x_1735_ = 201326591;
v___x_1736_ = 1;
v___x_1737_ = lean_uint32_sub(v_a_1734_, v___x_1736_);
v___x_1738_ = lean_uint32_dec_le(v___x_1735_, v___x_1737_);
if (v___x_1738_ == 0)
{
v___y_1716_ = v___y_1732_;
v___y_1717_ = v___x_1738_;
goto v___jp_1715_;
}
else
{
uint32_t v___x_1739_; uint8_t v___x_1740_; 
v___x_1739_ = 2139095040;
v___x_1740_ = lean_uint32_dec_lt(v_a_1734_, v___x_1739_);
v___y_1716_ = v___y_1732_;
v___y_1717_ = v___x_1740_;
goto v___jp_1715_;
}
}
v___jp_1741_:
{
if (v___y_1742_ == 0)
{
float v___x_1743_; 
v___x_1743_ = lean_float32_of_bits(v___y_1641_);
v___y_1732_ = v___x_1743_;
goto v___jp_1731_;
}
else
{
uint32_t v___x_1744_; uint32_t v___x_1745_; uint32_t v___x_1746_; uint32_t v___x_1747_; float v___x_1748_; lean_object* v___x_1749_; uint32_t v___x_1750_; uint32_t v___x_1751_; lean_object* v___x_1752_; lean_object* v___x_1753_; float v___x_1754_; float v___x_1755_; 
v___x_1744_ = 8388607;
v___x_1745_ = lean_uint32_land(v___y_1641_, v___x_1744_);
v___x_1746_ = 8388608;
v___x_1747_ = lean_uint32_lor(v___x_1745_, v___x_1746_);
v___x_1748_ = lean_uint32_to_float32(v___x_1747_);
v___x_1749_ = lp_competition_R2W01b_scaleTable;
v___x_1750_ = 23;
v___x_1751_ = lean_uint32_shift_right(v___y_1641_, v___x_1750_);
v___x_1752_ = lean_uint32_to_nat(v___x_1751_);
v___x_1753_ = lean_array_fget_borrowed(v___x_1749_, v___x_1752_);
lean_dec(v___x_1752_);
v___x_1754_ = lean_unbox_float32(v___x_1753_);
v___x_1755_ = lean_float32_mul(v___x_1748_, v___x_1754_);
v___y_1732_ = v___x_1755_;
goto v___jp_1731_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object* v___y_1764_, lean_object* v___y_1765_){
_start:
{
uint32_t v___y_8134__boxed_1766_; uint32_t v___y_8135__boxed_1767_; uint32_t v_res_1768_; lean_object* v_r_1769_; 
v___y_8134__boxed_1766_ = lean_unbox_uint32(v___y_1764_);
lean_dec(v___y_1764_);
v___y_8135__boxed_1767_ = lean_unbox_uint32(v___y_1765_);
lean_dec(v___y_1765_);
v_res_1768_ = lp_competition_main___lam__0(v___y_8134__boxed_1766_, v___y_8135__boxed_1767_);
v_r_1769_ = lean_box_uint32(v_res_1768_);
return v_r_1769_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint8_t v___x_1770_, uint32_t v___y_1771_, uint32_t v___y_1772_){
_start:
{
uint8_t v___y_1774_; uint8_t v___y_1790_; uint8_t v___y_1804_; uint8_t v___y_1821_; float v___y_1828_; float v___y_1829_; float v___y_1843_; uint8_t v___y_1844_; float v___y_1859_; uint32_t v___y_1869_; uint32_t v___y_1873_; uint32_t v___y_1877_; uint32_t v___y_1878_; uint32_t v___y_1879_; uint64_t v___y_1883_; uint32_t v___y_1884_; uint8_t v___y_1885_; uint64_t v___y_1886_; uint32_t v___y_1898_; uint32_t v___y_1899_; uint32_t v___y_1900_; uint32_t v___y_1904_; uint8_t v___y_1905_; uint64_t v___y_1906_; uint64_t v___y_1907_; uint8_t v___y_1919_; uint8_t v___y_1935_; uint8_t v___y_1949_; uint8_t v___y_1966_; float v___y_1973_; float v___y_1974_; float v___y_1988_; uint8_t v___y_1989_; float v___y_2004_; uint32_t v___y_2014_; uint32_t v___y_2018_; uint32_t v___y_2022_; uint32_t v___y_2023_; uint32_t v___y_2024_; uint8_t v___y_2028_; uint32_t v___y_2029_; uint64_t v___y_2030_; uint64_t v___y_2031_; uint32_t v___y_2043_; uint32_t v___y_2044_; uint32_t v___y_2045_; uint8_t v___y_2049_; uint32_t v___y_2050_; uint64_t v___y_2051_; uint64_t v___y_2052_; uint8_t v___y_2064_; uint8_t v___y_2080_; uint8_t v___y_2094_; uint8_t v___y_2111_; float v___y_2118_; float v___y_2119_; float v___y_2133_; uint8_t v___y_2134_; float v___y_2149_; uint32_t v___y_2159_; uint32_t v___y_2163_; uint32_t v___y_2167_; uint32_t v___y_2168_; uint32_t v___y_2169_; uint8_t v___y_2173_; uint32_t v___y_2174_; uint64_t v___y_2175_; uint64_t v___y_2176_; uint32_t v___y_2188_; uint32_t v___y_2189_; uint32_t v___y_2190_; uint8_t v___y_2194_; uint64_t v___y_2195_; uint32_t v___y_2196_; uint64_t v___y_2197_; uint32_t v___x_2208_; uint32_t v___x_2209_; uint8_t v___y_2211_; uint8_t v___y_2224_; uint8_t v___y_2237_; uint32_t v___x_2249_; uint32_t v___y_2251_; uint32_t v___y_2252_; uint32_t v___y_2253_; uint32_t v___y_2254_; uint32_t v___y_2261_; uint8_t v___y_2262_; uint32_t v___y_2263_; uint32_t v___y_2264_; uint64_t v___y_2268_; uint64_t v___y_2269_; uint32_t v___y_2270_; uint8_t v___y_2271_; uint64_t v___y_2272_; uint64_t v___y_2282_; uint8_t v___y_2283_; uint32_t v___y_2284_; uint64_t v___y_2285_; uint8_t v___y_2286_; uint64_t v___y_2287_; uint64_t v___y_2294_; uint64_t v___y_2295_; uint32_t v___y_2296_; uint8_t v___y_2297_; uint64_t v___y_2298_; uint64_t v___y_2304_; uint64_t v___y_2305_; uint32_t v___y_2306_; uint64_t v___y_2307_; uint8_t v___y_2308_; uint64_t v___y_2309_; uint64_t v___y_2364_; uint64_t v___y_2365_; uint32_t v___y_2366_; uint64_t v___y_2367_; uint64_t v___y_2368_; uint8_t v___y_2369_; uint64_t v___y_2370_; uint64_t v___y_2376_; uint64_t v___y_2377_; uint64_t v___y_2378_; uint64_t v___y_2379_; uint64_t v___y_2380_; uint32_t v___y_2381_; uint64_t v___y_2382_; uint8_t v___y_2383_; uint64_t v___y_2384_; uint64_t v___y_2389_; uint64_t v___y_2390_; uint64_t v___y_2391_; uint32_t v___y_2392_; uint64_t v___y_2393_; uint8_t v___y_2394_; uint64_t v___y_2395_; uint64_t v___y_2400_; uint64_t v___y_2401_; uint64_t v___y_2402_; uint64_t v___y_2403_; uint32_t v___y_2404_; uint64_t v___y_2405_; uint64_t v___y_2406_; uint8_t v___y_2407_; uint64_t v___y_2408_; uint64_t v___y_2413_; uint64_t v___y_2414_; uint64_t v___y_2415_; uint32_t v___y_2416_; uint64_t v___y_2417_; uint8_t v___y_2418_; uint64_t v___y_2419_; uint64_t v___y_2424_; uint64_t v___y_2425_; uint64_t v___y_2426_; uint64_t v___y_2427_; uint32_t v___y_2428_; uint64_t v___y_2429_; uint64_t v___y_2430_; uint8_t v___y_2431_; uint64_t v___y_2432_; uint64_t v___y_2437_; uint64_t v___y_2438_; uint32_t v___y_2439_; uint64_t v___y_2440_; uint64_t v___y_2441_; uint8_t v___y_2442_; uint64_t v___y_2443_; uint64_t v___y_2448_; uint64_t v___y_2449_; uint64_t v___y_2450_; uint64_t v___y_2451_; uint64_t v___y_2452_; uint32_t v___y_2453_; uint64_t v___y_2454_; uint8_t v___y_2455_; uint64_t v___y_2456_; uint64_t v___y_2461_; uint64_t v___y_2462_; uint64_t v___y_2463_; uint32_t v___y_2464_; uint64_t v___y_2465_; uint8_t v___y_2466_; uint64_t v___y_2467_; uint64_t v___y_2472_; uint64_t v___y_2473_; uint64_t v___y_2474_; uint32_t v___y_2475_; uint64_t v___y_2476_; uint8_t v___y_2477_; uint64_t v___y_2478_; uint64_t v___y_2482_; uint32_t v___y_2483_; uint64_t v___y_2484_; uint8_t v___y_2485_; uint32_t v___y_2494_; uint64_t v___y_2495_; uint64_t v___y_2496_; uint64_t v___y_2497_; uint8_t v___y_2498_; uint64_t v___y_2499_; uint32_t v___y_2533_; uint32_t v___y_2534_; uint32_t v___y_2535_; uint32_t v___y_2536_; uint8_t v___y_2543_; uint32_t v___y_2544_; uint32_t v___y_2545_; uint32_t v___y_2546_; uint8_t v___y_2550_; uint32_t v___y_2551_; uint64_t v___y_2552_; uint64_t v___y_2553_; uint64_t v___y_2554_; uint8_t v___y_2564_; uint32_t v___y_2565_; uint64_t v___y_2566_; uint8_t v___y_2567_; uint64_t v___y_2568_; uint64_t v___y_2569_; uint8_t v___y_2576_; uint32_t v___y_2577_; uint64_t v___y_2578_; uint64_t v___y_2579_; uint64_t v___y_2580_; uint8_t v___y_2586_; uint32_t v___y_2587_; uint64_t v___y_2588_; uint64_t v___y_2589_; uint64_t v___y_2590_; uint64_t v___y_2591_; uint8_t v___y_2646_; uint32_t v___y_2647_; uint64_t v___y_2648_; uint64_t v___y_2649_; uint64_t v___y_2650_; uint64_t v___y_2651_; uint64_t v___y_2652_; uint8_t v___y_2658_; uint32_t v___y_2659_; uint64_t v___y_2660_; uint64_t v___y_2661_; uint64_t v___y_2662_; uint64_t v___y_2663_; uint64_t v___y_2664_; uint64_t v___y_2665_; uint64_t v___y_2666_; uint8_t v___y_2671_; uint32_t v___y_2672_; uint64_t v___y_2673_; uint64_t v___y_2674_; uint64_t v___y_2675_; uint64_t v___y_2676_; uint64_t v___y_2677_; uint8_t v___y_2682_; uint32_t v___y_2683_; uint64_t v___y_2684_; uint64_t v___y_2685_; uint64_t v___y_2686_; uint64_t v___y_2687_; uint64_t v___y_2688_; uint64_t v___y_2689_; uint64_t v___y_2690_; uint8_t v___y_2695_; uint32_t v___y_2696_; uint64_t v___y_2697_; uint64_t v___y_2698_; uint64_t v___y_2699_; uint64_t v___y_2700_; uint64_t v___y_2701_; uint8_t v___y_2706_; uint32_t v___y_2707_; uint64_t v___y_2708_; uint64_t v___y_2709_; uint64_t v___y_2710_; uint64_t v___y_2711_; uint64_t v___y_2712_; uint64_t v___y_2713_; uint64_t v___y_2714_; uint8_t v___y_2719_; uint32_t v___y_2720_; uint64_t v___y_2721_; uint64_t v___y_2722_; uint64_t v___y_2723_; uint64_t v___y_2724_; uint64_t v___y_2725_; uint8_t v___y_2730_; uint32_t v___y_2731_; uint64_t v___y_2732_; uint64_t v___y_2733_; uint64_t v___y_2734_; uint64_t v___y_2735_; uint64_t v___y_2736_; uint64_t v___y_2737_; uint64_t v___y_2738_; uint8_t v___y_2743_; uint32_t v___y_2744_; uint64_t v___y_2745_; uint64_t v___y_2746_; uint64_t v___y_2747_; uint64_t v___y_2748_; uint64_t v___y_2749_; uint8_t v___y_2754_; uint32_t v___y_2755_; uint64_t v___y_2756_; uint64_t v___y_2757_; uint64_t v___y_2758_; uint64_t v___y_2759_; uint64_t v___y_2760_; uint8_t v___y_2764_; uint32_t v___y_2765_; uint64_t v___y_2766_; uint64_t v___y_2767_; uint8_t v___y_2776_; uint32_t v___y_2777_; uint64_t v___y_2778_; uint64_t v___y_2779_; uint64_t v___y_2780_; uint64_t v___y_2781_; uint32_t v___y_2815_; uint32_t v___y_2816_; uint32_t v___y_2817_; uint32_t v___y_2818_; uint8_t v___y_2825_; uint32_t v___y_2826_; uint32_t v___y_2827_; uint32_t v___y_2828_; uint8_t v___y_2832_; uint32_t v___y_2833_; uint64_t v___y_2834_; uint64_t v___y_2835_; uint64_t v___y_2836_; uint8_t v___y_2846_; uint8_t v___y_2847_; uint32_t v___y_2848_; uint64_t v___y_2849_; uint64_t v___y_2850_; uint64_t v___y_2851_; uint64_t v___y_2858_; uint8_t v___y_2859_; uint32_t v___y_2860_; uint64_t v___y_2861_; uint64_t v___y_2862_; uint8_t v___y_2868_; uint64_t v___y_2869_; uint32_t v___y_2870_; uint64_t v___y_2871_; uint64_t v___y_2872_; uint64_t v___y_2873_; uint64_t v___y_2928_; uint8_t v___y_2929_; uint32_t v___y_2930_; uint64_t v___y_2931_; uint64_t v___y_2932_; uint64_t v___y_2933_; uint64_t v___y_2934_; uint64_t v___y_2940_; uint64_t v___y_2941_; uint64_t v___y_2942_; uint8_t v___y_2943_; uint64_t v___y_2944_; uint32_t v___y_2945_; uint64_t v___y_2946_; uint64_t v___y_2947_; uint64_t v___y_2948_; uint64_t v___y_2953_; uint64_t v___y_2954_; uint8_t v___y_2955_; uint32_t v___y_2956_; uint64_t v___y_2957_; uint64_t v___y_2958_; uint64_t v___y_2959_; uint64_t v___y_2964_; uint64_t v___y_2965_; uint64_t v___y_2966_; uint8_t v___y_2967_; uint64_t v___y_2968_; uint32_t v___y_2969_; uint64_t v___y_2970_; uint64_t v___y_2971_; uint64_t v___y_2972_; uint64_t v___y_2977_; uint8_t v___y_2978_; uint64_t v___y_2979_; uint32_t v___y_2980_; uint64_t v___y_2981_; uint64_t v___y_2982_; uint64_t v___y_2983_; uint64_t v___y_2988_; uint64_t v___y_2989_; uint8_t v___y_2990_; uint64_t v___y_2991_; uint64_t v___y_2992_; uint32_t v___y_2993_; uint64_t v___y_2994_; uint64_t v___y_2995_; uint64_t v___y_2996_; uint64_t v___y_3001_; uint8_t v___y_3002_; uint32_t v___y_3003_; uint64_t v___y_3004_; uint64_t v___y_3005_; uint64_t v___y_3006_; uint64_t v___y_3007_; uint64_t v___y_3012_; uint64_t v___y_3013_; uint8_t v___y_3014_; uint64_t v___y_3015_; uint32_t v___y_3016_; uint64_t v___y_3017_; uint64_t v___y_3018_; uint64_t v___y_3019_; uint64_t v___y_3020_; uint64_t v___y_3025_; uint8_t v___y_3026_; uint64_t v___y_3027_; uint32_t v___y_3028_; uint64_t v___y_3029_; uint64_t v___y_3030_; uint64_t v___y_3031_; uint8_t v___y_3036_; uint64_t v___y_3037_; uint32_t v___y_3038_; uint64_t v___y_3039_; uint64_t v___y_3040_; uint64_t v___y_3041_; uint64_t v___y_3042_; uint64_t v___y_3046_; uint8_t v___y_3047_; uint32_t v___y_3048_; uint64_t v___y_3049_; uint8_t v___y_3058_; uint64_t v___y_3059_; uint64_t v___y_3060_; uint64_t v___y_3061_; uint32_t v___y_3062_; uint64_t v___y_3063_; uint32_t v_eu_3096_; uint32_t v___x_3097_; uint32_t v___x_3098_; uint32_t v___x_3099_; uint8_t v___x_3100_; 
v___x_2208_ = 23;
v___x_2209_ = lean_uint32_shift_right(v___y_1771_, v___x_2208_);
v___x_2249_ = 255;
v_eu_3096_ = lean_uint32_land(v___x_2209_, v___x_2249_);
v___x_3097_ = 1;
v___x_3098_ = lean_uint32_sub(v_eu_3096_, v___x_3097_);
v___x_3099_ = 253;
v___x_3100_ = lean_uint32_dec_le(v___x_3098_, v___x_3099_);
if (v___x_3100_ == 0)
{
uint32_t v___x_3101_; uint32_t v_ey_3102_; uint32_t v___y_3104_; uint64_t v___y_3105_; uint64_t v___y_3106_; uint8_t v___y_3107_; uint64_t v___y_3108_; uint32_t v___y_3115_; uint64_t v___y_3116_; uint8_t v___y_3117_; uint64_t v___y_3118_; uint32_t v___y_3125_; uint32_t v___y_3126_; uint8_t v___y_3127_; uint64_t v___y_3128_; uint8_t v___y_3136_; uint8_t v___y_3147_; uint8_t v___y_3148_; uint8_t v___y_3150_; uint8_t v___y_3151_; uint8_t v___y_3152_; uint8_t v___y_3154_; uint8_t v___y_3155_; uint8_t v___y_3161_; uint32_t v___x_3170_; uint32_t v___x_3171_; uint8_t v___x_3172_; 
v___x_3101_ = lean_uint32_shift_right(v___y_1772_, v___x_2208_);
v_ey_3102_ = lean_uint32_land(v___x_3101_, v___x_2249_);
v___x_3170_ = lean_uint32_add(v_eu_3096_, v_ey_3102_);
v___x_3171_ = 128;
v___x_3172_ = lean_uint32_dec_lt(v___x_3170_, v___x_3171_);
if (v___x_3172_ == 0)
{
uint32_t v___x_3173_; uint32_t v_a_3174_; uint32_t v___x_3175_; uint32_t v___x_3176_; uint8_t v___x_3177_; 
v___x_3173_ = 2147483647;
v_a_3174_ = lean_uint32_land(v___y_1771_, v___x_3173_);
v___x_3175_ = 201326591;
v___x_3176_ = lean_uint32_sub(v_a_3174_, v___x_3097_);
v___x_3177_ = lean_uint32_dec_le(v___x_3175_, v___x_3176_);
if (v___x_3177_ == 0)
{
v___y_2211_ = v___x_3177_;
goto v___jp_2210_;
}
else
{
uint32_t v___x_3178_; uint8_t v___x_3179_; 
v___x_3178_ = 2139095040;
v___x_3179_ = lean_uint32_dec_lt(v_a_3174_, v___x_3178_);
v___y_2211_ = v___x_3179_;
goto v___jp_2210_;
}
}
else
{
uint32_t v___x_3180_; uint32_t v___x_3181_; uint8_t v___x_3182_; 
v___x_3180_ = 4278190080;
v___x_3181_ = lean_uint32_shift_left(v___y_1771_, v___x_3097_);
v___x_3182_ = lean_uint32_dec_le(v___x_3180_, v___x_3181_);
if (v___x_3182_ == 0)
{
uint32_t v___x_3183_; uint8_t v___x_3184_; 
v___x_3183_ = lean_uint32_shift_left(v___y_1772_, v___x_3097_);
v___x_3184_ = lean_uint32_dec_le(v___x_3180_, v___x_3183_);
v___y_3161_ = v___x_3184_;
goto v___jp_3160_;
}
else
{
v___y_3161_ = v___x_3182_;
goto v___jp_3160_;
}
}
v___jp_3103_:
{
uint64_t v___x_3109_; uint64_t v___x_3110_; uint8_t v___x_3111_; 
v___x_3109_ = lean_uint32_to_uint64(v_ey_3102_);
v___x_3110_ = 0ULL;
v___x_3111_ = lean_uint64_dec_eq(v___x_3109_, v___x_3110_);
if (v___x_3111_ == 0)
{
uint64_t v___x_3112_; uint64_t v___x_3113_; 
v___x_3112_ = 1ULL;
v___x_3113_ = lean_uint64_sub(v___x_3109_, v___x_3112_);
v___y_2494_ = v___y_3104_;
v___y_2495_ = v___y_3108_;
v___y_2496_ = v___y_3106_;
v___y_2497_ = v___y_3105_;
v___y_2498_ = v___y_3107_;
v___y_2499_ = v___x_3113_;
goto v___jp_2493_;
}
else
{
v___y_2494_ = v___y_3104_;
v___y_2495_ = v___y_3108_;
v___y_2496_ = v___y_3106_;
v___y_2497_ = v___y_3105_;
v___y_2498_ = v___y_3107_;
v___y_2499_ = v___x_3110_;
goto v___jp_2493_;
}
}
v___jp_3114_:
{
uint64_t v___x_3119_; uint64_t v___x_3120_; uint8_t v___x_3121_; 
v___x_3119_ = lean_uint32_to_uint64(v_eu_3096_);
v___x_3120_ = 0ULL;
v___x_3121_ = lean_uint64_dec_eq(v___x_3119_, v___x_3120_);
if (v___x_3121_ == 0)
{
uint64_t v___x_3122_; uint64_t v___x_3123_; 
v___x_3122_ = 1ULL;
v___x_3123_ = lean_uint64_sub(v___x_3119_, v___x_3122_);
v___y_3104_ = v___y_3115_;
v___y_3105_ = v___y_3116_;
v___y_3106_ = v___y_3118_;
v___y_3107_ = v___y_3117_;
v___y_3108_ = v___x_3123_;
goto v___jp_3103_;
}
else
{
v___y_3104_ = v___y_3115_;
v___y_3105_ = v___y_3116_;
v___y_3106_ = v___y_3118_;
v___y_3107_ = v___y_3117_;
v___y_3108_ = v___x_3120_;
goto v___jp_3103_;
}
}
v___jp_3124_:
{
uint32_t v___x_3129_; uint8_t v___x_3130_; 
v___x_3129_ = 0;
v___x_3130_ = lean_uint32_dec_eq(v_ey_3102_, v___x_3129_);
if (v___x_3130_ == 0)
{
uint64_t v___x_3131_; uint64_t v___x_3132_; uint64_t v___x_3133_; 
v___x_3131_ = lean_uint32_to_uint64(v___y_3125_);
v___x_3132_ = 8388608ULL;
v___x_3133_ = lean_uint64_lor(v___x_3131_, v___x_3132_);
v___y_3115_ = v___y_3126_;
v___y_3116_ = v___y_3128_;
v___y_3117_ = v___y_3127_;
v___y_3118_ = v___x_3133_;
goto v___jp_3114_;
}
else
{
uint64_t v___x_3134_; 
v___x_3134_ = lean_uint32_to_uint64(v___y_3125_);
v___y_3115_ = v___y_3126_;
v___y_3116_ = v___y_3128_;
v___y_3117_ = v___y_3127_;
v___y_3118_ = v___x_3134_;
goto v___jp_3114_;
}
}
v___jp_3135_:
{
uint32_t v___x_3137_; uint32_t v_xFraction_3138_; uint32_t v_yFraction_3139_; uint32_t v___x_3140_; uint8_t v___x_3141_; 
v___x_3137_ = 8388607;
v_xFraction_3138_ = lean_uint32_land(v___y_1771_, v___x_3137_);
v_yFraction_3139_ = lean_uint32_land(v___y_1772_, v___x_3137_);
v___x_3140_ = 0;
v___x_3141_ = lean_uint32_dec_eq(v_eu_3096_, v___x_3140_);
if (v___x_3141_ == 0)
{
uint64_t v___x_3142_; uint64_t v___x_3143_; uint64_t v___x_3144_; 
v___x_3142_ = lean_uint32_to_uint64(v_xFraction_3138_);
v___x_3143_ = 8388608ULL;
v___x_3144_ = lean_uint64_lor(v___x_3142_, v___x_3143_);
v___y_3125_ = v_yFraction_3139_;
v___y_3126_ = v___x_3137_;
v___y_3127_ = v___y_3136_;
v___y_3128_ = v___x_3144_;
goto v___jp_3124_;
}
else
{
uint64_t v___x_3145_; 
v___x_3145_ = lean_uint32_to_uint64(v_xFraction_3138_);
v___y_3125_ = v_yFraction_3139_;
v___y_3126_ = v___x_3137_;
v___y_3127_ = v___y_3136_;
v___y_3128_ = v___x_3145_;
goto v___jp_3124_;
}
}
v___jp_3146_:
{
if (v___y_3148_ == 0)
{
v___y_3136_ = v___x_1770_;
goto v___jp_3135_;
}
else
{
v___y_3136_ = v___y_3147_;
goto v___jp_3135_;
}
}
v___jp_3149_:
{
if (v___y_3151_ == 0)
{
if (v___y_3152_ == 0)
{
v___y_3147_ = v___y_3150_;
v___y_3148_ = v___x_1770_;
goto v___jp_3146_;
}
else
{
v___y_3136_ = v___x_1770_;
goto v___jp_3135_;
}
}
else
{
v___y_3147_ = v___y_3150_;
v___y_3148_ = v___y_3152_;
goto v___jp_3146_;
}
}
v___jp_3153_:
{
uint32_t v___x_3156_; uint32_t v___x_3157_; uint32_t v___x_3158_; uint8_t v___x_3159_; 
v___x_3156_ = 2147483648;
v___x_3157_ = lean_uint32_land(v___y_1772_, v___x_3156_);
v___x_3158_ = 0;
v___x_3159_ = lean_uint32_dec_eq(v___x_3157_, v___x_3158_);
if (v___x_3159_ == 0)
{
v___y_3150_ = v___y_3154_;
v___y_3151_ = v___y_3155_;
v___y_3152_ = v___x_1770_;
goto v___jp_3149_;
}
else
{
v___y_3150_ = v___y_3154_;
v___y_3151_ = v___y_3155_;
v___y_3152_ = v___y_3154_;
goto v___jp_3149_;
}
}
v___jp_3160_:
{
if (v___y_3161_ == 0)
{
uint32_t v___x_3162_; uint32_t v___x_3163_; uint32_t v___x_3164_; uint8_t v___x_3165_; 
v___x_3162_ = 2147483648;
v___x_3163_ = lean_uint32_land(v___y_1771_, v___x_3162_);
v___x_3164_ = 0;
v___x_3165_ = lean_uint32_dec_eq(v___x_3163_, v___x_3164_);
if (v___x_3165_ == 0)
{
v___y_3154_ = v___y_3161_;
v___y_3155_ = v___x_1770_;
goto v___jp_3153_;
}
else
{
v___y_3154_ = v___y_3161_;
v___y_3155_ = v___y_3161_;
goto v___jp_3153_;
}
}
else
{
lean_object* v___x_3166_; lean_object* v___x_3167_; lean_object* v___x_3168_; uint32_t v___x_3169_; 
v___x_3166_ = lean_uint32_to_nat(v___y_1771_);
v___x_3167_ = lean_uint32_to_nat(v___y_1772_);
v___x_3168_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_3166_, v___x_3167_);
v___x_3169_ = lean_uint32_of_nat(v___x_3168_);
lean_dec(v___x_3168_);
return v___x_3169_;
}
}
}
else
{
uint32_t v___x_3185_; uint32_t v_ev_3186_; uint8_t v___y_3188_; uint64_t v___y_3189_; uint64_t v___y_3190_; uint32_t v___y_3191_; uint64_t v___y_3192_; uint8_t v___y_3199_; uint64_t v___y_3200_; uint32_t v___y_3201_; uint64_t v___y_3202_; uint32_t v___y_3209_; uint8_t v___y_3210_; uint32_t v___y_3211_; uint64_t v___y_3212_; uint8_t v___y_3220_; uint8_t v___y_3231_; uint8_t v___y_3232_; uint8_t v___y_3234_; uint32_t v___y_3235_; uint64_t v___y_3236_; uint64_t v___y_3237_; uint64_t v___y_3238_; uint8_t v___y_3245_; uint32_t v___y_3246_; uint64_t v___y_3247_; uint64_t v___y_3248_; uint8_t v___y_3255_; uint32_t v___y_3256_; uint32_t v___y_3257_; uint64_t v___y_3258_; uint8_t v___y_3266_; uint8_t v___y_3277_; uint8_t v___y_3278_; uint8_t v___y_3280_; uint8_t v___y_3281_; uint8_t v___y_3282_; uint8_t v___y_3284_; uint8_t v___y_3285_; uint8_t v___y_3291_; uint32_t v___x_3300_; uint8_t v___x_3301_; uint8_t v___y_3303_; uint8_t v___y_3304_; uint8_t v___y_3305_; uint8_t v___y_3307_; uint8_t v___y_3308_; uint8_t v___y_3314_; 
v___x_3185_ = lean_uint32_shift_right(v___y_1772_, v___x_2208_);
v_ev_3186_ = lean_uint32_land(v___x_3185_, v___x_2249_);
v___x_3300_ = lean_uint32_sub(v_ev_3186_, v___x_3097_);
v___x_3301_ = lean_uint32_dec_le(v___x_3300_, v___x_3099_);
if (v___x_3301_ == 0)
{
uint32_t v___x_3323_; uint32_t v___x_3324_; uint8_t v___x_3325_; 
v___x_3323_ = lean_uint32_add(v_eu_3096_, v_ev_3186_);
v___x_3324_ = 128;
v___x_3325_ = lean_uint32_dec_lt(v___x_3323_, v___x_3324_);
if (v___x_3325_ == 0)
{
uint32_t v___x_3326_; uint32_t v_a_3327_; uint32_t v___x_3328_; uint32_t v___x_3329_; uint8_t v___x_3330_; 
v___x_3326_ = 2147483647;
v_a_3327_ = lean_uint32_land(v___y_1771_, v___x_3326_);
v___x_3328_ = 201326591;
v___x_3329_ = lean_uint32_sub(v_a_3327_, v___x_3097_);
v___x_3330_ = lean_uint32_dec_le(v___x_3328_, v___x_3329_);
if (v___x_3330_ == 0)
{
v___y_2224_ = v___x_3330_;
goto v___jp_2223_;
}
else
{
uint32_t v___x_3331_; uint8_t v___x_3332_; 
v___x_3331_ = 2139095040;
v___x_3332_ = lean_uint32_dec_lt(v_a_3327_, v___x_3331_);
v___y_2224_ = v___x_3332_;
goto v___jp_2223_;
}
}
else
{
uint32_t v___x_3333_; uint32_t v___x_3334_; uint8_t v___x_3335_; 
v___x_3333_ = 4278190080;
v___x_3334_ = lean_uint32_shift_left(v___y_1771_, v___x_3097_);
v___x_3335_ = lean_uint32_dec_le(v___x_3333_, v___x_3334_);
if (v___x_3335_ == 0)
{
uint32_t v___x_3336_; uint8_t v___x_3337_; 
v___x_3336_ = lean_uint32_shift_left(v___y_1772_, v___x_3097_);
v___x_3337_ = lean_uint32_dec_le(v___x_3333_, v___x_3336_);
v___y_3291_ = v___x_3337_;
goto v___jp_3290_;
}
else
{
v___y_3291_ = v___x_3335_;
goto v___jp_3290_;
}
}
}
else
{
uint32_t v_s_3338_; uint32_t v___x_3339_; uint32_t v___x_3340_; uint32_t v___x_3341_; uint8_t v___x_3342_; 
v_s_3338_ = lean_uint32_add(v_eu_3096_, v_ev_3186_);
v___x_3339_ = 128;
v___x_3340_ = lean_uint32_sub(v_s_3338_, v___x_3339_);
v___x_3341_ = 252;
v___x_3342_ = lean_uint32_dec_le(v___x_3340_, v___x_3341_);
if (v___x_3342_ == 0)
{
uint8_t v___x_3343_; 
v___x_3343_ = lean_uint32_dec_lt(v_s_3338_, v___x_3339_);
if (v___x_3343_ == 0)
{
uint32_t v___x_3344_; uint32_t v_a_3345_; uint32_t v___x_3346_; uint32_t v___x_3347_; uint8_t v___x_3348_; 
v___x_3344_ = 2147483647;
v_a_3345_ = lean_uint32_land(v___y_1771_, v___x_3344_);
v___x_3346_ = 201326591;
v___x_3347_ = lean_uint32_sub(v_a_3345_, v___x_3097_);
v___x_3348_ = lean_uint32_dec_le(v___x_3346_, v___x_3347_);
if (v___x_3348_ == 0)
{
v___y_2237_ = v___x_3348_;
goto v___jp_2236_;
}
else
{
uint32_t v___x_3349_; uint8_t v___x_3350_; 
v___x_3349_ = 2139095040;
v___x_3350_ = lean_uint32_dec_lt(v_a_3345_, v___x_3349_);
v___y_2237_ = v___x_3350_;
goto v___jp_2236_;
}
}
else
{
uint32_t v___x_3351_; uint32_t v___x_3352_; uint8_t v___x_3353_; 
v___x_3351_ = 4278190080;
v___x_3352_ = lean_uint32_shift_left(v___y_1771_, v___x_3097_);
v___x_3353_ = lean_uint32_dec_le(v___x_3351_, v___x_3352_);
if (v___x_3353_ == 0)
{
uint32_t v___x_3354_; uint8_t v___x_3355_; 
v___x_3354_ = lean_uint32_shift_left(v___y_1772_, v___x_3097_);
v___x_3355_ = lean_uint32_dec_le(v___x_3351_, v___x_3354_);
v___y_3314_ = v___x_3355_;
goto v___jp_3313_;
}
else
{
v___y_3314_ = v___x_3353_;
goto v___jp_3313_;
}
}
}
else
{
uint32_t v___x_3356_; uint32_t v___x_3357_; uint32_t v___x_3358_; uint64_t v___y_3360_; uint32_t v_a_3378_; uint32_t v___x_3379_; uint32_t v_b_3380_; uint64_t v___x_3381_; uint64_t v___x_3382_; uint64_t v_p_3383_; uint64_t v___x_3384_; uint8_t v___x_3385_; 
v___x_3356_ = 8388607;
v___x_3357_ = lean_uint32_land(v___y_1771_, v___x_3356_);
v___x_3358_ = 8388608;
v_a_3378_ = lean_uint32_lor(v___x_3357_, v___x_3358_);
v___x_3379_ = lean_uint32_land(v___y_1772_, v___x_3356_);
v_b_3380_ = lean_uint32_lor(v___x_3379_, v___x_3358_);
v___x_3381_ = lean_uint32_to_uint64(v_a_3378_);
v___x_3382_ = lean_uint32_to_uint64(v_b_3380_);
v_p_3383_ = lean_uint64_mul(v___x_3381_, v___x_3382_);
v___x_3384_ = 140737488355328ULL;
v___x_3385_ = lean_uint64_dec_lt(v_p_3383_, v___x_3384_);
if (v___x_3385_ == 0)
{
uint64_t v___x_3386_; uint64_t v___x_3387_; uint64_t v___x_3388_; uint64_t v___x_3389_; uint64_t v___x_3390_; uint64_t v___x_3391_; uint64_t v___x_3392_; 
v___x_3386_ = 8388607ULL;
v___x_3387_ = lean_uint64_add(v_p_3383_, v___x_3386_);
v___x_3388_ = 24ULL;
v___x_3389_ = lean_uint64_shift_right(v_p_3383_, v___x_3388_);
v___x_3390_ = 1ULL;
v___x_3391_ = lean_uint64_land(v___x_3389_, v___x_3390_);
v___x_3392_ = lean_uint64_add(v___x_3387_, v___x_3391_);
v___y_3360_ = v___x_3392_;
goto v___jp_3359_;
}
else
{
uint64_t v___x_3393_; uint64_t v___x_3394_; uint64_t v___x_3395_; uint64_t v___x_3396_; uint64_t v___x_3397_; uint64_t v___x_3398_; uint64_t v___x_3399_; 
v___x_3393_ = 4194303ULL;
v___x_3394_ = lean_uint64_add(v_p_3383_, v___x_3393_);
v___x_3395_ = 23ULL;
v___x_3396_ = lean_uint64_shift_right(v_p_3383_, v___x_3395_);
v___x_3397_ = 1ULL;
v___x_3398_ = lean_uint64_land(v___x_3396_, v___x_3397_);
v___x_3399_ = lean_uint64_add(v___x_3394_, v___x_3398_);
v___y_3360_ = v___x_3399_;
goto v___jp_3359_;
}
v___jp_3359_:
{
uint64_t v___x_3361_; uint64_t v_high_3362_; uint64_t v___x_3363_; uint64_t v___x_3364_; uint64_t v___x_3365_; uint32_t v_q_3366_; uint32_t v___x_3367_; uint32_t v___x_3368_; uint32_t v___x_3369_; uint32_t v_e_3370_; uint32_t v___x_3371_; uint32_t v___x_3372_; uint32_t v___x_3373_; uint32_t v___x_3374_; uint32_t v___x_3375_; uint32_t v___x_3376_; uint32_t v___x_3377_; 
v___x_3361_ = 47ULL;
v_high_3362_ = lean_uint64_shift_right(v___y_3360_, v___x_3361_);
v___x_3363_ = 23ULL;
v___x_3364_ = lean_uint64_add(v___x_3363_, v_high_3362_);
v___x_3365_ = lean_uint64_shift_right(v___y_3360_, v___x_3364_);
v_q_3366_ = lean_uint64_to_uint32(v___x_3365_);
v___x_3367_ = 127;
v___x_3368_ = lean_uint32_sub(v_s_3338_, v___x_3367_);
v___x_3369_ = lean_uint64_to_uint32(v_high_3362_);
v_e_3370_ = lean_uint32_add(v___x_3368_, v___x_3369_);
v___x_3371_ = lean_uint32_xor(v___y_1771_, v___y_1772_);
v___x_3372_ = 2147483648;
v___x_3373_ = lean_uint32_land(v___x_3371_, v___x_3372_);
v___x_3374_ = lean_uint32_shift_left(v_e_3370_, v___x_2208_);
v___x_3375_ = lean_uint32_lor(v___x_3373_, v___x_3374_);
v___x_3376_ = lean_uint32_sub(v_q_3366_, v___x_3358_);
v___x_3377_ = lean_uint32_lor(v___x_3375_, v___x_3376_);
return v___x_3377_;
}
}
}
v___jp_3187_:
{
uint64_t v___x_3193_; uint64_t v___x_3194_; uint8_t v___x_3195_; 
v___x_3193_ = lean_uint32_to_uint64(v_ev_3186_);
v___x_3194_ = 0ULL;
v___x_3195_ = lean_uint64_dec_eq(v___x_3193_, v___x_3194_);
if (v___x_3195_ == 0)
{
uint64_t v___x_3196_; uint64_t v___x_3197_; 
v___x_3196_ = 1ULL;
v___x_3197_ = lean_uint64_sub(v___x_3193_, v___x_3196_);
v___y_3058_ = v___y_3188_;
v___y_3059_ = v___y_3192_;
v___y_3060_ = v___y_3190_;
v___y_3061_ = v___y_3189_;
v___y_3062_ = v___y_3191_;
v___y_3063_ = v___x_3197_;
goto v___jp_3057_;
}
else
{
v___y_3058_ = v___y_3188_;
v___y_3059_ = v___y_3192_;
v___y_3060_ = v___y_3190_;
v___y_3061_ = v___y_3189_;
v___y_3062_ = v___y_3191_;
v___y_3063_ = v___x_3194_;
goto v___jp_3057_;
}
}
v___jp_3198_:
{
uint64_t v___x_3203_; uint64_t v___x_3204_; uint8_t v___x_3205_; 
v___x_3203_ = lean_uint32_to_uint64(v_eu_3096_);
v___x_3204_ = 0ULL;
v___x_3205_ = lean_uint64_dec_eq(v___x_3203_, v___x_3204_);
if (v___x_3205_ == 0)
{
uint64_t v___x_3206_; uint64_t v___x_3207_; 
v___x_3206_ = 1ULL;
v___x_3207_ = lean_uint64_sub(v___x_3203_, v___x_3206_);
v___y_3188_ = v___y_3199_;
v___y_3189_ = v___y_3200_;
v___y_3190_ = v___y_3202_;
v___y_3191_ = v___y_3201_;
v___y_3192_ = v___x_3207_;
goto v___jp_3187_;
}
else
{
v___y_3188_ = v___y_3199_;
v___y_3189_ = v___y_3200_;
v___y_3190_ = v___y_3202_;
v___y_3191_ = v___y_3201_;
v___y_3192_ = v___x_3204_;
goto v___jp_3187_;
}
}
v___jp_3208_:
{
uint32_t v___x_3213_; uint8_t v___x_3214_; 
v___x_3213_ = 0;
v___x_3214_ = lean_uint32_dec_eq(v_ev_3186_, v___x_3213_);
if (v___x_3214_ == 0)
{
uint64_t v___x_3215_; uint64_t v___x_3216_; uint64_t v___x_3217_; 
v___x_3215_ = lean_uint32_to_uint64(v___y_3209_);
v___x_3216_ = 8388608ULL;
v___x_3217_ = lean_uint64_lor(v___x_3215_, v___x_3216_);
v___y_3199_ = v___y_3210_;
v___y_3200_ = v___y_3212_;
v___y_3201_ = v___y_3211_;
v___y_3202_ = v___x_3217_;
goto v___jp_3198_;
}
else
{
uint64_t v___x_3218_; 
v___x_3218_ = lean_uint32_to_uint64(v___y_3209_);
v___y_3199_ = v___y_3210_;
v___y_3200_ = v___y_3212_;
v___y_3201_ = v___y_3211_;
v___y_3202_ = v___x_3218_;
goto v___jp_3198_;
}
}
v___jp_3219_:
{
uint32_t v___x_3221_; uint32_t v_xFraction_3222_; uint32_t v_yFraction_3223_; uint32_t v___x_3224_; uint8_t v___x_3225_; 
v___x_3221_ = 8388607;
v_xFraction_3222_ = lean_uint32_land(v___y_1771_, v___x_3221_);
v_yFraction_3223_ = lean_uint32_land(v___y_1772_, v___x_3221_);
v___x_3224_ = 0;
v___x_3225_ = lean_uint32_dec_eq(v_eu_3096_, v___x_3224_);
if (v___x_3225_ == 0)
{
uint64_t v___x_3226_; uint64_t v___x_3227_; uint64_t v___x_3228_; 
v___x_3226_ = lean_uint32_to_uint64(v_xFraction_3222_);
v___x_3227_ = 8388608ULL;
v___x_3228_ = lean_uint64_lor(v___x_3226_, v___x_3227_);
v___y_3209_ = v_yFraction_3223_;
v___y_3210_ = v___y_3220_;
v___y_3211_ = v___x_3221_;
v___y_3212_ = v___x_3228_;
goto v___jp_3208_;
}
else
{
uint64_t v___x_3229_; 
v___x_3229_ = lean_uint32_to_uint64(v_xFraction_3222_);
v___y_3209_ = v_yFraction_3223_;
v___y_3210_ = v___y_3220_;
v___y_3211_ = v___x_3221_;
v___y_3212_ = v___x_3229_;
goto v___jp_3208_;
}
}
v___jp_3230_:
{
if (v___y_3232_ == 0)
{
v___y_3220_ = v___x_1770_;
goto v___jp_3219_;
}
else
{
v___y_3220_ = v___y_3231_;
goto v___jp_3219_;
}
}
v___jp_3233_:
{
uint64_t v___x_3239_; uint64_t v___x_3240_; uint8_t v___x_3241_; 
v___x_3239_ = lean_uint32_to_uint64(v_ev_3186_);
v___x_3240_ = 0ULL;
v___x_3241_ = lean_uint64_dec_eq(v___x_3239_, v___x_3240_);
if (v___x_3241_ == 0)
{
uint64_t v___x_3242_; uint64_t v___x_3243_; 
v___x_3242_ = 1ULL;
v___x_3243_ = lean_uint64_sub(v___x_3239_, v___x_3242_);
v___y_2776_ = v___y_3234_;
v___y_2777_ = v___y_3235_;
v___y_2778_ = v___y_3236_;
v___y_2779_ = v___y_3238_;
v___y_2780_ = v___y_3237_;
v___y_2781_ = v___x_3243_;
goto v___jp_2775_;
}
else
{
v___y_2776_ = v___y_3234_;
v___y_2777_ = v___y_3235_;
v___y_2778_ = v___y_3236_;
v___y_2779_ = v___y_3238_;
v___y_2780_ = v___y_3237_;
v___y_2781_ = v___x_3240_;
goto v___jp_2775_;
}
}
v___jp_3244_:
{
uint64_t v___x_3249_; uint64_t v___x_3250_; uint8_t v___x_3251_; 
v___x_3249_ = lean_uint32_to_uint64(v_eu_3096_);
v___x_3250_ = 0ULL;
v___x_3251_ = lean_uint64_dec_eq(v___x_3249_, v___x_3250_);
if (v___x_3251_ == 0)
{
uint64_t v___x_3252_; uint64_t v___x_3253_; 
v___x_3252_ = 1ULL;
v___x_3253_ = lean_uint64_sub(v___x_3249_, v___x_3252_);
v___y_3234_ = v___y_3245_;
v___y_3235_ = v___y_3246_;
v___y_3236_ = v___y_3248_;
v___y_3237_ = v___y_3247_;
v___y_3238_ = v___x_3253_;
goto v___jp_3233_;
}
else
{
v___y_3234_ = v___y_3245_;
v___y_3235_ = v___y_3246_;
v___y_3236_ = v___y_3248_;
v___y_3237_ = v___y_3247_;
v___y_3238_ = v___x_3250_;
goto v___jp_3233_;
}
}
v___jp_3254_:
{
uint32_t v___x_3259_; uint8_t v___x_3260_; 
v___x_3259_ = 0;
v___x_3260_ = lean_uint32_dec_eq(v_ev_3186_, v___x_3259_);
if (v___x_3260_ == 0)
{
uint64_t v___x_3261_; uint64_t v___x_3262_; uint64_t v___x_3263_; 
v___x_3261_ = lean_uint32_to_uint64(v___y_3256_);
v___x_3262_ = 8388608ULL;
v___x_3263_ = lean_uint64_lor(v___x_3261_, v___x_3262_);
v___y_3245_ = v___y_3255_;
v___y_3246_ = v___y_3257_;
v___y_3247_ = v___y_3258_;
v___y_3248_ = v___x_3263_;
goto v___jp_3244_;
}
else
{
uint64_t v___x_3264_; 
v___x_3264_ = lean_uint32_to_uint64(v___y_3256_);
v___y_3245_ = v___y_3255_;
v___y_3246_ = v___y_3257_;
v___y_3247_ = v___y_3258_;
v___y_3248_ = v___x_3264_;
goto v___jp_3244_;
}
}
v___jp_3265_:
{
uint32_t v___x_3267_; uint32_t v_xFraction_3268_; uint32_t v_yFraction_3269_; uint32_t v___x_3270_; uint8_t v___x_3271_; 
v___x_3267_ = 8388607;
v_xFraction_3268_ = lean_uint32_land(v___y_1771_, v___x_3267_);
v_yFraction_3269_ = lean_uint32_land(v___y_1772_, v___x_3267_);
v___x_3270_ = 0;
v___x_3271_ = lean_uint32_dec_eq(v_eu_3096_, v___x_3270_);
if (v___x_3271_ == 0)
{
uint64_t v___x_3272_; uint64_t v___x_3273_; uint64_t v___x_3274_; 
v___x_3272_ = lean_uint32_to_uint64(v_xFraction_3268_);
v___x_3273_ = 8388608ULL;
v___x_3274_ = lean_uint64_lor(v___x_3272_, v___x_3273_);
v___y_3255_ = v___y_3266_;
v___y_3256_ = v_yFraction_3269_;
v___y_3257_ = v___x_3267_;
v___y_3258_ = v___x_3274_;
goto v___jp_3254_;
}
else
{
uint64_t v___x_3275_; 
v___x_3275_ = lean_uint32_to_uint64(v_xFraction_3268_);
v___y_3255_ = v___y_3266_;
v___y_3256_ = v_yFraction_3269_;
v___y_3257_ = v___x_3267_;
v___y_3258_ = v___x_3275_;
goto v___jp_3254_;
}
}
v___jp_3276_:
{
if (v___y_3278_ == 0)
{
v___y_3266_ = v___x_1770_;
goto v___jp_3265_;
}
else
{
v___y_3266_ = v___y_3277_;
goto v___jp_3265_;
}
}
v___jp_3279_:
{
if (v___y_3281_ == 0)
{
if (v___y_3282_ == 0)
{
v___y_3277_ = v___y_3280_;
v___y_3278_ = v___x_3100_;
goto v___jp_3276_;
}
else
{
v___y_3266_ = v___x_1770_;
goto v___jp_3265_;
}
}
else
{
v___y_3277_ = v___y_3280_;
v___y_3278_ = v___y_3282_;
goto v___jp_3276_;
}
}
v___jp_3283_:
{
uint32_t v___x_3286_; uint32_t v___x_3287_; uint32_t v___x_3288_; uint8_t v___x_3289_; 
v___x_3286_ = 2147483648;
v___x_3287_ = lean_uint32_land(v___y_1772_, v___x_3286_);
v___x_3288_ = 0;
v___x_3289_ = lean_uint32_dec_eq(v___x_3287_, v___x_3288_);
if (v___x_3289_ == 0)
{
v___y_3280_ = v___y_3284_;
v___y_3281_ = v___y_3285_;
v___y_3282_ = v___x_1770_;
goto v___jp_3279_;
}
else
{
v___y_3280_ = v___y_3284_;
v___y_3281_ = v___y_3285_;
v___y_3282_ = v___y_3284_;
goto v___jp_3279_;
}
}
v___jp_3290_:
{
if (v___y_3291_ == 0)
{
uint32_t v___x_3292_; uint32_t v___x_3293_; uint32_t v___x_3294_; uint8_t v___x_3295_; 
v___x_3292_ = 2147483648;
v___x_3293_ = lean_uint32_land(v___y_1771_, v___x_3292_);
v___x_3294_ = 0;
v___x_3295_ = lean_uint32_dec_eq(v___x_3293_, v___x_3294_);
if (v___x_3295_ == 0)
{
v___y_3284_ = v___y_3291_;
v___y_3285_ = v___x_1770_;
goto v___jp_3283_;
}
else
{
v___y_3284_ = v___y_3291_;
v___y_3285_ = v___y_3291_;
goto v___jp_3283_;
}
}
else
{
lean_object* v___x_3296_; lean_object* v___x_3297_; lean_object* v___x_3298_; uint32_t v___x_3299_; 
v___x_3296_ = lean_uint32_to_nat(v___y_1771_);
v___x_3297_ = lean_uint32_to_nat(v___y_1772_);
v___x_3298_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_3296_, v___x_3297_);
v___x_3299_ = lean_uint32_of_nat(v___x_3298_);
lean_dec(v___x_3298_);
return v___x_3299_;
}
}
v___jp_3302_:
{
if (v___y_3304_ == 0)
{
if (v___y_3305_ == 0)
{
v___y_3231_ = v___y_3303_;
v___y_3232_ = v___x_3301_;
goto v___jp_3230_;
}
else
{
v___y_3220_ = v___x_1770_;
goto v___jp_3219_;
}
}
else
{
v___y_3231_ = v___y_3303_;
v___y_3232_ = v___y_3305_;
goto v___jp_3230_;
}
}
v___jp_3306_:
{
uint32_t v___x_3309_; uint32_t v___x_3310_; uint32_t v___x_3311_; uint8_t v___x_3312_; 
v___x_3309_ = 2147483648;
v___x_3310_ = lean_uint32_land(v___y_1772_, v___x_3309_);
v___x_3311_ = 0;
v___x_3312_ = lean_uint32_dec_eq(v___x_3310_, v___x_3311_);
if (v___x_3312_ == 0)
{
v___y_3303_ = v___y_3307_;
v___y_3304_ = v___y_3308_;
v___y_3305_ = v___x_1770_;
goto v___jp_3302_;
}
else
{
v___y_3303_ = v___y_3307_;
v___y_3304_ = v___y_3308_;
v___y_3305_ = v___y_3307_;
goto v___jp_3302_;
}
}
v___jp_3313_:
{
if (v___y_3314_ == 0)
{
uint32_t v___x_3315_; uint32_t v___x_3316_; uint32_t v___x_3317_; uint8_t v___x_3318_; 
v___x_3315_ = 2147483648;
v___x_3316_ = lean_uint32_land(v___y_1771_, v___x_3315_);
v___x_3317_ = 0;
v___x_3318_ = lean_uint32_dec_eq(v___x_3316_, v___x_3317_);
if (v___x_3318_ == 0)
{
v___y_3307_ = v___y_3314_;
v___y_3308_ = v___x_1770_;
goto v___jp_3306_;
}
else
{
v___y_3307_ = v___y_3314_;
v___y_3308_ = v___y_3314_;
goto v___jp_3306_;
}
}
else
{
lean_object* v___x_3319_; lean_object* v___x_3320_; lean_object* v___x_3321_; uint32_t v___x_3322_; 
v___x_3319_ = lean_uint32_to_nat(v___y_1771_);
v___x_3320_ = lean_uint32_to_nat(v___y_1772_);
v___x_3321_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_3319_, v___x_3320_);
v___x_3322_ = lean_uint32_of_nat(v___x_3321_);
lean_dec(v___x_3321_);
return v___x_3322_;
}
}
}
v___jp_1773_:
{
if (v___y_1774_ == 0)
{
uint32_t v___x_1775_; 
v___x_1775_ = lp_competition_Submission_FastMul_mul(v___y_1771_, v___y_1772_);
return v___x_1775_;
}
else
{
uint32_t v___x_1776_; uint32_t v___x_1777_; 
v___x_1776_ = 4194304;
v___x_1777_ = lean_uint32_lor(v___y_1772_, v___x_1776_);
return v___x_1777_;
}
}
v___jp_1778_:
{
uint32_t v___x_1779_; uint32_t v___x_1780_; uint32_t v___x_1781_; uint32_t v___x_1782_; uint8_t v___x_1783_; 
v___x_1779_ = 23;
v___x_1780_ = lean_uint32_shift_right(v___y_1772_, v___x_1779_);
v___x_1781_ = 255;
v___x_1782_ = lean_uint32_land(v___x_1780_, v___x_1781_);
v___x_1783_ = lean_uint32_dec_eq(v___x_1782_, v___x_1781_);
if (v___x_1783_ == 0)
{
v___y_1774_ = v___x_1783_;
goto v___jp_1773_;
}
else
{
uint32_t v___x_1784_; uint32_t v___x_1785_; uint32_t v___x_1786_; uint8_t v___x_1787_; 
v___x_1784_ = 8388607;
v___x_1785_ = lean_uint32_land(v___y_1772_, v___x_1784_);
v___x_1786_ = 0;
v___x_1787_ = lean_uint32_dec_eq(v___x_1785_, v___x_1786_);
if (v___x_1787_ == 0)
{
v___y_1774_ = v___x_1783_;
goto v___jp_1773_;
}
else
{
uint32_t v___x_1788_; 
v___x_1788_ = lp_competition_Submission_FastMul_mul(v___y_1771_, v___y_1772_);
return v___x_1788_;
}
}
}
v___jp_1789_:
{
if (v___y_1790_ == 0)
{
goto v___jp_1778_;
}
else
{
uint32_t v___x_1791_; uint32_t v___x_1792_; 
v___x_1791_ = 4194304;
v___x_1792_ = lean_uint32_lor(v___y_1771_, v___x_1791_);
return v___x_1792_;
}
}
v___jp_1793_:
{
uint32_t v___x_1794_; uint32_t v___x_1795_; uint32_t v___x_1796_; uint32_t v___x_1797_; uint8_t v___x_1798_; 
v___x_1794_ = 23;
v___x_1795_ = lean_uint32_shift_right(v___y_1771_, v___x_1794_);
v___x_1796_ = 255;
v___x_1797_ = lean_uint32_land(v___x_1795_, v___x_1796_);
v___x_1798_ = lean_uint32_dec_eq(v___x_1797_, v___x_1796_);
if (v___x_1798_ == 0)
{
v___y_1790_ = v___x_1798_;
goto v___jp_1789_;
}
else
{
uint32_t v___x_1799_; uint32_t v___x_1800_; uint32_t v___x_1801_; uint8_t v___x_1802_; 
v___x_1799_ = 8388607;
v___x_1800_ = lean_uint32_land(v___y_1771_, v___x_1799_);
v___x_1801_ = 0;
v___x_1802_ = lean_uint32_dec_eq(v___x_1800_, v___x_1801_);
if (v___x_1802_ == 0)
{
v___y_1790_ = v___x_1798_;
goto v___jp_1789_;
}
else
{
goto v___jp_1778_;
}
}
}
v___jp_1803_:
{
if (v___y_1804_ == 0)
{
goto v___jp_1793_;
}
else
{
uint32_t v___x_1805_; uint32_t v___x_1806_; uint32_t v___x_1807_; uint8_t v___x_1808_; 
v___x_1805_ = 4194304;
v___x_1806_ = lean_uint32_land(v___y_1772_, v___x_1805_);
v___x_1807_ = 0;
v___x_1808_ = lean_uint32_dec_eq(v___x_1806_, v___x_1807_);
if (v___x_1808_ == 0)
{
goto v___jp_1793_;
}
else
{
uint32_t v___x_1809_; 
v___x_1809_ = lean_uint32_lor(v___y_1772_, v___x_1805_);
return v___x_1809_;
}
}
}
v___jp_1810_:
{
uint32_t v___x_1811_; uint32_t v___x_1812_; uint32_t v___x_1813_; uint32_t v___x_1814_; uint8_t v___x_1815_; 
v___x_1811_ = 23;
v___x_1812_ = lean_uint32_shift_right(v___y_1772_, v___x_1811_);
v___x_1813_ = 255;
v___x_1814_ = lean_uint32_land(v___x_1812_, v___x_1813_);
v___x_1815_ = lean_uint32_dec_eq(v___x_1814_, v___x_1813_);
if (v___x_1815_ == 0)
{
v___y_1804_ = v___x_1815_;
goto v___jp_1803_;
}
else
{
uint32_t v___x_1816_; uint32_t v___x_1817_; uint32_t v___x_1818_; uint8_t v___x_1819_; 
v___x_1816_ = 8388607;
v___x_1817_ = lean_uint32_land(v___y_1772_, v___x_1816_);
v___x_1818_ = 0;
v___x_1819_ = lean_uint32_dec_eq(v___x_1817_, v___x_1818_);
if (v___x_1819_ == 0)
{
v___y_1804_ = v___x_1815_;
goto v___jp_1803_;
}
else
{
goto v___jp_1793_;
}
}
}
v___jp_1820_:
{
if (v___y_1821_ == 0)
{
goto v___jp_1810_;
}
else
{
uint32_t v___x_1822_; uint32_t v___x_1823_; uint32_t v___x_1824_; uint8_t v___x_1825_; 
v___x_1822_ = 4194304;
v___x_1823_ = lean_uint32_land(v___y_1771_, v___x_1822_);
v___x_1824_ = 0;
v___x_1825_ = lean_uint32_dec_eq(v___x_1823_, v___x_1824_);
if (v___x_1825_ == 0)
{
goto v___jp_1810_;
}
else
{
uint32_t v___x_1826_; 
v___x_1826_ = lean_uint32_lor(v___y_1771_, v___x_1822_);
return v___x_1826_;
}
}
}
v___jp_1827_:
{
float v_result_1830_; uint8_t v___x_1831_; 
v_result_1830_ = lean_float32_mul(v___y_1828_, v___y_1829_);
v___x_1831_ = lean_float32_beq(v_result_1830_, v_result_1830_);
if (v___x_1831_ == 0)
{
uint32_t v___x_1832_; uint32_t v___x_1833_; uint32_t v___x_1834_; uint32_t v___x_1835_; uint8_t v___x_1836_; 
v___x_1832_ = 23;
v___x_1833_ = lean_uint32_shift_right(v___y_1771_, v___x_1832_);
v___x_1834_ = 255;
v___x_1835_ = lean_uint32_land(v___x_1833_, v___x_1834_);
v___x_1836_ = lean_uint32_dec_eq(v___x_1835_, v___x_1834_);
if (v___x_1836_ == 0)
{
v___y_1821_ = v___x_1836_;
goto v___jp_1820_;
}
else
{
uint32_t v___x_1837_; uint32_t v___x_1838_; uint32_t v___x_1839_; uint8_t v___x_1840_; 
v___x_1837_ = 8388607;
v___x_1838_ = lean_uint32_land(v___y_1771_, v___x_1837_);
v___x_1839_ = 0;
v___x_1840_ = lean_uint32_dec_eq(v___x_1838_, v___x_1839_);
if (v___x_1840_ == 0)
{
v___y_1821_ = v___x_1836_;
goto v___jp_1820_;
}
else
{
goto v___jp_1810_;
}
}
}
else
{
uint32_t v___x_1841_; 
v___x_1841_ = lean_float32_to_bits(v_result_1830_);
return v___x_1841_;
}
}
v___jp_1842_:
{
if (v___y_1844_ == 0)
{
float v___x_1845_; 
v___x_1845_ = lean_float32_of_bits(v___y_1772_);
v___y_1828_ = v___y_1843_;
v___y_1829_ = v___x_1845_;
goto v___jp_1827_;
}
else
{
uint32_t v___x_1846_; uint32_t v___x_1847_; uint32_t v___x_1848_; uint32_t v___x_1849_; float v___x_1850_; lean_object* v___x_1851_; uint32_t v___x_1852_; uint32_t v___x_1853_; lean_object* v___x_1854_; lean_object* v___x_1855_; float v___x_1856_; float v___x_1857_; 
v___x_1846_ = 8388607;
v___x_1847_ = lean_uint32_land(v___y_1772_, v___x_1846_);
v___x_1848_ = 8388608;
v___x_1849_ = lean_uint32_lor(v___x_1847_, v___x_1848_);
v___x_1850_ = lean_uint32_to_float32(v___x_1849_);
v___x_1851_ = lp_competition_R2W01b_scaleTable;
v___x_1852_ = 23;
v___x_1853_ = lean_uint32_shift_right(v___y_1772_, v___x_1852_);
v___x_1854_ = lean_uint32_to_nat(v___x_1853_);
v___x_1855_ = lean_array_fget_borrowed(v___x_1851_, v___x_1854_);
lean_dec(v___x_1854_);
v___x_1856_ = lean_unbox_float32(v___x_1855_);
v___x_1857_ = lean_float32_mul(v___x_1850_, v___x_1856_);
v___y_1828_ = v___y_1843_;
v___y_1829_ = v___x_1857_;
goto v___jp_1827_;
}
}
v___jp_1858_:
{
uint32_t v___x_1860_; uint32_t v_a_1861_; uint32_t v___x_1862_; uint32_t v___x_1863_; uint32_t v___x_1864_; uint8_t v___x_1865_; 
v___x_1860_ = 2147483647;
v_a_1861_ = lean_uint32_land(v___y_1772_, v___x_1860_);
v___x_1862_ = 201326591;
v___x_1863_ = 1;
v___x_1864_ = lean_uint32_sub(v_a_1861_, v___x_1863_);
v___x_1865_ = lean_uint32_dec_le(v___x_1862_, v___x_1864_);
if (v___x_1865_ == 0)
{
v___y_1843_ = v___y_1859_;
v___y_1844_ = v___x_1865_;
goto v___jp_1842_;
}
else
{
uint32_t v___x_1866_; uint8_t v___x_1867_; 
v___x_1866_ = 2139095040;
v___x_1867_ = lean_uint32_dec_lt(v_a_1861_, v___x_1866_);
v___y_1843_ = v___y_1859_;
v___y_1844_ = v___x_1867_;
goto v___jp_1842_;
}
}
v___jp_1868_:
{
uint32_t v___x_1870_; uint32_t v___x_1871_; 
v___x_1870_ = 8388608;
v___x_1871_ = lean_uint32_lor(v___y_1869_, v___x_1870_);
return v___x_1871_;
}
v___jp_1872_:
{
uint32_t v___x_1874_; uint32_t v___x_1875_; 
v___x_1874_ = 8388608;
v___x_1875_ = lean_uint32_lor(v___y_1873_, v___x_1874_);
return v___x_1875_;
}
v___jp_1876_:
{
uint32_t v___x_1880_; uint32_t v___x_1881_; 
v___x_1880_ = lean_uint32_land(v___y_1877_, v___y_1878_);
v___x_1881_ = lean_uint32_lor(v___y_1879_, v___x_1880_);
return v___x_1881_;
}
v___jp_1882_:
{
uint8_t v___x_1887_; 
v___x_1887_ = lean_uint64_dec_eq(v___y_1886_, v___y_1883_);
if (v___x_1887_ == 0)
{
uint64_t v___x_1888_; uint8_t v___x_1889_; 
v___x_1888_ = 8388608ULL;
v___x_1889_ = lean_uint64_dec_eq(v___y_1886_, v___x_1888_);
if (v___x_1889_ == 0)
{
uint32_t v___x_1890_; 
v___x_1890_ = lean_uint64_to_uint32(v___y_1886_);
if (v___y_1885_ == 0)
{
uint32_t v___x_1891_; 
v___x_1891_ = 0;
v___y_1877_ = v___x_1890_;
v___y_1878_ = v___y_1884_;
v___y_1879_ = v___x_1891_;
goto v___jp_1876_;
}
else
{
uint32_t v___x_1892_; 
v___x_1892_ = 2147483648;
v___y_1877_ = v___x_1890_;
v___y_1878_ = v___y_1884_;
v___y_1879_ = v___x_1892_;
goto v___jp_1876_;
}
}
else
{
if (v___y_1885_ == 0)
{
uint32_t v___x_1893_; 
v___x_1893_ = 0;
v___y_1873_ = v___x_1893_;
goto v___jp_1872_;
}
else
{
uint32_t v___x_1894_; 
v___x_1894_ = 2147483648;
v___y_1873_ = v___x_1894_;
goto v___jp_1872_;
}
}
}
else
{
if (v___y_1885_ == 0)
{
uint32_t v___x_1895_; 
v___x_1895_ = 0;
return v___x_1895_;
}
else
{
uint32_t v___x_1896_; 
v___x_1896_ = 2147483648;
return v___x_1896_;
}
}
}
v___jp_1897_:
{
uint32_t v___x_1901_; uint32_t v___x_1902_; 
v___x_1901_ = lean_uint32_land(v___y_1898_, v___y_1899_);
v___x_1902_ = lean_uint32_lor(v___y_1900_, v___x_1901_);
return v___x_1902_;
}
v___jp_1903_:
{
uint8_t v___x_1908_; 
v___x_1908_ = lean_uint64_dec_eq(v___y_1907_, v___y_1906_);
if (v___x_1908_ == 0)
{
uint64_t v___x_1909_; uint8_t v___x_1910_; 
v___x_1909_ = 8388608ULL;
v___x_1910_ = lean_uint64_dec_eq(v___y_1907_, v___x_1909_);
if (v___x_1910_ == 0)
{
uint32_t v___x_1911_; 
v___x_1911_ = lean_uint64_to_uint32(v___y_1907_);
if (v___y_1905_ == 0)
{
uint32_t v___x_1912_; 
v___x_1912_ = 0;
v___y_1898_ = v___x_1911_;
v___y_1899_ = v___y_1904_;
v___y_1900_ = v___x_1912_;
goto v___jp_1897_;
}
else
{
uint32_t v___x_1913_; 
v___x_1913_ = 2147483648;
v___y_1898_ = v___x_1911_;
v___y_1899_ = v___y_1904_;
v___y_1900_ = v___x_1913_;
goto v___jp_1897_;
}
}
else
{
if (v___y_1905_ == 0)
{
uint32_t v___x_1914_; 
v___x_1914_ = 0;
v___y_1869_ = v___x_1914_;
goto v___jp_1868_;
}
else
{
uint32_t v___x_1915_; 
v___x_1915_ = 2147483648;
v___y_1869_ = v___x_1915_;
goto v___jp_1868_;
}
}
}
else
{
if (v___y_1905_ == 0)
{
uint32_t v___x_1916_; 
v___x_1916_ = 0;
return v___x_1916_;
}
else
{
uint32_t v___x_1917_; 
v___x_1917_ = 2147483648;
return v___x_1917_;
}
}
}
v___jp_1918_:
{
if (v___y_1919_ == 0)
{
uint32_t v___x_1920_; 
v___x_1920_ = lp_competition_Submission_FastMul_mul(v___y_1771_, v___y_1772_);
return v___x_1920_;
}
else
{
uint32_t v___x_1921_; uint32_t v___x_1922_; 
v___x_1921_ = 4194304;
v___x_1922_ = lean_uint32_lor(v___y_1772_, v___x_1921_);
return v___x_1922_;
}
}
v___jp_1923_:
{
uint32_t v___x_1924_; uint32_t v___x_1925_; uint32_t v___x_1926_; uint32_t v___x_1927_; uint8_t v___x_1928_; 
v___x_1924_ = 23;
v___x_1925_ = lean_uint32_shift_right(v___y_1772_, v___x_1924_);
v___x_1926_ = 255;
v___x_1927_ = lean_uint32_land(v___x_1925_, v___x_1926_);
v___x_1928_ = lean_uint32_dec_eq(v___x_1927_, v___x_1926_);
if (v___x_1928_ == 0)
{
v___y_1919_ = v___x_1928_;
goto v___jp_1918_;
}
else
{
uint32_t v___x_1929_; uint32_t v___x_1930_; uint32_t v___x_1931_; uint8_t v___x_1932_; 
v___x_1929_ = 8388607;
v___x_1930_ = lean_uint32_land(v___y_1772_, v___x_1929_);
v___x_1931_ = 0;
v___x_1932_ = lean_uint32_dec_eq(v___x_1930_, v___x_1931_);
if (v___x_1932_ == 0)
{
v___y_1919_ = v___x_1928_;
goto v___jp_1918_;
}
else
{
uint32_t v___x_1933_; 
v___x_1933_ = lp_competition_Submission_FastMul_mul(v___y_1771_, v___y_1772_);
return v___x_1933_;
}
}
}
v___jp_1934_:
{
if (v___y_1935_ == 0)
{
goto v___jp_1923_;
}
else
{
uint32_t v___x_1936_; uint32_t v___x_1937_; 
v___x_1936_ = 4194304;
v___x_1937_ = lean_uint32_lor(v___y_1771_, v___x_1936_);
return v___x_1937_;
}
}
v___jp_1938_:
{
uint32_t v___x_1939_; uint32_t v___x_1940_; uint32_t v___x_1941_; uint32_t v___x_1942_; uint8_t v___x_1943_; 
v___x_1939_ = 23;
v___x_1940_ = lean_uint32_shift_right(v___y_1771_, v___x_1939_);
v___x_1941_ = 255;
v___x_1942_ = lean_uint32_land(v___x_1940_, v___x_1941_);
v___x_1943_ = lean_uint32_dec_eq(v___x_1942_, v___x_1941_);
if (v___x_1943_ == 0)
{
v___y_1935_ = v___x_1943_;
goto v___jp_1934_;
}
else
{
uint32_t v___x_1944_; uint32_t v___x_1945_; uint32_t v___x_1946_; uint8_t v___x_1947_; 
v___x_1944_ = 8388607;
v___x_1945_ = lean_uint32_land(v___y_1771_, v___x_1944_);
v___x_1946_ = 0;
v___x_1947_ = lean_uint32_dec_eq(v___x_1945_, v___x_1946_);
if (v___x_1947_ == 0)
{
v___y_1935_ = v___x_1943_;
goto v___jp_1934_;
}
else
{
goto v___jp_1923_;
}
}
}
v___jp_1948_:
{
if (v___y_1949_ == 0)
{
goto v___jp_1938_;
}
else
{
uint32_t v___x_1950_; uint32_t v___x_1951_; uint32_t v___x_1952_; uint8_t v___x_1953_; 
v___x_1950_ = 4194304;
v___x_1951_ = lean_uint32_land(v___y_1772_, v___x_1950_);
v___x_1952_ = 0;
v___x_1953_ = lean_uint32_dec_eq(v___x_1951_, v___x_1952_);
if (v___x_1953_ == 0)
{
goto v___jp_1938_;
}
else
{
uint32_t v___x_1954_; 
v___x_1954_ = lean_uint32_lor(v___y_1772_, v___x_1950_);
return v___x_1954_;
}
}
}
v___jp_1955_:
{
uint32_t v___x_1956_; uint32_t v___x_1957_; uint32_t v___x_1958_; uint32_t v___x_1959_; uint8_t v___x_1960_; 
v___x_1956_ = 23;
v___x_1957_ = lean_uint32_shift_right(v___y_1772_, v___x_1956_);
v___x_1958_ = 255;
v___x_1959_ = lean_uint32_land(v___x_1957_, v___x_1958_);
v___x_1960_ = lean_uint32_dec_eq(v___x_1959_, v___x_1958_);
if (v___x_1960_ == 0)
{
v___y_1949_ = v___x_1960_;
goto v___jp_1948_;
}
else
{
uint32_t v___x_1961_; uint32_t v___x_1962_; uint32_t v___x_1963_; uint8_t v___x_1964_; 
v___x_1961_ = 8388607;
v___x_1962_ = lean_uint32_land(v___y_1772_, v___x_1961_);
v___x_1963_ = 0;
v___x_1964_ = lean_uint32_dec_eq(v___x_1962_, v___x_1963_);
if (v___x_1964_ == 0)
{
v___y_1949_ = v___x_1960_;
goto v___jp_1948_;
}
else
{
goto v___jp_1938_;
}
}
}
v___jp_1965_:
{
if (v___y_1966_ == 0)
{
goto v___jp_1955_;
}
else
{
uint32_t v___x_1967_; uint32_t v___x_1968_; uint32_t v___x_1969_; uint8_t v___x_1970_; 
v___x_1967_ = 4194304;
v___x_1968_ = lean_uint32_land(v___y_1771_, v___x_1967_);
v___x_1969_ = 0;
v___x_1970_ = lean_uint32_dec_eq(v___x_1968_, v___x_1969_);
if (v___x_1970_ == 0)
{
goto v___jp_1955_;
}
else
{
uint32_t v___x_1971_; 
v___x_1971_ = lean_uint32_lor(v___y_1771_, v___x_1967_);
return v___x_1971_;
}
}
}
v___jp_1972_:
{
float v_result_1975_; uint8_t v___x_1976_; 
v_result_1975_ = lean_float32_mul(v___y_1973_, v___y_1974_);
v___x_1976_ = lean_float32_beq(v_result_1975_, v_result_1975_);
if (v___x_1976_ == 0)
{
uint32_t v___x_1977_; uint32_t v___x_1978_; uint32_t v___x_1979_; uint32_t v___x_1980_; uint8_t v___x_1981_; 
v___x_1977_ = 23;
v___x_1978_ = lean_uint32_shift_right(v___y_1771_, v___x_1977_);
v___x_1979_ = 255;
v___x_1980_ = lean_uint32_land(v___x_1978_, v___x_1979_);
v___x_1981_ = lean_uint32_dec_eq(v___x_1980_, v___x_1979_);
if (v___x_1981_ == 0)
{
v___y_1966_ = v___x_1981_;
goto v___jp_1965_;
}
else
{
uint32_t v___x_1982_; uint32_t v___x_1983_; uint32_t v___x_1984_; uint8_t v___x_1985_; 
v___x_1982_ = 8388607;
v___x_1983_ = lean_uint32_land(v___y_1771_, v___x_1982_);
v___x_1984_ = 0;
v___x_1985_ = lean_uint32_dec_eq(v___x_1983_, v___x_1984_);
if (v___x_1985_ == 0)
{
v___y_1966_ = v___x_1981_;
goto v___jp_1965_;
}
else
{
goto v___jp_1955_;
}
}
}
else
{
uint32_t v___x_1986_; 
v___x_1986_ = lean_float32_to_bits(v_result_1975_);
return v___x_1986_;
}
}
v___jp_1987_:
{
if (v___y_1989_ == 0)
{
float v___x_1990_; 
v___x_1990_ = lean_float32_of_bits(v___y_1772_);
v___y_1973_ = v___y_1988_;
v___y_1974_ = v___x_1990_;
goto v___jp_1972_;
}
else
{
uint32_t v___x_1991_; uint32_t v___x_1992_; uint32_t v___x_1993_; uint32_t v___x_1994_; float v___x_1995_; lean_object* v___x_1996_; uint32_t v___x_1997_; uint32_t v___x_1998_; lean_object* v___x_1999_; lean_object* v___x_2000_; float v___x_2001_; float v___x_2002_; 
v___x_1991_ = 8388607;
v___x_1992_ = lean_uint32_land(v___y_1772_, v___x_1991_);
v___x_1993_ = 8388608;
v___x_1994_ = lean_uint32_lor(v___x_1992_, v___x_1993_);
v___x_1995_ = lean_uint32_to_float32(v___x_1994_);
v___x_1996_ = lp_competition_R2W01b_scaleTable;
v___x_1997_ = 23;
v___x_1998_ = lean_uint32_shift_right(v___y_1772_, v___x_1997_);
v___x_1999_ = lean_uint32_to_nat(v___x_1998_);
v___x_2000_ = lean_array_fget_borrowed(v___x_1996_, v___x_1999_);
lean_dec(v___x_1999_);
v___x_2001_ = lean_unbox_float32(v___x_2000_);
v___x_2002_ = lean_float32_mul(v___x_1995_, v___x_2001_);
v___y_1973_ = v___y_1988_;
v___y_1974_ = v___x_2002_;
goto v___jp_1972_;
}
}
v___jp_2003_:
{
uint32_t v___x_2005_; uint32_t v_a_2006_; uint32_t v___x_2007_; uint32_t v___x_2008_; uint32_t v___x_2009_; uint8_t v___x_2010_; 
v___x_2005_ = 2147483647;
v_a_2006_ = lean_uint32_land(v___y_1772_, v___x_2005_);
v___x_2007_ = 201326591;
v___x_2008_ = 1;
v___x_2009_ = lean_uint32_sub(v_a_2006_, v___x_2008_);
v___x_2010_ = lean_uint32_dec_le(v___x_2007_, v___x_2009_);
if (v___x_2010_ == 0)
{
v___y_1988_ = v___y_2004_;
v___y_1989_ = v___x_2010_;
goto v___jp_1987_;
}
else
{
uint32_t v___x_2011_; uint8_t v___x_2012_; 
v___x_2011_ = 2139095040;
v___x_2012_ = lean_uint32_dec_lt(v_a_2006_, v___x_2011_);
v___y_1988_ = v___y_2004_;
v___y_1989_ = v___x_2012_;
goto v___jp_1987_;
}
}
v___jp_2013_:
{
uint32_t v___x_2015_; uint32_t v___x_2016_; 
v___x_2015_ = 8388608;
v___x_2016_ = lean_uint32_lor(v___y_2014_, v___x_2015_);
return v___x_2016_;
}
v___jp_2017_:
{
uint32_t v___x_2019_; uint32_t v___x_2020_; 
v___x_2019_ = 8388608;
v___x_2020_ = lean_uint32_lor(v___y_2018_, v___x_2019_);
return v___x_2020_;
}
v___jp_2021_:
{
uint32_t v___x_2025_; uint32_t v___x_2026_; 
v___x_2025_ = lean_uint32_land(v___y_2023_, v___y_2022_);
v___x_2026_ = lean_uint32_lor(v___y_2024_, v___x_2025_);
return v___x_2026_;
}
v___jp_2027_:
{
uint8_t v___x_2032_; 
v___x_2032_ = lean_uint64_dec_eq(v___y_2031_, v___y_2030_);
if (v___x_2032_ == 0)
{
uint64_t v___x_2033_; uint8_t v___x_2034_; 
v___x_2033_ = 8388608ULL;
v___x_2034_ = lean_uint64_dec_eq(v___y_2031_, v___x_2033_);
if (v___x_2034_ == 0)
{
uint32_t v___x_2035_; 
v___x_2035_ = lean_uint64_to_uint32(v___y_2031_);
if (v___y_2028_ == 0)
{
uint32_t v___x_2036_; 
v___x_2036_ = 0;
v___y_2022_ = v___y_2029_;
v___y_2023_ = v___x_2035_;
v___y_2024_ = v___x_2036_;
goto v___jp_2021_;
}
else
{
uint32_t v___x_2037_; 
v___x_2037_ = 2147483648;
v___y_2022_ = v___y_2029_;
v___y_2023_ = v___x_2035_;
v___y_2024_ = v___x_2037_;
goto v___jp_2021_;
}
}
else
{
if (v___y_2028_ == 0)
{
uint32_t v___x_2038_; 
v___x_2038_ = 0;
v___y_2014_ = v___x_2038_;
goto v___jp_2013_;
}
else
{
uint32_t v___x_2039_; 
v___x_2039_ = 2147483648;
v___y_2014_ = v___x_2039_;
goto v___jp_2013_;
}
}
}
else
{
if (v___y_2028_ == 0)
{
uint32_t v___x_2040_; 
v___x_2040_ = 0;
return v___x_2040_;
}
else
{
uint32_t v___x_2041_; 
v___x_2041_ = 2147483648;
return v___x_2041_;
}
}
}
v___jp_2042_:
{
uint32_t v___x_2046_; uint32_t v___x_2047_; 
v___x_2046_ = lean_uint32_land(v___y_2044_, v___y_2043_);
v___x_2047_ = lean_uint32_lor(v___y_2045_, v___x_2046_);
return v___x_2047_;
}
v___jp_2048_:
{
uint8_t v___x_2053_; 
v___x_2053_ = lean_uint64_dec_eq(v___y_2052_, v___y_2051_);
if (v___x_2053_ == 0)
{
uint64_t v___x_2054_; uint8_t v___x_2055_; 
v___x_2054_ = 8388608ULL;
v___x_2055_ = lean_uint64_dec_eq(v___y_2052_, v___x_2054_);
if (v___x_2055_ == 0)
{
uint32_t v___x_2056_; 
v___x_2056_ = lean_uint64_to_uint32(v___y_2052_);
if (v___y_2049_ == 0)
{
uint32_t v___x_2057_; 
v___x_2057_ = 0;
v___y_2043_ = v___y_2050_;
v___y_2044_ = v___x_2056_;
v___y_2045_ = v___x_2057_;
goto v___jp_2042_;
}
else
{
uint32_t v___x_2058_; 
v___x_2058_ = 2147483648;
v___y_2043_ = v___y_2050_;
v___y_2044_ = v___x_2056_;
v___y_2045_ = v___x_2058_;
goto v___jp_2042_;
}
}
else
{
if (v___y_2049_ == 0)
{
uint32_t v___x_2059_; 
v___x_2059_ = 0;
v___y_2018_ = v___x_2059_;
goto v___jp_2017_;
}
else
{
uint32_t v___x_2060_; 
v___x_2060_ = 2147483648;
v___y_2018_ = v___x_2060_;
goto v___jp_2017_;
}
}
}
else
{
if (v___y_2049_ == 0)
{
uint32_t v___x_2061_; 
v___x_2061_ = 0;
return v___x_2061_;
}
else
{
uint32_t v___x_2062_; 
v___x_2062_ = 2147483648;
return v___x_2062_;
}
}
}
v___jp_2063_:
{
if (v___y_2064_ == 0)
{
uint32_t v___x_2065_; 
v___x_2065_ = lp_competition_Submission_FastMul_mul(v___y_1771_, v___y_1772_);
return v___x_2065_;
}
else
{
uint32_t v___x_2066_; uint32_t v___x_2067_; 
v___x_2066_ = 4194304;
v___x_2067_ = lean_uint32_lor(v___y_1772_, v___x_2066_);
return v___x_2067_;
}
}
v___jp_2068_:
{
uint32_t v___x_2069_; uint32_t v___x_2070_; uint32_t v___x_2071_; uint32_t v___x_2072_; uint8_t v___x_2073_; 
v___x_2069_ = 23;
v___x_2070_ = lean_uint32_shift_right(v___y_1772_, v___x_2069_);
v___x_2071_ = 255;
v___x_2072_ = lean_uint32_land(v___x_2070_, v___x_2071_);
v___x_2073_ = lean_uint32_dec_eq(v___x_2072_, v___x_2071_);
if (v___x_2073_ == 0)
{
v___y_2064_ = v___x_2073_;
goto v___jp_2063_;
}
else
{
uint32_t v___x_2074_; uint32_t v___x_2075_; uint32_t v___x_2076_; uint8_t v___x_2077_; 
v___x_2074_ = 8388607;
v___x_2075_ = lean_uint32_land(v___y_1772_, v___x_2074_);
v___x_2076_ = 0;
v___x_2077_ = lean_uint32_dec_eq(v___x_2075_, v___x_2076_);
if (v___x_2077_ == 0)
{
v___y_2064_ = v___x_2073_;
goto v___jp_2063_;
}
else
{
uint32_t v___x_2078_; 
v___x_2078_ = lp_competition_Submission_FastMul_mul(v___y_1771_, v___y_1772_);
return v___x_2078_;
}
}
}
v___jp_2079_:
{
if (v___y_2080_ == 0)
{
goto v___jp_2068_;
}
else
{
uint32_t v___x_2081_; uint32_t v___x_2082_; 
v___x_2081_ = 4194304;
v___x_2082_ = lean_uint32_lor(v___y_1771_, v___x_2081_);
return v___x_2082_;
}
}
v___jp_2083_:
{
uint32_t v___x_2084_; uint32_t v___x_2085_; uint32_t v___x_2086_; uint32_t v___x_2087_; uint8_t v___x_2088_; 
v___x_2084_ = 23;
v___x_2085_ = lean_uint32_shift_right(v___y_1771_, v___x_2084_);
v___x_2086_ = 255;
v___x_2087_ = lean_uint32_land(v___x_2085_, v___x_2086_);
v___x_2088_ = lean_uint32_dec_eq(v___x_2087_, v___x_2086_);
if (v___x_2088_ == 0)
{
v___y_2080_ = v___x_2088_;
goto v___jp_2079_;
}
else
{
uint32_t v___x_2089_; uint32_t v___x_2090_; uint32_t v___x_2091_; uint8_t v___x_2092_; 
v___x_2089_ = 8388607;
v___x_2090_ = lean_uint32_land(v___y_1771_, v___x_2089_);
v___x_2091_ = 0;
v___x_2092_ = lean_uint32_dec_eq(v___x_2090_, v___x_2091_);
if (v___x_2092_ == 0)
{
v___y_2080_ = v___x_2088_;
goto v___jp_2079_;
}
else
{
goto v___jp_2068_;
}
}
}
v___jp_2093_:
{
if (v___y_2094_ == 0)
{
goto v___jp_2083_;
}
else
{
uint32_t v___x_2095_; uint32_t v___x_2096_; uint32_t v___x_2097_; uint8_t v___x_2098_; 
v___x_2095_ = 4194304;
v___x_2096_ = lean_uint32_land(v___y_1772_, v___x_2095_);
v___x_2097_ = 0;
v___x_2098_ = lean_uint32_dec_eq(v___x_2096_, v___x_2097_);
if (v___x_2098_ == 0)
{
goto v___jp_2083_;
}
else
{
uint32_t v___x_2099_; 
v___x_2099_ = lean_uint32_lor(v___y_1772_, v___x_2095_);
return v___x_2099_;
}
}
}
v___jp_2100_:
{
uint32_t v___x_2101_; uint32_t v___x_2102_; uint32_t v___x_2103_; uint32_t v___x_2104_; uint8_t v___x_2105_; 
v___x_2101_ = 23;
v___x_2102_ = lean_uint32_shift_right(v___y_1772_, v___x_2101_);
v___x_2103_ = 255;
v___x_2104_ = lean_uint32_land(v___x_2102_, v___x_2103_);
v___x_2105_ = lean_uint32_dec_eq(v___x_2104_, v___x_2103_);
if (v___x_2105_ == 0)
{
v___y_2094_ = v___x_2105_;
goto v___jp_2093_;
}
else
{
uint32_t v___x_2106_; uint32_t v___x_2107_; uint32_t v___x_2108_; uint8_t v___x_2109_; 
v___x_2106_ = 8388607;
v___x_2107_ = lean_uint32_land(v___y_1772_, v___x_2106_);
v___x_2108_ = 0;
v___x_2109_ = lean_uint32_dec_eq(v___x_2107_, v___x_2108_);
if (v___x_2109_ == 0)
{
v___y_2094_ = v___x_2105_;
goto v___jp_2093_;
}
else
{
goto v___jp_2083_;
}
}
}
v___jp_2110_:
{
if (v___y_2111_ == 0)
{
goto v___jp_2100_;
}
else
{
uint32_t v___x_2112_; uint32_t v___x_2113_; uint32_t v___x_2114_; uint8_t v___x_2115_; 
v___x_2112_ = 4194304;
v___x_2113_ = lean_uint32_land(v___y_1771_, v___x_2112_);
v___x_2114_ = 0;
v___x_2115_ = lean_uint32_dec_eq(v___x_2113_, v___x_2114_);
if (v___x_2115_ == 0)
{
goto v___jp_2100_;
}
else
{
uint32_t v___x_2116_; 
v___x_2116_ = lean_uint32_lor(v___y_1771_, v___x_2112_);
return v___x_2116_;
}
}
}
v___jp_2117_:
{
float v_result_2120_; uint8_t v___x_2121_; 
v_result_2120_ = lean_float32_mul(v___y_2118_, v___y_2119_);
v___x_2121_ = lean_float32_beq(v_result_2120_, v_result_2120_);
if (v___x_2121_ == 0)
{
uint32_t v___x_2122_; uint32_t v___x_2123_; uint32_t v___x_2124_; uint32_t v___x_2125_; uint8_t v___x_2126_; 
v___x_2122_ = 23;
v___x_2123_ = lean_uint32_shift_right(v___y_1771_, v___x_2122_);
v___x_2124_ = 255;
v___x_2125_ = lean_uint32_land(v___x_2123_, v___x_2124_);
v___x_2126_ = lean_uint32_dec_eq(v___x_2125_, v___x_2124_);
if (v___x_2126_ == 0)
{
v___y_2111_ = v___x_2126_;
goto v___jp_2110_;
}
else
{
uint32_t v___x_2127_; uint32_t v___x_2128_; uint32_t v___x_2129_; uint8_t v___x_2130_; 
v___x_2127_ = 8388607;
v___x_2128_ = lean_uint32_land(v___y_1771_, v___x_2127_);
v___x_2129_ = 0;
v___x_2130_ = lean_uint32_dec_eq(v___x_2128_, v___x_2129_);
if (v___x_2130_ == 0)
{
v___y_2111_ = v___x_2126_;
goto v___jp_2110_;
}
else
{
goto v___jp_2100_;
}
}
}
else
{
uint32_t v___x_2131_; 
v___x_2131_ = lean_float32_to_bits(v_result_2120_);
return v___x_2131_;
}
}
v___jp_2132_:
{
if (v___y_2134_ == 0)
{
float v___x_2135_; 
v___x_2135_ = lean_float32_of_bits(v___y_1772_);
v___y_2118_ = v___y_2133_;
v___y_2119_ = v___x_2135_;
goto v___jp_2117_;
}
else
{
uint32_t v___x_2136_; uint32_t v___x_2137_; uint32_t v___x_2138_; uint32_t v___x_2139_; float v___x_2140_; lean_object* v___x_2141_; uint32_t v___x_2142_; uint32_t v___x_2143_; lean_object* v___x_2144_; lean_object* v___x_2145_; float v___x_2146_; float v___x_2147_; 
v___x_2136_ = 8388607;
v___x_2137_ = lean_uint32_land(v___y_1772_, v___x_2136_);
v___x_2138_ = 8388608;
v___x_2139_ = lean_uint32_lor(v___x_2137_, v___x_2138_);
v___x_2140_ = lean_uint32_to_float32(v___x_2139_);
v___x_2141_ = lp_competition_R2W01b_scaleTable;
v___x_2142_ = 23;
v___x_2143_ = lean_uint32_shift_right(v___y_1772_, v___x_2142_);
v___x_2144_ = lean_uint32_to_nat(v___x_2143_);
v___x_2145_ = lean_array_fget_borrowed(v___x_2141_, v___x_2144_);
lean_dec(v___x_2144_);
v___x_2146_ = lean_unbox_float32(v___x_2145_);
v___x_2147_ = lean_float32_mul(v___x_2140_, v___x_2146_);
v___y_2118_ = v___y_2133_;
v___y_2119_ = v___x_2147_;
goto v___jp_2117_;
}
}
v___jp_2148_:
{
uint32_t v___x_2150_; uint32_t v_a_2151_; uint32_t v___x_2152_; uint32_t v___x_2153_; uint32_t v___x_2154_; uint8_t v___x_2155_; 
v___x_2150_ = 2147483647;
v_a_2151_ = lean_uint32_land(v___y_1772_, v___x_2150_);
v___x_2152_ = 201326591;
v___x_2153_ = 1;
v___x_2154_ = lean_uint32_sub(v_a_2151_, v___x_2153_);
v___x_2155_ = lean_uint32_dec_le(v___x_2152_, v___x_2154_);
if (v___x_2155_ == 0)
{
v___y_2133_ = v___y_2149_;
v___y_2134_ = v___x_2155_;
goto v___jp_2132_;
}
else
{
uint32_t v___x_2156_; uint8_t v___x_2157_; 
v___x_2156_ = 2139095040;
v___x_2157_ = lean_uint32_dec_lt(v_a_2151_, v___x_2156_);
v___y_2133_ = v___y_2149_;
v___y_2134_ = v___x_2157_;
goto v___jp_2132_;
}
}
v___jp_2158_:
{
uint32_t v___x_2160_; uint32_t v___x_2161_; 
v___x_2160_ = 8388608;
v___x_2161_ = lean_uint32_lor(v___y_2159_, v___x_2160_);
return v___x_2161_;
}
v___jp_2162_:
{
uint32_t v___x_2164_; uint32_t v___x_2165_; 
v___x_2164_ = 8388608;
v___x_2165_ = lean_uint32_lor(v___y_2163_, v___x_2164_);
return v___x_2165_;
}
v___jp_2166_:
{
uint32_t v___x_2170_; uint32_t v___x_2171_; 
v___x_2170_ = lean_uint32_land(v___y_2167_, v___y_2168_);
v___x_2171_ = lean_uint32_lor(v___y_2169_, v___x_2170_);
return v___x_2171_;
}
v___jp_2172_:
{
uint8_t v___x_2177_; 
v___x_2177_ = lean_uint64_dec_eq(v___y_2176_, v___y_2175_);
if (v___x_2177_ == 0)
{
uint64_t v___x_2178_; uint8_t v___x_2179_; 
v___x_2178_ = 8388608ULL;
v___x_2179_ = lean_uint64_dec_eq(v___y_2176_, v___x_2178_);
if (v___x_2179_ == 0)
{
uint32_t v___x_2180_; 
v___x_2180_ = lean_uint64_to_uint32(v___y_2176_);
if (v___y_2173_ == 0)
{
uint32_t v___x_2181_; 
v___x_2181_ = 0;
v___y_2167_ = v___x_2180_;
v___y_2168_ = v___y_2174_;
v___y_2169_ = v___x_2181_;
goto v___jp_2166_;
}
else
{
uint32_t v___x_2182_; 
v___x_2182_ = 2147483648;
v___y_2167_ = v___x_2180_;
v___y_2168_ = v___y_2174_;
v___y_2169_ = v___x_2182_;
goto v___jp_2166_;
}
}
else
{
if (v___y_2173_ == 0)
{
uint32_t v___x_2183_; 
v___x_2183_ = 0;
v___y_2163_ = v___x_2183_;
goto v___jp_2162_;
}
else
{
uint32_t v___x_2184_; 
v___x_2184_ = 2147483648;
v___y_2163_ = v___x_2184_;
goto v___jp_2162_;
}
}
}
else
{
if (v___y_2173_ == 0)
{
uint32_t v___x_2185_; 
v___x_2185_ = 0;
return v___x_2185_;
}
else
{
uint32_t v___x_2186_; 
v___x_2186_ = 2147483648;
return v___x_2186_;
}
}
}
v___jp_2187_:
{
uint32_t v___x_2191_; uint32_t v___x_2192_; 
v___x_2191_ = lean_uint32_land(v___y_2188_, v___y_2189_);
v___x_2192_ = lean_uint32_lor(v___y_2190_, v___x_2191_);
return v___x_2192_;
}
v___jp_2193_:
{
uint8_t v___x_2198_; 
v___x_2198_ = lean_uint64_dec_eq(v___y_2197_, v___y_2195_);
if (v___x_2198_ == 0)
{
uint64_t v___x_2199_; uint8_t v___x_2200_; 
v___x_2199_ = 8388608ULL;
v___x_2200_ = lean_uint64_dec_eq(v___y_2197_, v___x_2199_);
if (v___x_2200_ == 0)
{
uint32_t v___x_2201_; 
v___x_2201_ = lean_uint64_to_uint32(v___y_2197_);
if (v___y_2194_ == 0)
{
uint32_t v___x_2202_; 
v___x_2202_ = 0;
v___y_2188_ = v___x_2201_;
v___y_2189_ = v___y_2196_;
v___y_2190_ = v___x_2202_;
goto v___jp_2187_;
}
else
{
uint32_t v___x_2203_; 
v___x_2203_ = 2147483648;
v___y_2188_ = v___x_2201_;
v___y_2189_ = v___y_2196_;
v___y_2190_ = v___x_2203_;
goto v___jp_2187_;
}
}
else
{
if (v___y_2194_ == 0)
{
uint32_t v___x_2204_; 
v___x_2204_ = 0;
v___y_2159_ = v___x_2204_;
goto v___jp_2158_;
}
else
{
uint32_t v___x_2205_; 
v___x_2205_ = 2147483648;
v___y_2159_ = v___x_2205_;
goto v___jp_2158_;
}
}
}
else
{
if (v___y_2194_ == 0)
{
uint32_t v___x_2206_; 
v___x_2206_ = 0;
return v___x_2206_;
}
else
{
uint32_t v___x_2207_; 
v___x_2207_ = 2147483648;
return v___x_2207_;
}
}
}
v___jp_2210_:
{
if (v___y_2211_ == 0)
{
float v___x_2212_; 
v___x_2212_ = lean_float32_of_bits(v___y_1771_);
v___y_1859_ = v___x_2212_;
goto v___jp_1858_;
}
else
{
uint32_t v___x_2213_; uint32_t v___x_2214_; uint32_t v___x_2215_; uint32_t v___x_2216_; float v___x_2217_; lean_object* v___x_2218_; lean_object* v___x_2219_; lean_object* v___x_2220_; float v___x_2221_; float v___x_2222_; 
v___x_2213_ = 8388607;
v___x_2214_ = lean_uint32_land(v___y_1771_, v___x_2213_);
v___x_2215_ = 8388608;
v___x_2216_ = lean_uint32_lor(v___x_2214_, v___x_2215_);
v___x_2217_ = lean_uint32_to_float32(v___x_2216_);
v___x_2218_ = lp_competition_R2W01b_scaleTable;
v___x_2219_ = lean_uint32_to_nat(v___x_2209_);
v___x_2220_ = lean_array_fget_borrowed(v___x_2218_, v___x_2219_);
lean_dec(v___x_2219_);
v___x_2221_ = lean_unbox_float32(v___x_2220_);
v___x_2222_ = lean_float32_mul(v___x_2217_, v___x_2221_);
v___y_1859_ = v___x_2222_;
goto v___jp_1858_;
}
}
v___jp_2223_:
{
if (v___y_2224_ == 0)
{
float v___x_2225_; 
v___x_2225_ = lean_float32_of_bits(v___y_1771_);
v___y_2004_ = v___x_2225_;
goto v___jp_2003_;
}
else
{
uint32_t v___x_2226_; uint32_t v___x_2227_; uint32_t v___x_2228_; uint32_t v___x_2229_; float v___x_2230_; lean_object* v___x_2231_; lean_object* v___x_2232_; lean_object* v___x_2233_; float v___x_2234_; float v___x_2235_; 
v___x_2226_ = 8388607;
v___x_2227_ = lean_uint32_land(v___y_1771_, v___x_2226_);
v___x_2228_ = 8388608;
v___x_2229_ = lean_uint32_lor(v___x_2227_, v___x_2228_);
v___x_2230_ = lean_uint32_to_float32(v___x_2229_);
v___x_2231_ = lp_competition_R2W01b_scaleTable;
v___x_2232_ = lean_uint32_to_nat(v___x_2209_);
v___x_2233_ = lean_array_fget_borrowed(v___x_2231_, v___x_2232_);
lean_dec(v___x_2232_);
v___x_2234_ = lean_unbox_float32(v___x_2233_);
v___x_2235_ = lean_float32_mul(v___x_2230_, v___x_2234_);
v___y_2004_ = v___x_2235_;
goto v___jp_2003_;
}
}
v___jp_2236_:
{
if (v___y_2237_ == 0)
{
float v___x_2238_; 
v___x_2238_ = lean_float32_of_bits(v___y_1771_);
v___y_2149_ = v___x_2238_;
goto v___jp_2148_;
}
else
{
uint32_t v___x_2239_; uint32_t v___x_2240_; uint32_t v___x_2241_; uint32_t v___x_2242_; float v___x_2243_; lean_object* v___x_2244_; lean_object* v___x_2245_; lean_object* v___x_2246_; float v___x_2247_; float v___x_2248_; 
v___x_2239_ = 8388607;
v___x_2240_ = lean_uint32_land(v___y_1771_, v___x_2239_);
v___x_2241_ = 8388608;
v___x_2242_ = lean_uint32_lor(v___x_2240_, v___x_2241_);
v___x_2243_ = lean_uint32_to_float32(v___x_2242_);
v___x_2244_ = lp_competition_R2W01b_scaleTable;
v___x_2245_ = lean_uint32_to_nat(v___x_2209_);
v___x_2246_ = lean_array_fget_borrowed(v___x_2244_, v___x_2245_);
lean_dec(v___x_2245_);
v___x_2247_ = lean_unbox_float32(v___x_2246_);
v___x_2248_ = lean_float32_mul(v___x_2243_, v___x_2247_);
v___y_2149_ = v___x_2248_;
goto v___jp_2148_;
}
}
v___jp_2250_:
{
uint32_t v___x_2255_; uint32_t v___x_2256_; uint32_t v___x_2257_; uint32_t v___x_2258_; uint32_t v___x_2259_; 
v___x_2255_ = lean_uint32_land(v___y_2253_, v___x_2249_);
v___x_2256_ = lean_uint32_shift_left(v___x_2255_, v___x_2208_);
v___x_2257_ = lean_uint32_lor(v___y_2254_, v___x_2256_);
v___x_2258_ = lean_uint32_land(v___y_2251_, v___y_2252_);
v___x_2259_ = lean_uint32_lor(v___x_2257_, v___x_2258_);
return v___x_2259_;
}
v___jp_2260_:
{
if (v___y_2262_ == 0)
{
uint32_t v___x_2265_; 
v___x_2265_ = 0;
v___y_2251_ = v___y_2264_;
v___y_2252_ = v___y_2261_;
v___y_2253_ = v___y_2263_;
v___y_2254_ = v___x_2265_;
goto v___jp_2250_;
}
else
{
uint32_t v___x_2266_; 
v___x_2266_ = 2147483648;
v___y_2251_ = v___y_2264_;
v___y_2252_ = v___y_2261_;
v___y_2253_ = v___y_2263_;
v___y_2254_ = v___x_2266_;
goto v___jp_2250_;
}
}
v___jp_2267_:
{
uint64_t v___x_2273_; uint64_t v_encodedExponent_2274_; uint32_t v___x_2275_; uint64_t v___x_2276_; uint8_t v___x_2277_; 
v___x_2273_ = 171ULL;
v_encodedExponent_2274_ = lean_uint64_sub(v___y_2269_, v___x_2273_);
v___x_2275_ = lean_uint64_to_uint32(v_encodedExponent_2274_);
v___x_2276_ = 8388608ULL;
v___x_2277_ = lean_uint64_dec_lt(v___y_2272_, v___x_2276_);
if (v___x_2277_ == 0)
{
uint64_t v___x_2278_; uint32_t v___x_2279_; 
v___x_2278_ = lean_uint64_sub(v___y_2272_, v___x_2276_);
v___x_2279_ = lean_uint64_to_uint32(v___x_2278_);
v___y_2261_ = v___y_2270_;
v___y_2262_ = v___y_2271_;
v___y_2263_ = v___x_2275_;
v___y_2264_ = v___x_2279_;
goto v___jp_2260_;
}
else
{
uint32_t v___x_2280_; 
v___x_2280_ = lean_uint64_to_uint32(v___y_2268_);
v___y_2261_ = v___y_2270_;
v___y_2262_ = v___y_2271_;
v___y_2263_ = v___x_2275_;
v___y_2264_ = v___x_2280_;
goto v___jp_2260_;
}
}
v___jp_2281_:
{
uint64_t v___x_2288_; uint8_t v___x_2289_; 
v___x_2288_ = 425ULL;
v___x_2289_ = lean_uint64_dec_lt(v___x_2288_, v___y_2287_);
if (v___x_2289_ == 0)
{
if (v___y_2283_ == 0)
{
v___y_2268_ = v___y_2282_;
v___y_2269_ = v___y_2287_;
v___y_2270_ = v___y_2284_;
v___y_2271_ = v___y_2286_;
v___y_2272_ = v___y_2285_;
goto v___jp_2267_;
}
else
{
uint64_t v___x_2290_; 
v___x_2290_ = 8388608ULL;
v___y_2268_ = v___y_2282_;
v___y_2269_ = v___y_2287_;
v___y_2270_ = v___y_2284_;
v___y_2271_ = v___y_2286_;
v___y_2272_ = v___x_2290_;
goto v___jp_2267_;
}
}
else
{
if (v___y_2286_ == 0)
{
uint32_t v___x_2291_; 
v___x_2291_ = 2139095040;
return v___x_2291_;
}
else
{
uint32_t v___x_2292_; 
v___x_2292_ = 4286578688;
return v___x_2292_;
}
}
}
v___jp_2293_:
{
uint64_t v___x_2299_; uint8_t v_carry_2300_; 
v___x_2299_ = 16777216ULL;
v_carry_2300_ = lean_uint64_dec_eq(v___y_2298_, v___x_2299_);
if (v_carry_2300_ == 0)
{
v___y_2282_ = v___y_2294_;
v___y_2283_ = v_carry_2300_;
v___y_2284_ = v___y_2296_;
v___y_2285_ = v___y_2298_;
v___y_2286_ = v___y_2297_;
v___y_2287_ = v___y_2295_;
goto v___jp_2281_;
}
else
{
uint64_t v___x_2301_; uint64_t v___x_2302_; 
v___x_2301_ = 1ULL;
v___x_2302_ = lean_uint64_add(v___y_2295_, v___x_2301_);
v___y_2282_ = v___y_2294_;
v___y_2283_ = v_carry_2300_;
v___y_2284_ = v___y_2296_;
v___y_2285_ = v___y_2298_;
v___y_2286_ = v___y_2297_;
v___y_2287_ = v___x_2302_;
goto v___jp_2281_;
}
}
v___jp_2303_:
{
uint64_t v_position_2310_; uint64_t v___x_2311_; uint8_t v___x_2312_; 
v_position_2310_ = lean_uint64_add(v___y_2309_, v___y_2305_);
v___x_2311_ = 172ULL;
v___x_2312_ = lean_uint64_dec_lt(v_position_2310_, v___x_2311_);
if (v___x_2312_ == 0)
{
uint64_t v___x_2313_; uint8_t v___x_2314_; 
v___x_2313_ = 23ULL;
v___x_2314_ = lean_uint64_dec_lt(v___y_2309_, v___x_2313_);
if (v___x_2314_ == 0)
{
uint64_t v___x_2315_; uint8_t v___x_2316_; 
v___x_2315_ = lean_uint64_sub(v___y_2309_, v___x_2313_);
v___x_2316_ = lean_uint64_dec_eq(v___x_2315_, v___y_2304_);
if (v___x_2316_ == 0)
{
uint64_t v___x_2317_; uint8_t v___x_2318_; 
v___x_2317_ = 64ULL;
v___x_2318_ = lean_uint64_dec_lt(v___x_2315_, v___x_2317_);
if (v___x_2318_ == 0)
{
uint8_t v___x_2319_; 
v___x_2319_ = lean_uint64_dec_eq(v___x_2315_, v___x_2317_);
if (v___x_2319_ == 0)
{
v___y_2294_ = v___y_2304_;
v___y_2295_ = v_position_2310_;
v___y_2296_ = v___y_2306_;
v___y_2297_ = v___y_2308_;
v___y_2298_ = v___y_2304_;
goto v___jp_2293_;
}
else
{
uint64_t v___x_2320_; uint8_t v___x_2321_; 
v___x_2320_ = 9223372036854775808ULL;
v___x_2321_ = lean_uint64_dec_lt(v___x_2320_, v___y_2307_);
if (v___x_2321_ == 0)
{
v___y_2294_ = v___y_2304_;
v___y_2295_ = v_position_2310_;
v___y_2296_ = v___y_2306_;
v___y_2297_ = v___y_2308_;
v___y_2298_ = v___y_2304_;
goto v___jp_2293_;
}
else
{
uint64_t v___x_2322_; 
v___x_2322_ = 1ULL;
v___y_2294_ = v___y_2304_;
v___y_2295_ = v_position_2310_;
v___y_2296_ = v___y_2306_;
v___y_2297_ = v___y_2308_;
v___y_2298_ = v___x_2322_;
goto v___jp_2293_;
}
}
}
else
{
uint64_t v_quotient_2323_; uint64_t v___x_2324_; uint64_t v___x_2325_; uint64_t v___x_2326_; uint64_t v_remainder_2327_; uint64_t v___x_2328_; uint64_t v_half_2329_; uint8_t v___x_2330_; 
v_quotient_2323_ = lean_uint64_shift_right(v___y_2307_, v___x_2315_);
v___x_2324_ = 1ULL;
v___x_2325_ = lean_uint64_shift_left(v___x_2324_, v___x_2315_);
v___x_2326_ = lean_uint64_sub(v___x_2325_, v___x_2324_);
v_remainder_2327_ = lean_uint64_land(v___y_2307_, v___x_2326_);
v___x_2328_ = lean_uint64_sub(v___x_2315_, v___x_2324_);
v_half_2329_ = lean_uint64_shift_left(v___x_2324_, v___x_2328_);
v___x_2330_ = lean_uint64_dec_lt(v_remainder_2327_, v_half_2329_);
if (v___x_2330_ == 0)
{
uint8_t v___x_2331_; 
v___x_2331_ = lean_uint64_dec_lt(v_half_2329_, v_remainder_2327_);
if (v___x_2331_ == 0)
{
uint64_t v___x_2332_; uint8_t v___x_2333_; 
v___x_2332_ = lean_uint64_land(v_quotient_2323_, v___x_2324_);
v___x_2333_ = lean_uint64_dec_eq(v___x_2332_, v___y_2304_);
if (v___x_2333_ == 0)
{
uint64_t v___x_2334_; 
v___x_2334_ = lean_uint64_add(v_quotient_2323_, v___x_2324_);
v___y_2294_ = v___y_2304_;
v___y_2295_ = v_position_2310_;
v___y_2296_ = v___y_2306_;
v___y_2297_ = v___y_2308_;
v___y_2298_ = v___x_2334_;
goto v___jp_2293_;
}
else
{
v___y_2294_ = v___y_2304_;
v___y_2295_ = v_position_2310_;
v___y_2296_ = v___y_2306_;
v___y_2297_ = v___y_2308_;
v___y_2298_ = v_quotient_2323_;
goto v___jp_2293_;
}
}
else
{
uint64_t v___x_2335_; 
v___x_2335_ = lean_uint64_add(v_quotient_2323_, v___x_2324_);
v___y_2294_ = v___y_2304_;
v___y_2295_ = v_position_2310_;
v___y_2296_ = v___y_2306_;
v___y_2297_ = v___y_2308_;
v___y_2298_ = v___x_2335_;
goto v___jp_2293_;
}
}
else
{
v___y_2294_ = v___y_2304_;
v___y_2295_ = v_position_2310_;
v___y_2296_ = v___y_2306_;
v___y_2297_ = v___y_2308_;
v___y_2298_ = v_quotient_2323_;
goto v___jp_2293_;
}
}
}
else
{
v___y_2294_ = v___y_2304_;
v___y_2295_ = v_position_2310_;
v___y_2296_ = v___y_2306_;
v___y_2297_ = v___y_2308_;
v___y_2298_ = v___y_2307_;
goto v___jp_2293_;
}
}
else
{
uint64_t v___x_2336_; uint64_t v___x_2337_; 
v___x_2336_ = lean_uint64_sub(v___x_2313_, v___y_2309_);
v___x_2337_ = lean_uint64_shift_left(v___y_2307_, v___x_2336_);
v___y_2294_ = v___y_2304_;
v___y_2295_ = v_position_2310_;
v___y_2296_ = v___y_2306_;
v___y_2297_ = v___y_2308_;
v___y_2298_ = v___x_2337_;
goto v___jp_2293_;
}
}
else
{
uint64_t v___x_2338_; uint8_t v___x_2339_; 
v___x_2338_ = 149ULL;
v___x_2339_ = lean_uint64_dec_lt(v___y_2305_, v___x_2338_);
if (v___x_2339_ == 0)
{
uint64_t v___x_2340_; uint64_t v___x_2341_; 
v___x_2340_ = lean_uint64_sub(v___y_2305_, v___x_2338_);
v___x_2341_ = lean_uint64_shift_left(v___y_2307_, v___x_2340_);
v___y_1883_ = v___y_2304_;
v___y_1884_ = v___y_2306_;
v___y_1885_ = v___y_2308_;
v___y_1886_ = v___x_2341_;
goto v___jp_1882_;
}
else
{
uint64_t v___x_2342_; uint8_t v___x_2343_; 
v___x_2342_ = lean_uint64_sub(v___x_2338_, v___y_2305_);
v___x_2343_ = lean_uint64_dec_eq(v___x_2342_, v___y_2304_);
if (v___x_2343_ == 0)
{
uint64_t v___x_2344_; uint8_t v___x_2345_; 
v___x_2344_ = 64ULL;
v___x_2345_ = lean_uint64_dec_lt(v___x_2342_, v___x_2344_);
if (v___x_2345_ == 0)
{
uint8_t v___x_2346_; 
v___x_2346_ = lean_uint64_dec_eq(v___x_2342_, v___x_2344_);
if (v___x_2346_ == 0)
{
v___y_1883_ = v___y_2304_;
v___y_1884_ = v___y_2306_;
v___y_1885_ = v___y_2308_;
v___y_1886_ = v___y_2304_;
goto v___jp_1882_;
}
else
{
uint64_t v___x_2347_; uint8_t v___x_2348_; 
v___x_2347_ = 9223372036854775808ULL;
v___x_2348_ = lean_uint64_dec_lt(v___x_2347_, v___y_2307_);
if (v___x_2348_ == 0)
{
v___y_1883_ = v___y_2304_;
v___y_1884_ = v___y_2306_;
v___y_1885_ = v___y_2308_;
v___y_1886_ = v___y_2304_;
goto v___jp_1882_;
}
else
{
uint64_t v___x_2349_; 
v___x_2349_ = 1ULL;
v___y_1883_ = v___y_2304_;
v___y_1884_ = v___y_2306_;
v___y_1885_ = v___y_2308_;
v___y_1886_ = v___x_2349_;
goto v___jp_1882_;
}
}
}
else
{
uint64_t v_quotient_2350_; uint64_t v___x_2351_; uint64_t v___x_2352_; uint64_t v___x_2353_; uint64_t v_remainder_2354_; uint64_t v___x_2355_; uint64_t v_half_2356_; uint8_t v___x_2357_; 
v_quotient_2350_ = lean_uint64_shift_right(v___y_2307_, v___x_2342_);
v___x_2351_ = 1ULL;
v___x_2352_ = lean_uint64_shift_left(v___x_2351_, v___x_2342_);
v___x_2353_ = lean_uint64_sub(v___x_2352_, v___x_2351_);
v_remainder_2354_ = lean_uint64_land(v___y_2307_, v___x_2353_);
v___x_2355_ = lean_uint64_sub(v___x_2342_, v___x_2351_);
v_half_2356_ = lean_uint64_shift_left(v___x_2351_, v___x_2355_);
v___x_2357_ = lean_uint64_dec_lt(v_remainder_2354_, v_half_2356_);
if (v___x_2357_ == 0)
{
uint8_t v___x_2358_; 
v___x_2358_ = lean_uint64_dec_lt(v_half_2356_, v_remainder_2354_);
if (v___x_2358_ == 0)
{
uint64_t v___x_2359_; uint8_t v___x_2360_; 
v___x_2359_ = lean_uint64_land(v_quotient_2350_, v___x_2351_);
v___x_2360_ = lean_uint64_dec_eq(v___x_2359_, v___y_2304_);
if (v___x_2360_ == 0)
{
uint64_t v___x_2361_; 
v___x_2361_ = lean_uint64_add(v_quotient_2350_, v___x_2351_);
v___y_1883_ = v___y_2304_;
v___y_1884_ = v___y_2306_;
v___y_1885_ = v___y_2308_;
v___y_1886_ = v___x_2361_;
goto v___jp_1882_;
}
else
{
v___y_1883_ = v___y_2304_;
v___y_1884_ = v___y_2306_;
v___y_1885_ = v___y_2308_;
v___y_1886_ = v_quotient_2350_;
goto v___jp_1882_;
}
}
else
{
uint64_t v___x_2362_; 
v___x_2362_ = lean_uint64_add(v_quotient_2350_, v___x_2351_);
v___y_1883_ = v___y_2304_;
v___y_1884_ = v___y_2306_;
v___y_1885_ = v___y_2308_;
v___y_1886_ = v___x_2362_;
goto v___jp_1882_;
}
}
else
{
v___y_1883_ = v___y_2304_;
v___y_1884_ = v___y_2306_;
v___y_1885_ = v___y_2308_;
v___y_1886_ = v_quotient_2350_;
goto v___jp_1882_;
}
}
}
else
{
v___y_1883_ = v___y_2304_;
v___y_1884_ = v___y_2306_;
v___y_1885_ = v___y_2308_;
v___y_1886_ = v___y_2307_;
goto v___jp_1882_;
}
}
}
}
v___jp_2363_:
{
uint64_t v___x_2371_; uint64_t v___x_2372_; uint8_t v___x_2373_; 
v___x_2371_ = 1ULL;
v___x_2372_ = lean_uint64_shift_right(v___y_2368_, v___x_2371_);
v___x_2373_ = lean_uint64_dec_eq(v___x_2372_, v___y_2364_);
if (v___x_2373_ == 0)
{
uint64_t v___x_2374_; 
v___x_2374_ = lean_uint64_add(v___y_2370_, v___x_2371_);
v___y_2304_ = v___y_2364_;
v___y_2305_ = v___y_2365_;
v___y_2306_ = v___y_2366_;
v___y_2307_ = v___y_2367_;
v___y_2308_ = v___y_2369_;
v___y_2309_ = v___x_2374_;
goto v___jp_2303_;
}
else
{
v___y_2304_ = v___y_2364_;
v___y_2305_ = v___y_2365_;
v___y_2306_ = v___y_2366_;
v___y_2307_ = v___y_2367_;
v___y_2308_ = v___y_2369_;
v___y_2309_ = v___y_2370_;
goto v___jp_2303_;
}
}
v___jp_2375_:
{
uint64_t v___x_2385_; uint8_t v___x_2386_; 
v___x_2385_ = lean_uint64_shift_right(v___y_2379_, v___y_2376_);
v___x_2386_ = lean_uint64_dec_eq(v___x_2385_, v___y_2377_);
if (v___x_2386_ == 0)
{
uint64_t v___x_2387_; 
v___x_2387_ = lean_uint64_add(v___y_2380_, v___y_2376_);
v___y_2364_ = v___y_2377_;
v___y_2365_ = v___y_2378_;
v___y_2366_ = v___y_2381_;
v___y_2367_ = v___y_2382_;
v___y_2368_ = v___y_2384_;
v___y_2369_ = v___y_2383_;
v___y_2370_ = v___x_2387_;
goto v___jp_2363_;
}
else
{
v___y_2364_ = v___y_2377_;
v___y_2365_ = v___y_2378_;
v___y_2366_ = v___y_2381_;
v___y_2367_ = v___y_2382_;
v___y_2368_ = v___y_2384_;
v___y_2369_ = v___y_2383_;
v___y_2370_ = v___y_2380_;
goto v___jp_2363_;
}
}
v___jp_2388_:
{
uint64_t v___x_2396_; uint64_t v___x_2397_; uint8_t v___x_2398_; 
v___x_2396_ = 2ULL;
v___x_2397_ = lean_uint64_shift_right(v___y_2391_, v___x_2396_);
v___x_2398_ = lean_uint64_dec_eq(v___x_2397_, v___y_2389_);
if (v___x_2398_ == 0)
{
v___y_2376_ = v___x_2396_;
v___y_2377_ = v___y_2389_;
v___y_2378_ = v___y_2390_;
v___y_2379_ = v___y_2391_;
v___y_2380_ = v___y_2395_;
v___y_2381_ = v___y_2392_;
v___y_2382_ = v___y_2393_;
v___y_2383_ = v___y_2394_;
v___y_2384_ = v___x_2397_;
goto v___jp_2375_;
}
else
{
v___y_2376_ = v___x_2396_;
v___y_2377_ = v___y_2389_;
v___y_2378_ = v___y_2390_;
v___y_2379_ = v___y_2391_;
v___y_2380_ = v___y_2395_;
v___y_2381_ = v___y_2392_;
v___y_2382_ = v___y_2393_;
v___y_2383_ = v___y_2394_;
v___y_2384_ = v___y_2391_;
goto v___jp_2375_;
}
}
v___jp_2399_:
{
uint64_t v___x_2409_; uint8_t v___x_2410_; 
v___x_2409_ = lean_uint64_shift_right(v___y_2401_, v___y_2400_);
v___x_2410_ = lean_uint64_dec_eq(v___x_2409_, v___y_2402_);
if (v___x_2410_ == 0)
{
uint64_t v___x_2411_; 
v___x_2411_ = lean_uint64_add(v___y_2406_, v___y_2400_);
v___y_2389_ = v___y_2402_;
v___y_2390_ = v___y_2403_;
v___y_2391_ = v___y_2408_;
v___y_2392_ = v___y_2404_;
v___y_2393_ = v___y_2405_;
v___y_2394_ = v___y_2407_;
v___y_2395_ = v___x_2411_;
goto v___jp_2388_;
}
else
{
v___y_2389_ = v___y_2402_;
v___y_2390_ = v___y_2403_;
v___y_2391_ = v___y_2408_;
v___y_2392_ = v___y_2404_;
v___y_2393_ = v___y_2405_;
v___y_2394_ = v___y_2407_;
v___y_2395_ = v___y_2406_;
goto v___jp_2388_;
}
}
v___jp_2412_:
{
uint64_t v___x_2420_; uint64_t v___x_2421_; uint8_t v___x_2422_; 
v___x_2420_ = 4ULL;
v___x_2421_ = lean_uint64_shift_right(v___y_2414_, v___x_2420_);
v___x_2422_ = lean_uint64_dec_eq(v___x_2421_, v___y_2413_);
if (v___x_2422_ == 0)
{
v___y_2400_ = v___x_2420_;
v___y_2401_ = v___y_2414_;
v___y_2402_ = v___y_2413_;
v___y_2403_ = v___y_2415_;
v___y_2404_ = v___y_2416_;
v___y_2405_ = v___y_2417_;
v___y_2406_ = v___y_2419_;
v___y_2407_ = v___y_2418_;
v___y_2408_ = v___x_2421_;
goto v___jp_2399_;
}
else
{
v___y_2400_ = v___x_2420_;
v___y_2401_ = v___y_2414_;
v___y_2402_ = v___y_2413_;
v___y_2403_ = v___y_2415_;
v___y_2404_ = v___y_2416_;
v___y_2405_ = v___y_2417_;
v___y_2406_ = v___y_2419_;
v___y_2407_ = v___y_2418_;
v___y_2408_ = v___y_2414_;
goto v___jp_2399_;
}
}
v___jp_2423_:
{
uint64_t v___x_2433_; uint8_t v___x_2434_; 
v___x_2433_ = lean_uint64_shift_right(v___y_2427_, v___y_2429_);
v___x_2434_ = lean_uint64_dec_eq(v___x_2433_, v___y_2424_);
if (v___x_2434_ == 0)
{
uint64_t v___x_2435_; 
v___x_2435_ = lean_uint64_add(v___y_2425_, v___y_2429_);
v___y_2413_ = v___y_2424_;
v___y_2414_ = v___y_2432_;
v___y_2415_ = v___y_2426_;
v___y_2416_ = v___y_2428_;
v___y_2417_ = v___y_2430_;
v___y_2418_ = v___y_2431_;
v___y_2419_ = v___x_2435_;
goto v___jp_2412_;
}
else
{
v___y_2413_ = v___y_2424_;
v___y_2414_ = v___y_2432_;
v___y_2415_ = v___y_2426_;
v___y_2416_ = v___y_2428_;
v___y_2417_ = v___y_2430_;
v___y_2418_ = v___y_2431_;
v___y_2419_ = v___y_2425_;
goto v___jp_2412_;
}
}
v___jp_2436_:
{
uint64_t v___x_2444_; uint64_t v___x_2445_; uint8_t v___x_2446_; 
v___x_2444_ = 8ULL;
v___x_2445_ = lean_uint64_shift_right(v___y_2440_, v___x_2444_);
v___x_2446_ = lean_uint64_dec_eq(v___x_2445_, v___y_2437_);
if (v___x_2446_ == 0)
{
v___y_2424_ = v___y_2437_;
v___y_2425_ = v___y_2443_;
v___y_2426_ = v___y_2438_;
v___y_2427_ = v___y_2440_;
v___y_2428_ = v___y_2439_;
v___y_2429_ = v___x_2444_;
v___y_2430_ = v___y_2441_;
v___y_2431_ = v___y_2442_;
v___y_2432_ = v___x_2445_;
goto v___jp_2423_;
}
else
{
v___y_2424_ = v___y_2437_;
v___y_2425_ = v___y_2443_;
v___y_2426_ = v___y_2438_;
v___y_2427_ = v___y_2440_;
v___y_2428_ = v___y_2439_;
v___y_2429_ = v___x_2444_;
v___y_2430_ = v___y_2441_;
v___y_2431_ = v___y_2442_;
v___y_2432_ = v___y_2440_;
goto v___jp_2423_;
}
}
v___jp_2447_:
{
uint64_t v___x_2457_; uint8_t v___x_2458_; 
v___x_2457_ = lean_uint64_shift_right(v___y_2448_, v___y_2449_);
v___x_2458_ = lean_uint64_dec_eq(v___x_2457_, v___y_2450_);
if (v___x_2458_ == 0)
{
uint64_t v___x_2459_; 
v___x_2459_ = lean_uint64_add(v___y_2452_, v___y_2449_);
v___y_2437_ = v___y_2450_;
v___y_2438_ = v___y_2451_;
v___y_2439_ = v___y_2453_;
v___y_2440_ = v___y_2456_;
v___y_2441_ = v___y_2454_;
v___y_2442_ = v___y_2455_;
v___y_2443_ = v___x_2459_;
goto v___jp_2436_;
}
else
{
v___y_2437_ = v___y_2450_;
v___y_2438_ = v___y_2451_;
v___y_2439_ = v___y_2453_;
v___y_2440_ = v___y_2456_;
v___y_2441_ = v___y_2454_;
v___y_2442_ = v___y_2455_;
v___y_2443_ = v___y_2452_;
goto v___jp_2436_;
}
}
v___jp_2460_:
{
uint64_t v___x_2468_; uint64_t v___x_2469_; uint8_t v___x_2470_; 
v___x_2468_ = 16ULL;
v___x_2469_ = lean_uint64_shift_right(v___y_2461_, v___x_2468_);
v___x_2470_ = lean_uint64_dec_eq(v___x_2469_, v___y_2462_);
if (v___x_2470_ == 0)
{
v___y_2448_ = v___y_2461_;
v___y_2449_ = v___x_2468_;
v___y_2450_ = v___y_2462_;
v___y_2451_ = v___y_2463_;
v___y_2452_ = v___y_2467_;
v___y_2453_ = v___y_2464_;
v___y_2454_ = v___y_2465_;
v___y_2455_ = v___y_2466_;
v___y_2456_ = v___x_2469_;
goto v___jp_2447_;
}
else
{
v___y_2448_ = v___y_2461_;
v___y_2449_ = v___x_2468_;
v___y_2450_ = v___y_2462_;
v___y_2451_ = v___y_2463_;
v___y_2452_ = v___y_2467_;
v___y_2453_ = v___y_2464_;
v___y_2454_ = v___y_2465_;
v___y_2455_ = v___y_2466_;
v___y_2456_ = v___y_2461_;
goto v___jp_2447_;
}
}
v___jp_2471_:
{
uint64_t v___x_2479_; uint8_t v___x_2480_; 
v___x_2479_ = lean_uint64_shift_right(v___y_2476_, v___y_2472_);
v___x_2480_ = lean_uint64_dec_eq(v___x_2479_, v___y_2473_);
if (v___x_2480_ == 0)
{
v___y_2461_ = v___y_2478_;
v___y_2462_ = v___y_2473_;
v___y_2463_ = v___y_2474_;
v___y_2464_ = v___y_2475_;
v___y_2465_ = v___y_2476_;
v___y_2466_ = v___y_2477_;
v___y_2467_ = v___y_2472_;
goto v___jp_2460_;
}
else
{
v___y_2461_ = v___y_2478_;
v___y_2462_ = v___y_2473_;
v___y_2463_ = v___y_2474_;
v___y_2464_ = v___y_2475_;
v___y_2465_ = v___y_2476_;
v___y_2466_ = v___y_2477_;
v___y_2467_ = v___y_2473_;
goto v___jp_2460_;
}
}
v___jp_2481_:
{
uint64_t v___x_2486_; uint8_t v___x_2487_; 
v___x_2486_ = 0ULL;
v___x_2487_ = lean_uint64_dec_eq(v___y_2484_, v___x_2486_);
if (v___x_2487_ == 0)
{
uint64_t v___x_2488_; uint64_t v___x_2489_; uint8_t v___x_2490_; 
v___x_2488_ = 32ULL;
v___x_2489_ = lean_uint64_shift_right(v___y_2484_, v___x_2488_);
v___x_2490_ = lean_uint64_dec_eq(v___x_2489_, v___x_2486_);
if (v___x_2490_ == 0)
{
v___y_2472_ = v___x_2488_;
v___y_2473_ = v___x_2486_;
v___y_2474_ = v___y_2482_;
v___y_2475_ = v___y_2483_;
v___y_2476_ = v___y_2484_;
v___y_2477_ = v___y_2485_;
v___y_2478_ = v___x_2489_;
goto v___jp_2471_;
}
else
{
v___y_2472_ = v___x_2488_;
v___y_2473_ = v___x_2486_;
v___y_2474_ = v___y_2482_;
v___y_2475_ = v___y_2483_;
v___y_2476_ = v___y_2484_;
v___y_2477_ = v___y_2485_;
v___y_2478_ = v___y_2484_;
goto v___jp_2471_;
}
}
else
{
if (v___y_2485_ == 0)
{
uint32_t v___x_2491_; 
v___x_2491_ = 0;
return v___x_2491_;
}
else
{
uint32_t v___x_2492_; 
v___x_2492_ = 2147483648;
return v___x_2492_;
}
}
}
v___jp_2493_:
{
uint64_t v___x_2500_; uint64_t v___x_2501_; uint64_t v___x_2502_; uint8_t v___x_2503_; 
v___x_2500_ = lean_uint64_mul(v___y_2497_, v___y_2496_);
v___x_2501_ = lean_uint64_add(v___y_2495_, v___y_2499_);
v___x_2502_ = 281474976710656ULL;
v___x_2503_ = lean_uint64_dec_lt(v___x_2500_, v___x_2502_);
if (v___x_2503_ == 0)
{
v___y_2482_ = v___x_2501_;
v___y_2483_ = v___y_2494_;
v___y_2484_ = v___x_2500_;
v___y_2485_ = v___y_2498_;
goto v___jp_2481_;
}
else
{
uint64_t v___x_2504_; uint8_t v___x_2505_; 
v___x_2504_ = 123ULL;
v___x_2505_ = lean_uint64_dec_le(v___x_2501_, v___x_2504_);
if (v___x_2505_ == 0)
{
v___y_2482_ = v___x_2501_;
v___y_2483_ = v___y_2494_;
v___y_2484_ = v___x_2500_;
v___y_2485_ = v___y_2498_;
goto v___jp_2481_;
}
else
{
uint64_t v___x_2506_; uint8_t v___x_2507_; 
v___x_2506_ = 0ULL;
v___x_2507_ = lean_uint64_dec_eq(v___x_2500_, v___x_2506_);
if (v___x_2507_ == 0)
{
uint64_t v___x_2508_; uint64_t v___x_2509_; uint8_t v___x_2510_; 
v___x_2508_ = 149ULL;
v___x_2509_ = lean_uint64_sub(v___x_2508_, v___x_2501_);
v___x_2510_ = lean_uint64_dec_eq(v___x_2509_, v___x_2506_);
if (v___x_2510_ == 0)
{
uint64_t v___x_2511_; uint8_t v___x_2512_; 
v___x_2511_ = 64ULL;
v___x_2512_ = lean_uint64_dec_lt(v___x_2509_, v___x_2511_);
if (v___x_2512_ == 0)
{
uint8_t v___x_2513_; 
v___x_2513_ = lean_uint64_dec_eq(v___x_2509_, v___x_2511_);
if (v___x_2513_ == 0)
{
v___y_1904_ = v___y_2494_;
v___y_1905_ = v___y_2498_;
v___y_1906_ = v___x_2506_;
v___y_1907_ = v___x_2506_;
goto v___jp_1903_;
}
else
{
uint64_t v___x_2514_; uint8_t v___x_2515_; 
v___x_2514_ = 9223372036854775808ULL;
v___x_2515_ = lean_uint64_dec_lt(v___x_2514_, v___x_2500_);
if (v___x_2515_ == 0)
{
v___y_1904_ = v___y_2494_;
v___y_1905_ = v___y_2498_;
v___y_1906_ = v___x_2506_;
v___y_1907_ = v___x_2506_;
goto v___jp_1903_;
}
else
{
uint64_t v___x_2516_; 
v___x_2516_ = 1ULL;
v___y_1904_ = v___y_2494_;
v___y_1905_ = v___y_2498_;
v___y_1906_ = v___x_2506_;
v___y_1907_ = v___x_2516_;
goto v___jp_1903_;
}
}
}
else
{
uint64_t v_quotient_2517_; uint64_t v___x_2518_; uint64_t v___x_2519_; uint64_t v___x_2520_; uint64_t v_remainder_2521_; uint64_t v___x_2522_; uint64_t v_half_2523_; uint8_t v___x_2524_; 
v_quotient_2517_ = lean_uint64_shift_right(v___x_2500_, v___x_2509_);
v___x_2518_ = 1ULL;
v___x_2519_ = lean_uint64_shift_left(v___x_2518_, v___x_2509_);
v___x_2520_ = lean_uint64_sub(v___x_2519_, v___x_2518_);
v_remainder_2521_ = lean_uint64_land(v___x_2500_, v___x_2520_);
v___x_2522_ = lean_uint64_sub(v___x_2509_, v___x_2518_);
v_half_2523_ = lean_uint64_shift_left(v___x_2518_, v___x_2522_);
v___x_2524_ = lean_uint64_dec_lt(v_remainder_2521_, v_half_2523_);
if (v___x_2524_ == 0)
{
uint8_t v___x_2525_; 
v___x_2525_ = lean_uint64_dec_lt(v_half_2523_, v_remainder_2521_);
if (v___x_2525_ == 0)
{
uint64_t v___x_2526_; uint8_t v___x_2527_; 
v___x_2526_ = lean_uint64_land(v_quotient_2517_, v___x_2518_);
v___x_2527_ = lean_uint64_dec_eq(v___x_2526_, v___x_2506_);
if (v___x_2527_ == 0)
{
uint64_t v___x_2528_; 
v___x_2528_ = lean_uint64_add(v_quotient_2517_, v___x_2518_);
v___y_1904_ = v___y_2494_;
v___y_1905_ = v___y_2498_;
v___y_1906_ = v___x_2506_;
v___y_1907_ = v___x_2528_;
goto v___jp_1903_;
}
else
{
v___y_1904_ = v___y_2494_;
v___y_1905_ = v___y_2498_;
v___y_1906_ = v___x_2506_;
v___y_1907_ = v_quotient_2517_;
goto v___jp_1903_;
}
}
else
{
uint64_t v___x_2529_; 
v___x_2529_ = lean_uint64_add(v_quotient_2517_, v___x_2518_);
v___y_1904_ = v___y_2494_;
v___y_1905_ = v___y_2498_;
v___y_1906_ = v___x_2506_;
v___y_1907_ = v___x_2529_;
goto v___jp_1903_;
}
}
else
{
v___y_1904_ = v___y_2494_;
v___y_1905_ = v___y_2498_;
v___y_1906_ = v___x_2506_;
v___y_1907_ = v_quotient_2517_;
goto v___jp_1903_;
}
}
}
else
{
v___y_1904_ = v___y_2494_;
v___y_1905_ = v___y_2498_;
v___y_1906_ = v___x_2506_;
v___y_1907_ = v___x_2500_;
goto v___jp_1903_;
}
}
else
{
if (v___y_2498_ == 0)
{
uint32_t v___x_2530_; 
v___x_2530_ = 0;
return v___x_2530_;
}
else
{
uint32_t v___x_2531_; 
v___x_2531_ = 2147483648;
return v___x_2531_;
}
}
}
}
}
v___jp_2532_:
{
uint32_t v___x_2537_; uint32_t v___x_2538_; uint32_t v___x_2539_; uint32_t v___x_2540_; uint32_t v___x_2541_; 
v___x_2537_ = lean_uint32_land(v___y_2535_, v___x_2249_);
v___x_2538_ = lean_uint32_shift_left(v___x_2537_, v___x_2208_);
v___x_2539_ = lean_uint32_lor(v___y_2536_, v___x_2538_);
v___x_2540_ = lean_uint32_land(v___y_2533_, v___y_2534_);
v___x_2541_ = lean_uint32_lor(v___x_2539_, v___x_2540_);
return v___x_2541_;
}
v___jp_2542_:
{
if (v___y_2543_ == 0)
{
uint32_t v___x_2547_; 
v___x_2547_ = 0;
v___y_2533_ = v___y_2546_;
v___y_2534_ = v___y_2544_;
v___y_2535_ = v___y_2545_;
v___y_2536_ = v___x_2547_;
goto v___jp_2532_;
}
else
{
uint32_t v___x_2548_; 
v___x_2548_ = 2147483648;
v___y_2533_ = v___y_2546_;
v___y_2534_ = v___y_2544_;
v___y_2535_ = v___y_2545_;
v___y_2536_ = v___x_2548_;
goto v___jp_2532_;
}
}
v___jp_2549_:
{
uint64_t v___x_2555_; uint64_t v_encodedExponent_2556_; uint32_t v___x_2557_; uint64_t v___x_2558_; uint8_t v___x_2559_; 
v___x_2555_ = 171ULL;
v_encodedExponent_2556_ = lean_uint64_sub(v___y_2553_, v___x_2555_);
v___x_2557_ = lean_uint64_to_uint32(v_encodedExponent_2556_);
v___x_2558_ = 8388608ULL;
v___x_2559_ = lean_uint64_dec_lt(v___y_2554_, v___x_2558_);
if (v___x_2559_ == 0)
{
uint64_t v___x_2560_; uint32_t v___x_2561_; 
v___x_2560_ = lean_uint64_sub(v___y_2554_, v___x_2558_);
v___x_2561_ = lean_uint64_to_uint32(v___x_2560_);
v___y_2543_ = v___y_2550_;
v___y_2544_ = v___y_2551_;
v___y_2545_ = v___x_2557_;
v___y_2546_ = v___x_2561_;
goto v___jp_2542_;
}
else
{
uint32_t v___x_2562_; 
v___x_2562_ = lean_uint64_to_uint32(v___y_2552_);
v___y_2543_ = v___y_2550_;
v___y_2544_ = v___y_2551_;
v___y_2545_ = v___x_2557_;
v___y_2546_ = v___x_2562_;
goto v___jp_2542_;
}
}
v___jp_2563_:
{
uint64_t v___x_2570_; uint8_t v___x_2571_; 
v___x_2570_ = 425ULL;
v___x_2571_ = lean_uint64_dec_lt(v___x_2570_, v___y_2569_);
if (v___x_2571_ == 0)
{
if (v___y_2567_ == 0)
{
v___y_2550_ = v___y_2564_;
v___y_2551_ = v___y_2565_;
v___y_2552_ = v___y_2568_;
v___y_2553_ = v___y_2569_;
v___y_2554_ = v___y_2566_;
goto v___jp_2549_;
}
else
{
uint64_t v___x_2572_; 
v___x_2572_ = 8388608ULL;
v___y_2550_ = v___y_2564_;
v___y_2551_ = v___y_2565_;
v___y_2552_ = v___y_2568_;
v___y_2553_ = v___y_2569_;
v___y_2554_ = v___x_2572_;
goto v___jp_2549_;
}
}
else
{
if (v___y_2564_ == 0)
{
uint32_t v___x_2573_; 
v___x_2573_ = 2139095040;
return v___x_2573_;
}
else
{
uint32_t v___x_2574_; 
v___x_2574_ = 4286578688;
return v___x_2574_;
}
}
}
v___jp_2575_:
{
uint64_t v___x_2581_; uint8_t v_carry_2582_; 
v___x_2581_ = 16777216ULL;
v_carry_2582_ = lean_uint64_dec_eq(v___y_2580_, v___x_2581_);
if (v_carry_2582_ == 0)
{
v___y_2564_ = v___y_2576_;
v___y_2565_ = v___y_2577_;
v___y_2566_ = v___y_2580_;
v___y_2567_ = v_carry_2582_;
v___y_2568_ = v___y_2578_;
v___y_2569_ = v___y_2579_;
goto v___jp_2563_;
}
else
{
uint64_t v___x_2583_; uint64_t v___x_2584_; 
v___x_2583_ = 1ULL;
v___x_2584_ = lean_uint64_add(v___y_2579_, v___x_2583_);
v___y_2564_ = v___y_2576_;
v___y_2565_ = v___y_2577_;
v___y_2566_ = v___y_2580_;
v___y_2567_ = v_carry_2582_;
v___y_2568_ = v___y_2578_;
v___y_2569_ = v___x_2584_;
goto v___jp_2563_;
}
}
v___jp_2585_:
{
uint64_t v_position_2592_; uint64_t v___x_2593_; uint8_t v___x_2594_; 
v_position_2592_ = lean_uint64_add(v___y_2591_, v___y_2590_);
v___x_2593_ = 172ULL;
v___x_2594_ = lean_uint64_dec_lt(v_position_2592_, v___x_2593_);
if (v___x_2594_ == 0)
{
uint64_t v___x_2595_; uint8_t v___x_2596_; 
v___x_2595_ = 23ULL;
v___x_2596_ = lean_uint64_dec_lt(v___y_2591_, v___x_2595_);
if (v___x_2596_ == 0)
{
uint64_t v___x_2597_; uint8_t v___x_2598_; 
v___x_2597_ = lean_uint64_sub(v___y_2591_, v___x_2595_);
v___x_2598_ = lean_uint64_dec_eq(v___x_2597_, v___y_2589_);
if (v___x_2598_ == 0)
{
uint64_t v___x_2599_; uint8_t v___x_2600_; 
v___x_2599_ = 64ULL;
v___x_2600_ = lean_uint64_dec_lt(v___x_2597_, v___x_2599_);
if (v___x_2600_ == 0)
{
uint8_t v___x_2601_; 
v___x_2601_ = lean_uint64_dec_eq(v___x_2597_, v___x_2599_);
if (v___x_2601_ == 0)
{
v___y_2576_ = v___y_2586_;
v___y_2577_ = v___y_2587_;
v___y_2578_ = v___y_2589_;
v___y_2579_ = v_position_2592_;
v___y_2580_ = v___y_2589_;
goto v___jp_2575_;
}
else
{
uint64_t v___x_2602_; uint8_t v___x_2603_; 
v___x_2602_ = 9223372036854775808ULL;
v___x_2603_ = lean_uint64_dec_lt(v___x_2602_, v___y_2588_);
if (v___x_2603_ == 0)
{
v___y_2576_ = v___y_2586_;
v___y_2577_ = v___y_2587_;
v___y_2578_ = v___y_2589_;
v___y_2579_ = v_position_2592_;
v___y_2580_ = v___y_2589_;
goto v___jp_2575_;
}
else
{
uint64_t v___x_2604_; 
v___x_2604_ = 1ULL;
v___y_2576_ = v___y_2586_;
v___y_2577_ = v___y_2587_;
v___y_2578_ = v___y_2589_;
v___y_2579_ = v_position_2592_;
v___y_2580_ = v___x_2604_;
goto v___jp_2575_;
}
}
}
else
{
uint64_t v_quotient_2605_; uint64_t v___x_2606_; uint64_t v___x_2607_; uint64_t v___x_2608_; uint64_t v_remainder_2609_; uint64_t v___x_2610_; uint64_t v_half_2611_; uint8_t v___x_2612_; 
v_quotient_2605_ = lean_uint64_shift_right(v___y_2588_, v___x_2597_);
v___x_2606_ = 1ULL;
v___x_2607_ = lean_uint64_shift_left(v___x_2606_, v___x_2597_);
v___x_2608_ = lean_uint64_sub(v___x_2607_, v___x_2606_);
v_remainder_2609_ = lean_uint64_land(v___y_2588_, v___x_2608_);
v___x_2610_ = lean_uint64_sub(v___x_2597_, v___x_2606_);
v_half_2611_ = lean_uint64_shift_left(v___x_2606_, v___x_2610_);
v___x_2612_ = lean_uint64_dec_lt(v_remainder_2609_, v_half_2611_);
if (v___x_2612_ == 0)
{
uint8_t v___x_2613_; 
v___x_2613_ = lean_uint64_dec_lt(v_half_2611_, v_remainder_2609_);
if (v___x_2613_ == 0)
{
uint64_t v___x_2614_; uint8_t v___x_2615_; 
v___x_2614_ = lean_uint64_land(v_quotient_2605_, v___x_2606_);
v___x_2615_ = lean_uint64_dec_eq(v___x_2614_, v___y_2589_);
if (v___x_2615_ == 0)
{
uint64_t v___x_2616_; 
v___x_2616_ = lean_uint64_add(v_quotient_2605_, v___x_2606_);
v___y_2576_ = v___y_2586_;
v___y_2577_ = v___y_2587_;
v___y_2578_ = v___y_2589_;
v___y_2579_ = v_position_2592_;
v___y_2580_ = v___x_2616_;
goto v___jp_2575_;
}
else
{
v___y_2576_ = v___y_2586_;
v___y_2577_ = v___y_2587_;
v___y_2578_ = v___y_2589_;
v___y_2579_ = v_position_2592_;
v___y_2580_ = v_quotient_2605_;
goto v___jp_2575_;
}
}
else
{
uint64_t v___x_2617_; 
v___x_2617_ = lean_uint64_add(v_quotient_2605_, v___x_2606_);
v___y_2576_ = v___y_2586_;
v___y_2577_ = v___y_2587_;
v___y_2578_ = v___y_2589_;
v___y_2579_ = v_position_2592_;
v___y_2580_ = v___x_2617_;
goto v___jp_2575_;
}
}
else
{
v___y_2576_ = v___y_2586_;
v___y_2577_ = v___y_2587_;
v___y_2578_ = v___y_2589_;
v___y_2579_ = v_position_2592_;
v___y_2580_ = v_quotient_2605_;
goto v___jp_2575_;
}
}
}
else
{
v___y_2576_ = v___y_2586_;
v___y_2577_ = v___y_2587_;
v___y_2578_ = v___y_2589_;
v___y_2579_ = v_position_2592_;
v___y_2580_ = v___y_2588_;
goto v___jp_2575_;
}
}
else
{
uint64_t v___x_2618_; uint64_t v___x_2619_; 
v___x_2618_ = lean_uint64_sub(v___x_2595_, v___y_2591_);
v___x_2619_ = lean_uint64_shift_left(v___y_2588_, v___x_2618_);
v___y_2576_ = v___y_2586_;
v___y_2577_ = v___y_2587_;
v___y_2578_ = v___y_2589_;
v___y_2579_ = v_position_2592_;
v___y_2580_ = v___x_2619_;
goto v___jp_2575_;
}
}
else
{
uint64_t v___x_2620_; uint8_t v___x_2621_; 
v___x_2620_ = 149ULL;
v___x_2621_ = lean_uint64_dec_lt(v___y_2590_, v___x_2620_);
if (v___x_2621_ == 0)
{
uint64_t v___x_2622_; uint64_t v___x_2623_; 
v___x_2622_ = lean_uint64_sub(v___y_2590_, v___x_2620_);
v___x_2623_ = lean_uint64_shift_left(v___y_2588_, v___x_2622_);
v___y_2028_ = v___y_2586_;
v___y_2029_ = v___y_2587_;
v___y_2030_ = v___y_2589_;
v___y_2031_ = v___x_2623_;
goto v___jp_2027_;
}
else
{
uint64_t v___x_2624_; uint8_t v___x_2625_; 
v___x_2624_ = lean_uint64_sub(v___x_2620_, v___y_2590_);
v___x_2625_ = lean_uint64_dec_eq(v___x_2624_, v___y_2589_);
if (v___x_2625_ == 0)
{
uint64_t v___x_2626_; uint8_t v___x_2627_; 
v___x_2626_ = 64ULL;
v___x_2627_ = lean_uint64_dec_lt(v___x_2624_, v___x_2626_);
if (v___x_2627_ == 0)
{
uint8_t v___x_2628_; 
v___x_2628_ = lean_uint64_dec_eq(v___x_2624_, v___x_2626_);
if (v___x_2628_ == 0)
{
v___y_2028_ = v___y_2586_;
v___y_2029_ = v___y_2587_;
v___y_2030_ = v___y_2589_;
v___y_2031_ = v___y_2589_;
goto v___jp_2027_;
}
else
{
uint64_t v___x_2629_; uint8_t v___x_2630_; 
v___x_2629_ = 9223372036854775808ULL;
v___x_2630_ = lean_uint64_dec_lt(v___x_2629_, v___y_2588_);
if (v___x_2630_ == 0)
{
v___y_2028_ = v___y_2586_;
v___y_2029_ = v___y_2587_;
v___y_2030_ = v___y_2589_;
v___y_2031_ = v___y_2589_;
goto v___jp_2027_;
}
else
{
uint64_t v___x_2631_; 
v___x_2631_ = 1ULL;
v___y_2028_ = v___y_2586_;
v___y_2029_ = v___y_2587_;
v___y_2030_ = v___y_2589_;
v___y_2031_ = v___x_2631_;
goto v___jp_2027_;
}
}
}
else
{
uint64_t v_quotient_2632_; uint64_t v___x_2633_; uint64_t v___x_2634_; uint64_t v___x_2635_; uint64_t v_remainder_2636_; uint64_t v___x_2637_; uint64_t v_half_2638_; uint8_t v___x_2639_; 
v_quotient_2632_ = lean_uint64_shift_right(v___y_2588_, v___x_2624_);
v___x_2633_ = 1ULL;
v___x_2634_ = lean_uint64_shift_left(v___x_2633_, v___x_2624_);
v___x_2635_ = lean_uint64_sub(v___x_2634_, v___x_2633_);
v_remainder_2636_ = lean_uint64_land(v___y_2588_, v___x_2635_);
v___x_2637_ = lean_uint64_sub(v___x_2624_, v___x_2633_);
v_half_2638_ = lean_uint64_shift_left(v___x_2633_, v___x_2637_);
v___x_2639_ = lean_uint64_dec_lt(v_remainder_2636_, v_half_2638_);
if (v___x_2639_ == 0)
{
uint8_t v___x_2640_; 
v___x_2640_ = lean_uint64_dec_lt(v_half_2638_, v_remainder_2636_);
if (v___x_2640_ == 0)
{
uint64_t v___x_2641_; uint8_t v___x_2642_; 
v___x_2641_ = lean_uint64_land(v_quotient_2632_, v___x_2633_);
v___x_2642_ = lean_uint64_dec_eq(v___x_2641_, v___y_2589_);
if (v___x_2642_ == 0)
{
uint64_t v___x_2643_; 
v___x_2643_ = lean_uint64_add(v_quotient_2632_, v___x_2633_);
v___y_2028_ = v___y_2586_;
v___y_2029_ = v___y_2587_;
v___y_2030_ = v___y_2589_;
v___y_2031_ = v___x_2643_;
goto v___jp_2027_;
}
else
{
v___y_2028_ = v___y_2586_;
v___y_2029_ = v___y_2587_;
v___y_2030_ = v___y_2589_;
v___y_2031_ = v_quotient_2632_;
goto v___jp_2027_;
}
}
else
{
uint64_t v___x_2644_; 
v___x_2644_ = lean_uint64_add(v_quotient_2632_, v___x_2633_);
v___y_2028_ = v___y_2586_;
v___y_2029_ = v___y_2587_;
v___y_2030_ = v___y_2589_;
v___y_2031_ = v___x_2644_;
goto v___jp_2027_;
}
}
else
{
v___y_2028_ = v___y_2586_;
v___y_2029_ = v___y_2587_;
v___y_2030_ = v___y_2589_;
v___y_2031_ = v_quotient_2632_;
goto v___jp_2027_;
}
}
}
else
{
v___y_2028_ = v___y_2586_;
v___y_2029_ = v___y_2587_;
v___y_2030_ = v___y_2589_;
v___y_2031_ = v___y_2588_;
goto v___jp_2027_;
}
}
}
}
v___jp_2645_:
{
uint64_t v___x_2653_; uint64_t v___x_2654_; uint8_t v___x_2655_; 
v___x_2653_ = 1ULL;
v___x_2654_ = lean_uint64_shift_right(v___y_2651_, v___x_2653_);
v___x_2655_ = lean_uint64_dec_eq(v___x_2654_, v___y_2649_);
if (v___x_2655_ == 0)
{
uint64_t v___x_2656_; 
v___x_2656_ = lean_uint64_add(v___y_2652_, v___x_2653_);
v___y_2586_ = v___y_2646_;
v___y_2587_ = v___y_2647_;
v___y_2588_ = v___y_2648_;
v___y_2589_ = v___y_2649_;
v___y_2590_ = v___y_2650_;
v___y_2591_ = v___x_2656_;
goto v___jp_2585_;
}
else
{
v___y_2586_ = v___y_2646_;
v___y_2587_ = v___y_2647_;
v___y_2588_ = v___y_2648_;
v___y_2589_ = v___y_2649_;
v___y_2590_ = v___y_2650_;
v___y_2591_ = v___y_2652_;
goto v___jp_2585_;
}
}
v___jp_2657_:
{
uint64_t v___x_2667_; uint8_t v___x_2668_; 
v___x_2667_ = lean_uint64_shift_right(v___y_2665_, v___y_2660_);
v___x_2668_ = lean_uint64_dec_eq(v___x_2667_, v___y_2662_);
if (v___x_2668_ == 0)
{
uint64_t v___x_2669_; 
v___x_2669_ = lean_uint64_add(v___y_2664_, v___y_2660_);
v___y_2646_ = v___y_2658_;
v___y_2647_ = v___y_2659_;
v___y_2648_ = v___y_2661_;
v___y_2649_ = v___y_2662_;
v___y_2650_ = v___y_2663_;
v___y_2651_ = v___y_2666_;
v___y_2652_ = v___x_2669_;
goto v___jp_2645_;
}
else
{
v___y_2646_ = v___y_2658_;
v___y_2647_ = v___y_2659_;
v___y_2648_ = v___y_2661_;
v___y_2649_ = v___y_2662_;
v___y_2650_ = v___y_2663_;
v___y_2651_ = v___y_2666_;
v___y_2652_ = v___y_2664_;
goto v___jp_2645_;
}
}
v___jp_2670_:
{
uint64_t v___x_2678_; uint64_t v___x_2679_; uint8_t v___x_2680_; 
v___x_2678_ = 2ULL;
v___x_2679_ = lean_uint64_shift_right(v___y_2676_, v___x_2678_);
v___x_2680_ = lean_uint64_dec_eq(v___x_2679_, v___y_2674_);
if (v___x_2680_ == 0)
{
v___y_2658_ = v___y_2671_;
v___y_2659_ = v___y_2672_;
v___y_2660_ = v___x_2678_;
v___y_2661_ = v___y_2673_;
v___y_2662_ = v___y_2674_;
v___y_2663_ = v___y_2675_;
v___y_2664_ = v___y_2677_;
v___y_2665_ = v___y_2676_;
v___y_2666_ = v___x_2679_;
goto v___jp_2657_;
}
else
{
v___y_2658_ = v___y_2671_;
v___y_2659_ = v___y_2672_;
v___y_2660_ = v___x_2678_;
v___y_2661_ = v___y_2673_;
v___y_2662_ = v___y_2674_;
v___y_2663_ = v___y_2675_;
v___y_2664_ = v___y_2677_;
v___y_2665_ = v___y_2676_;
v___y_2666_ = v___y_2676_;
goto v___jp_2657_;
}
}
v___jp_2681_:
{
uint64_t v___x_2691_; uint8_t v___x_2692_; 
v___x_2691_ = lean_uint64_shift_right(v___y_2684_, v___y_2688_);
v___x_2692_ = lean_uint64_dec_eq(v___x_2691_, v___y_2686_);
if (v___x_2692_ == 0)
{
uint64_t v___x_2693_; 
v___x_2693_ = lean_uint64_add(v___y_2687_, v___y_2688_);
v___y_2671_ = v___y_2682_;
v___y_2672_ = v___y_2683_;
v___y_2673_ = v___y_2685_;
v___y_2674_ = v___y_2686_;
v___y_2675_ = v___y_2689_;
v___y_2676_ = v___y_2690_;
v___y_2677_ = v___x_2693_;
goto v___jp_2670_;
}
else
{
v___y_2671_ = v___y_2682_;
v___y_2672_ = v___y_2683_;
v___y_2673_ = v___y_2685_;
v___y_2674_ = v___y_2686_;
v___y_2675_ = v___y_2689_;
v___y_2676_ = v___y_2690_;
v___y_2677_ = v___y_2687_;
goto v___jp_2670_;
}
}
v___jp_2694_:
{
uint64_t v___x_2702_; uint64_t v___x_2703_; uint8_t v___x_2704_; 
v___x_2702_ = 4ULL;
v___x_2703_ = lean_uint64_shift_right(v___y_2698_, v___x_2702_);
v___x_2704_ = lean_uint64_dec_eq(v___x_2703_, v___y_2699_);
if (v___x_2704_ == 0)
{
v___y_2682_ = v___y_2695_;
v___y_2683_ = v___y_2696_;
v___y_2684_ = v___y_2698_;
v___y_2685_ = v___y_2697_;
v___y_2686_ = v___y_2699_;
v___y_2687_ = v___y_2701_;
v___y_2688_ = v___x_2702_;
v___y_2689_ = v___y_2700_;
v___y_2690_ = v___x_2703_;
goto v___jp_2681_;
}
else
{
v___y_2682_ = v___y_2695_;
v___y_2683_ = v___y_2696_;
v___y_2684_ = v___y_2698_;
v___y_2685_ = v___y_2697_;
v___y_2686_ = v___y_2699_;
v___y_2687_ = v___y_2701_;
v___y_2688_ = v___x_2702_;
v___y_2689_ = v___y_2700_;
v___y_2690_ = v___y_2698_;
goto v___jp_2681_;
}
}
v___jp_2705_:
{
uint64_t v___x_2715_; uint8_t v___x_2716_; 
v___x_2715_ = lean_uint64_shift_right(v___y_2713_, v___y_2708_);
v___x_2716_ = lean_uint64_dec_eq(v___x_2715_, v___y_2710_);
if (v___x_2716_ == 0)
{
uint64_t v___x_2717_; 
v___x_2717_ = lean_uint64_add(v___y_2711_, v___y_2708_);
v___y_2695_ = v___y_2706_;
v___y_2696_ = v___y_2707_;
v___y_2697_ = v___y_2709_;
v___y_2698_ = v___y_2714_;
v___y_2699_ = v___y_2710_;
v___y_2700_ = v___y_2712_;
v___y_2701_ = v___x_2717_;
goto v___jp_2694_;
}
else
{
v___y_2695_ = v___y_2706_;
v___y_2696_ = v___y_2707_;
v___y_2697_ = v___y_2709_;
v___y_2698_ = v___y_2714_;
v___y_2699_ = v___y_2710_;
v___y_2700_ = v___y_2712_;
v___y_2701_ = v___y_2711_;
goto v___jp_2694_;
}
}
v___jp_2718_:
{
uint64_t v___x_2726_; uint64_t v___x_2727_; uint8_t v___x_2728_; 
v___x_2726_ = 8ULL;
v___x_2727_ = lean_uint64_shift_right(v___y_2724_, v___x_2726_);
v___x_2728_ = lean_uint64_dec_eq(v___x_2727_, v___y_2722_);
if (v___x_2728_ == 0)
{
v___y_2706_ = v___y_2719_;
v___y_2707_ = v___y_2720_;
v___y_2708_ = v___x_2726_;
v___y_2709_ = v___y_2721_;
v___y_2710_ = v___y_2722_;
v___y_2711_ = v___y_2725_;
v___y_2712_ = v___y_2723_;
v___y_2713_ = v___y_2724_;
v___y_2714_ = v___x_2727_;
goto v___jp_2705_;
}
else
{
v___y_2706_ = v___y_2719_;
v___y_2707_ = v___y_2720_;
v___y_2708_ = v___x_2726_;
v___y_2709_ = v___y_2721_;
v___y_2710_ = v___y_2722_;
v___y_2711_ = v___y_2725_;
v___y_2712_ = v___y_2723_;
v___y_2713_ = v___y_2724_;
v___y_2714_ = v___y_2724_;
goto v___jp_2705_;
}
}
v___jp_2729_:
{
uint64_t v___x_2739_; uint8_t v___x_2740_; 
v___x_2739_ = lean_uint64_shift_right(v___y_2734_, v___y_2737_);
v___x_2740_ = lean_uint64_dec_eq(v___x_2739_, v___y_2733_);
if (v___x_2740_ == 0)
{
uint64_t v___x_2741_; 
v___x_2741_ = lean_uint64_add(v___y_2736_, v___y_2737_);
v___y_2719_ = v___y_2730_;
v___y_2720_ = v___y_2731_;
v___y_2721_ = v___y_2732_;
v___y_2722_ = v___y_2733_;
v___y_2723_ = v___y_2735_;
v___y_2724_ = v___y_2738_;
v___y_2725_ = v___x_2741_;
goto v___jp_2718_;
}
else
{
v___y_2719_ = v___y_2730_;
v___y_2720_ = v___y_2731_;
v___y_2721_ = v___y_2732_;
v___y_2722_ = v___y_2733_;
v___y_2723_ = v___y_2735_;
v___y_2724_ = v___y_2738_;
v___y_2725_ = v___y_2736_;
goto v___jp_2718_;
}
}
v___jp_2742_:
{
uint64_t v___x_2750_; uint64_t v___x_2751_; uint8_t v___x_2752_; 
v___x_2750_ = 16ULL;
v___x_2751_ = lean_uint64_shift_right(v___y_2747_, v___x_2750_);
v___x_2752_ = lean_uint64_dec_eq(v___x_2751_, v___y_2746_);
if (v___x_2752_ == 0)
{
v___y_2730_ = v___y_2743_;
v___y_2731_ = v___y_2744_;
v___y_2732_ = v___y_2745_;
v___y_2733_ = v___y_2746_;
v___y_2734_ = v___y_2747_;
v___y_2735_ = v___y_2748_;
v___y_2736_ = v___y_2749_;
v___y_2737_ = v___x_2750_;
v___y_2738_ = v___x_2751_;
goto v___jp_2729_;
}
else
{
v___y_2730_ = v___y_2743_;
v___y_2731_ = v___y_2744_;
v___y_2732_ = v___y_2745_;
v___y_2733_ = v___y_2746_;
v___y_2734_ = v___y_2747_;
v___y_2735_ = v___y_2748_;
v___y_2736_ = v___y_2749_;
v___y_2737_ = v___x_2750_;
v___y_2738_ = v___y_2747_;
goto v___jp_2729_;
}
}
v___jp_2753_:
{
uint64_t v___x_2761_; uint8_t v___x_2762_; 
v___x_2761_ = lean_uint64_shift_right(v___y_2756_, v___y_2758_);
v___x_2762_ = lean_uint64_dec_eq(v___x_2761_, v___y_2757_);
if (v___x_2762_ == 0)
{
v___y_2743_ = v___y_2754_;
v___y_2744_ = v___y_2755_;
v___y_2745_ = v___y_2756_;
v___y_2746_ = v___y_2757_;
v___y_2747_ = v___y_2760_;
v___y_2748_ = v___y_2759_;
v___y_2749_ = v___y_2758_;
goto v___jp_2742_;
}
else
{
v___y_2743_ = v___y_2754_;
v___y_2744_ = v___y_2755_;
v___y_2745_ = v___y_2756_;
v___y_2746_ = v___y_2757_;
v___y_2747_ = v___y_2760_;
v___y_2748_ = v___y_2759_;
v___y_2749_ = v___y_2757_;
goto v___jp_2742_;
}
}
v___jp_2763_:
{
uint64_t v___x_2768_; uint8_t v___x_2769_; 
v___x_2768_ = 0ULL;
v___x_2769_ = lean_uint64_dec_eq(v___y_2766_, v___x_2768_);
if (v___x_2769_ == 0)
{
uint64_t v___x_2770_; uint64_t v___x_2771_; uint8_t v___x_2772_; 
v___x_2770_ = 32ULL;
v___x_2771_ = lean_uint64_shift_right(v___y_2766_, v___x_2770_);
v___x_2772_ = lean_uint64_dec_eq(v___x_2771_, v___x_2768_);
if (v___x_2772_ == 0)
{
v___y_2754_ = v___y_2764_;
v___y_2755_ = v___y_2765_;
v___y_2756_ = v___y_2766_;
v___y_2757_ = v___x_2768_;
v___y_2758_ = v___x_2770_;
v___y_2759_ = v___y_2767_;
v___y_2760_ = v___x_2771_;
goto v___jp_2753_;
}
else
{
v___y_2754_ = v___y_2764_;
v___y_2755_ = v___y_2765_;
v___y_2756_ = v___y_2766_;
v___y_2757_ = v___x_2768_;
v___y_2758_ = v___x_2770_;
v___y_2759_ = v___y_2767_;
v___y_2760_ = v___y_2766_;
goto v___jp_2753_;
}
}
else
{
if (v___y_2764_ == 0)
{
uint32_t v___x_2773_; 
v___x_2773_ = 0;
return v___x_2773_;
}
else
{
uint32_t v___x_2774_; 
v___x_2774_ = 2147483648;
return v___x_2774_;
}
}
}
v___jp_2775_:
{
uint64_t v___x_2782_; uint64_t v___x_2783_; uint64_t v___x_2784_; uint8_t v___x_2785_; 
v___x_2782_ = lean_uint64_mul(v___y_2780_, v___y_2778_);
v___x_2783_ = lean_uint64_add(v___y_2779_, v___y_2781_);
v___x_2784_ = 281474976710656ULL;
v___x_2785_ = lean_uint64_dec_lt(v___x_2782_, v___x_2784_);
if (v___x_2785_ == 0)
{
v___y_2764_ = v___y_2776_;
v___y_2765_ = v___y_2777_;
v___y_2766_ = v___x_2782_;
v___y_2767_ = v___x_2783_;
goto v___jp_2763_;
}
else
{
uint64_t v___x_2786_; uint8_t v___x_2787_; 
v___x_2786_ = 123ULL;
v___x_2787_ = lean_uint64_dec_le(v___x_2783_, v___x_2786_);
if (v___x_2787_ == 0)
{
v___y_2764_ = v___y_2776_;
v___y_2765_ = v___y_2777_;
v___y_2766_ = v___x_2782_;
v___y_2767_ = v___x_2783_;
goto v___jp_2763_;
}
else
{
uint64_t v___x_2788_; uint8_t v___x_2789_; 
v___x_2788_ = 0ULL;
v___x_2789_ = lean_uint64_dec_eq(v___x_2782_, v___x_2788_);
if (v___x_2789_ == 0)
{
uint64_t v___x_2790_; uint64_t v___x_2791_; uint8_t v___x_2792_; 
v___x_2790_ = 149ULL;
v___x_2791_ = lean_uint64_sub(v___x_2790_, v___x_2783_);
v___x_2792_ = lean_uint64_dec_eq(v___x_2791_, v___x_2788_);
if (v___x_2792_ == 0)
{
uint64_t v___x_2793_; uint8_t v___x_2794_; 
v___x_2793_ = 64ULL;
v___x_2794_ = lean_uint64_dec_lt(v___x_2791_, v___x_2793_);
if (v___x_2794_ == 0)
{
uint8_t v___x_2795_; 
v___x_2795_ = lean_uint64_dec_eq(v___x_2791_, v___x_2793_);
if (v___x_2795_ == 0)
{
v___y_2049_ = v___y_2776_;
v___y_2050_ = v___y_2777_;
v___y_2051_ = v___x_2788_;
v___y_2052_ = v___x_2788_;
goto v___jp_2048_;
}
else
{
uint64_t v___x_2796_; uint8_t v___x_2797_; 
v___x_2796_ = 9223372036854775808ULL;
v___x_2797_ = lean_uint64_dec_lt(v___x_2796_, v___x_2782_);
if (v___x_2797_ == 0)
{
v___y_2049_ = v___y_2776_;
v___y_2050_ = v___y_2777_;
v___y_2051_ = v___x_2788_;
v___y_2052_ = v___x_2788_;
goto v___jp_2048_;
}
else
{
uint64_t v___x_2798_; 
v___x_2798_ = 1ULL;
v___y_2049_ = v___y_2776_;
v___y_2050_ = v___y_2777_;
v___y_2051_ = v___x_2788_;
v___y_2052_ = v___x_2798_;
goto v___jp_2048_;
}
}
}
else
{
uint64_t v_quotient_2799_; uint64_t v___x_2800_; uint64_t v___x_2801_; uint64_t v___x_2802_; uint64_t v_remainder_2803_; uint64_t v___x_2804_; uint64_t v_half_2805_; uint8_t v___x_2806_; 
v_quotient_2799_ = lean_uint64_shift_right(v___x_2782_, v___x_2791_);
v___x_2800_ = 1ULL;
v___x_2801_ = lean_uint64_shift_left(v___x_2800_, v___x_2791_);
v___x_2802_ = lean_uint64_sub(v___x_2801_, v___x_2800_);
v_remainder_2803_ = lean_uint64_land(v___x_2782_, v___x_2802_);
v___x_2804_ = lean_uint64_sub(v___x_2791_, v___x_2800_);
v_half_2805_ = lean_uint64_shift_left(v___x_2800_, v___x_2804_);
v___x_2806_ = lean_uint64_dec_lt(v_remainder_2803_, v_half_2805_);
if (v___x_2806_ == 0)
{
uint8_t v___x_2807_; 
v___x_2807_ = lean_uint64_dec_lt(v_half_2805_, v_remainder_2803_);
if (v___x_2807_ == 0)
{
uint64_t v___x_2808_; uint8_t v___x_2809_; 
v___x_2808_ = lean_uint64_land(v_quotient_2799_, v___x_2800_);
v___x_2809_ = lean_uint64_dec_eq(v___x_2808_, v___x_2788_);
if (v___x_2809_ == 0)
{
uint64_t v___x_2810_; 
v___x_2810_ = lean_uint64_add(v_quotient_2799_, v___x_2800_);
v___y_2049_ = v___y_2776_;
v___y_2050_ = v___y_2777_;
v___y_2051_ = v___x_2788_;
v___y_2052_ = v___x_2810_;
goto v___jp_2048_;
}
else
{
v___y_2049_ = v___y_2776_;
v___y_2050_ = v___y_2777_;
v___y_2051_ = v___x_2788_;
v___y_2052_ = v_quotient_2799_;
goto v___jp_2048_;
}
}
else
{
uint64_t v___x_2811_; 
v___x_2811_ = lean_uint64_add(v_quotient_2799_, v___x_2800_);
v___y_2049_ = v___y_2776_;
v___y_2050_ = v___y_2777_;
v___y_2051_ = v___x_2788_;
v___y_2052_ = v___x_2811_;
goto v___jp_2048_;
}
}
else
{
v___y_2049_ = v___y_2776_;
v___y_2050_ = v___y_2777_;
v___y_2051_ = v___x_2788_;
v___y_2052_ = v_quotient_2799_;
goto v___jp_2048_;
}
}
}
else
{
v___y_2049_ = v___y_2776_;
v___y_2050_ = v___y_2777_;
v___y_2051_ = v___x_2788_;
v___y_2052_ = v___x_2782_;
goto v___jp_2048_;
}
}
else
{
if (v___y_2776_ == 0)
{
uint32_t v___x_2812_; 
v___x_2812_ = 0;
return v___x_2812_;
}
else
{
uint32_t v___x_2813_; 
v___x_2813_ = 2147483648;
return v___x_2813_;
}
}
}
}
}
v___jp_2814_:
{
uint32_t v___x_2819_; uint32_t v___x_2820_; uint32_t v___x_2821_; uint32_t v___x_2822_; uint32_t v___x_2823_; 
v___x_2819_ = lean_uint32_land(v___y_2817_, v___x_2249_);
v___x_2820_ = lean_uint32_shift_left(v___x_2819_, v___x_2208_);
v___x_2821_ = lean_uint32_lor(v___y_2818_, v___x_2820_);
v___x_2822_ = lean_uint32_land(v___y_2816_, v___y_2815_);
v___x_2823_ = lean_uint32_lor(v___x_2821_, v___x_2822_);
return v___x_2823_;
}
v___jp_2824_:
{
if (v___y_2825_ == 0)
{
uint32_t v___x_2829_; 
v___x_2829_ = 0;
v___y_2815_ = v___y_2826_;
v___y_2816_ = v___y_2828_;
v___y_2817_ = v___y_2827_;
v___y_2818_ = v___x_2829_;
goto v___jp_2814_;
}
else
{
uint32_t v___x_2830_; 
v___x_2830_ = 2147483648;
v___y_2815_ = v___y_2826_;
v___y_2816_ = v___y_2828_;
v___y_2817_ = v___y_2827_;
v___y_2818_ = v___x_2830_;
goto v___jp_2814_;
}
}
v___jp_2831_:
{
uint64_t v___x_2837_; uint64_t v_encodedExponent_2838_; uint32_t v___x_2839_; uint64_t v___x_2840_; uint8_t v___x_2841_; 
v___x_2837_ = 171ULL;
v_encodedExponent_2838_ = lean_uint64_sub(v___y_2835_, v___x_2837_);
v___x_2839_ = lean_uint64_to_uint32(v_encodedExponent_2838_);
v___x_2840_ = 8388608ULL;
v___x_2841_ = lean_uint64_dec_lt(v___y_2836_, v___x_2840_);
if (v___x_2841_ == 0)
{
uint64_t v___x_2842_; uint32_t v___x_2843_; 
v___x_2842_ = lean_uint64_sub(v___y_2836_, v___x_2840_);
v___x_2843_ = lean_uint64_to_uint32(v___x_2842_);
v___y_2825_ = v___y_2832_;
v___y_2826_ = v___y_2833_;
v___y_2827_ = v___x_2839_;
v___y_2828_ = v___x_2843_;
goto v___jp_2824_;
}
else
{
uint32_t v___x_2844_; 
v___x_2844_ = lean_uint64_to_uint32(v___y_2834_);
v___y_2825_ = v___y_2832_;
v___y_2826_ = v___y_2833_;
v___y_2827_ = v___x_2839_;
v___y_2828_ = v___x_2844_;
goto v___jp_2824_;
}
}
v___jp_2845_:
{
uint64_t v___x_2852_; uint8_t v___x_2853_; 
v___x_2852_ = 425ULL;
v___x_2853_ = lean_uint64_dec_lt(v___x_2852_, v___y_2851_);
if (v___x_2853_ == 0)
{
if (v___y_2846_ == 0)
{
v___y_2832_ = v___y_2847_;
v___y_2833_ = v___y_2848_;
v___y_2834_ = v___y_2849_;
v___y_2835_ = v___y_2851_;
v___y_2836_ = v___y_2850_;
goto v___jp_2831_;
}
else
{
uint64_t v___x_2854_; 
v___x_2854_ = 8388608ULL;
v___y_2832_ = v___y_2847_;
v___y_2833_ = v___y_2848_;
v___y_2834_ = v___y_2849_;
v___y_2835_ = v___y_2851_;
v___y_2836_ = v___x_2854_;
goto v___jp_2831_;
}
}
else
{
if (v___y_2847_ == 0)
{
uint32_t v___x_2855_; 
v___x_2855_ = 2139095040;
return v___x_2855_;
}
else
{
uint32_t v___x_2856_; 
v___x_2856_ = 4286578688;
return v___x_2856_;
}
}
}
v___jp_2857_:
{
uint64_t v___x_2863_; uint8_t v_carry_2864_; 
v___x_2863_ = 16777216ULL;
v_carry_2864_ = lean_uint64_dec_eq(v___y_2862_, v___x_2863_);
if (v_carry_2864_ == 0)
{
v___y_2846_ = v_carry_2864_;
v___y_2847_ = v___y_2859_;
v___y_2848_ = v___y_2860_;
v___y_2849_ = v___y_2861_;
v___y_2850_ = v___y_2862_;
v___y_2851_ = v___y_2858_;
goto v___jp_2845_;
}
else
{
uint64_t v___x_2865_; uint64_t v___x_2866_; 
v___x_2865_ = 1ULL;
v___x_2866_ = lean_uint64_add(v___y_2858_, v___x_2865_);
v___y_2846_ = v_carry_2864_;
v___y_2847_ = v___y_2859_;
v___y_2848_ = v___y_2860_;
v___y_2849_ = v___y_2861_;
v___y_2850_ = v___y_2862_;
v___y_2851_ = v___x_2866_;
goto v___jp_2845_;
}
}
v___jp_2867_:
{
uint64_t v_position_2874_; uint64_t v___x_2875_; uint8_t v___x_2876_; 
v_position_2874_ = lean_uint64_add(v___y_2873_, v___y_2869_);
v___x_2875_ = 172ULL;
v___x_2876_ = lean_uint64_dec_lt(v_position_2874_, v___x_2875_);
if (v___x_2876_ == 0)
{
uint64_t v___x_2877_; uint8_t v___x_2878_; 
v___x_2877_ = 23ULL;
v___x_2878_ = lean_uint64_dec_lt(v___y_2873_, v___x_2877_);
if (v___x_2878_ == 0)
{
uint64_t v___x_2879_; uint8_t v___x_2880_; 
v___x_2879_ = lean_uint64_sub(v___y_2873_, v___x_2877_);
v___x_2880_ = lean_uint64_dec_eq(v___x_2879_, v___y_2872_);
if (v___x_2880_ == 0)
{
uint64_t v___x_2881_; uint8_t v___x_2882_; 
v___x_2881_ = 64ULL;
v___x_2882_ = lean_uint64_dec_lt(v___x_2879_, v___x_2881_);
if (v___x_2882_ == 0)
{
uint8_t v___x_2883_; 
v___x_2883_ = lean_uint64_dec_eq(v___x_2879_, v___x_2881_);
if (v___x_2883_ == 0)
{
v___y_2858_ = v_position_2874_;
v___y_2859_ = v___y_2868_;
v___y_2860_ = v___y_2870_;
v___y_2861_ = v___y_2872_;
v___y_2862_ = v___y_2872_;
goto v___jp_2857_;
}
else
{
uint64_t v___x_2884_; uint8_t v___x_2885_; 
v___x_2884_ = 9223372036854775808ULL;
v___x_2885_ = lean_uint64_dec_lt(v___x_2884_, v___y_2871_);
if (v___x_2885_ == 0)
{
v___y_2858_ = v_position_2874_;
v___y_2859_ = v___y_2868_;
v___y_2860_ = v___y_2870_;
v___y_2861_ = v___y_2872_;
v___y_2862_ = v___y_2872_;
goto v___jp_2857_;
}
else
{
uint64_t v___x_2886_; 
v___x_2886_ = 1ULL;
v___y_2858_ = v_position_2874_;
v___y_2859_ = v___y_2868_;
v___y_2860_ = v___y_2870_;
v___y_2861_ = v___y_2872_;
v___y_2862_ = v___x_2886_;
goto v___jp_2857_;
}
}
}
else
{
uint64_t v_quotient_2887_; uint64_t v___x_2888_; uint64_t v___x_2889_; uint64_t v___x_2890_; uint64_t v_remainder_2891_; uint64_t v___x_2892_; uint64_t v_half_2893_; uint8_t v___x_2894_; 
v_quotient_2887_ = lean_uint64_shift_right(v___y_2871_, v___x_2879_);
v___x_2888_ = 1ULL;
v___x_2889_ = lean_uint64_shift_left(v___x_2888_, v___x_2879_);
v___x_2890_ = lean_uint64_sub(v___x_2889_, v___x_2888_);
v_remainder_2891_ = lean_uint64_land(v___y_2871_, v___x_2890_);
v___x_2892_ = lean_uint64_sub(v___x_2879_, v___x_2888_);
v_half_2893_ = lean_uint64_shift_left(v___x_2888_, v___x_2892_);
v___x_2894_ = lean_uint64_dec_lt(v_remainder_2891_, v_half_2893_);
if (v___x_2894_ == 0)
{
uint8_t v___x_2895_; 
v___x_2895_ = lean_uint64_dec_lt(v_half_2893_, v_remainder_2891_);
if (v___x_2895_ == 0)
{
uint64_t v___x_2896_; uint8_t v___x_2897_; 
v___x_2896_ = lean_uint64_land(v_quotient_2887_, v___x_2888_);
v___x_2897_ = lean_uint64_dec_eq(v___x_2896_, v___y_2872_);
if (v___x_2897_ == 0)
{
uint64_t v___x_2898_; 
v___x_2898_ = lean_uint64_add(v_quotient_2887_, v___x_2888_);
v___y_2858_ = v_position_2874_;
v___y_2859_ = v___y_2868_;
v___y_2860_ = v___y_2870_;
v___y_2861_ = v___y_2872_;
v___y_2862_ = v___x_2898_;
goto v___jp_2857_;
}
else
{
v___y_2858_ = v_position_2874_;
v___y_2859_ = v___y_2868_;
v___y_2860_ = v___y_2870_;
v___y_2861_ = v___y_2872_;
v___y_2862_ = v_quotient_2887_;
goto v___jp_2857_;
}
}
else
{
uint64_t v___x_2899_; 
v___x_2899_ = lean_uint64_add(v_quotient_2887_, v___x_2888_);
v___y_2858_ = v_position_2874_;
v___y_2859_ = v___y_2868_;
v___y_2860_ = v___y_2870_;
v___y_2861_ = v___y_2872_;
v___y_2862_ = v___x_2899_;
goto v___jp_2857_;
}
}
else
{
v___y_2858_ = v_position_2874_;
v___y_2859_ = v___y_2868_;
v___y_2860_ = v___y_2870_;
v___y_2861_ = v___y_2872_;
v___y_2862_ = v_quotient_2887_;
goto v___jp_2857_;
}
}
}
else
{
v___y_2858_ = v_position_2874_;
v___y_2859_ = v___y_2868_;
v___y_2860_ = v___y_2870_;
v___y_2861_ = v___y_2872_;
v___y_2862_ = v___y_2871_;
goto v___jp_2857_;
}
}
else
{
uint64_t v___x_2900_; uint64_t v___x_2901_; 
v___x_2900_ = lean_uint64_sub(v___x_2877_, v___y_2873_);
v___x_2901_ = lean_uint64_shift_left(v___y_2871_, v___x_2900_);
v___y_2858_ = v_position_2874_;
v___y_2859_ = v___y_2868_;
v___y_2860_ = v___y_2870_;
v___y_2861_ = v___y_2872_;
v___y_2862_ = v___x_2901_;
goto v___jp_2857_;
}
}
else
{
uint64_t v___x_2902_; uint8_t v___x_2903_; 
v___x_2902_ = 149ULL;
v___x_2903_ = lean_uint64_dec_lt(v___y_2869_, v___x_2902_);
if (v___x_2903_ == 0)
{
uint64_t v___x_2904_; uint64_t v___x_2905_; 
v___x_2904_ = lean_uint64_sub(v___y_2869_, v___x_2902_);
v___x_2905_ = lean_uint64_shift_left(v___y_2871_, v___x_2904_);
v___y_2173_ = v___y_2868_;
v___y_2174_ = v___y_2870_;
v___y_2175_ = v___y_2872_;
v___y_2176_ = v___x_2905_;
goto v___jp_2172_;
}
else
{
uint64_t v___x_2906_; uint8_t v___x_2907_; 
v___x_2906_ = lean_uint64_sub(v___x_2902_, v___y_2869_);
v___x_2907_ = lean_uint64_dec_eq(v___x_2906_, v___y_2872_);
if (v___x_2907_ == 0)
{
uint64_t v___x_2908_; uint8_t v___x_2909_; 
v___x_2908_ = 64ULL;
v___x_2909_ = lean_uint64_dec_lt(v___x_2906_, v___x_2908_);
if (v___x_2909_ == 0)
{
uint8_t v___x_2910_; 
v___x_2910_ = lean_uint64_dec_eq(v___x_2906_, v___x_2908_);
if (v___x_2910_ == 0)
{
v___y_2173_ = v___y_2868_;
v___y_2174_ = v___y_2870_;
v___y_2175_ = v___y_2872_;
v___y_2176_ = v___y_2872_;
goto v___jp_2172_;
}
else
{
uint64_t v___x_2911_; uint8_t v___x_2912_; 
v___x_2911_ = 9223372036854775808ULL;
v___x_2912_ = lean_uint64_dec_lt(v___x_2911_, v___y_2871_);
if (v___x_2912_ == 0)
{
v___y_2173_ = v___y_2868_;
v___y_2174_ = v___y_2870_;
v___y_2175_ = v___y_2872_;
v___y_2176_ = v___y_2872_;
goto v___jp_2172_;
}
else
{
uint64_t v___x_2913_; 
v___x_2913_ = 1ULL;
v___y_2173_ = v___y_2868_;
v___y_2174_ = v___y_2870_;
v___y_2175_ = v___y_2872_;
v___y_2176_ = v___x_2913_;
goto v___jp_2172_;
}
}
}
else
{
uint64_t v_quotient_2914_; uint64_t v___x_2915_; uint64_t v___x_2916_; uint64_t v___x_2917_; uint64_t v_remainder_2918_; uint64_t v___x_2919_; uint64_t v_half_2920_; uint8_t v___x_2921_; 
v_quotient_2914_ = lean_uint64_shift_right(v___y_2871_, v___x_2906_);
v___x_2915_ = 1ULL;
v___x_2916_ = lean_uint64_shift_left(v___x_2915_, v___x_2906_);
v___x_2917_ = lean_uint64_sub(v___x_2916_, v___x_2915_);
v_remainder_2918_ = lean_uint64_land(v___y_2871_, v___x_2917_);
v___x_2919_ = lean_uint64_sub(v___x_2906_, v___x_2915_);
v_half_2920_ = lean_uint64_shift_left(v___x_2915_, v___x_2919_);
v___x_2921_ = lean_uint64_dec_lt(v_remainder_2918_, v_half_2920_);
if (v___x_2921_ == 0)
{
uint8_t v___x_2922_; 
v___x_2922_ = lean_uint64_dec_lt(v_half_2920_, v_remainder_2918_);
if (v___x_2922_ == 0)
{
uint64_t v___x_2923_; uint8_t v___x_2924_; 
v___x_2923_ = lean_uint64_land(v_quotient_2914_, v___x_2915_);
v___x_2924_ = lean_uint64_dec_eq(v___x_2923_, v___y_2872_);
if (v___x_2924_ == 0)
{
uint64_t v___x_2925_; 
v___x_2925_ = lean_uint64_add(v_quotient_2914_, v___x_2915_);
v___y_2173_ = v___y_2868_;
v___y_2174_ = v___y_2870_;
v___y_2175_ = v___y_2872_;
v___y_2176_ = v___x_2925_;
goto v___jp_2172_;
}
else
{
v___y_2173_ = v___y_2868_;
v___y_2174_ = v___y_2870_;
v___y_2175_ = v___y_2872_;
v___y_2176_ = v_quotient_2914_;
goto v___jp_2172_;
}
}
else
{
uint64_t v___x_2926_; 
v___x_2926_ = lean_uint64_add(v_quotient_2914_, v___x_2915_);
v___y_2173_ = v___y_2868_;
v___y_2174_ = v___y_2870_;
v___y_2175_ = v___y_2872_;
v___y_2176_ = v___x_2926_;
goto v___jp_2172_;
}
}
else
{
v___y_2173_ = v___y_2868_;
v___y_2174_ = v___y_2870_;
v___y_2175_ = v___y_2872_;
v___y_2176_ = v_quotient_2914_;
goto v___jp_2172_;
}
}
}
else
{
v___y_2173_ = v___y_2868_;
v___y_2174_ = v___y_2870_;
v___y_2175_ = v___y_2872_;
v___y_2176_ = v___y_2871_;
goto v___jp_2172_;
}
}
}
}
v___jp_2927_:
{
uint64_t v___x_2935_; uint64_t v___x_2936_; uint8_t v___x_2937_; 
v___x_2935_ = 1ULL;
v___x_2936_ = lean_uint64_shift_right(v___y_2933_, v___x_2935_);
v___x_2937_ = lean_uint64_dec_eq(v___x_2936_, v___y_2932_);
if (v___x_2937_ == 0)
{
uint64_t v___x_2938_; 
v___x_2938_ = lean_uint64_add(v___y_2934_, v___x_2935_);
v___y_2868_ = v___y_2929_;
v___y_2869_ = v___y_2928_;
v___y_2870_ = v___y_2930_;
v___y_2871_ = v___y_2931_;
v___y_2872_ = v___y_2932_;
v___y_2873_ = v___x_2938_;
goto v___jp_2867_;
}
else
{
v___y_2868_ = v___y_2929_;
v___y_2869_ = v___y_2928_;
v___y_2870_ = v___y_2930_;
v___y_2871_ = v___y_2931_;
v___y_2872_ = v___y_2932_;
v___y_2873_ = v___y_2934_;
goto v___jp_2867_;
}
}
v___jp_2939_:
{
uint64_t v___x_2949_; uint8_t v___x_2950_; 
v___x_2949_ = lean_uint64_shift_right(v___y_2940_, v___y_2941_);
v___x_2950_ = lean_uint64_dec_eq(v___x_2949_, v___y_2946_);
if (v___x_2950_ == 0)
{
uint64_t v___x_2951_; 
v___x_2951_ = lean_uint64_add(v___y_2942_, v___y_2941_);
v___y_2928_ = v___y_2944_;
v___y_2929_ = v___y_2943_;
v___y_2930_ = v___y_2945_;
v___y_2931_ = v___y_2947_;
v___y_2932_ = v___y_2946_;
v___y_2933_ = v___y_2948_;
v___y_2934_ = v___x_2951_;
goto v___jp_2927_;
}
else
{
v___y_2928_ = v___y_2944_;
v___y_2929_ = v___y_2943_;
v___y_2930_ = v___y_2945_;
v___y_2931_ = v___y_2947_;
v___y_2932_ = v___y_2946_;
v___y_2933_ = v___y_2948_;
v___y_2934_ = v___y_2942_;
goto v___jp_2927_;
}
}
v___jp_2952_:
{
uint64_t v___x_2960_; uint64_t v___x_2961_; uint8_t v___x_2962_; 
v___x_2960_ = 2ULL;
v___x_2961_ = lean_uint64_shift_right(v___y_2953_, v___x_2960_);
v___x_2962_ = lean_uint64_dec_eq(v___x_2961_, v___y_2958_);
if (v___x_2962_ == 0)
{
v___y_2940_ = v___y_2953_;
v___y_2941_ = v___x_2960_;
v___y_2942_ = v___y_2959_;
v___y_2943_ = v___y_2955_;
v___y_2944_ = v___y_2954_;
v___y_2945_ = v___y_2956_;
v___y_2946_ = v___y_2958_;
v___y_2947_ = v___y_2957_;
v___y_2948_ = v___x_2961_;
goto v___jp_2939_;
}
else
{
v___y_2940_ = v___y_2953_;
v___y_2941_ = v___x_2960_;
v___y_2942_ = v___y_2959_;
v___y_2943_ = v___y_2955_;
v___y_2944_ = v___y_2954_;
v___y_2945_ = v___y_2956_;
v___y_2946_ = v___y_2958_;
v___y_2947_ = v___y_2957_;
v___y_2948_ = v___y_2953_;
goto v___jp_2939_;
}
}
v___jp_2963_:
{
uint64_t v___x_2973_; uint8_t v___x_2974_; 
v___x_2973_ = lean_uint64_shift_right(v___y_2966_, v___y_2965_);
v___x_2974_ = lean_uint64_dec_eq(v___x_2973_, v___y_2970_);
if (v___x_2974_ == 0)
{
uint64_t v___x_2975_; 
v___x_2975_ = lean_uint64_add(v___y_2964_, v___y_2965_);
v___y_2953_ = v___y_2972_;
v___y_2954_ = v___y_2968_;
v___y_2955_ = v___y_2967_;
v___y_2956_ = v___y_2969_;
v___y_2957_ = v___y_2971_;
v___y_2958_ = v___y_2970_;
v___y_2959_ = v___x_2975_;
goto v___jp_2952_;
}
else
{
v___y_2953_ = v___y_2972_;
v___y_2954_ = v___y_2968_;
v___y_2955_ = v___y_2967_;
v___y_2956_ = v___y_2969_;
v___y_2957_ = v___y_2971_;
v___y_2958_ = v___y_2970_;
v___y_2959_ = v___y_2964_;
goto v___jp_2952_;
}
}
v___jp_2976_:
{
uint64_t v___x_2984_; uint64_t v___x_2985_; uint8_t v___x_2986_; 
v___x_2984_ = 4ULL;
v___x_2985_ = lean_uint64_shift_right(v___y_2979_, v___x_2984_);
v___x_2986_ = lean_uint64_dec_eq(v___x_2985_, v___y_2982_);
if (v___x_2986_ == 0)
{
v___y_2964_ = v___y_2983_;
v___y_2965_ = v___x_2984_;
v___y_2966_ = v___y_2979_;
v___y_2967_ = v___y_2978_;
v___y_2968_ = v___y_2977_;
v___y_2969_ = v___y_2980_;
v___y_2970_ = v___y_2982_;
v___y_2971_ = v___y_2981_;
v___y_2972_ = v___x_2985_;
goto v___jp_2963_;
}
else
{
v___y_2964_ = v___y_2983_;
v___y_2965_ = v___x_2984_;
v___y_2966_ = v___y_2979_;
v___y_2967_ = v___y_2978_;
v___y_2968_ = v___y_2977_;
v___y_2969_ = v___y_2980_;
v___y_2970_ = v___y_2982_;
v___y_2971_ = v___y_2981_;
v___y_2972_ = v___y_2979_;
goto v___jp_2963_;
}
}
v___jp_2987_:
{
uint64_t v___x_2997_; uint8_t v___x_2998_; 
v___x_2997_ = lean_uint64_shift_right(v___y_2992_, v___y_2988_);
v___x_2998_ = lean_uint64_dec_eq(v___x_2997_, v___y_2994_);
if (v___x_2998_ == 0)
{
uint64_t v___x_2999_; 
v___x_2999_ = lean_uint64_add(v___y_2989_, v___y_2988_);
v___y_2977_ = v___y_2991_;
v___y_2978_ = v___y_2990_;
v___y_2979_ = v___y_2996_;
v___y_2980_ = v___y_2993_;
v___y_2981_ = v___y_2995_;
v___y_2982_ = v___y_2994_;
v___y_2983_ = v___x_2999_;
goto v___jp_2976_;
}
else
{
v___y_2977_ = v___y_2991_;
v___y_2978_ = v___y_2990_;
v___y_2979_ = v___y_2996_;
v___y_2980_ = v___y_2993_;
v___y_2981_ = v___y_2995_;
v___y_2982_ = v___y_2994_;
v___y_2983_ = v___y_2989_;
goto v___jp_2976_;
}
}
v___jp_3000_:
{
uint64_t v___x_3008_; uint64_t v___x_3009_; uint8_t v___x_3010_; 
v___x_3008_ = 8ULL;
v___x_3009_ = lean_uint64_shift_right(v___y_3004_, v___x_3008_);
v___x_3010_ = lean_uint64_dec_eq(v___x_3009_, v___y_3006_);
if (v___x_3010_ == 0)
{
v___y_2988_ = v___x_3008_;
v___y_2989_ = v___y_3007_;
v___y_2990_ = v___y_3002_;
v___y_2991_ = v___y_3001_;
v___y_2992_ = v___y_3004_;
v___y_2993_ = v___y_3003_;
v___y_2994_ = v___y_3006_;
v___y_2995_ = v___y_3005_;
v___y_2996_ = v___x_3009_;
goto v___jp_2987_;
}
else
{
v___y_2988_ = v___x_3008_;
v___y_2989_ = v___y_3007_;
v___y_2990_ = v___y_3002_;
v___y_2991_ = v___y_3001_;
v___y_2992_ = v___y_3004_;
v___y_2993_ = v___y_3003_;
v___y_2994_ = v___y_3006_;
v___y_2995_ = v___y_3005_;
v___y_2996_ = v___y_3004_;
goto v___jp_2987_;
}
}
v___jp_3011_:
{
uint64_t v___x_3021_; uint8_t v___x_3022_; 
v___x_3021_ = lean_uint64_shift_right(v___y_3013_, v___y_3012_);
v___x_3022_ = lean_uint64_dec_eq(v___x_3021_, v___y_3018_);
if (v___x_3022_ == 0)
{
uint64_t v___x_3023_; 
v___x_3023_ = lean_uint64_add(v___y_3017_, v___y_3012_);
v___y_3001_ = v___y_3015_;
v___y_3002_ = v___y_3014_;
v___y_3003_ = v___y_3016_;
v___y_3004_ = v___y_3020_;
v___y_3005_ = v___y_3019_;
v___y_3006_ = v___y_3018_;
v___y_3007_ = v___x_3023_;
goto v___jp_3000_;
}
else
{
v___y_3001_ = v___y_3015_;
v___y_3002_ = v___y_3014_;
v___y_3003_ = v___y_3016_;
v___y_3004_ = v___y_3020_;
v___y_3005_ = v___y_3019_;
v___y_3006_ = v___y_3018_;
v___y_3007_ = v___y_3017_;
goto v___jp_3000_;
}
}
v___jp_3024_:
{
uint64_t v___x_3032_; uint64_t v___x_3033_; uint8_t v___x_3034_; 
v___x_3032_ = 16ULL;
v___x_3033_ = lean_uint64_shift_right(v___y_3027_, v___x_3032_);
v___x_3034_ = lean_uint64_dec_eq(v___x_3033_, v___y_3030_);
if (v___x_3034_ == 0)
{
v___y_3012_ = v___x_3032_;
v___y_3013_ = v___y_3027_;
v___y_3014_ = v___y_3026_;
v___y_3015_ = v___y_3025_;
v___y_3016_ = v___y_3028_;
v___y_3017_ = v___y_3031_;
v___y_3018_ = v___y_3030_;
v___y_3019_ = v___y_3029_;
v___y_3020_ = v___x_3033_;
goto v___jp_3011_;
}
else
{
v___y_3012_ = v___x_3032_;
v___y_3013_ = v___y_3027_;
v___y_3014_ = v___y_3026_;
v___y_3015_ = v___y_3025_;
v___y_3016_ = v___y_3028_;
v___y_3017_ = v___y_3031_;
v___y_3018_ = v___y_3030_;
v___y_3019_ = v___y_3029_;
v___y_3020_ = v___y_3027_;
goto v___jp_3011_;
}
}
v___jp_3035_:
{
uint64_t v___x_3043_; uint8_t v___x_3044_; 
v___x_3043_ = lean_uint64_shift_right(v___y_3041_, v___y_3039_);
v___x_3044_ = lean_uint64_dec_eq(v___x_3043_, v___y_3040_);
if (v___x_3044_ == 0)
{
v___y_3025_ = v___y_3037_;
v___y_3026_ = v___y_3036_;
v___y_3027_ = v___y_3042_;
v___y_3028_ = v___y_3038_;
v___y_3029_ = v___y_3041_;
v___y_3030_ = v___y_3040_;
v___y_3031_ = v___y_3039_;
goto v___jp_3024_;
}
else
{
v___y_3025_ = v___y_3037_;
v___y_3026_ = v___y_3036_;
v___y_3027_ = v___y_3042_;
v___y_3028_ = v___y_3038_;
v___y_3029_ = v___y_3041_;
v___y_3030_ = v___y_3040_;
v___y_3031_ = v___y_3040_;
goto v___jp_3024_;
}
}
v___jp_3045_:
{
uint64_t v___x_3050_; uint8_t v___x_3051_; 
v___x_3050_ = 0ULL;
v___x_3051_ = lean_uint64_dec_eq(v___y_3049_, v___x_3050_);
if (v___x_3051_ == 0)
{
uint64_t v___x_3052_; uint64_t v___x_3053_; uint8_t v___x_3054_; 
v___x_3052_ = 32ULL;
v___x_3053_ = lean_uint64_shift_right(v___y_3049_, v___x_3052_);
v___x_3054_ = lean_uint64_dec_eq(v___x_3053_, v___x_3050_);
if (v___x_3054_ == 0)
{
v___y_3036_ = v___y_3047_;
v___y_3037_ = v___y_3046_;
v___y_3038_ = v___y_3048_;
v___y_3039_ = v___x_3052_;
v___y_3040_ = v___x_3050_;
v___y_3041_ = v___y_3049_;
v___y_3042_ = v___x_3053_;
goto v___jp_3035_;
}
else
{
v___y_3036_ = v___y_3047_;
v___y_3037_ = v___y_3046_;
v___y_3038_ = v___y_3048_;
v___y_3039_ = v___x_3052_;
v___y_3040_ = v___x_3050_;
v___y_3041_ = v___y_3049_;
v___y_3042_ = v___y_3049_;
goto v___jp_3035_;
}
}
else
{
if (v___y_3047_ == 0)
{
uint32_t v___x_3055_; 
v___x_3055_ = 0;
return v___x_3055_;
}
else
{
uint32_t v___x_3056_; 
v___x_3056_ = 2147483648;
return v___x_3056_;
}
}
}
v___jp_3057_:
{
uint64_t v___x_3064_; uint64_t v___x_3065_; uint64_t v___x_3066_; uint8_t v___x_3067_; 
v___x_3064_ = lean_uint64_mul(v___y_3061_, v___y_3060_);
v___x_3065_ = lean_uint64_add(v___y_3059_, v___y_3063_);
v___x_3066_ = 281474976710656ULL;
v___x_3067_ = lean_uint64_dec_lt(v___x_3064_, v___x_3066_);
if (v___x_3067_ == 0)
{
v___y_3046_ = v___x_3065_;
v___y_3047_ = v___y_3058_;
v___y_3048_ = v___y_3062_;
v___y_3049_ = v___x_3064_;
goto v___jp_3045_;
}
else
{
uint64_t v___x_3068_; uint8_t v___x_3069_; 
v___x_3068_ = 123ULL;
v___x_3069_ = lean_uint64_dec_le(v___x_3065_, v___x_3068_);
if (v___x_3069_ == 0)
{
v___y_3046_ = v___x_3065_;
v___y_3047_ = v___y_3058_;
v___y_3048_ = v___y_3062_;
v___y_3049_ = v___x_3064_;
goto v___jp_3045_;
}
else
{
uint64_t v___x_3070_; uint8_t v___x_3071_; 
v___x_3070_ = 0ULL;
v___x_3071_ = lean_uint64_dec_eq(v___x_3064_, v___x_3070_);
if (v___x_3071_ == 0)
{
uint64_t v___x_3072_; uint64_t v___x_3073_; uint8_t v___x_3074_; 
v___x_3072_ = 149ULL;
v___x_3073_ = lean_uint64_sub(v___x_3072_, v___x_3065_);
v___x_3074_ = lean_uint64_dec_eq(v___x_3073_, v___x_3070_);
if (v___x_3074_ == 0)
{
uint64_t v___x_3075_; uint8_t v___x_3076_; 
v___x_3075_ = 64ULL;
v___x_3076_ = lean_uint64_dec_lt(v___x_3073_, v___x_3075_);
if (v___x_3076_ == 0)
{
uint8_t v___x_3077_; 
v___x_3077_ = lean_uint64_dec_eq(v___x_3073_, v___x_3075_);
if (v___x_3077_ == 0)
{
v___y_2194_ = v___y_3058_;
v___y_2195_ = v___x_3070_;
v___y_2196_ = v___y_3062_;
v___y_2197_ = v___x_3070_;
goto v___jp_2193_;
}
else
{
uint64_t v___x_3078_; uint8_t v___x_3079_; 
v___x_3078_ = 9223372036854775808ULL;
v___x_3079_ = lean_uint64_dec_lt(v___x_3078_, v___x_3064_);
if (v___x_3079_ == 0)
{
v___y_2194_ = v___y_3058_;
v___y_2195_ = v___x_3070_;
v___y_2196_ = v___y_3062_;
v___y_2197_ = v___x_3070_;
goto v___jp_2193_;
}
else
{
uint64_t v___x_3080_; 
v___x_3080_ = 1ULL;
v___y_2194_ = v___y_3058_;
v___y_2195_ = v___x_3070_;
v___y_2196_ = v___y_3062_;
v___y_2197_ = v___x_3080_;
goto v___jp_2193_;
}
}
}
else
{
uint64_t v_quotient_3081_; uint64_t v___x_3082_; uint64_t v___x_3083_; uint64_t v___x_3084_; uint64_t v_remainder_3085_; uint64_t v___x_3086_; uint64_t v_half_3087_; uint8_t v___x_3088_; 
v_quotient_3081_ = lean_uint64_shift_right(v___x_3064_, v___x_3073_);
v___x_3082_ = 1ULL;
v___x_3083_ = lean_uint64_shift_left(v___x_3082_, v___x_3073_);
v___x_3084_ = lean_uint64_sub(v___x_3083_, v___x_3082_);
v_remainder_3085_ = lean_uint64_land(v___x_3064_, v___x_3084_);
v___x_3086_ = lean_uint64_sub(v___x_3073_, v___x_3082_);
v_half_3087_ = lean_uint64_shift_left(v___x_3082_, v___x_3086_);
v___x_3088_ = lean_uint64_dec_lt(v_remainder_3085_, v_half_3087_);
if (v___x_3088_ == 0)
{
uint8_t v___x_3089_; 
v___x_3089_ = lean_uint64_dec_lt(v_half_3087_, v_remainder_3085_);
if (v___x_3089_ == 0)
{
uint64_t v___x_3090_; uint8_t v___x_3091_; 
v___x_3090_ = lean_uint64_land(v_quotient_3081_, v___x_3082_);
v___x_3091_ = lean_uint64_dec_eq(v___x_3090_, v___x_3070_);
if (v___x_3091_ == 0)
{
uint64_t v___x_3092_; 
v___x_3092_ = lean_uint64_add(v_quotient_3081_, v___x_3082_);
v___y_2194_ = v___y_3058_;
v___y_2195_ = v___x_3070_;
v___y_2196_ = v___y_3062_;
v___y_2197_ = v___x_3092_;
goto v___jp_2193_;
}
else
{
v___y_2194_ = v___y_3058_;
v___y_2195_ = v___x_3070_;
v___y_2196_ = v___y_3062_;
v___y_2197_ = v_quotient_3081_;
goto v___jp_2193_;
}
}
else
{
uint64_t v___x_3093_; 
v___x_3093_ = lean_uint64_add(v_quotient_3081_, v___x_3082_);
v___y_2194_ = v___y_3058_;
v___y_2195_ = v___x_3070_;
v___y_2196_ = v___y_3062_;
v___y_2197_ = v___x_3093_;
goto v___jp_2193_;
}
}
else
{
v___y_2194_ = v___y_3058_;
v___y_2195_ = v___x_3070_;
v___y_2196_ = v___y_3062_;
v___y_2197_ = v_quotient_3081_;
goto v___jp_2193_;
}
}
}
else
{
v___y_2194_ = v___y_3058_;
v___y_2195_ = v___x_3070_;
v___y_2196_ = v___y_3062_;
v___y_2197_ = v___x_3064_;
goto v___jp_2193_;
}
}
else
{
if (v___y_3058_ == 0)
{
uint32_t v___x_3094_; 
v___x_3094_ = 0;
return v___x_3094_;
}
else
{
uint32_t v___x_3095_; 
v___x_3095_ = 2147483648;
return v___x_3095_;
}
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___x_3400_, lean_object* v___y_3401_, lean_object* v___y_3402_){
_start:
{
uint8_t v___x_8376__boxed_3403_; uint32_t v___y_8377__boxed_3404_; uint32_t v___y_8378__boxed_3405_; uint32_t v_res_3406_; lean_object* v_r_3407_; 
v___x_8376__boxed_3403_ = lean_unbox(v___x_3400_);
v___y_8377__boxed_3404_ = lean_unbox_uint32(v___y_3401_);
lean_dec(v___y_3401_);
v___y_8378__boxed_3405_ = lean_unbox_uint32(v___y_3402_);
lean_dec(v___y_3402_);
v_res_3406_ = lp_competition_main___lam__1(v___x_8376__boxed_3403_, v___y_8377__boxed_3404_, v___y_8378__boxed_3405_);
v_r_3407_ = lean_box_uint32(v_res_3406_);
return v_r_3407_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint8_t v___x_3408_, uint32_t v___y_3409_, uint32_t v___y_3410_){
_start:
{
uint8_t v___y_3412_; uint8_t v___y_3428_; uint8_t v___y_3442_; uint8_t v___y_3459_; float v___y_3466_; float v___y_3467_; float v___y_3481_; uint8_t v___y_3482_; float v___y_3497_; uint32_t v___y_3507_; uint32_t v___y_3511_; uint32_t v___y_3515_; uint32_t v___y_3516_; uint32_t v___y_3517_; uint8_t v___y_3521_; uint32_t v___y_3522_; uint64_t v___y_3523_; uint64_t v___y_3524_; uint32_t v___y_3536_; uint32_t v___y_3537_; uint32_t v___y_3538_; uint8_t v___y_3542_; uint32_t v___y_3543_; uint64_t v___y_3544_; uint64_t v___y_3545_; uint32_t v___x_3556_; uint32_t v___x_3557_; uint8_t v___y_3559_; uint32_t v___x_3571_; uint32_t v___y_3573_; uint32_t v___y_3574_; uint32_t v___y_3575_; uint32_t v___y_3576_; uint8_t v___y_3583_; uint32_t v___y_3584_; uint32_t v___y_3585_; uint32_t v___y_3586_; uint8_t v___y_3590_; uint64_t v___y_3591_; uint32_t v___y_3592_; uint64_t v___y_3593_; uint64_t v___y_3594_; uint8_t v___y_3604_; uint32_t v___y_3605_; uint64_t v___y_3606_; uint64_t v___y_3607_; uint8_t v___y_3608_; uint64_t v___y_3609_; uint64_t v___y_3616_; uint8_t v___y_3617_; uint64_t v___y_3618_; uint32_t v___y_3619_; uint64_t v___y_3620_; uint8_t v___y_3626_; uint64_t v___y_3627_; uint64_t v___y_3628_; uint32_t v___y_3629_; uint64_t v___y_3630_; uint64_t v___y_3631_; uint8_t v___y_3686_; uint64_t v___y_3687_; uint64_t v___y_3688_; uint32_t v___y_3689_; uint64_t v___y_3690_; uint64_t v___y_3691_; uint64_t v___y_3692_; uint8_t v___y_3698_; uint64_t v___y_3699_; uint64_t v___y_3700_; uint64_t v___y_3701_; uint64_t v___y_3702_; uint32_t v___y_3703_; uint64_t v___y_3704_; uint64_t v___y_3705_; uint64_t v___y_3706_; uint8_t v___y_3711_; uint64_t v___y_3712_; uint64_t v___y_3713_; uint64_t v___y_3714_; uint32_t v___y_3715_; uint64_t v___y_3716_; uint64_t v___y_3717_; uint8_t v___y_3722_; uint64_t v___y_3723_; uint64_t v___y_3724_; uint64_t v___y_3725_; uint64_t v___y_3726_; uint64_t v___y_3727_; uint32_t v___y_3728_; uint64_t v___y_3729_; uint64_t v___y_3730_; uint8_t v___y_3735_; uint64_t v___y_3736_; uint64_t v___y_3737_; uint32_t v___y_3738_; uint64_t v___y_3739_; uint64_t v___y_3740_; uint64_t v___y_3741_; uint64_t v___y_3746_; uint8_t v___y_3747_; uint64_t v___y_3748_; uint64_t v___y_3749_; uint64_t v___y_3750_; uint64_t v___y_3751_; uint32_t v___y_3752_; uint64_t v___y_3753_; uint64_t v___y_3754_; uint8_t v___y_3759_; uint64_t v___y_3760_; uint64_t v___y_3761_; uint32_t v___y_3762_; uint64_t v___y_3763_; uint64_t v___y_3764_; uint64_t v___y_3765_; uint8_t v___y_3770_; uint64_t v___y_3771_; uint64_t v___y_3772_; uint64_t v___y_3773_; uint64_t v___y_3774_; uint64_t v___y_3775_; uint32_t v___y_3776_; uint64_t v___y_3777_; uint64_t v___y_3778_; uint8_t v___y_3783_; uint64_t v___y_3784_; uint64_t v___y_3785_; uint64_t v___y_3786_; uint32_t v___y_3787_; uint64_t v___y_3788_; uint64_t v___y_3789_; uint8_t v___y_3794_; uint64_t v___y_3795_; uint64_t v___y_3796_; uint64_t v___y_3797_; uint32_t v___y_3798_; uint64_t v___y_3799_; uint64_t v___y_3800_; uint8_t v___y_3804_; uint64_t v___y_3805_; uint64_t v___y_3806_; uint32_t v___y_3807_; uint8_t v___y_3816_; uint64_t v___y_3817_; uint64_t v___y_3818_; uint32_t v___y_3819_; uint64_t v___y_3820_; uint64_t v___y_3821_; uint32_t v_ex_3854_; uint32_t v___x_3855_; uint32_t v_ey_3856_; uint8_t v___y_3858_; uint64_t v___y_3859_; uint32_t v___y_3860_; uint64_t v___y_3861_; uint64_t v___y_3862_; uint8_t v___y_3869_; uint32_t v___y_3870_; uint64_t v___y_3871_; uint64_t v___y_3872_; uint8_t v___y_3879_; uint32_t v___y_3880_; uint32_t v___y_3881_; uint64_t v___y_3882_; uint8_t v___y_3890_; uint8_t v___y_3901_; uint8_t v___y_3902_; uint32_t v___x_3903_; uint32_t v___x_3904_; uint8_t v___x_3905_; uint8_t v___y_3907_; uint8_t v___y_3908_; uint8_t v___y_3909_; uint8_t v___y_3911_; uint8_t v___y_3912_; uint8_t v___y_3918_; 
v___x_3556_ = 23;
v___x_3557_ = lean_uint32_shift_right(v___y_3409_, v___x_3556_);
v___x_3571_ = 255;
v_ex_3854_ = lean_uint32_land(v___x_3557_, v___x_3571_);
v___x_3855_ = lean_uint32_shift_right(v___y_3410_, v___x_3556_);
v_ey_3856_ = lean_uint32_land(v___x_3855_, v___x_3571_);
v___x_3903_ = lean_uint32_add(v_ex_3854_, v_ey_3856_);
v___x_3904_ = 128;
v___x_3905_ = lean_uint32_dec_lt(v___x_3903_, v___x_3904_);
if (v___x_3905_ == 0)
{
uint32_t v___x_3927_; uint32_t v_a_3928_; uint32_t v___x_3929_; uint32_t v___x_3930_; uint32_t v___x_3931_; uint8_t v___x_3932_; 
v___x_3927_ = 2147483647;
v_a_3928_ = lean_uint32_land(v___y_3409_, v___x_3927_);
v___x_3929_ = 201326591;
v___x_3930_ = 1;
v___x_3931_ = lean_uint32_sub(v_a_3928_, v___x_3930_);
v___x_3932_ = lean_uint32_dec_le(v___x_3929_, v___x_3931_);
if (v___x_3932_ == 0)
{
v___y_3559_ = v___x_3932_;
goto v___jp_3558_;
}
else
{
uint32_t v___x_3933_; uint8_t v___x_3934_; 
v___x_3933_ = 2139095040;
v___x_3934_ = lean_uint32_dec_lt(v_a_3928_, v___x_3933_);
v___y_3559_ = v___x_3934_;
goto v___jp_3558_;
}
}
else
{
uint32_t v___x_3935_; uint32_t v___x_3936_; uint32_t v___x_3937_; uint8_t v___x_3938_; 
v___x_3935_ = 4278190080;
v___x_3936_ = 1;
v___x_3937_ = lean_uint32_shift_left(v___y_3409_, v___x_3936_);
v___x_3938_ = lean_uint32_dec_le(v___x_3935_, v___x_3937_);
if (v___x_3938_ == 0)
{
uint32_t v___x_3939_; uint8_t v___x_3940_; 
v___x_3939_ = lean_uint32_shift_left(v___y_3410_, v___x_3936_);
v___x_3940_ = lean_uint32_dec_le(v___x_3935_, v___x_3939_);
v___y_3918_ = v___x_3940_;
goto v___jp_3917_;
}
else
{
v___y_3918_ = v___x_3938_;
goto v___jp_3917_;
}
}
v___jp_3411_:
{
if (v___y_3412_ == 0)
{
uint32_t v___x_3413_; 
v___x_3413_ = lp_competition_Submission_FastMul_mul(v___y_3409_, v___y_3410_);
return v___x_3413_;
}
else
{
uint32_t v___x_3414_; uint32_t v___x_3415_; 
v___x_3414_ = 4194304;
v___x_3415_ = lean_uint32_lor(v___y_3410_, v___x_3414_);
return v___x_3415_;
}
}
v___jp_3416_:
{
uint32_t v___x_3417_; uint32_t v___x_3418_; uint32_t v___x_3419_; uint32_t v___x_3420_; uint8_t v___x_3421_; 
v___x_3417_ = 23;
v___x_3418_ = lean_uint32_shift_right(v___y_3410_, v___x_3417_);
v___x_3419_ = 255;
v___x_3420_ = lean_uint32_land(v___x_3418_, v___x_3419_);
v___x_3421_ = lean_uint32_dec_eq(v___x_3420_, v___x_3419_);
if (v___x_3421_ == 0)
{
v___y_3412_ = v___x_3421_;
goto v___jp_3411_;
}
else
{
uint32_t v___x_3422_; uint32_t v___x_3423_; uint32_t v___x_3424_; uint8_t v___x_3425_; 
v___x_3422_ = 8388607;
v___x_3423_ = lean_uint32_land(v___y_3410_, v___x_3422_);
v___x_3424_ = 0;
v___x_3425_ = lean_uint32_dec_eq(v___x_3423_, v___x_3424_);
if (v___x_3425_ == 0)
{
v___y_3412_ = v___x_3421_;
goto v___jp_3411_;
}
else
{
uint32_t v___x_3426_; 
v___x_3426_ = lp_competition_Submission_FastMul_mul(v___y_3409_, v___y_3410_);
return v___x_3426_;
}
}
}
v___jp_3427_:
{
if (v___y_3428_ == 0)
{
goto v___jp_3416_;
}
else
{
uint32_t v___x_3429_; uint32_t v___x_3430_; 
v___x_3429_ = 4194304;
v___x_3430_ = lean_uint32_lor(v___y_3409_, v___x_3429_);
return v___x_3430_;
}
}
v___jp_3431_:
{
uint32_t v___x_3432_; uint32_t v___x_3433_; uint32_t v___x_3434_; uint32_t v___x_3435_; uint8_t v___x_3436_; 
v___x_3432_ = 23;
v___x_3433_ = lean_uint32_shift_right(v___y_3409_, v___x_3432_);
v___x_3434_ = 255;
v___x_3435_ = lean_uint32_land(v___x_3433_, v___x_3434_);
v___x_3436_ = lean_uint32_dec_eq(v___x_3435_, v___x_3434_);
if (v___x_3436_ == 0)
{
v___y_3428_ = v___x_3436_;
goto v___jp_3427_;
}
else
{
uint32_t v___x_3437_; uint32_t v___x_3438_; uint32_t v___x_3439_; uint8_t v___x_3440_; 
v___x_3437_ = 8388607;
v___x_3438_ = lean_uint32_land(v___y_3409_, v___x_3437_);
v___x_3439_ = 0;
v___x_3440_ = lean_uint32_dec_eq(v___x_3438_, v___x_3439_);
if (v___x_3440_ == 0)
{
v___y_3428_ = v___x_3436_;
goto v___jp_3427_;
}
else
{
goto v___jp_3416_;
}
}
}
v___jp_3441_:
{
if (v___y_3442_ == 0)
{
goto v___jp_3431_;
}
else
{
uint32_t v___x_3443_; uint32_t v___x_3444_; uint32_t v___x_3445_; uint8_t v___x_3446_; 
v___x_3443_ = 4194304;
v___x_3444_ = lean_uint32_land(v___y_3410_, v___x_3443_);
v___x_3445_ = 0;
v___x_3446_ = lean_uint32_dec_eq(v___x_3444_, v___x_3445_);
if (v___x_3446_ == 0)
{
goto v___jp_3431_;
}
else
{
uint32_t v___x_3447_; 
v___x_3447_ = lean_uint32_lor(v___y_3410_, v___x_3443_);
return v___x_3447_;
}
}
}
v___jp_3448_:
{
uint32_t v___x_3449_; uint32_t v___x_3450_; uint32_t v___x_3451_; uint32_t v___x_3452_; uint8_t v___x_3453_; 
v___x_3449_ = 23;
v___x_3450_ = lean_uint32_shift_right(v___y_3410_, v___x_3449_);
v___x_3451_ = 255;
v___x_3452_ = lean_uint32_land(v___x_3450_, v___x_3451_);
v___x_3453_ = lean_uint32_dec_eq(v___x_3452_, v___x_3451_);
if (v___x_3453_ == 0)
{
v___y_3442_ = v___x_3453_;
goto v___jp_3441_;
}
else
{
uint32_t v___x_3454_; uint32_t v___x_3455_; uint32_t v___x_3456_; uint8_t v___x_3457_; 
v___x_3454_ = 8388607;
v___x_3455_ = lean_uint32_land(v___y_3410_, v___x_3454_);
v___x_3456_ = 0;
v___x_3457_ = lean_uint32_dec_eq(v___x_3455_, v___x_3456_);
if (v___x_3457_ == 0)
{
v___y_3442_ = v___x_3453_;
goto v___jp_3441_;
}
else
{
goto v___jp_3431_;
}
}
}
v___jp_3458_:
{
if (v___y_3459_ == 0)
{
goto v___jp_3448_;
}
else
{
uint32_t v___x_3460_; uint32_t v___x_3461_; uint32_t v___x_3462_; uint8_t v___x_3463_; 
v___x_3460_ = 4194304;
v___x_3461_ = lean_uint32_land(v___y_3409_, v___x_3460_);
v___x_3462_ = 0;
v___x_3463_ = lean_uint32_dec_eq(v___x_3461_, v___x_3462_);
if (v___x_3463_ == 0)
{
goto v___jp_3448_;
}
else
{
uint32_t v___x_3464_; 
v___x_3464_ = lean_uint32_lor(v___y_3409_, v___x_3460_);
return v___x_3464_;
}
}
}
v___jp_3465_:
{
float v_result_3468_; uint8_t v___x_3469_; 
v_result_3468_ = lean_float32_mul(v___y_3466_, v___y_3467_);
v___x_3469_ = lean_float32_beq(v_result_3468_, v_result_3468_);
if (v___x_3469_ == 0)
{
uint32_t v___x_3470_; uint32_t v___x_3471_; uint32_t v___x_3472_; uint32_t v___x_3473_; uint8_t v___x_3474_; 
v___x_3470_ = 23;
v___x_3471_ = lean_uint32_shift_right(v___y_3409_, v___x_3470_);
v___x_3472_ = 255;
v___x_3473_ = lean_uint32_land(v___x_3471_, v___x_3472_);
v___x_3474_ = lean_uint32_dec_eq(v___x_3473_, v___x_3472_);
if (v___x_3474_ == 0)
{
v___y_3459_ = v___x_3474_;
goto v___jp_3458_;
}
else
{
uint32_t v___x_3475_; uint32_t v___x_3476_; uint32_t v___x_3477_; uint8_t v___x_3478_; 
v___x_3475_ = 8388607;
v___x_3476_ = lean_uint32_land(v___y_3409_, v___x_3475_);
v___x_3477_ = 0;
v___x_3478_ = lean_uint32_dec_eq(v___x_3476_, v___x_3477_);
if (v___x_3478_ == 0)
{
v___y_3459_ = v___x_3474_;
goto v___jp_3458_;
}
else
{
goto v___jp_3448_;
}
}
}
else
{
uint32_t v___x_3479_; 
v___x_3479_ = lean_float32_to_bits(v_result_3468_);
return v___x_3479_;
}
}
v___jp_3480_:
{
if (v___y_3482_ == 0)
{
float v___x_3483_; 
v___x_3483_ = lean_float32_of_bits(v___y_3410_);
v___y_3466_ = v___y_3481_;
v___y_3467_ = v___x_3483_;
goto v___jp_3465_;
}
else
{
uint32_t v___x_3484_; uint32_t v___x_3485_; uint32_t v___x_3486_; uint32_t v___x_3487_; float v___x_3488_; lean_object* v___x_3489_; uint32_t v___x_3490_; uint32_t v___x_3491_; lean_object* v___x_3492_; lean_object* v___x_3493_; float v___x_3494_; float v___x_3495_; 
v___x_3484_ = 8388607;
v___x_3485_ = lean_uint32_land(v___y_3410_, v___x_3484_);
v___x_3486_ = 8388608;
v___x_3487_ = lean_uint32_lor(v___x_3485_, v___x_3486_);
v___x_3488_ = lean_uint32_to_float32(v___x_3487_);
v___x_3489_ = lp_competition_R2W01b_scaleTable;
v___x_3490_ = 23;
v___x_3491_ = lean_uint32_shift_right(v___y_3410_, v___x_3490_);
v___x_3492_ = lean_uint32_to_nat(v___x_3491_);
v___x_3493_ = lean_array_fget_borrowed(v___x_3489_, v___x_3492_);
lean_dec(v___x_3492_);
v___x_3494_ = lean_unbox_float32(v___x_3493_);
v___x_3495_ = lean_float32_mul(v___x_3488_, v___x_3494_);
v___y_3466_ = v___y_3481_;
v___y_3467_ = v___x_3495_;
goto v___jp_3465_;
}
}
v___jp_3496_:
{
uint32_t v___x_3498_; uint32_t v_a_3499_; uint32_t v___x_3500_; uint32_t v___x_3501_; uint32_t v___x_3502_; uint8_t v___x_3503_; 
v___x_3498_ = 2147483647;
v_a_3499_ = lean_uint32_land(v___y_3410_, v___x_3498_);
v___x_3500_ = 201326591;
v___x_3501_ = 1;
v___x_3502_ = lean_uint32_sub(v_a_3499_, v___x_3501_);
v___x_3503_ = lean_uint32_dec_le(v___x_3500_, v___x_3502_);
if (v___x_3503_ == 0)
{
v___y_3481_ = v___y_3497_;
v___y_3482_ = v___x_3503_;
goto v___jp_3480_;
}
else
{
uint32_t v___x_3504_; uint8_t v___x_3505_; 
v___x_3504_ = 2139095040;
v___x_3505_ = lean_uint32_dec_lt(v_a_3499_, v___x_3504_);
v___y_3481_ = v___y_3497_;
v___y_3482_ = v___x_3505_;
goto v___jp_3480_;
}
}
v___jp_3506_:
{
uint32_t v___x_3508_; uint32_t v___x_3509_; 
v___x_3508_ = 8388608;
v___x_3509_ = lean_uint32_lor(v___y_3507_, v___x_3508_);
return v___x_3509_;
}
v___jp_3510_:
{
uint32_t v___x_3512_; uint32_t v___x_3513_; 
v___x_3512_ = 8388608;
v___x_3513_ = lean_uint32_lor(v___y_3511_, v___x_3512_);
return v___x_3513_;
}
v___jp_3514_:
{
uint32_t v___x_3518_; uint32_t v___x_3519_; 
v___x_3518_ = lean_uint32_land(v___y_3516_, v___y_3515_);
v___x_3519_ = lean_uint32_lor(v___y_3517_, v___x_3518_);
return v___x_3519_;
}
v___jp_3520_:
{
uint8_t v___x_3525_; 
v___x_3525_ = lean_uint64_dec_eq(v___y_3524_, v___y_3523_);
if (v___x_3525_ == 0)
{
uint64_t v___x_3526_; uint8_t v___x_3527_; 
v___x_3526_ = 8388608ULL;
v___x_3527_ = lean_uint64_dec_eq(v___y_3524_, v___x_3526_);
if (v___x_3527_ == 0)
{
uint32_t v___x_3528_; 
v___x_3528_ = lean_uint64_to_uint32(v___y_3524_);
if (v___y_3521_ == 0)
{
uint32_t v___x_3529_; 
v___x_3529_ = 0;
v___y_3515_ = v___y_3522_;
v___y_3516_ = v___x_3528_;
v___y_3517_ = v___x_3529_;
goto v___jp_3514_;
}
else
{
uint32_t v___x_3530_; 
v___x_3530_ = 2147483648;
v___y_3515_ = v___y_3522_;
v___y_3516_ = v___x_3528_;
v___y_3517_ = v___x_3530_;
goto v___jp_3514_;
}
}
else
{
if (v___y_3521_ == 0)
{
uint32_t v___x_3531_; 
v___x_3531_ = 0;
v___y_3511_ = v___x_3531_;
goto v___jp_3510_;
}
else
{
uint32_t v___x_3532_; 
v___x_3532_ = 2147483648;
v___y_3511_ = v___x_3532_;
goto v___jp_3510_;
}
}
}
else
{
if (v___y_3521_ == 0)
{
uint32_t v___x_3533_; 
v___x_3533_ = 0;
return v___x_3533_;
}
else
{
uint32_t v___x_3534_; 
v___x_3534_ = 2147483648;
return v___x_3534_;
}
}
}
v___jp_3535_:
{
uint32_t v___x_3539_; uint32_t v___x_3540_; 
v___x_3539_ = lean_uint32_land(v___y_3536_, v___y_3537_);
v___x_3540_ = lean_uint32_lor(v___y_3538_, v___x_3539_);
return v___x_3540_;
}
v___jp_3541_:
{
uint8_t v___x_3546_; 
v___x_3546_ = lean_uint64_dec_eq(v___y_3545_, v___y_3544_);
if (v___x_3546_ == 0)
{
uint64_t v___x_3547_; uint8_t v___x_3548_; 
v___x_3547_ = 8388608ULL;
v___x_3548_ = lean_uint64_dec_eq(v___y_3545_, v___x_3547_);
if (v___x_3548_ == 0)
{
uint32_t v___x_3549_; 
v___x_3549_ = lean_uint64_to_uint32(v___y_3545_);
if (v___y_3542_ == 0)
{
uint32_t v___x_3550_; 
v___x_3550_ = 0;
v___y_3536_ = v___x_3549_;
v___y_3537_ = v___y_3543_;
v___y_3538_ = v___x_3550_;
goto v___jp_3535_;
}
else
{
uint32_t v___x_3551_; 
v___x_3551_ = 2147483648;
v___y_3536_ = v___x_3549_;
v___y_3537_ = v___y_3543_;
v___y_3538_ = v___x_3551_;
goto v___jp_3535_;
}
}
else
{
if (v___y_3542_ == 0)
{
uint32_t v___x_3552_; 
v___x_3552_ = 0;
v___y_3507_ = v___x_3552_;
goto v___jp_3506_;
}
else
{
uint32_t v___x_3553_; 
v___x_3553_ = 2147483648;
v___y_3507_ = v___x_3553_;
goto v___jp_3506_;
}
}
}
else
{
if (v___y_3542_ == 0)
{
uint32_t v___x_3554_; 
v___x_3554_ = 0;
return v___x_3554_;
}
else
{
uint32_t v___x_3555_; 
v___x_3555_ = 2147483648;
return v___x_3555_;
}
}
}
v___jp_3558_:
{
if (v___y_3559_ == 0)
{
float v___x_3560_; 
v___x_3560_ = lean_float32_of_bits(v___y_3409_);
v___y_3497_ = v___x_3560_;
goto v___jp_3496_;
}
else
{
uint32_t v___x_3561_; uint32_t v___x_3562_; uint32_t v___x_3563_; uint32_t v___x_3564_; float v___x_3565_; lean_object* v___x_3566_; lean_object* v___x_3567_; lean_object* v___x_3568_; float v___x_3569_; float v___x_3570_; 
v___x_3561_ = 8388607;
v___x_3562_ = lean_uint32_land(v___y_3409_, v___x_3561_);
v___x_3563_ = 8388608;
v___x_3564_ = lean_uint32_lor(v___x_3562_, v___x_3563_);
v___x_3565_ = lean_uint32_to_float32(v___x_3564_);
v___x_3566_ = lp_competition_R2W01b_scaleTable;
v___x_3567_ = lean_uint32_to_nat(v___x_3557_);
v___x_3568_ = lean_array_fget_borrowed(v___x_3566_, v___x_3567_);
lean_dec(v___x_3567_);
v___x_3569_ = lean_unbox_float32(v___x_3568_);
v___x_3570_ = lean_float32_mul(v___x_3565_, v___x_3569_);
v___y_3497_ = v___x_3570_;
goto v___jp_3496_;
}
}
v___jp_3572_:
{
uint32_t v___x_3577_; uint32_t v___x_3578_; uint32_t v___x_3579_; uint32_t v___x_3580_; uint32_t v___x_3581_; 
v___x_3577_ = lean_uint32_land(v___y_3575_, v___x_3571_);
v___x_3578_ = lean_uint32_shift_left(v___x_3577_, v___x_3556_);
v___x_3579_ = lean_uint32_lor(v___y_3576_, v___x_3578_);
v___x_3580_ = lean_uint32_land(v___y_3574_, v___y_3573_);
v___x_3581_ = lean_uint32_lor(v___x_3579_, v___x_3580_);
return v___x_3581_;
}
v___jp_3582_:
{
if (v___y_3583_ == 0)
{
uint32_t v___x_3587_; 
v___x_3587_ = 0;
v___y_3573_ = v___y_3584_;
v___y_3574_ = v___y_3586_;
v___y_3575_ = v___y_3585_;
v___y_3576_ = v___x_3587_;
goto v___jp_3572_;
}
else
{
uint32_t v___x_3588_; 
v___x_3588_ = 2147483648;
v___y_3573_ = v___y_3584_;
v___y_3574_ = v___y_3586_;
v___y_3575_ = v___y_3585_;
v___y_3576_ = v___x_3588_;
goto v___jp_3572_;
}
}
v___jp_3589_:
{
uint64_t v___x_3595_; uint64_t v_encodedExponent_3596_; uint32_t v___x_3597_; uint64_t v___x_3598_; uint8_t v___x_3599_; 
v___x_3595_ = 171ULL;
v_encodedExponent_3596_ = lean_uint64_sub(v___y_3593_, v___x_3595_);
v___x_3597_ = lean_uint64_to_uint32(v_encodedExponent_3596_);
v___x_3598_ = 8388608ULL;
v___x_3599_ = lean_uint64_dec_lt(v___y_3594_, v___x_3598_);
if (v___x_3599_ == 0)
{
uint64_t v___x_3600_; uint32_t v___x_3601_; 
v___x_3600_ = lean_uint64_sub(v___y_3594_, v___x_3598_);
v___x_3601_ = lean_uint64_to_uint32(v___x_3600_);
v___y_3583_ = v___y_3590_;
v___y_3584_ = v___y_3592_;
v___y_3585_ = v___x_3597_;
v___y_3586_ = v___x_3601_;
goto v___jp_3582_;
}
else
{
uint32_t v___x_3602_; 
v___x_3602_ = lean_uint64_to_uint32(v___y_3591_);
v___y_3583_ = v___y_3590_;
v___y_3584_ = v___y_3592_;
v___y_3585_ = v___x_3597_;
v___y_3586_ = v___x_3602_;
goto v___jp_3582_;
}
}
v___jp_3603_:
{
uint64_t v___x_3610_; uint8_t v___x_3611_; 
v___x_3610_ = 425ULL;
v___x_3611_ = lean_uint64_dec_lt(v___x_3610_, v___y_3609_);
if (v___x_3611_ == 0)
{
if (v___y_3608_ == 0)
{
v___y_3590_ = v___y_3604_;
v___y_3591_ = v___y_3606_;
v___y_3592_ = v___y_3605_;
v___y_3593_ = v___y_3609_;
v___y_3594_ = v___y_3607_;
goto v___jp_3589_;
}
else
{
uint64_t v___x_3612_; 
v___x_3612_ = 8388608ULL;
v___y_3590_ = v___y_3604_;
v___y_3591_ = v___y_3606_;
v___y_3592_ = v___y_3605_;
v___y_3593_ = v___y_3609_;
v___y_3594_ = v___x_3612_;
goto v___jp_3589_;
}
}
else
{
if (v___y_3604_ == 0)
{
uint32_t v___x_3613_; 
v___x_3613_ = 2139095040;
return v___x_3613_;
}
else
{
uint32_t v___x_3614_; 
v___x_3614_ = 4286578688;
return v___x_3614_;
}
}
}
v___jp_3615_:
{
uint64_t v___x_3621_; uint8_t v_carry_3622_; 
v___x_3621_ = 16777216ULL;
v_carry_3622_ = lean_uint64_dec_eq(v___y_3620_, v___x_3621_);
if (v_carry_3622_ == 0)
{
v___y_3604_ = v___y_3617_;
v___y_3605_ = v___y_3619_;
v___y_3606_ = v___y_3618_;
v___y_3607_ = v___y_3620_;
v___y_3608_ = v_carry_3622_;
v___y_3609_ = v___y_3616_;
goto v___jp_3603_;
}
else
{
uint64_t v___x_3623_; uint64_t v___x_3624_; 
v___x_3623_ = 1ULL;
v___x_3624_ = lean_uint64_add(v___y_3616_, v___x_3623_);
v___y_3604_ = v___y_3617_;
v___y_3605_ = v___y_3619_;
v___y_3606_ = v___y_3618_;
v___y_3607_ = v___y_3620_;
v___y_3608_ = v_carry_3622_;
v___y_3609_ = v___x_3624_;
goto v___jp_3603_;
}
}
v___jp_3625_:
{
uint64_t v_position_3632_; uint64_t v___x_3633_; uint8_t v___x_3634_; 
v_position_3632_ = lean_uint64_add(v___y_3631_, v___y_3628_);
v___x_3633_ = 172ULL;
v___x_3634_ = lean_uint64_dec_lt(v_position_3632_, v___x_3633_);
if (v___x_3634_ == 0)
{
uint64_t v___x_3635_; uint8_t v___x_3636_; 
v___x_3635_ = 23ULL;
v___x_3636_ = lean_uint64_dec_lt(v___y_3631_, v___x_3635_);
if (v___x_3636_ == 0)
{
uint64_t v___x_3637_; uint8_t v___x_3638_; 
v___x_3637_ = lean_uint64_sub(v___y_3631_, v___x_3635_);
v___x_3638_ = lean_uint64_dec_eq(v___x_3637_, v___y_3630_);
if (v___x_3638_ == 0)
{
uint64_t v___x_3639_; uint8_t v___x_3640_; 
v___x_3639_ = 64ULL;
v___x_3640_ = lean_uint64_dec_lt(v___x_3637_, v___x_3639_);
if (v___x_3640_ == 0)
{
uint8_t v___x_3641_; 
v___x_3641_ = lean_uint64_dec_eq(v___x_3637_, v___x_3639_);
if (v___x_3641_ == 0)
{
v___y_3616_ = v_position_3632_;
v___y_3617_ = v___y_3626_;
v___y_3618_ = v___y_3630_;
v___y_3619_ = v___y_3629_;
v___y_3620_ = v___y_3630_;
goto v___jp_3615_;
}
else
{
uint64_t v___x_3642_; uint8_t v___x_3643_; 
v___x_3642_ = 9223372036854775808ULL;
v___x_3643_ = lean_uint64_dec_lt(v___x_3642_, v___y_3627_);
if (v___x_3643_ == 0)
{
v___y_3616_ = v_position_3632_;
v___y_3617_ = v___y_3626_;
v___y_3618_ = v___y_3630_;
v___y_3619_ = v___y_3629_;
v___y_3620_ = v___y_3630_;
goto v___jp_3615_;
}
else
{
uint64_t v___x_3644_; 
v___x_3644_ = 1ULL;
v___y_3616_ = v_position_3632_;
v___y_3617_ = v___y_3626_;
v___y_3618_ = v___y_3630_;
v___y_3619_ = v___y_3629_;
v___y_3620_ = v___x_3644_;
goto v___jp_3615_;
}
}
}
else
{
uint64_t v_quotient_3645_; uint64_t v___x_3646_; uint64_t v___x_3647_; uint64_t v___x_3648_; uint64_t v_remainder_3649_; uint64_t v___x_3650_; uint64_t v_half_3651_; uint8_t v___x_3652_; 
v_quotient_3645_ = lean_uint64_shift_right(v___y_3627_, v___x_3637_);
v___x_3646_ = 1ULL;
v___x_3647_ = lean_uint64_shift_left(v___x_3646_, v___x_3637_);
v___x_3648_ = lean_uint64_sub(v___x_3647_, v___x_3646_);
v_remainder_3649_ = lean_uint64_land(v___y_3627_, v___x_3648_);
v___x_3650_ = lean_uint64_sub(v___x_3637_, v___x_3646_);
v_half_3651_ = lean_uint64_shift_left(v___x_3646_, v___x_3650_);
v___x_3652_ = lean_uint64_dec_lt(v_remainder_3649_, v_half_3651_);
if (v___x_3652_ == 0)
{
uint8_t v___x_3653_; 
v___x_3653_ = lean_uint64_dec_lt(v_half_3651_, v_remainder_3649_);
if (v___x_3653_ == 0)
{
uint64_t v___x_3654_; uint8_t v___x_3655_; 
v___x_3654_ = lean_uint64_land(v_quotient_3645_, v___x_3646_);
v___x_3655_ = lean_uint64_dec_eq(v___x_3654_, v___y_3630_);
if (v___x_3655_ == 0)
{
uint64_t v___x_3656_; 
v___x_3656_ = lean_uint64_add(v_quotient_3645_, v___x_3646_);
v___y_3616_ = v_position_3632_;
v___y_3617_ = v___y_3626_;
v___y_3618_ = v___y_3630_;
v___y_3619_ = v___y_3629_;
v___y_3620_ = v___x_3656_;
goto v___jp_3615_;
}
else
{
v___y_3616_ = v_position_3632_;
v___y_3617_ = v___y_3626_;
v___y_3618_ = v___y_3630_;
v___y_3619_ = v___y_3629_;
v___y_3620_ = v_quotient_3645_;
goto v___jp_3615_;
}
}
else
{
uint64_t v___x_3657_; 
v___x_3657_ = lean_uint64_add(v_quotient_3645_, v___x_3646_);
v___y_3616_ = v_position_3632_;
v___y_3617_ = v___y_3626_;
v___y_3618_ = v___y_3630_;
v___y_3619_ = v___y_3629_;
v___y_3620_ = v___x_3657_;
goto v___jp_3615_;
}
}
else
{
v___y_3616_ = v_position_3632_;
v___y_3617_ = v___y_3626_;
v___y_3618_ = v___y_3630_;
v___y_3619_ = v___y_3629_;
v___y_3620_ = v_quotient_3645_;
goto v___jp_3615_;
}
}
}
else
{
v___y_3616_ = v_position_3632_;
v___y_3617_ = v___y_3626_;
v___y_3618_ = v___y_3630_;
v___y_3619_ = v___y_3629_;
v___y_3620_ = v___y_3627_;
goto v___jp_3615_;
}
}
else
{
uint64_t v___x_3658_; uint64_t v___x_3659_; 
v___x_3658_ = lean_uint64_sub(v___x_3635_, v___y_3631_);
v___x_3659_ = lean_uint64_shift_left(v___y_3627_, v___x_3658_);
v___y_3616_ = v_position_3632_;
v___y_3617_ = v___y_3626_;
v___y_3618_ = v___y_3630_;
v___y_3619_ = v___y_3629_;
v___y_3620_ = v___x_3659_;
goto v___jp_3615_;
}
}
else
{
uint64_t v___x_3660_; uint8_t v___x_3661_; 
v___x_3660_ = 149ULL;
v___x_3661_ = lean_uint64_dec_lt(v___y_3628_, v___x_3660_);
if (v___x_3661_ == 0)
{
uint64_t v___x_3662_; uint64_t v___x_3663_; 
v___x_3662_ = lean_uint64_sub(v___y_3628_, v___x_3660_);
v___x_3663_ = lean_uint64_shift_left(v___y_3627_, v___x_3662_);
v___y_3521_ = v___y_3626_;
v___y_3522_ = v___y_3629_;
v___y_3523_ = v___y_3630_;
v___y_3524_ = v___x_3663_;
goto v___jp_3520_;
}
else
{
uint64_t v___x_3664_; uint8_t v___x_3665_; 
v___x_3664_ = lean_uint64_sub(v___x_3660_, v___y_3628_);
v___x_3665_ = lean_uint64_dec_eq(v___x_3664_, v___y_3630_);
if (v___x_3665_ == 0)
{
uint64_t v___x_3666_; uint8_t v___x_3667_; 
v___x_3666_ = 64ULL;
v___x_3667_ = lean_uint64_dec_lt(v___x_3664_, v___x_3666_);
if (v___x_3667_ == 0)
{
uint8_t v___x_3668_; 
v___x_3668_ = lean_uint64_dec_eq(v___x_3664_, v___x_3666_);
if (v___x_3668_ == 0)
{
v___y_3521_ = v___y_3626_;
v___y_3522_ = v___y_3629_;
v___y_3523_ = v___y_3630_;
v___y_3524_ = v___y_3630_;
goto v___jp_3520_;
}
else
{
uint64_t v___x_3669_; uint8_t v___x_3670_; 
v___x_3669_ = 9223372036854775808ULL;
v___x_3670_ = lean_uint64_dec_lt(v___x_3669_, v___y_3627_);
if (v___x_3670_ == 0)
{
v___y_3521_ = v___y_3626_;
v___y_3522_ = v___y_3629_;
v___y_3523_ = v___y_3630_;
v___y_3524_ = v___y_3630_;
goto v___jp_3520_;
}
else
{
uint64_t v___x_3671_; 
v___x_3671_ = 1ULL;
v___y_3521_ = v___y_3626_;
v___y_3522_ = v___y_3629_;
v___y_3523_ = v___y_3630_;
v___y_3524_ = v___x_3671_;
goto v___jp_3520_;
}
}
}
else
{
uint64_t v_quotient_3672_; uint64_t v___x_3673_; uint64_t v___x_3674_; uint64_t v___x_3675_; uint64_t v_remainder_3676_; uint64_t v___x_3677_; uint64_t v_half_3678_; uint8_t v___x_3679_; 
v_quotient_3672_ = lean_uint64_shift_right(v___y_3627_, v___x_3664_);
v___x_3673_ = 1ULL;
v___x_3674_ = lean_uint64_shift_left(v___x_3673_, v___x_3664_);
v___x_3675_ = lean_uint64_sub(v___x_3674_, v___x_3673_);
v_remainder_3676_ = lean_uint64_land(v___y_3627_, v___x_3675_);
v___x_3677_ = lean_uint64_sub(v___x_3664_, v___x_3673_);
v_half_3678_ = lean_uint64_shift_left(v___x_3673_, v___x_3677_);
v___x_3679_ = lean_uint64_dec_lt(v_remainder_3676_, v_half_3678_);
if (v___x_3679_ == 0)
{
uint8_t v___x_3680_; 
v___x_3680_ = lean_uint64_dec_lt(v_half_3678_, v_remainder_3676_);
if (v___x_3680_ == 0)
{
uint64_t v___x_3681_; uint8_t v___x_3682_; 
v___x_3681_ = lean_uint64_land(v_quotient_3672_, v___x_3673_);
v___x_3682_ = lean_uint64_dec_eq(v___x_3681_, v___y_3630_);
if (v___x_3682_ == 0)
{
uint64_t v___x_3683_; 
v___x_3683_ = lean_uint64_add(v_quotient_3672_, v___x_3673_);
v___y_3521_ = v___y_3626_;
v___y_3522_ = v___y_3629_;
v___y_3523_ = v___y_3630_;
v___y_3524_ = v___x_3683_;
goto v___jp_3520_;
}
else
{
v___y_3521_ = v___y_3626_;
v___y_3522_ = v___y_3629_;
v___y_3523_ = v___y_3630_;
v___y_3524_ = v_quotient_3672_;
goto v___jp_3520_;
}
}
else
{
uint64_t v___x_3684_; 
v___x_3684_ = lean_uint64_add(v_quotient_3672_, v___x_3673_);
v___y_3521_ = v___y_3626_;
v___y_3522_ = v___y_3629_;
v___y_3523_ = v___y_3630_;
v___y_3524_ = v___x_3684_;
goto v___jp_3520_;
}
}
else
{
v___y_3521_ = v___y_3626_;
v___y_3522_ = v___y_3629_;
v___y_3523_ = v___y_3630_;
v___y_3524_ = v_quotient_3672_;
goto v___jp_3520_;
}
}
}
else
{
v___y_3521_ = v___y_3626_;
v___y_3522_ = v___y_3629_;
v___y_3523_ = v___y_3630_;
v___y_3524_ = v___y_3627_;
goto v___jp_3520_;
}
}
}
}
v___jp_3685_:
{
uint64_t v___x_3693_; uint64_t v___x_3694_; uint8_t v___x_3695_; 
v___x_3693_ = 1ULL;
v___x_3694_ = lean_uint64_shift_right(v___y_3691_, v___x_3693_);
v___x_3695_ = lean_uint64_dec_eq(v___x_3694_, v___y_3690_);
if (v___x_3695_ == 0)
{
uint64_t v___x_3696_; 
v___x_3696_ = lean_uint64_add(v___y_3692_, v___x_3693_);
v___y_3626_ = v___y_3686_;
v___y_3627_ = v___y_3687_;
v___y_3628_ = v___y_3688_;
v___y_3629_ = v___y_3689_;
v___y_3630_ = v___y_3690_;
v___y_3631_ = v___x_3696_;
goto v___jp_3625_;
}
else
{
v___y_3626_ = v___y_3686_;
v___y_3627_ = v___y_3687_;
v___y_3628_ = v___y_3688_;
v___y_3629_ = v___y_3689_;
v___y_3630_ = v___y_3690_;
v___y_3631_ = v___y_3692_;
goto v___jp_3625_;
}
}
v___jp_3697_:
{
uint64_t v___x_3707_; uint8_t v___x_3708_; 
v___x_3707_ = lean_uint64_shift_right(v___y_3701_, v___y_3704_);
v___x_3708_ = lean_uint64_dec_eq(v___x_3707_, v___y_3702_);
if (v___x_3708_ == 0)
{
uint64_t v___x_3709_; 
v___x_3709_ = lean_uint64_add(v___y_3705_, v___y_3704_);
v___y_3686_ = v___y_3698_;
v___y_3687_ = v___y_3699_;
v___y_3688_ = v___y_3700_;
v___y_3689_ = v___y_3703_;
v___y_3690_ = v___y_3702_;
v___y_3691_ = v___y_3706_;
v___y_3692_ = v___x_3709_;
goto v___jp_3685_;
}
else
{
v___y_3686_ = v___y_3698_;
v___y_3687_ = v___y_3699_;
v___y_3688_ = v___y_3700_;
v___y_3689_ = v___y_3703_;
v___y_3690_ = v___y_3702_;
v___y_3691_ = v___y_3706_;
v___y_3692_ = v___y_3705_;
goto v___jp_3685_;
}
}
v___jp_3710_:
{
uint64_t v___x_3718_; uint64_t v___x_3719_; uint8_t v___x_3720_; 
v___x_3718_ = 2ULL;
v___x_3719_ = lean_uint64_shift_right(v___y_3714_, v___x_3718_);
v___x_3720_ = lean_uint64_dec_eq(v___x_3719_, v___y_3716_);
if (v___x_3720_ == 0)
{
v___y_3698_ = v___y_3711_;
v___y_3699_ = v___y_3712_;
v___y_3700_ = v___y_3713_;
v___y_3701_ = v___y_3714_;
v___y_3702_ = v___y_3716_;
v___y_3703_ = v___y_3715_;
v___y_3704_ = v___x_3718_;
v___y_3705_ = v___y_3717_;
v___y_3706_ = v___x_3719_;
goto v___jp_3697_;
}
else
{
v___y_3698_ = v___y_3711_;
v___y_3699_ = v___y_3712_;
v___y_3700_ = v___y_3713_;
v___y_3701_ = v___y_3714_;
v___y_3702_ = v___y_3716_;
v___y_3703_ = v___y_3715_;
v___y_3704_ = v___x_3718_;
v___y_3705_ = v___y_3717_;
v___y_3706_ = v___y_3714_;
goto v___jp_3697_;
}
}
v___jp_3721_:
{
uint64_t v___x_3731_; uint8_t v___x_3732_; 
v___x_3731_ = lean_uint64_shift_right(v___y_3729_, v___y_3725_);
v___x_3732_ = lean_uint64_dec_eq(v___x_3731_, v___y_3727_);
if (v___x_3732_ == 0)
{
uint64_t v___x_3733_; 
v___x_3733_ = lean_uint64_add(v___y_3726_, v___y_3725_);
v___y_3711_ = v___y_3722_;
v___y_3712_ = v___y_3723_;
v___y_3713_ = v___y_3724_;
v___y_3714_ = v___y_3730_;
v___y_3715_ = v___y_3728_;
v___y_3716_ = v___y_3727_;
v___y_3717_ = v___x_3733_;
goto v___jp_3710_;
}
else
{
v___y_3711_ = v___y_3722_;
v___y_3712_ = v___y_3723_;
v___y_3713_ = v___y_3724_;
v___y_3714_ = v___y_3730_;
v___y_3715_ = v___y_3728_;
v___y_3716_ = v___y_3727_;
v___y_3717_ = v___y_3726_;
goto v___jp_3710_;
}
}
v___jp_3734_:
{
uint64_t v___x_3742_; uint64_t v___x_3743_; uint8_t v___x_3744_; 
v___x_3742_ = 4ULL;
v___x_3743_ = lean_uint64_shift_right(v___y_3740_, v___x_3742_);
v___x_3744_ = lean_uint64_dec_eq(v___x_3743_, v___y_3739_);
if (v___x_3744_ == 0)
{
v___y_3722_ = v___y_3735_;
v___y_3723_ = v___y_3736_;
v___y_3724_ = v___y_3737_;
v___y_3725_ = v___x_3742_;
v___y_3726_ = v___y_3741_;
v___y_3727_ = v___y_3739_;
v___y_3728_ = v___y_3738_;
v___y_3729_ = v___y_3740_;
v___y_3730_ = v___x_3743_;
goto v___jp_3721_;
}
else
{
v___y_3722_ = v___y_3735_;
v___y_3723_ = v___y_3736_;
v___y_3724_ = v___y_3737_;
v___y_3725_ = v___x_3742_;
v___y_3726_ = v___y_3741_;
v___y_3727_ = v___y_3739_;
v___y_3728_ = v___y_3738_;
v___y_3729_ = v___y_3740_;
v___y_3730_ = v___y_3740_;
goto v___jp_3721_;
}
}
v___jp_3745_:
{
uint64_t v___x_3755_; uint8_t v___x_3756_; 
v___x_3755_ = lean_uint64_shift_right(v___y_3753_, v___y_3746_);
v___x_3756_ = lean_uint64_dec_eq(v___x_3755_, v___y_3751_);
if (v___x_3756_ == 0)
{
uint64_t v___x_3757_; 
v___x_3757_ = lean_uint64_add(v___y_3750_, v___y_3746_);
v___y_3735_ = v___y_3747_;
v___y_3736_ = v___y_3748_;
v___y_3737_ = v___y_3749_;
v___y_3738_ = v___y_3752_;
v___y_3739_ = v___y_3751_;
v___y_3740_ = v___y_3754_;
v___y_3741_ = v___x_3757_;
goto v___jp_3734_;
}
else
{
v___y_3735_ = v___y_3747_;
v___y_3736_ = v___y_3748_;
v___y_3737_ = v___y_3749_;
v___y_3738_ = v___y_3752_;
v___y_3739_ = v___y_3751_;
v___y_3740_ = v___y_3754_;
v___y_3741_ = v___y_3750_;
goto v___jp_3734_;
}
}
v___jp_3758_:
{
uint64_t v___x_3766_; uint64_t v___x_3767_; uint8_t v___x_3768_; 
v___x_3766_ = 8ULL;
v___x_3767_ = lean_uint64_shift_right(v___y_3764_, v___x_3766_);
v___x_3768_ = lean_uint64_dec_eq(v___x_3767_, v___y_3763_);
if (v___x_3768_ == 0)
{
v___y_3746_ = v___x_3766_;
v___y_3747_ = v___y_3759_;
v___y_3748_ = v___y_3760_;
v___y_3749_ = v___y_3761_;
v___y_3750_ = v___y_3765_;
v___y_3751_ = v___y_3763_;
v___y_3752_ = v___y_3762_;
v___y_3753_ = v___y_3764_;
v___y_3754_ = v___x_3767_;
goto v___jp_3745_;
}
else
{
v___y_3746_ = v___x_3766_;
v___y_3747_ = v___y_3759_;
v___y_3748_ = v___y_3760_;
v___y_3749_ = v___y_3761_;
v___y_3750_ = v___y_3765_;
v___y_3751_ = v___y_3763_;
v___y_3752_ = v___y_3762_;
v___y_3753_ = v___y_3764_;
v___y_3754_ = v___y_3764_;
goto v___jp_3745_;
}
}
v___jp_3769_:
{
uint64_t v___x_3779_; uint8_t v___x_3780_; 
v___x_3779_ = lean_uint64_shift_right(v___y_3772_, v___y_3777_);
v___x_3780_ = lean_uint64_dec_eq(v___x_3779_, v___y_3775_);
if (v___x_3780_ == 0)
{
uint64_t v___x_3781_; 
v___x_3781_ = lean_uint64_add(v___y_3774_, v___y_3777_);
v___y_3759_ = v___y_3770_;
v___y_3760_ = v___y_3771_;
v___y_3761_ = v___y_3773_;
v___y_3762_ = v___y_3776_;
v___y_3763_ = v___y_3775_;
v___y_3764_ = v___y_3778_;
v___y_3765_ = v___x_3781_;
goto v___jp_3758_;
}
else
{
v___y_3759_ = v___y_3770_;
v___y_3760_ = v___y_3771_;
v___y_3761_ = v___y_3773_;
v___y_3762_ = v___y_3776_;
v___y_3763_ = v___y_3775_;
v___y_3764_ = v___y_3778_;
v___y_3765_ = v___y_3774_;
goto v___jp_3758_;
}
}
v___jp_3782_:
{
uint64_t v___x_3790_; uint64_t v___x_3791_; uint8_t v___x_3792_; 
v___x_3790_ = 16ULL;
v___x_3791_ = lean_uint64_shift_right(v___y_3786_, v___x_3790_);
v___x_3792_ = lean_uint64_dec_eq(v___x_3791_, v___y_3788_);
if (v___x_3792_ == 0)
{
v___y_3770_ = v___y_3783_;
v___y_3771_ = v___y_3784_;
v___y_3772_ = v___y_3786_;
v___y_3773_ = v___y_3785_;
v___y_3774_ = v___y_3789_;
v___y_3775_ = v___y_3788_;
v___y_3776_ = v___y_3787_;
v___y_3777_ = v___x_3790_;
v___y_3778_ = v___x_3791_;
goto v___jp_3769_;
}
else
{
v___y_3770_ = v___y_3783_;
v___y_3771_ = v___y_3784_;
v___y_3772_ = v___y_3786_;
v___y_3773_ = v___y_3785_;
v___y_3774_ = v___y_3789_;
v___y_3775_ = v___y_3788_;
v___y_3776_ = v___y_3787_;
v___y_3777_ = v___x_3790_;
v___y_3778_ = v___y_3786_;
goto v___jp_3769_;
}
}
v___jp_3793_:
{
uint64_t v___x_3801_; uint8_t v___x_3802_; 
v___x_3801_ = lean_uint64_shift_right(v___y_3795_, v___y_3799_);
v___x_3802_ = lean_uint64_dec_eq(v___x_3801_, v___y_3797_);
if (v___x_3802_ == 0)
{
v___y_3783_ = v___y_3794_;
v___y_3784_ = v___y_3795_;
v___y_3785_ = v___y_3796_;
v___y_3786_ = v___y_3800_;
v___y_3787_ = v___y_3798_;
v___y_3788_ = v___y_3797_;
v___y_3789_ = v___y_3799_;
goto v___jp_3782_;
}
else
{
v___y_3783_ = v___y_3794_;
v___y_3784_ = v___y_3795_;
v___y_3785_ = v___y_3796_;
v___y_3786_ = v___y_3800_;
v___y_3787_ = v___y_3798_;
v___y_3788_ = v___y_3797_;
v___y_3789_ = v___y_3797_;
goto v___jp_3782_;
}
}
v___jp_3803_:
{
uint64_t v___x_3808_; uint8_t v___x_3809_; 
v___x_3808_ = 0ULL;
v___x_3809_ = lean_uint64_dec_eq(v___y_3805_, v___x_3808_);
if (v___x_3809_ == 0)
{
uint64_t v___x_3810_; uint64_t v___x_3811_; uint8_t v___x_3812_; 
v___x_3810_ = 32ULL;
v___x_3811_ = lean_uint64_shift_right(v___y_3805_, v___x_3810_);
v___x_3812_ = lean_uint64_dec_eq(v___x_3811_, v___x_3808_);
if (v___x_3812_ == 0)
{
v___y_3794_ = v___y_3804_;
v___y_3795_ = v___y_3805_;
v___y_3796_ = v___y_3806_;
v___y_3797_ = v___x_3808_;
v___y_3798_ = v___y_3807_;
v___y_3799_ = v___x_3810_;
v___y_3800_ = v___x_3811_;
goto v___jp_3793_;
}
else
{
v___y_3794_ = v___y_3804_;
v___y_3795_ = v___y_3805_;
v___y_3796_ = v___y_3806_;
v___y_3797_ = v___x_3808_;
v___y_3798_ = v___y_3807_;
v___y_3799_ = v___x_3810_;
v___y_3800_ = v___y_3805_;
goto v___jp_3793_;
}
}
else
{
if (v___y_3804_ == 0)
{
uint32_t v___x_3813_; 
v___x_3813_ = 0;
return v___x_3813_;
}
else
{
uint32_t v___x_3814_; 
v___x_3814_ = 2147483648;
return v___x_3814_;
}
}
}
v___jp_3815_:
{
uint64_t v___x_3822_; uint64_t v___x_3823_; uint64_t v___x_3824_; uint8_t v___x_3825_; 
v___x_3822_ = lean_uint64_mul(v___y_3820_, v___y_3818_);
v___x_3823_ = lean_uint64_add(v___y_3817_, v___y_3821_);
v___x_3824_ = 281474976710656ULL;
v___x_3825_ = lean_uint64_dec_lt(v___x_3822_, v___x_3824_);
if (v___x_3825_ == 0)
{
v___y_3804_ = v___y_3816_;
v___y_3805_ = v___x_3822_;
v___y_3806_ = v___x_3823_;
v___y_3807_ = v___y_3819_;
goto v___jp_3803_;
}
else
{
uint64_t v___x_3826_; uint8_t v___x_3827_; 
v___x_3826_ = 123ULL;
v___x_3827_ = lean_uint64_dec_le(v___x_3823_, v___x_3826_);
if (v___x_3827_ == 0)
{
v___y_3804_ = v___y_3816_;
v___y_3805_ = v___x_3822_;
v___y_3806_ = v___x_3823_;
v___y_3807_ = v___y_3819_;
goto v___jp_3803_;
}
else
{
uint64_t v___x_3828_; uint8_t v___x_3829_; 
v___x_3828_ = 0ULL;
v___x_3829_ = lean_uint64_dec_eq(v___x_3822_, v___x_3828_);
if (v___x_3829_ == 0)
{
uint64_t v___x_3830_; uint64_t v___x_3831_; uint8_t v___x_3832_; 
v___x_3830_ = 149ULL;
v___x_3831_ = lean_uint64_sub(v___x_3830_, v___x_3823_);
v___x_3832_ = lean_uint64_dec_eq(v___x_3831_, v___x_3828_);
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
v___y_3542_ = v___y_3816_;
v___y_3543_ = v___y_3819_;
v___y_3544_ = v___x_3828_;
v___y_3545_ = v___x_3828_;
goto v___jp_3541_;
}
else
{
uint64_t v___x_3836_; uint8_t v___x_3837_; 
v___x_3836_ = 9223372036854775808ULL;
v___x_3837_ = lean_uint64_dec_lt(v___x_3836_, v___x_3822_);
if (v___x_3837_ == 0)
{
v___y_3542_ = v___y_3816_;
v___y_3543_ = v___y_3819_;
v___y_3544_ = v___x_3828_;
v___y_3545_ = v___x_3828_;
goto v___jp_3541_;
}
else
{
uint64_t v___x_3838_; 
v___x_3838_ = 1ULL;
v___y_3542_ = v___y_3816_;
v___y_3543_ = v___y_3819_;
v___y_3544_ = v___x_3828_;
v___y_3545_ = v___x_3838_;
goto v___jp_3541_;
}
}
}
else
{
uint64_t v_quotient_3839_; uint64_t v___x_3840_; uint64_t v___x_3841_; uint64_t v___x_3842_; uint64_t v_remainder_3843_; uint64_t v___x_3844_; uint64_t v_half_3845_; uint8_t v___x_3846_; 
v_quotient_3839_ = lean_uint64_shift_right(v___x_3822_, v___x_3831_);
v___x_3840_ = 1ULL;
v___x_3841_ = lean_uint64_shift_left(v___x_3840_, v___x_3831_);
v___x_3842_ = lean_uint64_sub(v___x_3841_, v___x_3840_);
v_remainder_3843_ = lean_uint64_land(v___x_3822_, v___x_3842_);
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
v___x_3849_ = lean_uint64_dec_eq(v___x_3848_, v___x_3828_);
if (v___x_3849_ == 0)
{
uint64_t v___x_3850_; 
v___x_3850_ = lean_uint64_add(v_quotient_3839_, v___x_3840_);
v___y_3542_ = v___y_3816_;
v___y_3543_ = v___y_3819_;
v___y_3544_ = v___x_3828_;
v___y_3545_ = v___x_3850_;
goto v___jp_3541_;
}
else
{
v___y_3542_ = v___y_3816_;
v___y_3543_ = v___y_3819_;
v___y_3544_ = v___x_3828_;
v___y_3545_ = v_quotient_3839_;
goto v___jp_3541_;
}
}
else
{
uint64_t v___x_3851_; 
v___x_3851_ = lean_uint64_add(v_quotient_3839_, v___x_3840_);
v___y_3542_ = v___y_3816_;
v___y_3543_ = v___y_3819_;
v___y_3544_ = v___x_3828_;
v___y_3545_ = v___x_3851_;
goto v___jp_3541_;
}
}
else
{
v___y_3542_ = v___y_3816_;
v___y_3543_ = v___y_3819_;
v___y_3544_ = v___x_3828_;
v___y_3545_ = v_quotient_3839_;
goto v___jp_3541_;
}
}
}
else
{
v___y_3542_ = v___y_3816_;
v___y_3543_ = v___y_3819_;
v___y_3544_ = v___x_3828_;
v___y_3545_ = v___x_3822_;
goto v___jp_3541_;
}
}
else
{
if (v___y_3816_ == 0)
{
uint32_t v___x_3852_; 
v___x_3852_ = 0;
return v___x_3852_;
}
else
{
uint32_t v___x_3853_; 
v___x_3853_ = 2147483648;
return v___x_3853_;
}
}
}
}
}
v___jp_3857_:
{
uint64_t v___x_3863_; uint64_t v___x_3864_; uint8_t v___x_3865_; 
v___x_3863_ = lean_uint32_to_uint64(v_ey_3856_);
v___x_3864_ = 0ULL;
v___x_3865_ = lean_uint64_dec_eq(v___x_3863_, v___x_3864_);
if (v___x_3865_ == 0)
{
uint64_t v___x_3866_; uint64_t v___x_3867_; 
v___x_3866_ = 1ULL;
v___x_3867_ = lean_uint64_sub(v___x_3863_, v___x_3866_);
v___y_3816_ = v___y_3858_;
v___y_3817_ = v___y_3862_;
v___y_3818_ = v___y_3859_;
v___y_3819_ = v___y_3860_;
v___y_3820_ = v___y_3861_;
v___y_3821_ = v___x_3867_;
goto v___jp_3815_;
}
else
{
v___y_3816_ = v___y_3858_;
v___y_3817_ = v___y_3862_;
v___y_3818_ = v___y_3859_;
v___y_3819_ = v___y_3860_;
v___y_3820_ = v___y_3861_;
v___y_3821_ = v___x_3864_;
goto v___jp_3815_;
}
}
v___jp_3868_:
{
uint64_t v___x_3873_; uint64_t v___x_3874_; uint8_t v___x_3875_; 
v___x_3873_ = lean_uint32_to_uint64(v_ex_3854_);
v___x_3874_ = 0ULL;
v___x_3875_ = lean_uint64_dec_eq(v___x_3873_, v___x_3874_);
if (v___x_3875_ == 0)
{
uint64_t v___x_3876_; uint64_t v___x_3877_; 
v___x_3876_ = 1ULL;
v___x_3877_ = lean_uint64_sub(v___x_3873_, v___x_3876_);
v___y_3858_ = v___y_3869_;
v___y_3859_ = v___y_3872_;
v___y_3860_ = v___y_3870_;
v___y_3861_ = v___y_3871_;
v___y_3862_ = v___x_3877_;
goto v___jp_3857_;
}
else
{
v___y_3858_ = v___y_3869_;
v___y_3859_ = v___y_3872_;
v___y_3860_ = v___y_3870_;
v___y_3861_ = v___y_3871_;
v___y_3862_ = v___x_3874_;
goto v___jp_3857_;
}
}
v___jp_3878_:
{
uint32_t v___x_3883_; uint8_t v___x_3884_; 
v___x_3883_ = 0;
v___x_3884_ = lean_uint32_dec_eq(v_ey_3856_, v___x_3883_);
if (v___x_3884_ == 0)
{
uint64_t v___x_3885_; uint64_t v___x_3886_; uint64_t v___x_3887_; 
v___x_3885_ = lean_uint32_to_uint64(v___y_3881_);
v___x_3886_ = 8388608ULL;
v___x_3887_ = lean_uint64_lor(v___x_3885_, v___x_3886_);
v___y_3869_ = v___y_3879_;
v___y_3870_ = v___y_3880_;
v___y_3871_ = v___y_3882_;
v___y_3872_ = v___x_3887_;
goto v___jp_3868_;
}
else
{
uint64_t v___x_3888_; 
v___x_3888_ = lean_uint32_to_uint64(v___y_3881_);
v___y_3869_ = v___y_3879_;
v___y_3870_ = v___y_3880_;
v___y_3871_ = v___y_3882_;
v___y_3872_ = v___x_3888_;
goto v___jp_3868_;
}
}
v___jp_3889_:
{
uint32_t v___x_3891_; uint32_t v_xFraction_3892_; uint32_t v_yFraction_3893_; uint32_t v___x_3894_; uint8_t v___x_3895_; 
v___x_3891_ = 8388607;
v_xFraction_3892_ = lean_uint32_land(v___y_3409_, v___x_3891_);
v_yFraction_3893_ = lean_uint32_land(v___y_3410_, v___x_3891_);
v___x_3894_ = 0;
v___x_3895_ = lean_uint32_dec_eq(v_ex_3854_, v___x_3894_);
if (v___x_3895_ == 0)
{
uint64_t v___x_3896_; uint64_t v___x_3897_; uint64_t v___x_3898_; 
v___x_3896_ = lean_uint32_to_uint64(v_xFraction_3892_);
v___x_3897_ = 8388608ULL;
v___x_3898_ = lean_uint64_lor(v___x_3896_, v___x_3897_);
v___y_3879_ = v___y_3890_;
v___y_3880_ = v___x_3891_;
v___y_3881_ = v_yFraction_3893_;
v___y_3882_ = v___x_3898_;
goto v___jp_3878_;
}
else
{
uint64_t v___x_3899_; 
v___x_3899_ = lean_uint32_to_uint64(v_xFraction_3892_);
v___y_3879_ = v___y_3890_;
v___y_3880_ = v___x_3891_;
v___y_3881_ = v_yFraction_3893_;
v___y_3882_ = v___x_3899_;
goto v___jp_3878_;
}
}
v___jp_3900_:
{
if (v___y_3902_ == 0)
{
v___y_3890_ = v___x_3408_;
goto v___jp_3889_;
}
else
{
v___y_3890_ = v___y_3901_;
goto v___jp_3889_;
}
}
v___jp_3906_:
{
if (v___y_3907_ == 0)
{
if (v___y_3909_ == 0)
{
v___y_3901_ = v___y_3908_;
v___y_3902_ = v___x_3905_;
goto v___jp_3900_;
}
else
{
v___y_3890_ = v___x_3408_;
goto v___jp_3889_;
}
}
else
{
v___y_3901_ = v___y_3908_;
v___y_3902_ = v___y_3909_;
goto v___jp_3900_;
}
}
v___jp_3910_:
{
uint32_t v___x_3913_; uint32_t v___x_3914_; uint32_t v___x_3915_; uint8_t v___x_3916_; 
v___x_3913_ = 2147483648;
v___x_3914_ = lean_uint32_land(v___y_3410_, v___x_3913_);
v___x_3915_ = 0;
v___x_3916_ = lean_uint32_dec_eq(v___x_3914_, v___x_3915_);
if (v___x_3916_ == 0)
{
v___y_3907_ = v___y_3912_;
v___y_3908_ = v___y_3911_;
v___y_3909_ = v___x_3408_;
goto v___jp_3906_;
}
else
{
v___y_3907_ = v___y_3912_;
v___y_3908_ = v___y_3911_;
v___y_3909_ = v___y_3911_;
goto v___jp_3906_;
}
}
v___jp_3917_:
{
if (v___y_3918_ == 0)
{
uint32_t v___x_3919_; uint32_t v___x_3920_; uint32_t v___x_3921_; uint8_t v___x_3922_; 
v___x_3919_ = 2147483648;
v___x_3920_ = lean_uint32_land(v___y_3409_, v___x_3919_);
v___x_3921_ = 0;
v___x_3922_ = lean_uint32_dec_eq(v___x_3920_, v___x_3921_);
if (v___x_3922_ == 0)
{
v___y_3911_ = v___y_3918_;
v___y_3912_ = v___x_3408_;
goto v___jp_3910_;
}
else
{
v___y_3911_ = v___y_3918_;
v___y_3912_ = v___y_3918_;
goto v___jp_3910_;
}
}
else
{
lean_object* v___x_3923_; lean_object* v___x_3924_; lean_object* v___x_3925_; uint32_t v___x_3926_; 
v___x_3923_ = lean_uint32_to_nat(v___y_3409_);
v___x_3924_ = lean_uint32_to_nat(v___y_3410_);
v___x_3925_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_3923_, v___x_3924_);
v___x_3926_ = lean_uint32_of_nat(v___x_3925_);
lean_dec(v___x_3925_);
return v___x_3926_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object* v___x_3941_, lean_object* v___y_3942_, lean_object* v___y_3943_){
_start:
{
uint8_t v___x_11517__boxed_3944_; uint32_t v___y_11518__boxed_3945_; uint32_t v___y_11519__boxed_3946_; uint32_t v_res_3947_; lean_object* v_r_3948_; 
v___x_11517__boxed_3944_ = lean_unbox(v___x_3941_);
v___y_11518__boxed_3945_ = lean_unbox_uint32(v___y_3942_);
lean_dec(v___y_3942_);
v___y_11519__boxed_3946_ = lean_unbox_uint32(v___y_3943_);
lean_dec(v___y_3943_);
v_res_3947_ = lp_competition_main___lam__3(v___x_11517__boxed_3944_, v___y_11518__boxed_3945_, v___y_11519__boxed_3946_);
v_r_3948_ = lean_box_uint32(v_res_3947_);
return v_r_3948_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_3963_; lean_object* v___x_3964_; lean_object* v___x_3965_; uint8_t v___x_3966_; 
v___x_3963_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_3964_ = lean_io_getenv(v___x_3963_);
v___x_3965_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_3966_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_3964_, v___x_3965_);
if (v___x_3966_ == 0)
{
lean_object* v___x_3967_; uint8_t v___x_3968_; 
v___x_3967_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_3968_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_3964_, v___x_3967_);
lean_dec(v___x_3964_);
if (v___x_3968_ == 0)
{
lean_object* v___x_3969_; lean_object* v___x_3970_; 
v___x_3969_ = ((lean_object*)(lp_competition_main___closed__6));
v___x_3970_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_3970_, 0, v___x_3969_);
return v___x_3970_;
}
else
{
lean_object* v___f_3971_; lean_object* v___x_3972_; lean_object* v___f_3973_; lean_object* v___x_3974_; lean_object* v___x_3975_; lean_object* v___x_3976_; 
v___f_3971_ = ((lean_object*)(lp_competition_main___closed__7));
v___x_3972_ = lean_box(v___x_3968_);
v___f_3973_ = lean_alloc_closure((void*)(lp_competition_main___lam__1___boxed), 3, 1);
lean_closure_set(v___f_3973_, 0, v___x_3972_);
v___x_3974_ = ((lean_object*)(lp_competition_main___closed__8));
v___x_3975_ = ((lean_object*)(lp_competition_main___closed__9));
v___x_3976_ = lp_competition_Bench_Suite_run(v___f_3971_, v___f_3973_, v___x_3974_, v___x_3975_);
return v___x_3976_;
}
}
else
{
lean_object* v___f_3977_; lean_object* v___x_3978_; lean_object* v___f_3979_; lean_object* v___x_3980_; lean_object* v___x_3981_; lean_object* v___x_3982_; 
lean_dec(v___x_3964_);
v___f_3977_ = ((lean_object*)(lp_competition_main___closed__7));
v___x_3978_ = lean_box(v___x_3966_);
v___f_3979_ = lean_alloc_closure((void*)(lp_competition_main___lam__3___boxed), 3, 1);
lean_closure_set(v___f_3979_, 0, v___x_3978_);
v___x_3980_ = ((lean_object*)(lp_competition_main___closed__8));
v___x_3981_ = ((lean_object*)(lp_competition_main___closed__9));
v___x_3982_ = lp_competition_Bench_Suite_run(v___f_3977_, v___f_3979_, v___x_3980_, v___x_3981_);
return v___x_3982_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_3983_){
_start:
{
lean_object* v_res_3984_; 
v_res_3984_ = _lean_main();
return v_res_3984_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_competition_BenchFull(uint8_t builtin);
lean_object* initialize_competition_BenchSuite(uint8_t builtin);
lean_object* initialize_competition_Submission(uint8_t builtin);
void lean_initialize();
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_competition_R19RuntimeCostMain(uint8_t builtin) {
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
  res = initialize_competition_R19RuntimeCostMain(1 /* builtin */);
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
