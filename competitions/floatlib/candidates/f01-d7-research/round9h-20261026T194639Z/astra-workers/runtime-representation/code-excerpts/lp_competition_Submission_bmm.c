LEAN_EXPORT lean_object* lp_competition_Submission_bmm(lean_object* v_batch_14554_, lean_object* v_m_14555_, lean_object* v_n_14556_, lean_object* v_p_14557_, lean_object* v_A_14558_, lean_object* v_B_14559_){
_start:
{
uint8_t v___y_14561_; lean_object* v___x_14572_; lean_object* v___x_14573_; uint8_t v___x_14574_; 
v___x_14572_ = lean_unsigned_to_nat(0u);
v___x_14573_ = lean_array_get_size(v_A_14558_);
v___x_14574_ = lean_nat_dec_lt(v___x_14572_, v___x_14573_);
if (v___x_14574_ == 0)
{
uint8_t v___x_14575_; 
v___x_14575_ = 1;
v___y_14561_ = v___x_14575_;
goto v___jp_14560_;
}
else
{
if (v___x_14574_ == 0)
{
v___y_14561_ = v___x_14574_;
goto v___jp_14560_;
}
else
{
size_t v___x_14576_; size_t v___x_14577_; uint8_t v___x_14578_; 
v___x_14576_ = ((size_t)0ULL);
v___x_14577_ = lean_usize_of_nat(v___x_14573_);
v___x_14578_ = lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00Submission_bmm_spec__1(v_A_14558_, v___x_14576_, v___x_14577_);
if (v___x_14578_ == 0)
{
v___y_14561_ = v___x_14574_;
goto v___jp_14560_;
}
else
{
lean_object* v___x_14579_; 
v___x_14579_ = lp_competition_Submission_R15PackedB2_dispatch(v_batch_14554_, v_m_14555_, v_n_14556_, v_p_14557_, v_A_14558_, v_B_14559_);
return v___x_14579_;
}
}
}
v___jp_14560_:
{
lean_object* v___x_14562_; lean_object* v___x_14563_; uint8_t v___x_14564_; 
v___x_14562_ = lean_unsigned_to_nat(0u);
v___x_14563_ = lean_array_get_size(v_B_14559_);
v___x_14564_ = lean_nat_dec_lt(v___x_14562_, v___x_14563_);
if (v___x_14564_ == 0)
{
lean_object* v___x_14565_; 
lean_dec_ref(v_B_14559_);
lean_dec_ref(v_A_14558_);
lean_dec(v_n_14556_);
v___x_14565_ = lp_competition_Submission_UnderflowZero_zeros(v_batch_14554_, v_m_14555_, v_p_14557_);
lean_dec(v_p_14557_);
lean_dec(v_m_14555_);
lean_dec(v_batch_14554_);
return v___x_14565_;
}
else
{
if (v___x_14564_ == 0)
{
lean_object* v___x_14566_; 
lean_dec_ref(v_B_14559_);
lean_dec_ref(v_A_14558_);
lean_dec(v_n_14556_);
v___x_14566_ = lp_competition_Submission_UnderflowZero_zeros(v_batch_14554_, v_m_14555_, v_p_14557_);
lean_dec(v_p_14557_);
lean_dec(v_m_14555_);
lean_dec(v_batch_14554_);
return v___x_14566_;
}
else
{
size_t v___x_14567_; size_t v___x_14568_; uint8_t v___x_14569_; 
v___x_14567_ = ((size_t)0ULL);
v___x_14568_ = lean_usize_of_nat(v___x_14563_);
v___x_14569_ = lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00Submission_bmm_spec__0(v___y_14561_, v_B_14559_, v___x_14567_, v___x_14568_);
if (v___x_14569_ == 0)
{
lean_object* v___x_14570_; 
lean_dec_ref(v_B_14559_);
lean_dec_ref(v_A_14558_);
lean_dec(v_n_14556_);
v___x_14570_ = lp_competition_Submission_UnderflowZero_zeros(v_batch_14554_, v_m_14555_, v_p_14557_);
lean_dec(v_p_14557_);
lean_dec(v_m_14555_);
lean_dec(v_batch_14554_);
return v___x_14570_;
}
else
{
lean_object* v___x_14571_; 
v___x_14571_ = lp_competition_Submission_R15PackedB2_dispatch(v_batch_14554_, v_m_14555_, v_n_14556_, v_p_14557_, v_A_14558_, v_B_14559_);
return v___x_14571_;
}
}
}
}
}
}
