LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_R22StreamingQuad_groups_spec__0(lean_object* v_b_17455_, lean_object* v_m_17456_, lean_object* v_n_17457_, lean_object* v_p_17458_, lean_object* v_A_17459_, lean_object* v_B_17460_, lean_object* v_n_17461_, lean_object* v_x_17462_, lean_object* v_i_17463_){
_start:
{
uint8_t v___x_17464_; 
v___x_17464_ = lean_nat_dec_lt(v_i_17463_, v_n_17461_);
if (v___x_17464_ == 0)
{
lean_dec(v_i_17463_);
lean_dec(v_p_17458_);
return v_x_17462_;
}
else
{
lean_object* v___x_17465_; lean_object* v___x_17466_; lean_object* v___x_17467_; lean_object* v___x_17468_; lean_object* v___x_17469_; lean_object* v___x_17470_; lean_object* v___x_17471_; lean_object* v___x_17472_; lean_object* v___x_17473_; lean_object* v___x_17474_; 
v___x_17465_ = lean_unsigned_to_nat(4u);
v___x_17466_ = lean_nat_mul(v_b_17455_, v_m_17456_);
v___x_17467_ = lean_nat_mul(v___x_17465_, v_i_17463_);
v___x_17468_ = lean_nat_add(v___x_17466_, v___x_17467_);
lean_dec(v___x_17467_);
lean_dec(v___x_17466_);
v___x_17469_ = lean_nat_mul(v___x_17468_, v_n_17457_);
lean_dec(v___x_17468_);
v___x_17470_ = lean_nat_mul(v_b_17455_, v_n_17457_);
v___x_17471_ = lean_nat_mul(v___x_17470_, v_p_17458_);
lean_dec(v___x_17470_);
lean_inc(v_p_17458_);
v___x_17472_ = lp_competition_Submission_R22StreamingQuad_rows4(v_p_17458_, v_n_17457_, v___x_17469_, v___x_17471_, v_A_17459_, v_B_17460_, v_x_17462_);
lean_dec(v___x_17471_);
lean_dec(v___x_17469_);
v___x_17473_ = lean_unsigned_to_nat(1u);
v___x_17474_ = lean_nat_add(v_i_17463_, v___x_17473_);
lean_dec(v_i_17463_);
v_x_17462_ = v___x_17472_;
v_i_17463_ = v___x_17474_;
goto _start;
}
}
}