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
uint8_t lean_float32_beq(float, float);
uint32_t lean_float32_to_bits(float);
float lean_float32_of_bits(uint32_t);
float lean_float32_add(float, float);
float lean_uint32_to_float32(uint32_t);
extern lean_object* lp_competition_R2W01b_scaleTable;
lean_object* lean_array_fget_borrowed(lean_object*, lean_object*);
float lean_float32_mul(float, float);
uint32_t lean_uint32_sub(uint32_t, uint32_t);
uint8_t lean_uint32_dec_le(uint32_t, uint32_t);
uint8_t lean_uint32_dec_lt(uint32_t, uint32_t);
extern lean_object* lp_competition_R19CompactScales_packed;
double lean_float_array_fget(lean_object*, lean_object*);
float lean_float_to_float32(double);
extern uint8_t lp_competition_R19CompactScales_valid;
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
uint8_t v___y_9_; uint8_t v___y_23_; uint8_t v___y_37_; uint8_t v___y_54_; float v___y_61_; float v___y_74_; uint8_t v___y_75_; float v___y_92_; uint8_t v___y_102_; float v___y_117_; uint8_t v___y_118_; float v___y_135_; uint8_t v___y_145_; uint8_t v___x_159_; 
v___x_159_ = lp_competition_R19CompactScales_valid;
if (v___x_159_ == 0)
{
uint32_t v___x_160_; uint32_t v_a_161_; uint32_t v___x_162_; uint32_t v___x_163_; uint32_t v___x_164_; uint8_t v___x_165_; 
v___x_160_ = 2147483647;
v_a_161_ = lean_uint32_land(v___y_1_, v___x_160_);
v___x_162_ = 201326591;
v___x_163_ = 1;
v___x_164_ = lean_uint32_sub(v_a_161_, v___x_163_);
v___x_165_ = lean_uint32_dec_le(v___x_162_, v___x_164_);
if (v___x_165_ == 0)
{
v___y_102_ = v___x_165_;
goto v___jp_101_;
}
else
{
uint32_t v___x_166_; uint8_t v___x_167_; 
v___x_166_ = 2139095040;
v___x_167_ = lean_uint32_dec_lt(v_a_161_, v___x_166_);
v___y_102_ = v___x_167_;
goto v___jp_101_;
}
}
else
{
uint32_t v___x_168_; uint32_t v_a_169_; uint32_t v___x_170_; uint32_t v___x_171_; uint32_t v___x_172_; uint8_t v___x_173_; 
v___x_168_ = 2147483647;
v_a_169_ = lean_uint32_land(v___y_1_, v___x_168_);
v___x_170_ = 201326591;
v___x_171_ = 1;
v___x_172_ = lean_uint32_sub(v_a_169_, v___x_171_);
v___x_173_ = lean_uint32_dec_le(v___x_170_, v___x_172_);
if (v___x_173_ == 0)
{
v___y_145_ = v___x_173_;
goto v___jp_144_;
}
else
{
uint32_t v___x_174_; uint8_t v___x_175_; 
v___x_174_ = 2139095040;
v___x_175_ = lean_uint32_dec_lt(v_a_169_, v___x_174_);
v___y_145_ = v___x_175_;
goto v___jp_144_;
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
uint8_t v___x_62_; 
v___x_62_ = lean_float32_beq(v___y_61_, v___y_61_);
if (v___x_62_ == 0)
{
uint32_t v___x_63_; uint32_t v___x_64_; uint32_t v___x_65_; uint32_t v___x_66_; uint8_t v___x_67_; 
v___x_63_ = 23;
v___x_64_ = lean_uint32_shift_right(v___y_1_, v___x_63_);
v___x_65_ = 255;
v___x_66_ = lean_uint32_land(v___x_64_, v___x_65_);
v___x_67_ = lean_uint32_dec_eq(v___x_66_, v___x_65_);
if (v___x_67_ == 0)
{
v___y_54_ = v___x_67_;
goto v___jp_53_;
}
else
{
uint32_t v___x_68_; uint32_t v___x_69_; uint32_t v___x_70_; uint8_t v___x_71_; 
v___x_68_ = 8388607;
v___x_69_ = lean_uint32_land(v___y_1_, v___x_68_);
v___x_70_ = 0;
v___x_71_ = lean_uint32_dec_eq(v___x_69_, v___x_70_);
if (v___x_71_ == 0)
{
v___y_54_ = v___x_67_;
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
uint32_t v___x_72_; 
v___x_72_ = lean_float32_to_bits(v___y_61_);
return v___x_72_;
}
}
v___jp_73_:
{
if (v___y_75_ == 0)
{
float v___x_76_; float v___x_77_; 
v___x_76_ = lean_float32_of_bits(v___y_2_);
v___x_77_ = lean_float32_add(v___y_74_, v___x_76_);
v___y_61_ = v___x_77_;
goto v___jp_60_;
}
else
{
uint32_t v___x_78_; uint32_t v___x_79_; uint32_t v___x_80_; uint32_t v___x_81_; float v___x_82_; lean_object* v___x_83_; uint32_t v___x_84_; uint32_t v___x_85_; lean_object* v___x_86_; lean_object* v___x_87_; float v___x_88_; float v___x_89_; float v___x_90_; 
v___x_78_ = 8388607;
v___x_79_ = lean_uint32_land(v___y_2_, v___x_78_);
v___x_80_ = 8388608;
v___x_81_ = lean_uint32_lor(v___x_79_, v___x_80_);
v___x_82_ = lean_uint32_to_float32(v___x_81_);
v___x_83_ = lp_competition_R2W01b_scaleTable;
v___x_84_ = 23;
v___x_85_ = lean_uint32_shift_right(v___y_2_, v___x_84_);
v___x_86_ = lean_uint32_to_nat(v___x_85_);
v___x_87_ = lean_array_fget_borrowed(v___x_83_, v___x_86_);
lean_dec(v___x_86_);
v___x_88_ = lean_unbox_float32(v___x_87_);
v___x_89_ = lean_float32_mul(v___x_82_, v___x_88_);
v___x_90_ = lean_float32_add(v___y_74_, v___x_89_);
v___y_61_ = v___x_90_;
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
v___y_74_ = v___y_92_;
v___y_75_ = v___x_98_;
goto v___jp_73_;
}
else
{
uint32_t v___x_99_; uint8_t v___x_100_; 
v___x_99_ = 2139095040;
v___x_100_ = lean_uint32_dec_lt(v_a_94_, v___x_99_);
v___y_74_ = v___y_92_;
v___y_75_ = v___x_100_;
goto v___jp_73_;
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
if (v___y_118_ == 0)
{
float v___x_119_; float v___x_120_; 
v___x_119_ = lean_float32_of_bits(v___y_2_);
v___x_120_ = lean_float32_add(v___y_117_, v___x_119_);
v___y_61_ = v___x_120_;
goto v___jp_60_;
}
else
{
uint32_t v___x_121_; uint32_t v___x_122_; uint32_t v___x_123_; uint32_t v___x_124_; float v___x_125_; lean_object* v___x_126_; uint32_t v___x_127_; uint32_t v___x_128_; lean_object* v___x_129_; double v___x_130_; float v___x_131_; float v___x_132_; float v___x_133_; 
v___x_121_ = 8388607;
v___x_122_ = lean_uint32_land(v___y_2_, v___x_121_);
v___x_123_ = 8388608;
v___x_124_ = lean_uint32_lor(v___x_122_, v___x_123_);
v___x_125_ = lean_uint32_to_float32(v___x_124_);
v___x_126_ = lp_competition_R19CompactScales_packed;
v___x_127_ = 23;
v___x_128_ = lean_uint32_shift_right(v___y_2_, v___x_127_);
v___x_129_ = lean_uint32_to_nat(v___x_128_);
v___x_130_ = lean_float_array_fget(v___x_126_, v___x_129_);
lean_dec(v___x_129_);
v___x_131_ = lean_float_to_float32(v___x_130_);
v___x_132_ = lean_float32_mul(v___x_125_, v___x_131_);
v___x_133_ = lean_float32_add(v___y_117_, v___x_132_);
v___y_61_ = v___x_133_;
goto v___jp_60_;
}
}
v___jp_134_:
{
uint32_t v___x_136_; uint32_t v_a_137_; uint32_t v___x_138_; uint32_t v___x_139_; uint32_t v___x_140_; uint8_t v___x_141_; 
v___x_136_ = 2147483647;
v_a_137_ = lean_uint32_land(v___y_2_, v___x_136_);
v___x_138_ = 201326591;
v___x_139_ = 1;
v___x_140_ = lean_uint32_sub(v_a_137_, v___x_139_);
v___x_141_ = lean_uint32_dec_le(v___x_138_, v___x_140_);
if (v___x_141_ == 0)
{
v___y_117_ = v___y_135_;
v___y_118_ = v___x_141_;
goto v___jp_116_;
}
else
{
uint32_t v___x_142_; uint8_t v___x_143_; 
v___x_142_ = 2139095040;
v___x_143_ = lean_uint32_dec_lt(v_a_137_, v___x_142_);
v___y_117_ = v___y_135_;
v___y_118_ = v___x_143_;
goto v___jp_116_;
}
}
v___jp_144_:
{
if (v___y_145_ == 0)
{
float v___x_146_; 
v___x_146_ = lean_float32_of_bits(v___y_1_);
v___y_135_ = v___x_146_;
goto v___jp_134_;
}
else
{
uint32_t v___x_147_; uint32_t v___x_148_; uint32_t v___x_149_; uint32_t v___x_150_; float v___x_151_; lean_object* v___x_152_; uint32_t v___x_153_; uint32_t v___x_154_; lean_object* v___x_155_; double v___x_156_; float v___x_157_; float v___x_158_; 
v___x_147_ = 8388607;
v___x_148_ = lean_uint32_land(v___y_1_, v___x_147_);
v___x_149_ = 8388608;
v___x_150_ = lean_uint32_lor(v___x_148_, v___x_149_);
v___x_151_ = lean_uint32_to_float32(v___x_150_);
v___x_152_ = lp_competition_R19CompactScales_packed;
v___x_153_ = 23;
v___x_154_ = lean_uint32_shift_right(v___y_1_, v___x_153_);
v___x_155_ = lean_uint32_to_nat(v___x_154_);
v___x_156_ = lean_float_array_fget(v___x_152_, v___x_155_);
lean_dec(v___x_155_);
v___x_157_ = lean_float_to_float32(v___x_156_);
v___x_158_ = lean_float32_mul(v___x_151_, v___x_157_);
v___y_135_ = v___x_158_;
goto v___jp_134_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object* v___y_176_, lean_object* v___y_177_){
_start:
{
uint32_t v___y_4929__boxed_178_; uint32_t v___y_4930__boxed_179_; uint32_t v_res_180_; lean_object* v_r_181_; 
v___y_4929__boxed_178_ = lean_unbox_uint32(v___y_176_);
lean_dec(v___y_176_);
v___y_4930__boxed_179_ = lean_unbox_uint32(v___y_177_);
lean_dec(v___y_177_);
v_res_180_ = lp_competition_main___lam__0(v___y_4929__boxed_178_, v___y_4930__boxed_179_);
v_r_181_ = lean_box_uint32(v_res_180_);
return v_r_181_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t v___y_182_, uint32_t v___y_183_){
_start:
{
uint32_t v___y_185_; uint32_t v___y_189_; uint32_t v___y_193_; uint32_t v___y_194_; uint32_t v___y_195_; uint32_t v___y_199_; uint8_t v___y_200_; uint64_t v___y_201_; uint64_t v___y_202_; uint32_t v___y_214_; uint32_t v___y_215_; uint32_t v___y_216_; uint32_t v___y_220_; uint64_t v___y_221_; uint8_t v___y_222_; uint64_t v___y_223_; uint8_t v___y_235_; uint8_t v___y_251_; uint8_t v___y_265_; uint8_t v___y_282_; float v___y_289_; uint32_t v___x_301_; uint32_t v___x_302_; uint32_t v___x_303_; uint32_t v___y_305_; uint32_t v___y_306_; uint32_t v___y_307_; uint32_t v___y_308_; uint32_t v___y_315_; uint8_t v___y_316_; uint32_t v___y_317_; uint32_t v___y_318_; uint32_t v___y_322_; uint8_t v___y_323_; uint64_t v___y_324_; uint64_t v___y_325_; uint64_t v___y_326_; uint32_t v___y_336_; uint8_t v___y_337_; uint8_t v___y_338_; uint64_t v___y_339_; uint64_t v___y_340_; uint64_t v___y_341_; uint32_t v___y_348_; uint64_t v___y_349_; uint8_t v___y_350_; uint64_t v___y_351_; uint64_t v___y_352_; uint32_t v___y_358_; uint8_t v___y_359_; uint64_t v___y_360_; uint64_t v___y_361_; uint64_t v___y_362_; uint64_t v___y_363_; uint32_t v___y_418_; uint8_t v___y_419_; uint64_t v___y_420_; uint64_t v___y_421_; uint64_t v___y_422_; uint64_t v___y_423_; uint64_t v___y_424_; uint64_t v___y_430_; uint64_t v___y_431_; uint32_t v___y_432_; uint8_t v___y_433_; uint64_t v___y_434_; uint64_t v___y_435_; uint64_t v___y_436_; uint64_t v___y_437_; uint64_t v___y_438_; uint64_t v___y_443_; uint32_t v___y_444_; uint8_t v___y_445_; uint64_t v___y_446_; uint64_t v___y_447_; uint64_t v___y_448_; uint64_t v___y_449_; uint32_t v___y_454_; uint64_t v___y_455_; uint8_t v___y_456_; uint64_t v___y_457_; uint64_t v___y_458_; uint64_t v___y_459_; uint64_t v___y_460_; uint64_t v___y_461_; uint64_t v___y_462_; uint32_t v___y_467_; uint8_t v___y_468_; uint64_t v___y_469_; uint64_t v___y_470_; uint64_t v___y_471_; uint64_t v___y_472_; uint64_t v___y_473_; uint32_t v___y_478_; uint64_t v___y_479_; uint8_t v___y_480_; uint64_t v___y_481_; uint64_t v___y_482_; uint64_t v___y_483_; uint64_t v___y_484_; uint64_t v___y_485_; uint64_t v___y_486_; uint32_t v___y_491_; uint8_t v___y_492_; uint64_t v___y_493_; uint64_t v___y_494_; uint64_t v___y_495_; uint64_t v___y_496_; uint64_t v___y_497_; uint64_t v___y_502_; uint32_t v___y_503_; uint64_t v___y_504_; uint64_t v___y_505_; uint8_t v___y_506_; uint64_t v___y_507_; uint64_t v___y_508_; uint64_t v___y_509_; uint64_t v___y_510_; uint32_t v___y_515_; uint64_t v___y_516_; uint8_t v___y_517_; uint64_t v___y_518_; uint64_t v___y_519_; uint64_t v___y_520_; uint64_t v___y_521_; uint32_t v___y_526_; uint8_t v___y_527_; uint64_t v___y_528_; uint64_t v___y_529_; uint64_t v___y_530_; uint64_t v___y_531_; uint64_t v___y_532_; uint32_t v___y_536_; uint8_t v___y_537_; uint64_t v___y_538_; uint64_t v___y_539_; uint32_t v___y_548_; uint64_t v___y_549_; uint64_t v___y_550_; uint64_t v___y_551_; uint8_t v___y_552_; uint64_t v___y_553_; uint32_t v_ex_586_; uint32_t v___x_587_; float v___y_589_; uint8_t v___y_590_; float v___y_605_; uint8_t v___y_615_; float v___y_628_; uint8_t v___y_629_; float v___y_644_; uint8_t v___y_654_; uint32_t v_ey_666_; uint64_t v___y_668_; uint32_t v___y_669_; uint64_t v___y_670_; uint8_t v___y_671_; uint64_t v___y_672_; uint32_t v___y_679_; uint64_t v___y_680_; uint8_t v___y_681_; uint64_t v___y_682_; uint32_t v___y_689_; uint8_t v___y_690_; uint32_t v___y_691_; uint64_t v___y_692_; uint8_t v___y_700_; uint32_t v___x_710_; uint32_t v___x_711_; uint8_t v___x_712_; uint8_t v___y_714_; uint8_t v___y_715_; uint8_t v___y_717_; uint8_t v___y_718_; uint8_t v___y_719_; uint8_t v___y_721_; uint8_t v___y_722_; uint8_t v___y_728_; 
v___x_301_ = 23;
v___x_302_ = lean_uint32_shift_right(v___y_182_, v___x_301_);
v___x_303_ = 255;
v_ex_586_ = lean_uint32_land(v___x_302_, v___x_303_);
v___x_587_ = lean_uint32_shift_right(v___y_183_, v___x_301_);
v_ey_666_ = lean_uint32_land(v___x_587_, v___x_303_);
v___x_710_ = lean_uint32_add(v_ex_586_, v_ey_666_);
v___x_711_ = 128;
v___x_712_ = lean_uint32_dec_lt(v___x_710_, v___x_711_);
if (v___x_712_ == 0)
{
uint8_t v___x_737_; 
v___x_737_ = lp_competition_R19CompactScales_valid;
if (v___x_737_ == 0)
{
uint32_t v___x_738_; uint32_t v_a_739_; uint32_t v___x_740_; uint32_t v___x_741_; uint32_t v___x_742_; uint8_t v___x_743_; 
v___x_738_ = 2147483647;
v_a_739_ = lean_uint32_land(v___y_182_, v___x_738_);
v___x_740_ = 201326591;
v___x_741_ = 1;
v___x_742_ = lean_uint32_sub(v_a_739_, v___x_741_);
v___x_743_ = lean_uint32_dec_le(v___x_740_, v___x_742_);
if (v___x_743_ == 0)
{
v___y_654_ = v___x_743_;
goto v___jp_653_;
}
else
{
uint32_t v___x_744_; uint8_t v___x_745_; 
v___x_744_ = 2139095040;
v___x_745_ = lean_uint32_dec_lt(v_a_739_, v___x_744_);
v___y_654_ = v___x_745_;
goto v___jp_653_;
}
}
else
{
uint32_t v___x_746_; uint32_t v_a_747_; uint32_t v___x_748_; uint32_t v___x_749_; uint32_t v___x_750_; uint8_t v___x_751_; 
v___x_746_ = 2147483647;
v_a_747_ = lean_uint32_land(v___y_182_, v___x_746_);
v___x_748_ = 201326591;
v___x_749_ = 1;
v___x_750_ = lean_uint32_sub(v_a_747_, v___x_749_);
v___x_751_ = lean_uint32_dec_le(v___x_748_, v___x_750_);
if (v___x_751_ == 0)
{
v___y_615_ = v___x_751_;
goto v___jp_614_;
}
else
{
uint32_t v___x_752_; uint8_t v___x_753_; 
v___x_752_ = 2139095040;
v___x_753_ = lean_uint32_dec_lt(v_a_747_, v___x_752_);
v___y_615_ = v___x_753_;
goto v___jp_614_;
}
}
}
else
{
uint32_t v___x_754_; uint32_t v___x_755_; uint32_t v___x_756_; uint8_t v___x_757_; 
v___x_754_ = 4278190080;
v___x_755_ = 1;
v___x_756_ = lean_uint32_shift_left(v___y_182_, v___x_755_);
v___x_757_ = lean_uint32_dec_le(v___x_754_, v___x_756_);
if (v___x_757_ == 0)
{
uint32_t v___x_758_; uint8_t v___x_759_; 
v___x_758_ = lean_uint32_shift_left(v___y_183_, v___x_755_);
v___x_759_ = lean_uint32_dec_le(v___x_754_, v___x_758_);
v___y_728_ = v___x_759_;
goto v___jp_727_;
}
else
{
v___y_728_ = v___x_757_;
goto v___jp_727_;
}
}
v___jp_184_:
{
uint32_t v___x_186_; uint32_t v___x_187_; 
v___x_186_ = 8388608;
v___x_187_ = lean_uint32_lor(v___y_185_, v___x_186_);
return v___x_187_;
}
v___jp_188_:
{
uint32_t v___x_190_; uint32_t v___x_191_; 
v___x_190_ = 8388608;
v___x_191_ = lean_uint32_lor(v___y_189_, v___x_190_);
return v___x_191_;
}
v___jp_192_:
{
uint32_t v___x_196_; uint32_t v___x_197_; 
v___x_196_ = lean_uint32_land(v___y_194_, v___y_193_);
v___x_197_ = lean_uint32_lor(v___y_195_, v___x_196_);
return v___x_197_;
}
v___jp_198_:
{
uint8_t v___x_203_; 
v___x_203_ = lean_uint64_dec_eq(v___y_202_, v___y_201_);
if (v___x_203_ == 0)
{
uint64_t v___x_204_; uint8_t v___x_205_; 
v___x_204_ = 8388608ULL;
v___x_205_ = lean_uint64_dec_eq(v___y_202_, v___x_204_);
if (v___x_205_ == 0)
{
uint32_t v___x_206_; 
v___x_206_ = lean_uint64_to_uint32(v___y_202_);
if (v___y_200_ == 0)
{
uint32_t v___x_207_; 
v___x_207_ = 0;
v___y_193_ = v___y_199_;
v___y_194_ = v___x_206_;
v___y_195_ = v___x_207_;
goto v___jp_192_;
}
else
{
uint32_t v___x_208_; 
v___x_208_ = 2147483648;
v___y_193_ = v___y_199_;
v___y_194_ = v___x_206_;
v___y_195_ = v___x_208_;
goto v___jp_192_;
}
}
else
{
if (v___y_200_ == 0)
{
uint32_t v___x_209_; 
v___x_209_ = 0;
v___y_189_ = v___x_209_;
goto v___jp_188_;
}
else
{
uint32_t v___x_210_; 
v___x_210_ = 2147483648;
v___y_189_ = v___x_210_;
goto v___jp_188_;
}
}
}
else
{
if (v___y_200_ == 0)
{
uint32_t v___x_211_; 
v___x_211_ = 0;
return v___x_211_;
}
else
{
uint32_t v___x_212_; 
v___x_212_ = 2147483648;
return v___x_212_;
}
}
}
v___jp_213_:
{
uint32_t v___x_217_; uint32_t v___x_218_; 
v___x_217_ = lean_uint32_land(v___y_215_, v___y_214_);
v___x_218_ = lean_uint32_lor(v___y_216_, v___x_217_);
return v___x_218_;
}
v___jp_219_:
{
uint8_t v___x_224_; 
v___x_224_ = lean_uint64_dec_eq(v___y_223_, v___y_221_);
if (v___x_224_ == 0)
{
uint64_t v___x_225_; uint8_t v___x_226_; 
v___x_225_ = 8388608ULL;
v___x_226_ = lean_uint64_dec_eq(v___y_223_, v___x_225_);
if (v___x_226_ == 0)
{
uint32_t v___x_227_; 
v___x_227_ = lean_uint64_to_uint32(v___y_223_);
if (v___y_222_ == 0)
{
uint32_t v___x_228_; 
v___x_228_ = 0;
v___y_214_ = v___y_220_;
v___y_215_ = v___x_227_;
v___y_216_ = v___x_228_;
goto v___jp_213_;
}
else
{
uint32_t v___x_229_; 
v___x_229_ = 2147483648;
v___y_214_ = v___y_220_;
v___y_215_ = v___x_227_;
v___y_216_ = v___x_229_;
goto v___jp_213_;
}
}
else
{
if (v___y_222_ == 0)
{
uint32_t v___x_230_; 
v___x_230_ = 0;
v___y_185_ = v___x_230_;
goto v___jp_184_;
}
else
{
uint32_t v___x_231_; 
v___x_231_ = 2147483648;
v___y_185_ = v___x_231_;
goto v___jp_184_;
}
}
}
else
{
if (v___y_222_ == 0)
{
uint32_t v___x_232_; 
v___x_232_ = 0;
return v___x_232_;
}
else
{
uint32_t v___x_233_; 
v___x_233_ = 2147483648;
return v___x_233_;
}
}
}
v___jp_234_:
{
if (v___y_235_ == 0)
{
uint32_t v___x_236_; 
v___x_236_ = lp_competition_Submission_FastMul_mul(v___y_182_, v___y_183_);
return v___x_236_;
}
else
{
uint32_t v___x_237_; uint32_t v___x_238_; 
v___x_237_ = 4194304;
v___x_238_ = lean_uint32_lor(v___y_183_, v___x_237_);
return v___x_238_;
}
}
v___jp_239_:
{
uint32_t v___x_240_; uint32_t v___x_241_; uint32_t v___x_242_; uint32_t v___x_243_; uint8_t v___x_244_; 
v___x_240_ = 23;
v___x_241_ = lean_uint32_shift_right(v___y_183_, v___x_240_);
v___x_242_ = 255;
v___x_243_ = lean_uint32_land(v___x_241_, v___x_242_);
v___x_244_ = lean_uint32_dec_eq(v___x_243_, v___x_242_);
if (v___x_244_ == 0)
{
v___y_235_ = v___x_244_;
goto v___jp_234_;
}
else
{
uint32_t v___x_245_; uint32_t v___x_246_; uint32_t v___x_247_; uint8_t v___x_248_; 
v___x_245_ = 8388607;
v___x_246_ = lean_uint32_land(v___y_183_, v___x_245_);
v___x_247_ = 0;
v___x_248_ = lean_uint32_dec_eq(v___x_246_, v___x_247_);
if (v___x_248_ == 0)
{
v___y_235_ = v___x_244_;
goto v___jp_234_;
}
else
{
uint32_t v___x_249_; 
v___x_249_ = lp_competition_Submission_FastMul_mul(v___y_182_, v___y_183_);
return v___x_249_;
}
}
}
v___jp_250_:
{
if (v___y_251_ == 0)
{
goto v___jp_239_;
}
else
{
uint32_t v___x_252_; uint32_t v___x_253_; 
v___x_252_ = 4194304;
v___x_253_ = lean_uint32_lor(v___y_182_, v___x_252_);
return v___x_253_;
}
}
v___jp_254_:
{
uint32_t v___x_255_; uint32_t v___x_256_; uint32_t v___x_257_; uint32_t v___x_258_; uint8_t v___x_259_; 
v___x_255_ = 23;
v___x_256_ = lean_uint32_shift_right(v___y_182_, v___x_255_);
v___x_257_ = 255;
v___x_258_ = lean_uint32_land(v___x_256_, v___x_257_);
v___x_259_ = lean_uint32_dec_eq(v___x_258_, v___x_257_);
if (v___x_259_ == 0)
{
v___y_251_ = v___x_259_;
goto v___jp_250_;
}
else
{
uint32_t v___x_260_; uint32_t v___x_261_; uint32_t v___x_262_; uint8_t v___x_263_; 
v___x_260_ = 8388607;
v___x_261_ = lean_uint32_land(v___y_182_, v___x_260_);
v___x_262_ = 0;
v___x_263_ = lean_uint32_dec_eq(v___x_261_, v___x_262_);
if (v___x_263_ == 0)
{
v___y_251_ = v___x_259_;
goto v___jp_250_;
}
else
{
goto v___jp_239_;
}
}
}
v___jp_264_:
{
if (v___y_265_ == 0)
{
goto v___jp_254_;
}
else
{
uint32_t v___x_266_; uint32_t v___x_267_; uint32_t v___x_268_; uint8_t v___x_269_; 
v___x_266_ = 4194304;
v___x_267_ = lean_uint32_land(v___y_183_, v___x_266_);
v___x_268_ = 0;
v___x_269_ = lean_uint32_dec_eq(v___x_267_, v___x_268_);
if (v___x_269_ == 0)
{
goto v___jp_254_;
}
else
{
uint32_t v___x_270_; 
v___x_270_ = lean_uint32_lor(v___y_183_, v___x_266_);
return v___x_270_;
}
}
}
v___jp_271_:
{
uint32_t v___x_272_; uint32_t v___x_273_; uint32_t v___x_274_; uint32_t v___x_275_; uint8_t v___x_276_; 
v___x_272_ = 23;
v___x_273_ = lean_uint32_shift_right(v___y_183_, v___x_272_);
v___x_274_ = 255;
v___x_275_ = lean_uint32_land(v___x_273_, v___x_274_);
v___x_276_ = lean_uint32_dec_eq(v___x_275_, v___x_274_);
if (v___x_276_ == 0)
{
v___y_265_ = v___x_276_;
goto v___jp_264_;
}
else
{
uint32_t v___x_277_; uint32_t v___x_278_; uint32_t v___x_279_; uint8_t v___x_280_; 
v___x_277_ = 8388607;
v___x_278_ = lean_uint32_land(v___y_183_, v___x_277_);
v___x_279_ = 0;
v___x_280_ = lean_uint32_dec_eq(v___x_278_, v___x_279_);
if (v___x_280_ == 0)
{
v___y_265_ = v___x_276_;
goto v___jp_264_;
}
else
{
goto v___jp_254_;
}
}
}
v___jp_281_:
{
if (v___y_282_ == 0)
{
goto v___jp_271_;
}
else
{
uint32_t v___x_283_; uint32_t v___x_284_; uint32_t v___x_285_; uint8_t v___x_286_; 
v___x_283_ = 4194304;
v___x_284_ = lean_uint32_land(v___y_182_, v___x_283_);
v___x_285_ = 0;
v___x_286_ = lean_uint32_dec_eq(v___x_284_, v___x_285_);
if (v___x_286_ == 0)
{
goto v___jp_271_;
}
else
{
uint32_t v___x_287_; 
v___x_287_ = lean_uint32_lor(v___y_182_, v___x_283_);
return v___x_287_;
}
}
}
v___jp_288_:
{
uint8_t v___x_290_; 
v___x_290_ = lean_float32_beq(v___y_289_, v___y_289_);
if (v___x_290_ == 0)
{
uint32_t v___x_291_; uint32_t v___x_292_; uint32_t v___x_293_; uint32_t v___x_294_; uint8_t v___x_295_; 
v___x_291_ = 23;
v___x_292_ = lean_uint32_shift_right(v___y_182_, v___x_291_);
v___x_293_ = 255;
v___x_294_ = lean_uint32_land(v___x_292_, v___x_293_);
v___x_295_ = lean_uint32_dec_eq(v___x_294_, v___x_293_);
if (v___x_295_ == 0)
{
v___y_282_ = v___x_295_;
goto v___jp_281_;
}
else
{
uint32_t v___x_296_; uint32_t v___x_297_; uint32_t v___x_298_; uint8_t v___x_299_; 
v___x_296_ = 8388607;
v___x_297_ = lean_uint32_land(v___y_182_, v___x_296_);
v___x_298_ = 0;
v___x_299_ = lean_uint32_dec_eq(v___x_297_, v___x_298_);
if (v___x_299_ == 0)
{
v___y_282_ = v___x_295_;
goto v___jp_281_;
}
else
{
goto v___jp_271_;
}
}
}
else
{
uint32_t v___x_300_; 
v___x_300_ = lean_float32_to_bits(v___y_289_);
return v___x_300_;
}
}
v___jp_304_:
{
uint32_t v___x_309_; uint32_t v___x_310_; uint32_t v___x_311_; uint32_t v___x_312_; uint32_t v___x_313_; 
v___x_309_ = lean_uint32_land(v___y_307_, v___x_303_);
v___x_310_ = lean_uint32_shift_left(v___x_309_, v___x_301_);
v___x_311_ = lean_uint32_lor(v___y_308_, v___x_310_);
v___x_312_ = lean_uint32_land(v___y_306_, v___y_305_);
v___x_313_ = lean_uint32_lor(v___x_311_, v___x_312_);
return v___x_313_;
}
v___jp_314_:
{
if (v___y_316_ == 0)
{
uint32_t v___x_319_; 
v___x_319_ = 0;
v___y_305_ = v___y_315_;
v___y_306_ = v___y_318_;
v___y_307_ = v___y_317_;
v___y_308_ = v___x_319_;
goto v___jp_304_;
}
else
{
uint32_t v___x_320_; 
v___x_320_ = 2147483648;
v___y_305_ = v___y_315_;
v___y_306_ = v___y_318_;
v___y_307_ = v___y_317_;
v___y_308_ = v___x_320_;
goto v___jp_304_;
}
}
v___jp_321_:
{
uint64_t v___x_327_; uint64_t v_encodedExponent_328_; uint32_t v___x_329_; uint64_t v___x_330_; uint8_t v___x_331_; 
v___x_327_ = 171ULL;
v_encodedExponent_328_ = lean_uint64_sub(v___y_325_, v___x_327_);
v___x_329_ = lean_uint64_to_uint32(v_encodedExponent_328_);
v___x_330_ = 8388608ULL;
v___x_331_ = lean_uint64_dec_lt(v___y_326_, v___x_330_);
if (v___x_331_ == 0)
{
uint64_t v___x_332_; uint32_t v___x_333_; 
v___x_332_ = lean_uint64_sub(v___y_326_, v___x_330_);
v___x_333_ = lean_uint64_to_uint32(v___x_332_);
v___y_315_ = v___y_322_;
v___y_316_ = v___y_323_;
v___y_317_ = v___x_329_;
v___y_318_ = v___x_333_;
goto v___jp_314_;
}
else
{
uint32_t v___x_334_; 
v___x_334_ = lean_uint64_to_uint32(v___y_324_);
v___y_315_ = v___y_322_;
v___y_316_ = v___y_323_;
v___y_317_ = v___x_329_;
v___y_318_ = v___x_334_;
goto v___jp_314_;
}
}
v___jp_335_:
{
uint64_t v___x_342_; uint8_t v___x_343_; 
v___x_342_ = 425ULL;
v___x_343_ = lean_uint64_dec_lt(v___x_342_, v___y_341_);
if (v___x_343_ == 0)
{
if (v___y_337_ == 0)
{
v___y_322_ = v___y_336_;
v___y_323_ = v___y_338_;
v___y_324_ = v___y_339_;
v___y_325_ = v___y_341_;
v___y_326_ = v___y_340_;
goto v___jp_321_;
}
else
{
uint64_t v___x_344_; 
v___x_344_ = 8388608ULL;
v___y_322_ = v___y_336_;
v___y_323_ = v___y_338_;
v___y_324_ = v___y_339_;
v___y_325_ = v___y_341_;
v___y_326_ = v___x_344_;
goto v___jp_321_;
}
}
else
{
if (v___y_338_ == 0)
{
uint32_t v___x_345_; 
v___x_345_ = 2139095040;
return v___x_345_;
}
else
{
uint32_t v___x_346_; 
v___x_346_ = 4286578688;
return v___x_346_;
}
}
}
v___jp_347_:
{
uint64_t v___x_353_; uint8_t v_carry_354_; 
v___x_353_ = 16777216ULL;
v_carry_354_ = lean_uint64_dec_eq(v___y_352_, v___x_353_);
if (v_carry_354_ == 0)
{
v___y_336_ = v___y_348_;
v___y_337_ = v_carry_354_;
v___y_338_ = v___y_350_;
v___y_339_ = v___y_351_;
v___y_340_ = v___y_352_;
v___y_341_ = v___y_349_;
goto v___jp_335_;
}
else
{
uint64_t v___x_355_; uint64_t v___x_356_; 
v___x_355_ = 1ULL;
v___x_356_ = lean_uint64_add(v___y_349_, v___x_355_);
v___y_336_ = v___y_348_;
v___y_337_ = v_carry_354_;
v___y_338_ = v___y_350_;
v___y_339_ = v___y_351_;
v___y_340_ = v___y_352_;
v___y_341_ = v___x_356_;
goto v___jp_335_;
}
}
v___jp_357_:
{
uint64_t v_position_364_; uint64_t v___x_365_; uint8_t v___x_366_; 
v_position_364_ = lean_uint64_add(v___y_363_, v___y_362_);
v___x_365_ = 172ULL;
v___x_366_ = lean_uint64_dec_lt(v_position_364_, v___x_365_);
if (v___x_366_ == 0)
{
uint64_t v___x_367_; uint8_t v___x_368_; 
v___x_367_ = 23ULL;
v___x_368_ = lean_uint64_dec_lt(v___y_363_, v___x_367_);
if (v___x_368_ == 0)
{
uint64_t v___x_369_; uint8_t v___x_370_; 
v___x_369_ = lean_uint64_sub(v___y_363_, v___x_367_);
v___x_370_ = lean_uint64_dec_eq(v___x_369_, v___y_360_);
if (v___x_370_ == 0)
{
uint64_t v___x_371_; uint8_t v___x_372_; 
v___x_371_ = 64ULL;
v___x_372_ = lean_uint64_dec_lt(v___x_369_, v___x_371_);
if (v___x_372_ == 0)
{
uint8_t v___x_373_; 
v___x_373_ = lean_uint64_dec_eq(v___x_369_, v___x_371_);
if (v___x_373_ == 0)
{
v___y_348_ = v___y_358_;
v___y_349_ = v_position_364_;
v___y_350_ = v___y_359_;
v___y_351_ = v___y_360_;
v___y_352_ = v___y_360_;
goto v___jp_347_;
}
else
{
uint64_t v___x_374_; uint8_t v___x_375_; 
v___x_374_ = 9223372036854775808ULL;
v___x_375_ = lean_uint64_dec_lt(v___x_374_, v___y_361_);
if (v___x_375_ == 0)
{
v___y_348_ = v___y_358_;
v___y_349_ = v_position_364_;
v___y_350_ = v___y_359_;
v___y_351_ = v___y_360_;
v___y_352_ = v___y_360_;
goto v___jp_347_;
}
else
{
uint64_t v___x_376_; 
v___x_376_ = 1ULL;
v___y_348_ = v___y_358_;
v___y_349_ = v_position_364_;
v___y_350_ = v___y_359_;
v___y_351_ = v___y_360_;
v___y_352_ = v___x_376_;
goto v___jp_347_;
}
}
}
else
{
uint64_t v_quotient_377_; uint64_t v___x_378_; uint64_t v___x_379_; uint64_t v___x_380_; uint64_t v_remainder_381_; uint64_t v___x_382_; uint64_t v_half_383_; uint8_t v___x_384_; 
v_quotient_377_ = lean_uint64_shift_right(v___y_361_, v___x_369_);
v___x_378_ = 1ULL;
v___x_379_ = lean_uint64_shift_left(v___x_378_, v___x_369_);
v___x_380_ = lean_uint64_sub(v___x_379_, v___x_378_);
v_remainder_381_ = lean_uint64_land(v___y_361_, v___x_380_);
v___x_382_ = lean_uint64_sub(v___x_369_, v___x_378_);
v_half_383_ = lean_uint64_shift_left(v___x_378_, v___x_382_);
v___x_384_ = lean_uint64_dec_lt(v_remainder_381_, v_half_383_);
if (v___x_384_ == 0)
{
uint8_t v___x_385_; 
v___x_385_ = lean_uint64_dec_lt(v_half_383_, v_remainder_381_);
if (v___x_385_ == 0)
{
uint64_t v___x_386_; uint8_t v___x_387_; 
v___x_386_ = lean_uint64_land(v_quotient_377_, v___x_378_);
v___x_387_ = lean_uint64_dec_eq(v___x_386_, v___y_360_);
if (v___x_387_ == 0)
{
uint64_t v___x_388_; 
v___x_388_ = lean_uint64_add(v_quotient_377_, v___x_378_);
v___y_348_ = v___y_358_;
v___y_349_ = v_position_364_;
v___y_350_ = v___y_359_;
v___y_351_ = v___y_360_;
v___y_352_ = v___x_388_;
goto v___jp_347_;
}
else
{
v___y_348_ = v___y_358_;
v___y_349_ = v_position_364_;
v___y_350_ = v___y_359_;
v___y_351_ = v___y_360_;
v___y_352_ = v_quotient_377_;
goto v___jp_347_;
}
}
else
{
uint64_t v___x_389_; 
v___x_389_ = lean_uint64_add(v_quotient_377_, v___x_378_);
v___y_348_ = v___y_358_;
v___y_349_ = v_position_364_;
v___y_350_ = v___y_359_;
v___y_351_ = v___y_360_;
v___y_352_ = v___x_389_;
goto v___jp_347_;
}
}
else
{
v___y_348_ = v___y_358_;
v___y_349_ = v_position_364_;
v___y_350_ = v___y_359_;
v___y_351_ = v___y_360_;
v___y_352_ = v_quotient_377_;
goto v___jp_347_;
}
}
}
else
{
v___y_348_ = v___y_358_;
v___y_349_ = v_position_364_;
v___y_350_ = v___y_359_;
v___y_351_ = v___y_360_;
v___y_352_ = v___y_361_;
goto v___jp_347_;
}
}
else
{
uint64_t v___x_390_; uint64_t v___x_391_; 
v___x_390_ = lean_uint64_sub(v___x_367_, v___y_363_);
v___x_391_ = lean_uint64_shift_left(v___y_361_, v___x_390_);
v___y_348_ = v___y_358_;
v___y_349_ = v_position_364_;
v___y_350_ = v___y_359_;
v___y_351_ = v___y_360_;
v___y_352_ = v___x_391_;
goto v___jp_347_;
}
}
else
{
uint64_t v___x_392_; uint8_t v___x_393_; 
v___x_392_ = 149ULL;
v___x_393_ = lean_uint64_dec_lt(v___y_362_, v___x_392_);
if (v___x_393_ == 0)
{
uint64_t v___x_394_; uint64_t v___x_395_; 
v___x_394_ = lean_uint64_sub(v___y_362_, v___x_392_);
v___x_395_ = lean_uint64_shift_left(v___y_361_, v___x_394_);
v___y_199_ = v___y_358_;
v___y_200_ = v___y_359_;
v___y_201_ = v___y_360_;
v___y_202_ = v___x_395_;
goto v___jp_198_;
}
else
{
uint64_t v___x_396_; uint8_t v___x_397_; 
v___x_396_ = lean_uint64_sub(v___x_392_, v___y_362_);
v___x_397_ = lean_uint64_dec_eq(v___x_396_, v___y_360_);
if (v___x_397_ == 0)
{
uint64_t v___x_398_; uint8_t v___x_399_; 
v___x_398_ = 64ULL;
v___x_399_ = lean_uint64_dec_lt(v___x_396_, v___x_398_);
if (v___x_399_ == 0)
{
uint8_t v___x_400_; 
v___x_400_ = lean_uint64_dec_eq(v___x_396_, v___x_398_);
if (v___x_400_ == 0)
{
v___y_199_ = v___y_358_;
v___y_200_ = v___y_359_;
v___y_201_ = v___y_360_;
v___y_202_ = v___y_360_;
goto v___jp_198_;
}
else
{
uint64_t v___x_401_; uint8_t v___x_402_; 
v___x_401_ = 9223372036854775808ULL;
v___x_402_ = lean_uint64_dec_lt(v___x_401_, v___y_361_);
if (v___x_402_ == 0)
{
v___y_199_ = v___y_358_;
v___y_200_ = v___y_359_;
v___y_201_ = v___y_360_;
v___y_202_ = v___y_360_;
goto v___jp_198_;
}
else
{
uint64_t v___x_403_; 
v___x_403_ = 1ULL;
v___y_199_ = v___y_358_;
v___y_200_ = v___y_359_;
v___y_201_ = v___y_360_;
v___y_202_ = v___x_403_;
goto v___jp_198_;
}
}
}
else
{
uint64_t v_quotient_404_; uint64_t v___x_405_; uint64_t v___x_406_; uint64_t v___x_407_; uint64_t v_remainder_408_; uint64_t v___x_409_; uint64_t v_half_410_; uint8_t v___x_411_; 
v_quotient_404_ = lean_uint64_shift_right(v___y_361_, v___x_396_);
v___x_405_ = 1ULL;
v___x_406_ = lean_uint64_shift_left(v___x_405_, v___x_396_);
v___x_407_ = lean_uint64_sub(v___x_406_, v___x_405_);
v_remainder_408_ = lean_uint64_land(v___y_361_, v___x_407_);
v___x_409_ = lean_uint64_sub(v___x_396_, v___x_405_);
v_half_410_ = lean_uint64_shift_left(v___x_405_, v___x_409_);
v___x_411_ = lean_uint64_dec_lt(v_remainder_408_, v_half_410_);
if (v___x_411_ == 0)
{
uint8_t v___x_412_; 
v___x_412_ = lean_uint64_dec_lt(v_half_410_, v_remainder_408_);
if (v___x_412_ == 0)
{
uint64_t v___x_413_; uint8_t v___x_414_; 
v___x_413_ = lean_uint64_land(v_quotient_404_, v___x_405_);
v___x_414_ = lean_uint64_dec_eq(v___x_413_, v___y_360_);
if (v___x_414_ == 0)
{
uint64_t v___x_415_; 
v___x_415_ = lean_uint64_add(v_quotient_404_, v___x_405_);
v___y_199_ = v___y_358_;
v___y_200_ = v___y_359_;
v___y_201_ = v___y_360_;
v___y_202_ = v___x_415_;
goto v___jp_198_;
}
else
{
v___y_199_ = v___y_358_;
v___y_200_ = v___y_359_;
v___y_201_ = v___y_360_;
v___y_202_ = v_quotient_404_;
goto v___jp_198_;
}
}
else
{
uint64_t v___x_416_; 
v___x_416_ = lean_uint64_add(v_quotient_404_, v___x_405_);
v___y_199_ = v___y_358_;
v___y_200_ = v___y_359_;
v___y_201_ = v___y_360_;
v___y_202_ = v___x_416_;
goto v___jp_198_;
}
}
else
{
v___y_199_ = v___y_358_;
v___y_200_ = v___y_359_;
v___y_201_ = v___y_360_;
v___y_202_ = v_quotient_404_;
goto v___jp_198_;
}
}
}
else
{
v___y_199_ = v___y_358_;
v___y_200_ = v___y_359_;
v___y_201_ = v___y_360_;
v___y_202_ = v___y_361_;
goto v___jp_198_;
}
}
}
}
v___jp_417_:
{
uint64_t v___x_425_; uint64_t v___x_426_; uint8_t v___x_427_; 
v___x_425_ = 1ULL;
v___x_426_ = lean_uint64_shift_right(v___y_423_, v___x_425_);
v___x_427_ = lean_uint64_dec_eq(v___x_426_, v___y_420_);
if (v___x_427_ == 0)
{
uint64_t v___x_428_; 
v___x_428_ = lean_uint64_add(v___y_424_, v___x_425_);
v___y_358_ = v___y_418_;
v___y_359_ = v___y_419_;
v___y_360_ = v___y_420_;
v___y_361_ = v___y_422_;
v___y_362_ = v___y_421_;
v___y_363_ = v___x_428_;
goto v___jp_357_;
}
else
{
v___y_358_ = v___y_418_;
v___y_359_ = v___y_419_;
v___y_360_ = v___y_420_;
v___y_361_ = v___y_422_;
v___y_362_ = v___y_421_;
v___y_363_ = v___y_424_;
goto v___jp_357_;
}
}
v___jp_429_:
{
uint64_t v___x_439_; uint8_t v___x_440_; 
v___x_439_ = lean_uint64_shift_right(v___y_430_, v___y_435_);
v___x_440_ = lean_uint64_dec_eq(v___x_439_, v___y_434_);
if (v___x_440_ == 0)
{
uint64_t v___x_441_; 
v___x_441_ = lean_uint64_add(v___y_431_, v___y_435_);
v___y_418_ = v___y_432_;
v___y_419_ = v___y_433_;
v___y_420_ = v___y_434_;
v___y_421_ = v___y_437_;
v___y_422_ = v___y_436_;
v___y_423_ = v___y_438_;
v___y_424_ = v___x_441_;
goto v___jp_417_;
}
else
{
v___y_418_ = v___y_432_;
v___y_419_ = v___y_433_;
v___y_420_ = v___y_434_;
v___y_421_ = v___y_437_;
v___y_422_ = v___y_436_;
v___y_423_ = v___y_438_;
v___y_424_ = v___y_431_;
goto v___jp_417_;
}
}
v___jp_442_:
{
uint64_t v___x_450_; uint64_t v___x_451_; uint8_t v___x_452_; 
v___x_450_ = 2ULL;
v___x_451_ = lean_uint64_shift_right(v___y_443_, v___x_450_);
v___x_452_ = lean_uint64_dec_eq(v___x_451_, v___y_446_);
if (v___x_452_ == 0)
{
v___y_430_ = v___y_443_;
v___y_431_ = v___y_449_;
v___y_432_ = v___y_444_;
v___y_433_ = v___y_445_;
v___y_434_ = v___y_446_;
v___y_435_ = v___x_450_;
v___y_436_ = v___y_448_;
v___y_437_ = v___y_447_;
v___y_438_ = v___x_451_;
goto v___jp_429_;
}
else
{
v___y_430_ = v___y_443_;
v___y_431_ = v___y_449_;
v___y_432_ = v___y_444_;
v___y_433_ = v___y_445_;
v___y_434_ = v___y_446_;
v___y_435_ = v___x_450_;
v___y_436_ = v___y_448_;
v___y_437_ = v___y_447_;
v___y_438_ = v___y_443_;
goto v___jp_429_;
}
}
v___jp_453_:
{
uint64_t v___x_463_; uint8_t v___x_464_; 
v___x_463_ = lean_uint64_shift_right(v___y_458_, v___y_455_);
v___x_464_ = lean_uint64_dec_eq(v___x_463_, v___y_457_);
if (v___x_464_ == 0)
{
uint64_t v___x_465_; 
v___x_465_ = lean_uint64_add(v___y_461_, v___y_455_);
v___y_443_ = v___y_462_;
v___y_444_ = v___y_454_;
v___y_445_ = v___y_456_;
v___y_446_ = v___y_457_;
v___y_447_ = v___y_460_;
v___y_448_ = v___y_459_;
v___y_449_ = v___x_465_;
goto v___jp_442_;
}
else
{
v___y_443_ = v___y_462_;
v___y_444_ = v___y_454_;
v___y_445_ = v___y_456_;
v___y_446_ = v___y_457_;
v___y_447_ = v___y_460_;
v___y_448_ = v___y_459_;
v___y_449_ = v___y_461_;
goto v___jp_442_;
}
}
v___jp_466_:
{
uint64_t v___x_474_; uint64_t v___x_475_; uint8_t v___x_476_; 
v___x_474_ = 4ULL;
v___x_475_ = lean_uint64_shift_right(v___y_472_, v___x_474_);
v___x_476_ = lean_uint64_dec_eq(v___x_475_, v___y_469_);
if (v___x_476_ == 0)
{
v___y_454_ = v___y_467_;
v___y_455_ = v___x_474_;
v___y_456_ = v___y_468_;
v___y_457_ = v___y_469_;
v___y_458_ = v___y_472_;
v___y_459_ = v___y_471_;
v___y_460_ = v___y_470_;
v___y_461_ = v___y_473_;
v___y_462_ = v___x_475_;
goto v___jp_453_;
}
else
{
v___y_454_ = v___y_467_;
v___y_455_ = v___x_474_;
v___y_456_ = v___y_468_;
v___y_457_ = v___y_469_;
v___y_458_ = v___y_472_;
v___y_459_ = v___y_471_;
v___y_460_ = v___y_470_;
v___y_461_ = v___y_473_;
v___y_462_ = v___y_472_;
goto v___jp_453_;
}
}
v___jp_477_:
{
uint64_t v___x_487_; uint8_t v___x_488_; 
v___x_487_ = lean_uint64_shift_right(v___y_485_, v___y_479_);
v___x_488_ = lean_uint64_dec_eq(v___x_487_, v___y_481_);
if (v___x_488_ == 0)
{
uint64_t v___x_489_; 
v___x_489_ = lean_uint64_add(v___y_484_, v___y_479_);
v___y_467_ = v___y_478_;
v___y_468_ = v___y_480_;
v___y_469_ = v___y_481_;
v___y_470_ = v___y_483_;
v___y_471_ = v___y_482_;
v___y_472_ = v___y_486_;
v___y_473_ = v___x_489_;
goto v___jp_466_;
}
else
{
v___y_467_ = v___y_478_;
v___y_468_ = v___y_480_;
v___y_469_ = v___y_481_;
v___y_470_ = v___y_483_;
v___y_471_ = v___y_482_;
v___y_472_ = v___y_486_;
v___y_473_ = v___y_484_;
goto v___jp_466_;
}
}
v___jp_490_:
{
uint64_t v___x_498_; uint64_t v___x_499_; uint8_t v___x_500_; 
v___x_498_ = 8ULL;
v___x_499_ = lean_uint64_shift_right(v___y_496_, v___x_498_);
v___x_500_ = lean_uint64_dec_eq(v___x_499_, v___y_493_);
if (v___x_500_ == 0)
{
v___y_478_ = v___y_491_;
v___y_479_ = v___x_498_;
v___y_480_ = v___y_492_;
v___y_481_ = v___y_493_;
v___y_482_ = v___y_495_;
v___y_483_ = v___y_494_;
v___y_484_ = v___y_497_;
v___y_485_ = v___y_496_;
v___y_486_ = v___x_499_;
goto v___jp_477_;
}
else
{
v___y_478_ = v___y_491_;
v___y_479_ = v___x_498_;
v___y_480_ = v___y_492_;
v___y_481_ = v___y_493_;
v___y_482_ = v___y_495_;
v___y_483_ = v___y_494_;
v___y_484_ = v___y_497_;
v___y_485_ = v___y_496_;
v___y_486_ = v___y_496_;
goto v___jp_477_;
}
}
v___jp_501_:
{
uint64_t v___x_511_; uint8_t v___x_512_; 
v___x_511_ = lean_uint64_shift_right(v___y_502_, v___y_504_);
v___x_512_ = lean_uint64_dec_eq(v___x_511_, v___y_507_);
if (v___x_512_ == 0)
{
uint64_t v___x_513_; 
v___x_513_ = lean_uint64_add(v___y_505_, v___y_504_);
v___y_491_ = v___y_503_;
v___y_492_ = v___y_506_;
v___y_493_ = v___y_507_;
v___y_494_ = v___y_509_;
v___y_495_ = v___y_508_;
v___y_496_ = v___y_510_;
v___y_497_ = v___x_513_;
goto v___jp_490_;
}
else
{
v___y_491_ = v___y_503_;
v___y_492_ = v___y_506_;
v___y_493_ = v___y_507_;
v___y_494_ = v___y_509_;
v___y_495_ = v___y_508_;
v___y_496_ = v___y_510_;
v___y_497_ = v___y_505_;
goto v___jp_490_;
}
}
v___jp_514_:
{
uint64_t v___x_522_; uint64_t v___x_523_; uint8_t v___x_524_; 
v___x_522_ = 16ULL;
v___x_523_ = lean_uint64_shift_right(v___y_516_, v___x_522_);
v___x_524_ = lean_uint64_dec_eq(v___x_523_, v___y_518_);
if (v___x_524_ == 0)
{
v___y_502_ = v___y_516_;
v___y_503_ = v___y_515_;
v___y_504_ = v___x_522_;
v___y_505_ = v___y_521_;
v___y_506_ = v___y_517_;
v___y_507_ = v___y_518_;
v___y_508_ = v___y_520_;
v___y_509_ = v___y_519_;
v___y_510_ = v___x_523_;
goto v___jp_501_;
}
else
{
v___y_502_ = v___y_516_;
v___y_503_ = v___y_515_;
v___y_504_ = v___x_522_;
v___y_505_ = v___y_521_;
v___y_506_ = v___y_517_;
v___y_507_ = v___y_518_;
v___y_508_ = v___y_520_;
v___y_509_ = v___y_519_;
v___y_510_ = v___y_516_;
goto v___jp_501_;
}
}
v___jp_525_:
{
uint64_t v___x_533_; uint8_t v___x_534_; 
v___x_533_ = lean_uint64_shift_right(v___y_529_, v___y_531_);
v___x_534_ = lean_uint64_dec_eq(v___x_533_, v___y_528_);
if (v___x_534_ == 0)
{
v___y_515_ = v___y_526_;
v___y_516_ = v___y_532_;
v___y_517_ = v___y_527_;
v___y_518_ = v___y_528_;
v___y_519_ = v___y_530_;
v___y_520_ = v___y_529_;
v___y_521_ = v___y_531_;
goto v___jp_514_;
}
else
{
v___y_515_ = v___y_526_;
v___y_516_ = v___y_532_;
v___y_517_ = v___y_527_;
v___y_518_ = v___y_528_;
v___y_519_ = v___y_530_;
v___y_520_ = v___y_529_;
v___y_521_ = v___y_528_;
goto v___jp_514_;
}
}
v___jp_535_:
{
uint64_t v___x_540_; uint8_t v___x_541_; 
v___x_540_ = 0ULL;
v___x_541_ = lean_uint64_dec_eq(v___y_539_, v___x_540_);
if (v___x_541_ == 0)
{
uint64_t v___x_542_; uint64_t v___x_543_; uint8_t v___x_544_; 
v___x_542_ = 32ULL;
v___x_543_ = lean_uint64_shift_right(v___y_539_, v___x_542_);
v___x_544_ = lean_uint64_dec_eq(v___x_543_, v___x_540_);
if (v___x_544_ == 0)
{
v___y_526_ = v___y_536_;
v___y_527_ = v___y_537_;
v___y_528_ = v___x_540_;
v___y_529_ = v___y_539_;
v___y_530_ = v___y_538_;
v___y_531_ = v___x_542_;
v___y_532_ = v___x_543_;
goto v___jp_525_;
}
else
{
v___y_526_ = v___y_536_;
v___y_527_ = v___y_537_;
v___y_528_ = v___x_540_;
v___y_529_ = v___y_539_;
v___y_530_ = v___y_538_;
v___y_531_ = v___x_542_;
v___y_532_ = v___y_539_;
goto v___jp_525_;
}
}
else
{
if (v___y_537_ == 0)
{
uint32_t v___x_545_; 
v___x_545_ = 0;
return v___x_545_;
}
else
{
uint32_t v___x_546_; 
v___x_546_ = 2147483648;
return v___x_546_;
}
}
}
v___jp_547_:
{
uint64_t v___x_554_; uint64_t v___x_555_; uint64_t v___x_556_; uint8_t v___x_557_; 
v___x_554_ = lean_uint64_mul(v___y_549_, v___y_551_);
v___x_555_ = lean_uint64_add(v___y_550_, v___y_553_);
v___x_556_ = 281474976710656ULL;
v___x_557_ = lean_uint64_dec_lt(v___x_554_, v___x_556_);
if (v___x_557_ == 0)
{
v___y_536_ = v___y_548_;
v___y_537_ = v___y_552_;
v___y_538_ = v___x_555_;
v___y_539_ = v___x_554_;
goto v___jp_535_;
}
else
{
uint64_t v___x_558_; uint8_t v___x_559_; 
v___x_558_ = 123ULL;
v___x_559_ = lean_uint64_dec_le(v___x_555_, v___x_558_);
if (v___x_559_ == 0)
{
v___y_536_ = v___y_548_;
v___y_537_ = v___y_552_;
v___y_538_ = v___x_555_;
v___y_539_ = v___x_554_;
goto v___jp_535_;
}
else
{
uint64_t v___x_560_; uint8_t v___x_561_; 
v___x_560_ = 0ULL;
v___x_561_ = lean_uint64_dec_eq(v___x_554_, v___x_560_);
if (v___x_561_ == 0)
{
uint64_t v___x_562_; uint64_t v___x_563_; uint8_t v___x_564_; 
v___x_562_ = 149ULL;
v___x_563_ = lean_uint64_sub(v___x_562_, v___x_555_);
v___x_564_ = lean_uint64_dec_eq(v___x_563_, v___x_560_);
if (v___x_564_ == 0)
{
uint64_t v___x_565_; uint8_t v___x_566_; 
v___x_565_ = 64ULL;
v___x_566_ = lean_uint64_dec_lt(v___x_563_, v___x_565_);
if (v___x_566_ == 0)
{
uint8_t v___x_567_; 
v___x_567_ = lean_uint64_dec_eq(v___x_563_, v___x_565_);
if (v___x_567_ == 0)
{
v___y_220_ = v___y_548_;
v___y_221_ = v___x_560_;
v___y_222_ = v___y_552_;
v___y_223_ = v___x_560_;
goto v___jp_219_;
}
else
{
uint64_t v___x_568_; uint8_t v___x_569_; 
v___x_568_ = 9223372036854775808ULL;
v___x_569_ = lean_uint64_dec_lt(v___x_568_, v___x_554_);
if (v___x_569_ == 0)
{
v___y_220_ = v___y_548_;
v___y_221_ = v___x_560_;
v___y_222_ = v___y_552_;
v___y_223_ = v___x_560_;
goto v___jp_219_;
}
else
{
uint64_t v___x_570_; 
v___x_570_ = 1ULL;
v___y_220_ = v___y_548_;
v___y_221_ = v___x_560_;
v___y_222_ = v___y_552_;
v___y_223_ = v___x_570_;
goto v___jp_219_;
}
}
}
else
{
uint64_t v_quotient_571_; uint64_t v___x_572_; uint64_t v___x_573_; uint64_t v___x_574_; uint64_t v_remainder_575_; uint64_t v___x_576_; uint64_t v_half_577_; uint8_t v___x_578_; 
v_quotient_571_ = lean_uint64_shift_right(v___x_554_, v___x_563_);
v___x_572_ = 1ULL;
v___x_573_ = lean_uint64_shift_left(v___x_572_, v___x_563_);
v___x_574_ = lean_uint64_sub(v___x_573_, v___x_572_);
v_remainder_575_ = lean_uint64_land(v___x_554_, v___x_574_);
v___x_576_ = lean_uint64_sub(v___x_563_, v___x_572_);
v_half_577_ = lean_uint64_shift_left(v___x_572_, v___x_576_);
v___x_578_ = lean_uint64_dec_lt(v_remainder_575_, v_half_577_);
if (v___x_578_ == 0)
{
uint8_t v___x_579_; 
v___x_579_ = lean_uint64_dec_lt(v_half_577_, v_remainder_575_);
if (v___x_579_ == 0)
{
uint64_t v___x_580_; uint8_t v___x_581_; 
v___x_580_ = lean_uint64_land(v_quotient_571_, v___x_572_);
v___x_581_ = lean_uint64_dec_eq(v___x_580_, v___x_560_);
if (v___x_581_ == 0)
{
uint64_t v___x_582_; 
v___x_582_ = lean_uint64_add(v_quotient_571_, v___x_572_);
v___y_220_ = v___y_548_;
v___y_221_ = v___x_560_;
v___y_222_ = v___y_552_;
v___y_223_ = v___x_582_;
goto v___jp_219_;
}
else
{
v___y_220_ = v___y_548_;
v___y_221_ = v___x_560_;
v___y_222_ = v___y_552_;
v___y_223_ = v_quotient_571_;
goto v___jp_219_;
}
}
else
{
uint64_t v___x_583_; 
v___x_583_ = lean_uint64_add(v_quotient_571_, v___x_572_);
v___y_220_ = v___y_548_;
v___y_221_ = v___x_560_;
v___y_222_ = v___y_552_;
v___y_223_ = v___x_583_;
goto v___jp_219_;
}
}
else
{
v___y_220_ = v___y_548_;
v___y_221_ = v___x_560_;
v___y_222_ = v___y_552_;
v___y_223_ = v_quotient_571_;
goto v___jp_219_;
}
}
}
else
{
v___y_220_ = v___y_548_;
v___y_221_ = v___x_560_;
v___y_222_ = v___y_552_;
v___y_223_ = v___x_554_;
goto v___jp_219_;
}
}
else
{
if (v___y_552_ == 0)
{
uint32_t v___x_584_; 
v___x_584_ = 0;
return v___x_584_;
}
else
{
uint32_t v___x_585_; 
v___x_585_ = 2147483648;
return v___x_585_;
}
}
}
}
}
v___jp_588_:
{
if (v___y_590_ == 0)
{
float v___x_591_; float v___x_592_; 
v___x_591_ = lean_float32_of_bits(v___y_183_);
v___x_592_ = lean_float32_mul(v___y_589_, v___x_591_);
v___y_289_ = v___x_592_;
goto v___jp_288_;
}
else
{
uint32_t v___x_593_; uint32_t v___x_594_; uint32_t v___x_595_; uint32_t v___x_596_; float v___x_597_; lean_object* v___x_598_; lean_object* v___x_599_; double v___x_600_; float v___x_601_; float v___x_602_; float v___x_603_; 
v___x_593_ = 8388607;
v___x_594_ = lean_uint32_land(v___y_183_, v___x_593_);
v___x_595_ = 8388608;
v___x_596_ = lean_uint32_lor(v___x_594_, v___x_595_);
v___x_597_ = lean_uint32_to_float32(v___x_596_);
v___x_598_ = lp_competition_R19CompactScales_packed;
v___x_599_ = lean_uint32_to_nat(v___x_587_);
v___x_600_ = lean_float_array_fget(v___x_598_, v___x_599_);
lean_dec(v___x_599_);
v___x_601_ = lean_float_to_float32(v___x_600_);
v___x_602_ = lean_float32_mul(v___x_597_, v___x_601_);
v___x_603_ = lean_float32_mul(v___y_589_, v___x_602_);
v___y_289_ = v___x_603_;
goto v___jp_288_;
}
}
v___jp_604_:
{
uint32_t v___x_606_; uint32_t v_a_607_; uint32_t v___x_608_; uint32_t v___x_609_; uint32_t v___x_610_; uint8_t v___x_611_; 
v___x_606_ = 2147483647;
v_a_607_ = lean_uint32_land(v___y_183_, v___x_606_);
v___x_608_ = 201326591;
v___x_609_ = 1;
v___x_610_ = lean_uint32_sub(v_a_607_, v___x_609_);
v___x_611_ = lean_uint32_dec_le(v___x_608_, v___x_610_);
if (v___x_611_ == 0)
{
v___y_589_ = v___y_605_;
v___y_590_ = v___x_611_;
goto v___jp_588_;
}
else
{
uint32_t v___x_612_; uint8_t v___x_613_; 
v___x_612_ = 2139095040;
v___x_613_ = lean_uint32_dec_lt(v_a_607_, v___x_612_);
v___y_589_ = v___y_605_;
v___y_590_ = v___x_613_;
goto v___jp_588_;
}
}
v___jp_614_:
{
if (v___y_615_ == 0)
{
float v___x_616_; 
v___x_616_ = lean_float32_of_bits(v___y_182_);
v___y_605_ = v___x_616_;
goto v___jp_604_;
}
else
{
uint32_t v___x_617_; uint32_t v___x_618_; uint32_t v___x_619_; uint32_t v___x_620_; float v___x_621_; lean_object* v___x_622_; lean_object* v___x_623_; double v___x_624_; float v___x_625_; float v___x_626_; 
v___x_617_ = 8388607;
v___x_618_ = lean_uint32_land(v___y_182_, v___x_617_);
v___x_619_ = 8388608;
v___x_620_ = lean_uint32_lor(v___x_618_, v___x_619_);
v___x_621_ = lean_uint32_to_float32(v___x_620_);
v___x_622_ = lp_competition_R19CompactScales_packed;
v___x_623_ = lean_uint32_to_nat(v___x_302_);
v___x_624_ = lean_float_array_fget(v___x_622_, v___x_623_);
lean_dec(v___x_623_);
v___x_625_ = lean_float_to_float32(v___x_624_);
v___x_626_ = lean_float32_mul(v___x_621_, v___x_625_);
v___y_605_ = v___x_626_;
goto v___jp_604_;
}
}
v___jp_627_:
{
if (v___y_629_ == 0)
{
float v___x_630_; float v___x_631_; 
v___x_630_ = lean_float32_of_bits(v___y_183_);
v___x_631_ = lean_float32_mul(v___y_628_, v___x_630_);
v___y_289_ = v___x_631_;
goto v___jp_288_;
}
else
{
uint32_t v___x_632_; uint32_t v___x_633_; uint32_t v___x_634_; uint32_t v___x_635_; float v___x_636_; lean_object* v___x_637_; lean_object* v___x_638_; lean_object* v___x_639_; float v___x_640_; float v___x_641_; float v___x_642_; 
v___x_632_ = 8388607;
v___x_633_ = lean_uint32_land(v___y_183_, v___x_632_);
v___x_634_ = 8388608;
v___x_635_ = lean_uint32_lor(v___x_633_, v___x_634_);
v___x_636_ = lean_uint32_to_float32(v___x_635_);
v___x_637_ = lp_competition_R2W01b_scaleTable;
v___x_638_ = lean_uint32_to_nat(v___x_587_);
v___x_639_ = lean_array_fget_borrowed(v___x_637_, v___x_638_);
lean_dec(v___x_638_);
v___x_640_ = lean_unbox_float32(v___x_639_);
v___x_641_ = lean_float32_mul(v___x_636_, v___x_640_);
v___x_642_ = lean_float32_mul(v___y_628_, v___x_641_);
v___y_289_ = v___x_642_;
goto v___jp_288_;
}
}
v___jp_643_:
{
uint32_t v___x_645_; uint32_t v_a_646_; uint32_t v___x_647_; uint32_t v___x_648_; uint32_t v___x_649_; uint8_t v___x_650_; 
v___x_645_ = 2147483647;
v_a_646_ = lean_uint32_land(v___y_183_, v___x_645_);
v___x_647_ = 201326591;
v___x_648_ = 1;
v___x_649_ = lean_uint32_sub(v_a_646_, v___x_648_);
v___x_650_ = lean_uint32_dec_le(v___x_647_, v___x_649_);
if (v___x_650_ == 0)
{
v___y_628_ = v___y_644_;
v___y_629_ = v___x_650_;
goto v___jp_627_;
}
else
{
uint32_t v___x_651_; uint8_t v___x_652_; 
v___x_651_ = 2139095040;
v___x_652_ = lean_uint32_dec_lt(v_a_646_, v___x_651_);
v___y_628_ = v___y_644_;
v___y_629_ = v___x_652_;
goto v___jp_627_;
}
}
v___jp_653_:
{
if (v___y_654_ == 0)
{
float v___x_655_; 
v___x_655_ = lean_float32_of_bits(v___y_182_);
v___y_644_ = v___x_655_;
goto v___jp_643_;
}
else
{
uint32_t v___x_656_; uint32_t v___x_657_; uint32_t v___x_658_; uint32_t v___x_659_; float v___x_660_; lean_object* v___x_661_; lean_object* v___x_662_; lean_object* v___x_663_; float v___x_664_; float v___x_665_; 
v___x_656_ = 8388607;
v___x_657_ = lean_uint32_land(v___y_182_, v___x_656_);
v___x_658_ = 8388608;
v___x_659_ = lean_uint32_lor(v___x_657_, v___x_658_);
v___x_660_ = lean_uint32_to_float32(v___x_659_);
v___x_661_ = lp_competition_R2W01b_scaleTable;
v___x_662_ = lean_uint32_to_nat(v___x_302_);
v___x_663_ = lean_array_fget_borrowed(v___x_661_, v___x_662_);
lean_dec(v___x_662_);
v___x_664_ = lean_unbox_float32(v___x_663_);
v___x_665_ = lean_float32_mul(v___x_660_, v___x_664_);
v___y_644_ = v___x_665_;
goto v___jp_643_;
}
}
v___jp_667_:
{
uint64_t v___x_673_; uint64_t v___x_674_; uint8_t v___x_675_; 
v___x_673_ = lean_uint32_to_uint64(v_ey_666_);
v___x_674_ = 0ULL;
v___x_675_ = lean_uint64_dec_eq(v___x_673_, v___x_674_);
if (v___x_675_ == 0)
{
uint64_t v___x_676_; uint64_t v___x_677_; 
v___x_676_ = 1ULL;
v___x_677_ = lean_uint64_sub(v___x_673_, v___x_676_);
v___y_548_ = v___y_669_;
v___y_549_ = v___y_668_;
v___y_550_ = v___y_672_;
v___y_551_ = v___y_670_;
v___y_552_ = v___y_671_;
v___y_553_ = v___x_677_;
goto v___jp_547_;
}
else
{
v___y_548_ = v___y_669_;
v___y_549_ = v___y_668_;
v___y_550_ = v___y_672_;
v___y_551_ = v___y_670_;
v___y_552_ = v___y_671_;
v___y_553_ = v___x_674_;
goto v___jp_547_;
}
}
v___jp_678_:
{
uint64_t v___x_683_; uint64_t v___x_684_; uint8_t v___x_685_; 
v___x_683_ = lean_uint32_to_uint64(v_ex_586_);
v___x_684_ = 0ULL;
v___x_685_ = lean_uint64_dec_eq(v___x_683_, v___x_684_);
if (v___x_685_ == 0)
{
uint64_t v___x_686_; uint64_t v___x_687_; 
v___x_686_ = 1ULL;
v___x_687_ = lean_uint64_sub(v___x_683_, v___x_686_);
v___y_668_ = v___y_680_;
v___y_669_ = v___y_679_;
v___y_670_ = v___y_682_;
v___y_671_ = v___y_681_;
v___y_672_ = v___x_687_;
goto v___jp_667_;
}
else
{
v___y_668_ = v___y_680_;
v___y_669_ = v___y_679_;
v___y_670_ = v___y_682_;
v___y_671_ = v___y_681_;
v___y_672_ = v___x_684_;
goto v___jp_667_;
}
}
v___jp_688_:
{
uint32_t v___x_693_; uint8_t v___x_694_; 
v___x_693_ = 0;
v___x_694_ = lean_uint32_dec_eq(v_ey_666_, v___x_693_);
if (v___x_694_ == 0)
{
uint64_t v___x_695_; uint64_t v___x_696_; uint64_t v___x_697_; 
v___x_695_ = lean_uint32_to_uint64(v___y_691_);
v___x_696_ = 8388608ULL;
v___x_697_ = lean_uint64_lor(v___x_695_, v___x_696_);
v___y_679_ = v___y_689_;
v___y_680_ = v___y_692_;
v___y_681_ = v___y_690_;
v___y_682_ = v___x_697_;
goto v___jp_678_;
}
else
{
uint64_t v___x_698_; 
v___x_698_ = lean_uint32_to_uint64(v___y_691_);
v___y_679_ = v___y_689_;
v___y_680_ = v___y_692_;
v___y_681_ = v___y_690_;
v___y_682_ = v___x_698_;
goto v___jp_678_;
}
}
v___jp_699_:
{
uint32_t v___x_701_; uint32_t v_xFraction_702_; uint32_t v_yFraction_703_; uint32_t v___x_704_; uint8_t v___x_705_; 
v___x_701_ = 8388607;
v_xFraction_702_ = lean_uint32_land(v___y_182_, v___x_701_);
v_yFraction_703_ = lean_uint32_land(v___y_183_, v___x_701_);
v___x_704_ = 0;
v___x_705_ = lean_uint32_dec_eq(v_ex_586_, v___x_704_);
if (v___x_705_ == 0)
{
uint64_t v___x_706_; uint64_t v___x_707_; uint64_t v___x_708_; 
v___x_706_ = lean_uint32_to_uint64(v_xFraction_702_);
v___x_707_ = 8388608ULL;
v___x_708_ = lean_uint64_lor(v___x_706_, v___x_707_);
v___y_689_ = v___x_701_;
v___y_690_ = v___y_700_;
v___y_691_ = v_yFraction_703_;
v___y_692_ = v___x_708_;
goto v___jp_688_;
}
else
{
uint64_t v___x_709_; 
v___x_709_ = lean_uint32_to_uint64(v_xFraction_702_);
v___y_689_ = v___x_701_;
v___y_690_ = v___y_700_;
v___y_691_ = v_yFraction_703_;
v___y_692_ = v___x_709_;
goto v___jp_688_;
}
}
v___jp_713_:
{
if (v___y_715_ == 0)
{
v___y_700_ = v___x_712_;
goto v___jp_699_;
}
else
{
v___y_700_ = v___y_714_;
goto v___jp_699_;
}
}
v___jp_716_:
{
if (v___y_717_ == 0)
{
if (v___y_719_ == 0)
{
v___y_714_ = v___y_718_;
v___y_715_ = v___x_712_;
goto v___jp_713_;
}
else
{
v___y_700_ = v___x_712_;
goto v___jp_699_;
}
}
else
{
v___y_714_ = v___y_718_;
v___y_715_ = v___y_719_;
goto v___jp_713_;
}
}
v___jp_720_:
{
uint32_t v___x_723_; uint32_t v___x_724_; uint32_t v___x_725_; uint8_t v___x_726_; 
v___x_723_ = 2147483648;
v___x_724_ = lean_uint32_land(v___y_183_, v___x_723_);
v___x_725_ = 0;
v___x_726_ = lean_uint32_dec_eq(v___x_724_, v___x_725_);
if (v___x_726_ == 0)
{
v___y_717_ = v___y_722_;
v___y_718_ = v___y_721_;
v___y_719_ = v___x_712_;
goto v___jp_716_;
}
else
{
v___y_717_ = v___y_722_;
v___y_718_ = v___y_721_;
v___y_719_ = v___y_721_;
goto v___jp_716_;
}
}
v___jp_727_:
{
if (v___y_728_ == 0)
{
uint32_t v___x_729_; uint32_t v___x_730_; uint32_t v___x_731_; uint8_t v___x_732_; 
v___x_729_ = 2147483648;
v___x_730_ = lean_uint32_land(v___y_182_, v___x_729_);
v___x_731_ = 0;
v___x_732_ = lean_uint32_dec_eq(v___x_730_, v___x_731_);
if (v___x_732_ == 0)
{
v___y_721_ = v___y_728_;
v___y_722_ = v___x_712_;
goto v___jp_720_;
}
else
{
v___y_721_ = v___y_728_;
v___y_722_ = v___y_728_;
goto v___jp_720_;
}
}
else
{
lean_object* v___x_733_; lean_object* v___x_734_; lean_object* v___x_735_; uint32_t v___x_736_; 
v___x_733_ = lean_uint32_to_nat(v___y_182_);
v___x_734_ = lean_uint32_to_nat(v___y_183_);
v___x_735_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_733_, v___x_734_);
v___x_736_ = lean_uint32_of_nat(v___x_735_);
lean_dec(v___x_735_);
return v___x_736_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___y_760_, lean_object* v___y_761_){
_start:
{
uint32_t v___y_5273__boxed_762_; uint32_t v___y_5274__boxed_763_; uint32_t v_res_764_; lean_object* v_r_765_; 
v___y_5273__boxed_762_ = lean_unbox_uint32(v___y_760_);
lean_dec(v___y_760_);
v___y_5274__boxed_763_ = lean_unbox_uint32(v___y_761_);
lean_dec(v___y_761_);
v_res_764_ = lp_competition_main___lam__1(v___y_5273__boxed_762_, v___y_5274__boxed_763_);
v_r_765_ = lean_box_uint32(v_res_764_);
return v_r_765_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint32_t v___y_766_, uint32_t v___y_767_){
_start:
{
uint32_t v___y_769_; uint32_t v___y_773_; uint32_t v___y_777_; uint32_t v___y_778_; uint32_t v___y_779_; uint64_t v___y_783_; uint32_t v___y_784_; uint8_t v___y_785_; uint64_t v___y_786_; uint32_t v___y_798_; uint32_t v___y_799_; uint32_t v___y_800_; uint32_t v___y_804_; uint64_t v___y_805_; uint8_t v___y_806_; uint64_t v___y_807_; uint8_t v___y_819_; uint8_t v___y_835_; uint8_t v___y_849_; uint8_t v___y_866_; float v___y_873_; uint32_t v___x_885_; uint32_t v___x_886_; uint32_t v___x_887_; uint32_t v___y_889_; uint32_t v___y_890_; uint32_t v___y_891_; uint32_t v___y_892_; uint32_t v___y_899_; uint8_t v___y_900_; uint32_t v___y_901_; uint32_t v___y_902_; uint64_t v___y_906_; uint32_t v___y_907_; uint64_t v___y_908_; uint8_t v___y_909_; uint64_t v___y_910_; uint64_t v___y_920_; uint64_t v___y_921_; uint8_t v___y_922_; uint32_t v___y_923_; uint8_t v___y_924_; uint64_t v___y_925_; uint64_t v___y_932_; uint64_t v___y_933_; uint32_t v___y_934_; uint8_t v___y_935_; uint64_t v___y_936_; uint64_t v___y_942_; uint32_t v___y_943_; uint64_t v___y_944_; uint64_t v___y_945_; uint8_t v___y_946_; uint64_t v___y_947_; uint64_t v___y_1002_; uint32_t v___y_1003_; uint64_t v___y_1004_; uint64_t v___y_1005_; uint64_t v___y_1006_; uint8_t v___y_1007_; uint64_t v___y_1008_; uint64_t v___y_1014_; uint64_t v___y_1015_; uint32_t v___y_1016_; uint64_t v___y_1017_; uint64_t v___y_1018_; uint64_t v___y_1019_; uint64_t v___y_1020_; uint8_t v___y_1021_; uint64_t v___y_1022_; uint64_t v___y_1027_; uint64_t v___y_1028_; uint32_t v___y_1029_; uint64_t v___y_1030_; uint64_t v___y_1031_; uint8_t v___y_1032_; uint64_t v___y_1033_; uint64_t v___y_1038_; uint64_t v___y_1039_; uint64_t v___y_1040_; uint32_t v___y_1041_; uint64_t v___y_1042_; uint64_t v___y_1043_; uint8_t v___y_1044_; uint64_t v___y_1045_; uint64_t v___y_1046_; uint64_t v___y_1051_; uint32_t v___y_1052_; uint64_t v___y_1053_; uint64_t v___y_1054_; uint64_t v___y_1055_; uint8_t v___y_1056_; uint64_t v___y_1057_; uint64_t v___y_1062_; uint64_t v___y_1063_; uint32_t v___y_1064_; uint64_t v___y_1065_; uint64_t v___y_1066_; uint64_t v___y_1067_; uint64_t v___y_1068_; uint8_t v___y_1069_; uint64_t v___y_1070_; uint64_t v___y_1075_; uint32_t v___y_1076_; uint64_t v___y_1077_; uint64_t v___y_1078_; uint64_t v___y_1079_; uint8_t v___y_1080_; uint64_t v___y_1081_; uint64_t v___y_1086_; uint64_t v___y_1087_; uint64_t v___y_1088_; uint64_t v___y_1089_; uint32_t v___y_1090_; uint64_t v___y_1091_; uint64_t v___y_1092_; uint8_t v___y_1093_; uint64_t v___y_1094_; uint64_t v___y_1099_; uint64_t v___y_1100_; uint32_t v___y_1101_; uint64_t v___y_1102_; uint64_t v___y_1103_; uint8_t v___y_1104_; uint64_t v___y_1105_; uint64_t v___y_1110_; uint64_t v___y_1111_; uint32_t v___y_1112_; uint64_t v___y_1113_; uint64_t v___y_1114_; uint8_t v___y_1115_; uint64_t v___y_1116_; uint32_t v___y_1120_; uint64_t v___y_1121_; uint64_t v___y_1122_; uint8_t v___y_1123_; uint64_t v___y_1132_; uint64_t v___y_1133_; uint32_t v___y_1134_; uint64_t v___y_1135_; uint8_t v___y_1136_; uint64_t v___y_1137_; uint32_t v_ex_1170_; uint32_t v___x_1171_; float v___y_1173_; uint8_t v___y_1174_; float v___y_1189_; uint8_t v___y_1199_; float v___y_1212_; uint8_t v___y_1213_; float v___y_1228_; uint8_t v___y_1238_; uint32_t v_ey_1250_; uint64_t v___y_1252_; uint64_t v___y_1253_; uint32_t v___y_1254_; uint8_t v___y_1255_; uint64_t v___y_1256_; uint64_t v___y_1263_; uint32_t v___y_1264_; uint8_t v___y_1265_; uint64_t v___y_1266_; uint32_t v___y_1273_; uint32_t v___y_1274_; uint8_t v___y_1275_; uint64_t v___y_1276_; uint8_t v___y_1284_; uint32_t v___x_1294_; uint32_t v___x_1295_; uint8_t v___x_1296_; uint8_t v___y_1298_; uint8_t v___y_1299_; uint8_t v___y_1301_; uint8_t v___y_1302_; uint8_t v___y_1303_; uint8_t v___y_1305_; uint8_t v___y_1306_; uint8_t v___y_1312_; 
v___x_885_ = 23;
v___x_886_ = lean_uint32_shift_right(v___y_766_, v___x_885_);
v___x_887_ = 255;
v_ex_1170_ = lean_uint32_land(v___x_886_, v___x_887_);
v___x_1171_ = lean_uint32_shift_right(v___y_767_, v___x_885_);
v_ey_1250_ = lean_uint32_land(v___x_1171_, v___x_887_);
v___x_1294_ = lean_uint32_add(v_ex_1170_, v_ey_1250_);
v___x_1295_ = 128;
v___x_1296_ = lean_uint32_dec_lt(v___x_1294_, v___x_1295_);
if (v___x_1296_ == 0)
{
uint8_t v___x_1321_; 
v___x_1321_ = lp_competition_R19CompactScales_valid;
if (v___x_1321_ == 0)
{
uint32_t v___x_1322_; uint32_t v_a_1323_; uint32_t v___x_1324_; uint32_t v___x_1325_; uint32_t v___x_1326_; uint8_t v___x_1327_; 
v___x_1322_ = 2147483647;
v_a_1323_ = lean_uint32_land(v___y_766_, v___x_1322_);
v___x_1324_ = 201326591;
v___x_1325_ = 1;
v___x_1326_ = lean_uint32_sub(v_a_1323_, v___x_1325_);
v___x_1327_ = lean_uint32_dec_le(v___x_1324_, v___x_1326_);
if (v___x_1327_ == 0)
{
v___y_1238_ = v___x_1327_;
goto v___jp_1237_;
}
else
{
uint32_t v___x_1328_; uint8_t v___x_1329_; 
v___x_1328_ = 2139095040;
v___x_1329_ = lean_uint32_dec_lt(v_a_1323_, v___x_1328_);
v___y_1238_ = v___x_1329_;
goto v___jp_1237_;
}
}
else
{
uint32_t v___x_1330_; uint32_t v_a_1331_; uint32_t v___x_1332_; uint32_t v___x_1333_; uint32_t v___x_1334_; uint8_t v___x_1335_; 
v___x_1330_ = 2147483647;
v_a_1331_ = lean_uint32_land(v___y_766_, v___x_1330_);
v___x_1332_ = 201326591;
v___x_1333_ = 1;
v___x_1334_ = lean_uint32_sub(v_a_1331_, v___x_1333_);
v___x_1335_ = lean_uint32_dec_le(v___x_1332_, v___x_1334_);
if (v___x_1335_ == 0)
{
v___y_1199_ = v___x_1335_;
goto v___jp_1198_;
}
else
{
uint32_t v___x_1336_; uint8_t v___x_1337_; 
v___x_1336_ = 2139095040;
v___x_1337_ = lean_uint32_dec_lt(v_a_1331_, v___x_1336_);
v___y_1199_ = v___x_1337_;
goto v___jp_1198_;
}
}
}
else
{
uint32_t v___x_1338_; uint32_t v___x_1339_; uint32_t v___x_1340_; uint8_t v___x_1341_; 
v___x_1338_ = 4278190080;
v___x_1339_ = 1;
v___x_1340_ = lean_uint32_shift_left(v___y_766_, v___x_1339_);
v___x_1341_ = lean_uint32_dec_le(v___x_1338_, v___x_1340_);
if (v___x_1341_ == 0)
{
uint32_t v___x_1342_; uint8_t v___x_1343_; 
v___x_1342_ = lean_uint32_shift_left(v___y_767_, v___x_1339_);
v___x_1343_ = lean_uint32_dec_le(v___x_1338_, v___x_1342_);
v___y_1312_ = v___x_1343_;
goto v___jp_1311_;
}
else
{
v___y_1312_ = v___x_1341_;
goto v___jp_1311_;
}
}
v___jp_768_:
{
uint32_t v___x_770_; uint32_t v___x_771_; 
v___x_770_ = 8388608;
v___x_771_ = lean_uint32_lor(v___y_769_, v___x_770_);
return v___x_771_;
}
v___jp_772_:
{
uint32_t v___x_774_; uint32_t v___x_775_; 
v___x_774_ = 8388608;
v___x_775_ = lean_uint32_lor(v___y_773_, v___x_774_);
return v___x_775_;
}
v___jp_776_:
{
uint32_t v___x_780_; uint32_t v___x_781_; 
v___x_780_ = lean_uint32_land(v___y_778_, v___y_777_);
v___x_781_ = lean_uint32_lor(v___y_779_, v___x_780_);
return v___x_781_;
}
v___jp_782_:
{
uint8_t v___x_787_; 
v___x_787_ = lean_uint64_dec_eq(v___y_786_, v___y_783_);
if (v___x_787_ == 0)
{
uint64_t v___x_788_; uint8_t v___x_789_; 
v___x_788_ = 8388608ULL;
v___x_789_ = lean_uint64_dec_eq(v___y_786_, v___x_788_);
if (v___x_789_ == 0)
{
uint32_t v___x_790_; 
v___x_790_ = lean_uint64_to_uint32(v___y_786_);
if (v___y_785_ == 0)
{
uint32_t v___x_791_; 
v___x_791_ = 0;
v___y_777_ = v___y_784_;
v___y_778_ = v___x_790_;
v___y_779_ = v___x_791_;
goto v___jp_776_;
}
else
{
uint32_t v___x_792_; 
v___x_792_ = 2147483648;
v___y_777_ = v___y_784_;
v___y_778_ = v___x_790_;
v___y_779_ = v___x_792_;
goto v___jp_776_;
}
}
else
{
if (v___y_785_ == 0)
{
uint32_t v___x_793_; 
v___x_793_ = 0;
v___y_773_ = v___x_793_;
goto v___jp_772_;
}
else
{
uint32_t v___x_794_; 
v___x_794_ = 2147483648;
v___y_773_ = v___x_794_;
goto v___jp_772_;
}
}
}
else
{
if (v___y_785_ == 0)
{
uint32_t v___x_795_; 
v___x_795_ = 0;
return v___x_795_;
}
else
{
uint32_t v___x_796_; 
v___x_796_ = 2147483648;
return v___x_796_;
}
}
}
v___jp_797_:
{
uint32_t v___x_801_; uint32_t v___x_802_; 
v___x_801_ = lean_uint32_land(v___y_799_, v___y_798_);
v___x_802_ = lean_uint32_lor(v___y_800_, v___x_801_);
return v___x_802_;
}
v___jp_803_:
{
uint8_t v___x_808_; 
v___x_808_ = lean_uint64_dec_eq(v___y_807_, v___y_805_);
if (v___x_808_ == 0)
{
uint64_t v___x_809_; uint8_t v___x_810_; 
v___x_809_ = 8388608ULL;
v___x_810_ = lean_uint64_dec_eq(v___y_807_, v___x_809_);
if (v___x_810_ == 0)
{
uint32_t v___x_811_; 
v___x_811_ = lean_uint64_to_uint32(v___y_807_);
if (v___y_806_ == 0)
{
uint32_t v___x_812_; 
v___x_812_ = 0;
v___y_798_ = v___y_804_;
v___y_799_ = v___x_811_;
v___y_800_ = v___x_812_;
goto v___jp_797_;
}
else
{
uint32_t v___x_813_; 
v___x_813_ = 2147483648;
v___y_798_ = v___y_804_;
v___y_799_ = v___x_811_;
v___y_800_ = v___x_813_;
goto v___jp_797_;
}
}
else
{
if (v___y_806_ == 0)
{
uint32_t v___x_814_; 
v___x_814_ = 0;
v___y_769_ = v___x_814_;
goto v___jp_768_;
}
else
{
uint32_t v___x_815_; 
v___x_815_ = 2147483648;
v___y_769_ = v___x_815_;
goto v___jp_768_;
}
}
}
else
{
if (v___y_806_ == 0)
{
uint32_t v___x_816_; 
v___x_816_ = 0;
return v___x_816_;
}
else
{
uint32_t v___x_817_; 
v___x_817_ = 2147483648;
return v___x_817_;
}
}
}
v___jp_818_:
{
if (v___y_819_ == 0)
{
uint32_t v___x_820_; 
v___x_820_ = lp_competition_Submission_FastMul_mul(v___y_766_, v___y_767_);
return v___x_820_;
}
else
{
uint32_t v___x_821_; uint32_t v___x_822_; 
v___x_821_ = 4194304;
v___x_822_ = lean_uint32_lor(v___y_767_, v___x_821_);
return v___x_822_;
}
}
v___jp_823_:
{
uint32_t v___x_824_; uint32_t v___x_825_; uint32_t v___x_826_; uint32_t v___x_827_; uint8_t v___x_828_; 
v___x_824_ = 23;
v___x_825_ = lean_uint32_shift_right(v___y_767_, v___x_824_);
v___x_826_ = 255;
v___x_827_ = lean_uint32_land(v___x_825_, v___x_826_);
v___x_828_ = lean_uint32_dec_eq(v___x_827_, v___x_826_);
if (v___x_828_ == 0)
{
v___y_819_ = v___x_828_;
goto v___jp_818_;
}
else
{
uint32_t v___x_829_; uint32_t v___x_830_; uint32_t v___x_831_; uint8_t v___x_832_; 
v___x_829_ = 8388607;
v___x_830_ = lean_uint32_land(v___y_767_, v___x_829_);
v___x_831_ = 0;
v___x_832_ = lean_uint32_dec_eq(v___x_830_, v___x_831_);
if (v___x_832_ == 0)
{
v___y_819_ = v___x_828_;
goto v___jp_818_;
}
else
{
uint32_t v___x_833_; 
v___x_833_ = lp_competition_Submission_FastMul_mul(v___y_766_, v___y_767_);
return v___x_833_;
}
}
}
v___jp_834_:
{
if (v___y_835_ == 0)
{
goto v___jp_823_;
}
else
{
uint32_t v___x_836_; uint32_t v___x_837_; 
v___x_836_ = 4194304;
v___x_837_ = lean_uint32_lor(v___y_766_, v___x_836_);
return v___x_837_;
}
}
v___jp_838_:
{
uint32_t v___x_839_; uint32_t v___x_840_; uint32_t v___x_841_; uint32_t v___x_842_; uint8_t v___x_843_; 
v___x_839_ = 23;
v___x_840_ = lean_uint32_shift_right(v___y_766_, v___x_839_);
v___x_841_ = 255;
v___x_842_ = lean_uint32_land(v___x_840_, v___x_841_);
v___x_843_ = lean_uint32_dec_eq(v___x_842_, v___x_841_);
if (v___x_843_ == 0)
{
v___y_835_ = v___x_843_;
goto v___jp_834_;
}
else
{
uint32_t v___x_844_; uint32_t v___x_845_; uint32_t v___x_846_; uint8_t v___x_847_; 
v___x_844_ = 8388607;
v___x_845_ = lean_uint32_land(v___y_766_, v___x_844_);
v___x_846_ = 0;
v___x_847_ = lean_uint32_dec_eq(v___x_845_, v___x_846_);
if (v___x_847_ == 0)
{
v___y_835_ = v___x_843_;
goto v___jp_834_;
}
else
{
goto v___jp_823_;
}
}
}
v___jp_848_:
{
if (v___y_849_ == 0)
{
goto v___jp_838_;
}
else
{
uint32_t v___x_850_; uint32_t v___x_851_; uint32_t v___x_852_; uint8_t v___x_853_; 
v___x_850_ = 4194304;
v___x_851_ = lean_uint32_land(v___y_767_, v___x_850_);
v___x_852_ = 0;
v___x_853_ = lean_uint32_dec_eq(v___x_851_, v___x_852_);
if (v___x_853_ == 0)
{
goto v___jp_838_;
}
else
{
uint32_t v___x_854_; 
v___x_854_ = lean_uint32_lor(v___y_767_, v___x_850_);
return v___x_854_;
}
}
}
v___jp_855_:
{
uint32_t v___x_856_; uint32_t v___x_857_; uint32_t v___x_858_; uint32_t v___x_859_; uint8_t v___x_860_; 
v___x_856_ = 23;
v___x_857_ = lean_uint32_shift_right(v___y_767_, v___x_856_);
v___x_858_ = 255;
v___x_859_ = lean_uint32_land(v___x_857_, v___x_858_);
v___x_860_ = lean_uint32_dec_eq(v___x_859_, v___x_858_);
if (v___x_860_ == 0)
{
v___y_849_ = v___x_860_;
goto v___jp_848_;
}
else
{
uint32_t v___x_861_; uint32_t v___x_862_; uint32_t v___x_863_; uint8_t v___x_864_; 
v___x_861_ = 8388607;
v___x_862_ = lean_uint32_land(v___y_767_, v___x_861_);
v___x_863_ = 0;
v___x_864_ = lean_uint32_dec_eq(v___x_862_, v___x_863_);
if (v___x_864_ == 0)
{
v___y_849_ = v___x_860_;
goto v___jp_848_;
}
else
{
goto v___jp_838_;
}
}
}
v___jp_865_:
{
if (v___y_866_ == 0)
{
goto v___jp_855_;
}
else
{
uint32_t v___x_867_; uint32_t v___x_868_; uint32_t v___x_869_; uint8_t v___x_870_; 
v___x_867_ = 4194304;
v___x_868_ = lean_uint32_land(v___y_766_, v___x_867_);
v___x_869_ = 0;
v___x_870_ = lean_uint32_dec_eq(v___x_868_, v___x_869_);
if (v___x_870_ == 0)
{
goto v___jp_855_;
}
else
{
uint32_t v___x_871_; 
v___x_871_ = lean_uint32_lor(v___y_766_, v___x_867_);
return v___x_871_;
}
}
}
v___jp_872_:
{
uint8_t v___x_874_; 
v___x_874_ = lean_float32_beq(v___y_873_, v___y_873_);
if (v___x_874_ == 0)
{
uint32_t v___x_875_; uint32_t v___x_876_; uint32_t v___x_877_; uint32_t v___x_878_; uint8_t v___x_879_; 
v___x_875_ = 23;
v___x_876_ = lean_uint32_shift_right(v___y_766_, v___x_875_);
v___x_877_ = 255;
v___x_878_ = lean_uint32_land(v___x_876_, v___x_877_);
v___x_879_ = lean_uint32_dec_eq(v___x_878_, v___x_877_);
if (v___x_879_ == 0)
{
v___y_866_ = v___x_879_;
goto v___jp_865_;
}
else
{
uint32_t v___x_880_; uint32_t v___x_881_; uint32_t v___x_882_; uint8_t v___x_883_; 
v___x_880_ = 8388607;
v___x_881_ = lean_uint32_land(v___y_766_, v___x_880_);
v___x_882_ = 0;
v___x_883_ = lean_uint32_dec_eq(v___x_881_, v___x_882_);
if (v___x_883_ == 0)
{
v___y_866_ = v___x_879_;
goto v___jp_865_;
}
else
{
goto v___jp_855_;
}
}
}
else
{
uint32_t v___x_884_; 
v___x_884_ = lean_float32_to_bits(v___y_873_);
return v___x_884_;
}
}
v___jp_888_:
{
uint32_t v___x_893_; uint32_t v___x_894_; uint32_t v___x_895_; uint32_t v___x_896_; uint32_t v___x_897_; 
v___x_893_ = lean_uint32_land(v___y_891_, v___x_887_);
v___x_894_ = lean_uint32_shift_left(v___x_893_, v___x_885_);
v___x_895_ = lean_uint32_lor(v___y_892_, v___x_894_);
v___x_896_ = lean_uint32_land(v___y_889_, v___y_890_);
v___x_897_ = lean_uint32_lor(v___x_895_, v___x_896_);
return v___x_897_;
}
v___jp_898_:
{
if (v___y_900_ == 0)
{
uint32_t v___x_903_; 
v___x_903_ = 0;
v___y_889_ = v___y_902_;
v___y_890_ = v___y_899_;
v___y_891_ = v___y_901_;
v___y_892_ = v___x_903_;
goto v___jp_888_;
}
else
{
uint32_t v___x_904_; 
v___x_904_ = 2147483648;
v___y_889_ = v___y_902_;
v___y_890_ = v___y_899_;
v___y_891_ = v___y_901_;
v___y_892_ = v___x_904_;
goto v___jp_888_;
}
}
v___jp_905_:
{
uint64_t v___x_911_; uint64_t v_encodedExponent_912_; uint32_t v___x_913_; uint64_t v___x_914_; uint8_t v___x_915_; 
v___x_911_ = 171ULL;
v_encodedExponent_912_ = lean_uint64_sub(v___y_908_, v___x_911_);
v___x_913_ = lean_uint64_to_uint32(v_encodedExponent_912_);
v___x_914_ = 8388608ULL;
v___x_915_ = lean_uint64_dec_lt(v___y_910_, v___x_914_);
if (v___x_915_ == 0)
{
uint64_t v___x_916_; uint32_t v___x_917_; 
v___x_916_ = lean_uint64_sub(v___y_910_, v___x_914_);
v___x_917_ = lean_uint64_to_uint32(v___x_916_);
v___y_899_ = v___y_907_;
v___y_900_ = v___y_909_;
v___y_901_ = v___x_913_;
v___y_902_ = v___x_917_;
goto v___jp_898_;
}
else
{
uint32_t v___x_918_; 
v___x_918_ = lean_uint64_to_uint32(v___y_906_);
v___y_899_ = v___y_907_;
v___y_900_ = v___y_909_;
v___y_901_ = v___x_913_;
v___y_902_ = v___x_918_;
goto v___jp_898_;
}
}
v___jp_919_:
{
uint64_t v___x_926_; uint8_t v___x_927_; 
v___x_926_ = 425ULL;
v___x_927_ = lean_uint64_dec_lt(v___x_926_, v___y_925_);
if (v___x_927_ == 0)
{
if (v___y_922_ == 0)
{
v___y_906_ = v___y_921_;
v___y_907_ = v___y_923_;
v___y_908_ = v___y_925_;
v___y_909_ = v___y_924_;
v___y_910_ = v___y_920_;
goto v___jp_905_;
}
else
{
uint64_t v___x_928_; 
v___x_928_ = 8388608ULL;
v___y_906_ = v___y_921_;
v___y_907_ = v___y_923_;
v___y_908_ = v___y_925_;
v___y_909_ = v___y_924_;
v___y_910_ = v___x_928_;
goto v___jp_905_;
}
}
else
{
if (v___y_924_ == 0)
{
uint32_t v___x_929_; 
v___x_929_ = 2139095040;
return v___x_929_;
}
else
{
uint32_t v___x_930_; 
v___x_930_ = 4286578688;
return v___x_930_;
}
}
}
v___jp_931_:
{
uint64_t v___x_937_; uint8_t v_carry_938_; 
v___x_937_ = 16777216ULL;
v_carry_938_ = lean_uint64_dec_eq(v___y_936_, v___x_937_);
if (v_carry_938_ == 0)
{
v___y_920_ = v___y_936_;
v___y_921_ = v___y_932_;
v___y_922_ = v_carry_938_;
v___y_923_ = v___y_934_;
v___y_924_ = v___y_935_;
v___y_925_ = v___y_933_;
goto v___jp_919_;
}
else
{
uint64_t v___x_939_; uint64_t v___x_940_; 
v___x_939_ = 1ULL;
v___x_940_ = lean_uint64_add(v___y_933_, v___x_939_);
v___y_920_ = v___y_936_;
v___y_921_ = v___y_932_;
v___y_922_ = v_carry_938_;
v___y_923_ = v___y_934_;
v___y_924_ = v___y_935_;
v___y_925_ = v___x_940_;
goto v___jp_919_;
}
}
v___jp_941_:
{
uint64_t v_position_948_; uint64_t v___x_949_; uint8_t v___x_950_; 
v_position_948_ = lean_uint64_add(v___y_947_, v___y_944_);
v___x_949_ = 172ULL;
v___x_950_ = lean_uint64_dec_lt(v_position_948_, v___x_949_);
if (v___x_950_ == 0)
{
uint64_t v___x_951_; uint8_t v___x_952_; 
v___x_951_ = 23ULL;
v___x_952_ = lean_uint64_dec_lt(v___y_947_, v___x_951_);
if (v___x_952_ == 0)
{
uint64_t v___x_953_; uint8_t v___x_954_; 
v___x_953_ = lean_uint64_sub(v___y_947_, v___x_951_);
v___x_954_ = lean_uint64_dec_eq(v___x_953_, v___y_942_);
if (v___x_954_ == 0)
{
uint64_t v___x_955_; uint8_t v___x_956_; 
v___x_955_ = 64ULL;
v___x_956_ = lean_uint64_dec_lt(v___x_953_, v___x_955_);
if (v___x_956_ == 0)
{
uint8_t v___x_957_; 
v___x_957_ = lean_uint64_dec_eq(v___x_953_, v___x_955_);
if (v___x_957_ == 0)
{
v___y_932_ = v___y_942_;
v___y_933_ = v_position_948_;
v___y_934_ = v___y_943_;
v___y_935_ = v___y_946_;
v___y_936_ = v___y_942_;
goto v___jp_931_;
}
else
{
uint64_t v___x_958_; uint8_t v___x_959_; 
v___x_958_ = 9223372036854775808ULL;
v___x_959_ = lean_uint64_dec_lt(v___x_958_, v___y_945_);
if (v___x_959_ == 0)
{
v___y_932_ = v___y_942_;
v___y_933_ = v_position_948_;
v___y_934_ = v___y_943_;
v___y_935_ = v___y_946_;
v___y_936_ = v___y_942_;
goto v___jp_931_;
}
else
{
uint64_t v___x_960_; 
v___x_960_ = 1ULL;
v___y_932_ = v___y_942_;
v___y_933_ = v_position_948_;
v___y_934_ = v___y_943_;
v___y_935_ = v___y_946_;
v___y_936_ = v___x_960_;
goto v___jp_931_;
}
}
}
else
{
uint64_t v_quotient_961_; uint64_t v___x_962_; uint64_t v___x_963_; uint64_t v___x_964_; uint64_t v_remainder_965_; uint64_t v___x_966_; uint64_t v_half_967_; uint8_t v___x_968_; 
v_quotient_961_ = lean_uint64_shift_right(v___y_945_, v___x_953_);
v___x_962_ = 1ULL;
v___x_963_ = lean_uint64_shift_left(v___x_962_, v___x_953_);
v___x_964_ = lean_uint64_sub(v___x_963_, v___x_962_);
v_remainder_965_ = lean_uint64_land(v___y_945_, v___x_964_);
v___x_966_ = lean_uint64_sub(v___x_953_, v___x_962_);
v_half_967_ = lean_uint64_shift_left(v___x_962_, v___x_966_);
v___x_968_ = lean_uint64_dec_lt(v_remainder_965_, v_half_967_);
if (v___x_968_ == 0)
{
uint8_t v___x_969_; 
v___x_969_ = lean_uint64_dec_lt(v_half_967_, v_remainder_965_);
if (v___x_969_ == 0)
{
uint64_t v___x_970_; uint8_t v___x_971_; 
v___x_970_ = lean_uint64_land(v_quotient_961_, v___x_962_);
v___x_971_ = lean_uint64_dec_eq(v___x_970_, v___y_942_);
if (v___x_971_ == 0)
{
uint64_t v___x_972_; 
v___x_972_ = lean_uint64_add(v_quotient_961_, v___x_962_);
v___y_932_ = v___y_942_;
v___y_933_ = v_position_948_;
v___y_934_ = v___y_943_;
v___y_935_ = v___y_946_;
v___y_936_ = v___x_972_;
goto v___jp_931_;
}
else
{
v___y_932_ = v___y_942_;
v___y_933_ = v_position_948_;
v___y_934_ = v___y_943_;
v___y_935_ = v___y_946_;
v___y_936_ = v_quotient_961_;
goto v___jp_931_;
}
}
else
{
uint64_t v___x_973_; 
v___x_973_ = lean_uint64_add(v_quotient_961_, v___x_962_);
v___y_932_ = v___y_942_;
v___y_933_ = v_position_948_;
v___y_934_ = v___y_943_;
v___y_935_ = v___y_946_;
v___y_936_ = v___x_973_;
goto v___jp_931_;
}
}
else
{
v___y_932_ = v___y_942_;
v___y_933_ = v_position_948_;
v___y_934_ = v___y_943_;
v___y_935_ = v___y_946_;
v___y_936_ = v_quotient_961_;
goto v___jp_931_;
}
}
}
else
{
v___y_932_ = v___y_942_;
v___y_933_ = v_position_948_;
v___y_934_ = v___y_943_;
v___y_935_ = v___y_946_;
v___y_936_ = v___y_945_;
goto v___jp_931_;
}
}
else
{
uint64_t v___x_974_; uint64_t v___x_975_; 
v___x_974_ = lean_uint64_sub(v___x_951_, v___y_947_);
v___x_975_ = lean_uint64_shift_left(v___y_945_, v___x_974_);
v___y_932_ = v___y_942_;
v___y_933_ = v_position_948_;
v___y_934_ = v___y_943_;
v___y_935_ = v___y_946_;
v___y_936_ = v___x_975_;
goto v___jp_931_;
}
}
else
{
uint64_t v___x_976_; uint8_t v___x_977_; 
v___x_976_ = 149ULL;
v___x_977_ = lean_uint64_dec_lt(v___y_944_, v___x_976_);
if (v___x_977_ == 0)
{
uint64_t v___x_978_; uint64_t v___x_979_; 
v___x_978_ = lean_uint64_sub(v___y_944_, v___x_976_);
v___x_979_ = lean_uint64_shift_left(v___y_945_, v___x_978_);
v___y_783_ = v___y_942_;
v___y_784_ = v___y_943_;
v___y_785_ = v___y_946_;
v___y_786_ = v___x_979_;
goto v___jp_782_;
}
else
{
uint64_t v___x_980_; uint8_t v___x_981_; 
v___x_980_ = lean_uint64_sub(v___x_976_, v___y_944_);
v___x_981_ = lean_uint64_dec_eq(v___x_980_, v___y_942_);
if (v___x_981_ == 0)
{
uint64_t v___x_982_; uint8_t v___x_983_; 
v___x_982_ = 64ULL;
v___x_983_ = lean_uint64_dec_lt(v___x_980_, v___x_982_);
if (v___x_983_ == 0)
{
uint8_t v___x_984_; 
v___x_984_ = lean_uint64_dec_eq(v___x_980_, v___x_982_);
if (v___x_984_ == 0)
{
v___y_783_ = v___y_942_;
v___y_784_ = v___y_943_;
v___y_785_ = v___y_946_;
v___y_786_ = v___y_942_;
goto v___jp_782_;
}
else
{
uint64_t v___x_985_; uint8_t v___x_986_; 
v___x_985_ = 9223372036854775808ULL;
v___x_986_ = lean_uint64_dec_lt(v___x_985_, v___y_945_);
if (v___x_986_ == 0)
{
v___y_783_ = v___y_942_;
v___y_784_ = v___y_943_;
v___y_785_ = v___y_946_;
v___y_786_ = v___y_942_;
goto v___jp_782_;
}
else
{
uint64_t v___x_987_; 
v___x_987_ = 1ULL;
v___y_783_ = v___y_942_;
v___y_784_ = v___y_943_;
v___y_785_ = v___y_946_;
v___y_786_ = v___x_987_;
goto v___jp_782_;
}
}
}
else
{
uint64_t v_quotient_988_; uint64_t v___x_989_; uint64_t v___x_990_; uint64_t v___x_991_; uint64_t v_remainder_992_; uint64_t v___x_993_; uint64_t v_half_994_; uint8_t v___x_995_; 
v_quotient_988_ = lean_uint64_shift_right(v___y_945_, v___x_980_);
v___x_989_ = 1ULL;
v___x_990_ = lean_uint64_shift_left(v___x_989_, v___x_980_);
v___x_991_ = lean_uint64_sub(v___x_990_, v___x_989_);
v_remainder_992_ = lean_uint64_land(v___y_945_, v___x_991_);
v___x_993_ = lean_uint64_sub(v___x_980_, v___x_989_);
v_half_994_ = lean_uint64_shift_left(v___x_989_, v___x_993_);
v___x_995_ = lean_uint64_dec_lt(v_remainder_992_, v_half_994_);
if (v___x_995_ == 0)
{
uint8_t v___x_996_; 
v___x_996_ = lean_uint64_dec_lt(v_half_994_, v_remainder_992_);
if (v___x_996_ == 0)
{
uint64_t v___x_997_; uint8_t v___x_998_; 
v___x_997_ = lean_uint64_land(v_quotient_988_, v___x_989_);
v___x_998_ = lean_uint64_dec_eq(v___x_997_, v___y_942_);
if (v___x_998_ == 0)
{
uint64_t v___x_999_; 
v___x_999_ = lean_uint64_add(v_quotient_988_, v___x_989_);
v___y_783_ = v___y_942_;
v___y_784_ = v___y_943_;
v___y_785_ = v___y_946_;
v___y_786_ = v___x_999_;
goto v___jp_782_;
}
else
{
v___y_783_ = v___y_942_;
v___y_784_ = v___y_943_;
v___y_785_ = v___y_946_;
v___y_786_ = v_quotient_988_;
goto v___jp_782_;
}
}
else
{
uint64_t v___x_1000_; 
v___x_1000_ = lean_uint64_add(v_quotient_988_, v___x_989_);
v___y_783_ = v___y_942_;
v___y_784_ = v___y_943_;
v___y_785_ = v___y_946_;
v___y_786_ = v___x_1000_;
goto v___jp_782_;
}
}
else
{
v___y_783_ = v___y_942_;
v___y_784_ = v___y_943_;
v___y_785_ = v___y_946_;
v___y_786_ = v_quotient_988_;
goto v___jp_782_;
}
}
}
else
{
v___y_783_ = v___y_942_;
v___y_784_ = v___y_943_;
v___y_785_ = v___y_946_;
v___y_786_ = v___y_945_;
goto v___jp_782_;
}
}
}
}
v___jp_1001_:
{
uint64_t v___x_1009_; uint64_t v___x_1010_; uint8_t v___x_1011_; 
v___x_1009_ = 1ULL;
v___x_1010_ = lean_uint64_shift_right(v___y_1006_, v___x_1009_);
v___x_1011_ = lean_uint64_dec_eq(v___x_1010_, v___y_1002_);
if (v___x_1011_ == 0)
{
uint64_t v___x_1012_; 
v___x_1012_ = lean_uint64_add(v___y_1008_, v___x_1009_);
v___y_942_ = v___y_1002_;
v___y_943_ = v___y_1003_;
v___y_944_ = v___y_1004_;
v___y_945_ = v___y_1005_;
v___y_946_ = v___y_1007_;
v___y_947_ = v___x_1012_;
goto v___jp_941_;
}
else
{
v___y_942_ = v___y_1002_;
v___y_943_ = v___y_1003_;
v___y_944_ = v___y_1004_;
v___y_945_ = v___y_1005_;
v___y_946_ = v___y_1007_;
v___y_947_ = v___y_1008_;
goto v___jp_941_;
}
}
v___jp_1013_:
{
uint64_t v___x_1023_; uint8_t v___x_1024_; 
v___x_1023_ = lean_uint64_shift_right(v___y_1014_, v___y_1020_);
v___x_1024_ = lean_uint64_dec_eq(v___x_1023_, v___y_1015_);
if (v___x_1024_ == 0)
{
uint64_t v___x_1025_; 
v___x_1025_ = lean_uint64_add(v___y_1017_, v___y_1020_);
v___y_1002_ = v___y_1015_;
v___y_1003_ = v___y_1016_;
v___y_1004_ = v___y_1018_;
v___y_1005_ = v___y_1019_;
v___y_1006_ = v___y_1022_;
v___y_1007_ = v___y_1021_;
v___y_1008_ = v___x_1025_;
goto v___jp_1001_;
}
else
{
v___y_1002_ = v___y_1015_;
v___y_1003_ = v___y_1016_;
v___y_1004_ = v___y_1018_;
v___y_1005_ = v___y_1019_;
v___y_1006_ = v___y_1022_;
v___y_1007_ = v___y_1021_;
v___y_1008_ = v___y_1017_;
goto v___jp_1001_;
}
}
v___jp_1026_:
{
uint64_t v___x_1034_; uint64_t v___x_1035_; uint8_t v___x_1036_; 
v___x_1034_ = 2ULL;
v___x_1035_ = lean_uint64_shift_right(v___y_1028_, v___x_1034_);
v___x_1036_ = lean_uint64_dec_eq(v___x_1035_, v___y_1027_);
if (v___x_1036_ == 0)
{
v___y_1014_ = v___y_1028_;
v___y_1015_ = v___y_1027_;
v___y_1016_ = v___y_1029_;
v___y_1017_ = v___y_1033_;
v___y_1018_ = v___y_1030_;
v___y_1019_ = v___y_1031_;
v___y_1020_ = v___x_1034_;
v___y_1021_ = v___y_1032_;
v___y_1022_ = v___x_1035_;
goto v___jp_1013_;
}
else
{
v___y_1014_ = v___y_1028_;
v___y_1015_ = v___y_1027_;
v___y_1016_ = v___y_1029_;
v___y_1017_ = v___y_1033_;
v___y_1018_ = v___y_1030_;
v___y_1019_ = v___y_1031_;
v___y_1020_ = v___x_1034_;
v___y_1021_ = v___y_1032_;
v___y_1022_ = v___y_1028_;
goto v___jp_1013_;
}
}
v___jp_1037_:
{
uint64_t v___x_1047_; uint8_t v___x_1048_; 
v___x_1047_ = lean_uint64_shift_right(v___y_1040_, v___y_1038_);
v___x_1048_ = lean_uint64_dec_eq(v___x_1047_, v___y_1039_);
if (v___x_1048_ == 0)
{
uint64_t v___x_1049_; 
v___x_1049_ = lean_uint64_add(v___y_1045_, v___y_1038_);
v___y_1027_ = v___y_1039_;
v___y_1028_ = v___y_1046_;
v___y_1029_ = v___y_1041_;
v___y_1030_ = v___y_1042_;
v___y_1031_ = v___y_1043_;
v___y_1032_ = v___y_1044_;
v___y_1033_ = v___x_1049_;
goto v___jp_1026_;
}
else
{
v___y_1027_ = v___y_1039_;
v___y_1028_ = v___y_1046_;
v___y_1029_ = v___y_1041_;
v___y_1030_ = v___y_1042_;
v___y_1031_ = v___y_1043_;
v___y_1032_ = v___y_1044_;
v___y_1033_ = v___y_1045_;
goto v___jp_1026_;
}
}
v___jp_1050_:
{
uint64_t v___x_1058_; uint64_t v___x_1059_; uint8_t v___x_1060_; 
v___x_1058_ = 4ULL;
v___x_1059_ = lean_uint64_shift_right(v___y_1053_, v___x_1058_);
v___x_1060_ = lean_uint64_dec_eq(v___x_1059_, v___y_1051_);
if (v___x_1060_ == 0)
{
v___y_1038_ = v___x_1058_;
v___y_1039_ = v___y_1051_;
v___y_1040_ = v___y_1053_;
v___y_1041_ = v___y_1052_;
v___y_1042_ = v___y_1054_;
v___y_1043_ = v___y_1055_;
v___y_1044_ = v___y_1056_;
v___y_1045_ = v___y_1057_;
v___y_1046_ = v___x_1059_;
goto v___jp_1037_;
}
else
{
v___y_1038_ = v___x_1058_;
v___y_1039_ = v___y_1051_;
v___y_1040_ = v___y_1053_;
v___y_1041_ = v___y_1052_;
v___y_1042_ = v___y_1054_;
v___y_1043_ = v___y_1055_;
v___y_1044_ = v___y_1056_;
v___y_1045_ = v___y_1057_;
v___y_1046_ = v___y_1053_;
goto v___jp_1037_;
}
}
v___jp_1061_:
{
uint64_t v___x_1071_; uint8_t v___x_1072_; 
v___x_1071_ = lean_uint64_shift_right(v___y_1065_, v___y_1063_);
v___x_1072_ = lean_uint64_dec_eq(v___x_1071_, v___y_1062_);
if (v___x_1072_ == 0)
{
uint64_t v___x_1073_; 
v___x_1073_ = lean_uint64_add(v___y_1068_, v___y_1063_);
v___y_1051_ = v___y_1062_;
v___y_1052_ = v___y_1064_;
v___y_1053_ = v___y_1070_;
v___y_1054_ = v___y_1066_;
v___y_1055_ = v___y_1067_;
v___y_1056_ = v___y_1069_;
v___y_1057_ = v___x_1073_;
goto v___jp_1050_;
}
else
{
v___y_1051_ = v___y_1062_;
v___y_1052_ = v___y_1064_;
v___y_1053_ = v___y_1070_;
v___y_1054_ = v___y_1066_;
v___y_1055_ = v___y_1067_;
v___y_1056_ = v___y_1069_;
v___y_1057_ = v___y_1068_;
goto v___jp_1050_;
}
}
v___jp_1074_:
{
uint64_t v___x_1082_; uint64_t v___x_1083_; uint8_t v___x_1084_; 
v___x_1082_ = 8ULL;
v___x_1083_ = lean_uint64_shift_right(v___y_1078_, v___x_1082_);
v___x_1084_ = lean_uint64_dec_eq(v___x_1083_, v___y_1075_);
if (v___x_1084_ == 0)
{
v___y_1062_ = v___y_1075_;
v___y_1063_ = v___x_1082_;
v___y_1064_ = v___y_1076_;
v___y_1065_ = v___y_1078_;
v___y_1066_ = v___y_1077_;
v___y_1067_ = v___y_1079_;
v___y_1068_ = v___y_1081_;
v___y_1069_ = v___y_1080_;
v___y_1070_ = v___x_1083_;
goto v___jp_1061_;
}
else
{
v___y_1062_ = v___y_1075_;
v___y_1063_ = v___x_1082_;
v___y_1064_ = v___y_1076_;
v___y_1065_ = v___y_1078_;
v___y_1066_ = v___y_1077_;
v___y_1067_ = v___y_1079_;
v___y_1068_ = v___y_1081_;
v___y_1069_ = v___y_1080_;
v___y_1070_ = v___y_1078_;
goto v___jp_1061_;
}
}
v___jp_1085_:
{
uint64_t v___x_1095_; uint8_t v___x_1096_; 
v___x_1095_ = lean_uint64_shift_right(v___y_1089_, v___y_1087_);
v___x_1096_ = lean_uint64_dec_eq(v___x_1095_, v___y_1088_);
if (v___x_1096_ == 0)
{
uint64_t v___x_1097_; 
v___x_1097_ = lean_uint64_add(v___y_1086_, v___y_1087_);
v___y_1075_ = v___y_1088_;
v___y_1076_ = v___y_1090_;
v___y_1077_ = v___y_1091_;
v___y_1078_ = v___y_1094_;
v___y_1079_ = v___y_1092_;
v___y_1080_ = v___y_1093_;
v___y_1081_ = v___x_1097_;
goto v___jp_1074_;
}
else
{
v___y_1075_ = v___y_1088_;
v___y_1076_ = v___y_1090_;
v___y_1077_ = v___y_1091_;
v___y_1078_ = v___y_1094_;
v___y_1079_ = v___y_1092_;
v___y_1080_ = v___y_1093_;
v___y_1081_ = v___y_1086_;
goto v___jp_1074_;
}
}
v___jp_1098_:
{
uint64_t v___x_1106_; uint64_t v___x_1107_; uint8_t v___x_1108_; 
v___x_1106_ = 16ULL;
v___x_1107_ = lean_uint64_shift_right(v___y_1100_, v___x_1106_);
v___x_1108_ = lean_uint64_dec_eq(v___x_1107_, v___y_1099_);
if (v___x_1108_ == 0)
{
v___y_1086_ = v___y_1105_;
v___y_1087_ = v___x_1106_;
v___y_1088_ = v___y_1099_;
v___y_1089_ = v___y_1100_;
v___y_1090_ = v___y_1101_;
v___y_1091_ = v___y_1102_;
v___y_1092_ = v___y_1103_;
v___y_1093_ = v___y_1104_;
v___y_1094_ = v___x_1107_;
goto v___jp_1085_;
}
else
{
v___y_1086_ = v___y_1105_;
v___y_1087_ = v___x_1106_;
v___y_1088_ = v___y_1099_;
v___y_1089_ = v___y_1100_;
v___y_1090_ = v___y_1101_;
v___y_1091_ = v___y_1102_;
v___y_1092_ = v___y_1103_;
v___y_1093_ = v___y_1104_;
v___y_1094_ = v___y_1100_;
goto v___jp_1085_;
}
}
v___jp_1109_:
{
uint64_t v___x_1117_; uint8_t v___x_1118_; 
v___x_1117_ = lean_uint64_shift_right(v___y_1114_, v___y_1110_);
v___x_1118_ = lean_uint64_dec_eq(v___x_1117_, v___y_1111_);
if (v___x_1118_ == 0)
{
v___y_1099_ = v___y_1111_;
v___y_1100_ = v___y_1116_;
v___y_1101_ = v___y_1112_;
v___y_1102_ = v___y_1113_;
v___y_1103_ = v___y_1114_;
v___y_1104_ = v___y_1115_;
v___y_1105_ = v___y_1110_;
goto v___jp_1098_;
}
else
{
v___y_1099_ = v___y_1111_;
v___y_1100_ = v___y_1116_;
v___y_1101_ = v___y_1112_;
v___y_1102_ = v___y_1113_;
v___y_1103_ = v___y_1114_;
v___y_1104_ = v___y_1115_;
v___y_1105_ = v___y_1111_;
goto v___jp_1098_;
}
}
v___jp_1119_:
{
uint64_t v___x_1124_; uint8_t v___x_1125_; 
v___x_1124_ = 0ULL;
v___x_1125_ = lean_uint64_dec_eq(v___y_1122_, v___x_1124_);
if (v___x_1125_ == 0)
{
uint64_t v___x_1126_; uint64_t v___x_1127_; uint8_t v___x_1128_; 
v___x_1126_ = 32ULL;
v___x_1127_ = lean_uint64_shift_right(v___y_1122_, v___x_1126_);
v___x_1128_ = lean_uint64_dec_eq(v___x_1127_, v___x_1124_);
if (v___x_1128_ == 0)
{
v___y_1110_ = v___x_1126_;
v___y_1111_ = v___x_1124_;
v___y_1112_ = v___y_1120_;
v___y_1113_ = v___y_1121_;
v___y_1114_ = v___y_1122_;
v___y_1115_ = v___y_1123_;
v___y_1116_ = v___x_1127_;
goto v___jp_1109_;
}
else
{
v___y_1110_ = v___x_1126_;
v___y_1111_ = v___x_1124_;
v___y_1112_ = v___y_1120_;
v___y_1113_ = v___y_1121_;
v___y_1114_ = v___y_1122_;
v___y_1115_ = v___y_1123_;
v___y_1116_ = v___y_1122_;
goto v___jp_1109_;
}
}
else
{
if (v___y_1123_ == 0)
{
uint32_t v___x_1129_; 
v___x_1129_ = 0;
return v___x_1129_;
}
else
{
uint32_t v___x_1130_; 
v___x_1130_ = 2147483648;
return v___x_1130_;
}
}
}
v___jp_1131_:
{
uint64_t v___x_1138_; uint64_t v___x_1139_; uint64_t v___x_1140_; uint8_t v___x_1141_; 
v___x_1138_ = lean_uint64_mul(v___y_1132_, v___y_1133_);
v___x_1139_ = lean_uint64_add(v___y_1135_, v___y_1137_);
v___x_1140_ = 281474976710656ULL;
v___x_1141_ = lean_uint64_dec_lt(v___x_1138_, v___x_1140_);
if (v___x_1141_ == 0)
{
v___y_1120_ = v___y_1134_;
v___y_1121_ = v___x_1139_;
v___y_1122_ = v___x_1138_;
v___y_1123_ = v___y_1136_;
goto v___jp_1119_;
}
else
{
uint64_t v___x_1142_; uint8_t v___x_1143_; 
v___x_1142_ = 123ULL;
v___x_1143_ = lean_uint64_dec_le(v___x_1139_, v___x_1142_);
if (v___x_1143_ == 0)
{
v___y_1120_ = v___y_1134_;
v___y_1121_ = v___x_1139_;
v___y_1122_ = v___x_1138_;
v___y_1123_ = v___y_1136_;
goto v___jp_1119_;
}
else
{
uint64_t v___x_1144_; uint8_t v___x_1145_; 
v___x_1144_ = 0ULL;
v___x_1145_ = lean_uint64_dec_eq(v___x_1138_, v___x_1144_);
if (v___x_1145_ == 0)
{
uint64_t v___x_1146_; uint64_t v___x_1147_; uint8_t v___x_1148_; 
v___x_1146_ = 149ULL;
v___x_1147_ = lean_uint64_sub(v___x_1146_, v___x_1139_);
v___x_1148_ = lean_uint64_dec_eq(v___x_1147_, v___x_1144_);
if (v___x_1148_ == 0)
{
uint64_t v___x_1149_; uint8_t v___x_1150_; 
v___x_1149_ = 64ULL;
v___x_1150_ = lean_uint64_dec_lt(v___x_1147_, v___x_1149_);
if (v___x_1150_ == 0)
{
uint8_t v___x_1151_; 
v___x_1151_ = lean_uint64_dec_eq(v___x_1147_, v___x_1149_);
if (v___x_1151_ == 0)
{
v___y_804_ = v___y_1134_;
v___y_805_ = v___x_1144_;
v___y_806_ = v___y_1136_;
v___y_807_ = v___x_1144_;
goto v___jp_803_;
}
else
{
uint64_t v___x_1152_; uint8_t v___x_1153_; 
v___x_1152_ = 9223372036854775808ULL;
v___x_1153_ = lean_uint64_dec_lt(v___x_1152_, v___x_1138_);
if (v___x_1153_ == 0)
{
v___y_804_ = v___y_1134_;
v___y_805_ = v___x_1144_;
v___y_806_ = v___y_1136_;
v___y_807_ = v___x_1144_;
goto v___jp_803_;
}
else
{
uint64_t v___x_1154_; 
v___x_1154_ = 1ULL;
v___y_804_ = v___y_1134_;
v___y_805_ = v___x_1144_;
v___y_806_ = v___y_1136_;
v___y_807_ = v___x_1154_;
goto v___jp_803_;
}
}
}
else
{
uint64_t v_quotient_1155_; uint64_t v___x_1156_; uint64_t v___x_1157_; uint64_t v___x_1158_; uint64_t v_remainder_1159_; uint64_t v___x_1160_; uint64_t v_half_1161_; uint8_t v___x_1162_; 
v_quotient_1155_ = lean_uint64_shift_right(v___x_1138_, v___x_1147_);
v___x_1156_ = 1ULL;
v___x_1157_ = lean_uint64_shift_left(v___x_1156_, v___x_1147_);
v___x_1158_ = lean_uint64_sub(v___x_1157_, v___x_1156_);
v_remainder_1159_ = lean_uint64_land(v___x_1138_, v___x_1158_);
v___x_1160_ = lean_uint64_sub(v___x_1147_, v___x_1156_);
v_half_1161_ = lean_uint64_shift_left(v___x_1156_, v___x_1160_);
v___x_1162_ = lean_uint64_dec_lt(v_remainder_1159_, v_half_1161_);
if (v___x_1162_ == 0)
{
uint8_t v___x_1163_; 
v___x_1163_ = lean_uint64_dec_lt(v_half_1161_, v_remainder_1159_);
if (v___x_1163_ == 0)
{
uint64_t v___x_1164_; uint8_t v___x_1165_; 
v___x_1164_ = lean_uint64_land(v_quotient_1155_, v___x_1156_);
v___x_1165_ = lean_uint64_dec_eq(v___x_1164_, v___x_1144_);
if (v___x_1165_ == 0)
{
uint64_t v___x_1166_; 
v___x_1166_ = lean_uint64_add(v_quotient_1155_, v___x_1156_);
v___y_804_ = v___y_1134_;
v___y_805_ = v___x_1144_;
v___y_806_ = v___y_1136_;
v___y_807_ = v___x_1166_;
goto v___jp_803_;
}
else
{
v___y_804_ = v___y_1134_;
v___y_805_ = v___x_1144_;
v___y_806_ = v___y_1136_;
v___y_807_ = v_quotient_1155_;
goto v___jp_803_;
}
}
else
{
uint64_t v___x_1167_; 
v___x_1167_ = lean_uint64_add(v_quotient_1155_, v___x_1156_);
v___y_804_ = v___y_1134_;
v___y_805_ = v___x_1144_;
v___y_806_ = v___y_1136_;
v___y_807_ = v___x_1167_;
goto v___jp_803_;
}
}
else
{
v___y_804_ = v___y_1134_;
v___y_805_ = v___x_1144_;
v___y_806_ = v___y_1136_;
v___y_807_ = v_quotient_1155_;
goto v___jp_803_;
}
}
}
else
{
v___y_804_ = v___y_1134_;
v___y_805_ = v___x_1144_;
v___y_806_ = v___y_1136_;
v___y_807_ = v___x_1138_;
goto v___jp_803_;
}
}
else
{
if (v___y_1136_ == 0)
{
uint32_t v___x_1168_; 
v___x_1168_ = 0;
return v___x_1168_;
}
else
{
uint32_t v___x_1169_; 
v___x_1169_ = 2147483648;
return v___x_1169_;
}
}
}
}
}
v___jp_1172_:
{
if (v___y_1174_ == 0)
{
float v___x_1175_; float v___x_1176_; 
v___x_1175_ = lean_float32_of_bits(v___y_767_);
v___x_1176_ = lean_float32_mul(v___y_1173_, v___x_1175_);
v___y_873_ = v___x_1176_;
goto v___jp_872_;
}
else
{
uint32_t v___x_1177_; uint32_t v___x_1178_; uint32_t v___x_1179_; uint32_t v___x_1180_; float v___x_1181_; lean_object* v___x_1182_; lean_object* v___x_1183_; double v___x_1184_; float v___x_1185_; float v___x_1186_; float v___x_1187_; 
v___x_1177_ = 8388607;
v___x_1178_ = lean_uint32_land(v___y_767_, v___x_1177_);
v___x_1179_ = 8388608;
v___x_1180_ = lean_uint32_lor(v___x_1178_, v___x_1179_);
v___x_1181_ = lean_uint32_to_float32(v___x_1180_);
v___x_1182_ = lp_competition_R19CompactScales_packed;
v___x_1183_ = lean_uint32_to_nat(v___x_1171_);
v___x_1184_ = lean_float_array_fget(v___x_1182_, v___x_1183_);
lean_dec(v___x_1183_);
v___x_1185_ = lean_float_to_float32(v___x_1184_);
v___x_1186_ = lean_float32_mul(v___x_1181_, v___x_1185_);
v___x_1187_ = lean_float32_mul(v___y_1173_, v___x_1186_);
v___y_873_ = v___x_1187_;
goto v___jp_872_;
}
}
v___jp_1188_:
{
uint32_t v___x_1190_; uint32_t v_a_1191_; uint32_t v___x_1192_; uint32_t v___x_1193_; uint32_t v___x_1194_; uint8_t v___x_1195_; 
v___x_1190_ = 2147483647;
v_a_1191_ = lean_uint32_land(v___y_767_, v___x_1190_);
v___x_1192_ = 201326591;
v___x_1193_ = 1;
v___x_1194_ = lean_uint32_sub(v_a_1191_, v___x_1193_);
v___x_1195_ = lean_uint32_dec_le(v___x_1192_, v___x_1194_);
if (v___x_1195_ == 0)
{
v___y_1173_ = v___y_1189_;
v___y_1174_ = v___x_1195_;
goto v___jp_1172_;
}
else
{
uint32_t v___x_1196_; uint8_t v___x_1197_; 
v___x_1196_ = 2139095040;
v___x_1197_ = lean_uint32_dec_lt(v_a_1191_, v___x_1196_);
v___y_1173_ = v___y_1189_;
v___y_1174_ = v___x_1197_;
goto v___jp_1172_;
}
}
v___jp_1198_:
{
if (v___y_1199_ == 0)
{
float v___x_1200_; 
v___x_1200_ = lean_float32_of_bits(v___y_766_);
v___y_1189_ = v___x_1200_;
goto v___jp_1188_;
}
else
{
uint32_t v___x_1201_; uint32_t v___x_1202_; uint32_t v___x_1203_; uint32_t v___x_1204_; float v___x_1205_; lean_object* v___x_1206_; lean_object* v___x_1207_; double v___x_1208_; float v___x_1209_; float v___x_1210_; 
v___x_1201_ = 8388607;
v___x_1202_ = lean_uint32_land(v___y_766_, v___x_1201_);
v___x_1203_ = 8388608;
v___x_1204_ = lean_uint32_lor(v___x_1202_, v___x_1203_);
v___x_1205_ = lean_uint32_to_float32(v___x_1204_);
v___x_1206_ = lp_competition_R19CompactScales_packed;
v___x_1207_ = lean_uint32_to_nat(v___x_886_);
v___x_1208_ = lean_float_array_fget(v___x_1206_, v___x_1207_);
lean_dec(v___x_1207_);
v___x_1209_ = lean_float_to_float32(v___x_1208_);
v___x_1210_ = lean_float32_mul(v___x_1205_, v___x_1209_);
v___y_1189_ = v___x_1210_;
goto v___jp_1188_;
}
}
v___jp_1211_:
{
if (v___y_1213_ == 0)
{
float v___x_1214_; float v___x_1215_; 
v___x_1214_ = lean_float32_of_bits(v___y_767_);
v___x_1215_ = lean_float32_mul(v___y_1212_, v___x_1214_);
v___y_873_ = v___x_1215_;
goto v___jp_872_;
}
else
{
uint32_t v___x_1216_; uint32_t v___x_1217_; uint32_t v___x_1218_; uint32_t v___x_1219_; float v___x_1220_; lean_object* v___x_1221_; lean_object* v___x_1222_; lean_object* v___x_1223_; float v___x_1224_; float v___x_1225_; float v___x_1226_; 
v___x_1216_ = 8388607;
v___x_1217_ = lean_uint32_land(v___y_767_, v___x_1216_);
v___x_1218_ = 8388608;
v___x_1219_ = lean_uint32_lor(v___x_1217_, v___x_1218_);
v___x_1220_ = lean_uint32_to_float32(v___x_1219_);
v___x_1221_ = lp_competition_R2W01b_scaleTable;
v___x_1222_ = lean_uint32_to_nat(v___x_1171_);
v___x_1223_ = lean_array_fget_borrowed(v___x_1221_, v___x_1222_);
lean_dec(v___x_1222_);
v___x_1224_ = lean_unbox_float32(v___x_1223_);
v___x_1225_ = lean_float32_mul(v___x_1220_, v___x_1224_);
v___x_1226_ = lean_float32_mul(v___y_1212_, v___x_1225_);
v___y_873_ = v___x_1226_;
goto v___jp_872_;
}
}
v___jp_1227_:
{
uint32_t v___x_1229_; uint32_t v_a_1230_; uint32_t v___x_1231_; uint32_t v___x_1232_; uint32_t v___x_1233_; uint8_t v___x_1234_; 
v___x_1229_ = 2147483647;
v_a_1230_ = lean_uint32_land(v___y_767_, v___x_1229_);
v___x_1231_ = 201326591;
v___x_1232_ = 1;
v___x_1233_ = lean_uint32_sub(v_a_1230_, v___x_1232_);
v___x_1234_ = lean_uint32_dec_le(v___x_1231_, v___x_1233_);
if (v___x_1234_ == 0)
{
v___y_1212_ = v___y_1228_;
v___y_1213_ = v___x_1234_;
goto v___jp_1211_;
}
else
{
uint32_t v___x_1235_; uint8_t v___x_1236_; 
v___x_1235_ = 2139095040;
v___x_1236_ = lean_uint32_dec_lt(v_a_1230_, v___x_1235_);
v___y_1212_ = v___y_1228_;
v___y_1213_ = v___x_1236_;
goto v___jp_1211_;
}
}
v___jp_1237_:
{
if (v___y_1238_ == 0)
{
float v___x_1239_; 
v___x_1239_ = lean_float32_of_bits(v___y_766_);
v___y_1228_ = v___x_1239_;
goto v___jp_1227_;
}
else
{
uint32_t v___x_1240_; uint32_t v___x_1241_; uint32_t v___x_1242_; uint32_t v___x_1243_; float v___x_1244_; lean_object* v___x_1245_; lean_object* v___x_1246_; lean_object* v___x_1247_; float v___x_1248_; float v___x_1249_; 
v___x_1240_ = 8388607;
v___x_1241_ = lean_uint32_land(v___y_766_, v___x_1240_);
v___x_1242_ = 8388608;
v___x_1243_ = lean_uint32_lor(v___x_1241_, v___x_1242_);
v___x_1244_ = lean_uint32_to_float32(v___x_1243_);
v___x_1245_ = lp_competition_R2W01b_scaleTable;
v___x_1246_ = lean_uint32_to_nat(v___x_886_);
v___x_1247_ = lean_array_fget_borrowed(v___x_1245_, v___x_1246_);
lean_dec(v___x_1246_);
v___x_1248_ = lean_unbox_float32(v___x_1247_);
v___x_1249_ = lean_float32_mul(v___x_1244_, v___x_1248_);
v___y_1228_ = v___x_1249_;
goto v___jp_1227_;
}
}
v___jp_1251_:
{
uint64_t v___x_1257_; uint64_t v___x_1258_; uint8_t v___x_1259_; 
v___x_1257_ = lean_uint32_to_uint64(v_ey_1250_);
v___x_1258_ = 0ULL;
v___x_1259_ = lean_uint64_dec_eq(v___x_1257_, v___x_1258_);
if (v___x_1259_ == 0)
{
uint64_t v___x_1260_; uint64_t v___x_1261_; 
v___x_1260_ = 1ULL;
v___x_1261_ = lean_uint64_sub(v___x_1257_, v___x_1260_);
v___y_1132_ = v___y_1252_;
v___y_1133_ = v___y_1253_;
v___y_1134_ = v___y_1254_;
v___y_1135_ = v___y_1256_;
v___y_1136_ = v___y_1255_;
v___y_1137_ = v___x_1261_;
goto v___jp_1131_;
}
else
{
v___y_1132_ = v___y_1252_;
v___y_1133_ = v___y_1253_;
v___y_1134_ = v___y_1254_;
v___y_1135_ = v___y_1256_;
v___y_1136_ = v___y_1255_;
v___y_1137_ = v___x_1258_;
goto v___jp_1131_;
}
}
v___jp_1262_:
{
uint64_t v___x_1267_; uint64_t v___x_1268_; uint8_t v___x_1269_; 
v___x_1267_ = lean_uint32_to_uint64(v_ex_1170_);
v___x_1268_ = 0ULL;
v___x_1269_ = lean_uint64_dec_eq(v___x_1267_, v___x_1268_);
if (v___x_1269_ == 0)
{
uint64_t v___x_1270_; uint64_t v___x_1271_; 
v___x_1270_ = 1ULL;
v___x_1271_ = lean_uint64_sub(v___x_1267_, v___x_1270_);
v___y_1252_ = v___y_1263_;
v___y_1253_ = v___y_1266_;
v___y_1254_ = v___y_1264_;
v___y_1255_ = v___y_1265_;
v___y_1256_ = v___x_1271_;
goto v___jp_1251_;
}
else
{
v___y_1252_ = v___y_1263_;
v___y_1253_ = v___y_1266_;
v___y_1254_ = v___y_1264_;
v___y_1255_ = v___y_1265_;
v___y_1256_ = v___x_1268_;
goto v___jp_1251_;
}
}
v___jp_1272_:
{
uint32_t v___x_1277_; uint8_t v___x_1278_; 
v___x_1277_ = 0;
v___x_1278_ = lean_uint32_dec_eq(v_ey_1250_, v___x_1277_);
if (v___x_1278_ == 0)
{
uint64_t v___x_1279_; uint64_t v___x_1280_; uint64_t v___x_1281_; 
v___x_1279_ = lean_uint32_to_uint64(v___y_1274_);
v___x_1280_ = 8388608ULL;
v___x_1281_ = lean_uint64_lor(v___x_1279_, v___x_1280_);
v___y_1263_ = v___y_1276_;
v___y_1264_ = v___y_1273_;
v___y_1265_ = v___y_1275_;
v___y_1266_ = v___x_1281_;
goto v___jp_1262_;
}
else
{
uint64_t v___x_1282_; 
v___x_1282_ = lean_uint32_to_uint64(v___y_1274_);
v___y_1263_ = v___y_1276_;
v___y_1264_ = v___y_1273_;
v___y_1265_ = v___y_1275_;
v___y_1266_ = v___x_1282_;
goto v___jp_1262_;
}
}
v___jp_1283_:
{
uint32_t v___x_1285_; uint32_t v_xFraction_1286_; uint32_t v_yFraction_1287_; uint32_t v___x_1288_; uint8_t v___x_1289_; 
v___x_1285_ = 8388607;
v_xFraction_1286_ = lean_uint32_land(v___y_766_, v___x_1285_);
v_yFraction_1287_ = lean_uint32_land(v___y_767_, v___x_1285_);
v___x_1288_ = 0;
v___x_1289_ = lean_uint32_dec_eq(v_ex_1170_, v___x_1288_);
if (v___x_1289_ == 0)
{
uint64_t v___x_1290_; uint64_t v___x_1291_; uint64_t v___x_1292_; 
v___x_1290_ = lean_uint32_to_uint64(v_xFraction_1286_);
v___x_1291_ = 8388608ULL;
v___x_1292_ = lean_uint64_lor(v___x_1290_, v___x_1291_);
v___y_1273_ = v___x_1285_;
v___y_1274_ = v_yFraction_1287_;
v___y_1275_ = v___y_1284_;
v___y_1276_ = v___x_1292_;
goto v___jp_1272_;
}
else
{
uint64_t v___x_1293_; 
v___x_1293_ = lean_uint32_to_uint64(v_xFraction_1286_);
v___y_1273_ = v___x_1285_;
v___y_1274_ = v_yFraction_1287_;
v___y_1275_ = v___y_1284_;
v___y_1276_ = v___x_1293_;
goto v___jp_1272_;
}
}
v___jp_1297_:
{
if (v___y_1299_ == 0)
{
v___y_1284_ = v___x_1296_;
goto v___jp_1283_;
}
else
{
v___y_1284_ = v___y_1298_;
goto v___jp_1283_;
}
}
v___jp_1300_:
{
if (v___y_1302_ == 0)
{
if (v___y_1303_ == 0)
{
v___y_1298_ = v___y_1301_;
v___y_1299_ = v___x_1296_;
goto v___jp_1297_;
}
else
{
v___y_1284_ = v___x_1296_;
goto v___jp_1283_;
}
}
else
{
v___y_1298_ = v___y_1301_;
v___y_1299_ = v___y_1303_;
goto v___jp_1297_;
}
}
v___jp_1304_:
{
uint32_t v___x_1307_; uint32_t v___x_1308_; uint32_t v___x_1309_; uint8_t v___x_1310_; 
v___x_1307_ = 2147483648;
v___x_1308_ = lean_uint32_land(v___y_767_, v___x_1307_);
v___x_1309_ = 0;
v___x_1310_ = lean_uint32_dec_eq(v___x_1308_, v___x_1309_);
if (v___x_1310_ == 0)
{
v___y_1301_ = v___y_1305_;
v___y_1302_ = v___y_1306_;
v___y_1303_ = v___x_1296_;
goto v___jp_1300_;
}
else
{
v___y_1301_ = v___y_1305_;
v___y_1302_ = v___y_1306_;
v___y_1303_ = v___y_1305_;
goto v___jp_1300_;
}
}
v___jp_1311_:
{
if (v___y_1312_ == 0)
{
uint32_t v___x_1313_; uint32_t v___x_1314_; uint32_t v___x_1315_; uint8_t v___x_1316_; 
v___x_1313_ = 2147483648;
v___x_1314_ = lean_uint32_land(v___y_766_, v___x_1313_);
v___x_1315_ = 0;
v___x_1316_ = lean_uint32_dec_eq(v___x_1314_, v___x_1315_);
if (v___x_1316_ == 0)
{
v___y_1305_ = v___y_1312_;
v___y_1306_ = v___x_1296_;
goto v___jp_1304_;
}
else
{
v___y_1305_ = v___y_1312_;
v___y_1306_ = v___y_1312_;
goto v___jp_1304_;
}
}
else
{
lean_object* v___x_1317_; lean_object* v___x_1318_; lean_object* v___x_1319_; uint32_t v___x_1320_; 
v___x_1317_ = lean_uint32_to_nat(v___y_766_);
v___x_1318_ = lean_uint32_to_nat(v___y_767_);
v___x_1319_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1317_, v___x_1318_);
v___x_1320_ = lean_uint32_of_nat(v___x_1319_);
lean_dec(v___x_1319_);
return v___x_1320_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object* v___y_1344_, lean_object* v___y_1345_){
_start:
{
uint32_t v___y_6391__boxed_1346_; uint32_t v___y_6392__boxed_1347_; uint32_t v_res_1348_; lean_object* v_r_1349_; 
v___y_6391__boxed_1346_ = lean_unbox_uint32(v___y_1344_);
lean_dec(v___y_1344_);
v___y_6392__boxed_1347_ = lean_unbox_uint32(v___y_1345_);
lean_dec(v___y_1345_);
v_res_1348_ = lp_competition_main___lam__3(v___y_6391__boxed_1346_, v___y_6392__boxed_1347_);
v_r_1349_ = lean_box_uint32(v_res_1348_);
return v_r_1349_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_1357_; lean_object* v___x_1358_; 
v___x_1357_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_1358_ = lean_io_getenv(v___x_1357_);
if (lean_obj_tag(v___x_1358_) == 0)
{
lean_object* v___f_1359_; lean_object* v___f_1360_; lean_object* v___x_1361_; lean_object* v___x_1362_; lean_object* v___x_1363_; 
v___f_1359_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_1360_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_1361_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_1362_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_1363_ = lp_competition_Bench_runFull(v___f_1359_, v___f_1360_, v___x_1361_, v___x_1362_);
return v___x_1363_;
}
else
{
lean_object* v___f_1364_; lean_object* v___f_1365_; lean_object* v___x_1366_; lean_object* v___x_1367_; lean_object* v___x_1368_; 
lean_dec_ref_known(v___x_1358_, 1);
v___f_1364_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_1365_ = ((lean_object*)(lp_competition_main___closed__5));
v___x_1366_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_1367_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_1368_ = lp_competition_Bench_Suite_run(v___f_1364_, v___f_1365_, v___x_1366_, v___x_1367_);
return v___x_1368_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_1369_){
_start:
{
lean_object* v_res_1370_; 
v_res_1370_ = _lean_main();
return v_res_1370_;
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
