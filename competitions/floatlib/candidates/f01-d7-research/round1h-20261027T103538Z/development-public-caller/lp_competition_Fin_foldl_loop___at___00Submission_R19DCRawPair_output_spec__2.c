LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_R19DCRawPair_output_spec__2(lean_object* v_baseB_14076_, lean_object* v_n_14077_, lean_object* v_baseA_14078_, lean_object* v_p_14079_, lean_object* v___x_14080_, lean_object* v___x_14081_, lean_object* v_n_14082_, lean_object* v_x_14083_, lean_object* v_i_14084_){
_start:
{
lean_object* v___y_14086_; uint8_t v___x_14090_; 
v___x_14090_ = lean_nat_dec_lt(v_i_14084_, v_n_14082_);
if (v___x_14090_ == 0)
{
lean_dec(v_i_14084_);
return v_x_14083_;
}
else
{
lean_object* v___x_14091_; lean_object* v___x_14092_; lean_object* v___y_14094_; lean_object* v___y_14095_; lean_object* v___y_14105_; lean_object* v___x_14114_; uint8_t v___x_14115_; 
v___x_14091_ = lean_unsigned_to_nat(2u);
v___x_14092_ = lean_nat_mul(v___x_14091_, v_i_14084_);
v___x_14114_ = lean_nat_sub(v_p_14079_, v___x_14092_);
v___x_14115_ = lean_nat_dec_le(v___x_14091_, v___x_14114_);
if (v___x_14115_ == 0)
{
v___y_14105_ = v___x_14114_;
goto v___jp_14104_;
}
else
{
lean_dec(v___x_14114_);
v___y_14105_ = v___x_14091_;
goto v___jp_14104_;
}
v___jp_14093_:
{
uint8_t v___x_14096_; 
v___x_14096_ = lean_nat_dec_eq(v___y_14095_, v___y_14094_);
if (v___x_14096_ == 0)
{
lean_object* v___x_14097_; lean_object* v___x_14098_; float v___x_14099_; lean_object* v_result_14100_; lean_object* v___x_14101_; 
v___x_14097_ = lean_nat_add(v_baseB_14076_, v___x_14092_);
lean_dec(v___x_14092_);
v___x_14098_ = lean_unsigned_to_nat(0u);
v___x_14099_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v_result_14100_ = lp_competition_Submission_R19DCRawPair_loop(v_n_14077_, v_baseA_14078_, v___x_14097_, v_p_14079_, v___x_14080_, v___x_14081_, v___x_14098_, v___x_14099_, v___x_14099_);
v___x_14101_ = lp_competition_Fin_foldl_loop___at___00Submission_R19DCRawPair_output_spec__0(v___x_14097_, v_result_14100_, v_n_14077_, v_baseA_14078_, v_p_14079_, v___x_14080_, v___x_14081_, v___y_14095_, v_x_14083_, v___x_14098_);
lean_dec(v___y_14095_);
lean_dec_ref(v_result_14100_);
lean_dec(v___x_14097_);
v___y_14086_ = v___x_14101_;
goto v___jp_14085_;
}
else
{
lean_object* v___x_14102_; lean_object* v___x_14103_; 
v___x_14102_ = lean_unsigned_to_nat(0u);
v___x_14103_ = lp_competition_Fin_foldl_loop___at___00Submission_R19DCRawPair_output_spec__1(v_baseB_14076_, v___x_14092_, v_n_14077_, v_baseA_14078_, v_p_14079_, v___x_14080_, v___x_14081_, v___y_14095_, v_x_14083_, v___x_14102_);
lean_dec(v___y_14095_);
lean_dec(v___x_14092_);
v___y_14086_ = v___x_14103_;
goto v___jp_14085_;
}
}
v___jp_14104_:
{
lean_object* v___x_14106_; uint8_t v___x_14107_; 
v___x_14106_ = lean_unsigned_to_nat(1u);
v___x_14107_ = lean_nat_dec_eq(v___y_14105_, v___x_14106_);
lean_dec(v___y_14105_);
if (v___x_14107_ == 0)
{
lean_object* v___x_14108_; lean_object* v___x_14109_; float v___x_14110_; lean_object* v___x_14111_; 
v___x_14108_ = lean_nat_add(v_baseB_14076_, v___x_14092_);
lean_dec(v___x_14092_);
v___x_14109_ = lean_unsigned_to_nat(0u);
v___x_14110_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_14111_ = lp_competition_Submission_R19DCRawPair_loopEmit(v_n_14077_, v_baseA_14078_, v___x_14108_, v_p_14079_, v___x_14080_, v___x_14081_, v_x_14083_, v___x_14109_, v___x_14110_, v___x_14110_);
lean_dec(v___x_14108_);
v___y_14086_ = v___x_14111_;
goto v___jp_14085_;
}
else
{
lean_object* v___x_14112_; uint8_t v___x_14113_; 
v___x_14112_ = lean_nat_sub(v_p_14079_, v___x_14092_);
v___x_14113_ = lean_nat_dec_le(v___x_14091_, v___x_14112_);
if (v___x_14113_ == 0)
{
v___y_14094_ = v___x_14106_;
v___y_14095_ = v___x_14112_;
goto v___jp_14093_;
}
else
{
lean_dec(v___x_14112_);
v___y_14094_ = v___x_14106_;
v___y_14095_ = v___x_14091_;
goto v___jp_14093_;
}
}
}
}
v___jp_14085_:
{
lean_object* v___x_14087_; lean_object* v___x_14088_; 
v___x_14087_ = lean_unsigned_to_nat(1u);
v___x_14088_ = lean_nat_add(v_i_14084_, v___x_14087_);
lean_dec(v_i_14084_);
v_x_14083_ = v___y_14086_;
v_i_14084_ = v___x_14088_;
goto _start;
}
}
}
