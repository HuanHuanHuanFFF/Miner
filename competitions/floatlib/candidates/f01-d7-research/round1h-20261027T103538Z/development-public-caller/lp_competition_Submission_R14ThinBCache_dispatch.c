LEAN_EXPORT lean_object* lp_competition_Submission_R14ThinBCache_dispatch(lean_object* v_batch_14452_, lean_object* v_m_14453_, lean_object* v_n_14454_, lean_object* v_p_14455_, lean_object* v_A_14456_, lean_object* v_B_14457_){
_start:
{
lean_object* v___x_14458_; uint8_t v___x_14459_; 
v___x_14458_ = lean_unsigned_to_nat(4u);
v___x_14459_ = lean_nat_dec_le(v___x_14458_, v_m_14453_);
if (v___x_14459_ == 0)
{
lean_object* v___x_14460_; 
v___x_14460_ = lp_competition_Submission_bmmBeforeR11Cross(v_batch_14452_, v_m_14453_, v_n_14454_, v_p_14455_, v_A_14456_, v_B_14457_);
return v___x_14460_;
}
else
{
lean_object* v___x_14461_; uint8_t v___x_14462_; 
v___x_14461_ = lean_unsigned_to_nat(1u);
v___x_14462_ = lean_nat_dec_lt(v___x_14461_, v_n_14454_);
if (v___x_14462_ == 0)
{
lean_object* v___x_14463_; 
v___x_14463_ = lp_competition_Submission_bmmBeforeR11Cross(v_batch_14452_, v_m_14453_, v_n_14454_, v_p_14455_, v_A_14456_, v_B_14457_);
return v___x_14463_;
}
else
{
lean_object* v___x_14464_; uint8_t v___x_14465_; 
v___x_14464_ = lean_unsigned_to_nat(0u);
v___x_14465_ = lean_nat_dec_lt(v___x_14464_, v_p_14455_);
if (v___x_14465_ == 0)
{
lean_object* v___x_14466_; 
v___x_14466_ = lp_competition_Submission_bmmBeforeR11Cross(v_batch_14452_, v_m_14453_, v_n_14454_, v_p_14455_, v_A_14456_, v_B_14457_);
return v___x_14466_;
}
else
{
lean_object* v___x_14467_; uint8_t v___x_14468_; 
v___x_14467_ = lean_unsigned_to_nat(2u);
v___x_14468_ = lean_nat_dec_le(v_p_14455_, v___x_14467_);
if (v___x_14468_ == 0)
{
lean_object* v___x_14469_; 
v___x_14469_ = lp_competition_Submission_bmmBeforeR11Cross(v_batch_14452_, v_m_14453_, v_n_14454_, v_p_14455_, v_A_14456_, v_B_14457_);
return v___x_14469_;
}
else
{
lean_object* v___x_14470_; 
v___x_14470_ = lp_competition_Submission_R14ThinBCache_output(v_batch_14452_, v_m_14453_, v_n_14454_, v_p_14455_, v_A_14456_, v_B_14457_);
lean_dec_ref(v_A_14456_);
lean_dec(v_p_14455_);
lean_dec(v_n_14454_);
lean_dec(v_m_14453_);
lean_dec(v_batch_14452_);
return v___x_14470_;
}
}
}
}
}
}
