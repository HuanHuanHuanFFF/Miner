LEAN_EXPORT uint32_t lp_competition_Submission_R19DirectBias_normalCore(uint32_t v_sum_14580_, uint32_t v_u_14581_, uint32_t v_v_14582_){
_start:
{
uint32_t v___x_14583_; uint32_t v___x_14584_; uint32_t v___x_14585_; uint64_t v___y_14587_; uint32_t v_a_14606_; uint32_t v___x_14607_; uint32_t v_b_14608_; uint64_t v___x_14609_; uint64_t v___x_14610_; uint64_t v_p_14611_; uint64_t v___x_14612_; uint8_t v___x_14613_; 
v___x_14583_ = 8388607;
v___x_14584_ = lean_uint32_land(v_u_14581_, v___x_14583_);
v___x_14585_ = 8388608;
v_a_14606_ = lean_uint32_lor(v___x_14584_, v___x_14585_);
v___x_14607_ = lean_uint32_land(v_v_14582_, v___x_14583_);
v_b_14608_ = lean_uint32_lor(v___x_14607_, v___x_14585_);
v___x_14609_ = lean_uint32_to_uint64(v_a_14606_);
v___x_14610_ = lean_uint32_to_uint64(v_b_14608_);
v_p_14611_ = lean_uint64_mul(v___x_14609_, v___x_14610_);
v___x_14612_ = 140737488355328ULL;
v___x_14613_ = lean_uint64_dec_lt(v_p_14611_, v___x_14612_);
if (v___x_14613_ == 0)
{
uint64_t v___x_14614_; uint64_t v___x_14615_; uint64_t v___x_14616_; uint64_t v___x_14617_; uint64_t v___x_14618_; uint64_t v___x_14619_; uint64_t v___x_14620_; 
v___x_14614_ = 8388607ULL;
v___x_14615_ = lean_uint64_add(v_p_14611_, v___x_14614_);
v___x_14616_ = 24ULL;
v___x_14617_ = lean_uint64_shift_right(v_p_14611_, v___x_14616_);
v___x_14618_ = 1ULL;
v___x_14619_ = lean_uint64_land(v___x_14617_, v___x_14618_);
v___x_14620_ = lean_uint64_add(v___x_14615_, v___x_14619_);
v___y_14587_ = v___x_14620_;
goto v___jp_14586_;
}
else
{
uint64_t v___x_14621_; uint64_t v___x_14622_; uint64_t v___x_14623_; uint64_t v___x_14624_; uint64_t v___x_14625_; uint64_t v___x_14626_; uint64_t v___x_14627_; 
v___x_14621_ = 4194303ULL;
v___x_14622_ = lean_uint64_add(v_p_14611_, v___x_14621_);
v___x_14623_ = 23ULL;
v___x_14624_ = lean_uint64_shift_right(v_p_14611_, v___x_14623_);
v___x_14625_ = 1ULL;
v___x_14626_ = lean_uint64_land(v___x_14624_, v___x_14625_);
v___x_14627_ = lean_uint64_add(v___x_14622_, v___x_14626_);
v___y_14587_ = v___x_14627_;
goto v___jp_14586_;
}
v___jp_14586_:
{
uint64_t v___x_14588_; uint64_t v_high_14589_; uint64_t v___x_14590_; uint64_t v___x_14591_; uint64_t v___x_14592_; uint32_t v_q_14593_; uint32_t v___x_14594_; uint32_t v___x_14595_; uint32_t v___x_14596_; uint32_t v_e_14597_; uint32_t v___x_14598_; uint32_t v___x_14599_; uint32_t v___x_14600_; uint32_t v___x_14601_; uint32_t v___x_14602_; uint32_t v___x_14603_; uint32_t v___x_14604_; uint32_t v___x_14605_; 
v___x_14588_ = 47ULL;
v_high_14589_ = lean_uint64_shift_right(v___y_14587_, v___x_14588_);
v___x_14590_ = 23ULL;
v___x_14591_ = lean_uint64_add(v___x_14590_, v_high_14589_);
v___x_14592_ = lean_uint64_shift_right(v___y_14587_, v___x_14591_);
v_q_14593_ = lean_uint64_to_uint32(v___x_14592_);
v___x_14594_ = 127;
v___x_14595_ = lean_uint32_sub(v_sum_14580_, v___x_14594_);
v___x_14596_ = lean_uint64_to_uint32(v_high_14589_);
v_e_14597_ = lean_uint32_add(v___x_14595_, v___x_14596_);
v___x_14598_ = lean_uint32_xor(v_u_14581_, v_v_14582_);
v___x_14599_ = 2147483648;
v___x_14600_ = lean_uint32_land(v___x_14598_, v___x_14599_);
v___x_14601_ = 23;
v___x_14602_ = lean_uint32_shift_left(v_e_14597_, v___x_14601_);
v___x_14603_ = lean_uint32_lor(v___x_14600_, v___x_14602_);
v___x_14604_ = lean_uint32_sub(v_q_14593_, v___x_14585_);
v___x_14605_ = lean_uint32_lor(v___x_14603_, v___x_14604_);
return v___x_14605_;
}
}
}
