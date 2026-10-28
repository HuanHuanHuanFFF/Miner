// Lean compiler output
// Module: R22BroadWordCostMain
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
uint32_t lean_uint32_add(uint32_t, uint32_t);
uint32_t lean_uint32_shift_left(uint32_t, uint32_t);
uint32_t lean_uint32_xor(uint32_t, uint32_t);
lean_object* lp_competition_Submission_sum___boxed(lean_object*, lean_object*);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word(lean_object*, lean_object*, lean_object*);
lean_object* lp_competition_Submission_bmm(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lean_io_getenv(lean_object*);
uint8_t l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(lean_object*, lean_object*);
uint32_t lp_competition_Submission_FastMul_mul(uint32_t, uint32_t);
uint8_t lean_uint64_dec_eq(uint64_t, uint64_t);
uint32_t lean_uint64_to_uint32(uint64_t);
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
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(lean_object*, lean_object*);
lean_object* lp_competition_Bench_Suite_run(lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_ctor_object lp_competition_r22CostBroadWordAdd___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*3 + 8, .m_other = 3, .m_tag = 0}, .m_objs = {((lean_object*)(((size_t)(8) << 1) | 1)),((lean_object*)(((size_t)(23) << 1) | 1)),((lean_object*)(((size_t)(127) << 1) | 1)),LEAN_SCALAR_PTR_LITERAL(0, 0, 0, 0, 0, 0, 0, 0)}};
static const lean_object* lp_competition_r22CostBroadWordAdd___closed__0 = (const lean_object*)&lp_competition_r22CostBroadWordAdd___closed__0_value;
LEAN_EXPORT uint32_t lp_competition_r22CostBroadWordAdd(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_r22CostBroadWordAdd___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint8_t, uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__2(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__2___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint8_t, uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition_main___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 14, .m_capacity = 14, .m_length = 13, .m_data = "BENCH_VARIANT"};
static const lean_object* lp_competition_main___closed__0 = (const lean_object*)&lp_competition_main___closed__0_value;
static const lean_string_object lp_competition_main___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 8, .m_capacity = 8, .m_length = 7, .m_data = "control"};
static const lean_object* lp_competition_main___closed__1 = (const lean_object*)&lp_competition_main___closed__1_value;
static const lean_ctor_object lp_competition_main___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__1_value)}};
static const lean_object* lp_competition_main___closed__2 = (const lean_object*)&lp_competition_main___closed__2_value;
static const lean_string_object lp_competition_main___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 10, .m_capacity = 10, .m_length = 9, .m_data = "broadword"};
static const lean_object* lp_competition_main___closed__3 = (const lean_object*)&lp_competition_main___closed__3_value;
static const lean_ctor_object lp_competition_main___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__3_value)}};
static const lean_object* lp_competition_main___closed__4 = (const lean_object*)&lp_competition_main___closed__4_value;
static const lean_string_object lp_competition_main___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 22, .m_capacity = 22, .m_length = 21, .m_data = "Unknown BENCH_VARIANT"};
static const lean_object* lp_competition_main___closed__5 = (const lean_object*)&lp_competition_main___closed__5_value;
static const lean_ctor_object lp_competition_main___closed__6_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_main___closed__5_value)}};
static const lean_object* lp_competition_main___closed__6 = (const lean_object*)&lp_competition_main___closed__6_value;
static const lean_closure_object lp_competition_main___closed__7_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_main___lam__0___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__7 = (const lean_object*)&lp_competition_main___closed__7_value;
static const lean_closure_object lp_competition_main___closed__8_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_sum___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__8 = (const lean_object*)&lp_competition_main___closed__8_value;
static const lean_closure_object lp_competition_main___closed__9_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_bmm, .m_arity = 6, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__9 = (const lean_object*)&lp_competition_main___closed__9_value;
static const lean_closure_object lp_competition_main___closed__10_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_main___lam__2___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__10 = (const lean_object*)&lp_competition_main___closed__10_value;
LEAN_EXPORT lean_object* _lean_main();
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_r22CostBroadWordAdd(uint32_t v_x_6_, uint32_t v_y_7_){
_start:
{
uint8_t v___y_15_; uint8_t v___y_29_; uint8_t v___y_43_; uint8_t v___y_60_; float v___y_67_; float v___y_68_; float v___y_82_; uint8_t v___y_83_; float v___y_98_; uint8_t v___y_108_; uint32_t v___x_131_; uint32_t v___x_132_; uint32_t v___x_133_; uint32_t v_eu_134_; uint32_t v___y_136_; uint32_t v___y_137_; uint32_t v___y_138_; uint32_t v___y_139_; uint32_t v___y_156_; uint32_t v___y_157_; uint32_t v___y_158_; uint32_t v___y_159_; uint32_t v___y_160_; uint32_t v___y_161_; uint32_t v___y_162_; uint32_t v___x_172_; uint32_t v_ev_173_; uint32_t v___y_175_; uint32_t v___y_176_; uint32_t v___y_177_; uint32_t v___y_178_; uint32_t v___y_195_; uint32_t v___y_196_; uint32_t v___y_197_; uint32_t v___y_198_; uint32_t v___y_199_; uint32_t v___y_200_; uint32_t v___y_201_; uint8_t v___y_212_; uint32_t v___x_252_; uint32_t v___x_253_; uint8_t v___x_254_; 
v___x_131_ = 23;
v___x_132_ = lean_uint32_shift_right(v_x_6_, v___x_131_);
v___x_133_ = 255;
v_eu_134_ = lean_uint32_land(v___x_132_, v___x_133_);
v___x_172_ = lean_uint32_shift_right(v_y_7_, v___x_131_);
v_ev_173_ = lean_uint32_land(v___x_172_, v___x_133_);
v___x_252_ = lean_uint32_xor(v_x_6_, v_y_7_);
v___x_253_ = 2147483648;
v___x_254_ = lean_uint32_dec_lt(v___x_252_, v___x_253_);
if (v___x_254_ == 0)
{
v___y_212_ = v___x_254_;
goto v___jp_211_;
}
else
{
uint32_t v___x_255_; uint32_t v___x_256_; uint32_t v___x_257_; uint8_t v___x_258_; 
v___x_255_ = 1;
v___x_256_ = lean_uint32_sub(v_eu_134_, v___x_255_);
v___x_257_ = 254;
v___x_258_ = lean_uint32_dec_lt(v___x_256_, v___x_257_);
v___y_212_ = v___x_258_;
goto v___jp_211_;
}
v___jp_8_:
{
lean_object* v___x_9_; lean_object* v___x_10_; lean_object* v___x_11_; lean_object* v___x_12_; uint32_t v___x_13_; 
v___x_9_ = ((lean_object*)(lp_competition_r22CostBroadWordAdd___closed__0));
v___x_10_ = lean_uint32_to_nat(v_x_6_);
v___x_11_ = lean_uint32_to_nat(v_y_7_);
v___x_12_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word(v___x_9_, v___x_10_, v___x_11_);
v___x_13_ = lean_uint32_of_nat(v___x_12_);
lean_dec(v___x_12_);
return v___x_13_;
}
v___jp_14_:
{
if (v___y_15_ == 0)
{
goto v___jp_8_;
}
else
{
uint32_t v___x_16_; uint32_t v___x_17_; 
v___x_16_ = 4194304;
v___x_17_ = lean_uint32_lor(v_y_7_, v___x_16_);
return v___x_17_;
}
}
v___jp_18_:
{
uint32_t v___x_19_; uint32_t v___x_20_; uint32_t v___x_21_; uint32_t v___x_22_; uint8_t v___x_23_; 
v___x_19_ = 23;
v___x_20_ = lean_uint32_shift_right(v_y_7_, v___x_19_);
v___x_21_ = 255;
v___x_22_ = lean_uint32_land(v___x_20_, v___x_21_);
v___x_23_ = lean_uint32_dec_eq(v___x_22_, v___x_21_);
if (v___x_23_ == 0)
{
v___y_15_ = v___x_23_;
goto v___jp_14_;
}
else
{
uint32_t v___x_24_; uint32_t v___x_25_; uint32_t v___x_26_; uint8_t v___x_27_; 
v___x_24_ = 8388607;
v___x_25_ = lean_uint32_land(v_y_7_, v___x_24_);
v___x_26_ = 0;
v___x_27_ = lean_uint32_dec_eq(v___x_25_, v___x_26_);
if (v___x_27_ == 0)
{
v___y_15_ = v___x_23_;
goto v___jp_14_;
}
else
{
goto v___jp_8_;
}
}
}
v___jp_28_:
{
if (v___y_29_ == 0)
{
goto v___jp_18_;
}
else
{
uint32_t v___x_30_; uint32_t v___x_31_; 
v___x_30_ = 4194304;
v___x_31_ = lean_uint32_lor(v_x_6_, v___x_30_);
return v___x_31_;
}
}
v___jp_32_:
{
uint32_t v___x_33_; uint32_t v___x_34_; uint32_t v___x_35_; uint32_t v___x_36_; uint8_t v___x_37_; 
v___x_33_ = 23;
v___x_34_ = lean_uint32_shift_right(v_x_6_, v___x_33_);
v___x_35_ = 255;
v___x_36_ = lean_uint32_land(v___x_34_, v___x_35_);
v___x_37_ = lean_uint32_dec_eq(v___x_36_, v___x_35_);
if (v___x_37_ == 0)
{
v___y_29_ = v___x_37_;
goto v___jp_28_;
}
else
{
uint32_t v___x_38_; uint32_t v___x_39_; uint32_t v___x_40_; uint8_t v___x_41_; 
v___x_38_ = 8388607;
v___x_39_ = lean_uint32_land(v_x_6_, v___x_38_);
v___x_40_ = 0;
v___x_41_ = lean_uint32_dec_eq(v___x_39_, v___x_40_);
if (v___x_41_ == 0)
{
v___y_29_ = v___x_37_;
goto v___jp_28_;
}
else
{
goto v___jp_18_;
}
}
}
v___jp_42_:
{
if (v___y_43_ == 0)
{
goto v___jp_32_;
}
else
{
uint32_t v___x_44_; uint32_t v___x_45_; uint32_t v___x_46_; uint8_t v___x_47_; 
v___x_44_ = 4194304;
v___x_45_ = lean_uint32_land(v_y_7_, v___x_44_);
v___x_46_ = 0;
v___x_47_ = lean_uint32_dec_eq(v___x_45_, v___x_46_);
if (v___x_47_ == 0)
{
goto v___jp_32_;
}
else
{
uint32_t v___x_48_; 
v___x_48_ = lean_uint32_lor(v_y_7_, v___x_44_);
return v___x_48_;
}
}
}
v___jp_49_:
{
uint32_t v___x_50_; uint32_t v___x_51_; uint32_t v___x_52_; uint32_t v___x_53_; uint8_t v___x_54_; 
v___x_50_ = 23;
v___x_51_ = lean_uint32_shift_right(v_y_7_, v___x_50_);
v___x_52_ = 255;
v___x_53_ = lean_uint32_land(v___x_51_, v___x_52_);
v___x_54_ = lean_uint32_dec_eq(v___x_53_, v___x_52_);
if (v___x_54_ == 0)
{
v___y_43_ = v___x_54_;
goto v___jp_42_;
}
else
{
uint32_t v___x_55_; uint32_t v___x_56_; uint32_t v___x_57_; uint8_t v___x_58_; 
v___x_55_ = 8388607;
v___x_56_ = lean_uint32_land(v_y_7_, v___x_55_);
v___x_57_ = 0;
v___x_58_ = lean_uint32_dec_eq(v___x_56_, v___x_57_);
if (v___x_58_ == 0)
{
v___y_43_ = v___x_54_;
goto v___jp_42_;
}
else
{
goto v___jp_32_;
}
}
}
v___jp_59_:
{
if (v___y_60_ == 0)
{
goto v___jp_49_;
}
else
{
uint32_t v___x_61_; uint32_t v___x_62_; uint32_t v___x_63_; uint8_t v___x_64_; 
v___x_61_ = 4194304;
v___x_62_ = lean_uint32_land(v_x_6_, v___x_61_);
v___x_63_ = 0;
v___x_64_ = lean_uint32_dec_eq(v___x_62_, v___x_63_);
if (v___x_64_ == 0)
{
goto v___jp_49_;
}
else
{
uint32_t v___x_65_; 
v___x_65_ = lean_uint32_lor(v_x_6_, v___x_61_);
return v___x_65_;
}
}
}
v___jp_66_:
{
float v_result_69_; uint8_t v___x_70_; 
v_result_69_ = lean_float32_add(v___y_67_, v___y_68_);
v___x_70_ = lean_float32_beq(v_result_69_, v_result_69_);
if (v___x_70_ == 0)
{
uint32_t v___x_71_; uint32_t v___x_72_; uint32_t v___x_73_; uint32_t v___x_74_; uint8_t v___x_75_; 
v___x_71_ = 23;
v___x_72_ = lean_uint32_shift_right(v_x_6_, v___x_71_);
v___x_73_ = 255;
v___x_74_ = lean_uint32_land(v___x_72_, v___x_73_);
v___x_75_ = lean_uint32_dec_eq(v___x_74_, v___x_73_);
if (v___x_75_ == 0)
{
v___y_60_ = v___x_75_;
goto v___jp_59_;
}
else
{
uint32_t v___x_76_; uint32_t v___x_77_; uint32_t v___x_78_; uint8_t v___x_79_; 
v___x_76_ = 8388607;
v___x_77_ = lean_uint32_land(v_x_6_, v___x_76_);
v___x_78_ = 0;
v___x_79_ = lean_uint32_dec_eq(v___x_77_, v___x_78_);
if (v___x_79_ == 0)
{
v___y_60_ = v___x_75_;
goto v___jp_59_;
}
else
{
goto v___jp_49_;
}
}
}
else
{
uint32_t v___x_80_; 
v___x_80_ = lean_float32_to_bits(v_result_69_);
return v___x_80_;
}
}
v___jp_81_:
{
if (v___y_83_ == 0)
{
float v___x_84_; 
v___x_84_ = lean_float32_of_bits(v_y_7_);
v___y_67_ = v___y_82_;
v___y_68_ = v___x_84_;
goto v___jp_66_;
}
else
{
uint32_t v___x_85_; uint32_t v___x_86_; uint32_t v___x_87_; uint32_t v___x_88_; float v___x_89_; lean_object* v___x_90_; uint32_t v___x_91_; uint32_t v___x_92_; lean_object* v___x_93_; lean_object* v___x_94_; float v___x_95_; float v___x_96_; 
v___x_85_ = 8388607;
v___x_86_ = lean_uint32_land(v_y_7_, v___x_85_);
v___x_87_ = 8388608;
v___x_88_ = lean_uint32_lor(v___x_86_, v___x_87_);
v___x_89_ = lean_uint32_to_float32(v___x_88_);
v___x_90_ = lp_competition_R2W01b_scaleTable;
v___x_91_ = 23;
v___x_92_ = lean_uint32_shift_right(v_y_7_, v___x_91_);
v___x_93_ = lean_uint32_to_nat(v___x_92_);
v___x_94_ = lean_array_fget_borrowed(v___x_90_, v___x_93_);
lean_dec(v___x_93_);
v___x_95_ = lean_unbox_float32(v___x_94_);
v___x_96_ = lean_float32_mul(v___x_89_, v___x_95_);
v___y_67_ = v___y_82_;
v___y_68_ = v___x_96_;
goto v___jp_66_;
}
}
v___jp_97_:
{
uint32_t v___x_99_; uint32_t v_a_100_; uint32_t v___x_101_; uint32_t v___x_102_; uint32_t v___x_103_; uint8_t v___x_104_; 
v___x_99_ = 2147483647;
v_a_100_ = lean_uint32_land(v_y_7_, v___x_99_);
v___x_101_ = 201326591;
v___x_102_ = 1;
v___x_103_ = lean_uint32_sub(v_a_100_, v___x_102_);
v___x_104_ = lean_uint32_dec_le(v___x_101_, v___x_103_);
if (v___x_104_ == 0)
{
v___y_82_ = v___y_98_;
v___y_83_ = v___x_104_;
goto v___jp_81_;
}
else
{
uint32_t v___x_105_; uint8_t v___x_106_; 
v___x_105_ = 2139095040;
v___x_106_ = lean_uint32_dec_lt(v_a_100_, v___x_105_);
v___y_82_ = v___y_98_;
v___y_83_ = v___x_106_;
goto v___jp_81_;
}
}
v___jp_107_:
{
if (v___y_108_ == 0)
{
float v___x_109_; 
v___x_109_ = lean_float32_of_bits(v_x_6_);
v___y_98_ = v___x_109_;
goto v___jp_97_;
}
else
{
uint32_t v___x_110_; uint32_t v___x_111_; uint32_t v___x_112_; uint32_t v___x_113_; float v___x_114_; lean_object* v___x_115_; uint32_t v___x_116_; uint32_t v___x_117_; lean_object* v___x_118_; lean_object* v___x_119_; float v___x_120_; float v___x_121_; 
v___x_110_ = 8388607;
v___x_111_ = lean_uint32_land(v_x_6_, v___x_110_);
v___x_112_ = 8388608;
v___x_113_ = lean_uint32_lor(v___x_111_, v___x_112_);
v___x_114_ = lean_uint32_to_float32(v___x_113_);
v___x_115_ = lp_competition_R2W01b_scaleTable;
v___x_116_ = 23;
v___x_117_ = lean_uint32_shift_right(v_x_6_, v___x_116_);
v___x_118_ = lean_uint32_to_nat(v___x_117_);
v___x_119_ = lean_array_fget_borrowed(v___x_115_, v___x_118_);
lean_dec(v___x_118_);
v___x_120_ = lean_unbox_float32(v___x_119_);
v___x_121_ = lean_float32_mul(v___x_114_, v___x_120_);
v___y_98_ = v___x_121_;
goto v___jp_97_;
}
}
v___jp_122_:
{
uint32_t v___x_123_; uint32_t v_a_124_; uint32_t v___x_125_; uint32_t v___x_126_; uint32_t v___x_127_; uint8_t v___x_128_; 
v___x_123_ = 2147483647;
v_a_124_ = lean_uint32_land(v_x_6_, v___x_123_);
v___x_125_ = 201326591;
v___x_126_ = 1;
v___x_127_ = lean_uint32_sub(v_a_124_, v___x_126_);
v___x_128_ = lean_uint32_dec_le(v___x_125_, v___x_127_);
if (v___x_128_ == 0)
{
v___y_108_ = v___x_128_;
goto v___jp_107_;
}
else
{
uint32_t v___x_129_; uint8_t v___x_130_; 
v___x_129_ = 2139095040;
v___x_130_ = lean_uint32_dec_lt(v_a_124_, v___x_129_);
v___y_108_ = v___x_130_;
goto v___jp_107_;
}
}
v___jp_135_:
{
uint32_t v_e_140_; uint32_t v___x_141_; uint32_t v_s_142_; uint8_t v___x_143_; 
v_e_140_ = lean_uint32_add(v_eu_134_, v___y_136_);
v___x_141_ = 2147483648;
v_s_142_ = lean_uint32_land(v_x_6_, v___x_141_);
v___x_143_ = lean_uint32_dec_le(v___x_133_, v_e_140_);
if (v___x_143_ == 0)
{
uint32_t v___x_144_; uint32_t v___x_145_; uint32_t v___x_146_; uint32_t v___x_147_; uint32_t v_m_148_; uint32_t v___x_149_; uint32_t v___x_150_; uint32_t v___x_151_; uint32_t v___x_152_; 
v___x_144_ = lean_uint32_add(v___y_139_, v___y_138_);
v___x_145_ = lean_uint32_shift_right(v___y_139_, v___y_138_);
v___x_146_ = lean_uint32_land(v___x_145_, v___y_137_);
v___x_147_ = lean_uint32_add(v___x_144_, v___x_146_);
v_m_148_ = lean_uint32_shift_right(v___x_147_, v___y_138_);
v___x_149_ = lean_uint32_sub(v_e_140_, v___y_137_);
v___x_150_ = lean_uint32_shift_left(v___x_149_, v___x_131_);
v___x_151_ = lean_uint32_add(v___x_150_, v_m_148_);
v___x_152_ = lean_uint32_lor(v_s_142_, v___x_151_);
return v___x_152_;
}
else
{
uint32_t v___x_153_; uint32_t v___x_154_; 
v___x_153_ = 2139095040;
v___x_154_ = lean_uint32_lor(v_s_142_, v___x_153_);
return v___x_154_;
}
}
v___jp_155_:
{
uint32_t v___x_163_; uint32_t v___x_164_; uint32_t v_t_165_; uint32_t v___x_166_; uint32_t v_carry_167_; uint8_t v___x_168_; 
v___x_163_ = lean_uint32_shift_right(v___y_161_, v___y_159_);
v___x_164_ = lean_uint32_lor(v___x_163_, v___y_162_);
v_t_165_ = lean_uint32_add(v___y_156_, v___x_164_);
v___x_166_ = 27;
v_carry_167_ = lean_uint32_shift_right(v_t_165_, v___x_166_);
v___x_168_ = lean_uint32_dec_eq(v_carry_167_, v___y_160_);
if (v___x_168_ == 0)
{
uint32_t v___x_169_; uint32_t v___x_170_; uint32_t v___x_171_; 
v___x_169_ = lean_uint32_shift_right(v_t_165_, v___y_157_);
v___x_170_ = lean_uint32_land(v_t_165_, v___y_157_);
v___x_171_ = lean_uint32_lor(v___x_169_, v___x_170_);
v___y_136_ = v_carry_167_;
v___y_137_ = v___y_157_;
v___y_138_ = v___y_158_;
v___y_139_ = v___x_171_;
goto v___jp_135_;
}
else
{
v___y_136_ = v_carry_167_;
v___y_137_ = v___y_157_;
v___y_138_ = v___y_158_;
v___y_139_ = v_t_165_;
goto v___jp_135_;
}
}
v___jp_174_:
{
uint32_t v_e_179_; uint32_t v___x_180_; uint32_t v_s_181_; uint8_t v___x_182_; 
v_e_179_ = lean_uint32_add(v_ev_173_, v___y_177_);
v___x_180_ = 2147483648;
v_s_181_ = lean_uint32_land(v_y_7_, v___x_180_);
v___x_182_ = lean_uint32_dec_le(v___x_133_, v_e_179_);
if (v___x_182_ == 0)
{
uint32_t v___x_183_; uint32_t v___x_184_; uint32_t v___x_185_; uint32_t v___x_186_; uint32_t v_m_187_; uint32_t v___x_188_; uint32_t v___x_189_; uint32_t v___x_190_; uint32_t v___x_191_; 
v___x_183_ = lean_uint32_add(v___y_178_, v___y_175_);
v___x_184_ = lean_uint32_shift_right(v___y_178_, v___y_175_);
v___x_185_ = lean_uint32_land(v___x_184_, v___y_176_);
v___x_186_ = lean_uint32_add(v___x_183_, v___x_185_);
v_m_187_ = lean_uint32_shift_right(v___x_186_, v___y_175_);
v___x_188_ = lean_uint32_sub(v_e_179_, v___y_176_);
v___x_189_ = lean_uint32_shift_left(v___x_188_, v___x_131_);
v___x_190_ = lean_uint32_add(v___x_189_, v_m_187_);
v___x_191_ = lean_uint32_lor(v_s_181_, v___x_190_);
return v___x_191_;
}
else
{
uint32_t v___x_192_; uint32_t v___x_193_; 
v___x_192_ = 2139095040;
v___x_193_ = lean_uint32_lor(v_s_181_, v___x_192_);
return v___x_193_;
}
}
v___jp_194_:
{
uint32_t v___x_202_; uint32_t v___x_203_; uint32_t v_t_204_; uint32_t v___x_205_; uint32_t v_carry_206_; uint8_t v___x_207_; 
v___x_202_ = lean_uint32_shift_right(v___y_200_, v___y_196_);
v___x_203_ = lean_uint32_lor(v___x_202_, v___y_201_);
v_t_204_ = lean_uint32_add(v___y_198_, v___x_203_);
v___x_205_ = 27;
v_carry_206_ = lean_uint32_shift_right(v_t_204_, v___x_205_);
v___x_207_ = lean_uint32_dec_eq(v_carry_206_, v___y_199_);
if (v___x_207_ == 0)
{
uint32_t v___x_208_; uint32_t v___x_209_; uint32_t v___x_210_; 
v___x_208_ = lean_uint32_shift_right(v_t_204_, v___y_197_);
v___x_209_ = lean_uint32_land(v_t_204_, v___y_197_);
v___x_210_ = lean_uint32_lor(v___x_208_, v___x_209_);
v___y_175_ = v___y_195_;
v___y_176_ = v___y_197_;
v___y_177_ = v_carry_206_;
v___y_178_ = v___x_210_;
goto v___jp_174_;
}
else
{
v___y_175_ = v___y_195_;
v___y_176_ = v___y_197_;
v___y_177_ = v_carry_206_;
v___y_178_ = v_t_204_;
goto v___jp_174_;
}
}
v___jp_211_:
{
if (v___y_212_ == 0)
{
goto v___jp_122_;
}
else
{
uint32_t v___x_213_; uint32_t v___x_214_; uint32_t v___x_215_; uint8_t v___x_216_; 
v___x_213_ = 1;
v___x_214_ = lean_uint32_sub(v_ev_173_, v___x_213_);
v___x_215_ = 254;
v___x_216_ = lean_uint32_dec_lt(v___x_214_, v___x_215_);
if (v___x_216_ == 0)
{
goto v___jp_122_;
}
else
{
uint8_t v___x_217_; 
v___x_217_ = lean_uint32_dec_lt(v_eu_134_, v_ev_173_);
if (v___x_217_ == 0)
{
uint32_t v___x_218_; uint32_t v___x_219_; uint8_t v___x_220_; 
v___x_218_ = lean_uint32_sub(v_eu_134_, v_ev_173_);
v___x_219_ = 25;
v___x_220_ = lean_uint32_dec_le(v___x_219_, v___x_218_);
if (v___x_220_ == 0)
{
uint32_t v___x_221_; uint32_t v___x_222_; uint32_t v___x_223_; uint32_t v___x_224_; uint32_t v___x_225_; uint32_t v_a_226_; uint32_t v___x_227_; uint32_t v___x_228_; uint32_t v_b_229_; uint32_t v___x_230_; uint32_t v_mask_231_; uint32_t v___x_232_; uint32_t v___x_233_; uint8_t v___x_234_; 
v___x_221_ = 8388607;
v___x_222_ = lean_uint32_land(v_x_6_, v___x_221_);
v___x_223_ = 8388608;
v___x_224_ = lean_uint32_lor(v___x_222_, v___x_223_);
v___x_225_ = 3;
v_a_226_ = lean_uint32_shift_left(v___x_224_, v___x_225_);
v___x_227_ = lean_uint32_land(v_y_7_, v___x_221_);
v___x_228_ = lean_uint32_lor(v___x_227_, v___x_223_);
v_b_229_ = lean_uint32_shift_left(v___x_228_, v___x_225_);
v___x_230_ = lean_uint32_shift_left(v___x_213_, v___x_218_);
v_mask_231_ = lean_uint32_sub(v___x_230_, v___x_213_);
v___x_232_ = lean_uint32_land(v_b_229_, v_mask_231_);
v___x_233_ = 0;
v___x_234_ = lean_uint32_dec_eq(v___x_232_, v___x_233_);
if (v___x_234_ == 0)
{
v___y_156_ = v_a_226_;
v___y_157_ = v___x_213_;
v___y_158_ = v___x_225_;
v___y_159_ = v___x_218_;
v___y_160_ = v___x_233_;
v___y_161_ = v_b_229_;
v___y_162_ = v___x_213_;
goto v___jp_155_;
}
else
{
v___y_156_ = v_a_226_;
v___y_157_ = v___x_213_;
v___y_158_ = v___x_225_;
v___y_159_ = v___x_218_;
v___y_160_ = v___x_233_;
v___y_161_ = v_b_229_;
v___y_162_ = v___x_233_;
goto v___jp_155_;
}
}
else
{
return v_x_6_;
}
}
else
{
uint32_t v___x_235_; uint32_t v___x_236_; uint8_t v___x_237_; 
v___x_235_ = lean_uint32_sub(v_ev_173_, v_eu_134_);
v___x_236_ = 25;
v___x_237_ = lean_uint32_dec_le(v___x_236_, v___x_235_);
if (v___x_237_ == 0)
{
uint32_t v___x_238_; uint32_t v___x_239_; uint32_t v___x_240_; uint32_t v___x_241_; uint32_t v___x_242_; uint32_t v_a_243_; uint32_t v___x_244_; uint32_t v___x_245_; uint32_t v_b_246_; uint32_t v___x_247_; uint32_t v_mask_248_; uint32_t v___x_249_; uint32_t v___x_250_; uint8_t v___x_251_; 
v___x_238_ = 8388607;
v___x_239_ = lean_uint32_land(v_y_7_, v___x_238_);
v___x_240_ = 8388608;
v___x_241_ = lean_uint32_lor(v___x_239_, v___x_240_);
v___x_242_ = 3;
v_a_243_ = lean_uint32_shift_left(v___x_241_, v___x_242_);
v___x_244_ = lean_uint32_land(v_x_6_, v___x_238_);
v___x_245_ = lean_uint32_lor(v___x_244_, v___x_240_);
v_b_246_ = lean_uint32_shift_left(v___x_245_, v___x_242_);
v___x_247_ = lean_uint32_shift_left(v___x_213_, v___x_235_);
v_mask_248_ = lean_uint32_sub(v___x_247_, v___x_213_);
v___x_249_ = lean_uint32_land(v_b_246_, v_mask_248_);
v___x_250_ = 0;
v___x_251_ = lean_uint32_dec_eq(v___x_249_, v___x_250_);
if (v___x_251_ == 0)
{
v___y_195_ = v___x_242_;
v___y_196_ = v___x_235_;
v___y_197_ = v___x_213_;
v___y_198_ = v_a_243_;
v___y_199_ = v___x_250_;
v___y_200_ = v_b_246_;
v___y_201_ = v___x_213_;
goto v___jp_194_;
}
else
{
v___y_195_ = v___x_242_;
v___y_196_ = v___x_235_;
v___y_197_ = v___x_213_;
v___y_198_ = v_a_243_;
v___y_199_ = v___x_250_;
v___y_200_ = v_b_246_;
v___y_201_ = v___x_250_;
goto v___jp_194_;
}
}
else
{
return v_y_7_;
}
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_r22CostBroadWordAdd___boxed(lean_object* v_x_259_, lean_object* v_y_260_){
_start:
{
uint32_t v_x_boxed_261_; uint32_t v_y_boxed_262_; uint32_t v_res_263_; lean_object* v_r_264_; 
v_x_boxed_261_ = lean_unbox_uint32(v_x_259_);
lean_dec(v_x_259_);
v_y_boxed_262_ = lean_unbox_uint32(v_y_260_);
lean_dec(v_y_260_);
v_res_263_ = lp_competition_r22CostBroadWordAdd(v_x_boxed_261_, v_y_boxed_262_);
v_r_264_ = lean_box_uint32(v_res_263_);
return v_r_264_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t v___y_265_, uint32_t v___y_266_){
_start:
{
uint8_t v___y_273_; uint8_t v___y_287_; uint8_t v___y_301_; uint8_t v___y_318_; float v___y_325_; float v___y_326_; float v___y_340_; uint8_t v___y_341_; float v___y_356_; uint8_t v___y_366_; uint32_t v___x_389_; uint32_t v___x_390_; uint32_t v___x_391_; uint32_t v_eu_392_; uint32_t v___y_394_; uint32_t v___y_395_; uint32_t v___y_396_; uint32_t v___y_397_; uint32_t v___y_414_; uint32_t v___y_415_; uint32_t v___y_416_; uint32_t v___y_417_; uint32_t v___y_418_; uint32_t v___y_419_; uint32_t v___y_420_; uint32_t v___x_430_; uint32_t v_ev_431_; uint32_t v___y_433_; uint32_t v___y_434_; uint32_t v___y_435_; uint32_t v___y_436_; uint32_t v___y_453_; uint32_t v___y_454_; uint32_t v___y_455_; uint32_t v___y_456_; uint32_t v___y_457_; uint32_t v___y_458_; uint32_t v___y_459_; uint8_t v___y_470_; uint32_t v___x_510_; uint32_t v___x_511_; uint8_t v___x_512_; 
v___x_389_ = 23;
v___x_390_ = lean_uint32_shift_right(v___y_265_, v___x_389_);
v___x_391_ = 255;
v_eu_392_ = lean_uint32_land(v___x_390_, v___x_391_);
v___x_430_ = lean_uint32_shift_right(v___y_266_, v___x_389_);
v_ev_431_ = lean_uint32_land(v___x_430_, v___x_391_);
v___x_510_ = lean_uint32_xor(v___y_265_, v___y_266_);
v___x_511_ = 2147483648;
v___x_512_ = lean_uint32_dec_lt(v___x_510_, v___x_511_);
if (v___x_512_ == 0)
{
v___y_470_ = v___x_512_;
goto v___jp_469_;
}
else
{
uint32_t v___x_513_; uint32_t v___x_514_; uint32_t v___x_515_; uint8_t v___x_516_; 
v___x_513_ = 1;
v___x_514_ = lean_uint32_sub(v_eu_392_, v___x_513_);
v___x_515_ = 254;
v___x_516_ = lean_uint32_dec_lt(v___x_514_, v___x_515_);
v___y_470_ = v___x_516_;
goto v___jp_469_;
}
v___jp_267_:
{
lean_object* v___x_268_; lean_object* v___x_269_; lean_object* v___x_270_; uint32_t v___x_271_; 
v___x_268_ = lean_uint32_to_nat(v___y_265_);
v___x_269_ = lean_uint32_to_nat(v___y_266_);
v___x_270_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_268_, v___x_269_);
v___x_271_ = lean_uint32_of_nat(v___x_270_);
lean_dec(v___x_270_);
return v___x_271_;
}
v___jp_272_:
{
if (v___y_273_ == 0)
{
goto v___jp_267_;
}
else
{
uint32_t v___x_274_; uint32_t v___x_275_; 
v___x_274_ = 4194304;
v___x_275_ = lean_uint32_lor(v___y_266_, v___x_274_);
return v___x_275_;
}
}
v___jp_276_:
{
uint32_t v___x_277_; uint32_t v___x_278_; uint32_t v___x_279_; uint32_t v___x_280_; uint8_t v___x_281_; 
v___x_277_ = 23;
v___x_278_ = lean_uint32_shift_right(v___y_266_, v___x_277_);
v___x_279_ = 255;
v___x_280_ = lean_uint32_land(v___x_278_, v___x_279_);
v___x_281_ = lean_uint32_dec_eq(v___x_280_, v___x_279_);
if (v___x_281_ == 0)
{
v___y_273_ = v___x_281_;
goto v___jp_272_;
}
else
{
uint32_t v___x_282_; uint32_t v___x_283_; uint32_t v___x_284_; uint8_t v___x_285_; 
v___x_282_ = 8388607;
v___x_283_ = lean_uint32_land(v___y_266_, v___x_282_);
v___x_284_ = 0;
v___x_285_ = lean_uint32_dec_eq(v___x_283_, v___x_284_);
if (v___x_285_ == 0)
{
v___y_273_ = v___x_281_;
goto v___jp_272_;
}
else
{
goto v___jp_267_;
}
}
}
v___jp_286_:
{
if (v___y_287_ == 0)
{
goto v___jp_276_;
}
else
{
uint32_t v___x_288_; uint32_t v___x_289_; 
v___x_288_ = 4194304;
v___x_289_ = lean_uint32_lor(v___y_265_, v___x_288_);
return v___x_289_;
}
}
v___jp_290_:
{
uint32_t v___x_291_; uint32_t v___x_292_; uint32_t v___x_293_; uint32_t v___x_294_; uint8_t v___x_295_; 
v___x_291_ = 23;
v___x_292_ = lean_uint32_shift_right(v___y_265_, v___x_291_);
v___x_293_ = 255;
v___x_294_ = lean_uint32_land(v___x_292_, v___x_293_);
v___x_295_ = lean_uint32_dec_eq(v___x_294_, v___x_293_);
if (v___x_295_ == 0)
{
v___y_287_ = v___x_295_;
goto v___jp_286_;
}
else
{
uint32_t v___x_296_; uint32_t v___x_297_; uint32_t v___x_298_; uint8_t v___x_299_; 
v___x_296_ = 8388607;
v___x_297_ = lean_uint32_land(v___y_265_, v___x_296_);
v___x_298_ = 0;
v___x_299_ = lean_uint32_dec_eq(v___x_297_, v___x_298_);
if (v___x_299_ == 0)
{
v___y_287_ = v___x_295_;
goto v___jp_286_;
}
else
{
goto v___jp_276_;
}
}
}
v___jp_300_:
{
if (v___y_301_ == 0)
{
goto v___jp_290_;
}
else
{
uint32_t v___x_302_; uint32_t v___x_303_; uint32_t v___x_304_; uint8_t v___x_305_; 
v___x_302_ = 4194304;
v___x_303_ = lean_uint32_land(v___y_266_, v___x_302_);
v___x_304_ = 0;
v___x_305_ = lean_uint32_dec_eq(v___x_303_, v___x_304_);
if (v___x_305_ == 0)
{
goto v___jp_290_;
}
else
{
uint32_t v___x_306_; 
v___x_306_ = lean_uint32_lor(v___y_266_, v___x_302_);
return v___x_306_;
}
}
}
v___jp_307_:
{
uint32_t v___x_308_; uint32_t v___x_309_; uint32_t v___x_310_; uint32_t v___x_311_; uint8_t v___x_312_; 
v___x_308_ = 23;
v___x_309_ = lean_uint32_shift_right(v___y_266_, v___x_308_);
v___x_310_ = 255;
v___x_311_ = lean_uint32_land(v___x_309_, v___x_310_);
v___x_312_ = lean_uint32_dec_eq(v___x_311_, v___x_310_);
if (v___x_312_ == 0)
{
v___y_301_ = v___x_312_;
goto v___jp_300_;
}
else
{
uint32_t v___x_313_; uint32_t v___x_314_; uint32_t v___x_315_; uint8_t v___x_316_; 
v___x_313_ = 8388607;
v___x_314_ = lean_uint32_land(v___y_266_, v___x_313_);
v___x_315_ = 0;
v___x_316_ = lean_uint32_dec_eq(v___x_314_, v___x_315_);
if (v___x_316_ == 0)
{
v___y_301_ = v___x_312_;
goto v___jp_300_;
}
else
{
goto v___jp_290_;
}
}
}
v___jp_317_:
{
if (v___y_318_ == 0)
{
goto v___jp_307_;
}
else
{
uint32_t v___x_319_; uint32_t v___x_320_; uint32_t v___x_321_; uint8_t v___x_322_; 
v___x_319_ = 4194304;
v___x_320_ = lean_uint32_land(v___y_265_, v___x_319_);
v___x_321_ = 0;
v___x_322_ = lean_uint32_dec_eq(v___x_320_, v___x_321_);
if (v___x_322_ == 0)
{
goto v___jp_307_;
}
else
{
uint32_t v___x_323_; 
v___x_323_ = lean_uint32_lor(v___y_265_, v___x_319_);
return v___x_323_;
}
}
}
v___jp_324_:
{
float v_result_327_; uint8_t v___x_328_; 
v_result_327_ = lean_float32_add(v___y_325_, v___y_326_);
v___x_328_ = lean_float32_beq(v_result_327_, v_result_327_);
if (v___x_328_ == 0)
{
uint32_t v___x_329_; uint32_t v___x_330_; uint32_t v___x_331_; uint32_t v___x_332_; uint8_t v___x_333_; 
v___x_329_ = 23;
v___x_330_ = lean_uint32_shift_right(v___y_265_, v___x_329_);
v___x_331_ = 255;
v___x_332_ = lean_uint32_land(v___x_330_, v___x_331_);
v___x_333_ = lean_uint32_dec_eq(v___x_332_, v___x_331_);
if (v___x_333_ == 0)
{
v___y_318_ = v___x_333_;
goto v___jp_317_;
}
else
{
uint32_t v___x_334_; uint32_t v___x_335_; uint32_t v___x_336_; uint8_t v___x_337_; 
v___x_334_ = 8388607;
v___x_335_ = lean_uint32_land(v___y_265_, v___x_334_);
v___x_336_ = 0;
v___x_337_ = lean_uint32_dec_eq(v___x_335_, v___x_336_);
if (v___x_337_ == 0)
{
v___y_318_ = v___x_333_;
goto v___jp_317_;
}
else
{
goto v___jp_307_;
}
}
}
else
{
uint32_t v___x_338_; 
v___x_338_ = lean_float32_to_bits(v_result_327_);
return v___x_338_;
}
}
v___jp_339_:
{
if (v___y_341_ == 0)
{
float v___x_342_; 
v___x_342_ = lean_float32_of_bits(v___y_266_);
v___y_325_ = v___y_340_;
v___y_326_ = v___x_342_;
goto v___jp_324_;
}
else
{
uint32_t v___x_343_; uint32_t v___x_344_; uint32_t v___x_345_; uint32_t v___x_346_; float v___x_347_; lean_object* v___x_348_; uint32_t v___x_349_; uint32_t v___x_350_; lean_object* v___x_351_; lean_object* v___x_352_; float v___x_353_; float v___x_354_; 
v___x_343_ = 8388607;
v___x_344_ = lean_uint32_land(v___y_266_, v___x_343_);
v___x_345_ = 8388608;
v___x_346_ = lean_uint32_lor(v___x_344_, v___x_345_);
v___x_347_ = lean_uint32_to_float32(v___x_346_);
v___x_348_ = lp_competition_R2W01b_scaleTable;
v___x_349_ = 23;
v___x_350_ = lean_uint32_shift_right(v___y_266_, v___x_349_);
v___x_351_ = lean_uint32_to_nat(v___x_350_);
v___x_352_ = lean_array_fget_borrowed(v___x_348_, v___x_351_);
lean_dec(v___x_351_);
v___x_353_ = lean_unbox_float32(v___x_352_);
v___x_354_ = lean_float32_mul(v___x_347_, v___x_353_);
v___y_325_ = v___y_340_;
v___y_326_ = v___x_354_;
goto v___jp_324_;
}
}
v___jp_355_:
{
uint32_t v___x_357_; uint32_t v_a_358_; uint32_t v___x_359_; uint32_t v___x_360_; uint32_t v___x_361_; uint8_t v___x_362_; 
v___x_357_ = 2147483647;
v_a_358_ = lean_uint32_land(v___y_266_, v___x_357_);
v___x_359_ = 201326591;
v___x_360_ = 1;
v___x_361_ = lean_uint32_sub(v_a_358_, v___x_360_);
v___x_362_ = lean_uint32_dec_le(v___x_359_, v___x_361_);
if (v___x_362_ == 0)
{
v___y_340_ = v___y_356_;
v___y_341_ = v___x_362_;
goto v___jp_339_;
}
else
{
uint32_t v___x_363_; uint8_t v___x_364_; 
v___x_363_ = 2139095040;
v___x_364_ = lean_uint32_dec_lt(v_a_358_, v___x_363_);
v___y_340_ = v___y_356_;
v___y_341_ = v___x_364_;
goto v___jp_339_;
}
}
v___jp_365_:
{
if (v___y_366_ == 0)
{
float v___x_367_; 
v___x_367_ = lean_float32_of_bits(v___y_265_);
v___y_356_ = v___x_367_;
goto v___jp_355_;
}
else
{
uint32_t v___x_368_; uint32_t v___x_369_; uint32_t v___x_370_; uint32_t v___x_371_; float v___x_372_; lean_object* v___x_373_; uint32_t v___x_374_; uint32_t v___x_375_; lean_object* v___x_376_; lean_object* v___x_377_; float v___x_378_; float v___x_379_; 
v___x_368_ = 8388607;
v___x_369_ = lean_uint32_land(v___y_265_, v___x_368_);
v___x_370_ = 8388608;
v___x_371_ = lean_uint32_lor(v___x_369_, v___x_370_);
v___x_372_ = lean_uint32_to_float32(v___x_371_);
v___x_373_ = lp_competition_R2W01b_scaleTable;
v___x_374_ = 23;
v___x_375_ = lean_uint32_shift_right(v___y_265_, v___x_374_);
v___x_376_ = lean_uint32_to_nat(v___x_375_);
v___x_377_ = lean_array_fget_borrowed(v___x_373_, v___x_376_);
lean_dec(v___x_376_);
v___x_378_ = lean_unbox_float32(v___x_377_);
v___x_379_ = lean_float32_mul(v___x_372_, v___x_378_);
v___y_356_ = v___x_379_;
goto v___jp_355_;
}
}
v___jp_380_:
{
uint32_t v___x_381_; uint32_t v_a_382_; uint32_t v___x_383_; uint32_t v___x_384_; uint32_t v___x_385_; uint8_t v___x_386_; 
v___x_381_ = 2147483647;
v_a_382_ = lean_uint32_land(v___y_265_, v___x_381_);
v___x_383_ = 201326591;
v___x_384_ = 1;
v___x_385_ = lean_uint32_sub(v_a_382_, v___x_384_);
v___x_386_ = lean_uint32_dec_le(v___x_383_, v___x_385_);
if (v___x_386_ == 0)
{
v___y_366_ = v___x_386_;
goto v___jp_365_;
}
else
{
uint32_t v___x_387_; uint8_t v___x_388_; 
v___x_387_ = 2139095040;
v___x_388_ = lean_uint32_dec_lt(v_a_382_, v___x_387_);
v___y_366_ = v___x_388_;
goto v___jp_365_;
}
}
v___jp_393_:
{
uint32_t v_e_398_; uint32_t v___x_399_; uint32_t v_s_400_; uint8_t v___x_401_; 
v_e_398_ = lean_uint32_add(v_eu_392_, v___y_396_);
v___x_399_ = 2147483648;
v_s_400_ = lean_uint32_land(v___y_265_, v___x_399_);
v___x_401_ = lean_uint32_dec_le(v___x_391_, v_e_398_);
if (v___x_401_ == 0)
{
uint32_t v___x_402_; uint32_t v___x_403_; uint32_t v___x_404_; uint32_t v___x_405_; uint32_t v_m_406_; uint32_t v___x_407_; uint32_t v___x_408_; uint32_t v___x_409_; uint32_t v___x_410_; 
v___x_402_ = lean_uint32_add(v___y_397_, v___y_394_);
v___x_403_ = lean_uint32_shift_right(v___y_397_, v___y_394_);
v___x_404_ = lean_uint32_land(v___x_403_, v___y_395_);
v___x_405_ = lean_uint32_add(v___x_402_, v___x_404_);
v_m_406_ = lean_uint32_shift_right(v___x_405_, v___y_394_);
v___x_407_ = lean_uint32_sub(v_e_398_, v___y_395_);
v___x_408_ = lean_uint32_shift_left(v___x_407_, v___x_389_);
v___x_409_ = lean_uint32_add(v___x_408_, v_m_406_);
v___x_410_ = lean_uint32_lor(v_s_400_, v___x_409_);
return v___x_410_;
}
else
{
uint32_t v___x_411_; uint32_t v___x_412_; 
v___x_411_ = 2139095040;
v___x_412_ = lean_uint32_lor(v_s_400_, v___x_411_);
return v___x_412_;
}
}
v___jp_413_:
{
uint32_t v___x_421_; uint32_t v___x_422_; uint32_t v_t_423_; uint32_t v___x_424_; uint32_t v_carry_425_; uint8_t v___x_426_; 
v___x_421_ = lean_uint32_shift_right(v___y_417_, v___y_415_);
v___x_422_ = lean_uint32_lor(v___x_421_, v___y_420_);
v_t_423_ = lean_uint32_add(v___y_416_, v___x_422_);
v___x_424_ = 27;
v_carry_425_ = lean_uint32_shift_right(v_t_423_, v___x_424_);
v___x_426_ = lean_uint32_dec_eq(v_carry_425_, v___y_419_);
if (v___x_426_ == 0)
{
uint32_t v___x_427_; uint32_t v___x_428_; uint32_t v___x_429_; 
v___x_427_ = lean_uint32_shift_right(v_t_423_, v___y_418_);
v___x_428_ = lean_uint32_land(v_t_423_, v___y_418_);
v___x_429_ = lean_uint32_lor(v___x_427_, v___x_428_);
v___y_394_ = v___y_414_;
v___y_395_ = v___y_418_;
v___y_396_ = v_carry_425_;
v___y_397_ = v___x_429_;
goto v___jp_393_;
}
else
{
v___y_394_ = v___y_414_;
v___y_395_ = v___y_418_;
v___y_396_ = v_carry_425_;
v___y_397_ = v_t_423_;
goto v___jp_393_;
}
}
v___jp_432_:
{
uint32_t v_e_437_; uint32_t v___x_438_; uint32_t v_s_439_; uint8_t v___x_440_; 
v_e_437_ = lean_uint32_add(v_ev_431_, v___y_433_);
v___x_438_ = 2147483648;
v_s_439_ = lean_uint32_land(v___y_266_, v___x_438_);
v___x_440_ = lean_uint32_dec_le(v___x_391_, v_e_437_);
if (v___x_440_ == 0)
{
uint32_t v___x_441_; uint32_t v___x_442_; uint32_t v___x_443_; uint32_t v___x_444_; uint32_t v_m_445_; uint32_t v___x_446_; uint32_t v___x_447_; uint32_t v___x_448_; uint32_t v___x_449_; 
v___x_441_ = lean_uint32_add(v___y_436_, v___y_434_);
v___x_442_ = lean_uint32_shift_right(v___y_436_, v___y_434_);
v___x_443_ = lean_uint32_land(v___x_442_, v___y_435_);
v___x_444_ = lean_uint32_add(v___x_441_, v___x_443_);
v_m_445_ = lean_uint32_shift_right(v___x_444_, v___y_434_);
v___x_446_ = lean_uint32_sub(v_e_437_, v___y_435_);
v___x_447_ = lean_uint32_shift_left(v___x_446_, v___x_389_);
v___x_448_ = lean_uint32_add(v___x_447_, v_m_445_);
v___x_449_ = lean_uint32_lor(v_s_439_, v___x_448_);
return v___x_449_;
}
else
{
uint32_t v___x_450_; uint32_t v___x_451_; 
v___x_450_ = 2139095040;
v___x_451_ = lean_uint32_lor(v_s_439_, v___x_450_);
return v___x_451_;
}
}
v___jp_452_:
{
uint32_t v___x_460_; uint32_t v___x_461_; uint32_t v_t_462_; uint32_t v___x_463_; uint32_t v_carry_464_; uint8_t v___x_465_; 
v___x_460_ = lean_uint32_shift_right(v___y_458_, v___y_454_);
v___x_461_ = lean_uint32_lor(v___x_460_, v___y_459_);
v_t_462_ = lean_uint32_add(v___y_456_, v___x_461_);
v___x_463_ = 27;
v_carry_464_ = lean_uint32_shift_right(v_t_462_, v___x_463_);
v___x_465_ = lean_uint32_dec_eq(v_carry_464_, v___y_453_);
if (v___x_465_ == 0)
{
uint32_t v___x_466_; uint32_t v___x_467_; uint32_t v___x_468_; 
v___x_466_ = lean_uint32_shift_right(v_t_462_, v___y_457_);
v___x_467_ = lean_uint32_land(v_t_462_, v___y_457_);
v___x_468_ = lean_uint32_lor(v___x_466_, v___x_467_);
v___y_433_ = v_carry_464_;
v___y_434_ = v___y_455_;
v___y_435_ = v___y_457_;
v___y_436_ = v___x_468_;
goto v___jp_432_;
}
else
{
v___y_433_ = v_carry_464_;
v___y_434_ = v___y_455_;
v___y_435_ = v___y_457_;
v___y_436_ = v_t_462_;
goto v___jp_432_;
}
}
v___jp_469_:
{
if (v___y_470_ == 0)
{
goto v___jp_380_;
}
else
{
uint32_t v___x_471_; uint32_t v___x_472_; uint32_t v___x_473_; uint8_t v___x_474_; 
v___x_471_ = 1;
v___x_472_ = lean_uint32_sub(v_ev_431_, v___x_471_);
v___x_473_ = 254;
v___x_474_ = lean_uint32_dec_lt(v___x_472_, v___x_473_);
if (v___x_474_ == 0)
{
goto v___jp_380_;
}
else
{
uint8_t v___x_475_; 
v___x_475_ = lean_uint32_dec_lt(v_eu_392_, v_ev_431_);
if (v___x_475_ == 0)
{
uint32_t v___x_476_; uint32_t v___x_477_; uint8_t v___x_478_; 
v___x_476_ = lean_uint32_sub(v_eu_392_, v_ev_431_);
v___x_477_ = 25;
v___x_478_ = lean_uint32_dec_le(v___x_477_, v___x_476_);
if (v___x_478_ == 0)
{
uint32_t v___x_479_; uint32_t v___x_480_; uint32_t v___x_481_; uint32_t v___x_482_; uint32_t v___x_483_; uint32_t v_a_484_; uint32_t v___x_485_; uint32_t v___x_486_; uint32_t v_b_487_; uint32_t v___x_488_; uint32_t v_mask_489_; uint32_t v___x_490_; uint32_t v___x_491_; uint8_t v___x_492_; 
v___x_479_ = 8388607;
v___x_480_ = lean_uint32_land(v___y_265_, v___x_479_);
v___x_481_ = 8388608;
v___x_482_ = lean_uint32_lor(v___x_480_, v___x_481_);
v___x_483_ = 3;
v_a_484_ = lean_uint32_shift_left(v___x_482_, v___x_483_);
v___x_485_ = lean_uint32_land(v___y_266_, v___x_479_);
v___x_486_ = lean_uint32_lor(v___x_485_, v___x_481_);
v_b_487_ = lean_uint32_shift_left(v___x_486_, v___x_483_);
v___x_488_ = lean_uint32_shift_left(v___x_471_, v___x_476_);
v_mask_489_ = lean_uint32_sub(v___x_488_, v___x_471_);
v___x_490_ = lean_uint32_land(v_b_487_, v_mask_489_);
v___x_491_ = 0;
v___x_492_ = lean_uint32_dec_eq(v___x_490_, v___x_491_);
if (v___x_492_ == 0)
{
v___y_414_ = v___x_483_;
v___y_415_ = v___x_476_;
v___y_416_ = v_a_484_;
v___y_417_ = v_b_487_;
v___y_418_ = v___x_471_;
v___y_419_ = v___x_491_;
v___y_420_ = v___x_471_;
goto v___jp_413_;
}
else
{
v___y_414_ = v___x_483_;
v___y_415_ = v___x_476_;
v___y_416_ = v_a_484_;
v___y_417_ = v_b_487_;
v___y_418_ = v___x_471_;
v___y_419_ = v___x_491_;
v___y_420_ = v___x_491_;
goto v___jp_413_;
}
}
else
{
return v___y_265_;
}
}
else
{
uint32_t v___x_493_; uint32_t v___x_494_; uint8_t v___x_495_; 
v___x_493_ = lean_uint32_sub(v_ev_431_, v_eu_392_);
v___x_494_ = 25;
v___x_495_ = lean_uint32_dec_le(v___x_494_, v___x_493_);
if (v___x_495_ == 0)
{
uint32_t v___x_496_; uint32_t v___x_497_; uint32_t v___x_498_; uint32_t v___x_499_; uint32_t v___x_500_; uint32_t v_a_501_; uint32_t v___x_502_; uint32_t v___x_503_; uint32_t v_b_504_; uint32_t v___x_505_; uint32_t v_mask_506_; uint32_t v___x_507_; uint32_t v___x_508_; uint8_t v___x_509_; 
v___x_496_ = 8388607;
v___x_497_ = lean_uint32_land(v___y_266_, v___x_496_);
v___x_498_ = 8388608;
v___x_499_ = lean_uint32_lor(v___x_497_, v___x_498_);
v___x_500_ = 3;
v_a_501_ = lean_uint32_shift_left(v___x_499_, v___x_500_);
v___x_502_ = lean_uint32_land(v___y_265_, v___x_496_);
v___x_503_ = lean_uint32_lor(v___x_502_, v___x_498_);
v_b_504_ = lean_uint32_shift_left(v___x_503_, v___x_500_);
v___x_505_ = lean_uint32_shift_left(v___x_471_, v___x_493_);
v_mask_506_ = lean_uint32_sub(v___x_505_, v___x_471_);
v___x_507_ = lean_uint32_land(v_b_504_, v_mask_506_);
v___x_508_ = 0;
v___x_509_ = lean_uint32_dec_eq(v___x_507_, v___x_508_);
if (v___x_509_ == 0)
{
v___y_453_ = v___x_508_;
v___y_454_ = v___x_493_;
v___y_455_ = v___x_500_;
v___y_456_ = v_a_501_;
v___y_457_ = v___x_471_;
v___y_458_ = v_b_504_;
v___y_459_ = v___x_471_;
goto v___jp_452_;
}
else
{
v___y_453_ = v___x_508_;
v___y_454_ = v___x_493_;
v___y_455_ = v___x_500_;
v___y_456_ = v_a_501_;
v___y_457_ = v___x_471_;
v___y_458_ = v_b_504_;
v___y_459_ = v___x_508_;
goto v___jp_452_;
}
}
else
{
return v___y_266_;
}
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object* v___y_517_, lean_object* v___y_518_){
_start:
{
uint32_t v___y_5083__boxed_519_; uint32_t v___y_5084__boxed_520_; uint32_t v_res_521_; lean_object* v_r_522_; 
v___y_5083__boxed_519_ = lean_unbox_uint32(v___y_517_);
lean_dec(v___y_517_);
v___y_5084__boxed_520_ = lean_unbox_uint32(v___y_518_);
lean_dec(v___y_518_);
v_res_521_ = lp_competition_main___lam__0(v___y_5083__boxed_519_, v___y_5084__boxed_520_);
v_r_522_ = lean_box_uint32(v_res_521_);
return v_r_522_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint8_t v___x_523_, uint32_t v___y_524_, uint32_t v___y_525_){
_start:
{
uint8_t v___y_527_; uint8_t v___y_543_; uint8_t v___y_557_; uint8_t v___y_574_; float v___y_581_; float v___y_582_; float v___y_596_; uint8_t v___y_597_; float v___y_612_; uint32_t v___y_622_; uint32_t v___y_626_; uint32_t v___y_630_; uint32_t v___y_631_; uint32_t v___y_632_; uint8_t v___y_636_; uint64_t v___y_637_; uint32_t v___y_638_; uint64_t v___y_639_; uint32_t v___y_651_; uint32_t v___y_652_; uint32_t v___y_653_; uint8_t v___y_657_; uint64_t v___y_658_; uint32_t v___y_659_; uint64_t v___y_660_; uint32_t v___x_671_; uint32_t v___x_672_; uint8_t v___y_674_; uint32_t v___x_686_; uint32_t v___y_688_; uint32_t v___y_689_; uint32_t v___y_690_; uint32_t v___y_691_; uint8_t v___y_698_; uint32_t v___y_699_; uint32_t v___y_700_; uint32_t v___y_701_; uint8_t v___y_705_; uint64_t v___y_706_; uint64_t v___y_707_; uint32_t v___y_708_; uint64_t v___y_709_; uint8_t v___y_719_; uint8_t v___y_720_; uint64_t v___y_721_; uint64_t v___y_722_; uint32_t v___y_723_; uint64_t v___y_724_; uint8_t v___y_731_; uint64_t v___y_732_; uint64_t v___y_733_; uint32_t v___y_734_; uint64_t v___y_735_; uint8_t v___y_741_; uint64_t v___y_742_; uint64_t v___y_743_; uint64_t v___y_744_; uint32_t v___y_745_; uint64_t v___y_746_; uint8_t v___y_801_; uint64_t v___y_802_; uint64_t v___y_803_; uint64_t v___y_804_; uint64_t v___y_805_; uint32_t v___y_806_; uint64_t v___y_807_; uint8_t v___y_813_; uint64_t v___y_814_; uint64_t v___y_815_; uint64_t v___y_816_; uint64_t v___y_817_; uint64_t v___y_818_; uint32_t v___y_819_; uint64_t v___y_820_; uint64_t v___y_821_; uint8_t v___y_826_; uint64_t v___y_827_; uint64_t v___y_828_; uint64_t v___y_829_; uint64_t v___y_830_; uint32_t v___y_831_; uint64_t v___y_832_; uint8_t v___y_837_; uint64_t v___y_838_; uint64_t v___y_839_; uint64_t v___y_840_; uint64_t v___y_841_; uint64_t v___y_842_; uint64_t v___y_843_; uint32_t v___y_844_; uint64_t v___y_845_; uint8_t v___y_850_; uint64_t v___y_851_; uint64_t v___y_852_; uint64_t v___y_853_; uint64_t v___y_854_; uint32_t v___y_855_; uint64_t v___y_856_; uint8_t v___y_861_; uint64_t v___y_862_; uint64_t v___y_863_; uint64_t v___y_864_; uint64_t v___y_865_; uint64_t v___y_866_; uint64_t v___y_867_; uint32_t v___y_868_; uint64_t v___y_869_; uint8_t v___y_874_; uint64_t v___y_875_; uint64_t v___y_876_; uint64_t v___y_877_; uint64_t v___y_878_; uint32_t v___y_879_; uint64_t v___y_880_; uint8_t v___y_885_; uint64_t v___y_886_; uint64_t v___y_887_; uint64_t v___y_888_; uint64_t v___y_889_; uint64_t v___y_890_; uint64_t v___y_891_; uint32_t v___y_892_; uint64_t v___y_893_; uint8_t v___y_898_; uint64_t v___y_899_; uint64_t v___y_900_; uint64_t v___y_901_; uint64_t v___y_902_; uint32_t v___y_903_; uint64_t v___y_904_; uint8_t v___y_909_; uint64_t v___y_910_; uint64_t v___y_911_; uint64_t v___y_912_; uint64_t v___y_913_; uint32_t v___y_914_; uint64_t v___y_915_; uint8_t v___y_919_; uint64_t v___y_920_; uint64_t v___y_921_; uint32_t v___y_922_; uint8_t v___y_931_; uint64_t v___y_932_; uint64_t v___y_933_; uint64_t v___y_934_; uint32_t v___y_935_; uint64_t v___y_936_; uint32_t v_ex_969_; uint32_t v___x_970_; uint32_t v_ey_971_; uint8_t v___y_973_; uint64_t v___y_974_; uint64_t v___y_975_; uint32_t v___y_976_; uint64_t v___y_977_; uint8_t v___y_984_; uint64_t v___y_985_; uint32_t v___y_986_; uint64_t v___y_987_; uint8_t v___y_994_; uint32_t v___y_995_; uint32_t v___y_996_; uint64_t v___y_997_; uint8_t v___y_1005_; uint8_t v___y_1016_; uint8_t v___y_1017_; uint32_t v___x_1018_; uint32_t v___x_1019_; uint8_t v___x_1020_; uint8_t v___y_1022_; uint8_t v___y_1023_; uint8_t v___y_1024_; uint8_t v___y_1026_; uint8_t v___y_1027_; uint8_t v___y_1033_; 
v___x_671_ = 23;
v___x_672_ = lean_uint32_shift_right(v___y_524_, v___x_671_);
v___x_686_ = 255;
v_ex_969_ = lean_uint32_land(v___x_672_, v___x_686_);
v___x_970_ = lean_uint32_shift_right(v___y_525_, v___x_671_);
v_ey_971_ = lean_uint32_land(v___x_970_, v___x_686_);
v___x_1018_ = lean_uint32_add(v_ex_969_, v_ey_971_);
v___x_1019_ = 128;
v___x_1020_ = lean_uint32_dec_lt(v___x_1018_, v___x_1019_);
if (v___x_1020_ == 0)
{
uint32_t v___x_1042_; uint32_t v_a_1043_; uint32_t v___x_1044_; uint32_t v___x_1045_; uint32_t v___x_1046_; uint8_t v___x_1047_; 
v___x_1042_ = 2147483647;
v_a_1043_ = lean_uint32_land(v___y_524_, v___x_1042_);
v___x_1044_ = 201326591;
v___x_1045_ = 1;
v___x_1046_ = lean_uint32_sub(v_a_1043_, v___x_1045_);
v___x_1047_ = lean_uint32_dec_le(v___x_1044_, v___x_1046_);
if (v___x_1047_ == 0)
{
v___y_674_ = v___x_1047_;
goto v___jp_673_;
}
else
{
uint32_t v___x_1048_; uint8_t v___x_1049_; 
v___x_1048_ = 2139095040;
v___x_1049_ = lean_uint32_dec_lt(v_a_1043_, v___x_1048_);
v___y_674_ = v___x_1049_;
goto v___jp_673_;
}
}
else
{
uint32_t v___x_1050_; uint32_t v___x_1051_; uint32_t v___x_1052_; uint8_t v___x_1053_; 
v___x_1050_ = 4278190080;
v___x_1051_ = 1;
v___x_1052_ = lean_uint32_shift_left(v___y_524_, v___x_1051_);
v___x_1053_ = lean_uint32_dec_le(v___x_1050_, v___x_1052_);
if (v___x_1053_ == 0)
{
uint32_t v___x_1054_; uint8_t v___x_1055_; 
v___x_1054_ = lean_uint32_shift_left(v___y_525_, v___x_1051_);
v___x_1055_ = lean_uint32_dec_le(v___x_1050_, v___x_1054_);
v___y_1033_ = v___x_1055_;
goto v___jp_1032_;
}
else
{
v___y_1033_ = v___x_1053_;
goto v___jp_1032_;
}
}
v___jp_526_:
{
if (v___y_527_ == 0)
{
uint32_t v___x_528_; 
v___x_528_ = lp_competition_Submission_FastMul_mul(v___y_524_, v___y_525_);
return v___x_528_;
}
else
{
uint32_t v___x_529_; uint32_t v___x_530_; 
v___x_529_ = 4194304;
v___x_530_ = lean_uint32_lor(v___y_525_, v___x_529_);
return v___x_530_;
}
}
v___jp_531_:
{
uint32_t v___x_532_; uint32_t v___x_533_; uint32_t v___x_534_; uint32_t v___x_535_; uint8_t v___x_536_; 
v___x_532_ = 23;
v___x_533_ = lean_uint32_shift_right(v___y_525_, v___x_532_);
v___x_534_ = 255;
v___x_535_ = lean_uint32_land(v___x_533_, v___x_534_);
v___x_536_ = lean_uint32_dec_eq(v___x_535_, v___x_534_);
if (v___x_536_ == 0)
{
v___y_527_ = v___x_536_;
goto v___jp_526_;
}
else
{
uint32_t v___x_537_; uint32_t v___x_538_; uint32_t v___x_539_; uint8_t v___x_540_; 
v___x_537_ = 8388607;
v___x_538_ = lean_uint32_land(v___y_525_, v___x_537_);
v___x_539_ = 0;
v___x_540_ = lean_uint32_dec_eq(v___x_538_, v___x_539_);
if (v___x_540_ == 0)
{
v___y_527_ = v___x_536_;
goto v___jp_526_;
}
else
{
uint32_t v___x_541_; 
v___x_541_ = lp_competition_Submission_FastMul_mul(v___y_524_, v___y_525_);
return v___x_541_;
}
}
}
v___jp_542_:
{
if (v___y_543_ == 0)
{
goto v___jp_531_;
}
else
{
uint32_t v___x_544_; uint32_t v___x_545_; 
v___x_544_ = 4194304;
v___x_545_ = lean_uint32_lor(v___y_524_, v___x_544_);
return v___x_545_;
}
}
v___jp_546_:
{
uint32_t v___x_547_; uint32_t v___x_548_; uint32_t v___x_549_; uint32_t v___x_550_; uint8_t v___x_551_; 
v___x_547_ = 23;
v___x_548_ = lean_uint32_shift_right(v___y_524_, v___x_547_);
v___x_549_ = 255;
v___x_550_ = lean_uint32_land(v___x_548_, v___x_549_);
v___x_551_ = lean_uint32_dec_eq(v___x_550_, v___x_549_);
if (v___x_551_ == 0)
{
v___y_543_ = v___x_551_;
goto v___jp_542_;
}
else
{
uint32_t v___x_552_; uint32_t v___x_553_; uint32_t v___x_554_; uint8_t v___x_555_; 
v___x_552_ = 8388607;
v___x_553_ = lean_uint32_land(v___y_524_, v___x_552_);
v___x_554_ = 0;
v___x_555_ = lean_uint32_dec_eq(v___x_553_, v___x_554_);
if (v___x_555_ == 0)
{
v___y_543_ = v___x_551_;
goto v___jp_542_;
}
else
{
goto v___jp_531_;
}
}
}
v___jp_556_:
{
if (v___y_557_ == 0)
{
goto v___jp_546_;
}
else
{
uint32_t v___x_558_; uint32_t v___x_559_; uint32_t v___x_560_; uint8_t v___x_561_; 
v___x_558_ = 4194304;
v___x_559_ = lean_uint32_land(v___y_525_, v___x_558_);
v___x_560_ = 0;
v___x_561_ = lean_uint32_dec_eq(v___x_559_, v___x_560_);
if (v___x_561_ == 0)
{
goto v___jp_546_;
}
else
{
uint32_t v___x_562_; 
v___x_562_ = lean_uint32_lor(v___y_525_, v___x_558_);
return v___x_562_;
}
}
}
v___jp_563_:
{
uint32_t v___x_564_; uint32_t v___x_565_; uint32_t v___x_566_; uint32_t v___x_567_; uint8_t v___x_568_; 
v___x_564_ = 23;
v___x_565_ = lean_uint32_shift_right(v___y_525_, v___x_564_);
v___x_566_ = 255;
v___x_567_ = lean_uint32_land(v___x_565_, v___x_566_);
v___x_568_ = lean_uint32_dec_eq(v___x_567_, v___x_566_);
if (v___x_568_ == 0)
{
v___y_557_ = v___x_568_;
goto v___jp_556_;
}
else
{
uint32_t v___x_569_; uint32_t v___x_570_; uint32_t v___x_571_; uint8_t v___x_572_; 
v___x_569_ = 8388607;
v___x_570_ = lean_uint32_land(v___y_525_, v___x_569_);
v___x_571_ = 0;
v___x_572_ = lean_uint32_dec_eq(v___x_570_, v___x_571_);
if (v___x_572_ == 0)
{
v___y_557_ = v___x_568_;
goto v___jp_556_;
}
else
{
goto v___jp_546_;
}
}
}
v___jp_573_:
{
if (v___y_574_ == 0)
{
goto v___jp_563_;
}
else
{
uint32_t v___x_575_; uint32_t v___x_576_; uint32_t v___x_577_; uint8_t v___x_578_; 
v___x_575_ = 4194304;
v___x_576_ = lean_uint32_land(v___y_524_, v___x_575_);
v___x_577_ = 0;
v___x_578_ = lean_uint32_dec_eq(v___x_576_, v___x_577_);
if (v___x_578_ == 0)
{
goto v___jp_563_;
}
else
{
uint32_t v___x_579_; 
v___x_579_ = lean_uint32_lor(v___y_524_, v___x_575_);
return v___x_579_;
}
}
}
v___jp_580_:
{
float v_result_583_; uint8_t v___x_584_; 
v_result_583_ = lean_float32_mul(v___y_581_, v___y_582_);
v___x_584_ = lean_float32_beq(v_result_583_, v_result_583_);
if (v___x_584_ == 0)
{
uint32_t v___x_585_; uint32_t v___x_586_; uint32_t v___x_587_; uint32_t v___x_588_; uint8_t v___x_589_; 
v___x_585_ = 23;
v___x_586_ = lean_uint32_shift_right(v___y_524_, v___x_585_);
v___x_587_ = 255;
v___x_588_ = lean_uint32_land(v___x_586_, v___x_587_);
v___x_589_ = lean_uint32_dec_eq(v___x_588_, v___x_587_);
if (v___x_589_ == 0)
{
v___y_574_ = v___x_589_;
goto v___jp_573_;
}
else
{
uint32_t v___x_590_; uint32_t v___x_591_; uint32_t v___x_592_; uint8_t v___x_593_; 
v___x_590_ = 8388607;
v___x_591_ = lean_uint32_land(v___y_524_, v___x_590_);
v___x_592_ = 0;
v___x_593_ = lean_uint32_dec_eq(v___x_591_, v___x_592_);
if (v___x_593_ == 0)
{
v___y_574_ = v___x_589_;
goto v___jp_573_;
}
else
{
goto v___jp_563_;
}
}
}
else
{
uint32_t v___x_594_; 
v___x_594_ = lean_float32_to_bits(v_result_583_);
return v___x_594_;
}
}
v___jp_595_:
{
if (v___y_597_ == 0)
{
float v___x_598_; 
v___x_598_ = lean_float32_of_bits(v___y_525_);
v___y_581_ = v___y_596_;
v___y_582_ = v___x_598_;
goto v___jp_580_;
}
else
{
uint32_t v___x_599_; uint32_t v___x_600_; uint32_t v___x_601_; uint32_t v___x_602_; float v___x_603_; lean_object* v___x_604_; uint32_t v___x_605_; uint32_t v___x_606_; lean_object* v___x_607_; lean_object* v___x_608_; float v___x_609_; float v___x_610_; 
v___x_599_ = 8388607;
v___x_600_ = lean_uint32_land(v___y_525_, v___x_599_);
v___x_601_ = 8388608;
v___x_602_ = lean_uint32_lor(v___x_600_, v___x_601_);
v___x_603_ = lean_uint32_to_float32(v___x_602_);
v___x_604_ = lp_competition_R2W01b_scaleTable;
v___x_605_ = 23;
v___x_606_ = lean_uint32_shift_right(v___y_525_, v___x_605_);
v___x_607_ = lean_uint32_to_nat(v___x_606_);
v___x_608_ = lean_array_fget_borrowed(v___x_604_, v___x_607_);
lean_dec(v___x_607_);
v___x_609_ = lean_unbox_float32(v___x_608_);
v___x_610_ = lean_float32_mul(v___x_603_, v___x_609_);
v___y_581_ = v___y_596_;
v___y_582_ = v___x_610_;
goto v___jp_580_;
}
}
v___jp_611_:
{
uint32_t v___x_613_; uint32_t v_a_614_; uint32_t v___x_615_; uint32_t v___x_616_; uint32_t v___x_617_; uint8_t v___x_618_; 
v___x_613_ = 2147483647;
v_a_614_ = lean_uint32_land(v___y_525_, v___x_613_);
v___x_615_ = 201326591;
v___x_616_ = 1;
v___x_617_ = lean_uint32_sub(v_a_614_, v___x_616_);
v___x_618_ = lean_uint32_dec_le(v___x_615_, v___x_617_);
if (v___x_618_ == 0)
{
v___y_596_ = v___y_612_;
v___y_597_ = v___x_618_;
goto v___jp_595_;
}
else
{
uint32_t v___x_619_; uint8_t v___x_620_; 
v___x_619_ = 2139095040;
v___x_620_ = lean_uint32_dec_lt(v_a_614_, v___x_619_);
v___y_596_ = v___y_612_;
v___y_597_ = v___x_620_;
goto v___jp_595_;
}
}
v___jp_621_:
{
uint32_t v___x_623_; uint32_t v___x_624_; 
v___x_623_ = 8388608;
v___x_624_ = lean_uint32_lor(v___y_622_, v___x_623_);
return v___x_624_;
}
v___jp_625_:
{
uint32_t v___x_627_; uint32_t v___x_628_; 
v___x_627_ = 8388608;
v___x_628_ = lean_uint32_lor(v___y_626_, v___x_627_);
return v___x_628_;
}
v___jp_629_:
{
uint32_t v___x_633_; uint32_t v___x_634_; 
v___x_633_ = lean_uint32_land(v___y_631_, v___y_630_);
v___x_634_ = lean_uint32_lor(v___y_632_, v___x_633_);
return v___x_634_;
}
v___jp_635_:
{
uint8_t v___x_640_; 
v___x_640_ = lean_uint64_dec_eq(v___y_639_, v___y_637_);
if (v___x_640_ == 0)
{
uint64_t v___x_641_; uint8_t v___x_642_; 
v___x_641_ = 8388608ULL;
v___x_642_ = lean_uint64_dec_eq(v___y_639_, v___x_641_);
if (v___x_642_ == 0)
{
uint32_t v___x_643_; 
v___x_643_ = lean_uint64_to_uint32(v___y_639_);
if (v___y_636_ == 0)
{
uint32_t v___x_644_; 
v___x_644_ = 0;
v___y_630_ = v___y_638_;
v___y_631_ = v___x_643_;
v___y_632_ = v___x_644_;
goto v___jp_629_;
}
else
{
uint32_t v___x_645_; 
v___x_645_ = 2147483648;
v___y_630_ = v___y_638_;
v___y_631_ = v___x_643_;
v___y_632_ = v___x_645_;
goto v___jp_629_;
}
}
else
{
if (v___y_636_ == 0)
{
uint32_t v___x_646_; 
v___x_646_ = 0;
v___y_626_ = v___x_646_;
goto v___jp_625_;
}
else
{
uint32_t v___x_647_; 
v___x_647_ = 2147483648;
v___y_626_ = v___x_647_;
goto v___jp_625_;
}
}
}
else
{
if (v___y_636_ == 0)
{
uint32_t v___x_648_; 
v___x_648_ = 0;
return v___x_648_;
}
else
{
uint32_t v___x_649_; 
v___x_649_ = 2147483648;
return v___x_649_;
}
}
}
v___jp_650_:
{
uint32_t v___x_654_; uint32_t v___x_655_; 
v___x_654_ = lean_uint32_land(v___y_651_, v___y_652_);
v___x_655_ = lean_uint32_lor(v___y_653_, v___x_654_);
return v___x_655_;
}
v___jp_656_:
{
uint8_t v___x_661_; 
v___x_661_ = lean_uint64_dec_eq(v___y_660_, v___y_658_);
if (v___x_661_ == 0)
{
uint64_t v___x_662_; uint8_t v___x_663_; 
v___x_662_ = 8388608ULL;
v___x_663_ = lean_uint64_dec_eq(v___y_660_, v___x_662_);
if (v___x_663_ == 0)
{
uint32_t v___x_664_; 
v___x_664_ = lean_uint64_to_uint32(v___y_660_);
if (v___y_657_ == 0)
{
uint32_t v___x_665_; 
v___x_665_ = 0;
v___y_651_ = v___x_664_;
v___y_652_ = v___y_659_;
v___y_653_ = v___x_665_;
goto v___jp_650_;
}
else
{
uint32_t v___x_666_; 
v___x_666_ = 2147483648;
v___y_651_ = v___x_664_;
v___y_652_ = v___y_659_;
v___y_653_ = v___x_666_;
goto v___jp_650_;
}
}
else
{
if (v___y_657_ == 0)
{
uint32_t v___x_667_; 
v___x_667_ = 0;
v___y_622_ = v___x_667_;
goto v___jp_621_;
}
else
{
uint32_t v___x_668_; 
v___x_668_ = 2147483648;
v___y_622_ = v___x_668_;
goto v___jp_621_;
}
}
}
else
{
if (v___y_657_ == 0)
{
uint32_t v___x_669_; 
v___x_669_ = 0;
return v___x_669_;
}
else
{
uint32_t v___x_670_; 
v___x_670_ = 2147483648;
return v___x_670_;
}
}
}
v___jp_673_:
{
if (v___y_674_ == 0)
{
float v___x_675_; 
v___x_675_ = lean_float32_of_bits(v___y_524_);
v___y_612_ = v___x_675_;
goto v___jp_611_;
}
else
{
uint32_t v___x_676_; uint32_t v___x_677_; uint32_t v___x_678_; uint32_t v___x_679_; float v___x_680_; lean_object* v___x_681_; lean_object* v___x_682_; lean_object* v___x_683_; float v___x_684_; float v___x_685_; 
v___x_676_ = 8388607;
v___x_677_ = lean_uint32_land(v___y_524_, v___x_676_);
v___x_678_ = 8388608;
v___x_679_ = lean_uint32_lor(v___x_677_, v___x_678_);
v___x_680_ = lean_uint32_to_float32(v___x_679_);
v___x_681_ = lp_competition_R2W01b_scaleTable;
v___x_682_ = lean_uint32_to_nat(v___x_672_);
v___x_683_ = lean_array_fget_borrowed(v___x_681_, v___x_682_);
lean_dec(v___x_682_);
v___x_684_ = lean_unbox_float32(v___x_683_);
v___x_685_ = lean_float32_mul(v___x_680_, v___x_684_);
v___y_612_ = v___x_685_;
goto v___jp_611_;
}
}
v___jp_687_:
{
uint32_t v___x_692_; uint32_t v___x_693_; uint32_t v___x_694_; uint32_t v___x_695_; uint32_t v___x_696_; 
v___x_692_ = lean_uint32_land(v___y_690_, v___x_686_);
v___x_693_ = lean_uint32_shift_left(v___x_692_, v___x_671_);
v___x_694_ = lean_uint32_lor(v___y_691_, v___x_693_);
v___x_695_ = lean_uint32_land(v___y_688_, v___y_689_);
v___x_696_ = lean_uint32_lor(v___x_694_, v___x_695_);
return v___x_696_;
}
v___jp_697_:
{
if (v___y_698_ == 0)
{
uint32_t v___x_702_; 
v___x_702_ = 0;
v___y_688_ = v___y_701_;
v___y_689_ = v___y_699_;
v___y_690_ = v___y_700_;
v___y_691_ = v___x_702_;
goto v___jp_687_;
}
else
{
uint32_t v___x_703_; 
v___x_703_ = 2147483648;
v___y_688_ = v___y_701_;
v___y_689_ = v___y_699_;
v___y_690_ = v___y_700_;
v___y_691_ = v___x_703_;
goto v___jp_687_;
}
}
v___jp_704_:
{
uint64_t v___x_710_; uint64_t v_encodedExponent_711_; uint32_t v___x_712_; uint64_t v___x_713_; uint8_t v___x_714_; 
v___x_710_ = 171ULL;
v_encodedExponent_711_ = lean_uint64_sub(v___y_706_, v___x_710_);
v___x_712_ = lean_uint64_to_uint32(v_encodedExponent_711_);
v___x_713_ = 8388608ULL;
v___x_714_ = lean_uint64_dec_lt(v___y_709_, v___x_713_);
if (v___x_714_ == 0)
{
uint64_t v___x_715_; uint32_t v___x_716_; 
v___x_715_ = lean_uint64_sub(v___y_709_, v___x_713_);
v___x_716_ = lean_uint64_to_uint32(v___x_715_);
v___y_698_ = v___y_705_;
v___y_699_ = v___y_708_;
v___y_700_ = v___x_712_;
v___y_701_ = v___x_716_;
goto v___jp_697_;
}
else
{
uint32_t v___x_717_; 
v___x_717_ = lean_uint64_to_uint32(v___y_707_);
v___y_698_ = v___y_705_;
v___y_699_ = v___y_708_;
v___y_700_ = v___x_712_;
v___y_701_ = v___x_717_;
goto v___jp_697_;
}
}
v___jp_718_:
{
uint64_t v___x_725_; uint8_t v___x_726_; 
v___x_725_ = 425ULL;
v___x_726_ = lean_uint64_dec_lt(v___x_725_, v___y_724_);
if (v___x_726_ == 0)
{
if (v___y_720_ == 0)
{
v___y_705_ = v___y_719_;
v___y_706_ = v___y_724_;
v___y_707_ = v___y_721_;
v___y_708_ = v___y_723_;
v___y_709_ = v___y_722_;
goto v___jp_704_;
}
else
{
uint64_t v___x_727_; 
v___x_727_ = 8388608ULL;
v___y_705_ = v___y_719_;
v___y_706_ = v___y_724_;
v___y_707_ = v___y_721_;
v___y_708_ = v___y_723_;
v___y_709_ = v___x_727_;
goto v___jp_704_;
}
}
else
{
if (v___y_719_ == 0)
{
uint32_t v___x_728_; 
v___x_728_ = 2139095040;
return v___x_728_;
}
else
{
uint32_t v___x_729_; 
v___x_729_ = 4286578688;
return v___x_729_;
}
}
}
v___jp_730_:
{
uint64_t v___x_736_; uint8_t v_carry_737_; 
v___x_736_ = 16777216ULL;
v_carry_737_ = lean_uint64_dec_eq(v___y_735_, v___x_736_);
if (v_carry_737_ == 0)
{
v___y_719_ = v___y_731_;
v___y_720_ = v_carry_737_;
v___y_721_ = v___y_732_;
v___y_722_ = v___y_735_;
v___y_723_ = v___y_734_;
v___y_724_ = v___y_733_;
goto v___jp_718_;
}
else
{
uint64_t v___x_738_; uint64_t v___x_739_; 
v___x_738_ = 1ULL;
v___x_739_ = lean_uint64_add(v___y_733_, v___x_738_);
v___y_719_ = v___y_731_;
v___y_720_ = v_carry_737_;
v___y_721_ = v___y_732_;
v___y_722_ = v___y_735_;
v___y_723_ = v___y_734_;
v___y_724_ = v___x_739_;
goto v___jp_718_;
}
}
v___jp_740_:
{
uint64_t v_position_747_; uint64_t v___x_748_; uint8_t v___x_749_; 
v_position_747_ = lean_uint64_add(v___y_746_, v___y_744_);
v___x_748_ = 172ULL;
v___x_749_ = lean_uint64_dec_lt(v_position_747_, v___x_748_);
if (v___x_749_ == 0)
{
uint64_t v___x_750_; uint8_t v___x_751_; 
v___x_750_ = 23ULL;
v___x_751_ = lean_uint64_dec_lt(v___y_746_, v___x_750_);
if (v___x_751_ == 0)
{
uint64_t v___x_752_; uint8_t v___x_753_; 
v___x_752_ = lean_uint64_sub(v___y_746_, v___x_750_);
v___x_753_ = lean_uint64_dec_eq(v___x_752_, v___y_742_);
if (v___x_753_ == 0)
{
uint64_t v___x_754_; uint8_t v___x_755_; 
v___x_754_ = 64ULL;
v___x_755_ = lean_uint64_dec_lt(v___x_752_, v___x_754_);
if (v___x_755_ == 0)
{
uint8_t v___x_756_; 
v___x_756_ = lean_uint64_dec_eq(v___x_752_, v___x_754_);
if (v___x_756_ == 0)
{
v___y_731_ = v___y_741_;
v___y_732_ = v___y_742_;
v___y_733_ = v_position_747_;
v___y_734_ = v___y_745_;
v___y_735_ = v___y_742_;
goto v___jp_730_;
}
else
{
uint64_t v___x_757_; uint8_t v___x_758_; 
v___x_757_ = 9223372036854775808ULL;
v___x_758_ = lean_uint64_dec_lt(v___x_757_, v___y_743_);
if (v___x_758_ == 0)
{
v___y_731_ = v___y_741_;
v___y_732_ = v___y_742_;
v___y_733_ = v_position_747_;
v___y_734_ = v___y_745_;
v___y_735_ = v___y_742_;
goto v___jp_730_;
}
else
{
uint64_t v___x_759_; 
v___x_759_ = 1ULL;
v___y_731_ = v___y_741_;
v___y_732_ = v___y_742_;
v___y_733_ = v_position_747_;
v___y_734_ = v___y_745_;
v___y_735_ = v___x_759_;
goto v___jp_730_;
}
}
}
else
{
uint64_t v_quotient_760_; uint64_t v___x_761_; uint64_t v___x_762_; uint64_t v___x_763_; uint64_t v_remainder_764_; uint64_t v___x_765_; uint64_t v_half_766_; uint8_t v___x_767_; 
v_quotient_760_ = lean_uint64_shift_right(v___y_743_, v___x_752_);
v___x_761_ = 1ULL;
v___x_762_ = lean_uint64_shift_left(v___x_761_, v___x_752_);
v___x_763_ = lean_uint64_sub(v___x_762_, v___x_761_);
v_remainder_764_ = lean_uint64_land(v___y_743_, v___x_763_);
v___x_765_ = lean_uint64_sub(v___x_752_, v___x_761_);
v_half_766_ = lean_uint64_shift_left(v___x_761_, v___x_765_);
v___x_767_ = lean_uint64_dec_lt(v_remainder_764_, v_half_766_);
if (v___x_767_ == 0)
{
uint8_t v___x_768_; 
v___x_768_ = lean_uint64_dec_lt(v_half_766_, v_remainder_764_);
if (v___x_768_ == 0)
{
uint64_t v___x_769_; uint8_t v___x_770_; 
v___x_769_ = lean_uint64_land(v_quotient_760_, v___x_761_);
v___x_770_ = lean_uint64_dec_eq(v___x_769_, v___y_742_);
if (v___x_770_ == 0)
{
uint64_t v___x_771_; 
v___x_771_ = lean_uint64_add(v_quotient_760_, v___x_761_);
v___y_731_ = v___y_741_;
v___y_732_ = v___y_742_;
v___y_733_ = v_position_747_;
v___y_734_ = v___y_745_;
v___y_735_ = v___x_771_;
goto v___jp_730_;
}
else
{
v___y_731_ = v___y_741_;
v___y_732_ = v___y_742_;
v___y_733_ = v_position_747_;
v___y_734_ = v___y_745_;
v___y_735_ = v_quotient_760_;
goto v___jp_730_;
}
}
else
{
uint64_t v___x_772_; 
v___x_772_ = lean_uint64_add(v_quotient_760_, v___x_761_);
v___y_731_ = v___y_741_;
v___y_732_ = v___y_742_;
v___y_733_ = v_position_747_;
v___y_734_ = v___y_745_;
v___y_735_ = v___x_772_;
goto v___jp_730_;
}
}
else
{
v___y_731_ = v___y_741_;
v___y_732_ = v___y_742_;
v___y_733_ = v_position_747_;
v___y_734_ = v___y_745_;
v___y_735_ = v_quotient_760_;
goto v___jp_730_;
}
}
}
else
{
v___y_731_ = v___y_741_;
v___y_732_ = v___y_742_;
v___y_733_ = v_position_747_;
v___y_734_ = v___y_745_;
v___y_735_ = v___y_743_;
goto v___jp_730_;
}
}
else
{
uint64_t v___x_773_; uint64_t v___x_774_; 
v___x_773_ = lean_uint64_sub(v___x_750_, v___y_746_);
v___x_774_ = lean_uint64_shift_left(v___y_743_, v___x_773_);
v___y_731_ = v___y_741_;
v___y_732_ = v___y_742_;
v___y_733_ = v_position_747_;
v___y_734_ = v___y_745_;
v___y_735_ = v___x_774_;
goto v___jp_730_;
}
}
else
{
uint64_t v___x_775_; uint8_t v___x_776_; 
v___x_775_ = 149ULL;
v___x_776_ = lean_uint64_dec_lt(v___y_744_, v___x_775_);
if (v___x_776_ == 0)
{
uint64_t v___x_777_; uint64_t v___x_778_; 
v___x_777_ = lean_uint64_sub(v___y_744_, v___x_775_);
v___x_778_ = lean_uint64_shift_left(v___y_743_, v___x_777_);
v___y_636_ = v___y_741_;
v___y_637_ = v___y_742_;
v___y_638_ = v___y_745_;
v___y_639_ = v___x_778_;
goto v___jp_635_;
}
else
{
uint64_t v___x_779_; uint8_t v___x_780_; 
v___x_779_ = lean_uint64_sub(v___x_775_, v___y_744_);
v___x_780_ = lean_uint64_dec_eq(v___x_779_, v___y_742_);
if (v___x_780_ == 0)
{
uint64_t v___x_781_; uint8_t v___x_782_; 
v___x_781_ = 64ULL;
v___x_782_ = lean_uint64_dec_lt(v___x_779_, v___x_781_);
if (v___x_782_ == 0)
{
uint8_t v___x_783_; 
v___x_783_ = lean_uint64_dec_eq(v___x_779_, v___x_781_);
if (v___x_783_ == 0)
{
v___y_636_ = v___y_741_;
v___y_637_ = v___y_742_;
v___y_638_ = v___y_745_;
v___y_639_ = v___y_742_;
goto v___jp_635_;
}
else
{
uint64_t v___x_784_; uint8_t v___x_785_; 
v___x_784_ = 9223372036854775808ULL;
v___x_785_ = lean_uint64_dec_lt(v___x_784_, v___y_743_);
if (v___x_785_ == 0)
{
v___y_636_ = v___y_741_;
v___y_637_ = v___y_742_;
v___y_638_ = v___y_745_;
v___y_639_ = v___y_742_;
goto v___jp_635_;
}
else
{
uint64_t v___x_786_; 
v___x_786_ = 1ULL;
v___y_636_ = v___y_741_;
v___y_637_ = v___y_742_;
v___y_638_ = v___y_745_;
v___y_639_ = v___x_786_;
goto v___jp_635_;
}
}
}
else
{
uint64_t v_quotient_787_; uint64_t v___x_788_; uint64_t v___x_789_; uint64_t v___x_790_; uint64_t v_remainder_791_; uint64_t v___x_792_; uint64_t v_half_793_; uint8_t v___x_794_; 
v_quotient_787_ = lean_uint64_shift_right(v___y_743_, v___x_779_);
v___x_788_ = 1ULL;
v___x_789_ = lean_uint64_shift_left(v___x_788_, v___x_779_);
v___x_790_ = lean_uint64_sub(v___x_789_, v___x_788_);
v_remainder_791_ = lean_uint64_land(v___y_743_, v___x_790_);
v___x_792_ = lean_uint64_sub(v___x_779_, v___x_788_);
v_half_793_ = lean_uint64_shift_left(v___x_788_, v___x_792_);
v___x_794_ = lean_uint64_dec_lt(v_remainder_791_, v_half_793_);
if (v___x_794_ == 0)
{
uint8_t v___x_795_; 
v___x_795_ = lean_uint64_dec_lt(v_half_793_, v_remainder_791_);
if (v___x_795_ == 0)
{
uint64_t v___x_796_; uint8_t v___x_797_; 
v___x_796_ = lean_uint64_land(v_quotient_787_, v___x_788_);
v___x_797_ = lean_uint64_dec_eq(v___x_796_, v___y_742_);
if (v___x_797_ == 0)
{
uint64_t v___x_798_; 
v___x_798_ = lean_uint64_add(v_quotient_787_, v___x_788_);
v___y_636_ = v___y_741_;
v___y_637_ = v___y_742_;
v___y_638_ = v___y_745_;
v___y_639_ = v___x_798_;
goto v___jp_635_;
}
else
{
v___y_636_ = v___y_741_;
v___y_637_ = v___y_742_;
v___y_638_ = v___y_745_;
v___y_639_ = v_quotient_787_;
goto v___jp_635_;
}
}
else
{
uint64_t v___x_799_; 
v___x_799_ = lean_uint64_add(v_quotient_787_, v___x_788_);
v___y_636_ = v___y_741_;
v___y_637_ = v___y_742_;
v___y_638_ = v___y_745_;
v___y_639_ = v___x_799_;
goto v___jp_635_;
}
}
else
{
v___y_636_ = v___y_741_;
v___y_637_ = v___y_742_;
v___y_638_ = v___y_745_;
v___y_639_ = v_quotient_787_;
goto v___jp_635_;
}
}
}
else
{
v___y_636_ = v___y_741_;
v___y_637_ = v___y_742_;
v___y_638_ = v___y_745_;
v___y_639_ = v___y_743_;
goto v___jp_635_;
}
}
}
}
v___jp_800_:
{
uint64_t v___x_808_; uint64_t v___x_809_; uint8_t v___x_810_; 
v___x_808_ = 1ULL;
v___x_809_ = lean_uint64_shift_right(v___y_804_, v___x_808_);
v___x_810_ = lean_uint64_dec_eq(v___x_809_, v___y_802_);
if (v___x_810_ == 0)
{
uint64_t v___x_811_; 
v___x_811_ = lean_uint64_add(v___y_807_, v___x_808_);
v___y_741_ = v___y_801_;
v___y_742_ = v___y_802_;
v___y_743_ = v___y_803_;
v___y_744_ = v___y_805_;
v___y_745_ = v___y_806_;
v___y_746_ = v___x_811_;
goto v___jp_740_;
}
else
{
v___y_741_ = v___y_801_;
v___y_742_ = v___y_802_;
v___y_743_ = v___y_803_;
v___y_744_ = v___y_805_;
v___y_745_ = v___y_806_;
v___y_746_ = v___y_807_;
goto v___jp_740_;
}
}
v___jp_812_:
{
uint64_t v___x_822_; uint8_t v___x_823_; 
v___x_822_ = lean_uint64_shift_right(v___y_815_, v___y_820_);
v___x_823_ = lean_uint64_dec_eq(v___x_822_, v___y_816_);
if (v___x_823_ == 0)
{
uint64_t v___x_824_; 
v___x_824_ = lean_uint64_add(v___y_814_, v___y_820_);
v___y_801_ = v___y_813_;
v___y_802_ = v___y_816_;
v___y_803_ = v___y_817_;
v___y_804_ = v___y_821_;
v___y_805_ = v___y_818_;
v___y_806_ = v___y_819_;
v___y_807_ = v___x_824_;
goto v___jp_800_;
}
else
{
v___y_801_ = v___y_813_;
v___y_802_ = v___y_816_;
v___y_803_ = v___y_817_;
v___y_804_ = v___y_821_;
v___y_805_ = v___y_818_;
v___y_806_ = v___y_819_;
v___y_807_ = v___y_814_;
goto v___jp_800_;
}
}
v___jp_825_:
{
uint64_t v___x_833_; uint64_t v___x_834_; uint8_t v___x_835_; 
v___x_833_ = 2ULL;
v___x_834_ = lean_uint64_shift_right(v___y_828_, v___x_833_);
v___x_835_ = lean_uint64_dec_eq(v___x_834_, v___y_827_);
if (v___x_835_ == 0)
{
v___y_813_ = v___y_826_;
v___y_814_ = v___y_832_;
v___y_815_ = v___y_828_;
v___y_816_ = v___y_827_;
v___y_817_ = v___y_829_;
v___y_818_ = v___y_830_;
v___y_819_ = v___y_831_;
v___y_820_ = v___x_833_;
v___y_821_ = v___x_834_;
goto v___jp_812_;
}
else
{
v___y_813_ = v___y_826_;
v___y_814_ = v___y_832_;
v___y_815_ = v___y_828_;
v___y_816_ = v___y_827_;
v___y_817_ = v___y_829_;
v___y_818_ = v___y_830_;
v___y_819_ = v___y_831_;
v___y_820_ = v___x_833_;
v___y_821_ = v___y_828_;
goto v___jp_812_;
}
}
v___jp_836_:
{
uint64_t v___x_846_; uint8_t v___x_847_; 
v___x_846_ = lean_uint64_shift_right(v___y_838_, v___y_843_);
v___x_847_ = lean_uint64_dec_eq(v___x_846_, v___y_839_);
if (v___x_847_ == 0)
{
uint64_t v___x_848_; 
v___x_848_ = lean_uint64_add(v___y_842_, v___y_843_);
v___y_826_ = v___y_837_;
v___y_827_ = v___y_839_;
v___y_828_ = v___y_845_;
v___y_829_ = v___y_840_;
v___y_830_ = v___y_841_;
v___y_831_ = v___y_844_;
v___y_832_ = v___x_848_;
goto v___jp_825_;
}
else
{
v___y_826_ = v___y_837_;
v___y_827_ = v___y_839_;
v___y_828_ = v___y_845_;
v___y_829_ = v___y_840_;
v___y_830_ = v___y_841_;
v___y_831_ = v___y_844_;
v___y_832_ = v___y_842_;
goto v___jp_825_;
}
}
v___jp_849_:
{
uint64_t v___x_857_; uint64_t v___x_858_; uint8_t v___x_859_; 
v___x_857_ = 4ULL;
v___x_858_ = lean_uint64_shift_right(v___y_851_, v___x_857_);
v___x_859_ = lean_uint64_dec_eq(v___x_858_, v___y_852_);
if (v___x_859_ == 0)
{
v___y_837_ = v___y_850_;
v___y_838_ = v___y_851_;
v___y_839_ = v___y_852_;
v___y_840_ = v___y_853_;
v___y_841_ = v___y_854_;
v___y_842_ = v___y_856_;
v___y_843_ = v___x_857_;
v___y_844_ = v___y_855_;
v___y_845_ = v___x_858_;
goto v___jp_836_;
}
else
{
v___y_837_ = v___y_850_;
v___y_838_ = v___y_851_;
v___y_839_ = v___y_852_;
v___y_840_ = v___y_853_;
v___y_841_ = v___y_854_;
v___y_842_ = v___y_856_;
v___y_843_ = v___x_857_;
v___y_844_ = v___y_855_;
v___y_845_ = v___y_851_;
goto v___jp_836_;
}
}
v___jp_860_:
{
uint64_t v___x_870_; uint8_t v___x_871_; 
v___x_870_ = lean_uint64_shift_right(v___y_862_, v___y_867_);
v___x_871_ = lean_uint64_dec_eq(v___x_870_, v___y_864_);
if (v___x_871_ == 0)
{
uint64_t v___x_872_; 
v___x_872_ = lean_uint64_add(v___y_863_, v___y_867_);
v___y_850_ = v___y_861_;
v___y_851_ = v___y_869_;
v___y_852_ = v___y_864_;
v___y_853_ = v___y_865_;
v___y_854_ = v___y_866_;
v___y_855_ = v___y_868_;
v___y_856_ = v___x_872_;
goto v___jp_849_;
}
else
{
v___y_850_ = v___y_861_;
v___y_851_ = v___y_869_;
v___y_852_ = v___y_864_;
v___y_853_ = v___y_865_;
v___y_854_ = v___y_866_;
v___y_855_ = v___y_868_;
v___y_856_ = v___y_863_;
goto v___jp_849_;
}
}
v___jp_873_:
{
uint64_t v___x_881_; uint64_t v___x_882_; uint8_t v___x_883_; 
v___x_881_ = 8ULL;
v___x_882_ = lean_uint64_shift_right(v___y_875_, v___x_881_);
v___x_883_ = lean_uint64_dec_eq(v___x_882_, v___y_876_);
if (v___x_883_ == 0)
{
v___y_861_ = v___y_874_;
v___y_862_ = v___y_875_;
v___y_863_ = v___y_880_;
v___y_864_ = v___y_876_;
v___y_865_ = v___y_877_;
v___y_866_ = v___y_878_;
v___y_867_ = v___x_881_;
v___y_868_ = v___y_879_;
v___y_869_ = v___x_882_;
goto v___jp_860_;
}
else
{
v___y_861_ = v___y_874_;
v___y_862_ = v___y_875_;
v___y_863_ = v___y_880_;
v___y_864_ = v___y_876_;
v___y_865_ = v___y_877_;
v___y_866_ = v___y_878_;
v___y_867_ = v___x_881_;
v___y_868_ = v___y_879_;
v___y_869_ = v___y_875_;
goto v___jp_860_;
}
}
v___jp_884_:
{
uint64_t v___x_894_; uint8_t v___x_895_; 
v___x_894_ = lean_uint64_shift_right(v___y_889_, v___y_887_);
v___x_895_ = lean_uint64_dec_eq(v___x_894_, v___y_888_);
if (v___x_895_ == 0)
{
uint64_t v___x_896_; 
v___x_896_ = lean_uint64_add(v___y_886_, v___y_887_);
v___y_874_ = v___y_885_;
v___y_875_ = v___y_893_;
v___y_876_ = v___y_888_;
v___y_877_ = v___y_890_;
v___y_878_ = v___y_891_;
v___y_879_ = v___y_892_;
v___y_880_ = v___x_896_;
goto v___jp_873_;
}
else
{
v___y_874_ = v___y_885_;
v___y_875_ = v___y_893_;
v___y_876_ = v___y_888_;
v___y_877_ = v___y_890_;
v___y_878_ = v___y_891_;
v___y_879_ = v___y_892_;
v___y_880_ = v___y_886_;
goto v___jp_873_;
}
}
v___jp_897_:
{
uint64_t v___x_905_; uint64_t v___x_906_; uint8_t v___x_907_; 
v___x_905_ = 16ULL;
v___x_906_ = lean_uint64_shift_right(v___y_901_, v___x_905_);
v___x_907_ = lean_uint64_dec_eq(v___x_906_, v___y_899_);
if (v___x_907_ == 0)
{
v___y_885_ = v___y_898_;
v___y_886_ = v___y_904_;
v___y_887_ = v___x_905_;
v___y_888_ = v___y_899_;
v___y_889_ = v___y_901_;
v___y_890_ = v___y_900_;
v___y_891_ = v___y_902_;
v___y_892_ = v___y_903_;
v___y_893_ = v___x_906_;
goto v___jp_884_;
}
else
{
v___y_885_ = v___y_898_;
v___y_886_ = v___y_904_;
v___y_887_ = v___x_905_;
v___y_888_ = v___y_899_;
v___y_889_ = v___y_901_;
v___y_890_ = v___y_900_;
v___y_891_ = v___y_902_;
v___y_892_ = v___y_903_;
v___y_893_ = v___y_901_;
goto v___jp_884_;
}
}
v___jp_908_:
{
uint64_t v___x_916_; uint8_t v___x_917_; 
v___x_916_ = lean_uint64_shift_right(v___y_911_, v___y_913_);
v___x_917_ = lean_uint64_dec_eq(v___x_916_, v___y_910_);
if (v___x_917_ == 0)
{
v___y_898_ = v___y_909_;
v___y_899_ = v___y_910_;
v___y_900_ = v___y_911_;
v___y_901_ = v___y_915_;
v___y_902_ = v___y_912_;
v___y_903_ = v___y_914_;
v___y_904_ = v___y_913_;
goto v___jp_897_;
}
else
{
v___y_898_ = v___y_909_;
v___y_899_ = v___y_910_;
v___y_900_ = v___y_911_;
v___y_901_ = v___y_915_;
v___y_902_ = v___y_912_;
v___y_903_ = v___y_914_;
v___y_904_ = v___y_910_;
goto v___jp_897_;
}
}
v___jp_918_:
{
uint64_t v___x_923_; uint8_t v___x_924_; 
v___x_923_ = 0ULL;
v___x_924_ = lean_uint64_dec_eq(v___y_920_, v___x_923_);
if (v___x_924_ == 0)
{
uint64_t v___x_925_; uint64_t v___x_926_; uint8_t v___x_927_; 
v___x_925_ = 32ULL;
v___x_926_ = lean_uint64_shift_right(v___y_920_, v___x_925_);
v___x_927_ = lean_uint64_dec_eq(v___x_926_, v___x_923_);
if (v___x_927_ == 0)
{
v___y_909_ = v___y_919_;
v___y_910_ = v___x_923_;
v___y_911_ = v___y_920_;
v___y_912_ = v___y_921_;
v___y_913_ = v___x_925_;
v___y_914_ = v___y_922_;
v___y_915_ = v___x_926_;
goto v___jp_908_;
}
else
{
v___y_909_ = v___y_919_;
v___y_910_ = v___x_923_;
v___y_911_ = v___y_920_;
v___y_912_ = v___y_921_;
v___y_913_ = v___x_925_;
v___y_914_ = v___y_922_;
v___y_915_ = v___y_920_;
goto v___jp_908_;
}
}
else
{
if (v___y_919_ == 0)
{
uint32_t v___x_928_; 
v___x_928_ = 0;
return v___x_928_;
}
else
{
uint32_t v___x_929_; 
v___x_929_ = 2147483648;
return v___x_929_;
}
}
}
v___jp_930_:
{
uint64_t v___x_937_; uint64_t v___x_938_; uint64_t v___x_939_; uint8_t v___x_940_; 
v___x_937_ = lean_uint64_mul(v___y_934_, v___y_933_);
v___x_938_ = lean_uint64_add(v___y_932_, v___y_936_);
v___x_939_ = 281474976710656ULL;
v___x_940_ = lean_uint64_dec_lt(v___x_937_, v___x_939_);
if (v___x_940_ == 0)
{
v___y_919_ = v___y_931_;
v___y_920_ = v___x_937_;
v___y_921_ = v___x_938_;
v___y_922_ = v___y_935_;
goto v___jp_918_;
}
else
{
uint64_t v___x_941_; uint8_t v___x_942_; 
v___x_941_ = 123ULL;
v___x_942_ = lean_uint64_dec_le(v___x_938_, v___x_941_);
if (v___x_942_ == 0)
{
v___y_919_ = v___y_931_;
v___y_920_ = v___x_937_;
v___y_921_ = v___x_938_;
v___y_922_ = v___y_935_;
goto v___jp_918_;
}
else
{
uint64_t v___x_943_; uint8_t v___x_944_; 
v___x_943_ = 0ULL;
v___x_944_ = lean_uint64_dec_eq(v___x_937_, v___x_943_);
if (v___x_944_ == 0)
{
uint64_t v___x_945_; uint64_t v___x_946_; uint8_t v___x_947_; 
v___x_945_ = 149ULL;
v___x_946_ = lean_uint64_sub(v___x_945_, v___x_938_);
v___x_947_ = lean_uint64_dec_eq(v___x_946_, v___x_943_);
if (v___x_947_ == 0)
{
uint64_t v___x_948_; uint8_t v___x_949_; 
v___x_948_ = 64ULL;
v___x_949_ = lean_uint64_dec_lt(v___x_946_, v___x_948_);
if (v___x_949_ == 0)
{
uint8_t v___x_950_; 
v___x_950_ = lean_uint64_dec_eq(v___x_946_, v___x_948_);
if (v___x_950_ == 0)
{
v___y_657_ = v___y_931_;
v___y_658_ = v___x_943_;
v___y_659_ = v___y_935_;
v___y_660_ = v___x_943_;
goto v___jp_656_;
}
else
{
uint64_t v___x_951_; uint8_t v___x_952_; 
v___x_951_ = 9223372036854775808ULL;
v___x_952_ = lean_uint64_dec_lt(v___x_951_, v___x_937_);
if (v___x_952_ == 0)
{
v___y_657_ = v___y_931_;
v___y_658_ = v___x_943_;
v___y_659_ = v___y_935_;
v___y_660_ = v___x_943_;
goto v___jp_656_;
}
else
{
uint64_t v___x_953_; 
v___x_953_ = 1ULL;
v___y_657_ = v___y_931_;
v___y_658_ = v___x_943_;
v___y_659_ = v___y_935_;
v___y_660_ = v___x_953_;
goto v___jp_656_;
}
}
}
else
{
uint64_t v_quotient_954_; uint64_t v___x_955_; uint64_t v___x_956_; uint64_t v___x_957_; uint64_t v_remainder_958_; uint64_t v___x_959_; uint64_t v_half_960_; uint8_t v___x_961_; 
v_quotient_954_ = lean_uint64_shift_right(v___x_937_, v___x_946_);
v___x_955_ = 1ULL;
v___x_956_ = lean_uint64_shift_left(v___x_955_, v___x_946_);
v___x_957_ = lean_uint64_sub(v___x_956_, v___x_955_);
v_remainder_958_ = lean_uint64_land(v___x_937_, v___x_957_);
v___x_959_ = lean_uint64_sub(v___x_946_, v___x_955_);
v_half_960_ = lean_uint64_shift_left(v___x_955_, v___x_959_);
v___x_961_ = lean_uint64_dec_lt(v_remainder_958_, v_half_960_);
if (v___x_961_ == 0)
{
uint8_t v___x_962_; 
v___x_962_ = lean_uint64_dec_lt(v_half_960_, v_remainder_958_);
if (v___x_962_ == 0)
{
uint64_t v___x_963_; uint8_t v___x_964_; 
v___x_963_ = lean_uint64_land(v_quotient_954_, v___x_955_);
v___x_964_ = lean_uint64_dec_eq(v___x_963_, v___x_943_);
if (v___x_964_ == 0)
{
uint64_t v___x_965_; 
v___x_965_ = lean_uint64_add(v_quotient_954_, v___x_955_);
v___y_657_ = v___y_931_;
v___y_658_ = v___x_943_;
v___y_659_ = v___y_935_;
v___y_660_ = v___x_965_;
goto v___jp_656_;
}
else
{
v___y_657_ = v___y_931_;
v___y_658_ = v___x_943_;
v___y_659_ = v___y_935_;
v___y_660_ = v_quotient_954_;
goto v___jp_656_;
}
}
else
{
uint64_t v___x_966_; 
v___x_966_ = lean_uint64_add(v_quotient_954_, v___x_955_);
v___y_657_ = v___y_931_;
v___y_658_ = v___x_943_;
v___y_659_ = v___y_935_;
v___y_660_ = v___x_966_;
goto v___jp_656_;
}
}
else
{
v___y_657_ = v___y_931_;
v___y_658_ = v___x_943_;
v___y_659_ = v___y_935_;
v___y_660_ = v_quotient_954_;
goto v___jp_656_;
}
}
}
else
{
v___y_657_ = v___y_931_;
v___y_658_ = v___x_943_;
v___y_659_ = v___y_935_;
v___y_660_ = v___x_937_;
goto v___jp_656_;
}
}
else
{
if (v___y_931_ == 0)
{
uint32_t v___x_967_; 
v___x_967_ = 0;
return v___x_967_;
}
else
{
uint32_t v___x_968_; 
v___x_968_ = 2147483648;
return v___x_968_;
}
}
}
}
}
v___jp_972_:
{
uint64_t v___x_978_; uint64_t v___x_979_; uint8_t v___x_980_; 
v___x_978_ = lean_uint32_to_uint64(v_ey_971_);
v___x_979_ = 0ULL;
v___x_980_ = lean_uint64_dec_eq(v___x_978_, v___x_979_);
if (v___x_980_ == 0)
{
uint64_t v___x_981_; uint64_t v___x_982_; 
v___x_981_ = 1ULL;
v___x_982_ = lean_uint64_sub(v___x_978_, v___x_981_);
v___y_931_ = v___y_973_;
v___y_932_ = v___y_977_;
v___y_933_ = v___y_974_;
v___y_934_ = v___y_975_;
v___y_935_ = v___y_976_;
v___y_936_ = v___x_982_;
goto v___jp_930_;
}
else
{
v___y_931_ = v___y_973_;
v___y_932_ = v___y_977_;
v___y_933_ = v___y_974_;
v___y_934_ = v___y_975_;
v___y_935_ = v___y_976_;
v___y_936_ = v___x_979_;
goto v___jp_930_;
}
}
v___jp_983_:
{
uint64_t v___x_988_; uint64_t v___x_989_; uint8_t v___x_990_; 
v___x_988_ = lean_uint32_to_uint64(v_ex_969_);
v___x_989_ = 0ULL;
v___x_990_ = lean_uint64_dec_eq(v___x_988_, v___x_989_);
if (v___x_990_ == 0)
{
uint64_t v___x_991_; uint64_t v___x_992_; 
v___x_991_ = 1ULL;
v___x_992_ = lean_uint64_sub(v___x_988_, v___x_991_);
v___y_973_ = v___y_984_;
v___y_974_ = v___y_987_;
v___y_975_ = v___y_985_;
v___y_976_ = v___y_986_;
v___y_977_ = v___x_992_;
goto v___jp_972_;
}
else
{
v___y_973_ = v___y_984_;
v___y_974_ = v___y_987_;
v___y_975_ = v___y_985_;
v___y_976_ = v___y_986_;
v___y_977_ = v___x_989_;
goto v___jp_972_;
}
}
v___jp_993_:
{
uint32_t v___x_998_; uint8_t v___x_999_; 
v___x_998_ = 0;
v___x_999_ = lean_uint32_dec_eq(v_ey_971_, v___x_998_);
if (v___x_999_ == 0)
{
uint64_t v___x_1000_; uint64_t v___x_1001_; uint64_t v___x_1002_; 
v___x_1000_ = lean_uint32_to_uint64(v___y_995_);
v___x_1001_ = 8388608ULL;
v___x_1002_ = lean_uint64_lor(v___x_1000_, v___x_1001_);
v___y_984_ = v___y_994_;
v___y_985_ = v___y_997_;
v___y_986_ = v___y_996_;
v___y_987_ = v___x_1002_;
goto v___jp_983_;
}
else
{
uint64_t v___x_1003_; 
v___x_1003_ = lean_uint32_to_uint64(v___y_995_);
v___y_984_ = v___y_994_;
v___y_985_ = v___y_997_;
v___y_986_ = v___y_996_;
v___y_987_ = v___x_1003_;
goto v___jp_983_;
}
}
v___jp_1004_:
{
uint32_t v___x_1006_; uint32_t v_xFraction_1007_; uint32_t v_yFraction_1008_; uint32_t v___x_1009_; uint8_t v___x_1010_; 
v___x_1006_ = 8388607;
v_xFraction_1007_ = lean_uint32_land(v___y_524_, v___x_1006_);
v_yFraction_1008_ = lean_uint32_land(v___y_525_, v___x_1006_);
v___x_1009_ = 0;
v___x_1010_ = lean_uint32_dec_eq(v_ex_969_, v___x_1009_);
if (v___x_1010_ == 0)
{
uint64_t v___x_1011_; uint64_t v___x_1012_; uint64_t v___x_1013_; 
v___x_1011_ = lean_uint32_to_uint64(v_xFraction_1007_);
v___x_1012_ = 8388608ULL;
v___x_1013_ = lean_uint64_lor(v___x_1011_, v___x_1012_);
v___y_994_ = v___y_1005_;
v___y_995_ = v_yFraction_1008_;
v___y_996_ = v___x_1006_;
v___y_997_ = v___x_1013_;
goto v___jp_993_;
}
else
{
uint64_t v___x_1014_; 
v___x_1014_ = lean_uint32_to_uint64(v_xFraction_1007_);
v___y_994_ = v___y_1005_;
v___y_995_ = v_yFraction_1008_;
v___y_996_ = v___x_1006_;
v___y_997_ = v___x_1014_;
goto v___jp_993_;
}
}
v___jp_1015_:
{
if (v___y_1017_ == 0)
{
v___y_1005_ = v___x_523_;
goto v___jp_1004_;
}
else
{
v___y_1005_ = v___y_1016_;
goto v___jp_1004_;
}
}
v___jp_1021_:
{
if (v___y_1022_ == 0)
{
if (v___y_1024_ == 0)
{
v___y_1016_ = v___y_1023_;
v___y_1017_ = v___x_1020_;
goto v___jp_1015_;
}
else
{
v___y_1005_ = v___x_523_;
goto v___jp_1004_;
}
}
else
{
v___y_1016_ = v___y_1023_;
v___y_1017_ = v___y_1024_;
goto v___jp_1015_;
}
}
v___jp_1025_:
{
uint32_t v___x_1028_; uint32_t v___x_1029_; uint32_t v___x_1030_; uint8_t v___x_1031_; 
v___x_1028_ = 2147483648;
v___x_1029_ = lean_uint32_land(v___y_525_, v___x_1028_);
v___x_1030_ = 0;
v___x_1031_ = lean_uint32_dec_eq(v___x_1029_, v___x_1030_);
if (v___x_1031_ == 0)
{
v___y_1022_ = v___y_1027_;
v___y_1023_ = v___y_1026_;
v___y_1024_ = v___x_523_;
goto v___jp_1021_;
}
else
{
v___y_1022_ = v___y_1027_;
v___y_1023_ = v___y_1026_;
v___y_1024_ = v___y_1026_;
goto v___jp_1021_;
}
}
v___jp_1032_:
{
if (v___y_1033_ == 0)
{
uint32_t v___x_1034_; uint32_t v___x_1035_; uint32_t v___x_1036_; uint8_t v___x_1037_; 
v___x_1034_ = 2147483648;
v___x_1035_ = lean_uint32_land(v___y_524_, v___x_1034_);
v___x_1036_ = 0;
v___x_1037_ = lean_uint32_dec_eq(v___x_1035_, v___x_1036_);
if (v___x_1037_ == 0)
{
v___y_1026_ = v___y_1033_;
v___y_1027_ = v___x_523_;
goto v___jp_1025_;
}
else
{
v___y_1026_ = v___y_1033_;
v___y_1027_ = v___y_1033_;
goto v___jp_1025_;
}
}
else
{
lean_object* v___x_1038_; lean_object* v___x_1039_; lean_object* v___x_1040_; uint32_t v___x_1041_; 
v___x_1038_ = lean_uint32_to_nat(v___y_524_);
v___x_1039_ = lean_uint32_to_nat(v___y_525_);
v___x_1040_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1038_, v___x_1039_);
v___x_1041_ = lean_uint32_of_nat(v___x_1040_);
lean_dec(v___x_1040_);
return v___x_1041_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___x_1056_, lean_object* v___y_1057_, lean_object* v___y_1058_){
_start:
{
uint8_t v___x_5547__boxed_1059_; uint32_t v___y_5548__boxed_1060_; uint32_t v___y_5549__boxed_1061_; uint32_t v_res_1062_; lean_object* v_r_1063_; 
v___x_5547__boxed_1059_ = lean_unbox(v___x_1056_);
v___y_5548__boxed_1060_ = lean_unbox_uint32(v___y_1057_);
lean_dec(v___y_1057_);
v___y_5549__boxed_1061_ = lean_unbox_uint32(v___y_1058_);
lean_dec(v___y_1058_);
v_res_1062_ = lp_competition_main___lam__1(v___x_5547__boxed_1059_, v___y_5548__boxed_1060_, v___y_5549__boxed_1061_);
v_r_1063_ = lean_box_uint32(v_res_1062_);
return v_r_1063_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__2(uint32_t v___y_1064_, uint32_t v___y_1065_){
_start:
{
uint8_t v___y_1072_; uint8_t v___y_1086_; uint8_t v___y_1100_; uint8_t v___y_1117_; float v___y_1124_; float v___y_1125_; float v___y_1139_; uint8_t v___y_1140_; float v___y_1155_; uint8_t v___y_1165_; uint32_t v___x_1179_; uint32_t v_a_1180_; uint32_t v___x_1181_; uint32_t v___x_1182_; uint32_t v___x_1183_; uint8_t v___x_1184_; 
v___x_1179_ = 2147483647;
v_a_1180_ = lean_uint32_land(v___y_1064_, v___x_1179_);
v___x_1181_ = 201326591;
v___x_1182_ = 1;
v___x_1183_ = lean_uint32_sub(v_a_1180_, v___x_1182_);
v___x_1184_ = lean_uint32_dec_le(v___x_1181_, v___x_1183_);
if (v___x_1184_ == 0)
{
v___y_1165_ = v___x_1184_;
goto v___jp_1164_;
}
else
{
uint32_t v___x_1185_; uint8_t v___x_1186_; 
v___x_1185_ = 2139095040;
v___x_1186_ = lean_uint32_dec_lt(v_a_1180_, v___x_1185_);
v___y_1165_ = v___x_1186_;
goto v___jp_1164_;
}
v___jp_1066_:
{
lean_object* v___x_1067_; lean_object* v___x_1068_; lean_object* v___x_1069_; uint32_t v___x_1070_; 
v___x_1067_ = lean_uint32_to_nat(v___y_1064_);
v___x_1068_ = lean_uint32_to_nat(v___y_1065_);
v___x_1069_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_1067_, v___x_1068_);
v___x_1070_ = lean_uint32_of_nat(v___x_1069_);
lean_dec(v___x_1069_);
return v___x_1070_;
}
v___jp_1071_:
{
if (v___y_1072_ == 0)
{
goto v___jp_1066_;
}
else
{
uint32_t v___x_1073_; uint32_t v___x_1074_; 
v___x_1073_ = 4194304;
v___x_1074_ = lean_uint32_lor(v___y_1065_, v___x_1073_);
return v___x_1074_;
}
}
v___jp_1075_:
{
uint32_t v___x_1076_; uint32_t v___x_1077_; uint32_t v___x_1078_; uint32_t v___x_1079_; uint8_t v___x_1080_; 
v___x_1076_ = 23;
v___x_1077_ = lean_uint32_shift_right(v___y_1065_, v___x_1076_);
v___x_1078_ = 255;
v___x_1079_ = lean_uint32_land(v___x_1077_, v___x_1078_);
v___x_1080_ = lean_uint32_dec_eq(v___x_1079_, v___x_1078_);
if (v___x_1080_ == 0)
{
v___y_1072_ = v___x_1080_;
goto v___jp_1071_;
}
else
{
uint32_t v___x_1081_; uint32_t v___x_1082_; uint32_t v___x_1083_; uint8_t v___x_1084_; 
v___x_1081_ = 8388607;
v___x_1082_ = lean_uint32_land(v___y_1065_, v___x_1081_);
v___x_1083_ = 0;
v___x_1084_ = lean_uint32_dec_eq(v___x_1082_, v___x_1083_);
if (v___x_1084_ == 0)
{
v___y_1072_ = v___x_1080_;
goto v___jp_1071_;
}
else
{
goto v___jp_1066_;
}
}
}
v___jp_1085_:
{
if (v___y_1086_ == 0)
{
goto v___jp_1075_;
}
else
{
uint32_t v___x_1087_; uint32_t v___x_1088_; 
v___x_1087_ = 4194304;
v___x_1088_ = lean_uint32_lor(v___y_1064_, v___x_1087_);
return v___x_1088_;
}
}
v___jp_1089_:
{
uint32_t v___x_1090_; uint32_t v___x_1091_; uint32_t v___x_1092_; uint32_t v___x_1093_; uint8_t v___x_1094_; 
v___x_1090_ = 23;
v___x_1091_ = lean_uint32_shift_right(v___y_1064_, v___x_1090_);
v___x_1092_ = 255;
v___x_1093_ = lean_uint32_land(v___x_1091_, v___x_1092_);
v___x_1094_ = lean_uint32_dec_eq(v___x_1093_, v___x_1092_);
if (v___x_1094_ == 0)
{
v___y_1086_ = v___x_1094_;
goto v___jp_1085_;
}
else
{
uint32_t v___x_1095_; uint32_t v___x_1096_; uint32_t v___x_1097_; uint8_t v___x_1098_; 
v___x_1095_ = 8388607;
v___x_1096_ = lean_uint32_land(v___y_1064_, v___x_1095_);
v___x_1097_ = 0;
v___x_1098_ = lean_uint32_dec_eq(v___x_1096_, v___x_1097_);
if (v___x_1098_ == 0)
{
v___y_1086_ = v___x_1094_;
goto v___jp_1085_;
}
else
{
goto v___jp_1075_;
}
}
}
v___jp_1099_:
{
if (v___y_1100_ == 0)
{
goto v___jp_1089_;
}
else
{
uint32_t v___x_1101_; uint32_t v___x_1102_; uint32_t v___x_1103_; uint8_t v___x_1104_; 
v___x_1101_ = 4194304;
v___x_1102_ = lean_uint32_land(v___y_1065_, v___x_1101_);
v___x_1103_ = 0;
v___x_1104_ = lean_uint32_dec_eq(v___x_1102_, v___x_1103_);
if (v___x_1104_ == 0)
{
goto v___jp_1089_;
}
else
{
uint32_t v___x_1105_; 
v___x_1105_ = lean_uint32_lor(v___y_1065_, v___x_1101_);
return v___x_1105_;
}
}
}
v___jp_1106_:
{
uint32_t v___x_1107_; uint32_t v___x_1108_; uint32_t v___x_1109_; uint32_t v___x_1110_; uint8_t v___x_1111_; 
v___x_1107_ = 23;
v___x_1108_ = lean_uint32_shift_right(v___y_1065_, v___x_1107_);
v___x_1109_ = 255;
v___x_1110_ = lean_uint32_land(v___x_1108_, v___x_1109_);
v___x_1111_ = lean_uint32_dec_eq(v___x_1110_, v___x_1109_);
if (v___x_1111_ == 0)
{
v___y_1100_ = v___x_1111_;
goto v___jp_1099_;
}
else
{
uint32_t v___x_1112_; uint32_t v___x_1113_; uint32_t v___x_1114_; uint8_t v___x_1115_; 
v___x_1112_ = 8388607;
v___x_1113_ = lean_uint32_land(v___y_1065_, v___x_1112_);
v___x_1114_ = 0;
v___x_1115_ = lean_uint32_dec_eq(v___x_1113_, v___x_1114_);
if (v___x_1115_ == 0)
{
v___y_1100_ = v___x_1111_;
goto v___jp_1099_;
}
else
{
goto v___jp_1089_;
}
}
}
v___jp_1116_:
{
if (v___y_1117_ == 0)
{
goto v___jp_1106_;
}
else
{
uint32_t v___x_1118_; uint32_t v___x_1119_; uint32_t v___x_1120_; uint8_t v___x_1121_; 
v___x_1118_ = 4194304;
v___x_1119_ = lean_uint32_land(v___y_1064_, v___x_1118_);
v___x_1120_ = 0;
v___x_1121_ = lean_uint32_dec_eq(v___x_1119_, v___x_1120_);
if (v___x_1121_ == 0)
{
goto v___jp_1106_;
}
else
{
uint32_t v___x_1122_; 
v___x_1122_ = lean_uint32_lor(v___y_1064_, v___x_1118_);
return v___x_1122_;
}
}
}
v___jp_1123_:
{
float v_result_1126_; uint8_t v___x_1127_; 
v_result_1126_ = lean_float32_add(v___y_1124_, v___y_1125_);
v___x_1127_ = lean_float32_beq(v_result_1126_, v_result_1126_);
if (v___x_1127_ == 0)
{
uint32_t v___x_1128_; uint32_t v___x_1129_; uint32_t v___x_1130_; uint32_t v___x_1131_; uint8_t v___x_1132_; 
v___x_1128_ = 23;
v___x_1129_ = lean_uint32_shift_right(v___y_1064_, v___x_1128_);
v___x_1130_ = 255;
v___x_1131_ = lean_uint32_land(v___x_1129_, v___x_1130_);
v___x_1132_ = lean_uint32_dec_eq(v___x_1131_, v___x_1130_);
if (v___x_1132_ == 0)
{
v___y_1117_ = v___x_1132_;
goto v___jp_1116_;
}
else
{
uint32_t v___x_1133_; uint32_t v___x_1134_; uint32_t v___x_1135_; uint8_t v___x_1136_; 
v___x_1133_ = 8388607;
v___x_1134_ = lean_uint32_land(v___y_1064_, v___x_1133_);
v___x_1135_ = 0;
v___x_1136_ = lean_uint32_dec_eq(v___x_1134_, v___x_1135_);
if (v___x_1136_ == 0)
{
v___y_1117_ = v___x_1132_;
goto v___jp_1116_;
}
else
{
goto v___jp_1106_;
}
}
}
else
{
uint32_t v___x_1137_; 
v___x_1137_ = lean_float32_to_bits(v_result_1126_);
return v___x_1137_;
}
}
v___jp_1138_:
{
if (v___y_1140_ == 0)
{
float v___x_1141_; 
v___x_1141_ = lean_float32_of_bits(v___y_1065_);
v___y_1124_ = v___y_1139_;
v___y_1125_ = v___x_1141_;
goto v___jp_1123_;
}
else
{
uint32_t v___x_1142_; uint32_t v___x_1143_; uint32_t v___x_1144_; uint32_t v___x_1145_; float v___x_1146_; lean_object* v___x_1147_; uint32_t v___x_1148_; uint32_t v___x_1149_; lean_object* v___x_1150_; lean_object* v___x_1151_; float v___x_1152_; float v___x_1153_; 
v___x_1142_ = 8388607;
v___x_1143_ = lean_uint32_land(v___y_1065_, v___x_1142_);
v___x_1144_ = 8388608;
v___x_1145_ = lean_uint32_lor(v___x_1143_, v___x_1144_);
v___x_1146_ = lean_uint32_to_float32(v___x_1145_);
v___x_1147_ = lp_competition_R2W01b_scaleTable;
v___x_1148_ = 23;
v___x_1149_ = lean_uint32_shift_right(v___y_1065_, v___x_1148_);
v___x_1150_ = lean_uint32_to_nat(v___x_1149_);
v___x_1151_ = lean_array_fget_borrowed(v___x_1147_, v___x_1150_);
lean_dec(v___x_1150_);
v___x_1152_ = lean_unbox_float32(v___x_1151_);
v___x_1153_ = lean_float32_mul(v___x_1146_, v___x_1152_);
v___y_1124_ = v___y_1139_;
v___y_1125_ = v___x_1153_;
goto v___jp_1123_;
}
}
v___jp_1154_:
{
uint32_t v___x_1156_; uint32_t v_a_1157_; uint32_t v___x_1158_; uint32_t v___x_1159_; uint32_t v___x_1160_; uint8_t v___x_1161_; 
v___x_1156_ = 2147483647;
v_a_1157_ = lean_uint32_land(v___y_1065_, v___x_1156_);
v___x_1158_ = 201326591;
v___x_1159_ = 1;
v___x_1160_ = lean_uint32_sub(v_a_1157_, v___x_1159_);
v___x_1161_ = lean_uint32_dec_le(v___x_1158_, v___x_1160_);
if (v___x_1161_ == 0)
{
v___y_1139_ = v___y_1155_;
v___y_1140_ = v___x_1161_;
goto v___jp_1138_;
}
else
{
uint32_t v___x_1162_; uint8_t v___x_1163_; 
v___x_1162_ = 2139095040;
v___x_1163_ = lean_uint32_dec_lt(v_a_1157_, v___x_1162_);
v___y_1139_ = v___y_1155_;
v___y_1140_ = v___x_1163_;
goto v___jp_1138_;
}
}
v___jp_1164_:
{
if (v___y_1165_ == 0)
{
float v___x_1166_; 
v___x_1166_ = lean_float32_of_bits(v___y_1064_);
v___y_1155_ = v___x_1166_;
goto v___jp_1154_;
}
else
{
uint32_t v___x_1167_; uint32_t v___x_1168_; uint32_t v___x_1169_; uint32_t v___x_1170_; float v___x_1171_; lean_object* v___x_1172_; uint32_t v___x_1173_; uint32_t v___x_1174_; lean_object* v___x_1175_; lean_object* v___x_1176_; float v___x_1177_; float v___x_1178_; 
v___x_1167_ = 8388607;
v___x_1168_ = lean_uint32_land(v___y_1064_, v___x_1167_);
v___x_1169_ = 8388608;
v___x_1170_ = lean_uint32_lor(v___x_1168_, v___x_1169_);
v___x_1171_ = lean_uint32_to_float32(v___x_1170_);
v___x_1172_ = lp_competition_R2W01b_scaleTable;
v___x_1173_ = 23;
v___x_1174_ = lean_uint32_shift_right(v___y_1064_, v___x_1173_);
v___x_1175_ = lean_uint32_to_nat(v___x_1174_);
v___x_1176_ = lean_array_fget_borrowed(v___x_1172_, v___x_1175_);
lean_dec(v___x_1175_);
v___x_1177_ = lean_unbox_float32(v___x_1176_);
v___x_1178_ = lean_float32_mul(v___x_1171_, v___x_1177_);
v___y_1155_ = v___x_1178_;
goto v___jp_1154_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__2___boxed(lean_object* v___y_1187_, lean_object* v___y_1188_){
_start:
{
uint32_t v___y_6578__boxed_1189_; uint32_t v___y_6579__boxed_1190_; uint32_t v_res_1191_; lean_object* v_r_1192_; 
v___y_6578__boxed_1189_ = lean_unbox_uint32(v___y_1187_);
lean_dec(v___y_1187_);
v___y_6579__boxed_1190_ = lean_unbox_uint32(v___y_1188_);
lean_dec(v___y_1188_);
v_res_1191_ = lp_competition_main___lam__2(v___y_6578__boxed_1189_, v___y_6579__boxed_1190_);
v_r_1192_ = lean_box_uint32(v_res_1191_);
return v_r_1192_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint8_t v___x_1193_, uint32_t v___y_1194_, uint32_t v___y_1195_){
_start:
{
uint8_t v___y_1197_; uint8_t v___y_1213_; uint8_t v___y_1227_; uint8_t v___y_1244_; float v___y_1251_; float v___y_1252_; float v___y_1266_; uint8_t v___y_1267_; float v___y_1282_; uint32_t v___y_1292_; uint32_t v___y_1296_; uint32_t v___y_1300_; uint32_t v___y_1301_; uint32_t v___y_1302_; uint32_t v___y_1306_; uint64_t v___y_1307_; uint8_t v___y_1308_; uint64_t v___y_1309_; uint32_t v___y_1321_; uint32_t v___y_1322_; uint32_t v___y_1323_; uint32_t v___y_1327_; uint8_t v___y_1328_; uint64_t v___y_1329_; uint64_t v___y_1330_; uint32_t v___x_1341_; uint32_t v___x_1342_; uint8_t v___y_1344_; uint32_t v___x_1356_; uint32_t v___y_1358_; uint32_t v___y_1359_; uint32_t v___y_1360_; uint32_t v___y_1361_; uint32_t v___y_1368_; uint8_t v___y_1369_; uint32_t v___y_1370_; uint32_t v___y_1371_; uint32_t v___y_1375_; uint64_t v___y_1376_; uint8_t v___y_1377_; uint64_t v___y_1378_; uint64_t v___y_1379_; uint32_t v___y_1389_; uint8_t v___y_1390_; uint64_t v___y_1391_; uint8_t v___y_1392_; uint64_t v___y_1393_; uint64_t v___y_1394_; uint32_t v___y_1401_; uint64_t v___y_1402_; uint64_t v___y_1403_; uint8_t v___y_1404_; uint64_t v___y_1405_; uint32_t v___y_1411_; uint64_t v___y_1412_; uint8_t v___y_1413_; uint64_t v___y_1414_; uint64_t v___y_1415_; uint64_t v___y_1416_; uint32_t v___y_1471_; uint64_t v___y_1472_; uint64_t v___y_1473_; uint8_t v___y_1474_; uint64_t v___y_1475_; uint64_t v___y_1476_; uint64_t v___y_1477_; uint32_t v___y_1483_; uint64_t v___y_1484_; uint64_t v___y_1485_; uint64_t v___y_1486_; uint64_t v___y_1487_; uint8_t v___y_1488_; uint64_t v___y_1489_; uint64_t v___y_1490_; uint64_t v___y_1491_; uint32_t v___y_1496_; uint64_t v___y_1497_; uint64_t v___y_1498_; uint8_t v___y_1499_; uint64_t v___y_1500_; uint64_t v___y_1501_; uint64_t v___y_1502_; uint32_t v___y_1507_; uint64_t v___y_1508_; uint64_t v___y_1509_; uint64_t v___y_1510_; uint64_t v___y_1511_; uint8_t v___y_1512_; uint64_t v___y_1513_; uint64_t v___y_1514_; uint64_t v___y_1515_; uint32_t v___y_1520_; uint64_t v___y_1521_; uint64_t v___y_1522_; uint8_t v___y_1523_; uint64_t v___y_1524_; uint64_t v___y_1525_; uint64_t v___y_1526_; uint64_t v___y_1531_; uint32_t v___y_1532_; uint64_t v___y_1533_; uint64_t v___y_1534_; uint64_t v___y_1535_; uint8_t v___y_1536_; uint64_t v___y_1537_; uint64_t v___y_1538_; uint64_t v___y_1539_; uint32_t v___y_1544_; uint64_t v___y_1545_; uint64_t v___y_1546_; uint8_t v___y_1547_; uint64_t v___y_1548_; uint64_t v___y_1549_; uint64_t v___y_1550_; uint32_t v___y_1555_; uint64_t v___y_1556_; uint64_t v___y_1557_; uint64_t v___y_1558_; uint64_t v___y_1559_; uint8_t v___y_1560_; uint64_t v___y_1561_; uint64_t v___y_1562_; uint64_t v___y_1563_; uint32_t v___y_1568_; uint64_t v___y_1569_; uint64_t v___y_1570_; uint8_t v___y_1571_; uint64_t v___y_1572_; uint64_t v___y_1573_; uint64_t v___y_1574_; uint32_t v___y_1579_; uint64_t v___y_1580_; uint8_t v___y_1581_; uint64_t v___y_1582_; uint64_t v___y_1583_; uint64_t v___y_1584_; uint64_t v___y_1585_; uint32_t v___y_1589_; uint8_t v___y_1590_; uint64_t v___y_1591_; uint64_t v___y_1592_; uint32_t v___y_1601_; uint64_t v___y_1602_; uint64_t v___y_1603_; uint64_t v___y_1604_; uint8_t v___y_1605_; uint64_t v___y_1606_; uint32_t v_ex_1639_; uint32_t v___x_1640_; uint32_t v_ey_1641_; uint32_t v___y_1643_; uint64_t v___y_1644_; uint64_t v___y_1645_; uint8_t v___y_1646_; uint64_t v___y_1647_; uint32_t v___y_1654_; uint64_t v___y_1655_; uint8_t v___y_1656_; uint64_t v___y_1657_; uint32_t v___y_1664_; uint32_t v___y_1665_; uint8_t v___y_1666_; uint64_t v___y_1667_; uint8_t v___y_1675_; uint8_t v___y_1686_; uint8_t v___y_1687_; uint32_t v___x_1688_; uint32_t v___x_1689_; uint8_t v___x_1690_; uint8_t v___y_1692_; uint8_t v___y_1693_; uint8_t v___y_1694_; uint8_t v___y_1696_; uint8_t v___y_1697_; uint8_t v___y_1703_; 
v___x_1341_ = 23;
v___x_1342_ = lean_uint32_shift_right(v___y_1194_, v___x_1341_);
v___x_1356_ = 255;
v_ex_1639_ = lean_uint32_land(v___x_1342_, v___x_1356_);
v___x_1640_ = lean_uint32_shift_right(v___y_1195_, v___x_1341_);
v_ey_1641_ = lean_uint32_land(v___x_1640_, v___x_1356_);
v___x_1688_ = lean_uint32_add(v_ex_1639_, v_ey_1641_);
v___x_1689_ = 128;
v___x_1690_ = lean_uint32_dec_lt(v___x_1688_, v___x_1689_);
if (v___x_1690_ == 0)
{
uint32_t v___x_1712_; uint32_t v_a_1713_; uint32_t v___x_1714_; uint32_t v___x_1715_; uint32_t v___x_1716_; uint8_t v___x_1717_; 
v___x_1712_ = 2147483647;
v_a_1713_ = lean_uint32_land(v___y_1194_, v___x_1712_);
v___x_1714_ = 201326591;
v___x_1715_ = 1;
v___x_1716_ = lean_uint32_sub(v_a_1713_, v___x_1715_);
v___x_1717_ = lean_uint32_dec_le(v___x_1714_, v___x_1716_);
if (v___x_1717_ == 0)
{
v___y_1344_ = v___x_1717_;
goto v___jp_1343_;
}
else
{
uint32_t v___x_1718_; uint8_t v___x_1719_; 
v___x_1718_ = 2139095040;
v___x_1719_ = lean_uint32_dec_lt(v_a_1713_, v___x_1718_);
v___y_1344_ = v___x_1719_;
goto v___jp_1343_;
}
}
else
{
uint32_t v___x_1720_; uint32_t v___x_1721_; uint32_t v___x_1722_; uint8_t v___x_1723_; 
v___x_1720_ = 4278190080;
v___x_1721_ = 1;
v___x_1722_ = lean_uint32_shift_left(v___y_1194_, v___x_1721_);
v___x_1723_ = lean_uint32_dec_le(v___x_1720_, v___x_1722_);
if (v___x_1723_ == 0)
{
uint32_t v___x_1724_; uint8_t v___x_1725_; 
v___x_1724_ = lean_uint32_shift_left(v___y_1195_, v___x_1721_);
v___x_1725_ = lean_uint32_dec_le(v___x_1720_, v___x_1724_);
v___y_1703_ = v___x_1725_;
goto v___jp_1702_;
}
else
{
v___y_1703_ = v___x_1723_;
goto v___jp_1702_;
}
}
v___jp_1196_:
{
if (v___y_1197_ == 0)
{
uint32_t v___x_1198_; 
v___x_1198_ = lp_competition_Submission_FastMul_mul(v___y_1194_, v___y_1195_);
return v___x_1198_;
}
else
{
uint32_t v___x_1199_; uint32_t v___x_1200_; 
v___x_1199_ = 4194304;
v___x_1200_ = lean_uint32_lor(v___y_1195_, v___x_1199_);
return v___x_1200_;
}
}
v___jp_1201_:
{
uint32_t v___x_1202_; uint32_t v___x_1203_; uint32_t v___x_1204_; uint32_t v___x_1205_; uint8_t v___x_1206_; 
v___x_1202_ = 23;
v___x_1203_ = lean_uint32_shift_right(v___y_1195_, v___x_1202_);
v___x_1204_ = 255;
v___x_1205_ = lean_uint32_land(v___x_1203_, v___x_1204_);
v___x_1206_ = lean_uint32_dec_eq(v___x_1205_, v___x_1204_);
if (v___x_1206_ == 0)
{
v___y_1197_ = v___x_1206_;
goto v___jp_1196_;
}
else
{
uint32_t v___x_1207_; uint32_t v___x_1208_; uint32_t v___x_1209_; uint8_t v___x_1210_; 
v___x_1207_ = 8388607;
v___x_1208_ = lean_uint32_land(v___y_1195_, v___x_1207_);
v___x_1209_ = 0;
v___x_1210_ = lean_uint32_dec_eq(v___x_1208_, v___x_1209_);
if (v___x_1210_ == 0)
{
v___y_1197_ = v___x_1206_;
goto v___jp_1196_;
}
else
{
uint32_t v___x_1211_; 
v___x_1211_ = lp_competition_Submission_FastMul_mul(v___y_1194_, v___y_1195_);
return v___x_1211_;
}
}
}
v___jp_1212_:
{
if (v___y_1213_ == 0)
{
goto v___jp_1201_;
}
else
{
uint32_t v___x_1214_; uint32_t v___x_1215_; 
v___x_1214_ = 4194304;
v___x_1215_ = lean_uint32_lor(v___y_1194_, v___x_1214_);
return v___x_1215_;
}
}
v___jp_1216_:
{
uint32_t v___x_1217_; uint32_t v___x_1218_; uint32_t v___x_1219_; uint32_t v___x_1220_; uint8_t v___x_1221_; 
v___x_1217_ = 23;
v___x_1218_ = lean_uint32_shift_right(v___y_1194_, v___x_1217_);
v___x_1219_ = 255;
v___x_1220_ = lean_uint32_land(v___x_1218_, v___x_1219_);
v___x_1221_ = lean_uint32_dec_eq(v___x_1220_, v___x_1219_);
if (v___x_1221_ == 0)
{
v___y_1213_ = v___x_1221_;
goto v___jp_1212_;
}
else
{
uint32_t v___x_1222_; uint32_t v___x_1223_; uint32_t v___x_1224_; uint8_t v___x_1225_; 
v___x_1222_ = 8388607;
v___x_1223_ = lean_uint32_land(v___y_1194_, v___x_1222_);
v___x_1224_ = 0;
v___x_1225_ = lean_uint32_dec_eq(v___x_1223_, v___x_1224_);
if (v___x_1225_ == 0)
{
v___y_1213_ = v___x_1221_;
goto v___jp_1212_;
}
else
{
goto v___jp_1201_;
}
}
}
v___jp_1226_:
{
if (v___y_1227_ == 0)
{
goto v___jp_1216_;
}
else
{
uint32_t v___x_1228_; uint32_t v___x_1229_; uint32_t v___x_1230_; uint8_t v___x_1231_; 
v___x_1228_ = 4194304;
v___x_1229_ = lean_uint32_land(v___y_1195_, v___x_1228_);
v___x_1230_ = 0;
v___x_1231_ = lean_uint32_dec_eq(v___x_1229_, v___x_1230_);
if (v___x_1231_ == 0)
{
goto v___jp_1216_;
}
else
{
uint32_t v___x_1232_; 
v___x_1232_ = lean_uint32_lor(v___y_1195_, v___x_1228_);
return v___x_1232_;
}
}
}
v___jp_1233_:
{
uint32_t v___x_1234_; uint32_t v___x_1235_; uint32_t v___x_1236_; uint32_t v___x_1237_; uint8_t v___x_1238_; 
v___x_1234_ = 23;
v___x_1235_ = lean_uint32_shift_right(v___y_1195_, v___x_1234_);
v___x_1236_ = 255;
v___x_1237_ = lean_uint32_land(v___x_1235_, v___x_1236_);
v___x_1238_ = lean_uint32_dec_eq(v___x_1237_, v___x_1236_);
if (v___x_1238_ == 0)
{
v___y_1227_ = v___x_1238_;
goto v___jp_1226_;
}
else
{
uint32_t v___x_1239_; uint32_t v___x_1240_; uint32_t v___x_1241_; uint8_t v___x_1242_; 
v___x_1239_ = 8388607;
v___x_1240_ = lean_uint32_land(v___y_1195_, v___x_1239_);
v___x_1241_ = 0;
v___x_1242_ = lean_uint32_dec_eq(v___x_1240_, v___x_1241_);
if (v___x_1242_ == 0)
{
v___y_1227_ = v___x_1238_;
goto v___jp_1226_;
}
else
{
goto v___jp_1216_;
}
}
}
v___jp_1243_:
{
if (v___y_1244_ == 0)
{
goto v___jp_1233_;
}
else
{
uint32_t v___x_1245_; uint32_t v___x_1246_; uint32_t v___x_1247_; uint8_t v___x_1248_; 
v___x_1245_ = 4194304;
v___x_1246_ = lean_uint32_land(v___y_1194_, v___x_1245_);
v___x_1247_ = 0;
v___x_1248_ = lean_uint32_dec_eq(v___x_1246_, v___x_1247_);
if (v___x_1248_ == 0)
{
goto v___jp_1233_;
}
else
{
uint32_t v___x_1249_; 
v___x_1249_ = lean_uint32_lor(v___y_1194_, v___x_1245_);
return v___x_1249_;
}
}
}
v___jp_1250_:
{
float v_result_1253_; uint8_t v___x_1254_; 
v_result_1253_ = lean_float32_mul(v___y_1251_, v___y_1252_);
v___x_1254_ = lean_float32_beq(v_result_1253_, v_result_1253_);
if (v___x_1254_ == 0)
{
uint32_t v___x_1255_; uint32_t v___x_1256_; uint32_t v___x_1257_; uint32_t v___x_1258_; uint8_t v___x_1259_; 
v___x_1255_ = 23;
v___x_1256_ = lean_uint32_shift_right(v___y_1194_, v___x_1255_);
v___x_1257_ = 255;
v___x_1258_ = lean_uint32_land(v___x_1256_, v___x_1257_);
v___x_1259_ = lean_uint32_dec_eq(v___x_1258_, v___x_1257_);
if (v___x_1259_ == 0)
{
v___y_1244_ = v___x_1259_;
goto v___jp_1243_;
}
else
{
uint32_t v___x_1260_; uint32_t v___x_1261_; uint32_t v___x_1262_; uint8_t v___x_1263_; 
v___x_1260_ = 8388607;
v___x_1261_ = lean_uint32_land(v___y_1194_, v___x_1260_);
v___x_1262_ = 0;
v___x_1263_ = lean_uint32_dec_eq(v___x_1261_, v___x_1262_);
if (v___x_1263_ == 0)
{
v___y_1244_ = v___x_1259_;
goto v___jp_1243_;
}
else
{
goto v___jp_1233_;
}
}
}
else
{
uint32_t v___x_1264_; 
v___x_1264_ = lean_float32_to_bits(v_result_1253_);
return v___x_1264_;
}
}
v___jp_1265_:
{
if (v___y_1267_ == 0)
{
float v___x_1268_; 
v___x_1268_ = lean_float32_of_bits(v___y_1195_);
v___y_1251_ = v___y_1266_;
v___y_1252_ = v___x_1268_;
goto v___jp_1250_;
}
else
{
uint32_t v___x_1269_; uint32_t v___x_1270_; uint32_t v___x_1271_; uint32_t v___x_1272_; float v___x_1273_; lean_object* v___x_1274_; uint32_t v___x_1275_; uint32_t v___x_1276_; lean_object* v___x_1277_; lean_object* v___x_1278_; float v___x_1279_; float v___x_1280_; 
v___x_1269_ = 8388607;
v___x_1270_ = lean_uint32_land(v___y_1195_, v___x_1269_);
v___x_1271_ = 8388608;
v___x_1272_ = lean_uint32_lor(v___x_1270_, v___x_1271_);
v___x_1273_ = lean_uint32_to_float32(v___x_1272_);
v___x_1274_ = lp_competition_R2W01b_scaleTable;
v___x_1275_ = 23;
v___x_1276_ = lean_uint32_shift_right(v___y_1195_, v___x_1275_);
v___x_1277_ = lean_uint32_to_nat(v___x_1276_);
v___x_1278_ = lean_array_fget_borrowed(v___x_1274_, v___x_1277_);
lean_dec(v___x_1277_);
v___x_1279_ = lean_unbox_float32(v___x_1278_);
v___x_1280_ = lean_float32_mul(v___x_1273_, v___x_1279_);
v___y_1251_ = v___y_1266_;
v___y_1252_ = v___x_1280_;
goto v___jp_1250_;
}
}
v___jp_1281_:
{
uint32_t v___x_1283_; uint32_t v_a_1284_; uint32_t v___x_1285_; uint32_t v___x_1286_; uint32_t v___x_1287_; uint8_t v___x_1288_; 
v___x_1283_ = 2147483647;
v_a_1284_ = lean_uint32_land(v___y_1195_, v___x_1283_);
v___x_1285_ = 201326591;
v___x_1286_ = 1;
v___x_1287_ = lean_uint32_sub(v_a_1284_, v___x_1286_);
v___x_1288_ = lean_uint32_dec_le(v___x_1285_, v___x_1287_);
if (v___x_1288_ == 0)
{
v___y_1266_ = v___y_1282_;
v___y_1267_ = v___x_1288_;
goto v___jp_1265_;
}
else
{
uint32_t v___x_1289_; uint8_t v___x_1290_; 
v___x_1289_ = 2139095040;
v___x_1290_ = lean_uint32_dec_lt(v_a_1284_, v___x_1289_);
v___y_1266_ = v___y_1282_;
v___y_1267_ = v___x_1290_;
goto v___jp_1265_;
}
}
v___jp_1291_:
{
uint32_t v___x_1293_; uint32_t v___x_1294_; 
v___x_1293_ = 8388608;
v___x_1294_ = lean_uint32_lor(v___y_1292_, v___x_1293_);
return v___x_1294_;
}
v___jp_1295_:
{
uint32_t v___x_1297_; uint32_t v___x_1298_; 
v___x_1297_ = 8388608;
v___x_1298_ = lean_uint32_lor(v___y_1296_, v___x_1297_);
return v___x_1298_;
}
v___jp_1299_:
{
uint32_t v___x_1303_; uint32_t v___x_1304_; 
v___x_1303_ = lean_uint32_land(v___y_1301_, v___y_1300_);
v___x_1304_ = lean_uint32_lor(v___y_1302_, v___x_1303_);
return v___x_1304_;
}
v___jp_1305_:
{
uint8_t v___x_1310_; 
v___x_1310_ = lean_uint64_dec_eq(v___y_1309_, v___y_1307_);
if (v___x_1310_ == 0)
{
uint64_t v___x_1311_; uint8_t v___x_1312_; 
v___x_1311_ = 8388608ULL;
v___x_1312_ = lean_uint64_dec_eq(v___y_1309_, v___x_1311_);
if (v___x_1312_ == 0)
{
uint32_t v___x_1313_; 
v___x_1313_ = lean_uint64_to_uint32(v___y_1309_);
if (v___y_1308_ == 0)
{
uint32_t v___x_1314_; 
v___x_1314_ = 0;
v___y_1300_ = v___y_1306_;
v___y_1301_ = v___x_1313_;
v___y_1302_ = v___x_1314_;
goto v___jp_1299_;
}
else
{
uint32_t v___x_1315_; 
v___x_1315_ = 2147483648;
v___y_1300_ = v___y_1306_;
v___y_1301_ = v___x_1313_;
v___y_1302_ = v___x_1315_;
goto v___jp_1299_;
}
}
else
{
if (v___y_1308_ == 0)
{
uint32_t v___x_1316_; 
v___x_1316_ = 0;
v___y_1296_ = v___x_1316_;
goto v___jp_1295_;
}
else
{
uint32_t v___x_1317_; 
v___x_1317_ = 2147483648;
v___y_1296_ = v___x_1317_;
goto v___jp_1295_;
}
}
}
else
{
if (v___y_1308_ == 0)
{
uint32_t v___x_1318_; 
v___x_1318_ = 0;
return v___x_1318_;
}
else
{
uint32_t v___x_1319_; 
v___x_1319_ = 2147483648;
return v___x_1319_;
}
}
}
v___jp_1320_:
{
uint32_t v___x_1324_; uint32_t v___x_1325_; 
v___x_1324_ = lean_uint32_land(v___y_1322_, v___y_1321_);
v___x_1325_ = lean_uint32_lor(v___y_1323_, v___x_1324_);
return v___x_1325_;
}
v___jp_1326_:
{
uint8_t v___x_1331_; 
v___x_1331_ = lean_uint64_dec_eq(v___y_1330_, v___y_1329_);
if (v___x_1331_ == 0)
{
uint64_t v___x_1332_; uint8_t v___x_1333_; 
v___x_1332_ = 8388608ULL;
v___x_1333_ = lean_uint64_dec_eq(v___y_1330_, v___x_1332_);
if (v___x_1333_ == 0)
{
uint32_t v___x_1334_; 
v___x_1334_ = lean_uint64_to_uint32(v___y_1330_);
if (v___y_1328_ == 0)
{
uint32_t v___x_1335_; 
v___x_1335_ = 0;
v___y_1321_ = v___y_1327_;
v___y_1322_ = v___x_1334_;
v___y_1323_ = v___x_1335_;
goto v___jp_1320_;
}
else
{
uint32_t v___x_1336_; 
v___x_1336_ = 2147483648;
v___y_1321_ = v___y_1327_;
v___y_1322_ = v___x_1334_;
v___y_1323_ = v___x_1336_;
goto v___jp_1320_;
}
}
else
{
if (v___y_1328_ == 0)
{
uint32_t v___x_1337_; 
v___x_1337_ = 0;
v___y_1292_ = v___x_1337_;
goto v___jp_1291_;
}
else
{
uint32_t v___x_1338_; 
v___x_1338_ = 2147483648;
v___y_1292_ = v___x_1338_;
goto v___jp_1291_;
}
}
}
else
{
if (v___y_1328_ == 0)
{
uint32_t v___x_1339_; 
v___x_1339_ = 0;
return v___x_1339_;
}
else
{
uint32_t v___x_1340_; 
v___x_1340_ = 2147483648;
return v___x_1340_;
}
}
}
v___jp_1343_:
{
if (v___y_1344_ == 0)
{
float v___x_1345_; 
v___x_1345_ = lean_float32_of_bits(v___y_1194_);
v___y_1282_ = v___x_1345_;
goto v___jp_1281_;
}
else
{
uint32_t v___x_1346_; uint32_t v___x_1347_; uint32_t v___x_1348_; uint32_t v___x_1349_; float v___x_1350_; lean_object* v___x_1351_; lean_object* v___x_1352_; lean_object* v___x_1353_; float v___x_1354_; float v___x_1355_; 
v___x_1346_ = 8388607;
v___x_1347_ = lean_uint32_land(v___y_1194_, v___x_1346_);
v___x_1348_ = 8388608;
v___x_1349_ = lean_uint32_lor(v___x_1347_, v___x_1348_);
v___x_1350_ = lean_uint32_to_float32(v___x_1349_);
v___x_1351_ = lp_competition_R2W01b_scaleTable;
v___x_1352_ = lean_uint32_to_nat(v___x_1342_);
v___x_1353_ = lean_array_fget_borrowed(v___x_1351_, v___x_1352_);
lean_dec(v___x_1352_);
v___x_1354_ = lean_unbox_float32(v___x_1353_);
v___x_1355_ = lean_float32_mul(v___x_1350_, v___x_1354_);
v___y_1282_ = v___x_1355_;
goto v___jp_1281_;
}
}
v___jp_1357_:
{
uint32_t v___x_1362_; uint32_t v___x_1363_; uint32_t v___x_1364_; uint32_t v___x_1365_; uint32_t v___x_1366_; 
v___x_1362_ = lean_uint32_land(v___y_1359_, v___x_1356_);
v___x_1363_ = lean_uint32_shift_left(v___x_1362_, v___x_1341_);
v___x_1364_ = lean_uint32_lor(v___y_1361_, v___x_1363_);
v___x_1365_ = lean_uint32_land(v___y_1360_, v___y_1358_);
v___x_1366_ = lean_uint32_lor(v___x_1364_, v___x_1365_);
return v___x_1366_;
}
v___jp_1367_:
{
if (v___y_1369_ == 0)
{
uint32_t v___x_1372_; 
v___x_1372_ = 0;
v___y_1358_ = v___y_1368_;
v___y_1359_ = v___y_1370_;
v___y_1360_ = v___y_1371_;
v___y_1361_ = v___x_1372_;
goto v___jp_1357_;
}
else
{
uint32_t v___x_1373_; 
v___x_1373_ = 2147483648;
v___y_1358_ = v___y_1368_;
v___y_1359_ = v___y_1370_;
v___y_1360_ = v___y_1371_;
v___y_1361_ = v___x_1373_;
goto v___jp_1357_;
}
}
v___jp_1374_:
{
uint64_t v___x_1380_; uint64_t v_encodedExponent_1381_; uint32_t v___x_1382_; uint64_t v___x_1383_; uint8_t v___x_1384_; 
v___x_1380_ = 171ULL;
v_encodedExponent_1381_ = lean_uint64_sub(v___y_1378_, v___x_1380_);
v___x_1382_ = lean_uint64_to_uint32(v_encodedExponent_1381_);
v___x_1383_ = 8388608ULL;
v___x_1384_ = lean_uint64_dec_lt(v___y_1379_, v___x_1383_);
if (v___x_1384_ == 0)
{
uint64_t v___x_1385_; uint32_t v___x_1386_; 
v___x_1385_ = lean_uint64_sub(v___y_1379_, v___x_1383_);
v___x_1386_ = lean_uint64_to_uint32(v___x_1385_);
v___y_1368_ = v___y_1375_;
v___y_1369_ = v___y_1377_;
v___y_1370_ = v___x_1382_;
v___y_1371_ = v___x_1386_;
goto v___jp_1367_;
}
else
{
uint32_t v___x_1387_; 
v___x_1387_ = lean_uint64_to_uint32(v___y_1376_);
v___y_1368_ = v___y_1375_;
v___y_1369_ = v___y_1377_;
v___y_1370_ = v___x_1382_;
v___y_1371_ = v___x_1387_;
goto v___jp_1367_;
}
}
v___jp_1388_:
{
uint64_t v___x_1395_; uint8_t v___x_1396_; 
v___x_1395_ = 425ULL;
v___x_1396_ = lean_uint64_dec_lt(v___x_1395_, v___y_1394_);
if (v___x_1396_ == 0)
{
if (v___y_1390_ == 0)
{
v___y_1375_ = v___y_1389_;
v___y_1376_ = v___y_1391_;
v___y_1377_ = v___y_1392_;
v___y_1378_ = v___y_1394_;
v___y_1379_ = v___y_1393_;
goto v___jp_1374_;
}
else
{
uint64_t v___x_1397_; 
v___x_1397_ = 8388608ULL;
v___y_1375_ = v___y_1389_;
v___y_1376_ = v___y_1391_;
v___y_1377_ = v___y_1392_;
v___y_1378_ = v___y_1394_;
v___y_1379_ = v___x_1397_;
goto v___jp_1374_;
}
}
else
{
if (v___y_1392_ == 0)
{
uint32_t v___x_1398_; 
v___x_1398_ = 2139095040;
return v___x_1398_;
}
else
{
uint32_t v___x_1399_; 
v___x_1399_ = 4286578688;
return v___x_1399_;
}
}
}
v___jp_1400_:
{
uint64_t v___x_1406_; uint8_t v_carry_1407_; 
v___x_1406_ = 16777216ULL;
v_carry_1407_ = lean_uint64_dec_eq(v___y_1405_, v___x_1406_);
if (v_carry_1407_ == 0)
{
v___y_1389_ = v___y_1401_;
v___y_1390_ = v_carry_1407_;
v___y_1391_ = v___y_1403_;
v___y_1392_ = v___y_1404_;
v___y_1393_ = v___y_1405_;
v___y_1394_ = v___y_1402_;
goto v___jp_1388_;
}
else
{
uint64_t v___x_1408_; uint64_t v___x_1409_; 
v___x_1408_ = 1ULL;
v___x_1409_ = lean_uint64_add(v___y_1402_, v___x_1408_);
v___y_1389_ = v___y_1401_;
v___y_1390_ = v_carry_1407_;
v___y_1391_ = v___y_1403_;
v___y_1392_ = v___y_1404_;
v___y_1393_ = v___y_1405_;
v___y_1394_ = v___x_1409_;
goto v___jp_1388_;
}
}
v___jp_1410_:
{
uint64_t v_position_1417_; uint64_t v___x_1418_; uint8_t v___x_1419_; 
v_position_1417_ = lean_uint64_add(v___y_1416_, v___y_1415_);
v___x_1418_ = 172ULL;
v___x_1419_ = lean_uint64_dec_lt(v_position_1417_, v___x_1418_);
if (v___x_1419_ == 0)
{
uint64_t v___x_1420_; uint8_t v___x_1421_; 
v___x_1420_ = 23ULL;
v___x_1421_ = lean_uint64_dec_lt(v___y_1416_, v___x_1420_);
if (v___x_1421_ == 0)
{
uint64_t v___x_1422_; uint8_t v___x_1423_; 
v___x_1422_ = lean_uint64_sub(v___y_1416_, v___x_1420_);
v___x_1423_ = lean_uint64_dec_eq(v___x_1422_, v___y_1412_);
if (v___x_1423_ == 0)
{
uint64_t v___x_1424_; uint8_t v___x_1425_; 
v___x_1424_ = 64ULL;
v___x_1425_ = lean_uint64_dec_lt(v___x_1422_, v___x_1424_);
if (v___x_1425_ == 0)
{
uint8_t v___x_1426_; 
v___x_1426_ = lean_uint64_dec_eq(v___x_1422_, v___x_1424_);
if (v___x_1426_ == 0)
{
v___y_1401_ = v___y_1411_;
v___y_1402_ = v_position_1417_;
v___y_1403_ = v___y_1412_;
v___y_1404_ = v___y_1413_;
v___y_1405_ = v___y_1412_;
goto v___jp_1400_;
}
else
{
uint64_t v___x_1427_; uint8_t v___x_1428_; 
v___x_1427_ = 9223372036854775808ULL;
v___x_1428_ = lean_uint64_dec_lt(v___x_1427_, v___y_1414_);
if (v___x_1428_ == 0)
{
v___y_1401_ = v___y_1411_;
v___y_1402_ = v_position_1417_;
v___y_1403_ = v___y_1412_;
v___y_1404_ = v___y_1413_;
v___y_1405_ = v___y_1412_;
goto v___jp_1400_;
}
else
{
uint64_t v___x_1429_; 
v___x_1429_ = 1ULL;
v___y_1401_ = v___y_1411_;
v___y_1402_ = v_position_1417_;
v___y_1403_ = v___y_1412_;
v___y_1404_ = v___y_1413_;
v___y_1405_ = v___x_1429_;
goto v___jp_1400_;
}
}
}
else
{
uint64_t v_quotient_1430_; uint64_t v___x_1431_; uint64_t v___x_1432_; uint64_t v___x_1433_; uint64_t v_remainder_1434_; uint64_t v___x_1435_; uint64_t v_half_1436_; uint8_t v___x_1437_; 
v_quotient_1430_ = lean_uint64_shift_right(v___y_1414_, v___x_1422_);
v___x_1431_ = 1ULL;
v___x_1432_ = lean_uint64_shift_left(v___x_1431_, v___x_1422_);
v___x_1433_ = lean_uint64_sub(v___x_1432_, v___x_1431_);
v_remainder_1434_ = lean_uint64_land(v___y_1414_, v___x_1433_);
v___x_1435_ = lean_uint64_sub(v___x_1422_, v___x_1431_);
v_half_1436_ = lean_uint64_shift_left(v___x_1431_, v___x_1435_);
v___x_1437_ = lean_uint64_dec_lt(v_remainder_1434_, v_half_1436_);
if (v___x_1437_ == 0)
{
uint8_t v___x_1438_; 
v___x_1438_ = lean_uint64_dec_lt(v_half_1436_, v_remainder_1434_);
if (v___x_1438_ == 0)
{
uint64_t v___x_1439_; uint8_t v___x_1440_; 
v___x_1439_ = lean_uint64_land(v_quotient_1430_, v___x_1431_);
v___x_1440_ = lean_uint64_dec_eq(v___x_1439_, v___y_1412_);
if (v___x_1440_ == 0)
{
uint64_t v___x_1441_; 
v___x_1441_ = lean_uint64_add(v_quotient_1430_, v___x_1431_);
v___y_1401_ = v___y_1411_;
v___y_1402_ = v_position_1417_;
v___y_1403_ = v___y_1412_;
v___y_1404_ = v___y_1413_;
v___y_1405_ = v___x_1441_;
goto v___jp_1400_;
}
else
{
v___y_1401_ = v___y_1411_;
v___y_1402_ = v_position_1417_;
v___y_1403_ = v___y_1412_;
v___y_1404_ = v___y_1413_;
v___y_1405_ = v_quotient_1430_;
goto v___jp_1400_;
}
}
else
{
uint64_t v___x_1442_; 
v___x_1442_ = lean_uint64_add(v_quotient_1430_, v___x_1431_);
v___y_1401_ = v___y_1411_;
v___y_1402_ = v_position_1417_;
v___y_1403_ = v___y_1412_;
v___y_1404_ = v___y_1413_;
v___y_1405_ = v___x_1442_;
goto v___jp_1400_;
}
}
else
{
v___y_1401_ = v___y_1411_;
v___y_1402_ = v_position_1417_;
v___y_1403_ = v___y_1412_;
v___y_1404_ = v___y_1413_;
v___y_1405_ = v_quotient_1430_;
goto v___jp_1400_;
}
}
}
else
{
v___y_1401_ = v___y_1411_;
v___y_1402_ = v_position_1417_;
v___y_1403_ = v___y_1412_;
v___y_1404_ = v___y_1413_;
v___y_1405_ = v___y_1414_;
goto v___jp_1400_;
}
}
else
{
uint64_t v___x_1443_; uint64_t v___x_1444_; 
v___x_1443_ = lean_uint64_sub(v___x_1420_, v___y_1416_);
v___x_1444_ = lean_uint64_shift_left(v___y_1414_, v___x_1443_);
v___y_1401_ = v___y_1411_;
v___y_1402_ = v_position_1417_;
v___y_1403_ = v___y_1412_;
v___y_1404_ = v___y_1413_;
v___y_1405_ = v___x_1444_;
goto v___jp_1400_;
}
}
else
{
uint64_t v___x_1445_; uint8_t v___x_1446_; 
v___x_1445_ = 149ULL;
v___x_1446_ = lean_uint64_dec_lt(v___y_1415_, v___x_1445_);
if (v___x_1446_ == 0)
{
uint64_t v___x_1447_; uint64_t v___x_1448_; 
v___x_1447_ = lean_uint64_sub(v___y_1415_, v___x_1445_);
v___x_1448_ = lean_uint64_shift_left(v___y_1414_, v___x_1447_);
v___y_1306_ = v___y_1411_;
v___y_1307_ = v___y_1412_;
v___y_1308_ = v___y_1413_;
v___y_1309_ = v___x_1448_;
goto v___jp_1305_;
}
else
{
uint64_t v___x_1449_; uint8_t v___x_1450_; 
v___x_1449_ = lean_uint64_sub(v___x_1445_, v___y_1415_);
v___x_1450_ = lean_uint64_dec_eq(v___x_1449_, v___y_1412_);
if (v___x_1450_ == 0)
{
uint64_t v___x_1451_; uint8_t v___x_1452_; 
v___x_1451_ = 64ULL;
v___x_1452_ = lean_uint64_dec_lt(v___x_1449_, v___x_1451_);
if (v___x_1452_ == 0)
{
uint8_t v___x_1453_; 
v___x_1453_ = lean_uint64_dec_eq(v___x_1449_, v___x_1451_);
if (v___x_1453_ == 0)
{
v___y_1306_ = v___y_1411_;
v___y_1307_ = v___y_1412_;
v___y_1308_ = v___y_1413_;
v___y_1309_ = v___y_1412_;
goto v___jp_1305_;
}
else
{
uint64_t v___x_1454_; uint8_t v___x_1455_; 
v___x_1454_ = 9223372036854775808ULL;
v___x_1455_ = lean_uint64_dec_lt(v___x_1454_, v___y_1414_);
if (v___x_1455_ == 0)
{
v___y_1306_ = v___y_1411_;
v___y_1307_ = v___y_1412_;
v___y_1308_ = v___y_1413_;
v___y_1309_ = v___y_1412_;
goto v___jp_1305_;
}
else
{
uint64_t v___x_1456_; 
v___x_1456_ = 1ULL;
v___y_1306_ = v___y_1411_;
v___y_1307_ = v___y_1412_;
v___y_1308_ = v___y_1413_;
v___y_1309_ = v___x_1456_;
goto v___jp_1305_;
}
}
}
else
{
uint64_t v_quotient_1457_; uint64_t v___x_1458_; uint64_t v___x_1459_; uint64_t v___x_1460_; uint64_t v_remainder_1461_; uint64_t v___x_1462_; uint64_t v_half_1463_; uint8_t v___x_1464_; 
v_quotient_1457_ = lean_uint64_shift_right(v___y_1414_, v___x_1449_);
v___x_1458_ = 1ULL;
v___x_1459_ = lean_uint64_shift_left(v___x_1458_, v___x_1449_);
v___x_1460_ = lean_uint64_sub(v___x_1459_, v___x_1458_);
v_remainder_1461_ = lean_uint64_land(v___y_1414_, v___x_1460_);
v___x_1462_ = lean_uint64_sub(v___x_1449_, v___x_1458_);
v_half_1463_ = lean_uint64_shift_left(v___x_1458_, v___x_1462_);
v___x_1464_ = lean_uint64_dec_lt(v_remainder_1461_, v_half_1463_);
if (v___x_1464_ == 0)
{
uint8_t v___x_1465_; 
v___x_1465_ = lean_uint64_dec_lt(v_half_1463_, v_remainder_1461_);
if (v___x_1465_ == 0)
{
uint64_t v___x_1466_; uint8_t v___x_1467_; 
v___x_1466_ = lean_uint64_land(v_quotient_1457_, v___x_1458_);
v___x_1467_ = lean_uint64_dec_eq(v___x_1466_, v___y_1412_);
if (v___x_1467_ == 0)
{
uint64_t v___x_1468_; 
v___x_1468_ = lean_uint64_add(v_quotient_1457_, v___x_1458_);
v___y_1306_ = v___y_1411_;
v___y_1307_ = v___y_1412_;
v___y_1308_ = v___y_1413_;
v___y_1309_ = v___x_1468_;
goto v___jp_1305_;
}
else
{
v___y_1306_ = v___y_1411_;
v___y_1307_ = v___y_1412_;
v___y_1308_ = v___y_1413_;
v___y_1309_ = v_quotient_1457_;
goto v___jp_1305_;
}
}
else
{
uint64_t v___x_1469_; 
v___x_1469_ = lean_uint64_add(v_quotient_1457_, v___x_1458_);
v___y_1306_ = v___y_1411_;
v___y_1307_ = v___y_1412_;
v___y_1308_ = v___y_1413_;
v___y_1309_ = v___x_1469_;
goto v___jp_1305_;
}
}
else
{
v___y_1306_ = v___y_1411_;
v___y_1307_ = v___y_1412_;
v___y_1308_ = v___y_1413_;
v___y_1309_ = v_quotient_1457_;
goto v___jp_1305_;
}
}
}
else
{
v___y_1306_ = v___y_1411_;
v___y_1307_ = v___y_1412_;
v___y_1308_ = v___y_1413_;
v___y_1309_ = v___y_1414_;
goto v___jp_1305_;
}
}
}
}
v___jp_1470_:
{
uint64_t v___x_1478_; uint64_t v___x_1479_; uint8_t v___x_1480_; 
v___x_1478_ = 1ULL;
v___x_1479_ = lean_uint64_shift_right(v___y_1473_, v___x_1478_);
v___x_1480_ = lean_uint64_dec_eq(v___x_1479_, v___y_1472_);
if (v___x_1480_ == 0)
{
uint64_t v___x_1481_; 
v___x_1481_ = lean_uint64_add(v___y_1477_, v___x_1478_);
v___y_1411_ = v___y_1471_;
v___y_1412_ = v___y_1472_;
v___y_1413_ = v___y_1474_;
v___y_1414_ = v___y_1475_;
v___y_1415_ = v___y_1476_;
v___y_1416_ = v___x_1481_;
goto v___jp_1410_;
}
else
{
v___y_1411_ = v___y_1471_;
v___y_1412_ = v___y_1472_;
v___y_1413_ = v___y_1474_;
v___y_1414_ = v___y_1475_;
v___y_1415_ = v___y_1476_;
v___y_1416_ = v___y_1477_;
goto v___jp_1410_;
}
}
v___jp_1482_:
{
uint64_t v___x_1492_; uint8_t v___x_1493_; 
v___x_1492_ = lean_uint64_shift_right(v___y_1484_, v___y_1486_);
v___x_1493_ = lean_uint64_dec_eq(v___x_1492_, v___y_1487_);
if (v___x_1493_ == 0)
{
uint64_t v___x_1494_; 
v___x_1494_ = lean_uint64_add(v___y_1485_, v___y_1486_);
v___y_1471_ = v___y_1483_;
v___y_1472_ = v___y_1487_;
v___y_1473_ = v___y_1491_;
v___y_1474_ = v___y_1488_;
v___y_1475_ = v___y_1489_;
v___y_1476_ = v___y_1490_;
v___y_1477_ = v___x_1494_;
goto v___jp_1470_;
}
else
{
v___y_1471_ = v___y_1483_;
v___y_1472_ = v___y_1487_;
v___y_1473_ = v___y_1491_;
v___y_1474_ = v___y_1488_;
v___y_1475_ = v___y_1489_;
v___y_1476_ = v___y_1490_;
v___y_1477_ = v___y_1485_;
goto v___jp_1470_;
}
}
v___jp_1495_:
{
uint64_t v___x_1503_; uint64_t v___x_1504_; uint8_t v___x_1505_; 
v___x_1503_ = 2ULL;
v___x_1504_ = lean_uint64_shift_right(v___y_1497_, v___x_1503_);
v___x_1505_ = lean_uint64_dec_eq(v___x_1504_, v___y_1498_);
if (v___x_1505_ == 0)
{
v___y_1483_ = v___y_1496_;
v___y_1484_ = v___y_1497_;
v___y_1485_ = v___y_1502_;
v___y_1486_ = v___x_1503_;
v___y_1487_ = v___y_1498_;
v___y_1488_ = v___y_1499_;
v___y_1489_ = v___y_1500_;
v___y_1490_ = v___y_1501_;
v___y_1491_ = v___x_1504_;
goto v___jp_1482_;
}
else
{
v___y_1483_ = v___y_1496_;
v___y_1484_ = v___y_1497_;
v___y_1485_ = v___y_1502_;
v___y_1486_ = v___x_1503_;
v___y_1487_ = v___y_1498_;
v___y_1488_ = v___y_1499_;
v___y_1489_ = v___y_1500_;
v___y_1490_ = v___y_1501_;
v___y_1491_ = v___y_1497_;
goto v___jp_1482_;
}
}
v___jp_1506_:
{
uint64_t v___x_1516_; uint8_t v___x_1517_; 
v___x_1516_ = lean_uint64_shift_right(v___y_1508_, v___y_1510_);
v___x_1517_ = lean_uint64_dec_eq(v___x_1516_, v___y_1511_);
if (v___x_1517_ == 0)
{
uint64_t v___x_1518_; 
v___x_1518_ = lean_uint64_add(v___y_1509_, v___y_1510_);
v___y_1496_ = v___y_1507_;
v___y_1497_ = v___y_1515_;
v___y_1498_ = v___y_1511_;
v___y_1499_ = v___y_1512_;
v___y_1500_ = v___y_1513_;
v___y_1501_ = v___y_1514_;
v___y_1502_ = v___x_1518_;
goto v___jp_1495_;
}
else
{
v___y_1496_ = v___y_1507_;
v___y_1497_ = v___y_1515_;
v___y_1498_ = v___y_1511_;
v___y_1499_ = v___y_1512_;
v___y_1500_ = v___y_1513_;
v___y_1501_ = v___y_1514_;
v___y_1502_ = v___y_1509_;
goto v___jp_1495_;
}
}
v___jp_1519_:
{
uint64_t v___x_1527_; uint64_t v___x_1528_; uint8_t v___x_1529_; 
v___x_1527_ = 4ULL;
v___x_1528_ = lean_uint64_shift_right(v___y_1521_, v___x_1527_);
v___x_1529_ = lean_uint64_dec_eq(v___x_1528_, v___y_1522_);
if (v___x_1529_ == 0)
{
v___y_1507_ = v___y_1520_;
v___y_1508_ = v___y_1521_;
v___y_1509_ = v___y_1526_;
v___y_1510_ = v___x_1527_;
v___y_1511_ = v___y_1522_;
v___y_1512_ = v___y_1523_;
v___y_1513_ = v___y_1524_;
v___y_1514_ = v___y_1525_;
v___y_1515_ = v___x_1528_;
goto v___jp_1506_;
}
else
{
v___y_1507_ = v___y_1520_;
v___y_1508_ = v___y_1521_;
v___y_1509_ = v___y_1526_;
v___y_1510_ = v___x_1527_;
v___y_1511_ = v___y_1522_;
v___y_1512_ = v___y_1523_;
v___y_1513_ = v___y_1524_;
v___y_1514_ = v___y_1525_;
v___y_1515_ = v___y_1521_;
goto v___jp_1506_;
}
}
v___jp_1530_:
{
uint64_t v___x_1540_; uint8_t v___x_1541_; 
v___x_1540_ = lean_uint64_shift_right(v___y_1534_, v___y_1531_);
v___x_1541_ = lean_uint64_dec_eq(v___x_1540_, v___y_1535_);
if (v___x_1541_ == 0)
{
uint64_t v___x_1542_; 
v___x_1542_ = lean_uint64_add(v___y_1533_, v___y_1531_);
v___y_1520_ = v___y_1532_;
v___y_1521_ = v___y_1539_;
v___y_1522_ = v___y_1535_;
v___y_1523_ = v___y_1536_;
v___y_1524_ = v___y_1537_;
v___y_1525_ = v___y_1538_;
v___y_1526_ = v___x_1542_;
goto v___jp_1519_;
}
else
{
v___y_1520_ = v___y_1532_;
v___y_1521_ = v___y_1539_;
v___y_1522_ = v___y_1535_;
v___y_1523_ = v___y_1536_;
v___y_1524_ = v___y_1537_;
v___y_1525_ = v___y_1538_;
v___y_1526_ = v___y_1533_;
goto v___jp_1519_;
}
}
v___jp_1543_:
{
uint64_t v___x_1551_; uint64_t v___x_1552_; uint8_t v___x_1553_; 
v___x_1551_ = 8ULL;
v___x_1552_ = lean_uint64_shift_right(v___y_1545_, v___x_1551_);
v___x_1553_ = lean_uint64_dec_eq(v___x_1552_, v___y_1546_);
if (v___x_1553_ == 0)
{
v___y_1531_ = v___x_1551_;
v___y_1532_ = v___y_1544_;
v___y_1533_ = v___y_1550_;
v___y_1534_ = v___y_1545_;
v___y_1535_ = v___y_1546_;
v___y_1536_ = v___y_1547_;
v___y_1537_ = v___y_1548_;
v___y_1538_ = v___y_1549_;
v___y_1539_ = v___x_1552_;
goto v___jp_1530_;
}
else
{
v___y_1531_ = v___x_1551_;
v___y_1532_ = v___y_1544_;
v___y_1533_ = v___y_1550_;
v___y_1534_ = v___y_1545_;
v___y_1535_ = v___y_1546_;
v___y_1536_ = v___y_1547_;
v___y_1537_ = v___y_1548_;
v___y_1538_ = v___y_1549_;
v___y_1539_ = v___y_1545_;
goto v___jp_1530_;
}
}
v___jp_1554_:
{
uint64_t v___x_1564_; uint8_t v___x_1565_; 
v___x_1564_ = lean_uint64_shift_right(v___y_1558_, v___y_1556_);
v___x_1565_ = lean_uint64_dec_eq(v___x_1564_, v___y_1559_);
if (v___x_1565_ == 0)
{
uint64_t v___x_1566_; 
v___x_1566_ = lean_uint64_add(v___y_1557_, v___y_1556_);
v___y_1544_ = v___y_1555_;
v___y_1545_ = v___y_1563_;
v___y_1546_ = v___y_1559_;
v___y_1547_ = v___y_1560_;
v___y_1548_ = v___y_1561_;
v___y_1549_ = v___y_1562_;
v___y_1550_ = v___x_1566_;
goto v___jp_1543_;
}
else
{
v___y_1544_ = v___y_1555_;
v___y_1545_ = v___y_1563_;
v___y_1546_ = v___y_1559_;
v___y_1547_ = v___y_1560_;
v___y_1548_ = v___y_1561_;
v___y_1549_ = v___y_1562_;
v___y_1550_ = v___y_1557_;
goto v___jp_1543_;
}
}
v___jp_1567_:
{
uint64_t v___x_1575_; uint64_t v___x_1576_; uint8_t v___x_1577_; 
v___x_1575_ = 16ULL;
v___x_1576_ = lean_uint64_shift_right(v___y_1569_, v___x_1575_);
v___x_1577_ = lean_uint64_dec_eq(v___x_1576_, v___y_1570_);
if (v___x_1577_ == 0)
{
v___y_1555_ = v___y_1568_;
v___y_1556_ = v___x_1575_;
v___y_1557_ = v___y_1574_;
v___y_1558_ = v___y_1569_;
v___y_1559_ = v___y_1570_;
v___y_1560_ = v___y_1571_;
v___y_1561_ = v___y_1572_;
v___y_1562_ = v___y_1573_;
v___y_1563_ = v___x_1576_;
goto v___jp_1554_;
}
else
{
v___y_1555_ = v___y_1568_;
v___y_1556_ = v___x_1575_;
v___y_1557_ = v___y_1574_;
v___y_1558_ = v___y_1569_;
v___y_1559_ = v___y_1570_;
v___y_1560_ = v___y_1571_;
v___y_1561_ = v___y_1572_;
v___y_1562_ = v___y_1573_;
v___y_1563_ = v___y_1569_;
goto v___jp_1554_;
}
}
v___jp_1578_:
{
uint64_t v___x_1586_; uint8_t v___x_1587_; 
v___x_1586_ = lean_uint64_shift_right(v___y_1582_, v___y_1583_);
v___x_1587_ = lean_uint64_dec_eq(v___x_1586_, v___y_1580_);
if (v___x_1587_ == 0)
{
v___y_1568_ = v___y_1579_;
v___y_1569_ = v___y_1585_;
v___y_1570_ = v___y_1580_;
v___y_1571_ = v___y_1581_;
v___y_1572_ = v___y_1582_;
v___y_1573_ = v___y_1584_;
v___y_1574_ = v___y_1583_;
goto v___jp_1567_;
}
else
{
v___y_1568_ = v___y_1579_;
v___y_1569_ = v___y_1585_;
v___y_1570_ = v___y_1580_;
v___y_1571_ = v___y_1581_;
v___y_1572_ = v___y_1582_;
v___y_1573_ = v___y_1584_;
v___y_1574_ = v___y_1580_;
goto v___jp_1567_;
}
}
v___jp_1588_:
{
uint64_t v___x_1593_; uint8_t v___x_1594_; 
v___x_1593_ = 0ULL;
v___x_1594_ = lean_uint64_dec_eq(v___y_1591_, v___x_1593_);
if (v___x_1594_ == 0)
{
uint64_t v___x_1595_; uint64_t v___x_1596_; uint8_t v___x_1597_; 
v___x_1595_ = 32ULL;
v___x_1596_ = lean_uint64_shift_right(v___y_1591_, v___x_1595_);
v___x_1597_ = lean_uint64_dec_eq(v___x_1596_, v___x_1593_);
if (v___x_1597_ == 0)
{
v___y_1579_ = v___y_1589_;
v___y_1580_ = v___x_1593_;
v___y_1581_ = v___y_1590_;
v___y_1582_ = v___y_1591_;
v___y_1583_ = v___x_1595_;
v___y_1584_ = v___y_1592_;
v___y_1585_ = v___x_1596_;
goto v___jp_1578_;
}
else
{
v___y_1579_ = v___y_1589_;
v___y_1580_ = v___x_1593_;
v___y_1581_ = v___y_1590_;
v___y_1582_ = v___y_1591_;
v___y_1583_ = v___x_1595_;
v___y_1584_ = v___y_1592_;
v___y_1585_ = v___y_1591_;
goto v___jp_1578_;
}
}
else
{
if (v___y_1590_ == 0)
{
uint32_t v___x_1598_; 
v___x_1598_ = 0;
return v___x_1598_;
}
else
{
uint32_t v___x_1599_; 
v___x_1599_ = 2147483648;
return v___x_1599_;
}
}
}
v___jp_1600_:
{
uint64_t v___x_1607_; uint64_t v___x_1608_; uint64_t v___x_1609_; uint8_t v___x_1610_; 
v___x_1607_ = lean_uint64_mul(v___y_1603_, v___y_1604_);
v___x_1608_ = lean_uint64_add(v___y_1602_, v___y_1606_);
v___x_1609_ = 281474976710656ULL;
v___x_1610_ = lean_uint64_dec_lt(v___x_1607_, v___x_1609_);
if (v___x_1610_ == 0)
{
v___y_1589_ = v___y_1601_;
v___y_1590_ = v___y_1605_;
v___y_1591_ = v___x_1607_;
v___y_1592_ = v___x_1608_;
goto v___jp_1588_;
}
else
{
uint64_t v___x_1611_; uint8_t v___x_1612_; 
v___x_1611_ = 123ULL;
v___x_1612_ = lean_uint64_dec_le(v___x_1608_, v___x_1611_);
if (v___x_1612_ == 0)
{
v___y_1589_ = v___y_1601_;
v___y_1590_ = v___y_1605_;
v___y_1591_ = v___x_1607_;
v___y_1592_ = v___x_1608_;
goto v___jp_1588_;
}
else
{
uint64_t v___x_1613_; uint8_t v___x_1614_; 
v___x_1613_ = 0ULL;
v___x_1614_ = lean_uint64_dec_eq(v___x_1607_, v___x_1613_);
if (v___x_1614_ == 0)
{
uint64_t v___x_1615_; uint64_t v___x_1616_; uint8_t v___x_1617_; 
v___x_1615_ = 149ULL;
v___x_1616_ = lean_uint64_sub(v___x_1615_, v___x_1608_);
v___x_1617_ = lean_uint64_dec_eq(v___x_1616_, v___x_1613_);
if (v___x_1617_ == 0)
{
uint64_t v___x_1618_; uint8_t v___x_1619_; 
v___x_1618_ = 64ULL;
v___x_1619_ = lean_uint64_dec_lt(v___x_1616_, v___x_1618_);
if (v___x_1619_ == 0)
{
uint8_t v___x_1620_; 
v___x_1620_ = lean_uint64_dec_eq(v___x_1616_, v___x_1618_);
if (v___x_1620_ == 0)
{
v___y_1327_ = v___y_1601_;
v___y_1328_ = v___y_1605_;
v___y_1329_ = v___x_1613_;
v___y_1330_ = v___x_1613_;
goto v___jp_1326_;
}
else
{
uint64_t v___x_1621_; uint8_t v___x_1622_; 
v___x_1621_ = 9223372036854775808ULL;
v___x_1622_ = lean_uint64_dec_lt(v___x_1621_, v___x_1607_);
if (v___x_1622_ == 0)
{
v___y_1327_ = v___y_1601_;
v___y_1328_ = v___y_1605_;
v___y_1329_ = v___x_1613_;
v___y_1330_ = v___x_1613_;
goto v___jp_1326_;
}
else
{
uint64_t v___x_1623_; 
v___x_1623_ = 1ULL;
v___y_1327_ = v___y_1601_;
v___y_1328_ = v___y_1605_;
v___y_1329_ = v___x_1613_;
v___y_1330_ = v___x_1623_;
goto v___jp_1326_;
}
}
}
else
{
uint64_t v_quotient_1624_; uint64_t v___x_1625_; uint64_t v___x_1626_; uint64_t v___x_1627_; uint64_t v_remainder_1628_; uint64_t v___x_1629_; uint64_t v_half_1630_; uint8_t v___x_1631_; 
v_quotient_1624_ = lean_uint64_shift_right(v___x_1607_, v___x_1616_);
v___x_1625_ = 1ULL;
v___x_1626_ = lean_uint64_shift_left(v___x_1625_, v___x_1616_);
v___x_1627_ = lean_uint64_sub(v___x_1626_, v___x_1625_);
v_remainder_1628_ = lean_uint64_land(v___x_1607_, v___x_1627_);
v___x_1629_ = lean_uint64_sub(v___x_1616_, v___x_1625_);
v_half_1630_ = lean_uint64_shift_left(v___x_1625_, v___x_1629_);
v___x_1631_ = lean_uint64_dec_lt(v_remainder_1628_, v_half_1630_);
if (v___x_1631_ == 0)
{
uint8_t v___x_1632_; 
v___x_1632_ = lean_uint64_dec_lt(v_half_1630_, v_remainder_1628_);
if (v___x_1632_ == 0)
{
uint64_t v___x_1633_; uint8_t v___x_1634_; 
v___x_1633_ = lean_uint64_land(v_quotient_1624_, v___x_1625_);
v___x_1634_ = lean_uint64_dec_eq(v___x_1633_, v___x_1613_);
if (v___x_1634_ == 0)
{
uint64_t v___x_1635_; 
v___x_1635_ = lean_uint64_add(v_quotient_1624_, v___x_1625_);
v___y_1327_ = v___y_1601_;
v___y_1328_ = v___y_1605_;
v___y_1329_ = v___x_1613_;
v___y_1330_ = v___x_1635_;
goto v___jp_1326_;
}
else
{
v___y_1327_ = v___y_1601_;
v___y_1328_ = v___y_1605_;
v___y_1329_ = v___x_1613_;
v___y_1330_ = v_quotient_1624_;
goto v___jp_1326_;
}
}
else
{
uint64_t v___x_1636_; 
v___x_1636_ = lean_uint64_add(v_quotient_1624_, v___x_1625_);
v___y_1327_ = v___y_1601_;
v___y_1328_ = v___y_1605_;
v___y_1329_ = v___x_1613_;
v___y_1330_ = v___x_1636_;
goto v___jp_1326_;
}
}
else
{
v___y_1327_ = v___y_1601_;
v___y_1328_ = v___y_1605_;
v___y_1329_ = v___x_1613_;
v___y_1330_ = v_quotient_1624_;
goto v___jp_1326_;
}
}
}
else
{
v___y_1327_ = v___y_1601_;
v___y_1328_ = v___y_1605_;
v___y_1329_ = v___x_1613_;
v___y_1330_ = v___x_1607_;
goto v___jp_1326_;
}
}
else
{
if (v___y_1605_ == 0)
{
uint32_t v___x_1637_; 
v___x_1637_ = 0;
return v___x_1637_;
}
else
{
uint32_t v___x_1638_; 
v___x_1638_ = 2147483648;
return v___x_1638_;
}
}
}
}
}
v___jp_1642_:
{
uint64_t v___x_1648_; uint64_t v___x_1649_; uint8_t v___x_1650_; 
v___x_1648_ = lean_uint32_to_uint64(v_ey_1641_);
v___x_1649_ = 0ULL;
v___x_1650_ = lean_uint64_dec_eq(v___x_1648_, v___x_1649_);
if (v___x_1650_ == 0)
{
uint64_t v___x_1651_; uint64_t v___x_1652_; 
v___x_1651_ = 1ULL;
v___x_1652_ = lean_uint64_sub(v___x_1648_, v___x_1651_);
v___y_1601_ = v___y_1643_;
v___y_1602_ = v___y_1647_;
v___y_1603_ = v___y_1644_;
v___y_1604_ = v___y_1645_;
v___y_1605_ = v___y_1646_;
v___y_1606_ = v___x_1652_;
goto v___jp_1600_;
}
else
{
v___y_1601_ = v___y_1643_;
v___y_1602_ = v___y_1647_;
v___y_1603_ = v___y_1644_;
v___y_1604_ = v___y_1645_;
v___y_1605_ = v___y_1646_;
v___y_1606_ = v___x_1649_;
goto v___jp_1600_;
}
}
v___jp_1653_:
{
uint64_t v___x_1658_; uint64_t v___x_1659_; uint8_t v___x_1660_; 
v___x_1658_ = lean_uint32_to_uint64(v_ex_1639_);
v___x_1659_ = 0ULL;
v___x_1660_ = lean_uint64_dec_eq(v___x_1658_, v___x_1659_);
if (v___x_1660_ == 0)
{
uint64_t v___x_1661_; uint64_t v___x_1662_; 
v___x_1661_ = 1ULL;
v___x_1662_ = lean_uint64_sub(v___x_1658_, v___x_1661_);
v___y_1643_ = v___y_1654_;
v___y_1644_ = v___y_1655_;
v___y_1645_ = v___y_1657_;
v___y_1646_ = v___y_1656_;
v___y_1647_ = v___x_1662_;
goto v___jp_1642_;
}
else
{
v___y_1643_ = v___y_1654_;
v___y_1644_ = v___y_1655_;
v___y_1645_ = v___y_1657_;
v___y_1646_ = v___y_1656_;
v___y_1647_ = v___x_1659_;
goto v___jp_1642_;
}
}
v___jp_1663_:
{
uint32_t v___x_1668_; uint8_t v___x_1669_; 
v___x_1668_ = 0;
v___x_1669_ = lean_uint32_dec_eq(v_ey_1641_, v___x_1668_);
if (v___x_1669_ == 0)
{
uint64_t v___x_1670_; uint64_t v___x_1671_; uint64_t v___x_1672_; 
v___x_1670_ = lean_uint32_to_uint64(v___y_1665_);
v___x_1671_ = 8388608ULL;
v___x_1672_ = lean_uint64_lor(v___x_1670_, v___x_1671_);
v___y_1654_ = v___y_1664_;
v___y_1655_ = v___y_1667_;
v___y_1656_ = v___y_1666_;
v___y_1657_ = v___x_1672_;
goto v___jp_1653_;
}
else
{
uint64_t v___x_1673_; 
v___x_1673_ = lean_uint32_to_uint64(v___y_1665_);
v___y_1654_ = v___y_1664_;
v___y_1655_ = v___y_1667_;
v___y_1656_ = v___y_1666_;
v___y_1657_ = v___x_1673_;
goto v___jp_1653_;
}
}
v___jp_1674_:
{
uint32_t v___x_1676_; uint32_t v_xFraction_1677_; uint32_t v_yFraction_1678_; uint32_t v___x_1679_; uint8_t v___x_1680_; 
v___x_1676_ = 8388607;
v_xFraction_1677_ = lean_uint32_land(v___y_1194_, v___x_1676_);
v_yFraction_1678_ = lean_uint32_land(v___y_1195_, v___x_1676_);
v___x_1679_ = 0;
v___x_1680_ = lean_uint32_dec_eq(v_ex_1639_, v___x_1679_);
if (v___x_1680_ == 0)
{
uint64_t v___x_1681_; uint64_t v___x_1682_; uint64_t v___x_1683_; 
v___x_1681_ = lean_uint32_to_uint64(v_xFraction_1677_);
v___x_1682_ = 8388608ULL;
v___x_1683_ = lean_uint64_lor(v___x_1681_, v___x_1682_);
v___y_1664_ = v___x_1676_;
v___y_1665_ = v_yFraction_1678_;
v___y_1666_ = v___y_1675_;
v___y_1667_ = v___x_1683_;
goto v___jp_1663_;
}
else
{
uint64_t v___x_1684_; 
v___x_1684_ = lean_uint32_to_uint64(v_xFraction_1677_);
v___y_1664_ = v___x_1676_;
v___y_1665_ = v_yFraction_1678_;
v___y_1666_ = v___y_1675_;
v___y_1667_ = v___x_1684_;
goto v___jp_1663_;
}
}
v___jp_1685_:
{
if (v___y_1687_ == 0)
{
v___y_1675_ = v___x_1193_;
goto v___jp_1674_;
}
else
{
v___y_1675_ = v___y_1686_;
goto v___jp_1674_;
}
}
v___jp_1691_:
{
if (v___y_1692_ == 0)
{
if (v___y_1694_ == 0)
{
v___y_1686_ = v___y_1693_;
v___y_1687_ = v___x_1690_;
goto v___jp_1685_;
}
else
{
v___y_1675_ = v___x_1193_;
goto v___jp_1674_;
}
}
else
{
v___y_1686_ = v___y_1693_;
v___y_1687_ = v___y_1694_;
goto v___jp_1685_;
}
}
v___jp_1695_:
{
uint32_t v___x_1698_; uint32_t v___x_1699_; uint32_t v___x_1700_; uint8_t v___x_1701_; 
v___x_1698_ = 2147483648;
v___x_1699_ = lean_uint32_land(v___y_1195_, v___x_1698_);
v___x_1700_ = 0;
v___x_1701_ = lean_uint32_dec_eq(v___x_1699_, v___x_1700_);
if (v___x_1701_ == 0)
{
v___y_1692_ = v___y_1697_;
v___y_1693_ = v___y_1696_;
v___y_1694_ = v___x_1193_;
goto v___jp_1691_;
}
else
{
v___y_1692_ = v___y_1697_;
v___y_1693_ = v___y_1696_;
v___y_1694_ = v___y_1696_;
goto v___jp_1691_;
}
}
v___jp_1702_:
{
if (v___y_1703_ == 0)
{
uint32_t v___x_1704_; uint32_t v___x_1705_; uint32_t v___x_1706_; uint8_t v___x_1707_; 
v___x_1704_ = 2147483648;
v___x_1705_ = lean_uint32_land(v___y_1194_, v___x_1704_);
v___x_1706_ = 0;
v___x_1707_ = lean_uint32_dec_eq(v___x_1705_, v___x_1706_);
if (v___x_1707_ == 0)
{
v___y_1696_ = v___y_1703_;
v___y_1697_ = v___x_1193_;
goto v___jp_1695_;
}
else
{
v___y_1696_ = v___y_1703_;
v___y_1697_ = v___y_1703_;
goto v___jp_1695_;
}
}
else
{
lean_object* v___x_1708_; lean_object* v___x_1709_; lean_object* v___x_1710_; uint32_t v___x_1711_; 
v___x_1708_ = lean_uint32_to_nat(v___y_1194_);
v___x_1709_ = lean_uint32_to_nat(v___y_1195_);
v___x_1710_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1708_, v___x_1709_);
v___x_1711_ = lean_uint32_of_nat(v___x_1710_);
lean_dec(v___x_1710_);
return v___x_1711_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object* v___x_1726_, lean_object* v___y_1727_, lean_object* v___y_1728_){
_start:
{
uint8_t v___x_6820__boxed_1729_; uint32_t v___y_6821__boxed_1730_; uint32_t v___y_6822__boxed_1731_; uint32_t v_res_1732_; lean_object* v_r_1733_; 
v___x_6820__boxed_1729_ = lean_unbox(v___x_1726_);
v___y_6821__boxed_1730_ = lean_unbox_uint32(v___y_1727_);
lean_dec(v___y_1727_);
v___y_6822__boxed_1731_ = lean_unbox_uint32(v___y_1728_);
lean_dec(v___y_1728_);
v_res_1732_ = lp_competition_main___lam__3(v___x_6820__boxed_1729_, v___y_6821__boxed_1730_, v___y_6822__boxed_1731_);
v_r_1733_ = lean_box_uint32(v_res_1732_);
return v_r_1733_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_1749_; lean_object* v___x_1750_; lean_object* v___x_1751_; uint8_t v___x_1752_; 
v___x_1749_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_1750_ = lean_io_getenv(v___x_1749_);
v___x_1751_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_1752_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_1750_, v___x_1751_);
if (v___x_1752_ == 0)
{
lean_object* v___x_1753_; uint8_t v___x_1754_; 
v___x_1753_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_1754_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_1750_, v___x_1753_);
lean_dec(v___x_1750_);
if (v___x_1754_ == 0)
{
lean_object* v___x_1755_; lean_object* v___x_1756_; 
v___x_1755_ = ((lean_object*)(lp_competition_main___closed__6));
v___x_1756_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_1756_, 0, v___x_1755_);
return v___x_1756_;
}
else
{
lean_object* v___f_1757_; lean_object* v___x_1758_; lean_object* v___f_1759_; lean_object* v___x_1760_; lean_object* v___x_1761_; lean_object* v___x_1762_; 
v___f_1757_ = ((lean_object*)(lp_competition_main___closed__7));
v___x_1758_ = lean_box(v___x_1754_);
v___f_1759_ = lean_alloc_closure((void*)(lp_competition_main___lam__1___boxed), 3, 1);
lean_closure_set(v___f_1759_, 0, v___x_1758_);
v___x_1760_ = ((lean_object*)(lp_competition_main___closed__8));
v___x_1761_ = ((lean_object*)(lp_competition_main___closed__9));
v___x_1762_ = lp_competition_Bench_Suite_run(v___f_1757_, v___f_1759_, v___x_1760_, v___x_1761_);
return v___x_1762_;
}
}
else
{
lean_object* v___f_1763_; lean_object* v___x_1764_; lean_object* v___f_1765_; lean_object* v___x_1766_; lean_object* v___x_1767_; lean_object* v___x_1768_; 
lean_dec(v___x_1750_);
v___f_1763_ = ((lean_object*)(lp_competition_main___closed__10));
v___x_1764_ = lean_box(v___x_1752_);
v___f_1765_ = lean_alloc_closure((void*)(lp_competition_main___lam__3___boxed), 3, 1);
lean_closure_set(v___f_1765_, 0, v___x_1764_);
v___x_1766_ = ((lean_object*)(lp_competition_main___closed__8));
v___x_1767_ = ((lean_object*)(lp_competition_main___closed__9));
v___x_1768_ = lp_competition_Bench_Suite_run(v___f_1763_, v___f_1765_, v___x_1766_, v___x_1767_);
return v___x_1768_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_1769_){
_start:
{
lean_object* v_res_1770_; 
v_res_1770_ = _lean_main();
return v_res_1770_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_competition_BenchFull(uint8_t builtin);
lean_object* initialize_competition_BenchSuite(uint8_t builtin);
lean_object* initialize_competition_Submission(uint8_t builtin);
void lean_initialize();
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_competition_R22BroadWordCostMain(uint8_t builtin) {
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
  res = initialize_competition_R22BroadWordCostMain(1 /* builtin */);
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
