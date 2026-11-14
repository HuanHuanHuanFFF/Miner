// Lean compiler output
// Module: R22Indexed8CostMain
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
lean_object* lp_competition_Bench_Suite_run(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lp_competition_Submission_R22IndexedResident8_guarded(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lean_io_getenv(lean_object*);
uint8_t l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(lean_object*, lean_object*);
lean_object* lp_competition_Submission_R22Resident8_guarded(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
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
LEAN_EXPORT uint32_t lp_competition_runRaw8___lam__1(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_runRaw8___lam__1___boxed(lean_object*, lean_object*);
static const lean_closure_object lp_competition_runRaw8___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_runRaw8___lam__1___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runRaw8___closed__0 = (const lean_object*)&lp_competition_runRaw8___closed__0_value;
static const lean_closure_object lp_competition_runRaw8___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_R22Resident8_guarded, .m_arity = 6, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runRaw8___closed__1 = (const lean_object*)&lp_competition_runRaw8___closed__1_value;
LEAN_EXPORT lean_object* lp_competition_runRaw8();
LEAN_EXPORT lean_object* lp_competition_runRaw8___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_runIndexed8___lam__1(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_runIndexed8___lam__1___boxed(lean_object*, lean_object*);
static const lean_closure_object lp_competition_runIndexed8___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_runIndexed8___lam__1___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runIndexed8___closed__0 = (const lean_object*)&lp_competition_runIndexed8___closed__0_value;
static const lean_closure_object lp_competition_runIndexed8___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_R22IndexedResident8_guarded, .m_arity = 6, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runIndexed8___closed__1 = (const lean_object*)&lp_competition_runIndexed8___closed__1_value;
LEAN_EXPORT lean_object* lp_competition_runIndexed8();
LEAN_EXPORT lean_object* lp_competition_runIndexed8___boxed(lean_object*);
static const lean_string_object lp_competition_main___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 14, .m_capacity = 14, .m_length = 13, .m_data = "BENCH_VARIANT"};
static const lean_object* lp_competition_main___closed__0 = (const lean_object*)&lp_competition_main___closed__0_value;
static const lean_string_object lp_competition_main___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 8, .m_capacity = 8, .m_length = 7, .m_data = "control"};
static const lean_object* lp_competition_main___closed__1 = (const lean_object*)&lp_competition_main___closed__1_value;
static const lean_ctor_object lp_competition_main___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__1_value)}};
static const lean_object* lp_competition_main___closed__2 = (const lean_object*)&lp_competition_main___closed__2_value;
static const lean_string_object lp_competition_main___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 5, .m_capacity = 5, .m_length = 4, .m_data = "raw8"};
static const lean_object* lp_competition_main___closed__3 = (const lean_object*)&lp_competition_main___closed__3_value;
static const lean_ctor_object lp_competition_main___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__3_value)}};
static const lean_object* lp_competition_main___closed__4 = (const lean_object*)&lp_competition_main___closed__4_value;
static const lean_string_object lp_competition_main___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "indexed8"};
static const lean_object* lp_competition_main___closed__5 = (const lean_object*)&lp_competition_main___closed__5_value;
static const lean_ctor_object lp_competition_main___closed__6_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__5_value)}};
static const lean_object* lp_competition_main___closed__6 = (const lean_object*)&lp_competition_main___closed__6_value;
static const lean_string_object lp_competition_main___closed__7_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 49, .m_capacity = 49, .m_length = 48, .m_data = "BENCH_VARIANT must be control, raw8, or indexed8"};
static const lean_object* lp_competition_main___closed__7 = (const lean_object*)&lp_competition_main___closed__7_value;
static const lean_ctor_object lp_competition_main___closed__8_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_main___closed__7_value)}};
static const lean_object* lp_competition_main___closed__8 = (const lean_object*)&lp_competition_main___closed__8_value;
LEAN_EXPORT lean_object* _lean_main();
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_runControl___lam__0(uint32_t v___y_1_, uint32_t v___y_2_){
_start:
{
uint8_t v___y_9_; uint8_t v___y_23_; uint8_t v___y_37_; uint8_t v___y_54_; float v___y_61_; float v___y_62_; float v___y_76_; uint8_t v___y_77_; float v___y_92_; uint8_t v___y_102_; uint32_t v___x_116_; uint32_t v_a_117_; uint32_t v___x_118_; uint32_t v___x_119_; uint32_t v___x_120_; uint8_t v___x_121_; 
v___x_116_ = 2147483647;
v_a_117_ = lean_uint32_land(v___y_1_, v___x_116_);
v___x_118_ = 201326591;
v___x_119_ = 1;
v___x_120_ = lean_uint32_sub(v_a_117_, v___x_119_);
v___x_121_ = lean_uint32_dec_le(v___x_118_, v___x_120_);
if (v___x_121_ == 0)
{
v___y_102_ = v___x_121_;
goto v___jp_101_;
}
else
{
uint32_t v___x_122_; uint8_t v___x_123_; 
v___x_122_ = 2139095040;
v___x_123_ = lean_uint32_dec_lt(v_a_117_, v___x_122_);
v___y_102_ = v___x_123_;
goto v___jp_101_;
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
}
}
LEAN_EXPORT lean_object* lp_competition_runControl___lam__0___boxed(lean_object* v___y_124_, lean_object* v___y_125_){
_start:
{
uint32_t v___y_2190__boxed_126_; uint32_t v___y_2191__boxed_127_; uint32_t v_res_128_; lean_object* v_r_129_; 
v___y_2190__boxed_126_ = lean_unbox_uint32(v___y_124_);
lean_dec(v___y_124_);
v___y_2191__boxed_127_ = lean_unbox_uint32(v___y_125_);
lean_dec(v___y_125_);
v_res_128_ = lp_competition_runControl___lam__0(v___y_2190__boxed_126_, v___y_2191__boxed_127_);
v_r_129_ = lean_box_uint32(v_res_128_);
return v_r_129_;
}
}
LEAN_EXPORT uint32_t lp_competition_runControl___lam__1(uint32_t v___y_130_, uint32_t v___y_131_){
_start:
{
uint32_t v___y_133_; uint32_t v___y_137_; uint32_t v___y_141_; uint32_t v___y_142_; uint32_t v___y_143_; uint8_t v___y_147_; uint32_t v___y_148_; uint64_t v___y_149_; uint64_t v___y_150_; uint32_t v___y_162_; uint32_t v___y_163_; uint32_t v___y_164_; uint8_t v___y_168_; uint32_t v___y_169_; uint64_t v___y_170_; uint64_t v___y_171_; uint8_t v___y_183_; uint8_t v___y_199_; uint8_t v___y_213_; uint8_t v___y_230_; float v___y_237_; float v___y_238_; float v___y_252_; uint8_t v___y_253_; float v___y_268_; uint32_t v___x_277_; uint32_t v___x_278_; uint8_t v___y_280_; uint32_t v___x_292_; uint32_t v___y_294_; uint32_t v___y_295_; uint32_t v___y_296_; uint32_t v___y_297_; uint8_t v___y_304_; uint32_t v___y_305_; uint32_t v___y_306_; uint32_t v___y_307_; uint8_t v___y_311_; uint64_t v___y_312_; uint32_t v___y_313_; uint64_t v___y_314_; uint64_t v___y_315_; uint8_t v___y_325_; uint32_t v___y_326_; uint64_t v___y_327_; uint64_t v___y_328_; uint8_t v___y_329_; uint64_t v___y_330_; uint8_t v___y_337_; uint64_t v___y_338_; uint64_t v___y_339_; uint32_t v___y_340_; uint64_t v___y_341_; uint8_t v___y_347_; uint64_t v___y_348_; uint32_t v___y_349_; uint64_t v___y_350_; uint64_t v___y_351_; uint64_t v___y_352_; uint64_t v___y_407_; uint8_t v___y_408_; uint32_t v___y_409_; uint64_t v___y_410_; uint64_t v___y_411_; uint64_t v___y_412_; uint64_t v___y_413_; uint64_t v___y_419_; uint8_t v___y_420_; uint64_t v___y_421_; uint64_t v___y_422_; uint64_t v___y_423_; uint32_t v___y_424_; uint64_t v___y_425_; uint64_t v___y_426_; uint64_t v___y_427_; uint8_t v___y_432_; uint32_t v___y_433_; uint64_t v___y_434_; uint64_t v___y_435_; uint64_t v___y_436_; uint64_t v___y_437_; uint64_t v___y_438_; uint8_t v___y_443_; uint64_t v___y_444_; uint64_t v___y_445_; uint64_t v___y_446_; uint64_t v___y_447_; uint32_t v___y_448_; uint64_t v___y_449_; uint64_t v___y_450_; uint64_t v___y_451_; uint8_t v___y_456_; uint32_t v___y_457_; uint64_t v___y_458_; uint64_t v___y_459_; uint64_t v___y_460_; uint64_t v___y_461_; uint64_t v___y_462_; uint64_t v___y_467_; uint8_t v___y_468_; uint64_t v___y_469_; uint64_t v___y_470_; uint32_t v___y_471_; uint64_t v___y_472_; uint64_t v___y_473_; uint64_t v___y_474_; uint64_t v___y_475_; uint64_t v___y_480_; uint8_t v___y_481_; uint32_t v___y_482_; uint64_t v___y_483_; uint64_t v___y_484_; uint64_t v___y_485_; uint64_t v___y_486_; uint8_t v___y_491_; uint64_t v___y_492_; uint64_t v___y_493_; uint64_t v___y_494_; uint32_t v___y_495_; uint64_t v___y_496_; uint64_t v___y_497_; uint64_t v___y_498_; uint64_t v___y_499_; uint8_t v___y_504_; uint64_t v___y_505_; uint32_t v___y_506_; uint64_t v___y_507_; uint64_t v___y_508_; uint64_t v___y_509_; uint64_t v___y_510_; uint8_t v___y_515_; uint64_t v___y_516_; uint64_t v___y_517_; uint64_t v___y_518_; uint32_t v___y_519_; uint64_t v___y_520_; uint64_t v___y_521_; uint8_t v___y_525_; uint64_t v___y_526_; uint32_t v___y_527_; uint64_t v___y_528_; uint8_t v___y_537_; uint64_t v___y_538_; uint32_t v___y_539_; uint64_t v___y_540_; uint64_t v___y_541_; uint64_t v___y_542_; uint32_t v_ex_575_; uint32_t v___x_576_; uint32_t v_ey_577_; uint8_t v___y_579_; uint32_t v___y_580_; uint64_t v___y_581_; uint64_t v___y_582_; uint64_t v___y_583_; uint8_t v___y_590_; uint32_t v___y_591_; uint64_t v___y_592_; uint64_t v___y_593_; uint32_t v___y_600_; uint8_t v___y_601_; uint32_t v___y_602_; uint64_t v___y_603_; uint8_t v___y_611_; uint32_t v___x_621_; uint32_t v___x_622_; uint8_t v___x_623_; uint8_t v___y_625_; uint8_t v___y_626_; uint8_t v___y_628_; uint8_t v___y_629_; uint8_t v___y_630_; uint8_t v___y_632_; uint8_t v___y_633_; uint8_t v___y_639_; 
v___x_277_ = 23;
v___x_278_ = lean_uint32_shift_right(v___y_130_, v___x_277_);
v___x_292_ = 255;
v_ex_575_ = lean_uint32_land(v___x_278_, v___x_292_);
v___x_576_ = lean_uint32_shift_right(v___y_131_, v___x_277_);
v_ey_577_ = lean_uint32_land(v___x_576_, v___x_292_);
v___x_621_ = lean_uint32_add(v_ex_575_, v_ey_577_);
v___x_622_ = 128;
v___x_623_ = lean_uint32_dec_lt(v___x_621_, v___x_622_);
if (v___x_623_ == 0)
{
uint32_t v___x_648_; uint32_t v_a_649_; uint32_t v___x_650_; uint32_t v___x_651_; uint32_t v___x_652_; uint8_t v___x_653_; 
v___x_648_ = 2147483647;
v_a_649_ = lean_uint32_land(v___y_130_, v___x_648_);
v___x_650_ = 201326591;
v___x_651_ = 1;
v___x_652_ = lean_uint32_sub(v_a_649_, v___x_651_);
v___x_653_ = lean_uint32_dec_le(v___x_650_, v___x_652_);
if (v___x_653_ == 0)
{
v___y_280_ = v___x_653_;
goto v___jp_279_;
}
else
{
uint32_t v___x_654_; uint8_t v___x_655_; 
v___x_654_ = 2139095040;
v___x_655_ = lean_uint32_dec_lt(v_a_649_, v___x_654_);
v___y_280_ = v___x_655_;
goto v___jp_279_;
}
}
else
{
uint32_t v___x_656_; uint32_t v___x_657_; uint32_t v___x_658_; uint8_t v___x_659_; 
v___x_656_ = 4278190080;
v___x_657_ = 1;
v___x_658_ = lean_uint32_shift_left(v___y_130_, v___x_657_);
v___x_659_ = lean_uint32_dec_le(v___x_656_, v___x_658_);
if (v___x_659_ == 0)
{
uint32_t v___x_660_; uint8_t v___x_661_; 
v___x_660_ = lean_uint32_shift_left(v___y_131_, v___x_657_);
v___x_661_ = lean_uint32_dec_le(v___x_656_, v___x_660_);
v___y_639_ = v___x_661_;
goto v___jp_638_;
}
else
{
v___y_639_ = v___x_659_;
goto v___jp_638_;
}
}
v___jp_132_:
{
uint32_t v___x_134_; uint32_t v___x_135_; 
v___x_134_ = 8388608;
v___x_135_ = lean_uint32_lor(v___y_133_, v___x_134_);
return v___x_135_;
}
v___jp_136_:
{
uint32_t v___x_138_; uint32_t v___x_139_; 
v___x_138_ = 8388608;
v___x_139_ = lean_uint32_lor(v___y_137_, v___x_138_);
return v___x_139_;
}
v___jp_140_:
{
uint32_t v___x_144_; uint32_t v___x_145_; 
v___x_144_ = lean_uint32_land(v___y_141_, v___y_142_);
v___x_145_ = lean_uint32_lor(v___y_143_, v___x_144_);
return v___x_145_;
}
v___jp_146_:
{
uint8_t v___x_151_; 
v___x_151_ = lean_uint64_dec_eq(v___y_150_, v___y_149_);
if (v___x_151_ == 0)
{
uint64_t v___x_152_; uint8_t v___x_153_; 
v___x_152_ = 8388608ULL;
v___x_153_ = lean_uint64_dec_eq(v___y_150_, v___x_152_);
if (v___x_153_ == 0)
{
uint32_t v___x_154_; 
v___x_154_ = lean_uint64_to_uint32(v___y_150_);
if (v___y_147_ == 0)
{
uint32_t v___x_155_; 
v___x_155_ = 0;
v___y_141_ = v___x_154_;
v___y_142_ = v___y_148_;
v___y_143_ = v___x_155_;
goto v___jp_140_;
}
else
{
uint32_t v___x_156_; 
v___x_156_ = 2147483648;
v___y_141_ = v___x_154_;
v___y_142_ = v___y_148_;
v___y_143_ = v___x_156_;
goto v___jp_140_;
}
}
else
{
if (v___y_147_ == 0)
{
uint32_t v___x_157_; 
v___x_157_ = 0;
v___y_137_ = v___x_157_;
goto v___jp_136_;
}
else
{
uint32_t v___x_158_; 
v___x_158_ = 2147483648;
v___y_137_ = v___x_158_;
goto v___jp_136_;
}
}
}
else
{
if (v___y_147_ == 0)
{
uint32_t v___x_159_; 
v___x_159_ = 0;
return v___x_159_;
}
else
{
uint32_t v___x_160_; 
v___x_160_ = 2147483648;
return v___x_160_;
}
}
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
v___x_172_ = lean_uint64_dec_eq(v___y_171_, v___y_170_);
if (v___x_172_ == 0)
{
uint64_t v___x_173_; uint8_t v___x_174_; 
v___x_173_ = 8388608ULL;
v___x_174_ = lean_uint64_dec_eq(v___y_171_, v___x_173_);
if (v___x_174_ == 0)
{
uint32_t v___x_175_; 
v___x_175_ = lean_uint64_to_uint32(v___y_171_);
if (v___y_168_ == 0)
{
uint32_t v___x_176_; 
v___x_176_ = 0;
v___y_162_ = v___x_175_;
v___y_163_ = v___y_169_;
v___y_164_ = v___x_176_;
goto v___jp_161_;
}
else
{
uint32_t v___x_177_; 
v___x_177_ = 2147483648;
v___y_162_ = v___x_175_;
v___y_163_ = v___y_169_;
v___y_164_ = v___x_177_;
goto v___jp_161_;
}
}
else
{
if (v___y_168_ == 0)
{
uint32_t v___x_178_; 
v___x_178_ = 0;
v___y_133_ = v___x_178_;
goto v___jp_132_;
}
else
{
uint32_t v___x_179_; 
v___x_179_ = 2147483648;
v___y_133_ = v___x_179_;
goto v___jp_132_;
}
}
}
else
{
if (v___y_168_ == 0)
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
if (v___y_183_ == 0)
{
uint32_t v___x_184_; 
v___x_184_ = lp_competition_Submission_FastMul_mul(v___y_130_, v___y_131_);
return v___x_184_;
}
else
{
uint32_t v___x_185_; uint32_t v___x_186_; 
v___x_185_ = 4194304;
v___x_186_ = lean_uint32_lor(v___y_131_, v___x_185_);
return v___x_186_;
}
}
v___jp_187_:
{
uint32_t v___x_188_; uint32_t v___x_189_; uint32_t v___x_190_; uint32_t v___x_191_; uint8_t v___x_192_; 
v___x_188_ = 23;
v___x_189_ = lean_uint32_shift_right(v___y_131_, v___x_188_);
v___x_190_ = 255;
v___x_191_ = lean_uint32_land(v___x_189_, v___x_190_);
v___x_192_ = lean_uint32_dec_eq(v___x_191_, v___x_190_);
if (v___x_192_ == 0)
{
v___y_183_ = v___x_192_;
goto v___jp_182_;
}
else
{
uint32_t v___x_193_; uint32_t v___x_194_; uint32_t v___x_195_; uint8_t v___x_196_; 
v___x_193_ = 8388607;
v___x_194_ = lean_uint32_land(v___y_131_, v___x_193_);
v___x_195_ = 0;
v___x_196_ = lean_uint32_dec_eq(v___x_194_, v___x_195_);
if (v___x_196_ == 0)
{
v___y_183_ = v___x_192_;
goto v___jp_182_;
}
else
{
uint32_t v___x_197_; 
v___x_197_ = lp_competition_Submission_FastMul_mul(v___y_130_, v___y_131_);
return v___x_197_;
}
}
}
v___jp_198_:
{
if (v___y_199_ == 0)
{
goto v___jp_187_;
}
else
{
uint32_t v___x_200_; uint32_t v___x_201_; 
v___x_200_ = 4194304;
v___x_201_ = lean_uint32_lor(v___y_130_, v___x_200_);
return v___x_201_;
}
}
v___jp_202_:
{
uint32_t v___x_203_; uint32_t v___x_204_; uint32_t v___x_205_; uint32_t v___x_206_; uint8_t v___x_207_; 
v___x_203_ = 23;
v___x_204_ = lean_uint32_shift_right(v___y_130_, v___x_203_);
v___x_205_ = 255;
v___x_206_ = lean_uint32_land(v___x_204_, v___x_205_);
v___x_207_ = lean_uint32_dec_eq(v___x_206_, v___x_205_);
if (v___x_207_ == 0)
{
v___y_199_ = v___x_207_;
goto v___jp_198_;
}
else
{
uint32_t v___x_208_; uint32_t v___x_209_; uint32_t v___x_210_; uint8_t v___x_211_; 
v___x_208_ = 8388607;
v___x_209_ = lean_uint32_land(v___y_130_, v___x_208_);
v___x_210_ = 0;
v___x_211_ = lean_uint32_dec_eq(v___x_209_, v___x_210_);
if (v___x_211_ == 0)
{
v___y_199_ = v___x_207_;
goto v___jp_198_;
}
else
{
goto v___jp_187_;
}
}
}
v___jp_212_:
{
if (v___y_213_ == 0)
{
goto v___jp_202_;
}
else
{
uint32_t v___x_214_; uint32_t v___x_215_; uint32_t v___x_216_; uint8_t v___x_217_; 
v___x_214_ = 4194304;
v___x_215_ = lean_uint32_land(v___y_131_, v___x_214_);
v___x_216_ = 0;
v___x_217_ = lean_uint32_dec_eq(v___x_215_, v___x_216_);
if (v___x_217_ == 0)
{
goto v___jp_202_;
}
else
{
uint32_t v___x_218_; 
v___x_218_ = lean_uint32_lor(v___y_131_, v___x_214_);
return v___x_218_;
}
}
}
v___jp_219_:
{
uint32_t v___x_220_; uint32_t v___x_221_; uint32_t v___x_222_; uint32_t v___x_223_; uint8_t v___x_224_; 
v___x_220_ = 23;
v___x_221_ = lean_uint32_shift_right(v___y_131_, v___x_220_);
v___x_222_ = 255;
v___x_223_ = lean_uint32_land(v___x_221_, v___x_222_);
v___x_224_ = lean_uint32_dec_eq(v___x_223_, v___x_222_);
if (v___x_224_ == 0)
{
v___y_213_ = v___x_224_;
goto v___jp_212_;
}
else
{
uint32_t v___x_225_; uint32_t v___x_226_; uint32_t v___x_227_; uint8_t v___x_228_; 
v___x_225_ = 8388607;
v___x_226_ = lean_uint32_land(v___y_131_, v___x_225_);
v___x_227_ = 0;
v___x_228_ = lean_uint32_dec_eq(v___x_226_, v___x_227_);
if (v___x_228_ == 0)
{
v___y_213_ = v___x_224_;
goto v___jp_212_;
}
else
{
goto v___jp_202_;
}
}
}
v___jp_229_:
{
if (v___y_230_ == 0)
{
goto v___jp_219_;
}
else
{
uint32_t v___x_231_; uint32_t v___x_232_; uint32_t v___x_233_; uint8_t v___x_234_; 
v___x_231_ = 4194304;
v___x_232_ = lean_uint32_land(v___y_130_, v___x_231_);
v___x_233_ = 0;
v___x_234_ = lean_uint32_dec_eq(v___x_232_, v___x_233_);
if (v___x_234_ == 0)
{
goto v___jp_219_;
}
else
{
uint32_t v___x_235_; 
v___x_235_ = lean_uint32_lor(v___y_130_, v___x_231_);
return v___x_235_;
}
}
}
v___jp_236_:
{
float v_result_239_; uint8_t v___x_240_; 
v_result_239_ = lean_float32_mul(v___y_237_, v___y_238_);
v___x_240_ = lean_float32_beq(v_result_239_, v_result_239_);
if (v___x_240_ == 0)
{
uint32_t v___x_241_; uint32_t v___x_242_; uint32_t v___x_243_; uint32_t v___x_244_; uint8_t v___x_245_; 
v___x_241_ = 23;
v___x_242_ = lean_uint32_shift_right(v___y_130_, v___x_241_);
v___x_243_ = 255;
v___x_244_ = lean_uint32_land(v___x_242_, v___x_243_);
v___x_245_ = lean_uint32_dec_eq(v___x_244_, v___x_243_);
if (v___x_245_ == 0)
{
v___y_230_ = v___x_245_;
goto v___jp_229_;
}
else
{
uint32_t v___x_246_; uint32_t v___x_247_; uint32_t v___x_248_; uint8_t v___x_249_; 
v___x_246_ = 8388607;
v___x_247_ = lean_uint32_land(v___y_130_, v___x_246_);
v___x_248_ = 0;
v___x_249_ = lean_uint32_dec_eq(v___x_247_, v___x_248_);
if (v___x_249_ == 0)
{
v___y_230_ = v___x_245_;
goto v___jp_229_;
}
else
{
goto v___jp_219_;
}
}
}
else
{
uint32_t v___x_250_; 
v___x_250_ = lean_float32_to_bits(v_result_239_);
return v___x_250_;
}
}
v___jp_251_:
{
if (v___y_253_ == 0)
{
float v___x_254_; 
v___x_254_ = lean_float32_of_bits(v___y_131_);
v___y_237_ = v___y_252_;
v___y_238_ = v___x_254_;
goto v___jp_236_;
}
else
{
uint32_t v___x_255_; uint32_t v___x_256_; uint32_t v___x_257_; uint32_t v___x_258_; float v___x_259_; lean_object* v___x_260_; uint32_t v___x_261_; uint32_t v___x_262_; lean_object* v___x_263_; lean_object* v___x_264_; float v___x_265_; float v___x_266_; 
v___x_255_ = 8388607;
v___x_256_ = lean_uint32_land(v___y_131_, v___x_255_);
v___x_257_ = 8388608;
v___x_258_ = lean_uint32_lor(v___x_256_, v___x_257_);
v___x_259_ = lean_uint32_to_float32(v___x_258_);
v___x_260_ = lp_competition_R2W01b_scaleTable;
v___x_261_ = 23;
v___x_262_ = lean_uint32_shift_right(v___y_131_, v___x_261_);
v___x_263_ = lean_uint32_to_nat(v___x_262_);
v___x_264_ = lean_array_fget_borrowed(v___x_260_, v___x_263_);
lean_dec(v___x_263_);
v___x_265_ = lean_unbox_float32(v___x_264_);
v___x_266_ = lean_float32_mul(v___x_259_, v___x_265_);
v___y_237_ = v___y_252_;
v___y_238_ = v___x_266_;
goto v___jp_236_;
}
}
v___jp_267_:
{
uint32_t v___x_269_; uint32_t v_a_270_; uint32_t v___x_271_; uint32_t v___x_272_; uint32_t v___x_273_; uint8_t v___x_274_; 
v___x_269_ = 2147483647;
v_a_270_ = lean_uint32_land(v___y_131_, v___x_269_);
v___x_271_ = 201326591;
v___x_272_ = 1;
v___x_273_ = lean_uint32_sub(v_a_270_, v___x_272_);
v___x_274_ = lean_uint32_dec_le(v___x_271_, v___x_273_);
if (v___x_274_ == 0)
{
v___y_252_ = v___y_268_;
v___y_253_ = v___x_274_;
goto v___jp_251_;
}
else
{
uint32_t v___x_275_; uint8_t v___x_276_; 
v___x_275_ = 2139095040;
v___x_276_ = lean_uint32_dec_lt(v_a_270_, v___x_275_);
v___y_252_ = v___y_268_;
v___y_253_ = v___x_276_;
goto v___jp_251_;
}
}
v___jp_279_:
{
if (v___y_280_ == 0)
{
float v___x_281_; 
v___x_281_ = lean_float32_of_bits(v___y_130_);
v___y_268_ = v___x_281_;
goto v___jp_267_;
}
else
{
uint32_t v___x_282_; uint32_t v___x_283_; uint32_t v___x_284_; uint32_t v___x_285_; float v___x_286_; lean_object* v___x_287_; lean_object* v___x_288_; lean_object* v___x_289_; float v___x_290_; float v___x_291_; 
v___x_282_ = 8388607;
v___x_283_ = lean_uint32_land(v___y_130_, v___x_282_);
v___x_284_ = 8388608;
v___x_285_ = lean_uint32_lor(v___x_283_, v___x_284_);
v___x_286_ = lean_uint32_to_float32(v___x_285_);
v___x_287_ = lp_competition_R2W01b_scaleTable;
v___x_288_ = lean_uint32_to_nat(v___x_278_);
v___x_289_ = lean_array_fget_borrowed(v___x_287_, v___x_288_);
lean_dec(v___x_288_);
v___x_290_ = lean_unbox_float32(v___x_289_);
v___x_291_ = lean_float32_mul(v___x_286_, v___x_290_);
v___y_268_ = v___x_291_;
goto v___jp_267_;
}
}
v___jp_293_:
{
uint32_t v___x_298_; uint32_t v___x_299_; uint32_t v___x_300_; uint32_t v___x_301_; uint32_t v___x_302_; 
v___x_298_ = lean_uint32_land(v___y_296_, v___x_292_);
v___x_299_ = lean_uint32_shift_left(v___x_298_, v___x_277_);
v___x_300_ = lean_uint32_lor(v___y_297_, v___x_299_);
v___x_301_ = lean_uint32_land(v___y_294_, v___y_295_);
v___x_302_ = lean_uint32_lor(v___x_300_, v___x_301_);
return v___x_302_;
}
v___jp_303_:
{
if (v___y_304_ == 0)
{
uint32_t v___x_308_; 
v___x_308_ = 0;
v___y_294_ = v___y_307_;
v___y_295_ = v___y_305_;
v___y_296_ = v___y_306_;
v___y_297_ = v___x_308_;
goto v___jp_293_;
}
else
{
uint32_t v___x_309_; 
v___x_309_ = 2147483648;
v___y_294_ = v___y_307_;
v___y_295_ = v___y_305_;
v___y_296_ = v___y_306_;
v___y_297_ = v___x_309_;
goto v___jp_293_;
}
}
v___jp_310_:
{
uint64_t v___x_316_; uint64_t v_encodedExponent_317_; uint32_t v___x_318_; uint64_t v___x_319_; uint8_t v___x_320_; 
v___x_316_ = 171ULL;
v_encodedExponent_317_ = lean_uint64_sub(v___y_314_, v___x_316_);
v___x_318_ = lean_uint64_to_uint32(v_encodedExponent_317_);
v___x_319_ = 8388608ULL;
v___x_320_ = lean_uint64_dec_lt(v___y_315_, v___x_319_);
if (v___x_320_ == 0)
{
uint64_t v___x_321_; uint32_t v___x_322_; 
v___x_321_ = lean_uint64_sub(v___y_315_, v___x_319_);
v___x_322_ = lean_uint64_to_uint32(v___x_321_);
v___y_304_ = v___y_311_;
v___y_305_ = v___y_313_;
v___y_306_ = v___x_318_;
v___y_307_ = v___x_322_;
goto v___jp_303_;
}
else
{
uint32_t v___x_323_; 
v___x_323_ = lean_uint64_to_uint32(v___y_312_);
v___y_304_ = v___y_311_;
v___y_305_ = v___y_313_;
v___y_306_ = v___x_318_;
v___y_307_ = v___x_323_;
goto v___jp_303_;
}
}
v___jp_324_:
{
uint64_t v___x_331_; uint8_t v___x_332_; 
v___x_331_ = 425ULL;
v___x_332_ = lean_uint64_dec_lt(v___x_331_, v___y_330_);
if (v___x_332_ == 0)
{
if (v___y_329_ == 0)
{
v___y_311_ = v___y_325_;
v___y_312_ = v___y_327_;
v___y_313_ = v___y_326_;
v___y_314_ = v___y_330_;
v___y_315_ = v___y_328_;
goto v___jp_310_;
}
else
{
uint64_t v___x_333_; 
v___x_333_ = 8388608ULL;
v___y_311_ = v___y_325_;
v___y_312_ = v___y_327_;
v___y_313_ = v___y_326_;
v___y_314_ = v___y_330_;
v___y_315_ = v___x_333_;
goto v___jp_310_;
}
}
else
{
if (v___y_325_ == 0)
{
uint32_t v___x_334_; 
v___x_334_ = 2139095040;
return v___x_334_;
}
else
{
uint32_t v___x_335_; 
v___x_335_ = 4286578688;
return v___x_335_;
}
}
}
v___jp_336_:
{
uint64_t v___x_342_; uint8_t v_carry_343_; 
v___x_342_ = 16777216ULL;
v_carry_343_ = lean_uint64_dec_eq(v___y_341_, v___x_342_);
if (v_carry_343_ == 0)
{
v___y_325_ = v___y_337_;
v___y_326_ = v___y_340_;
v___y_327_ = v___y_339_;
v___y_328_ = v___y_341_;
v___y_329_ = v_carry_343_;
v___y_330_ = v___y_338_;
goto v___jp_324_;
}
else
{
uint64_t v___x_344_; uint64_t v___x_345_; 
v___x_344_ = 1ULL;
v___x_345_ = lean_uint64_add(v___y_338_, v___x_344_);
v___y_325_ = v___y_337_;
v___y_326_ = v___y_340_;
v___y_327_ = v___y_339_;
v___y_328_ = v___y_341_;
v___y_329_ = v_carry_343_;
v___y_330_ = v___x_345_;
goto v___jp_324_;
}
}
v___jp_346_:
{
uint64_t v_position_353_; uint64_t v___x_354_; uint8_t v___x_355_; 
v_position_353_ = lean_uint64_add(v___y_352_, v___y_351_);
v___x_354_ = 172ULL;
v___x_355_ = lean_uint64_dec_lt(v_position_353_, v___x_354_);
if (v___x_355_ == 0)
{
uint64_t v___x_356_; uint8_t v___x_357_; 
v___x_356_ = 23ULL;
v___x_357_ = lean_uint64_dec_lt(v___y_352_, v___x_356_);
if (v___x_357_ == 0)
{
uint64_t v___x_358_; uint8_t v___x_359_; 
v___x_358_ = lean_uint64_sub(v___y_352_, v___x_356_);
v___x_359_ = lean_uint64_dec_eq(v___x_358_, v___y_350_);
if (v___x_359_ == 0)
{
uint64_t v___x_360_; uint8_t v___x_361_; 
v___x_360_ = 64ULL;
v___x_361_ = lean_uint64_dec_lt(v___x_358_, v___x_360_);
if (v___x_361_ == 0)
{
uint8_t v___x_362_; 
v___x_362_ = lean_uint64_dec_eq(v___x_358_, v___x_360_);
if (v___x_362_ == 0)
{
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v___y_350_;
goto v___jp_336_;
}
else
{
uint64_t v___x_363_; uint8_t v___x_364_; 
v___x_363_ = 9223372036854775808ULL;
v___x_364_ = lean_uint64_dec_lt(v___x_363_, v___y_348_);
if (v___x_364_ == 0)
{
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v___y_350_;
goto v___jp_336_;
}
else
{
uint64_t v___x_365_; 
v___x_365_ = 1ULL;
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v___x_365_;
goto v___jp_336_;
}
}
}
else
{
uint64_t v_quotient_366_; uint64_t v___x_367_; uint64_t v___x_368_; uint64_t v___x_369_; uint64_t v_remainder_370_; uint64_t v___x_371_; uint64_t v_half_372_; uint8_t v___x_373_; 
v_quotient_366_ = lean_uint64_shift_right(v___y_348_, v___x_358_);
v___x_367_ = 1ULL;
v___x_368_ = lean_uint64_shift_left(v___x_367_, v___x_358_);
v___x_369_ = lean_uint64_sub(v___x_368_, v___x_367_);
v_remainder_370_ = lean_uint64_land(v___y_348_, v___x_369_);
v___x_371_ = lean_uint64_sub(v___x_358_, v___x_367_);
v_half_372_ = lean_uint64_shift_left(v___x_367_, v___x_371_);
v___x_373_ = lean_uint64_dec_lt(v_remainder_370_, v_half_372_);
if (v___x_373_ == 0)
{
uint8_t v___x_374_; 
v___x_374_ = lean_uint64_dec_lt(v_half_372_, v_remainder_370_);
if (v___x_374_ == 0)
{
uint64_t v___x_375_; uint8_t v___x_376_; 
v___x_375_ = lean_uint64_land(v_quotient_366_, v___x_367_);
v___x_376_ = lean_uint64_dec_eq(v___x_375_, v___y_350_);
if (v___x_376_ == 0)
{
uint64_t v___x_377_; 
v___x_377_ = lean_uint64_add(v_quotient_366_, v___x_367_);
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v___x_377_;
goto v___jp_336_;
}
else
{
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v_quotient_366_;
goto v___jp_336_;
}
}
else
{
uint64_t v___x_378_; 
v___x_378_ = lean_uint64_add(v_quotient_366_, v___x_367_);
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v___x_378_;
goto v___jp_336_;
}
}
else
{
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v_quotient_366_;
goto v___jp_336_;
}
}
}
else
{
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v___y_348_;
goto v___jp_336_;
}
}
else
{
uint64_t v___x_379_; uint64_t v___x_380_; 
v___x_379_ = lean_uint64_sub(v___x_356_, v___y_352_);
v___x_380_ = lean_uint64_shift_left(v___y_348_, v___x_379_);
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v___x_380_;
goto v___jp_336_;
}
}
else
{
uint64_t v___x_381_; uint8_t v___x_382_; 
v___x_381_ = 149ULL;
v___x_382_ = lean_uint64_dec_lt(v___y_351_, v___x_381_);
if (v___x_382_ == 0)
{
uint64_t v___x_383_; uint64_t v___x_384_; 
v___x_383_ = lean_uint64_sub(v___y_351_, v___x_381_);
v___x_384_ = lean_uint64_shift_left(v___y_348_, v___x_383_);
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v___x_384_;
goto v___jp_146_;
}
else
{
uint64_t v___x_385_; uint8_t v___x_386_; 
v___x_385_ = lean_uint64_sub(v___x_381_, v___y_351_);
v___x_386_ = lean_uint64_dec_eq(v___x_385_, v___y_350_);
if (v___x_386_ == 0)
{
uint64_t v___x_387_; uint8_t v___x_388_; 
v___x_387_ = 64ULL;
v___x_388_ = lean_uint64_dec_lt(v___x_385_, v___x_387_);
if (v___x_388_ == 0)
{
uint8_t v___x_389_; 
v___x_389_ = lean_uint64_dec_eq(v___x_385_, v___x_387_);
if (v___x_389_ == 0)
{
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v___y_350_;
goto v___jp_146_;
}
else
{
uint64_t v___x_390_; uint8_t v___x_391_; 
v___x_390_ = 9223372036854775808ULL;
v___x_391_ = lean_uint64_dec_lt(v___x_390_, v___y_348_);
if (v___x_391_ == 0)
{
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v___y_350_;
goto v___jp_146_;
}
else
{
uint64_t v___x_392_; 
v___x_392_ = 1ULL;
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v___x_392_;
goto v___jp_146_;
}
}
}
else
{
uint64_t v_quotient_393_; uint64_t v___x_394_; uint64_t v___x_395_; uint64_t v___x_396_; uint64_t v_remainder_397_; uint64_t v___x_398_; uint64_t v_half_399_; uint8_t v___x_400_; 
v_quotient_393_ = lean_uint64_shift_right(v___y_348_, v___x_385_);
v___x_394_ = 1ULL;
v___x_395_ = lean_uint64_shift_left(v___x_394_, v___x_385_);
v___x_396_ = lean_uint64_sub(v___x_395_, v___x_394_);
v_remainder_397_ = lean_uint64_land(v___y_348_, v___x_396_);
v___x_398_ = lean_uint64_sub(v___x_385_, v___x_394_);
v_half_399_ = lean_uint64_shift_left(v___x_394_, v___x_398_);
v___x_400_ = lean_uint64_dec_lt(v_remainder_397_, v_half_399_);
if (v___x_400_ == 0)
{
uint8_t v___x_401_; 
v___x_401_ = lean_uint64_dec_lt(v_half_399_, v_remainder_397_);
if (v___x_401_ == 0)
{
uint64_t v___x_402_; uint8_t v___x_403_; 
v___x_402_ = lean_uint64_land(v_quotient_393_, v___x_394_);
v___x_403_ = lean_uint64_dec_eq(v___x_402_, v___y_350_);
if (v___x_403_ == 0)
{
uint64_t v___x_404_; 
v___x_404_ = lean_uint64_add(v_quotient_393_, v___x_394_);
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v___x_404_;
goto v___jp_146_;
}
else
{
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v_quotient_393_;
goto v___jp_146_;
}
}
else
{
uint64_t v___x_405_; 
v___x_405_ = lean_uint64_add(v_quotient_393_, v___x_394_);
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v___x_405_;
goto v___jp_146_;
}
}
else
{
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v_quotient_393_;
goto v___jp_146_;
}
}
}
else
{
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v___y_348_;
goto v___jp_146_;
}
}
}
}
v___jp_406_:
{
uint64_t v___x_414_; uint64_t v___x_415_; uint8_t v___x_416_; 
v___x_414_ = 1ULL;
v___x_415_ = lean_uint64_shift_right(v___y_407_, v___x_414_);
v___x_416_ = lean_uint64_dec_eq(v___x_415_, v___y_411_);
if (v___x_416_ == 0)
{
uint64_t v___x_417_; 
v___x_417_ = lean_uint64_add(v___y_413_, v___x_414_);
v___y_347_ = v___y_408_;
v___y_348_ = v___y_410_;
v___y_349_ = v___y_409_;
v___y_350_ = v___y_411_;
v___y_351_ = v___y_412_;
v___y_352_ = v___x_417_;
goto v___jp_346_;
}
else
{
v___y_347_ = v___y_408_;
v___y_348_ = v___y_410_;
v___y_349_ = v___y_409_;
v___y_350_ = v___y_411_;
v___y_351_ = v___y_412_;
v___y_352_ = v___y_413_;
goto v___jp_346_;
}
}
v___jp_418_:
{
uint64_t v___x_428_; uint8_t v___x_429_; 
v___x_428_ = lean_uint64_shift_right(v___y_425_, v___y_419_);
v___x_429_ = lean_uint64_dec_eq(v___x_428_, v___y_422_);
if (v___x_429_ == 0)
{
uint64_t v___x_430_; 
v___x_430_ = lean_uint64_add(v___y_421_, v___y_419_);
v___y_407_ = v___y_427_;
v___y_408_ = v___y_420_;
v___y_409_ = v___y_424_;
v___y_410_ = v___y_423_;
v___y_411_ = v___y_422_;
v___y_412_ = v___y_426_;
v___y_413_ = v___x_430_;
goto v___jp_406_;
}
else
{
v___y_407_ = v___y_427_;
v___y_408_ = v___y_420_;
v___y_409_ = v___y_424_;
v___y_410_ = v___y_423_;
v___y_411_ = v___y_422_;
v___y_412_ = v___y_426_;
v___y_413_ = v___y_421_;
goto v___jp_406_;
}
}
v___jp_431_:
{
uint64_t v___x_439_; uint64_t v___x_440_; uint8_t v___x_441_; 
v___x_439_ = 2ULL;
v___x_440_ = lean_uint64_shift_right(v___y_436_, v___x_439_);
v___x_441_ = lean_uint64_dec_eq(v___x_440_, v___y_435_);
if (v___x_441_ == 0)
{
v___y_419_ = v___x_439_;
v___y_420_ = v___y_432_;
v___y_421_ = v___y_438_;
v___y_422_ = v___y_435_;
v___y_423_ = v___y_434_;
v___y_424_ = v___y_433_;
v___y_425_ = v___y_436_;
v___y_426_ = v___y_437_;
v___y_427_ = v___x_440_;
goto v___jp_418_;
}
else
{
v___y_419_ = v___x_439_;
v___y_420_ = v___y_432_;
v___y_421_ = v___y_438_;
v___y_422_ = v___y_435_;
v___y_423_ = v___y_434_;
v___y_424_ = v___y_433_;
v___y_425_ = v___y_436_;
v___y_426_ = v___y_437_;
v___y_427_ = v___y_436_;
goto v___jp_418_;
}
}
v___jp_442_:
{
uint64_t v___x_452_; uint8_t v___x_453_; 
v___x_452_ = lean_uint64_shift_right(v___y_449_, v___y_444_);
v___x_453_ = lean_uint64_dec_eq(v___x_452_, v___y_446_);
if (v___x_453_ == 0)
{
uint64_t v___x_454_; 
v___x_454_ = lean_uint64_add(v___y_445_, v___y_444_);
v___y_432_ = v___y_443_;
v___y_433_ = v___y_448_;
v___y_434_ = v___y_447_;
v___y_435_ = v___y_446_;
v___y_436_ = v___y_451_;
v___y_437_ = v___y_450_;
v___y_438_ = v___x_454_;
goto v___jp_431_;
}
else
{
v___y_432_ = v___y_443_;
v___y_433_ = v___y_448_;
v___y_434_ = v___y_447_;
v___y_435_ = v___y_446_;
v___y_436_ = v___y_451_;
v___y_437_ = v___y_450_;
v___y_438_ = v___y_445_;
goto v___jp_431_;
}
}
v___jp_455_:
{
uint64_t v___x_463_; uint64_t v___x_464_; uint8_t v___x_465_; 
v___x_463_ = 4ULL;
v___x_464_ = lean_uint64_shift_right(v___y_460_, v___x_463_);
v___x_465_ = lean_uint64_dec_eq(v___x_464_, v___y_459_);
if (v___x_465_ == 0)
{
v___y_443_ = v___y_456_;
v___y_444_ = v___x_463_;
v___y_445_ = v___y_462_;
v___y_446_ = v___y_459_;
v___y_447_ = v___y_458_;
v___y_448_ = v___y_457_;
v___y_449_ = v___y_460_;
v___y_450_ = v___y_461_;
v___y_451_ = v___x_464_;
goto v___jp_442_;
}
else
{
v___y_443_ = v___y_456_;
v___y_444_ = v___x_463_;
v___y_445_ = v___y_462_;
v___y_446_ = v___y_459_;
v___y_447_ = v___y_458_;
v___y_448_ = v___y_457_;
v___y_449_ = v___y_460_;
v___y_450_ = v___y_461_;
v___y_451_ = v___y_460_;
goto v___jp_442_;
}
}
v___jp_466_:
{
uint64_t v___x_476_; uint8_t v___x_477_; 
v___x_476_ = lean_uint64_shift_right(v___y_467_, v___y_474_);
v___x_477_ = lean_uint64_dec_eq(v___x_476_, v___y_469_);
if (v___x_477_ == 0)
{
uint64_t v___x_478_; 
v___x_478_ = lean_uint64_add(v___y_472_, v___y_474_);
v___y_456_ = v___y_468_;
v___y_457_ = v___y_471_;
v___y_458_ = v___y_470_;
v___y_459_ = v___y_469_;
v___y_460_ = v___y_475_;
v___y_461_ = v___y_473_;
v___y_462_ = v___x_478_;
goto v___jp_455_;
}
else
{
v___y_456_ = v___y_468_;
v___y_457_ = v___y_471_;
v___y_458_ = v___y_470_;
v___y_459_ = v___y_469_;
v___y_460_ = v___y_475_;
v___y_461_ = v___y_473_;
v___y_462_ = v___y_472_;
goto v___jp_455_;
}
}
v___jp_479_:
{
uint64_t v___x_487_; uint64_t v___x_488_; uint8_t v___x_489_; 
v___x_487_ = 8ULL;
v___x_488_ = lean_uint64_shift_right(v___y_480_, v___x_487_);
v___x_489_ = lean_uint64_dec_eq(v___x_488_, v___y_484_);
if (v___x_489_ == 0)
{
v___y_467_ = v___y_480_;
v___y_468_ = v___y_481_;
v___y_469_ = v___y_484_;
v___y_470_ = v___y_483_;
v___y_471_ = v___y_482_;
v___y_472_ = v___y_486_;
v___y_473_ = v___y_485_;
v___y_474_ = v___x_487_;
v___y_475_ = v___x_488_;
goto v___jp_466_;
}
else
{
v___y_467_ = v___y_480_;
v___y_468_ = v___y_481_;
v___y_469_ = v___y_484_;
v___y_470_ = v___y_483_;
v___y_471_ = v___y_482_;
v___y_472_ = v___y_486_;
v___y_473_ = v___y_485_;
v___y_474_ = v___x_487_;
v___y_475_ = v___y_480_;
goto v___jp_466_;
}
}
v___jp_490_:
{
uint64_t v___x_500_; uint8_t v___x_501_; 
v___x_500_ = lean_uint64_shift_right(v___y_492_, v___y_497_);
v___x_501_ = lean_uint64_dec_eq(v___x_500_, v___y_493_);
if (v___x_501_ == 0)
{
uint64_t v___x_502_; 
v___x_502_ = lean_uint64_add(v___y_498_, v___y_497_);
v___y_480_ = v___y_499_;
v___y_481_ = v___y_491_;
v___y_482_ = v___y_495_;
v___y_483_ = v___y_494_;
v___y_484_ = v___y_493_;
v___y_485_ = v___y_496_;
v___y_486_ = v___x_502_;
goto v___jp_479_;
}
else
{
v___y_480_ = v___y_499_;
v___y_481_ = v___y_491_;
v___y_482_ = v___y_495_;
v___y_483_ = v___y_494_;
v___y_484_ = v___y_493_;
v___y_485_ = v___y_496_;
v___y_486_ = v___y_498_;
goto v___jp_479_;
}
}
v___jp_503_:
{
uint64_t v___x_511_; uint64_t v___x_512_; uint8_t v___x_513_; 
v___x_511_ = 16ULL;
v___x_512_ = lean_uint64_shift_right(v___y_505_, v___x_511_);
v___x_513_ = lean_uint64_dec_eq(v___x_512_, v___y_508_);
if (v___x_513_ == 0)
{
v___y_491_ = v___y_504_;
v___y_492_ = v___y_505_;
v___y_493_ = v___y_508_;
v___y_494_ = v___y_507_;
v___y_495_ = v___y_506_;
v___y_496_ = v___y_509_;
v___y_497_ = v___x_511_;
v___y_498_ = v___y_510_;
v___y_499_ = v___x_512_;
goto v___jp_490_;
}
else
{
v___y_491_ = v___y_504_;
v___y_492_ = v___y_505_;
v___y_493_ = v___y_508_;
v___y_494_ = v___y_507_;
v___y_495_ = v___y_506_;
v___y_496_ = v___y_509_;
v___y_497_ = v___x_511_;
v___y_498_ = v___y_510_;
v___y_499_ = v___y_505_;
goto v___jp_490_;
}
}
v___jp_514_:
{
uint64_t v___x_522_; uint8_t v___x_523_; 
v___x_522_ = lean_uint64_shift_right(v___y_518_, v___y_516_);
v___x_523_ = lean_uint64_dec_eq(v___x_522_, v___y_517_);
if (v___x_523_ == 0)
{
v___y_504_ = v___y_515_;
v___y_505_ = v___y_521_;
v___y_506_ = v___y_519_;
v___y_507_ = v___y_518_;
v___y_508_ = v___y_517_;
v___y_509_ = v___y_520_;
v___y_510_ = v___y_516_;
goto v___jp_503_;
}
else
{
v___y_504_ = v___y_515_;
v___y_505_ = v___y_521_;
v___y_506_ = v___y_519_;
v___y_507_ = v___y_518_;
v___y_508_ = v___y_517_;
v___y_509_ = v___y_520_;
v___y_510_ = v___y_517_;
goto v___jp_503_;
}
}
v___jp_524_:
{
uint64_t v___x_529_; uint8_t v___x_530_; 
v___x_529_ = 0ULL;
v___x_530_ = lean_uint64_dec_eq(v___y_526_, v___x_529_);
if (v___x_530_ == 0)
{
uint64_t v___x_531_; uint64_t v___x_532_; uint8_t v___x_533_; 
v___x_531_ = 32ULL;
v___x_532_ = lean_uint64_shift_right(v___y_526_, v___x_531_);
v___x_533_ = lean_uint64_dec_eq(v___x_532_, v___x_529_);
if (v___x_533_ == 0)
{
v___y_515_ = v___y_525_;
v___y_516_ = v___x_531_;
v___y_517_ = v___x_529_;
v___y_518_ = v___y_526_;
v___y_519_ = v___y_527_;
v___y_520_ = v___y_528_;
v___y_521_ = v___x_532_;
goto v___jp_514_;
}
else
{
v___y_515_ = v___y_525_;
v___y_516_ = v___x_531_;
v___y_517_ = v___x_529_;
v___y_518_ = v___y_526_;
v___y_519_ = v___y_527_;
v___y_520_ = v___y_528_;
v___y_521_ = v___y_526_;
goto v___jp_514_;
}
}
else
{
if (v___y_525_ == 0)
{
uint32_t v___x_534_; 
v___x_534_ = 0;
return v___x_534_;
}
else
{
uint32_t v___x_535_; 
v___x_535_ = 2147483648;
return v___x_535_;
}
}
}
v___jp_536_:
{
uint64_t v___x_543_; uint64_t v___x_544_; uint64_t v___x_545_; uint8_t v___x_546_; 
v___x_543_ = lean_uint64_mul(v___y_541_, v___y_540_);
v___x_544_ = lean_uint64_add(v___y_538_, v___y_542_);
v___x_545_ = 281474976710656ULL;
v___x_546_ = lean_uint64_dec_lt(v___x_543_, v___x_545_);
if (v___x_546_ == 0)
{
v___y_525_ = v___y_537_;
v___y_526_ = v___x_543_;
v___y_527_ = v___y_539_;
v___y_528_ = v___x_544_;
goto v___jp_524_;
}
else
{
uint64_t v___x_547_; uint8_t v___x_548_; 
v___x_547_ = 123ULL;
v___x_548_ = lean_uint64_dec_le(v___x_544_, v___x_547_);
if (v___x_548_ == 0)
{
v___y_525_ = v___y_537_;
v___y_526_ = v___x_543_;
v___y_527_ = v___y_539_;
v___y_528_ = v___x_544_;
goto v___jp_524_;
}
else
{
uint64_t v___x_549_; uint8_t v___x_550_; 
v___x_549_ = 0ULL;
v___x_550_ = lean_uint64_dec_eq(v___x_543_, v___x_549_);
if (v___x_550_ == 0)
{
uint64_t v___x_551_; uint64_t v___x_552_; uint8_t v___x_553_; 
v___x_551_ = 149ULL;
v___x_552_ = lean_uint64_sub(v___x_551_, v___x_544_);
v___x_553_ = lean_uint64_dec_eq(v___x_552_, v___x_549_);
if (v___x_553_ == 0)
{
uint64_t v___x_554_; uint8_t v___x_555_; 
v___x_554_ = 64ULL;
v___x_555_ = lean_uint64_dec_lt(v___x_552_, v___x_554_);
if (v___x_555_ == 0)
{
uint8_t v___x_556_; 
v___x_556_ = lean_uint64_dec_eq(v___x_552_, v___x_554_);
if (v___x_556_ == 0)
{
v___y_168_ = v___y_537_;
v___y_169_ = v___y_539_;
v___y_170_ = v___x_549_;
v___y_171_ = v___x_549_;
goto v___jp_167_;
}
else
{
uint64_t v___x_557_; uint8_t v___x_558_; 
v___x_557_ = 9223372036854775808ULL;
v___x_558_ = lean_uint64_dec_lt(v___x_557_, v___x_543_);
if (v___x_558_ == 0)
{
v___y_168_ = v___y_537_;
v___y_169_ = v___y_539_;
v___y_170_ = v___x_549_;
v___y_171_ = v___x_549_;
goto v___jp_167_;
}
else
{
uint64_t v___x_559_; 
v___x_559_ = 1ULL;
v___y_168_ = v___y_537_;
v___y_169_ = v___y_539_;
v___y_170_ = v___x_549_;
v___y_171_ = v___x_559_;
goto v___jp_167_;
}
}
}
else
{
uint64_t v_quotient_560_; uint64_t v___x_561_; uint64_t v___x_562_; uint64_t v___x_563_; uint64_t v_remainder_564_; uint64_t v___x_565_; uint64_t v_half_566_; uint8_t v___x_567_; 
v_quotient_560_ = lean_uint64_shift_right(v___x_543_, v___x_552_);
v___x_561_ = 1ULL;
v___x_562_ = lean_uint64_shift_left(v___x_561_, v___x_552_);
v___x_563_ = lean_uint64_sub(v___x_562_, v___x_561_);
v_remainder_564_ = lean_uint64_land(v___x_543_, v___x_563_);
v___x_565_ = lean_uint64_sub(v___x_552_, v___x_561_);
v_half_566_ = lean_uint64_shift_left(v___x_561_, v___x_565_);
v___x_567_ = lean_uint64_dec_lt(v_remainder_564_, v_half_566_);
if (v___x_567_ == 0)
{
uint8_t v___x_568_; 
v___x_568_ = lean_uint64_dec_lt(v_half_566_, v_remainder_564_);
if (v___x_568_ == 0)
{
uint64_t v___x_569_; uint8_t v___x_570_; 
v___x_569_ = lean_uint64_land(v_quotient_560_, v___x_561_);
v___x_570_ = lean_uint64_dec_eq(v___x_569_, v___x_549_);
if (v___x_570_ == 0)
{
uint64_t v___x_571_; 
v___x_571_ = lean_uint64_add(v_quotient_560_, v___x_561_);
v___y_168_ = v___y_537_;
v___y_169_ = v___y_539_;
v___y_170_ = v___x_549_;
v___y_171_ = v___x_571_;
goto v___jp_167_;
}
else
{
v___y_168_ = v___y_537_;
v___y_169_ = v___y_539_;
v___y_170_ = v___x_549_;
v___y_171_ = v_quotient_560_;
goto v___jp_167_;
}
}
else
{
uint64_t v___x_572_; 
v___x_572_ = lean_uint64_add(v_quotient_560_, v___x_561_);
v___y_168_ = v___y_537_;
v___y_169_ = v___y_539_;
v___y_170_ = v___x_549_;
v___y_171_ = v___x_572_;
goto v___jp_167_;
}
}
else
{
v___y_168_ = v___y_537_;
v___y_169_ = v___y_539_;
v___y_170_ = v___x_549_;
v___y_171_ = v_quotient_560_;
goto v___jp_167_;
}
}
}
else
{
v___y_168_ = v___y_537_;
v___y_169_ = v___y_539_;
v___y_170_ = v___x_549_;
v___y_171_ = v___x_543_;
goto v___jp_167_;
}
}
else
{
if (v___y_537_ == 0)
{
uint32_t v___x_573_; 
v___x_573_ = 0;
return v___x_573_;
}
else
{
uint32_t v___x_574_; 
v___x_574_ = 2147483648;
return v___x_574_;
}
}
}
}
}
v___jp_578_:
{
uint64_t v___x_584_; uint64_t v___x_585_; uint8_t v___x_586_; 
v___x_584_ = lean_uint32_to_uint64(v_ey_577_);
v___x_585_ = 0ULL;
v___x_586_ = lean_uint64_dec_eq(v___x_584_, v___x_585_);
if (v___x_586_ == 0)
{
uint64_t v___x_587_; uint64_t v___x_588_; 
v___x_587_ = 1ULL;
v___x_588_ = lean_uint64_sub(v___x_584_, v___x_587_);
v___y_537_ = v___y_579_;
v___y_538_ = v___y_583_;
v___y_539_ = v___y_580_;
v___y_540_ = v___y_581_;
v___y_541_ = v___y_582_;
v___y_542_ = v___x_588_;
goto v___jp_536_;
}
else
{
v___y_537_ = v___y_579_;
v___y_538_ = v___y_583_;
v___y_539_ = v___y_580_;
v___y_540_ = v___y_581_;
v___y_541_ = v___y_582_;
v___y_542_ = v___x_585_;
goto v___jp_536_;
}
}
v___jp_589_:
{
uint64_t v___x_594_; uint64_t v___x_595_; uint8_t v___x_596_; 
v___x_594_ = lean_uint32_to_uint64(v_ex_575_);
v___x_595_ = 0ULL;
v___x_596_ = lean_uint64_dec_eq(v___x_594_, v___x_595_);
if (v___x_596_ == 0)
{
uint64_t v___x_597_; uint64_t v___x_598_; 
v___x_597_ = 1ULL;
v___x_598_ = lean_uint64_sub(v___x_594_, v___x_597_);
v___y_579_ = v___y_590_;
v___y_580_ = v___y_591_;
v___y_581_ = v___y_593_;
v___y_582_ = v___y_592_;
v___y_583_ = v___x_598_;
goto v___jp_578_;
}
else
{
v___y_579_ = v___y_590_;
v___y_580_ = v___y_591_;
v___y_581_ = v___y_593_;
v___y_582_ = v___y_592_;
v___y_583_ = v___x_595_;
goto v___jp_578_;
}
}
v___jp_599_:
{
uint32_t v___x_604_; uint8_t v___x_605_; 
v___x_604_ = 0;
v___x_605_ = lean_uint32_dec_eq(v_ey_577_, v___x_604_);
if (v___x_605_ == 0)
{
uint64_t v___x_606_; uint64_t v___x_607_; uint64_t v___x_608_; 
v___x_606_ = lean_uint32_to_uint64(v___y_600_);
v___x_607_ = 8388608ULL;
v___x_608_ = lean_uint64_lor(v___x_606_, v___x_607_);
v___y_590_ = v___y_601_;
v___y_591_ = v___y_602_;
v___y_592_ = v___y_603_;
v___y_593_ = v___x_608_;
goto v___jp_589_;
}
else
{
uint64_t v___x_609_; 
v___x_609_ = lean_uint32_to_uint64(v___y_600_);
v___y_590_ = v___y_601_;
v___y_591_ = v___y_602_;
v___y_592_ = v___y_603_;
v___y_593_ = v___x_609_;
goto v___jp_589_;
}
}
v___jp_610_:
{
uint32_t v___x_612_; uint32_t v_xFraction_613_; uint32_t v_yFraction_614_; uint32_t v___x_615_; uint8_t v___x_616_; 
v___x_612_ = 8388607;
v_xFraction_613_ = lean_uint32_land(v___y_130_, v___x_612_);
v_yFraction_614_ = lean_uint32_land(v___y_131_, v___x_612_);
v___x_615_ = 0;
v___x_616_ = lean_uint32_dec_eq(v_ex_575_, v___x_615_);
if (v___x_616_ == 0)
{
uint64_t v___x_617_; uint64_t v___x_618_; uint64_t v___x_619_; 
v___x_617_ = lean_uint32_to_uint64(v_xFraction_613_);
v___x_618_ = 8388608ULL;
v___x_619_ = lean_uint64_lor(v___x_617_, v___x_618_);
v___y_600_ = v_yFraction_614_;
v___y_601_ = v___y_611_;
v___y_602_ = v___x_612_;
v___y_603_ = v___x_619_;
goto v___jp_599_;
}
else
{
uint64_t v___x_620_; 
v___x_620_ = lean_uint32_to_uint64(v_xFraction_613_);
v___y_600_ = v_yFraction_614_;
v___y_601_ = v___y_611_;
v___y_602_ = v___x_612_;
v___y_603_ = v___x_620_;
goto v___jp_599_;
}
}
v___jp_624_:
{
if (v___y_626_ == 0)
{
v___y_611_ = v___x_623_;
goto v___jp_610_;
}
else
{
v___y_611_ = v___y_625_;
goto v___jp_610_;
}
}
v___jp_627_:
{
if (v___y_628_ == 0)
{
if (v___y_630_ == 0)
{
v___y_625_ = v___y_629_;
v___y_626_ = v___x_623_;
goto v___jp_624_;
}
else
{
v___y_611_ = v___x_623_;
goto v___jp_610_;
}
}
else
{
v___y_625_ = v___y_629_;
v___y_626_ = v___y_630_;
goto v___jp_624_;
}
}
v___jp_631_:
{
uint32_t v___x_634_; uint32_t v___x_635_; uint32_t v___x_636_; uint8_t v___x_637_; 
v___x_634_ = 2147483648;
v___x_635_ = lean_uint32_land(v___y_131_, v___x_634_);
v___x_636_ = 0;
v___x_637_ = lean_uint32_dec_eq(v___x_635_, v___x_636_);
if (v___x_637_ == 0)
{
v___y_628_ = v___y_633_;
v___y_629_ = v___y_632_;
v___y_630_ = v___x_623_;
goto v___jp_627_;
}
else
{
v___y_628_ = v___y_633_;
v___y_629_ = v___y_632_;
v___y_630_ = v___y_632_;
goto v___jp_627_;
}
}
v___jp_638_:
{
if (v___y_639_ == 0)
{
uint32_t v___x_640_; uint32_t v___x_641_; uint32_t v___x_642_; uint8_t v___x_643_; 
v___x_640_ = 2147483648;
v___x_641_ = lean_uint32_land(v___y_130_, v___x_640_);
v___x_642_ = 0;
v___x_643_ = lean_uint32_dec_eq(v___x_641_, v___x_642_);
if (v___x_643_ == 0)
{
v___y_632_ = v___y_639_;
v___y_633_ = v___x_623_;
goto v___jp_631_;
}
else
{
v___y_632_ = v___y_639_;
v___y_633_ = v___y_639_;
goto v___jp_631_;
}
}
else
{
lean_object* v___x_644_; lean_object* v___x_645_; lean_object* v___x_646_; uint32_t v___x_647_; 
v___x_644_ = lean_uint32_to_nat(v___y_130_);
v___x_645_ = lean_uint32_to_nat(v___y_131_);
v___x_646_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_644_, v___x_645_);
v___x_647_ = lean_uint32_of_nat(v___x_646_);
lean_dec(v___x_646_);
return v___x_647_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_runControl___lam__1___boxed(lean_object* v___y_662_, lean_object* v___y_663_){
_start:
{
uint32_t v___y_2432__boxed_664_; uint32_t v___y_2433__boxed_665_; uint32_t v_res_666_; lean_object* v_r_667_; 
v___y_2432__boxed_664_ = lean_unbox_uint32(v___y_662_);
lean_dec(v___y_662_);
v___y_2433__boxed_665_ = lean_unbox_uint32(v___y_663_);
lean_dec(v___y_663_);
v_res_666_ = lp_competition_runControl___lam__1(v___y_2432__boxed_664_, v___y_2433__boxed_665_);
v_r_667_ = lean_box_uint32(v_res_666_);
return v_r_667_;
}
}
LEAN_EXPORT lean_object* lp_competition_runControl(){
_start:
{
lean_object* v___f_673_; lean_object* v___f_674_; lean_object* v___x_675_; lean_object* v___x_676_; lean_object* v___x_677_; 
v___f_673_ = ((lean_object*)(lp_competition_runControl___closed__0));
v___f_674_ = ((lean_object*)(lp_competition_runControl___closed__1));
v___x_675_ = ((lean_object*)(lp_competition_runControl___closed__2));
v___x_676_ = ((lean_object*)(lp_competition_runControl___closed__3));
v___x_677_ = lp_competition_Bench_Suite_run(v___f_673_, v___f_674_, v___x_675_, v___x_676_);
return v___x_677_;
}
}
LEAN_EXPORT lean_object* lp_competition_runControl___boxed(lean_object* v_a_678_){
_start:
{
lean_object* v_res_679_; 
v_res_679_ = lp_competition_runControl();
return v_res_679_;
}
}
LEAN_EXPORT uint32_t lp_competition_runRaw8___lam__1(uint32_t v___y_680_, uint32_t v___y_681_){
_start:
{
uint32_t v___y_683_; uint32_t v___y_687_; uint32_t v___y_691_; uint32_t v___y_692_; uint32_t v___y_693_; uint8_t v___y_697_; uint64_t v___y_698_; uint32_t v___y_699_; uint64_t v___y_700_; uint32_t v___y_712_; uint32_t v___y_713_; uint32_t v___y_714_; uint8_t v___y_718_; uint64_t v___y_719_; uint32_t v___y_720_; uint64_t v___y_721_; uint8_t v___y_733_; uint8_t v___y_749_; uint8_t v___y_763_; uint8_t v___y_780_; float v___y_787_; float v___y_788_; float v___y_802_; uint8_t v___y_803_; float v___y_818_; uint32_t v___x_827_; uint32_t v___x_828_; uint8_t v___y_830_; uint32_t v___x_842_; uint32_t v___y_844_; uint32_t v___y_845_; uint32_t v___y_846_; uint32_t v___y_847_; uint8_t v___y_854_; uint32_t v___y_855_; uint32_t v___y_856_; uint32_t v___y_857_; uint8_t v___y_861_; uint64_t v___y_862_; uint64_t v___y_863_; uint32_t v___y_864_; uint64_t v___y_865_; uint8_t v___y_875_; uint8_t v___y_876_; uint64_t v___y_877_; uint64_t v___y_878_; uint32_t v___y_879_; uint64_t v___y_880_; uint8_t v___y_887_; uint64_t v___y_888_; uint64_t v___y_889_; uint32_t v___y_890_; uint64_t v___y_891_; uint64_t v___y_897_; uint8_t v___y_898_; uint64_t v___y_899_; uint64_t v___y_900_; uint32_t v___y_901_; uint64_t v___y_902_; uint8_t v___y_957_; uint64_t v___y_958_; uint64_t v___y_959_; uint64_t v___y_960_; uint32_t v___y_961_; uint64_t v___y_962_; uint64_t v___y_963_; uint64_t v___y_969_; uint64_t v___y_970_; uint8_t v___y_971_; uint64_t v___y_972_; uint64_t v___y_973_; uint64_t v___y_974_; uint64_t v___y_975_; uint32_t v___y_976_; uint64_t v___y_977_; uint8_t v___y_982_; uint64_t v___y_983_; uint64_t v___y_984_; uint64_t v___y_985_; uint64_t v___y_986_; uint32_t v___y_987_; uint64_t v___y_988_; uint64_t v___y_993_; uint8_t v___y_994_; uint64_t v___y_995_; uint64_t v___y_996_; uint64_t v___y_997_; uint64_t v___y_998_; uint64_t v___y_999_; uint32_t v___y_1000_; uint64_t v___y_1001_; uint8_t v___y_1006_; uint64_t v___y_1007_; uint64_t v___y_1008_; uint64_t v___y_1009_; uint64_t v___y_1010_; uint32_t v___y_1011_; uint64_t v___y_1012_; uint64_t v___y_1017_; uint64_t v___y_1018_; uint64_t v___y_1019_; uint8_t v___y_1020_; uint64_t v___y_1021_; uint64_t v___y_1022_; uint64_t v___y_1023_; uint32_t v___y_1024_; uint64_t v___y_1025_; uint8_t v___y_1030_; uint64_t v___y_1031_; uint64_t v___y_1032_; uint64_t v___y_1033_; uint64_t v___y_1034_; uint32_t v___y_1035_; uint64_t v___y_1036_; uint64_t v___y_1041_; uint8_t v___y_1042_; uint64_t v___y_1043_; uint64_t v___y_1044_; uint64_t v___y_1045_; uint64_t v___y_1046_; uint64_t v___y_1047_; uint32_t v___y_1048_; uint64_t v___y_1049_; uint8_t v___y_1054_; uint64_t v___y_1055_; uint64_t v___y_1056_; uint64_t v___y_1057_; uint64_t v___y_1058_; uint32_t v___y_1059_; uint64_t v___y_1060_; uint64_t v___y_1065_; uint8_t v___y_1066_; uint64_t v___y_1067_; uint64_t v___y_1068_; uint32_t v___y_1069_; uint64_t v___y_1070_; uint64_t v___y_1071_; uint64_t v___y_1075_; uint8_t v___y_1076_; uint64_t v___y_1077_; uint32_t v___y_1078_; uint8_t v___y_1087_; uint64_t v___y_1088_; uint32_t v___y_1089_; uint64_t v___y_1090_; uint64_t v___y_1091_; uint64_t v___y_1092_; uint32_t v_ex_1125_; uint32_t v___x_1126_; uint32_t v_ey_1127_; uint8_t v___y_1129_; uint64_t v___y_1130_; uint32_t v___y_1131_; uint64_t v___y_1132_; uint64_t v___y_1133_; uint8_t v___y_1140_; uint64_t v___y_1141_; uint32_t v___y_1142_; uint64_t v___y_1143_; uint8_t v___y_1150_; uint32_t v___y_1151_; uint32_t v___y_1152_; uint64_t v___y_1153_; uint8_t v___y_1161_; uint32_t v___x_1171_; uint32_t v___x_1172_; uint8_t v___x_1173_; uint8_t v___y_1175_; uint8_t v___y_1176_; uint8_t v___y_1178_; uint8_t v___y_1179_; uint8_t v___y_1180_; uint8_t v___y_1182_; uint8_t v___y_1183_; uint8_t v___y_1189_; 
v___x_827_ = 23;
v___x_828_ = lean_uint32_shift_right(v___y_680_, v___x_827_);
v___x_842_ = 255;
v_ex_1125_ = lean_uint32_land(v___x_828_, v___x_842_);
v___x_1126_ = lean_uint32_shift_right(v___y_681_, v___x_827_);
v_ey_1127_ = lean_uint32_land(v___x_1126_, v___x_842_);
v___x_1171_ = lean_uint32_add(v_ex_1125_, v_ey_1127_);
v___x_1172_ = 128;
v___x_1173_ = lean_uint32_dec_lt(v___x_1171_, v___x_1172_);
if (v___x_1173_ == 0)
{
uint32_t v___x_1198_; uint32_t v_a_1199_; uint32_t v___x_1200_; uint32_t v___x_1201_; uint32_t v___x_1202_; uint8_t v___x_1203_; 
v___x_1198_ = 2147483647;
v_a_1199_ = lean_uint32_land(v___y_680_, v___x_1198_);
v___x_1200_ = 201326591;
v___x_1201_ = 1;
v___x_1202_ = lean_uint32_sub(v_a_1199_, v___x_1201_);
v___x_1203_ = lean_uint32_dec_le(v___x_1200_, v___x_1202_);
if (v___x_1203_ == 0)
{
v___y_830_ = v___x_1203_;
goto v___jp_829_;
}
else
{
uint32_t v___x_1204_; uint8_t v___x_1205_; 
v___x_1204_ = 2139095040;
v___x_1205_ = lean_uint32_dec_lt(v_a_1199_, v___x_1204_);
v___y_830_ = v___x_1205_;
goto v___jp_829_;
}
}
else
{
uint32_t v___x_1206_; uint32_t v___x_1207_; uint32_t v___x_1208_; uint8_t v___x_1209_; 
v___x_1206_ = 4278190080;
v___x_1207_ = 1;
v___x_1208_ = lean_uint32_shift_left(v___y_680_, v___x_1207_);
v___x_1209_ = lean_uint32_dec_le(v___x_1206_, v___x_1208_);
if (v___x_1209_ == 0)
{
uint32_t v___x_1210_; uint8_t v___x_1211_; 
v___x_1210_ = lean_uint32_shift_left(v___y_681_, v___x_1207_);
v___x_1211_ = lean_uint32_dec_le(v___x_1206_, v___x_1210_);
v___y_1189_ = v___x_1211_;
goto v___jp_1188_;
}
else
{
v___y_1189_ = v___x_1209_;
goto v___jp_1188_;
}
}
v___jp_682_:
{
uint32_t v___x_684_; uint32_t v___x_685_; 
v___x_684_ = 8388608;
v___x_685_ = lean_uint32_lor(v___y_683_, v___x_684_);
return v___x_685_;
}
v___jp_686_:
{
uint32_t v___x_688_; uint32_t v___x_689_; 
v___x_688_ = 8388608;
v___x_689_ = lean_uint32_lor(v___y_687_, v___x_688_);
return v___x_689_;
}
v___jp_690_:
{
uint32_t v___x_694_; uint32_t v___x_695_; 
v___x_694_ = lean_uint32_land(v___y_691_, v___y_692_);
v___x_695_ = lean_uint32_lor(v___y_693_, v___x_694_);
return v___x_695_;
}
v___jp_696_:
{
uint8_t v___x_701_; 
v___x_701_ = lean_uint64_dec_eq(v___y_700_, v___y_698_);
if (v___x_701_ == 0)
{
uint64_t v___x_702_; uint8_t v___x_703_; 
v___x_702_ = 8388608ULL;
v___x_703_ = lean_uint64_dec_eq(v___y_700_, v___x_702_);
if (v___x_703_ == 0)
{
uint32_t v___x_704_; 
v___x_704_ = lean_uint64_to_uint32(v___y_700_);
if (v___y_697_ == 0)
{
uint32_t v___x_705_; 
v___x_705_ = 0;
v___y_691_ = v___x_704_;
v___y_692_ = v___y_699_;
v___y_693_ = v___x_705_;
goto v___jp_690_;
}
else
{
uint32_t v___x_706_; 
v___x_706_ = 2147483648;
v___y_691_ = v___x_704_;
v___y_692_ = v___y_699_;
v___y_693_ = v___x_706_;
goto v___jp_690_;
}
}
else
{
if (v___y_697_ == 0)
{
uint32_t v___x_707_; 
v___x_707_ = 0;
v___y_687_ = v___x_707_;
goto v___jp_686_;
}
else
{
uint32_t v___x_708_; 
v___x_708_ = 2147483648;
v___y_687_ = v___x_708_;
goto v___jp_686_;
}
}
}
else
{
if (v___y_697_ == 0)
{
uint32_t v___x_709_; 
v___x_709_ = 0;
return v___x_709_;
}
else
{
uint32_t v___x_710_; 
v___x_710_ = 2147483648;
return v___x_710_;
}
}
}
v___jp_711_:
{
uint32_t v___x_715_; uint32_t v___x_716_; 
v___x_715_ = lean_uint32_land(v___y_712_, v___y_713_);
v___x_716_ = lean_uint32_lor(v___y_714_, v___x_715_);
return v___x_716_;
}
v___jp_717_:
{
uint8_t v___x_722_; 
v___x_722_ = lean_uint64_dec_eq(v___y_721_, v___y_719_);
if (v___x_722_ == 0)
{
uint64_t v___x_723_; uint8_t v___x_724_; 
v___x_723_ = 8388608ULL;
v___x_724_ = lean_uint64_dec_eq(v___y_721_, v___x_723_);
if (v___x_724_ == 0)
{
uint32_t v___x_725_; 
v___x_725_ = lean_uint64_to_uint32(v___y_721_);
if (v___y_718_ == 0)
{
uint32_t v___x_726_; 
v___x_726_ = 0;
v___y_712_ = v___x_725_;
v___y_713_ = v___y_720_;
v___y_714_ = v___x_726_;
goto v___jp_711_;
}
else
{
uint32_t v___x_727_; 
v___x_727_ = 2147483648;
v___y_712_ = v___x_725_;
v___y_713_ = v___y_720_;
v___y_714_ = v___x_727_;
goto v___jp_711_;
}
}
else
{
if (v___y_718_ == 0)
{
uint32_t v___x_728_; 
v___x_728_ = 0;
v___y_683_ = v___x_728_;
goto v___jp_682_;
}
else
{
uint32_t v___x_729_; 
v___x_729_ = 2147483648;
v___y_683_ = v___x_729_;
goto v___jp_682_;
}
}
}
else
{
if (v___y_718_ == 0)
{
uint32_t v___x_730_; 
v___x_730_ = 0;
return v___x_730_;
}
else
{
uint32_t v___x_731_; 
v___x_731_ = 2147483648;
return v___x_731_;
}
}
}
v___jp_732_:
{
if (v___y_733_ == 0)
{
uint32_t v___x_734_; 
v___x_734_ = lp_competition_Submission_FastMul_mul(v___y_680_, v___y_681_);
return v___x_734_;
}
else
{
uint32_t v___x_735_; uint32_t v___x_736_; 
v___x_735_ = 4194304;
v___x_736_ = lean_uint32_lor(v___y_681_, v___x_735_);
return v___x_736_;
}
}
v___jp_737_:
{
uint32_t v___x_738_; uint32_t v___x_739_; uint32_t v___x_740_; uint32_t v___x_741_; uint8_t v___x_742_; 
v___x_738_ = 23;
v___x_739_ = lean_uint32_shift_right(v___y_681_, v___x_738_);
v___x_740_ = 255;
v___x_741_ = lean_uint32_land(v___x_739_, v___x_740_);
v___x_742_ = lean_uint32_dec_eq(v___x_741_, v___x_740_);
if (v___x_742_ == 0)
{
v___y_733_ = v___x_742_;
goto v___jp_732_;
}
else
{
uint32_t v___x_743_; uint32_t v___x_744_; uint32_t v___x_745_; uint8_t v___x_746_; 
v___x_743_ = 8388607;
v___x_744_ = lean_uint32_land(v___y_681_, v___x_743_);
v___x_745_ = 0;
v___x_746_ = lean_uint32_dec_eq(v___x_744_, v___x_745_);
if (v___x_746_ == 0)
{
v___y_733_ = v___x_742_;
goto v___jp_732_;
}
else
{
uint32_t v___x_747_; 
v___x_747_ = lp_competition_Submission_FastMul_mul(v___y_680_, v___y_681_);
return v___x_747_;
}
}
}
v___jp_748_:
{
if (v___y_749_ == 0)
{
goto v___jp_737_;
}
else
{
uint32_t v___x_750_; uint32_t v___x_751_; 
v___x_750_ = 4194304;
v___x_751_ = lean_uint32_lor(v___y_680_, v___x_750_);
return v___x_751_;
}
}
v___jp_752_:
{
uint32_t v___x_753_; uint32_t v___x_754_; uint32_t v___x_755_; uint32_t v___x_756_; uint8_t v___x_757_; 
v___x_753_ = 23;
v___x_754_ = lean_uint32_shift_right(v___y_680_, v___x_753_);
v___x_755_ = 255;
v___x_756_ = lean_uint32_land(v___x_754_, v___x_755_);
v___x_757_ = lean_uint32_dec_eq(v___x_756_, v___x_755_);
if (v___x_757_ == 0)
{
v___y_749_ = v___x_757_;
goto v___jp_748_;
}
else
{
uint32_t v___x_758_; uint32_t v___x_759_; uint32_t v___x_760_; uint8_t v___x_761_; 
v___x_758_ = 8388607;
v___x_759_ = lean_uint32_land(v___y_680_, v___x_758_);
v___x_760_ = 0;
v___x_761_ = lean_uint32_dec_eq(v___x_759_, v___x_760_);
if (v___x_761_ == 0)
{
v___y_749_ = v___x_757_;
goto v___jp_748_;
}
else
{
goto v___jp_737_;
}
}
}
v___jp_762_:
{
if (v___y_763_ == 0)
{
goto v___jp_752_;
}
else
{
uint32_t v___x_764_; uint32_t v___x_765_; uint32_t v___x_766_; uint8_t v___x_767_; 
v___x_764_ = 4194304;
v___x_765_ = lean_uint32_land(v___y_681_, v___x_764_);
v___x_766_ = 0;
v___x_767_ = lean_uint32_dec_eq(v___x_765_, v___x_766_);
if (v___x_767_ == 0)
{
goto v___jp_752_;
}
else
{
uint32_t v___x_768_; 
v___x_768_ = lean_uint32_lor(v___y_681_, v___x_764_);
return v___x_768_;
}
}
}
v___jp_769_:
{
uint32_t v___x_770_; uint32_t v___x_771_; uint32_t v___x_772_; uint32_t v___x_773_; uint8_t v___x_774_; 
v___x_770_ = 23;
v___x_771_ = lean_uint32_shift_right(v___y_681_, v___x_770_);
v___x_772_ = 255;
v___x_773_ = lean_uint32_land(v___x_771_, v___x_772_);
v___x_774_ = lean_uint32_dec_eq(v___x_773_, v___x_772_);
if (v___x_774_ == 0)
{
v___y_763_ = v___x_774_;
goto v___jp_762_;
}
else
{
uint32_t v___x_775_; uint32_t v___x_776_; uint32_t v___x_777_; uint8_t v___x_778_; 
v___x_775_ = 8388607;
v___x_776_ = lean_uint32_land(v___y_681_, v___x_775_);
v___x_777_ = 0;
v___x_778_ = lean_uint32_dec_eq(v___x_776_, v___x_777_);
if (v___x_778_ == 0)
{
v___y_763_ = v___x_774_;
goto v___jp_762_;
}
else
{
goto v___jp_752_;
}
}
}
v___jp_779_:
{
if (v___y_780_ == 0)
{
goto v___jp_769_;
}
else
{
uint32_t v___x_781_; uint32_t v___x_782_; uint32_t v___x_783_; uint8_t v___x_784_; 
v___x_781_ = 4194304;
v___x_782_ = lean_uint32_land(v___y_680_, v___x_781_);
v___x_783_ = 0;
v___x_784_ = lean_uint32_dec_eq(v___x_782_, v___x_783_);
if (v___x_784_ == 0)
{
goto v___jp_769_;
}
else
{
uint32_t v___x_785_; 
v___x_785_ = lean_uint32_lor(v___y_680_, v___x_781_);
return v___x_785_;
}
}
}
v___jp_786_:
{
float v_result_789_; uint8_t v___x_790_; 
v_result_789_ = lean_float32_mul(v___y_787_, v___y_788_);
v___x_790_ = lean_float32_beq(v_result_789_, v_result_789_);
if (v___x_790_ == 0)
{
uint32_t v___x_791_; uint32_t v___x_792_; uint32_t v___x_793_; uint32_t v___x_794_; uint8_t v___x_795_; 
v___x_791_ = 23;
v___x_792_ = lean_uint32_shift_right(v___y_680_, v___x_791_);
v___x_793_ = 255;
v___x_794_ = lean_uint32_land(v___x_792_, v___x_793_);
v___x_795_ = lean_uint32_dec_eq(v___x_794_, v___x_793_);
if (v___x_795_ == 0)
{
v___y_780_ = v___x_795_;
goto v___jp_779_;
}
else
{
uint32_t v___x_796_; uint32_t v___x_797_; uint32_t v___x_798_; uint8_t v___x_799_; 
v___x_796_ = 8388607;
v___x_797_ = lean_uint32_land(v___y_680_, v___x_796_);
v___x_798_ = 0;
v___x_799_ = lean_uint32_dec_eq(v___x_797_, v___x_798_);
if (v___x_799_ == 0)
{
v___y_780_ = v___x_795_;
goto v___jp_779_;
}
else
{
goto v___jp_769_;
}
}
}
else
{
uint32_t v___x_800_; 
v___x_800_ = lean_float32_to_bits(v_result_789_);
return v___x_800_;
}
}
v___jp_801_:
{
if (v___y_803_ == 0)
{
float v___x_804_; 
v___x_804_ = lean_float32_of_bits(v___y_681_);
v___y_787_ = v___y_802_;
v___y_788_ = v___x_804_;
goto v___jp_786_;
}
else
{
uint32_t v___x_805_; uint32_t v___x_806_; uint32_t v___x_807_; uint32_t v___x_808_; float v___x_809_; lean_object* v___x_810_; uint32_t v___x_811_; uint32_t v___x_812_; lean_object* v___x_813_; lean_object* v___x_814_; float v___x_815_; float v___x_816_; 
v___x_805_ = 8388607;
v___x_806_ = lean_uint32_land(v___y_681_, v___x_805_);
v___x_807_ = 8388608;
v___x_808_ = lean_uint32_lor(v___x_806_, v___x_807_);
v___x_809_ = lean_uint32_to_float32(v___x_808_);
v___x_810_ = lp_competition_R2W01b_scaleTable;
v___x_811_ = 23;
v___x_812_ = lean_uint32_shift_right(v___y_681_, v___x_811_);
v___x_813_ = lean_uint32_to_nat(v___x_812_);
v___x_814_ = lean_array_fget_borrowed(v___x_810_, v___x_813_);
lean_dec(v___x_813_);
v___x_815_ = lean_unbox_float32(v___x_814_);
v___x_816_ = lean_float32_mul(v___x_809_, v___x_815_);
v___y_787_ = v___y_802_;
v___y_788_ = v___x_816_;
goto v___jp_786_;
}
}
v___jp_817_:
{
uint32_t v___x_819_; uint32_t v_a_820_; uint32_t v___x_821_; uint32_t v___x_822_; uint32_t v___x_823_; uint8_t v___x_824_; 
v___x_819_ = 2147483647;
v_a_820_ = lean_uint32_land(v___y_681_, v___x_819_);
v___x_821_ = 201326591;
v___x_822_ = 1;
v___x_823_ = lean_uint32_sub(v_a_820_, v___x_822_);
v___x_824_ = lean_uint32_dec_le(v___x_821_, v___x_823_);
if (v___x_824_ == 0)
{
v___y_802_ = v___y_818_;
v___y_803_ = v___x_824_;
goto v___jp_801_;
}
else
{
uint32_t v___x_825_; uint8_t v___x_826_; 
v___x_825_ = 2139095040;
v___x_826_ = lean_uint32_dec_lt(v_a_820_, v___x_825_);
v___y_802_ = v___y_818_;
v___y_803_ = v___x_826_;
goto v___jp_801_;
}
}
v___jp_829_:
{
if (v___y_830_ == 0)
{
float v___x_831_; 
v___x_831_ = lean_float32_of_bits(v___y_680_);
v___y_818_ = v___x_831_;
goto v___jp_817_;
}
else
{
uint32_t v___x_832_; uint32_t v___x_833_; uint32_t v___x_834_; uint32_t v___x_835_; float v___x_836_; lean_object* v___x_837_; lean_object* v___x_838_; lean_object* v___x_839_; float v___x_840_; float v___x_841_; 
v___x_832_ = 8388607;
v___x_833_ = lean_uint32_land(v___y_680_, v___x_832_);
v___x_834_ = 8388608;
v___x_835_ = lean_uint32_lor(v___x_833_, v___x_834_);
v___x_836_ = lean_uint32_to_float32(v___x_835_);
v___x_837_ = lp_competition_R2W01b_scaleTable;
v___x_838_ = lean_uint32_to_nat(v___x_828_);
v___x_839_ = lean_array_fget_borrowed(v___x_837_, v___x_838_);
lean_dec(v___x_838_);
v___x_840_ = lean_unbox_float32(v___x_839_);
v___x_841_ = lean_float32_mul(v___x_836_, v___x_840_);
v___y_818_ = v___x_841_;
goto v___jp_817_;
}
}
v___jp_843_:
{
uint32_t v___x_848_; uint32_t v___x_849_; uint32_t v___x_850_; uint32_t v___x_851_; uint32_t v___x_852_; 
v___x_848_ = lean_uint32_land(v___y_845_, v___x_842_);
v___x_849_ = lean_uint32_shift_left(v___x_848_, v___x_827_);
v___x_850_ = lean_uint32_lor(v___y_847_, v___x_849_);
v___x_851_ = lean_uint32_land(v___y_844_, v___y_846_);
v___x_852_ = lean_uint32_lor(v___x_850_, v___x_851_);
return v___x_852_;
}
v___jp_853_:
{
if (v___y_854_ == 0)
{
uint32_t v___x_858_; 
v___x_858_ = 0;
v___y_844_ = v___y_857_;
v___y_845_ = v___y_855_;
v___y_846_ = v___y_856_;
v___y_847_ = v___x_858_;
goto v___jp_843_;
}
else
{
uint32_t v___x_859_; 
v___x_859_ = 2147483648;
v___y_844_ = v___y_857_;
v___y_845_ = v___y_855_;
v___y_846_ = v___y_856_;
v___y_847_ = v___x_859_;
goto v___jp_843_;
}
}
v___jp_860_:
{
uint64_t v___x_866_; uint64_t v_encodedExponent_867_; uint32_t v___x_868_; uint64_t v___x_869_; uint8_t v___x_870_; 
v___x_866_ = 171ULL;
v_encodedExponent_867_ = lean_uint64_sub(v___y_863_, v___x_866_);
v___x_868_ = lean_uint64_to_uint32(v_encodedExponent_867_);
v___x_869_ = 8388608ULL;
v___x_870_ = lean_uint64_dec_lt(v___y_865_, v___x_869_);
if (v___x_870_ == 0)
{
uint64_t v___x_871_; uint32_t v___x_872_; 
v___x_871_ = lean_uint64_sub(v___y_865_, v___x_869_);
v___x_872_ = lean_uint64_to_uint32(v___x_871_);
v___y_854_ = v___y_861_;
v___y_855_ = v___x_868_;
v___y_856_ = v___y_864_;
v___y_857_ = v___x_872_;
goto v___jp_853_;
}
else
{
uint32_t v___x_873_; 
v___x_873_ = lean_uint64_to_uint32(v___y_862_);
v___y_854_ = v___y_861_;
v___y_855_ = v___x_868_;
v___y_856_ = v___y_864_;
v___y_857_ = v___x_873_;
goto v___jp_853_;
}
}
v___jp_874_:
{
uint64_t v___x_881_; uint8_t v___x_882_; 
v___x_881_ = 425ULL;
v___x_882_ = lean_uint64_dec_lt(v___x_881_, v___y_880_);
if (v___x_882_ == 0)
{
if (v___y_875_ == 0)
{
v___y_861_ = v___y_876_;
v___y_862_ = v___y_877_;
v___y_863_ = v___y_880_;
v___y_864_ = v___y_879_;
v___y_865_ = v___y_878_;
goto v___jp_860_;
}
else
{
uint64_t v___x_883_; 
v___x_883_ = 8388608ULL;
v___y_861_ = v___y_876_;
v___y_862_ = v___y_877_;
v___y_863_ = v___y_880_;
v___y_864_ = v___y_879_;
v___y_865_ = v___x_883_;
goto v___jp_860_;
}
}
else
{
if (v___y_876_ == 0)
{
uint32_t v___x_884_; 
v___x_884_ = 2139095040;
return v___x_884_;
}
else
{
uint32_t v___x_885_; 
v___x_885_ = 4286578688;
return v___x_885_;
}
}
}
v___jp_886_:
{
uint64_t v___x_892_; uint8_t v_carry_893_; 
v___x_892_ = 16777216ULL;
v_carry_893_ = lean_uint64_dec_eq(v___y_891_, v___x_892_);
if (v_carry_893_ == 0)
{
v___y_875_ = v_carry_893_;
v___y_876_ = v___y_887_;
v___y_877_ = v___y_889_;
v___y_878_ = v___y_891_;
v___y_879_ = v___y_890_;
v___y_880_ = v___y_888_;
goto v___jp_874_;
}
else
{
uint64_t v___x_894_; uint64_t v___x_895_; 
v___x_894_ = 1ULL;
v___x_895_ = lean_uint64_add(v___y_888_, v___x_894_);
v___y_875_ = v_carry_893_;
v___y_876_ = v___y_887_;
v___y_877_ = v___y_889_;
v___y_878_ = v___y_891_;
v___y_879_ = v___y_890_;
v___y_880_ = v___x_895_;
goto v___jp_874_;
}
}
v___jp_896_:
{
uint64_t v_position_903_; uint64_t v___x_904_; uint8_t v___x_905_; 
v_position_903_ = lean_uint64_add(v___y_902_, v___y_900_);
v___x_904_ = 172ULL;
v___x_905_ = lean_uint64_dec_lt(v_position_903_, v___x_904_);
if (v___x_905_ == 0)
{
uint64_t v___x_906_; uint8_t v___x_907_; 
v___x_906_ = 23ULL;
v___x_907_ = lean_uint64_dec_lt(v___y_902_, v___x_906_);
if (v___x_907_ == 0)
{
uint64_t v___x_908_; uint8_t v___x_909_; 
v___x_908_ = lean_uint64_sub(v___y_902_, v___x_906_);
v___x_909_ = lean_uint64_dec_eq(v___x_908_, v___y_899_);
if (v___x_909_ == 0)
{
uint64_t v___x_910_; uint8_t v___x_911_; 
v___x_910_ = 64ULL;
v___x_911_ = lean_uint64_dec_lt(v___x_908_, v___x_910_);
if (v___x_911_ == 0)
{
uint8_t v___x_912_; 
v___x_912_ = lean_uint64_dec_eq(v___x_908_, v___x_910_);
if (v___x_912_ == 0)
{
v___y_887_ = v___y_898_;
v___y_888_ = v_position_903_;
v___y_889_ = v___y_899_;
v___y_890_ = v___y_901_;
v___y_891_ = v___y_899_;
goto v___jp_886_;
}
else
{
uint64_t v___x_913_; uint8_t v___x_914_; 
v___x_913_ = 9223372036854775808ULL;
v___x_914_ = lean_uint64_dec_lt(v___x_913_, v___y_897_);
if (v___x_914_ == 0)
{
v___y_887_ = v___y_898_;
v___y_888_ = v_position_903_;
v___y_889_ = v___y_899_;
v___y_890_ = v___y_901_;
v___y_891_ = v___y_899_;
goto v___jp_886_;
}
else
{
uint64_t v___x_915_; 
v___x_915_ = 1ULL;
v___y_887_ = v___y_898_;
v___y_888_ = v_position_903_;
v___y_889_ = v___y_899_;
v___y_890_ = v___y_901_;
v___y_891_ = v___x_915_;
goto v___jp_886_;
}
}
}
else
{
uint64_t v_quotient_916_; uint64_t v___x_917_; uint64_t v___x_918_; uint64_t v___x_919_; uint64_t v_remainder_920_; uint64_t v___x_921_; uint64_t v_half_922_; uint8_t v___x_923_; 
v_quotient_916_ = lean_uint64_shift_right(v___y_897_, v___x_908_);
v___x_917_ = 1ULL;
v___x_918_ = lean_uint64_shift_left(v___x_917_, v___x_908_);
v___x_919_ = lean_uint64_sub(v___x_918_, v___x_917_);
v_remainder_920_ = lean_uint64_land(v___y_897_, v___x_919_);
v___x_921_ = lean_uint64_sub(v___x_908_, v___x_917_);
v_half_922_ = lean_uint64_shift_left(v___x_917_, v___x_921_);
v___x_923_ = lean_uint64_dec_lt(v_remainder_920_, v_half_922_);
if (v___x_923_ == 0)
{
uint8_t v___x_924_; 
v___x_924_ = lean_uint64_dec_lt(v_half_922_, v_remainder_920_);
if (v___x_924_ == 0)
{
uint64_t v___x_925_; uint8_t v___x_926_; 
v___x_925_ = lean_uint64_land(v_quotient_916_, v___x_917_);
v___x_926_ = lean_uint64_dec_eq(v___x_925_, v___y_899_);
if (v___x_926_ == 0)
{
uint64_t v___x_927_; 
v___x_927_ = lean_uint64_add(v_quotient_916_, v___x_917_);
v___y_887_ = v___y_898_;
v___y_888_ = v_position_903_;
v___y_889_ = v___y_899_;
v___y_890_ = v___y_901_;
v___y_891_ = v___x_927_;
goto v___jp_886_;
}
else
{
v___y_887_ = v___y_898_;
v___y_888_ = v_position_903_;
v___y_889_ = v___y_899_;
v___y_890_ = v___y_901_;
v___y_891_ = v_quotient_916_;
goto v___jp_886_;
}
}
else
{
uint64_t v___x_928_; 
v___x_928_ = lean_uint64_add(v_quotient_916_, v___x_917_);
v___y_887_ = v___y_898_;
v___y_888_ = v_position_903_;
v___y_889_ = v___y_899_;
v___y_890_ = v___y_901_;
v___y_891_ = v___x_928_;
goto v___jp_886_;
}
}
else
{
v___y_887_ = v___y_898_;
v___y_888_ = v_position_903_;
v___y_889_ = v___y_899_;
v___y_890_ = v___y_901_;
v___y_891_ = v_quotient_916_;
goto v___jp_886_;
}
}
}
else
{
v___y_887_ = v___y_898_;
v___y_888_ = v_position_903_;
v___y_889_ = v___y_899_;
v___y_890_ = v___y_901_;
v___y_891_ = v___y_897_;
goto v___jp_886_;
}
}
else
{
uint64_t v___x_929_; uint64_t v___x_930_; 
v___x_929_ = lean_uint64_sub(v___x_906_, v___y_902_);
v___x_930_ = lean_uint64_shift_left(v___y_897_, v___x_929_);
v___y_887_ = v___y_898_;
v___y_888_ = v_position_903_;
v___y_889_ = v___y_899_;
v___y_890_ = v___y_901_;
v___y_891_ = v___x_930_;
goto v___jp_886_;
}
}
else
{
uint64_t v___x_931_; uint8_t v___x_932_; 
v___x_931_ = 149ULL;
v___x_932_ = lean_uint64_dec_lt(v___y_900_, v___x_931_);
if (v___x_932_ == 0)
{
uint64_t v___x_933_; uint64_t v___x_934_; 
v___x_933_ = lean_uint64_sub(v___y_900_, v___x_931_);
v___x_934_ = lean_uint64_shift_left(v___y_897_, v___x_933_);
v___y_697_ = v___y_898_;
v___y_698_ = v___y_899_;
v___y_699_ = v___y_901_;
v___y_700_ = v___x_934_;
goto v___jp_696_;
}
else
{
uint64_t v___x_935_; uint8_t v___x_936_; 
v___x_935_ = lean_uint64_sub(v___x_931_, v___y_900_);
v___x_936_ = lean_uint64_dec_eq(v___x_935_, v___y_899_);
if (v___x_936_ == 0)
{
uint64_t v___x_937_; uint8_t v___x_938_; 
v___x_937_ = 64ULL;
v___x_938_ = lean_uint64_dec_lt(v___x_935_, v___x_937_);
if (v___x_938_ == 0)
{
uint8_t v___x_939_; 
v___x_939_ = lean_uint64_dec_eq(v___x_935_, v___x_937_);
if (v___x_939_ == 0)
{
v___y_697_ = v___y_898_;
v___y_698_ = v___y_899_;
v___y_699_ = v___y_901_;
v___y_700_ = v___y_899_;
goto v___jp_696_;
}
else
{
uint64_t v___x_940_; uint8_t v___x_941_; 
v___x_940_ = 9223372036854775808ULL;
v___x_941_ = lean_uint64_dec_lt(v___x_940_, v___y_897_);
if (v___x_941_ == 0)
{
v___y_697_ = v___y_898_;
v___y_698_ = v___y_899_;
v___y_699_ = v___y_901_;
v___y_700_ = v___y_899_;
goto v___jp_696_;
}
else
{
uint64_t v___x_942_; 
v___x_942_ = 1ULL;
v___y_697_ = v___y_898_;
v___y_698_ = v___y_899_;
v___y_699_ = v___y_901_;
v___y_700_ = v___x_942_;
goto v___jp_696_;
}
}
}
else
{
uint64_t v_quotient_943_; uint64_t v___x_944_; uint64_t v___x_945_; uint64_t v___x_946_; uint64_t v_remainder_947_; uint64_t v___x_948_; uint64_t v_half_949_; uint8_t v___x_950_; 
v_quotient_943_ = lean_uint64_shift_right(v___y_897_, v___x_935_);
v___x_944_ = 1ULL;
v___x_945_ = lean_uint64_shift_left(v___x_944_, v___x_935_);
v___x_946_ = lean_uint64_sub(v___x_945_, v___x_944_);
v_remainder_947_ = lean_uint64_land(v___y_897_, v___x_946_);
v___x_948_ = lean_uint64_sub(v___x_935_, v___x_944_);
v_half_949_ = lean_uint64_shift_left(v___x_944_, v___x_948_);
v___x_950_ = lean_uint64_dec_lt(v_remainder_947_, v_half_949_);
if (v___x_950_ == 0)
{
uint8_t v___x_951_; 
v___x_951_ = lean_uint64_dec_lt(v_half_949_, v_remainder_947_);
if (v___x_951_ == 0)
{
uint64_t v___x_952_; uint8_t v___x_953_; 
v___x_952_ = lean_uint64_land(v_quotient_943_, v___x_944_);
v___x_953_ = lean_uint64_dec_eq(v___x_952_, v___y_899_);
if (v___x_953_ == 0)
{
uint64_t v___x_954_; 
v___x_954_ = lean_uint64_add(v_quotient_943_, v___x_944_);
v___y_697_ = v___y_898_;
v___y_698_ = v___y_899_;
v___y_699_ = v___y_901_;
v___y_700_ = v___x_954_;
goto v___jp_696_;
}
else
{
v___y_697_ = v___y_898_;
v___y_698_ = v___y_899_;
v___y_699_ = v___y_901_;
v___y_700_ = v_quotient_943_;
goto v___jp_696_;
}
}
else
{
uint64_t v___x_955_; 
v___x_955_ = lean_uint64_add(v_quotient_943_, v___x_944_);
v___y_697_ = v___y_898_;
v___y_698_ = v___y_899_;
v___y_699_ = v___y_901_;
v___y_700_ = v___x_955_;
goto v___jp_696_;
}
}
else
{
v___y_697_ = v___y_898_;
v___y_698_ = v___y_899_;
v___y_699_ = v___y_901_;
v___y_700_ = v_quotient_943_;
goto v___jp_696_;
}
}
}
else
{
v___y_697_ = v___y_898_;
v___y_698_ = v___y_899_;
v___y_699_ = v___y_901_;
v___y_700_ = v___y_897_;
goto v___jp_696_;
}
}
}
}
v___jp_956_:
{
uint64_t v___x_964_; uint64_t v___x_965_; uint8_t v___x_966_; 
v___x_964_ = 1ULL;
v___x_965_ = lean_uint64_shift_right(v___y_962_, v___x_964_);
v___x_966_ = lean_uint64_dec_eq(v___x_965_, v___y_960_);
if (v___x_966_ == 0)
{
uint64_t v___x_967_; 
v___x_967_ = lean_uint64_add(v___y_963_, v___x_964_);
v___y_897_ = v___y_958_;
v___y_898_ = v___y_957_;
v___y_899_ = v___y_960_;
v___y_900_ = v___y_959_;
v___y_901_ = v___y_961_;
v___y_902_ = v___x_967_;
goto v___jp_896_;
}
else
{
v___y_897_ = v___y_958_;
v___y_898_ = v___y_957_;
v___y_899_ = v___y_960_;
v___y_900_ = v___y_959_;
v___y_901_ = v___y_961_;
v___y_902_ = v___y_963_;
goto v___jp_896_;
}
}
v___jp_968_:
{
uint64_t v___x_978_; uint8_t v___x_979_; 
v___x_978_ = lean_uint64_shift_right(v___y_973_, v___y_972_);
v___x_979_ = lean_uint64_dec_eq(v___x_978_, v___y_974_);
if (v___x_979_ == 0)
{
uint64_t v___x_980_; 
v___x_980_ = lean_uint64_add(v___y_969_, v___y_972_);
v___y_957_ = v___y_971_;
v___y_958_ = v___y_970_;
v___y_959_ = v___y_975_;
v___y_960_ = v___y_974_;
v___y_961_ = v___y_976_;
v___y_962_ = v___y_977_;
v___y_963_ = v___x_980_;
goto v___jp_956_;
}
else
{
v___y_957_ = v___y_971_;
v___y_958_ = v___y_970_;
v___y_959_ = v___y_975_;
v___y_960_ = v___y_974_;
v___y_961_ = v___y_976_;
v___y_962_ = v___y_977_;
v___y_963_ = v___y_969_;
goto v___jp_956_;
}
}
v___jp_981_:
{
uint64_t v___x_989_; uint64_t v___x_990_; uint8_t v___x_991_; 
v___x_989_ = 2ULL;
v___x_990_ = lean_uint64_shift_right(v___y_984_, v___x_989_);
v___x_991_ = lean_uint64_dec_eq(v___x_990_, v___y_986_);
if (v___x_991_ == 0)
{
v___y_969_ = v___y_988_;
v___y_970_ = v___y_983_;
v___y_971_ = v___y_982_;
v___y_972_ = v___x_989_;
v___y_973_ = v___y_984_;
v___y_974_ = v___y_986_;
v___y_975_ = v___y_985_;
v___y_976_ = v___y_987_;
v___y_977_ = v___x_990_;
goto v___jp_968_;
}
else
{
v___y_969_ = v___y_988_;
v___y_970_ = v___y_983_;
v___y_971_ = v___y_982_;
v___y_972_ = v___x_989_;
v___y_973_ = v___y_984_;
v___y_974_ = v___y_986_;
v___y_975_ = v___y_985_;
v___y_976_ = v___y_987_;
v___y_977_ = v___y_984_;
goto v___jp_968_;
}
}
v___jp_992_:
{
uint64_t v___x_1002_; uint8_t v___x_1003_; 
v___x_1002_ = lean_uint64_shift_right(v___y_999_, v___y_997_);
v___x_1003_ = lean_uint64_dec_eq(v___x_1002_, v___y_995_);
if (v___x_1003_ == 0)
{
uint64_t v___x_1004_; 
v___x_1004_ = lean_uint64_add(v___y_998_, v___y_997_);
v___y_982_ = v___y_994_;
v___y_983_ = v___y_993_;
v___y_984_ = v___y_1001_;
v___y_985_ = v___y_996_;
v___y_986_ = v___y_995_;
v___y_987_ = v___y_1000_;
v___y_988_ = v___x_1004_;
goto v___jp_981_;
}
else
{
v___y_982_ = v___y_994_;
v___y_983_ = v___y_993_;
v___y_984_ = v___y_1001_;
v___y_985_ = v___y_996_;
v___y_986_ = v___y_995_;
v___y_987_ = v___y_1000_;
v___y_988_ = v___y_998_;
goto v___jp_981_;
}
}
v___jp_1005_:
{
uint64_t v___x_1013_; uint64_t v___x_1014_; uint8_t v___x_1015_; 
v___x_1013_ = 4ULL;
v___x_1014_ = lean_uint64_shift_right(v___y_1010_, v___x_1013_);
v___x_1015_ = lean_uint64_dec_eq(v___x_1014_, v___y_1009_);
if (v___x_1015_ == 0)
{
v___y_993_ = v___y_1007_;
v___y_994_ = v___y_1006_;
v___y_995_ = v___y_1009_;
v___y_996_ = v___y_1008_;
v___y_997_ = v___x_1013_;
v___y_998_ = v___y_1012_;
v___y_999_ = v___y_1010_;
v___y_1000_ = v___y_1011_;
v___y_1001_ = v___x_1014_;
goto v___jp_992_;
}
else
{
v___y_993_ = v___y_1007_;
v___y_994_ = v___y_1006_;
v___y_995_ = v___y_1009_;
v___y_996_ = v___y_1008_;
v___y_997_ = v___x_1013_;
v___y_998_ = v___y_1012_;
v___y_999_ = v___y_1010_;
v___y_1000_ = v___y_1011_;
v___y_1001_ = v___y_1010_;
goto v___jp_992_;
}
}
v___jp_1016_:
{
uint64_t v___x_1026_; uint8_t v___x_1027_; 
v___x_1026_ = lean_uint64_shift_right(v___y_1018_, v___y_1021_);
v___x_1027_ = lean_uint64_dec_eq(v___x_1026_, v___y_1022_);
if (v___x_1027_ == 0)
{
uint64_t v___x_1028_; 
v___x_1028_ = lean_uint64_add(v___y_1017_, v___y_1021_);
v___y_1006_ = v___y_1020_;
v___y_1007_ = v___y_1019_;
v___y_1008_ = v___y_1023_;
v___y_1009_ = v___y_1022_;
v___y_1010_ = v___y_1025_;
v___y_1011_ = v___y_1024_;
v___y_1012_ = v___x_1028_;
goto v___jp_1005_;
}
else
{
v___y_1006_ = v___y_1020_;
v___y_1007_ = v___y_1019_;
v___y_1008_ = v___y_1023_;
v___y_1009_ = v___y_1022_;
v___y_1010_ = v___y_1025_;
v___y_1011_ = v___y_1024_;
v___y_1012_ = v___y_1017_;
goto v___jp_1005_;
}
}
v___jp_1029_:
{
uint64_t v___x_1037_; uint64_t v___x_1038_; uint8_t v___x_1039_; 
v___x_1037_ = 8ULL;
v___x_1038_ = lean_uint64_shift_right(v___y_1032_, v___x_1037_);
v___x_1039_ = lean_uint64_dec_eq(v___x_1038_, v___y_1034_);
if (v___x_1039_ == 0)
{
v___y_1017_ = v___y_1036_;
v___y_1018_ = v___y_1032_;
v___y_1019_ = v___y_1031_;
v___y_1020_ = v___y_1030_;
v___y_1021_ = v___x_1037_;
v___y_1022_ = v___y_1034_;
v___y_1023_ = v___y_1033_;
v___y_1024_ = v___y_1035_;
v___y_1025_ = v___x_1038_;
goto v___jp_1016_;
}
else
{
v___y_1017_ = v___y_1036_;
v___y_1018_ = v___y_1032_;
v___y_1019_ = v___y_1031_;
v___y_1020_ = v___y_1030_;
v___y_1021_ = v___x_1037_;
v___y_1022_ = v___y_1034_;
v___y_1023_ = v___y_1033_;
v___y_1024_ = v___y_1035_;
v___y_1025_ = v___y_1032_;
goto v___jp_1016_;
}
}
v___jp_1040_:
{
uint64_t v___x_1050_; uint8_t v___x_1051_; 
v___x_1050_ = lean_uint64_shift_right(v___y_1043_, v___y_1045_);
v___x_1051_ = lean_uint64_dec_eq(v___x_1050_, v___y_1046_);
if (v___x_1051_ == 0)
{
uint64_t v___x_1052_; 
v___x_1052_ = lean_uint64_add(v___y_1044_, v___y_1045_);
v___y_1030_ = v___y_1042_;
v___y_1031_ = v___y_1041_;
v___y_1032_ = v___y_1049_;
v___y_1033_ = v___y_1047_;
v___y_1034_ = v___y_1046_;
v___y_1035_ = v___y_1048_;
v___y_1036_ = v___x_1052_;
goto v___jp_1029_;
}
else
{
v___y_1030_ = v___y_1042_;
v___y_1031_ = v___y_1041_;
v___y_1032_ = v___y_1049_;
v___y_1033_ = v___y_1047_;
v___y_1034_ = v___y_1046_;
v___y_1035_ = v___y_1048_;
v___y_1036_ = v___y_1044_;
goto v___jp_1029_;
}
}
v___jp_1053_:
{
uint64_t v___x_1061_; uint64_t v___x_1062_; uint8_t v___x_1063_; 
v___x_1061_ = 16ULL;
v___x_1062_ = lean_uint64_shift_right(v___y_1056_, v___x_1061_);
v___x_1063_ = lean_uint64_dec_eq(v___x_1062_, v___y_1058_);
if (v___x_1063_ == 0)
{
v___y_1041_ = v___y_1055_;
v___y_1042_ = v___y_1054_;
v___y_1043_ = v___y_1056_;
v___y_1044_ = v___y_1060_;
v___y_1045_ = v___x_1061_;
v___y_1046_ = v___y_1058_;
v___y_1047_ = v___y_1057_;
v___y_1048_ = v___y_1059_;
v___y_1049_ = v___x_1062_;
goto v___jp_1040_;
}
else
{
v___y_1041_ = v___y_1055_;
v___y_1042_ = v___y_1054_;
v___y_1043_ = v___y_1056_;
v___y_1044_ = v___y_1060_;
v___y_1045_ = v___x_1061_;
v___y_1046_ = v___y_1058_;
v___y_1047_ = v___y_1057_;
v___y_1048_ = v___y_1059_;
v___y_1049_ = v___y_1056_;
goto v___jp_1040_;
}
}
v___jp_1064_:
{
uint64_t v___x_1072_; uint8_t v___x_1073_; 
v___x_1072_ = lean_uint64_shift_right(v___y_1065_, v___y_1070_);
v___x_1073_ = lean_uint64_dec_eq(v___x_1072_, v___y_1067_);
if (v___x_1073_ == 0)
{
v___y_1054_ = v___y_1066_;
v___y_1055_ = v___y_1065_;
v___y_1056_ = v___y_1071_;
v___y_1057_ = v___y_1068_;
v___y_1058_ = v___y_1067_;
v___y_1059_ = v___y_1069_;
v___y_1060_ = v___y_1070_;
goto v___jp_1053_;
}
else
{
v___y_1054_ = v___y_1066_;
v___y_1055_ = v___y_1065_;
v___y_1056_ = v___y_1071_;
v___y_1057_ = v___y_1068_;
v___y_1058_ = v___y_1067_;
v___y_1059_ = v___y_1069_;
v___y_1060_ = v___y_1067_;
goto v___jp_1053_;
}
}
v___jp_1074_:
{
uint64_t v___x_1079_; uint8_t v___x_1080_; 
v___x_1079_ = 0ULL;
v___x_1080_ = lean_uint64_dec_eq(v___y_1075_, v___x_1079_);
if (v___x_1080_ == 0)
{
uint64_t v___x_1081_; uint64_t v___x_1082_; uint8_t v___x_1083_; 
v___x_1081_ = 32ULL;
v___x_1082_ = lean_uint64_shift_right(v___y_1075_, v___x_1081_);
v___x_1083_ = lean_uint64_dec_eq(v___x_1082_, v___x_1079_);
if (v___x_1083_ == 0)
{
v___y_1065_ = v___y_1075_;
v___y_1066_ = v___y_1076_;
v___y_1067_ = v___x_1079_;
v___y_1068_ = v___y_1077_;
v___y_1069_ = v___y_1078_;
v___y_1070_ = v___x_1081_;
v___y_1071_ = v___x_1082_;
goto v___jp_1064_;
}
else
{
v___y_1065_ = v___y_1075_;
v___y_1066_ = v___y_1076_;
v___y_1067_ = v___x_1079_;
v___y_1068_ = v___y_1077_;
v___y_1069_ = v___y_1078_;
v___y_1070_ = v___x_1081_;
v___y_1071_ = v___y_1075_;
goto v___jp_1064_;
}
}
else
{
if (v___y_1076_ == 0)
{
uint32_t v___x_1084_; 
v___x_1084_ = 0;
return v___x_1084_;
}
else
{
uint32_t v___x_1085_; 
v___x_1085_ = 2147483648;
return v___x_1085_;
}
}
}
v___jp_1086_:
{
uint64_t v___x_1093_; uint64_t v___x_1094_; uint64_t v___x_1095_; uint8_t v___x_1096_; 
v___x_1093_ = lean_uint64_mul(v___y_1088_, v___y_1091_);
v___x_1094_ = lean_uint64_add(v___y_1090_, v___y_1092_);
v___x_1095_ = 281474976710656ULL;
v___x_1096_ = lean_uint64_dec_lt(v___x_1093_, v___x_1095_);
if (v___x_1096_ == 0)
{
v___y_1075_ = v___x_1093_;
v___y_1076_ = v___y_1087_;
v___y_1077_ = v___x_1094_;
v___y_1078_ = v___y_1089_;
goto v___jp_1074_;
}
else
{
uint64_t v___x_1097_; uint8_t v___x_1098_; 
v___x_1097_ = 123ULL;
v___x_1098_ = lean_uint64_dec_le(v___x_1094_, v___x_1097_);
if (v___x_1098_ == 0)
{
v___y_1075_ = v___x_1093_;
v___y_1076_ = v___y_1087_;
v___y_1077_ = v___x_1094_;
v___y_1078_ = v___y_1089_;
goto v___jp_1074_;
}
else
{
uint64_t v___x_1099_; uint8_t v___x_1100_; 
v___x_1099_ = 0ULL;
v___x_1100_ = lean_uint64_dec_eq(v___x_1093_, v___x_1099_);
if (v___x_1100_ == 0)
{
uint64_t v___x_1101_; uint64_t v___x_1102_; uint8_t v___x_1103_; 
v___x_1101_ = 149ULL;
v___x_1102_ = lean_uint64_sub(v___x_1101_, v___x_1094_);
v___x_1103_ = lean_uint64_dec_eq(v___x_1102_, v___x_1099_);
if (v___x_1103_ == 0)
{
uint64_t v___x_1104_; uint8_t v___x_1105_; 
v___x_1104_ = 64ULL;
v___x_1105_ = lean_uint64_dec_lt(v___x_1102_, v___x_1104_);
if (v___x_1105_ == 0)
{
uint8_t v___x_1106_; 
v___x_1106_ = lean_uint64_dec_eq(v___x_1102_, v___x_1104_);
if (v___x_1106_ == 0)
{
v___y_718_ = v___y_1087_;
v___y_719_ = v___x_1099_;
v___y_720_ = v___y_1089_;
v___y_721_ = v___x_1099_;
goto v___jp_717_;
}
else
{
uint64_t v___x_1107_; uint8_t v___x_1108_; 
v___x_1107_ = 9223372036854775808ULL;
v___x_1108_ = lean_uint64_dec_lt(v___x_1107_, v___x_1093_);
if (v___x_1108_ == 0)
{
v___y_718_ = v___y_1087_;
v___y_719_ = v___x_1099_;
v___y_720_ = v___y_1089_;
v___y_721_ = v___x_1099_;
goto v___jp_717_;
}
else
{
uint64_t v___x_1109_; 
v___x_1109_ = 1ULL;
v___y_718_ = v___y_1087_;
v___y_719_ = v___x_1099_;
v___y_720_ = v___y_1089_;
v___y_721_ = v___x_1109_;
goto v___jp_717_;
}
}
}
else
{
uint64_t v_quotient_1110_; uint64_t v___x_1111_; uint64_t v___x_1112_; uint64_t v___x_1113_; uint64_t v_remainder_1114_; uint64_t v___x_1115_; uint64_t v_half_1116_; uint8_t v___x_1117_; 
v_quotient_1110_ = lean_uint64_shift_right(v___x_1093_, v___x_1102_);
v___x_1111_ = 1ULL;
v___x_1112_ = lean_uint64_shift_left(v___x_1111_, v___x_1102_);
v___x_1113_ = lean_uint64_sub(v___x_1112_, v___x_1111_);
v_remainder_1114_ = lean_uint64_land(v___x_1093_, v___x_1113_);
v___x_1115_ = lean_uint64_sub(v___x_1102_, v___x_1111_);
v_half_1116_ = lean_uint64_shift_left(v___x_1111_, v___x_1115_);
v___x_1117_ = lean_uint64_dec_lt(v_remainder_1114_, v_half_1116_);
if (v___x_1117_ == 0)
{
uint8_t v___x_1118_; 
v___x_1118_ = lean_uint64_dec_lt(v_half_1116_, v_remainder_1114_);
if (v___x_1118_ == 0)
{
uint64_t v___x_1119_; uint8_t v___x_1120_; 
v___x_1119_ = lean_uint64_land(v_quotient_1110_, v___x_1111_);
v___x_1120_ = lean_uint64_dec_eq(v___x_1119_, v___x_1099_);
if (v___x_1120_ == 0)
{
uint64_t v___x_1121_; 
v___x_1121_ = lean_uint64_add(v_quotient_1110_, v___x_1111_);
v___y_718_ = v___y_1087_;
v___y_719_ = v___x_1099_;
v___y_720_ = v___y_1089_;
v___y_721_ = v___x_1121_;
goto v___jp_717_;
}
else
{
v___y_718_ = v___y_1087_;
v___y_719_ = v___x_1099_;
v___y_720_ = v___y_1089_;
v___y_721_ = v_quotient_1110_;
goto v___jp_717_;
}
}
else
{
uint64_t v___x_1122_; 
v___x_1122_ = lean_uint64_add(v_quotient_1110_, v___x_1111_);
v___y_718_ = v___y_1087_;
v___y_719_ = v___x_1099_;
v___y_720_ = v___y_1089_;
v___y_721_ = v___x_1122_;
goto v___jp_717_;
}
}
else
{
v___y_718_ = v___y_1087_;
v___y_719_ = v___x_1099_;
v___y_720_ = v___y_1089_;
v___y_721_ = v_quotient_1110_;
goto v___jp_717_;
}
}
}
else
{
v___y_718_ = v___y_1087_;
v___y_719_ = v___x_1099_;
v___y_720_ = v___y_1089_;
v___y_721_ = v___x_1093_;
goto v___jp_717_;
}
}
else
{
if (v___y_1087_ == 0)
{
uint32_t v___x_1123_; 
v___x_1123_ = 0;
return v___x_1123_;
}
else
{
uint32_t v___x_1124_; 
v___x_1124_ = 2147483648;
return v___x_1124_;
}
}
}
}
}
v___jp_1128_:
{
uint64_t v___x_1134_; uint64_t v___x_1135_; uint8_t v___x_1136_; 
v___x_1134_ = lean_uint32_to_uint64(v_ey_1127_);
v___x_1135_ = 0ULL;
v___x_1136_ = lean_uint64_dec_eq(v___x_1134_, v___x_1135_);
if (v___x_1136_ == 0)
{
uint64_t v___x_1137_; uint64_t v___x_1138_; 
v___x_1137_ = 1ULL;
v___x_1138_ = lean_uint64_sub(v___x_1134_, v___x_1137_);
v___y_1087_ = v___y_1129_;
v___y_1088_ = v___y_1130_;
v___y_1089_ = v___y_1131_;
v___y_1090_ = v___y_1133_;
v___y_1091_ = v___y_1132_;
v___y_1092_ = v___x_1138_;
goto v___jp_1086_;
}
else
{
v___y_1087_ = v___y_1129_;
v___y_1088_ = v___y_1130_;
v___y_1089_ = v___y_1131_;
v___y_1090_ = v___y_1133_;
v___y_1091_ = v___y_1132_;
v___y_1092_ = v___x_1135_;
goto v___jp_1086_;
}
}
v___jp_1139_:
{
uint64_t v___x_1144_; uint64_t v___x_1145_; uint8_t v___x_1146_; 
v___x_1144_ = lean_uint32_to_uint64(v_ex_1125_);
v___x_1145_ = 0ULL;
v___x_1146_ = lean_uint64_dec_eq(v___x_1144_, v___x_1145_);
if (v___x_1146_ == 0)
{
uint64_t v___x_1147_; uint64_t v___x_1148_; 
v___x_1147_ = 1ULL;
v___x_1148_ = lean_uint64_sub(v___x_1144_, v___x_1147_);
v___y_1129_ = v___y_1140_;
v___y_1130_ = v___y_1141_;
v___y_1131_ = v___y_1142_;
v___y_1132_ = v___y_1143_;
v___y_1133_ = v___x_1148_;
goto v___jp_1128_;
}
else
{
v___y_1129_ = v___y_1140_;
v___y_1130_ = v___y_1141_;
v___y_1131_ = v___y_1142_;
v___y_1132_ = v___y_1143_;
v___y_1133_ = v___x_1145_;
goto v___jp_1128_;
}
}
v___jp_1149_:
{
uint32_t v___x_1154_; uint8_t v___x_1155_; 
v___x_1154_ = 0;
v___x_1155_ = lean_uint32_dec_eq(v_ey_1127_, v___x_1154_);
if (v___x_1155_ == 0)
{
uint64_t v___x_1156_; uint64_t v___x_1157_; uint64_t v___x_1158_; 
v___x_1156_ = lean_uint32_to_uint64(v___y_1151_);
v___x_1157_ = 8388608ULL;
v___x_1158_ = lean_uint64_lor(v___x_1156_, v___x_1157_);
v___y_1140_ = v___y_1150_;
v___y_1141_ = v___y_1153_;
v___y_1142_ = v___y_1152_;
v___y_1143_ = v___x_1158_;
goto v___jp_1139_;
}
else
{
uint64_t v___x_1159_; 
v___x_1159_ = lean_uint32_to_uint64(v___y_1151_);
v___y_1140_ = v___y_1150_;
v___y_1141_ = v___y_1153_;
v___y_1142_ = v___y_1152_;
v___y_1143_ = v___x_1159_;
goto v___jp_1139_;
}
}
v___jp_1160_:
{
uint32_t v___x_1162_; uint32_t v_xFraction_1163_; uint32_t v_yFraction_1164_; uint32_t v___x_1165_; uint8_t v___x_1166_; 
v___x_1162_ = 8388607;
v_xFraction_1163_ = lean_uint32_land(v___y_680_, v___x_1162_);
v_yFraction_1164_ = lean_uint32_land(v___y_681_, v___x_1162_);
v___x_1165_ = 0;
v___x_1166_ = lean_uint32_dec_eq(v_ex_1125_, v___x_1165_);
if (v___x_1166_ == 0)
{
uint64_t v___x_1167_; uint64_t v___x_1168_; uint64_t v___x_1169_; 
v___x_1167_ = lean_uint32_to_uint64(v_xFraction_1163_);
v___x_1168_ = 8388608ULL;
v___x_1169_ = lean_uint64_lor(v___x_1167_, v___x_1168_);
v___y_1150_ = v___y_1161_;
v___y_1151_ = v_yFraction_1164_;
v___y_1152_ = v___x_1162_;
v___y_1153_ = v___x_1169_;
goto v___jp_1149_;
}
else
{
uint64_t v___x_1170_; 
v___x_1170_ = lean_uint32_to_uint64(v_xFraction_1163_);
v___y_1150_ = v___y_1161_;
v___y_1151_ = v_yFraction_1164_;
v___y_1152_ = v___x_1162_;
v___y_1153_ = v___x_1170_;
goto v___jp_1149_;
}
}
v___jp_1174_:
{
if (v___y_1176_ == 0)
{
v___y_1161_ = v___x_1173_;
goto v___jp_1160_;
}
else
{
v___y_1161_ = v___y_1175_;
goto v___jp_1160_;
}
}
v___jp_1177_:
{
if (v___y_1179_ == 0)
{
if (v___y_1180_ == 0)
{
v___y_1175_ = v___y_1178_;
v___y_1176_ = v___x_1173_;
goto v___jp_1174_;
}
else
{
v___y_1161_ = v___x_1173_;
goto v___jp_1160_;
}
}
else
{
v___y_1175_ = v___y_1178_;
v___y_1176_ = v___y_1180_;
goto v___jp_1174_;
}
}
v___jp_1181_:
{
uint32_t v___x_1184_; uint32_t v___x_1185_; uint32_t v___x_1186_; uint8_t v___x_1187_; 
v___x_1184_ = 2147483648;
v___x_1185_ = lean_uint32_land(v___y_681_, v___x_1184_);
v___x_1186_ = 0;
v___x_1187_ = lean_uint32_dec_eq(v___x_1185_, v___x_1186_);
if (v___x_1187_ == 0)
{
v___y_1178_ = v___y_1182_;
v___y_1179_ = v___y_1183_;
v___y_1180_ = v___x_1173_;
goto v___jp_1177_;
}
else
{
v___y_1178_ = v___y_1182_;
v___y_1179_ = v___y_1183_;
v___y_1180_ = v___y_1182_;
goto v___jp_1177_;
}
}
v___jp_1188_:
{
if (v___y_1189_ == 0)
{
uint32_t v___x_1190_; uint32_t v___x_1191_; uint32_t v___x_1192_; uint8_t v___x_1193_; 
v___x_1190_ = 2147483648;
v___x_1191_ = lean_uint32_land(v___y_680_, v___x_1190_);
v___x_1192_ = 0;
v___x_1193_ = lean_uint32_dec_eq(v___x_1191_, v___x_1192_);
if (v___x_1193_ == 0)
{
v___y_1182_ = v___y_1189_;
v___y_1183_ = v___x_1173_;
goto v___jp_1181_;
}
else
{
v___y_1182_ = v___y_1189_;
v___y_1183_ = v___y_1189_;
goto v___jp_1181_;
}
}
else
{
lean_object* v___x_1194_; lean_object* v___x_1195_; lean_object* v___x_1196_; uint32_t v___x_1197_; 
v___x_1194_ = lean_uint32_to_nat(v___y_680_);
v___x_1195_ = lean_uint32_to_nat(v___y_681_);
v___x_1196_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1194_, v___x_1195_);
v___x_1197_ = lean_uint32_of_nat(v___x_1196_);
lean_dec(v___x_1196_);
return v___x_1197_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_runRaw8___lam__1___boxed(lean_object* v___y_1212_, lean_object* v___y_1213_){
_start:
{
uint32_t v___y_2190__boxed_1214_; uint32_t v___y_2191__boxed_1215_; uint32_t v_res_1216_; lean_object* v_r_1217_; 
v___y_2190__boxed_1214_ = lean_unbox_uint32(v___y_1212_);
lean_dec(v___y_1212_);
v___y_2191__boxed_1215_ = lean_unbox_uint32(v___y_1213_);
lean_dec(v___y_1213_);
v_res_1216_ = lp_competition_runRaw8___lam__1(v___y_2190__boxed_1214_, v___y_2191__boxed_1215_);
v_r_1217_ = lean_box_uint32(v_res_1216_);
return v_r_1217_;
}
}
LEAN_EXPORT lean_object* lp_competition_runRaw8(){
_start:
{
lean_object* v___f_1221_; lean_object* v___f_1222_; lean_object* v___x_1223_; lean_object* v___x_1224_; lean_object* v___x_1225_; 
v___f_1221_ = ((lean_object*)(lp_competition_runControl___closed__0));
v___f_1222_ = ((lean_object*)(lp_competition_runRaw8___closed__0));
v___x_1223_ = ((lean_object*)(lp_competition_runControl___closed__2));
v___x_1224_ = ((lean_object*)(lp_competition_runRaw8___closed__1));
v___x_1225_ = lp_competition_Bench_Suite_run(v___f_1221_, v___f_1222_, v___x_1223_, v___x_1224_);
return v___x_1225_;
}
}
LEAN_EXPORT lean_object* lp_competition_runRaw8___boxed(lean_object* v_a_1226_){
_start:
{
lean_object* v_res_1227_; 
v_res_1227_ = lp_competition_runRaw8();
return v_res_1227_;
}
}
LEAN_EXPORT uint32_t lp_competition_runIndexed8___lam__1(uint32_t v___y_1228_, uint32_t v___y_1229_){
_start:
{
uint32_t v___y_1231_; uint32_t v___y_1235_; uint32_t v___y_1239_; uint32_t v___y_1240_; uint32_t v___y_1241_; uint64_t v___y_1245_; uint8_t v___y_1246_; uint32_t v___y_1247_; uint64_t v___y_1248_; uint32_t v___y_1260_; uint32_t v___y_1261_; uint32_t v___y_1262_; uint64_t v___y_1266_; uint8_t v___y_1267_; uint32_t v___y_1268_; uint64_t v___y_1269_; uint8_t v___y_1281_; uint8_t v___y_1297_; uint8_t v___y_1311_; uint8_t v___y_1328_; float v___y_1335_; float v___y_1336_; float v___y_1350_; uint8_t v___y_1351_; float v___y_1366_; uint32_t v___x_1375_; uint32_t v___x_1376_; uint8_t v___y_1378_; uint32_t v___x_1390_; uint32_t v___y_1392_; uint32_t v___y_1393_; uint32_t v___y_1394_; uint32_t v___y_1395_; uint32_t v___y_1402_; uint8_t v___y_1403_; uint32_t v___y_1404_; uint32_t v___y_1405_; uint64_t v___y_1409_; uint64_t v___y_1410_; uint8_t v___y_1411_; uint32_t v___y_1412_; uint64_t v___y_1413_; uint64_t v___y_1423_; uint64_t v___y_1424_; uint8_t v___y_1425_; uint8_t v___y_1426_; uint32_t v___y_1427_; uint64_t v___y_1428_; uint64_t v___y_1435_; uint64_t v___y_1436_; uint8_t v___y_1437_; uint32_t v___y_1438_; uint64_t v___y_1439_; uint64_t v___y_1445_; uint64_t v___y_1446_; uint8_t v___y_1447_; uint64_t v___y_1448_; uint32_t v___y_1449_; uint64_t v___y_1450_; uint64_t v___y_1505_; uint64_t v___y_1506_; uint64_t v___y_1507_; uint8_t v___y_1508_; uint32_t v___y_1509_; uint64_t v___y_1510_; uint64_t v___y_1511_; uint64_t v___y_1517_; uint64_t v___y_1518_; uint64_t v___y_1519_; uint8_t v___y_1520_; uint64_t v___y_1521_; uint64_t v___y_1522_; uint64_t v___y_1523_; uint32_t v___y_1524_; uint64_t v___y_1525_; uint64_t v___y_1530_; uint64_t v___y_1531_; uint8_t v___y_1532_; uint64_t v___y_1533_; uint32_t v___y_1534_; uint64_t v___y_1535_; uint64_t v___y_1536_; uint64_t v___y_1541_; uint64_t v___y_1542_; uint64_t v___y_1543_; uint64_t v___y_1544_; uint64_t v___y_1545_; uint8_t v___y_1546_; uint64_t v___y_1547_; uint32_t v___y_1548_; uint64_t v___y_1549_; uint64_t v___y_1554_; uint64_t v___y_1555_; uint8_t v___y_1556_; uint64_t v___y_1557_; uint32_t v___y_1558_; uint64_t v___y_1559_; uint64_t v___y_1560_; uint64_t v___y_1565_; uint64_t v___y_1566_; uint64_t v___y_1567_; uint64_t v___y_1568_; uint8_t v___y_1569_; uint64_t v___y_1570_; uint64_t v___y_1571_; uint32_t v___y_1572_; uint64_t v___y_1573_; uint64_t v___y_1578_; uint64_t v___y_1579_; uint8_t v___y_1580_; uint64_t v___y_1581_; uint32_t v___y_1582_; uint64_t v___y_1583_; uint64_t v___y_1584_; uint64_t v___y_1589_; uint64_t v___y_1590_; uint64_t v___y_1591_; uint64_t v___y_1592_; uint8_t v___y_1593_; uint64_t v___y_1594_; uint32_t v___y_1595_; uint64_t v___y_1596_; uint64_t v___y_1597_; uint64_t v___y_1602_; uint64_t v___y_1603_; uint64_t v___y_1604_; uint8_t v___y_1605_; uint32_t v___y_1606_; uint64_t v___y_1607_; uint64_t v___y_1608_; uint64_t v___y_1613_; uint64_t v___y_1614_; uint64_t v___y_1615_; uint8_t v___y_1616_; uint64_t v___y_1617_; uint32_t v___y_1618_; uint64_t v___y_1619_; uint64_t v___y_1623_; uint8_t v___y_1624_; uint64_t v___y_1625_; uint32_t v___y_1626_; uint64_t v___y_1635_; uint64_t v___y_1636_; uint8_t v___y_1637_; uint32_t v___y_1638_; uint64_t v___y_1639_; uint64_t v___y_1640_; uint32_t v_ex_1673_; uint32_t v___x_1674_; uint32_t v_ey_1675_; uint64_t v___y_1677_; uint8_t v___y_1678_; uint64_t v___y_1679_; uint32_t v___y_1680_; uint64_t v___y_1681_; uint8_t v___y_1688_; uint32_t v___y_1689_; uint64_t v___y_1690_; uint64_t v___y_1691_; uint32_t v___y_1698_; uint8_t v___y_1699_; uint32_t v___y_1700_; uint64_t v___y_1701_; uint8_t v___y_1709_; uint32_t v___x_1719_; uint32_t v___x_1720_; uint8_t v___x_1721_; uint8_t v___y_1723_; uint8_t v___y_1724_; uint8_t v___y_1726_; uint8_t v___y_1727_; uint8_t v___y_1728_; uint8_t v___y_1730_; uint8_t v___y_1731_; uint8_t v___y_1737_; 
v___x_1375_ = 23;
v___x_1376_ = lean_uint32_shift_right(v___y_1228_, v___x_1375_);
v___x_1390_ = 255;
v_ex_1673_ = lean_uint32_land(v___x_1376_, v___x_1390_);
v___x_1674_ = lean_uint32_shift_right(v___y_1229_, v___x_1375_);
v_ey_1675_ = lean_uint32_land(v___x_1674_, v___x_1390_);
v___x_1719_ = lean_uint32_add(v_ex_1673_, v_ey_1675_);
v___x_1720_ = 128;
v___x_1721_ = lean_uint32_dec_lt(v___x_1719_, v___x_1720_);
if (v___x_1721_ == 0)
{
uint32_t v___x_1746_; uint32_t v_a_1747_; uint32_t v___x_1748_; uint32_t v___x_1749_; uint32_t v___x_1750_; uint8_t v___x_1751_; 
v___x_1746_ = 2147483647;
v_a_1747_ = lean_uint32_land(v___y_1228_, v___x_1746_);
v___x_1748_ = 201326591;
v___x_1749_ = 1;
v___x_1750_ = lean_uint32_sub(v_a_1747_, v___x_1749_);
v___x_1751_ = lean_uint32_dec_le(v___x_1748_, v___x_1750_);
if (v___x_1751_ == 0)
{
v___y_1378_ = v___x_1751_;
goto v___jp_1377_;
}
else
{
uint32_t v___x_1752_; uint8_t v___x_1753_; 
v___x_1752_ = 2139095040;
v___x_1753_ = lean_uint32_dec_lt(v_a_1747_, v___x_1752_);
v___y_1378_ = v___x_1753_;
goto v___jp_1377_;
}
}
else
{
uint32_t v___x_1754_; uint32_t v___x_1755_; uint32_t v___x_1756_; uint8_t v___x_1757_; 
v___x_1754_ = 4278190080;
v___x_1755_ = 1;
v___x_1756_ = lean_uint32_shift_left(v___y_1228_, v___x_1755_);
v___x_1757_ = lean_uint32_dec_le(v___x_1754_, v___x_1756_);
if (v___x_1757_ == 0)
{
uint32_t v___x_1758_; uint8_t v___x_1759_; 
v___x_1758_ = lean_uint32_shift_left(v___y_1229_, v___x_1755_);
v___x_1759_ = lean_uint32_dec_le(v___x_1754_, v___x_1758_);
v___y_1737_ = v___x_1759_;
goto v___jp_1736_;
}
else
{
v___y_1737_ = v___x_1757_;
goto v___jp_1736_;
}
}
v___jp_1230_:
{
uint32_t v___x_1232_; uint32_t v___x_1233_; 
v___x_1232_ = 8388608;
v___x_1233_ = lean_uint32_lor(v___y_1231_, v___x_1232_);
return v___x_1233_;
}
v___jp_1234_:
{
uint32_t v___x_1236_; uint32_t v___x_1237_; 
v___x_1236_ = 8388608;
v___x_1237_ = lean_uint32_lor(v___y_1235_, v___x_1236_);
return v___x_1237_;
}
v___jp_1238_:
{
uint32_t v___x_1242_; uint32_t v___x_1243_; 
v___x_1242_ = lean_uint32_land(v___y_1239_, v___y_1240_);
v___x_1243_ = lean_uint32_lor(v___y_1241_, v___x_1242_);
return v___x_1243_;
}
v___jp_1244_:
{
uint8_t v___x_1249_; 
v___x_1249_ = lean_uint64_dec_eq(v___y_1248_, v___y_1245_);
if (v___x_1249_ == 0)
{
uint64_t v___x_1250_; uint8_t v___x_1251_; 
v___x_1250_ = 8388608ULL;
v___x_1251_ = lean_uint64_dec_eq(v___y_1248_, v___x_1250_);
if (v___x_1251_ == 0)
{
uint32_t v___x_1252_; 
v___x_1252_ = lean_uint64_to_uint32(v___y_1248_);
if (v___y_1246_ == 0)
{
uint32_t v___x_1253_; 
v___x_1253_ = 0;
v___y_1239_ = v___x_1252_;
v___y_1240_ = v___y_1247_;
v___y_1241_ = v___x_1253_;
goto v___jp_1238_;
}
else
{
uint32_t v___x_1254_; 
v___x_1254_ = 2147483648;
v___y_1239_ = v___x_1252_;
v___y_1240_ = v___y_1247_;
v___y_1241_ = v___x_1254_;
goto v___jp_1238_;
}
}
else
{
if (v___y_1246_ == 0)
{
uint32_t v___x_1255_; 
v___x_1255_ = 0;
v___y_1235_ = v___x_1255_;
goto v___jp_1234_;
}
else
{
uint32_t v___x_1256_; 
v___x_1256_ = 2147483648;
v___y_1235_ = v___x_1256_;
goto v___jp_1234_;
}
}
}
else
{
if (v___y_1246_ == 0)
{
uint32_t v___x_1257_; 
v___x_1257_ = 0;
return v___x_1257_;
}
else
{
uint32_t v___x_1258_; 
v___x_1258_ = 2147483648;
return v___x_1258_;
}
}
}
v___jp_1259_:
{
uint32_t v___x_1263_; uint32_t v___x_1264_; 
v___x_1263_ = lean_uint32_land(v___y_1260_, v___y_1261_);
v___x_1264_ = lean_uint32_lor(v___y_1262_, v___x_1263_);
return v___x_1264_;
}
v___jp_1265_:
{
uint8_t v___x_1270_; 
v___x_1270_ = lean_uint64_dec_eq(v___y_1269_, v___y_1266_);
if (v___x_1270_ == 0)
{
uint64_t v___x_1271_; uint8_t v___x_1272_; 
v___x_1271_ = 8388608ULL;
v___x_1272_ = lean_uint64_dec_eq(v___y_1269_, v___x_1271_);
if (v___x_1272_ == 0)
{
uint32_t v___x_1273_; 
v___x_1273_ = lean_uint64_to_uint32(v___y_1269_);
if (v___y_1267_ == 0)
{
uint32_t v___x_1274_; 
v___x_1274_ = 0;
v___y_1260_ = v___x_1273_;
v___y_1261_ = v___y_1268_;
v___y_1262_ = v___x_1274_;
goto v___jp_1259_;
}
else
{
uint32_t v___x_1275_; 
v___x_1275_ = 2147483648;
v___y_1260_ = v___x_1273_;
v___y_1261_ = v___y_1268_;
v___y_1262_ = v___x_1275_;
goto v___jp_1259_;
}
}
else
{
if (v___y_1267_ == 0)
{
uint32_t v___x_1276_; 
v___x_1276_ = 0;
v___y_1231_ = v___x_1276_;
goto v___jp_1230_;
}
else
{
uint32_t v___x_1277_; 
v___x_1277_ = 2147483648;
v___y_1231_ = v___x_1277_;
goto v___jp_1230_;
}
}
}
else
{
if (v___y_1267_ == 0)
{
uint32_t v___x_1278_; 
v___x_1278_ = 0;
return v___x_1278_;
}
else
{
uint32_t v___x_1279_; 
v___x_1279_ = 2147483648;
return v___x_1279_;
}
}
}
v___jp_1280_:
{
if (v___y_1281_ == 0)
{
uint32_t v___x_1282_; 
v___x_1282_ = lp_competition_Submission_FastMul_mul(v___y_1228_, v___y_1229_);
return v___x_1282_;
}
else
{
uint32_t v___x_1283_; uint32_t v___x_1284_; 
v___x_1283_ = 4194304;
v___x_1284_ = lean_uint32_lor(v___y_1229_, v___x_1283_);
return v___x_1284_;
}
}
v___jp_1285_:
{
uint32_t v___x_1286_; uint32_t v___x_1287_; uint32_t v___x_1288_; uint32_t v___x_1289_; uint8_t v___x_1290_; 
v___x_1286_ = 23;
v___x_1287_ = lean_uint32_shift_right(v___y_1229_, v___x_1286_);
v___x_1288_ = 255;
v___x_1289_ = lean_uint32_land(v___x_1287_, v___x_1288_);
v___x_1290_ = lean_uint32_dec_eq(v___x_1289_, v___x_1288_);
if (v___x_1290_ == 0)
{
v___y_1281_ = v___x_1290_;
goto v___jp_1280_;
}
else
{
uint32_t v___x_1291_; uint32_t v___x_1292_; uint32_t v___x_1293_; uint8_t v___x_1294_; 
v___x_1291_ = 8388607;
v___x_1292_ = lean_uint32_land(v___y_1229_, v___x_1291_);
v___x_1293_ = 0;
v___x_1294_ = lean_uint32_dec_eq(v___x_1292_, v___x_1293_);
if (v___x_1294_ == 0)
{
v___y_1281_ = v___x_1290_;
goto v___jp_1280_;
}
else
{
uint32_t v___x_1295_; 
v___x_1295_ = lp_competition_Submission_FastMul_mul(v___y_1228_, v___y_1229_);
return v___x_1295_;
}
}
}
v___jp_1296_:
{
if (v___y_1297_ == 0)
{
goto v___jp_1285_;
}
else
{
uint32_t v___x_1298_; uint32_t v___x_1299_; 
v___x_1298_ = 4194304;
v___x_1299_ = lean_uint32_lor(v___y_1228_, v___x_1298_);
return v___x_1299_;
}
}
v___jp_1300_:
{
uint32_t v___x_1301_; uint32_t v___x_1302_; uint32_t v___x_1303_; uint32_t v___x_1304_; uint8_t v___x_1305_; 
v___x_1301_ = 23;
v___x_1302_ = lean_uint32_shift_right(v___y_1228_, v___x_1301_);
v___x_1303_ = 255;
v___x_1304_ = lean_uint32_land(v___x_1302_, v___x_1303_);
v___x_1305_ = lean_uint32_dec_eq(v___x_1304_, v___x_1303_);
if (v___x_1305_ == 0)
{
v___y_1297_ = v___x_1305_;
goto v___jp_1296_;
}
else
{
uint32_t v___x_1306_; uint32_t v___x_1307_; uint32_t v___x_1308_; uint8_t v___x_1309_; 
v___x_1306_ = 8388607;
v___x_1307_ = lean_uint32_land(v___y_1228_, v___x_1306_);
v___x_1308_ = 0;
v___x_1309_ = lean_uint32_dec_eq(v___x_1307_, v___x_1308_);
if (v___x_1309_ == 0)
{
v___y_1297_ = v___x_1305_;
goto v___jp_1296_;
}
else
{
goto v___jp_1285_;
}
}
}
v___jp_1310_:
{
if (v___y_1311_ == 0)
{
goto v___jp_1300_;
}
else
{
uint32_t v___x_1312_; uint32_t v___x_1313_; uint32_t v___x_1314_; uint8_t v___x_1315_; 
v___x_1312_ = 4194304;
v___x_1313_ = lean_uint32_land(v___y_1229_, v___x_1312_);
v___x_1314_ = 0;
v___x_1315_ = lean_uint32_dec_eq(v___x_1313_, v___x_1314_);
if (v___x_1315_ == 0)
{
goto v___jp_1300_;
}
else
{
uint32_t v___x_1316_; 
v___x_1316_ = lean_uint32_lor(v___y_1229_, v___x_1312_);
return v___x_1316_;
}
}
}
v___jp_1317_:
{
uint32_t v___x_1318_; uint32_t v___x_1319_; uint32_t v___x_1320_; uint32_t v___x_1321_; uint8_t v___x_1322_; 
v___x_1318_ = 23;
v___x_1319_ = lean_uint32_shift_right(v___y_1229_, v___x_1318_);
v___x_1320_ = 255;
v___x_1321_ = lean_uint32_land(v___x_1319_, v___x_1320_);
v___x_1322_ = lean_uint32_dec_eq(v___x_1321_, v___x_1320_);
if (v___x_1322_ == 0)
{
v___y_1311_ = v___x_1322_;
goto v___jp_1310_;
}
else
{
uint32_t v___x_1323_; uint32_t v___x_1324_; uint32_t v___x_1325_; uint8_t v___x_1326_; 
v___x_1323_ = 8388607;
v___x_1324_ = lean_uint32_land(v___y_1229_, v___x_1323_);
v___x_1325_ = 0;
v___x_1326_ = lean_uint32_dec_eq(v___x_1324_, v___x_1325_);
if (v___x_1326_ == 0)
{
v___y_1311_ = v___x_1322_;
goto v___jp_1310_;
}
else
{
goto v___jp_1300_;
}
}
}
v___jp_1327_:
{
if (v___y_1328_ == 0)
{
goto v___jp_1317_;
}
else
{
uint32_t v___x_1329_; uint32_t v___x_1330_; uint32_t v___x_1331_; uint8_t v___x_1332_; 
v___x_1329_ = 4194304;
v___x_1330_ = lean_uint32_land(v___y_1228_, v___x_1329_);
v___x_1331_ = 0;
v___x_1332_ = lean_uint32_dec_eq(v___x_1330_, v___x_1331_);
if (v___x_1332_ == 0)
{
goto v___jp_1317_;
}
else
{
uint32_t v___x_1333_; 
v___x_1333_ = lean_uint32_lor(v___y_1228_, v___x_1329_);
return v___x_1333_;
}
}
}
v___jp_1334_:
{
float v_result_1337_; uint8_t v___x_1338_; 
v_result_1337_ = lean_float32_mul(v___y_1335_, v___y_1336_);
v___x_1338_ = lean_float32_beq(v_result_1337_, v_result_1337_);
if (v___x_1338_ == 0)
{
uint32_t v___x_1339_; uint32_t v___x_1340_; uint32_t v___x_1341_; uint32_t v___x_1342_; uint8_t v___x_1343_; 
v___x_1339_ = 23;
v___x_1340_ = lean_uint32_shift_right(v___y_1228_, v___x_1339_);
v___x_1341_ = 255;
v___x_1342_ = lean_uint32_land(v___x_1340_, v___x_1341_);
v___x_1343_ = lean_uint32_dec_eq(v___x_1342_, v___x_1341_);
if (v___x_1343_ == 0)
{
v___y_1328_ = v___x_1343_;
goto v___jp_1327_;
}
else
{
uint32_t v___x_1344_; uint32_t v___x_1345_; uint32_t v___x_1346_; uint8_t v___x_1347_; 
v___x_1344_ = 8388607;
v___x_1345_ = lean_uint32_land(v___y_1228_, v___x_1344_);
v___x_1346_ = 0;
v___x_1347_ = lean_uint32_dec_eq(v___x_1345_, v___x_1346_);
if (v___x_1347_ == 0)
{
v___y_1328_ = v___x_1343_;
goto v___jp_1327_;
}
else
{
goto v___jp_1317_;
}
}
}
else
{
uint32_t v___x_1348_; 
v___x_1348_ = lean_float32_to_bits(v_result_1337_);
return v___x_1348_;
}
}
v___jp_1349_:
{
if (v___y_1351_ == 0)
{
float v___x_1352_; 
v___x_1352_ = lean_float32_of_bits(v___y_1229_);
v___y_1335_ = v___y_1350_;
v___y_1336_ = v___x_1352_;
goto v___jp_1334_;
}
else
{
uint32_t v___x_1353_; uint32_t v___x_1354_; uint32_t v___x_1355_; uint32_t v___x_1356_; float v___x_1357_; lean_object* v___x_1358_; uint32_t v___x_1359_; uint32_t v___x_1360_; lean_object* v___x_1361_; lean_object* v___x_1362_; float v___x_1363_; float v___x_1364_; 
v___x_1353_ = 8388607;
v___x_1354_ = lean_uint32_land(v___y_1229_, v___x_1353_);
v___x_1355_ = 8388608;
v___x_1356_ = lean_uint32_lor(v___x_1354_, v___x_1355_);
v___x_1357_ = lean_uint32_to_float32(v___x_1356_);
v___x_1358_ = lp_competition_R2W01b_scaleTable;
v___x_1359_ = 23;
v___x_1360_ = lean_uint32_shift_right(v___y_1229_, v___x_1359_);
v___x_1361_ = lean_uint32_to_nat(v___x_1360_);
v___x_1362_ = lean_array_fget_borrowed(v___x_1358_, v___x_1361_);
lean_dec(v___x_1361_);
v___x_1363_ = lean_unbox_float32(v___x_1362_);
v___x_1364_ = lean_float32_mul(v___x_1357_, v___x_1363_);
v___y_1335_ = v___y_1350_;
v___y_1336_ = v___x_1364_;
goto v___jp_1334_;
}
}
v___jp_1365_:
{
uint32_t v___x_1367_; uint32_t v_a_1368_; uint32_t v___x_1369_; uint32_t v___x_1370_; uint32_t v___x_1371_; uint8_t v___x_1372_; 
v___x_1367_ = 2147483647;
v_a_1368_ = lean_uint32_land(v___y_1229_, v___x_1367_);
v___x_1369_ = 201326591;
v___x_1370_ = 1;
v___x_1371_ = lean_uint32_sub(v_a_1368_, v___x_1370_);
v___x_1372_ = lean_uint32_dec_le(v___x_1369_, v___x_1371_);
if (v___x_1372_ == 0)
{
v___y_1350_ = v___y_1366_;
v___y_1351_ = v___x_1372_;
goto v___jp_1349_;
}
else
{
uint32_t v___x_1373_; uint8_t v___x_1374_; 
v___x_1373_ = 2139095040;
v___x_1374_ = lean_uint32_dec_lt(v_a_1368_, v___x_1373_);
v___y_1350_ = v___y_1366_;
v___y_1351_ = v___x_1374_;
goto v___jp_1349_;
}
}
v___jp_1377_:
{
if (v___y_1378_ == 0)
{
float v___x_1379_; 
v___x_1379_ = lean_float32_of_bits(v___y_1228_);
v___y_1366_ = v___x_1379_;
goto v___jp_1365_;
}
else
{
uint32_t v___x_1380_; uint32_t v___x_1381_; uint32_t v___x_1382_; uint32_t v___x_1383_; float v___x_1384_; lean_object* v___x_1385_; lean_object* v___x_1386_; lean_object* v___x_1387_; float v___x_1388_; float v___x_1389_; 
v___x_1380_ = 8388607;
v___x_1381_ = lean_uint32_land(v___y_1228_, v___x_1380_);
v___x_1382_ = 8388608;
v___x_1383_ = lean_uint32_lor(v___x_1381_, v___x_1382_);
v___x_1384_ = lean_uint32_to_float32(v___x_1383_);
v___x_1385_ = lp_competition_R2W01b_scaleTable;
v___x_1386_ = lean_uint32_to_nat(v___x_1376_);
v___x_1387_ = lean_array_fget_borrowed(v___x_1385_, v___x_1386_);
lean_dec(v___x_1386_);
v___x_1388_ = lean_unbox_float32(v___x_1387_);
v___x_1389_ = lean_float32_mul(v___x_1384_, v___x_1388_);
v___y_1366_ = v___x_1389_;
goto v___jp_1365_;
}
}
v___jp_1391_:
{
uint32_t v___x_1396_; uint32_t v___x_1397_; uint32_t v___x_1398_; uint32_t v___x_1399_; uint32_t v___x_1400_; 
v___x_1396_ = lean_uint32_land(v___y_1392_, v___x_1390_);
v___x_1397_ = lean_uint32_shift_left(v___x_1396_, v___x_1375_);
v___x_1398_ = lean_uint32_lor(v___y_1395_, v___x_1397_);
v___x_1399_ = lean_uint32_land(v___y_1393_, v___y_1394_);
v___x_1400_ = lean_uint32_lor(v___x_1398_, v___x_1399_);
return v___x_1400_;
}
v___jp_1401_:
{
if (v___y_1403_ == 0)
{
uint32_t v___x_1406_; 
v___x_1406_ = 0;
v___y_1392_ = v___y_1402_;
v___y_1393_ = v___y_1405_;
v___y_1394_ = v___y_1404_;
v___y_1395_ = v___x_1406_;
goto v___jp_1391_;
}
else
{
uint32_t v___x_1407_; 
v___x_1407_ = 2147483648;
v___y_1392_ = v___y_1402_;
v___y_1393_ = v___y_1405_;
v___y_1394_ = v___y_1404_;
v___y_1395_ = v___x_1407_;
goto v___jp_1391_;
}
}
v___jp_1408_:
{
uint64_t v___x_1414_; uint64_t v_encodedExponent_1415_; uint32_t v___x_1416_; uint64_t v___x_1417_; uint8_t v___x_1418_; 
v___x_1414_ = 171ULL;
v_encodedExponent_1415_ = lean_uint64_sub(v___y_1410_, v___x_1414_);
v___x_1416_ = lean_uint64_to_uint32(v_encodedExponent_1415_);
v___x_1417_ = 8388608ULL;
v___x_1418_ = lean_uint64_dec_lt(v___y_1413_, v___x_1417_);
if (v___x_1418_ == 0)
{
uint64_t v___x_1419_; uint32_t v___x_1420_; 
v___x_1419_ = lean_uint64_sub(v___y_1413_, v___x_1417_);
v___x_1420_ = lean_uint64_to_uint32(v___x_1419_);
v___y_1402_ = v___x_1416_;
v___y_1403_ = v___y_1411_;
v___y_1404_ = v___y_1412_;
v___y_1405_ = v___x_1420_;
goto v___jp_1401_;
}
else
{
uint32_t v___x_1421_; 
v___x_1421_ = lean_uint64_to_uint32(v___y_1409_);
v___y_1402_ = v___x_1416_;
v___y_1403_ = v___y_1411_;
v___y_1404_ = v___y_1412_;
v___y_1405_ = v___x_1421_;
goto v___jp_1401_;
}
}
v___jp_1422_:
{
uint64_t v___x_1429_; uint8_t v___x_1430_; 
v___x_1429_ = 425ULL;
v___x_1430_ = lean_uint64_dec_lt(v___x_1429_, v___y_1428_);
if (v___x_1430_ == 0)
{
if (v___y_1425_ == 0)
{
v___y_1409_ = v___y_1424_;
v___y_1410_ = v___y_1428_;
v___y_1411_ = v___y_1426_;
v___y_1412_ = v___y_1427_;
v___y_1413_ = v___y_1423_;
goto v___jp_1408_;
}
else
{
uint64_t v___x_1431_; 
v___x_1431_ = 8388608ULL;
v___y_1409_ = v___y_1424_;
v___y_1410_ = v___y_1428_;
v___y_1411_ = v___y_1426_;
v___y_1412_ = v___y_1427_;
v___y_1413_ = v___x_1431_;
goto v___jp_1408_;
}
}
else
{
if (v___y_1426_ == 0)
{
uint32_t v___x_1432_; 
v___x_1432_ = 2139095040;
return v___x_1432_;
}
else
{
uint32_t v___x_1433_; 
v___x_1433_ = 4286578688;
return v___x_1433_;
}
}
}
v___jp_1434_:
{
uint64_t v___x_1440_; uint8_t v_carry_1441_; 
v___x_1440_ = 16777216ULL;
v_carry_1441_ = lean_uint64_dec_eq(v___y_1439_, v___x_1440_);
if (v_carry_1441_ == 0)
{
v___y_1423_ = v___y_1439_;
v___y_1424_ = v___y_1436_;
v___y_1425_ = v_carry_1441_;
v___y_1426_ = v___y_1437_;
v___y_1427_ = v___y_1438_;
v___y_1428_ = v___y_1435_;
goto v___jp_1422_;
}
else
{
uint64_t v___x_1442_; uint64_t v___x_1443_; 
v___x_1442_ = 1ULL;
v___x_1443_ = lean_uint64_add(v___y_1435_, v___x_1442_);
v___y_1423_ = v___y_1439_;
v___y_1424_ = v___y_1436_;
v___y_1425_ = v_carry_1441_;
v___y_1426_ = v___y_1437_;
v___y_1427_ = v___y_1438_;
v___y_1428_ = v___x_1443_;
goto v___jp_1422_;
}
}
v___jp_1444_:
{
uint64_t v_position_1451_; uint64_t v___x_1452_; uint8_t v___x_1453_; 
v_position_1451_ = lean_uint64_add(v___y_1450_, v___y_1445_);
v___x_1452_ = 172ULL;
v___x_1453_ = lean_uint64_dec_lt(v_position_1451_, v___x_1452_);
if (v___x_1453_ == 0)
{
uint64_t v___x_1454_; uint8_t v___x_1455_; 
v___x_1454_ = 23ULL;
v___x_1455_ = lean_uint64_dec_lt(v___y_1450_, v___x_1454_);
if (v___x_1455_ == 0)
{
uint64_t v___x_1456_; uint8_t v___x_1457_; 
v___x_1456_ = lean_uint64_sub(v___y_1450_, v___x_1454_);
v___x_1457_ = lean_uint64_dec_eq(v___x_1456_, v___y_1446_);
if (v___x_1457_ == 0)
{
uint64_t v___x_1458_; uint8_t v___x_1459_; 
v___x_1458_ = 64ULL;
v___x_1459_ = lean_uint64_dec_lt(v___x_1456_, v___x_1458_);
if (v___x_1459_ == 0)
{
uint8_t v___x_1460_; 
v___x_1460_ = lean_uint64_dec_eq(v___x_1456_, v___x_1458_);
if (v___x_1460_ == 0)
{
v___y_1435_ = v_position_1451_;
v___y_1436_ = v___y_1446_;
v___y_1437_ = v___y_1447_;
v___y_1438_ = v___y_1449_;
v___y_1439_ = v___y_1446_;
goto v___jp_1434_;
}
else
{
uint64_t v___x_1461_; uint8_t v___x_1462_; 
v___x_1461_ = 9223372036854775808ULL;
v___x_1462_ = lean_uint64_dec_lt(v___x_1461_, v___y_1448_);
if (v___x_1462_ == 0)
{
v___y_1435_ = v_position_1451_;
v___y_1436_ = v___y_1446_;
v___y_1437_ = v___y_1447_;
v___y_1438_ = v___y_1449_;
v___y_1439_ = v___y_1446_;
goto v___jp_1434_;
}
else
{
uint64_t v___x_1463_; 
v___x_1463_ = 1ULL;
v___y_1435_ = v_position_1451_;
v___y_1436_ = v___y_1446_;
v___y_1437_ = v___y_1447_;
v___y_1438_ = v___y_1449_;
v___y_1439_ = v___x_1463_;
goto v___jp_1434_;
}
}
}
else
{
uint64_t v_quotient_1464_; uint64_t v___x_1465_; uint64_t v___x_1466_; uint64_t v___x_1467_; uint64_t v_remainder_1468_; uint64_t v___x_1469_; uint64_t v_half_1470_; uint8_t v___x_1471_; 
v_quotient_1464_ = lean_uint64_shift_right(v___y_1448_, v___x_1456_);
v___x_1465_ = 1ULL;
v___x_1466_ = lean_uint64_shift_left(v___x_1465_, v___x_1456_);
v___x_1467_ = lean_uint64_sub(v___x_1466_, v___x_1465_);
v_remainder_1468_ = lean_uint64_land(v___y_1448_, v___x_1467_);
v___x_1469_ = lean_uint64_sub(v___x_1456_, v___x_1465_);
v_half_1470_ = lean_uint64_shift_left(v___x_1465_, v___x_1469_);
v___x_1471_ = lean_uint64_dec_lt(v_remainder_1468_, v_half_1470_);
if (v___x_1471_ == 0)
{
uint8_t v___x_1472_; 
v___x_1472_ = lean_uint64_dec_lt(v_half_1470_, v_remainder_1468_);
if (v___x_1472_ == 0)
{
uint64_t v___x_1473_; uint8_t v___x_1474_; 
v___x_1473_ = lean_uint64_land(v_quotient_1464_, v___x_1465_);
v___x_1474_ = lean_uint64_dec_eq(v___x_1473_, v___y_1446_);
if (v___x_1474_ == 0)
{
uint64_t v___x_1475_; 
v___x_1475_ = lean_uint64_add(v_quotient_1464_, v___x_1465_);
v___y_1435_ = v_position_1451_;
v___y_1436_ = v___y_1446_;
v___y_1437_ = v___y_1447_;
v___y_1438_ = v___y_1449_;
v___y_1439_ = v___x_1475_;
goto v___jp_1434_;
}
else
{
v___y_1435_ = v_position_1451_;
v___y_1436_ = v___y_1446_;
v___y_1437_ = v___y_1447_;
v___y_1438_ = v___y_1449_;
v___y_1439_ = v_quotient_1464_;
goto v___jp_1434_;
}
}
else
{
uint64_t v___x_1476_; 
v___x_1476_ = lean_uint64_add(v_quotient_1464_, v___x_1465_);
v___y_1435_ = v_position_1451_;
v___y_1436_ = v___y_1446_;
v___y_1437_ = v___y_1447_;
v___y_1438_ = v___y_1449_;
v___y_1439_ = v___x_1476_;
goto v___jp_1434_;
}
}
else
{
v___y_1435_ = v_position_1451_;
v___y_1436_ = v___y_1446_;
v___y_1437_ = v___y_1447_;
v___y_1438_ = v___y_1449_;
v___y_1439_ = v_quotient_1464_;
goto v___jp_1434_;
}
}
}
else
{
v___y_1435_ = v_position_1451_;
v___y_1436_ = v___y_1446_;
v___y_1437_ = v___y_1447_;
v___y_1438_ = v___y_1449_;
v___y_1439_ = v___y_1448_;
goto v___jp_1434_;
}
}
else
{
uint64_t v___x_1477_; uint64_t v___x_1478_; 
v___x_1477_ = lean_uint64_sub(v___x_1454_, v___y_1450_);
v___x_1478_ = lean_uint64_shift_left(v___y_1448_, v___x_1477_);
v___y_1435_ = v_position_1451_;
v___y_1436_ = v___y_1446_;
v___y_1437_ = v___y_1447_;
v___y_1438_ = v___y_1449_;
v___y_1439_ = v___x_1478_;
goto v___jp_1434_;
}
}
else
{
uint64_t v___x_1479_; uint8_t v___x_1480_; 
v___x_1479_ = 149ULL;
v___x_1480_ = lean_uint64_dec_lt(v___y_1445_, v___x_1479_);
if (v___x_1480_ == 0)
{
uint64_t v___x_1481_; uint64_t v___x_1482_; 
v___x_1481_ = lean_uint64_sub(v___y_1445_, v___x_1479_);
v___x_1482_ = lean_uint64_shift_left(v___y_1448_, v___x_1481_);
v___y_1245_ = v___y_1446_;
v___y_1246_ = v___y_1447_;
v___y_1247_ = v___y_1449_;
v___y_1248_ = v___x_1482_;
goto v___jp_1244_;
}
else
{
uint64_t v___x_1483_; uint8_t v___x_1484_; 
v___x_1483_ = lean_uint64_sub(v___x_1479_, v___y_1445_);
v___x_1484_ = lean_uint64_dec_eq(v___x_1483_, v___y_1446_);
if (v___x_1484_ == 0)
{
uint64_t v___x_1485_; uint8_t v___x_1486_; 
v___x_1485_ = 64ULL;
v___x_1486_ = lean_uint64_dec_lt(v___x_1483_, v___x_1485_);
if (v___x_1486_ == 0)
{
uint8_t v___x_1487_; 
v___x_1487_ = lean_uint64_dec_eq(v___x_1483_, v___x_1485_);
if (v___x_1487_ == 0)
{
v___y_1245_ = v___y_1446_;
v___y_1246_ = v___y_1447_;
v___y_1247_ = v___y_1449_;
v___y_1248_ = v___y_1446_;
goto v___jp_1244_;
}
else
{
uint64_t v___x_1488_; uint8_t v___x_1489_; 
v___x_1488_ = 9223372036854775808ULL;
v___x_1489_ = lean_uint64_dec_lt(v___x_1488_, v___y_1448_);
if (v___x_1489_ == 0)
{
v___y_1245_ = v___y_1446_;
v___y_1246_ = v___y_1447_;
v___y_1247_ = v___y_1449_;
v___y_1248_ = v___y_1446_;
goto v___jp_1244_;
}
else
{
uint64_t v___x_1490_; 
v___x_1490_ = 1ULL;
v___y_1245_ = v___y_1446_;
v___y_1246_ = v___y_1447_;
v___y_1247_ = v___y_1449_;
v___y_1248_ = v___x_1490_;
goto v___jp_1244_;
}
}
}
else
{
uint64_t v_quotient_1491_; uint64_t v___x_1492_; uint64_t v___x_1493_; uint64_t v___x_1494_; uint64_t v_remainder_1495_; uint64_t v___x_1496_; uint64_t v_half_1497_; uint8_t v___x_1498_; 
v_quotient_1491_ = lean_uint64_shift_right(v___y_1448_, v___x_1483_);
v___x_1492_ = 1ULL;
v___x_1493_ = lean_uint64_shift_left(v___x_1492_, v___x_1483_);
v___x_1494_ = lean_uint64_sub(v___x_1493_, v___x_1492_);
v_remainder_1495_ = lean_uint64_land(v___y_1448_, v___x_1494_);
v___x_1496_ = lean_uint64_sub(v___x_1483_, v___x_1492_);
v_half_1497_ = lean_uint64_shift_left(v___x_1492_, v___x_1496_);
v___x_1498_ = lean_uint64_dec_lt(v_remainder_1495_, v_half_1497_);
if (v___x_1498_ == 0)
{
uint8_t v___x_1499_; 
v___x_1499_ = lean_uint64_dec_lt(v_half_1497_, v_remainder_1495_);
if (v___x_1499_ == 0)
{
uint64_t v___x_1500_; uint8_t v___x_1501_; 
v___x_1500_ = lean_uint64_land(v_quotient_1491_, v___x_1492_);
v___x_1501_ = lean_uint64_dec_eq(v___x_1500_, v___y_1446_);
if (v___x_1501_ == 0)
{
uint64_t v___x_1502_; 
v___x_1502_ = lean_uint64_add(v_quotient_1491_, v___x_1492_);
v___y_1245_ = v___y_1446_;
v___y_1246_ = v___y_1447_;
v___y_1247_ = v___y_1449_;
v___y_1248_ = v___x_1502_;
goto v___jp_1244_;
}
else
{
v___y_1245_ = v___y_1446_;
v___y_1246_ = v___y_1447_;
v___y_1247_ = v___y_1449_;
v___y_1248_ = v_quotient_1491_;
goto v___jp_1244_;
}
}
else
{
uint64_t v___x_1503_; 
v___x_1503_ = lean_uint64_add(v_quotient_1491_, v___x_1492_);
v___y_1245_ = v___y_1446_;
v___y_1246_ = v___y_1447_;
v___y_1247_ = v___y_1449_;
v___y_1248_ = v___x_1503_;
goto v___jp_1244_;
}
}
else
{
v___y_1245_ = v___y_1446_;
v___y_1246_ = v___y_1447_;
v___y_1247_ = v___y_1449_;
v___y_1248_ = v_quotient_1491_;
goto v___jp_1244_;
}
}
}
else
{
v___y_1245_ = v___y_1446_;
v___y_1246_ = v___y_1447_;
v___y_1247_ = v___y_1449_;
v___y_1248_ = v___y_1448_;
goto v___jp_1244_;
}
}
}
}
v___jp_1504_:
{
uint64_t v___x_1512_; uint64_t v___x_1513_; uint8_t v___x_1514_; 
v___x_1512_ = 1ULL;
v___x_1513_ = lean_uint64_shift_right(v___y_1507_, v___x_1512_);
v___x_1514_ = lean_uint64_dec_eq(v___x_1513_, v___y_1506_);
if (v___x_1514_ == 0)
{
uint64_t v___x_1515_; 
v___x_1515_ = lean_uint64_add(v___y_1511_, v___x_1512_);
v___y_1445_ = v___y_1505_;
v___y_1446_ = v___y_1506_;
v___y_1447_ = v___y_1508_;
v___y_1448_ = v___y_1510_;
v___y_1449_ = v___y_1509_;
v___y_1450_ = v___x_1515_;
goto v___jp_1444_;
}
else
{
v___y_1445_ = v___y_1505_;
v___y_1446_ = v___y_1506_;
v___y_1447_ = v___y_1508_;
v___y_1448_ = v___y_1510_;
v___y_1449_ = v___y_1509_;
v___y_1450_ = v___y_1511_;
goto v___jp_1444_;
}
}
v___jp_1516_:
{
uint64_t v___x_1526_; uint8_t v___x_1527_; 
v___x_1526_ = lean_uint64_shift_right(v___y_1521_, v___y_1522_);
v___x_1527_ = lean_uint64_dec_eq(v___x_1526_, v___y_1519_);
if (v___x_1527_ == 0)
{
uint64_t v___x_1528_; 
v___x_1528_ = lean_uint64_add(v___y_1517_, v___y_1522_);
v___y_1505_ = v___y_1518_;
v___y_1506_ = v___y_1519_;
v___y_1507_ = v___y_1525_;
v___y_1508_ = v___y_1520_;
v___y_1509_ = v___y_1524_;
v___y_1510_ = v___y_1523_;
v___y_1511_ = v___x_1528_;
goto v___jp_1504_;
}
else
{
v___y_1505_ = v___y_1518_;
v___y_1506_ = v___y_1519_;
v___y_1507_ = v___y_1525_;
v___y_1508_ = v___y_1520_;
v___y_1509_ = v___y_1524_;
v___y_1510_ = v___y_1523_;
v___y_1511_ = v___y_1517_;
goto v___jp_1504_;
}
}
v___jp_1529_:
{
uint64_t v___x_1537_; uint64_t v___x_1538_; uint8_t v___x_1539_; 
v___x_1537_ = 2ULL;
v___x_1538_ = lean_uint64_shift_right(v___y_1533_, v___x_1537_);
v___x_1539_ = lean_uint64_dec_eq(v___x_1538_, v___y_1531_);
if (v___x_1539_ == 0)
{
v___y_1517_ = v___y_1536_;
v___y_1518_ = v___y_1530_;
v___y_1519_ = v___y_1531_;
v___y_1520_ = v___y_1532_;
v___y_1521_ = v___y_1533_;
v___y_1522_ = v___x_1537_;
v___y_1523_ = v___y_1535_;
v___y_1524_ = v___y_1534_;
v___y_1525_ = v___x_1538_;
goto v___jp_1516_;
}
else
{
v___y_1517_ = v___y_1536_;
v___y_1518_ = v___y_1530_;
v___y_1519_ = v___y_1531_;
v___y_1520_ = v___y_1532_;
v___y_1521_ = v___y_1533_;
v___y_1522_ = v___x_1537_;
v___y_1523_ = v___y_1535_;
v___y_1524_ = v___y_1534_;
v___y_1525_ = v___y_1533_;
goto v___jp_1516_;
}
}
v___jp_1540_:
{
uint64_t v___x_1550_; uint8_t v___x_1551_; 
v___x_1550_ = lean_uint64_shift_right(v___y_1545_, v___y_1544_);
v___x_1551_ = lean_uint64_dec_eq(v___x_1550_, v___y_1542_);
if (v___x_1551_ == 0)
{
uint64_t v___x_1552_; 
v___x_1552_ = lean_uint64_add(v___y_1543_, v___y_1544_);
v___y_1530_ = v___y_1541_;
v___y_1531_ = v___y_1542_;
v___y_1532_ = v___y_1546_;
v___y_1533_ = v___y_1549_;
v___y_1534_ = v___y_1548_;
v___y_1535_ = v___y_1547_;
v___y_1536_ = v___x_1552_;
goto v___jp_1529_;
}
else
{
v___y_1530_ = v___y_1541_;
v___y_1531_ = v___y_1542_;
v___y_1532_ = v___y_1546_;
v___y_1533_ = v___y_1549_;
v___y_1534_ = v___y_1548_;
v___y_1535_ = v___y_1547_;
v___y_1536_ = v___y_1543_;
goto v___jp_1529_;
}
}
v___jp_1553_:
{
uint64_t v___x_1561_; uint64_t v___x_1562_; uint8_t v___x_1563_; 
v___x_1561_ = 4ULL;
v___x_1562_ = lean_uint64_shift_right(v___y_1557_, v___x_1561_);
v___x_1563_ = lean_uint64_dec_eq(v___x_1562_, v___y_1555_);
if (v___x_1563_ == 0)
{
v___y_1541_ = v___y_1554_;
v___y_1542_ = v___y_1555_;
v___y_1543_ = v___y_1560_;
v___y_1544_ = v___x_1561_;
v___y_1545_ = v___y_1557_;
v___y_1546_ = v___y_1556_;
v___y_1547_ = v___y_1559_;
v___y_1548_ = v___y_1558_;
v___y_1549_ = v___x_1562_;
goto v___jp_1540_;
}
else
{
v___y_1541_ = v___y_1554_;
v___y_1542_ = v___y_1555_;
v___y_1543_ = v___y_1560_;
v___y_1544_ = v___x_1561_;
v___y_1545_ = v___y_1557_;
v___y_1546_ = v___y_1556_;
v___y_1547_ = v___y_1559_;
v___y_1548_ = v___y_1558_;
v___y_1549_ = v___y_1557_;
goto v___jp_1540_;
}
}
v___jp_1564_:
{
uint64_t v___x_1574_; uint8_t v___x_1575_; 
v___x_1574_ = lean_uint64_shift_right(v___y_1570_, v___y_1567_);
v___x_1575_ = lean_uint64_dec_eq(v___x_1574_, v___y_1568_);
if (v___x_1575_ == 0)
{
uint64_t v___x_1576_; 
v___x_1576_ = lean_uint64_add(v___y_1566_, v___y_1567_);
v___y_1554_ = v___y_1565_;
v___y_1555_ = v___y_1568_;
v___y_1556_ = v___y_1569_;
v___y_1557_ = v___y_1573_;
v___y_1558_ = v___y_1572_;
v___y_1559_ = v___y_1571_;
v___y_1560_ = v___x_1576_;
goto v___jp_1553_;
}
else
{
v___y_1554_ = v___y_1565_;
v___y_1555_ = v___y_1568_;
v___y_1556_ = v___y_1569_;
v___y_1557_ = v___y_1573_;
v___y_1558_ = v___y_1572_;
v___y_1559_ = v___y_1571_;
v___y_1560_ = v___y_1566_;
goto v___jp_1553_;
}
}
v___jp_1577_:
{
uint64_t v___x_1585_; uint64_t v___x_1586_; uint8_t v___x_1587_; 
v___x_1585_ = 8ULL;
v___x_1586_ = lean_uint64_shift_right(v___y_1581_, v___x_1585_);
v___x_1587_ = lean_uint64_dec_eq(v___x_1586_, v___y_1579_);
if (v___x_1587_ == 0)
{
v___y_1565_ = v___y_1578_;
v___y_1566_ = v___y_1584_;
v___y_1567_ = v___x_1585_;
v___y_1568_ = v___y_1579_;
v___y_1569_ = v___y_1580_;
v___y_1570_ = v___y_1581_;
v___y_1571_ = v___y_1583_;
v___y_1572_ = v___y_1582_;
v___y_1573_ = v___x_1586_;
goto v___jp_1564_;
}
else
{
v___y_1565_ = v___y_1578_;
v___y_1566_ = v___y_1584_;
v___y_1567_ = v___x_1585_;
v___y_1568_ = v___y_1579_;
v___y_1569_ = v___y_1580_;
v___y_1570_ = v___y_1581_;
v___y_1571_ = v___y_1583_;
v___y_1572_ = v___y_1582_;
v___y_1573_ = v___y_1581_;
goto v___jp_1564_;
}
}
v___jp_1588_:
{
uint64_t v___x_1598_; uint8_t v___x_1599_; 
v___x_1598_ = lean_uint64_shift_right(v___y_1590_, v___y_1596_);
v___x_1599_ = lean_uint64_dec_eq(v___x_1598_, v___y_1592_);
if (v___x_1599_ == 0)
{
uint64_t v___x_1600_; 
v___x_1600_ = lean_uint64_add(v___y_1591_, v___y_1596_);
v___y_1578_ = v___y_1589_;
v___y_1579_ = v___y_1592_;
v___y_1580_ = v___y_1593_;
v___y_1581_ = v___y_1597_;
v___y_1582_ = v___y_1595_;
v___y_1583_ = v___y_1594_;
v___y_1584_ = v___x_1600_;
goto v___jp_1577_;
}
else
{
v___y_1578_ = v___y_1589_;
v___y_1579_ = v___y_1592_;
v___y_1580_ = v___y_1593_;
v___y_1581_ = v___y_1597_;
v___y_1582_ = v___y_1595_;
v___y_1583_ = v___y_1594_;
v___y_1584_ = v___y_1591_;
goto v___jp_1577_;
}
}
v___jp_1601_:
{
uint64_t v___x_1609_; uint64_t v___x_1610_; uint8_t v___x_1611_; 
v___x_1609_ = 16ULL;
v___x_1610_ = lean_uint64_shift_right(v___y_1603_, v___x_1609_);
v___x_1611_ = lean_uint64_dec_eq(v___x_1610_, v___y_1604_);
if (v___x_1611_ == 0)
{
v___y_1589_ = v___y_1602_;
v___y_1590_ = v___y_1603_;
v___y_1591_ = v___y_1608_;
v___y_1592_ = v___y_1604_;
v___y_1593_ = v___y_1605_;
v___y_1594_ = v___y_1607_;
v___y_1595_ = v___y_1606_;
v___y_1596_ = v___x_1609_;
v___y_1597_ = v___x_1610_;
goto v___jp_1588_;
}
else
{
v___y_1589_ = v___y_1602_;
v___y_1590_ = v___y_1603_;
v___y_1591_ = v___y_1608_;
v___y_1592_ = v___y_1604_;
v___y_1593_ = v___y_1605_;
v___y_1594_ = v___y_1607_;
v___y_1595_ = v___y_1606_;
v___y_1596_ = v___x_1609_;
v___y_1597_ = v___y_1603_;
goto v___jp_1588_;
}
}
v___jp_1612_:
{
uint64_t v___x_1620_; uint8_t v___x_1621_; 
v___x_1620_ = lean_uint64_shift_right(v___y_1617_, v___y_1615_);
v___x_1621_ = lean_uint64_dec_eq(v___x_1620_, v___y_1614_);
if (v___x_1621_ == 0)
{
v___y_1602_ = v___y_1613_;
v___y_1603_ = v___y_1619_;
v___y_1604_ = v___y_1614_;
v___y_1605_ = v___y_1616_;
v___y_1606_ = v___y_1618_;
v___y_1607_ = v___y_1617_;
v___y_1608_ = v___y_1615_;
goto v___jp_1601_;
}
else
{
v___y_1602_ = v___y_1613_;
v___y_1603_ = v___y_1619_;
v___y_1604_ = v___y_1614_;
v___y_1605_ = v___y_1616_;
v___y_1606_ = v___y_1618_;
v___y_1607_ = v___y_1617_;
v___y_1608_ = v___y_1614_;
goto v___jp_1601_;
}
}
v___jp_1622_:
{
uint64_t v___x_1627_; uint8_t v___x_1628_; 
v___x_1627_ = 0ULL;
v___x_1628_ = lean_uint64_dec_eq(v___y_1625_, v___x_1627_);
if (v___x_1628_ == 0)
{
uint64_t v___x_1629_; uint64_t v___x_1630_; uint8_t v___x_1631_; 
v___x_1629_ = 32ULL;
v___x_1630_ = lean_uint64_shift_right(v___y_1625_, v___x_1629_);
v___x_1631_ = lean_uint64_dec_eq(v___x_1630_, v___x_1627_);
if (v___x_1631_ == 0)
{
v___y_1613_ = v___y_1623_;
v___y_1614_ = v___x_1627_;
v___y_1615_ = v___x_1629_;
v___y_1616_ = v___y_1624_;
v___y_1617_ = v___y_1625_;
v___y_1618_ = v___y_1626_;
v___y_1619_ = v___x_1630_;
goto v___jp_1612_;
}
else
{
v___y_1613_ = v___y_1623_;
v___y_1614_ = v___x_1627_;
v___y_1615_ = v___x_1629_;
v___y_1616_ = v___y_1624_;
v___y_1617_ = v___y_1625_;
v___y_1618_ = v___y_1626_;
v___y_1619_ = v___y_1625_;
goto v___jp_1612_;
}
}
else
{
if (v___y_1624_ == 0)
{
uint32_t v___x_1632_; 
v___x_1632_ = 0;
return v___x_1632_;
}
else
{
uint32_t v___x_1633_; 
v___x_1633_ = 2147483648;
return v___x_1633_;
}
}
}
v___jp_1634_:
{
uint64_t v___x_1641_; uint64_t v___x_1642_; uint64_t v___x_1643_; uint8_t v___x_1644_; 
v___x_1641_ = lean_uint64_mul(v___y_1639_, v___y_1635_);
v___x_1642_ = lean_uint64_add(v___y_1636_, v___y_1640_);
v___x_1643_ = 281474976710656ULL;
v___x_1644_ = lean_uint64_dec_lt(v___x_1641_, v___x_1643_);
if (v___x_1644_ == 0)
{
v___y_1623_ = v___x_1642_;
v___y_1624_ = v___y_1637_;
v___y_1625_ = v___x_1641_;
v___y_1626_ = v___y_1638_;
goto v___jp_1622_;
}
else
{
uint64_t v___x_1645_; uint8_t v___x_1646_; 
v___x_1645_ = 123ULL;
v___x_1646_ = lean_uint64_dec_le(v___x_1642_, v___x_1645_);
if (v___x_1646_ == 0)
{
v___y_1623_ = v___x_1642_;
v___y_1624_ = v___y_1637_;
v___y_1625_ = v___x_1641_;
v___y_1626_ = v___y_1638_;
goto v___jp_1622_;
}
else
{
uint64_t v___x_1647_; uint8_t v___x_1648_; 
v___x_1647_ = 0ULL;
v___x_1648_ = lean_uint64_dec_eq(v___x_1641_, v___x_1647_);
if (v___x_1648_ == 0)
{
uint64_t v___x_1649_; uint64_t v___x_1650_; uint8_t v___x_1651_; 
v___x_1649_ = 149ULL;
v___x_1650_ = lean_uint64_sub(v___x_1649_, v___x_1642_);
v___x_1651_ = lean_uint64_dec_eq(v___x_1650_, v___x_1647_);
if (v___x_1651_ == 0)
{
uint64_t v___x_1652_; uint8_t v___x_1653_; 
v___x_1652_ = 64ULL;
v___x_1653_ = lean_uint64_dec_lt(v___x_1650_, v___x_1652_);
if (v___x_1653_ == 0)
{
uint8_t v___x_1654_; 
v___x_1654_ = lean_uint64_dec_eq(v___x_1650_, v___x_1652_);
if (v___x_1654_ == 0)
{
v___y_1266_ = v___x_1647_;
v___y_1267_ = v___y_1637_;
v___y_1268_ = v___y_1638_;
v___y_1269_ = v___x_1647_;
goto v___jp_1265_;
}
else
{
uint64_t v___x_1655_; uint8_t v___x_1656_; 
v___x_1655_ = 9223372036854775808ULL;
v___x_1656_ = lean_uint64_dec_lt(v___x_1655_, v___x_1641_);
if (v___x_1656_ == 0)
{
v___y_1266_ = v___x_1647_;
v___y_1267_ = v___y_1637_;
v___y_1268_ = v___y_1638_;
v___y_1269_ = v___x_1647_;
goto v___jp_1265_;
}
else
{
uint64_t v___x_1657_; 
v___x_1657_ = 1ULL;
v___y_1266_ = v___x_1647_;
v___y_1267_ = v___y_1637_;
v___y_1268_ = v___y_1638_;
v___y_1269_ = v___x_1657_;
goto v___jp_1265_;
}
}
}
else
{
uint64_t v_quotient_1658_; uint64_t v___x_1659_; uint64_t v___x_1660_; uint64_t v___x_1661_; uint64_t v_remainder_1662_; uint64_t v___x_1663_; uint64_t v_half_1664_; uint8_t v___x_1665_; 
v_quotient_1658_ = lean_uint64_shift_right(v___x_1641_, v___x_1650_);
v___x_1659_ = 1ULL;
v___x_1660_ = lean_uint64_shift_left(v___x_1659_, v___x_1650_);
v___x_1661_ = lean_uint64_sub(v___x_1660_, v___x_1659_);
v_remainder_1662_ = lean_uint64_land(v___x_1641_, v___x_1661_);
v___x_1663_ = lean_uint64_sub(v___x_1650_, v___x_1659_);
v_half_1664_ = lean_uint64_shift_left(v___x_1659_, v___x_1663_);
v___x_1665_ = lean_uint64_dec_lt(v_remainder_1662_, v_half_1664_);
if (v___x_1665_ == 0)
{
uint8_t v___x_1666_; 
v___x_1666_ = lean_uint64_dec_lt(v_half_1664_, v_remainder_1662_);
if (v___x_1666_ == 0)
{
uint64_t v___x_1667_; uint8_t v___x_1668_; 
v___x_1667_ = lean_uint64_land(v_quotient_1658_, v___x_1659_);
v___x_1668_ = lean_uint64_dec_eq(v___x_1667_, v___x_1647_);
if (v___x_1668_ == 0)
{
uint64_t v___x_1669_; 
v___x_1669_ = lean_uint64_add(v_quotient_1658_, v___x_1659_);
v___y_1266_ = v___x_1647_;
v___y_1267_ = v___y_1637_;
v___y_1268_ = v___y_1638_;
v___y_1269_ = v___x_1669_;
goto v___jp_1265_;
}
else
{
v___y_1266_ = v___x_1647_;
v___y_1267_ = v___y_1637_;
v___y_1268_ = v___y_1638_;
v___y_1269_ = v_quotient_1658_;
goto v___jp_1265_;
}
}
else
{
uint64_t v___x_1670_; 
v___x_1670_ = lean_uint64_add(v_quotient_1658_, v___x_1659_);
v___y_1266_ = v___x_1647_;
v___y_1267_ = v___y_1637_;
v___y_1268_ = v___y_1638_;
v___y_1269_ = v___x_1670_;
goto v___jp_1265_;
}
}
else
{
v___y_1266_ = v___x_1647_;
v___y_1267_ = v___y_1637_;
v___y_1268_ = v___y_1638_;
v___y_1269_ = v_quotient_1658_;
goto v___jp_1265_;
}
}
}
else
{
v___y_1266_ = v___x_1647_;
v___y_1267_ = v___y_1637_;
v___y_1268_ = v___y_1638_;
v___y_1269_ = v___x_1641_;
goto v___jp_1265_;
}
}
else
{
if (v___y_1637_ == 0)
{
uint32_t v___x_1671_; 
v___x_1671_ = 0;
return v___x_1671_;
}
else
{
uint32_t v___x_1672_; 
v___x_1672_ = 2147483648;
return v___x_1672_;
}
}
}
}
}
v___jp_1676_:
{
uint64_t v___x_1682_; uint64_t v___x_1683_; uint8_t v___x_1684_; 
v___x_1682_ = lean_uint32_to_uint64(v_ey_1675_);
v___x_1683_ = 0ULL;
v___x_1684_ = lean_uint64_dec_eq(v___x_1682_, v___x_1683_);
if (v___x_1684_ == 0)
{
uint64_t v___x_1685_; uint64_t v___x_1686_; 
v___x_1685_ = 1ULL;
v___x_1686_ = lean_uint64_sub(v___x_1682_, v___x_1685_);
v___y_1635_ = v___y_1677_;
v___y_1636_ = v___y_1681_;
v___y_1637_ = v___y_1678_;
v___y_1638_ = v___y_1680_;
v___y_1639_ = v___y_1679_;
v___y_1640_ = v___x_1686_;
goto v___jp_1634_;
}
else
{
v___y_1635_ = v___y_1677_;
v___y_1636_ = v___y_1681_;
v___y_1637_ = v___y_1678_;
v___y_1638_ = v___y_1680_;
v___y_1639_ = v___y_1679_;
v___y_1640_ = v___x_1683_;
goto v___jp_1634_;
}
}
v___jp_1687_:
{
uint64_t v___x_1692_; uint64_t v___x_1693_; uint8_t v___x_1694_; 
v___x_1692_ = lean_uint32_to_uint64(v_ex_1673_);
v___x_1693_ = 0ULL;
v___x_1694_ = lean_uint64_dec_eq(v___x_1692_, v___x_1693_);
if (v___x_1694_ == 0)
{
uint64_t v___x_1695_; uint64_t v___x_1696_; 
v___x_1695_ = 1ULL;
v___x_1696_ = lean_uint64_sub(v___x_1692_, v___x_1695_);
v___y_1677_ = v___y_1691_;
v___y_1678_ = v___y_1688_;
v___y_1679_ = v___y_1690_;
v___y_1680_ = v___y_1689_;
v___y_1681_ = v___x_1696_;
goto v___jp_1676_;
}
else
{
v___y_1677_ = v___y_1691_;
v___y_1678_ = v___y_1688_;
v___y_1679_ = v___y_1690_;
v___y_1680_ = v___y_1689_;
v___y_1681_ = v___x_1693_;
goto v___jp_1676_;
}
}
v___jp_1697_:
{
uint32_t v___x_1702_; uint8_t v___x_1703_; 
v___x_1702_ = 0;
v___x_1703_ = lean_uint32_dec_eq(v_ey_1675_, v___x_1702_);
if (v___x_1703_ == 0)
{
uint64_t v___x_1704_; uint64_t v___x_1705_; uint64_t v___x_1706_; 
v___x_1704_ = lean_uint32_to_uint64(v___y_1698_);
v___x_1705_ = 8388608ULL;
v___x_1706_ = lean_uint64_lor(v___x_1704_, v___x_1705_);
v___y_1688_ = v___y_1699_;
v___y_1689_ = v___y_1700_;
v___y_1690_ = v___y_1701_;
v___y_1691_ = v___x_1706_;
goto v___jp_1687_;
}
else
{
uint64_t v___x_1707_; 
v___x_1707_ = lean_uint32_to_uint64(v___y_1698_);
v___y_1688_ = v___y_1699_;
v___y_1689_ = v___y_1700_;
v___y_1690_ = v___y_1701_;
v___y_1691_ = v___x_1707_;
goto v___jp_1687_;
}
}
v___jp_1708_:
{
uint32_t v___x_1710_; uint32_t v_xFraction_1711_; uint32_t v_yFraction_1712_; uint32_t v___x_1713_; uint8_t v___x_1714_; 
v___x_1710_ = 8388607;
v_xFraction_1711_ = lean_uint32_land(v___y_1228_, v___x_1710_);
v_yFraction_1712_ = lean_uint32_land(v___y_1229_, v___x_1710_);
v___x_1713_ = 0;
v___x_1714_ = lean_uint32_dec_eq(v_ex_1673_, v___x_1713_);
if (v___x_1714_ == 0)
{
uint64_t v___x_1715_; uint64_t v___x_1716_; uint64_t v___x_1717_; 
v___x_1715_ = lean_uint32_to_uint64(v_xFraction_1711_);
v___x_1716_ = 8388608ULL;
v___x_1717_ = lean_uint64_lor(v___x_1715_, v___x_1716_);
v___y_1698_ = v_yFraction_1712_;
v___y_1699_ = v___y_1709_;
v___y_1700_ = v___x_1710_;
v___y_1701_ = v___x_1717_;
goto v___jp_1697_;
}
else
{
uint64_t v___x_1718_; 
v___x_1718_ = lean_uint32_to_uint64(v_xFraction_1711_);
v___y_1698_ = v_yFraction_1712_;
v___y_1699_ = v___y_1709_;
v___y_1700_ = v___x_1710_;
v___y_1701_ = v___x_1718_;
goto v___jp_1697_;
}
}
v___jp_1722_:
{
if (v___y_1724_ == 0)
{
v___y_1709_ = v___x_1721_;
goto v___jp_1708_;
}
else
{
v___y_1709_ = v___y_1723_;
goto v___jp_1708_;
}
}
v___jp_1725_:
{
if (v___y_1726_ == 0)
{
if (v___y_1728_ == 0)
{
v___y_1723_ = v___y_1727_;
v___y_1724_ = v___x_1721_;
goto v___jp_1722_;
}
else
{
v___y_1709_ = v___x_1721_;
goto v___jp_1708_;
}
}
else
{
v___y_1723_ = v___y_1727_;
v___y_1724_ = v___y_1728_;
goto v___jp_1722_;
}
}
v___jp_1729_:
{
uint32_t v___x_1732_; uint32_t v___x_1733_; uint32_t v___x_1734_; uint8_t v___x_1735_; 
v___x_1732_ = 2147483648;
v___x_1733_ = lean_uint32_land(v___y_1229_, v___x_1732_);
v___x_1734_ = 0;
v___x_1735_ = lean_uint32_dec_eq(v___x_1733_, v___x_1734_);
if (v___x_1735_ == 0)
{
v___y_1726_ = v___y_1731_;
v___y_1727_ = v___y_1730_;
v___y_1728_ = v___x_1721_;
goto v___jp_1725_;
}
else
{
v___y_1726_ = v___y_1731_;
v___y_1727_ = v___y_1730_;
v___y_1728_ = v___y_1730_;
goto v___jp_1725_;
}
}
v___jp_1736_:
{
if (v___y_1737_ == 0)
{
uint32_t v___x_1738_; uint32_t v___x_1739_; uint32_t v___x_1740_; uint8_t v___x_1741_; 
v___x_1738_ = 2147483648;
v___x_1739_ = lean_uint32_land(v___y_1228_, v___x_1738_);
v___x_1740_ = 0;
v___x_1741_ = lean_uint32_dec_eq(v___x_1739_, v___x_1740_);
if (v___x_1741_ == 0)
{
v___y_1730_ = v___y_1737_;
v___y_1731_ = v___x_1721_;
goto v___jp_1729_;
}
else
{
v___y_1730_ = v___y_1737_;
v___y_1731_ = v___y_1737_;
goto v___jp_1729_;
}
}
else
{
lean_object* v___x_1742_; lean_object* v___x_1743_; lean_object* v___x_1744_; uint32_t v___x_1745_; 
v___x_1742_ = lean_uint32_to_nat(v___y_1228_);
v___x_1743_ = lean_uint32_to_nat(v___y_1229_);
v___x_1744_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1742_, v___x_1743_);
v___x_1745_ = lean_uint32_of_nat(v___x_1744_);
lean_dec(v___x_1744_);
return v___x_1745_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_runIndexed8___lam__1___boxed(lean_object* v___y_1760_, lean_object* v___y_1761_){
_start:
{
uint32_t v___y_2190__boxed_1762_; uint32_t v___y_2191__boxed_1763_; uint32_t v_res_1764_; lean_object* v_r_1765_; 
v___y_2190__boxed_1762_ = lean_unbox_uint32(v___y_1760_);
lean_dec(v___y_1760_);
v___y_2191__boxed_1763_ = lean_unbox_uint32(v___y_1761_);
lean_dec(v___y_1761_);
v_res_1764_ = lp_competition_runIndexed8___lam__1(v___y_2190__boxed_1762_, v___y_2191__boxed_1763_);
v_r_1765_ = lean_box_uint32(v_res_1764_);
return v_r_1765_;
}
}
LEAN_EXPORT lean_object* lp_competition_runIndexed8(){
_start:
{
lean_object* v___f_1769_; lean_object* v___f_1770_; lean_object* v___x_1771_; lean_object* v___x_1772_; lean_object* v___x_1773_; 
v___f_1769_ = ((lean_object*)(lp_competition_runControl___closed__0));
v___f_1770_ = ((lean_object*)(lp_competition_runIndexed8___closed__0));
v___x_1771_ = ((lean_object*)(lp_competition_runControl___closed__2));
v___x_1772_ = ((lean_object*)(lp_competition_runIndexed8___closed__1));
v___x_1773_ = lp_competition_Bench_Suite_run(v___f_1769_, v___f_1770_, v___x_1771_, v___x_1772_);
return v___x_1773_;
}
}
LEAN_EXPORT lean_object* lp_competition_runIndexed8___boxed(lean_object* v_a_1774_){
_start:
{
lean_object* v_res_1775_; 
v_res_1775_ = lp_competition_runIndexed8();
return v_res_1775_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_1790_; lean_object* v___x_1791_; lean_object* v___x_1792_; uint8_t v___x_1793_; 
v___x_1790_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_1791_ = lean_io_getenv(v___x_1790_);
v___x_1792_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_1793_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_1791_, v___x_1792_);
if (v___x_1793_ == 0)
{
lean_object* v___x_1794_; uint8_t v___x_1795_; 
v___x_1794_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_1795_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_1791_, v___x_1794_);
if (v___x_1795_ == 0)
{
lean_object* v___x_1796_; uint8_t v___x_1797_; 
v___x_1796_ = ((lean_object*)(lp_competition_main___closed__6));
v___x_1797_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_1791_, v___x_1796_);
lean_dec(v___x_1791_);
if (v___x_1797_ == 0)
{
lean_object* v___x_1798_; lean_object* v___x_1799_; 
v___x_1798_ = ((lean_object*)(lp_competition_main___closed__8));
v___x_1799_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_1799_, 0, v___x_1798_);
return v___x_1799_;
}
else
{
lean_object* v___x_1800_; 
v___x_1800_ = lp_competition_runIndexed8();
return v___x_1800_;
}
}
else
{
lean_object* v___x_1801_; 
lean_dec(v___x_1791_);
v___x_1801_ = lp_competition_runRaw8();
return v___x_1801_;
}
}
else
{
lean_object* v___x_1802_; 
lean_dec(v___x_1791_);
v___x_1802_ = lp_competition_runControl();
return v___x_1802_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_1803_){
_start:
{
lean_object* v_res_1804_; 
v_res_1804_ = _lean_main();
return v_res_1804_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_competition_BenchFull(uint8_t builtin);
lean_object* initialize_competition_BenchSuite(uint8_t builtin);
lean_object* initialize_competition_Submission(uint8_t builtin);
void lean_initialize();
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_competition_R22Indexed8CostMain(uint8_t builtin) {
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
  res = initialize_competition_R22Indexed8CostMain(1 /* builtin */);
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
