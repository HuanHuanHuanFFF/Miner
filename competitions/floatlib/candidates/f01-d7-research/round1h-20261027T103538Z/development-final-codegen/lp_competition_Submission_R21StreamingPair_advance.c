LEAN_EXPORT lean_object* lp_competition_Submission_R21StreamingPair_advance(lean_object* v_p_14691_, lean_object* v_baseA0_14692_, lean_object* v_baseA1_14693_, lean_object* v_baseB_14694_, lean_object* v_A_14695_, lean_object* v_B_14696_, lean_object* v_k_14697_, lean_object* v_s_14698_){
_start:
{
lean_object* v___x_14699_; uint32_t v___x_14700_; float v___y_14702_; uint32_t v___y_14703_; uint32_t v___y_14716_; lean_object* v___x_14723_; uint8_t v___x_14724_; 
v___x_14699_ = lean_nat_add(v_baseA0_14692_, v_k_14697_);
v___x_14700_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___x_14723_ = lean_array_get_size(v_A_14695_);
v___x_14724_ = lean_nat_dec_lt(v___x_14699_, v___x_14723_);
if (v___x_14724_ == 0)
{
lean_dec(v___x_14699_);
v___y_14716_ = v___x_14700_;
goto v___jp_14715_;
}
else
{
lean_object* v___x_14725_; uint32_t v___x_14726_; 
v___x_14725_ = lean_array_fget_borrowed(v_A_14695_, v___x_14699_);
lean_dec(v___x_14699_);
v___x_14726_ = lean_unbox_uint32(v___x_14725_);
v___y_14716_ = v___x_14726_;
goto v___jp_14715_;
}
v___jp_14701_:
{
float v_a1_14704_; lean_object* v___x_14705_; lean_object* v_rowB_14706_; lean_object* v___x_14707_; lean_object* v___x_14708_; lean_object* v___x_14709_; lean_object* v___f_14710_; lean_object* v___x_14711_; size_t v_sz_14712_; size_t v___x_14713_; lean_object* v___x_14714_; 
v_a1_14704_ = lean_float32_of_bits(v___y_14703_);
v___x_14705_ = lean_nat_mul(v_k_14697_, v_p_14691_);
v_rowB_14706_ = lean_nat_add(v_baseB_14694_, v___x_14705_);
lean_dec(v___x_14705_);
v___x_14707_ = lean_box_float32(v___y_14702_);
v___x_14708_ = lean_box_float32(v_a1_14704_);
v___x_14709_ = lp_competition_Submission_UnderflowZero_zeros___boxed__const__1;
v___f_14710_ = lean_alloc_closure((void*)(lp_competition_Submission_R21StreamingPair_advance___lam__0___boxed), 8, 5);
lean_closure_set(v___f_14710_, 0, v___x_14707_);
lean_closure_set(v___f_14710_, 1, v___x_14708_);
lean_closure_set(v___f_14710_, 2, v_rowB_14706_);
lean_closure_set(v___f_14710_, 3, v_B_14696_);
lean_closure_set(v___f_14710_, 4, v___x_14709_);
v___x_14711_ = ((lean_object*)(lp_competition_Submission_R21StreamingPair_advance___closed__9));
v_sz_14712_ = lean_array_size(v_s_14698_);
v___x_14713_ = ((size_t)0ULL);
v___x_14714_ = l___private_Init_Data_Array_Basic_0__Array_mapFinIdxMUnsafe_map___redArg(v___x_14711_, v___f_14710_, v_sz_14712_, v___x_14713_, v_s_14698_);
return v___x_14714_;
}
v___jp_14715_:
{
float v_a0_14717_; lean_object* v___x_14718_; lean_object* v___x_14719_; uint8_t v___x_14720_; 
v_a0_14717_ = lean_float32_of_bits(v___y_14716_);
v___x_14718_ = lean_nat_add(v_baseA1_14693_, v_k_14697_);
v___x_14719_ = lean_array_get_size(v_A_14695_);
v___x_14720_ = lean_nat_dec_lt(v___x_14718_, v___x_14719_);
if (v___x_14720_ == 0)
{
lean_dec(v___x_14718_);
v___y_14702_ = v_a0_14717_;
v___y_14703_ = v___x_14700_;
goto v___jp_14701_;
}
else
{
lean_object* v___x_14721_; uint32_t v___x_14722_; 
v___x_14721_ = lean_array_fget_borrowed(v_A_14695_, v___x_14718_);
lean_dec(v___x_14718_);
v___x_14722_ = lean_unbox_uint32(v___x_14721_);
v___y_14702_ = v_a0_14717_;
v___y_14703_ = v___x_14722_;
goto v___jp_14701_;
}
}
}
}
