LEAN_EXPORT lean_object* lp_competition_Submission_R22StreamingQuad_loop(lean_object* v_p_17201_, lean_object* v_n_17202_, lean_object* v_baseA_17203_, lean_object* v_baseB_17204_, lean_object* v_A_17205_, lean_object* v_B_17206_, lean_object* v_k_17207_, lean_object* v_s_17208_){
_start:
{
uint8_t v___x_17209_; 
v___x_17209_ = lean_nat_dec_lt(v_k_17207_, v_n_17202_);
if (v___x_17209_ == 0)
{
lean_dec(v_k_17207_);
return v_s_17208_;
}
else
{
lean_object* v___x_17210_; lean_object* v___x_17211_; float v___y_17213_; float v___y_17214_; float v___y_17215_; uint32_t v___y_17216_; lean_object* v___x_17224_; uint32_t v___x_17225_; float v___y_17227_; float v___y_17228_; uint32_t v___y_17229_; float v___y_17240_; uint32_t v___y_17241_; uint32_t v___y_17252_; lean_object* v___x_17260_; uint8_t v___x_17261_; 
v___x_17210_ = lean_unsigned_to_nat(1u);
v___x_17211_ = lean_nat_add(v_k_17207_, v___x_17210_);
v___x_17224_ = lean_nat_add(v_baseA_17203_, v_k_17207_);
v___x_17225_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___x_17260_ = lean_array_get_size(v_A_17205_);
v___x_17261_ = lean_nat_dec_lt(v___x_17224_, v___x_17260_);
if (v___x_17261_ == 0)
{
lean_dec(v___x_17224_);
v___y_17252_ = v___x_17225_;
goto v___jp_17251_;
}
else
{
lean_object* v___x_17262_; uint32_t v___x_17263_; 
v___x_17262_ = lean_array_fget_borrowed(v_A_17205_, v___x_17224_);
lean_dec(v___x_17224_);
v___x_17263_ = lean_unbox_uint32(v___x_17262_);
v___y_17252_ = v___x_17263_;
goto v___jp_17251_;
}
v___jp_17212_:
{
float v_a3_17217_; lean_object* v___x_17218_; lean_object* v_rowB_17219_; size_t v_sz_17220_; size_t v___x_17221_; lean_object* v___x_17222_; 
v_a3_17217_ = lean_float32_of_bits(v___y_17216_);
v___x_17218_ = lean_nat_mul(v_k_17207_, v_p_17201_);
lean_dec(v_k_17207_);
v_rowB_17219_ = lean_nat_add(v_baseB_17204_, v___x_17218_);
lean_dec(v___x_17218_);
v_sz_17220_ = lean_array_size(v_s_17208_);
v___x_17221_ = ((size_t)0ULL);
v___x_17222_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapFinIdxMUnsafe_map___at___00Submission_R22StreamingQuad_loop_spec__0___redArg(v___y_17214_, v___y_17215_, v___y_17213_, v_a3_17217_, v_rowB_17219_, v_B_17206_, v_sz_17220_, v___x_17221_, v_s_17208_);
lean_dec(v_rowB_17219_);
v_k_17207_ = v___x_17211_;
v_s_17208_ = v___x_17222_;
goto _start;
}
v___jp_17226_:
{
float v_a2_17230_; lean_object* v___x_17231_; lean_object* v___x_17232_; lean_object* v___x_17233_; lean_object* v___x_17234_; lean_object* v___x_17235_; uint8_t v___x_17236_; 
v_a2_17230_ = lean_float32_of_bits(v___y_17229_);
v___x_17231_ = lean_unsigned_to_nat(3u);
v___x_17232_ = lean_nat_mul(v___x_17231_, v_n_17202_);
v___x_17233_ = lean_nat_add(v_baseA_17203_, v___x_17232_);
lean_dec(v___x_17232_);
v___x_17234_ = lean_nat_add(v___x_17233_, v_k_17207_);
lean_dec(v___x_17233_);
v___x_17235_ = lean_array_get_size(v_A_17205_);
v___x_17236_ = lean_nat_dec_lt(v___x_17234_, v___x_17235_);
if (v___x_17236_ == 0)
{
lean_dec(v___x_17234_);
v___y_17213_ = v_a2_17230_;
v___y_17214_ = v___y_17227_;
v___y_17215_ = v___y_17228_;
v___y_17216_ = v___x_17225_;
goto v___jp_17212_;
}
else
{
lean_object* v___x_17237_; uint32_t v___x_17238_; 
v___x_17237_ = lean_array_fget_borrowed(v_A_17205_, v___x_17234_);
lean_dec(v___x_17234_);
v___x_17238_ = lean_unbox_uint32(v___x_17237_);
v___y_17213_ = v_a2_17230_;
v___y_17214_ = v___y_17227_;
v___y_17215_ = v___y_17228_;
v___y_17216_ = v___x_17238_;
goto v___jp_17212_;
}
}
v___jp_17239_:
{
float v_a1_17242_; lean_object* v___x_17243_; lean_object* v___x_17244_; lean_object* v___x_17245_; lean_object* v___x_17246_; lean_object* v___x_17247_; uint8_t v___x_17248_; 
v_a1_17242_ = lean_float32_of_bits(v___y_17241_);
v___x_17243_ = lean_unsigned_to_nat(2u);
v___x_17244_ = lean_nat_mul(v___x_17243_, v_n_17202_);
v___x_17245_ = lean_nat_add(v_baseA_17203_, v___x_17244_);
lean_dec(v___x_17244_);
v___x_17246_ = lean_nat_add(v___x_17245_, v_k_17207_);
lean_dec(v___x_17245_);
v___x_17247_ = lean_array_get_size(v_A_17205_);
v___x_17248_ = lean_nat_dec_lt(v___x_17246_, v___x_17247_);
if (v___x_17248_ == 0)
{
lean_dec(v___x_17246_);
v___y_17227_ = v___y_17240_;
v___y_17228_ = v_a1_17242_;
v___y_17229_ = v___x_17225_;
goto v___jp_17226_;
}
else
{
lean_object* v___x_17249_; uint32_t v___x_17250_; 
v___x_17249_ = lean_array_fget_borrowed(v_A_17205_, v___x_17246_);
lean_dec(v___x_17246_);
v___x_17250_ = lean_unbox_uint32(v___x_17249_);
v___y_17227_ = v___y_17240_;
v___y_17228_ = v_a1_17242_;
v___y_17229_ = v___x_17250_;
goto v___jp_17226_;
}
}
v___jp_17251_:
{
float v_a0_17253_; lean_object* v___x_17254_; lean_object* v___x_17255_; lean_object* v___x_17256_; uint8_t v___x_17257_; 
v_a0_17253_ = lean_float32_of_bits(v___y_17252_);
v___x_17254_ = lean_nat_add(v_baseA_17203_, v_n_17202_);
v___x_17255_ = lean_nat_add(v___x_17254_, v_k_17207_);
lean_dec(v___x_17254_);
v___x_17256_ = lean_array_get_size(v_A_17205_);
v___x_17257_ = lean_nat_dec_lt(v___x_17255_, v___x_17256_);
if (v___x_17257_ == 0)
{
lean_dec(v___x_17255_);
v___y_17240_ = v_a0_17253_;
v___y_17241_ = v___x_17225_;
goto v___jp_17239_;
}
else
{
lean_object* v___x_17258_; uint32_t v___x_17259_; 
v___x_17258_ = lean_array_fget_borrowed(v_A_17205_, v___x_17255_);
lean_dec(v___x_17255_);
v___x_17259_ = lean_unbox_uint32(v___x_17258_);
v___y_17240_ = v_a0_17253_;
v___y_17241_ = v___x_17259_;
goto v___jp_17239_;
}
}
}
}
}