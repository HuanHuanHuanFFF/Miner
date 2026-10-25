LEAN_EXPORT uint64_t lp_competition_Submission_R15BranchlessNormal_round(uint64_t v_value_7696_, uint64_t v_shift_7697_){
_start:
{
uint64_t v_q_7698_; uint64_t v___y_7700_; uint64_t v___y_7701_; uint64_t v___y_7702_; uint64_t v___x_7706_; uint64_t v___y_7708_; uint64_t v___y_7709_; uint64_t v___x_7713_; uint64_t v___x_7714_; uint64_t v_r_7715_; uint64_t v___x_7716_; uint64_t v_half_7717_; uint8_t v___x_7718_; uint8_t v___x_7719_; uint64_t v___y_7721_; 
v_q_7698_ = lean_uint64_shift_right(v_value_7696_, v_shift_7697_);
v___x_7706_ = 1ULL;
v___x_7713_ = lean_uint64_shift_left(v___x_7706_, v_shift_7697_);
v___x_7714_ = lean_uint64_sub(v___x_7713_, v___x_7706_);
v_r_7715_ = lean_uint64_land(v_value_7696_, v___x_7714_);
v___x_7716_ = lean_uint64_sub(v_shift_7697_, v___x_7706_);
v_half_7717_ = lean_uint64_shift_left(v___x_7706_, v___x_7716_);
v___x_7718_ = lean_uint64_dec_lt(v_r_7715_, v_half_7717_);
v___x_7719_ = lean_uint64_dec_lt(v_half_7717_, v_r_7715_);
if (v___x_7718_ == 0)
{
v___y_7721_ = v___x_7706_;
goto v___jp_7720_;
}
else
{
uint64_t v___x_7723_; 
v___x_7723_ = 0ULL;
v___y_7721_ = v___x_7723_;
goto v___jp_7720_;
}
v___jp_7699_:
{
uint64_t v___x_7703_; uint64_t v___x_7704_; uint64_t v___x_7705_; 
v___x_7703_ = lean_uint64_lor(v___y_7701_, v___y_7702_);
v___x_7704_ = lean_uint64_land(v___y_7700_, v___x_7703_);
v___x_7705_ = lean_uint64_add(v_q_7698_, v___x_7704_);
return v___x_7705_;
}
v___jp_7707_:
{
uint64_t v___x_7710_; uint64_t v___x_7711_; uint8_t v___x_7712_; 
v___x_7710_ = lean_uint64_land(v_q_7698_, v___x_7706_);
v___x_7711_ = 0ULL;
v___x_7712_ = lean_uint64_dec_eq(v___x_7710_, v___x_7711_);
if (v___x_7712_ == 0)
{
v___y_7700_ = v___y_7708_;
v___y_7701_ = v___y_7709_;
v___y_7702_ = v___x_7706_;
goto v___jp_7699_;
}
else
{
v___y_7700_ = v___y_7708_;
v___y_7701_ = v___y_7709_;
v___y_7702_ = v___x_7711_;
goto v___jp_7699_;
}
}
v___jp_7720_:
{
if (v___x_7719_ == 0)
{
uint64_t v___x_7722_; 
v___x_7722_ = 0ULL;
v___y_7708_ = v___y_7721_;
v___y_7709_ = v___x_7722_;
goto v___jp_7707_;
}
else
{
v___y_7708_ = v___y_7721_;
v___y_7709_ = v___x_7706_;
goto v___jp_7707_;
}
}
}
}