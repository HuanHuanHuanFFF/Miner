LEAN_EXPORT lean_object* lp_competition_Submission_bmm(lean_object* v_batch_15269_, lean_object* v_m_15270_, lean_object* v_n_15271_, lean_object* v_p_15272_, lean_object* v_A_15273_, lean_object* v_B_15274_){
_start:
{
uint8_t v___y_15276_; lean_object* v___x_15287_; lean_object* v___x_15288_; uint8_t v___x_15289_; 
v___x_15287_ = lean_unsigned_to_nat(0u);
v___x_15288_ = lean_array_get_size(v_A_15273_);
v___x_15289_ = lean_nat_dec_lt(v___x_15287_, v___x_15288_);
if (v___x_15289_ == 0)
{
uint8_t v___x_15290_; 
v___x_15290_ = 1;
v___y_15276_ = v___x_15290_;
goto v___jp_15275_;
}
else
{
if (v___x_15289_ == 0)
{
v___y_15276_ = v___x_15289_;
goto v___jp_15275_;
}
else
{
size_t v___x_15291_; size_t v___x_15292_; uint8_t v___x_15293_; 
v___x_15291_ = ((size_t)0ULL);
v___x_15292_ = lean_usize_of_nat(v___x_15288_);
v___x_15293_ = lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00Submission_bmm_spec__1(v_A_15273_, v___x_15291_, v___x_15292_);
if (v___x_15293_ == 0)
{
v___y_15276_ = v___x_15289_;
goto v___jp_15275_;
}
else
{
lean_object* v___x_15294_; 
v___x_15294_ = lp_competition_Submission_R15PackedB2_dispatch(v_batch_15269_, v_m_15270_, v_n_15271_, v_p_15272_, v_A_15273_, v_B_15274_);
return v___x_15294_;
}
}
}
v___jp_15275_:
{
lean_object* v___x_15277_; lean_object* v___x_15278_; uint8_t v___x_15279_; 
v___x_15277_ = lean_unsigned_to_nat(0u);
v___x_15278_ = lean_array_get_size(v_B_15274_);
v___x_15279_ = lean_nat_dec_lt(v___x_15277_, v___x_15278_);
if (v___x_15279_ == 0)
{
lean_object* v___x_15280_; 
lean_dec_ref(v_B_15274_);
lean_dec_ref(v_A_15273_);
lean_dec(v_n_15271_);
v___x_15280_ = lp_competition_Submission_UnderflowZero_zeros(v_batch_15269_, v_m_15270_, v_p_15272_);
lean_dec(v_p_15272_);
lean_dec(v_m_15270_);
lean_dec(v_batch_15269_);
return v___x_15280_;
}
else
{
if (v___x_15279_ == 0)
{
lean_object* v___x_15281_; 
lean_dec_ref(v_B_15274_);
lean_dec_ref(v_A_15273_);
lean_dec(v_n_15271_);
v___x_15281_ = lp_competition_Submission_UnderflowZero_zeros(v_batch_15269_, v_m_15270_, v_p_15272_);
lean_dec(v_p_15272_);
lean_dec(v_m_15270_);
lean_dec(v_batch_15269_);
return v___x_15281_;
}
else
{
size_t v___x_15282_; size_t v___x_15283_; uint8_t v___x_15284_; 
v___x_15282_ = ((size_t)0ULL);
v___x_15283_ = lean_usize_of_nat(v___x_15278_);
v___x_15284_ = lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00Submission_bmm_spec__0(v___y_15276_, v_B_15274_, v___x_15282_, v___x_15283_);
if (v___x_15284_ == 0)
{
lean_object* v___x_15285_; 
lean_dec_ref(v_B_15274_);
lean_dec_ref(v_A_15273_);
lean_dec(v_n_15271_);
v___x_15285_ = lp_competition_Submission_UnderflowZero_zeros(v_batch_15269_, v_m_15270_, v_p_15272_);
lean_dec(v_p_15272_);
lean_dec(v_m_15270_);
lean_dec(v_batch_15269_);
return v___x_15285_;
}
else
{
lean_object* v___x_15286_; 
v___x_15286_ = lp_competition_Submission_R15PackedB2_dispatch(v_batch_15269_, v_m_15270_, v_n_15271_, v_p_15272_, v_A_15273_, v_B_15274_);
return v___x_15286_;
}
}
}
}
}
}
