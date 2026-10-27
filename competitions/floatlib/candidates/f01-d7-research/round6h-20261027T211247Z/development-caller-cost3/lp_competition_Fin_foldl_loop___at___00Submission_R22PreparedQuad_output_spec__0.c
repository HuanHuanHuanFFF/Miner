LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_R22PreparedQuad_output_spec__0(lean_object* v_m_18214_, lean_object* v_n_18215_, lean_object* v_p_18216_, lean_object* v_A_18217_, lean_object* v_B_18218_, lean_object* v_prepared_18219_, lean_object* v_n_18220_, lean_object* v_x_18221_, lean_object* v_i_18222_){
_start:
{
uint8_t v___x_18223_; 
v___x_18223_ = lean_nat_dec_lt(v_i_18222_, v_n_18220_);
if (v___x_18223_ == 0)
{
lean_dec(v_i_18222_);
lean_dec(v_p_18216_);
return v_x_18221_;
}
else
{
lean_object* v___x_18224_; lean_object* v___x_18225_; lean_object* v___x_18226_; 
lean_inc(v_p_18216_);
v___x_18224_ = lp_competition_Submission_R22PreparedQuad_rows(v_m_18214_, v_n_18215_, v_p_18216_, v_i_18222_, v_A_18217_, v_B_18218_, v_prepared_18219_, v_x_18221_);
v___x_18225_ = lean_unsigned_to_nat(1u);
v___x_18226_ = lean_nat_add(v_i_18222_, v___x_18225_);
lean_dec(v_i_18222_);
v_x_18221_ = v___x_18224_;
v_i_18222_ = v___x_18226_;
goto _start;
}
}
}