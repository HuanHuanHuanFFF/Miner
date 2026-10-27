LEAN_EXPORT uint32_t lp_competition_Submission_R17NumericMulInteger_guardedMul(lean_object* v_fallback_14624_, uint32_t v_x_14625_, uint32_t v_y_14626_){
_start:
{
uint32_t v___x_14627_; uint32_t v___x_14628_; uint32_t v___x_14629_; uint32_t v_eu_14630_; uint32_t v___x_14631_; uint32_t v___x_14632_; uint32_t v___x_14633_; uint8_t v___x_14634_; 
v___x_14627_ = 23;
v___x_14628_ = lean_uint32_shift_right(v_x_14625_, v___x_14627_);
v___x_14629_ = 255;
v_eu_14630_ = lean_uint32_land(v___x_14628_, v___x_14629_);
v___x_14631_ = 1;
v___x_14632_ = lean_uint32_sub(v_eu_14630_, v___x_14631_);
v___x_14633_ = 253;
v___x_14634_ = lean_uint32_dec_le(v___x_14632_, v___x_14633_);
if (v___x_14634_ == 0)
{
lean_object* v___x_14635_; lean_object* v___x_14636_; lean_object* v___x_14637_; uint32_t v___x_14638_; 
v___x_14635_ = lean_box_uint32(v_x_14625_);
v___x_14636_ = lean_box_uint32(v_y_14626_);
v___x_14637_ = lean_apply_2(v_fallback_14624_, v___x_14635_, v___x_14636_);
v___x_14638_ = lean_unbox_uint32(v___x_14637_);
lean_dec(v___x_14637_);
return v___x_14638_;
}
else
{
uint32_t v___x_14639_; uint32_t v_ev_14640_; uint32_t v___x_14641_; uint8_t v___x_14642_; 
v___x_14639_ = lean_uint32_shift_right(v_y_14626_, v___x_14627_);
v_ev_14640_ = lean_uint32_land(v___x_14639_, v___x_14629_);
v___x_14641_ = lean_uint32_sub(v_ev_14640_, v___x_14631_);
v___x_14642_ = lean_uint32_dec_le(v___x_14641_, v___x_14633_);
if (v___x_14642_ == 0)
{
lean_object* v___x_14643_; lean_object* v___x_14644_; lean_object* v___x_14645_; uint32_t v___x_14646_; 
v___x_14643_ = lean_box_uint32(v_x_14625_);
v___x_14644_ = lean_box_uint32(v_y_14626_);
v___x_14645_ = lean_apply_2(v_fallback_14624_, v___x_14643_, v___x_14644_);
v___x_14646_ = lean_unbox_uint32(v___x_14645_);
lean_dec(v___x_14645_);
return v___x_14646_;
}
else
{
uint32_t v_s_14647_; uint32_t v___x_14648_; uint32_t v___x_14649_; uint32_t v___x_14650_; uint8_t v___x_14651_; 
v_s_14647_ = lean_uint32_add(v_eu_14630_, v_ev_14640_);
v___x_14648_ = 128;
v___x_14649_ = lean_uint32_sub(v_s_14647_, v___x_14648_);
v___x_14650_ = 252;
v___x_14651_ = lean_uint32_dec_le(v___x_14649_, v___x_14650_);
if (v___x_14651_ == 0)
{
lean_object* v___x_14652_; lean_object* v___x_14653_; lean_object* v___x_14654_; uint32_t v___x_14655_; 
v___x_14652_ = lean_box_uint32(v_x_14625_);
v___x_14653_ = lean_box_uint32(v_y_14626_);
v___x_14654_ = lean_apply_2(v_fallback_14624_, v___x_14652_, v___x_14653_);
v___x_14655_ = lean_unbox_uint32(v___x_14654_);
lean_dec(v___x_14654_);
return v___x_14655_;
}
else
{
uint32_t v___x_14656_; uint32_t v___x_14657_; uint32_t v___x_14658_; uint32_t v_a_14659_; uint32_t v___x_14660_; uint32_t v_b_14661_; uint64_t v___x_14662_; uint64_t v___x_14663_; uint64_t v_product_14664_; float v___x_14665_; uint64_t v_r_14666_; uint64_t v___y_14668_; uint64_t v___x_14684_; uint8_t v___x_14685_; 
lean_dec_ref(v_fallback_14624_);
v___x_14656_ = 8388607;
v___x_14657_ = lean_uint32_land(v_x_14625_, v___x_14656_);
v___x_14658_ = 8388608;
v_a_14659_ = lean_uint32_lor(v___x_14657_, v___x_14658_);
v___x_14660_ = lean_uint32_land(v_y_14626_, v___x_14656_);
v_b_14661_ = lean_uint32_lor(v___x_14660_, v___x_14658_);
v___x_14662_ = lean_uint32_to_uint64(v_a_14659_);
v___x_14663_ = lean_uint32_to_uint64(v_b_14661_);
v_product_14664_ = lean_uint64_mul(v___x_14662_, v___x_14663_);
v___x_14665_ = lean_uint64_to_float32(v_product_14664_);
v_r_14666_ = lean_float32_to_uint64(v___x_14665_);
v___x_14684_ = 140737488355328ULL;
v___x_14685_ = lean_uint64_dec_le(v___x_14684_, v_r_14666_);
if (v___x_14685_ == 0)
{
uint64_t v___x_14686_; 
v___x_14686_ = 0ULL;
v___y_14668_ = v___x_14686_;
goto v___jp_14667_;
}
else
{
uint64_t v___x_14687_; 
v___x_14687_ = 1ULL;
v___y_14668_ = v___x_14687_;
goto v___jp_14667_;
}
v___jp_14667_:
{
uint64_t v___x_14669_; uint64_t v___x_14670_; uint64_t v___x_14671_; uint32_t v_q_14672_; uint32_t v___x_14673_; uint32_t v___x_14674_; uint32_t v___x_14675_; uint32_t v_e_14676_; uint32_t v___x_14677_; uint32_t v___x_14678_; uint32_t v___x_14679_; uint32_t v___x_14680_; uint32_t v___x_14681_; uint32_t v___x_14682_; uint32_t v___x_14683_; 
v___x_14669_ = 23ULL;
v___x_14670_ = lean_uint64_add(v___x_14669_, v___y_14668_);
v___x_14671_ = lean_uint64_shift_right(v_r_14666_, v___x_14670_);
v_q_14672_ = lean_uint64_to_uint32(v___x_14671_);
v___x_14673_ = 127;
v___x_14674_ = lean_uint32_sub(v_s_14647_, v___x_14673_);
v___x_14675_ = lean_uint64_to_uint32(v___y_14668_);
v_e_14676_ = lean_uint32_add(v___x_14674_, v___x_14675_);
v___x_14677_ = lean_uint32_xor(v_x_14625_, v_y_14626_);
v___x_14678_ = 2147483648;
v___x_14679_ = lean_uint32_land(v___x_14677_, v___x_14678_);
v___x_14680_ = lean_uint32_shift_left(v_e_14676_, v___x_14627_);
v___x_14681_ = lean_uint32_lor(v___x_14679_, v___x_14680_);
v___x_14682_ = lean_uint32_sub(v_q_14672_, v___x_14658_);
v___x_14683_ = lean_uint32_lor(v___x_14681_, v___x_14682_);
return v___x_14683_;
}
}
}
}
}
}