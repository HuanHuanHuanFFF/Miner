LEAN_EXPORT lean_object* lp_competition_Submission_R15PackedB2_dispatch(lean_object* v_batch_15201_, lean_object* v_m_15202_, lean_object* v_n_15203_, lean_object* v_p_15204_, lean_object* v_A_15205_, lean_object* v_B_15206_){
_start:
{
lean_object* v___x_15207_; uint8_t v___x_15208_; 
v___x_15207_ = lean_unsigned_to_nat(2u);
v___x_15208_ = lean_nat_dec_le(v___x_15207_, v_p_15204_);
if (v___x_15208_ == 0)
{
lean_object* v___x_15209_; 
v___x_15209_ = lp_competition_Submission_R14ThinBCache_dispatch(v_batch_15201_, v_m_15202_, v_n_15203_, v_p_15204_, v_A_15205_, v_B_15206_);
return v___x_15209_;
}
else
{
lean_object* v___x_15210_; uint8_t v___x_15211_; 
v___x_15210_ = lean_unsigned_to_nat(8u);
v___x_15211_ = lean_nat_dec_le(v_p_15204_, v___x_15210_);
if (v___x_15211_ == 0)
{
lean_object* v___x_15212_; 
v___x_15212_ = lp_competition_Submission_R14ThinBCache_dispatch(v_batch_15201_, v_m_15202_, v_n_15203_, v_p_15204_, v_A_15205_, v_B_15206_);
return v___x_15212_;
}
else
{
lean_object* v___x_15213_; uint8_t v___x_15214_; 
v___x_15213_ = lean_unsigned_to_nat(1u);
v___x_15214_ = lean_nat_dec_lt(v___x_15213_, v_n_15203_);
if (v___x_15214_ == 0)
{
lean_object* v___x_15215_; 
v___x_15215_ = lp_competition_Submission_R14ThinBCache_dispatch(v_batch_15201_, v_m_15202_, v_n_15203_, v_p_15204_, v_A_15205_, v_B_15206_);
return v___x_15215_;
}
else
{
lean_object* v___x_15216_; uint8_t v___x_15217_; 
v___x_15216_ = lean_unsigned_to_nat(4u);
v___x_15217_ = lean_nat_dec_le(v___x_15216_, v_m_15202_);
if (v___x_15217_ == 0)
{
lean_object* v___x_15218_; 
v___x_15218_ = lp_competition_Submission_R14ThinBCache_dispatch(v_batch_15201_, v_m_15202_, v_n_15203_, v_p_15204_, v_A_15205_, v_B_15206_);
return v___x_15218_;
}
else
{
lean_object* v___x_15219_; 
v___x_15219_ = lp_competition_Submission_R15PackedB2_output(v_batch_15201_, v_m_15202_, v_n_15203_, v_p_15204_, v_A_15205_, v_B_15206_);
lean_dec_ref(v_A_15205_);
lean_dec(v_m_15202_);
lean_dec(v_batch_15201_);
return v___x_15219_;
}
}
}
}
}
}
