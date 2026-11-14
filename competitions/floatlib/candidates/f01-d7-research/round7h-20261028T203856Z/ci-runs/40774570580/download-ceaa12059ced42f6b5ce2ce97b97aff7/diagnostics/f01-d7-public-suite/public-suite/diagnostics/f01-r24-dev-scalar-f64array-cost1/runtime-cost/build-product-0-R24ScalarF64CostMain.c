// Lean compiler output
// Module: R24ScalarF64CostMain
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
double lean_uint32_to_float(uint32_t);
double lean_float_array_get(lean_object*, lean_object*);
double lean_float_mul(double, double);
double lean_float_add(double, double);
float lean_float_to_float32(double);
extern lean_object* lp_competition_Submission_R24F64Add_nativeScales;
uint32_t lp_competition_Submission_R24F64Add_retainedAdd(uint32_t, uint32_t);
uint64_t lean_float_to_bits(double);
extern double l_instInhabitedFloat;
lean_object* lean_array_get_borrowed(lean_object*, lean_object*, lean_object*);
extern lean_object* lp_competition_Submission_R24F64Add_boxedScales;
lean_object* lean_io_getenv(lean_object*);
uint8_t l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(lean_object*, lean_object*);
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
LEAN_EXPORT uint32_t lp_competition_runF64Native___lam__0(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_runF64Native___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_runF64Native___lam__1(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_runF64Native___lam__1___boxed(lean_object*, lean_object*);
static const lean_closure_object lp_competition_runF64Native___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_runF64Native___lam__0___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runF64Native___closed__0 = (const lean_object*)&lp_competition_runF64Native___closed__0_value;
static const lean_closure_object lp_competition_runF64Native___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_runF64Native___lam__1___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runF64Native___closed__1 = (const lean_object*)&lp_competition_runF64Native___closed__1_value;
LEAN_EXPORT lean_object* lp_competition_runF64Native();
LEAN_EXPORT lean_object* lp_competition_runF64Native___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_competition_runF64Boxed___lam__0___boxed__const__1;
LEAN_EXPORT uint32_t lp_competition_runF64Boxed___lam__0(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_runF64Boxed___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_runF64Boxed___lam__1(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_runF64Boxed___lam__1___boxed(lean_object*, lean_object*);
static const lean_closure_object lp_competition_runF64Boxed___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_runF64Boxed___lam__0___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runF64Boxed___closed__0 = (const lean_object*)&lp_competition_runF64Boxed___closed__0_value;
static const lean_closure_object lp_competition_runF64Boxed___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_runF64Boxed___lam__1___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runF64Boxed___closed__1 = (const lean_object*)&lp_competition_runF64Boxed___closed__1_value;
LEAN_EXPORT lean_object* lp_competition_runF64Boxed();
LEAN_EXPORT lean_object* lp_competition_runF64Boxed___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_runF64Cast___lam__0(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_runF64Cast___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_runF64Cast___lam__1(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_runF64Cast___lam__1___boxed(lean_object*, lean_object*);
static const lean_closure_object lp_competition_runF64Cast___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_runF64Cast___lam__0___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runF64Cast___closed__0 = (const lean_object*)&lp_competition_runF64Cast___closed__0_value;
static const lean_closure_object lp_competition_runF64Cast___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_runF64Cast___lam__1___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runF64Cast___closed__1 = (const lean_object*)&lp_competition_runF64Cast___closed__1_value;
LEAN_EXPORT lean_object* lp_competition_runF64Cast();
LEAN_EXPORT lean_object* lp_competition_runF64Cast___boxed(lean_object*);
static const lean_string_object lp_competition_main___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 14, .m_capacity = 14, .m_length = 13, .m_data = "BENCH_VARIANT"};
static const lean_object* lp_competition_main___closed__0 = (const lean_object*)&lp_competition_main___closed__0_value;
static const lean_string_object lp_competition_main___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 8, .m_capacity = 8, .m_length = 7, .m_data = "control"};
static const lean_object* lp_competition_main___closed__1 = (const lean_object*)&lp_competition_main___closed__1_value;
static const lean_ctor_object lp_competition_main___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__1_value)}};
static const lean_object* lp_competition_main___closed__2 = (const lean_object*)&lp_competition_main___closed__2_value;
static const lean_string_object lp_competition_main___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 10, .m_capacity = 10, .m_length = 9, .m_data = "f64native"};
static const lean_object* lp_competition_main___closed__3 = (const lean_object*)&lp_competition_main___closed__3_value;
static const lean_ctor_object lp_competition_main___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__3_value)}};
static const lean_object* lp_competition_main___closed__4 = (const lean_object*)&lp_competition_main___closed__4_value;
static const lean_string_object lp_competition_main___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "f64boxed"};
static const lean_object* lp_competition_main___closed__5 = (const lean_object*)&lp_competition_main___closed__5_value;
static const lean_ctor_object lp_competition_main___closed__6_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__5_value)}};
static const lean_object* lp_competition_main___closed__6 = (const lean_object*)&lp_competition_main___closed__6_value;
static const lean_string_object lp_competition_main___closed__7_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 8, .m_capacity = 8, .m_length = 7, .m_data = "f64cast"};
static const lean_object* lp_competition_main___closed__7 = (const lean_object*)&lp_competition_main___closed__7_value;
static const lean_ctor_object lp_competition_main___closed__8_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__7_value)}};
static const lean_object* lp_competition_main___closed__8 = (const lean_object*)&lp_competition_main___closed__8_value;
static const lean_string_object lp_competition_main___closed__9_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 43, .m_capacity = 43, .m_length = 42, .m_data = "BENCH_VARIANT invalid for R24 F64 ADD cost"};
static const lean_object* lp_competition_main___closed__9 = (const lean_object*)&lp_competition_main___closed__9_value;
static const lean_ctor_object lp_competition_main___closed__10_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_main___closed__9_value)}};
static const lean_object* lp_competition_main___closed__10 = (const lean_object*)&lp_competition_main___closed__10_value;
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
LEAN_EXPORT uint32_t lp_competition_runF64Native___lam__0(uint32_t v___y_680_, uint32_t v___y_681_){
_start:
{
uint32_t v___y_683_; double v___y_684_; lean_object* v___y_685_; uint32_t v___y_686_; uint32_t v___y_744_; uint32_t v___x_760_; uint32_t v___x_761_; uint8_t v___x_762_; 
v___x_760_ = 2139095040;
v___x_761_ = lean_uint32_land(v___y_680_, v___x_760_);
v___x_762_ = lean_uint32_dec_eq(v___x_761_, v___x_760_);
if (v___x_762_ == 0)
{
uint32_t v___x_763_; uint8_t v___x_764_; 
v___x_763_ = lean_uint32_land(v___y_681_, v___x_760_);
v___x_764_ = lean_uint32_dec_eq(v___x_763_, v___x_760_);
if (v___x_764_ == 0)
{
uint32_t v___x_765_; uint32_t v___x_766_; uint32_t v___x_767_; uint8_t v___x_768_; 
v___x_765_ = 8388607;
v___x_766_ = lean_uint32_land(v___y_680_, v___x_765_);
v___x_767_ = 0;
v___x_768_ = lean_uint32_dec_eq(v___x_761_, v___x_767_);
if (v___x_768_ == 0)
{
uint32_t v___x_769_; uint32_t v___x_770_; 
v___x_769_ = 8388608;
v___x_770_ = lean_uint32_lor(v___x_766_, v___x_769_);
v___y_744_ = v___x_770_;
goto v___jp_743_;
}
else
{
v___y_744_ = v___x_766_;
goto v___jp_743_;
}
}
else
{
uint32_t v___x_771_; 
v___x_771_ = lp_competition_Submission_R24F64Add_retainedAdd(v___y_680_, v___y_681_);
return v___x_771_;
}
}
else
{
uint32_t v___x_772_; 
v___x_772_ = lp_competition_Submission_R24F64Add_retainedAdd(v___y_680_, v___y_681_);
return v___x_772_;
}
v___jp_682_:
{
double v___x_687_; uint32_t v___x_688_; lean_object* v___x_689_; double v___x_690_; double v___x_691_; double v___x_692_; uint64_t v___x_693_; uint64_t v___x_694_; uint64_t v___x_695_; uint32_t v___x_696_; uint32_t v___x_697_; uint32_t v_sign_698_; uint64_t v___x_699_; uint64_t v___x_700_; uint64_t v___x_701_; uint64_t v_e_702_; uint64_t v___x_703_; uint8_t v___x_704_; 
v___x_687_ = lean_uint32_to_float(v___y_686_);
v___x_688_ = lean_uint32_shift_right(v___y_681_, v___y_683_);
v___x_689_ = lean_uint32_to_nat(v___x_688_);
v___x_690_ = lean_float_array_get(v___y_685_, v___x_689_);
lean_dec(v___x_689_);
v___x_691_ = lean_float_mul(v___x_687_, v___x_690_);
v___x_692_ = lean_float_add(v___y_684_, v___x_691_);
v___x_693_ = lean_float_to_bits(v___x_692_);
v___x_694_ = 32ULL;
v___x_695_ = lean_uint64_shift_right(v___x_693_, v___x_694_);
v___x_696_ = lean_uint64_to_uint32(v___x_695_);
v___x_697_ = 2147483648;
v_sign_698_ = lean_uint32_land(v___x_696_, v___x_697_);
v___x_699_ = 52ULL;
v___x_700_ = lean_uint64_shift_right(v___x_693_, v___x_699_);
v___x_701_ = 2047ULL;
v_e_702_ = lean_uint64_land(v___x_700_, v___x_701_);
v___x_703_ = 873ULL;
v___x_704_ = lean_uint64_dec_lt(v_e_702_, v___x_703_);
if (v___x_704_ == 0)
{
uint64_t v___x_705_; uint8_t v___x_706_; 
v___x_705_ = 1150ULL;
v___x_706_ = lean_uint64_dec_lt(v___x_705_, v_e_702_);
if (v___x_706_ == 0)
{
uint64_t v___x_707_; uint64_t v___x_708_; uint64_t v___x_709_; uint64_t v_m_710_; uint64_t v___x_711_; uint8_t v___x_712_; 
v___x_707_ = 4503599627370495ULL;
v___x_708_ = lean_uint64_land(v___x_693_, v___x_707_);
v___x_709_ = 4503599627370496ULL;
v_m_710_ = lean_uint64_lor(v___x_708_, v___x_709_);
v___x_711_ = 897ULL;
v___x_712_ = lean_uint64_dec_lt(v_e_702_, v___x_711_);
if (v___x_712_ == 0)
{
uint64_t v___x_713_; uint64_t v___x_714_; uint64_t v___x_715_; uint64_t v___x_716_; uint64_t v___x_717_; uint64_t v___x_718_; uint64_t v___x_719_; uint64_t v___x_720_; uint32_t v_q_721_; uint32_t v___x_722_; uint32_t v___x_723_; uint32_t v___x_724_; uint32_t v___x_725_; uint32_t v___x_726_; uint32_t v___x_727_; 
v___x_713_ = 268435455ULL;
v___x_714_ = lean_uint64_add(v_m_710_, v___x_713_);
v___x_715_ = 29ULL;
v___x_716_ = lean_uint64_shift_right(v_m_710_, v___x_715_);
v___x_717_ = 1ULL;
v___x_718_ = lean_uint64_land(v___x_716_, v___x_717_);
v___x_719_ = lean_uint64_add(v___x_714_, v___x_718_);
v___x_720_ = lean_uint64_shift_right(v___x_719_, v___x_715_);
v_q_721_ = lean_uint64_to_uint32(v___x_720_);
v___x_722_ = lean_uint64_to_uint32(v_e_702_);
v___x_723_ = 897;
v___x_724_ = lean_uint32_sub(v___x_722_, v___x_723_);
v___x_725_ = lean_uint32_shift_left(v___x_724_, v___y_683_);
v___x_726_ = lean_uint32_add(v___x_725_, v_q_721_);
v___x_727_ = lean_uint32_lor(v_sign_698_, v___x_726_);
return v___x_727_;
}
else
{
uint64_t v___x_728_; uint64_t v_d_729_; uint64_t v___x_730_; uint64_t v___x_731_; uint64_t v___x_732_; uint64_t v___x_733_; uint64_t v___x_734_; uint64_t v___x_735_; uint64_t v___x_736_; uint64_t v___x_737_; uint64_t v_q_738_; uint32_t v___x_739_; uint32_t v___x_740_; 
v___x_728_ = 926ULL;
v_d_729_ = lean_uint64_sub(v___x_728_, v_e_702_);
v___x_730_ = 1ULL;
v___x_731_ = lean_uint64_sub(v_d_729_, v___x_730_);
v___x_732_ = lean_uint64_shift_left(v___x_730_, v___x_731_);
v___x_733_ = lean_uint64_sub(v___x_732_, v___x_730_);
v___x_734_ = lean_uint64_add(v_m_710_, v___x_733_);
v___x_735_ = lean_uint64_shift_right(v_m_710_, v_d_729_);
v___x_736_ = lean_uint64_land(v___x_735_, v___x_730_);
v___x_737_ = lean_uint64_add(v___x_734_, v___x_736_);
v_q_738_ = lean_uint64_shift_right(v___x_737_, v_d_729_);
v___x_739_ = lean_uint64_to_uint32(v_q_738_);
v___x_740_ = lean_uint32_lor(v_sign_698_, v___x_739_);
return v___x_740_;
}
}
else
{
uint32_t v___x_741_; uint32_t v___x_742_; 
v___x_741_ = 2139095040;
v___x_742_ = lean_uint32_lor(v_sign_698_, v___x_741_);
return v___x_742_;
}
}
else
{
return v_sign_698_;
}
}
v___jp_743_:
{
double v___x_745_; lean_object* v___x_746_; uint32_t v___x_747_; uint32_t v___x_748_; lean_object* v___x_749_; double v___x_750_; double v___x_751_; uint32_t v___x_752_; uint32_t v___x_753_; uint32_t v___x_754_; uint32_t v___x_755_; uint32_t v___x_756_; uint8_t v___x_757_; 
v___x_745_ = lean_uint32_to_float(v___y_744_);
v___x_746_ = lp_competition_Submission_R24F64Add_nativeScales;
v___x_747_ = 23;
v___x_748_ = lean_uint32_shift_right(v___y_680_, v___x_747_);
v___x_749_ = lean_uint32_to_nat(v___x_748_);
v___x_750_ = lean_float_array_get(v___x_746_, v___x_749_);
lean_dec(v___x_749_);
v___x_751_ = lean_float_mul(v___x_745_, v___x_750_);
v___x_752_ = 8388607;
v___x_753_ = lean_uint32_land(v___y_681_, v___x_752_);
v___x_754_ = 2139095040;
v___x_755_ = lean_uint32_land(v___y_681_, v___x_754_);
v___x_756_ = 0;
v___x_757_ = lean_uint32_dec_eq(v___x_755_, v___x_756_);
if (v___x_757_ == 0)
{
uint32_t v___x_758_; uint32_t v___x_759_; 
v___x_758_ = 8388608;
v___x_759_ = lean_uint32_lor(v___x_753_, v___x_758_);
v___y_683_ = v___x_747_;
v___y_684_ = v___x_751_;
v___y_685_ = v___x_746_;
v___y_686_ = v___x_759_;
goto v___jp_682_;
}
else
{
v___y_683_ = v___x_747_;
v___y_684_ = v___x_751_;
v___y_685_ = v___x_746_;
v___y_686_ = v___x_753_;
goto v___jp_682_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_runF64Native___lam__0___boxed(lean_object* v___y_773_, lean_object* v___y_774_){
_start:
{
uint32_t v___y_1770__boxed_775_; uint32_t v___y_1771__boxed_776_; uint32_t v_res_777_; lean_object* v_r_778_; 
v___y_1770__boxed_775_ = lean_unbox_uint32(v___y_773_);
lean_dec(v___y_773_);
v___y_1771__boxed_776_ = lean_unbox_uint32(v___y_774_);
lean_dec(v___y_774_);
v_res_777_ = lp_competition_runF64Native___lam__0(v___y_1770__boxed_775_, v___y_1771__boxed_776_);
v_r_778_ = lean_box_uint32(v_res_777_);
return v_r_778_;
}
}
LEAN_EXPORT uint32_t lp_competition_runF64Native___lam__1(uint32_t v___y_779_, uint32_t v___y_780_){
_start:
{
uint32_t v___y_782_; uint32_t v___y_786_; uint32_t v___y_790_; uint32_t v___y_791_; uint32_t v___y_792_; uint32_t v___y_796_; uint8_t v___y_797_; uint64_t v___y_798_; uint64_t v___y_799_; uint32_t v___y_811_; uint32_t v___y_812_; uint32_t v___y_813_; uint32_t v___y_817_; uint8_t v___y_818_; uint64_t v___y_819_; uint64_t v___y_820_; uint8_t v___y_832_; uint8_t v___y_848_; uint8_t v___y_862_; uint8_t v___y_879_; float v___y_886_; float v___y_887_; float v___y_901_; uint8_t v___y_902_; float v___y_917_; uint32_t v___x_926_; uint32_t v___x_927_; uint8_t v___y_929_; uint32_t v___x_941_; uint32_t v___y_943_; uint32_t v___y_944_; uint32_t v___y_945_; uint32_t v___y_946_; uint32_t v___y_953_; uint8_t v___y_954_; uint32_t v___y_955_; uint32_t v___y_956_; uint32_t v___y_960_; uint8_t v___y_961_; uint64_t v___y_962_; uint64_t v___y_963_; uint64_t v___y_964_; uint32_t v___y_974_; uint8_t v___y_975_; uint64_t v___y_976_; uint64_t v___y_977_; uint8_t v___y_978_; uint64_t v___y_979_; uint32_t v___y_986_; uint64_t v___y_987_; uint8_t v___y_988_; uint64_t v___y_989_; uint64_t v___y_990_; uint32_t v___y_996_; uint8_t v___y_997_; uint64_t v___y_998_; uint64_t v___y_999_; uint64_t v___y_1000_; uint64_t v___y_1001_; uint32_t v___y_1056_; uint64_t v___y_1057_; uint8_t v___y_1058_; uint64_t v___y_1059_; uint64_t v___y_1060_; uint64_t v___y_1061_; uint64_t v___y_1062_; uint32_t v___y_1068_; uint64_t v___y_1069_; uint8_t v___y_1070_; uint64_t v___y_1071_; uint64_t v___y_1072_; uint64_t v___y_1073_; uint64_t v___y_1074_; uint64_t v___y_1075_; uint64_t v___y_1076_; uint32_t v___y_1081_; uint64_t v___y_1082_; uint8_t v___y_1083_; uint64_t v___y_1084_; uint64_t v___y_1085_; uint64_t v___y_1086_; uint64_t v___y_1087_; uint32_t v___y_1092_; uint64_t v___y_1093_; uint8_t v___y_1094_; uint64_t v___y_1095_; uint64_t v___y_1096_; uint64_t v___y_1097_; uint64_t v___y_1098_; uint64_t v___y_1099_; uint64_t v___y_1100_; uint32_t v___y_1105_; uint8_t v___y_1106_; uint64_t v___y_1107_; uint64_t v___y_1108_; uint64_t v___y_1109_; uint64_t v___y_1110_; uint64_t v___y_1111_; uint64_t v___y_1116_; uint32_t v___y_1117_; uint8_t v___y_1118_; uint64_t v___y_1119_; uint64_t v___y_1120_; uint64_t v___y_1121_; uint64_t v___y_1122_; uint64_t v___y_1123_; uint64_t v___y_1124_; uint32_t v___y_1129_; uint8_t v___y_1130_; uint64_t v___y_1131_; uint64_t v___y_1132_; uint64_t v___y_1133_; uint64_t v___y_1134_; uint64_t v___y_1135_; uint64_t v___y_1140_; uint32_t v___y_1141_; uint8_t v___y_1142_; uint64_t v___y_1143_; uint64_t v___y_1144_; uint64_t v___y_1145_; uint64_t v___y_1146_; uint64_t v___y_1147_; uint64_t v___y_1148_; uint32_t v___y_1153_; uint8_t v___y_1154_; uint64_t v___y_1155_; uint64_t v___y_1156_; uint64_t v___y_1157_; uint64_t v___y_1158_; uint64_t v___y_1159_; uint64_t v___y_1164_; uint32_t v___y_1165_; uint8_t v___y_1166_; uint64_t v___y_1167_; uint64_t v___y_1168_; uint64_t v___y_1169_; uint64_t v___y_1170_; uint32_t v___y_1174_; uint8_t v___y_1175_; uint64_t v___y_1176_; uint64_t v___y_1177_; uint32_t v___y_1186_; uint8_t v___y_1187_; uint64_t v___y_1188_; uint64_t v___y_1189_; uint64_t v___y_1190_; uint64_t v___y_1191_; uint32_t v_ex_1224_; uint32_t v___x_1225_; uint32_t v_ey_1226_; uint32_t v___y_1228_; uint8_t v___y_1229_; uint64_t v___y_1230_; uint64_t v___y_1231_; uint64_t v___y_1232_; uint32_t v___y_1239_; uint8_t v___y_1240_; uint64_t v___y_1241_; uint64_t v___y_1242_; uint32_t v___y_1249_; uint8_t v___y_1250_; uint32_t v___y_1251_; uint64_t v___y_1252_; uint8_t v___y_1260_; uint32_t v___x_1270_; uint32_t v___x_1271_; uint8_t v___x_1272_; uint8_t v___y_1274_; uint8_t v___y_1275_; uint8_t v___y_1277_; uint8_t v___y_1278_; uint8_t v___y_1279_; uint8_t v___y_1281_; uint8_t v___y_1282_; uint8_t v___y_1288_; 
v___x_926_ = 23;
v___x_927_ = lean_uint32_shift_right(v___y_779_, v___x_926_);
v___x_941_ = 255;
v_ex_1224_ = lean_uint32_land(v___x_927_, v___x_941_);
v___x_1225_ = lean_uint32_shift_right(v___y_780_, v___x_926_);
v_ey_1226_ = lean_uint32_land(v___x_1225_, v___x_941_);
v___x_1270_ = lean_uint32_add(v_ex_1224_, v_ey_1226_);
v___x_1271_ = 128;
v___x_1272_ = lean_uint32_dec_lt(v___x_1270_, v___x_1271_);
if (v___x_1272_ == 0)
{
uint32_t v___x_1297_; uint32_t v_a_1298_; uint32_t v___x_1299_; uint32_t v___x_1300_; uint32_t v___x_1301_; uint8_t v___x_1302_; 
v___x_1297_ = 2147483647;
v_a_1298_ = lean_uint32_land(v___y_779_, v___x_1297_);
v___x_1299_ = 201326591;
v___x_1300_ = 1;
v___x_1301_ = lean_uint32_sub(v_a_1298_, v___x_1300_);
v___x_1302_ = lean_uint32_dec_le(v___x_1299_, v___x_1301_);
if (v___x_1302_ == 0)
{
v___y_929_ = v___x_1302_;
goto v___jp_928_;
}
else
{
uint32_t v___x_1303_; uint8_t v___x_1304_; 
v___x_1303_ = 2139095040;
v___x_1304_ = lean_uint32_dec_lt(v_a_1298_, v___x_1303_);
v___y_929_ = v___x_1304_;
goto v___jp_928_;
}
}
else
{
uint32_t v___x_1305_; uint32_t v___x_1306_; uint32_t v___x_1307_; uint8_t v___x_1308_; 
v___x_1305_ = 4278190080;
v___x_1306_ = 1;
v___x_1307_ = lean_uint32_shift_left(v___y_779_, v___x_1306_);
v___x_1308_ = lean_uint32_dec_le(v___x_1305_, v___x_1307_);
if (v___x_1308_ == 0)
{
uint32_t v___x_1309_; uint8_t v___x_1310_; 
v___x_1309_ = lean_uint32_shift_left(v___y_780_, v___x_1306_);
v___x_1310_ = lean_uint32_dec_le(v___x_1305_, v___x_1309_);
v___y_1288_ = v___x_1310_;
goto v___jp_1287_;
}
else
{
v___y_1288_ = v___x_1308_;
goto v___jp_1287_;
}
}
v___jp_781_:
{
uint32_t v___x_783_; uint32_t v___x_784_; 
v___x_783_ = 8388608;
v___x_784_ = lean_uint32_lor(v___y_782_, v___x_783_);
return v___x_784_;
}
v___jp_785_:
{
uint32_t v___x_787_; uint32_t v___x_788_; 
v___x_787_ = 8388608;
v___x_788_ = lean_uint32_lor(v___y_786_, v___x_787_);
return v___x_788_;
}
v___jp_789_:
{
uint32_t v___x_793_; uint32_t v___x_794_; 
v___x_793_ = lean_uint32_land(v___y_790_, v___y_791_);
v___x_794_ = lean_uint32_lor(v___y_792_, v___x_793_);
return v___x_794_;
}
v___jp_795_:
{
uint8_t v___x_800_; 
v___x_800_ = lean_uint64_dec_eq(v___y_799_, v___y_798_);
if (v___x_800_ == 0)
{
uint64_t v___x_801_; uint8_t v___x_802_; 
v___x_801_ = 8388608ULL;
v___x_802_ = lean_uint64_dec_eq(v___y_799_, v___x_801_);
if (v___x_802_ == 0)
{
uint32_t v___x_803_; 
v___x_803_ = lean_uint64_to_uint32(v___y_799_);
if (v___y_797_ == 0)
{
uint32_t v___x_804_; 
v___x_804_ = 0;
v___y_790_ = v___x_803_;
v___y_791_ = v___y_796_;
v___y_792_ = v___x_804_;
goto v___jp_789_;
}
else
{
uint32_t v___x_805_; 
v___x_805_ = 2147483648;
v___y_790_ = v___x_803_;
v___y_791_ = v___y_796_;
v___y_792_ = v___x_805_;
goto v___jp_789_;
}
}
else
{
if (v___y_797_ == 0)
{
uint32_t v___x_806_; 
v___x_806_ = 0;
v___y_786_ = v___x_806_;
goto v___jp_785_;
}
else
{
uint32_t v___x_807_; 
v___x_807_ = 2147483648;
v___y_786_ = v___x_807_;
goto v___jp_785_;
}
}
}
else
{
if (v___y_797_ == 0)
{
uint32_t v___x_808_; 
v___x_808_ = 0;
return v___x_808_;
}
else
{
uint32_t v___x_809_; 
v___x_809_ = 2147483648;
return v___x_809_;
}
}
}
v___jp_810_:
{
uint32_t v___x_814_; uint32_t v___x_815_; 
v___x_814_ = lean_uint32_land(v___y_812_, v___y_811_);
v___x_815_ = lean_uint32_lor(v___y_813_, v___x_814_);
return v___x_815_;
}
v___jp_816_:
{
uint8_t v___x_821_; 
v___x_821_ = lean_uint64_dec_eq(v___y_820_, v___y_819_);
if (v___x_821_ == 0)
{
uint64_t v___x_822_; uint8_t v___x_823_; 
v___x_822_ = 8388608ULL;
v___x_823_ = lean_uint64_dec_eq(v___y_820_, v___x_822_);
if (v___x_823_ == 0)
{
uint32_t v___x_824_; 
v___x_824_ = lean_uint64_to_uint32(v___y_820_);
if (v___y_818_ == 0)
{
uint32_t v___x_825_; 
v___x_825_ = 0;
v___y_811_ = v___y_817_;
v___y_812_ = v___x_824_;
v___y_813_ = v___x_825_;
goto v___jp_810_;
}
else
{
uint32_t v___x_826_; 
v___x_826_ = 2147483648;
v___y_811_ = v___y_817_;
v___y_812_ = v___x_824_;
v___y_813_ = v___x_826_;
goto v___jp_810_;
}
}
else
{
if (v___y_818_ == 0)
{
uint32_t v___x_827_; 
v___x_827_ = 0;
v___y_782_ = v___x_827_;
goto v___jp_781_;
}
else
{
uint32_t v___x_828_; 
v___x_828_ = 2147483648;
v___y_782_ = v___x_828_;
goto v___jp_781_;
}
}
}
else
{
if (v___y_818_ == 0)
{
uint32_t v___x_829_; 
v___x_829_ = 0;
return v___x_829_;
}
else
{
uint32_t v___x_830_; 
v___x_830_ = 2147483648;
return v___x_830_;
}
}
}
v___jp_831_:
{
if (v___y_832_ == 0)
{
uint32_t v___x_833_; 
v___x_833_ = lp_competition_Submission_FastMul_mul(v___y_779_, v___y_780_);
return v___x_833_;
}
else
{
uint32_t v___x_834_; uint32_t v___x_835_; 
v___x_834_ = 4194304;
v___x_835_ = lean_uint32_lor(v___y_780_, v___x_834_);
return v___x_835_;
}
}
v___jp_836_:
{
uint32_t v___x_837_; uint32_t v___x_838_; uint32_t v___x_839_; uint32_t v___x_840_; uint8_t v___x_841_; 
v___x_837_ = 23;
v___x_838_ = lean_uint32_shift_right(v___y_780_, v___x_837_);
v___x_839_ = 255;
v___x_840_ = lean_uint32_land(v___x_838_, v___x_839_);
v___x_841_ = lean_uint32_dec_eq(v___x_840_, v___x_839_);
if (v___x_841_ == 0)
{
v___y_832_ = v___x_841_;
goto v___jp_831_;
}
else
{
uint32_t v___x_842_; uint32_t v___x_843_; uint32_t v___x_844_; uint8_t v___x_845_; 
v___x_842_ = 8388607;
v___x_843_ = lean_uint32_land(v___y_780_, v___x_842_);
v___x_844_ = 0;
v___x_845_ = lean_uint32_dec_eq(v___x_843_, v___x_844_);
if (v___x_845_ == 0)
{
v___y_832_ = v___x_841_;
goto v___jp_831_;
}
else
{
uint32_t v___x_846_; 
v___x_846_ = lp_competition_Submission_FastMul_mul(v___y_779_, v___y_780_);
return v___x_846_;
}
}
}
v___jp_847_:
{
if (v___y_848_ == 0)
{
goto v___jp_836_;
}
else
{
uint32_t v___x_849_; uint32_t v___x_850_; 
v___x_849_ = 4194304;
v___x_850_ = lean_uint32_lor(v___y_779_, v___x_849_);
return v___x_850_;
}
}
v___jp_851_:
{
uint32_t v___x_852_; uint32_t v___x_853_; uint32_t v___x_854_; uint32_t v___x_855_; uint8_t v___x_856_; 
v___x_852_ = 23;
v___x_853_ = lean_uint32_shift_right(v___y_779_, v___x_852_);
v___x_854_ = 255;
v___x_855_ = lean_uint32_land(v___x_853_, v___x_854_);
v___x_856_ = lean_uint32_dec_eq(v___x_855_, v___x_854_);
if (v___x_856_ == 0)
{
v___y_848_ = v___x_856_;
goto v___jp_847_;
}
else
{
uint32_t v___x_857_; uint32_t v___x_858_; uint32_t v___x_859_; uint8_t v___x_860_; 
v___x_857_ = 8388607;
v___x_858_ = lean_uint32_land(v___y_779_, v___x_857_);
v___x_859_ = 0;
v___x_860_ = lean_uint32_dec_eq(v___x_858_, v___x_859_);
if (v___x_860_ == 0)
{
v___y_848_ = v___x_856_;
goto v___jp_847_;
}
else
{
goto v___jp_836_;
}
}
}
v___jp_861_:
{
if (v___y_862_ == 0)
{
goto v___jp_851_;
}
else
{
uint32_t v___x_863_; uint32_t v___x_864_; uint32_t v___x_865_; uint8_t v___x_866_; 
v___x_863_ = 4194304;
v___x_864_ = lean_uint32_land(v___y_780_, v___x_863_);
v___x_865_ = 0;
v___x_866_ = lean_uint32_dec_eq(v___x_864_, v___x_865_);
if (v___x_866_ == 0)
{
goto v___jp_851_;
}
else
{
uint32_t v___x_867_; 
v___x_867_ = lean_uint32_lor(v___y_780_, v___x_863_);
return v___x_867_;
}
}
}
v___jp_868_:
{
uint32_t v___x_869_; uint32_t v___x_870_; uint32_t v___x_871_; uint32_t v___x_872_; uint8_t v___x_873_; 
v___x_869_ = 23;
v___x_870_ = lean_uint32_shift_right(v___y_780_, v___x_869_);
v___x_871_ = 255;
v___x_872_ = lean_uint32_land(v___x_870_, v___x_871_);
v___x_873_ = lean_uint32_dec_eq(v___x_872_, v___x_871_);
if (v___x_873_ == 0)
{
v___y_862_ = v___x_873_;
goto v___jp_861_;
}
else
{
uint32_t v___x_874_; uint32_t v___x_875_; uint32_t v___x_876_; uint8_t v___x_877_; 
v___x_874_ = 8388607;
v___x_875_ = lean_uint32_land(v___y_780_, v___x_874_);
v___x_876_ = 0;
v___x_877_ = lean_uint32_dec_eq(v___x_875_, v___x_876_);
if (v___x_877_ == 0)
{
v___y_862_ = v___x_873_;
goto v___jp_861_;
}
else
{
goto v___jp_851_;
}
}
}
v___jp_878_:
{
if (v___y_879_ == 0)
{
goto v___jp_868_;
}
else
{
uint32_t v___x_880_; uint32_t v___x_881_; uint32_t v___x_882_; uint8_t v___x_883_; 
v___x_880_ = 4194304;
v___x_881_ = lean_uint32_land(v___y_779_, v___x_880_);
v___x_882_ = 0;
v___x_883_ = lean_uint32_dec_eq(v___x_881_, v___x_882_);
if (v___x_883_ == 0)
{
goto v___jp_868_;
}
else
{
uint32_t v___x_884_; 
v___x_884_ = lean_uint32_lor(v___y_779_, v___x_880_);
return v___x_884_;
}
}
}
v___jp_885_:
{
float v_result_888_; uint8_t v___x_889_; 
v_result_888_ = lean_float32_mul(v___y_886_, v___y_887_);
v___x_889_ = lean_float32_beq(v_result_888_, v_result_888_);
if (v___x_889_ == 0)
{
uint32_t v___x_890_; uint32_t v___x_891_; uint32_t v___x_892_; uint32_t v___x_893_; uint8_t v___x_894_; 
v___x_890_ = 23;
v___x_891_ = lean_uint32_shift_right(v___y_779_, v___x_890_);
v___x_892_ = 255;
v___x_893_ = lean_uint32_land(v___x_891_, v___x_892_);
v___x_894_ = lean_uint32_dec_eq(v___x_893_, v___x_892_);
if (v___x_894_ == 0)
{
v___y_879_ = v___x_894_;
goto v___jp_878_;
}
else
{
uint32_t v___x_895_; uint32_t v___x_896_; uint32_t v___x_897_; uint8_t v___x_898_; 
v___x_895_ = 8388607;
v___x_896_ = lean_uint32_land(v___y_779_, v___x_895_);
v___x_897_ = 0;
v___x_898_ = lean_uint32_dec_eq(v___x_896_, v___x_897_);
if (v___x_898_ == 0)
{
v___y_879_ = v___x_894_;
goto v___jp_878_;
}
else
{
goto v___jp_868_;
}
}
}
else
{
uint32_t v___x_899_; 
v___x_899_ = lean_float32_to_bits(v_result_888_);
return v___x_899_;
}
}
v___jp_900_:
{
if (v___y_902_ == 0)
{
float v___x_903_; 
v___x_903_ = lean_float32_of_bits(v___y_780_);
v___y_886_ = v___y_901_;
v___y_887_ = v___x_903_;
goto v___jp_885_;
}
else
{
uint32_t v___x_904_; uint32_t v___x_905_; uint32_t v___x_906_; uint32_t v___x_907_; float v___x_908_; lean_object* v___x_909_; uint32_t v___x_910_; uint32_t v___x_911_; lean_object* v___x_912_; lean_object* v___x_913_; float v___x_914_; float v___x_915_; 
v___x_904_ = 8388607;
v___x_905_ = lean_uint32_land(v___y_780_, v___x_904_);
v___x_906_ = 8388608;
v___x_907_ = lean_uint32_lor(v___x_905_, v___x_906_);
v___x_908_ = lean_uint32_to_float32(v___x_907_);
v___x_909_ = lp_competition_R2W01b_scaleTable;
v___x_910_ = 23;
v___x_911_ = lean_uint32_shift_right(v___y_780_, v___x_910_);
v___x_912_ = lean_uint32_to_nat(v___x_911_);
v___x_913_ = lean_array_fget_borrowed(v___x_909_, v___x_912_);
lean_dec(v___x_912_);
v___x_914_ = lean_unbox_float32(v___x_913_);
v___x_915_ = lean_float32_mul(v___x_908_, v___x_914_);
v___y_886_ = v___y_901_;
v___y_887_ = v___x_915_;
goto v___jp_885_;
}
}
v___jp_916_:
{
uint32_t v___x_918_; uint32_t v_a_919_; uint32_t v___x_920_; uint32_t v___x_921_; uint32_t v___x_922_; uint8_t v___x_923_; 
v___x_918_ = 2147483647;
v_a_919_ = lean_uint32_land(v___y_780_, v___x_918_);
v___x_920_ = 201326591;
v___x_921_ = 1;
v___x_922_ = lean_uint32_sub(v_a_919_, v___x_921_);
v___x_923_ = lean_uint32_dec_le(v___x_920_, v___x_922_);
if (v___x_923_ == 0)
{
v___y_901_ = v___y_917_;
v___y_902_ = v___x_923_;
goto v___jp_900_;
}
else
{
uint32_t v___x_924_; uint8_t v___x_925_; 
v___x_924_ = 2139095040;
v___x_925_ = lean_uint32_dec_lt(v_a_919_, v___x_924_);
v___y_901_ = v___y_917_;
v___y_902_ = v___x_925_;
goto v___jp_900_;
}
}
v___jp_928_:
{
if (v___y_929_ == 0)
{
float v___x_930_; 
v___x_930_ = lean_float32_of_bits(v___y_779_);
v___y_917_ = v___x_930_;
goto v___jp_916_;
}
else
{
uint32_t v___x_931_; uint32_t v___x_932_; uint32_t v___x_933_; uint32_t v___x_934_; float v___x_935_; lean_object* v___x_936_; lean_object* v___x_937_; lean_object* v___x_938_; float v___x_939_; float v___x_940_; 
v___x_931_ = 8388607;
v___x_932_ = lean_uint32_land(v___y_779_, v___x_931_);
v___x_933_ = 8388608;
v___x_934_ = lean_uint32_lor(v___x_932_, v___x_933_);
v___x_935_ = lean_uint32_to_float32(v___x_934_);
v___x_936_ = lp_competition_R2W01b_scaleTable;
v___x_937_ = lean_uint32_to_nat(v___x_927_);
v___x_938_ = lean_array_fget_borrowed(v___x_936_, v___x_937_);
lean_dec(v___x_937_);
v___x_939_ = lean_unbox_float32(v___x_938_);
v___x_940_ = lean_float32_mul(v___x_935_, v___x_939_);
v___y_917_ = v___x_940_;
goto v___jp_916_;
}
}
v___jp_942_:
{
uint32_t v___x_947_; uint32_t v___x_948_; uint32_t v___x_949_; uint32_t v___x_950_; uint32_t v___x_951_; 
v___x_947_ = lean_uint32_land(v___y_945_, v___x_941_);
v___x_948_ = lean_uint32_shift_left(v___x_947_, v___x_926_);
v___x_949_ = lean_uint32_lor(v___y_946_, v___x_948_);
v___x_950_ = lean_uint32_land(v___y_943_, v___y_944_);
v___x_951_ = lean_uint32_lor(v___x_949_, v___x_950_);
return v___x_951_;
}
v___jp_952_:
{
if (v___y_954_ == 0)
{
uint32_t v___x_957_; 
v___x_957_ = 0;
v___y_943_ = v___y_956_;
v___y_944_ = v___y_953_;
v___y_945_ = v___y_955_;
v___y_946_ = v___x_957_;
goto v___jp_942_;
}
else
{
uint32_t v___x_958_; 
v___x_958_ = 2147483648;
v___y_943_ = v___y_956_;
v___y_944_ = v___y_953_;
v___y_945_ = v___y_955_;
v___y_946_ = v___x_958_;
goto v___jp_942_;
}
}
v___jp_959_:
{
uint64_t v___x_965_; uint64_t v_encodedExponent_966_; uint32_t v___x_967_; uint64_t v___x_968_; uint8_t v___x_969_; 
v___x_965_ = 171ULL;
v_encodedExponent_966_ = lean_uint64_sub(v___y_962_, v___x_965_);
v___x_967_ = lean_uint64_to_uint32(v_encodedExponent_966_);
v___x_968_ = 8388608ULL;
v___x_969_ = lean_uint64_dec_lt(v___y_964_, v___x_968_);
if (v___x_969_ == 0)
{
uint64_t v___x_970_; uint32_t v___x_971_; 
v___x_970_ = lean_uint64_sub(v___y_964_, v___x_968_);
v___x_971_ = lean_uint64_to_uint32(v___x_970_);
v___y_953_ = v___y_960_;
v___y_954_ = v___y_961_;
v___y_955_ = v___x_967_;
v___y_956_ = v___x_971_;
goto v___jp_952_;
}
else
{
uint32_t v___x_972_; 
v___x_972_ = lean_uint64_to_uint32(v___y_963_);
v___y_953_ = v___y_960_;
v___y_954_ = v___y_961_;
v___y_955_ = v___x_967_;
v___y_956_ = v___x_972_;
goto v___jp_952_;
}
}
v___jp_973_:
{
uint64_t v___x_980_; uint8_t v___x_981_; 
v___x_980_ = 425ULL;
v___x_981_ = lean_uint64_dec_lt(v___x_980_, v___y_979_);
if (v___x_981_ == 0)
{
if (v___y_978_ == 0)
{
v___y_960_ = v___y_974_;
v___y_961_ = v___y_975_;
v___y_962_ = v___y_979_;
v___y_963_ = v___y_977_;
v___y_964_ = v___y_976_;
goto v___jp_959_;
}
else
{
uint64_t v___x_982_; 
v___x_982_ = 8388608ULL;
v___y_960_ = v___y_974_;
v___y_961_ = v___y_975_;
v___y_962_ = v___y_979_;
v___y_963_ = v___y_977_;
v___y_964_ = v___x_982_;
goto v___jp_959_;
}
}
else
{
if (v___y_975_ == 0)
{
uint32_t v___x_983_; 
v___x_983_ = 2139095040;
return v___x_983_;
}
else
{
uint32_t v___x_984_; 
v___x_984_ = 4286578688;
return v___x_984_;
}
}
}
v___jp_985_:
{
uint64_t v___x_991_; uint8_t v_carry_992_; 
v___x_991_ = 16777216ULL;
v_carry_992_ = lean_uint64_dec_eq(v___y_990_, v___x_991_);
if (v_carry_992_ == 0)
{
v___y_974_ = v___y_986_;
v___y_975_ = v___y_988_;
v___y_976_ = v___y_990_;
v___y_977_ = v___y_989_;
v___y_978_ = v_carry_992_;
v___y_979_ = v___y_987_;
goto v___jp_973_;
}
else
{
uint64_t v___x_993_; uint64_t v___x_994_; 
v___x_993_ = 1ULL;
v___x_994_ = lean_uint64_add(v___y_987_, v___x_993_);
v___y_974_ = v___y_986_;
v___y_975_ = v___y_988_;
v___y_976_ = v___y_990_;
v___y_977_ = v___y_989_;
v___y_978_ = v_carry_992_;
v___y_979_ = v___x_994_;
goto v___jp_973_;
}
}
v___jp_995_:
{
uint64_t v_position_1002_; uint64_t v___x_1003_; uint8_t v___x_1004_; 
v_position_1002_ = lean_uint64_add(v___y_1001_, v___y_1000_);
v___x_1003_ = 172ULL;
v___x_1004_ = lean_uint64_dec_lt(v_position_1002_, v___x_1003_);
if (v___x_1004_ == 0)
{
uint64_t v___x_1005_; uint8_t v___x_1006_; 
v___x_1005_ = 23ULL;
v___x_1006_ = lean_uint64_dec_lt(v___y_1001_, v___x_1005_);
if (v___x_1006_ == 0)
{
uint64_t v___x_1007_; uint8_t v___x_1008_; 
v___x_1007_ = lean_uint64_sub(v___y_1001_, v___x_1005_);
v___x_1008_ = lean_uint64_dec_eq(v___x_1007_, v___y_999_);
if (v___x_1008_ == 0)
{
uint64_t v___x_1009_; uint8_t v___x_1010_; 
v___x_1009_ = 64ULL;
v___x_1010_ = lean_uint64_dec_lt(v___x_1007_, v___x_1009_);
if (v___x_1010_ == 0)
{
uint8_t v___x_1011_; 
v___x_1011_ = lean_uint64_dec_eq(v___x_1007_, v___x_1009_);
if (v___x_1011_ == 0)
{
v___y_986_ = v___y_996_;
v___y_987_ = v_position_1002_;
v___y_988_ = v___y_997_;
v___y_989_ = v___y_999_;
v___y_990_ = v___y_999_;
goto v___jp_985_;
}
else
{
uint64_t v___x_1012_; uint8_t v___x_1013_; 
v___x_1012_ = 9223372036854775808ULL;
v___x_1013_ = lean_uint64_dec_lt(v___x_1012_, v___y_998_);
if (v___x_1013_ == 0)
{
v___y_986_ = v___y_996_;
v___y_987_ = v_position_1002_;
v___y_988_ = v___y_997_;
v___y_989_ = v___y_999_;
v___y_990_ = v___y_999_;
goto v___jp_985_;
}
else
{
uint64_t v___x_1014_; 
v___x_1014_ = 1ULL;
v___y_986_ = v___y_996_;
v___y_987_ = v_position_1002_;
v___y_988_ = v___y_997_;
v___y_989_ = v___y_999_;
v___y_990_ = v___x_1014_;
goto v___jp_985_;
}
}
}
else
{
uint64_t v_quotient_1015_; uint64_t v___x_1016_; uint64_t v___x_1017_; uint64_t v___x_1018_; uint64_t v_remainder_1019_; uint64_t v___x_1020_; uint64_t v_half_1021_; uint8_t v___x_1022_; 
v_quotient_1015_ = lean_uint64_shift_right(v___y_998_, v___x_1007_);
v___x_1016_ = 1ULL;
v___x_1017_ = lean_uint64_shift_left(v___x_1016_, v___x_1007_);
v___x_1018_ = lean_uint64_sub(v___x_1017_, v___x_1016_);
v_remainder_1019_ = lean_uint64_land(v___y_998_, v___x_1018_);
v___x_1020_ = lean_uint64_sub(v___x_1007_, v___x_1016_);
v_half_1021_ = lean_uint64_shift_left(v___x_1016_, v___x_1020_);
v___x_1022_ = lean_uint64_dec_lt(v_remainder_1019_, v_half_1021_);
if (v___x_1022_ == 0)
{
uint8_t v___x_1023_; 
v___x_1023_ = lean_uint64_dec_lt(v_half_1021_, v_remainder_1019_);
if (v___x_1023_ == 0)
{
uint64_t v___x_1024_; uint8_t v___x_1025_; 
v___x_1024_ = lean_uint64_land(v_quotient_1015_, v___x_1016_);
v___x_1025_ = lean_uint64_dec_eq(v___x_1024_, v___y_999_);
if (v___x_1025_ == 0)
{
uint64_t v___x_1026_; 
v___x_1026_ = lean_uint64_add(v_quotient_1015_, v___x_1016_);
v___y_986_ = v___y_996_;
v___y_987_ = v_position_1002_;
v___y_988_ = v___y_997_;
v___y_989_ = v___y_999_;
v___y_990_ = v___x_1026_;
goto v___jp_985_;
}
else
{
v___y_986_ = v___y_996_;
v___y_987_ = v_position_1002_;
v___y_988_ = v___y_997_;
v___y_989_ = v___y_999_;
v___y_990_ = v_quotient_1015_;
goto v___jp_985_;
}
}
else
{
uint64_t v___x_1027_; 
v___x_1027_ = lean_uint64_add(v_quotient_1015_, v___x_1016_);
v___y_986_ = v___y_996_;
v___y_987_ = v_position_1002_;
v___y_988_ = v___y_997_;
v___y_989_ = v___y_999_;
v___y_990_ = v___x_1027_;
goto v___jp_985_;
}
}
else
{
v___y_986_ = v___y_996_;
v___y_987_ = v_position_1002_;
v___y_988_ = v___y_997_;
v___y_989_ = v___y_999_;
v___y_990_ = v_quotient_1015_;
goto v___jp_985_;
}
}
}
else
{
v___y_986_ = v___y_996_;
v___y_987_ = v_position_1002_;
v___y_988_ = v___y_997_;
v___y_989_ = v___y_999_;
v___y_990_ = v___y_998_;
goto v___jp_985_;
}
}
else
{
uint64_t v___x_1028_; uint64_t v___x_1029_; 
v___x_1028_ = lean_uint64_sub(v___x_1005_, v___y_1001_);
v___x_1029_ = lean_uint64_shift_left(v___y_998_, v___x_1028_);
v___y_986_ = v___y_996_;
v___y_987_ = v_position_1002_;
v___y_988_ = v___y_997_;
v___y_989_ = v___y_999_;
v___y_990_ = v___x_1029_;
goto v___jp_985_;
}
}
else
{
uint64_t v___x_1030_; uint8_t v___x_1031_; 
v___x_1030_ = 149ULL;
v___x_1031_ = lean_uint64_dec_lt(v___y_1000_, v___x_1030_);
if (v___x_1031_ == 0)
{
uint64_t v___x_1032_; uint64_t v___x_1033_; 
v___x_1032_ = lean_uint64_sub(v___y_1000_, v___x_1030_);
v___x_1033_ = lean_uint64_shift_left(v___y_998_, v___x_1032_);
v___y_796_ = v___y_996_;
v___y_797_ = v___y_997_;
v___y_798_ = v___y_999_;
v___y_799_ = v___x_1033_;
goto v___jp_795_;
}
else
{
uint64_t v___x_1034_; uint8_t v___x_1035_; 
v___x_1034_ = lean_uint64_sub(v___x_1030_, v___y_1000_);
v___x_1035_ = lean_uint64_dec_eq(v___x_1034_, v___y_999_);
if (v___x_1035_ == 0)
{
uint64_t v___x_1036_; uint8_t v___x_1037_; 
v___x_1036_ = 64ULL;
v___x_1037_ = lean_uint64_dec_lt(v___x_1034_, v___x_1036_);
if (v___x_1037_ == 0)
{
uint8_t v___x_1038_; 
v___x_1038_ = lean_uint64_dec_eq(v___x_1034_, v___x_1036_);
if (v___x_1038_ == 0)
{
v___y_796_ = v___y_996_;
v___y_797_ = v___y_997_;
v___y_798_ = v___y_999_;
v___y_799_ = v___y_999_;
goto v___jp_795_;
}
else
{
uint64_t v___x_1039_; uint8_t v___x_1040_; 
v___x_1039_ = 9223372036854775808ULL;
v___x_1040_ = lean_uint64_dec_lt(v___x_1039_, v___y_998_);
if (v___x_1040_ == 0)
{
v___y_796_ = v___y_996_;
v___y_797_ = v___y_997_;
v___y_798_ = v___y_999_;
v___y_799_ = v___y_999_;
goto v___jp_795_;
}
else
{
uint64_t v___x_1041_; 
v___x_1041_ = 1ULL;
v___y_796_ = v___y_996_;
v___y_797_ = v___y_997_;
v___y_798_ = v___y_999_;
v___y_799_ = v___x_1041_;
goto v___jp_795_;
}
}
}
else
{
uint64_t v_quotient_1042_; uint64_t v___x_1043_; uint64_t v___x_1044_; uint64_t v___x_1045_; uint64_t v_remainder_1046_; uint64_t v___x_1047_; uint64_t v_half_1048_; uint8_t v___x_1049_; 
v_quotient_1042_ = lean_uint64_shift_right(v___y_998_, v___x_1034_);
v___x_1043_ = 1ULL;
v___x_1044_ = lean_uint64_shift_left(v___x_1043_, v___x_1034_);
v___x_1045_ = lean_uint64_sub(v___x_1044_, v___x_1043_);
v_remainder_1046_ = lean_uint64_land(v___y_998_, v___x_1045_);
v___x_1047_ = lean_uint64_sub(v___x_1034_, v___x_1043_);
v_half_1048_ = lean_uint64_shift_left(v___x_1043_, v___x_1047_);
v___x_1049_ = lean_uint64_dec_lt(v_remainder_1046_, v_half_1048_);
if (v___x_1049_ == 0)
{
uint8_t v___x_1050_; 
v___x_1050_ = lean_uint64_dec_lt(v_half_1048_, v_remainder_1046_);
if (v___x_1050_ == 0)
{
uint64_t v___x_1051_; uint8_t v___x_1052_; 
v___x_1051_ = lean_uint64_land(v_quotient_1042_, v___x_1043_);
v___x_1052_ = lean_uint64_dec_eq(v___x_1051_, v___y_999_);
if (v___x_1052_ == 0)
{
uint64_t v___x_1053_; 
v___x_1053_ = lean_uint64_add(v_quotient_1042_, v___x_1043_);
v___y_796_ = v___y_996_;
v___y_797_ = v___y_997_;
v___y_798_ = v___y_999_;
v___y_799_ = v___x_1053_;
goto v___jp_795_;
}
else
{
v___y_796_ = v___y_996_;
v___y_797_ = v___y_997_;
v___y_798_ = v___y_999_;
v___y_799_ = v_quotient_1042_;
goto v___jp_795_;
}
}
else
{
uint64_t v___x_1054_; 
v___x_1054_ = lean_uint64_add(v_quotient_1042_, v___x_1043_);
v___y_796_ = v___y_996_;
v___y_797_ = v___y_997_;
v___y_798_ = v___y_999_;
v___y_799_ = v___x_1054_;
goto v___jp_795_;
}
}
else
{
v___y_796_ = v___y_996_;
v___y_797_ = v___y_997_;
v___y_798_ = v___y_999_;
v___y_799_ = v_quotient_1042_;
goto v___jp_795_;
}
}
}
else
{
v___y_796_ = v___y_996_;
v___y_797_ = v___y_997_;
v___y_798_ = v___y_999_;
v___y_799_ = v___y_998_;
goto v___jp_795_;
}
}
}
}
v___jp_1055_:
{
uint64_t v___x_1063_; uint64_t v___x_1064_; uint8_t v___x_1065_; 
v___x_1063_ = 1ULL;
v___x_1064_ = lean_uint64_shift_right(v___y_1057_, v___x_1063_);
v___x_1065_ = lean_uint64_dec_eq(v___x_1064_, v___y_1060_);
if (v___x_1065_ == 0)
{
uint64_t v___x_1066_; 
v___x_1066_ = lean_uint64_add(v___y_1062_, v___x_1063_);
v___y_996_ = v___y_1056_;
v___y_997_ = v___y_1058_;
v___y_998_ = v___y_1059_;
v___y_999_ = v___y_1060_;
v___y_1000_ = v___y_1061_;
v___y_1001_ = v___x_1066_;
goto v___jp_995_;
}
else
{
v___y_996_ = v___y_1056_;
v___y_997_ = v___y_1058_;
v___y_998_ = v___y_1059_;
v___y_999_ = v___y_1060_;
v___y_1000_ = v___y_1061_;
v___y_1001_ = v___y_1062_;
goto v___jp_995_;
}
}
v___jp_1067_:
{
uint64_t v___x_1077_; uint8_t v___x_1078_; 
v___x_1077_ = lean_uint64_shift_right(v___y_1069_, v___y_1074_);
v___x_1078_ = lean_uint64_dec_eq(v___x_1077_, v___y_1073_);
if (v___x_1078_ == 0)
{
uint64_t v___x_1079_; 
v___x_1079_ = lean_uint64_add(v___y_1071_, v___y_1074_);
v___y_1056_ = v___y_1068_;
v___y_1057_ = v___y_1076_;
v___y_1058_ = v___y_1070_;
v___y_1059_ = v___y_1072_;
v___y_1060_ = v___y_1073_;
v___y_1061_ = v___y_1075_;
v___y_1062_ = v___x_1079_;
goto v___jp_1055_;
}
else
{
v___y_1056_ = v___y_1068_;
v___y_1057_ = v___y_1076_;
v___y_1058_ = v___y_1070_;
v___y_1059_ = v___y_1072_;
v___y_1060_ = v___y_1073_;
v___y_1061_ = v___y_1075_;
v___y_1062_ = v___y_1071_;
goto v___jp_1055_;
}
}
v___jp_1080_:
{
uint64_t v___x_1088_; uint64_t v___x_1089_; uint8_t v___x_1090_; 
v___x_1088_ = 2ULL;
v___x_1089_ = lean_uint64_shift_right(v___y_1082_, v___x_1088_);
v___x_1090_ = lean_uint64_dec_eq(v___x_1089_, v___y_1085_);
if (v___x_1090_ == 0)
{
v___y_1068_ = v___y_1081_;
v___y_1069_ = v___y_1082_;
v___y_1070_ = v___y_1083_;
v___y_1071_ = v___y_1087_;
v___y_1072_ = v___y_1084_;
v___y_1073_ = v___y_1085_;
v___y_1074_ = v___x_1088_;
v___y_1075_ = v___y_1086_;
v___y_1076_ = v___x_1089_;
goto v___jp_1067_;
}
else
{
v___y_1068_ = v___y_1081_;
v___y_1069_ = v___y_1082_;
v___y_1070_ = v___y_1083_;
v___y_1071_ = v___y_1087_;
v___y_1072_ = v___y_1084_;
v___y_1073_ = v___y_1085_;
v___y_1074_ = v___x_1088_;
v___y_1075_ = v___y_1086_;
v___y_1076_ = v___y_1082_;
goto v___jp_1067_;
}
}
v___jp_1091_:
{
uint64_t v___x_1101_; uint8_t v___x_1102_; 
v___x_1101_ = lean_uint64_shift_right(v___y_1095_, v___y_1098_);
v___x_1102_ = lean_uint64_dec_eq(v___x_1101_, v___y_1097_);
if (v___x_1102_ == 0)
{
uint64_t v___x_1103_; 
v___x_1103_ = lean_uint64_add(v___y_1093_, v___y_1098_);
v___y_1081_ = v___y_1092_;
v___y_1082_ = v___y_1100_;
v___y_1083_ = v___y_1094_;
v___y_1084_ = v___y_1096_;
v___y_1085_ = v___y_1097_;
v___y_1086_ = v___y_1099_;
v___y_1087_ = v___x_1103_;
goto v___jp_1080_;
}
else
{
v___y_1081_ = v___y_1092_;
v___y_1082_ = v___y_1100_;
v___y_1083_ = v___y_1094_;
v___y_1084_ = v___y_1096_;
v___y_1085_ = v___y_1097_;
v___y_1086_ = v___y_1099_;
v___y_1087_ = v___y_1093_;
goto v___jp_1080_;
}
}
v___jp_1104_:
{
uint64_t v___x_1112_; uint64_t v___x_1113_; uint8_t v___x_1114_; 
v___x_1112_ = 4ULL;
v___x_1113_ = lean_uint64_shift_right(v___y_1107_, v___x_1112_);
v___x_1114_ = lean_uint64_dec_eq(v___x_1113_, v___y_1109_);
if (v___x_1114_ == 0)
{
v___y_1092_ = v___y_1105_;
v___y_1093_ = v___y_1111_;
v___y_1094_ = v___y_1106_;
v___y_1095_ = v___y_1107_;
v___y_1096_ = v___y_1108_;
v___y_1097_ = v___y_1109_;
v___y_1098_ = v___x_1112_;
v___y_1099_ = v___y_1110_;
v___y_1100_ = v___x_1113_;
goto v___jp_1091_;
}
else
{
v___y_1092_ = v___y_1105_;
v___y_1093_ = v___y_1111_;
v___y_1094_ = v___y_1106_;
v___y_1095_ = v___y_1107_;
v___y_1096_ = v___y_1108_;
v___y_1097_ = v___y_1109_;
v___y_1098_ = v___x_1112_;
v___y_1099_ = v___y_1110_;
v___y_1100_ = v___y_1107_;
goto v___jp_1091_;
}
}
v___jp_1115_:
{
uint64_t v___x_1125_; uint8_t v___x_1126_; 
v___x_1125_ = lean_uint64_shift_right(v___y_1119_, v___y_1121_);
v___x_1126_ = lean_uint64_dec_eq(v___x_1125_, v___y_1122_);
if (v___x_1126_ == 0)
{
uint64_t v___x_1127_; 
v___x_1127_ = lean_uint64_add(v___y_1116_, v___y_1121_);
v___y_1105_ = v___y_1117_;
v___y_1106_ = v___y_1118_;
v___y_1107_ = v___y_1124_;
v___y_1108_ = v___y_1120_;
v___y_1109_ = v___y_1122_;
v___y_1110_ = v___y_1123_;
v___y_1111_ = v___x_1127_;
goto v___jp_1104_;
}
else
{
v___y_1105_ = v___y_1117_;
v___y_1106_ = v___y_1118_;
v___y_1107_ = v___y_1124_;
v___y_1108_ = v___y_1120_;
v___y_1109_ = v___y_1122_;
v___y_1110_ = v___y_1123_;
v___y_1111_ = v___y_1116_;
goto v___jp_1104_;
}
}
v___jp_1128_:
{
uint64_t v___x_1136_; uint64_t v___x_1137_; uint8_t v___x_1138_; 
v___x_1136_ = 8ULL;
v___x_1137_ = lean_uint64_shift_right(v___y_1131_, v___x_1136_);
v___x_1138_ = lean_uint64_dec_eq(v___x_1137_, v___y_1133_);
if (v___x_1138_ == 0)
{
v___y_1116_ = v___y_1135_;
v___y_1117_ = v___y_1129_;
v___y_1118_ = v___y_1130_;
v___y_1119_ = v___y_1131_;
v___y_1120_ = v___y_1132_;
v___y_1121_ = v___x_1136_;
v___y_1122_ = v___y_1133_;
v___y_1123_ = v___y_1134_;
v___y_1124_ = v___x_1137_;
goto v___jp_1115_;
}
else
{
v___y_1116_ = v___y_1135_;
v___y_1117_ = v___y_1129_;
v___y_1118_ = v___y_1130_;
v___y_1119_ = v___y_1131_;
v___y_1120_ = v___y_1132_;
v___y_1121_ = v___x_1136_;
v___y_1122_ = v___y_1133_;
v___y_1123_ = v___y_1134_;
v___y_1124_ = v___y_1131_;
goto v___jp_1115_;
}
}
v___jp_1139_:
{
uint64_t v___x_1149_; uint8_t v___x_1150_; 
v___x_1149_ = lean_uint64_shift_right(v___y_1143_, v___y_1146_);
v___x_1150_ = lean_uint64_dec_eq(v___x_1149_, v___y_1145_);
if (v___x_1150_ == 0)
{
uint64_t v___x_1151_; 
v___x_1151_ = lean_uint64_add(v___y_1140_, v___y_1146_);
v___y_1129_ = v___y_1141_;
v___y_1130_ = v___y_1142_;
v___y_1131_ = v___y_1148_;
v___y_1132_ = v___y_1144_;
v___y_1133_ = v___y_1145_;
v___y_1134_ = v___y_1147_;
v___y_1135_ = v___x_1151_;
goto v___jp_1128_;
}
else
{
v___y_1129_ = v___y_1141_;
v___y_1130_ = v___y_1142_;
v___y_1131_ = v___y_1148_;
v___y_1132_ = v___y_1144_;
v___y_1133_ = v___y_1145_;
v___y_1134_ = v___y_1147_;
v___y_1135_ = v___y_1140_;
goto v___jp_1128_;
}
}
v___jp_1152_:
{
uint64_t v___x_1160_; uint64_t v___x_1161_; uint8_t v___x_1162_; 
v___x_1160_ = 16ULL;
v___x_1161_ = lean_uint64_shift_right(v___y_1156_, v___x_1160_);
v___x_1162_ = lean_uint64_dec_eq(v___x_1161_, v___y_1157_);
if (v___x_1162_ == 0)
{
v___y_1140_ = v___y_1159_;
v___y_1141_ = v___y_1153_;
v___y_1142_ = v___y_1154_;
v___y_1143_ = v___y_1156_;
v___y_1144_ = v___y_1155_;
v___y_1145_ = v___y_1157_;
v___y_1146_ = v___x_1160_;
v___y_1147_ = v___y_1158_;
v___y_1148_ = v___x_1161_;
goto v___jp_1139_;
}
else
{
v___y_1140_ = v___y_1159_;
v___y_1141_ = v___y_1153_;
v___y_1142_ = v___y_1154_;
v___y_1143_ = v___y_1156_;
v___y_1144_ = v___y_1155_;
v___y_1145_ = v___y_1157_;
v___y_1146_ = v___x_1160_;
v___y_1147_ = v___y_1158_;
v___y_1148_ = v___y_1156_;
goto v___jp_1139_;
}
}
v___jp_1163_:
{
uint64_t v___x_1171_; uint8_t v___x_1172_; 
v___x_1171_ = lean_uint64_shift_right(v___y_1167_, v___y_1164_);
v___x_1172_ = lean_uint64_dec_eq(v___x_1171_, v___y_1168_);
if (v___x_1172_ == 0)
{
v___y_1153_ = v___y_1165_;
v___y_1154_ = v___y_1166_;
v___y_1155_ = v___y_1167_;
v___y_1156_ = v___y_1170_;
v___y_1157_ = v___y_1168_;
v___y_1158_ = v___y_1169_;
v___y_1159_ = v___y_1164_;
goto v___jp_1152_;
}
else
{
v___y_1153_ = v___y_1165_;
v___y_1154_ = v___y_1166_;
v___y_1155_ = v___y_1167_;
v___y_1156_ = v___y_1170_;
v___y_1157_ = v___y_1168_;
v___y_1158_ = v___y_1169_;
v___y_1159_ = v___y_1168_;
goto v___jp_1152_;
}
}
v___jp_1173_:
{
uint64_t v___x_1178_; uint8_t v___x_1179_; 
v___x_1178_ = 0ULL;
v___x_1179_ = lean_uint64_dec_eq(v___y_1176_, v___x_1178_);
if (v___x_1179_ == 0)
{
uint64_t v___x_1180_; uint64_t v___x_1181_; uint8_t v___x_1182_; 
v___x_1180_ = 32ULL;
v___x_1181_ = lean_uint64_shift_right(v___y_1176_, v___x_1180_);
v___x_1182_ = lean_uint64_dec_eq(v___x_1181_, v___x_1178_);
if (v___x_1182_ == 0)
{
v___y_1164_ = v___x_1180_;
v___y_1165_ = v___y_1174_;
v___y_1166_ = v___y_1175_;
v___y_1167_ = v___y_1176_;
v___y_1168_ = v___x_1178_;
v___y_1169_ = v___y_1177_;
v___y_1170_ = v___x_1181_;
goto v___jp_1163_;
}
else
{
v___y_1164_ = v___x_1180_;
v___y_1165_ = v___y_1174_;
v___y_1166_ = v___y_1175_;
v___y_1167_ = v___y_1176_;
v___y_1168_ = v___x_1178_;
v___y_1169_ = v___y_1177_;
v___y_1170_ = v___y_1176_;
goto v___jp_1163_;
}
}
else
{
if (v___y_1175_ == 0)
{
uint32_t v___x_1183_; 
v___x_1183_ = 0;
return v___x_1183_;
}
else
{
uint32_t v___x_1184_; 
v___x_1184_ = 2147483648;
return v___x_1184_;
}
}
}
v___jp_1185_:
{
uint64_t v___x_1192_; uint64_t v___x_1193_; uint64_t v___x_1194_; uint8_t v___x_1195_; 
v___x_1192_ = lean_uint64_mul(v___y_1190_, v___y_1189_);
v___x_1193_ = lean_uint64_add(v___y_1188_, v___y_1191_);
v___x_1194_ = 281474976710656ULL;
v___x_1195_ = lean_uint64_dec_lt(v___x_1192_, v___x_1194_);
if (v___x_1195_ == 0)
{
v___y_1174_ = v___y_1186_;
v___y_1175_ = v___y_1187_;
v___y_1176_ = v___x_1192_;
v___y_1177_ = v___x_1193_;
goto v___jp_1173_;
}
else
{
uint64_t v___x_1196_; uint8_t v___x_1197_; 
v___x_1196_ = 123ULL;
v___x_1197_ = lean_uint64_dec_le(v___x_1193_, v___x_1196_);
if (v___x_1197_ == 0)
{
v___y_1174_ = v___y_1186_;
v___y_1175_ = v___y_1187_;
v___y_1176_ = v___x_1192_;
v___y_1177_ = v___x_1193_;
goto v___jp_1173_;
}
else
{
uint64_t v___x_1198_; uint8_t v___x_1199_; 
v___x_1198_ = 0ULL;
v___x_1199_ = lean_uint64_dec_eq(v___x_1192_, v___x_1198_);
if (v___x_1199_ == 0)
{
uint64_t v___x_1200_; uint64_t v___x_1201_; uint8_t v___x_1202_; 
v___x_1200_ = 149ULL;
v___x_1201_ = lean_uint64_sub(v___x_1200_, v___x_1193_);
v___x_1202_ = lean_uint64_dec_eq(v___x_1201_, v___x_1198_);
if (v___x_1202_ == 0)
{
uint64_t v___x_1203_; uint8_t v___x_1204_; 
v___x_1203_ = 64ULL;
v___x_1204_ = lean_uint64_dec_lt(v___x_1201_, v___x_1203_);
if (v___x_1204_ == 0)
{
uint8_t v___x_1205_; 
v___x_1205_ = lean_uint64_dec_eq(v___x_1201_, v___x_1203_);
if (v___x_1205_ == 0)
{
v___y_817_ = v___y_1186_;
v___y_818_ = v___y_1187_;
v___y_819_ = v___x_1198_;
v___y_820_ = v___x_1198_;
goto v___jp_816_;
}
else
{
uint64_t v___x_1206_; uint8_t v___x_1207_; 
v___x_1206_ = 9223372036854775808ULL;
v___x_1207_ = lean_uint64_dec_lt(v___x_1206_, v___x_1192_);
if (v___x_1207_ == 0)
{
v___y_817_ = v___y_1186_;
v___y_818_ = v___y_1187_;
v___y_819_ = v___x_1198_;
v___y_820_ = v___x_1198_;
goto v___jp_816_;
}
else
{
uint64_t v___x_1208_; 
v___x_1208_ = 1ULL;
v___y_817_ = v___y_1186_;
v___y_818_ = v___y_1187_;
v___y_819_ = v___x_1198_;
v___y_820_ = v___x_1208_;
goto v___jp_816_;
}
}
}
else
{
uint64_t v_quotient_1209_; uint64_t v___x_1210_; uint64_t v___x_1211_; uint64_t v___x_1212_; uint64_t v_remainder_1213_; uint64_t v___x_1214_; uint64_t v_half_1215_; uint8_t v___x_1216_; 
v_quotient_1209_ = lean_uint64_shift_right(v___x_1192_, v___x_1201_);
v___x_1210_ = 1ULL;
v___x_1211_ = lean_uint64_shift_left(v___x_1210_, v___x_1201_);
v___x_1212_ = lean_uint64_sub(v___x_1211_, v___x_1210_);
v_remainder_1213_ = lean_uint64_land(v___x_1192_, v___x_1212_);
v___x_1214_ = lean_uint64_sub(v___x_1201_, v___x_1210_);
v_half_1215_ = lean_uint64_shift_left(v___x_1210_, v___x_1214_);
v___x_1216_ = lean_uint64_dec_lt(v_remainder_1213_, v_half_1215_);
if (v___x_1216_ == 0)
{
uint8_t v___x_1217_; 
v___x_1217_ = lean_uint64_dec_lt(v_half_1215_, v_remainder_1213_);
if (v___x_1217_ == 0)
{
uint64_t v___x_1218_; uint8_t v___x_1219_; 
v___x_1218_ = lean_uint64_land(v_quotient_1209_, v___x_1210_);
v___x_1219_ = lean_uint64_dec_eq(v___x_1218_, v___x_1198_);
if (v___x_1219_ == 0)
{
uint64_t v___x_1220_; 
v___x_1220_ = lean_uint64_add(v_quotient_1209_, v___x_1210_);
v___y_817_ = v___y_1186_;
v___y_818_ = v___y_1187_;
v___y_819_ = v___x_1198_;
v___y_820_ = v___x_1220_;
goto v___jp_816_;
}
else
{
v___y_817_ = v___y_1186_;
v___y_818_ = v___y_1187_;
v___y_819_ = v___x_1198_;
v___y_820_ = v_quotient_1209_;
goto v___jp_816_;
}
}
else
{
uint64_t v___x_1221_; 
v___x_1221_ = lean_uint64_add(v_quotient_1209_, v___x_1210_);
v___y_817_ = v___y_1186_;
v___y_818_ = v___y_1187_;
v___y_819_ = v___x_1198_;
v___y_820_ = v___x_1221_;
goto v___jp_816_;
}
}
else
{
v___y_817_ = v___y_1186_;
v___y_818_ = v___y_1187_;
v___y_819_ = v___x_1198_;
v___y_820_ = v_quotient_1209_;
goto v___jp_816_;
}
}
}
else
{
v___y_817_ = v___y_1186_;
v___y_818_ = v___y_1187_;
v___y_819_ = v___x_1198_;
v___y_820_ = v___x_1192_;
goto v___jp_816_;
}
}
else
{
if (v___y_1187_ == 0)
{
uint32_t v___x_1222_; 
v___x_1222_ = 0;
return v___x_1222_;
}
else
{
uint32_t v___x_1223_; 
v___x_1223_ = 2147483648;
return v___x_1223_;
}
}
}
}
}
v___jp_1227_:
{
uint64_t v___x_1233_; uint64_t v___x_1234_; uint8_t v___x_1235_; 
v___x_1233_ = lean_uint32_to_uint64(v_ey_1226_);
v___x_1234_ = 0ULL;
v___x_1235_ = lean_uint64_dec_eq(v___x_1233_, v___x_1234_);
if (v___x_1235_ == 0)
{
uint64_t v___x_1236_; uint64_t v___x_1237_; 
v___x_1236_ = 1ULL;
v___x_1237_ = lean_uint64_sub(v___x_1233_, v___x_1236_);
v___y_1186_ = v___y_1228_;
v___y_1187_ = v___y_1229_;
v___y_1188_ = v___y_1232_;
v___y_1189_ = v___y_1230_;
v___y_1190_ = v___y_1231_;
v___y_1191_ = v___x_1237_;
goto v___jp_1185_;
}
else
{
v___y_1186_ = v___y_1228_;
v___y_1187_ = v___y_1229_;
v___y_1188_ = v___y_1232_;
v___y_1189_ = v___y_1230_;
v___y_1190_ = v___y_1231_;
v___y_1191_ = v___x_1234_;
goto v___jp_1185_;
}
}
v___jp_1238_:
{
uint64_t v___x_1243_; uint64_t v___x_1244_; uint8_t v___x_1245_; 
v___x_1243_ = lean_uint32_to_uint64(v_ex_1224_);
v___x_1244_ = 0ULL;
v___x_1245_ = lean_uint64_dec_eq(v___x_1243_, v___x_1244_);
if (v___x_1245_ == 0)
{
uint64_t v___x_1246_; uint64_t v___x_1247_; 
v___x_1246_ = 1ULL;
v___x_1247_ = lean_uint64_sub(v___x_1243_, v___x_1246_);
v___y_1228_ = v___y_1239_;
v___y_1229_ = v___y_1240_;
v___y_1230_ = v___y_1242_;
v___y_1231_ = v___y_1241_;
v___y_1232_ = v___x_1247_;
goto v___jp_1227_;
}
else
{
v___y_1228_ = v___y_1239_;
v___y_1229_ = v___y_1240_;
v___y_1230_ = v___y_1242_;
v___y_1231_ = v___y_1241_;
v___y_1232_ = v___x_1244_;
goto v___jp_1227_;
}
}
v___jp_1248_:
{
uint32_t v___x_1253_; uint8_t v___x_1254_; 
v___x_1253_ = 0;
v___x_1254_ = lean_uint32_dec_eq(v_ey_1226_, v___x_1253_);
if (v___x_1254_ == 0)
{
uint64_t v___x_1255_; uint64_t v___x_1256_; uint64_t v___x_1257_; 
v___x_1255_ = lean_uint32_to_uint64(v___y_1251_);
v___x_1256_ = 8388608ULL;
v___x_1257_ = lean_uint64_lor(v___x_1255_, v___x_1256_);
v___y_1239_ = v___y_1249_;
v___y_1240_ = v___y_1250_;
v___y_1241_ = v___y_1252_;
v___y_1242_ = v___x_1257_;
goto v___jp_1238_;
}
else
{
uint64_t v___x_1258_; 
v___x_1258_ = lean_uint32_to_uint64(v___y_1251_);
v___y_1239_ = v___y_1249_;
v___y_1240_ = v___y_1250_;
v___y_1241_ = v___y_1252_;
v___y_1242_ = v___x_1258_;
goto v___jp_1238_;
}
}
v___jp_1259_:
{
uint32_t v___x_1261_; uint32_t v_xFraction_1262_; uint32_t v_yFraction_1263_; uint32_t v___x_1264_; uint8_t v___x_1265_; 
v___x_1261_ = 8388607;
v_xFraction_1262_ = lean_uint32_land(v___y_779_, v___x_1261_);
v_yFraction_1263_ = lean_uint32_land(v___y_780_, v___x_1261_);
v___x_1264_ = 0;
v___x_1265_ = lean_uint32_dec_eq(v_ex_1224_, v___x_1264_);
if (v___x_1265_ == 0)
{
uint64_t v___x_1266_; uint64_t v___x_1267_; uint64_t v___x_1268_; 
v___x_1266_ = lean_uint32_to_uint64(v_xFraction_1262_);
v___x_1267_ = 8388608ULL;
v___x_1268_ = lean_uint64_lor(v___x_1266_, v___x_1267_);
v___y_1249_ = v___x_1261_;
v___y_1250_ = v___y_1260_;
v___y_1251_ = v_yFraction_1263_;
v___y_1252_ = v___x_1268_;
goto v___jp_1248_;
}
else
{
uint64_t v___x_1269_; 
v___x_1269_ = lean_uint32_to_uint64(v_xFraction_1262_);
v___y_1249_ = v___x_1261_;
v___y_1250_ = v___y_1260_;
v___y_1251_ = v_yFraction_1263_;
v___y_1252_ = v___x_1269_;
goto v___jp_1248_;
}
}
v___jp_1273_:
{
if (v___y_1275_ == 0)
{
v___y_1260_ = v___x_1272_;
goto v___jp_1259_;
}
else
{
v___y_1260_ = v___y_1274_;
goto v___jp_1259_;
}
}
v___jp_1276_:
{
if (v___y_1278_ == 0)
{
if (v___y_1279_ == 0)
{
v___y_1274_ = v___y_1277_;
v___y_1275_ = v___x_1272_;
goto v___jp_1273_;
}
else
{
v___y_1260_ = v___x_1272_;
goto v___jp_1259_;
}
}
else
{
v___y_1274_ = v___y_1277_;
v___y_1275_ = v___y_1279_;
goto v___jp_1273_;
}
}
v___jp_1280_:
{
uint32_t v___x_1283_; uint32_t v___x_1284_; uint32_t v___x_1285_; uint8_t v___x_1286_; 
v___x_1283_ = 2147483648;
v___x_1284_ = lean_uint32_land(v___y_780_, v___x_1283_);
v___x_1285_ = 0;
v___x_1286_ = lean_uint32_dec_eq(v___x_1284_, v___x_1285_);
if (v___x_1286_ == 0)
{
v___y_1277_ = v___y_1281_;
v___y_1278_ = v___y_1282_;
v___y_1279_ = v___x_1272_;
goto v___jp_1276_;
}
else
{
v___y_1277_ = v___y_1281_;
v___y_1278_ = v___y_1282_;
v___y_1279_ = v___y_1281_;
goto v___jp_1276_;
}
}
v___jp_1287_:
{
if (v___y_1288_ == 0)
{
uint32_t v___x_1289_; uint32_t v___x_1290_; uint32_t v___x_1291_; uint8_t v___x_1292_; 
v___x_1289_ = 2147483648;
v___x_1290_ = lean_uint32_land(v___y_779_, v___x_1289_);
v___x_1291_ = 0;
v___x_1292_ = lean_uint32_dec_eq(v___x_1290_, v___x_1291_);
if (v___x_1292_ == 0)
{
v___y_1281_ = v___y_1288_;
v___y_1282_ = v___x_1272_;
goto v___jp_1280_;
}
else
{
v___y_1281_ = v___y_1288_;
v___y_1282_ = v___y_1288_;
goto v___jp_1280_;
}
}
else
{
lean_object* v___x_1293_; lean_object* v___x_1294_; lean_object* v___x_1295_; uint32_t v___x_1296_; 
v___x_1293_ = lean_uint32_to_nat(v___y_779_);
v___x_1294_ = lean_uint32_to_nat(v___y_780_);
v___x_1295_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1293_, v___x_1294_);
v___x_1296_ = lean_uint32_of_nat(v___x_1295_);
lean_dec(v___x_1295_);
return v___x_1296_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_runF64Native___lam__1___boxed(lean_object* v___y_1311_, lean_object* v___y_1312_){
_start:
{
uint32_t v___y_1946__boxed_1313_; uint32_t v___y_1947__boxed_1314_; uint32_t v_res_1315_; lean_object* v_r_1316_; 
v___y_1946__boxed_1313_ = lean_unbox_uint32(v___y_1311_);
lean_dec(v___y_1311_);
v___y_1947__boxed_1314_ = lean_unbox_uint32(v___y_1312_);
lean_dec(v___y_1312_);
v_res_1315_ = lp_competition_runF64Native___lam__1(v___y_1946__boxed_1313_, v___y_1947__boxed_1314_);
v_r_1316_ = lean_box_uint32(v_res_1315_);
return v_r_1316_;
}
}
LEAN_EXPORT lean_object* lp_competition_runF64Native(){
_start:
{
lean_object* v___f_1320_; lean_object* v___f_1321_; lean_object* v___x_1322_; lean_object* v___x_1323_; lean_object* v___x_1324_; 
v___f_1320_ = ((lean_object*)(lp_competition_runF64Native___closed__0));
v___f_1321_ = ((lean_object*)(lp_competition_runF64Native___closed__1));
v___x_1322_ = ((lean_object*)(lp_competition_runControl___closed__2));
v___x_1323_ = ((lean_object*)(lp_competition_runControl___closed__3));
v___x_1324_ = lp_competition_Bench_Suite_run(v___f_1320_, v___f_1321_, v___x_1322_, v___x_1323_);
return v___x_1324_;
}
}
LEAN_EXPORT lean_object* lp_competition_runF64Native___boxed(lean_object* v_a_1325_){
_start:
{
lean_object* v_res_1326_; 
v_res_1326_ = lp_competition_runF64Native();
return v_res_1326_;
}
}
static lean_object* _init_lp_competition_runF64Boxed___lam__0___boxed__const__1(void){
_start:
{
double v___x_1327_; lean_object* v___x_1328_; 
v___x_1327_ = l_instInhabitedFloat;
v___x_1328_ = lean_box_float(v___x_1327_);
return v___x_1328_;
}
}
LEAN_EXPORT uint32_t lp_competition_runF64Boxed___lam__0(uint32_t v___y_1329_, uint32_t v___y_1330_){
_start:
{
uint32_t v___x_1331_; uint32_t v___x_1332_; uint8_t v___x_1333_; 
v___x_1331_ = 2139095040;
v___x_1332_ = lean_uint32_land(v___y_1329_, v___x_1331_);
v___x_1333_ = lean_uint32_dec_eq(v___x_1332_, v___x_1331_);
if (v___x_1333_ == 0)
{
uint32_t v___x_1334_; uint8_t v___x_1335_; 
v___x_1334_ = lean_uint32_land(v___y_1330_, v___x_1331_);
v___x_1335_ = lean_uint32_dec_eq(v___x_1334_, v___x_1331_);
if (v___x_1335_ == 0)
{
uint32_t v___y_1337_; lean_object* v___y_1338_; double v___y_1339_; uint32_t v___y_1340_; uint32_t v___y_1399_; uint32_t v___x_1415_; uint32_t v___x_1416_; uint32_t v___x_1417_; uint8_t v___x_1418_; 
v___x_1415_ = 8388607;
v___x_1416_ = lean_uint32_land(v___y_1329_, v___x_1415_);
v___x_1417_ = 0;
v___x_1418_ = lean_uint32_dec_eq(v___x_1332_, v___x_1417_);
if (v___x_1418_ == 0)
{
uint32_t v___x_1419_; uint32_t v___x_1420_; 
v___x_1419_ = 8388608;
v___x_1420_ = lean_uint32_lor(v___x_1416_, v___x_1419_);
v___y_1399_ = v___x_1420_;
goto v___jp_1398_;
}
else
{
v___y_1399_ = v___x_1416_;
goto v___jp_1398_;
}
v___jp_1336_:
{
double v___x_1341_; uint32_t v___x_1342_; lean_object* v___x_1343_; lean_object* v___x_1344_; lean_object* v___x_1345_; double v___x_1346_; double v___x_1347_; double v___x_1348_; uint64_t v___x_1349_; uint64_t v___x_1350_; uint64_t v___x_1351_; uint32_t v___x_1352_; uint32_t v___x_1353_; uint32_t v_sign_1354_; uint64_t v___x_1355_; uint64_t v___x_1356_; uint64_t v___x_1357_; uint64_t v_e_1358_; uint64_t v___x_1359_; uint8_t v___x_1360_; 
v___x_1341_ = lean_uint32_to_float(v___y_1340_);
v___x_1342_ = lean_uint32_shift_right(v___y_1330_, v___y_1337_);
v___x_1343_ = lean_uint32_to_nat(v___x_1342_);
v___x_1344_ = lp_competition_runF64Boxed___lam__0___boxed__const__1;
v___x_1345_ = lean_array_get_borrowed(v___x_1344_, v___y_1338_, v___x_1343_);
lean_dec(v___x_1343_);
v___x_1346_ = lean_unbox_float(v___x_1345_);
v___x_1347_ = lean_float_mul(v___x_1341_, v___x_1346_);
v___x_1348_ = lean_float_add(v___y_1339_, v___x_1347_);
v___x_1349_ = lean_float_to_bits(v___x_1348_);
v___x_1350_ = 32ULL;
v___x_1351_ = lean_uint64_shift_right(v___x_1349_, v___x_1350_);
v___x_1352_ = lean_uint64_to_uint32(v___x_1351_);
v___x_1353_ = 2147483648;
v_sign_1354_ = lean_uint32_land(v___x_1352_, v___x_1353_);
v___x_1355_ = 52ULL;
v___x_1356_ = lean_uint64_shift_right(v___x_1349_, v___x_1355_);
v___x_1357_ = 2047ULL;
v_e_1358_ = lean_uint64_land(v___x_1356_, v___x_1357_);
v___x_1359_ = 873ULL;
v___x_1360_ = lean_uint64_dec_lt(v_e_1358_, v___x_1359_);
if (v___x_1360_ == 0)
{
uint64_t v___x_1361_; uint8_t v___x_1362_; 
v___x_1361_ = 1150ULL;
v___x_1362_ = lean_uint64_dec_lt(v___x_1361_, v_e_1358_);
if (v___x_1362_ == 0)
{
uint64_t v___x_1363_; uint64_t v___x_1364_; uint64_t v___x_1365_; uint64_t v_m_1366_; uint64_t v___x_1367_; uint8_t v___x_1368_; 
v___x_1363_ = 4503599627370495ULL;
v___x_1364_ = lean_uint64_land(v___x_1349_, v___x_1363_);
v___x_1365_ = 4503599627370496ULL;
v_m_1366_ = lean_uint64_lor(v___x_1364_, v___x_1365_);
v___x_1367_ = 897ULL;
v___x_1368_ = lean_uint64_dec_lt(v_e_1358_, v___x_1367_);
if (v___x_1368_ == 0)
{
uint64_t v___x_1369_; uint64_t v___x_1370_; uint64_t v___x_1371_; uint64_t v___x_1372_; uint64_t v___x_1373_; uint64_t v___x_1374_; uint64_t v___x_1375_; uint64_t v___x_1376_; uint32_t v_q_1377_; uint32_t v___x_1378_; uint32_t v___x_1379_; uint32_t v___x_1380_; uint32_t v___x_1381_; uint32_t v___x_1382_; uint32_t v___x_1383_; 
v___x_1369_ = 268435455ULL;
v___x_1370_ = lean_uint64_add(v_m_1366_, v___x_1369_);
v___x_1371_ = 29ULL;
v___x_1372_ = lean_uint64_shift_right(v_m_1366_, v___x_1371_);
v___x_1373_ = 1ULL;
v___x_1374_ = lean_uint64_land(v___x_1372_, v___x_1373_);
v___x_1375_ = lean_uint64_add(v___x_1370_, v___x_1374_);
v___x_1376_ = lean_uint64_shift_right(v___x_1375_, v___x_1371_);
v_q_1377_ = lean_uint64_to_uint32(v___x_1376_);
v___x_1378_ = lean_uint64_to_uint32(v_e_1358_);
v___x_1379_ = 897;
v___x_1380_ = lean_uint32_sub(v___x_1378_, v___x_1379_);
v___x_1381_ = lean_uint32_shift_left(v___x_1380_, v___y_1337_);
v___x_1382_ = lean_uint32_add(v___x_1381_, v_q_1377_);
v___x_1383_ = lean_uint32_lor(v_sign_1354_, v___x_1382_);
return v___x_1383_;
}
else
{
uint64_t v___x_1384_; uint64_t v_d_1385_; uint64_t v___x_1386_; uint64_t v___x_1387_; uint64_t v___x_1388_; uint64_t v___x_1389_; uint64_t v___x_1390_; uint64_t v___x_1391_; uint64_t v___x_1392_; uint64_t v___x_1393_; uint64_t v_q_1394_; uint32_t v___x_1395_; uint32_t v___x_1396_; 
v___x_1384_ = 926ULL;
v_d_1385_ = lean_uint64_sub(v___x_1384_, v_e_1358_);
v___x_1386_ = 1ULL;
v___x_1387_ = lean_uint64_sub(v_d_1385_, v___x_1386_);
v___x_1388_ = lean_uint64_shift_left(v___x_1386_, v___x_1387_);
v___x_1389_ = lean_uint64_sub(v___x_1388_, v___x_1386_);
v___x_1390_ = lean_uint64_add(v_m_1366_, v___x_1389_);
v___x_1391_ = lean_uint64_shift_right(v_m_1366_, v_d_1385_);
v___x_1392_ = lean_uint64_land(v___x_1391_, v___x_1386_);
v___x_1393_ = lean_uint64_add(v___x_1390_, v___x_1392_);
v_q_1394_ = lean_uint64_shift_right(v___x_1393_, v_d_1385_);
v___x_1395_ = lean_uint64_to_uint32(v_q_1394_);
v___x_1396_ = lean_uint32_lor(v_sign_1354_, v___x_1395_);
return v___x_1396_;
}
}
else
{
uint32_t v___x_1397_; 
v___x_1397_ = lean_uint32_lor(v_sign_1354_, v___x_1331_);
return v___x_1397_;
}
}
else
{
return v_sign_1354_;
}
}
v___jp_1398_:
{
double v___x_1400_; lean_object* v___x_1401_; uint32_t v___x_1402_; uint32_t v___x_1403_; lean_object* v___x_1404_; lean_object* v___x_1405_; lean_object* v___x_1406_; double v___x_1407_; double v___x_1408_; uint32_t v___x_1409_; uint32_t v___x_1410_; uint32_t v___x_1411_; uint8_t v___x_1412_; 
v___x_1400_ = lean_uint32_to_float(v___y_1399_);
v___x_1401_ = lp_competition_Submission_R24F64Add_boxedScales;
v___x_1402_ = 23;
v___x_1403_ = lean_uint32_shift_right(v___y_1329_, v___x_1402_);
v___x_1404_ = lean_uint32_to_nat(v___x_1403_);
v___x_1405_ = lp_competition_runF64Boxed___lam__0___boxed__const__1;
v___x_1406_ = lean_array_get_borrowed(v___x_1405_, v___x_1401_, v___x_1404_);
lean_dec(v___x_1404_);
v___x_1407_ = lean_unbox_float(v___x_1406_);
v___x_1408_ = lean_float_mul(v___x_1400_, v___x_1407_);
v___x_1409_ = 8388607;
v___x_1410_ = lean_uint32_land(v___y_1330_, v___x_1409_);
v___x_1411_ = 0;
v___x_1412_ = lean_uint32_dec_eq(v___x_1334_, v___x_1411_);
if (v___x_1412_ == 0)
{
uint32_t v___x_1413_; uint32_t v___x_1414_; 
v___x_1413_ = 8388608;
v___x_1414_ = lean_uint32_lor(v___x_1410_, v___x_1413_);
v___y_1337_ = v___x_1402_;
v___y_1338_ = v___x_1401_;
v___y_1339_ = v___x_1408_;
v___y_1340_ = v___x_1414_;
goto v___jp_1336_;
}
else
{
v___y_1337_ = v___x_1402_;
v___y_1338_ = v___x_1401_;
v___y_1339_ = v___x_1408_;
v___y_1340_ = v___x_1410_;
goto v___jp_1336_;
}
}
}
else
{
uint32_t v___x_1421_; 
v___x_1421_ = lp_competition_Submission_R24F64Add_retainedAdd(v___y_1329_, v___y_1330_);
return v___x_1421_;
}
}
else
{
uint32_t v___x_1422_; 
v___x_1422_ = lp_competition_Submission_R24F64Add_retainedAdd(v___y_1329_, v___y_1330_);
return v___x_1422_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_runF64Boxed___lam__0___boxed(lean_object* v___y_1423_, lean_object* v___y_1424_){
_start:
{
uint32_t v___y_1764__boxed_1425_; uint32_t v___y_1765__boxed_1426_; uint32_t v_res_1427_; lean_object* v_r_1428_; 
v___y_1764__boxed_1425_ = lean_unbox_uint32(v___y_1423_);
lean_dec(v___y_1423_);
v___y_1765__boxed_1426_ = lean_unbox_uint32(v___y_1424_);
lean_dec(v___y_1424_);
v_res_1427_ = lp_competition_runF64Boxed___lam__0(v___y_1764__boxed_1425_, v___y_1765__boxed_1426_);
v_r_1428_ = lean_box_uint32(v_res_1427_);
return v_r_1428_;
}
}
LEAN_EXPORT uint32_t lp_competition_runF64Boxed___lam__1(uint32_t v___y_1429_, uint32_t v___y_1430_){
_start:
{
uint32_t v___y_1432_; uint32_t v___y_1436_; uint32_t v___y_1440_; uint32_t v___y_1441_; uint32_t v___y_1442_; uint64_t v___y_1446_; uint32_t v___y_1447_; uint8_t v___y_1448_; uint64_t v___y_1449_; uint32_t v___y_1461_; uint32_t v___y_1462_; uint32_t v___y_1463_; uint64_t v___y_1467_; uint32_t v___y_1468_; uint8_t v___y_1469_; uint64_t v___y_1470_; uint8_t v___y_1482_; uint8_t v___y_1498_; uint8_t v___y_1512_; uint8_t v___y_1529_; float v___y_1536_; float v___y_1537_; float v___y_1551_; uint8_t v___y_1552_; float v___y_1567_; uint32_t v___x_1576_; uint32_t v___x_1577_; uint8_t v___y_1579_; uint32_t v___x_1591_; uint32_t v___y_1593_; uint32_t v___y_1594_; uint32_t v___y_1595_; uint32_t v___y_1596_; uint32_t v___y_1603_; uint8_t v___y_1604_; uint32_t v___y_1605_; uint32_t v___y_1606_; uint64_t v___y_1610_; uint32_t v___y_1611_; uint64_t v___y_1612_; uint8_t v___y_1613_; uint64_t v___y_1614_; uint64_t v___y_1624_; uint64_t v___y_1625_; uint32_t v___y_1626_; uint8_t v___y_1627_; uint8_t v___y_1628_; uint64_t v___y_1629_; uint64_t v___y_1636_; uint32_t v___y_1637_; uint64_t v___y_1638_; uint8_t v___y_1639_; uint64_t v___y_1640_; uint64_t v___y_1646_; uint64_t v___y_1647_; uint32_t v___y_1648_; uint8_t v___y_1649_; uint64_t v___y_1650_; uint64_t v___y_1651_; uint64_t v___y_1706_; uint64_t v___y_1707_; uint64_t v___y_1708_; uint32_t v___y_1709_; uint8_t v___y_1710_; uint64_t v___y_1711_; uint64_t v___y_1712_; uint64_t v___y_1718_; uint64_t v___y_1719_; uint64_t v___y_1720_; uint64_t v___y_1721_; uint32_t v___y_1722_; uint64_t v___y_1723_; uint8_t v___y_1724_; uint64_t v___y_1725_; uint64_t v___y_1726_; uint64_t v___y_1731_; uint64_t v___y_1732_; uint64_t v___y_1733_; uint32_t v___y_1734_; uint8_t v___y_1735_; uint64_t v___y_1736_; uint64_t v___y_1737_; uint64_t v___y_1742_; uint64_t v___y_1743_; uint64_t v___y_1744_; uint32_t v___y_1745_; uint64_t v___y_1746_; uint8_t v___y_1747_; uint64_t v___y_1748_; uint64_t v___y_1749_; uint64_t v___y_1750_; uint64_t v___y_1755_; uint64_t v___y_1756_; uint32_t v___y_1757_; uint8_t v___y_1758_; uint64_t v___y_1759_; uint64_t v___y_1760_; uint64_t v___y_1761_; uint64_t v___y_1766_; uint64_t v___y_1767_; uint64_t v___y_1768_; uint32_t v___y_1769_; uint64_t v___y_1770_; uint8_t v___y_1771_; uint64_t v___y_1772_; uint64_t v___y_1773_; uint64_t v___y_1774_; uint64_t v___y_1779_; uint64_t v___y_1780_; uint32_t v___y_1781_; uint64_t v___y_1782_; uint8_t v___y_1783_; uint64_t v___y_1784_; uint64_t v___y_1785_; uint64_t v___y_1790_; uint64_t v___y_1791_; uint64_t v___y_1792_; uint32_t v___y_1793_; uint8_t v___y_1794_; uint64_t v___y_1795_; uint64_t v___y_1796_; uint64_t v___y_1797_; uint64_t v___y_1798_; uint64_t v___y_1803_; uint64_t v___y_1804_; uint32_t v___y_1805_; uint8_t v___y_1806_; uint64_t v___y_1807_; uint64_t v___y_1808_; uint64_t v___y_1809_; uint64_t v___y_1814_; uint64_t v___y_1815_; uint64_t v___y_1816_; uint32_t v___y_1817_; uint8_t v___y_1818_; uint64_t v___y_1819_; uint64_t v___y_1820_; uint64_t v___y_1824_; uint32_t v___y_1825_; uint8_t v___y_1826_; uint64_t v___y_1827_; uint64_t v___y_1836_; uint32_t v___y_1837_; uint8_t v___y_1838_; uint64_t v___y_1839_; uint64_t v___y_1840_; uint64_t v___y_1841_; uint32_t v_ex_1874_; uint32_t v___x_1875_; uint32_t v_ey_1876_; uint64_t v___y_1878_; uint32_t v___y_1879_; uint8_t v___y_1880_; uint64_t v___y_1881_; uint64_t v___y_1882_; uint32_t v___y_1889_; uint8_t v___y_1890_; uint64_t v___y_1891_; uint64_t v___y_1892_; uint32_t v___y_1899_; uint8_t v___y_1900_; uint32_t v___y_1901_; uint64_t v___y_1902_; uint8_t v___y_1910_; uint32_t v___x_1920_; uint32_t v___x_1921_; uint8_t v___x_1922_; uint8_t v___y_1924_; uint8_t v___y_1925_; uint8_t v___y_1927_; uint8_t v___y_1928_; uint8_t v___y_1929_; uint8_t v___y_1931_; uint8_t v___y_1932_; uint8_t v___y_1938_; 
v___x_1576_ = 23;
v___x_1577_ = lean_uint32_shift_right(v___y_1429_, v___x_1576_);
v___x_1591_ = 255;
v_ex_1874_ = lean_uint32_land(v___x_1577_, v___x_1591_);
v___x_1875_ = lean_uint32_shift_right(v___y_1430_, v___x_1576_);
v_ey_1876_ = lean_uint32_land(v___x_1875_, v___x_1591_);
v___x_1920_ = lean_uint32_add(v_ex_1874_, v_ey_1876_);
v___x_1921_ = 128;
v___x_1922_ = lean_uint32_dec_lt(v___x_1920_, v___x_1921_);
if (v___x_1922_ == 0)
{
uint32_t v___x_1947_; uint32_t v_a_1948_; uint32_t v___x_1949_; uint32_t v___x_1950_; uint32_t v___x_1951_; uint8_t v___x_1952_; 
v___x_1947_ = 2147483647;
v_a_1948_ = lean_uint32_land(v___y_1429_, v___x_1947_);
v___x_1949_ = 201326591;
v___x_1950_ = 1;
v___x_1951_ = lean_uint32_sub(v_a_1948_, v___x_1950_);
v___x_1952_ = lean_uint32_dec_le(v___x_1949_, v___x_1951_);
if (v___x_1952_ == 0)
{
v___y_1579_ = v___x_1952_;
goto v___jp_1578_;
}
else
{
uint32_t v___x_1953_; uint8_t v___x_1954_; 
v___x_1953_ = 2139095040;
v___x_1954_ = lean_uint32_dec_lt(v_a_1948_, v___x_1953_);
v___y_1579_ = v___x_1954_;
goto v___jp_1578_;
}
}
else
{
uint32_t v___x_1955_; uint32_t v___x_1956_; uint32_t v___x_1957_; uint8_t v___x_1958_; 
v___x_1955_ = 4278190080;
v___x_1956_ = 1;
v___x_1957_ = lean_uint32_shift_left(v___y_1429_, v___x_1956_);
v___x_1958_ = lean_uint32_dec_le(v___x_1955_, v___x_1957_);
if (v___x_1958_ == 0)
{
uint32_t v___x_1959_; uint8_t v___x_1960_; 
v___x_1959_ = lean_uint32_shift_left(v___y_1430_, v___x_1956_);
v___x_1960_ = lean_uint32_dec_le(v___x_1955_, v___x_1959_);
v___y_1938_ = v___x_1960_;
goto v___jp_1937_;
}
else
{
v___y_1938_ = v___x_1958_;
goto v___jp_1937_;
}
}
v___jp_1431_:
{
uint32_t v___x_1433_; uint32_t v___x_1434_; 
v___x_1433_ = 8388608;
v___x_1434_ = lean_uint32_lor(v___y_1432_, v___x_1433_);
return v___x_1434_;
}
v___jp_1435_:
{
uint32_t v___x_1437_; uint32_t v___x_1438_; 
v___x_1437_ = 8388608;
v___x_1438_ = lean_uint32_lor(v___y_1436_, v___x_1437_);
return v___x_1438_;
}
v___jp_1439_:
{
uint32_t v___x_1443_; uint32_t v___x_1444_; 
v___x_1443_ = lean_uint32_land(v___y_1440_, v___y_1441_);
v___x_1444_ = lean_uint32_lor(v___y_1442_, v___x_1443_);
return v___x_1444_;
}
v___jp_1445_:
{
uint8_t v___x_1450_; 
v___x_1450_ = lean_uint64_dec_eq(v___y_1449_, v___y_1446_);
if (v___x_1450_ == 0)
{
uint64_t v___x_1451_; uint8_t v___x_1452_; 
v___x_1451_ = 8388608ULL;
v___x_1452_ = lean_uint64_dec_eq(v___y_1449_, v___x_1451_);
if (v___x_1452_ == 0)
{
uint32_t v___x_1453_; 
v___x_1453_ = lean_uint64_to_uint32(v___y_1449_);
if (v___y_1448_ == 0)
{
uint32_t v___x_1454_; 
v___x_1454_ = 0;
v___y_1440_ = v___x_1453_;
v___y_1441_ = v___y_1447_;
v___y_1442_ = v___x_1454_;
goto v___jp_1439_;
}
else
{
uint32_t v___x_1455_; 
v___x_1455_ = 2147483648;
v___y_1440_ = v___x_1453_;
v___y_1441_ = v___y_1447_;
v___y_1442_ = v___x_1455_;
goto v___jp_1439_;
}
}
else
{
if (v___y_1448_ == 0)
{
uint32_t v___x_1456_; 
v___x_1456_ = 0;
v___y_1436_ = v___x_1456_;
goto v___jp_1435_;
}
else
{
uint32_t v___x_1457_; 
v___x_1457_ = 2147483648;
v___y_1436_ = v___x_1457_;
goto v___jp_1435_;
}
}
}
else
{
if (v___y_1448_ == 0)
{
uint32_t v___x_1458_; 
v___x_1458_ = 0;
return v___x_1458_;
}
else
{
uint32_t v___x_1459_; 
v___x_1459_ = 2147483648;
return v___x_1459_;
}
}
}
v___jp_1460_:
{
uint32_t v___x_1464_; uint32_t v___x_1465_; 
v___x_1464_ = lean_uint32_land(v___y_1462_, v___y_1461_);
v___x_1465_ = lean_uint32_lor(v___y_1463_, v___x_1464_);
return v___x_1465_;
}
v___jp_1466_:
{
uint8_t v___x_1471_; 
v___x_1471_ = lean_uint64_dec_eq(v___y_1470_, v___y_1467_);
if (v___x_1471_ == 0)
{
uint64_t v___x_1472_; uint8_t v___x_1473_; 
v___x_1472_ = 8388608ULL;
v___x_1473_ = lean_uint64_dec_eq(v___y_1470_, v___x_1472_);
if (v___x_1473_ == 0)
{
uint32_t v___x_1474_; 
v___x_1474_ = lean_uint64_to_uint32(v___y_1470_);
if (v___y_1469_ == 0)
{
uint32_t v___x_1475_; 
v___x_1475_ = 0;
v___y_1461_ = v___y_1468_;
v___y_1462_ = v___x_1474_;
v___y_1463_ = v___x_1475_;
goto v___jp_1460_;
}
else
{
uint32_t v___x_1476_; 
v___x_1476_ = 2147483648;
v___y_1461_ = v___y_1468_;
v___y_1462_ = v___x_1474_;
v___y_1463_ = v___x_1476_;
goto v___jp_1460_;
}
}
else
{
if (v___y_1469_ == 0)
{
uint32_t v___x_1477_; 
v___x_1477_ = 0;
v___y_1432_ = v___x_1477_;
goto v___jp_1431_;
}
else
{
uint32_t v___x_1478_; 
v___x_1478_ = 2147483648;
v___y_1432_ = v___x_1478_;
goto v___jp_1431_;
}
}
}
else
{
if (v___y_1469_ == 0)
{
uint32_t v___x_1479_; 
v___x_1479_ = 0;
return v___x_1479_;
}
else
{
uint32_t v___x_1480_; 
v___x_1480_ = 2147483648;
return v___x_1480_;
}
}
}
v___jp_1481_:
{
if (v___y_1482_ == 0)
{
uint32_t v___x_1483_; 
v___x_1483_ = lp_competition_Submission_FastMul_mul(v___y_1429_, v___y_1430_);
return v___x_1483_;
}
else
{
uint32_t v___x_1484_; uint32_t v___x_1485_; 
v___x_1484_ = 4194304;
v___x_1485_ = lean_uint32_lor(v___y_1430_, v___x_1484_);
return v___x_1485_;
}
}
v___jp_1486_:
{
uint32_t v___x_1487_; uint32_t v___x_1488_; uint32_t v___x_1489_; uint32_t v___x_1490_; uint8_t v___x_1491_; 
v___x_1487_ = 23;
v___x_1488_ = lean_uint32_shift_right(v___y_1430_, v___x_1487_);
v___x_1489_ = 255;
v___x_1490_ = lean_uint32_land(v___x_1488_, v___x_1489_);
v___x_1491_ = lean_uint32_dec_eq(v___x_1490_, v___x_1489_);
if (v___x_1491_ == 0)
{
v___y_1482_ = v___x_1491_;
goto v___jp_1481_;
}
else
{
uint32_t v___x_1492_; uint32_t v___x_1493_; uint32_t v___x_1494_; uint8_t v___x_1495_; 
v___x_1492_ = 8388607;
v___x_1493_ = lean_uint32_land(v___y_1430_, v___x_1492_);
v___x_1494_ = 0;
v___x_1495_ = lean_uint32_dec_eq(v___x_1493_, v___x_1494_);
if (v___x_1495_ == 0)
{
v___y_1482_ = v___x_1491_;
goto v___jp_1481_;
}
else
{
uint32_t v___x_1496_; 
v___x_1496_ = lp_competition_Submission_FastMul_mul(v___y_1429_, v___y_1430_);
return v___x_1496_;
}
}
}
v___jp_1497_:
{
if (v___y_1498_ == 0)
{
goto v___jp_1486_;
}
else
{
uint32_t v___x_1499_; uint32_t v___x_1500_; 
v___x_1499_ = 4194304;
v___x_1500_ = lean_uint32_lor(v___y_1429_, v___x_1499_);
return v___x_1500_;
}
}
v___jp_1501_:
{
uint32_t v___x_1502_; uint32_t v___x_1503_; uint32_t v___x_1504_; uint32_t v___x_1505_; uint8_t v___x_1506_; 
v___x_1502_ = 23;
v___x_1503_ = lean_uint32_shift_right(v___y_1429_, v___x_1502_);
v___x_1504_ = 255;
v___x_1505_ = lean_uint32_land(v___x_1503_, v___x_1504_);
v___x_1506_ = lean_uint32_dec_eq(v___x_1505_, v___x_1504_);
if (v___x_1506_ == 0)
{
v___y_1498_ = v___x_1506_;
goto v___jp_1497_;
}
else
{
uint32_t v___x_1507_; uint32_t v___x_1508_; uint32_t v___x_1509_; uint8_t v___x_1510_; 
v___x_1507_ = 8388607;
v___x_1508_ = lean_uint32_land(v___y_1429_, v___x_1507_);
v___x_1509_ = 0;
v___x_1510_ = lean_uint32_dec_eq(v___x_1508_, v___x_1509_);
if (v___x_1510_ == 0)
{
v___y_1498_ = v___x_1506_;
goto v___jp_1497_;
}
else
{
goto v___jp_1486_;
}
}
}
v___jp_1511_:
{
if (v___y_1512_ == 0)
{
goto v___jp_1501_;
}
else
{
uint32_t v___x_1513_; uint32_t v___x_1514_; uint32_t v___x_1515_; uint8_t v___x_1516_; 
v___x_1513_ = 4194304;
v___x_1514_ = lean_uint32_land(v___y_1430_, v___x_1513_);
v___x_1515_ = 0;
v___x_1516_ = lean_uint32_dec_eq(v___x_1514_, v___x_1515_);
if (v___x_1516_ == 0)
{
goto v___jp_1501_;
}
else
{
uint32_t v___x_1517_; 
v___x_1517_ = lean_uint32_lor(v___y_1430_, v___x_1513_);
return v___x_1517_;
}
}
}
v___jp_1518_:
{
uint32_t v___x_1519_; uint32_t v___x_1520_; uint32_t v___x_1521_; uint32_t v___x_1522_; uint8_t v___x_1523_; 
v___x_1519_ = 23;
v___x_1520_ = lean_uint32_shift_right(v___y_1430_, v___x_1519_);
v___x_1521_ = 255;
v___x_1522_ = lean_uint32_land(v___x_1520_, v___x_1521_);
v___x_1523_ = lean_uint32_dec_eq(v___x_1522_, v___x_1521_);
if (v___x_1523_ == 0)
{
v___y_1512_ = v___x_1523_;
goto v___jp_1511_;
}
else
{
uint32_t v___x_1524_; uint32_t v___x_1525_; uint32_t v___x_1526_; uint8_t v___x_1527_; 
v___x_1524_ = 8388607;
v___x_1525_ = lean_uint32_land(v___y_1430_, v___x_1524_);
v___x_1526_ = 0;
v___x_1527_ = lean_uint32_dec_eq(v___x_1525_, v___x_1526_);
if (v___x_1527_ == 0)
{
v___y_1512_ = v___x_1523_;
goto v___jp_1511_;
}
else
{
goto v___jp_1501_;
}
}
}
v___jp_1528_:
{
if (v___y_1529_ == 0)
{
goto v___jp_1518_;
}
else
{
uint32_t v___x_1530_; uint32_t v___x_1531_; uint32_t v___x_1532_; uint8_t v___x_1533_; 
v___x_1530_ = 4194304;
v___x_1531_ = lean_uint32_land(v___y_1429_, v___x_1530_);
v___x_1532_ = 0;
v___x_1533_ = lean_uint32_dec_eq(v___x_1531_, v___x_1532_);
if (v___x_1533_ == 0)
{
goto v___jp_1518_;
}
else
{
uint32_t v___x_1534_; 
v___x_1534_ = lean_uint32_lor(v___y_1429_, v___x_1530_);
return v___x_1534_;
}
}
}
v___jp_1535_:
{
float v_result_1538_; uint8_t v___x_1539_; 
v_result_1538_ = lean_float32_mul(v___y_1536_, v___y_1537_);
v___x_1539_ = lean_float32_beq(v_result_1538_, v_result_1538_);
if (v___x_1539_ == 0)
{
uint32_t v___x_1540_; uint32_t v___x_1541_; uint32_t v___x_1542_; uint32_t v___x_1543_; uint8_t v___x_1544_; 
v___x_1540_ = 23;
v___x_1541_ = lean_uint32_shift_right(v___y_1429_, v___x_1540_);
v___x_1542_ = 255;
v___x_1543_ = lean_uint32_land(v___x_1541_, v___x_1542_);
v___x_1544_ = lean_uint32_dec_eq(v___x_1543_, v___x_1542_);
if (v___x_1544_ == 0)
{
v___y_1529_ = v___x_1544_;
goto v___jp_1528_;
}
else
{
uint32_t v___x_1545_; uint32_t v___x_1546_; uint32_t v___x_1547_; uint8_t v___x_1548_; 
v___x_1545_ = 8388607;
v___x_1546_ = lean_uint32_land(v___y_1429_, v___x_1545_);
v___x_1547_ = 0;
v___x_1548_ = lean_uint32_dec_eq(v___x_1546_, v___x_1547_);
if (v___x_1548_ == 0)
{
v___y_1529_ = v___x_1544_;
goto v___jp_1528_;
}
else
{
goto v___jp_1518_;
}
}
}
else
{
uint32_t v___x_1549_; 
v___x_1549_ = lean_float32_to_bits(v_result_1538_);
return v___x_1549_;
}
}
v___jp_1550_:
{
if (v___y_1552_ == 0)
{
float v___x_1553_; 
v___x_1553_ = lean_float32_of_bits(v___y_1430_);
v___y_1536_ = v___y_1551_;
v___y_1537_ = v___x_1553_;
goto v___jp_1535_;
}
else
{
uint32_t v___x_1554_; uint32_t v___x_1555_; uint32_t v___x_1556_; uint32_t v___x_1557_; float v___x_1558_; lean_object* v___x_1559_; uint32_t v___x_1560_; uint32_t v___x_1561_; lean_object* v___x_1562_; lean_object* v___x_1563_; float v___x_1564_; float v___x_1565_; 
v___x_1554_ = 8388607;
v___x_1555_ = lean_uint32_land(v___y_1430_, v___x_1554_);
v___x_1556_ = 8388608;
v___x_1557_ = lean_uint32_lor(v___x_1555_, v___x_1556_);
v___x_1558_ = lean_uint32_to_float32(v___x_1557_);
v___x_1559_ = lp_competition_R2W01b_scaleTable;
v___x_1560_ = 23;
v___x_1561_ = lean_uint32_shift_right(v___y_1430_, v___x_1560_);
v___x_1562_ = lean_uint32_to_nat(v___x_1561_);
v___x_1563_ = lean_array_fget_borrowed(v___x_1559_, v___x_1562_);
lean_dec(v___x_1562_);
v___x_1564_ = lean_unbox_float32(v___x_1563_);
v___x_1565_ = lean_float32_mul(v___x_1558_, v___x_1564_);
v___y_1536_ = v___y_1551_;
v___y_1537_ = v___x_1565_;
goto v___jp_1535_;
}
}
v___jp_1566_:
{
uint32_t v___x_1568_; uint32_t v_a_1569_; uint32_t v___x_1570_; uint32_t v___x_1571_; uint32_t v___x_1572_; uint8_t v___x_1573_; 
v___x_1568_ = 2147483647;
v_a_1569_ = lean_uint32_land(v___y_1430_, v___x_1568_);
v___x_1570_ = 201326591;
v___x_1571_ = 1;
v___x_1572_ = lean_uint32_sub(v_a_1569_, v___x_1571_);
v___x_1573_ = lean_uint32_dec_le(v___x_1570_, v___x_1572_);
if (v___x_1573_ == 0)
{
v___y_1551_ = v___y_1567_;
v___y_1552_ = v___x_1573_;
goto v___jp_1550_;
}
else
{
uint32_t v___x_1574_; uint8_t v___x_1575_; 
v___x_1574_ = 2139095040;
v___x_1575_ = lean_uint32_dec_lt(v_a_1569_, v___x_1574_);
v___y_1551_ = v___y_1567_;
v___y_1552_ = v___x_1575_;
goto v___jp_1550_;
}
}
v___jp_1578_:
{
if (v___y_1579_ == 0)
{
float v___x_1580_; 
v___x_1580_ = lean_float32_of_bits(v___y_1429_);
v___y_1567_ = v___x_1580_;
goto v___jp_1566_;
}
else
{
uint32_t v___x_1581_; uint32_t v___x_1582_; uint32_t v___x_1583_; uint32_t v___x_1584_; float v___x_1585_; lean_object* v___x_1586_; lean_object* v___x_1587_; lean_object* v___x_1588_; float v___x_1589_; float v___x_1590_; 
v___x_1581_ = 8388607;
v___x_1582_ = lean_uint32_land(v___y_1429_, v___x_1581_);
v___x_1583_ = 8388608;
v___x_1584_ = lean_uint32_lor(v___x_1582_, v___x_1583_);
v___x_1585_ = lean_uint32_to_float32(v___x_1584_);
v___x_1586_ = lp_competition_R2W01b_scaleTable;
v___x_1587_ = lean_uint32_to_nat(v___x_1577_);
v___x_1588_ = lean_array_fget_borrowed(v___x_1586_, v___x_1587_);
lean_dec(v___x_1587_);
v___x_1589_ = lean_unbox_float32(v___x_1588_);
v___x_1590_ = lean_float32_mul(v___x_1585_, v___x_1589_);
v___y_1567_ = v___x_1590_;
goto v___jp_1566_;
}
}
v___jp_1592_:
{
uint32_t v___x_1597_; uint32_t v___x_1598_; uint32_t v___x_1599_; uint32_t v___x_1600_; uint32_t v___x_1601_; 
v___x_1597_ = lean_uint32_land(v___y_1595_, v___x_1591_);
v___x_1598_ = lean_uint32_shift_left(v___x_1597_, v___x_1576_);
v___x_1599_ = lean_uint32_lor(v___y_1596_, v___x_1598_);
v___x_1600_ = lean_uint32_land(v___y_1594_, v___y_1593_);
v___x_1601_ = lean_uint32_lor(v___x_1599_, v___x_1600_);
return v___x_1601_;
}
v___jp_1602_:
{
if (v___y_1604_ == 0)
{
uint32_t v___x_1607_; 
v___x_1607_ = 0;
v___y_1593_ = v___y_1603_;
v___y_1594_ = v___y_1606_;
v___y_1595_ = v___y_1605_;
v___y_1596_ = v___x_1607_;
goto v___jp_1592_;
}
else
{
uint32_t v___x_1608_; 
v___x_1608_ = 2147483648;
v___y_1593_ = v___y_1603_;
v___y_1594_ = v___y_1606_;
v___y_1595_ = v___y_1605_;
v___y_1596_ = v___x_1608_;
goto v___jp_1592_;
}
}
v___jp_1609_:
{
uint64_t v___x_1615_; uint64_t v_encodedExponent_1616_; uint32_t v___x_1617_; uint64_t v___x_1618_; uint8_t v___x_1619_; 
v___x_1615_ = 171ULL;
v_encodedExponent_1616_ = lean_uint64_sub(v___y_1612_, v___x_1615_);
v___x_1617_ = lean_uint64_to_uint32(v_encodedExponent_1616_);
v___x_1618_ = 8388608ULL;
v___x_1619_ = lean_uint64_dec_lt(v___y_1614_, v___x_1618_);
if (v___x_1619_ == 0)
{
uint64_t v___x_1620_; uint32_t v___x_1621_; 
v___x_1620_ = lean_uint64_sub(v___y_1614_, v___x_1618_);
v___x_1621_ = lean_uint64_to_uint32(v___x_1620_);
v___y_1603_ = v___y_1611_;
v___y_1604_ = v___y_1613_;
v___y_1605_ = v___x_1617_;
v___y_1606_ = v___x_1621_;
goto v___jp_1602_;
}
else
{
uint32_t v___x_1622_; 
v___x_1622_ = lean_uint64_to_uint32(v___y_1610_);
v___y_1603_ = v___y_1611_;
v___y_1604_ = v___y_1613_;
v___y_1605_ = v___x_1617_;
v___y_1606_ = v___x_1622_;
goto v___jp_1602_;
}
}
v___jp_1623_:
{
uint64_t v___x_1630_; uint8_t v___x_1631_; 
v___x_1630_ = 425ULL;
v___x_1631_ = lean_uint64_dec_lt(v___x_1630_, v___y_1629_);
if (v___x_1631_ == 0)
{
if (v___y_1627_ == 0)
{
v___y_1610_ = v___y_1625_;
v___y_1611_ = v___y_1626_;
v___y_1612_ = v___y_1629_;
v___y_1613_ = v___y_1628_;
v___y_1614_ = v___y_1624_;
goto v___jp_1609_;
}
else
{
uint64_t v___x_1632_; 
v___x_1632_ = 8388608ULL;
v___y_1610_ = v___y_1625_;
v___y_1611_ = v___y_1626_;
v___y_1612_ = v___y_1629_;
v___y_1613_ = v___y_1628_;
v___y_1614_ = v___x_1632_;
goto v___jp_1609_;
}
}
else
{
if (v___y_1628_ == 0)
{
uint32_t v___x_1633_; 
v___x_1633_ = 2139095040;
return v___x_1633_;
}
else
{
uint32_t v___x_1634_; 
v___x_1634_ = 4286578688;
return v___x_1634_;
}
}
}
v___jp_1635_:
{
uint64_t v___x_1641_; uint8_t v_carry_1642_; 
v___x_1641_ = 16777216ULL;
v_carry_1642_ = lean_uint64_dec_eq(v___y_1640_, v___x_1641_);
if (v_carry_1642_ == 0)
{
v___y_1624_ = v___y_1640_;
v___y_1625_ = v___y_1636_;
v___y_1626_ = v___y_1637_;
v___y_1627_ = v_carry_1642_;
v___y_1628_ = v___y_1639_;
v___y_1629_ = v___y_1638_;
goto v___jp_1623_;
}
else
{
uint64_t v___x_1643_; uint64_t v___x_1644_; 
v___x_1643_ = 1ULL;
v___x_1644_ = lean_uint64_add(v___y_1638_, v___x_1643_);
v___y_1624_ = v___y_1640_;
v___y_1625_ = v___y_1636_;
v___y_1626_ = v___y_1637_;
v___y_1627_ = v_carry_1642_;
v___y_1628_ = v___y_1639_;
v___y_1629_ = v___x_1644_;
goto v___jp_1623_;
}
}
v___jp_1645_:
{
uint64_t v_position_1652_; uint64_t v___x_1653_; uint8_t v___x_1654_; 
v_position_1652_ = lean_uint64_add(v___y_1651_, v___y_1646_);
v___x_1653_ = 172ULL;
v___x_1654_ = lean_uint64_dec_lt(v_position_1652_, v___x_1653_);
if (v___x_1654_ == 0)
{
uint64_t v___x_1655_; uint8_t v___x_1656_; 
v___x_1655_ = 23ULL;
v___x_1656_ = lean_uint64_dec_lt(v___y_1651_, v___x_1655_);
if (v___x_1656_ == 0)
{
uint64_t v___x_1657_; uint8_t v___x_1658_; 
v___x_1657_ = lean_uint64_sub(v___y_1651_, v___x_1655_);
v___x_1658_ = lean_uint64_dec_eq(v___x_1657_, v___y_1647_);
if (v___x_1658_ == 0)
{
uint64_t v___x_1659_; uint8_t v___x_1660_; 
v___x_1659_ = 64ULL;
v___x_1660_ = lean_uint64_dec_lt(v___x_1657_, v___x_1659_);
if (v___x_1660_ == 0)
{
uint8_t v___x_1661_; 
v___x_1661_ = lean_uint64_dec_eq(v___x_1657_, v___x_1659_);
if (v___x_1661_ == 0)
{
v___y_1636_ = v___y_1647_;
v___y_1637_ = v___y_1648_;
v___y_1638_ = v_position_1652_;
v___y_1639_ = v___y_1649_;
v___y_1640_ = v___y_1647_;
goto v___jp_1635_;
}
else
{
uint64_t v___x_1662_; uint8_t v___x_1663_; 
v___x_1662_ = 9223372036854775808ULL;
v___x_1663_ = lean_uint64_dec_lt(v___x_1662_, v___y_1650_);
if (v___x_1663_ == 0)
{
v___y_1636_ = v___y_1647_;
v___y_1637_ = v___y_1648_;
v___y_1638_ = v_position_1652_;
v___y_1639_ = v___y_1649_;
v___y_1640_ = v___y_1647_;
goto v___jp_1635_;
}
else
{
uint64_t v___x_1664_; 
v___x_1664_ = 1ULL;
v___y_1636_ = v___y_1647_;
v___y_1637_ = v___y_1648_;
v___y_1638_ = v_position_1652_;
v___y_1639_ = v___y_1649_;
v___y_1640_ = v___x_1664_;
goto v___jp_1635_;
}
}
}
else
{
uint64_t v_quotient_1665_; uint64_t v___x_1666_; uint64_t v___x_1667_; uint64_t v___x_1668_; uint64_t v_remainder_1669_; uint64_t v___x_1670_; uint64_t v_half_1671_; uint8_t v___x_1672_; 
v_quotient_1665_ = lean_uint64_shift_right(v___y_1650_, v___x_1657_);
v___x_1666_ = 1ULL;
v___x_1667_ = lean_uint64_shift_left(v___x_1666_, v___x_1657_);
v___x_1668_ = lean_uint64_sub(v___x_1667_, v___x_1666_);
v_remainder_1669_ = lean_uint64_land(v___y_1650_, v___x_1668_);
v___x_1670_ = lean_uint64_sub(v___x_1657_, v___x_1666_);
v_half_1671_ = lean_uint64_shift_left(v___x_1666_, v___x_1670_);
v___x_1672_ = lean_uint64_dec_lt(v_remainder_1669_, v_half_1671_);
if (v___x_1672_ == 0)
{
uint8_t v___x_1673_; 
v___x_1673_ = lean_uint64_dec_lt(v_half_1671_, v_remainder_1669_);
if (v___x_1673_ == 0)
{
uint64_t v___x_1674_; uint8_t v___x_1675_; 
v___x_1674_ = lean_uint64_land(v_quotient_1665_, v___x_1666_);
v___x_1675_ = lean_uint64_dec_eq(v___x_1674_, v___y_1647_);
if (v___x_1675_ == 0)
{
uint64_t v___x_1676_; 
v___x_1676_ = lean_uint64_add(v_quotient_1665_, v___x_1666_);
v___y_1636_ = v___y_1647_;
v___y_1637_ = v___y_1648_;
v___y_1638_ = v_position_1652_;
v___y_1639_ = v___y_1649_;
v___y_1640_ = v___x_1676_;
goto v___jp_1635_;
}
else
{
v___y_1636_ = v___y_1647_;
v___y_1637_ = v___y_1648_;
v___y_1638_ = v_position_1652_;
v___y_1639_ = v___y_1649_;
v___y_1640_ = v_quotient_1665_;
goto v___jp_1635_;
}
}
else
{
uint64_t v___x_1677_; 
v___x_1677_ = lean_uint64_add(v_quotient_1665_, v___x_1666_);
v___y_1636_ = v___y_1647_;
v___y_1637_ = v___y_1648_;
v___y_1638_ = v_position_1652_;
v___y_1639_ = v___y_1649_;
v___y_1640_ = v___x_1677_;
goto v___jp_1635_;
}
}
else
{
v___y_1636_ = v___y_1647_;
v___y_1637_ = v___y_1648_;
v___y_1638_ = v_position_1652_;
v___y_1639_ = v___y_1649_;
v___y_1640_ = v_quotient_1665_;
goto v___jp_1635_;
}
}
}
else
{
v___y_1636_ = v___y_1647_;
v___y_1637_ = v___y_1648_;
v___y_1638_ = v_position_1652_;
v___y_1639_ = v___y_1649_;
v___y_1640_ = v___y_1650_;
goto v___jp_1635_;
}
}
else
{
uint64_t v___x_1678_; uint64_t v___x_1679_; 
v___x_1678_ = lean_uint64_sub(v___x_1655_, v___y_1651_);
v___x_1679_ = lean_uint64_shift_left(v___y_1650_, v___x_1678_);
v___y_1636_ = v___y_1647_;
v___y_1637_ = v___y_1648_;
v___y_1638_ = v_position_1652_;
v___y_1639_ = v___y_1649_;
v___y_1640_ = v___x_1679_;
goto v___jp_1635_;
}
}
else
{
uint64_t v___x_1680_; uint8_t v___x_1681_; 
v___x_1680_ = 149ULL;
v___x_1681_ = lean_uint64_dec_lt(v___y_1646_, v___x_1680_);
if (v___x_1681_ == 0)
{
uint64_t v___x_1682_; uint64_t v___x_1683_; 
v___x_1682_ = lean_uint64_sub(v___y_1646_, v___x_1680_);
v___x_1683_ = lean_uint64_shift_left(v___y_1650_, v___x_1682_);
v___y_1446_ = v___y_1647_;
v___y_1447_ = v___y_1648_;
v___y_1448_ = v___y_1649_;
v___y_1449_ = v___x_1683_;
goto v___jp_1445_;
}
else
{
uint64_t v___x_1684_; uint8_t v___x_1685_; 
v___x_1684_ = lean_uint64_sub(v___x_1680_, v___y_1646_);
v___x_1685_ = lean_uint64_dec_eq(v___x_1684_, v___y_1647_);
if (v___x_1685_ == 0)
{
uint64_t v___x_1686_; uint8_t v___x_1687_; 
v___x_1686_ = 64ULL;
v___x_1687_ = lean_uint64_dec_lt(v___x_1684_, v___x_1686_);
if (v___x_1687_ == 0)
{
uint8_t v___x_1688_; 
v___x_1688_ = lean_uint64_dec_eq(v___x_1684_, v___x_1686_);
if (v___x_1688_ == 0)
{
v___y_1446_ = v___y_1647_;
v___y_1447_ = v___y_1648_;
v___y_1448_ = v___y_1649_;
v___y_1449_ = v___y_1647_;
goto v___jp_1445_;
}
else
{
uint64_t v___x_1689_; uint8_t v___x_1690_; 
v___x_1689_ = 9223372036854775808ULL;
v___x_1690_ = lean_uint64_dec_lt(v___x_1689_, v___y_1650_);
if (v___x_1690_ == 0)
{
v___y_1446_ = v___y_1647_;
v___y_1447_ = v___y_1648_;
v___y_1448_ = v___y_1649_;
v___y_1449_ = v___y_1647_;
goto v___jp_1445_;
}
else
{
uint64_t v___x_1691_; 
v___x_1691_ = 1ULL;
v___y_1446_ = v___y_1647_;
v___y_1447_ = v___y_1648_;
v___y_1448_ = v___y_1649_;
v___y_1449_ = v___x_1691_;
goto v___jp_1445_;
}
}
}
else
{
uint64_t v_quotient_1692_; uint64_t v___x_1693_; uint64_t v___x_1694_; uint64_t v___x_1695_; uint64_t v_remainder_1696_; uint64_t v___x_1697_; uint64_t v_half_1698_; uint8_t v___x_1699_; 
v_quotient_1692_ = lean_uint64_shift_right(v___y_1650_, v___x_1684_);
v___x_1693_ = 1ULL;
v___x_1694_ = lean_uint64_shift_left(v___x_1693_, v___x_1684_);
v___x_1695_ = lean_uint64_sub(v___x_1694_, v___x_1693_);
v_remainder_1696_ = lean_uint64_land(v___y_1650_, v___x_1695_);
v___x_1697_ = lean_uint64_sub(v___x_1684_, v___x_1693_);
v_half_1698_ = lean_uint64_shift_left(v___x_1693_, v___x_1697_);
v___x_1699_ = lean_uint64_dec_lt(v_remainder_1696_, v_half_1698_);
if (v___x_1699_ == 0)
{
uint8_t v___x_1700_; 
v___x_1700_ = lean_uint64_dec_lt(v_half_1698_, v_remainder_1696_);
if (v___x_1700_ == 0)
{
uint64_t v___x_1701_; uint8_t v___x_1702_; 
v___x_1701_ = lean_uint64_land(v_quotient_1692_, v___x_1693_);
v___x_1702_ = lean_uint64_dec_eq(v___x_1701_, v___y_1647_);
if (v___x_1702_ == 0)
{
uint64_t v___x_1703_; 
v___x_1703_ = lean_uint64_add(v_quotient_1692_, v___x_1693_);
v___y_1446_ = v___y_1647_;
v___y_1447_ = v___y_1648_;
v___y_1448_ = v___y_1649_;
v___y_1449_ = v___x_1703_;
goto v___jp_1445_;
}
else
{
v___y_1446_ = v___y_1647_;
v___y_1447_ = v___y_1648_;
v___y_1448_ = v___y_1649_;
v___y_1449_ = v_quotient_1692_;
goto v___jp_1445_;
}
}
else
{
uint64_t v___x_1704_; 
v___x_1704_ = lean_uint64_add(v_quotient_1692_, v___x_1693_);
v___y_1446_ = v___y_1647_;
v___y_1447_ = v___y_1648_;
v___y_1448_ = v___y_1649_;
v___y_1449_ = v___x_1704_;
goto v___jp_1445_;
}
}
else
{
v___y_1446_ = v___y_1647_;
v___y_1447_ = v___y_1648_;
v___y_1448_ = v___y_1649_;
v___y_1449_ = v_quotient_1692_;
goto v___jp_1445_;
}
}
}
else
{
v___y_1446_ = v___y_1647_;
v___y_1447_ = v___y_1648_;
v___y_1448_ = v___y_1649_;
v___y_1449_ = v___y_1650_;
goto v___jp_1445_;
}
}
}
}
v___jp_1705_:
{
uint64_t v___x_1713_; uint64_t v___x_1714_; uint8_t v___x_1715_; 
v___x_1713_ = 1ULL;
v___x_1714_ = lean_uint64_shift_right(v___y_1707_, v___x_1713_);
v___x_1715_ = lean_uint64_dec_eq(v___x_1714_, v___y_1708_);
if (v___x_1715_ == 0)
{
uint64_t v___x_1716_; 
v___x_1716_ = lean_uint64_add(v___y_1712_, v___x_1713_);
v___y_1646_ = v___y_1706_;
v___y_1647_ = v___y_1708_;
v___y_1648_ = v___y_1709_;
v___y_1649_ = v___y_1710_;
v___y_1650_ = v___y_1711_;
v___y_1651_ = v___x_1716_;
goto v___jp_1645_;
}
else
{
v___y_1646_ = v___y_1706_;
v___y_1647_ = v___y_1708_;
v___y_1648_ = v___y_1709_;
v___y_1649_ = v___y_1710_;
v___y_1650_ = v___y_1711_;
v___y_1651_ = v___y_1712_;
goto v___jp_1645_;
}
}
v___jp_1717_:
{
uint64_t v___x_1727_; uint8_t v___x_1728_; 
v___x_1727_ = lean_uint64_shift_right(v___y_1719_, v___y_1721_);
v___x_1728_ = lean_uint64_dec_eq(v___x_1727_, v___y_1720_);
if (v___x_1728_ == 0)
{
uint64_t v___x_1729_; 
v___x_1729_ = lean_uint64_add(v___y_1723_, v___y_1721_);
v___y_1706_ = v___y_1718_;
v___y_1707_ = v___y_1726_;
v___y_1708_ = v___y_1720_;
v___y_1709_ = v___y_1722_;
v___y_1710_ = v___y_1724_;
v___y_1711_ = v___y_1725_;
v___y_1712_ = v___x_1729_;
goto v___jp_1705_;
}
else
{
v___y_1706_ = v___y_1718_;
v___y_1707_ = v___y_1726_;
v___y_1708_ = v___y_1720_;
v___y_1709_ = v___y_1722_;
v___y_1710_ = v___y_1724_;
v___y_1711_ = v___y_1725_;
v___y_1712_ = v___y_1723_;
goto v___jp_1705_;
}
}
v___jp_1730_:
{
uint64_t v___x_1738_; uint64_t v___x_1739_; uint8_t v___x_1740_; 
v___x_1738_ = 2ULL;
v___x_1739_ = lean_uint64_shift_right(v___y_1732_, v___x_1738_);
v___x_1740_ = lean_uint64_dec_eq(v___x_1739_, v___y_1733_);
if (v___x_1740_ == 0)
{
v___y_1718_ = v___y_1731_;
v___y_1719_ = v___y_1732_;
v___y_1720_ = v___y_1733_;
v___y_1721_ = v___x_1738_;
v___y_1722_ = v___y_1734_;
v___y_1723_ = v___y_1737_;
v___y_1724_ = v___y_1735_;
v___y_1725_ = v___y_1736_;
v___y_1726_ = v___x_1739_;
goto v___jp_1717_;
}
else
{
v___y_1718_ = v___y_1731_;
v___y_1719_ = v___y_1732_;
v___y_1720_ = v___y_1733_;
v___y_1721_ = v___x_1738_;
v___y_1722_ = v___y_1734_;
v___y_1723_ = v___y_1737_;
v___y_1724_ = v___y_1735_;
v___y_1725_ = v___y_1736_;
v___y_1726_ = v___y_1732_;
goto v___jp_1717_;
}
}
v___jp_1741_:
{
uint64_t v___x_1751_; uint8_t v___x_1752_; 
v___x_1751_ = lean_uint64_shift_right(v___y_1749_, v___y_1746_);
v___x_1752_ = lean_uint64_dec_eq(v___x_1751_, v___y_1743_);
if (v___x_1752_ == 0)
{
uint64_t v___x_1753_; 
v___x_1753_ = lean_uint64_add(v___y_1744_, v___y_1746_);
v___y_1731_ = v___y_1742_;
v___y_1732_ = v___y_1750_;
v___y_1733_ = v___y_1743_;
v___y_1734_ = v___y_1745_;
v___y_1735_ = v___y_1747_;
v___y_1736_ = v___y_1748_;
v___y_1737_ = v___x_1753_;
goto v___jp_1730_;
}
else
{
v___y_1731_ = v___y_1742_;
v___y_1732_ = v___y_1750_;
v___y_1733_ = v___y_1743_;
v___y_1734_ = v___y_1745_;
v___y_1735_ = v___y_1747_;
v___y_1736_ = v___y_1748_;
v___y_1737_ = v___y_1744_;
goto v___jp_1730_;
}
}
v___jp_1754_:
{
uint64_t v___x_1762_; uint64_t v___x_1763_; uint8_t v___x_1764_; 
v___x_1762_ = 4ULL;
v___x_1763_ = lean_uint64_shift_right(v___y_1760_, v___x_1762_);
v___x_1764_ = lean_uint64_dec_eq(v___x_1763_, v___y_1756_);
if (v___x_1764_ == 0)
{
v___y_1742_ = v___y_1755_;
v___y_1743_ = v___y_1756_;
v___y_1744_ = v___y_1761_;
v___y_1745_ = v___y_1757_;
v___y_1746_ = v___x_1762_;
v___y_1747_ = v___y_1758_;
v___y_1748_ = v___y_1759_;
v___y_1749_ = v___y_1760_;
v___y_1750_ = v___x_1763_;
goto v___jp_1741_;
}
else
{
v___y_1742_ = v___y_1755_;
v___y_1743_ = v___y_1756_;
v___y_1744_ = v___y_1761_;
v___y_1745_ = v___y_1757_;
v___y_1746_ = v___x_1762_;
v___y_1747_ = v___y_1758_;
v___y_1748_ = v___y_1759_;
v___y_1749_ = v___y_1760_;
v___y_1750_ = v___y_1760_;
goto v___jp_1741_;
}
}
v___jp_1765_:
{
uint64_t v___x_1775_; uint8_t v___x_1776_; 
v___x_1775_ = lean_uint64_shift_right(v___y_1770_, v___y_1766_);
v___x_1776_ = lean_uint64_dec_eq(v___x_1775_, v___y_1768_);
if (v___x_1776_ == 0)
{
uint64_t v___x_1777_; 
v___x_1777_ = lean_uint64_add(v___y_1773_, v___y_1766_);
v___y_1755_ = v___y_1767_;
v___y_1756_ = v___y_1768_;
v___y_1757_ = v___y_1769_;
v___y_1758_ = v___y_1771_;
v___y_1759_ = v___y_1772_;
v___y_1760_ = v___y_1774_;
v___y_1761_ = v___x_1777_;
goto v___jp_1754_;
}
else
{
v___y_1755_ = v___y_1767_;
v___y_1756_ = v___y_1768_;
v___y_1757_ = v___y_1769_;
v___y_1758_ = v___y_1771_;
v___y_1759_ = v___y_1772_;
v___y_1760_ = v___y_1774_;
v___y_1761_ = v___y_1773_;
goto v___jp_1754_;
}
}
v___jp_1778_:
{
uint64_t v___x_1786_; uint64_t v___x_1787_; uint8_t v___x_1788_; 
v___x_1786_ = 8ULL;
v___x_1787_ = lean_uint64_shift_right(v___y_1782_, v___x_1786_);
v___x_1788_ = lean_uint64_dec_eq(v___x_1787_, v___y_1780_);
if (v___x_1788_ == 0)
{
v___y_1766_ = v___x_1786_;
v___y_1767_ = v___y_1779_;
v___y_1768_ = v___y_1780_;
v___y_1769_ = v___y_1781_;
v___y_1770_ = v___y_1782_;
v___y_1771_ = v___y_1783_;
v___y_1772_ = v___y_1784_;
v___y_1773_ = v___y_1785_;
v___y_1774_ = v___x_1787_;
goto v___jp_1765_;
}
else
{
v___y_1766_ = v___x_1786_;
v___y_1767_ = v___y_1779_;
v___y_1768_ = v___y_1780_;
v___y_1769_ = v___y_1781_;
v___y_1770_ = v___y_1782_;
v___y_1771_ = v___y_1783_;
v___y_1772_ = v___y_1784_;
v___y_1773_ = v___y_1785_;
v___y_1774_ = v___y_1782_;
goto v___jp_1765_;
}
}
v___jp_1789_:
{
uint64_t v___x_1799_; uint8_t v___x_1800_; 
v___x_1799_ = lean_uint64_shift_right(v___y_1795_, v___y_1797_);
v___x_1800_ = lean_uint64_dec_eq(v___x_1799_, v___y_1792_);
if (v___x_1800_ == 0)
{
uint64_t v___x_1801_; 
v___x_1801_ = lean_uint64_add(v___y_1791_, v___y_1797_);
v___y_1779_ = v___y_1790_;
v___y_1780_ = v___y_1792_;
v___y_1781_ = v___y_1793_;
v___y_1782_ = v___y_1798_;
v___y_1783_ = v___y_1794_;
v___y_1784_ = v___y_1796_;
v___y_1785_ = v___x_1801_;
goto v___jp_1778_;
}
else
{
v___y_1779_ = v___y_1790_;
v___y_1780_ = v___y_1792_;
v___y_1781_ = v___y_1793_;
v___y_1782_ = v___y_1798_;
v___y_1783_ = v___y_1794_;
v___y_1784_ = v___y_1796_;
v___y_1785_ = v___y_1791_;
goto v___jp_1778_;
}
}
v___jp_1802_:
{
uint64_t v___x_1810_; uint64_t v___x_1811_; uint8_t v___x_1812_; 
v___x_1810_ = 16ULL;
v___x_1811_ = lean_uint64_shift_right(v___y_1807_, v___x_1810_);
v___x_1812_ = lean_uint64_dec_eq(v___x_1811_, v___y_1804_);
if (v___x_1812_ == 0)
{
v___y_1790_ = v___y_1803_;
v___y_1791_ = v___y_1809_;
v___y_1792_ = v___y_1804_;
v___y_1793_ = v___y_1805_;
v___y_1794_ = v___y_1806_;
v___y_1795_ = v___y_1807_;
v___y_1796_ = v___y_1808_;
v___y_1797_ = v___x_1810_;
v___y_1798_ = v___x_1811_;
goto v___jp_1789_;
}
else
{
v___y_1790_ = v___y_1803_;
v___y_1791_ = v___y_1809_;
v___y_1792_ = v___y_1804_;
v___y_1793_ = v___y_1805_;
v___y_1794_ = v___y_1806_;
v___y_1795_ = v___y_1807_;
v___y_1796_ = v___y_1808_;
v___y_1797_ = v___x_1810_;
v___y_1798_ = v___y_1807_;
goto v___jp_1789_;
}
}
v___jp_1813_:
{
uint64_t v___x_1821_; uint8_t v___x_1822_; 
v___x_1821_ = lean_uint64_shift_right(v___y_1819_, v___y_1815_);
v___x_1822_ = lean_uint64_dec_eq(v___x_1821_, v___y_1816_);
if (v___x_1822_ == 0)
{
v___y_1803_ = v___y_1814_;
v___y_1804_ = v___y_1816_;
v___y_1805_ = v___y_1817_;
v___y_1806_ = v___y_1818_;
v___y_1807_ = v___y_1820_;
v___y_1808_ = v___y_1819_;
v___y_1809_ = v___y_1815_;
goto v___jp_1802_;
}
else
{
v___y_1803_ = v___y_1814_;
v___y_1804_ = v___y_1816_;
v___y_1805_ = v___y_1817_;
v___y_1806_ = v___y_1818_;
v___y_1807_ = v___y_1820_;
v___y_1808_ = v___y_1819_;
v___y_1809_ = v___y_1816_;
goto v___jp_1802_;
}
}
v___jp_1823_:
{
uint64_t v___x_1828_; uint8_t v___x_1829_; 
v___x_1828_ = 0ULL;
v___x_1829_ = lean_uint64_dec_eq(v___y_1827_, v___x_1828_);
if (v___x_1829_ == 0)
{
uint64_t v___x_1830_; uint64_t v___x_1831_; uint8_t v___x_1832_; 
v___x_1830_ = 32ULL;
v___x_1831_ = lean_uint64_shift_right(v___y_1827_, v___x_1830_);
v___x_1832_ = lean_uint64_dec_eq(v___x_1831_, v___x_1828_);
if (v___x_1832_ == 0)
{
v___y_1814_ = v___y_1824_;
v___y_1815_ = v___x_1830_;
v___y_1816_ = v___x_1828_;
v___y_1817_ = v___y_1825_;
v___y_1818_ = v___y_1826_;
v___y_1819_ = v___y_1827_;
v___y_1820_ = v___x_1831_;
goto v___jp_1813_;
}
else
{
v___y_1814_ = v___y_1824_;
v___y_1815_ = v___x_1830_;
v___y_1816_ = v___x_1828_;
v___y_1817_ = v___y_1825_;
v___y_1818_ = v___y_1826_;
v___y_1819_ = v___y_1827_;
v___y_1820_ = v___y_1827_;
goto v___jp_1813_;
}
}
else
{
if (v___y_1826_ == 0)
{
uint32_t v___x_1833_; 
v___x_1833_ = 0;
return v___x_1833_;
}
else
{
uint32_t v___x_1834_; 
v___x_1834_ = 2147483648;
return v___x_1834_;
}
}
}
v___jp_1835_:
{
uint64_t v___x_1842_; uint64_t v___x_1843_; uint64_t v___x_1844_; uint8_t v___x_1845_; 
v___x_1842_ = lean_uint64_mul(v___y_1840_, v___y_1836_);
v___x_1843_ = lean_uint64_add(v___y_1839_, v___y_1841_);
v___x_1844_ = 281474976710656ULL;
v___x_1845_ = lean_uint64_dec_lt(v___x_1842_, v___x_1844_);
if (v___x_1845_ == 0)
{
v___y_1824_ = v___x_1843_;
v___y_1825_ = v___y_1837_;
v___y_1826_ = v___y_1838_;
v___y_1827_ = v___x_1842_;
goto v___jp_1823_;
}
else
{
uint64_t v___x_1846_; uint8_t v___x_1847_; 
v___x_1846_ = 123ULL;
v___x_1847_ = lean_uint64_dec_le(v___x_1843_, v___x_1846_);
if (v___x_1847_ == 0)
{
v___y_1824_ = v___x_1843_;
v___y_1825_ = v___y_1837_;
v___y_1826_ = v___y_1838_;
v___y_1827_ = v___x_1842_;
goto v___jp_1823_;
}
else
{
uint64_t v___x_1848_; uint8_t v___x_1849_; 
v___x_1848_ = 0ULL;
v___x_1849_ = lean_uint64_dec_eq(v___x_1842_, v___x_1848_);
if (v___x_1849_ == 0)
{
uint64_t v___x_1850_; uint64_t v___x_1851_; uint8_t v___x_1852_; 
v___x_1850_ = 149ULL;
v___x_1851_ = lean_uint64_sub(v___x_1850_, v___x_1843_);
v___x_1852_ = lean_uint64_dec_eq(v___x_1851_, v___x_1848_);
if (v___x_1852_ == 0)
{
uint64_t v___x_1853_; uint8_t v___x_1854_; 
v___x_1853_ = 64ULL;
v___x_1854_ = lean_uint64_dec_lt(v___x_1851_, v___x_1853_);
if (v___x_1854_ == 0)
{
uint8_t v___x_1855_; 
v___x_1855_ = lean_uint64_dec_eq(v___x_1851_, v___x_1853_);
if (v___x_1855_ == 0)
{
v___y_1467_ = v___x_1848_;
v___y_1468_ = v___y_1837_;
v___y_1469_ = v___y_1838_;
v___y_1470_ = v___x_1848_;
goto v___jp_1466_;
}
else
{
uint64_t v___x_1856_; uint8_t v___x_1857_; 
v___x_1856_ = 9223372036854775808ULL;
v___x_1857_ = lean_uint64_dec_lt(v___x_1856_, v___x_1842_);
if (v___x_1857_ == 0)
{
v___y_1467_ = v___x_1848_;
v___y_1468_ = v___y_1837_;
v___y_1469_ = v___y_1838_;
v___y_1470_ = v___x_1848_;
goto v___jp_1466_;
}
else
{
uint64_t v___x_1858_; 
v___x_1858_ = 1ULL;
v___y_1467_ = v___x_1848_;
v___y_1468_ = v___y_1837_;
v___y_1469_ = v___y_1838_;
v___y_1470_ = v___x_1858_;
goto v___jp_1466_;
}
}
}
else
{
uint64_t v_quotient_1859_; uint64_t v___x_1860_; uint64_t v___x_1861_; uint64_t v___x_1862_; uint64_t v_remainder_1863_; uint64_t v___x_1864_; uint64_t v_half_1865_; uint8_t v___x_1866_; 
v_quotient_1859_ = lean_uint64_shift_right(v___x_1842_, v___x_1851_);
v___x_1860_ = 1ULL;
v___x_1861_ = lean_uint64_shift_left(v___x_1860_, v___x_1851_);
v___x_1862_ = lean_uint64_sub(v___x_1861_, v___x_1860_);
v_remainder_1863_ = lean_uint64_land(v___x_1842_, v___x_1862_);
v___x_1864_ = lean_uint64_sub(v___x_1851_, v___x_1860_);
v_half_1865_ = lean_uint64_shift_left(v___x_1860_, v___x_1864_);
v___x_1866_ = lean_uint64_dec_lt(v_remainder_1863_, v_half_1865_);
if (v___x_1866_ == 0)
{
uint8_t v___x_1867_; 
v___x_1867_ = lean_uint64_dec_lt(v_half_1865_, v_remainder_1863_);
if (v___x_1867_ == 0)
{
uint64_t v___x_1868_; uint8_t v___x_1869_; 
v___x_1868_ = lean_uint64_land(v_quotient_1859_, v___x_1860_);
v___x_1869_ = lean_uint64_dec_eq(v___x_1868_, v___x_1848_);
if (v___x_1869_ == 0)
{
uint64_t v___x_1870_; 
v___x_1870_ = lean_uint64_add(v_quotient_1859_, v___x_1860_);
v___y_1467_ = v___x_1848_;
v___y_1468_ = v___y_1837_;
v___y_1469_ = v___y_1838_;
v___y_1470_ = v___x_1870_;
goto v___jp_1466_;
}
else
{
v___y_1467_ = v___x_1848_;
v___y_1468_ = v___y_1837_;
v___y_1469_ = v___y_1838_;
v___y_1470_ = v_quotient_1859_;
goto v___jp_1466_;
}
}
else
{
uint64_t v___x_1871_; 
v___x_1871_ = lean_uint64_add(v_quotient_1859_, v___x_1860_);
v___y_1467_ = v___x_1848_;
v___y_1468_ = v___y_1837_;
v___y_1469_ = v___y_1838_;
v___y_1470_ = v___x_1871_;
goto v___jp_1466_;
}
}
else
{
v___y_1467_ = v___x_1848_;
v___y_1468_ = v___y_1837_;
v___y_1469_ = v___y_1838_;
v___y_1470_ = v_quotient_1859_;
goto v___jp_1466_;
}
}
}
else
{
v___y_1467_ = v___x_1848_;
v___y_1468_ = v___y_1837_;
v___y_1469_ = v___y_1838_;
v___y_1470_ = v___x_1842_;
goto v___jp_1466_;
}
}
else
{
if (v___y_1838_ == 0)
{
uint32_t v___x_1872_; 
v___x_1872_ = 0;
return v___x_1872_;
}
else
{
uint32_t v___x_1873_; 
v___x_1873_ = 2147483648;
return v___x_1873_;
}
}
}
}
}
v___jp_1877_:
{
uint64_t v___x_1883_; uint64_t v___x_1884_; uint8_t v___x_1885_; 
v___x_1883_ = lean_uint32_to_uint64(v_ey_1876_);
v___x_1884_ = 0ULL;
v___x_1885_ = lean_uint64_dec_eq(v___x_1883_, v___x_1884_);
if (v___x_1885_ == 0)
{
uint64_t v___x_1886_; uint64_t v___x_1887_; 
v___x_1886_ = 1ULL;
v___x_1887_ = lean_uint64_sub(v___x_1883_, v___x_1886_);
v___y_1836_ = v___y_1878_;
v___y_1837_ = v___y_1879_;
v___y_1838_ = v___y_1880_;
v___y_1839_ = v___y_1882_;
v___y_1840_ = v___y_1881_;
v___y_1841_ = v___x_1887_;
goto v___jp_1835_;
}
else
{
v___y_1836_ = v___y_1878_;
v___y_1837_ = v___y_1879_;
v___y_1838_ = v___y_1880_;
v___y_1839_ = v___y_1882_;
v___y_1840_ = v___y_1881_;
v___y_1841_ = v___x_1884_;
goto v___jp_1835_;
}
}
v___jp_1888_:
{
uint64_t v___x_1893_; uint64_t v___x_1894_; uint8_t v___x_1895_; 
v___x_1893_ = lean_uint32_to_uint64(v_ex_1874_);
v___x_1894_ = 0ULL;
v___x_1895_ = lean_uint64_dec_eq(v___x_1893_, v___x_1894_);
if (v___x_1895_ == 0)
{
uint64_t v___x_1896_; uint64_t v___x_1897_; 
v___x_1896_ = 1ULL;
v___x_1897_ = lean_uint64_sub(v___x_1893_, v___x_1896_);
v___y_1878_ = v___y_1892_;
v___y_1879_ = v___y_1889_;
v___y_1880_ = v___y_1890_;
v___y_1881_ = v___y_1891_;
v___y_1882_ = v___x_1897_;
goto v___jp_1877_;
}
else
{
v___y_1878_ = v___y_1892_;
v___y_1879_ = v___y_1889_;
v___y_1880_ = v___y_1890_;
v___y_1881_ = v___y_1891_;
v___y_1882_ = v___x_1894_;
goto v___jp_1877_;
}
}
v___jp_1898_:
{
uint32_t v___x_1903_; uint8_t v___x_1904_; 
v___x_1903_ = 0;
v___x_1904_ = lean_uint32_dec_eq(v_ey_1876_, v___x_1903_);
if (v___x_1904_ == 0)
{
uint64_t v___x_1905_; uint64_t v___x_1906_; uint64_t v___x_1907_; 
v___x_1905_ = lean_uint32_to_uint64(v___y_1901_);
v___x_1906_ = 8388608ULL;
v___x_1907_ = lean_uint64_lor(v___x_1905_, v___x_1906_);
v___y_1889_ = v___y_1899_;
v___y_1890_ = v___y_1900_;
v___y_1891_ = v___y_1902_;
v___y_1892_ = v___x_1907_;
goto v___jp_1888_;
}
else
{
uint64_t v___x_1908_; 
v___x_1908_ = lean_uint32_to_uint64(v___y_1901_);
v___y_1889_ = v___y_1899_;
v___y_1890_ = v___y_1900_;
v___y_1891_ = v___y_1902_;
v___y_1892_ = v___x_1908_;
goto v___jp_1888_;
}
}
v___jp_1909_:
{
uint32_t v___x_1911_; uint32_t v_xFraction_1912_; uint32_t v_yFraction_1913_; uint32_t v___x_1914_; uint8_t v___x_1915_; 
v___x_1911_ = 8388607;
v_xFraction_1912_ = lean_uint32_land(v___y_1429_, v___x_1911_);
v_yFraction_1913_ = lean_uint32_land(v___y_1430_, v___x_1911_);
v___x_1914_ = 0;
v___x_1915_ = lean_uint32_dec_eq(v_ex_1874_, v___x_1914_);
if (v___x_1915_ == 0)
{
uint64_t v___x_1916_; uint64_t v___x_1917_; uint64_t v___x_1918_; 
v___x_1916_ = lean_uint32_to_uint64(v_xFraction_1912_);
v___x_1917_ = 8388608ULL;
v___x_1918_ = lean_uint64_lor(v___x_1916_, v___x_1917_);
v___y_1899_ = v___x_1911_;
v___y_1900_ = v___y_1910_;
v___y_1901_ = v_yFraction_1913_;
v___y_1902_ = v___x_1918_;
goto v___jp_1898_;
}
else
{
uint64_t v___x_1919_; 
v___x_1919_ = lean_uint32_to_uint64(v_xFraction_1912_);
v___y_1899_ = v___x_1911_;
v___y_1900_ = v___y_1910_;
v___y_1901_ = v_yFraction_1913_;
v___y_1902_ = v___x_1919_;
goto v___jp_1898_;
}
}
v___jp_1923_:
{
if (v___y_1925_ == 0)
{
v___y_1910_ = v___x_1922_;
goto v___jp_1909_;
}
else
{
v___y_1910_ = v___y_1924_;
goto v___jp_1909_;
}
}
v___jp_1926_:
{
if (v___y_1927_ == 0)
{
if (v___y_1929_ == 0)
{
v___y_1924_ = v___y_1928_;
v___y_1925_ = v___x_1922_;
goto v___jp_1923_;
}
else
{
v___y_1910_ = v___x_1922_;
goto v___jp_1909_;
}
}
else
{
v___y_1924_ = v___y_1928_;
v___y_1925_ = v___y_1929_;
goto v___jp_1923_;
}
}
v___jp_1930_:
{
uint32_t v___x_1933_; uint32_t v___x_1934_; uint32_t v___x_1935_; uint8_t v___x_1936_; 
v___x_1933_ = 2147483648;
v___x_1934_ = lean_uint32_land(v___y_1430_, v___x_1933_);
v___x_1935_ = 0;
v___x_1936_ = lean_uint32_dec_eq(v___x_1934_, v___x_1935_);
if (v___x_1936_ == 0)
{
v___y_1927_ = v___y_1932_;
v___y_1928_ = v___y_1931_;
v___y_1929_ = v___x_1922_;
goto v___jp_1926_;
}
else
{
v___y_1927_ = v___y_1932_;
v___y_1928_ = v___y_1931_;
v___y_1929_ = v___y_1931_;
goto v___jp_1926_;
}
}
v___jp_1937_:
{
if (v___y_1938_ == 0)
{
uint32_t v___x_1939_; uint32_t v___x_1940_; uint32_t v___x_1941_; uint8_t v___x_1942_; 
v___x_1939_ = 2147483648;
v___x_1940_ = lean_uint32_land(v___y_1429_, v___x_1939_);
v___x_1941_ = 0;
v___x_1942_ = lean_uint32_dec_eq(v___x_1940_, v___x_1941_);
if (v___x_1942_ == 0)
{
v___y_1931_ = v___y_1938_;
v___y_1932_ = v___x_1922_;
goto v___jp_1930_;
}
else
{
v___y_1931_ = v___y_1938_;
v___y_1932_ = v___y_1938_;
goto v___jp_1930_;
}
}
else
{
lean_object* v___x_1943_; lean_object* v___x_1944_; lean_object* v___x_1945_; uint32_t v___x_1946_; 
v___x_1943_ = lean_uint32_to_nat(v___y_1429_);
v___x_1944_ = lean_uint32_to_nat(v___y_1430_);
v___x_1945_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1943_, v___x_1944_);
v___x_1946_ = lean_uint32_of_nat(v___x_1945_);
lean_dec(v___x_1945_);
return v___x_1946_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_runF64Boxed___lam__1___boxed(lean_object* v___y_1961_, lean_object* v___y_1962_){
_start:
{
uint32_t v___y_1949__boxed_1963_; uint32_t v___y_1950__boxed_1964_; uint32_t v_res_1965_; lean_object* v_r_1966_; 
v___y_1949__boxed_1963_ = lean_unbox_uint32(v___y_1961_);
lean_dec(v___y_1961_);
v___y_1950__boxed_1964_ = lean_unbox_uint32(v___y_1962_);
lean_dec(v___y_1962_);
v_res_1965_ = lp_competition_runF64Boxed___lam__1(v___y_1949__boxed_1963_, v___y_1950__boxed_1964_);
v_r_1966_ = lean_box_uint32(v_res_1965_);
return v_r_1966_;
}
}
LEAN_EXPORT lean_object* lp_competition_runF64Boxed(){
_start:
{
lean_object* v___f_1970_; lean_object* v___f_1971_; lean_object* v___x_1972_; lean_object* v___x_1973_; lean_object* v___x_1974_; 
v___f_1970_ = ((lean_object*)(lp_competition_runF64Boxed___closed__0));
v___f_1971_ = ((lean_object*)(lp_competition_runF64Boxed___closed__1));
v___x_1972_ = ((lean_object*)(lp_competition_runControl___closed__2));
v___x_1973_ = ((lean_object*)(lp_competition_runControl___closed__3));
v___x_1974_ = lp_competition_Bench_Suite_run(v___f_1970_, v___f_1971_, v___x_1972_, v___x_1973_);
return v___x_1974_;
}
}
LEAN_EXPORT lean_object* lp_competition_runF64Boxed___boxed(lean_object* v_a_1975_){
_start:
{
lean_object* v_res_1976_; 
v_res_1976_ = lp_competition_runF64Boxed();
return v_res_1976_;
}
}
LEAN_EXPORT uint32_t lp_competition_runF64Cast___lam__0(uint32_t v___y_1977_, uint32_t v___y_1978_){
_start:
{
double v___y_1980_; uint32_t v___y_1981_; lean_object* v___y_1982_; uint32_t v___y_1983_; uint32_t v___y_1993_; uint32_t v___x_2009_; uint32_t v___x_2010_; uint8_t v___x_2011_; 
v___x_2009_ = 2139095040;
v___x_2010_ = lean_uint32_land(v___y_1977_, v___x_2009_);
v___x_2011_ = lean_uint32_dec_eq(v___x_2010_, v___x_2009_);
if (v___x_2011_ == 0)
{
uint32_t v___x_2012_; uint8_t v___x_2013_; 
v___x_2012_ = lean_uint32_land(v___y_1978_, v___x_2009_);
v___x_2013_ = lean_uint32_dec_eq(v___x_2012_, v___x_2009_);
if (v___x_2013_ == 0)
{
uint32_t v___x_2014_; uint32_t v___x_2015_; uint32_t v___x_2016_; uint8_t v___x_2017_; 
v___x_2014_ = 8388607;
v___x_2015_ = lean_uint32_land(v___y_1977_, v___x_2014_);
v___x_2016_ = 0;
v___x_2017_ = lean_uint32_dec_eq(v___x_2010_, v___x_2016_);
if (v___x_2017_ == 0)
{
uint32_t v___x_2018_; uint32_t v___x_2019_; 
v___x_2018_ = 8388608;
v___x_2019_ = lean_uint32_lor(v___x_2015_, v___x_2018_);
v___y_1993_ = v___x_2019_;
goto v___jp_1992_;
}
else
{
v___y_1993_ = v___x_2015_;
goto v___jp_1992_;
}
}
else
{
uint32_t v___x_2020_; 
v___x_2020_ = lp_competition_Submission_R24F64Add_retainedAdd(v___y_1977_, v___y_1978_);
return v___x_2020_;
}
}
else
{
uint32_t v___x_2021_; 
v___x_2021_ = lp_competition_Submission_R24F64Add_retainedAdd(v___y_1977_, v___y_1978_);
return v___x_2021_;
}
v___jp_1979_:
{
double v___x_1984_; uint32_t v___x_1985_; lean_object* v___x_1986_; double v___x_1987_; double v___x_1988_; double v___x_1989_; float v___x_1990_; uint32_t v___x_1991_; 
v___x_1984_ = lean_uint32_to_float(v___y_1983_);
v___x_1985_ = lean_uint32_shift_right(v___y_1978_, v___y_1981_);
v___x_1986_ = lean_uint32_to_nat(v___x_1985_);
v___x_1987_ = lean_float_array_get(v___y_1982_, v___x_1986_);
lean_dec(v___x_1986_);
v___x_1988_ = lean_float_mul(v___x_1984_, v___x_1987_);
v___x_1989_ = lean_float_add(v___y_1980_, v___x_1988_);
v___x_1990_ = lean_float_to_float32(v___x_1989_);
v___x_1991_ = lean_float32_to_bits(v___x_1990_);
return v___x_1991_;
}
v___jp_1992_:
{
double v___x_1994_; lean_object* v___x_1995_; uint32_t v___x_1996_; uint32_t v___x_1997_; lean_object* v___x_1998_; double v___x_1999_; double v___x_2000_; uint32_t v___x_2001_; uint32_t v___x_2002_; uint32_t v___x_2003_; uint32_t v___x_2004_; uint32_t v___x_2005_; uint8_t v___x_2006_; 
v___x_1994_ = lean_uint32_to_float(v___y_1993_);
v___x_1995_ = lp_competition_Submission_R24F64Add_nativeScales;
v___x_1996_ = 23;
v___x_1997_ = lean_uint32_shift_right(v___y_1977_, v___x_1996_);
v___x_1998_ = lean_uint32_to_nat(v___x_1997_);
v___x_1999_ = lean_float_array_get(v___x_1995_, v___x_1998_);
lean_dec(v___x_1998_);
v___x_2000_ = lean_float_mul(v___x_1994_, v___x_1999_);
v___x_2001_ = 8388607;
v___x_2002_ = lean_uint32_land(v___y_1978_, v___x_2001_);
v___x_2003_ = 2139095040;
v___x_2004_ = lean_uint32_land(v___y_1978_, v___x_2003_);
v___x_2005_ = 0;
v___x_2006_ = lean_uint32_dec_eq(v___x_2004_, v___x_2005_);
if (v___x_2006_ == 0)
{
uint32_t v___x_2007_; uint32_t v___x_2008_; 
v___x_2007_ = 8388608;
v___x_2008_ = lean_uint32_lor(v___x_2002_, v___x_2007_);
v___y_1980_ = v___x_2000_;
v___y_1981_ = v___x_1996_;
v___y_1982_ = v___x_1995_;
v___y_1983_ = v___x_2008_;
goto v___jp_1979_;
}
else
{
v___y_1980_ = v___x_2000_;
v___y_1981_ = v___x_1996_;
v___y_1982_ = v___x_1995_;
v___y_1983_ = v___x_2002_;
goto v___jp_1979_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_runF64Cast___lam__0___boxed(lean_object* v___y_2022_, lean_object* v___y_2023_){
_start:
{
uint32_t v___y_1678__boxed_2024_; uint32_t v___y_1679__boxed_2025_; uint32_t v_res_2026_; lean_object* v_r_2027_; 
v___y_1678__boxed_2024_ = lean_unbox_uint32(v___y_2022_);
lean_dec(v___y_2022_);
v___y_1679__boxed_2025_ = lean_unbox_uint32(v___y_2023_);
lean_dec(v___y_2023_);
v_res_2026_ = lp_competition_runF64Cast___lam__0(v___y_1678__boxed_2024_, v___y_1679__boxed_2025_);
v_r_2027_ = lean_box_uint32(v_res_2026_);
return v_r_2027_;
}
}
LEAN_EXPORT uint32_t lp_competition_runF64Cast___lam__1(uint32_t v___y_2028_, uint32_t v___y_2029_){
_start:
{
uint32_t v___y_2031_; uint32_t v___y_2035_; uint32_t v___y_2039_; uint32_t v___y_2040_; uint32_t v___y_2041_; uint8_t v___y_2045_; uint32_t v___y_2046_; uint64_t v___y_2047_; uint64_t v___y_2048_; uint32_t v___y_2060_; uint32_t v___y_2061_; uint32_t v___y_2062_; uint8_t v___y_2066_; uint32_t v___y_2067_; uint64_t v___y_2068_; uint64_t v___y_2069_; uint8_t v___y_2081_; uint8_t v___y_2097_; uint8_t v___y_2111_; uint8_t v___y_2128_; float v___y_2135_; float v___y_2136_; float v___y_2150_; uint8_t v___y_2151_; float v___y_2166_; uint32_t v___x_2175_; uint32_t v___x_2176_; uint8_t v___y_2178_; uint32_t v___x_2190_; uint32_t v___y_2192_; uint32_t v___y_2193_; uint32_t v___y_2194_; uint32_t v___y_2195_; uint8_t v___y_2202_; uint32_t v___y_2203_; uint32_t v___y_2204_; uint32_t v___y_2205_; uint64_t v___y_2209_; uint64_t v___y_2210_; uint32_t v___y_2211_; uint8_t v___y_2212_; uint64_t v___y_2213_; uint8_t v___y_2223_; uint32_t v___y_2224_; uint64_t v___y_2225_; uint64_t v___y_2226_; uint8_t v___y_2227_; uint64_t v___y_2228_; uint64_t v___y_2235_; uint64_t v___y_2236_; uint32_t v___y_2237_; uint8_t v___y_2238_; uint64_t v___y_2239_; uint64_t v___y_2245_; uint8_t v___y_2246_; uint32_t v___y_2247_; uint64_t v___y_2248_; uint64_t v___y_2249_; uint64_t v___y_2250_; uint64_t v___y_2305_; uint32_t v___y_2306_; uint8_t v___y_2307_; uint64_t v___y_2308_; uint64_t v___y_2309_; uint64_t v___y_2310_; uint64_t v___y_2311_; uint64_t v___y_2317_; uint64_t v___y_2318_; uint64_t v___y_2319_; uint64_t v___y_2320_; uint8_t v___y_2321_; uint32_t v___y_2322_; uint64_t v___y_2323_; uint64_t v___y_2324_; uint64_t v___y_2325_; uint64_t v___y_2330_; uint32_t v___y_2331_; uint8_t v___y_2332_; uint64_t v___y_2333_; uint64_t v___y_2334_; uint64_t v___y_2335_; uint64_t v___y_2336_; uint64_t v___y_2341_; uint64_t v___y_2342_; uint64_t v___y_2343_; uint8_t v___y_2344_; uint32_t v___y_2345_; uint64_t v___y_2346_; uint64_t v___y_2347_; uint64_t v___y_2348_; uint64_t v___y_2349_; uint64_t v___y_2354_; uint64_t v___y_2355_; uint32_t v___y_2356_; uint8_t v___y_2357_; uint64_t v___y_2358_; uint64_t v___y_2359_; uint64_t v___y_2360_; uint64_t v___y_2365_; uint64_t v___y_2366_; uint64_t v___y_2367_; uint64_t v___y_2368_; uint8_t v___y_2369_; uint32_t v___y_2370_; uint64_t v___y_2371_; uint64_t v___y_2372_; uint64_t v___y_2373_; uint64_t v___y_2378_; uint64_t v___y_2379_; uint32_t v___y_2380_; uint8_t v___y_2381_; uint64_t v___y_2382_; uint64_t v___y_2383_; uint64_t v___y_2384_; uint64_t v___y_2389_; uint64_t v___y_2390_; uint64_t v___y_2391_; uint8_t v___y_2392_; uint32_t v___y_2393_; uint64_t v___y_2394_; uint64_t v___y_2395_; uint64_t v___y_2396_; uint64_t v___y_2397_; uint64_t v___y_2402_; uint32_t v___y_2403_; uint8_t v___y_2404_; uint64_t v___y_2405_; uint64_t v___y_2406_; uint64_t v___y_2407_; uint64_t v___y_2408_; uint64_t v___y_2413_; uint64_t v___y_2414_; uint64_t v___y_2415_; uint8_t v___y_2416_; uint32_t v___y_2417_; uint64_t v___y_2418_; uint64_t v___y_2419_; uint64_t v___y_2423_; uint32_t v___y_2424_; uint8_t v___y_2425_; uint64_t v___y_2426_; uint64_t v___y_2435_; uint64_t v___y_2436_; uint8_t v___y_2437_; uint32_t v___y_2438_; uint64_t v___y_2439_; uint64_t v___y_2440_; uint32_t v_ex_2473_; uint32_t v___x_2474_; uint32_t v_ey_2475_; uint64_t v___y_2477_; uint64_t v___y_2478_; uint32_t v___y_2479_; uint8_t v___y_2480_; uint64_t v___y_2481_; uint8_t v___y_2488_; uint32_t v___y_2489_; uint64_t v___y_2490_; uint64_t v___y_2491_; uint32_t v___y_2498_; uint32_t v___y_2499_; uint8_t v___y_2500_; uint64_t v___y_2501_; uint8_t v___y_2509_; uint32_t v___x_2519_; uint32_t v___x_2520_; uint8_t v___x_2521_; uint8_t v___y_2523_; uint8_t v___y_2524_; uint8_t v___y_2526_; uint8_t v___y_2527_; uint8_t v___y_2528_; uint8_t v___y_2530_; uint8_t v___y_2531_; uint8_t v___y_2537_; 
v___x_2175_ = 23;
v___x_2176_ = lean_uint32_shift_right(v___y_2028_, v___x_2175_);
v___x_2190_ = 255;
v_ex_2473_ = lean_uint32_land(v___x_2176_, v___x_2190_);
v___x_2474_ = lean_uint32_shift_right(v___y_2029_, v___x_2175_);
v_ey_2475_ = lean_uint32_land(v___x_2474_, v___x_2190_);
v___x_2519_ = lean_uint32_add(v_ex_2473_, v_ey_2475_);
v___x_2520_ = 128;
v___x_2521_ = lean_uint32_dec_lt(v___x_2519_, v___x_2520_);
if (v___x_2521_ == 0)
{
uint32_t v___x_2546_; uint32_t v_a_2547_; uint32_t v___x_2548_; uint32_t v___x_2549_; uint32_t v___x_2550_; uint8_t v___x_2551_; 
v___x_2546_ = 2147483647;
v_a_2547_ = lean_uint32_land(v___y_2028_, v___x_2546_);
v___x_2548_ = 201326591;
v___x_2549_ = 1;
v___x_2550_ = lean_uint32_sub(v_a_2547_, v___x_2549_);
v___x_2551_ = lean_uint32_dec_le(v___x_2548_, v___x_2550_);
if (v___x_2551_ == 0)
{
v___y_2178_ = v___x_2551_;
goto v___jp_2177_;
}
else
{
uint32_t v___x_2552_; uint8_t v___x_2553_; 
v___x_2552_ = 2139095040;
v___x_2553_ = lean_uint32_dec_lt(v_a_2547_, v___x_2552_);
v___y_2178_ = v___x_2553_;
goto v___jp_2177_;
}
}
else
{
uint32_t v___x_2554_; uint32_t v___x_2555_; uint32_t v___x_2556_; uint8_t v___x_2557_; 
v___x_2554_ = 4278190080;
v___x_2555_ = 1;
v___x_2556_ = lean_uint32_shift_left(v___y_2028_, v___x_2555_);
v___x_2557_ = lean_uint32_dec_le(v___x_2554_, v___x_2556_);
if (v___x_2557_ == 0)
{
uint32_t v___x_2558_; uint8_t v___x_2559_; 
v___x_2558_ = lean_uint32_shift_left(v___y_2029_, v___x_2555_);
v___x_2559_ = lean_uint32_dec_le(v___x_2554_, v___x_2558_);
v___y_2537_ = v___x_2559_;
goto v___jp_2536_;
}
else
{
v___y_2537_ = v___x_2557_;
goto v___jp_2536_;
}
}
v___jp_2030_:
{
uint32_t v___x_2032_; uint32_t v___x_2033_; 
v___x_2032_ = 8388608;
v___x_2033_ = lean_uint32_lor(v___y_2031_, v___x_2032_);
return v___x_2033_;
}
v___jp_2034_:
{
uint32_t v___x_2036_; uint32_t v___x_2037_; 
v___x_2036_ = 8388608;
v___x_2037_ = lean_uint32_lor(v___y_2035_, v___x_2036_);
return v___x_2037_;
}
v___jp_2038_:
{
uint32_t v___x_2042_; uint32_t v___x_2043_; 
v___x_2042_ = lean_uint32_land(v___y_2040_, v___y_2039_);
v___x_2043_ = lean_uint32_lor(v___y_2041_, v___x_2042_);
return v___x_2043_;
}
v___jp_2044_:
{
uint8_t v___x_2049_; 
v___x_2049_ = lean_uint64_dec_eq(v___y_2048_, v___y_2047_);
if (v___x_2049_ == 0)
{
uint64_t v___x_2050_; uint8_t v___x_2051_; 
v___x_2050_ = 8388608ULL;
v___x_2051_ = lean_uint64_dec_eq(v___y_2048_, v___x_2050_);
if (v___x_2051_ == 0)
{
uint32_t v___x_2052_; 
v___x_2052_ = lean_uint64_to_uint32(v___y_2048_);
if (v___y_2045_ == 0)
{
uint32_t v___x_2053_; 
v___x_2053_ = 0;
v___y_2039_ = v___y_2046_;
v___y_2040_ = v___x_2052_;
v___y_2041_ = v___x_2053_;
goto v___jp_2038_;
}
else
{
uint32_t v___x_2054_; 
v___x_2054_ = 2147483648;
v___y_2039_ = v___y_2046_;
v___y_2040_ = v___x_2052_;
v___y_2041_ = v___x_2054_;
goto v___jp_2038_;
}
}
else
{
if (v___y_2045_ == 0)
{
uint32_t v___x_2055_; 
v___x_2055_ = 0;
v___y_2035_ = v___x_2055_;
goto v___jp_2034_;
}
else
{
uint32_t v___x_2056_; 
v___x_2056_ = 2147483648;
v___y_2035_ = v___x_2056_;
goto v___jp_2034_;
}
}
}
else
{
if (v___y_2045_ == 0)
{
uint32_t v___x_2057_; 
v___x_2057_ = 0;
return v___x_2057_;
}
else
{
uint32_t v___x_2058_; 
v___x_2058_ = 2147483648;
return v___x_2058_;
}
}
}
v___jp_2059_:
{
uint32_t v___x_2063_; uint32_t v___x_2064_; 
v___x_2063_ = lean_uint32_land(v___y_2061_, v___y_2060_);
v___x_2064_ = lean_uint32_lor(v___y_2062_, v___x_2063_);
return v___x_2064_;
}
v___jp_2065_:
{
uint8_t v___x_2070_; 
v___x_2070_ = lean_uint64_dec_eq(v___y_2069_, v___y_2068_);
if (v___x_2070_ == 0)
{
uint64_t v___x_2071_; uint8_t v___x_2072_; 
v___x_2071_ = 8388608ULL;
v___x_2072_ = lean_uint64_dec_eq(v___y_2069_, v___x_2071_);
if (v___x_2072_ == 0)
{
uint32_t v___x_2073_; 
v___x_2073_ = lean_uint64_to_uint32(v___y_2069_);
if (v___y_2066_ == 0)
{
uint32_t v___x_2074_; 
v___x_2074_ = 0;
v___y_2060_ = v___y_2067_;
v___y_2061_ = v___x_2073_;
v___y_2062_ = v___x_2074_;
goto v___jp_2059_;
}
else
{
uint32_t v___x_2075_; 
v___x_2075_ = 2147483648;
v___y_2060_ = v___y_2067_;
v___y_2061_ = v___x_2073_;
v___y_2062_ = v___x_2075_;
goto v___jp_2059_;
}
}
else
{
if (v___y_2066_ == 0)
{
uint32_t v___x_2076_; 
v___x_2076_ = 0;
v___y_2031_ = v___x_2076_;
goto v___jp_2030_;
}
else
{
uint32_t v___x_2077_; 
v___x_2077_ = 2147483648;
v___y_2031_ = v___x_2077_;
goto v___jp_2030_;
}
}
}
else
{
if (v___y_2066_ == 0)
{
uint32_t v___x_2078_; 
v___x_2078_ = 0;
return v___x_2078_;
}
else
{
uint32_t v___x_2079_; 
v___x_2079_ = 2147483648;
return v___x_2079_;
}
}
}
v___jp_2080_:
{
if (v___y_2081_ == 0)
{
uint32_t v___x_2082_; 
v___x_2082_ = lp_competition_Submission_FastMul_mul(v___y_2028_, v___y_2029_);
return v___x_2082_;
}
else
{
uint32_t v___x_2083_; uint32_t v___x_2084_; 
v___x_2083_ = 4194304;
v___x_2084_ = lean_uint32_lor(v___y_2029_, v___x_2083_);
return v___x_2084_;
}
}
v___jp_2085_:
{
uint32_t v___x_2086_; uint32_t v___x_2087_; uint32_t v___x_2088_; uint32_t v___x_2089_; uint8_t v___x_2090_; 
v___x_2086_ = 23;
v___x_2087_ = lean_uint32_shift_right(v___y_2029_, v___x_2086_);
v___x_2088_ = 255;
v___x_2089_ = lean_uint32_land(v___x_2087_, v___x_2088_);
v___x_2090_ = lean_uint32_dec_eq(v___x_2089_, v___x_2088_);
if (v___x_2090_ == 0)
{
v___y_2081_ = v___x_2090_;
goto v___jp_2080_;
}
else
{
uint32_t v___x_2091_; uint32_t v___x_2092_; uint32_t v___x_2093_; uint8_t v___x_2094_; 
v___x_2091_ = 8388607;
v___x_2092_ = lean_uint32_land(v___y_2029_, v___x_2091_);
v___x_2093_ = 0;
v___x_2094_ = lean_uint32_dec_eq(v___x_2092_, v___x_2093_);
if (v___x_2094_ == 0)
{
v___y_2081_ = v___x_2090_;
goto v___jp_2080_;
}
else
{
uint32_t v___x_2095_; 
v___x_2095_ = lp_competition_Submission_FastMul_mul(v___y_2028_, v___y_2029_);
return v___x_2095_;
}
}
}
v___jp_2096_:
{
if (v___y_2097_ == 0)
{
goto v___jp_2085_;
}
else
{
uint32_t v___x_2098_; uint32_t v___x_2099_; 
v___x_2098_ = 4194304;
v___x_2099_ = lean_uint32_lor(v___y_2028_, v___x_2098_);
return v___x_2099_;
}
}
v___jp_2100_:
{
uint32_t v___x_2101_; uint32_t v___x_2102_; uint32_t v___x_2103_; uint32_t v___x_2104_; uint8_t v___x_2105_; 
v___x_2101_ = 23;
v___x_2102_ = lean_uint32_shift_right(v___y_2028_, v___x_2101_);
v___x_2103_ = 255;
v___x_2104_ = lean_uint32_land(v___x_2102_, v___x_2103_);
v___x_2105_ = lean_uint32_dec_eq(v___x_2104_, v___x_2103_);
if (v___x_2105_ == 0)
{
v___y_2097_ = v___x_2105_;
goto v___jp_2096_;
}
else
{
uint32_t v___x_2106_; uint32_t v___x_2107_; uint32_t v___x_2108_; uint8_t v___x_2109_; 
v___x_2106_ = 8388607;
v___x_2107_ = lean_uint32_land(v___y_2028_, v___x_2106_);
v___x_2108_ = 0;
v___x_2109_ = lean_uint32_dec_eq(v___x_2107_, v___x_2108_);
if (v___x_2109_ == 0)
{
v___y_2097_ = v___x_2105_;
goto v___jp_2096_;
}
else
{
goto v___jp_2085_;
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
v___x_2113_ = lean_uint32_land(v___y_2029_, v___x_2112_);
v___x_2114_ = 0;
v___x_2115_ = lean_uint32_dec_eq(v___x_2113_, v___x_2114_);
if (v___x_2115_ == 0)
{
goto v___jp_2100_;
}
else
{
uint32_t v___x_2116_; 
v___x_2116_ = lean_uint32_lor(v___y_2029_, v___x_2112_);
return v___x_2116_;
}
}
}
v___jp_2117_:
{
uint32_t v___x_2118_; uint32_t v___x_2119_; uint32_t v___x_2120_; uint32_t v___x_2121_; uint8_t v___x_2122_; 
v___x_2118_ = 23;
v___x_2119_ = lean_uint32_shift_right(v___y_2029_, v___x_2118_);
v___x_2120_ = 255;
v___x_2121_ = lean_uint32_land(v___x_2119_, v___x_2120_);
v___x_2122_ = lean_uint32_dec_eq(v___x_2121_, v___x_2120_);
if (v___x_2122_ == 0)
{
v___y_2111_ = v___x_2122_;
goto v___jp_2110_;
}
else
{
uint32_t v___x_2123_; uint32_t v___x_2124_; uint32_t v___x_2125_; uint8_t v___x_2126_; 
v___x_2123_ = 8388607;
v___x_2124_ = lean_uint32_land(v___y_2029_, v___x_2123_);
v___x_2125_ = 0;
v___x_2126_ = lean_uint32_dec_eq(v___x_2124_, v___x_2125_);
if (v___x_2126_ == 0)
{
v___y_2111_ = v___x_2122_;
goto v___jp_2110_;
}
else
{
goto v___jp_2100_;
}
}
}
v___jp_2127_:
{
if (v___y_2128_ == 0)
{
goto v___jp_2117_;
}
else
{
uint32_t v___x_2129_; uint32_t v___x_2130_; uint32_t v___x_2131_; uint8_t v___x_2132_; 
v___x_2129_ = 4194304;
v___x_2130_ = lean_uint32_land(v___y_2028_, v___x_2129_);
v___x_2131_ = 0;
v___x_2132_ = lean_uint32_dec_eq(v___x_2130_, v___x_2131_);
if (v___x_2132_ == 0)
{
goto v___jp_2117_;
}
else
{
uint32_t v___x_2133_; 
v___x_2133_ = lean_uint32_lor(v___y_2028_, v___x_2129_);
return v___x_2133_;
}
}
}
v___jp_2134_:
{
float v_result_2137_; uint8_t v___x_2138_; 
v_result_2137_ = lean_float32_mul(v___y_2135_, v___y_2136_);
v___x_2138_ = lean_float32_beq(v_result_2137_, v_result_2137_);
if (v___x_2138_ == 0)
{
uint32_t v___x_2139_; uint32_t v___x_2140_; uint32_t v___x_2141_; uint32_t v___x_2142_; uint8_t v___x_2143_; 
v___x_2139_ = 23;
v___x_2140_ = lean_uint32_shift_right(v___y_2028_, v___x_2139_);
v___x_2141_ = 255;
v___x_2142_ = lean_uint32_land(v___x_2140_, v___x_2141_);
v___x_2143_ = lean_uint32_dec_eq(v___x_2142_, v___x_2141_);
if (v___x_2143_ == 0)
{
v___y_2128_ = v___x_2143_;
goto v___jp_2127_;
}
else
{
uint32_t v___x_2144_; uint32_t v___x_2145_; uint32_t v___x_2146_; uint8_t v___x_2147_; 
v___x_2144_ = 8388607;
v___x_2145_ = lean_uint32_land(v___y_2028_, v___x_2144_);
v___x_2146_ = 0;
v___x_2147_ = lean_uint32_dec_eq(v___x_2145_, v___x_2146_);
if (v___x_2147_ == 0)
{
v___y_2128_ = v___x_2143_;
goto v___jp_2127_;
}
else
{
goto v___jp_2117_;
}
}
}
else
{
uint32_t v___x_2148_; 
v___x_2148_ = lean_float32_to_bits(v_result_2137_);
return v___x_2148_;
}
}
v___jp_2149_:
{
if (v___y_2151_ == 0)
{
float v___x_2152_; 
v___x_2152_ = lean_float32_of_bits(v___y_2029_);
v___y_2135_ = v___y_2150_;
v___y_2136_ = v___x_2152_;
goto v___jp_2134_;
}
else
{
uint32_t v___x_2153_; uint32_t v___x_2154_; uint32_t v___x_2155_; uint32_t v___x_2156_; float v___x_2157_; lean_object* v___x_2158_; uint32_t v___x_2159_; uint32_t v___x_2160_; lean_object* v___x_2161_; lean_object* v___x_2162_; float v___x_2163_; float v___x_2164_; 
v___x_2153_ = 8388607;
v___x_2154_ = lean_uint32_land(v___y_2029_, v___x_2153_);
v___x_2155_ = 8388608;
v___x_2156_ = lean_uint32_lor(v___x_2154_, v___x_2155_);
v___x_2157_ = lean_uint32_to_float32(v___x_2156_);
v___x_2158_ = lp_competition_R2W01b_scaleTable;
v___x_2159_ = 23;
v___x_2160_ = lean_uint32_shift_right(v___y_2029_, v___x_2159_);
v___x_2161_ = lean_uint32_to_nat(v___x_2160_);
v___x_2162_ = lean_array_fget_borrowed(v___x_2158_, v___x_2161_);
lean_dec(v___x_2161_);
v___x_2163_ = lean_unbox_float32(v___x_2162_);
v___x_2164_ = lean_float32_mul(v___x_2157_, v___x_2163_);
v___y_2135_ = v___y_2150_;
v___y_2136_ = v___x_2164_;
goto v___jp_2134_;
}
}
v___jp_2165_:
{
uint32_t v___x_2167_; uint32_t v_a_2168_; uint32_t v___x_2169_; uint32_t v___x_2170_; uint32_t v___x_2171_; uint8_t v___x_2172_; 
v___x_2167_ = 2147483647;
v_a_2168_ = lean_uint32_land(v___y_2029_, v___x_2167_);
v___x_2169_ = 201326591;
v___x_2170_ = 1;
v___x_2171_ = lean_uint32_sub(v_a_2168_, v___x_2170_);
v___x_2172_ = lean_uint32_dec_le(v___x_2169_, v___x_2171_);
if (v___x_2172_ == 0)
{
v___y_2150_ = v___y_2166_;
v___y_2151_ = v___x_2172_;
goto v___jp_2149_;
}
else
{
uint32_t v___x_2173_; uint8_t v___x_2174_; 
v___x_2173_ = 2139095040;
v___x_2174_ = lean_uint32_dec_lt(v_a_2168_, v___x_2173_);
v___y_2150_ = v___y_2166_;
v___y_2151_ = v___x_2174_;
goto v___jp_2149_;
}
}
v___jp_2177_:
{
if (v___y_2178_ == 0)
{
float v___x_2179_; 
v___x_2179_ = lean_float32_of_bits(v___y_2028_);
v___y_2166_ = v___x_2179_;
goto v___jp_2165_;
}
else
{
uint32_t v___x_2180_; uint32_t v___x_2181_; uint32_t v___x_2182_; uint32_t v___x_2183_; float v___x_2184_; lean_object* v___x_2185_; lean_object* v___x_2186_; lean_object* v___x_2187_; float v___x_2188_; float v___x_2189_; 
v___x_2180_ = 8388607;
v___x_2181_ = lean_uint32_land(v___y_2028_, v___x_2180_);
v___x_2182_ = 8388608;
v___x_2183_ = lean_uint32_lor(v___x_2181_, v___x_2182_);
v___x_2184_ = lean_uint32_to_float32(v___x_2183_);
v___x_2185_ = lp_competition_R2W01b_scaleTable;
v___x_2186_ = lean_uint32_to_nat(v___x_2176_);
v___x_2187_ = lean_array_fget_borrowed(v___x_2185_, v___x_2186_);
lean_dec(v___x_2186_);
v___x_2188_ = lean_unbox_float32(v___x_2187_);
v___x_2189_ = lean_float32_mul(v___x_2184_, v___x_2188_);
v___y_2166_ = v___x_2189_;
goto v___jp_2165_;
}
}
v___jp_2191_:
{
uint32_t v___x_2196_; uint32_t v___x_2197_; uint32_t v___x_2198_; uint32_t v___x_2199_; uint32_t v___x_2200_; 
v___x_2196_ = lean_uint32_land(v___y_2194_, v___x_2190_);
v___x_2197_ = lean_uint32_shift_left(v___x_2196_, v___x_2175_);
v___x_2198_ = lean_uint32_lor(v___y_2195_, v___x_2197_);
v___x_2199_ = lean_uint32_land(v___y_2193_, v___y_2192_);
v___x_2200_ = lean_uint32_lor(v___x_2198_, v___x_2199_);
return v___x_2200_;
}
v___jp_2201_:
{
if (v___y_2202_ == 0)
{
uint32_t v___x_2206_; 
v___x_2206_ = 0;
v___y_2192_ = v___y_2203_;
v___y_2193_ = v___y_2205_;
v___y_2194_ = v___y_2204_;
v___y_2195_ = v___x_2206_;
goto v___jp_2191_;
}
else
{
uint32_t v___x_2207_; 
v___x_2207_ = 2147483648;
v___y_2192_ = v___y_2203_;
v___y_2193_ = v___y_2205_;
v___y_2194_ = v___y_2204_;
v___y_2195_ = v___x_2207_;
goto v___jp_2191_;
}
}
v___jp_2208_:
{
uint64_t v___x_2214_; uint64_t v_encodedExponent_2215_; uint32_t v___x_2216_; uint64_t v___x_2217_; uint8_t v___x_2218_; 
v___x_2214_ = 171ULL;
v_encodedExponent_2215_ = lean_uint64_sub(v___y_2209_, v___x_2214_);
v___x_2216_ = lean_uint64_to_uint32(v_encodedExponent_2215_);
v___x_2217_ = 8388608ULL;
v___x_2218_ = lean_uint64_dec_lt(v___y_2213_, v___x_2217_);
if (v___x_2218_ == 0)
{
uint64_t v___x_2219_; uint32_t v___x_2220_; 
v___x_2219_ = lean_uint64_sub(v___y_2213_, v___x_2217_);
v___x_2220_ = lean_uint64_to_uint32(v___x_2219_);
v___y_2202_ = v___y_2212_;
v___y_2203_ = v___y_2211_;
v___y_2204_ = v___x_2216_;
v___y_2205_ = v___x_2220_;
goto v___jp_2201_;
}
else
{
uint32_t v___x_2221_; 
v___x_2221_ = lean_uint64_to_uint32(v___y_2210_);
v___y_2202_ = v___y_2212_;
v___y_2203_ = v___y_2211_;
v___y_2204_ = v___x_2216_;
v___y_2205_ = v___x_2221_;
goto v___jp_2201_;
}
}
v___jp_2222_:
{
uint64_t v___x_2229_; uint8_t v___x_2230_; 
v___x_2229_ = 425ULL;
v___x_2230_ = lean_uint64_dec_lt(v___x_2229_, v___y_2228_);
if (v___x_2230_ == 0)
{
if (v___y_2227_ == 0)
{
v___y_2209_ = v___y_2228_;
v___y_2210_ = v___y_2225_;
v___y_2211_ = v___y_2224_;
v___y_2212_ = v___y_2223_;
v___y_2213_ = v___y_2226_;
goto v___jp_2208_;
}
else
{
uint64_t v___x_2231_; 
v___x_2231_ = 8388608ULL;
v___y_2209_ = v___y_2228_;
v___y_2210_ = v___y_2225_;
v___y_2211_ = v___y_2224_;
v___y_2212_ = v___y_2223_;
v___y_2213_ = v___x_2231_;
goto v___jp_2208_;
}
}
else
{
if (v___y_2223_ == 0)
{
uint32_t v___x_2232_; 
v___x_2232_ = 2139095040;
return v___x_2232_;
}
else
{
uint32_t v___x_2233_; 
v___x_2233_ = 4286578688;
return v___x_2233_;
}
}
}
v___jp_2234_:
{
uint64_t v___x_2240_; uint8_t v_carry_2241_; 
v___x_2240_ = 16777216ULL;
v_carry_2241_ = lean_uint64_dec_eq(v___y_2239_, v___x_2240_);
if (v_carry_2241_ == 0)
{
v___y_2223_ = v___y_2238_;
v___y_2224_ = v___y_2237_;
v___y_2225_ = v___y_2236_;
v___y_2226_ = v___y_2239_;
v___y_2227_ = v_carry_2241_;
v___y_2228_ = v___y_2235_;
goto v___jp_2222_;
}
else
{
uint64_t v___x_2242_; uint64_t v___x_2243_; 
v___x_2242_ = 1ULL;
v___x_2243_ = lean_uint64_add(v___y_2235_, v___x_2242_);
v___y_2223_ = v___y_2238_;
v___y_2224_ = v___y_2237_;
v___y_2225_ = v___y_2236_;
v___y_2226_ = v___y_2239_;
v___y_2227_ = v_carry_2241_;
v___y_2228_ = v___x_2243_;
goto v___jp_2222_;
}
}
v___jp_2244_:
{
uint64_t v_position_2251_; uint64_t v___x_2252_; uint8_t v___x_2253_; 
v_position_2251_ = lean_uint64_add(v___y_2250_, v___y_2249_);
v___x_2252_ = 172ULL;
v___x_2253_ = lean_uint64_dec_lt(v_position_2251_, v___x_2252_);
if (v___x_2253_ == 0)
{
uint64_t v___x_2254_; uint8_t v___x_2255_; 
v___x_2254_ = 23ULL;
v___x_2255_ = lean_uint64_dec_lt(v___y_2250_, v___x_2254_);
if (v___x_2255_ == 0)
{
uint64_t v___x_2256_; uint8_t v___x_2257_; 
v___x_2256_ = lean_uint64_sub(v___y_2250_, v___x_2254_);
v___x_2257_ = lean_uint64_dec_eq(v___x_2256_, v___y_2248_);
if (v___x_2257_ == 0)
{
uint64_t v___x_2258_; uint8_t v___x_2259_; 
v___x_2258_ = 64ULL;
v___x_2259_ = lean_uint64_dec_lt(v___x_2256_, v___x_2258_);
if (v___x_2259_ == 0)
{
uint8_t v___x_2260_; 
v___x_2260_ = lean_uint64_dec_eq(v___x_2256_, v___x_2258_);
if (v___x_2260_ == 0)
{
v___y_2235_ = v_position_2251_;
v___y_2236_ = v___y_2248_;
v___y_2237_ = v___y_2247_;
v___y_2238_ = v___y_2246_;
v___y_2239_ = v___y_2248_;
goto v___jp_2234_;
}
else
{
uint64_t v___x_2261_; uint8_t v___x_2262_; 
v___x_2261_ = 9223372036854775808ULL;
v___x_2262_ = lean_uint64_dec_lt(v___x_2261_, v___y_2245_);
if (v___x_2262_ == 0)
{
v___y_2235_ = v_position_2251_;
v___y_2236_ = v___y_2248_;
v___y_2237_ = v___y_2247_;
v___y_2238_ = v___y_2246_;
v___y_2239_ = v___y_2248_;
goto v___jp_2234_;
}
else
{
uint64_t v___x_2263_; 
v___x_2263_ = 1ULL;
v___y_2235_ = v_position_2251_;
v___y_2236_ = v___y_2248_;
v___y_2237_ = v___y_2247_;
v___y_2238_ = v___y_2246_;
v___y_2239_ = v___x_2263_;
goto v___jp_2234_;
}
}
}
else
{
uint64_t v_quotient_2264_; uint64_t v___x_2265_; uint64_t v___x_2266_; uint64_t v___x_2267_; uint64_t v_remainder_2268_; uint64_t v___x_2269_; uint64_t v_half_2270_; uint8_t v___x_2271_; 
v_quotient_2264_ = lean_uint64_shift_right(v___y_2245_, v___x_2256_);
v___x_2265_ = 1ULL;
v___x_2266_ = lean_uint64_shift_left(v___x_2265_, v___x_2256_);
v___x_2267_ = lean_uint64_sub(v___x_2266_, v___x_2265_);
v_remainder_2268_ = lean_uint64_land(v___y_2245_, v___x_2267_);
v___x_2269_ = lean_uint64_sub(v___x_2256_, v___x_2265_);
v_half_2270_ = lean_uint64_shift_left(v___x_2265_, v___x_2269_);
v___x_2271_ = lean_uint64_dec_lt(v_remainder_2268_, v_half_2270_);
if (v___x_2271_ == 0)
{
uint8_t v___x_2272_; 
v___x_2272_ = lean_uint64_dec_lt(v_half_2270_, v_remainder_2268_);
if (v___x_2272_ == 0)
{
uint64_t v___x_2273_; uint8_t v___x_2274_; 
v___x_2273_ = lean_uint64_land(v_quotient_2264_, v___x_2265_);
v___x_2274_ = lean_uint64_dec_eq(v___x_2273_, v___y_2248_);
if (v___x_2274_ == 0)
{
uint64_t v___x_2275_; 
v___x_2275_ = lean_uint64_add(v_quotient_2264_, v___x_2265_);
v___y_2235_ = v_position_2251_;
v___y_2236_ = v___y_2248_;
v___y_2237_ = v___y_2247_;
v___y_2238_ = v___y_2246_;
v___y_2239_ = v___x_2275_;
goto v___jp_2234_;
}
else
{
v___y_2235_ = v_position_2251_;
v___y_2236_ = v___y_2248_;
v___y_2237_ = v___y_2247_;
v___y_2238_ = v___y_2246_;
v___y_2239_ = v_quotient_2264_;
goto v___jp_2234_;
}
}
else
{
uint64_t v___x_2276_; 
v___x_2276_ = lean_uint64_add(v_quotient_2264_, v___x_2265_);
v___y_2235_ = v_position_2251_;
v___y_2236_ = v___y_2248_;
v___y_2237_ = v___y_2247_;
v___y_2238_ = v___y_2246_;
v___y_2239_ = v___x_2276_;
goto v___jp_2234_;
}
}
else
{
v___y_2235_ = v_position_2251_;
v___y_2236_ = v___y_2248_;
v___y_2237_ = v___y_2247_;
v___y_2238_ = v___y_2246_;
v___y_2239_ = v_quotient_2264_;
goto v___jp_2234_;
}
}
}
else
{
v___y_2235_ = v_position_2251_;
v___y_2236_ = v___y_2248_;
v___y_2237_ = v___y_2247_;
v___y_2238_ = v___y_2246_;
v___y_2239_ = v___y_2245_;
goto v___jp_2234_;
}
}
else
{
uint64_t v___x_2277_; uint64_t v___x_2278_; 
v___x_2277_ = lean_uint64_sub(v___x_2254_, v___y_2250_);
v___x_2278_ = lean_uint64_shift_left(v___y_2245_, v___x_2277_);
v___y_2235_ = v_position_2251_;
v___y_2236_ = v___y_2248_;
v___y_2237_ = v___y_2247_;
v___y_2238_ = v___y_2246_;
v___y_2239_ = v___x_2278_;
goto v___jp_2234_;
}
}
else
{
uint64_t v___x_2279_; uint8_t v___x_2280_; 
v___x_2279_ = 149ULL;
v___x_2280_ = lean_uint64_dec_lt(v___y_2249_, v___x_2279_);
if (v___x_2280_ == 0)
{
uint64_t v___x_2281_; uint64_t v___x_2282_; 
v___x_2281_ = lean_uint64_sub(v___y_2249_, v___x_2279_);
v___x_2282_ = lean_uint64_shift_left(v___y_2245_, v___x_2281_);
v___y_2045_ = v___y_2246_;
v___y_2046_ = v___y_2247_;
v___y_2047_ = v___y_2248_;
v___y_2048_ = v___x_2282_;
goto v___jp_2044_;
}
else
{
uint64_t v___x_2283_; uint8_t v___x_2284_; 
v___x_2283_ = lean_uint64_sub(v___x_2279_, v___y_2249_);
v___x_2284_ = lean_uint64_dec_eq(v___x_2283_, v___y_2248_);
if (v___x_2284_ == 0)
{
uint64_t v___x_2285_; uint8_t v___x_2286_; 
v___x_2285_ = 64ULL;
v___x_2286_ = lean_uint64_dec_lt(v___x_2283_, v___x_2285_);
if (v___x_2286_ == 0)
{
uint8_t v___x_2287_; 
v___x_2287_ = lean_uint64_dec_eq(v___x_2283_, v___x_2285_);
if (v___x_2287_ == 0)
{
v___y_2045_ = v___y_2246_;
v___y_2046_ = v___y_2247_;
v___y_2047_ = v___y_2248_;
v___y_2048_ = v___y_2248_;
goto v___jp_2044_;
}
else
{
uint64_t v___x_2288_; uint8_t v___x_2289_; 
v___x_2288_ = 9223372036854775808ULL;
v___x_2289_ = lean_uint64_dec_lt(v___x_2288_, v___y_2245_);
if (v___x_2289_ == 0)
{
v___y_2045_ = v___y_2246_;
v___y_2046_ = v___y_2247_;
v___y_2047_ = v___y_2248_;
v___y_2048_ = v___y_2248_;
goto v___jp_2044_;
}
else
{
uint64_t v___x_2290_; 
v___x_2290_ = 1ULL;
v___y_2045_ = v___y_2246_;
v___y_2046_ = v___y_2247_;
v___y_2047_ = v___y_2248_;
v___y_2048_ = v___x_2290_;
goto v___jp_2044_;
}
}
}
else
{
uint64_t v_quotient_2291_; uint64_t v___x_2292_; uint64_t v___x_2293_; uint64_t v___x_2294_; uint64_t v_remainder_2295_; uint64_t v___x_2296_; uint64_t v_half_2297_; uint8_t v___x_2298_; 
v_quotient_2291_ = lean_uint64_shift_right(v___y_2245_, v___x_2283_);
v___x_2292_ = 1ULL;
v___x_2293_ = lean_uint64_shift_left(v___x_2292_, v___x_2283_);
v___x_2294_ = lean_uint64_sub(v___x_2293_, v___x_2292_);
v_remainder_2295_ = lean_uint64_land(v___y_2245_, v___x_2294_);
v___x_2296_ = lean_uint64_sub(v___x_2283_, v___x_2292_);
v_half_2297_ = lean_uint64_shift_left(v___x_2292_, v___x_2296_);
v___x_2298_ = lean_uint64_dec_lt(v_remainder_2295_, v_half_2297_);
if (v___x_2298_ == 0)
{
uint8_t v___x_2299_; 
v___x_2299_ = lean_uint64_dec_lt(v_half_2297_, v_remainder_2295_);
if (v___x_2299_ == 0)
{
uint64_t v___x_2300_; uint8_t v___x_2301_; 
v___x_2300_ = lean_uint64_land(v_quotient_2291_, v___x_2292_);
v___x_2301_ = lean_uint64_dec_eq(v___x_2300_, v___y_2248_);
if (v___x_2301_ == 0)
{
uint64_t v___x_2302_; 
v___x_2302_ = lean_uint64_add(v_quotient_2291_, v___x_2292_);
v___y_2045_ = v___y_2246_;
v___y_2046_ = v___y_2247_;
v___y_2047_ = v___y_2248_;
v___y_2048_ = v___x_2302_;
goto v___jp_2044_;
}
else
{
v___y_2045_ = v___y_2246_;
v___y_2046_ = v___y_2247_;
v___y_2047_ = v___y_2248_;
v___y_2048_ = v_quotient_2291_;
goto v___jp_2044_;
}
}
else
{
uint64_t v___x_2303_; 
v___x_2303_ = lean_uint64_add(v_quotient_2291_, v___x_2292_);
v___y_2045_ = v___y_2246_;
v___y_2046_ = v___y_2247_;
v___y_2047_ = v___y_2248_;
v___y_2048_ = v___x_2303_;
goto v___jp_2044_;
}
}
else
{
v___y_2045_ = v___y_2246_;
v___y_2046_ = v___y_2247_;
v___y_2047_ = v___y_2248_;
v___y_2048_ = v_quotient_2291_;
goto v___jp_2044_;
}
}
}
else
{
v___y_2045_ = v___y_2246_;
v___y_2046_ = v___y_2247_;
v___y_2047_ = v___y_2248_;
v___y_2048_ = v___y_2245_;
goto v___jp_2044_;
}
}
}
}
v___jp_2304_:
{
uint64_t v___x_2312_; uint64_t v___x_2313_; uint8_t v___x_2314_; 
v___x_2312_ = 1ULL;
v___x_2313_ = lean_uint64_shift_right(v___y_2310_, v___x_2312_);
v___x_2314_ = lean_uint64_dec_eq(v___x_2313_, v___y_2308_);
if (v___x_2314_ == 0)
{
uint64_t v___x_2315_; 
v___x_2315_ = lean_uint64_add(v___y_2311_, v___x_2312_);
v___y_2245_ = v___y_2305_;
v___y_2246_ = v___y_2307_;
v___y_2247_ = v___y_2306_;
v___y_2248_ = v___y_2308_;
v___y_2249_ = v___y_2309_;
v___y_2250_ = v___x_2315_;
goto v___jp_2244_;
}
else
{
v___y_2245_ = v___y_2305_;
v___y_2246_ = v___y_2307_;
v___y_2247_ = v___y_2306_;
v___y_2248_ = v___y_2308_;
v___y_2249_ = v___y_2309_;
v___y_2250_ = v___y_2311_;
goto v___jp_2244_;
}
}
v___jp_2316_:
{
uint64_t v___x_2326_; uint8_t v___x_2327_; 
v___x_2326_ = lean_uint64_shift_right(v___y_2319_, v___y_2323_);
v___x_2327_ = lean_uint64_dec_eq(v___x_2326_, v___y_2320_);
if (v___x_2327_ == 0)
{
uint64_t v___x_2328_; 
v___x_2328_ = lean_uint64_add(v___y_2317_, v___y_2323_);
v___y_2305_ = v___y_2318_;
v___y_2306_ = v___y_2322_;
v___y_2307_ = v___y_2321_;
v___y_2308_ = v___y_2320_;
v___y_2309_ = v___y_2324_;
v___y_2310_ = v___y_2325_;
v___y_2311_ = v___x_2328_;
goto v___jp_2304_;
}
else
{
v___y_2305_ = v___y_2318_;
v___y_2306_ = v___y_2322_;
v___y_2307_ = v___y_2321_;
v___y_2308_ = v___y_2320_;
v___y_2309_ = v___y_2324_;
v___y_2310_ = v___y_2325_;
v___y_2311_ = v___y_2317_;
goto v___jp_2304_;
}
}
v___jp_2329_:
{
uint64_t v___x_2337_; uint64_t v___x_2338_; uint8_t v___x_2339_; 
v___x_2337_ = 2ULL;
v___x_2338_ = lean_uint64_shift_right(v___y_2334_, v___x_2337_);
v___x_2339_ = lean_uint64_dec_eq(v___x_2338_, v___y_2333_);
if (v___x_2339_ == 0)
{
v___y_2317_ = v___y_2336_;
v___y_2318_ = v___y_2330_;
v___y_2319_ = v___y_2334_;
v___y_2320_ = v___y_2333_;
v___y_2321_ = v___y_2332_;
v___y_2322_ = v___y_2331_;
v___y_2323_ = v___x_2337_;
v___y_2324_ = v___y_2335_;
v___y_2325_ = v___x_2338_;
goto v___jp_2316_;
}
else
{
v___y_2317_ = v___y_2336_;
v___y_2318_ = v___y_2330_;
v___y_2319_ = v___y_2334_;
v___y_2320_ = v___y_2333_;
v___y_2321_ = v___y_2332_;
v___y_2322_ = v___y_2331_;
v___y_2323_ = v___x_2337_;
v___y_2324_ = v___y_2335_;
v___y_2325_ = v___y_2334_;
goto v___jp_2316_;
}
}
v___jp_2340_:
{
uint64_t v___x_2350_; uint8_t v___x_2351_; 
v___x_2350_ = lean_uint64_shift_right(v___y_2341_, v___y_2348_);
v___x_2351_ = lean_uint64_dec_eq(v___x_2350_, v___y_2343_);
if (v___x_2351_ == 0)
{
uint64_t v___x_2352_; 
v___x_2352_ = lean_uint64_add(v___y_2346_, v___y_2348_);
v___y_2330_ = v___y_2342_;
v___y_2331_ = v___y_2345_;
v___y_2332_ = v___y_2344_;
v___y_2333_ = v___y_2343_;
v___y_2334_ = v___y_2349_;
v___y_2335_ = v___y_2347_;
v___y_2336_ = v___x_2352_;
goto v___jp_2329_;
}
else
{
v___y_2330_ = v___y_2342_;
v___y_2331_ = v___y_2345_;
v___y_2332_ = v___y_2344_;
v___y_2333_ = v___y_2343_;
v___y_2334_ = v___y_2349_;
v___y_2335_ = v___y_2347_;
v___y_2336_ = v___y_2346_;
goto v___jp_2329_;
}
}
v___jp_2353_:
{
uint64_t v___x_2361_; uint64_t v___x_2362_; uint8_t v___x_2363_; 
v___x_2361_ = 4ULL;
v___x_2362_ = lean_uint64_shift_right(v___y_2355_, v___x_2361_);
v___x_2363_ = lean_uint64_dec_eq(v___x_2362_, v___y_2358_);
if (v___x_2363_ == 0)
{
v___y_2341_ = v___y_2355_;
v___y_2342_ = v___y_2354_;
v___y_2343_ = v___y_2358_;
v___y_2344_ = v___y_2357_;
v___y_2345_ = v___y_2356_;
v___y_2346_ = v___y_2360_;
v___y_2347_ = v___y_2359_;
v___y_2348_ = v___x_2361_;
v___y_2349_ = v___x_2362_;
goto v___jp_2340_;
}
else
{
v___y_2341_ = v___y_2355_;
v___y_2342_ = v___y_2354_;
v___y_2343_ = v___y_2358_;
v___y_2344_ = v___y_2357_;
v___y_2345_ = v___y_2356_;
v___y_2346_ = v___y_2360_;
v___y_2347_ = v___y_2359_;
v___y_2348_ = v___x_2361_;
v___y_2349_ = v___y_2355_;
goto v___jp_2340_;
}
}
v___jp_2364_:
{
uint64_t v___x_2374_; uint8_t v___x_2375_; 
v___x_2374_ = lean_uint64_shift_right(v___y_2366_, v___y_2367_);
v___x_2375_ = lean_uint64_dec_eq(v___x_2374_, v___y_2368_);
if (v___x_2375_ == 0)
{
uint64_t v___x_2376_; 
v___x_2376_ = lean_uint64_add(v___y_2371_, v___y_2367_);
v___y_2354_ = v___y_2365_;
v___y_2355_ = v___y_2373_;
v___y_2356_ = v___y_2370_;
v___y_2357_ = v___y_2369_;
v___y_2358_ = v___y_2368_;
v___y_2359_ = v___y_2372_;
v___y_2360_ = v___x_2376_;
goto v___jp_2353_;
}
else
{
v___y_2354_ = v___y_2365_;
v___y_2355_ = v___y_2373_;
v___y_2356_ = v___y_2370_;
v___y_2357_ = v___y_2369_;
v___y_2358_ = v___y_2368_;
v___y_2359_ = v___y_2372_;
v___y_2360_ = v___y_2371_;
goto v___jp_2353_;
}
}
v___jp_2377_:
{
uint64_t v___x_2385_; uint64_t v___x_2386_; uint8_t v___x_2387_; 
v___x_2385_ = 8ULL;
v___x_2386_ = lean_uint64_shift_right(v___y_2379_, v___x_2385_);
v___x_2387_ = lean_uint64_dec_eq(v___x_2386_, v___y_2382_);
if (v___x_2387_ == 0)
{
v___y_2365_ = v___y_2378_;
v___y_2366_ = v___y_2379_;
v___y_2367_ = v___x_2385_;
v___y_2368_ = v___y_2382_;
v___y_2369_ = v___y_2381_;
v___y_2370_ = v___y_2380_;
v___y_2371_ = v___y_2384_;
v___y_2372_ = v___y_2383_;
v___y_2373_ = v___x_2386_;
goto v___jp_2364_;
}
else
{
v___y_2365_ = v___y_2378_;
v___y_2366_ = v___y_2379_;
v___y_2367_ = v___x_2385_;
v___y_2368_ = v___y_2382_;
v___y_2369_ = v___y_2381_;
v___y_2370_ = v___y_2380_;
v___y_2371_ = v___y_2384_;
v___y_2372_ = v___y_2383_;
v___y_2373_ = v___y_2379_;
goto v___jp_2364_;
}
}
v___jp_2388_:
{
uint64_t v___x_2398_; uint8_t v___x_2399_; 
v___x_2398_ = lean_uint64_shift_right(v___y_2395_, v___y_2394_);
v___x_2399_ = lean_uint64_dec_eq(v___x_2398_, v___y_2391_);
if (v___x_2399_ == 0)
{
uint64_t v___x_2400_; 
v___x_2400_ = lean_uint64_add(v___y_2389_, v___y_2394_);
v___y_2378_ = v___y_2390_;
v___y_2379_ = v___y_2397_;
v___y_2380_ = v___y_2393_;
v___y_2381_ = v___y_2392_;
v___y_2382_ = v___y_2391_;
v___y_2383_ = v___y_2396_;
v___y_2384_ = v___x_2400_;
goto v___jp_2377_;
}
else
{
v___y_2378_ = v___y_2390_;
v___y_2379_ = v___y_2397_;
v___y_2380_ = v___y_2393_;
v___y_2381_ = v___y_2392_;
v___y_2382_ = v___y_2391_;
v___y_2383_ = v___y_2396_;
v___y_2384_ = v___y_2389_;
goto v___jp_2377_;
}
}
v___jp_2401_:
{
uint64_t v___x_2409_; uint64_t v___x_2410_; uint8_t v___x_2411_; 
v___x_2409_ = 16ULL;
v___x_2410_ = lean_uint64_shift_right(v___y_2406_, v___x_2409_);
v___x_2411_ = lean_uint64_dec_eq(v___x_2410_, v___y_2405_);
if (v___x_2411_ == 0)
{
v___y_2389_ = v___y_2408_;
v___y_2390_ = v___y_2402_;
v___y_2391_ = v___y_2405_;
v___y_2392_ = v___y_2404_;
v___y_2393_ = v___y_2403_;
v___y_2394_ = v___x_2409_;
v___y_2395_ = v___y_2406_;
v___y_2396_ = v___y_2407_;
v___y_2397_ = v___x_2410_;
goto v___jp_2388_;
}
else
{
v___y_2389_ = v___y_2408_;
v___y_2390_ = v___y_2402_;
v___y_2391_ = v___y_2405_;
v___y_2392_ = v___y_2404_;
v___y_2393_ = v___y_2403_;
v___y_2394_ = v___x_2409_;
v___y_2395_ = v___y_2406_;
v___y_2396_ = v___y_2407_;
v___y_2397_ = v___y_2406_;
goto v___jp_2388_;
}
}
v___jp_2412_:
{
uint64_t v___x_2420_; uint8_t v___x_2421_; 
v___x_2420_ = lean_uint64_shift_right(v___y_2413_, v___y_2414_);
v___x_2421_ = lean_uint64_dec_eq(v___x_2420_, v___y_2415_);
if (v___x_2421_ == 0)
{
v___y_2402_ = v___y_2413_;
v___y_2403_ = v___y_2417_;
v___y_2404_ = v___y_2416_;
v___y_2405_ = v___y_2415_;
v___y_2406_ = v___y_2419_;
v___y_2407_ = v___y_2418_;
v___y_2408_ = v___y_2414_;
goto v___jp_2401_;
}
else
{
v___y_2402_ = v___y_2413_;
v___y_2403_ = v___y_2417_;
v___y_2404_ = v___y_2416_;
v___y_2405_ = v___y_2415_;
v___y_2406_ = v___y_2419_;
v___y_2407_ = v___y_2418_;
v___y_2408_ = v___y_2415_;
goto v___jp_2401_;
}
}
v___jp_2422_:
{
uint64_t v___x_2427_; uint8_t v___x_2428_; 
v___x_2427_ = 0ULL;
v___x_2428_ = lean_uint64_dec_eq(v___y_2423_, v___x_2427_);
if (v___x_2428_ == 0)
{
uint64_t v___x_2429_; uint64_t v___x_2430_; uint8_t v___x_2431_; 
v___x_2429_ = 32ULL;
v___x_2430_ = lean_uint64_shift_right(v___y_2423_, v___x_2429_);
v___x_2431_ = lean_uint64_dec_eq(v___x_2430_, v___x_2427_);
if (v___x_2431_ == 0)
{
v___y_2413_ = v___y_2423_;
v___y_2414_ = v___x_2429_;
v___y_2415_ = v___x_2427_;
v___y_2416_ = v___y_2425_;
v___y_2417_ = v___y_2424_;
v___y_2418_ = v___y_2426_;
v___y_2419_ = v___x_2430_;
goto v___jp_2412_;
}
else
{
v___y_2413_ = v___y_2423_;
v___y_2414_ = v___x_2429_;
v___y_2415_ = v___x_2427_;
v___y_2416_ = v___y_2425_;
v___y_2417_ = v___y_2424_;
v___y_2418_ = v___y_2426_;
v___y_2419_ = v___y_2423_;
goto v___jp_2412_;
}
}
else
{
if (v___y_2425_ == 0)
{
uint32_t v___x_2432_; 
v___x_2432_ = 0;
return v___x_2432_;
}
else
{
uint32_t v___x_2433_; 
v___x_2433_ = 2147483648;
return v___x_2433_;
}
}
}
v___jp_2434_:
{
uint64_t v___x_2441_; uint64_t v___x_2442_; uint64_t v___x_2443_; uint8_t v___x_2444_; 
v___x_2441_ = lean_uint64_mul(v___y_2439_, v___y_2435_);
v___x_2442_ = lean_uint64_add(v___y_2436_, v___y_2440_);
v___x_2443_ = 281474976710656ULL;
v___x_2444_ = lean_uint64_dec_lt(v___x_2441_, v___x_2443_);
if (v___x_2444_ == 0)
{
v___y_2423_ = v___x_2441_;
v___y_2424_ = v___y_2438_;
v___y_2425_ = v___y_2437_;
v___y_2426_ = v___x_2442_;
goto v___jp_2422_;
}
else
{
uint64_t v___x_2445_; uint8_t v___x_2446_; 
v___x_2445_ = 123ULL;
v___x_2446_ = lean_uint64_dec_le(v___x_2442_, v___x_2445_);
if (v___x_2446_ == 0)
{
v___y_2423_ = v___x_2441_;
v___y_2424_ = v___y_2438_;
v___y_2425_ = v___y_2437_;
v___y_2426_ = v___x_2442_;
goto v___jp_2422_;
}
else
{
uint64_t v___x_2447_; uint8_t v___x_2448_; 
v___x_2447_ = 0ULL;
v___x_2448_ = lean_uint64_dec_eq(v___x_2441_, v___x_2447_);
if (v___x_2448_ == 0)
{
uint64_t v___x_2449_; uint64_t v___x_2450_; uint8_t v___x_2451_; 
v___x_2449_ = 149ULL;
v___x_2450_ = lean_uint64_sub(v___x_2449_, v___x_2442_);
v___x_2451_ = lean_uint64_dec_eq(v___x_2450_, v___x_2447_);
if (v___x_2451_ == 0)
{
uint64_t v___x_2452_; uint8_t v___x_2453_; 
v___x_2452_ = 64ULL;
v___x_2453_ = lean_uint64_dec_lt(v___x_2450_, v___x_2452_);
if (v___x_2453_ == 0)
{
uint8_t v___x_2454_; 
v___x_2454_ = lean_uint64_dec_eq(v___x_2450_, v___x_2452_);
if (v___x_2454_ == 0)
{
v___y_2066_ = v___y_2437_;
v___y_2067_ = v___y_2438_;
v___y_2068_ = v___x_2447_;
v___y_2069_ = v___x_2447_;
goto v___jp_2065_;
}
else
{
uint64_t v___x_2455_; uint8_t v___x_2456_; 
v___x_2455_ = 9223372036854775808ULL;
v___x_2456_ = lean_uint64_dec_lt(v___x_2455_, v___x_2441_);
if (v___x_2456_ == 0)
{
v___y_2066_ = v___y_2437_;
v___y_2067_ = v___y_2438_;
v___y_2068_ = v___x_2447_;
v___y_2069_ = v___x_2447_;
goto v___jp_2065_;
}
else
{
uint64_t v___x_2457_; 
v___x_2457_ = 1ULL;
v___y_2066_ = v___y_2437_;
v___y_2067_ = v___y_2438_;
v___y_2068_ = v___x_2447_;
v___y_2069_ = v___x_2457_;
goto v___jp_2065_;
}
}
}
else
{
uint64_t v_quotient_2458_; uint64_t v___x_2459_; uint64_t v___x_2460_; uint64_t v___x_2461_; uint64_t v_remainder_2462_; uint64_t v___x_2463_; uint64_t v_half_2464_; uint8_t v___x_2465_; 
v_quotient_2458_ = lean_uint64_shift_right(v___x_2441_, v___x_2450_);
v___x_2459_ = 1ULL;
v___x_2460_ = lean_uint64_shift_left(v___x_2459_, v___x_2450_);
v___x_2461_ = lean_uint64_sub(v___x_2460_, v___x_2459_);
v_remainder_2462_ = lean_uint64_land(v___x_2441_, v___x_2461_);
v___x_2463_ = lean_uint64_sub(v___x_2450_, v___x_2459_);
v_half_2464_ = lean_uint64_shift_left(v___x_2459_, v___x_2463_);
v___x_2465_ = lean_uint64_dec_lt(v_remainder_2462_, v_half_2464_);
if (v___x_2465_ == 0)
{
uint8_t v___x_2466_; 
v___x_2466_ = lean_uint64_dec_lt(v_half_2464_, v_remainder_2462_);
if (v___x_2466_ == 0)
{
uint64_t v___x_2467_; uint8_t v___x_2468_; 
v___x_2467_ = lean_uint64_land(v_quotient_2458_, v___x_2459_);
v___x_2468_ = lean_uint64_dec_eq(v___x_2467_, v___x_2447_);
if (v___x_2468_ == 0)
{
uint64_t v___x_2469_; 
v___x_2469_ = lean_uint64_add(v_quotient_2458_, v___x_2459_);
v___y_2066_ = v___y_2437_;
v___y_2067_ = v___y_2438_;
v___y_2068_ = v___x_2447_;
v___y_2069_ = v___x_2469_;
goto v___jp_2065_;
}
else
{
v___y_2066_ = v___y_2437_;
v___y_2067_ = v___y_2438_;
v___y_2068_ = v___x_2447_;
v___y_2069_ = v_quotient_2458_;
goto v___jp_2065_;
}
}
else
{
uint64_t v___x_2470_; 
v___x_2470_ = lean_uint64_add(v_quotient_2458_, v___x_2459_);
v___y_2066_ = v___y_2437_;
v___y_2067_ = v___y_2438_;
v___y_2068_ = v___x_2447_;
v___y_2069_ = v___x_2470_;
goto v___jp_2065_;
}
}
else
{
v___y_2066_ = v___y_2437_;
v___y_2067_ = v___y_2438_;
v___y_2068_ = v___x_2447_;
v___y_2069_ = v_quotient_2458_;
goto v___jp_2065_;
}
}
}
else
{
v___y_2066_ = v___y_2437_;
v___y_2067_ = v___y_2438_;
v___y_2068_ = v___x_2447_;
v___y_2069_ = v___x_2441_;
goto v___jp_2065_;
}
}
else
{
if (v___y_2437_ == 0)
{
uint32_t v___x_2471_; 
v___x_2471_ = 0;
return v___x_2471_;
}
else
{
uint32_t v___x_2472_; 
v___x_2472_ = 2147483648;
return v___x_2472_;
}
}
}
}
}
v___jp_2476_:
{
uint64_t v___x_2482_; uint64_t v___x_2483_; uint8_t v___x_2484_; 
v___x_2482_ = lean_uint32_to_uint64(v_ey_2475_);
v___x_2483_ = 0ULL;
v___x_2484_ = lean_uint64_dec_eq(v___x_2482_, v___x_2483_);
if (v___x_2484_ == 0)
{
uint64_t v___x_2485_; uint64_t v___x_2486_; 
v___x_2485_ = 1ULL;
v___x_2486_ = lean_uint64_sub(v___x_2482_, v___x_2485_);
v___y_2435_ = v___y_2477_;
v___y_2436_ = v___y_2481_;
v___y_2437_ = v___y_2480_;
v___y_2438_ = v___y_2479_;
v___y_2439_ = v___y_2478_;
v___y_2440_ = v___x_2486_;
goto v___jp_2434_;
}
else
{
v___y_2435_ = v___y_2477_;
v___y_2436_ = v___y_2481_;
v___y_2437_ = v___y_2480_;
v___y_2438_ = v___y_2479_;
v___y_2439_ = v___y_2478_;
v___y_2440_ = v___x_2483_;
goto v___jp_2434_;
}
}
v___jp_2487_:
{
uint64_t v___x_2492_; uint64_t v___x_2493_; uint8_t v___x_2494_; 
v___x_2492_ = lean_uint32_to_uint64(v_ex_2473_);
v___x_2493_ = 0ULL;
v___x_2494_ = lean_uint64_dec_eq(v___x_2492_, v___x_2493_);
if (v___x_2494_ == 0)
{
uint64_t v___x_2495_; uint64_t v___x_2496_; 
v___x_2495_ = 1ULL;
v___x_2496_ = lean_uint64_sub(v___x_2492_, v___x_2495_);
v___y_2477_ = v___y_2491_;
v___y_2478_ = v___y_2490_;
v___y_2479_ = v___y_2489_;
v___y_2480_ = v___y_2488_;
v___y_2481_ = v___x_2496_;
goto v___jp_2476_;
}
else
{
v___y_2477_ = v___y_2491_;
v___y_2478_ = v___y_2490_;
v___y_2479_ = v___y_2489_;
v___y_2480_ = v___y_2488_;
v___y_2481_ = v___x_2493_;
goto v___jp_2476_;
}
}
v___jp_2497_:
{
uint32_t v___x_2502_; uint8_t v___x_2503_; 
v___x_2502_ = 0;
v___x_2503_ = lean_uint32_dec_eq(v_ey_2475_, v___x_2502_);
if (v___x_2503_ == 0)
{
uint64_t v___x_2504_; uint64_t v___x_2505_; uint64_t v___x_2506_; 
v___x_2504_ = lean_uint32_to_uint64(v___y_2498_);
v___x_2505_ = 8388608ULL;
v___x_2506_ = lean_uint64_lor(v___x_2504_, v___x_2505_);
v___y_2488_ = v___y_2500_;
v___y_2489_ = v___y_2499_;
v___y_2490_ = v___y_2501_;
v___y_2491_ = v___x_2506_;
goto v___jp_2487_;
}
else
{
uint64_t v___x_2507_; 
v___x_2507_ = lean_uint32_to_uint64(v___y_2498_);
v___y_2488_ = v___y_2500_;
v___y_2489_ = v___y_2499_;
v___y_2490_ = v___y_2501_;
v___y_2491_ = v___x_2507_;
goto v___jp_2487_;
}
}
v___jp_2508_:
{
uint32_t v___x_2510_; uint32_t v_xFraction_2511_; uint32_t v_yFraction_2512_; uint32_t v___x_2513_; uint8_t v___x_2514_; 
v___x_2510_ = 8388607;
v_xFraction_2511_ = lean_uint32_land(v___y_2028_, v___x_2510_);
v_yFraction_2512_ = lean_uint32_land(v___y_2029_, v___x_2510_);
v___x_2513_ = 0;
v___x_2514_ = lean_uint32_dec_eq(v_ex_2473_, v___x_2513_);
if (v___x_2514_ == 0)
{
uint64_t v___x_2515_; uint64_t v___x_2516_; uint64_t v___x_2517_; 
v___x_2515_ = lean_uint32_to_uint64(v_xFraction_2511_);
v___x_2516_ = 8388608ULL;
v___x_2517_ = lean_uint64_lor(v___x_2515_, v___x_2516_);
v___y_2498_ = v_yFraction_2512_;
v___y_2499_ = v___x_2510_;
v___y_2500_ = v___y_2509_;
v___y_2501_ = v___x_2517_;
goto v___jp_2497_;
}
else
{
uint64_t v___x_2518_; 
v___x_2518_ = lean_uint32_to_uint64(v_xFraction_2511_);
v___y_2498_ = v_yFraction_2512_;
v___y_2499_ = v___x_2510_;
v___y_2500_ = v___y_2509_;
v___y_2501_ = v___x_2518_;
goto v___jp_2497_;
}
}
v___jp_2522_:
{
if (v___y_2524_ == 0)
{
v___y_2509_ = v___x_2521_;
goto v___jp_2508_;
}
else
{
v___y_2509_ = v___y_2523_;
goto v___jp_2508_;
}
}
v___jp_2525_:
{
if (v___y_2527_ == 0)
{
if (v___y_2528_ == 0)
{
v___y_2523_ = v___y_2526_;
v___y_2524_ = v___x_2521_;
goto v___jp_2522_;
}
else
{
v___y_2509_ = v___x_2521_;
goto v___jp_2508_;
}
}
else
{
v___y_2523_ = v___y_2526_;
v___y_2524_ = v___y_2528_;
goto v___jp_2522_;
}
}
v___jp_2529_:
{
uint32_t v___x_2532_; uint32_t v___x_2533_; uint32_t v___x_2534_; uint8_t v___x_2535_; 
v___x_2532_ = 2147483648;
v___x_2533_ = lean_uint32_land(v___y_2029_, v___x_2532_);
v___x_2534_ = 0;
v___x_2535_ = lean_uint32_dec_eq(v___x_2533_, v___x_2534_);
if (v___x_2535_ == 0)
{
v___y_2526_ = v___y_2530_;
v___y_2527_ = v___y_2531_;
v___y_2528_ = v___x_2521_;
goto v___jp_2525_;
}
else
{
v___y_2526_ = v___y_2530_;
v___y_2527_ = v___y_2531_;
v___y_2528_ = v___y_2530_;
goto v___jp_2525_;
}
}
v___jp_2536_:
{
if (v___y_2537_ == 0)
{
uint32_t v___x_2538_; uint32_t v___x_2539_; uint32_t v___x_2540_; uint8_t v___x_2541_; 
v___x_2538_ = 2147483648;
v___x_2539_ = lean_uint32_land(v___y_2028_, v___x_2538_);
v___x_2540_ = 0;
v___x_2541_ = lean_uint32_dec_eq(v___x_2539_, v___x_2540_);
if (v___x_2541_ == 0)
{
v___y_2530_ = v___y_2537_;
v___y_2531_ = v___x_2521_;
goto v___jp_2529_;
}
else
{
v___y_2530_ = v___y_2537_;
v___y_2531_ = v___y_2537_;
goto v___jp_2529_;
}
}
else
{
lean_object* v___x_2542_; lean_object* v___x_2543_; lean_object* v___x_2544_; uint32_t v___x_2545_; 
v___x_2542_ = lean_uint32_to_nat(v___y_2028_);
v___x_2543_ = lean_uint32_to_nat(v___y_2029_);
v___x_2544_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_2542_, v___x_2543_);
v___x_2545_ = lean_uint32_of_nat(v___x_2544_);
lean_dec(v___x_2544_);
return v___x_2545_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_runF64Cast___lam__1___boxed(lean_object* v___y_2560_, lean_object* v___y_2561_){
_start:
{
uint32_t v___y_1770__boxed_2562_; uint32_t v___y_1771__boxed_2563_; uint32_t v_res_2564_; lean_object* v_r_2565_; 
v___y_1770__boxed_2562_ = lean_unbox_uint32(v___y_2560_);
lean_dec(v___y_2560_);
v___y_1771__boxed_2563_ = lean_unbox_uint32(v___y_2561_);
lean_dec(v___y_2561_);
v_res_2564_ = lp_competition_runF64Cast___lam__1(v___y_1770__boxed_2562_, v___y_1771__boxed_2563_);
v_r_2565_ = lean_box_uint32(v_res_2564_);
return v_r_2565_;
}
}
LEAN_EXPORT lean_object* lp_competition_runF64Cast(){
_start:
{
lean_object* v___f_2569_; lean_object* v___f_2570_; lean_object* v___x_2571_; lean_object* v___x_2572_; lean_object* v___x_2573_; 
v___f_2569_ = ((lean_object*)(lp_competition_runF64Cast___closed__0));
v___f_2570_ = ((lean_object*)(lp_competition_runF64Cast___closed__1));
v___x_2571_ = ((lean_object*)(lp_competition_runControl___closed__2));
v___x_2572_ = ((lean_object*)(lp_competition_runControl___closed__3));
v___x_2573_ = lp_competition_Bench_Suite_run(v___f_2569_, v___f_2570_, v___x_2571_, v___x_2572_);
return v___x_2573_;
}
}
LEAN_EXPORT lean_object* lp_competition_runF64Cast___boxed(lean_object* v_a_2574_){
_start:
{
lean_object* v_res_2575_; 
v_res_2575_ = lp_competition_runF64Cast();
return v_res_2575_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_2593_; lean_object* v___x_2594_; lean_object* v___x_2595_; uint8_t v___x_2596_; 
v___x_2593_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_2594_ = lean_io_getenv(v___x_2593_);
v___x_2595_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_2596_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_2594_, v___x_2595_);
if (v___x_2596_ == 0)
{
lean_object* v___x_2597_; uint8_t v___x_2598_; 
v___x_2597_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_2598_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_2594_, v___x_2597_);
if (v___x_2598_ == 0)
{
lean_object* v___x_2599_; uint8_t v___x_2600_; 
v___x_2599_ = ((lean_object*)(lp_competition_main___closed__6));
v___x_2600_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_2594_, v___x_2599_);
if (v___x_2600_ == 0)
{
lean_object* v___x_2601_; uint8_t v___x_2602_; 
v___x_2601_ = ((lean_object*)(lp_competition_main___closed__8));
v___x_2602_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_2594_, v___x_2601_);
lean_dec(v___x_2594_);
if (v___x_2602_ == 0)
{
lean_object* v___x_2603_; lean_object* v___x_2604_; 
v___x_2603_ = ((lean_object*)(lp_competition_main___closed__10));
v___x_2604_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_2604_, 0, v___x_2603_);
return v___x_2604_;
}
else
{
lean_object* v___x_2605_; 
v___x_2605_ = lp_competition_runF64Cast();
return v___x_2605_;
}
}
else
{
lean_object* v___x_2606_; 
lean_dec(v___x_2594_);
v___x_2606_ = lp_competition_runF64Boxed();
return v___x_2606_;
}
}
else
{
lean_object* v___x_2607_; 
lean_dec(v___x_2594_);
v___x_2607_ = lp_competition_runF64Native();
return v___x_2607_;
}
}
else
{
lean_object* v___x_2608_; 
lean_dec(v___x_2594_);
v___x_2608_ = lp_competition_runControl();
return v___x_2608_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_2609_){
_start:
{
lean_object* v_res_2610_; 
v_res_2610_ = _lean_main();
return v_res_2610_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_competition_BenchFull(uint8_t builtin);
lean_object* initialize_competition_BenchSuite(uint8_t builtin);
lean_object* initialize_competition_Submission(uint8_t builtin);
void lean_initialize();
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_competition_R24ScalarF64CostMain(uint8_t builtin) {
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
lp_competition_runF64Boxed___lam__0___boxed__const__1 = _init_lp_competition_runF64Boxed___lam__0___boxed__const__1();
lean_mark_persistent(lp_competition_runF64Boxed___lam__0___boxed__const__1);
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
  res = initialize_competition_R24ScalarF64CostMain(1 /* builtin */);
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
