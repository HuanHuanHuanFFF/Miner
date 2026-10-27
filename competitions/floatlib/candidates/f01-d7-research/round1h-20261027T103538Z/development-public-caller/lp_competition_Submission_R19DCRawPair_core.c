LEAN_EXPORT lean_object* lp_competition_Submission_R19DCRawPair_core(lean_object* v_batch_14187_, lean_object* v_m_14188_, lean_object* v_n_14189_, lean_object* v_p_14190_, lean_object* v_A_14191_, lean_object* v_B_14192_){
_start:
{
lean_object* v___x_14193_; uint8_t v___x_14194_; 
v___x_14193_ = lean_unsigned_to_nat(1u);
v___x_14194_ = lean_nat_dec_le(v_n_14189_, v___x_14193_);
if (v___x_14194_ == 0)
{
uint8_t v___x_14195_; 
v___x_14195_ = lean_nat_dec_le(v_p_14190_, v___x_14193_);
if (v___x_14195_ == 0)
{
lean_object* v___x_14196_; 
v___x_14196_ = lp_competition_Submission_R19DCRawPair_output(v_batch_14187_, v_m_14188_, v_n_14189_, v_p_14190_, v_A_14191_, v_B_14192_);
return v___x_14196_;
}
else
{
lean_object* v___x_14197_; 
v___x_14197_ = lp_competition_Submission_DirectContinuous_output(v_batch_14187_, v_m_14188_, v_n_14189_, v_p_14190_, v_A_14191_, v_B_14192_);
return v___x_14197_;
}
}
else
{
lean_object* v___x_14198_; 
v___x_14198_ = lp_competition_Submission_DirectContinuous_output(v_batch_14187_, v_m_14188_, v_n_14189_, v_p_14190_, v_A_14191_, v_B_14192_);
return v___x_14198_;
}
}
}
