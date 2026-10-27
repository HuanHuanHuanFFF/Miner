LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_R22StreamingQuad_rows4_spec__0(lean_object* v_baseB_17335_, lean_object* v_s_17336_, lean_object* v_n_17337_, lean_object* v_baseA_17338_, lean_object* v_p_17339_, lean_object* v_A_17340_, lean_object* v_B_17341_, lean_object* v_n_17342_, lean_object* v_x_17343_, lean_object* v_i_17344_){
_start:
{
uint8_t v___x_17345_; 
v___x_17345_ = lean_nat_dec_lt(v_i_17344_, v_n_17342_);
if (v___x_17345_ == 0)
{
lean_dec(v_i_17344_);
return v_x_17343_;
}
else
{
lean_object* v___x_17346_; float v_s0_17347_; lean_object* v___x_17348_; uint32_t v___x_17349_; lean_object* v___x_17350_; lean_object* v___x_17351_; lean_object* v___x_17352_; lean_object* v___x_17353_; 
v___x_17346_ = lean_array_fget_borrowed(v_s_17336_, v_i_17344_);
v_s0_17347_ = lean_ctor_get_float32(v___x_17346_, 0);
v___x_17348_ = lean_nat_add(v_baseB_17335_, v_i_17344_);
v___x_17349_ = lp_competition_Submission_Packed10_finish(v_n_17337_, v_baseA_17338_, v___x_17348_, v_p_17339_, v_A_17340_, v_B_17341_, v_s0_17347_);
lean_dec(v___x_17348_);
v___x_17350_ = lean_box_uint32(v___x_17349_);
v___x_17351_ = lean_array_push(v_x_17343_, v___x_17350_);
v___x_17352_ = lean_unsigned_to_nat(1u);
v___x_17353_ = lean_nat_add(v_i_17344_, v___x_17352_);
lean_dec(v_i_17344_);
v_x_17343_ = v___x_17351_;
v_i_17344_ = v___x_17353_;
goto _start;
}
}
}