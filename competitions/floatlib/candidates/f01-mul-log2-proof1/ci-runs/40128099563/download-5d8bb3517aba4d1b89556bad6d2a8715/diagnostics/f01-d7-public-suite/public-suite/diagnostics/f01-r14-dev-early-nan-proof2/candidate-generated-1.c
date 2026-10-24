// Lean compiler output
// Module: MainFull
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
lean_object* lean_io_getenv(lean_object*);
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
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(lean_object*, lean_object*);
lean_object* lp_competition_Submission_sum___boxed(lean_object*, lean_object*);
lean_object* lp_competition_Submission_bmm(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lp_competition_Bench_runFull(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lp_competition_Bench_Suite_run(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object*, lean_object*);
static const lean_string_object lp_competition_main___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 11, .m_capacity = 11, .m_length = 10, .m_data = "BENCH_PLAN"};
static const lean_object* lp_competition_main___closed__0 = (const lean_object*)&lp_competition_main___closed__0_value;
static const lean_closure_object lp_competition_main___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_main___lam__0___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__1 = (const lean_object*)&lp_competition_main___closed__1_value;
static const lean_closure_object lp_competition_main___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_main___lam__1___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__2 = (const lean_object*)&lp_competition_main___closed__2_value;
static const lean_closure_object lp_competition_main___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_sum___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__3 = (const lean_object*)&lp_competition_main___closed__3_value;
static const lean_closure_object lp_competition_main___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_bmm, .m_arity = 6, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__4 = (const lean_object*)&lp_competition_main___closed__4_value;
static const lean_closure_object lp_competition_main___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_main___lam__3___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__5 = (const lean_object*)&lp_competition_main___closed__5_value;
LEAN_EXPORT lean_object* _lean_main();
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t v___y_1_, uint32_t v___y_2_){
_start:
{
uint8_t v___y_9_; uint8_t v___y_23_; uint8_t v___y_37_; uint8_t v___y_54_; float v___y_61_; float v___y_62_; float v___y_76_; uint8_t v___y_77_; float v___y_92_; uint8_t v___y_102_; uint8_t v___y_126_; uint8_t v___y_140_; uint8_t v___y_154_; uint8_t v___y_171_; uint32_t v___x_177_; uint32_t v___x_178_; uint32_t v___x_179_; uint32_t v___x_180_; uint8_t v___x_181_; 
v___x_177_ = 23;
v___x_178_ = lean_uint32_shift_right(v___y_1_, v___x_177_);
v___x_179_ = 255;
v___x_180_ = lean_uint32_land(v___x_178_, v___x_179_);
v___x_181_ = lean_uint32_dec_eq(v___x_180_, v___x_179_);
if (v___x_181_ == 0)
{
v___y_171_ = v___x_181_;
goto v___jp_170_;
}
else
{
uint32_t v___x_182_; uint32_t v___x_183_; uint32_t v___x_184_; uint8_t v___x_185_; 
v___x_182_ = 8388607;
v___x_183_ = lean_uint32_land(v___y_1_, v___x_182_);
v___x_184_ = 0;
v___x_185_ = lean_uint32_dec_eq(v___x_183_, v___x_184_);
if (v___x_185_ == 0)
{
v___y_171_ = v___x_181_;
goto v___jp_170_;
}
else
{
goto v___jp_160_;
}
}
v___jp_3_:
{
lean_object* v___x_4_; lean_object* v___x_5_; lean_object* v___x_6_; uint32_t v___x_7_; 
v___x_4_ = lean_uint32_to_nat(v___y_1_);
v___x_5_ = lean_uint32_to_nat(v___y_2_);
v___x_6_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_4_, v___x_5_);
v___x_7_ = lean_uint32_of_nat(v___x_6_);
lean_dec(v___x_6_);
return v___x_7_;
}
v___jp_8_:
{
if (v___y_9_ == 0)
{
goto v___jp_3_;
}
else
{
uint32_t v___x_10_; uint32_t v___x_11_; 
v___x_10_ = 4194304;
v___x_11_ = lean_uint32_lor(v___y_2_, v___x_10_);
return v___x_11_;
}
}
v___jp_12_:
{
uint32_t v___x_13_; uint32_t v___x_14_; uint32_t v___x_15_; uint32_t v___x_16_; uint8_t v___x_17_; 
v___x_13_ = 23;
v___x_14_ = lean_uint32_shift_right(v___y_2_, v___x_13_);
v___x_15_ = 255;
v___x_16_ = lean_uint32_land(v___x_14_, v___x_15_);
v___x_17_ = lean_uint32_dec_eq(v___x_16_, v___x_15_);
if (v___x_17_ == 0)
{
v___y_9_ = v___x_17_;
goto v___jp_8_;
}
else
{
uint32_t v___x_18_; uint32_t v___x_19_; uint32_t v___x_20_; uint8_t v___x_21_; 
v___x_18_ = 8388607;
v___x_19_ = lean_uint32_land(v___y_2_, v___x_18_);
v___x_20_ = 0;
v___x_21_ = lean_uint32_dec_eq(v___x_19_, v___x_20_);
if (v___x_21_ == 0)
{
v___y_9_ = v___x_17_;
goto v___jp_8_;
}
else
{
goto v___jp_3_;
}
}
}
v___jp_22_:
{
if (v___y_23_ == 0)
{
goto v___jp_12_;
}
else
{
uint32_t v___x_24_; uint32_t v___x_25_; 
v___x_24_ = 4194304;
v___x_25_ = lean_uint32_lor(v___y_1_, v___x_24_);
return v___x_25_;
}
}
v___jp_26_:
{
uint32_t v___x_27_; uint32_t v___x_28_; uint32_t v___x_29_; uint32_t v___x_30_; uint8_t v___x_31_; 
v___x_27_ = 23;
v___x_28_ = lean_uint32_shift_right(v___y_1_, v___x_27_);
v___x_29_ = 255;
v___x_30_ = lean_uint32_land(v___x_28_, v___x_29_);
v___x_31_ = lean_uint32_dec_eq(v___x_30_, v___x_29_);
if (v___x_31_ == 0)
{
v___y_23_ = v___x_31_;
goto v___jp_22_;
}
else
{
uint32_t v___x_32_; uint32_t v___x_33_; uint32_t v___x_34_; uint8_t v___x_35_; 
v___x_32_ = 8388607;
v___x_33_ = lean_uint32_land(v___y_1_, v___x_32_);
v___x_34_ = 0;
v___x_35_ = lean_uint32_dec_eq(v___x_33_, v___x_34_);
if (v___x_35_ == 0)
{
v___y_23_ = v___x_31_;
goto v___jp_22_;
}
else
{
goto v___jp_12_;
}
}
}
v___jp_36_:
{
if (v___y_37_ == 0)
{
goto v___jp_26_;
}
else
{
uint32_t v___x_38_; uint32_t v___x_39_; uint32_t v___x_40_; uint8_t v___x_41_; 
v___x_38_ = 4194304;
v___x_39_ = lean_uint32_land(v___y_2_, v___x_38_);
v___x_40_ = 0;
v___x_41_ = lean_uint32_dec_eq(v___x_39_, v___x_40_);
if (v___x_41_ == 0)
{
goto v___jp_26_;
}
else
{
uint32_t v___x_42_; 
v___x_42_ = lean_uint32_lor(v___y_2_, v___x_38_);
return v___x_42_;
}
}
}
v___jp_43_:
{
uint32_t v___x_44_; uint32_t v___x_45_; uint32_t v___x_46_; uint32_t v___x_47_; uint8_t v___x_48_; 
v___x_44_ = 23;
v___x_45_ = lean_uint32_shift_right(v___y_2_, v___x_44_);
v___x_46_ = 255;
v___x_47_ = lean_uint32_land(v___x_45_, v___x_46_);
v___x_48_ = lean_uint32_dec_eq(v___x_47_, v___x_46_);
if (v___x_48_ == 0)
{
v___y_37_ = v___x_48_;
goto v___jp_36_;
}
else
{
uint32_t v___x_49_; uint32_t v___x_50_; uint32_t v___x_51_; uint8_t v___x_52_; 
v___x_49_ = 8388607;
v___x_50_ = lean_uint32_land(v___y_2_, v___x_49_);
v___x_51_ = 0;
v___x_52_ = lean_uint32_dec_eq(v___x_50_, v___x_51_);
if (v___x_52_ == 0)
{
v___y_37_ = v___x_48_;
goto v___jp_36_;
}
else
{
goto v___jp_26_;
}
}
}
v___jp_53_:
{
if (v___y_54_ == 0)
{
goto v___jp_43_;
}
else
{
uint32_t v___x_55_; uint32_t v___x_56_; uint32_t v___x_57_; uint8_t v___x_58_; 
v___x_55_ = 4194304;
v___x_56_ = lean_uint32_land(v___y_1_, v___x_55_);
v___x_57_ = 0;
v___x_58_ = lean_uint32_dec_eq(v___x_56_, v___x_57_);
if (v___x_58_ == 0)
{
goto v___jp_43_;
}
else
{
uint32_t v___x_59_; 
v___x_59_ = lean_uint32_lor(v___y_1_, v___x_55_);
return v___x_59_;
}
}
}
v___jp_60_:
{
float v_result_63_; uint8_t v___x_64_; 
v_result_63_ = lean_float32_add(v___y_61_, v___y_62_);
v___x_64_ = lean_float32_beq(v_result_63_, v_result_63_);
if (v___x_64_ == 0)
{
uint32_t v___x_65_; uint32_t v___x_66_; uint32_t v___x_67_; uint32_t v___x_68_; uint8_t v___x_69_; 
v___x_65_ = 23;
v___x_66_ = lean_uint32_shift_right(v___y_1_, v___x_65_);
v___x_67_ = 255;
v___x_68_ = lean_uint32_land(v___x_66_, v___x_67_);
v___x_69_ = lean_uint32_dec_eq(v___x_68_, v___x_67_);
if (v___x_69_ == 0)
{
v___y_54_ = v___x_69_;
goto v___jp_53_;
}
else
{
uint32_t v___x_70_; uint32_t v___x_71_; uint32_t v___x_72_; uint8_t v___x_73_; 
v___x_70_ = 8388607;
v___x_71_ = lean_uint32_land(v___y_1_, v___x_70_);
v___x_72_ = 0;
v___x_73_ = lean_uint32_dec_eq(v___x_71_, v___x_72_);
if (v___x_73_ == 0)
{
v___y_54_ = v___x_69_;
goto v___jp_53_;
}
else
{
goto v___jp_43_;
}
}
}
else
{
uint32_t v___x_74_; 
v___x_74_ = lean_float32_to_bits(v_result_63_);
return v___x_74_;
}
}
v___jp_75_:
{
if (v___y_77_ == 0)
{
float v___x_78_; 
v___x_78_ = lean_float32_of_bits(v___y_2_);
v___y_61_ = v___y_76_;
v___y_62_ = v___x_78_;
goto v___jp_60_;
}
else
{
uint32_t v___x_79_; uint32_t v___x_80_; uint32_t v___x_81_; uint32_t v___x_82_; float v___x_83_; lean_object* v___x_84_; uint32_t v___x_85_; uint32_t v___x_86_; lean_object* v___x_87_; lean_object* v___x_88_; float v___x_89_; float v___x_90_; 
v___x_79_ = 8388607;
v___x_80_ = lean_uint32_land(v___y_2_, v___x_79_);
v___x_81_ = 8388608;
v___x_82_ = lean_uint32_lor(v___x_80_, v___x_81_);
v___x_83_ = lean_uint32_to_float32(v___x_82_);
v___x_84_ = lp_competition_R2W01b_scaleTable;
v___x_85_ = 23;
v___x_86_ = lean_uint32_shift_right(v___y_2_, v___x_85_);
v___x_87_ = lean_uint32_to_nat(v___x_86_);
v___x_88_ = lean_array_fget_borrowed(v___x_84_, v___x_87_);
lean_dec(v___x_87_);
v___x_89_ = lean_unbox_float32(v___x_88_);
v___x_90_ = lean_float32_mul(v___x_83_, v___x_89_);
v___y_61_ = v___y_76_;
v___y_62_ = v___x_90_;
goto v___jp_60_;
}
}
v___jp_91_:
{
uint32_t v___x_93_; uint32_t v_a_94_; uint32_t v___x_95_; uint32_t v___x_96_; uint32_t v___x_97_; uint8_t v___x_98_; 
v___x_93_ = 2147483647;
v_a_94_ = lean_uint32_land(v___y_2_, v___x_93_);
v___x_95_ = 201326591;
v___x_96_ = 1;
v___x_97_ = lean_uint32_sub(v_a_94_, v___x_96_);
v___x_98_ = lean_uint32_dec_le(v___x_95_, v___x_97_);
if (v___x_98_ == 0)
{
v___y_76_ = v___y_92_;
v___y_77_ = v___x_98_;
goto v___jp_75_;
}
else
{
uint32_t v___x_99_; uint8_t v___x_100_; 
v___x_99_ = 2139095040;
v___x_100_ = lean_uint32_dec_lt(v_a_94_, v___x_99_);
v___y_76_ = v___y_92_;
v___y_77_ = v___x_100_;
goto v___jp_75_;
}
}
v___jp_101_:
{
if (v___y_102_ == 0)
{
float v___x_103_; 
v___x_103_ = lean_float32_of_bits(v___y_1_);
v___y_92_ = v___x_103_;
goto v___jp_91_;
}
else
{
uint32_t v___x_104_; uint32_t v___x_105_; uint32_t v___x_106_; uint32_t v___x_107_; float v___x_108_; lean_object* v___x_109_; uint32_t v___x_110_; uint32_t v___x_111_; lean_object* v___x_112_; lean_object* v___x_113_; float v___x_114_; float v___x_115_; 
v___x_104_ = 8388607;
v___x_105_ = lean_uint32_land(v___y_1_, v___x_104_);
v___x_106_ = 8388608;
v___x_107_ = lean_uint32_lor(v___x_105_, v___x_106_);
v___x_108_ = lean_uint32_to_float32(v___x_107_);
v___x_109_ = lp_competition_R2W01b_scaleTable;
v___x_110_ = 23;
v___x_111_ = lean_uint32_shift_right(v___y_1_, v___x_110_);
v___x_112_ = lean_uint32_to_nat(v___x_111_);
v___x_113_ = lean_array_fget_borrowed(v___x_109_, v___x_112_);
lean_dec(v___x_112_);
v___x_114_ = lean_unbox_float32(v___x_113_);
v___x_115_ = lean_float32_mul(v___x_108_, v___x_114_);
v___y_92_ = v___x_115_;
goto v___jp_91_;
}
}
v___jp_116_:
{
uint32_t v___x_117_; uint32_t v_a_118_; uint32_t v___x_119_; uint32_t v___x_120_; uint32_t v___x_121_; uint8_t v___x_122_; 
v___x_117_ = 2147483647;
v_a_118_ = lean_uint32_land(v___y_1_, v___x_117_);
v___x_119_ = 201326591;
v___x_120_ = 1;
v___x_121_ = lean_uint32_sub(v_a_118_, v___x_120_);
v___x_122_ = lean_uint32_dec_le(v___x_119_, v___x_121_);
if (v___x_122_ == 0)
{
v___y_102_ = v___x_122_;
goto v___jp_101_;
}
else
{
uint32_t v___x_123_; uint8_t v___x_124_; 
v___x_123_ = 2139095040;
v___x_124_ = lean_uint32_dec_lt(v_a_118_, v___x_123_);
v___y_102_ = v___x_124_;
goto v___jp_101_;
}
}
v___jp_125_:
{
if (v___y_126_ == 0)
{
goto v___jp_116_;
}
else
{
uint32_t v___x_127_; uint32_t v___x_128_; 
v___x_127_ = 4194304;
v___x_128_ = lean_uint32_lor(v___y_2_, v___x_127_);
return v___x_128_;
}
}
v___jp_129_:
{
uint32_t v___x_130_; uint32_t v___x_131_; uint32_t v___x_132_; uint32_t v___x_133_; uint8_t v___x_134_; 
v___x_130_ = 23;
v___x_131_ = lean_uint32_shift_right(v___y_2_, v___x_130_);
v___x_132_ = 255;
v___x_133_ = lean_uint32_land(v___x_131_, v___x_132_);
v___x_134_ = lean_uint32_dec_eq(v___x_133_, v___x_132_);
if (v___x_134_ == 0)
{
v___y_126_ = v___x_134_;
goto v___jp_125_;
}
else
{
uint32_t v___x_135_; uint32_t v___x_136_; uint32_t v___x_137_; uint8_t v___x_138_; 
v___x_135_ = 8388607;
v___x_136_ = lean_uint32_land(v___y_2_, v___x_135_);
v___x_137_ = 0;
v___x_138_ = lean_uint32_dec_eq(v___x_136_, v___x_137_);
if (v___x_138_ == 0)
{
v___y_126_ = v___x_134_;
goto v___jp_125_;
}
else
{
goto v___jp_116_;
}
}
}
v___jp_139_:
{
if (v___y_140_ == 0)
{
goto v___jp_129_;
}
else
{
uint32_t v___x_141_; uint32_t v___x_142_; 
v___x_141_ = 4194304;
v___x_142_ = lean_uint32_lor(v___y_1_, v___x_141_);
return v___x_142_;
}
}
v___jp_143_:
{
uint32_t v___x_144_; uint32_t v___x_145_; uint32_t v___x_146_; uint32_t v___x_147_; uint8_t v___x_148_; 
v___x_144_ = 23;
v___x_145_ = lean_uint32_shift_right(v___y_1_, v___x_144_);
v___x_146_ = 255;
v___x_147_ = lean_uint32_land(v___x_145_, v___x_146_);
v___x_148_ = lean_uint32_dec_eq(v___x_147_, v___x_146_);
if (v___x_148_ == 0)
{
v___y_140_ = v___x_148_;
goto v___jp_139_;
}
else
{
uint32_t v___x_149_; uint32_t v___x_150_; uint32_t v___x_151_; uint8_t v___x_152_; 
v___x_149_ = 8388607;
v___x_150_ = lean_uint32_land(v___y_1_, v___x_149_);
v___x_151_ = 0;
v___x_152_ = lean_uint32_dec_eq(v___x_150_, v___x_151_);
if (v___x_152_ == 0)
{
v___y_140_ = v___x_148_;
goto v___jp_139_;
}
else
{
goto v___jp_129_;
}
}
}
v___jp_153_:
{
if (v___y_154_ == 0)
{
goto v___jp_143_;
}
else
{
uint32_t v___x_155_; uint32_t v___x_156_; uint32_t v___x_157_; uint8_t v___x_158_; 
v___x_155_ = 4194304;
v___x_156_ = lean_uint32_land(v___y_2_, v___x_155_);
v___x_157_ = 0;
v___x_158_ = lean_uint32_dec_eq(v___x_156_, v___x_157_);
if (v___x_158_ == 0)
{
goto v___jp_143_;
}
else
{
uint32_t v___x_159_; 
v___x_159_ = lean_uint32_lor(v___y_2_, v___x_155_);
return v___x_159_;
}
}
}
v___jp_160_:
{
uint32_t v___x_161_; uint32_t v___x_162_; uint32_t v___x_163_; uint32_t v___x_164_; uint8_t v___x_165_; 
v___x_161_ = 23;
v___x_162_ = lean_uint32_shift_right(v___y_2_, v___x_161_);
v___x_163_ = 255;
v___x_164_ = lean_uint32_land(v___x_162_, v___x_163_);
v___x_165_ = lean_uint32_dec_eq(v___x_164_, v___x_163_);
if (v___x_165_ == 0)
{
v___y_154_ = v___x_165_;
goto v___jp_153_;
}
else
{
uint32_t v___x_166_; uint32_t v___x_167_; uint32_t v___x_168_; uint8_t v___x_169_; 
v___x_166_ = 8388607;
v___x_167_ = lean_uint32_land(v___y_2_, v___x_166_);
v___x_168_ = 0;
v___x_169_ = lean_uint32_dec_eq(v___x_167_, v___x_168_);
if (v___x_169_ == 0)
{
v___y_154_ = v___x_165_;
goto v___jp_153_;
}
else
{
goto v___jp_143_;
}
}
}
v___jp_170_:
{
if (v___y_171_ == 0)
{
goto v___jp_160_;
}
else
{
uint32_t v___x_172_; uint32_t v___x_173_; uint32_t v___x_174_; uint8_t v___x_175_; 
v___x_172_ = 4194304;
v___x_173_ = lean_uint32_land(v___y_1_, v___x_172_);
v___x_174_ = 0;
v___x_175_ = lean_uint32_dec_eq(v___x_173_, v___x_174_);
if (v___x_175_ == 0)
{
goto v___jp_160_;
}
else
{
uint32_t v___x_176_; 
v___x_176_ = lean_uint32_lor(v___y_1_, v___x_172_);
return v___x_176_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object* v___y_186_, lean_object* v___y_187_){
_start:
{
uint32_t v___y_5081__boxed_188_; uint32_t v___y_5082__boxed_189_; uint32_t v_res_190_; lean_object* v_r_191_; 
v___y_5081__boxed_188_ = lean_unbox_uint32(v___y_186_);
lean_dec(v___y_186_);
v___y_5082__boxed_189_ = lean_unbox_uint32(v___y_187_);
lean_dec(v___y_187_);
v_res_190_ = lp_competition_main___lam__0(v___y_5081__boxed_188_, v___y_5082__boxed_189_);
v_r_191_ = lean_box_uint32(v_res_190_);
return v_r_191_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t v___y_192_, uint32_t v___y_193_){
_start:
{
uint32_t v___y_195_; uint32_t v___y_196_; uint32_t v___y_197_; uint32_t v___y_201_; uint32_t v___y_202_; uint32_t v___y_203_; uint32_t v___y_207_; uint8_t v___y_211_; uint32_t v___y_212_; uint64_t v___y_213_; uint64_t v___y_214_; uint32_t v___y_226_; uint8_t v___y_230_; uint32_t v___y_231_; uint64_t v___y_232_; uint64_t v___y_233_; uint8_t v___y_245_; uint8_t v___y_261_; uint8_t v___y_275_; uint8_t v___y_292_; float v___y_299_; float v___y_300_; float v___y_314_; uint8_t v___y_315_; float v___y_330_; uint8_t v___y_340_; uint8_t v___y_364_; uint32_t v___x_367_; uint32_t v___x_368_; uint32_t v___x_369_; uint32_t v___y_371_; uint32_t v___y_372_; uint32_t v___y_373_; uint32_t v___y_374_; uint8_t v___y_381_; uint32_t v___y_382_; uint32_t v___y_383_; uint32_t v___y_384_; uint8_t v___y_388_; uint64_t v___y_389_; uint32_t v___y_390_; uint64_t v___y_391_; uint64_t v___y_392_; uint8_t v___y_402_; uint8_t v___y_403_; uint32_t v___y_404_; uint64_t v___y_405_; uint64_t v___y_406_; uint64_t v___y_407_; uint8_t v___y_414_; uint32_t v___y_415_; uint64_t v___y_416_; uint64_t v___y_417_; uint64_t v___y_418_; uint8_t v___y_424_; uint64_t v___y_425_; uint32_t v___y_426_; uint64_t v___y_427_; uint64_t v___y_428_; uint64_t v___y_429_; uint8_t v___y_484_; uint64_t v___y_485_; uint64_t v___y_486_; uint32_t v___y_487_; uint64_t v___y_488_; uint64_t v___y_489_; uint64_t v___y_490_; uint64_t v___y_496_; uint8_t v___y_497_; uint64_t v___y_498_; uint64_t v___y_499_; uint64_t v___y_500_; uint32_t v___y_501_; uint64_t v___y_502_; uint64_t v___y_503_; uint64_t v___y_504_; uint8_t v___y_509_; uint64_t v___y_510_; uint64_t v___y_511_; uint32_t v___y_512_; uint64_t v___y_513_; uint64_t v___y_514_; uint64_t v___y_515_; uint8_t v___y_520_; uint64_t v___y_521_; uint64_t v___y_522_; uint64_t v___y_523_; uint64_t v___y_524_; uint32_t v___y_525_; uint64_t v___y_526_; uint64_t v___y_527_; uint64_t v___y_528_; uint8_t v___y_533_; uint64_t v___y_534_; uint64_t v___y_535_; uint32_t v___y_536_; uint64_t v___y_537_; uint64_t v___y_538_; uint64_t v___y_539_; uint64_t v___y_544_; uint8_t v___y_545_; uint64_t v___y_546_; uint32_t v___y_547_; uint64_t v___y_548_; uint64_t v___y_549_; uint64_t v___y_550_; uint64_t v___y_551_; uint64_t v___y_552_; uint8_t v___y_557_; uint64_t v___y_558_; uint32_t v___y_559_; uint64_t v___y_560_; uint64_t v___y_561_; uint64_t v___y_562_; uint64_t v___y_563_; uint8_t v___y_568_; uint64_t v___y_569_; uint64_t v___y_570_; uint64_t v___y_571_; uint32_t v___y_572_; uint64_t v___y_573_; uint64_t v___y_574_; uint64_t v___y_575_; uint64_t v___y_576_; uint8_t v___y_581_; uint64_t v___y_582_; uint64_t v___y_583_; uint32_t v___y_584_; uint64_t v___y_585_; uint64_t v___y_586_; uint64_t v___y_587_; uint8_t v___y_592_; uint64_t v___y_593_; uint32_t v___y_594_; uint64_t v___y_595_; uint64_t v___y_596_; uint64_t v___y_597_; uint64_t v___y_598_; uint8_t v___y_602_; uint64_t v___y_603_; uint32_t v___y_604_; uint64_t v___y_605_; uint8_t v___y_614_; uint64_t v___y_615_; uint64_t v___y_616_; uint32_t v___y_617_; uint64_t v___y_618_; uint64_t v___y_619_; uint32_t v_ex_652_; uint32_t v___x_653_; uint32_t v_ey_654_; uint8_t v___y_662_; uint8_t v___y_672_; uint8_t v___y_685_; uint8_t v___y_692_; uint64_t v___y_693_; uint32_t v___y_694_; uint64_t v___y_695_; uint64_t v___y_696_; uint8_t v___y_703_; uint32_t v___y_704_; uint64_t v___y_705_; uint64_t v___y_706_; uint8_t v___y_713_; uint32_t v___y_714_; uint32_t v___y_715_; uint64_t v___y_716_; uint8_t v___y_724_; uint32_t v___x_734_; uint32_t v___x_735_; uint8_t v___x_736_; uint8_t v___y_738_; uint8_t v___y_739_; uint8_t v___y_741_; uint8_t v___y_742_; uint8_t v___y_743_; uint8_t v___y_745_; uint8_t v___y_746_; uint8_t v___y_752_; 
v___x_367_ = 23;
v___x_368_ = lean_uint32_shift_right(v___y_192_, v___x_367_);
v___x_369_ = 255;
v_ex_652_ = lean_uint32_land(v___x_368_, v___x_369_);
v___x_653_ = lean_uint32_shift_right(v___y_193_, v___x_367_);
v_ey_654_ = lean_uint32_land(v___x_653_, v___x_369_);
v___x_734_ = lean_uint32_add(v_ex_652_, v_ey_654_);
v___x_735_ = 128;
v___x_736_ = lean_uint32_dec_lt(v___x_734_, v___x_735_);
if (v___x_736_ == 0)
{
uint8_t v___x_761_; 
v___x_761_ = lean_uint32_dec_eq(v_ex_652_, v___x_369_);
if (v___x_761_ == 0)
{
v___y_685_ = v___x_761_;
goto v___jp_684_;
}
else
{
uint32_t v___x_762_; uint32_t v___x_763_; uint32_t v___x_764_; uint8_t v___x_765_; 
v___x_762_ = 8388607;
v___x_763_ = lean_uint32_land(v___y_192_, v___x_762_);
v___x_764_ = 0;
v___x_765_ = lean_uint32_dec_eq(v___x_763_, v___x_764_);
if (v___x_765_ == 0)
{
v___y_685_ = v___x_761_;
goto v___jp_684_;
}
else
{
goto v___jp_678_;
}
}
}
else
{
uint32_t v___x_766_; uint32_t v___x_767_; uint32_t v___x_768_; uint8_t v___x_769_; 
v___x_766_ = 4278190080;
v___x_767_ = 1;
v___x_768_ = lean_uint32_shift_left(v___y_192_, v___x_767_);
v___x_769_ = lean_uint32_dec_le(v___x_766_, v___x_768_);
if (v___x_769_ == 0)
{
uint32_t v___x_770_; uint8_t v___x_771_; 
v___x_770_ = lean_uint32_shift_left(v___y_193_, v___x_767_);
v___x_771_ = lean_uint32_dec_le(v___x_766_, v___x_770_);
v___y_752_ = v___x_771_;
goto v___jp_751_;
}
else
{
v___y_752_ = v___x_769_;
goto v___jp_751_;
}
}
v___jp_194_:
{
uint32_t v___x_198_; uint32_t v___x_199_; 
v___x_198_ = lean_uint32_land(v___y_196_, v___y_195_);
v___x_199_ = lean_uint32_lor(v___y_197_, v___x_198_);
return v___x_199_;
}
v___jp_200_:
{
uint32_t v___x_204_; uint32_t v___x_205_; 
v___x_204_ = lean_uint32_land(v___y_201_, v___y_202_);
v___x_205_ = lean_uint32_lor(v___y_203_, v___x_204_);
return v___x_205_;
}
v___jp_206_:
{
uint32_t v___x_208_; uint32_t v___x_209_; 
v___x_208_ = 8388608;
v___x_209_ = lean_uint32_lor(v___y_207_, v___x_208_);
return v___x_209_;
}
v___jp_210_:
{
uint8_t v___x_215_; 
v___x_215_ = lean_uint64_dec_eq(v___y_214_, v___y_213_);
if (v___x_215_ == 0)
{
uint64_t v___x_216_; uint8_t v___x_217_; 
v___x_216_ = 8388608ULL;
v___x_217_ = lean_uint64_dec_eq(v___y_214_, v___x_216_);
if (v___x_217_ == 0)
{
uint32_t v___x_218_; 
v___x_218_ = lean_uint64_to_uint32(v___y_214_);
if (v___y_211_ == 0)
{
uint32_t v___x_219_; 
v___x_219_ = 0;
v___y_201_ = v___x_218_;
v___y_202_ = v___y_212_;
v___y_203_ = v___x_219_;
goto v___jp_200_;
}
else
{
uint32_t v___x_220_; 
v___x_220_ = 2147483648;
v___y_201_ = v___x_218_;
v___y_202_ = v___y_212_;
v___y_203_ = v___x_220_;
goto v___jp_200_;
}
}
else
{
if (v___y_211_ == 0)
{
uint32_t v___x_221_; 
v___x_221_ = 0;
v___y_207_ = v___x_221_;
goto v___jp_206_;
}
else
{
uint32_t v___x_222_; 
v___x_222_ = 2147483648;
v___y_207_ = v___x_222_;
goto v___jp_206_;
}
}
}
else
{
if (v___y_211_ == 0)
{
uint32_t v___x_223_; 
v___x_223_ = 0;
return v___x_223_;
}
else
{
uint32_t v___x_224_; 
v___x_224_ = 2147483648;
return v___x_224_;
}
}
}
v___jp_225_:
{
uint32_t v___x_227_; uint32_t v___x_228_; 
v___x_227_ = 8388608;
v___x_228_ = lean_uint32_lor(v___y_226_, v___x_227_);
return v___x_228_;
}
v___jp_229_:
{
uint8_t v___x_234_; 
v___x_234_ = lean_uint64_dec_eq(v___y_233_, v___y_232_);
if (v___x_234_ == 0)
{
uint64_t v___x_235_; uint8_t v___x_236_; 
v___x_235_ = 8388608ULL;
v___x_236_ = lean_uint64_dec_eq(v___y_233_, v___x_235_);
if (v___x_236_ == 0)
{
uint32_t v___x_237_; 
v___x_237_ = lean_uint64_to_uint32(v___y_233_);
if (v___y_230_ == 0)
{
uint32_t v___x_238_; 
v___x_238_ = 0;
v___y_195_ = v___y_231_;
v___y_196_ = v___x_237_;
v___y_197_ = v___x_238_;
goto v___jp_194_;
}
else
{
uint32_t v___x_239_; 
v___x_239_ = 2147483648;
v___y_195_ = v___y_231_;
v___y_196_ = v___x_237_;
v___y_197_ = v___x_239_;
goto v___jp_194_;
}
}
else
{
if (v___y_230_ == 0)
{
uint32_t v___x_240_; 
v___x_240_ = 0;
v___y_226_ = v___x_240_;
goto v___jp_225_;
}
else
{
uint32_t v___x_241_; 
v___x_241_ = 2147483648;
v___y_226_ = v___x_241_;
goto v___jp_225_;
}
}
}
else
{
if (v___y_230_ == 0)
{
uint32_t v___x_242_; 
v___x_242_ = 0;
return v___x_242_;
}
else
{
uint32_t v___x_243_; 
v___x_243_ = 2147483648;
return v___x_243_;
}
}
}
v___jp_244_:
{
if (v___y_245_ == 0)
{
uint32_t v___x_246_; 
v___x_246_ = lp_competition_Submission_FastMul_mul(v___y_192_, v___y_193_);
return v___x_246_;
}
else
{
uint32_t v___x_247_; uint32_t v___x_248_; 
v___x_247_ = 4194304;
v___x_248_ = lean_uint32_lor(v___y_193_, v___x_247_);
return v___x_248_;
}
}
v___jp_249_:
{
uint32_t v___x_250_; uint32_t v___x_251_; uint32_t v___x_252_; uint32_t v___x_253_; uint8_t v___x_254_; 
v___x_250_ = 23;
v___x_251_ = lean_uint32_shift_right(v___y_193_, v___x_250_);
v___x_252_ = 255;
v___x_253_ = lean_uint32_land(v___x_251_, v___x_252_);
v___x_254_ = lean_uint32_dec_eq(v___x_253_, v___x_252_);
if (v___x_254_ == 0)
{
v___y_245_ = v___x_254_;
goto v___jp_244_;
}
else
{
uint32_t v___x_255_; uint32_t v___x_256_; uint32_t v___x_257_; uint8_t v___x_258_; 
v___x_255_ = 8388607;
v___x_256_ = lean_uint32_land(v___y_193_, v___x_255_);
v___x_257_ = 0;
v___x_258_ = lean_uint32_dec_eq(v___x_256_, v___x_257_);
if (v___x_258_ == 0)
{
v___y_245_ = v___x_254_;
goto v___jp_244_;
}
else
{
uint32_t v___x_259_; 
v___x_259_ = lp_competition_Submission_FastMul_mul(v___y_192_, v___y_193_);
return v___x_259_;
}
}
}
v___jp_260_:
{
if (v___y_261_ == 0)
{
goto v___jp_249_;
}
else
{
uint32_t v___x_262_; uint32_t v___x_263_; 
v___x_262_ = 4194304;
v___x_263_ = lean_uint32_lor(v___y_192_, v___x_262_);
return v___x_263_;
}
}
v___jp_264_:
{
uint32_t v___x_265_; uint32_t v___x_266_; uint32_t v___x_267_; uint32_t v___x_268_; uint8_t v___x_269_; 
v___x_265_ = 23;
v___x_266_ = lean_uint32_shift_right(v___y_192_, v___x_265_);
v___x_267_ = 255;
v___x_268_ = lean_uint32_land(v___x_266_, v___x_267_);
v___x_269_ = lean_uint32_dec_eq(v___x_268_, v___x_267_);
if (v___x_269_ == 0)
{
v___y_261_ = v___x_269_;
goto v___jp_260_;
}
else
{
uint32_t v___x_270_; uint32_t v___x_271_; uint32_t v___x_272_; uint8_t v___x_273_; 
v___x_270_ = 8388607;
v___x_271_ = lean_uint32_land(v___y_192_, v___x_270_);
v___x_272_ = 0;
v___x_273_ = lean_uint32_dec_eq(v___x_271_, v___x_272_);
if (v___x_273_ == 0)
{
v___y_261_ = v___x_269_;
goto v___jp_260_;
}
else
{
goto v___jp_249_;
}
}
}
v___jp_274_:
{
if (v___y_275_ == 0)
{
goto v___jp_264_;
}
else
{
uint32_t v___x_276_; uint32_t v___x_277_; uint32_t v___x_278_; uint8_t v___x_279_; 
v___x_276_ = 4194304;
v___x_277_ = lean_uint32_land(v___y_193_, v___x_276_);
v___x_278_ = 0;
v___x_279_ = lean_uint32_dec_eq(v___x_277_, v___x_278_);
if (v___x_279_ == 0)
{
goto v___jp_264_;
}
else
{
uint32_t v___x_280_; 
v___x_280_ = lean_uint32_lor(v___y_193_, v___x_276_);
return v___x_280_;
}
}
}
v___jp_281_:
{
uint32_t v___x_282_; uint32_t v___x_283_; uint32_t v___x_284_; uint32_t v___x_285_; uint8_t v___x_286_; 
v___x_282_ = 23;
v___x_283_ = lean_uint32_shift_right(v___y_193_, v___x_282_);
v___x_284_ = 255;
v___x_285_ = lean_uint32_land(v___x_283_, v___x_284_);
v___x_286_ = lean_uint32_dec_eq(v___x_285_, v___x_284_);
if (v___x_286_ == 0)
{
v___y_275_ = v___x_286_;
goto v___jp_274_;
}
else
{
uint32_t v___x_287_; uint32_t v___x_288_; uint32_t v___x_289_; uint8_t v___x_290_; 
v___x_287_ = 8388607;
v___x_288_ = lean_uint32_land(v___y_193_, v___x_287_);
v___x_289_ = 0;
v___x_290_ = lean_uint32_dec_eq(v___x_288_, v___x_289_);
if (v___x_290_ == 0)
{
v___y_275_ = v___x_286_;
goto v___jp_274_;
}
else
{
goto v___jp_264_;
}
}
}
v___jp_291_:
{
if (v___y_292_ == 0)
{
goto v___jp_281_;
}
else
{
uint32_t v___x_293_; uint32_t v___x_294_; uint32_t v___x_295_; uint8_t v___x_296_; 
v___x_293_ = 4194304;
v___x_294_ = lean_uint32_land(v___y_192_, v___x_293_);
v___x_295_ = 0;
v___x_296_ = lean_uint32_dec_eq(v___x_294_, v___x_295_);
if (v___x_296_ == 0)
{
goto v___jp_281_;
}
else
{
uint32_t v___x_297_; 
v___x_297_ = lean_uint32_lor(v___y_192_, v___x_293_);
return v___x_297_;
}
}
}
v___jp_298_:
{
float v_result_301_; uint8_t v___x_302_; 
v_result_301_ = lean_float32_mul(v___y_299_, v___y_300_);
v___x_302_ = lean_float32_beq(v_result_301_, v_result_301_);
if (v___x_302_ == 0)
{
uint32_t v___x_303_; uint32_t v___x_304_; uint32_t v___x_305_; uint32_t v___x_306_; uint8_t v___x_307_; 
v___x_303_ = 23;
v___x_304_ = lean_uint32_shift_right(v___y_192_, v___x_303_);
v___x_305_ = 255;
v___x_306_ = lean_uint32_land(v___x_304_, v___x_305_);
v___x_307_ = lean_uint32_dec_eq(v___x_306_, v___x_305_);
if (v___x_307_ == 0)
{
v___y_292_ = v___x_307_;
goto v___jp_291_;
}
else
{
uint32_t v___x_308_; uint32_t v___x_309_; uint32_t v___x_310_; uint8_t v___x_311_; 
v___x_308_ = 8388607;
v___x_309_ = lean_uint32_land(v___y_192_, v___x_308_);
v___x_310_ = 0;
v___x_311_ = lean_uint32_dec_eq(v___x_309_, v___x_310_);
if (v___x_311_ == 0)
{
v___y_292_ = v___x_307_;
goto v___jp_291_;
}
else
{
goto v___jp_281_;
}
}
}
else
{
uint32_t v___x_312_; 
v___x_312_ = lean_float32_to_bits(v_result_301_);
return v___x_312_;
}
}
v___jp_313_:
{
if (v___y_315_ == 0)
{
float v___x_316_; 
v___x_316_ = lean_float32_of_bits(v___y_193_);
v___y_299_ = v___y_314_;
v___y_300_ = v___x_316_;
goto v___jp_298_;
}
else
{
uint32_t v___x_317_; uint32_t v___x_318_; uint32_t v___x_319_; uint32_t v___x_320_; float v___x_321_; lean_object* v___x_322_; uint32_t v___x_323_; uint32_t v___x_324_; lean_object* v___x_325_; lean_object* v___x_326_; float v___x_327_; float v___x_328_; 
v___x_317_ = 8388607;
v___x_318_ = lean_uint32_land(v___y_193_, v___x_317_);
v___x_319_ = 8388608;
v___x_320_ = lean_uint32_lor(v___x_318_, v___x_319_);
v___x_321_ = lean_uint32_to_float32(v___x_320_);
v___x_322_ = lp_competition_R2W01b_scaleTable;
v___x_323_ = 23;
v___x_324_ = lean_uint32_shift_right(v___y_193_, v___x_323_);
v___x_325_ = lean_uint32_to_nat(v___x_324_);
v___x_326_ = lean_array_fget_borrowed(v___x_322_, v___x_325_);
lean_dec(v___x_325_);
v___x_327_ = lean_unbox_float32(v___x_326_);
v___x_328_ = lean_float32_mul(v___x_321_, v___x_327_);
v___y_299_ = v___y_314_;
v___y_300_ = v___x_328_;
goto v___jp_298_;
}
}
v___jp_329_:
{
uint32_t v___x_331_; uint32_t v_a_332_; uint32_t v___x_333_; uint32_t v___x_334_; uint32_t v___x_335_; uint8_t v___x_336_; 
v___x_331_ = 2147483647;
v_a_332_ = lean_uint32_land(v___y_193_, v___x_331_);
v___x_333_ = 201326591;
v___x_334_ = 1;
v___x_335_ = lean_uint32_sub(v_a_332_, v___x_334_);
v___x_336_ = lean_uint32_dec_le(v___x_333_, v___x_335_);
if (v___x_336_ == 0)
{
v___y_314_ = v___y_330_;
v___y_315_ = v___x_336_;
goto v___jp_313_;
}
else
{
uint32_t v___x_337_; uint8_t v___x_338_; 
v___x_337_ = 2139095040;
v___x_338_ = lean_uint32_dec_lt(v_a_332_, v___x_337_);
v___y_314_ = v___y_330_;
v___y_315_ = v___x_338_;
goto v___jp_313_;
}
}
v___jp_339_:
{
if (v___y_340_ == 0)
{
float v___x_341_; 
v___x_341_ = lean_float32_of_bits(v___y_192_);
v___y_330_ = v___x_341_;
goto v___jp_329_;
}
else
{
uint32_t v___x_342_; uint32_t v___x_343_; uint32_t v___x_344_; uint32_t v___x_345_; float v___x_346_; lean_object* v___x_347_; uint32_t v___x_348_; uint32_t v___x_349_; lean_object* v___x_350_; lean_object* v___x_351_; float v___x_352_; float v___x_353_; 
v___x_342_ = 8388607;
v___x_343_ = lean_uint32_land(v___y_192_, v___x_342_);
v___x_344_ = 8388608;
v___x_345_ = lean_uint32_lor(v___x_343_, v___x_344_);
v___x_346_ = lean_uint32_to_float32(v___x_345_);
v___x_347_ = lp_competition_R2W01b_scaleTable;
v___x_348_ = 23;
v___x_349_ = lean_uint32_shift_right(v___y_192_, v___x_348_);
v___x_350_ = lean_uint32_to_nat(v___x_349_);
v___x_351_ = lean_array_fget_borrowed(v___x_347_, v___x_350_);
lean_dec(v___x_350_);
v___x_352_ = lean_unbox_float32(v___x_351_);
v___x_353_ = lean_float32_mul(v___x_346_, v___x_352_);
v___y_330_ = v___x_353_;
goto v___jp_329_;
}
}
v___jp_354_:
{
uint32_t v___x_355_; uint32_t v_a_356_; uint32_t v___x_357_; uint32_t v___x_358_; uint32_t v___x_359_; uint8_t v___x_360_; 
v___x_355_ = 2147483647;
v_a_356_ = lean_uint32_land(v___y_192_, v___x_355_);
v___x_357_ = 201326591;
v___x_358_ = 1;
v___x_359_ = lean_uint32_sub(v_a_356_, v___x_358_);
v___x_360_ = lean_uint32_dec_le(v___x_357_, v___x_359_);
if (v___x_360_ == 0)
{
v___y_340_ = v___x_360_;
goto v___jp_339_;
}
else
{
uint32_t v___x_361_; uint8_t v___x_362_; 
v___x_361_ = 2139095040;
v___x_362_ = lean_uint32_dec_lt(v_a_356_, v___x_361_);
v___y_340_ = v___x_362_;
goto v___jp_339_;
}
}
v___jp_363_:
{
if (v___y_364_ == 0)
{
goto v___jp_354_;
}
else
{
uint32_t v___x_365_; uint32_t v___x_366_; 
v___x_365_ = 4194304;
v___x_366_ = lean_uint32_lor(v___y_193_, v___x_365_);
return v___x_366_;
}
}
v___jp_370_:
{
uint32_t v___x_375_; uint32_t v___x_376_; uint32_t v___x_377_; uint32_t v___x_378_; uint32_t v___x_379_; 
v___x_375_ = lean_uint32_land(v___y_371_, v___x_369_);
v___x_376_ = lean_uint32_shift_left(v___x_375_, v___x_367_);
v___x_377_ = lean_uint32_lor(v___y_374_, v___x_376_);
v___x_378_ = lean_uint32_land(v___y_373_, v___y_372_);
v___x_379_ = lean_uint32_lor(v___x_377_, v___x_378_);
return v___x_379_;
}
v___jp_380_:
{
if (v___y_381_ == 0)
{
uint32_t v___x_385_; 
v___x_385_ = 0;
v___y_371_ = v___y_382_;
v___y_372_ = v___y_383_;
v___y_373_ = v___y_384_;
v___y_374_ = v___x_385_;
goto v___jp_370_;
}
else
{
uint32_t v___x_386_; 
v___x_386_ = 2147483648;
v___y_371_ = v___y_382_;
v___y_372_ = v___y_383_;
v___y_373_ = v___y_384_;
v___y_374_ = v___x_386_;
goto v___jp_370_;
}
}
v___jp_387_:
{
uint64_t v___x_393_; uint64_t v_encodedExponent_394_; uint32_t v___x_395_; uint64_t v___x_396_; uint8_t v___x_397_; 
v___x_393_ = 171ULL;
v_encodedExponent_394_ = lean_uint64_sub(v___y_389_, v___x_393_);
v___x_395_ = lean_uint64_to_uint32(v_encodedExponent_394_);
v___x_396_ = 8388608ULL;
v___x_397_ = lean_uint64_dec_lt(v___y_392_, v___x_396_);
if (v___x_397_ == 0)
{
uint64_t v___x_398_; uint32_t v___x_399_; 
v___x_398_ = lean_uint64_sub(v___y_392_, v___x_396_);
v___x_399_ = lean_uint64_to_uint32(v___x_398_);
v___y_381_ = v___y_388_;
v___y_382_ = v___x_395_;
v___y_383_ = v___y_390_;
v___y_384_ = v___x_399_;
goto v___jp_380_;
}
else
{
uint32_t v___x_400_; 
v___x_400_ = lean_uint64_to_uint32(v___y_391_);
v___y_381_ = v___y_388_;
v___y_382_ = v___x_395_;
v___y_383_ = v___y_390_;
v___y_384_ = v___x_400_;
goto v___jp_380_;
}
}
v___jp_401_:
{
uint64_t v___x_408_; uint8_t v___x_409_; 
v___x_408_ = 425ULL;
v___x_409_ = lean_uint64_dec_lt(v___x_408_, v___y_407_);
if (v___x_409_ == 0)
{
if (v___y_403_ == 0)
{
v___y_388_ = v___y_402_;
v___y_389_ = v___y_407_;
v___y_390_ = v___y_404_;
v___y_391_ = v___y_406_;
v___y_392_ = v___y_405_;
goto v___jp_387_;
}
else
{
uint64_t v___x_410_; 
v___x_410_ = 8388608ULL;
v___y_388_ = v___y_402_;
v___y_389_ = v___y_407_;
v___y_390_ = v___y_404_;
v___y_391_ = v___y_406_;
v___y_392_ = v___x_410_;
goto v___jp_387_;
}
}
else
{
if (v___y_402_ == 0)
{
uint32_t v___x_411_; 
v___x_411_ = 2139095040;
return v___x_411_;
}
else
{
uint32_t v___x_412_; 
v___x_412_ = 4286578688;
return v___x_412_;
}
}
}
v___jp_413_:
{
uint64_t v___x_419_; uint8_t v_carry_420_; 
v___x_419_ = 16777216ULL;
v_carry_420_ = lean_uint64_dec_eq(v___y_418_, v___x_419_);
if (v_carry_420_ == 0)
{
v___y_402_ = v___y_414_;
v___y_403_ = v_carry_420_;
v___y_404_ = v___y_415_;
v___y_405_ = v___y_418_;
v___y_406_ = v___y_417_;
v___y_407_ = v___y_416_;
goto v___jp_401_;
}
else
{
uint64_t v___x_421_; uint64_t v___x_422_; 
v___x_421_ = 1ULL;
v___x_422_ = lean_uint64_add(v___y_416_, v___x_421_);
v___y_402_ = v___y_414_;
v___y_403_ = v_carry_420_;
v___y_404_ = v___y_415_;
v___y_405_ = v___y_418_;
v___y_406_ = v___y_417_;
v___y_407_ = v___x_422_;
goto v___jp_401_;
}
}
v___jp_423_:
{
uint64_t v_position_430_; uint64_t v___x_431_; uint8_t v___x_432_; 
v_position_430_ = lean_uint64_add(v___y_429_, v___y_427_);
v___x_431_ = 172ULL;
v___x_432_ = lean_uint64_dec_lt(v_position_430_, v___x_431_);
if (v___x_432_ == 0)
{
uint64_t v___x_433_; uint8_t v___x_434_; 
v___x_433_ = 23ULL;
v___x_434_ = lean_uint64_dec_lt(v___y_429_, v___x_433_);
if (v___x_434_ == 0)
{
uint64_t v___x_435_; uint8_t v___x_436_; 
v___x_435_ = lean_uint64_sub(v___y_429_, v___x_433_);
v___x_436_ = lean_uint64_dec_eq(v___x_435_, v___y_428_);
if (v___x_436_ == 0)
{
uint64_t v___x_437_; uint8_t v___x_438_; 
v___x_437_ = 64ULL;
v___x_438_ = lean_uint64_dec_lt(v___x_435_, v___x_437_);
if (v___x_438_ == 0)
{
uint8_t v___x_439_; 
v___x_439_ = lean_uint64_dec_eq(v___x_435_, v___x_437_);
if (v___x_439_ == 0)
{
v___y_414_ = v___y_424_;
v___y_415_ = v___y_426_;
v___y_416_ = v_position_430_;
v___y_417_ = v___y_428_;
v___y_418_ = v___y_428_;
goto v___jp_413_;
}
else
{
uint64_t v___x_440_; uint8_t v___x_441_; 
v___x_440_ = 9223372036854775808ULL;
v___x_441_ = lean_uint64_dec_lt(v___x_440_, v___y_425_);
if (v___x_441_ == 0)
{
v___y_414_ = v___y_424_;
v___y_415_ = v___y_426_;
v___y_416_ = v_position_430_;
v___y_417_ = v___y_428_;
v___y_418_ = v___y_428_;
goto v___jp_413_;
}
else
{
uint64_t v___x_442_; 
v___x_442_ = 1ULL;
v___y_414_ = v___y_424_;
v___y_415_ = v___y_426_;
v___y_416_ = v_position_430_;
v___y_417_ = v___y_428_;
v___y_418_ = v___x_442_;
goto v___jp_413_;
}
}
}
else
{
uint64_t v_quotient_443_; uint64_t v___x_444_; uint64_t v___x_445_; uint64_t v___x_446_; uint64_t v_remainder_447_; uint64_t v___x_448_; uint64_t v_half_449_; uint8_t v___x_450_; 
v_quotient_443_ = lean_uint64_shift_right(v___y_425_, v___x_435_);
v___x_444_ = 1ULL;
v___x_445_ = lean_uint64_shift_left(v___x_444_, v___x_435_);
v___x_446_ = lean_uint64_sub(v___x_445_, v___x_444_);
v_remainder_447_ = lean_uint64_land(v___y_425_, v___x_446_);
v___x_448_ = lean_uint64_sub(v___x_435_, v___x_444_);
v_half_449_ = lean_uint64_shift_left(v___x_444_, v___x_448_);
v___x_450_ = lean_uint64_dec_lt(v_remainder_447_, v_half_449_);
if (v___x_450_ == 0)
{
uint8_t v___x_451_; 
v___x_451_ = lean_uint64_dec_lt(v_half_449_, v_remainder_447_);
if (v___x_451_ == 0)
{
uint64_t v___x_452_; uint8_t v___x_453_; 
v___x_452_ = lean_uint64_land(v_quotient_443_, v___x_444_);
v___x_453_ = lean_uint64_dec_eq(v___x_452_, v___y_428_);
if (v___x_453_ == 0)
{
uint64_t v___x_454_; 
v___x_454_ = lean_uint64_add(v_quotient_443_, v___x_444_);
v___y_414_ = v___y_424_;
v___y_415_ = v___y_426_;
v___y_416_ = v_position_430_;
v___y_417_ = v___y_428_;
v___y_418_ = v___x_454_;
goto v___jp_413_;
}
else
{
v___y_414_ = v___y_424_;
v___y_415_ = v___y_426_;
v___y_416_ = v_position_430_;
v___y_417_ = v___y_428_;
v___y_418_ = v_quotient_443_;
goto v___jp_413_;
}
}
else
{
uint64_t v___x_455_; 
v___x_455_ = lean_uint64_add(v_quotient_443_, v___x_444_);
v___y_414_ = v___y_424_;
v___y_415_ = v___y_426_;
v___y_416_ = v_position_430_;
v___y_417_ = v___y_428_;
v___y_418_ = v___x_455_;
goto v___jp_413_;
}
}
else
{
v___y_414_ = v___y_424_;
v___y_415_ = v___y_426_;
v___y_416_ = v_position_430_;
v___y_417_ = v___y_428_;
v___y_418_ = v_quotient_443_;
goto v___jp_413_;
}
}
}
else
{
v___y_414_ = v___y_424_;
v___y_415_ = v___y_426_;
v___y_416_ = v_position_430_;
v___y_417_ = v___y_428_;
v___y_418_ = v___y_425_;
goto v___jp_413_;
}
}
else
{
uint64_t v___x_456_; uint64_t v___x_457_; 
v___x_456_ = lean_uint64_sub(v___x_433_, v___y_429_);
v___x_457_ = lean_uint64_shift_left(v___y_425_, v___x_456_);
v___y_414_ = v___y_424_;
v___y_415_ = v___y_426_;
v___y_416_ = v_position_430_;
v___y_417_ = v___y_428_;
v___y_418_ = v___x_457_;
goto v___jp_413_;
}
}
else
{
uint64_t v___x_458_; uint8_t v___x_459_; 
v___x_458_ = 149ULL;
v___x_459_ = lean_uint64_dec_lt(v___y_427_, v___x_458_);
if (v___x_459_ == 0)
{
uint64_t v___x_460_; uint64_t v___x_461_; 
v___x_460_ = lean_uint64_sub(v___y_427_, v___x_458_);
v___x_461_ = lean_uint64_shift_left(v___y_425_, v___x_460_);
v___y_211_ = v___y_424_;
v___y_212_ = v___y_426_;
v___y_213_ = v___y_428_;
v___y_214_ = v___x_461_;
goto v___jp_210_;
}
else
{
uint64_t v___x_462_; uint8_t v___x_463_; 
v___x_462_ = lean_uint64_sub(v___x_458_, v___y_427_);
v___x_463_ = lean_uint64_dec_eq(v___x_462_, v___y_428_);
if (v___x_463_ == 0)
{
uint64_t v___x_464_; uint8_t v___x_465_; 
v___x_464_ = 64ULL;
v___x_465_ = lean_uint64_dec_lt(v___x_462_, v___x_464_);
if (v___x_465_ == 0)
{
uint8_t v___x_466_; 
v___x_466_ = lean_uint64_dec_eq(v___x_462_, v___x_464_);
if (v___x_466_ == 0)
{
v___y_211_ = v___y_424_;
v___y_212_ = v___y_426_;
v___y_213_ = v___y_428_;
v___y_214_ = v___y_428_;
goto v___jp_210_;
}
else
{
uint64_t v___x_467_; uint8_t v___x_468_; 
v___x_467_ = 9223372036854775808ULL;
v___x_468_ = lean_uint64_dec_lt(v___x_467_, v___y_425_);
if (v___x_468_ == 0)
{
v___y_211_ = v___y_424_;
v___y_212_ = v___y_426_;
v___y_213_ = v___y_428_;
v___y_214_ = v___y_428_;
goto v___jp_210_;
}
else
{
uint64_t v___x_469_; 
v___x_469_ = 1ULL;
v___y_211_ = v___y_424_;
v___y_212_ = v___y_426_;
v___y_213_ = v___y_428_;
v___y_214_ = v___x_469_;
goto v___jp_210_;
}
}
}
else
{
uint64_t v_quotient_470_; uint64_t v___x_471_; uint64_t v___x_472_; uint64_t v___x_473_; uint64_t v_remainder_474_; uint64_t v___x_475_; uint64_t v_half_476_; uint8_t v___x_477_; 
v_quotient_470_ = lean_uint64_shift_right(v___y_425_, v___x_462_);
v___x_471_ = 1ULL;
v___x_472_ = lean_uint64_shift_left(v___x_471_, v___x_462_);
v___x_473_ = lean_uint64_sub(v___x_472_, v___x_471_);
v_remainder_474_ = lean_uint64_land(v___y_425_, v___x_473_);
v___x_475_ = lean_uint64_sub(v___x_462_, v___x_471_);
v_half_476_ = lean_uint64_shift_left(v___x_471_, v___x_475_);
v___x_477_ = lean_uint64_dec_lt(v_remainder_474_, v_half_476_);
if (v___x_477_ == 0)
{
uint8_t v___x_478_; 
v___x_478_ = lean_uint64_dec_lt(v_half_476_, v_remainder_474_);
if (v___x_478_ == 0)
{
uint64_t v___x_479_; uint8_t v___x_480_; 
v___x_479_ = lean_uint64_land(v_quotient_470_, v___x_471_);
v___x_480_ = lean_uint64_dec_eq(v___x_479_, v___y_428_);
if (v___x_480_ == 0)
{
uint64_t v___x_481_; 
v___x_481_ = lean_uint64_add(v_quotient_470_, v___x_471_);
v___y_211_ = v___y_424_;
v___y_212_ = v___y_426_;
v___y_213_ = v___y_428_;
v___y_214_ = v___x_481_;
goto v___jp_210_;
}
else
{
v___y_211_ = v___y_424_;
v___y_212_ = v___y_426_;
v___y_213_ = v___y_428_;
v___y_214_ = v_quotient_470_;
goto v___jp_210_;
}
}
else
{
uint64_t v___x_482_; 
v___x_482_ = lean_uint64_add(v_quotient_470_, v___x_471_);
v___y_211_ = v___y_424_;
v___y_212_ = v___y_426_;
v___y_213_ = v___y_428_;
v___y_214_ = v___x_482_;
goto v___jp_210_;
}
}
else
{
v___y_211_ = v___y_424_;
v___y_212_ = v___y_426_;
v___y_213_ = v___y_428_;
v___y_214_ = v_quotient_470_;
goto v___jp_210_;
}
}
}
else
{
v___y_211_ = v___y_424_;
v___y_212_ = v___y_426_;
v___y_213_ = v___y_428_;
v___y_214_ = v___y_425_;
goto v___jp_210_;
}
}
}
}
v___jp_483_:
{
uint64_t v___x_491_; uint64_t v___x_492_; uint8_t v___x_493_; 
v___x_491_ = 1ULL;
v___x_492_ = lean_uint64_shift_right(v___y_485_, v___x_491_);
v___x_493_ = lean_uint64_dec_eq(v___x_492_, v___y_489_);
if (v___x_493_ == 0)
{
uint64_t v___x_494_; 
v___x_494_ = lean_uint64_add(v___y_490_, v___x_491_);
v___y_424_ = v___y_484_;
v___y_425_ = v___y_486_;
v___y_426_ = v___y_487_;
v___y_427_ = v___y_488_;
v___y_428_ = v___y_489_;
v___y_429_ = v___x_494_;
goto v___jp_423_;
}
else
{
v___y_424_ = v___y_484_;
v___y_425_ = v___y_486_;
v___y_426_ = v___y_487_;
v___y_427_ = v___y_488_;
v___y_428_ = v___y_489_;
v___y_429_ = v___y_490_;
goto v___jp_423_;
}
}
v___jp_495_:
{
uint64_t v___x_505_; uint8_t v___x_506_; 
v___x_505_ = lean_uint64_shift_right(v___y_499_, v___y_496_);
v___x_506_ = lean_uint64_dec_eq(v___x_505_, v___y_503_);
if (v___x_506_ == 0)
{
uint64_t v___x_507_; 
v___x_507_ = lean_uint64_add(v___y_500_, v___y_496_);
v___y_484_ = v___y_497_;
v___y_485_ = v___y_504_;
v___y_486_ = v___y_498_;
v___y_487_ = v___y_501_;
v___y_488_ = v___y_502_;
v___y_489_ = v___y_503_;
v___y_490_ = v___x_507_;
goto v___jp_483_;
}
else
{
v___y_484_ = v___y_497_;
v___y_485_ = v___y_504_;
v___y_486_ = v___y_498_;
v___y_487_ = v___y_501_;
v___y_488_ = v___y_502_;
v___y_489_ = v___y_503_;
v___y_490_ = v___y_500_;
goto v___jp_483_;
}
}
v___jp_508_:
{
uint64_t v___x_516_; uint64_t v___x_517_; uint8_t v___x_518_; 
v___x_516_ = 2ULL;
v___x_517_ = lean_uint64_shift_right(v___y_511_, v___x_516_);
v___x_518_ = lean_uint64_dec_eq(v___x_517_, v___y_514_);
if (v___x_518_ == 0)
{
v___y_496_ = v___x_516_;
v___y_497_ = v___y_509_;
v___y_498_ = v___y_510_;
v___y_499_ = v___y_511_;
v___y_500_ = v___y_515_;
v___y_501_ = v___y_512_;
v___y_502_ = v___y_513_;
v___y_503_ = v___y_514_;
v___y_504_ = v___x_517_;
goto v___jp_495_;
}
else
{
v___y_496_ = v___x_516_;
v___y_497_ = v___y_509_;
v___y_498_ = v___y_510_;
v___y_499_ = v___y_511_;
v___y_500_ = v___y_515_;
v___y_501_ = v___y_512_;
v___y_502_ = v___y_513_;
v___y_503_ = v___y_514_;
v___y_504_ = v___y_511_;
goto v___jp_495_;
}
}
v___jp_519_:
{
uint64_t v___x_529_; uint8_t v___x_530_; 
v___x_529_ = lean_uint64_shift_right(v___y_524_, v___y_523_);
v___x_530_ = lean_uint64_dec_eq(v___x_529_, v___y_527_);
if (v___x_530_ == 0)
{
uint64_t v___x_531_; 
v___x_531_ = lean_uint64_add(v___y_522_, v___y_523_);
v___y_509_ = v___y_520_;
v___y_510_ = v___y_521_;
v___y_511_ = v___y_528_;
v___y_512_ = v___y_525_;
v___y_513_ = v___y_526_;
v___y_514_ = v___y_527_;
v___y_515_ = v___x_531_;
goto v___jp_508_;
}
else
{
v___y_509_ = v___y_520_;
v___y_510_ = v___y_521_;
v___y_511_ = v___y_528_;
v___y_512_ = v___y_525_;
v___y_513_ = v___y_526_;
v___y_514_ = v___y_527_;
v___y_515_ = v___y_522_;
goto v___jp_508_;
}
}
v___jp_532_:
{
uint64_t v___x_540_; uint64_t v___x_541_; uint8_t v___x_542_; 
v___x_540_ = 4ULL;
v___x_541_ = lean_uint64_shift_right(v___y_535_, v___x_540_);
v___x_542_ = lean_uint64_dec_eq(v___x_541_, v___y_538_);
if (v___x_542_ == 0)
{
v___y_520_ = v___y_533_;
v___y_521_ = v___y_534_;
v___y_522_ = v___y_539_;
v___y_523_ = v___x_540_;
v___y_524_ = v___y_535_;
v___y_525_ = v___y_536_;
v___y_526_ = v___y_537_;
v___y_527_ = v___y_538_;
v___y_528_ = v___x_541_;
goto v___jp_519_;
}
else
{
v___y_520_ = v___y_533_;
v___y_521_ = v___y_534_;
v___y_522_ = v___y_539_;
v___y_523_ = v___x_540_;
v___y_524_ = v___y_535_;
v___y_525_ = v___y_536_;
v___y_526_ = v___y_537_;
v___y_527_ = v___y_538_;
v___y_528_ = v___y_535_;
goto v___jp_519_;
}
}
v___jp_543_:
{
uint64_t v___x_553_; uint8_t v___x_554_; 
v___x_553_ = lean_uint64_shift_right(v___y_548_, v___y_544_);
v___x_554_ = lean_uint64_dec_eq(v___x_553_, v___y_551_);
if (v___x_554_ == 0)
{
uint64_t v___x_555_; 
v___x_555_ = lean_uint64_add(v___y_550_, v___y_544_);
v___y_533_ = v___y_545_;
v___y_534_ = v___y_546_;
v___y_535_ = v___y_552_;
v___y_536_ = v___y_547_;
v___y_537_ = v___y_549_;
v___y_538_ = v___y_551_;
v___y_539_ = v___x_555_;
goto v___jp_532_;
}
else
{
v___y_533_ = v___y_545_;
v___y_534_ = v___y_546_;
v___y_535_ = v___y_552_;
v___y_536_ = v___y_547_;
v___y_537_ = v___y_549_;
v___y_538_ = v___y_551_;
v___y_539_ = v___y_550_;
goto v___jp_532_;
}
}
v___jp_556_:
{
uint64_t v___x_564_; uint64_t v___x_565_; uint8_t v___x_566_; 
v___x_564_ = 8ULL;
v___x_565_ = lean_uint64_shift_right(v___y_561_, v___x_564_);
v___x_566_ = lean_uint64_dec_eq(v___x_565_, v___y_562_);
if (v___x_566_ == 0)
{
v___y_544_ = v___x_564_;
v___y_545_ = v___y_557_;
v___y_546_ = v___y_558_;
v___y_547_ = v___y_559_;
v___y_548_ = v___y_561_;
v___y_549_ = v___y_560_;
v___y_550_ = v___y_563_;
v___y_551_ = v___y_562_;
v___y_552_ = v___x_565_;
goto v___jp_543_;
}
else
{
v___y_544_ = v___x_564_;
v___y_545_ = v___y_557_;
v___y_546_ = v___y_558_;
v___y_547_ = v___y_559_;
v___y_548_ = v___y_561_;
v___y_549_ = v___y_560_;
v___y_550_ = v___y_563_;
v___y_551_ = v___y_562_;
v___y_552_ = v___y_561_;
goto v___jp_543_;
}
}
v___jp_567_:
{
uint64_t v___x_577_; uint8_t v___x_578_; 
v___x_577_ = lean_uint64_shift_right(v___y_571_, v___y_574_);
v___x_578_ = lean_uint64_dec_eq(v___x_577_, v___y_575_);
if (v___x_578_ == 0)
{
uint64_t v___x_579_; 
v___x_579_ = lean_uint64_add(v___y_570_, v___y_574_);
v___y_557_ = v___y_568_;
v___y_558_ = v___y_569_;
v___y_559_ = v___y_572_;
v___y_560_ = v___y_573_;
v___y_561_ = v___y_576_;
v___y_562_ = v___y_575_;
v___y_563_ = v___x_579_;
goto v___jp_556_;
}
else
{
v___y_557_ = v___y_568_;
v___y_558_ = v___y_569_;
v___y_559_ = v___y_572_;
v___y_560_ = v___y_573_;
v___y_561_ = v___y_576_;
v___y_562_ = v___y_575_;
v___y_563_ = v___y_570_;
goto v___jp_556_;
}
}
v___jp_580_:
{
uint64_t v___x_588_; uint64_t v___x_589_; uint8_t v___x_590_; 
v___x_588_ = 16ULL;
v___x_589_ = lean_uint64_shift_right(v___y_583_, v___x_588_);
v___x_590_ = lean_uint64_dec_eq(v___x_589_, v___y_586_);
if (v___x_590_ == 0)
{
v___y_568_ = v___y_581_;
v___y_569_ = v___y_582_;
v___y_570_ = v___y_587_;
v___y_571_ = v___y_583_;
v___y_572_ = v___y_584_;
v___y_573_ = v___y_585_;
v___y_574_ = v___x_588_;
v___y_575_ = v___y_586_;
v___y_576_ = v___x_589_;
goto v___jp_567_;
}
else
{
v___y_568_ = v___y_581_;
v___y_569_ = v___y_582_;
v___y_570_ = v___y_587_;
v___y_571_ = v___y_583_;
v___y_572_ = v___y_584_;
v___y_573_ = v___y_585_;
v___y_574_ = v___x_588_;
v___y_575_ = v___y_586_;
v___y_576_ = v___y_583_;
goto v___jp_567_;
}
}
v___jp_591_:
{
uint64_t v___x_599_; uint8_t v___x_600_; 
v___x_599_ = lean_uint64_shift_right(v___y_593_, v___y_596_);
v___x_600_ = lean_uint64_dec_eq(v___x_599_, v___y_597_);
if (v___x_600_ == 0)
{
v___y_581_ = v___y_592_;
v___y_582_ = v___y_593_;
v___y_583_ = v___y_598_;
v___y_584_ = v___y_594_;
v___y_585_ = v___y_595_;
v___y_586_ = v___y_597_;
v___y_587_ = v___y_596_;
goto v___jp_580_;
}
else
{
v___y_581_ = v___y_592_;
v___y_582_ = v___y_593_;
v___y_583_ = v___y_598_;
v___y_584_ = v___y_594_;
v___y_585_ = v___y_595_;
v___y_586_ = v___y_597_;
v___y_587_ = v___y_597_;
goto v___jp_580_;
}
}
v___jp_601_:
{
uint64_t v___x_606_; uint8_t v___x_607_; 
v___x_606_ = 0ULL;
v___x_607_ = lean_uint64_dec_eq(v___y_603_, v___x_606_);
if (v___x_607_ == 0)
{
uint64_t v___x_608_; uint64_t v___x_609_; uint8_t v___x_610_; 
v___x_608_ = 32ULL;
v___x_609_ = lean_uint64_shift_right(v___y_603_, v___x_608_);
v___x_610_ = lean_uint64_dec_eq(v___x_609_, v___x_606_);
if (v___x_610_ == 0)
{
v___y_592_ = v___y_602_;
v___y_593_ = v___y_603_;
v___y_594_ = v___y_604_;
v___y_595_ = v___y_605_;
v___y_596_ = v___x_608_;
v___y_597_ = v___x_606_;
v___y_598_ = v___x_609_;
goto v___jp_591_;
}
else
{
v___y_592_ = v___y_602_;
v___y_593_ = v___y_603_;
v___y_594_ = v___y_604_;
v___y_595_ = v___y_605_;
v___y_596_ = v___x_608_;
v___y_597_ = v___x_606_;
v___y_598_ = v___y_603_;
goto v___jp_591_;
}
}
else
{
if (v___y_602_ == 0)
{
uint32_t v___x_611_; 
v___x_611_ = 0;
return v___x_611_;
}
else
{
uint32_t v___x_612_; 
v___x_612_ = 2147483648;
return v___x_612_;
}
}
}
v___jp_613_:
{
uint64_t v___x_620_; uint64_t v___x_621_; uint64_t v___x_622_; uint8_t v___x_623_; 
v___x_620_ = lean_uint64_mul(v___y_618_, v___y_616_);
v___x_621_ = lean_uint64_add(v___y_615_, v___y_619_);
v___x_622_ = 281474976710656ULL;
v___x_623_ = lean_uint64_dec_lt(v___x_620_, v___x_622_);
if (v___x_623_ == 0)
{
v___y_602_ = v___y_614_;
v___y_603_ = v___x_620_;
v___y_604_ = v___y_617_;
v___y_605_ = v___x_621_;
goto v___jp_601_;
}
else
{
uint64_t v___x_624_; uint8_t v___x_625_; 
v___x_624_ = 123ULL;
v___x_625_ = lean_uint64_dec_le(v___x_621_, v___x_624_);
if (v___x_625_ == 0)
{
v___y_602_ = v___y_614_;
v___y_603_ = v___x_620_;
v___y_604_ = v___y_617_;
v___y_605_ = v___x_621_;
goto v___jp_601_;
}
else
{
uint64_t v___x_626_; uint8_t v___x_627_; 
v___x_626_ = 0ULL;
v___x_627_ = lean_uint64_dec_eq(v___x_620_, v___x_626_);
if (v___x_627_ == 0)
{
uint64_t v___x_628_; uint64_t v___x_629_; uint8_t v___x_630_; 
v___x_628_ = 149ULL;
v___x_629_ = lean_uint64_sub(v___x_628_, v___x_621_);
v___x_630_ = lean_uint64_dec_eq(v___x_629_, v___x_626_);
if (v___x_630_ == 0)
{
uint64_t v___x_631_; uint8_t v___x_632_; 
v___x_631_ = 64ULL;
v___x_632_ = lean_uint64_dec_lt(v___x_629_, v___x_631_);
if (v___x_632_ == 0)
{
uint8_t v___x_633_; 
v___x_633_ = lean_uint64_dec_eq(v___x_629_, v___x_631_);
if (v___x_633_ == 0)
{
v___y_230_ = v___y_614_;
v___y_231_ = v___y_617_;
v___y_232_ = v___x_626_;
v___y_233_ = v___x_626_;
goto v___jp_229_;
}
else
{
uint64_t v___x_634_; uint8_t v___x_635_; 
v___x_634_ = 9223372036854775808ULL;
v___x_635_ = lean_uint64_dec_lt(v___x_634_, v___x_620_);
if (v___x_635_ == 0)
{
v___y_230_ = v___y_614_;
v___y_231_ = v___y_617_;
v___y_232_ = v___x_626_;
v___y_233_ = v___x_626_;
goto v___jp_229_;
}
else
{
uint64_t v___x_636_; 
v___x_636_ = 1ULL;
v___y_230_ = v___y_614_;
v___y_231_ = v___y_617_;
v___y_232_ = v___x_626_;
v___y_233_ = v___x_636_;
goto v___jp_229_;
}
}
}
else
{
uint64_t v_quotient_637_; uint64_t v___x_638_; uint64_t v___x_639_; uint64_t v___x_640_; uint64_t v_remainder_641_; uint64_t v___x_642_; uint64_t v_half_643_; uint8_t v___x_644_; 
v_quotient_637_ = lean_uint64_shift_right(v___x_620_, v___x_629_);
v___x_638_ = 1ULL;
v___x_639_ = lean_uint64_shift_left(v___x_638_, v___x_629_);
v___x_640_ = lean_uint64_sub(v___x_639_, v___x_638_);
v_remainder_641_ = lean_uint64_land(v___x_620_, v___x_640_);
v___x_642_ = lean_uint64_sub(v___x_629_, v___x_638_);
v_half_643_ = lean_uint64_shift_left(v___x_638_, v___x_642_);
v___x_644_ = lean_uint64_dec_lt(v_remainder_641_, v_half_643_);
if (v___x_644_ == 0)
{
uint8_t v___x_645_; 
v___x_645_ = lean_uint64_dec_lt(v_half_643_, v_remainder_641_);
if (v___x_645_ == 0)
{
uint64_t v___x_646_; uint8_t v___x_647_; 
v___x_646_ = lean_uint64_land(v_quotient_637_, v___x_638_);
v___x_647_ = lean_uint64_dec_eq(v___x_646_, v___x_626_);
if (v___x_647_ == 0)
{
uint64_t v___x_648_; 
v___x_648_ = lean_uint64_add(v_quotient_637_, v___x_638_);
v___y_230_ = v___y_614_;
v___y_231_ = v___y_617_;
v___y_232_ = v___x_626_;
v___y_233_ = v___x_648_;
goto v___jp_229_;
}
else
{
v___y_230_ = v___y_614_;
v___y_231_ = v___y_617_;
v___y_232_ = v___x_626_;
v___y_233_ = v_quotient_637_;
goto v___jp_229_;
}
}
else
{
uint64_t v___x_649_; 
v___x_649_ = lean_uint64_add(v_quotient_637_, v___x_638_);
v___y_230_ = v___y_614_;
v___y_231_ = v___y_617_;
v___y_232_ = v___x_626_;
v___y_233_ = v___x_649_;
goto v___jp_229_;
}
}
else
{
v___y_230_ = v___y_614_;
v___y_231_ = v___y_617_;
v___y_232_ = v___x_626_;
v___y_233_ = v_quotient_637_;
goto v___jp_229_;
}
}
}
else
{
v___y_230_ = v___y_614_;
v___y_231_ = v___y_617_;
v___y_232_ = v___x_626_;
v___y_233_ = v___x_620_;
goto v___jp_229_;
}
}
else
{
if (v___y_614_ == 0)
{
uint32_t v___x_650_; 
v___x_650_ = 0;
return v___x_650_;
}
else
{
uint32_t v___x_651_; 
v___x_651_ = 2147483648;
return v___x_651_;
}
}
}
}
}
v___jp_655_:
{
uint8_t v___x_656_; 
v___x_656_ = lean_uint32_dec_eq(v_ey_654_, v___x_369_);
if (v___x_656_ == 0)
{
v___y_364_ = v___x_656_;
goto v___jp_363_;
}
else
{
uint32_t v___x_657_; uint32_t v___x_658_; uint32_t v___x_659_; uint8_t v___x_660_; 
v___x_657_ = 8388607;
v___x_658_ = lean_uint32_land(v___y_193_, v___x_657_);
v___x_659_ = 0;
v___x_660_ = lean_uint32_dec_eq(v___x_658_, v___x_659_);
if (v___x_660_ == 0)
{
v___y_364_ = v___x_656_;
goto v___jp_363_;
}
else
{
goto v___jp_354_;
}
}
}
v___jp_661_:
{
if (v___y_662_ == 0)
{
goto v___jp_655_;
}
else
{
uint32_t v___x_663_; uint32_t v___x_664_; 
v___x_663_ = 4194304;
v___x_664_ = lean_uint32_lor(v___y_192_, v___x_663_);
return v___x_664_;
}
}
v___jp_665_:
{
uint8_t v___x_666_; 
v___x_666_ = lean_uint32_dec_eq(v_ex_652_, v___x_369_);
if (v___x_666_ == 0)
{
v___y_662_ = v___x_666_;
goto v___jp_661_;
}
else
{
uint32_t v___x_667_; uint32_t v___x_668_; uint32_t v___x_669_; uint8_t v___x_670_; 
v___x_667_ = 8388607;
v___x_668_ = lean_uint32_land(v___y_192_, v___x_667_);
v___x_669_ = 0;
v___x_670_ = lean_uint32_dec_eq(v___x_668_, v___x_669_);
if (v___x_670_ == 0)
{
v___y_662_ = v___x_666_;
goto v___jp_661_;
}
else
{
goto v___jp_655_;
}
}
}
v___jp_671_:
{
if (v___y_672_ == 0)
{
goto v___jp_665_;
}
else
{
uint32_t v___x_673_; uint32_t v___x_674_; uint32_t v___x_675_; uint8_t v___x_676_; 
v___x_673_ = 4194304;
v___x_674_ = lean_uint32_land(v___y_193_, v___x_673_);
v___x_675_ = 0;
v___x_676_ = lean_uint32_dec_eq(v___x_674_, v___x_675_);
if (v___x_676_ == 0)
{
goto v___jp_665_;
}
else
{
uint32_t v___x_677_; 
v___x_677_ = lean_uint32_lor(v___y_193_, v___x_673_);
return v___x_677_;
}
}
}
v___jp_678_:
{
uint8_t v___x_679_; 
v___x_679_ = lean_uint32_dec_eq(v_ey_654_, v___x_369_);
if (v___x_679_ == 0)
{
v___y_672_ = v___x_679_;
goto v___jp_671_;
}
else
{
uint32_t v___x_680_; uint32_t v___x_681_; uint32_t v___x_682_; uint8_t v___x_683_; 
v___x_680_ = 8388607;
v___x_681_ = lean_uint32_land(v___y_193_, v___x_680_);
v___x_682_ = 0;
v___x_683_ = lean_uint32_dec_eq(v___x_681_, v___x_682_);
if (v___x_683_ == 0)
{
v___y_672_ = v___x_679_;
goto v___jp_671_;
}
else
{
goto v___jp_665_;
}
}
}
v___jp_684_:
{
if (v___y_685_ == 0)
{
goto v___jp_678_;
}
else
{
uint32_t v___x_686_; uint32_t v___x_687_; uint32_t v___x_688_; uint8_t v___x_689_; 
v___x_686_ = 4194304;
v___x_687_ = lean_uint32_land(v___y_192_, v___x_686_);
v___x_688_ = 0;
v___x_689_ = lean_uint32_dec_eq(v___x_687_, v___x_688_);
if (v___x_689_ == 0)
{
goto v___jp_678_;
}
else
{
uint32_t v___x_690_; 
v___x_690_ = lean_uint32_lor(v___y_192_, v___x_686_);
return v___x_690_;
}
}
}
v___jp_691_:
{
uint64_t v___x_697_; uint64_t v___x_698_; uint8_t v___x_699_; 
v___x_697_ = lean_uint32_to_uint64(v_ey_654_);
v___x_698_ = 0ULL;
v___x_699_ = lean_uint64_dec_eq(v___x_697_, v___x_698_);
if (v___x_699_ == 0)
{
uint64_t v___x_700_; uint64_t v___x_701_; 
v___x_700_ = 1ULL;
v___x_701_ = lean_uint64_sub(v___x_697_, v___x_700_);
v___y_614_ = v___y_692_;
v___y_615_ = v___y_696_;
v___y_616_ = v___y_693_;
v___y_617_ = v___y_694_;
v___y_618_ = v___y_695_;
v___y_619_ = v___x_701_;
goto v___jp_613_;
}
else
{
v___y_614_ = v___y_692_;
v___y_615_ = v___y_696_;
v___y_616_ = v___y_693_;
v___y_617_ = v___y_694_;
v___y_618_ = v___y_695_;
v___y_619_ = v___x_698_;
goto v___jp_613_;
}
}
v___jp_702_:
{
uint64_t v___x_707_; uint64_t v___x_708_; uint8_t v___x_709_; 
v___x_707_ = lean_uint32_to_uint64(v_ex_652_);
v___x_708_ = 0ULL;
v___x_709_ = lean_uint64_dec_eq(v___x_707_, v___x_708_);
if (v___x_709_ == 0)
{
uint64_t v___x_710_; uint64_t v___x_711_; 
v___x_710_ = 1ULL;
v___x_711_ = lean_uint64_sub(v___x_707_, v___x_710_);
v___y_692_ = v___y_703_;
v___y_693_ = v___y_706_;
v___y_694_ = v___y_704_;
v___y_695_ = v___y_705_;
v___y_696_ = v___x_711_;
goto v___jp_691_;
}
else
{
v___y_692_ = v___y_703_;
v___y_693_ = v___y_706_;
v___y_694_ = v___y_704_;
v___y_695_ = v___y_705_;
v___y_696_ = v___x_708_;
goto v___jp_691_;
}
}
v___jp_712_:
{
uint32_t v___x_717_; uint8_t v___x_718_; 
v___x_717_ = 0;
v___x_718_ = lean_uint32_dec_eq(v_ey_654_, v___x_717_);
if (v___x_718_ == 0)
{
uint64_t v___x_719_; uint64_t v___x_720_; uint64_t v___x_721_; 
v___x_719_ = lean_uint32_to_uint64(v___y_714_);
v___x_720_ = 8388608ULL;
v___x_721_ = lean_uint64_lor(v___x_719_, v___x_720_);
v___y_703_ = v___y_713_;
v___y_704_ = v___y_715_;
v___y_705_ = v___y_716_;
v___y_706_ = v___x_721_;
goto v___jp_702_;
}
else
{
uint64_t v___x_722_; 
v___x_722_ = lean_uint32_to_uint64(v___y_714_);
v___y_703_ = v___y_713_;
v___y_704_ = v___y_715_;
v___y_705_ = v___y_716_;
v___y_706_ = v___x_722_;
goto v___jp_702_;
}
}
v___jp_723_:
{
uint32_t v___x_725_; uint32_t v_xFraction_726_; uint32_t v_yFraction_727_; uint32_t v___x_728_; uint8_t v___x_729_; 
v___x_725_ = 8388607;
v_xFraction_726_ = lean_uint32_land(v___y_192_, v___x_725_);
v_yFraction_727_ = lean_uint32_land(v___y_193_, v___x_725_);
v___x_728_ = 0;
v___x_729_ = lean_uint32_dec_eq(v_ex_652_, v___x_728_);
if (v___x_729_ == 0)
{
uint64_t v___x_730_; uint64_t v___x_731_; uint64_t v___x_732_; 
v___x_730_ = lean_uint32_to_uint64(v_xFraction_726_);
v___x_731_ = 8388608ULL;
v___x_732_ = lean_uint64_lor(v___x_730_, v___x_731_);
v___y_713_ = v___y_724_;
v___y_714_ = v_yFraction_727_;
v___y_715_ = v___x_725_;
v___y_716_ = v___x_732_;
goto v___jp_712_;
}
else
{
uint64_t v___x_733_; 
v___x_733_ = lean_uint32_to_uint64(v_xFraction_726_);
v___y_713_ = v___y_724_;
v___y_714_ = v_yFraction_727_;
v___y_715_ = v___x_725_;
v___y_716_ = v___x_733_;
goto v___jp_712_;
}
}
v___jp_737_:
{
if (v___y_739_ == 0)
{
v___y_724_ = v___x_736_;
goto v___jp_723_;
}
else
{
v___y_724_ = v___y_738_;
goto v___jp_723_;
}
}
v___jp_740_:
{
if (v___y_742_ == 0)
{
if (v___y_743_ == 0)
{
v___y_738_ = v___y_741_;
v___y_739_ = v___x_736_;
goto v___jp_737_;
}
else
{
v___y_724_ = v___x_736_;
goto v___jp_723_;
}
}
else
{
v___y_738_ = v___y_741_;
v___y_739_ = v___y_743_;
goto v___jp_737_;
}
}
v___jp_744_:
{
uint32_t v___x_747_; uint32_t v___x_748_; uint32_t v___x_749_; uint8_t v___x_750_; 
v___x_747_ = 2147483648;
v___x_748_ = lean_uint32_land(v___y_193_, v___x_747_);
v___x_749_ = 0;
v___x_750_ = lean_uint32_dec_eq(v___x_748_, v___x_749_);
if (v___x_750_ == 0)
{
v___y_741_ = v___y_745_;
v___y_742_ = v___y_746_;
v___y_743_ = v___x_736_;
goto v___jp_740_;
}
else
{
v___y_741_ = v___y_745_;
v___y_742_ = v___y_746_;
v___y_743_ = v___y_745_;
goto v___jp_740_;
}
}
v___jp_751_:
{
if (v___y_752_ == 0)
{
uint32_t v___x_753_; uint32_t v___x_754_; uint32_t v___x_755_; uint8_t v___x_756_; 
v___x_753_ = 2147483648;
v___x_754_ = lean_uint32_land(v___y_192_, v___x_753_);
v___x_755_ = 0;
v___x_756_ = lean_uint32_dec_eq(v___x_754_, v___x_755_);
if (v___x_756_ == 0)
{
v___y_745_ = v___y_752_;
v___y_746_ = v___x_736_;
goto v___jp_744_;
}
else
{
v___y_745_ = v___y_752_;
v___y_746_ = v___y_752_;
goto v___jp_744_;
}
}
else
{
lean_object* v___x_757_; lean_object* v___x_758_; lean_object* v___x_759_; uint32_t v___x_760_; 
v___x_757_ = lean_uint32_to_nat(v___y_192_);
v___x_758_ = lean_uint32_to_nat(v___y_193_);
v___x_759_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_757_, v___x_758_);
v___x_760_ = lean_uint32_of_nat(v___x_759_);
lean_dec(v___x_759_);
return v___x_760_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___y_772_, lean_object* v___y_773_){
_start:
{
uint32_t v___y_5447__boxed_774_; uint32_t v___y_5448__boxed_775_; uint32_t v_res_776_; lean_object* v_r_777_; 
v___y_5447__boxed_774_ = lean_unbox_uint32(v___y_772_);
lean_dec(v___y_772_);
v___y_5448__boxed_775_ = lean_unbox_uint32(v___y_773_);
lean_dec(v___y_773_);
v_res_776_ = lp_competition_main___lam__1(v___y_5447__boxed_774_, v___y_5448__boxed_775_);
v_r_777_ = lean_box_uint32(v_res_776_);
return v_r_777_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint32_t v___y_778_, uint32_t v___y_779_){
_start:
{
uint32_t v___y_781_; uint32_t v___y_782_; uint32_t v___y_783_; uint32_t v___y_787_; uint32_t v___y_788_; uint32_t v___y_789_; uint32_t v___y_793_; uint64_t v___y_797_; uint8_t v___y_798_; uint32_t v___y_799_; uint64_t v___y_800_; uint32_t v___y_812_; uint64_t v___y_816_; uint8_t v___y_817_; uint32_t v___y_818_; uint64_t v___y_819_; uint8_t v___y_831_; uint8_t v___y_847_; uint8_t v___y_861_; uint8_t v___y_878_; float v___y_885_; float v___y_886_; float v___y_900_; uint8_t v___y_901_; float v___y_916_; uint8_t v___y_926_; uint8_t v___y_950_; uint32_t v___x_953_; uint32_t v___x_954_; uint32_t v___x_955_; uint32_t v___y_957_; uint32_t v___y_958_; uint32_t v___y_959_; uint32_t v___y_960_; uint32_t v___y_967_; uint8_t v___y_968_; uint32_t v___y_969_; uint32_t v___y_970_; uint64_t v___y_974_; uint64_t v___y_975_; uint8_t v___y_976_; uint32_t v___y_977_; uint64_t v___y_978_; uint64_t v___y_988_; uint64_t v___y_989_; uint8_t v___y_990_; uint8_t v___y_991_; uint32_t v___y_992_; uint64_t v___y_993_; uint64_t v___y_1000_; uint8_t v___y_1001_; uint32_t v___y_1002_; uint64_t v___y_1003_; uint64_t v___y_1004_; uint64_t v___y_1010_; uint64_t v___y_1011_; uint64_t v___y_1012_; uint8_t v___y_1013_; uint32_t v___y_1014_; uint64_t v___y_1015_; uint64_t v___y_1070_; uint64_t v___y_1071_; uint64_t v___y_1072_; uint64_t v___y_1073_; uint8_t v___y_1074_; uint32_t v___y_1075_; uint64_t v___y_1076_; uint64_t v___y_1082_; uint64_t v___y_1083_; uint64_t v___y_1084_; uint64_t v___y_1085_; uint64_t v___y_1086_; uint64_t v___y_1087_; uint8_t v___y_1088_; uint32_t v___y_1089_; uint64_t v___y_1090_; uint64_t v___y_1095_; uint64_t v___y_1096_; uint64_t v___y_1097_; uint64_t v___y_1098_; uint8_t v___y_1099_; uint32_t v___y_1100_; uint64_t v___y_1101_; uint64_t v___y_1106_; uint64_t v___y_1107_; uint64_t v___y_1108_; uint64_t v___y_1109_; uint64_t v___y_1110_; uint8_t v___y_1111_; uint64_t v___y_1112_; uint32_t v___y_1113_; uint64_t v___y_1114_; uint64_t v___y_1119_; uint64_t v___y_1120_; uint64_t v___y_1121_; uint64_t v___y_1122_; uint8_t v___y_1123_; uint32_t v___y_1124_; uint64_t v___y_1125_; uint64_t v___y_1130_; uint64_t v___y_1131_; uint64_t v___y_1132_; uint64_t v___y_1133_; uint64_t v___y_1134_; uint8_t v___y_1135_; uint64_t v___y_1136_; uint32_t v___y_1137_; uint64_t v___y_1138_; uint64_t v___y_1143_; uint64_t v___y_1144_; uint64_t v___y_1145_; uint64_t v___y_1146_; uint8_t v___y_1147_; uint32_t v___y_1148_; uint64_t v___y_1149_; uint64_t v___y_1154_; uint64_t v___y_1155_; uint64_t v___y_1156_; uint64_t v___y_1157_; uint64_t v___y_1158_; uint8_t v___y_1159_; uint32_t v___y_1160_; uint64_t v___y_1161_; uint64_t v___y_1162_; uint64_t v___y_1167_; uint64_t v___y_1168_; uint64_t v___y_1169_; uint64_t v___y_1170_; uint8_t v___y_1171_; uint32_t v___y_1172_; uint64_t v___y_1173_; uint64_t v___y_1178_; uint64_t v___y_1179_; uint64_t v___y_1180_; uint8_t v___y_1181_; uint32_t v___y_1182_; uint64_t v___y_1183_; uint64_t v___y_1184_; uint64_t v___y_1188_; uint64_t v___y_1189_; uint8_t v___y_1190_; uint32_t v___y_1191_; uint64_t v___y_1200_; uint64_t v___y_1201_; uint64_t v___y_1202_; uint8_t v___y_1203_; uint32_t v___y_1204_; uint64_t v___y_1205_; uint32_t v_ex_1238_; uint32_t v___x_1239_; uint32_t v_ey_1240_; uint8_t v___y_1248_; uint8_t v___y_1258_; uint8_t v___y_1271_; uint64_t v___y_1278_; uint64_t v___y_1279_; uint8_t v___y_1280_; uint32_t v___y_1281_; uint64_t v___y_1282_; uint64_t v___y_1289_; uint8_t v___y_1290_; uint32_t v___y_1291_; uint64_t v___y_1292_; uint8_t v___y_1299_; uint32_t v___y_1300_; uint32_t v___y_1301_; uint64_t v___y_1302_; uint8_t v___y_1310_; uint32_t v___x_1320_; uint32_t v___x_1321_; uint8_t v___x_1322_; uint8_t v___y_1324_; uint8_t v___y_1325_; uint8_t v___y_1327_; uint8_t v___y_1328_; uint8_t v___y_1329_; uint8_t v___y_1331_; uint8_t v___y_1332_; uint8_t v___y_1338_; 
v___x_953_ = 23;
v___x_954_ = lean_uint32_shift_right(v___y_778_, v___x_953_);
v___x_955_ = 255;
v_ex_1238_ = lean_uint32_land(v___x_954_, v___x_955_);
v___x_1239_ = lean_uint32_shift_right(v___y_779_, v___x_953_);
v_ey_1240_ = lean_uint32_land(v___x_1239_, v___x_955_);
v___x_1320_ = lean_uint32_add(v_ex_1238_, v_ey_1240_);
v___x_1321_ = 128;
v___x_1322_ = lean_uint32_dec_lt(v___x_1320_, v___x_1321_);
if (v___x_1322_ == 0)
{
uint8_t v___x_1347_; 
v___x_1347_ = lean_uint32_dec_eq(v_ex_1238_, v___x_955_);
if (v___x_1347_ == 0)
{
v___y_1271_ = v___x_1347_;
goto v___jp_1270_;
}
else
{
uint32_t v___x_1348_; uint32_t v___x_1349_; uint32_t v___x_1350_; uint8_t v___x_1351_; 
v___x_1348_ = 8388607;
v___x_1349_ = lean_uint32_land(v___y_778_, v___x_1348_);
v___x_1350_ = 0;
v___x_1351_ = lean_uint32_dec_eq(v___x_1349_, v___x_1350_);
if (v___x_1351_ == 0)
{
v___y_1271_ = v___x_1347_;
goto v___jp_1270_;
}
else
{
goto v___jp_1264_;
}
}
}
else
{
uint32_t v___x_1352_; uint32_t v___x_1353_; uint32_t v___x_1354_; uint8_t v___x_1355_; 
v___x_1352_ = 4278190080;
v___x_1353_ = 1;
v___x_1354_ = lean_uint32_shift_left(v___y_778_, v___x_1353_);
v___x_1355_ = lean_uint32_dec_le(v___x_1352_, v___x_1354_);
if (v___x_1355_ == 0)
{
uint32_t v___x_1356_; uint8_t v___x_1357_; 
v___x_1356_ = lean_uint32_shift_left(v___y_779_, v___x_1353_);
v___x_1357_ = lean_uint32_dec_le(v___x_1352_, v___x_1356_);
v___y_1338_ = v___x_1357_;
goto v___jp_1337_;
}
else
{
v___y_1338_ = v___x_1355_;
goto v___jp_1337_;
}
}
v___jp_780_:
{
uint32_t v___x_784_; uint32_t v___x_785_; 
v___x_784_ = lean_uint32_land(v___y_782_, v___y_781_);
v___x_785_ = lean_uint32_lor(v___y_783_, v___x_784_);
return v___x_785_;
}
v___jp_786_:
{
uint32_t v___x_790_; uint32_t v___x_791_; 
v___x_790_ = lean_uint32_land(v___y_787_, v___y_788_);
v___x_791_ = lean_uint32_lor(v___y_789_, v___x_790_);
return v___x_791_;
}
v___jp_792_:
{
uint32_t v___x_794_; uint32_t v___x_795_; 
v___x_794_ = 8388608;
v___x_795_ = lean_uint32_lor(v___y_793_, v___x_794_);
return v___x_795_;
}
v___jp_796_:
{
uint8_t v___x_801_; 
v___x_801_ = lean_uint64_dec_eq(v___y_800_, v___y_797_);
if (v___x_801_ == 0)
{
uint64_t v___x_802_; uint8_t v___x_803_; 
v___x_802_ = 8388608ULL;
v___x_803_ = lean_uint64_dec_eq(v___y_800_, v___x_802_);
if (v___x_803_ == 0)
{
uint32_t v___x_804_; 
v___x_804_ = lean_uint64_to_uint32(v___y_800_);
if (v___y_798_ == 0)
{
uint32_t v___x_805_; 
v___x_805_ = 0;
v___y_787_ = v___x_804_;
v___y_788_ = v___y_799_;
v___y_789_ = v___x_805_;
goto v___jp_786_;
}
else
{
uint32_t v___x_806_; 
v___x_806_ = 2147483648;
v___y_787_ = v___x_804_;
v___y_788_ = v___y_799_;
v___y_789_ = v___x_806_;
goto v___jp_786_;
}
}
else
{
if (v___y_798_ == 0)
{
uint32_t v___x_807_; 
v___x_807_ = 0;
v___y_793_ = v___x_807_;
goto v___jp_792_;
}
else
{
uint32_t v___x_808_; 
v___x_808_ = 2147483648;
v___y_793_ = v___x_808_;
goto v___jp_792_;
}
}
}
else
{
if (v___y_798_ == 0)
{
uint32_t v___x_809_; 
v___x_809_ = 0;
return v___x_809_;
}
else
{
uint32_t v___x_810_; 
v___x_810_ = 2147483648;
return v___x_810_;
}
}
}
v___jp_811_:
{
uint32_t v___x_813_; uint32_t v___x_814_; 
v___x_813_ = 8388608;
v___x_814_ = lean_uint32_lor(v___y_812_, v___x_813_);
return v___x_814_;
}
v___jp_815_:
{
uint8_t v___x_820_; 
v___x_820_ = lean_uint64_dec_eq(v___y_819_, v___y_816_);
if (v___x_820_ == 0)
{
uint64_t v___x_821_; uint8_t v___x_822_; 
v___x_821_ = 8388608ULL;
v___x_822_ = lean_uint64_dec_eq(v___y_819_, v___x_821_);
if (v___x_822_ == 0)
{
uint32_t v___x_823_; 
v___x_823_ = lean_uint64_to_uint32(v___y_819_);
if (v___y_817_ == 0)
{
uint32_t v___x_824_; 
v___x_824_ = 0;
v___y_781_ = v___y_818_;
v___y_782_ = v___x_823_;
v___y_783_ = v___x_824_;
goto v___jp_780_;
}
else
{
uint32_t v___x_825_; 
v___x_825_ = 2147483648;
v___y_781_ = v___y_818_;
v___y_782_ = v___x_823_;
v___y_783_ = v___x_825_;
goto v___jp_780_;
}
}
else
{
if (v___y_817_ == 0)
{
uint32_t v___x_826_; 
v___x_826_ = 0;
v___y_812_ = v___x_826_;
goto v___jp_811_;
}
else
{
uint32_t v___x_827_; 
v___x_827_ = 2147483648;
v___y_812_ = v___x_827_;
goto v___jp_811_;
}
}
}
else
{
if (v___y_817_ == 0)
{
uint32_t v___x_828_; 
v___x_828_ = 0;
return v___x_828_;
}
else
{
uint32_t v___x_829_; 
v___x_829_ = 2147483648;
return v___x_829_;
}
}
}
v___jp_830_:
{
if (v___y_831_ == 0)
{
uint32_t v___x_832_; 
v___x_832_ = lp_competition_Submission_FastMul_mul(v___y_778_, v___y_779_);
return v___x_832_;
}
else
{
uint32_t v___x_833_; uint32_t v___x_834_; 
v___x_833_ = 4194304;
v___x_834_ = lean_uint32_lor(v___y_779_, v___x_833_);
return v___x_834_;
}
}
v___jp_835_:
{
uint32_t v___x_836_; uint32_t v___x_837_; uint32_t v___x_838_; uint32_t v___x_839_; uint8_t v___x_840_; 
v___x_836_ = 23;
v___x_837_ = lean_uint32_shift_right(v___y_779_, v___x_836_);
v___x_838_ = 255;
v___x_839_ = lean_uint32_land(v___x_837_, v___x_838_);
v___x_840_ = lean_uint32_dec_eq(v___x_839_, v___x_838_);
if (v___x_840_ == 0)
{
v___y_831_ = v___x_840_;
goto v___jp_830_;
}
else
{
uint32_t v___x_841_; uint32_t v___x_842_; uint32_t v___x_843_; uint8_t v___x_844_; 
v___x_841_ = 8388607;
v___x_842_ = lean_uint32_land(v___y_779_, v___x_841_);
v___x_843_ = 0;
v___x_844_ = lean_uint32_dec_eq(v___x_842_, v___x_843_);
if (v___x_844_ == 0)
{
v___y_831_ = v___x_840_;
goto v___jp_830_;
}
else
{
uint32_t v___x_845_; 
v___x_845_ = lp_competition_Submission_FastMul_mul(v___y_778_, v___y_779_);
return v___x_845_;
}
}
}
v___jp_846_:
{
if (v___y_847_ == 0)
{
goto v___jp_835_;
}
else
{
uint32_t v___x_848_; uint32_t v___x_849_; 
v___x_848_ = 4194304;
v___x_849_ = lean_uint32_lor(v___y_778_, v___x_848_);
return v___x_849_;
}
}
v___jp_850_:
{
uint32_t v___x_851_; uint32_t v___x_852_; uint32_t v___x_853_; uint32_t v___x_854_; uint8_t v___x_855_; 
v___x_851_ = 23;
v___x_852_ = lean_uint32_shift_right(v___y_778_, v___x_851_);
v___x_853_ = 255;
v___x_854_ = lean_uint32_land(v___x_852_, v___x_853_);
v___x_855_ = lean_uint32_dec_eq(v___x_854_, v___x_853_);
if (v___x_855_ == 0)
{
v___y_847_ = v___x_855_;
goto v___jp_846_;
}
else
{
uint32_t v___x_856_; uint32_t v___x_857_; uint32_t v___x_858_; uint8_t v___x_859_; 
v___x_856_ = 8388607;
v___x_857_ = lean_uint32_land(v___y_778_, v___x_856_);
v___x_858_ = 0;
v___x_859_ = lean_uint32_dec_eq(v___x_857_, v___x_858_);
if (v___x_859_ == 0)
{
v___y_847_ = v___x_855_;
goto v___jp_846_;
}
else
{
goto v___jp_835_;
}
}
}
v___jp_860_:
{
if (v___y_861_ == 0)
{
goto v___jp_850_;
}
else
{
uint32_t v___x_862_; uint32_t v___x_863_; uint32_t v___x_864_; uint8_t v___x_865_; 
v___x_862_ = 4194304;
v___x_863_ = lean_uint32_land(v___y_779_, v___x_862_);
v___x_864_ = 0;
v___x_865_ = lean_uint32_dec_eq(v___x_863_, v___x_864_);
if (v___x_865_ == 0)
{
goto v___jp_850_;
}
else
{
uint32_t v___x_866_; 
v___x_866_ = lean_uint32_lor(v___y_779_, v___x_862_);
return v___x_866_;
}
}
}
v___jp_867_:
{
uint32_t v___x_868_; uint32_t v___x_869_; uint32_t v___x_870_; uint32_t v___x_871_; uint8_t v___x_872_; 
v___x_868_ = 23;
v___x_869_ = lean_uint32_shift_right(v___y_779_, v___x_868_);
v___x_870_ = 255;
v___x_871_ = lean_uint32_land(v___x_869_, v___x_870_);
v___x_872_ = lean_uint32_dec_eq(v___x_871_, v___x_870_);
if (v___x_872_ == 0)
{
v___y_861_ = v___x_872_;
goto v___jp_860_;
}
else
{
uint32_t v___x_873_; uint32_t v___x_874_; uint32_t v___x_875_; uint8_t v___x_876_; 
v___x_873_ = 8388607;
v___x_874_ = lean_uint32_land(v___y_779_, v___x_873_);
v___x_875_ = 0;
v___x_876_ = lean_uint32_dec_eq(v___x_874_, v___x_875_);
if (v___x_876_ == 0)
{
v___y_861_ = v___x_872_;
goto v___jp_860_;
}
else
{
goto v___jp_850_;
}
}
}
v___jp_877_:
{
if (v___y_878_ == 0)
{
goto v___jp_867_;
}
else
{
uint32_t v___x_879_; uint32_t v___x_880_; uint32_t v___x_881_; uint8_t v___x_882_; 
v___x_879_ = 4194304;
v___x_880_ = lean_uint32_land(v___y_778_, v___x_879_);
v___x_881_ = 0;
v___x_882_ = lean_uint32_dec_eq(v___x_880_, v___x_881_);
if (v___x_882_ == 0)
{
goto v___jp_867_;
}
else
{
uint32_t v___x_883_; 
v___x_883_ = lean_uint32_lor(v___y_778_, v___x_879_);
return v___x_883_;
}
}
}
v___jp_884_:
{
float v_result_887_; uint8_t v___x_888_; 
v_result_887_ = lean_float32_mul(v___y_885_, v___y_886_);
v___x_888_ = lean_float32_beq(v_result_887_, v_result_887_);
if (v___x_888_ == 0)
{
uint32_t v___x_889_; uint32_t v___x_890_; uint32_t v___x_891_; uint32_t v___x_892_; uint8_t v___x_893_; 
v___x_889_ = 23;
v___x_890_ = lean_uint32_shift_right(v___y_778_, v___x_889_);
v___x_891_ = 255;
v___x_892_ = lean_uint32_land(v___x_890_, v___x_891_);
v___x_893_ = lean_uint32_dec_eq(v___x_892_, v___x_891_);
if (v___x_893_ == 0)
{
v___y_878_ = v___x_893_;
goto v___jp_877_;
}
else
{
uint32_t v___x_894_; uint32_t v___x_895_; uint32_t v___x_896_; uint8_t v___x_897_; 
v___x_894_ = 8388607;
v___x_895_ = lean_uint32_land(v___y_778_, v___x_894_);
v___x_896_ = 0;
v___x_897_ = lean_uint32_dec_eq(v___x_895_, v___x_896_);
if (v___x_897_ == 0)
{
v___y_878_ = v___x_893_;
goto v___jp_877_;
}
else
{
goto v___jp_867_;
}
}
}
else
{
uint32_t v___x_898_; 
v___x_898_ = lean_float32_to_bits(v_result_887_);
return v___x_898_;
}
}
v___jp_899_:
{
if (v___y_901_ == 0)
{
float v___x_902_; 
v___x_902_ = lean_float32_of_bits(v___y_779_);
v___y_885_ = v___y_900_;
v___y_886_ = v___x_902_;
goto v___jp_884_;
}
else
{
uint32_t v___x_903_; uint32_t v___x_904_; uint32_t v___x_905_; uint32_t v___x_906_; float v___x_907_; lean_object* v___x_908_; uint32_t v___x_909_; uint32_t v___x_910_; lean_object* v___x_911_; lean_object* v___x_912_; float v___x_913_; float v___x_914_; 
v___x_903_ = 8388607;
v___x_904_ = lean_uint32_land(v___y_779_, v___x_903_);
v___x_905_ = 8388608;
v___x_906_ = lean_uint32_lor(v___x_904_, v___x_905_);
v___x_907_ = lean_uint32_to_float32(v___x_906_);
v___x_908_ = lp_competition_R2W01b_scaleTable;
v___x_909_ = 23;
v___x_910_ = lean_uint32_shift_right(v___y_779_, v___x_909_);
v___x_911_ = lean_uint32_to_nat(v___x_910_);
v___x_912_ = lean_array_fget_borrowed(v___x_908_, v___x_911_);
lean_dec(v___x_911_);
v___x_913_ = lean_unbox_float32(v___x_912_);
v___x_914_ = lean_float32_mul(v___x_907_, v___x_913_);
v___y_885_ = v___y_900_;
v___y_886_ = v___x_914_;
goto v___jp_884_;
}
}
v___jp_915_:
{
uint32_t v___x_917_; uint32_t v_a_918_; uint32_t v___x_919_; uint32_t v___x_920_; uint32_t v___x_921_; uint8_t v___x_922_; 
v___x_917_ = 2147483647;
v_a_918_ = lean_uint32_land(v___y_779_, v___x_917_);
v___x_919_ = 201326591;
v___x_920_ = 1;
v___x_921_ = lean_uint32_sub(v_a_918_, v___x_920_);
v___x_922_ = lean_uint32_dec_le(v___x_919_, v___x_921_);
if (v___x_922_ == 0)
{
v___y_900_ = v___y_916_;
v___y_901_ = v___x_922_;
goto v___jp_899_;
}
else
{
uint32_t v___x_923_; uint8_t v___x_924_; 
v___x_923_ = 2139095040;
v___x_924_ = lean_uint32_dec_lt(v_a_918_, v___x_923_);
v___y_900_ = v___y_916_;
v___y_901_ = v___x_924_;
goto v___jp_899_;
}
}
v___jp_925_:
{
if (v___y_926_ == 0)
{
float v___x_927_; 
v___x_927_ = lean_float32_of_bits(v___y_778_);
v___y_916_ = v___x_927_;
goto v___jp_915_;
}
else
{
uint32_t v___x_928_; uint32_t v___x_929_; uint32_t v___x_930_; uint32_t v___x_931_; float v___x_932_; lean_object* v___x_933_; uint32_t v___x_934_; uint32_t v___x_935_; lean_object* v___x_936_; lean_object* v___x_937_; float v___x_938_; float v___x_939_; 
v___x_928_ = 8388607;
v___x_929_ = lean_uint32_land(v___y_778_, v___x_928_);
v___x_930_ = 8388608;
v___x_931_ = lean_uint32_lor(v___x_929_, v___x_930_);
v___x_932_ = lean_uint32_to_float32(v___x_931_);
v___x_933_ = lp_competition_R2W01b_scaleTable;
v___x_934_ = 23;
v___x_935_ = lean_uint32_shift_right(v___y_778_, v___x_934_);
v___x_936_ = lean_uint32_to_nat(v___x_935_);
v___x_937_ = lean_array_fget_borrowed(v___x_933_, v___x_936_);
lean_dec(v___x_936_);
v___x_938_ = lean_unbox_float32(v___x_937_);
v___x_939_ = lean_float32_mul(v___x_932_, v___x_938_);
v___y_916_ = v___x_939_;
goto v___jp_915_;
}
}
v___jp_940_:
{
uint32_t v___x_941_; uint32_t v_a_942_; uint32_t v___x_943_; uint32_t v___x_944_; uint32_t v___x_945_; uint8_t v___x_946_; 
v___x_941_ = 2147483647;
v_a_942_ = lean_uint32_land(v___y_778_, v___x_941_);
v___x_943_ = 201326591;
v___x_944_ = 1;
v___x_945_ = lean_uint32_sub(v_a_942_, v___x_944_);
v___x_946_ = lean_uint32_dec_le(v___x_943_, v___x_945_);
if (v___x_946_ == 0)
{
v___y_926_ = v___x_946_;
goto v___jp_925_;
}
else
{
uint32_t v___x_947_; uint8_t v___x_948_; 
v___x_947_ = 2139095040;
v___x_948_ = lean_uint32_dec_lt(v_a_942_, v___x_947_);
v___y_926_ = v___x_948_;
goto v___jp_925_;
}
}
v___jp_949_:
{
if (v___y_950_ == 0)
{
goto v___jp_940_;
}
else
{
uint32_t v___x_951_; uint32_t v___x_952_; 
v___x_951_ = 4194304;
v___x_952_ = lean_uint32_lor(v___y_779_, v___x_951_);
return v___x_952_;
}
}
v___jp_956_:
{
uint32_t v___x_961_; uint32_t v___x_962_; uint32_t v___x_963_; uint32_t v___x_964_; uint32_t v___x_965_; 
v___x_961_ = lean_uint32_land(v___y_958_, v___x_955_);
v___x_962_ = lean_uint32_shift_left(v___x_961_, v___x_953_);
v___x_963_ = lean_uint32_lor(v___y_960_, v___x_962_);
v___x_964_ = lean_uint32_land(v___y_957_, v___y_959_);
v___x_965_ = lean_uint32_lor(v___x_963_, v___x_964_);
return v___x_965_;
}
v___jp_966_:
{
if (v___y_968_ == 0)
{
uint32_t v___x_971_; 
v___x_971_ = 0;
v___y_957_ = v___y_970_;
v___y_958_ = v___y_967_;
v___y_959_ = v___y_969_;
v___y_960_ = v___x_971_;
goto v___jp_956_;
}
else
{
uint32_t v___x_972_; 
v___x_972_ = 2147483648;
v___y_957_ = v___y_970_;
v___y_958_ = v___y_967_;
v___y_959_ = v___y_969_;
v___y_960_ = v___x_972_;
goto v___jp_956_;
}
}
v___jp_973_:
{
uint64_t v___x_979_; uint64_t v_encodedExponent_980_; uint32_t v___x_981_; uint64_t v___x_982_; uint8_t v___x_983_; 
v___x_979_ = 171ULL;
v_encodedExponent_980_ = lean_uint64_sub(v___y_975_, v___x_979_);
v___x_981_ = lean_uint64_to_uint32(v_encodedExponent_980_);
v___x_982_ = 8388608ULL;
v___x_983_ = lean_uint64_dec_lt(v___y_978_, v___x_982_);
if (v___x_983_ == 0)
{
uint64_t v___x_984_; uint32_t v___x_985_; 
v___x_984_ = lean_uint64_sub(v___y_978_, v___x_982_);
v___x_985_ = lean_uint64_to_uint32(v___x_984_);
v___y_967_ = v___x_981_;
v___y_968_ = v___y_976_;
v___y_969_ = v___y_977_;
v___y_970_ = v___x_985_;
goto v___jp_966_;
}
else
{
uint32_t v___x_986_; 
v___x_986_ = lean_uint64_to_uint32(v___y_974_);
v___y_967_ = v___x_981_;
v___y_968_ = v___y_976_;
v___y_969_ = v___y_977_;
v___y_970_ = v___x_986_;
goto v___jp_966_;
}
}
v___jp_987_:
{
uint64_t v___x_994_; uint8_t v___x_995_; 
v___x_994_ = 425ULL;
v___x_995_ = lean_uint64_dec_lt(v___x_994_, v___y_993_);
if (v___x_995_ == 0)
{
if (v___y_990_ == 0)
{
v___y_974_ = v___y_989_;
v___y_975_ = v___y_993_;
v___y_976_ = v___y_991_;
v___y_977_ = v___y_992_;
v___y_978_ = v___y_988_;
goto v___jp_973_;
}
else
{
uint64_t v___x_996_; 
v___x_996_ = 8388608ULL;
v___y_974_ = v___y_989_;
v___y_975_ = v___y_993_;
v___y_976_ = v___y_991_;
v___y_977_ = v___y_992_;
v___y_978_ = v___x_996_;
goto v___jp_973_;
}
}
else
{
if (v___y_991_ == 0)
{
uint32_t v___x_997_; 
v___x_997_ = 2139095040;
return v___x_997_;
}
else
{
uint32_t v___x_998_; 
v___x_998_ = 4286578688;
return v___x_998_;
}
}
}
v___jp_999_:
{
uint64_t v___x_1005_; uint8_t v_carry_1006_; 
v___x_1005_ = 16777216ULL;
v_carry_1006_ = lean_uint64_dec_eq(v___y_1004_, v___x_1005_);
if (v_carry_1006_ == 0)
{
v___y_988_ = v___y_1004_;
v___y_989_ = v___y_1000_;
v___y_990_ = v_carry_1006_;
v___y_991_ = v___y_1001_;
v___y_992_ = v___y_1002_;
v___y_993_ = v___y_1003_;
goto v___jp_987_;
}
else
{
uint64_t v___x_1007_; uint64_t v___x_1008_; 
v___x_1007_ = 1ULL;
v___x_1008_ = lean_uint64_add(v___y_1003_, v___x_1007_);
v___y_988_ = v___y_1004_;
v___y_989_ = v___y_1000_;
v___y_990_ = v_carry_1006_;
v___y_991_ = v___y_1001_;
v___y_992_ = v___y_1002_;
v___y_993_ = v___x_1008_;
goto v___jp_987_;
}
}
v___jp_1009_:
{
uint64_t v_position_1016_; uint64_t v___x_1017_; uint8_t v___x_1018_; 
v_position_1016_ = lean_uint64_add(v___y_1015_, v___y_1011_);
v___x_1017_ = 172ULL;
v___x_1018_ = lean_uint64_dec_lt(v_position_1016_, v___x_1017_);
if (v___x_1018_ == 0)
{
uint64_t v___x_1019_; uint8_t v___x_1020_; 
v___x_1019_ = 23ULL;
v___x_1020_ = lean_uint64_dec_lt(v___y_1015_, v___x_1019_);
if (v___x_1020_ == 0)
{
uint64_t v___x_1021_; uint8_t v___x_1022_; 
v___x_1021_ = lean_uint64_sub(v___y_1015_, v___x_1019_);
v___x_1022_ = lean_uint64_dec_eq(v___x_1021_, v___y_1012_);
if (v___x_1022_ == 0)
{
uint64_t v___x_1023_; uint8_t v___x_1024_; 
v___x_1023_ = 64ULL;
v___x_1024_ = lean_uint64_dec_lt(v___x_1021_, v___x_1023_);
if (v___x_1024_ == 0)
{
uint8_t v___x_1025_; 
v___x_1025_ = lean_uint64_dec_eq(v___x_1021_, v___x_1023_);
if (v___x_1025_ == 0)
{
v___y_1000_ = v___y_1012_;
v___y_1001_ = v___y_1013_;
v___y_1002_ = v___y_1014_;
v___y_1003_ = v_position_1016_;
v___y_1004_ = v___y_1012_;
goto v___jp_999_;
}
else
{
uint64_t v___x_1026_; uint8_t v___x_1027_; 
v___x_1026_ = 9223372036854775808ULL;
v___x_1027_ = lean_uint64_dec_lt(v___x_1026_, v___y_1010_);
if (v___x_1027_ == 0)
{
v___y_1000_ = v___y_1012_;
v___y_1001_ = v___y_1013_;
v___y_1002_ = v___y_1014_;
v___y_1003_ = v_position_1016_;
v___y_1004_ = v___y_1012_;
goto v___jp_999_;
}
else
{
uint64_t v___x_1028_; 
v___x_1028_ = 1ULL;
v___y_1000_ = v___y_1012_;
v___y_1001_ = v___y_1013_;
v___y_1002_ = v___y_1014_;
v___y_1003_ = v_position_1016_;
v___y_1004_ = v___x_1028_;
goto v___jp_999_;
}
}
}
else
{
uint64_t v_quotient_1029_; uint64_t v___x_1030_; uint64_t v___x_1031_; uint64_t v___x_1032_; uint64_t v_remainder_1033_; uint64_t v___x_1034_; uint64_t v_half_1035_; uint8_t v___x_1036_; 
v_quotient_1029_ = lean_uint64_shift_right(v___y_1010_, v___x_1021_);
v___x_1030_ = 1ULL;
v___x_1031_ = lean_uint64_shift_left(v___x_1030_, v___x_1021_);
v___x_1032_ = lean_uint64_sub(v___x_1031_, v___x_1030_);
v_remainder_1033_ = lean_uint64_land(v___y_1010_, v___x_1032_);
v___x_1034_ = lean_uint64_sub(v___x_1021_, v___x_1030_);
v_half_1035_ = lean_uint64_shift_left(v___x_1030_, v___x_1034_);
v___x_1036_ = lean_uint64_dec_lt(v_remainder_1033_, v_half_1035_);
if (v___x_1036_ == 0)
{
uint8_t v___x_1037_; 
v___x_1037_ = lean_uint64_dec_lt(v_half_1035_, v_remainder_1033_);
if (v___x_1037_ == 0)
{
uint64_t v___x_1038_; uint8_t v___x_1039_; 
v___x_1038_ = lean_uint64_land(v_quotient_1029_, v___x_1030_);
v___x_1039_ = lean_uint64_dec_eq(v___x_1038_, v___y_1012_);
if (v___x_1039_ == 0)
{
uint64_t v___x_1040_; 
v___x_1040_ = lean_uint64_add(v_quotient_1029_, v___x_1030_);
v___y_1000_ = v___y_1012_;
v___y_1001_ = v___y_1013_;
v___y_1002_ = v___y_1014_;
v___y_1003_ = v_position_1016_;
v___y_1004_ = v___x_1040_;
goto v___jp_999_;
}
else
{
v___y_1000_ = v___y_1012_;
v___y_1001_ = v___y_1013_;
v___y_1002_ = v___y_1014_;
v___y_1003_ = v_position_1016_;
v___y_1004_ = v_quotient_1029_;
goto v___jp_999_;
}
}
else
{
uint64_t v___x_1041_; 
v___x_1041_ = lean_uint64_add(v_quotient_1029_, v___x_1030_);
v___y_1000_ = v___y_1012_;
v___y_1001_ = v___y_1013_;
v___y_1002_ = v___y_1014_;
v___y_1003_ = v_position_1016_;
v___y_1004_ = v___x_1041_;
goto v___jp_999_;
}
}
else
{
v___y_1000_ = v___y_1012_;
v___y_1001_ = v___y_1013_;
v___y_1002_ = v___y_1014_;
v___y_1003_ = v_position_1016_;
v___y_1004_ = v_quotient_1029_;
goto v___jp_999_;
}
}
}
else
{
v___y_1000_ = v___y_1012_;
v___y_1001_ = v___y_1013_;
v___y_1002_ = v___y_1014_;
v___y_1003_ = v_position_1016_;
v___y_1004_ = v___y_1010_;
goto v___jp_999_;
}
}
else
{
uint64_t v___x_1042_; uint64_t v___x_1043_; 
v___x_1042_ = lean_uint64_sub(v___x_1019_, v___y_1015_);
v___x_1043_ = lean_uint64_shift_left(v___y_1010_, v___x_1042_);
v___y_1000_ = v___y_1012_;
v___y_1001_ = v___y_1013_;
v___y_1002_ = v___y_1014_;
v___y_1003_ = v_position_1016_;
v___y_1004_ = v___x_1043_;
goto v___jp_999_;
}
}
else
{
uint64_t v___x_1044_; uint8_t v___x_1045_; 
v___x_1044_ = 149ULL;
v___x_1045_ = lean_uint64_dec_lt(v___y_1011_, v___x_1044_);
if (v___x_1045_ == 0)
{
uint64_t v___x_1046_; uint64_t v___x_1047_; 
v___x_1046_ = lean_uint64_sub(v___y_1011_, v___x_1044_);
v___x_1047_ = lean_uint64_shift_left(v___y_1010_, v___x_1046_);
v___y_797_ = v___y_1012_;
v___y_798_ = v___y_1013_;
v___y_799_ = v___y_1014_;
v___y_800_ = v___x_1047_;
goto v___jp_796_;
}
else
{
uint64_t v___x_1048_; uint8_t v___x_1049_; 
v___x_1048_ = lean_uint64_sub(v___x_1044_, v___y_1011_);
v___x_1049_ = lean_uint64_dec_eq(v___x_1048_, v___y_1012_);
if (v___x_1049_ == 0)
{
uint64_t v___x_1050_; uint8_t v___x_1051_; 
v___x_1050_ = 64ULL;
v___x_1051_ = lean_uint64_dec_lt(v___x_1048_, v___x_1050_);
if (v___x_1051_ == 0)
{
uint8_t v___x_1052_; 
v___x_1052_ = lean_uint64_dec_eq(v___x_1048_, v___x_1050_);
if (v___x_1052_ == 0)
{
v___y_797_ = v___y_1012_;
v___y_798_ = v___y_1013_;
v___y_799_ = v___y_1014_;
v___y_800_ = v___y_1012_;
goto v___jp_796_;
}
else
{
uint64_t v___x_1053_; uint8_t v___x_1054_; 
v___x_1053_ = 9223372036854775808ULL;
v___x_1054_ = lean_uint64_dec_lt(v___x_1053_, v___y_1010_);
if (v___x_1054_ == 0)
{
v___y_797_ = v___y_1012_;
v___y_798_ = v___y_1013_;
v___y_799_ = v___y_1014_;
v___y_800_ = v___y_1012_;
goto v___jp_796_;
}
else
{
uint64_t v___x_1055_; 
v___x_1055_ = 1ULL;
v___y_797_ = v___y_1012_;
v___y_798_ = v___y_1013_;
v___y_799_ = v___y_1014_;
v___y_800_ = v___x_1055_;
goto v___jp_796_;
}
}
}
else
{
uint64_t v_quotient_1056_; uint64_t v___x_1057_; uint64_t v___x_1058_; uint64_t v___x_1059_; uint64_t v_remainder_1060_; uint64_t v___x_1061_; uint64_t v_half_1062_; uint8_t v___x_1063_; 
v_quotient_1056_ = lean_uint64_shift_right(v___y_1010_, v___x_1048_);
v___x_1057_ = 1ULL;
v___x_1058_ = lean_uint64_shift_left(v___x_1057_, v___x_1048_);
v___x_1059_ = lean_uint64_sub(v___x_1058_, v___x_1057_);
v_remainder_1060_ = lean_uint64_land(v___y_1010_, v___x_1059_);
v___x_1061_ = lean_uint64_sub(v___x_1048_, v___x_1057_);
v_half_1062_ = lean_uint64_shift_left(v___x_1057_, v___x_1061_);
v___x_1063_ = lean_uint64_dec_lt(v_remainder_1060_, v_half_1062_);
if (v___x_1063_ == 0)
{
uint8_t v___x_1064_; 
v___x_1064_ = lean_uint64_dec_lt(v_half_1062_, v_remainder_1060_);
if (v___x_1064_ == 0)
{
uint64_t v___x_1065_; uint8_t v___x_1066_; 
v___x_1065_ = lean_uint64_land(v_quotient_1056_, v___x_1057_);
v___x_1066_ = lean_uint64_dec_eq(v___x_1065_, v___y_1012_);
if (v___x_1066_ == 0)
{
uint64_t v___x_1067_; 
v___x_1067_ = lean_uint64_add(v_quotient_1056_, v___x_1057_);
v___y_797_ = v___y_1012_;
v___y_798_ = v___y_1013_;
v___y_799_ = v___y_1014_;
v___y_800_ = v___x_1067_;
goto v___jp_796_;
}
else
{
v___y_797_ = v___y_1012_;
v___y_798_ = v___y_1013_;
v___y_799_ = v___y_1014_;
v___y_800_ = v_quotient_1056_;
goto v___jp_796_;
}
}
else
{
uint64_t v___x_1068_; 
v___x_1068_ = lean_uint64_add(v_quotient_1056_, v___x_1057_);
v___y_797_ = v___y_1012_;
v___y_798_ = v___y_1013_;
v___y_799_ = v___y_1014_;
v___y_800_ = v___x_1068_;
goto v___jp_796_;
}
}
else
{
v___y_797_ = v___y_1012_;
v___y_798_ = v___y_1013_;
v___y_799_ = v___y_1014_;
v___y_800_ = v_quotient_1056_;
goto v___jp_796_;
}
}
}
else
{
v___y_797_ = v___y_1012_;
v___y_798_ = v___y_1013_;
v___y_799_ = v___y_1014_;
v___y_800_ = v___y_1010_;
goto v___jp_796_;
}
}
}
}
v___jp_1069_:
{
uint64_t v___x_1077_; uint64_t v___x_1078_; uint8_t v___x_1079_; 
v___x_1077_ = 1ULL;
v___x_1078_ = lean_uint64_shift_right(v___y_1073_, v___x_1077_);
v___x_1079_ = lean_uint64_dec_eq(v___x_1078_, v___y_1072_);
if (v___x_1079_ == 0)
{
uint64_t v___x_1080_; 
v___x_1080_ = lean_uint64_add(v___y_1076_, v___x_1077_);
v___y_1010_ = v___y_1070_;
v___y_1011_ = v___y_1071_;
v___y_1012_ = v___y_1072_;
v___y_1013_ = v___y_1074_;
v___y_1014_ = v___y_1075_;
v___y_1015_ = v___x_1080_;
goto v___jp_1009_;
}
else
{
v___y_1010_ = v___y_1070_;
v___y_1011_ = v___y_1071_;
v___y_1012_ = v___y_1072_;
v___y_1013_ = v___y_1074_;
v___y_1014_ = v___y_1075_;
v___y_1015_ = v___y_1076_;
goto v___jp_1009_;
}
}
v___jp_1081_:
{
uint64_t v___x_1091_; uint8_t v___x_1092_; 
v___x_1091_ = lean_uint64_shift_right(v___y_1084_, v___y_1087_);
v___x_1092_ = lean_uint64_dec_eq(v___x_1091_, v___y_1085_);
if (v___x_1092_ == 0)
{
uint64_t v___x_1093_; 
v___x_1093_ = lean_uint64_add(v___y_1086_, v___y_1087_);
v___y_1070_ = v___y_1082_;
v___y_1071_ = v___y_1083_;
v___y_1072_ = v___y_1085_;
v___y_1073_ = v___y_1090_;
v___y_1074_ = v___y_1088_;
v___y_1075_ = v___y_1089_;
v___y_1076_ = v___x_1093_;
goto v___jp_1069_;
}
else
{
v___y_1070_ = v___y_1082_;
v___y_1071_ = v___y_1083_;
v___y_1072_ = v___y_1085_;
v___y_1073_ = v___y_1090_;
v___y_1074_ = v___y_1088_;
v___y_1075_ = v___y_1089_;
v___y_1076_ = v___y_1086_;
goto v___jp_1069_;
}
}
v___jp_1094_:
{
uint64_t v___x_1102_; uint64_t v___x_1103_; uint8_t v___x_1104_; 
v___x_1102_ = 2ULL;
v___x_1103_ = lean_uint64_shift_right(v___y_1097_, v___x_1102_);
v___x_1104_ = lean_uint64_dec_eq(v___x_1103_, v___y_1098_);
if (v___x_1104_ == 0)
{
v___y_1082_ = v___y_1095_;
v___y_1083_ = v___y_1096_;
v___y_1084_ = v___y_1097_;
v___y_1085_ = v___y_1098_;
v___y_1086_ = v___y_1101_;
v___y_1087_ = v___x_1102_;
v___y_1088_ = v___y_1099_;
v___y_1089_ = v___y_1100_;
v___y_1090_ = v___x_1103_;
goto v___jp_1081_;
}
else
{
v___y_1082_ = v___y_1095_;
v___y_1083_ = v___y_1096_;
v___y_1084_ = v___y_1097_;
v___y_1085_ = v___y_1098_;
v___y_1086_ = v___y_1101_;
v___y_1087_ = v___x_1102_;
v___y_1088_ = v___y_1099_;
v___y_1089_ = v___y_1100_;
v___y_1090_ = v___y_1097_;
goto v___jp_1081_;
}
}
v___jp_1105_:
{
uint64_t v___x_1115_; uint8_t v___x_1116_; 
v___x_1115_ = lean_uint64_shift_right(v___y_1109_, v___y_1112_);
v___x_1116_ = lean_uint64_dec_eq(v___x_1115_, v___y_1108_);
if (v___x_1116_ == 0)
{
uint64_t v___x_1117_; 
v___x_1117_ = lean_uint64_add(v___y_1110_, v___y_1112_);
v___y_1095_ = v___y_1106_;
v___y_1096_ = v___y_1107_;
v___y_1097_ = v___y_1114_;
v___y_1098_ = v___y_1108_;
v___y_1099_ = v___y_1111_;
v___y_1100_ = v___y_1113_;
v___y_1101_ = v___x_1117_;
goto v___jp_1094_;
}
else
{
v___y_1095_ = v___y_1106_;
v___y_1096_ = v___y_1107_;
v___y_1097_ = v___y_1114_;
v___y_1098_ = v___y_1108_;
v___y_1099_ = v___y_1111_;
v___y_1100_ = v___y_1113_;
v___y_1101_ = v___y_1110_;
goto v___jp_1094_;
}
}
v___jp_1118_:
{
uint64_t v___x_1126_; uint64_t v___x_1127_; uint8_t v___x_1128_; 
v___x_1126_ = 4ULL;
v___x_1127_ = lean_uint64_shift_right(v___y_1122_, v___x_1126_);
v___x_1128_ = lean_uint64_dec_eq(v___x_1127_, v___y_1121_);
if (v___x_1128_ == 0)
{
v___y_1106_ = v___y_1119_;
v___y_1107_ = v___y_1120_;
v___y_1108_ = v___y_1121_;
v___y_1109_ = v___y_1122_;
v___y_1110_ = v___y_1125_;
v___y_1111_ = v___y_1123_;
v___y_1112_ = v___x_1126_;
v___y_1113_ = v___y_1124_;
v___y_1114_ = v___x_1127_;
goto v___jp_1105_;
}
else
{
v___y_1106_ = v___y_1119_;
v___y_1107_ = v___y_1120_;
v___y_1108_ = v___y_1121_;
v___y_1109_ = v___y_1122_;
v___y_1110_ = v___y_1125_;
v___y_1111_ = v___y_1123_;
v___y_1112_ = v___x_1126_;
v___y_1113_ = v___y_1124_;
v___y_1114_ = v___y_1122_;
goto v___jp_1105_;
}
}
v___jp_1129_:
{
uint64_t v___x_1139_; uint8_t v___x_1140_; 
v___x_1139_ = lean_uint64_shift_right(v___y_1133_, v___y_1130_);
v___x_1140_ = lean_uint64_dec_eq(v___x_1139_, v___y_1134_);
if (v___x_1140_ == 0)
{
uint64_t v___x_1141_; 
v___x_1141_ = lean_uint64_add(v___y_1136_, v___y_1130_);
v___y_1119_ = v___y_1131_;
v___y_1120_ = v___y_1132_;
v___y_1121_ = v___y_1134_;
v___y_1122_ = v___y_1138_;
v___y_1123_ = v___y_1135_;
v___y_1124_ = v___y_1137_;
v___y_1125_ = v___x_1141_;
goto v___jp_1118_;
}
else
{
v___y_1119_ = v___y_1131_;
v___y_1120_ = v___y_1132_;
v___y_1121_ = v___y_1134_;
v___y_1122_ = v___y_1138_;
v___y_1123_ = v___y_1135_;
v___y_1124_ = v___y_1137_;
v___y_1125_ = v___y_1136_;
goto v___jp_1118_;
}
}
v___jp_1142_:
{
uint64_t v___x_1150_; uint64_t v___x_1151_; uint8_t v___x_1152_; 
v___x_1150_ = 8ULL;
v___x_1151_ = lean_uint64_shift_right(v___y_1145_, v___x_1150_);
v___x_1152_ = lean_uint64_dec_eq(v___x_1151_, v___y_1146_);
if (v___x_1152_ == 0)
{
v___y_1130_ = v___x_1150_;
v___y_1131_ = v___y_1143_;
v___y_1132_ = v___y_1144_;
v___y_1133_ = v___y_1145_;
v___y_1134_ = v___y_1146_;
v___y_1135_ = v___y_1147_;
v___y_1136_ = v___y_1149_;
v___y_1137_ = v___y_1148_;
v___y_1138_ = v___x_1151_;
goto v___jp_1129_;
}
else
{
v___y_1130_ = v___x_1150_;
v___y_1131_ = v___y_1143_;
v___y_1132_ = v___y_1144_;
v___y_1133_ = v___y_1145_;
v___y_1134_ = v___y_1146_;
v___y_1135_ = v___y_1147_;
v___y_1136_ = v___y_1149_;
v___y_1137_ = v___y_1148_;
v___y_1138_ = v___y_1145_;
goto v___jp_1129_;
}
}
v___jp_1153_:
{
uint64_t v___x_1163_; uint8_t v___x_1164_; 
v___x_1163_ = lean_uint64_shift_right(v___y_1156_, v___y_1154_);
v___x_1164_ = lean_uint64_dec_eq(v___x_1163_, v___y_1158_);
if (v___x_1164_ == 0)
{
uint64_t v___x_1165_; 
v___x_1165_ = lean_uint64_add(v___y_1161_, v___y_1154_);
v___y_1143_ = v___y_1155_;
v___y_1144_ = v___y_1157_;
v___y_1145_ = v___y_1162_;
v___y_1146_ = v___y_1158_;
v___y_1147_ = v___y_1159_;
v___y_1148_ = v___y_1160_;
v___y_1149_ = v___x_1165_;
goto v___jp_1142_;
}
else
{
v___y_1143_ = v___y_1155_;
v___y_1144_ = v___y_1157_;
v___y_1145_ = v___y_1162_;
v___y_1146_ = v___y_1158_;
v___y_1147_ = v___y_1159_;
v___y_1148_ = v___y_1160_;
v___y_1149_ = v___y_1161_;
goto v___jp_1142_;
}
}
v___jp_1166_:
{
uint64_t v___x_1174_; uint64_t v___x_1175_; uint8_t v___x_1176_; 
v___x_1174_ = 16ULL;
v___x_1175_ = lean_uint64_shift_right(v___y_1169_, v___x_1174_);
v___x_1176_ = lean_uint64_dec_eq(v___x_1175_, v___y_1170_);
if (v___x_1176_ == 0)
{
v___y_1154_ = v___x_1174_;
v___y_1155_ = v___y_1167_;
v___y_1156_ = v___y_1169_;
v___y_1157_ = v___y_1168_;
v___y_1158_ = v___y_1170_;
v___y_1159_ = v___y_1171_;
v___y_1160_ = v___y_1172_;
v___y_1161_ = v___y_1173_;
v___y_1162_ = v___x_1175_;
goto v___jp_1153_;
}
else
{
v___y_1154_ = v___x_1174_;
v___y_1155_ = v___y_1167_;
v___y_1156_ = v___y_1169_;
v___y_1157_ = v___y_1168_;
v___y_1158_ = v___y_1170_;
v___y_1159_ = v___y_1171_;
v___y_1160_ = v___y_1172_;
v___y_1161_ = v___y_1173_;
v___y_1162_ = v___y_1169_;
goto v___jp_1153_;
}
}
v___jp_1177_:
{
uint64_t v___x_1185_; uint8_t v___x_1186_; 
v___x_1185_ = lean_uint64_shift_right(v___y_1178_, v___y_1183_);
v___x_1186_ = lean_uint64_dec_eq(v___x_1185_, v___y_1180_);
if (v___x_1186_ == 0)
{
v___y_1167_ = v___y_1178_;
v___y_1168_ = v___y_1179_;
v___y_1169_ = v___y_1184_;
v___y_1170_ = v___y_1180_;
v___y_1171_ = v___y_1181_;
v___y_1172_ = v___y_1182_;
v___y_1173_ = v___y_1183_;
goto v___jp_1166_;
}
else
{
v___y_1167_ = v___y_1178_;
v___y_1168_ = v___y_1179_;
v___y_1169_ = v___y_1184_;
v___y_1170_ = v___y_1180_;
v___y_1171_ = v___y_1181_;
v___y_1172_ = v___y_1182_;
v___y_1173_ = v___y_1180_;
goto v___jp_1166_;
}
}
v___jp_1187_:
{
uint64_t v___x_1192_; uint8_t v___x_1193_; 
v___x_1192_ = 0ULL;
v___x_1193_ = lean_uint64_dec_eq(v___y_1188_, v___x_1192_);
if (v___x_1193_ == 0)
{
uint64_t v___x_1194_; uint64_t v___x_1195_; uint8_t v___x_1196_; 
v___x_1194_ = 32ULL;
v___x_1195_ = lean_uint64_shift_right(v___y_1188_, v___x_1194_);
v___x_1196_ = lean_uint64_dec_eq(v___x_1195_, v___x_1192_);
if (v___x_1196_ == 0)
{
v___y_1178_ = v___y_1188_;
v___y_1179_ = v___y_1189_;
v___y_1180_ = v___x_1192_;
v___y_1181_ = v___y_1190_;
v___y_1182_ = v___y_1191_;
v___y_1183_ = v___x_1194_;
v___y_1184_ = v___x_1195_;
goto v___jp_1177_;
}
else
{
v___y_1178_ = v___y_1188_;
v___y_1179_ = v___y_1189_;
v___y_1180_ = v___x_1192_;
v___y_1181_ = v___y_1190_;
v___y_1182_ = v___y_1191_;
v___y_1183_ = v___x_1194_;
v___y_1184_ = v___y_1188_;
goto v___jp_1177_;
}
}
else
{
if (v___y_1190_ == 0)
{
uint32_t v___x_1197_; 
v___x_1197_ = 0;
return v___x_1197_;
}
else
{
uint32_t v___x_1198_; 
v___x_1198_ = 2147483648;
return v___x_1198_;
}
}
}
v___jp_1199_:
{
uint64_t v___x_1206_; uint64_t v___x_1207_; uint64_t v___x_1208_; uint8_t v___x_1209_; 
v___x_1206_ = lean_uint64_mul(v___y_1201_, v___y_1200_);
v___x_1207_ = lean_uint64_add(v___y_1202_, v___y_1205_);
v___x_1208_ = 281474976710656ULL;
v___x_1209_ = lean_uint64_dec_lt(v___x_1206_, v___x_1208_);
if (v___x_1209_ == 0)
{
v___y_1188_ = v___x_1206_;
v___y_1189_ = v___x_1207_;
v___y_1190_ = v___y_1203_;
v___y_1191_ = v___y_1204_;
goto v___jp_1187_;
}
else
{
uint64_t v___x_1210_; uint8_t v___x_1211_; 
v___x_1210_ = 123ULL;
v___x_1211_ = lean_uint64_dec_le(v___x_1207_, v___x_1210_);
if (v___x_1211_ == 0)
{
v___y_1188_ = v___x_1206_;
v___y_1189_ = v___x_1207_;
v___y_1190_ = v___y_1203_;
v___y_1191_ = v___y_1204_;
goto v___jp_1187_;
}
else
{
uint64_t v___x_1212_; uint8_t v___x_1213_; 
v___x_1212_ = 0ULL;
v___x_1213_ = lean_uint64_dec_eq(v___x_1206_, v___x_1212_);
if (v___x_1213_ == 0)
{
uint64_t v___x_1214_; uint64_t v___x_1215_; uint8_t v___x_1216_; 
v___x_1214_ = 149ULL;
v___x_1215_ = lean_uint64_sub(v___x_1214_, v___x_1207_);
v___x_1216_ = lean_uint64_dec_eq(v___x_1215_, v___x_1212_);
if (v___x_1216_ == 0)
{
uint64_t v___x_1217_; uint8_t v___x_1218_; 
v___x_1217_ = 64ULL;
v___x_1218_ = lean_uint64_dec_lt(v___x_1215_, v___x_1217_);
if (v___x_1218_ == 0)
{
uint8_t v___x_1219_; 
v___x_1219_ = lean_uint64_dec_eq(v___x_1215_, v___x_1217_);
if (v___x_1219_ == 0)
{
v___y_816_ = v___x_1212_;
v___y_817_ = v___y_1203_;
v___y_818_ = v___y_1204_;
v___y_819_ = v___x_1212_;
goto v___jp_815_;
}
else
{
uint64_t v___x_1220_; uint8_t v___x_1221_; 
v___x_1220_ = 9223372036854775808ULL;
v___x_1221_ = lean_uint64_dec_lt(v___x_1220_, v___x_1206_);
if (v___x_1221_ == 0)
{
v___y_816_ = v___x_1212_;
v___y_817_ = v___y_1203_;
v___y_818_ = v___y_1204_;
v___y_819_ = v___x_1212_;
goto v___jp_815_;
}
else
{
uint64_t v___x_1222_; 
v___x_1222_ = 1ULL;
v___y_816_ = v___x_1212_;
v___y_817_ = v___y_1203_;
v___y_818_ = v___y_1204_;
v___y_819_ = v___x_1222_;
goto v___jp_815_;
}
}
}
else
{
uint64_t v_quotient_1223_; uint64_t v___x_1224_; uint64_t v___x_1225_; uint64_t v___x_1226_; uint64_t v_remainder_1227_; uint64_t v___x_1228_; uint64_t v_half_1229_; uint8_t v___x_1230_; 
v_quotient_1223_ = lean_uint64_shift_right(v___x_1206_, v___x_1215_);
v___x_1224_ = 1ULL;
v___x_1225_ = lean_uint64_shift_left(v___x_1224_, v___x_1215_);
v___x_1226_ = lean_uint64_sub(v___x_1225_, v___x_1224_);
v_remainder_1227_ = lean_uint64_land(v___x_1206_, v___x_1226_);
v___x_1228_ = lean_uint64_sub(v___x_1215_, v___x_1224_);
v_half_1229_ = lean_uint64_shift_left(v___x_1224_, v___x_1228_);
v___x_1230_ = lean_uint64_dec_lt(v_remainder_1227_, v_half_1229_);
if (v___x_1230_ == 0)
{
uint8_t v___x_1231_; 
v___x_1231_ = lean_uint64_dec_lt(v_half_1229_, v_remainder_1227_);
if (v___x_1231_ == 0)
{
uint64_t v___x_1232_; uint8_t v___x_1233_; 
v___x_1232_ = lean_uint64_land(v_quotient_1223_, v___x_1224_);
v___x_1233_ = lean_uint64_dec_eq(v___x_1232_, v___x_1212_);
if (v___x_1233_ == 0)
{
uint64_t v___x_1234_; 
v___x_1234_ = lean_uint64_add(v_quotient_1223_, v___x_1224_);
v___y_816_ = v___x_1212_;
v___y_817_ = v___y_1203_;
v___y_818_ = v___y_1204_;
v___y_819_ = v___x_1234_;
goto v___jp_815_;
}
else
{
v___y_816_ = v___x_1212_;
v___y_817_ = v___y_1203_;
v___y_818_ = v___y_1204_;
v___y_819_ = v_quotient_1223_;
goto v___jp_815_;
}
}
else
{
uint64_t v___x_1235_; 
v___x_1235_ = lean_uint64_add(v_quotient_1223_, v___x_1224_);
v___y_816_ = v___x_1212_;
v___y_817_ = v___y_1203_;
v___y_818_ = v___y_1204_;
v___y_819_ = v___x_1235_;
goto v___jp_815_;
}
}
else
{
v___y_816_ = v___x_1212_;
v___y_817_ = v___y_1203_;
v___y_818_ = v___y_1204_;
v___y_819_ = v_quotient_1223_;
goto v___jp_815_;
}
}
}
else
{
v___y_816_ = v___x_1212_;
v___y_817_ = v___y_1203_;
v___y_818_ = v___y_1204_;
v___y_819_ = v___x_1206_;
goto v___jp_815_;
}
}
else
{
if (v___y_1203_ == 0)
{
uint32_t v___x_1236_; 
v___x_1236_ = 0;
return v___x_1236_;
}
else
{
uint32_t v___x_1237_; 
v___x_1237_ = 2147483648;
return v___x_1237_;
}
}
}
}
}
v___jp_1241_:
{
uint8_t v___x_1242_; 
v___x_1242_ = lean_uint32_dec_eq(v_ey_1240_, v___x_955_);
if (v___x_1242_ == 0)
{
v___y_950_ = v___x_1242_;
goto v___jp_949_;
}
else
{
uint32_t v___x_1243_; uint32_t v___x_1244_; uint32_t v___x_1245_; uint8_t v___x_1246_; 
v___x_1243_ = 8388607;
v___x_1244_ = lean_uint32_land(v___y_779_, v___x_1243_);
v___x_1245_ = 0;
v___x_1246_ = lean_uint32_dec_eq(v___x_1244_, v___x_1245_);
if (v___x_1246_ == 0)
{
v___y_950_ = v___x_1242_;
goto v___jp_949_;
}
else
{
goto v___jp_940_;
}
}
}
v___jp_1247_:
{
if (v___y_1248_ == 0)
{
goto v___jp_1241_;
}
else
{
uint32_t v___x_1249_; uint32_t v___x_1250_; 
v___x_1249_ = 4194304;
v___x_1250_ = lean_uint32_lor(v___y_778_, v___x_1249_);
return v___x_1250_;
}
}
v___jp_1251_:
{
uint8_t v___x_1252_; 
v___x_1252_ = lean_uint32_dec_eq(v_ex_1238_, v___x_955_);
if (v___x_1252_ == 0)
{
v___y_1248_ = v___x_1252_;
goto v___jp_1247_;
}
else
{
uint32_t v___x_1253_; uint32_t v___x_1254_; uint32_t v___x_1255_; uint8_t v___x_1256_; 
v___x_1253_ = 8388607;
v___x_1254_ = lean_uint32_land(v___y_778_, v___x_1253_);
v___x_1255_ = 0;
v___x_1256_ = lean_uint32_dec_eq(v___x_1254_, v___x_1255_);
if (v___x_1256_ == 0)
{
v___y_1248_ = v___x_1252_;
goto v___jp_1247_;
}
else
{
goto v___jp_1241_;
}
}
}
v___jp_1257_:
{
if (v___y_1258_ == 0)
{
goto v___jp_1251_;
}
else
{
uint32_t v___x_1259_; uint32_t v___x_1260_; uint32_t v___x_1261_; uint8_t v___x_1262_; 
v___x_1259_ = 4194304;
v___x_1260_ = lean_uint32_land(v___y_779_, v___x_1259_);
v___x_1261_ = 0;
v___x_1262_ = lean_uint32_dec_eq(v___x_1260_, v___x_1261_);
if (v___x_1262_ == 0)
{
goto v___jp_1251_;
}
else
{
uint32_t v___x_1263_; 
v___x_1263_ = lean_uint32_lor(v___y_779_, v___x_1259_);
return v___x_1263_;
}
}
}
v___jp_1264_:
{
uint8_t v___x_1265_; 
v___x_1265_ = lean_uint32_dec_eq(v_ey_1240_, v___x_955_);
if (v___x_1265_ == 0)
{
v___y_1258_ = v___x_1265_;
goto v___jp_1257_;
}
else
{
uint32_t v___x_1266_; uint32_t v___x_1267_; uint32_t v___x_1268_; uint8_t v___x_1269_; 
v___x_1266_ = 8388607;
v___x_1267_ = lean_uint32_land(v___y_779_, v___x_1266_);
v___x_1268_ = 0;
v___x_1269_ = lean_uint32_dec_eq(v___x_1267_, v___x_1268_);
if (v___x_1269_ == 0)
{
v___y_1258_ = v___x_1265_;
goto v___jp_1257_;
}
else
{
goto v___jp_1251_;
}
}
}
v___jp_1270_:
{
if (v___y_1271_ == 0)
{
goto v___jp_1264_;
}
else
{
uint32_t v___x_1272_; uint32_t v___x_1273_; uint32_t v___x_1274_; uint8_t v___x_1275_; 
v___x_1272_ = 4194304;
v___x_1273_ = lean_uint32_land(v___y_778_, v___x_1272_);
v___x_1274_ = 0;
v___x_1275_ = lean_uint32_dec_eq(v___x_1273_, v___x_1274_);
if (v___x_1275_ == 0)
{
goto v___jp_1264_;
}
else
{
uint32_t v___x_1276_; 
v___x_1276_ = lean_uint32_lor(v___y_778_, v___x_1272_);
return v___x_1276_;
}
}
}
v___jp_1277_:
{
uint64_t v___x_1283_; uint64_t v___x_1284_; uint8_t v___x_1285_; 
v___x_1283_ = lean_uint32_to_uint64(v_ey_1240_);
v___x_1284_ = 0ULL;
v___x_1285_ = lean_uint64_dec_eq(v___x_1283_, v___x_1284_);
if (v___x_1285_ == 0)
{
uint64_t v___x_1286_; uint64_t v___x_1287_; 
v___x_1286_ = 1ULL;
v___x_1287_ = lean_uint64_sub(v___x_1283_, v___x_1286_);
v___y_1200_ = v___y_1278_;
v___y_1201_ = v___y_1279_;
v___y_1202_ = v___y_1282_;
v___y_1203_ = v___y_1280_;
v___y_1204_ = v___y_1281_;
v___y_1205_ = v___x_1287_;
goto v___jp_1199_;
}
else
{
v___y_1200_ = v___y_1278_;
v___y_1201_ = v___y_1279_;
v___y_1202_ = v___y_1282_;
v___y_1203_ = v___y_1280_;
v___y_1204_ = v___y_1281_;
v___y_1205_ = v___x_1284_;
goto v___jp_1199_;
}
}
v___jp_1288_:
{
uint64_t v___x_1293_; uint64_t v___x_1294_; uint8_t v___x_1295_; 
v___x_1293_ = lean_uint32_to_uint64(v_ex_1238_);
v___x_1294_ = 0ULL;
v___x_1295_ = lean_uint64_dec_eq(v___x_1293_, v___x_1294_);
if (v___x_1295_ == 0)
{
uint64_t v___x_1296_; uint64_t v___x_1297_; 
v___x_1296_ = 1ULL;
v___x_1297_ = lean_uint64_sub(v___x_1293_, v___x_1296_);
v___y_1278_ = v___y_1292_;
v___y_1279_ = v___y_1289_;
v___y_1280_ = v___y_1290_;
v___y_1281_ = v___y_1291_;
v___y_1282_ = v___x_1297_;
goto v___jp_1277_;
}
else
{
v___y_1278_ = v___y_1292_;
v___y_1279_ = v___y_1289_;
v___y_1280_ = v___y_1290_;
v___y_1281_ = v___y_1291_;
v___y_1282_ = v___x_1294_;
goto v___jp_1277_;
}
}
v___jp_1298_:
{
uint32_t v___x_1303_; uint8_t v___x_1304_; 
v___x_1303_ = 0;
v___x_1304_ = lean_uint32_dec_eq(v_ey_1240_, v___x_1303_);
if (v___x_1304_ == 0)
{
uint64_t v___x_1305_; uint64_t v___x_1306_; uint64_t v___x_1307_; 
v___x_1305_ = lean_uint32_to_uint64(v___y_1300_);
v___x_1306_ = 8388608ULL;
v___x_1307_ = lean_uint64_lor(v___x_1305_, v___x_1306_);
v___y_1289_ = v___y_1302_;
v___y_1290_ = v___y_1299_;
v___y_1291_ = v___y_1301_;
v___y_1292_ = v___x_1307_;
goto v___jp_1288_;
}
else
{
uint64_t v___x_1308_; 
v___x_1308_ = lean_uint32_to_uint64(v___y_1300_);
v___y_1289_ = v___y_1302_;
v___y_1290_ = v___y_1299_;
v___y_1291_ = v___y_1301_;
v___y_1292_ = v___x_1308_;
goto v___jp_1288_;
}
}
v___jp_1309_:
{
uint32_t v___x_1311_; uint32_t v_xFraction_1312_; uint32_t v_yFraction_1313_; uint32_t v___x_1314_; uint8_t v___x_1315_; 
v___x_1311_ = 8388607;
v_xFraction_1312_ = lean_uint32_land(v___y_778_, v___x_1311_);
v_yFraction_1313_ = lean_uint32_land(v___y_779_, v___x_1311_);
v___x_1314_ = 0;
v___x_1315_ = lean_uint32_dec_eq(v_ex_1238_, v___x_1314_);
if (v___x_1315_ == 0)
{
uint64_t v___x_1316_; uint64_t v___x_1317_; uint64_t v___x_1318_; 
v___x_1316_ = lean_uint32_to_uint64(v_xFraction_1312_);
v___x_1317_ = 8388608ULL;
v___x_1318_ = lean_uint64_lor(v___x_1316_, v___x_1317_);
v___y_1299_ = v___y_1310_;
v___y_1300_ = v_yFraction_1313_;
v___y_1301_ = v___x_1311_;
v___y_1302_ = v___x_1318_;
goto v___jp_1298_;
}
else
{
uint64_t v___x_1319_; 
v___x_1319_ = lean_uint32_to_uint64(v_xFraction_1312_);
v___y_1299_ = v___y_1310_;
v___y_1300_ = v_yFraction_1313_;
v___y_1301_ = v___x_1311_;
v___y_1302_ = v___x_1319_;
goto v___jp_1298_;
}
}
v___jp_1323_:
{
if (v___y_1325_ == 0)
{
v___y_1310_ = v___x_1322_;
goto v___jp_1309_;
}
else
{
v___y_1310_ = v___y_1324_;
goto v___jp_1309_;
}
}
v___jp_1326_:
{
if (v___y_1328_ == 0)
{
if (v___y_1329_ == 0)
{
v___y_1324_ = v___y_1327_;
v___y_1325_ = v___x_1322_;
goto v___jp_1323_;
}
else
{
v___y_1310_ = v___x_1322_;
goto v___jp_1309_;
}
}
else
{
v___y_1324_ = v___y_1327_;
v___y_1325_ = v___y_1329_;
goto v___jp_1323_;
}
}
v___jp_1330_:
{
uint32_t v___x_1333_; uint32_t v___x_1334_; uint32_t v___x_1335_; uint8_t v___x_1336_; 
v___x_1333_ = 2147483648;
v___x_1334_ = lean_uint32_land(v___y_779_, v___x_1333_);
v___x_1335_ = 0;
v___x_1336_ = lean_uint32_dec_eq(v___x_1334_, v___x_1335_);
if (v___x_1336_ == 0)
{
v___y_1327_ = v___y_1331_;
v___y_1328_ = v___y_1332_;
v___y_1329_ = v___x_1322_;
goto v___jp_1326_;
}
else
{
v___y_1327_ = v___y_1331_;
v___y_1328_ = v___y_1332_;
v___y_1329_ = v___y_1331_;
goto v___jp_1326_;
}
}
v___jp_1337_:
{
if (v___y_1338_ == 0)
{
uint32_t v___x_1339_; uint32_t v___x_1340_; uint32_t v___x_1341_; uint8_t v___x_1342_; 
v___x_1339_ = 2147483648;
v___x_1340_ = lean_uint32_land(v___y_778_, v___x_1339_);
v___x_1341_ = 0;
v___x_1342_ = lean_uint32_dec_eq(v___x_1340_, v___x_1341_);
if (v___x_1342_ == 0)
{
v___y_1331_ = v___y_1338_;
v___y_1332_ = v___x_1322_;
goto v___jp_1330_;
}
else
{
v___y_1331_ = v___y_1338_;
v___y_1332_ = v___y_1338_;
goto v___jp_1330_;
}
}
else
{
lean_object* v___x_1343_; lean_object* v___x_1344_; lean_object* v___x_1345_; uint32_t v___x_1346_; 
v___x_1343_ = lean_uint32_to_nat(v___y_778_);
v___x_1344_ = lean_uint32_to_nat(v___y_779_);
v___x_1345_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1343_, v___x_1344_);
v___x_1346_ = lean_uint32_of_nat(v___x_1345_);
lean_dec(v___x_1345_);
return v___x_1346_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object* v___y_1358_, lean_object* v___y_1359_){
_start:
{
uint32_t v___y_6571__boxed_1360_; uint32_t v___y_6572__boxed_1361_; uint32_t v_res_1362_; lean_object* v_r_1363_; 
v___y_6571__boxed_1360_ = lean_unbox_uint32(v___y_1358_);
lean_dec(v___y_1358_);
v___y_6572__boxed_1361_ = lean_unbox_uint32(v___y_1359_);
lean_dec(v___y_1359_);
v_res_1362_ = lp_competition_main___lam__3(v___y_6571__boxed_1360_, v___y_6572__boxed_1361_);
v_r_1363_ = lean_box_uint32(v_res_1362_);
return v_r_1363_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_1371_; lean_object* v___x_1372_; 
v___x_1371_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_1372_ = lean_io_getenv(v___x_1371_);
if (lean_obj_tag(v___x_1372_) == 0)
{
lean_object* v___f_1373_; lean_object* v___f_1374_; lean_object* v___x_1375_; lean_object* v___x_1376_; lean_object* v___x_1377_; 
v___f_1373_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_1374_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_1375_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_1376_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_1377_ = lp_competition_Bench_runFull(v___f_1373_, v___f_1374_, v___x_1375_, v___x_1376_);
return v___x_1377_;
}
else
{
lean_object* v___f_1378_; lean_object* v___f_1379_; lean_object* v___x_1380_; lean_object* v___x_1381_; lean_object* v___x_1382_; 
lean_dec_ref_known(v___x_1372_, 1);
v___f_1378_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_1379_ = ((lean_object*)(lp_competition_main___closed__5));
v___x_1380_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_1381_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_1382_ = lp_competition_Bench_Suite_run(v___f_1378_, v___f_1379_, v___x_1380_, v___x_1381_);
return v___x_1382_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_1383_){
_start:
{
lean_object* v_res_1384_; 
v_res_1384_ = _lean_main();
return v_res_1384_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_competition_BenchFull(uint8_t builtin);
lean_object* initialize_competition_BenchSuite(uint8_t builtin);
lean_object* initialize_competition_Submission(uint8_t builtin);
void lean_initialize();
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_competition_MainFull(uint8_t builtin) {
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
  res = initialize_competition_MainFull(1 /* builtin */);
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
