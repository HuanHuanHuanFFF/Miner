LEAN_EXPORT lean_object* lp_competition_Submission_R20TerminalPair_loopEmit(lean_object* v_n_14671_, lean_object* v_baseA_14672_, lean_object* v_baseB_14673_, lean_object* v_p_14674_, lean_object* v_A_14675_, lean_object* v_B_14676_, lean_object* v_out_14677_, lean_object* v_k_14678_, float v_s0_14679_, float v_s1_14680_){
_start:
{
lean_object* v___y_14682_; float v___y_14683_; float v___y_14684_; uint32_t v___y_14685_; uint8_t v___x_14693_; 
v___x_14693_ = lean_nat_dec_lt(v_k_14678_, v_n_14671_);
if (v___x_14693_ == 0)
{
uint32_t v___x_14694_; lean_object* v___x_14695_; lean_object* v_out_14696_; lean_object* v___x_14697_; lean_object* v___x_14698_; uint32_t v___x_14699_; lean_object* v___x_14700_; lean_object* v___x_14701_; 
lean_dec(v_k_14678_);
v___x_14694_ = lp_competition_Submission_Packed10_finish(v_n_14671_, v_baseA_14672_, v_baseB_14673_, v_p_14674_, v_A_14675_, v_B_14676_, v_s0_14679_);
v___x_14695_ = lean_box_uint32(v___x_14694_);
v_out_14696_ = lean_array_push(v_out_14677_, v___x_14695_);
v___x_14697_ = lean_unsigned_to_nat(1u);
v___x_14698_ = lean_nat_add(v_baseB_14673_, v___x_14697_);
v___x_14699_ = lp_competition_Submission_Packed10_finish(v_n_14671_, v_baseA_14672_, v___x_14698_, v_p_14674_, v_A_14675_, v_B_14676_, v_s1_14680_);
lean_dec(v___x_14698_);
v___x_14700_ = lean_box_uint32(v___x_14699_);
v___x_14701_ = lean_array_push(v_out_14696_, v___x_14700_);
return v___x_14701_;
}
else
{
lean_object* v___x_14702_; uint32_t v___x_14703_; lean_object* v___y_14705_; float v___y_14706_; uint32_t v___y_14707_; uint32_t v___y_14717_; lean_object* v___x_14725_; uint8_t v___x_14726_; 
v___x_14702_ = lean_nat_add(v_baseA_14672_, v_k_14678_);
v___x_14703_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___x_14725_ = lean_array_get_size(v_A_14675_);
v___x_14726_ = lean_nat_dec_lt(v___x_14702_, v___x_14725_);
if (v___x_14726_ == 0)
{
lean_dec(v___x_14702_);
v___y_14717_ = v___x_14703_;
goto v___jp_14716_;
}
else
{
lean_object* v___x_14727_; uint32_t v___x_14728_; 
v___x_14727_ = lean_array_fget_borrowed(v_A_14675_, v___x_14702_);
lean_dec(v___x_14702_);
v___x_14728_ = lean_unbox_uint32(v___x_14727_);
v___y_14717_ = v___x_14728_;
goto v___jp_14716_;
}
v___jp_14704_:
{
float v_b0_14708_; lean_object* v___x_14709_; lean_object* v___x_14710_; lean_object* v___x_14711_; lean_object* v___x_14712_; uint8_t v___x_14713_; 
v_b0_14708_ = lean_float32_of_bits(v___y_14707_);
v___x_14709_ = lean_unsigned_to_nat(1u);
v___x_14710_ = lean_nat_add(v_baseB_14673_, v___x_14709_);
v___x_14711_ = lean_nat_add(v___x_14710_, v___y_14705_);
lean_dec(v___y_14705_);
lean_dec(v___x_14710_);
v___x_14712_ = lean_array_get_size(v_B_14676_);
v___x_14713_ = lean_nat_dec_lt(v___x_14711_, v___x_14712_);
if (v___x_14713_ == 0)
{
lean_dec(v___x_14711_);
v___y_14682_ = v___x_14709_;
v___y_14683_ = v_b0_14708_;
v___y_14684_ = v___y_14706_;
v___y_14685_ = v___x_14703_;
goto v___jp_14681_;
}
else
{
lean_object* v___x_14714_; uint32_t v___x_14715_; 
v___x_14714_ = lean_array_fget_borrowed(v_B_14676_, v___x_14711_);
lean_dec(v___x_14711_);
v___x_14715_ = lean_unbox_uint32(v___x_14714_);
v___y_14682_ = v___x_14709_;
v___y_14683_ = v_b0_14708_;
v___y_14684_ = v___y_14706_;
v___y_14685_ = v___x_14715_;
goto v___jp_14681_;
}
}
v___jp_14716_:
{
float v_a_14718_; lean_object* v___x_14719_; lean_object* v___x_14720_; lean_object* v___x_14721_; uint8_t v___x_14722_; 
v_a_14718_ = lean_float32_of_bits(v___y_14717_);
v___x_14719_ = lean_nat_mul(v_k_14678_, v_p_14674_);
v___x_14720_ = lean_nat_add(v_baseB_14673_, v___x_14719_);
v___x_14721_ = lean_array_get_size(v_B_14676_);
v___x_14722_ = lean_nat_dec_lt(v___x_14720_, v___x_14721_);
if (v___x_14722_ == 0)
{
lean_dec(v___x_14720_);
v___y_14705_ = v___x_14719_;
v___y_14706_ = v_a_14718_;
v___y_14707_ = v___x_14703_;
goto v___jp_14704_;
}
else
{
lean_object* v___x_14723_; uint32_t v___x_14724_; 
v___x_14723_ = lean_array_fget_borrowed(v_B_14676_, v___x_14720_);
lean_dec(v___x_14720_);
v___x_14724_ = lean_unbox_uint32(v___x_14723_);
v___y_14705_ = v___x_14719_;
v___y_14706_ = v_a_14718_;
v___y_14707_ = v___x_14724_;
goto v___jp_14704_;
}
}
}
v___jp_14681_:
{
float v_b1_14686_; lean_object* v___x_14687_; float v___x_14688_; float v___x_14689_; float v___x_14690_; float v___x_14691_; 
v_b1_14686_ = lean_float32_of_bits(v___y_14685_);
v___x_14687_ = lean_nat_add(v_k_14678_, v___y_14682_);
lean_dec(v_k_14678_);
v___x_14688_ = lean_float32_mul(v___y_14684_, v___y_14683_);
v___x_14689_ = lean_float32_add(v_s0_14679_, v___x_14688_);
v___x_14690_ = lean_float32_mul(v___y_14684_, v_b1_14686_);
v___x_14691_ = lean_float32_add(v_s1_14680_, v___x_14690_);
v_k_14678_ = v___x_14687_;
v_s0_14679_ = v___x_14689_;
v_s1_14680_ = v___x_14691_;
goto _start;
}
}
}
