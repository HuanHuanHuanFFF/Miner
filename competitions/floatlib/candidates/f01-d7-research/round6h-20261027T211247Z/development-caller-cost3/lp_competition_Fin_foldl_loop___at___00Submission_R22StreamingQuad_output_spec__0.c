LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_R22StreamingQuad_output_spec__0(lean_object* v_m_17565_, lean_object* v_n_17566_, lean_object* v_p_17567_, lean_object* v_A_17568_, lean_object* v_B_17569_, lean_object* v_n_17570_, lean_object* v_x_17571_, lean_object* v_i_17572_){
_start:
{
uint8_t v___x_17573_; 
v___x_17573_ = lean_nat_dec_lt(v_i_17572_, v_n_17570_);
if (v___x_17573_ == 0)
{
lean_dec(v_i_17572_);
lean_dec(v_p_17567_);
return v_x_17571_;
}
else
{
lean_object* v___x_17574_; lean_object* v___x_17575_; lean_object* v___x_17576_; 
lean_inc(v_p_17567_);
v___x_17574_ = lp_competition_Submission_R22StreamingQuad_rows(v_m_17565_, v_n_17566_, v_p_17567_, v_i_17572_, v_A_17568_, v_B_17569_, v_x_17571_);
v___x_17575_ = lean_unsigned_to_nat(1u);
v___x_17576_ = lean_nat_add(v_i_17572_, v___x_17575_);
lean_dec(v_i_17572_);
v_x_17571_ = v___x_17574_;
v_i_17572_ = v___x_17576_;
goto _start;
}
}
}