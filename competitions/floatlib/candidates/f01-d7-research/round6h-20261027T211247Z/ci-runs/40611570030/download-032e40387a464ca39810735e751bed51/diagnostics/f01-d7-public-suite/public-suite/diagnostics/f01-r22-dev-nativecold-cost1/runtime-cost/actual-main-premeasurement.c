// Lean compiler output
// Module: R22NativeColdCostMain
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
uint32_t lean_uint32_land(uint32_t, uint32_t);
uint32_t lean_uint32_sub(uint32_t, uint32_t);
uint32_t lean_uint32_lor(uint32_t, uint32_t);
uint8_t lean_uint32_dec_lt(uint32_t, uint32_t);
uint32_t lp_competition_Submission_R22NativeCold_retainedMul(uint32_t, uint32_t);
float lean_uint32_to_float32(uint32_t);
extern lean_object* lp_competition_R2W01b_scaleTable;
uint32_t lean_uint32_shift_right(uint32_t, uint32_t);
lean_object* lean_uint32_to_nat(uint32_t);
lean_object* lean_array_fget_borrowed(lean_object*, lean_object*);
float lean_float32_mul(float, float);
uint32_t lean_float32_to_bits(float);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(lean_object*, lean_object*);
uint32_t lean_uint32_of_nat(lean_object*);
uint8_t lean_uint32_dec_eq(uint32_t, uint32_t);
float lean_float32_add(float, float);
uint8_t lean_float32_beq(float, float);
float lean_float32_of_bits(uint32_t);
uint8_t lean_uint32_dec_le(uint32_t, uint32_t);
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
lean_object* lean_io_getenv(lean_object*);
uint8_t l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(lean_object*, lean_object*);
uint32_t lp_competition_Submission_R22NativeColdAdd_coldAdd(uint32_t, uint32_t);
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
LEAN_EXPORT uint32_t lp_competition_runTh0___lam__1(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_runTh0___lam__1___boxed(lean_object*, lean_object*);
static const lean_closure_object lp_competition_runTh0___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_runTh0___lam__1___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runTh0___closed__0 = (const lean_object*)&lp_competition_runTh0___closed__0_value;
LEAN_EXPORT lean_object* lp_competition_runTh0();
LEAN_EXPORT lean_object* lp_competition_runTh0___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_runNativeInline___lam__1(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_runNativeInline___lam__1___boxed(lean_object*, lean_object*);
static const lean_closure_object lp_competition_runNativeInline___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_runNativeInline___lam__1___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runNativeInline___closed__0 = (const lean_object*)&lp_competition_runNativeInline___closed__0_value;
LEAN_EXPORT lean_object* lp_competition_runNativeInline();
LEAN_EXPORT lean_object* lp_competition_runNativeInline___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_runNativeCold___lam__1(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_runNativeCold___lam__1___boxed(lean_object*, lean_object*);
static const lean_closure_object lp_competition_runNativeCold___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_runNativeCold___lam__1___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runNativeCold___closed__0 = (const lean_object*)&lp_competition_runNativeCold___closed__0_value;
LEAN_EXPORT lean_object* lp_competition_runNativeCold();
LEAN_EXPORT lean_object* lp_competition_runNativeCold___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_runNativeAdd___lam__0(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_runNativeAdd___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_runNativeAdd___lam__1(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_runNativeAdd___lam__1___boxed(lean_object*, lean_object*);
static const lean_closure_object lp_competition_runNativeAdd___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_runNativeAdd___lam__0___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runNativeAdd___closed__0 = (const lean_object*)&lp_competition_runNativeAdd___closed__0_value;
static const lean_closure_object lp_competition_runNativeAdd___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_runNativeAdd___lam__1___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runNativeAdd___closed__1 = (const lean_object*)&lp_competition_runNativeAdd___closed__1_value;
LEAN_EXPORT lean_object* lp_competition_runNativeAdd();
LEAN_EXPORT lean_object* lp_competition_runNativeAdd___boxed(lean_object*);
static const lean_string_object lp_competition_main___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 14, .m_capacity = 14, .m_length = 13, .m_data = "BENCH_VARIANT"};
static const lean_object* lp_competition_main___closed__0 = (const lean_object*)&lp_competition_main___closed__0_value;
static const lean_string_object lp_competition_main___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 8, .m_capacity = 8, .m_length = 7, .m_data = "control"};
static const lean_object* lp_competition_main___closed__1 = (const lean_object*)&lp_competition_main___closed__1_value;
static const lean_ctor_object lp_competition_main___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__1_value)}};
static const lean_object* lp_competition_main___closed__2 = (const lean_object*)&lp_competition_main___closed__2_value;
static const lean_string_object lp_competition_main___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 4, .m_capacity = 4, .m_length = 3, .m_data = "th0"};
static const lean_object* lp_competition_main___closed__3 = (const lean_object*)&lp_competition_main___closed__3_value;
static const lean_ctor_object lp_competition_main___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__3_value)}};
static const lean_object* lp_competition_main___closed__4 = (const lean_object*)&lp_competition_main___closed__4_value;
static const lean_string_object lp_competition_main___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 13, .m_capacity = 13, .m_length = 12, .m_data = "nativeinline"};
static const lean_object* lp_competition_main___closed__5 = (const lean_object*)&lp_competition_main___closed__5_value;
static const lean_ctor_object lp_competition_main___closed__6_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__5_value)}};
static const lean_object* lp_competition_main___closed__6 = (const lean_object*)&lp_competition_main___closed__6_value;
static const lean_string_object lp_competition_main___closed__7_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 11, .m_capacity = 11, .m_length = 10, .m_data = "nativecold"};
static const lean_object* lp_competition_main___closed__7 = (const lean_object*)&lp_competition_main___closed__7_value;
static const lean_ctor_object lp_competition_main___closed__8_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__7_value)}};
static const lean_object* lp_competition_main___closed__8 = (const lean_object*)&lp_competition_main___closed__8_value;
static const lean_string_object lp_competition_main___closed__9_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 10, .m_capacity = 10, .m_length = 9, .m_data = "nativeadd"};
static const lean_object* lp_competition_main___closed__9 = (const lean_object*)&lp_competition_main___closed__9_value;
static const lean_ctor_object lp_competition_main___closed__10_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__9_value)}};
static const lean_object* lp_competition_main___closed__10 = (const lean_object*)&lp_competition_main___closed__10_value;
static const lean_string_object lp_competition_main___closed__11_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 48, .m_capacity = 48, .m_length = 47, .m_data = "BENCH_VARIANT invalid for NativeCold diagnostic"};
static const lean_object* lp_competition_main___closed__11 = (const lean_object*)&lp_competition_main___closed__11_value;
static const lean_ctor_object lp_competition_main___closed__12_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_main___closed__11_value)}};
static const lean_object* lp_competition_main___closed__12 = (const lean_object*)&lp_competition_main___closed__12_value;
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
LEAN_EXPORT uint32_t lp_competition_runTh0___lam__1(uint32_t v___y_680_, uint32_t v___y_681_){
_start:
{
uint8_t v___y_683_; uint8_t v___y_699_; uint8_t v___y_713_; uint8_t v___y_730_; float v___y_737_; float v___y_738_; float v___y_752_; uint8_t v___y_753_; float v___y_768_; uint8_t v___y_778_; uint32_t v___x_792_; uint32_t v_a_793_; uint32_t v___x_794_; uint32_t v___x_795_; uint32_t v___x_796_; uint8_t v___x_797_; 
v___x_792_ = 2147483647;
v_a_793_ = lean_uint32_land(v___y_680_, v___x_792_);
v___x_794_ = 201326591;
v___x_795_ = 1;
v___x_796_ = lean_uint32_sub(v_a_793_, v___x_795_);
v___x_797_ = lean_uint32_dec_le(v___x_794_, v___x_796_);
if (v___x_797_ == 0)
{
v___y_778_ = v___x_797_;
goto v___jp_777_;
}
else
{
uint32_t v___x_798_; uint8_t v___x_799_; 
v___x_798_ = 2139095040;
v___x_799_ = lean_uint32_dec_lt(v_a_793_, v___x_798_);
v___y_778_ = v___x_799_;
goto v___jp_777_;
}
v___jp_682_:
{
if (v___y_683_ == 0)
{
uint32_t v___x_684_; 
v___x_684_ = lp_competition_Submission_FastMul_mul(v___y_680_, v___y_681_);
return v___x_684_;
}
else
{
uint32_t v___x_685_; uint32_t v___x_686_; 
v___x_685_ = 4194304;
v___x_686_ = lean_uint32_lor(v___y_681_, v___x_685_);
return v___x_686_;
}
}
v___jp_687_:
{
uint32_t v___x_688_; uint32_t v___x_689_; uint32_t v___x_690_; uint32_t v___x_691_; uint8_t v___x_692_; 
v___x_688_ = 23;
v___x_689_ = lean_uint32_shift_right(v___y_681_, v___x_688_);
v___x_690_ = 255;
v___x_691_ = lean_uint32_land(v___x_689_, v___x_690_);
v___x_692_ = lean_uint32_dec_eq(v___x_691_, v___x_690_);
if (v___x_692_ == 0)
{
v___y_683_ = v___x_692_;
goto v___jp_682_;
}
else
{
uint32_t v___x_693_; uint32_t v___x_694_; uint32_t v___x_695_; uint8_t v___x_696_; 
v___x_693_ = 8388607;
v___x_694_ = lean_uint32_land(v___y_681_, v___x_693_);
v___x_695_ = 0;
v___x_696_ = lean_uint32_dec_eq(v___x_694_, v___x_695_);
if (v___x_696_ == 0)
{
v___y_683_ = v___x_692_;
goto v___jp_682_;
}
else
{
uint32_t v___x_697_; 
v___x_697_ = lp_competition_Submission_FastMul_mul(v___y_680_, v___y_681_);
return v___x_697_;
}
}
}
v___jp_698_:
{
if (v___y_699_ == 0)
{
goto v___jp_687_;
}
else
{
uint32_t v___x_700_; uint32_t v___x_701_; 
v___x_700_ = 4194304;
v___x_701_ = lean_uint32_lor(v___y_680_, v___x_700_);
return v___x_701_;
}
}
v___jp_702_:
{
uint32_t v___x_703_; uint32_t v___x_704_; uint32_t v___x_705_; uint32_t v___x_706_; uint8_t v___x_707_; 
v___x_703_ = 23;
v___x_704_ = lean_uint32_shift_right(v___y_680_, v___x_703_);
v___x_705_ = 255;
v___x_706_ = lean_uint32_land(v___x_704_, v___x_705_);
v___x_707_ = lean_uint32_dec_eq(v___x_706_, v___x_705_);
if (v___x_707_ == 0)
{
v___y_699_ = v___x_707_;
goto v___jp_698_;
}
else
{
uint32_t v___x_708_; uint32_t v___x_709_; uint32_t v___x_710_; uint8_t v___x_711_; 
v___x_708_ = 8388607;
v___x_709_ = lean_uint32_land(v___y_680_, v___x_708_);
v___x_710_ = 0;
v___x_711_ = lean_uint32_dec_eq(v___x_709_, v___x_710_);
if (v___x_711_ == 0)
{
v___y_699_ = v___x_707_;
goto v___jp_698_;
}
else
{
goto v___jp_687_;
}
}
}
v___jp_712_:
{
if (v___y_713_ == 0)
{
goto v___jp_702_;
}
else
{
uint32_t v___x_714_; uint32_t v___x_715_; uint32_t v___x_716_; uint8_t v___x_717_; 
v___x_714_ = 4194304;
v___x_715_ = lean_uint32_land(v___y_681_, v___x_714_);
v___x_716_ = 0;
v___x_717_ = lean_uint32_dec_eq(v___x_715_, v___x_716_);
if (v___x_717_ == 0)
{
goto v___jp_702_;
}
else
{
uint32_t v___x_718_; 
v___x_718_ = lean_uint32_lor(v___y_681_, v___x_714_);
return v___x_718_;
}
}
}
v___jp_719_:
{
uint32_t v___x_720_; uint32_t v___x_721_; uint32_t v___x_722_; uint32_t v___x_723_; uint8_t v___x_724_; 
v___x_720_ = 23;
v___x_721_ = lean_uint32_shift_right(v___y_681_, v___x_720_);
v___x_722_ = 255;
v___x_723_ = lean_uint32_land(v___x_721_, v___x_722_);
v___x_724_ = lean_uint32_dec_eq(v___x_723_, v___x_722_);
if (v___x_724_ == 0)
{
v___y_713_ = v___x_724_;
goto v___jp_712_;
}
else
{
uint32_t v___x_725_; uint32_t v___x_726_; uint32_t v___x_727_; uint8_t v___x_728_; 
v___x_725_ = 8388607;
v___x_726_ = lean_uint32_land(v___y_681_, v___x_725_);
v___x_727_ = 0;
v___x_728_ = lean_uint32_dec_eq(v___x_726_, v___x_727_);
if (v___x_728_ == 0)
{
v___y_713_ = v___x_724_;
goto v___jp_712_;
}
else
{
goto v___jp_702_;
}
}
}
v___jp_729_:
{
if (v___y_730_ == 0)
{
goto v___jp_719_;
}
else
{
uint32_t v___x_731_; uint32_t v___x_732_; uint32_t v___x_733_; uint8_t v___x_734_; 
v___x_731_ = 4194304;
v___x_732_ = lean_uint32_land(v___y_680_, v___x_731_);
v___x_733_ = 0;
v___x_734_ = lean_uint32_dec_eq(v___x_732_, v___x_733_);
if (v___x_734_ == 0)
{
goto v___jp_719_;
}
else
{
uint32_t v___x_735_; 
v___x_735_ = lean_uint32_lor(v___y_680_, v___x_731_);
return v___x_735_;
}
}
}
v___jp_736_:
{
float v_result_739_; uint8_t v___x_740_; 
v_result_739_ = lean_float32_mul(v___y_737_, v___y_738_);
v___x_740_ = lean_float32_beq(v_result_739_, v_result_739_);
if (v___x_740_ == 0)
{
uint32_t v___x_741_; uint32_t v___x_742_; uint32_t v___x_743_; uint32_t v___x_744_; uint8_t v___x_745_; 
v___x_741_ = 23;
v___x_742_ = lean_uint32_shift_right(v___y_680_, v___x_741_);
v___x_743_ = 255;
v___x_744_ = lean_uint32_land(v___x_742_, v___x_743_);
v___x_745_ = lean_uint32_dec_eq(v___x_744_, v___x_743_);
if (v___x_745_ == 0)
{
v___y_730_ = v___x_745_;
goto v___jp_729_;
}
else
{
uint32_t v___x_746_; uint32_t v___x_747_; uint32_t v___x_748_; uint8_t v___x_749_; 
v___x_746_ = 8388607;
v___x_747_ = lean_uint32_land(v___y_680_, v___x_746_);
v___x_748_ = 0;
v___x_749_ = lean_uint32_dec_eq(v___x_747_, v___x_748_);
if (v___x_749_ == 0)
{
v___y_730_ = v___x_745_;
goto v___jp_729_;
}
else
{
goto v___jp_719_;
}
}
}
else
{
uint32_t v___x_750_; 
v___x_750_ = lean_float32_to_bits(v_result_739_);
return v___x_750_;
}
}
v___jp_751_:
{
if (v___y_753_ == 0)
{
float v___x_754_; 
v___x_754_ = lean_float32_of_bits(v___y_681_);
v___y_737_ = v___y_752_;
v___y_738_ = v___x_754_;
goto v___jp_736_;
}
else
{
uint32_t v___x_755_; uint32_t v___x_756_; uint32_t v___x_757_; uint32_t v___x_758_; float v___x_759_; lean_object* v___x_760_; uint32_t v___x_761_; uint32_t v___x_762_; lean_object* v___x_763_; lean_object* v___x_764_; float v___x_765_; float v___x_766_; 
v___x_755_ = 8388607;
v___x_756_ = lean_uint32_land(v___y_681_, v___x_755_);
v___x_757_ = 8388608;
v___x_758_ = lean_uint32_lor(v___x_756_, v___x_757_);
v___x_759_ = lean_uint32_to_float32(v___x_758_);
v___x_760_ = lp_competition_R2W01b_scaleTable;
v___x_761_ = 23;
v___x_762_ = lean_uint32_shift_right(v___y_681_, v___x_761_);
v___x_763_ = lean_uint32_to_nat(v___x_762_);
v___x_764_ = lean_array_fget_borrowed(v___x_760_, v___x_763_);
lean_dec(v___x_763_);
v___x_765_ = lean_unbox_float32(v___x_764_);
v___x_766_ = lean_float32_mul(v___x_759_, v___x_765_);
v___y_737_ = v___y_752_;
v___y_738_ = v___x_766_;
goto v___jp_736_;
}
}
v___jp_767_:
{
uint32_t v___x_769_; uint32_t v_a_770_; uint32_t v___x_771_; uint32_t v___x_772_; uint32_t v___x_773_; uint8_t v___x_774_; 
v___x_769_ = 2147483647;
v_a_770_ = lean_uint32_land(v___y_681_, v___x_769_);
v___x_771_ = 201326591;
v___x_772_ = 1;
v___x_773_ = lean_uint32_sub(v_a_770_, v___x_772_);
v___x_774_ = lean_uint32_dec_le(v___x_771_, v___x_773_);
if (v___x_774_ == 0)
{
v___y_752_ = v___y_768_;
v___y_753_ = v___x_774_;
goto v___jp_751_;
}
else
{
uint32_t v___x_775_; uint8_t v___x_776_; 
v___x_775_ = 2139095040;
v___x_776_ = lean_uint32_dec_lt(v_a_770_, v___x_775_);
v___y_752_ = v___y_768_;
v___y_753_ = v___x_776_;
goto v___jp_751_;
}
}
v___jp_777_:
{
if (v___y_778_ == 0)
{
float v___x_779_; 
v___x_779_ = lean_float32_of_bits(v___y_680_);
v___y_768_ = v___x_779_;
goto v___jp_767_;
}
else
{
uint32_t v___x_780_; uint32_t v___x_781_; uint32_t v___x_782_; uint32_t v___x_783_; float v___x_784_; lean_object* v___x_785_; uint32_t v___x_786_; uint32_t v___x_787_; lean_object* v___x_788_; lean_object* v___x_789_; float v___x_790_; float v___x_791_; 
v___x_780_ = 8388607;
v___x_781_ = lean_uint32_land(v___y_680_, v___x_780_);
v___x_782_ = 8388608;
v___x_783_ = lean_uint32_lor(v___x_781_, v___x_782_);
v___x_784_ = lean_uint32_to_float32(v___x_783_);
v___x_785_ = lp_competition_R2W01b_scaleTable;
v___x_786_ = 23;
v___x_787_ = lean_uint32_shift_right(v___y_680_, v___x_786_);
v___x_788_ = lean_uint32_to_nat(v___x_787_);
v___x_789_ = lean_array_fget_borrowed(v___x_785_, v___x_788_);
lean_dec(v___x_788_);
v___x_790_ = lean_unbox_float32(v___x_789_);
v___x_791_ = lean_float32_mul(v___x_784_, v___x_790_);
v___y_768_ = v___x_791_;
goto v___jp_767_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_runTh0___lam__1___boxed(lean_object* v___y_800_, lean_object* v___y_801_){
_start:
{
uint32_t v___y_896__boxed_802_; uint32_t v___y_897__boxed_803_; uint32_t v_res_804_; lean_object* v_r_805_; 
v___y_896__boxed_802_ = lean_unbox_uint32(v___y_800_);
lean_dec(v___y_800_);
v___y_897__boxed_803_ = lean_unbox_uint32(v___y_801_);
lean_dec(v___y_801_);
v_res_804_ = lp_competition_runTh0___lam__1(v___y_896__boxed_802_, v___y_897__boxed_803_);
v_r_805_ = lean_box_uint32(v_res_804_);
return v_r_805_;
}
}
LEAN_EXPORT lean_object* lp_competition_runTh0(){
_start:
{
lean_object* v___f_808_; lean_object* v___f_809_; lean_object* v___x_810_; lean_object* v___x_811_; lean_object* v___x_812_; 
v___f_808_ = ((lean_object*)(lp_competition_runControl___closed__0));
v___f_809_ = ((lean_object*)(lp_competition_runTh0___closed__0));
v___x_810_ = ((lean_object*)(lp_competition_runControl___closed__2));
v___x_811_ = ((lean_object*)(lp_competition_runControl___closed__3));
v___x_812_ = lp_competition_Bench_Suite_run(v___f_808_, v___f_809_, v___x_810_, v___x_811_);
return v___x_812_;
}
}
LEAN_EXPORT lean_object* lp_competition_runTh0___boxed(lean_object* v_a_813_){
_start:
{
lean_object* v_res_814_; 
v_res_814_ = lp_competition_runTh0();
return v_res_814_;
}
}
LEAN_EXPORT uint32_t lp_competition_runNativeInline___lam__1(uint32_t v___y_815_, uint32_t v___y_816_){
_start:
{
uint32_t v___y_818_; uint32_t v___y_822_; uint32_t v___y_826_; uint32_t v___y_827_; uint32_t v___y_828_; uint8_t v___y_832_; uint32_t v___y_833_; uint64_t v___y_834_; uint64_t v___y_835_; uint32_t v___y_847_; uint32_t v___y_848_; uint32_t v___y_849_; uint64_t v___y_853_; uint8_t v___y_854_; uint32_t v___y_855_; uint64_t v___y_856_; uint8_t v___y_868_; uint8_t v___y_884_; uint8_t v___y_898_; uint8_t v___y_915_; float v___y_922_; float v___y_923_; float v___y_937_; uint8_t v___y_938_; float v___y_953_; uint32_t v___x_962_; uint32_t v___x_963_; uint32_t v___x_964_; uint32_t v___x_965_; uint32_t v___x_966_; uint32_t v___x_967_; uint32_t v___x_968_; uint32_t v___x_969_; uint8_t v___x_970_; 
v___x_962_ = 2147483647;
v___x_963_ = lean_uint32_land(v___y_815_, v___x_962_);
v___x_964_ = 536870912;
v___x_965_ = lean_uint32_sub(v___x_963_, v___x_964_);
v___x_966_ = lean_uint32_land(v___y_816_, v___x_962_);
v___x_967_ = lean_uint32_sub(v___x_966_, v___x_964_);
v___x_968_ = lean_uint32_lor(v___x_965_, v___x_967_);
v___x_969_ = 1073741824;
v___x_970_ = lean_uint32_dec_lt(v___x_968_, v___x_969_);
if (v___x_970_ == 0)
{
uint32_t v___x_971_; uint32_t v___x_972_; uint8_t v___y_974_; uint32_t v___x_986_; uint32_t v___y_988_; uint32_t v___y_989_; uint32_t v___y_990_; uint32_t v___y_991_; uint32_t v___y_998_; uint8_t v___y_999_; uint32_t v___y_1000_; uint32_t v___y_1001_; uint8_t v___y_1005_; uint64_t v___y_1006_; uint64_t v___y_1007_; uint32_t v___y_1008_; uint64_t v___y_1009_; uint8_t v___y_1019_; uint8_t v___y_1020_; uint64_t v___y_1021_; uint32_t v___y_1022_; uint64_t v___y_1023_; uint64_t v___y_1024_; uint8_t v___y_1031_; uint64_t v___y_1032_; uint64_t v___y_1033_; uint32_t v___y_1034_; uint64_t v___y_1035_; uint64_t v___y_1041_; uint8_t v___y_1042_; uint64_t v___y_1043_; uint32_t v___y_1044_; uint64_t v___y_1045_; uint64_t v___y_1046_; uint64_t v___y_1101_; uint8_t v___y_1102_; uint64_t v___y_1103_; uint64_t v___y_1104_; uint32_t v___y_1105_; uint64_t v___y_1106_; uint64_t v___y_1107_; uint64_t v___y_1113_; uint64_t v___y_1114_; uint64_t v___y_1115_; uint8_t v___y_1116_; uint64_t v___y_1117_; uint64_t v___y_1118_; uint64_t v___y_1119_; uint32_t v___y_1120_; uint64_t v___y_1121_; uint64_t v___y_1126_; uint8_t v___y_1127_; uint64_t v___y_1128_; uint64_t v___y_1129_; uint32_t v___y_1130_; uint64_t v___y_1131_; uint64_t v___y_1132_; uint64_t v___y_1137_; uint64_t v___y_1138_; uint64_t v___y_1139_; uint8_t v___y_1140_; uint64_t v___y_1141_; uint64_t v___y_1142_; uint32_t v___y_1143_; uint64_t v___y_1144_; uint64_t v___y_1145_; uint64_t v___y_1150_; uint64_t v___y_1151_; uint8_t v___y_1152_; uint64_t v___y_1153_; uint32_t v___y_1154_; uint64_t v___y_1155_; uint64_t v___y_1156_; uint64_t v___y_1161_; uint8_t v___y_1162_; uint64_t v___y_1163_; uint64_t v___y_1164_; uint64_t v___y_1165_; uint64_t v___y_1166_; uint32_t v___y_1167_; uint64_t v___y_1168_; uint64_t v___y_1169_; uint64_t v___y_1174_; uint8_t v___y_1175_; uint64_t v___y_1176_; uint32_t v___y_1177_; uint64_t v___y_1178_; uint64_t v___y_1179_; uint64_t v___y_1180_; uint64_t v___y_1185_; uint8_t v___y_1186_; uint64_t v___y_1187_; uint64_t v___y_1188_; uint64_t v___y_1189_; uint32_t v___y_1190_; uint64_t v___y_1191_; uint64_t v___y_1192_; uint64_t v___y_1193_; uint64_t v___y_1198_; uint8_t v___y_1199_; uint64_t v___y_1200_; uint32_t v___y_1201_; uint64_t v___y_1202_; uint64_t v___y_1203_; uint64_t v___y_1204_; uint64_t v___y_1209_; uint8_t v___y_1210_; uint64_t v___y_1211_; uint64_t v___y_1212_; uint64_t v___y_1213_; uint32_t v___y_1214_; uint64_t v___y_1215_; uint64_t v___y_1219_; uint8_t v___y_1220_; uint64_t v___y_1221_; uint32_t v___y_1222_; uint8_t v___y_1231_; uint64_t v___y_1232_; uint64_t v___y_1233_; uint64_t v___y_1234_; uint32_t v___y_1235_; uint64_t v___y_1236_; uint32_t v_ex_1269_; uint32_t v___x_1270_; uint32_t v_ey_1271_; uint8_t v___y_1273_; uint64_t v___y_1274_; uint64_t v___y_1275_; uint32_t v___y_1276_; uint64_t v___y_1277_; uint8_t v___y_1284_; uint64_t v___y_1285_; uint32_t v___y_1286_; uint64_t v___y_1287_; uint8_t v___y_1294_; uint32_t v___y_1295_; uint32_t v___y_1296_; uint64_t v___y_1297_; uint8_t v___y_1305_; uint32_t v___x_1315_; uint32_t v___x_1316_; uint8_t v___x_1317_; uint8_t v___y_1319_; uint8_t v___y_1320_; uint8_t v___y_1321_; uint8_t v___y_1323_; uint8_t v___y_1324_; uint8_t v___y_1330_; 
v___x_971_ = 23;
v___x_972_ = lean_uint32_shift_right(v___y_815_, v___x_971_);
v___x_986_ = 255;
v_ex_1269_ = lean_uint32_land(v___x_972_, v___x_986_);
v___x_1270_ = lean_uint32_shift_right(v___y_816_, v___x_971_);
v_ey_1271_ = lean_uint32_land(v___x_1270_, v___x_986_);
v___x_1315_ = lean_uint32_add(v_ex_1269_, v_ey_1271_);
v___x_1316_ = 128;
v___x_1317_ = lean_uint32_dec_lt(v___x_1315_, v___x_1316_);
if (v___x_1317_ == 0)
{
uint32_t v___x_1339_; uint32_t v___x_1340_; uint32_t v___x_1341_; uint8_t v___x_1342_; 
v___x_1339_ = 201326591;
v___x_1340_ = 1;
v___x_1341_ = lean_uint32_sub(v___x_963_, v___x_1340_);
v___x_1342_ = lean_uint32_dec_le(v___x_1339_, v___x_1341_);
if (v___x_1342_ == 0)
{
v___y_974_ = v___x_1342_;
goto v___jp_973_;
}
else
{
uint32_t v___x_1343_; uint8_t v___x_1344_; 
v___x_1343_ = 2139095040;
v___x_1344_ = lean_uint32_dec_lt(v___x_963_, v___x_1343_);
v___y_974_ = v___x_1344_;
goto v___jp_973_;
}
}
else
{
uint32_t v___x_1345_; uint32_t v___x_1346_; uint32_t v___x_1347_; uint8_t v___x_1348_; 
v___x_1345_ = 4278190080;
v___x_1346_ = 1;
v___x_1347_ = lean_uint32_shift_left(v___y_815_, v___x_1346_);
v___x_1348_ = lean_uint32_dec_le(v___x_1345_, v___x_1347_);
if (v___x_1348_ == 0)
{
uint32_t v___x_1349_; uint8_t v___x_1350_; 
v___x_1349_ = lean_uint32_shift_left(v___y_816_, v___x_1346_);
v___x_1350_ = lean_uint32_dec_le(v___x_1345_, v___x_1349_);
v___y_1330_ = v___x_1350_;
goto v___jp_1329_;
}
else
{
v___y_1330_ = v___x_1348_;
goto v___jp_1329_;
}
}
v___jp_973_:
{
if (v___y_974_ == 0)
{
float v___x_975_; 
v___x_975_ = lean_float32_of_bits(v___y_815_);
v___y_953_ = v___x_975_;
goto v___jp_952_;
}
else
{
uint32_t v___x_976_; uint32_t v___x_977_; uint32_t v___x_978_; uint32_t v___x_979_; float v___x_980_; lean_object* v___x_981_; lean_object* v___x_982_; lean_object* v___x_983_; float v___x_984_; float v___x_985_; 
v___x_976_ = 8388607;
v___x_977_ = lean_uint32_land(v___y_815_, v___x_976_);
v___x_978_ = 8388608;
v___x_979_ = lean_uint32_lor(v___x_977_, v___x_978_);
v___x_980_ = lean_uint32_to_float32(v___x_979_);
v___x_981_ = lp_competition_R2W01b_scaleTable;
v___x_982_ = lean_uint32_to_nat(v___x_972_);
v___x_983_ = lean_array_fget_borrowed(v___x_981_, v___x_982_);
lean_dec(v___x_982_);
v___x_984_ = lean_unbox_float32(v___x_983_);
v___x_985_ = lean_float32_mul(v___x_980_, v___x_984_);
v___y_953_ = v___x_985_;
goto v___jp_952_;
}
}
v___jp_987_:
{
uint32_t v___x_992_; uint32_t v___x_993_; uint32_t v___x_994_; uint32_t v___x_995_; uint32_t v___x_996_; 
v___x_992_ = lean_uint32_land(v___y_988_, v___x_986_);
v___x_993_ = lean_uint32_shift_left(v___x_992_, v___x_971_);
v___x_994_ = lean_uint32_lor(v___y_991_, v___x_993_);
v___x_995_ = lean_uint32_land(v___y_989_, v___y_990_);
v___x_996_ = lean_uint32_lor(v___x_994_, v___x_995_);
return v___x_996_;
}
v___jp_997_:
{
if (v___y_999_ == 0)
{
uint32_t v___x_1002_; 
v___x_1002_ = 0;
v___y_988_ = v___y_998_;
v___y_989_ = v___y_1001_;
v___y_990_ = v___y_1000_;
v___y_991_ = v___x_1002_;
goto v___jp_987_;
}
else
{
uint32_t v___x_1003_; 
v___x_1003_ = 2147483648;
v___y_988_ = v___y_998_;
v___y_989_ = v___y_1001_;
v___y_990_ = v___y_1000_;
v___y_991_ = v___x_1003_;
goto v___jp_987_;
}
}
v___jp_1004_:
{
uint64_t v___x_1010_; uint64_t v_encodedExponent_1011_; uint32_t v___x_1012_; uint64_t v___x_1013_; uint8_t v___x_1014_; 
v___x_1010_ = 171ULL;
v_encodedExponent_1011_ = lean_uint64_sub(v___y_1006_, v___x_1010_);
v___x_1012_ = lean_uint64_to_uint32(v_encodedExponent_1011_);
v___x_1013_ = 8388608ULL;
v___x_1014_ = lean_uint64_dec_lt(v___y_1009_, v___x_1013_);
if (v___x_1014_ == 0)
{
uint64_t v___x_1015_; uint32_t v___x_1016_; 
v___x_1015_ = lean_uint64_sub(v___y_1009_, v___x_1013_);
v___x_1016_ = lean_uint64_to_uint32(v___x_1015_);
v___y_998_ = v___x_1012_;
v___y_999_ = v___y_1005_;
v___y_1000_ = v___y_1008_;
v___y_1001_ = v___x_1016_;
goto v___jp_997_;
}
else
{
uint32_t v___x_1017_; 
v___x_1017_ = lean_uint64_to_uint32(v___y_1007_);
v___y_998_ = v___x_1012_;
v___y_999_ = v___y_1005_;
v___y_1000_ = v___y_1008_;
v___y_1001_ = v___x_1017_;
goto v___jp_997_;
}
}
v___jp_1018_:
{
uint64_t v___x_1025_; uint8_t v___x_1026_; 
v___x_1025_ = 425ULL;
v___x_1026_ = lean_uint64_dec_lt(v___x_1025_, v___y_1024_);
if (v___x_1026_ == 0)
{
if (v___y_1019_ == 0)
{
v___y_1005_ = v___y_1020_;
v___y_1006_ = v___y_1024_;
v___y_1007_ = v___y_1023_;
v___y_1008_ = v___y_1022_;
v___y_1009_ = v___y_1021_;
goto v___jp_1004_;
}
else
{
uint64_t v___x_1027_; 
v___x_1027_ = 8388608ULL;
v___y_1005_ = v___y_1020_;
v___y_1006_ = v___y_1024_;
v___y_1007_ = v___y_1023_;
v___y_1008_ = v___y_1022_;
v___y_1009_ = v___x_1027_;
goto v___jp_1004_;
}
}
else
{
if (v___y_1020_ == 0)
{
uint32_t v___x_1028_; 
v___x_1028_ = 2139095040;
return v___x_1028_;
}
else
{
uint32_t v___x_1029_; 
v___x_1029_ = 4286578688;
return v___x_1029_;
}
}
}
v___jp_1030_:
{
uint64_t v___x_1036_; uint8_t v_carry_1037_; 
v___x_1036_ = 16777216ULL;
v_carry_1037_ = lean_uint64_dec_eq(v___y_1035_, v___x_1036_);
if (v_carry_1037_ == 0)
{
v___y_1019_ = v_carry_1037_;
v___y_1020_ = v___y_1031_;
v___y_1021_ = v___y_1035_;
v___y_1022_ = v___y_1034_;
v___y_1023_ = v___y_1033_;
v___y_1024_ = v___y_1032_;
goto v___jp_1018_;
}
else
{
uint64_t v___x_1038_; uint64_t v___x_1039_; 
v___x_1038_ = 1ULL;
v___x_1039_ = lean_uint64_add(v___y_1032_, v___x_1038_);
v___y_1019_ = v_carry_1037_;
v___y_1020_ = v___y_1031_;
v___y_1021_ = v___y_1035_;
v___y_1022_ = v___y_1034_;
v___y_1023_ = v___y_1033_;
v___y_1024_ = v___x_1039_;
goto v___jp_1018_;
}
}
v___jp_1040_:
{
uint64_t v_position_1047_; uint64_t v___x_1048_; uint8_t v___x_1049_; 
v_position_1047_ = lean_uint64_add(v___y_1046_, v___y_1041_);
v___x_1048_ = 172ULL;
v___x_1049_ = lean_uint64_dec_lt(v_position_1047_, v___x_1048_);
if (v___x_1049_ == 0)
{
uint64_t v___x_1050_; uint8_t v___x_1051_; 
v___x_1050_ = 23ULL;
v___x_1051_ = lean_uint64_dec_lt(v___y_1046_, v___x_1050_);
if (v___x_1051_ == 0)
{
uint64_t v___x_1052_; uint8_t v___x_1053_; 
v___x_1052_ = lean_uint64_sub(v___y_1046_, v___x_1050_);
v___x_1053_ = lean_uint64_dec_eq(v___x_1052_, v___y_1045_);
if (v___x_1053_ == 0)
{
uint64_t v___x_1054_; uint8_t v___x_1055_; 
v___x_1054_ = 64ULL;
v___x_1055_ = lean_uint64_dec_lt(v___x_1052_, v___x_1054_);
if (v___x_1055_ == 0)
{
uint8_t v___x_1056_; 
v___x_1056_ = lean_uint64_dec_eq(v___x_1052_, v___x_1054_);
if (v___x_1056_ == 0)
{
v___y_1031_ = v___y_1042_;
v___y_1032_ = v_position_1047_;
v___y_1033_ = v___y_1045_;
v___y_1034_ = v___y_1044_;
v___y_1035_ = v___y_1045_;
goto v___jp_1030_;
}
else
{
uint64_t v___x_1057_; uint8_t v___x_1058_; 
v___x_1057_ = 9223372036854775808ULL;
v___x_1058_ = lean_uint64_dec_lt(v___x_1057_, v___y_1043_);
if (v___x_1058_ == 0)
{
v___y_1031_ = v___y_1042_;
v___y_1032_ = v_position_1047_;
v___y_1033_ = v___y_1045_;
v___y_1034_ = v___y_1044_;
v___y_1035_ = v___y_1045_;
goto v___jp_1030_;
}
else
{
uint64_t v___x_1059_; 
v___x_1059_ = 1ULL;
v___y_1031_ = v___y_1042_;
v___y_1032_ = v_position_1047_;
v___y_1033_ = v___y_1045_;
v___y_1034_ = v___y_1044_;
v___y_1035_ = v___x_1059_;
goto v___jp_1030_;
}
}
}
else
{
uint64_t v_quotient_1060_; uint64_t v___x_1061_; uint64_t v___x_1062_; uint64_t v___x_1063_; uint64_t v_remainder_1064_; uint64_t v___x_1065_; uint64_t v_half_1066_; uint8_t v___x_1067_; 
v_quotient_1060_ = lean_uint64_shift_right(v___y_1043_, v___x_1052_);
v___x_1061_ = 1ULL;
v___x_1062_ = lean_uint64_shift_left(v___x_1061_, v___x_1052_);
v___x_1063_ = lean_uint64_sub(v___x_1062_, v___x_1061_);
v_remainder_1064_ = lean_uint64_land(v___y_1043_, v___x_1063_);
v___x_1065_ = lean_uint64_sub(v___x_1052_, v___x_1061_);
v_half_1066_ = lean_uint64_shift_left(v___x_1061_, v___x_1065_);
v___x_1067_ = lean_uint64_dec_lt(v_remainder_1064_, v_half_1066_);
if (v___x_1067_ == 0)
{
uint8_t v___x_1068_; 
v___x_1068_ = lean_uint64_dec_lt(v_half_1066_, v_remainder_1064_);
if (v___x_1068_ == 0)
{
uint64_t v___x_1069_; uint8_t v___x_1070_; 
v___x_1069_ = lean_uint64_land(v_quotient_1060_, v___x_1061_);
v___x_1070_ = lean_uint64_dec_eq(v___x_1069_, v___y_1045_);
if (v___x_1070_ == 0)
{
uint64_t v___x_1071_; 
v___x_1071_ = lean_uint64_add(v_quotient_1060_, v___x_1061_);
v___y_1031_ = v___y_1042_;
v___y_1032_ = v_position_1047_;
v___y_1033_ = v___y_1045_;
v___y_1034_ = v___y_1044_;
v___y_1035_ = v___x_1071_;
goto v___jp_1030_;
}
else
{
v___y_1031_ = v___y_1042_;
v___y_1032_ = v_position_1047_;
v___y_1033_ = v___y_1045_;
v___y_1034_ = v___y_1044_;
v___y_1035_ = v_quotient_1060_;
goto v___jp_1030_;
}
}
else
{
uint64_t v___x_1072_; 
v___x_1072_ = lean_uint64_add(v_quotient_1060_, v___x_1061_);
v___y_1031_ = v___y_1042_;
v___y_1032_ = v_position_1047_;
v___y_1033_ = v___y_1045_;
v___y_1034_ = v___y_1044_;
v___y_1035_ = v___x_1072_;
goto v___jp_1030_;
}
}
else
{
v___y_1031_ = v___y_1042_;
v___y_1032_ = v_position_1047_;
v___y_1033_ = v___y_1045_;
v___y_1034_ = v___y_1044_;
v___y_1035_ = v_quotient_1060_;
goto v___jp_1030_;
}
}
}
else
{
v___y_1031_ = v___y_1042_;
v___y_1032_ = v_position_1047_;
v___y_1033_ = v___y_1045_;
v___y_1034_ = v___y_1044_;
v___y_1035_ = v___y_1043_;
goto v___jp_1030_;
}
}
else
{
uint64_t v___x_1073_; uint64_t v___x_1074_; 
v___x_1073_ = lean_uint64_sub(v___x_1050_, v___y_1046_);
v___x_1074_ = lean_uint64_shift_left(v___y_1043_, v___x_1073_);
v___y_1031_ = v___y_1042_;
v___y_1032_ = v_position_1047_;
v___y_1033_ = v___y_1045_;
v___y_1034_ = v___y_1044_;
v___y_1035_ = v___x_1074_;
goto v___jp_1030_;
}
}
else
{
uint64_t v___x_1075_; uint8_t v___x_1076_; 
v___x_1075_ = 149ULL;
v___x_1076_ = lean_uint64_dec_lt(v___y_1041_, v___x_1075_);
if (v___x_1076_ == 0)
{
uint64_t v___x_1077_; uint64_t v___x_1078_; 
v___x_1077_ = lean_uint64_sub(v___y_1041_, v___x_1075_);
v___x_1078_ = lean_uint64_shift_left(v___y_1043_, v___x_1077_);
v___y_832_ = v___y_1042_;
v___y_833_ = v___y_1044_;
v___y_834_ = v___y_1045_;
v___y_835_ = v___x_1078_;
goto v___jp_831_;
}
else
{
uint64_t v___x_1079_; uint8_t v___x_1080_; 
v___x_1079_ = lean_uint64_sub(v___x_1075_, v___y_1041_);
v___x_1080_ = lean_uint64_dec_eq(v___x_1079_, v___y_1045_);
if (v___x_1080_ == 0)
{
uint64_t v___x_1081_; uint8_t v___x_1082_; 
v___x_1081_ = 64ULL;
v___x_1082_ = lean_uint64_dec_lt(v___x_1079_, v___x_1081_);
if (v___x_1082_ == 0)
{
uint8_t v___x_1083_; 
v___x_1083_ = lean_uint64_dec_eq(v___x_1079_, v___x_1081_);
if (v___x_1083_ == 0)
{
v___y_832_ = v___y_1042_;
v___y_833_ = v___y_1044_;
v___y_834_ = v___y_1045_;
v___y_835_ = v___y_1045_;
goto v___jp_831_;
}
else
{
uint64_t v___x_1084_; uint8_t v___x_1085_; 
v___x_1084_ = 9223372036854775808ULL;
v___x_1085_ = lean_uint64_dec_lt(v___x_1084_, v___y_1043_);
if (v___x_1085_ == 0)
{
v___y_832_ = v___y_1042_;
v___y_833_ = v___y_1044_;
v___y_834_ = v___y_1045_;
v___y_835_ = v___y_1045_;
goto v___jp_831_;
}
else
{
uint64_t v___x_1086_; 
v___x_1086_ = 1ULL;
v___y_832_ = v___y_1042_;
v___y_833_ = v___y_1044_;
v___y_834_ = v___y_1045_;
v___y_835_ = v___x_1086_;
goto v___jp_831_;
}
}
}
else
{
uint64_t v_quotient_1087_; uint64_t v___x_1088_; uint64_t v___x_1089_; uint64_t v___x_1090_; uint64_t v_remainder_1091_; uint64_t v___x_1092_; uint64_t v_half_1093_; uint8_t v___x_1094_; 
v_quotient_1087_ = lean_uint64_shift_right(v___y_1043_, v___x_1079_);
v___x_1088_ = 1ULL;
v___x_1089_ = lean_uint64_shift_left(v___x_1088_, v___x_1079_);
v___x_1090_ = lean_uint64_sub(v___x_1089_, v___x_1088_);
v_remainder_1091_ = lean_uint64_land(v___y_1043_, v___x_1090_);
v___x_1092_ = lean_uint64_sub(v___x_1079_, v___x_1088_);
v_half_1093_ = lean_uint64_shift_left(v___x_1088_, v___x_1092_);
v___x_1094_ = lean_uint64_dec_lt(v_remainder_1091_, v_half_1093_);
if (v___x_1094_ == 0)
{
uint8_t v___x_1095_; 
v___x_1095_ = lean_uint64_dec_lt(v_half_1093_, v_remainder_1091_);
if (v___x_1095_ == 0)
{
uint64_t v___x_1096_; uint8_t v___x_1097_; 
v___x_1096_ = lean_uint64_land(v_quotient_1087_, v___x_1088_);
v___x_1097_ = lean_uint64_dec_eq(v___x_1096_, v___y_1045_);
if (v___x_1097_ == 0)
{
uint64_t v___x_1098_; 
v___x_1098_ = lean_uint64_add(v_quotient_1087_, v___x_1088_);
v___y_832_ = v___y_1042_;
v___y_833_ = v___y_1044_;
v___y_834_ = v___y_1045_;
v___y_835_ = v___x_1098_;
goto v___jp_831_;
}
else
{
v___y_832_ = v___y_1042_;
v___y_833_ = v___y_1044_;
v___y_834_ = v___y_1045_;
v___y_835_ = v_quotient_1087_;
goto v___jp_831_;
}
}
else
{
uint64_t v___x_1099_; 
v___x_1099_ = lean_uint64_add(v_quotient_1087_, v___x_1088_);
v___y_832_ = v___y_1042_;
v___y_833_ = v___y_1044_;
v___y_834_ = v___y_1045_;
v___y_835_ = v___x_1099_;
goto v___jp_831_;
}
}
else
{
v___y_832_ = v___y_1042_;
v___y_833_ = v___y_1044_;
v___y_834_ = v___y_1045_;
v___y_835_ = v_quotient_1087_;
goto v___jp_831_;
}
}
}
else
{
v___y_832_ = v___y_1042_;
v___y_833_ = v___y_1044_;
v___y_834_ = v___y_1045_;
v___y_835_ = v___y_1043_;
goto v___jp_831_;
}
}
}
}
v___jp_1100_:
{
uint64_t v___x_1108_; uint64_t v___x_1109_; uint8_t v___x_1110_; 
v___x_1108_ = 1ULL;
v___x_1109_ = lean_uint64_shift_right(v___y_1104_, v___x_1108_);
v___x_1110_ = lean_uint64_dec_eq(v___x_1109_, v___y_1106_);
if (v___x_1110_ == 0)
{
uint64_t v___x_1111_; 
v___x_1111_ = lean_uint64_add(v___y_1107_, v___x_1108_);
v___y_1041_ = v___y_1101_;
v___y_1042_ = v___y_1102_;
v___y_1043_ = v___y_1103_;
v___y_1044_ = v___y_1105_;
v___y_1045_ = v___y_1106_;
v___y_1046_ = v___x_1111_;
goto v___jp_1040_;
}
else
{
v___y_1041_ = v___y_1101_;
v___y_1042_ = v___y_1102_;
v___y_1043_ = v___y_1103_;
v___y_1044_ = v___y_1105_;
v___y_1045_ = v___y_1106_;
v___y_1046_ = v___y_1107_;
goto v___jp_1040_;
}
}
v___jp_1112_:
{
uint64_t v___x_1122_; uint8_t v___x_1123_; 
v___x_1122_ = lean_uint64_shift_right(v___y_1118_, v___y_1114_);
v___x_1123_ = lean_uint64_dec_eq(v___x_1122_, v___y_1119_);
if (v___x_1123_ == 0)
{
uint64_t v___x_1124_; 
v___x_1124_ = lean_uint64_add(v___y_1113_, v___y_1114_);
v___y_1101_ = v___y_1115_;
v___y_1102_ = v___y_1116_;
v___y_1103_ = v___y_1117_;
v___y_1104_ = v___y_1121_;
v___y_1105_ = v___y_1120_;
v___y_1106_ = v___y_1119_;
v___y_1107_ = v___x_1124_;
goto v___jp_1100_;
}
else
{
v___y_1101_ = v___y_1115_;
v___y_1102_ = v___y_1116_;
v___y_1103_ = v___y_1117_;
v___y_1104_ = v___y_1121_;
v___y_1105_ = v___y_1120_;
v___y_1106_ = v___y_1119_;
v___y_1107_ = v___y_1113_;
goto v___jp_1100_;
}
}
v___jp_1125_:
{
uint64_t v___x_1133_; uint64_t v___x_1134_; uint8_t v___x_1135_; 
v___x_1133_ = 2ULL;
v___x_1134_ = lean_uint64_shift_right(v___y_1129_, v___x_1133_);
v___x_1135_ = lean_uint64_dec_eq(v___x_1134_, v___y_1131_);
if (v___x_1135_ == 0)
{
v___y_1113_ = v___y_1132_;
v___y_1114_ = v___x_1133_;
v___y_1115_ = v___y_1126_;
v___y_1116_ = v___y_1127_;
v___y_1117_ = v___y_1128_;
v___y_1118_ = v___y_1129_;
v___y_1119_ = v___y_1131_;
v___y_1120_ = v___y_1130_;
v___y_1121_ = v___x_1134_;
goto v___jp_1112_;
}
else
{
v___y_1113_ = v___y_1132_;
v___y_1114_ = v___x_1133_;
v___y_1115_ = v___y_1126_;
v___y_1116_ = v___y_1127_;
v___y_1117_ = v___y_1128_;
v___y_1118_ = v___y_1129_;
v___y_1119_ = v___y_1131_;
v___y_1120_ = v___y_1130_;
v___y_1121_ = v___y_1129_;
goto v___jp_1112_;
}
}
v___jp_1136_:
{
uint64_t v___x_1146_; uint8_t v___x_1147_; 
v___x_1146_ = lean_uint64_shift_right(v___y_1137_, v___y_1144_);
v___x_1147_ = lean_uint64_dec_eq(v___x_1146_, v___y_1142_);
if (v___x_1147_ == 0)
{
uint64_t v___x_1148_; 
v___x_1148_ = lean_uint64_add(v___y_1138_, v___y_1144_);
v___y_1126_ = v___y_1139_;
v___y_1127_ = v___y_1140_;
v___y_1128_ = v___y_1141_;
v___y_1129_ = v___y_1145_;
v___y_1130_ = v___y_1143_;
v___y_1131_ = v___y_1142_;
v___y_1132_ = v___x_1148_;
goto v___jp_1125_;
}
else
{
v___y_1126_ = v___y_1139_;
v___y_1127_ = v___y_1140_;
v___y_1128_ = v___y_1141_;
v___y_1129_ = v___y_1145_;
v___y_1130_ = v___y_1143_;
v___y_1131_ = v___y_1142_;
v___y_1132_ = v___y_1138_;
goto v___jp_1125_;
}
}
v___jp_1149_:
{
uint64_t v___x_1157_; uint64_t v___x_1158_; uint8_t v___x_1159_; 
v___x_1157_ = 4ULL;
v___x_1158_ = lean_uint64_shift_right(v___y_1150_, v___x_1157_);
v___x_1159_ = lean_uint64_dec_eq(v___x_1158_, v___y_1155_);
if (v___x_1159_ == 0)
{
v___y_1137_ = v___y_1150_;
v___y_1138_ = v___y_1156_;
v___y_1139_ = v___y_1151_;
v___y_1140_ = v___y_1152_;
v___y_1141_ = v___y_1153_;
v___y_1142_ = v___y_1155_;
v___y_1143_ = v___y_1154_;
v___y_1144_ = v___x_1157_;
v___y_1145_ = v___x_1158_;
goto v___jp_1136_;
}
else
{
v___y_1137_ = v___y_1150_;
v___y_1138_ = v___y_1156_;
v___y_1139_ = v___y_1151_;
v___y_1140_ = v___y_1152_;
v___y_1141_ = v___y_1153_;
v___y_1142_ = v___y_1155_;
v___y_1143_ = v___y_1154_;
v___y_1144_ = v___x_1157_;
v___y_1145_ = v___y_1150_;
goto v___jp_1136_;
}
}
v___jp_1160_:
{
uint64_t v___x_1170_; uint8_t v___x_1171_; 
v___x_1170_ = lean_uint64_shift_right(v___y_1165_, v___y_1163_);
v___x_1171_ = lean_uint64_dec_eq(v___x_1170_, v___y_1166_);
if (v___x_1171_ == 0)
{
uint64_t v___x_1172_; 
v___x_1172_ = lean_uint64_add(v___y_1168_, v___y_1163_);
v___y_1150_ = v___y_1169_;
v___y_1151_ = v___y_1161_;
v___y_1152_ = v___y_1162_;
v___y_1153_ = v___y_1164_;
v___y_1154_ = v___y_1167_;
v___y_1155_ = v___y_1166_;
v___y_1156_ = v___x_1172_;
goto v___jp_1149_;
}
else
{
v___y_1150_ = v___y_1169_;
v___y_1151_ = v___y_1161_;
v___y_1152_ = v___y_1162_;
v___y_1153_ = v___y_1164_;
v___y_1154_ = v___y_1167_;
v___y_1155_ = v___y_1166_;
v___y_1156_ = v___y_1168_;
goto v___jp_1149_;
}
}
v___jp_1173_:
{
uint64_t v___x_1181_; uint64_t v___x_1182_; uint8_t v___x_1183_; 
v___x_1181_ = 8ULL;
v___x_1182_ = lean_uint64_shift_right(v___y_1179_, v___x_1181_);
v___x_1183_ = lean_uint64_dec_eq(v___x_1182_, v___y_1178_);
if (v___x_1183_ == 0)
{
v___y_1161_ = v___y_1174_;
v___y_1162_ = v___y_1175_;
v___y_1163_ = v___x_1181_;
v___y_1164_ = v___y_1176_;
v___y_1165_ = v___y_1179_;
v___y_1166_ = v___y_1178_;
v___y_1167_ = v___y_1177_;
v___y_1168_ = v___y_1180_;
v___y_1169_ = v___x_1182_;
goto v___jp_1160_;
}
else
{
v___y_1161_ = v___y_1174_;
v___y_1162_ = v___y_1175_;
v___y_1163_ = v___x_1181_;
v___y_1164_ = v___y_1176_;
v___y_1165_ = v___y_1179_;
v___y_1166_ = v___y_1178_;
v___y_1167_ = v___y_1177_;
v___y_1168_ = v___y_1180_;
v___y_1169_ = v___y_1179_;
goto v___jp_1160_;
}
}
v___jp_1184_:
{
uint64_t v___x_1194_; uint8_t v___x_1195_; 
v___x_1194_ = lean_uint64_shift_right(v___y_1191_, v___y_1187_);
v___x_1195_ = lean_uint64_dec_eq(v___x_1194_, v___y_1189_);
if (v___x_1195_ == 0)
{
uint64_t v___x_1196_; 
v___x_1196_ = lean_uint64_add(v___y_1192_, v___y_1187_);
v___y_1174_ = v___y_1185_;
v___y_1175_ = v___y_1186_;
v___y_1176_ = v___y_1188_;
v___y_1177_ = v___y_1190_;
v___y_1178_ = v___y_1189_;
v___y_1179_ = v___y_1193_;
v___y_1180_ = v___x_1196_;
goto v___jp_1173_;
}
else
{
v___y_1174_ = v___y_1185_;
v___y_1175_ = v___y_1186_;
v___y_1176_ = v___y_1188_;
v___y_1177_ = v___y_1190_;
v___y_1178_ = v___y_1189_;
v___y_1179_ = v___y_1193_;
v___y_1180_ = v___y_1192_;
goto v___jp_1173_;
}
}
v___jp_1197_:
{
uint64_t v___x_1205_; uint64_t v___x_1206_; uint8_t v___x_1207_; 
v___x_1205_ = 16ULL;
v___x_1206_ = lean_uint64_shift_right(v___y_1203_, v___x_1205_);
v___x_1207_ = lean_uint64_dec_eq(v___x_1206_, v___y_1202_);
if (v___x_1207_ == 0)
{
v___y_1185_ = v___y_1198_;
v___y_1186_ = v___y_1199_;
v___y_1187_ = v___x_1205_;
v___y_1188_ = v___y_1200_;
v___y_1189_ = v___y_1202_;
v___y_1190_ = v___y_1201_;
v___y_1191_ = v___y_1203_;
v___y_1192_ = v___y_1204_;
v___y_1193_ = v___x_1206_;
goto v___jp_1184_;
}
else
{
v___y_1185_ = v___y_1198_;
v___y_1186_ = v___y_1199_;
v___y_1187_ = v___x_1205_;
v___y_1188_ = v___y_1200_;
v___y_1189_ = v___y_1202_;
v___y_1190_ = v___y_1201_;
v___y_1191_ = v___y_1203_;
v___y_1192_ = v___y_1204_;
v___y_1193_ = v___y_1203_;
goto v___jp_1184_;
}
}
v___jp_1208_:
{
uint64_t v___x_1216_; uint8_t v___x_1217_; 
v___x_1216_ = lean_uint64_shift_right(v___y_1212_, v___y_1211_);
v___x_1217_ = lean_uint64_dec_eq(v___x_1216_, v___y_1213_);
if (v___x_1217_ == 0)
{
v___y_1198_ = v___y_1209_;
v___y_1199_ = v___y_1210_;
v___y_1200_ = v___y_1212_;
v___y_1201_ = v___y_1214_;
v___y_1202_ = v___y_1213_;
v___y_1203_ = v___y_1215_;
v___y_1204_ = v___y_1211_;
goto v___jp_1197_;
}
else
{
v___y_1198_ = v___y_1209_;
v___y_1199_ = v___y_1210_;
v___y_1200_ = v___y_1212_;
v___y_1201_ = v___y_1214_;
v___y_1202_ = v___y_1213_;
v___y_1203_ = v___y_1215_;
v___y_1204_ = v___y_1213_;
goto v___jp_1197_;
}
}
v___jp_1218_:
{
uint64_t v___x_1223_; uint8_t v___x_1224_; 
v___x_1223_ = 0ULL;
v___x_1224_ = lean_uint64_dec_eq(v___y_1221_, v___x_1223_);
if (v___x_1224_ == 0)
{
uint64_t v___x_1225_; uint64_t v___x_1226_; uint8_t v___x_1227_; 
v___x_1225_ = 32ULL;
v___x_1226_ = lean_uint64_shift_right(v___y_1221_, v___x_1225_);
v___x_1227_ = lean_uint64_dec_eq(v___x_1226_, v___x_1223_);
if (v___x_1227_ == 0)
{
v___y_1209_ = v___y_1219_;
v___y_1210_ = v___y_1220_;
v___y_1211_ = v___x_1225_;
v___y_1212_ = v___y_1221_;
v___y_1213_ = v___x_1223_;
v___y_1214_ = v___y_1222_;
v___y_1215_ = v___x_1226_;
goto v___jp_1208_;
}
else
{
v___y_1209_ = v___y_1219_;
v___y_1210_ = v___y_1220_;
v___y_1211_ = v___x_1225_;
v___y_1212_ = v___y_1221_;
v___y_1213_ = v___x_1223_;
v___y_1214_ = v___y_1222_;
v___y_1215_ = v___y_1221_;
goto v___jp_1208_;
}
}
else
{
if (v___y_1220_ == 0)
{
uint32_t v___x_1228_; 
v___x_1228_ = 0;
return v___x_1228_;
}
else
{
uint32_t v___x_1229_; 
v___x_1229_ = 2147483648;
return v___x_1229_;
}
}
}
v___jp_1230_:
{
uint64_t v___x_1237_; uint64_t v___x_1238_; uint64_t v___x_1239_; uint8_t v___x_1240_; 
v___x_1237_ = lean_uint64_mul(v___y_1234_, v___y_1233_);
v___x_1238_ = lean_uint64_add(v___y_1232_, v___y_1236_);
v___x_1239_ = 281474976710656ULL;
v___x_1240_ = lean_uint64_dec_lt(v___x_1237_, v___x_1239_);
if (v___x_1240_ == 0)
{
v___y_1219_ = v___x_1238_;
v___y_1220_ = v___y_1231_;
v___y_1221_ = v___x_1237_;
v___y_1222_ = v___y_1235_;
goto v___jp_1218_;
}
else
{
uint64_t v___x_1241_; uint8_t v___x_1242_; 
v___x_1241_ = 123ULL;
v___x_1242_ = lean_uint64_dec_le(v___x_1238_, v___x_1241_);
if (v___x_1242_ == 0)
{
v___y_1219_ = v___x_1238_;
v___y_1220_ = v___y_1231_;
v___y_1221_ = v___x_1237_;
v___y_1222_ = v___y_1235_;
goto v___jp_1218_;
}
else
{
uint64_t v___x_1243_; uint8_t v___x_1244_; 
v___x_1243_ = 0ULL;
v___x_1244_ = lean_uint64_dec_eq(v___x_1237_, v___x_1243_);
if (v___x_1244_ == 0)
{
uint64_t v___x_1245_; uint64_t v___x_1246_; uint8_t v___x_1247_; 
v___x_1245_ = 149ULL;
v___x_1246_ = lean_uint64_sub(v___x_1245_, v___x_1238_);
v___x_1247_ = lean_uint64_dec_eq(v___x_1246_, v___x_1243_);
if (v___x_1247_ == 0)
{
uint64_t v___x_1248_; uint8_t v___x_1249_; 
v___x_1248_ = 64ULL;
v___x_1249_ = lean_uint64_dec_lt(v___x_1246_, v___x_1248_);
if (v___x_1249_ == 0)
{
uint8_t v___x_1250_; 
v___x_1250_ = lean_uint64_dec_eq(v___x_1246_, v___x_1248_);
if (v___x_1250_ == 0)
{
v___y_853_ = v___x_1243_;
v___y_854_ = v___y_1231_;
v___y_855_ = v___y_1235_;
v___y_856_ = v___x_1243_;
goto v___jp_852_;
}
else
{
uint64_t v___x_1251_; uint8_t v___x_1252_; 
v___x_1251_ = 9223372036854775808ULL;
v___x_1252_ = lean_uint64_dec_lt(v___x_1251_, v___x_1237_);
if (v___x_1252_ == 0)
{
v___y_853_ = v___x_1243_;
v___y_854_ = v___y_1231_;
v___y_855_ = v___y_1235_;
v___y_856_ = v___x_1243_;
goto v___jp_852_;
}
else
{
uint64_t v___x_1253_; 
v___x_1253_ = 1ULL;
v___y_853_ = v___x_1243_;
v___y_854_ = v___y_1231_;
v___y_855_ = v___y_1235_;
v___y_856_ = v___x_1253_;
goto v___jp_852_;
}
}
}
else
{
uint64_t v_quotient_1254_; uint64_t v___x_1255_; uint64_t v___x_1256_; uint64_t v___x_1257_; uint64_t v_remainder_1258_; uint64_t v___x_1259_; uint64_t v_half_1260_; uint8_t v___x_1261_; 
v_quotient_1254_ = lean_uint64_shift_right(v___x_1237_, v___x_1246_);
v___x_1255_ = 1ULL;
v___x_1256_ = lean_uint64_shift_left(v___x_1255_, v___x_1246_);
v___x_1257_ = lean_uint64_sub(v___x_1256_, v___x_1255_);
v_remainder_1258_ = lean_uint64_land(v___x_1237_, v___x_1257_);
v___x_1259_ = lean_uint64_sub(v___x_1246_, v___x_1255_);
v_half_1260_ = lean_uint64_shift_left(v___x_1255_, v___x_1259_);
v___x_1261_ = lean_uint64_dec_lt(v_remainder_1258_, v_half_1260_);
if (v___x_1261_ == 0)
{
uint8_t v___x_1262_; 
v___x_1262_ = lean_uint64_dec_lt(v_half_1260_, v_remainder_1258_);
if (v___x_1262_ == 0)
{
uint64_t v___x_1263_; uint8_t v___x_1264_; 
v___x_1263_ = lean_uint64_land(v_quotient_1254_, v___x_1255_);
v___x_1264_ = lean_uint64_dec_eq(v___x_1263_, v___x_1243_);
if (v___x_1264_ == 0)
{
uint64_t v___x_1265_; 
v___x_1265_ = lean_uint64_add(v_quotient_1254_, v___x_1255_);
v___y_853_ = v___x_1243_;
v___y_854_ = v___y_1231_;
v___y_855_ = v___y_1235_;
v___y_856_ = v___x_1265_;
goto v___jp_852_;
}
else
{
v___y_853_ = v___x_1243_;
v___y_854_ = v___y_1231_;
v___y_855_ = v___y_1235_;
v___y_856_ = v_quotient_1254_;
goto v___jp_852_;
}
}
else
{
uint64_t v___x_1266_; 
v___x_1266_ = lean_uint64_add(v_quotient_1254_, v___x_1255_);
v___y_853_ = v___x_1243_;
v___y_854_ = v___y_1231_;
v___y_855_ = v___y_1235_;
v___y_856_ = v___x_1266_;
goto v___jp_852_;
}
}
else
{
v___y_853_ = v___x_1243_;
v___y_854_ = v___y_1231_;
v___y_855_ = v___y_1235_;
v___y_856_ = v_quotient_1254_;
goto v___jp_852_;
}
}
}
else
{
v___y_853_ = v___x_1243_;
v___y_854_ = v___y_1231_;
v___y_855_ = v___y_1235_;
v___y_856_ = v___x_1237_;
goto v___jp_852_;
}
}
else
{
if (v___y_1231_ == 0)
{
uint32_t v___x_1267_; 
v___x_1267_ = 0;
return v___x_1267_;
}
else
{
uint32_t v___x_1268_; 
v___x_1268_ = 2147483648;
return v___x_1268_;
}
}
}
}
}
v___jp_1272_:
{
uint64_t v___x_1278_; uint64_t v___x_1279_; uint8_t v___x_1280_; 
v___x_1278_ = lean_uint32_to_uint64(v_ey_1271_);
v___x_1279_ = 0ULL;
v___x_1280_ = lean_uint64_dec_eq(v___x_1278_, v___x_1279_);
if (v___x_1280_ == 0)
{
uint64_t v___x_1281_; uint64_t v___x_1282_; 
v___x_1281_ = 1ULL;
v___x_1282_ = lean_uint64_sub(v___x_1278_, v___x_1281_);
v___y_1231_ = v___y_1273_;
v___y_1232_ = v___y_1277_;
v___y_1233_ = v___y_1275_;
v___y_1234_ = v___y_1274_;
v___y_1235_ = v___y_1276_;
v___y_1236_ = v___x_1282_;
goto v___jp_1230_;
}
else
{
v___y_1231_ = v___y_1273_;
v___y_1232_ = v___y_1277_;
v___y_1233_ = v___y_1275_;
v___y_1234_ = v___y_1274_;
v___y_1235_ = v___y_1276_;
v___y_1236_ = v___x_1279_;
goto v___jp_1230_;
}
}
v___jp_1283_:
{
uint64_t v___x_1288_; uint64_t v___x_1289_; uint8_t v___x_1290_; 
v___x_1288_ = lean_uint32_to_uint64(v_ex_1269_);
v___x_1289_ = 0ULL;
v___x_1290_ = lean_uint64_dec_eq(v___x_1288_, v___x_1289_);
if (v___x_1290_ == 0)
{
uint64_t v___x_1291_; uint64_t v___x_1292_; 
v___x_1291_ = 1ULL;
v___x_1292_ = lean_uint64_sub(v___x_1288_, v___x_1291_);
v___y_1273_ = v___y_1284_;
v___y_1274_ = v___y_1285_;
v___y_1275_ = v___y_1287_;
v___y_1276_ = v___y_1286_;
v___y_1277_ = v___x_1292_;
goto v___jp_1272_;
}
else
{
v___y_1273_ = v___y_1284_;
v___y_1274_ = v___y_1285_;
v___y_1275_ = v___y_1287_;
v___y_1276_ = v___y_1286_;
v___y_1277_ = v___x_1289_;
goto v___jp_1272_;
}
}
v___jp_1293_:
{
uint32_t v___x_1298_; uint8_t v___x_1299_; 
v___x_1298_ = 0;
v___x_1299_ = lean_uint32_dec_eq(v_ey_1271_, v___x_1298_);
if (v___x_1299_ == 0)
{
uint64_t v___x_1300_; uint64_t v___x_1301_; uint64_t v___x_1302_; 
v___x_1300_ = lean_uint32_to_uint64(v___y_1295_);
v___x_1301_ = 8388608ULL;
v___x_1302_ = lean_uint64_lor(v___x_1300_, v___x_1301_);
v___y_1284_ = v___y_1294_;
v___y_1285_ = v___y_1297_;
v___y_1286_ = v___y_1296_;
v___y_1287_ = v___x_1302_;
goto v___jp_1283_;
}
else
{
uint64_t v___x_1303_; 
v___x_1303_ = lean_uint32_to_uint64(v___y_1295_);
v___y_1284_ = v___y_1294_;
v___y_1285_ = v___y_1297_;
v___y_1286_ = v___y_1296_;
v___y_1287_ = v___x_1303_;
goto v___jp_1283_;
}
}
v___jp_1304_:
{
uint32_t v___x_1306_; uint32_t v_xFraction_1307_; uint32_t v_yFraction_1308_; uint32_t v___x_1309_; uint8_t v___x_1310_; 
v___x_1306_ = 8388607;
v_xFraction_1307_ = lean_uint32_land(v___y_815_, v___x_1306_);
v_yFraction_1308_ = lean_uint32_land(v___y_816_, v___x_1306_);
v___x_1309_ = 0;
v___x_1310_ = lean_uint32_dec_eq(v_ex_1269_, v___x_1309_);
if (v___x_1310_ == 0)
{
uint64_t v___x_1311_; uint64_t v___x_1312_; uint64_t v___x_1313_; 
v___x_1311_ = lean_uint32_to_uint64(v_xFraction_1307_);
v___x_1312_ = 8388608ULL;
v___x_1313_ = lean_uint64_lor(v___x_1311_, v___x_1312_);
v___y_1294_ = v___y_1305_;
v___y_1295_ = v_yFraction_1308_;
v___y_1296_ = v___x_1306_;
v___y_1297_ = v___x_1313_;
goto v___jp_1293_;
}
else
{
uint64_t v___x_1314_; 
v___x_1314_ = lean_uint32_to_uint64(v_xFraction_1307_);
v___y_1294_ = v___y_1305_;
v___y_1295_ = v_yFraction_1308_;
v___y_1296_ = v___x_1306_;
v___y_1297_ = v___x_1314_;
goto v___jp_1293_;
}
}
v___jp_1318_:
{
if (v___y_1319_ == 0)
{
if (v___y_1321_ == 0)
{
v___y_1305_ = v___y_1320_;
goto v___jp_1304_;
}
else
{
v___y_1305_ = v___x_1317_;
goto v___jp_1304_;
}
}
else
{
if (v___y_1321_ == 0)
{
v___y_1305_ = v___x_1317_;
goto v___jp_1304_;
}
else
{
v___y_1305_ = v___y_1320_;
goto v___jp_1304_;
}
}
}
v___jp_1322_:
{
uint32_t v___x_1325_; uint32_t v___x_1326_; uint32_t v___x_1327_; uint8_t v___x_1328_; 
v___x_1325_ = 2147483648;
v___x_1326_ = lean_uint32_land(v___y_816_, v___x_1325_);
v___x_1327_ = 0;
v___x_1328_ = lean_uint32_dec_eq(v___x_1326_, v___x_1327_);
if (v___x_1328_ == 0)
{
v___y_1319_ = v___y_1324_;
v___y_1320_ = v___y_1323_;
v___y_1321_ = v___x_1317_;
goto v___jp_1318_;
}
else
{
v___y_1319_ = v___y_1324_;
v___y_1320_ = v___y_1323_;
v___y_1321_ = v___y_1323_;
goto v___jp_1318_;
}
}
v___jp_1329_:
{
if (v___y_1330_ == 0)
{
uint32_t v___x_1331_; uint32_t v___x_1332_; uint32_t v___x_1333_; uint8_t v___x_1334_; 
v___x_1331_ = 2147483648;
v___x_1332_ = lean_uint32_land(v___y_815_, v___x_1331_);
v___x_1333_ = 0;
v___x_1334_ = lean_uint32_dec_eq(v___x_1332_, v___x_1333_);
if (v___x_1334_ == 0)
{
v___y_1323_ = v___y_1330_;
v___y_1324_ = v___x_1317_;
goto v___jp_1322_;
}
else
{
v___y_1323_ = v___y_1330_;
v___y_1324_ = v___y_1330_;
goto v___jp_1322_;
}
}
else
{
lean_object* v___x_1335_; lean_object* v___x_1336_; lean_object* v___x_1337_; uint32_t v___x_1338_; 
v___x_1335_ = lean_uint32_to_nat(v___y_815_);
v___x_1336_ = lean_uint32_to_nat(v___y_816_);
v___x_1337_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1335_, v___x_1336_);
v___x_1338_ = lean_uint32_of_nat(v___x_1337_);
lean_dec(v___x_1337_);
return v___x_1338_;
}
}
}
else
{
uint32_t v___x_1351_; uint32_t v___x_1352_; uint32_t v___x_1353_; uint32_t v___x_1354_; float v___x_1355_; lean_object* v___x_1356_; uint32_t v___x_1357_; uint32_t v___x_1358_; lean_object* v___x_1359_; lean_object* v___x_1360_; float v___x_1361_; float v___x_1362_; uint32_t v___x_1363_; uint32_t v___x_1364_; float v___x_1365_; uint32_t v___x_1366_; lean_object* v___x_1367_; lean_object* v___x_1368_; float v___x_1369_; float v___x_1370_; float v___x_1371_; uint32_t v___x_1372_; 
v___x_1351_ = 8388607;
v___x_1352_ = lean_uint32_land(v___y_815_, v___x_1351_);
v___x_1353_ = 8388608;
v___x_1354_ = lean_uint32_lor(v___x_1352_, v___x_1353_);
v___x_1355_ = lean_uint32_to_float32(v___x_1354_);
v___x_1356_ = lp_competition_R2W01b_scaleTable;
v___x_1357_ = 23;
v___x_1358_ = lean_uint32_shift_right(v___y_815_, v___x_1357_);
v___x_1359_ = lean_uint32_to_nat(v___x_1358_);
v___x_1360_ = lean_array_fget_borrowed(v___x_1356_, v___x_1359_);
lean_dec(v___x_1359_);
v___x_1361_ = lean_unbox_float32(v___x_1360_);
v___x_1362_ = lean_float32_mul(v___x_1355_, v___x_1361_);
v___x_1363_ = lean_uint32_land(v___y_816_, v___x_1351_);
v___x_1364_ = lean_uint32_lor(v___x_1363_, v___x_1353_);
v___x_1365_ = lean_uint32_to_float32(v___x_1364_);
v___x_1366_ = lean_uint32_shift_right(v___y_816_, v___x_1357_);
v___x_1367_ = lean_uint32_to_nat(v___x_1366_);
v___x_1368_ = lean_array_fget_borrowed(v___x_1356_, v___x_1367_);
lean_dec(v___x_1367_);
v___x_1369_ = lean_unbox_float32(v___x_1368_);
v___x_1370_ = lean_float32_mul(v___x_1365_, v___x_1369_);
v___x_1371_ = lean_float32_mul(v___x_1362_, v___x_1370_);
v___x_1372_ = lean_float32_to_bits(v___x_1371_);
return v___x_1372_;
}
v___jp_817_:
{
uint32_t v___x_819_; uint32_t v___x_820_; 
v___x_819_ = 8388608;
v___x_820_ = lean_uint32_lor(v___y_818_, v___x_819_);
return v___x_820_;
}
v___jp_821_:
{
uint32_t v___x_823_; uint32_t v___x_824_; 
v___x_823_ = 8388608;
v___x_824_ = lean_uint32_lor(v___y_822_, v___x_823_);
return v___x_824_;
}
v___jp_825_:
{
uint32_t v___x_829_; uint32_t v___x_830_; 
v___x_829_ = lean_uint32_land(v___y_826_, v___y_827_);
v___x_830_ = lean_uint32_lor(v___y_828_, v___x_829_);
return v___x_830_;
}
v___jp_831_:
{
uint8_t v___x_836_; 
v___x_836_ = lean_uint64_dec_eq(v___y_835_, v___y_834_);
if (v___x_836_ == 0)
{
uint64_t v___x_837_; uint8_t v___x_838_; 
v___x_837_ = 8388608ULL;
v___x_838_ = lean_uint64_dec_eq(v___y_835_, v___x_837_);
if (v___x_838_ == 0)
{
uint32_t v___x_839_; 
v___x_839_ = lean_uint64_to_uint32(v___y_835_);
if (v___y_832_ == 0)
{
uint32_t v___x_840_; 
v___x_840_ = 0;
v___y_826_ = v___x_839_;
v___y_827_ = v___y_833_;
v___y_828_ = v___x_840_;
goto v___jp_825_;
}
else
{
uint32_t v___x_841_; 
v___x_841_ = 2147483648;
v___y_826_ = v___x_839_;
v___y_827_ = v___y_833_;
v___y_828_ = v___x_841_;
goto v___jp_825_;
}
}
else
{
if (v___y_832_ == 0)
{
uint32_t v___x_842_; 
v___x_842_ = 0;
v___y_818_ = v___x_842_;
goto v___jp_817_;
}
else
{
uint32_t v___x_843_; 
v___x_843_ = 2147483648;
v___y_818_ = v___x_843_;
goto v___jp_817_;
}
}
}
else
{
if (v___y_832_ == 0)
{
uint32_t v___x_844_; 
v___x_844_ = 0;
return v___x_844_;
}
else
{
uint32_t v___x_845_; 
v___x_845_ = 2147483648;
return v___x_845_;
}
}
}
v___jp_846_:
{
uint32_t v___x_850_; uint32_t v___x_851_; 
v___x_850_ = lean_uint32_land(v___y_848_, v___y_847_);
v___x_851_ = lean_uint32_lor(v___y_849_, v___x_850_);
return v___x_851_;
}
v___jp_852_:
{
uint8_t v___x_857_; 
v___x_857_ = lean_uint64_dec_eq(v___y_856_, v___y_853_);
if (v___x_857_ == 0)
{
uint64_t v___x_858_; uint8_t v___x_859_; 
v___x_858_ = 8388608ULL;
v___x_859_ = lean_uint64_dec_eq(v___y_856_, v___x_858_);
if (v___x_859_ == 0)
{
uint32_t v___x_860_; 
v___x_860_ = lean_uint64_to_uint32(v___y_856_);
if (v___y_854_ == 0)
{
uint32_t v___x_861_; 
v___x_861_ = 0;
v___y_847_ = v___y_855_;
v___y_848_ = v___x_860_;
v___y_849_ = v___x_861_;
goto v___jp_846_;
}
else
{
uint32_t v___x_862_; 
v___x_862_ = 2147483648;
v___y_847_ = v___y_855_;
v___y_848_ = v___x_860_;
v___y_849_ = v___x_862_;
goto v___jp_846_;
}
}
else
{
if (v___y_854_ == 0)
{
uint32_t v___x_863_; 
v___x_863_ = 0;
v___y_822_ = v___x_863_;
goto v___jp_821_;
}
else
{
uint32_t v___x_864_; 
v___x_864_ = 2147483648;
v___y_822_ = v___x_864_;
goto v___jp_821_;
}
}
}
else
{
if (v___y_854_ == 0)
{
uint32_t v___x_865_; 
v___x_865_ = 0;
return v___x_865_;
}
else
{
uint32_t v___x_866_; 
v___x_866_ = 2147483648;
return v___x_866_;
}
}
}
v___jp_867_:
{
if (v___y_868_ == 0)
{
uint32_t v___x_869_; 
v___x_869_ = lp_competition_Submission_FastMul_mul(v___y_815_, v___y_816_);
return v___x_869_;
}
else
{
uint32_t v___x_870_; uint32_t v___x_871_; 
v___x_870_ = 4194304;
v___x_871_ = lean_uint32_lor(v___y_816_, v___x_870_);
return v___x_871_;
}
}
v___jp_872_:
{
uint32_t v___x_873_; uint32_t v___x_874_; uint32_t v___x_875_; uint32_t v___x_876_; uint8_t v___x_877_; 
v___x_873_ = 23;
v___x_874_ = lean_uint32_shift_right(v___y_816_, v___x_873_);
v___x_875_ = 255;
v___x_876_ = lean_uint32_land(v___x_874_, v___x_875_);
v___x_877_ = lean_uint32_dec_eq(v___x_876_, v___x_875_);
if (v___x_877_ == 0)
{
v___y_868_ = v___x_877_;
goto v___jp_867_;
}
else
{
uint32_t v___x_878_; uint32_t v___x_879_; uint32_t v___x_880_; uint8_t v___x_881_; 
v___x_878_ = 8388607;
v___x_879_ = lean_uint32_land(v___y_816_, v___x_878_);
v___x_880_ = 0;
v___x_881_ = lean_uint32_dec_eq(v___x_879_, v___x_880_);
if (v___x_881_ == 0)
{
v___y_868_ = v___x_877_;
goto v___jp_867_;
}
else
{
uint32_t v___x_882_; 
v___x_882_ = lp_competition_Submission_FastMul_mul(v___y_815_, v___y_816_);
return v___x_882_;
}
}
}
v___jp_883_:
{
if (v___y_884_ == 0)
{
goto v___jp_872_;
}
else
{
uint32_t v___x_885_; uint32_t v___x_886_; 
v___x_885_ = 4194304;
v___x_886_ = lean_uint32_lor(v___y_815_, v___x_885_);
return v___x_886_;
}
}
v___jp_887_:
{
uint32_t v___x_888_; uint32_t v___x_889_; uint32_t v___x_890_; uint32_t v___x_891_; uint8_t v___x_892_; 
v___x_888_ = 23;
v___x_889_ = lean_uint32_shift_right(v___y_815_, v___x_888_);
v___x_890_ = 255;
v___x_891_ = lean_uint32_land(v___x_889_, v___x_890_);
v___x_892_ = lean_uint32_dec_eq(v___x_891_, v___x_890_);
if (v___x_892_ == 0)
{
v___y_884_ = v___x_892_;
goto v___jp_883_;
}
else
{
uint32_t v___x_893_; uint32_t v___x_894_; uint32_t v___x_895_; uint8_t v___x_896_; 
v___x_893_ = 8388607;
v___x_894_ = lean_uint32_land(v___y_815_, v___x_893_);
v___x_895_ = 0;
v___x_896_ = lean_uint32_dec_eq(v___x_894_, v___x_895_);
if (v___x_896_ == 0)
{
v___y_884_ = v___x_892_;
goto v___jp_883_;
}
else
{
goto v___jp_872_;
}
}
}
v___jp_897_:
{
if (v___y_898_ == 0)
{
goto v___jp_887_;
}
else
{
uint32_t v___x_899_; uint32_t v___x_900_; uint32_t v___x_901_; uint8_t v___x_902_; 
v___x_899_ = 4194304;
v___x_900_ = lean_uint32_land(v___y_816_, v___x_899_);
v___x_901_ = 0;
v___x_902_ = lean_uint32_dec_eq(v___x_900_, v___x_901_);
if (v___x_902_ == 0)
{
goto v___jp_887_;
}
else
{
uint32_t v___x_903_; 
v___x_903_ = lean_uint32_lor(v___y_816_, v___x_899_);
return v___x_903_;
}
}
}
v___jp_904_:
{
uint32_t v___x_905_; uint32_t v___x_906_; uint32_t v___x_907_; uint32_t v___x_908_; uint8_t v___x_909_; 
v___x_905_ = 23;
v___x_906_ = lean_uint32_shift_right(v___y_816_, v___x_905_);
v___x_907_ = 255;
v___x_908_ = lean_uint32_land(v___x_906_, v___x_907_);
v___x_909_ = lean_uint32_dec_eq(v___x_908_, v___x_907_);
if (v___x_909_ == 0)
{
v___y_898_ = v___x_909_;
goto v___jp_897_;
}
else
{
uint32_t v___x_910_; uint32_t v___x_911_; uint32_t v___x_912_; uint8_t v___x_913_; 
v___x_910_ = 8388607;
v___x_911_ = lean_uint32_land(v___y_816_, v___x_910_);
v___x_912_ = 0;
v___x_913_ = lean_uint32_dec_eq(v___x_911_, v___x_912_);
if (v___x_913_ == 0)
{
v___y_898_ = v___x_909_;
goto v___jp_897_;
}
else
{
goto v___jp_887_;
}
}
}
v___jp_914_:
{
if (v___y_915_ == 0)
{
goto v___jp_904_;
}
else
{
uint32_t v___x_916_; uint32_t v___x_917_; uint32_t v___x_918_; uint8_t v___x_919_; 
v___x_916_ = 4194304;
v___x_917_ = lean_uint32_land(v___y_815_, v___x_916_);
v___x_918_ = 0;
v___x_919_ = lean_uint32_dec_eq(v___x_917_, v___x_918_);
if (v___x_919_ == 0)
{
goto v___jp_904_;
}
else
{
uint32_t v___x_920_; 
v___x_920_ = lean_uint32_lor(v___y_815_, v___x_916_);
return v___x_920_;
}
}
}
v___jp_921_:
{
float v_result_924_; uint8_t v___x_925_; 
v_result_924_ = lean_float32_mul(v___y_922_, v___y_923_);
v___x_925_ = lean_float32_beq(v_result_924_, v_result_924_);
if (v___x_925_ == 0)
{
uint32_t v___x_926_; uint32_t v___x_927_; uint32_t v___x_928_; uint32_t v___x_929_; uint8_t v___x_930_; 
v___x_926_ = 23;
v___x_927_ = lean_uint32_shift_right(v___y_815_, v___x_926_);
v___x_928_ = 255;
v___x_929_ = lean_uint32_land(v___x_927_, v___x_928_);
v___x_930_ = lean_uint32_dec_eq(v___x_929_, v___x_928_);
if (v___x_930_ == 0)
{
v___y_915_ = v___x_930_;
goto v___jp_914_;
}
else
{
uint32_t v___x_931_; uint32_t v___x_932_; uint32_t v___x_933_; uint8_t v___x_934_; 
v___x_931_ = 8388607;
v___x_932_ = lean_uint32_land(v___y_815_, v___x_931_);
v___x_933_ = 0;
v___x_934_ = lean_uint32_dec_eq(v___x_932_, v___x_933_);
if (v___x_934_ == 0)
{
v___y_915_ = v___x_930_;
goto v___jp_914_;
}
else
{
goto v___jp_904_;
}
}
}
else
{
uint32_t v___x_935_; 
v___x_935_ = lean_float32_to_bits(v_result_924_);
return v___x_935_;
}
}
v___jp_936_:
{
if (v___y_938_ == 0)
{
float v___x_939_; 
v___x_939_ = lean_float32_of_bits(v___y_816_);
v___y_922_ = v___y_937_;
v___y_923_ = v___x_939_;
goto v___jp_921_;
}
else
{
uint32_t v___x_940_; uint32_t v___x_941_; uint32_t v___x_942_; uint32_t v___x_943_; float v___x_944_; lean_object* v___x_945_; uint32_t v___x_946_; uint32_t v___x_947_; lean_object* v___x_948_; lean_object* v___x_949_; float v___x_950_; float v___x_951_; 
v___x_940_ = 8388607;
v___x_941_ = lean_uint32_land(v___y_816_, v___x_940_);
v___x_942_ = 8388608;
v___x_943_ = lean_uint32_lor(v___x_941_, v___x_942_);
v___x_944_ = lean_uint32_to_float32(v___x_943_);
v___x_945_ = lp_competition_R2W01b_scaleTable;
v___x_946_ = 23;
v___x_947_ = lean_uint32_shift_right(v___y_816_, v___x_946_);
v___x_948_ = lean_uint32_to_nat(v___x_947_);
v___x_949_ = lean_array_fget_borrowed(v___x_945_, v___x_948_);
lean_dec(v___x_948_);
v___x_950_ = lean_unbox_float32(v___x_949_);
v___x_951_ = lean_float32_mul(v___x_944_, v___x_950_);
v___y_922_ = v___y_937_;
v___y_923_ = v___x_951_;
goto v___jp_921_;
}
}
v___jp_952_:
{
uint32_t v___x_954_; uint32_t v_a_955_; uint32_t v___x_956_; uint32_t v___x_957_; uint32_t v___x_958_; uint8_t v___x_959_; 
v___x_954_ = 2147483647;
v_a_955_ = lean_uint32_land(v___y_816_, v___x_954_);
v___x_956_ = 201326591;
v___x_957_ = 1;
v___x_958_ = lean_uint32_sub(v_a_955_, v___x_957_);
v___x_959_ = lean_uint32_dec_le(v___x_956_, v___x_958_);
if (v___x_959_ == 0)
{
v___y_937_ = v___y_953_;
v___y_938_ = v___x_959_;
goto v___jp_936_;
}
else
{
uint32_t v___x_960_; uint8_t v___x_961_; 
v___x_960_ = 2139095040;
v___x_961_ = lean_uint32_dec_lt(v_a_955_, v___x_960_);
v___y_937_ = v___y_953_;
v___y_938_ = v___x_961_;
goto v___jp_936_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_runNativeInline___lam__1___boxed(lean_object* v___y_1373_, lean_object* v___y_1374_){
_start:
{
uint32_t v___y_2247__boxed_1375_; uint32_t v___y_2248__boxed_1376_; uint32_t v_res_1377_; lean_object* v_r_1378_; 
v___y_2247__boxed_1375_ = lean_unbox_uint32(v___y_1373_);
lean_dec(v___y_1373_);
v___y_2248__boxed_1376_ = lean_unbox_uint32(v___y_1374_);
lean_dec(v___y_1374_);
v_res_1377_ = lp_competition_runNativeInline___lam__1(v___y_2247__boxed_1375_, v___y_2248__boxed_1376_);
v_r_1378_ = lean_box_uint32(v_res_1377_);
return v_r_1378_;
}
}
LEAN_EXPORT lean_object* lp_competition_runNativeInline(){
_start:
{
lean_object* v___f_1381_; lean_object* v___f_1382_; lean_object* v___x_1383_; lean_object* v___x_1384_; lean_object* v___x_1385_; 
v___f_1381_ = ((lean_object*)(lp_competition_runControl___closed__0));
v___f_1382_ = ((lean_object*)(lp_competition_runNativeInline___closed__0));
v___x_1383_ = ((lean_object*)(lp_competition_runControl___closed__2));
v___x_1384_ = ((lean_object*)(lp_competition_runControl___closed__3));
v___x_1385_ = lp_competition_Bench_Suite_run(v___f_1381_, v___f_1382_, v___x_1383_, v___x_1384_);
return v___x_1385_;
}
}
LEAN_EXPORT lean_object* lp_competition_runNativeInline___boxed(lean_object* v_a_1386_){
_start:
{
lean_object* v_res_1387_; 
v_res_1387_ = lp_competition_runNativeInline();
return v_res_1387_;
}
}
LEAN_EXPORT uint32_t lp_competition_runNativeCold___lam__1(uint32_t v___y_1388_, uint32_t v___y_1389_){
_start:
{
uint32_t v___x_1390_; uint32_t v___x_1391_; uint32_t v___x_1392_; uint32_t v___x_1393_; uint32_t v___x_1394_; uint32_t v___x_1395_; uint32_t v___x_1396_; uint32_t v___x_1397_; uint8_t v___x_1398_; 
v___x_1390_ = 2147483647;
v___x_1391_ = lean_uint32_land(v___y_1388_, v___x_1390_);
v___x_1392_ = 536870912;
v___x_1393_ = lean_uint32_sub(v___x_1391_, v___x_1392_);
v___x_1394_ = lean_uint32_land(v___y_1389_, v___x_1390_);
v___x_1395_ = lean_uint32_sub(v___x_1394_, v___x_1392_);
v___x_1396_ = lean_uint32_lor(v___x_1393_, v___x_1395_);
v___x_1397_ = 1073741824;
v___x_1398_ = lean_uint32_dec_lt(v___x_1396_, v___x_1397_);
if (v___x_1398_ == 0)
{
uint32_t v___x_1399_; 
v___x_1399_ = lp_competition_Submission_R22NativeCold_retainedMul(v___y_1388_, v___y_1389_);
return v___x_1399_;
}
else
{
uint32_t v___x_1400_; uint32_t v___x_1401_; uint32_t v___x_1402_; uint32_t v___x_1403_; float v___x_1404_; lean_object* v___x_1405_; uint32_t v___x_1406_; uint32_t v___x_1407_; lean_object* v___x_1408_; lean_object* v___x_1409_; float v___x_1410_; float v___x_1411_; uint32_t v___x_1412_; uint32_t v___x_1413_; float v___x_1414_; uint32_t v___x_1415_; lean_object* v___x_1416_; lean_object* v___x_1417_; float v___x_1418_; float v___x_1419_; float v___x_1420_; uint32_t v___x_1421_; 
v___x_1400_ = 8388607;
v___x_1401_ = lean_uint32_land(v___y_1388_, v___x_1400_);
v___x_1402_ = 8388608;
v___x_1403_ = lean_uint32_lor(v___x_1401_, v___x_1402_);
v___x_1404_ = lean_uint32_to_float32(v___x_1403_);
v___x_1405_ = lp_competition_R2W01b_scaleTable;
v___x_1406_ = 23;
v___x_1407_ = lean_uint32_shift_right(v___y_1388_, v___x_1406_);
v___x_1408_ = lean_uint32_to_nat(v___x_1407_);
v___x_1409_ = lean_array_fget_borrowed(v___x_1405_, v___x_1408_);
lean_dec(v___x_1408_);
v___x_1410_ = lean_unbox_float32(v___x_1409_);
v___x_1411_ = lean_float32_mul(v___x_1404_, v___x_1410_);
v___x_1412_ = lean_uint32_land(v___y_1389_, v___x_1400_);
v___x_1413_ = lean_uint32_lor(v___x_1412_, v___x_1402_);
v___x_1414_ = lean_uint32_to_float32(v___x_1413_);
v___x_1415_ = lean_uint32_shift_right(v___y_1389_, v___x_1406_);
v___x_1416_ = lean_uint32_to_nat(v___x_1415_);
v___x_1417_ = lean_array_fget_borrowed(v___x_1405_, v___x_1416_);
lean_dec(v___x_1416_);
v___x_1418_ = lean_unbox_float32(v___x_1417_);
v___x_1419_ = lean_float32_mul(v___x_1414_, v___x_1418_);
v___x_1420_ = lean_float32_mul(v___x_1411_, v___x_1419_);
v___x_1421_ = lean_float32_to_bits(v___x_1420_);
return v___x_1421_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_runNativeCold___lam__1___boxed(lean_object* v___y_1422_, lean_object* v___y_1423_){
_start:
{
uint32_t v___y_699__boxed_1424_; uint32_t v___y_700__boxed_1425_; uint32_t v_res_1426_; lean_object* v_r_1427_; 
v___y_699__boxed_1424_ = lean_unbox_uint32(v___y_1422_);
lean_dec(v___y_1422_);
v___y_700__boxed_1425_ = lean_unbox_uint32(v___y_1423_);
lean_dec(v___y_1423_);
v_res_1426_ = lp_competition_runNativeCold___lam__1(v___y_699__boxed_1424_, v___y_700__boxed_1425_);
v_r_1427_ = lean_box_uint32(v_res_1426_);
return v_r_1427_;
}
}
LEAN_EXPORT lean_object* lp_competition_runNativeCold(){
_start:
{
lean_object* v___f_1430_; lean_object* v___f_1431_; lean_object* v___x_1432_; lean_object* v___x_1433_; lean_object* v___x_1434_; 
v___f_1430_ = ((lean_object*)(lp_competition_runControl___closed__0));
v___f_1431_ = ((lean_object*)(lp_competition_runNativeCold___closed__0));
v___x_1432_ = ((lean_object*)(lp_competition_runControl___closed__2));
v___x_1433_ = ((lean_object*)(lp_competition_runControl___closed__3));
v___x_1434_ = lp_competition_Bench_Suite_run(v___f_1430_, v___f_1431_, v___x_1432_, v___x_1433_);
return v___x_1434_;
}
}
LEAN_EXPORT lean_object* lp_competition_runNativeCold___boxed(lean_object* v_a_1435_){
_start:
{
lean_object* v_res_1436_; 
v_res_1436_ = lp_competition_runNativeCold();
return v_res_1436_;
}
}
LEAN_EXPORT uint32_t lp_competition_runNativeAdd___lam__0(uint32_t v___y_1437_, uint32_t v___y_1438_){
_start:
{
uint8_t v___y_1440_; uint8_t v___y_1465_; uint32_t v___x_1475_; uint32_t v_a_1476_; uint32_t v___x_1477_; uint32_t v___x_1478_; uint32_t v___x_1479_; uint8_t v___x_1480_; 
v___x_1475_ = 2147483647;
v_a_1476_ = lean_uint32_land(v___y_1437_, v___x_1475_);
v___x_1477_ = 201326591;
v___x_1478_ = 1;
v___x_1479_ = lean_uint32_sub(v_a_1476_, v___x_1478_);
v___x_1480_ = lean_uint32_dec_le(v___x_1477_, v___x_1479_);
if (v___x_1480_ == 0)
{
v___y_1465_ = v___x_1480_;
goto v___jp_1464_;
}
else
{
uint32_t v___x_1481_; uint8_t v___x_1482_; 
v___x_1481_ = 2139095040;
v___x_1482_ = lean_uint32_dec_lt(v_a_1476_, v___x_1481_);
v___y_1465_ = v___x_1482_;
goto v___jp_1464_;
}
v___jp_1439_:
{
if (v___y_1440_ == 0)
{
uint32_t v___x_1441_; 
v___x_1441_ = lp_competition_Submission_R22NativeColdAdd_coldAdd(v___y_1437_, v___y_1438_);
return v___x_1441_;
}
else
{
uint32_t v___x_1442_; uint32_t v___x_1443_; uint32_t v___x_1444_; uint32_t v___x_1445_; float v___x_1446_; lean_object* v___x_1447_; uint32_t v___x_1448_; uint32_t v___x_1449_; lean_object* v___x_1450_; lean_object* v___x_1451_; float v___x_1452_; float v___x_1453_; uint32_t v___x_1454_; uint32_t v___x_1455_; float v___x_1456_; uint32_t v___x_1457_; lean_object* v___x_1458_; lean_object* v___x_1459_; float v___x_1460_; float v___x_1461_; float v___x_1462_; uint32_t v___x_1463_; 
v___x_1442_ = 8388607;
v___x_1443_ = lean_uint32_land(v___y_1437_, v___x_1442_);
v___x_1444_ = 8388608;
v___x_1445_ = lean_uint32_lor(v___x_1443_, v___x_1444_);
v___x_1446_ = lean_uint32_to_float32(v___x_1445_);
v___x_1447_ = lp_competition_R2W01b_scaleTable;
v___x_1448_ = 23;
v___x_1449_ = lean_uint32_shift_right(v___y_1437_, v___x_1448_);
v___x_1450_ = lean_uint32_to_nat(v___x_1449_);
v___x_1451_ = lean_array_fget_borrowed(v___x_1447_, v___x_1450_);
lean_dec(v___x_1450_);
v___x_1452_ = lean_unbox_float32(v___x_1451_);
v___x_1453_ = lean_float32_mul(v___x_1446_, v___x_1452_);
v___x_1454_ = lean_uint32_land(v___y_1438_, v___x_1442_);
v___x_1455_ = lean_uint32_lor(v___x_1454_, v___x_1444_);
v___x_1456_ = lean_uint32_to_float32(v___x_1455_);
v___x_1457_ = lean_uint32_shift_right(v___y_1438_, v___x_1448_);
v___x_1458_ = lean_uint32_to_nat(v___x_1457_);
v___x_1459_ = lean_array_fget_borrowed(v___x_1447_, v___x_1458_);
lean_dec(v___x_1458_);
v___x_1460_ = lean_unbox_float32(v___x_1459_);
v___x_1461_ = lean_float32_mul(v___x_1456_, v___x_1460_);
v___x_1462_ = lean_float32_add(v___x_1453_, v___x_1461_);
v___x_1463_ = lean_float32_to_bits(v___x_1462_);
return v___x_1463_;
}
}
v___jp_1464_:
{
if (v___y_1465_ == 0)
{
uint32_t v___x_1466_; 
v___x_1466_ = lp_competition_Submission_R22NativeColdAdd_coldAdd(v___y_1437_, v___y_1438_);
return v___x_1466_;
}
else
{
uint32_t v___x_1467_; uint32_t v_a_1468_; uint32_t v___x_1469_; uint32_t v___x_1470_; uint32_t v___x_1471_; uint8_t v___x_1472_; 
v___x_1467_ = 2147483647;
v_a_1468_ = lean_uint32_land(v___y_1438_, v___x_1467_);
v___x_1469_ = 201326591;
v___x_1470_ = 1;
v___x_1471_ = lean_uint32_sub(v_a_1468_, v___x_1470_);
v___x_1472_ = lean_uint32_dec_le(v___x_1469_, v___x_1471_);
if (v___x_1472_ == 0)
{
v___y_1440_ = v___x_1472_;
goto v___jp_1439_;
}
else
{
uint32_t v___x_1473_; uint8_t v___x_1474_; 
v___x_1473_ = 2139095040;
v___x_1474_ = lean_uint32_dec_lt(v_a_1468_, v___x_1473_);
v___y_1440_ = v___x_1474_;
goto v___jp_1439_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_runNativeAdd___lam__0___boxed(lean_object* v___y_1483_, lean_object* v___y_1484_){
_start:
{
uint32_t v___y_1668__boxed_1485_; uint32_t v___y_1669__boxed_1486_; uint32_t v_res_1487_; lean_object* v_r_1488_; 
v___y_1668__boxed_1485_ = lean_unbox_uint32(v___y_1483_);
lean_dec(v___y_1483_);
v___y_1669__boxed_1486_ = lean_unbox_uint32(v___y_1484_);
lean_dec(v___y_1484_);
v_res_1487_ = lp_competition_runNativeAdd___lam__0(v___y_1668__boxed_1485_, v___y_1669__boxed_1486_);
v_r_1488_ = lean_box_uint32(v_res_1487_);
return v_r_1488_;
}
}
LEAN_EXPORT uint32_t lp_competition_runNativeAdd___lam__1(uint32_t v___y_1489_, uint32_t v___y_1490_){
_start:
{
uint32_t v___y_1492_; uint32_t v___y_1496_; uint32_t v___y_1500_; uint32_t v___y_1501_; uint32_t v___y_1502_; uint8_t v___y_1506_; uint32_t v___y_1507_; uint64_t v___y_1508_; uint64_t v___y_1509_; uint32_t v___y_1521_; uint32_t v___y_1522_; uint32_t v___y_1523_; uint8_t v___y_1527_; uint64_t v___y_1528_; uint32_t v___y_1529_; uint64_t v___y_1530_; uint8_t v___y_1542_; uint8_t v___y_1558_; uint8_t v___y_1572_; uint8_t v___y_1589_; float v___y_1596_; float v___y_1597_; float v___y_1611_; uint8_t v___y_1612_; float v___y_1627_; uint32_t v___x_1636_; uint32_t v___x_1637_; uint8_t v___y_1639_; uint32_t v___x_1651_; uint32_t v___y_1653_; uint32_t v___y_1654_; uint32_t v___y_1655_; uint32_t v___y_1656_; uint8_t v___y_1663_; uint32_t v___y_1664_; uint32_t v___y_1665_; uint32_t v___y_1666_; uint8_t v___y_1670_; uint64_t v___y_1671_; uint32_t v___y_1672_; uint64_t v___y_1673_; uint64_t v___y_1674_; uint8_t v___y_1684_; uint64_t v___y_1685_; uint32_t v___y_1686_; uint64_t v___y_1687_; uint8_t v___y_1688_; uint64_t v___y_1689_; uint8_t v___y_1696_; uint64_t v___y_1697_; uint32_t v___y_1698_; uint64_t v___y_1699_; uint64_t v___y_1700_; uint8_t v___y_1706_; uint32_t v___y_1707_; uint64_t v___y_1708_; uint64_t v___y_1709_; uint64_t v___y_1710_; uint64_t v___y_1711_; uint8_t v___y_1766_; uint64_t v___y_1767_; uint32_t v___y_1768_; uint64_t v___y_1769_; uint64_t v___y_1770_; uint64_t v___y_1771_; uint64_t v___y_1772_; uint8_t v___y_1778_; uint64_t v___y_1779_; uint64_t v___y_1780_; uint64_t v___y_1781_; uint32_t v___y_1782_; uint64_t v___y_1783_; uint64_t v___y_1784_; uint64_t v___y_1785_; uint64_t v___y_1786_; uint8_t v___y_1791_; uint64_t v___y_1792_; uint32_t v___y_1793_; uint64_t v___y_1794_; uint64_t v___y_1795_; uint64_t v___y_1796_; uint64_t v___y_1797_; uint8_t v___y_1802_; uint64_t v___y_1803_; uint64_t v___y_1804_; uint32_t v___y_1805_; uint64_t v___y_1806_; uint64_t v___y_1807_; uint64_t v___y_1808_; uint64_t v___y_1809_; uint64_t v___y_1810_; uint8_t v___y_1815_; uint32_t v___y_1816_; uint64_t v___y_1817_; uint64_t v___y_1818_; uint64_t v___y_1819_; uint64_t v___y_1820_; uint64_t v___y_1821_; uint64_t v___y_1826_; uint64_t v___y_1827_; uint8_t v___y_1828_; uint64_t v___y_1829_; uint32_t v___y_1830_; uint64_t v___y_1831_; uint64_t v___y_1832_; uint64_t v___y_1833_; uint64_t v___y_1834_; uint64_t v___y_1839_; uint8_t v___y_1840_; uint32_t v___y_1841_; uint64_t v___y_1842_; uint64_t v___y_1843_; uint64_t v___y_1844_; uint64_t v___y_1845_; uint64_t v___y_1850_; uint64_t v___y_1851_; uint8_t v___y_1852_; uint64_t v___y_1853_; uint32_t v___y_1854_; uint64_t v___y_1855_; uint64_t v___y_1856_; uint64_t v___y_1857_; uint64_t v___y_1858_; uint64_t v___y_1863_; uint8_t v___y_1864_; uint32_t v___y_1865_; uint64_t v___y_1866_; uint64_t v___y_1867_; uint64_t v___y_1868_; uint64_t v___y_1869_; uint8_t v___y_1874_; uint64_t v___y_1875_; uint32_t v___y_1876_; uint64_t v___y_1877_; uint64_t v___y_1878_; uint64_t v___y_1879_; uint64_t v___y_1880_; uint8_t v___y_1884_; uint32_t v___y_1885_; uint64_t v___y_1886_; uint64_t v___y_1887_; uint64_t v___y_1896_; uint64_t v___y_1897_; uint8_t v___y_1898_; uint64_t v___y_1899_; uint32_t v___y_1900_; uint64_t v___y_1901_; uint32_t v_ex_1934_; uint32_t v___x_1935_; uint32_t v_ey_1936_; uint64_t v___y_1938_; uint64_t v___y_1939_; uint8_t v___y_1940_; uint32_t v___y_1941_; uint64_t v___y_1942_; uint64_t v___y_1949_; uint8_t v___y_1950_; uint32_t v___y_1951_; uint64_t v___y_1952_; uint8_t v___y_1959_; uint32_t v___y_1960_; uint32_t v___y_1961_; uint64_t v___y_1962_; uint8_t v___y_1970_; uint32_t v___x_1980_; uint32_t v___x_1981_; uint8_t v___x_1982_; uint8_t v___y_1984_; uint8_t v___y_1985_; uint8_t v___y_1987_; uint8_t v___y_1988_; uint8_t v___y_1989_; uint8_t v___y_1991_; uint8_t v___y_1992_; uint8_t v___y_1998_; 
v___x_1636_ = 23;
v___x_1637_ = lean_uint32_shift_right(v___y_1489_, v___x_1636_);
v___x_1651_ = 255;
v_ex_1934_ = lean_uint32_land(v___x_1637_, v___x_1651_);
v___x_1935_ = lean_uint32_shift_right(v___y_1490_, v___x_1636_);
v_ey_1936_ = lean_uint32_land(v___x_1935_, v___x_1651_);
v___x_1980_ = lean_uint32_add(v_ex_1934_, v_ey_1936_);
v___x_1981_ = 128;
v___x_1982_ = lean_uint32_dec_lt(v___x_1980_, v___x_1981_);
if (v___x_1982_ == 0)
{
uint32_t v___x_2007_; uint32_t v_a_2008_; uint32_t v___x_2009_; uint32_t v___x_2010_; uint32_t v___x_2011_; uint8_t v___x_2012_; 
v___x_2007_ = 2147483647;
v_a_2008_ = lean_uint32_land(v___y_1489_, v___x_2007_);
v___x_2009_ = 201326591;
v___x_2010_ = 1;
v___x_2011_ = lean_uint32_sub(v_a_2008_, v___x_2010_);
v___x_2012_ = lean_uint32_dec_le(v___x_2009_, v___x_2011_);
if (v___x_2012_ == 0)
{
v___y_1639_ = v___x_2012_;
goto v___jp_1638_;
}
else
{
uint32_t v___x_2013_; uint8_t v___x_2014_; 
v___x_2013_ = 2139095040;
v___x_2014_ = lean_uint32_dec_lt(v_a_2008_, v___x_2013_);
v___y_1639_ = v___x_2014_;
goto v___jp_1638_;
}
}
else
{
uint32_t v___x_2015_; uint32_t v___x_2016_; uint32_t v___x_2017_; uint8_t v___x_2018_; 
v___x_2015_ = 4278190080;
v___x_2016_ = 1;
v___x_2017_ = lean_uint32_shift_left(v___y_1489_, v___x_2016_);
v___x_2018_ = lean_uint32_dec_le(v___x_2015_, v___x_2017_);
if (v___x_2018_ == 0)
{
uint32_t v___x_2019_; uint8_t v___x_2020_; 
v___x_2019_ = lean_uint32_shift_left(v___y_1490_, v___x_2016_);
v___x_2020_ = lean_uint32_dec_le(v___x_2015_, v___x_2019_);
v___y_1998_ = v___x_2020_;
goto v___jp_1997_;
}
else
{
v___y_1998_ = v___x_2018_;
goto v___jp_1997_;
}
}
v___jp_1491_:
{
uint32_t v___x_1493_; uint32_t v___x_1494_; 
v___x_1493_ = 8388608;
v___x_1494_ = lean_uint32_lor(v___y_1492_, v___x_1493_);
return v___x_1494_;
}
v___jp_1495_:
{
uint32_t v___x_1497_; uint32_t v___x_1498_; 
v___x_1497_ = 8388608;
v___x_1498_ = lean_uint32_lor(v___y_1496_, v___x_1497_);
return v___x_1498_;
}
v___jp_1499_:
{
uint32_t v___x_1503_; uint32_t v___x_1504_; 
v___x_1503_ = lean_uint32_land(v___y_1500_, v___y_1501_);
v___x_1504_ = lean_uint32_lor(v___y_1502_, v___x_1503_);
return v___x_1504_;
}
v___jp_1505_:
{
uint8_t v___x_1510_; 
v___x_1510_ = lean_uint64_dec_eq(v___y_1509_, v___y_1508_);
if (v___x_1510_ == 0)
{
uint64_t v___x_1511_; uint8_t v___x_1512_; 
v___x_1511_ = 8388608ULL;
v___x_1512_ = lean_uint64_dec_eq(v___y_1509_, v___x_1511_);
if (v___x_1512_ == 0)
{
uint32_t v___x_1513_; 
v___x_1513_ = lean_uint64_to_uint32(v___y_1509_);
if (v___y_1506_ == 0)
{
uint32_t v___x_1514_; 
v___x_1514_ = 0;
v___y_1500_ = v___x_1513_;
v___y_1501_ = v___y_1507_;
v___y_1502_ = v___x_1514_;
goto v___jp_1499_;
}
else
{
uint32_t v___x_1515_; 
v___x_1515_ = 2147483648;
v___y_1500_ = v___x_1513_;
v___y_1501_ = v___y_1507_;
v___y_1502_ = v___x_1515_;
goto v___jp_1499_;
}
}
else
{
if (v___y_1506_ == 0)
{
uint32_t v___x_1516_; 
v___x_1516_ = 0;
v___y_1496_ = v___x_1516_;
goto v___jp_1495_;
}
else
{
uint32_t v___x_1517_; 
v___x_1517_ = 2147483648;
v___y_1496_ = v___x_1517_;
goto v___jp_1495_;
}
}
}
else
{
if (v___y_1506_ == 0)
{
uint32_t v___x_1518_; 
v___x_1518_ = 0;
return v___x_1518_;
}
else
{
uint32_t v___x_1519_; 
v___x_1519_ = 2147483648;
return v___x_1519_;
}
}
}
v___jp_1520_:
{
uint32_t v___x_1524_; uint32_t v___x_1525_; 
v___x_1524_ = lean_uint32_land(v___y_1521_, v___y_1522_);
v___x_1525_ = lean_uint32_lor(v___y_1523_, v___x_1524_);
return v___x_1525_;
}
v___jp_1526_:
{
uint8_t v___x_1531_; 
v___x_1531_ = lean_uint64_dec_eq(v___y_1530_, v___y_1528_);
if (v___x_1531_ == 0)
{
uint64_t v___x_1532_; uint8_t v___x_1533_; 
v___x_1532_ = 8388608ULL;
v___x_1533_ = lean_uint64_dec_eq(v___y_1530_, v___x_1532_);
if (v___x_1533_ == 0)
{
uint32_t v___x_1534_; 
v___x_1534_ = lean_uint64_to_uint32(v___y_1530_);
if (v___y_1527_ == 0)
{
uint32_t v___x_1535_; 
v___x_1535_ = 0;
v___y_1521_ = v___x_1534_;
v___y_1522_ = v___y_1529_;
v___y_1523_ = v___x_1535_;
goto v___jp_1520_;
}
else
{
uint32_t v___x_1536_; 
v___x_1536_ = 2147483648;
v___y_1521_ = v___x_1534_;
v___y_1522_ = v___y_1529_;
v___y_1523_ = v___x_1536_;
goto v___jp_1520_;
}
}
else
{
if (v___y_1527_ == 0)
{
uint32_t v___x_1537_; 
v___x_1537_ = 0;
v___y_1492_ = v___x_1537_;
goto v___jp_1491_;
}
else
{
uint32_t v___x_1538_; 
v___x_1538_ = 2147483648;
v___y_1492_ = v___x_1538_;
goto v___jp_1491_;
}
}
}
else
{
if (v___y_1527_ == 0)
{
uint32_t v___x_1539_; 
v___x_1539_ = 0;
return v___x_1539_;
}
else
{
uint32_t v___x_1540_; 
v___x_1540_ = 2147483648;
return v___x_1540_;
}
}
}
v___jp_1541_:
{
if (v___y_1542_ == 0)
{
uint32_t v___x_1543_; 
v___x_1543_ = lp_competition_Submission_FastMul_mul(v___y_1489_, v___y_1490_);
return v___x_1543_;
}
else
{
uint32_t v___x_1544_; uint32_t v___x_1545_; 
v___x_1544_ = 4194304;
v___x_1545_ = lean_uint32_lor(v___y_1490_, v___x_1544_);
return v___x_1545_;
}
}
v___jp_1546_:
{
uint32_t v___x_1547_; uint32_t v___x_1548_; uint32_t v___x_1549_; uint32_t v___x_1550_; uint8_t v___x_1551_; 
v___x_1547_ = 23;
v___x_1548_ = lean_uint32_shift_right(v___y_1490_, v___x_1547_);
v___x_1549_ = 255;
v___x_1550_ = lean_uint32_land(v___x_1548_, v___x_1549_);
v___x_1551_ = lean_uint32_dec_eq(v___x_1550_, v___x_1549_);
if (v___x_1551_ == 0)
{
v___y_1542_ = v___x_1551_;
goto v___jp_1541_;
}
else
{
uint32_t v___x_1552_; uint32_t v___x_1553_; uint32_t v___x_1554_; uint8_t v___x_1555_; 
v___x_1552_ = 8388607;
v___x_1553_ = lean_uint32_land(v___y_1490_, v___x_1552_);
v___x_1554_ = 0;
v___x_1555_ = lean_uint32_dec_eq(v___x_1553_, v___x_1554_);
if (v___x_1555_ == 0)
{
v___y_1542_ = v___x_1551_;
goto v___jp_1541_;
}
else
{
uint32_t v___x_1556_; 
v___x_1556_ = lp_competition_Submission_FastMul_mul(v___y_1489_, v___y_1490_);
return v___x_1556_;
}
}
}
v___jp_1557_:
{
if (v___y_1558_ == 0)
{
goto v___jp_1546_;
}
else
{
uint32_t v___x_1559_; uint32_t v___x_1560_; 
v___x_1559_ = 4194304;
v___x_1560_ = lean_uint32_lor(v___y_1489_, v___x_1559_);
return v___x_1560_;
}
}
v___jp_1561_:
{
uint32_t v___x_1562_; uint32_t v___x_1563_; uint32_t v___x_1564_; uint32_t v___x_1565_; uint8_t v___x_1566_; 
v___x_1562_ = 23;
v___x_1563_ = lean_uint32_shift_right(v___y_1489_, v___x_1562_);
v___x_1564_ = 255;
v___x_1565_ = lean_uint32_land(v___x_1563_, v___x_1564_);
v___x_1566_ = lean_uint32_dec_eq(v___x_1565_, v___x_1564_);
if (v___x_1566_ == 0)
{
v___y_1558_ = v___x_1566_;
goto v___jp_1557_;
}
else
{
uint32_t v___x_1567_; uint32_t v___x_1568_; uint32_t v___x_1569_; uint8_t v___x_1570_; 
v___x_1567_ = 8388607;
v___x_1568_ = lean_uint32_land(v___y_1489_, v___x_1567_);
v___x_1569_ = 0;
v___x_1570_ = lean_uint32_dec_eq(v___x_1568_, v___x_1569_);
if (v___x_1570_ == 0)
{
v___y_1558_ = v___x_1566_;
goto v___jp_1557_;
}
else
{
goto v___jp_1546_;
}
}
}
v___jp_1571_:
{
if (v___y_1572_ == 0)
{
goto v___jp_1561_;
}
else
{
uint32_t v___x_1573_; uint32_t v___x_1574_; uint32_t v___x_1575_; uint8_t v___x_1576_; 
v___x_1573_ = 4194304;
v___x_1574_ = lean_uint32_land(v___y_1490_, v___x_1573_);
v___x_1575_ = 0;
v___x_1576_ = lean_uint32_dec_eq(v___x_1574_, v___x_1575_);
if (v___x_1576_ == 0)
{
goto v___jp_1561_;
}
else
{
uint32_t v___x_1577_; 
v___x_1577_ = lean_uint32_lor(v___y_1490_, v___x_1573_);
return v___x_1577_;
}
}
}
v___jp_1578_:
{
uint32_t v___x_1579_; uint32_t v___x_1580_; uint32_t v___x_1581_; uint32_t v___x_1582_; uint8_t v___x_1583_; 
v___x_1579_ = 23;
v___x_1580_ = lean_uint32_shift_right(v___y_1490_, v___x_1579_);
v___x_1581_ = 255;
v___x_1582_ = lean_uint32_land(v___x_1580_, v___x_1581_);
v___x_1583_ = lean_uint32_dec_eq(v___x_1582_, v___x_1581_);
if (v___x_1583_ == 0)
{
v___y_1572_ = v___x_1583_;
goto v___jp_1571_;
}
else
{
uint32_t v___x_1584_; uint32_t v___x_1585_; uint32_t v___x_1586_; uint8_t v___x_1587_; 
v___x_1584_ = 8388607;
v___x_1585_ = lean_uint32_land(v___y_1490_, v___x_1584_);
v___x_1586_ = 0;
v___x_1587_ = lean_uint32_dec_eq(v___x_1585_, v___x_1586_);
if (v___x_1587_ == 0)
{
v___y_1572_ = v___x_1583_;
goto v___jp_1571_;
}
else
{
goto v___jp_1561_;
}
}
}
v___jp_1588_:
{
if (v___y_1589_ == 0)
{
goto v___jp_1578_;
}
else
{
uint32_t v___x_1590_; uint32_t v___x_1591_; uint32_t v___x_1592_; uint8_t v___x_1593_; 
v___x_1590_ = 4194304;
v___x_1591_ = lean_uint32_land(v___y_1489_, v___x_1590_);
v___x_1592_ = 0;
v___x_1593_ = lean_uint32_dec_eq(v___x_1591_, v___x_1592_);
if (v___x_1593_ == 0)
{
goto v___jp_1578_;
}
else
{
uint32_t v___x_1594_; 
v___x_1594_ = lean_uint32_lor(v___y_1489_, v___x_1590_);
return v___x_1594_;
}
}
}
v___jp_1595_:
{
float v_result_1598_; uint8_t v___x_1599_; 
v_result_1598_ = lean_float32_mul(v___y_1596_, v___y_1597_);
v___x_1599_ = lean_float32_beq(v_result_1598_, v_result_1598_);
if (v___x_1599_ == 0)
{
uint32_t v___x_1600_; uint32_t v___x_1601_; uint32_t v___x_1602_; uint32_t v___x_1603_; uint8_t v___x_1604_; 
v___x_1600_ = 23;
v___x_1601_ = lean_uint32_shift_right(v___y_1489_, v___x_1600_);
v___x_1602_ = 255;
v___x_1603_ = lean_uint32_land(v___x_1601_, v___x_1602_);
v___x_1604_ = lean_uint32_dec_eq(v___x_1603_, v___x_1602_);
if (v___x_1604_ == 0)
{
v___y_1589_ = v___x_1604_;
goto v___jp_1588_;
}
else
{
uint32_t v___x_1605_; uint32_t v___x_1606_; uint32_t v___x_1607_; uint8_t v___x_1608_; 
v___x_1605_ = 8388607;
v___x_1606_ = lean_uint32_land(v___y_1489_, v___x_1605_);
v___x_1607_ = 0;
v___x_1608_ = lean_uint32_dec_eq(v___x_1606_, v___x_1607_);
if (v___x_1608_ == 0)
{
v___y_1589_ = v___x_1604_;
goto v___jp_1588_;
}
else
{
goto v___jp_1578_;
}
}
}
else
{
uint32_t v___x_1609_; 
v___x_1609_ = lean_float32_to_bits(v_result_1598_);
return v___x_1609_;
}
}
v___jp_1610_:
{
if (v___y_1612_ == 0)
{
float v___x_1613_; 
v___x_1613_ = lean_float32_of_bits(v___y_1490_);
v___y_1596_ = v___y_1611_;
v___y_1597_ = v___x_1613_;
goto v___jp_1595_;
}
else
{
uint32_t v___x_1614_; uint32_t v___x_1615_; uint32_t v___x_1616_; uint32_t v___x_1617_; float v___x_1618_; lean_object* v___x_1619_; uint32_t v___x_1620_; uint32_t v___x_1621_; lean_object* v___x_1622_; lean_object* v___x_1623_; float v___x_1624_; float v___x_1625_; 
v___x_1614_ = 8388607;
v___x_1615_ = lean_uint32_land(v___y_1490_, v___x_1614_);
v___x_1616_ = 8388608;
v___x_1617_ = lean_uint32_lor(v___x_1615_, v___x_1616_);
v___x_1618_ = lean_uint32_to_float32(v___x_1617_);
v___x_1619_ = lp_competition_R2W01b_scaleTable;
v___x_1620_ = 23;
v___x_1621_ = lean_uint32_shift_right(v___y_1490_, v___x_1620_);
v___x_1622_ = lean_uint32_to_nat(v___x_1621_);
v___x_1623_ = lean_array_fget_borrowed(v___x_1619_, v___x_1622_);
lean_dec(v___x_1622_);
v___x_1624_ = lean_unbox_float32(v___x_1623_);
v___x_1625_ = lean_float32_mul(v___x_1618_, v___x_1624_);
v___y_1596_ = v___y_1611_;
v___y_1597_ = v___x_1625_;
goto v___jp_1595_;
}
}
v___jp_1626_:
{
uint32_t v___x_1628_; uint32_t v_a_1629_; uint32_t v___x_1630_; uint32_t v___x_1631_; uint32_t v___x_1632_; uint8_t v___x_1633_; 
v___x_1628_ = 2147483647;
v_a_1629_ = lean_uint32_land(v___y_1490_, v___x_1628_);
v___x_1630_ = 201326591;
v___x_1631_ = 1;
v___x_1632_ = lean_uint32_sub(v_a_1629_, v___x_1631_);
v___x_1633_ = lean_uint32_dec_le(v___x_1630_, v___x_1632_);
if (v___x_1633_ == 0)
{
v___y_1611_ = v___y_1627_;
v___y_1612_ = v___x_1633_;
goto v___jp_1610_;
}
else
{
uint32_t v___x_1634_; uint8_t v___x_1635_; 
v___x_1634_ = 2139095040;
v___x_1635_ = lean_uint32_dec_lt(v_a_1629_, v___x_1634_);
v___y_1611_ = v___y_1627_;
v___y_1612_ = v___x_1635_;
goto v___jp_1610_;
}
}
v___jp_1638_:
{
if (v___y_1639_ == 0)
{
float v___x_1640_; 
v___x_1640_ = lean_float32_of_bits(v___y_1489_);
v___y_1627_ = v___x_1640_;
goto v___jp_1626_;
}
else
{
uint32_t v___x_1641_; uint32_t v___x_1642_; uint32_t v___x_1643_; uint32_t v___x_1644_; float v___x_1645_; lean_object* v___x_1646_; lean_object* v___x_1647_; lean_object* v___x_1648_; float v___x_1649_; float v___x_1650_; 
v___x_1641_ = 8388607;
v___x_1642_ = lean_uint32_land(v___y_1489_, v___x_1641_);
v___x_1643_ = 8388608;
v___x_1644_ = lean_uint32_lor(v___x_1642_, v___x_1643_);
v___x_1645_ = lean_uint32_to_float32(v___x_1644_);
v___x_1646_ = lp_competition_R2W01b_scaleTable;
v___x_1647_ = lean_uint32_to_nat(v___x_1637_);
v___x_1648_ = lean_array_fget_borrowed(v___x_1646_, v___x_1647_);
lean_dec(v___x_1647_);
v___x_1649_ = lean_unbox_float32(v___x_1648_);
v___x_1650_ = lean_float32_mul(v___x_1645_, v___x_1649_);
v___y_1627_ = v___x_1650_;
goto v___jp_1626_;
}
}
v___jp_1652_:
{
uint32_t v___x_1657_; uint32_t v___x_1658_; uint32_t v___x_1659_; uint32_t v___x_1660_; uint32_t v___x_1661_; 
v___x_1657_ = lean_uint32_land(v___y_1654_, v___x_1651_);
v___x_1658_ = lean_uint32_shift_left(v___x_1657_, v___x_1636_);
v___x_1659_ = lean_uint32_lor(v___y_1656_, v___x_1658_);
v___x_1660_ = lean_uint32_land(v___y_1653_, v___y_1655_);
v___x_1661_ = lean_uint32_lor(v___x_1659_, v___x_1660_);
return v___x_1661_;
}
v___jp_1662_:
{
if (v___y_1663_ == 0)
{
uint32_t v___x_1667_; 
v___x_1667_ = 0;
v___y_1653_ = v___y_1666_;
v___y_1654_ = v___y_1664_;
v___y_1655_ = v___y_1665_;
v___y_1656_ = v___x_1667_;
goto v___jp_1652_;
}
else
{
uint32_t v___x_1668_; 
v___x_1668_ = 2147483648;
v___y_1653_ = v___y_1666_;
v___y_1654_ = v___y_1664_;
v___y_1655_ = v___y_1665_;
v___y_1656_ = v___x_1668_;
goto v___jp_1652_;
}
}
v___jp_1669_:
{
uint64_t v___x_1675_; uint64_t v_encodedExponent_1676_; uint32_t v___x_1677_; uint64_t v___x_1678_; uint8_t v___x_1679_; 
v___x_1675_ = 171ULL;
v_encodedExponent_1676_ = lean_uint64_sub(v___y_1671_, v___x_1675_);
v___x_1677_ = lean_uint64_to_uint32(v_encodedExponent_1676_);
v___x_1678_ = 8388608ULL;
v___x_1679_ = lean_uint64_dec_lt(v___y_1674_, v___x_1678_);
if (v___x_1679_ == 0)
{
uint64_t v___x_1680_; uint32_t v___x_1681_; 
v___x_1680_ = lean_uint64_sub(v___y_1674_, v___x_1678_);
v___x_1681_ = lean_uint64_to_uint32(v___x_1680_);
v___y_1663_ = v___y_1670_;
v___y_1664_ = v___x_1677_;
v___y_1665_ = v___y_1672_;
v___y_1666_ = v___x_1681_;
goto v___jp_1662_;
}
else
{
uint32_t v___x_1682_; 
v___x_1682_ = lean_uint64_to_uint32(v___y_1673_);
v___y_1663_ = v___y_1670_;
v___y_1664_ = v___x_1677_;
v___y_1665_ = v___y_1672_;
v___y_1666_ = v___x_1682_;
goto v___jp_1662_;
}
}
v___jp_1683_:
{
uint64_t v___x_1690_; uint8_t v___x_1691_; 
v___x_1690_ = 425ULL;
v___x_1691_ = lean_uint64_dec_lt(v___x_1690_, v___y_1689_);
if (v___x_1691_ == 0)
{
if (v___y_1688_ == 0)
{
v___y_1670_ = v___y_1684_;
v___y_1671_ = v___y_1689_;
v___y_1672_ = v___y_1686_;
v___y_1673_ = v___y_1687_;
v___y_1674_ = v___y_1685_;
goto v___jp_1669_;
}
else
{
uint64_t v___x_1692_; 
v___x_1692_ = 8388608ULL;
v___y_1670_ = v___y_1684_;
v___y_1671_ = v___y_1689_;
v___y_1672_ = v___y_1686_;
v___y_1673_ = v___y_1687_;
v___y_1674_ = v___x_1692_;
goto v___jp_1669_;
}
}
else
{
if (v___y_1684_ == 0)
{
uint32_t v___x_1693_; 
v___x_1693_ = 2139095040;
return v___x_1693_;
}
else
{
uint32_t v___x_1694_; 
v___x_1694_ = 4286578688;
return v___x_1694_;
}
}
}
v___jp_1695_:
{
uint64_t v___x_1701_; uint8_t v_carry_1702_; 
v___x_1701_ = 16777216ULL;
v_carry_1702_ = lean_uint64_dec_eq(v___y_1700_, v___x_1701_);
if (v_carry_1702_ == 0)
{
v___y_1684_ = v___y_1696_;
v___y_1685_ = v___y_1700_;
v___y_1686_ = v___y_1698_;
v___y_1687_ = v___y_1699_;
v___y_1688_ = v_carry_1702_;
v___y_1689_ = v___y_1697_;
goto v___jp_1683_;
}
else
{
uint64_t v___x_1703_; uint64_t v___x_1704_; 
v___x_1703_ = 1ULL;
v___x_1704_ = lean_uint64_add(v___y_1697_, v___x_1703_);
v___y_1684_ = v___y_1696_;
v___y_1685_ = v___y_1700_;
v___y_1686_ = v___y_1698_;
v___y_1687_ = v___y_1699_;
v___y_1688_ = v_carry_1702_;
v___y_1689_ = v___x_1704_;
goto v___jp_1683_;
}
}
v___jp_1705_:
{
uint64_t v_position_1712_; uint64_t v___x_1713_; uint8_t v___x_1714_; 
v_position_1712_ = lean_uint64_add(v___y_1711_, v___y_1710_);
v___x_1713_ = 172ULL;
v___x_1714_ = lean_uint64_dec_lt(v_position_1712_, v___x_1713_);
if (v___x_1714_ == 0)
{
uint64_t v___x_1715_; uint8_t v___x_1716_; 
v___x_1715_ = 23ULL;
v___x_1716_ = lean_uint64_dec_lt(v___y_1711_, v___x_1715_);
if (v___x_1716_ == 0)
{
uint64_t v___x_1717_; uint8_t v___x_1718_; 
v___x_1717_ = lean_uint64_sub(v___y_1711_, v___x_1715_);
v___x_1718_ = lean_uint64_dec_eq(v___x_1717_, v___y_1709_);
if (v___x_1718_ == 0)
{
uint64_t v___x_1719_; uint8_t v___x_1720_; 
v___x_1719_ = 64ULL;
v___x_1720_ = lean_uint64_dec_lt(v___x_1717_, v___x_1719_);
if (v___x_1720_ == 0)
{
uint8_t v___x_1721_; 
v___x_1721_ = lean_uint64_dec_eq(v___x_1717_, v___x_1719_);
if (v___x_1721_ == 0)
{
v___y_1696_ = v___y_1706_;
v___y_1697_ = v_position_1712_;
v___y_1698_ = v___y_1707_;
v___y_1699_ = v___y_1709_;
v___y_1700_ = v___y_1709_;
goto v___jp_1695_;
}
else
{
uint64_t v___x_1722_; uint8_t v___x_1723_; 
v___x_1722_ = 9223372036854775808ULL;
v___x_1723_ = lean_uint64_dec_lt(v___x_1722_, v___y_1708_);
if (v___x_1723_ == 0)
{
v___y_1696_ = v___y_1706_;
v___y_1697_ = v_position_1712_;
v___y_1698_ = v___y_1707_;
v___y_1699_ = v___y_1709_;
v___y_1700_ = v___y_1709_;
goto v___jp_1695_;
}
else
{
uint64_t v___x_1724_; 
v___x_1724_ = 1ULL;
v___y_1696_ = v___y_1706_;
v___y_1697_ = v_position_1712_;
v___y_1698_ = v___y_1707_;
v___y_1699_ = v___y_1709_;
v___y_1700_ = v___x_1724_;
goto v___jp_1695_;
}
}
}
else
{
uint64_t v_quotient_1725_; uint64_t v___x_1726_; uint64_t v___x_1727_; uint64_t v___x_1728_; uint64_t v_remainder_1729_; uint64_t v___x_1730_; uint64_t v_half_1731_; uint8_t v___x_1732_; 
v_quotient_1725_ = lean_uint64_shift_right(v___y_1708_, v___x_1717_);
v___x_1726_ = 1ULL;
v___x_1727_ = lean_uint64_shift_left(v___x_1726_, v___x_1717_);
v___x_1728_ = lean_uint64_sub(v___x_1727_, v___x_1726_);
v_remainder_1729_ = lean_uint64_land(v___y_1708_, v___x_1728_);
v___x_1730_ = lean_uint64_sub(v___x_1717_, v___x_1726_);
v_half_1731_ = lean_uint64_shift_left(v___x_1726_, v___x_1730_);
v___x_1732_ = lean_uint64_dec_lt(v_remainder_1729_, v_half_1731_);
if (v___x_1732_ == 0)
{
uint8_t v___x_1733_; 
v___x_1733_ = lean_uint64_dec_lt(v_half_1731_, v_remainder_1729_);
if (v___x_1733_ == 0)
{
uint64_t v___x_1734_; uint8_t v___x_1735_; 
v___x_1734_ = lean_uint64_land(v_quotient_1725_, v___x_1726_);
v___x_1735_ = lean_uint64_dec_eq(v___x_1734_, v___y_1709_);
if (v___x_1735_ == 0)
{
uint64_t v___x_1736_; 
v___x_1736_ = lean_uint64_add(v_quotient_1725_, v___x_1726_);
v___y_1696_ = v___y_1706_;
v___y_1697_ = v_position_1712_;
v___y_1698_ = v___y_1707_;
v___y_1699_ = v___y_1709_;
v___y_1700_ = v___x_1736_;
goto v___jp_1695_;
}
else
{
v___y_1696_ = v___y_1706_;
v___y_1697_ = v_position_1712_;
v___y_1698_ = v___y_1707_;
v___y_1699_ = v___y_1709_;
v___y_1700_ = v_quotient_1725_;
goto v___jp_1695_;
}
}
else
{
uint64_t v___x_1737_; 
v___x_1737_ = lean_uint64_add(v_quotient_1725_, v___x_1726_);
v___y_1696_ = v___y_1706_;
v___y_1697_ = v_position_1712_;
v___y_1698_ = v___y_1707_;
v___y_1699_ = v___y_1709_;
v___y_1700_ = v___x_1737_;
goto v___jp_1695_;
}
}
else
{
v___y_1696_ = v___y_1706_;
v___y_1697_ = v_position_1712_;
v___y_1698_ = v___y_1707_;
v___y_1699_ = v___y_1709_;
v___y_1700_ = v_quotient_1725_;
goto v___jp_1695_;
}
}
}
else
{
v___y_1696_ = v___y_1706_;
v___y_1697_ = v_position_1712_;
v___y_1698_ = v___y_1707_;
v___y_1699_ = v___y_1709_;
v___y_1700_ = v___y_1708_;
goto v___jp_1695_;
}
}
else
{
uint64_t v___x_1738_; uint64_t v___x_1739_; 
v___x_1738_ = lean_uint64_sub(v___x_1715_, v___y_1711_);
v___x_1739_ = lean_uint64_shift_left(v___y_1708_, v___x_1738_);
v___y_1696_ = v___y_1706_;
v___y_1697_ = v_position_1712_;
v___y_1698_ = v___y_1707_;
v___y_1699_ = v___y_1709_;
v___y_1700_ = v___x_1739_;
goto v___jp_1695_;
}
}
else
{
uint64_t v___x_1740_; uint8_t v___x_1741_; 
v___x_1740_ = 149ULL;
v___x_1741_ = lean_uint64_dec_lt(v___y_1710_, v___x_1740_);
if (v___x_1741_ == 0)
{
uint64_t v___x_1742_; uint64_t v___x_1743_; 
v___x_1742_ = lean_uint64_sub(v___y_1710_, v___x_1740_);
v___x_1743_ = lean_uint64_shift_left(v___y_1708_, v___x_1742_);
v___y_1506_ = v___y_1706_;
v___y_1507_ = v___y_1707_;
v___y_1508_ = v___y_1709_;
v___y_1509_ = v___x_1743_;
goto v___jp_1505_;
}
else
{
uint64_t v___x_1744_; uint8_t v___x_1745_; 
v___x_1744_ = lean_uint64_sub(v___x_1740_, v___y_1710_);
v___x_1745_ = lean_uint64_dec_eq(v___x_1744_, v___y_1709_);
if (v___x_1745_ == 0)
{
uint64_t v___x_1746_; uint8_t v___x_1747_; 
v___x_1746_ = 64ULL;
v___x_1747_ = lean_uint64_dec_lt(v___x_1744_, v___x_1746_);
if (v___x_1747_ == 0)
{
uint8_t v___x_1748_; 
v___x_1748_ = lean_uint64_dec_eq(v___x_1744_, v___x_1746_);
if (v___x_1748_ == 0)
{
v___y_1506_ = v___y_1706_;
v___y_1507_ = v___y_1707_;
v___y_1508_ = v___y_1709_;
v___y_1509_ = v___y_1709_;
goto v___jp_1505_;
}
else
{
uint64_t v___x_1749_; uint8_t v___x_1750_; 
v___x_1749_ = 9223372036854775808ULL;
v___x_1750_ = lean_uint64_dec_lt(v___x_1749_, v___y_1708_);
if (v___x_1750_ == 0)
{
v___y_1506_ = v___y_1706_;
v___y_1507_ = v___y_1707_;
v___y_1508_ = v___y_1709_;
v___y_1509_ = v___y_1709_;
goto v___jp_1505_;
}
else
{
uint64_t v___x_1751_; 
v___x_1751_ = 1ULL;
v___y_1506_ = v___y_1706_;
v___y_1507_ = v___y_1707_;
v___y_1508_ = v___y_1709_;
v___y_1509_ = v___x_1751_;
goto v___jp_1505_;
}
}
}
else
{
uint64_t v_quotient_1752_; uint64_t v___x_1753_; uint64_t v___x_1754_; uint64_t v___x_1755_; uint64_t v_remainder_1756_; uint64_t v___x_1757_; uint64_t v_half_1758_; uint8_t v___x_1759_; 
v_quotient_1752_ = lean_uint64_shift_right(v___y_1708_, v___x_1744_);
v___x_1753_ = 1ULL;
v___x_1754_ = lean_uint64_shift_left(v___x_1753_, v___x_1744_);
v___x_1755_ = lean_uint64_sub(v___x_1754_, v___x_1753_);
v_remainder_1756_ = lean_uint64_land(v___y_1708_, v___x_1755_);
v___x_1757_ = lean_uint64_sub(v___x_1744_, v___x_1753_);
v_half_1758_ = lean_uint64_shift_left(v___x_1753_, v___x_1757_);
v___x_1759_ = lean_uint64_dec_lt(v_remainder_1756_, v_half_1758_);
if (v___x_1759_ == 0)
{
uint8_t v___x_1760_; 
v___x_1760_ = lean_uint64_dec_lt(v_half_1758_, v_remainder_1756_);
if (v___x_1760_ == 0)
{
uint64_t v___x_1761_; uint8_t v___x_1762_; 
v___x_1761_ = lean_uint64_land(v_quotient_1752_, v___x_1753_);
v___x_1762_ = lean_uint64_dec_eq(v___x_1761_, v___y_1709_);
if (v___x_1762_ == 0)
{
uint64_t v___x_1763_; 
v___x_1763_ = lean_uint64_add(v_quotient_1752_, v___x_1753_);
v___y_1506_ = v___y_1706_;
v___y_1507_ = v___y_1707_;
v___y_1508_ = v___y_1709_;
v___y_1509_ = v___x_1763_;
goto v___jp_1505_;
}
else
{
v___y_1506_ = v___y_1706_;
v___y_1507_ = v___y_1707_;
v___y_1508_ = v___y_1709_;
v___y_1509_ = v_quotient_1752_;
goto v___jp_1505_;
}
}
else
{
uint64_t v___x_1764_; 
v___x_1764_ = lean_uint64_add(v_quotient_1752_, v___x_1753_);
v___y_1506_ = v___y_1706_;
v___y_1507_ = v___y_1707_;
v___y_1508_ = v___y_1709_;
v___y_1509_ = v___x_1764_;
goto v___jp_1505_;
}
}
else
{
v___y_1506_ = v___y_1706_;
v___y_1507_ = v___y_1707_;
v___y_1508_ = v___y_1709_;
v___y_1509_ = v_quotient_1752_;
goto v___jp_1505_;
}
}
}
else
{
v___y_1506_ = v___y_1706_;
v___y_1507_ = v___y_1707_;
v___y_1508_ = v___y_1709_;
v___y_1509_ = v___y_1708_;
goto v___jp_1505_;
}
}
}
}
v___jp_1765_:
{
uint64_t v___x_1773_; uint64_t v___x_1774_; uint8_t v___x_1775_; 
v___x_1773_ = 1ULL;
v___x_1774_ = lean_uint64_shift_right(v___y_1767_, v___x_1773_);
v___x_1775_ = lean_uint64_dec_eq(v___x_1774_, v___y_1771_);
if (v___x_1775_ == 0)
{
uint64_t v___x_1776_; 
v___x_1776_ = lean_uint64_add(v___y_1772_, v___x_1773_);
v___y_1706_ = v___y_1766_;
v___y_1707_ = v___y_1768_;
v___y_1708_ = v___y_1770_;
v___y_1709_ = v___y_1771_;
v___y_1710_ = v___y_1769_;
v___y_1711_ = v___x_1776_;
goto v___jp_1705_;
}
else
{
v___y_1706_ = v___y_1766_;
v___y_1707_ = v___y_1768_;
v___y_1708_ = v___y_1770_;
v___y_1709_ = v___y_1771_;
v___y_1710_ = v___y_1769_;
v___y_1711_ = v___y_1772_;
goto v___jp_1705_;
}
}
v___jp_1777_:
{
uint64_t v___x_1787_; uint8_t v___x_1788_; 
v___x_1787_ = lean_uint64_shift_right(v___y_1780_, v___y_1781_);
v___x_1788_ = lean_uint64_dec_eq(v___x_1787_, v___y_1783_);
if (v___x_1788_ == 0)
{
uint64_t v___x_1789_; 
v___x_1789_ = lean_uint64_add(v___y_1779_, v___y_1781_);
v___y_1766_ = v___y_1778_;
v___y_1767_ = v___y_1786_;
v___y_1768_ = v___y_1782_;
v___y_1769_ = v___y_1785_;
v___y_1770_ = v___y_1784_;
v___y_1771_ = v___y_1783_;
v___y_1772_ = v___x_1789_;
goto v___jp_1765_;
}
else
{
v___y_1766_ = v___y_1778_;
v___y_1767_ = v___y_1786_;
v___y_1768_ = v___y_1782_;
v___y_1769_ = v___y_1785_;
v___y_1770_ = v___y_1784_;
v___y_1771_ = v___y_1783_;
v___y_1772_ = v___y_1779_;
goto v___jp_1765_;
}
}
v___jp_1790_:
{
uint64_t v___x_1798_; uint64_t v___x_1799_; uint8_t v___x_1800_; 
v___x_1798_ = 2ULL;
v___x_1799_ = lean_uint64_shift_right(v___y_1792_, v___x_1798_);
v___x_1800_ = lean_uint64_dec_eq(v___x_1799_, v___y_1796_);
if (v___x_1800_ == 0)
{
v___y_1778_ = v___y_1791_;
v___y_1779_ = v___y_1797_;
v___y_1780_ = v___y_1792_;
v___y_1781_ = v___x_1798_;
v___y_1782_ = v___y_1793_;
v___y_1783_ = v___y_1796_;
v___y_1784_ = v___y_1795_;
v___y_1785_ = v___y_1794_;
v___y_1786_ = v___x_1799_;
goto v___jp_1777_;
}
else
{
v___y_1778_ = v___y_1791_;
v___y_1779_ = v___y_1797_;
v___y_1780_ = v___y_1792_;
v___y_1781_ = v___x_1798_;
v___y_1782_ = v___y_1793_;
v___y_1783_ = v___y_1796_;
v___y_1784_ = v___y_1795_;
v___y_1785_ = v___y_1794_;
v___y_1786_ = v___y_1792_;
goto v___jp_1777_;
}
}
v___jp_1801_:
{
uint64_t v___x_1811_; uint8_t v___x_1812_; 
v___x_1811_ = lean_uint64_shift_right(v___y_1806_, v___y_1804_);
v___x_1812_ = lean_uint64_dec_eq(v___x_1811_, v___y_1807_);
if (v___x_1812_ == 0)
{
uint64_t v___x_1813_; 
v___x_1813_ = lean_uint64_add(v___y_1803_, v___y_1804_);
v___y_1791_ = v___y_1802_;
v___y_1792_ = v___y_1810_;
v___y_1793_ = v___y_1805_;
v___y_1794_ = v___y_1809_;
v___y_1795_ = v___y_1808_;
v___y_1796_ = v___y_1807_;
v___y_1797_ = v___x_1813_;
goto v___jp_1790_;
}
else
{
v___y_1791_ = v___y_1802_;
v___y_1792_ = v___y_1810_;
v___y_1793_ = v___y_1805_;
v___y_1794_ = v___y_1809_;
v___y_1795_ = v___y_1808_;
v___y_1796_ = v___y_1807_;
v___y_1797_ = v___y_1803_;
goto v___jp_1790_;
}
}
v___jp_1814_:
{
uint64_t v___x_1822_; uint64_t v___x_1823_; uint8_t v___x_1824_; 
v___x_1822_ = 4ULL;
v___x_1823_ = lean_uint64_shift_right(v___y_1820_, v___x_1822_);
v___x_1824_ = lean_uint64_dec_eq(v___x_1823_, v___y_1819_);
if (v___x_1824_ == 0)
{
v___y_1802_ = v___y_1815_;
v___y_1803_ = v___y_1821_;
v___y_1804_ = v___x_1822_;
v___y_1805_ = v___y_1816_;
v___y_1806_ = v___y_1820_;
v___y_1807_ = v___y_1819_;
v___y_1808_ = v___y_1818_;
v___y_1809_ = v___y_1817_;
v___y_1810_ = v___x_1823_;
goto v___jp_1801_;
}
else
{
v___y_1802_ = v___y_1815_;
v___y_1803_ = v___y_1821_;
v___y_1804_ = v___x_1822_;
v___y_1805_ = v___y_1816_;
v___y_1806_ = v___y_1820_;
v___y_1807_ = v___y_1819_;
v___y_1808_ = v___y_1818_;
v___y_1809_ = v___y_1817_;
v___y_1810_ = v___y_1820_;
goto v___jp_1801_;
}
}
v___jp_1825_:
{
uint64_t v___x_1835_; uint8_t v___x_1836_; 
v___x_1835_ = lean_uint64_shift_right(v___y_1827_, v___y_1826_);
v___x_1836_ = lean_uint64_dec_eq(v___x_1835_, v___y_1831_);
if (v___x_1836_ == 0)
{
uint64_t v___x_1837_; 
v___x_1837_ = lean_uint64_add(v___y_1829_, v___y_1826_);
v___y_1815_ = v___y_1828_;
v___y_1816_ = v___y_1830_;
v___y_1817_ = v___y_1833_;
v___y_1818_ = v___y_1832_;
v___y_1819_ = v___y_1831_;
v___y_1820_ = v___y_1834_;
v___y_1821_ = v___x_1837_;
goto v___jp_1814_;
}
else
{
v___y_1815_ = v___y_1828_;
v___y_1816_ = v___y_1830_;
v___y_1817_ = v___y_1833_;
v___y_1818_ = v___y_1832_;
v___y_1819_ = v___y_1831_;
v___y_1820_ = v___y_1834_;
v___y_1821_ = v___y_1829_;
goto v___jp_1814_;
}
}
v___jp_1838_:
{
uint64_t v___x_1846_; uint64_t v___x_1847_; uint8_t v___x_1848_; 
v___x_1846_ = 8ULL;
v___x_1847_ = lean_uint64_shift_right(v___y_1839_, v___x_1846_);
v___x_1848_ = lean_uint64_dec_eq(v___x_1847_, v___y_1844_);
if (v___x_1848_ == 0)
{
v___y_1826_ = v___x_1846_;
v___y_1827_ = v___y_1839_;
v___y_1828_ = v___y_1840_;
v___y_1829_ = v___y_1845_;
v___y_1830_ = v___y_1841_;
v___y_1831_ = v___y_1844_;
v___y_1832_ = v___y_1843_;
v___y_1833_ = v___y_1842_;
v___y_1834_ = v___x_1847_;
goto v___jp_1825_;
}
else
{
v___y_1826_ = v___x_1846_;
v___y_1827_ = v___y_1839_;
v___y_1828_ = v___y_1840_;
v___y_1829_ = v___y_1845_;
v___y_1830_ = v___y_1841_;
v___y_1831_ = v___y_1844_;
v___y_1832_ = v___y_1843_;
v___y_1833_ = v___y_1842_;
v___y_1834_ = v___y_1839_;
goto v___jp_1825_;
}
}
v___jp_1849_:
{
uint64_t v___x_1859_; uint8_t v___x_1860_; 
v___x_1859_ = lean_uint64_shift_right(v___y_1851_, v___y_1850_);
v___x_1860_ = lean_uint64_dec_eq(v___x_1859_, v___y_1855_);
if (v___x_1860_ == 0)
{
uint64_t v___x_1861_; 
v___x_1861_ = lean_uint64_add(v___y_1853_, v___y_1850_);
v___y_1839_ = v___y_1858_;
v___y_1840_ = v___y_1852_;
v___y_1841_ = v___y_1854_;
v___y_1842_ = v___y_1857_;
v___y_1843_ = v___y_1856_;
v___y_1844_ = v___y_1855_;
v___y_1845_ = v___x_1861_;
goto v___jp_1838_;
}
else
{
v___y_1839_ = v___y_1858_;
v___y_1840_ = v___y_1852_;
v___y_1841_ = v___y_1854_;
v___y_1842_ = v___y_1857_;
v___y_1843_ = v___y_1856_;
v___y_1844_ = v___y_1855_;
v___y_1845_ = v___y_1853_;
goto v___jp_1838_;
}
}
v___jp_1862_:
{
uint64_t v___x_1870_; uint64_t v___x_1871_; uint8_t v___x_1872_; 
v___x_1870_ = 16ULL;
v___x_1871_ = lean_uint64_shift_right(v___y_1863_, v___x_1870_);
v___x_1872_ = lean_uint64_dec_eq(v___x_1871_, v___y_1868_);
if (v___x_1872_ == 0)
{
v___y_1850_ = v___x_1870_;
v___y_1851_ = v___y_1863_;
v___y_1852_ = v___y_1864_;
v___y_1853_ = v___y_1869_;
v___y_1854_ = v___y_1865_;
v___y_1855_ = v___y_1868_;
v___y_1856_ = v___y_1867_;
v___y_1857_ = v___y_1866_;
v___y_1858_ = v___x_1871_;
goto v___jp_1849_;
}
else
{
v___y_1850_ = v___x_1870_;
v___y_1851_ = v___y_1863_;
v___y_1852_ = v___y_1864_;
v___y_1853_ = v___y_1869_;
v___y_1854_ = v___y_1865_;
v___y_1855_ = v___y_1868_;
v___y_1856_ = v___y_1867_;
v___y_1857_ = v___y_1866_;
v___y_1858_ = v___y_1863_;
goto v___jp_1849_;
}
}
v___jp_1873_:
{
uint64_t v___x_1881_; uint8_t v___x_1882_; 
v___x_1881_ = lean_uint64_shift_right(v___y_1878_, v___y_1875_);
v___x_1882_ = lean_uint64_dec_eq(v___x_1881_, v___y_1877_);
if (v___x_1882_ == 0)
{
v___y_1863_ = v___y_1880_;
v___y_1864_ = v___y_1874_;
v___y_1865_ = v___y_1876_;
v___y_1866_ = v___y_1879_;
v___y_1867_ = v___y_1878_;
v___y_1868_ = v___y_1877_;
v___y_1869_ = v___y_1875_;
goto v___jp_1862_;
}
else
{
v___y_1863_ = v___y_1880_;
v___y_1864_ = v___y_1874_;
v___y_1865_ = v___y_1876_;
v___y_1866_ = v___y_1879_;
v___y_1867_ = v___y_1878_;
v___y_1868_ = v___y_1877_;
v___y_1869_ = v___y_1877_;
goto v___jp_1862_;
}
}
v___jp_1883_:
{
uint64_t v___x_1888_; uint8_t v___x_1889_; 
v___x_1888_ = 0ULL;
v___x_1889_ = lean_uint64_dec_eq(v___y_1887_, v___x_1888_);
if (v___x_1889_ == 0)
{
uint64_t v___x_1890_; uint64_t v___x_1891_; uint8_t v___x_1892_; 
v___x_1890_ = 32ULL;
v___x_1891_ = lean_uint64_shift_right(v___y_1887_, v___x_1890_);
v___x_1892_ = lean_uint64_dec_eq(v___x_1891_, v___x_1888_);
if (v___x_1892_ == 0)
{
v___y_1874_ = v___y_1884_;
v___y_1875_ = v___x_1890_;
v___y_1876_ = v___y_1885_;
v___y_1877_ = v___x_1888_;
v___y_1878_ = v___y_1887_;
v___y_1879_ = v___y_1886_;
v___y_1880_ = v___x_1891_;
goto v___jp_1873_;
}
else
{
v___y_1874_ = v___y_1884_;
v___y_1875_ = v___x_1890_;
v___y_1876_ = v___y_1885_;
v___y_1877_ = v___x_1888_;
v___y_1878_ = v___y_1887_;
v___y_1879_ = v___y_1886_;
v___y_1880_ = v___y_1887_;
goto v___jp_1873_;
}
}
else
{
if (v___y_1884_ == 0)
{
uint32_t v___x_1893_; 
v___x_1893_ = 0;
return v___x_1893_;
}
else
{
uint32_t v___x_1894_; 
v___x_1894_ = 2147483648;
return v___x_1894_;
}
}
}
v___jp_1895_:
{
uint64_t v___x_1902_; uint64_t v___x_1903_; uint64_t v___x_1904_; uint8_t v___x_1905_; 
v___x_1902_ = lean_uint64_mul(v___y_1897_, v___y_1896_);
v___x_1903_ = lean_uint64_add(v___y_1899_, v___y_1901_);
v___x_1904_ = 281474976710656ULL;
v___x_1905_ = lean_uint64_dec_lt(v___x_1902_, v___x_1904_);
if (v___x_1905_ == 0)
{
v___y_1884_ = v___y_1898_;
v___y_1885_ = v___y_1900_;
v___y_1886_ = v___x_1903_;
v___y_1887_ = v___x_1902_;
goto v___jp_1883_;
}
else
{
uint64_t v___x_1906_; uint8_t v___x_1907_; 
v___x_1906_ = 123ULL;
v___x_1907_ = lean_uint64_dec_le(v___x_1903_, v___x_1906_);
if (v___x_1907_ == 0)
{
v___y_1884_ = v___y_1898_;
v___y_1885_ = v___y_1900_;
v___y_1886_ = v___x_1903_;
v___y_1887_ = v___x_1902_;
goto v___jp_1883_;
}
else
{
uint64_t v___x_1908_; uint8_t v___x_1909_; 
v___x_1908_ = 0ULL;
v___x_1909_ = lean_uint64_dec_eq(v___x_1902_, v___x_1908_);
if (v___x_1909_ == 0)
{
uint64_t v___x_1910_; uint64_t v___x_1911_; uint8_t v___x_1912_; 
v___x_1910_ = 149ULL;
v___x_1911_ = lean_uint64_sub(v___x_1910_, v___x_1903_);
v___x_1912_ = lean_uint64_dec_eq(v___x_1911_, v___x_1908_);
if (v___x_1912_ == 0)
{
uint64_t v___x_1913_; uint8_t v___x_1914_; 
v___x_1913_ = 64ULL;
v___x_1914_ = lean_uint64_dec_lt(v___x_1911_, v___x_1913_);
if (v___x_1914_ == 0)
{
uint8_t v___x_1915_; 
v___x_1915_ = lean_uint64_dec_eq(v___x_1911_, v___x_1913_);
if (v___x_1915_ == 0)
{
v___y_1527_ = v___y_1898_;
v___y_1528_ = v___x_1908_;
v___y_1529_ = v___y_1900_;
v___y_1530_ = v___x_1908_;
goto v___jp_1526_;
}
else
{
uint64_t v___x_1916_; uint8_t v___x_1917_; 
v___x_1916_ = 9223372036854775808ULL;
v___x_1917_ = lean_uint64_dec_lt(v___x_1916_, v___x_1902_);
if (v___x_1917_ == 0)
{
v___y_1527_ = v___y_1898_;
v___y_1528_ = v___x_1908_;
v___y_1529_ = v___y_1900_;
v___y_1530_ = v___x_1908_;
goto v___jp_1526_;
}
else
{
uint64_t v___x_1918_; 
v___x_1918_ = 1ULL;
v___y_1527_ = v___y_1898_;
v___y_1528_ = v___x_1908_;
v___y_1529_ = v___y_1900_;
v___y_1530_ = v___x_1918_;
goto v___jp_1526_;
}
}
}
else
{
uint64_t v_quotient_1919_; uint64_t v___x_1920_; uint64_t v___x_1921_; uint64_t v___x_1922_; uint64_t v_remainder_1923_; uint64_t v___x_1924_; uint64_t v_half_1925_; uint8_t v___x_1926_; 
v_quotient_1919_ = lean_uint64_shift_right(v___x_1902_, v___x_1911_);
v___x_1920_ = 1ULL;
v___x_1921_ = lean_uint64_shift_left(v___x_1920_, v___x_1911_);
v___x_1922_ = lean_uint64_sub(v___x_1921_, v___x_1920_);
v_remainder_1923_ = lean_uint64_land(v___x_1902_, v___x_1922_);
v___x_1924_ = lean_uint64_sub(v___x_1911_, v___x_1920_);
v_half_1925_ = lean_uint64_shift_left(v___x_1920_, v___x_1924_);
v___x_1926_ = lean_uint64_dec_lt(v_remainder_1923_, v_half_1925_);
if (v___x_1926_ == 0)
{
uint8_t v___x_1927_; 
v___x_1927_ = lean_uint64_dec_lt(v_half_1925_, v_remainder_1923_);
if (v___x_1927_ == 0)
{
uint64_t v___x_1928_; uint8_t v___x_1929_; 
v___x_1928_ = lean_uint64_land(v_quotient_1919_, v___x_1920_);
v___x_1929_ = lean_uint64_dec_eq(v___x_1928_, v___x_1908_);
if (v___x_1929_ == 0)
{
uint64_t v___x_1930_; 
v___x_1930_ = lean_uint64_add(v_quotient_1919_, v___x_1920_);
v___y_1527_ = v___y_1898_;
v___y_1528_ = v___x_1908_;
v___y_1529_ = v___y_1900_;
v___y_1530_ = v___x_1930_;
goto v___jp_1526_;
}
else
{
v___y_1527_ = v___y_1898_;
v___y_1528_ = v___x_1908_;
v___y_1529_ = v___y_1900_;
v___y_1530_ = v_quotient_1919_;
goto v___jp_1526_;
}
}
else
{
uint64_t v___x_1931_; 
v___x_1931_ = lean_uint64_add(v_quotient_1919_, v___x_1920_);
v___y_1527_ = v___y_1898_;
v___y_1528_ = v___x_1908_;
v___y_1529_ = v___y_1900_;
v___y_1530_ = v___x_1931_;
goto v___jp_1526_;
}
}
else
{
v___y_1527_ = v___y_1898_;
v___y_1528_ = v___x_1908_;
v___y_1529_ = v___y_1900_;
v___y_1530_ = v_quotient_1919_;
goto v___jp_1526_;
}
}
}
else
{
v___y_1527_ = v___y_1898_;
v___y_1528_ = v___x_1908_;
v___y_1529_ = v___y_1900_;
v___y_1530_ = v___x_1902_;
goto v___jp_1526_;
}
}
else
{
if (v___y_1898_ == 0)
{
uint32_t v___x_1932_; 
v___x_1932_ = 0;
return v___x_1932_;
}
else
{
uint32_t v___x_1933_; 
v___x_1933_ = 2147483648;
return v___x_1933_;
}
}
}
}
}
v___jp_1937_:
{
uint64_t v___x_1943_; uint64_t v___x_1944_; uint8_t v___x_1945_; 
v___x_1943_ = lean_uint32_to_uint64(v_ey_1936_);
v___x_1944_ = 0ULL;
v___x_1945_ = lean_uint64_dec_eq(v___x_1943_, v___x_1944_);
if (v___x_1945_ == 0)
{
uint64_t v___x_1946_; uint64_t v___x_1947_; 
v___x_1946_ = 1ULL;
v___x_1947_ = lean_uint64_sub(v___x_1943_, v___x_1946_);
v___y_1896_ = v___y_1938_;
v___y_1897_ = v___y_1939_;
v___y_1898_ = v___y_1940_;
v___y_1899_ = v___y_1942_;
v___y_1900_ = v___y_1941_;
v___y_1901_ = v___x_1947_;
goto v___jp_1895_;
}
else
{
v___y_1896_ = v___y_1938_;
v___y_1897_ = v___y_1939_;
v___y_1898_ = v___y_1940_;
v___y_1899_ = v___y_1942_;
v___y_1900_ = v___y_1941_;
v___y_1901_ = v___x_1944_;
goto v___jp_1895_;
}
}
v___jp_1948_:
{
uint64_t v___x_1953_; uint64_t v___x_1954_; uint8_t v___x_1955_; 
v___x_1953_ = lean_uint32_to_uint64(v_ex_1934_);
v___x_1954_ = 0ULL;
v___x_1955_ = lean_uint64_dec_eq(v___x_1953_, v___x_1954_);
if (v___x_1955_ == 0)
{
uint64_t v___x_1956_; uint64_t v___x_1957_; 
v___x_1956_ = 1ULL;
v___x_1957_ = lean_uint64_sub(v___x_1953_, v___x_1956_);
v___y_1938_ = v___y_1952_;
v___y_1939_ = v___y_1949_;
v___y_1940_ = v___y_1950_;
v___y_1941_ = v___y_1951_;
v___y_1942_ = v___x_1957_;
goto v___jp_1937_;
}
else
{
v___y_1938_ = v___y_1952_;
v___y_1939_ = v___y_1949_;
v___y_1940_ = v___y_1950_;
v___y_1941_ = v___y_1951_;
v___y_1942_ = v___x_1954_;
goto v___jp_1937_;
}
}
v___jp_1958_:
{
uint32_t v___x_1963_; uint8_t v___x_1964_; 
v___x_1963_ = 0;
v___x_1964_ = lean_uint32_dec_eq(v_ey_1936_, v___x_1963_);
if (v___x_1964_ == 0)
{
uint64_t v___x_1965_; uint64_t v___x_1966_; uint64_t v___x_1967_; 
v___x_1965_ = lean_uint32_to_uint64(v___y_1960_);
v___x_1966_ = 8388608ULL;
v___x_1967_ = lean_uint64_lor(v___x_1965_, v___x_1966_);
v___y_1949_ = v___y_1962_;
v___y_1950_ = v___y_1959_;
v___y_1951_ = v___y_1961_;
v___y_1952_ = v___x_1967_;
goto v___jp_1948_;
}
else
{
uint64_t v___x_1968_; 
v___x_1968_ = lean_uint32_to_uint64(v___y_1960_);
v___y_1949_ = v___y_1962_;
v___y_1950_ = v___y_1959_;
v___y_1951_ = v___y_1961_;
v___y_1952_ = v___x_1968_;
goto v___jp_1948_;
}
}
v___jp_1969_:
{
uint32_t v___x_1971_; uint32_t v_xFraction_1972_; uint32_t v_yFraction_1973_; uint32_t v___x_1974_; uint8_t v___x_1975_; 
v___x_1971_ = 8388607;
v_xFraction_1972_ = lean_uint32_land(v___y_1489_, v___x_1971_);
v_yFraction_1973_ = lean_uint32_land(v___y_1490_, v___x_1971_);
v___x_1974_ = 0;
v___x_1975_ = lean_uint32_dec_eq(v_ex_1934_, v___x_1974_);
if (v___x_1975_ == 0)
{
uint64_t v___x_1976_; uint64_t v___x_1977_; uint64_t v___x_1978_; 
v___x_1976_ = lean_uint32_to_uint64(v_xFraction_1972_);
v___x_1977_ = 8388608ULL;
v___x_1978_ = lean_uint64_lor(v___x_1976_, v___x_1977_);
v___y_1959_ = v___y_1970_;
v___y_1960_ = v_yFraction_1973_;
v___y_1961_ = v___x_1971_;
v___y_1962_ = v___x_1978_;
goto v___jp_1958_;
}
else
{
uint64_t v___x_1979_; 
v___x_1979_ = lean_uint32_to_uint64(v_xFraction_1972_);
v___y_1959_ = v___y_1970_;
v___y_1960_ = v_yFraction_1973_;
v___y_1961_ = v___x_1971_;
v___y_1962_ = v___x_1979_;
goto v___jp_1958_;
}
}
v___jp_1983_:
{
if (v___y_1985_ == 0)
{
v___y_1970_ = v___x_1982_;
goto v___jp_1969_;
}
else
{
v___y_1970_ = v___y_1984_;
goto v___jp_1969_;
}
}
v___jp_1986_:
{
if (v___y_1988_ == 0)
{
if (v___y_1989_ == 0)
{
v___y_1984_ = v___y_1987_;
v___y_1985_ = v___x_1982_;
goto v___jp_1983_;
}
else
{
v___y_1970_ = v___x_1982_;
goto v___jp_1969_;
}
}
else
{
v___y_1984_ = v___y_1987_;
v___y_1985_ = v___y_1989_;
goto v___jp_1983_;
}
}
v___jp_1990_:
{
uint32_t v___x_1993_; uint32_t v___x_1994_; uint32_t v___x_1995_; uint8_t v___x_1996_; 
v___x_1993_ = 2147483648;
v___x_1994_ = lean_uint32_land(v___y_1490_, v___x_1993_);
v___x_1995_ = 0;
v___x_1996_ = lean_uint32_dec_eq(v___x_1994_, v___x_1995_);
if (v___x_1996_ == 0)
{
v___y_1987_ = v___y_1991_;
v___y_1988_ = v___y_1992_;
v___y_1989_ = v___x_1982_;
goto v___jp_1986_;
}
else
{
v___y_1987_ = v___y_1991_;
v___y_1988_ = v___y_1992_;
v___y_1989_ = v___y_1991_;
goto v___jp_1986_;
}
}
v___jp_1997_:
{
if (v___y_1998_ == 0)
{
uint32_t v___x_1999_; uint32_t v___x_2000_; uint32_t v___x_2001_; uint8_t v___x_2002_; 
v___x_1999_ = 2147483648;
v___x_2000_ = lean_uint32_land(v___y_1489_, v___x_1999_);
v___x_2001_ = 0;
v___x_2002_ = lean_uint32_dec_eq(v___x_2000_, v___x_2001_);
if (v___x_2002_ == 0)
{
v___y_1991_ = v___y_1998_;
v___y_1992_ = v___x_1982_;
goto v___jp_1990_;
}
else
{
v___y_1991_ = v___y_1998_;
v___y_1992_ = v___y_1998_;
goto v___jp_1990_;
}
}
else
{
lean_object* v___x_2003_; lean_object* v___x_2004_; lean_object* v___x_2005_; uint32_t v___x_2006_; 
v___x_2003_ = lean_uint32_to_nat(v___y_1489_);
v___x_2004_ = lean_uint32_to_nat(v___y_1490_);
v___x_2005_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_2003_, v___x_2004_);
v___x_2006_ = lean_uint32_of_nat(v___x_2005_);
lean_dec(v___x_2005_);
return v___x_2006_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_runNativeAdd___lam__1___boxed(lean_object* v___y_2021_, lean_object* v___y_2022_){
_start:
{
uint32_t v___y_1758__boxed_2023_; uint32_t v___y_1759__boxed_2024_; uint32_t v_res_2025_; lean_object* v_r_2026_; 
v___y_1758__boxed_2023_ = lean_unbox_uint32(v___y_2021_);
lean_dec(v___y_2021_);
v___y_1759__boxed_2024_ = lean_unbox_uint32(v___y_2022_);
lean_dec(v___y_2022_);
v_res_2025_ = lp_competition_runNativeAdd___lam__1(v___y_1758__boxed_2023_, v___y_1759__boxed_2024_);
v_r_2026_ = lean_box_uint32(v_res_2025_);
return v_r_2026_;
}
}
LEAN_EXPORT lean_object* lp_competition_runNativeAdd(){
_start:
{
lean_object* v___f_2030_; lean_object* v___f_2031_; lean_object* v___x_2032_; lean_object* v___x_2033_; lean_object* v___x_2034_; 
v___f_2030_ = ((lean_object*)(lp_competition_runNativeAdd___closed__0));
v___f_2031_ = ((lean_object*)(lp_competition_runNativeAdd___closed__1));
v___x_2032_ = ((lean_object*)(lp_competition_runControl___closed__2));
v___x_2033_ = ((lean_object*)(lp_competition_runControl___closed__3));
v___x_2034_ = lp_competition_Bench_Suite_run(v___f_2030_, v___f_2031_, v___x_2032_, v___x_2033_);
return v___x_2034_;
}
}
LEAN_EXPORT lean_object* lp_competition_runNativeAdd___boxed(lean_object* v_a_2035_){
_start:
{
lean_object* v_res_2036_; 
v_res_2036_ = lp_competition_runNativeAdd();
return v_res_2036_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_2057_; lean_object* v___x_2058_; lean_object* v___x_2059_; uint8_t v___x_2060_; 
v___x_2057_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_2058_ = lean_io_getenv(v___x_2057_);
v___x_2059_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_2060_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_2058_, v___x_2059_);
if (v___x_2060_ == 0)
{
lean_object* v___x_2061_; uint8_t v___x_2062_; 
v___x_2061_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_2062_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_2058_, v___x_2061_);
if (v___x_2062_ == 0)
{
lean_object* v___x_2063_; uint8_t v___x_2064_; 
v___x_2063_ = ((lean_object*)(lp_competition_main___closed__6));
v___x_2064_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_2058_, v___x_2063_);
if (v___x_2064_ == 0)
{
lean_object* v___x_2065_; uint8_t v___x_2066_; 
v___x_2065_ = ((lean_object*)(lp_competition_main___closed__8));
v___x_2066_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_2058_, v___x_2065_);
if (v___x_2066_ == 0)
{
lean_object* v___x_2067_; uint8_t v___x_2068_; 
v___x_2067_ = ((lean_object*)(lp_competition_main___closed__10));
v___x_2068_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_2058_, v___x_2067_);
lean_dec(v___x_2058_);
if (v___x_2068_ == 0)
{
lean_object* v___x_2069_; lean_object* v___x_2070_; 
v___x_2069_ = ((lean_object*)(lp_competition_main___closed__12));
v___x_2070_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_2070_, 0, v___x_2069_);
return v___x_2070_;
}
else
{
lean_object* v___x_2071_; 
v___x_2071_ = lp_competition_runNativeAdd();
return v___x_2071_;
}
}
else
{
lean_object* v___x_2072_; 
lean_dec(v___x_2058_);
v___x_2072_ = lp_competition_runNativeCold();
return v___x_2072_;
}
}
else
{
lean_object* v___x_2073_; 
lean_dec(v___x_2058_);
v___x_2073_ = lp_competition_runNativeInline();
return v___x_2073_;
}
}
else
{
lean_object* v___x_2074_; 
lean_dec(v___x_2058_);
v___x_2074_ = lp_competition_runTh0();
return v___x_2074_;
}
}
else
{
lean_object* v___x_2075_; 
lean_dec(v___x_2058_);
v___x_2075_ = lp_competition_runControl();
return v___x_2075_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_2076_){
_start:
{
lean_object* v_res_2077_; 
v_res_2077_ = _lean_main();
return v_res_2077_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_competition_BenchFull(uint8_t builtin);
lean_object* initialize_competition_BenchSuite(uint8_t builtin);
lean_object* initialize_competition_Submission(uint8_t builtin);
void lean_initialize();
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_competition_R22NativeColdCostMain(uint8_t builtin) {
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
  res = initialize_competition_R22NativeColdCostMain(1 /* builtin */);
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
