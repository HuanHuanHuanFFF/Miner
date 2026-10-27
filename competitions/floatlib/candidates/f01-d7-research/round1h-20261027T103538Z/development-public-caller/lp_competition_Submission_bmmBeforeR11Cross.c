LEAN_EXPORT lean_object* lp_competition_Submission_bmmBeforeR11Cross(lean_object* v_batch_14206_, lean_object* v_m_14207_, lean_object* v_n_14208_, lean_object* v_p_14209_, lean_object* v_A_14210_, lean_object* v_B_14211_){
_start:
{
lean_object* v___x_14217_; uint8_t v___x_14218_; 
v___x_14217_ = lean_unsigned_to_nat(4u);
v___x_14218_ = lean_nat_dec_le(v_n_14208_, v___x_14217_);
if (v___x_14218_ == 0)
{
goto v___jp_14212_;
}
else
{
lean_object* v___x_14219_; uint8_t v___x_14220_; 
v___x_14219_ = lean_unsigned_to_nat(2u);
v___x_14220_ = lean_nat_dec_lt(v___x_14219_, v_p_14209_);
if (v___x_14220_ == 0)
{
goto v___jp_14212_;
}
else
{
lean_object* v___x_14221_; 
v___x_14221_ = lp_competition_Submission_R19DCRawPair_core(v_batch_14206_, v_m_14207_, v_n_14208_, v_p_14209_, v_A_14210_, v_B_14211_);
lean_dec_ref(v_B_14211_);
lean_dec_ref(v_A_14210_);
lean_dec(v_p_14209_);
lean_dec(v_n_14208_);
lean_dec(v_m_14207_);
lean_dec(v_batch_14206_);
return v___x_14221_;
}
}
v___jp_14212_:
{
lean_object* v___x_14213_; uint8_t v___x_14214_; 
v___x_14213_ = lean_unsigned_to_nat(8u);
v___x_14214_ = lean_nat_dec_le(v_p_14209_, v___x_14213_);
if (v___x_14214_ == 0)
{
lean_object* v___x_14215_; 
v___x_14215_ = lp_competition_Submission_bmmBeforeDirectRows(v_batch_14206_, v_m_14207_, v_n_14208_, v_p_14209_, v_A_14210_, v_B_14211_);
return v___x_14215_;
}
else
{
lean_object* v___x_14216_; 
v___x_14216_ = lp_competition_Submission_R19DCRawPair_core(v_batch_14206_, v_m_14207_, v_n_14208_, v_p_14209_, v_A_14210_, v_B_14211_);
lean_dec_ref(v_B_14211_);
lean_dec_ref(v_A_14210_);
lean_dec(v_p_14209_);
lean_dec(v_n_14208_);
lean_dec(v_m_14207_);
lean_dec(v_batch_14206_);
return v___x_14216_;
}
}
}
}
