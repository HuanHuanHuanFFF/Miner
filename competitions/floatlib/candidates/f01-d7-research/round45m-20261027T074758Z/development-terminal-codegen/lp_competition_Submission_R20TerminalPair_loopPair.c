LEAN_EXPORT lean_object* lp_competition_Submission_R20TerminalPair_loopPair(lean_object* v_n_14580_, lean_object* v_baseA_14581_, lean_object* v_baseB_14582_, lean_object* v_p_14583_, lean_object* v_A_14584_, lean_object* v_B_14585_, lean_object* v_k_14586_, float v_s0_14587_, float v_s1_14588_){
_start:
{
float v___y_14590_; lean_object* v___y_14591_; float v___y_14592_; uint32_t v___y_14593_; uint8_t v___x_14601_; 
v___x_14601_ = lean_nat_dec_lt(v_k_14586_, v_n_14580_);
if (v___x_14601_ == 0)
{
lean_object* v___x_14602_; 
lean_dec(v_k_14586_);
v___x_14602_ = lean_alloc_ctor(0, 0, 8);
lean_ctor_set_float32(v___x_14602_, 0, v_s0_14587_);
lean_ctor_set_float32(v___x_14602_, 4, v_s1_14588_);
return v___x_14602_;
}
else
{
lean_object* v___x_14603_; uint32_t v___x_14604_; float v___y_14606_; lean_object* v___y_14607_; uint32_t v___y_14608_; uint32_t v___y_14618_; lean_object* v___x_14626_; uint8_t v___x_14627_; 
v___x_14603_ = lean_nat_add(v_baseA_14581_, v_k_14586_);
v___x_14604_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___x_14626_ = lean_array_get_size(v_A_14584_);
v___x_14627_ = lean_nat_dec_lt(v___x_14603_, v___x_14626_);
if (v___x_14627_ == 0)
{
lean_dec(v___x_14603_);
v___y_14618_ = v___x_14604_;
goto v___jp_14617_;
}
else
{
lean_object* v___x_14628_; uint32_t v___x_14629_; 
v___x_14628_ = lean_array_fget_borrowed(v_A_14584_, v___x_14603_);
lean_dec(v___x_14603_);
v___x_14629_ = lean_unbox_uint32(v___x_14628_);
v___y_14618_ = v___x_14629_;
goto v___jp_14617_;
}
v___jp_14605_:
{
float v_b0_14609_; lean_object* v___x_14610_; lean_object* v___x_14611_; lean_object* v___x_14612_; lean_object* v___x_14613_; uint8_t v___x_14614_; 
v_b0_14609_ = lean_float32_of_bits(v___y_14608_);
v___x_14610_ = lean_unsigned_to_nat(1u);
v___x_14611_ = lean_nat_add(v_baseB_14582_, v___x_14610_);
v___x_14612_ = lean_nat_add(v___x_14611_, v___y_14607_);
lean_dec(v___y_14607_);
lean_dec(v___x_14611_);
v___x_14613_ = lean_array_get_size(v_B_14585_);
v___x_14614_ = lean_nat_dec_lt(v___x_14612_, v___x_14613_);
if (v___x_14614_ == 0)
{
lean_dec(v___x_14612_);
v___y_14590_ = v_b0_14609_;
v___y_14591_ = v___x_14610_;
v___y_14592_ = v___y_14606_;
v___y_14593_ = v___x_14604_;
goto v___jp_14589_;
}
else
{
lean_object* v___x_14615_; uint32_t v___x_14616_; 
v___x_14615_ = lean_array_fget_borrowed(v_B_14585_, v___x_14612_);
lean_dec(v___x_14612_);
v___x_14616_ = lean_unbox_uint32(v___x_14615_);
v___y_14590_ = v_b0_14609_;
v___y_14591_ = v___x_14610_;
v___y_14592_ = v___y_14606_;
v___y_14593_ = v___x_14616_;
goto v___jp_14589_;
}
}
v___jp_14617_:
{
float v_a_14619_; lean_object* v___x_14620_; lean_object* v___x_14621_; lean_object* v___x_14622_; uint8_t v___x_14623_; 
v_a_14619_ = lean_float32_of_bits(v___y_14618_);
v___x_14620_ = lean_nat_mul(v_k_14586_, v_p_14583_);
v___x_14621_ = lean_nat_add(v_baseB_14582_, v___x_14620_);
v___x_14622_ = lean_array_get_size(v_B_14585_);
v___x_14623_ = lean_nat_dec_lt(v___x_14621_, v___x_14622_);
if (v___x_14623_ == 0)
{
lean_dec(v___x_14621_);
v___y_14606_ = v_a_14619_;
v___y_14607_ = v___x_14620_;
v___y_14608_ = v___x_14604_;
goto v___jp_14605_;
}
else
{
lean_object* v___x_14624_; uint32_t v___x_14625_; 
v___x_14624_ = lean_array_fget_borrowed(v_B_14585_, v___x_14621_);
lean_dec(v___x_14621_);
v___x_14625_ = lean_unbox_uint32(v___x_14624_);
v___y_14606_ = v_a_14619_;
v___y_14607_ = v___x_14620_;
v___y_14608_ = v___x_14625_;
goto v___jp_14605_;
}
}
}
v___jp_14589_:
{
float v_b1_14594_; lean_object* v___x_14595_; float v___x_14596_; float v___x_14597_; float v___x_14598_; float v___x_14599_; 
v_b1_14594_ = lean_float32_of_bits(v___y_14593_);
v___x_14595_ = lean_nat_add(v_k_14586_, v___y_14591_);
lean_dec(v_k_14586_);
v___x_14596_ = lean_float32_mul(v___y_14592_, v___y_14590_);
v___x_14597_ = lean_float32_add(v_s0_14587_, v___x_14596_);
v___x_14598_ = lean_float32_mul(v___y_14592_, v_b1_14594_);
v___x_14599_ = lean_float32_add(v_s1_14588_, v___x_14598_);
v_k_14586_ = v___x_14595_;
v_s0_14587_ = v___x_14597_;
v_s1_14588_ = v___x_14599_;
goto _start;
}
}
}
