LEAN_EXPORT uint32_t lp_competition_Submission_R17NumericMulInteger_normalCore(uint32_t v_sum_14580_, uint32_t v_u_14581_, uint32_t v_v_14582_){
_start:
{
uint32_t v___x_14583_; uint32_t v___x_14584_; uint32_t v___x_14585_; uint32_t v_a_14586_; uint32_t v___x_14587_; uint32_t v_b_14588_; uint64_t v___x_14589_; uint64_t v___x_14590_; uint64_t v_product_14591_; float v___x_14592_; uint64_t v_r_14593_; uint64_t v___y_14595_; uint64_t v___x_14612_; uint8_t v___x_14613_; 
v___x_14583_ = 8388607;
v___x_14584_ = lean_uint32_land(v_u_14581_, v___x_14583_);
v___x_14585_ = 8388608;
v_a_14586_ = lean_uint32_lor(v___x_14584_, v___x_14585_);
v___x_14587_ = lean_uint32_land(v_v_14582_, v___x_14583_);
v_b_14588_ = lean_uint32_lor(v___x_14587_, v___x_14585_);
v___x_14589_ = lean_uint32_to_uint64(v_a_14586_);
v___x_14590_ = lean_uint32_to_uint64(v_b_14588_);
v_product_14591_ = lean_uint64_mul(v___x_14589_, v___x_14590_);
v___x_14592_ = lean_uint64_to_float32(v_product_14591_);
v_r_14593_ = lean_float32_to_uint64(v___x_14592_);
v___x_14612_ = 140737488355328ULL;
v___x_14613_ = lean_uint64_dec_le(v___x_14612_, v_r_14593_);
if (v___x_14613_ == 0)
{
uint64_t v___x_14614_; 
v___x_14614_ = 0ULL;
v___y_14595_ = v___x_14614_;
goto v___jp_14594_;
}
else
{
uint64_t v___x_14615_; 
v___x_14615_ = 1ULL;
v___y_14595_ = v___x_14615_;
goto v___jp_14594_;
}
v___jp_14594_:
{
uint64_t v___x_14596_; uint64_t v___x_14597_; uint64_t v___x_14598_; uint32_t v_q_14599_; uint32_t v___x_14600_; uint32_t v___x_14601_; uint32_t v___x_14602_; uint32_t v_e_14603_; uint32_t v___x_14604_; uint32_t v___x_14605_; uint32_t v___x_14606_; uint32_t v___x_14607_; uint32_t v___x_14608_; uint32_t v___x_14609_; uint32_t v___x_14610_; uint32_t v___x_14611_; 
v___x_14596_ = 23ULL;
v___x_14597_ = lean_uint64_add(v___x_14596_, v___y_14595_);
v___x_14598_ = lean_uint64_shift_right(v_r_14593_, v___x_14597_);
v_q_14599_ = lean_uint64_to_uint32(v___x_14598_);
v___x_14600_ = 127;
v___x_14601_ = lean_uint32_sub(v_sum_14580_, v___x_14600_);
v___x_14602_ = lean_uint64_to_uint32(v___y_14595_);
v_e_14603_ = lean_uint32_add(v___x_14601_, v___x_14602_);
v___x_14604_ = lean_uint32_xor(v_u_14581_, v_v_14582_);
v___x_14605_ = 2147483648;
v___x_14606_ = lean_uint32_land(v___x_14604_, v___x_14605_);
v___x_14607_ = 23;
v___x_14608_ = lean_uint32_shift_left(v_e_14603_, v___x_14607_);
v___x_14609_ = lean_uint32_lor(v___x_14606_, v___x_14608_);
v___x_14610_ = lean_uint32_sub(v_q_14599_, v___x_14585_);
v___x_14611_ = lean_uint32_lor(v___x_14609_, v___x_14610_);
return v___x_14611_;
}
}
}