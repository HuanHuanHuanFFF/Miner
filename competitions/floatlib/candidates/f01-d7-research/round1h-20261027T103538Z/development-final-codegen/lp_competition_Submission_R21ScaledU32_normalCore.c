LEAN_EXPORT uint32_t lp_competition_Submission_R21ScaledU32_normalCore(uint32_t v_sum_14583_, uint32_t v_u_14584_, uint32_t v_v_14585_){
_start:
{
float v_scale_14586_; uint32_t v___x_14587_; uint32_t v___x_14588_; uint32_t v___x_14589_; uint32_t v_a_14590_; uint32_t v___x_14591_; uint32_t v_b_14592_; uint64_t v___x_14593_; uint64_t v___x_14594_; uint64_t v_p_14595_; float v___x_14596_; float v___x_14597_; uint32_t v_z_14598_; uint32_t v___x_14599_; uint32_t v_high_14600_; uint32_t v_q_14601_; uint32_t v___x_14602_; uint32_t v___x_14603_; uint32_t v_e_14604_; uint32_t v___x_14605_; uint32_t v___x_14606_; uint32_t v___x_14607_; uint32_t v___x_14608_; uint32_t v___x_14609_; uint32_t v___x_14610_; uint32_t v___x_14611_; uint32_t v___x_14612_; 
v_scale_14586_ = lp_competition_Submission_R21ScaledU32_powNeg23;
v___x_14587_ = 8388607;
v___x_14588_ = lean_uint32_land(v_u_14584_, v___x_14587_);
v___x_14589_ = 8388608;
v_a_14590_ = lean_uint32_lor(v___x_14588_, v___x_14589_);
v___x_14591_ = lean_uint32_land(v_v_14585_, v___x_14587_);
v_b_14592_ = lean_uint32_lor(v___x_14591_, v___x_14589_);
v___x_14593_ = lean_uint32_to_uint64(v_a_14590_);
v___x_14594_ = lean_uint32_to_uint64(v_b_14592_);
v_p_14595_ = lean_uint64_mul(v___x_14593_, v___x_14594_);
v___x_14596_ = lean_uint64_to_float32(v_p_14595_);
v___x_14597_ = lean_float32_mul(v___x_14596_, v_scale_14586_);
v_z_14598_ = lean_float32_to_uint32(v___x_14597_);
v___x_14599_ = 24;
v_high_14600_ = lean_uint32_shift_right(v_z_14598_, v___x_14599_);
v_q_14601_ = lean_uint32_shift_right(v_z_14598_, v_high_14600_);
v___x_14602_ = 127;
v___x_14603_ = lean_uint32_sub(v_sum_14583_, v___x_14602_);
v_e_14604_ = lean_uint32_add(v___x_14603_, v_high_14600_);
v___x_14605_ = lean_uint32_xor(v_u_14584_, v_v_14585_);
v___x_14606_ = 2147483648;
v___x_14607_ = lean_uint32_land(v___x_14605_, v___x_14606_);
v___x_14608_ = 23;
v___x_14609_ = lean_uint32_shift_left(v_e_14604_, v___x_14608_);
v___x_14610_ = lean_uint32_lor(v___x_14607_, v___x_14609_);
v___x_14611_ = lean_uint32_sub(v_q_14601_, v___x_14589_);
v___x_14612_ = lean_uint32_lor(v___x_14610_, v___x_14611_);
return v___x_14612_;
}
}
