LEAN_EXPORT lean_object* lp_competition_Submission_R19DCRawPair_loopEmit(lean_object* v_n_13598_, lean_object* v_baseA_13599_, lean_object* v_baseB_13600_, lean_object* v_p_13601_, lean_object* v_A_13602_, lean_object* v_B_13603_, lean_object* v_out_13604_, lean_object* v_k_13605_, float v_s0_13606_, float v_s1_13607_){
_start:
{
lean_object* v___y_13609_; float v___y_13610_; float v___y_13611_; uint32_t v___y_13612_; uint8_t v___x_13620_; 
v___x_13620_ = lean_nat_dec_lt(v_k_13605_, v_n_13598_);
if (v___x_13620_ == 0)
{
uint32_t v___x_13621_; lean_object* v___x_13622_; lean_object* v_out_13623_; lean_object* v___x_13624_; lean_object* v___x_13625_; uint32_t v___x_13626_; lean_object* v___x_13627_; lean_object* v___x_13628_; 
lean_dec(v_k_13605_);
v___x_13621_ = lp_competition_Submission_Packed10_finish(v_n_13598_, v_baseA_13599_, v_baseB_13600_, v_p_13601_, v_A_13602_, v_B_13603_, v_s0_13606_);
v___x_13622_ = lean_box_uint32(v___x_13621_);
v_out_13623_ = lean_array_push(v_out_13604_, v___x_13622_);
v___x_13624_ = lean_unsigned_to_nat(1u);
v___x_13625_ = lean_nat_add(v_baseB_13600_, v___x_13624_);
v___x_13626_ = lp_competition_Submission_Packed10_finish(v_n_13598_, v_baseA_13599_, v___x_13625_, v_p_13601_, v_A_13602_, v_B_13603_, v_s1_13607_);
lean_dec(v___x_13625_);
v___x_13627_ = lean_box_uint32(v___x_13626_);
v___x_13628_ = lean_array_push(v_out_13623_, v___x_13627_);
return v___x_13628_;
}
else
{
lean_object* v___x_13629_; uint32_t v___x_13630_; lean_object* v___y_13632_; float v___y_13633_; uint32_t v___y_13634_; uint32_t v___y_13644_; lean_object* v___x_13652_; uint8_t v___x_13653_; 
v___x_13629_ = lean_nat_add(v_baseA_13599_, v_k_13605_);
v___x_13630_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___x_13652_ = lean_array_get_size(v_A_13602_);
v___x_13653_ = lean_nat_dec_lt(v___x_13629_, v___x_13652_);
if (v___x_13653_ == 0)
{
lean_dec(v___x_13629_);
v___y_13644_ = v___x_13630_;
goto v___jp_13643_;
}
else
{
lean_object* v___x_13654_; uint32_t v___x_13655_; 
v___x_13654_ = lean_array_fget_borrowed(v_A_13602_, v___x_13629_);
lean_dec(v___x_13629_);
v___x_13655_ = lean_unbox_uint32(v___x_13654_);
v___y_13644_ = v___x_13655_;
goto v___jp_13643_;
}
v___jp_13631_:
{
float v_b0_13635_; lean_object* v___x_13636_; lean_object* v___x_13637_; lean_object* v___x_13638_; lean_object* v___x_13639_; uint8_t v___x_13640_; 
v_b0_13635_ = lean_float32_of_bits(v___y_13634_);
v___x_13636_ = lean_unsigned_to_nat(1u);
v___x_13637_ = lean_nat_add(v_baseB_13600_, v___x_13636_);
v___x_13638_ = lean_nat_add(v___x_13637_, v___y_13632_);
lean_dec(v___y_13632_);
lean_dec(v___x_13637_);
v___x_13639_ = lean_array_get_size(v_B_13603_);
v___x_13640_ = lean_nat_dec_lt(v___x_13638_, v___x_13639_);
if (v___x_13640_ == 0)
{
lean_dec(v___x_13638_);
v___y_13609_ = v___x_13636_;
v___y_13610_ = v_b0_13635_;
v___y_13611_ = v___y_13633_;
v___y_13612_ = v___x_13630_;
goto v___jp_13608_;
}
else
{
lean_object* v___x_13641_; uint32_t v___x_13642_; 
v___x_13641_ = lean_array_fget_borrowed(v_B_13603_, v___x_13638_);
lean_dec(v___x_13638_);
v___x_13642_ = lean_unbox_uint32(v___x_13641_);
v___y_13609_ = v___x_13636_;
v___y_13610_ = v_b0_13635_;
v___y_13611_ = v___y_13633_;
v___y_13612_ = v___x_13642_;
goto v___jp_13608_;
}
}
v___jp_13643_:
{
float v_a_13645_; lean_object* v___x_13646_; lean_object* v___x_13647_; lean_object* v___x_13648_; uint8_t v___x_13649_; 
v_a_13645_ = lean_float32_of_bits(v___y_13644_);
v___x_13646_ = lean_nat_mul(v_k_13605_, v_p_13601_);
v___x_13647_ = lean_nat_add(v_baseB_13600_, v___x_13646_);
v___x_13648_ = lean_array_get_size(v_B_13603_);
v___x_13649_ = lean_nat_dec_lt(v___x_13647_, v___x_13648_);
if (v___x_13649_ == 0)
{
lean_dec(v___x_13647_);
v___y_13632_ = v___x_13646_;
v___y_13633_ = v_a_13645_;
v___y_13634_ = v___x_13630_;
goto v___jp_13631_;
}
else
{
lean_object* v___x_13650_; uint32_t v___x_13651_; 
v___x_13650_ = lean_array_fget_borrowed(v_B_13603_, v___x_13647_);
lean_dec(v___x_13647_);
v___x_13651_ = lean_unbox_uint32(v___x_13650_);
v___y_13632_ = v___x_13646_;
v___y_13633_ = v_a_13645_;
v___y_13634_ = v___x_13651_;
goto v___jp_13631_;
}
}
}
v___jp_13608_:
{
float v_b1_13613_; lean_object* v___x_13614_; float v___x_13615_; float v___x_13616_; float v___x_13617_; float v___x_13618_; 
v_b1_13613_ = lean_float32_of_bits(v___y_13612_);
v___x_13614_ = lean_nat_add(v_k_13605_, v___y_13609_);
lean_dec(v_k_13605_);
v___x_13615_ = lean_float32_mul(v___y_13611_, v___y_13610_);
v___x_13616_ = lean_float32_add(v_s0_13606_, v___x_13615_);
v___x_13617_ = lean_float32_mul(v___y_13611_, v_b1_13613_);
v___x_13618_ = lean_float32_add(v_s1_13607_, v___x_13617_);
v_k_13605_ = v___x_13614_;
v_s0_13606_ = v___x_13616_;
v_s1_13607_ = v___x_13618_;
goto _start;
}
}
}
