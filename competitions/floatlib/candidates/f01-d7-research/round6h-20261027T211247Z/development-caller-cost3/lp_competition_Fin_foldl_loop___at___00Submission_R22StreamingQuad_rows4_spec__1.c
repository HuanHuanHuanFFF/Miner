LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_R22StreamingQuad_rows4_spec__1(lean_object* v_baseA_17400_, lean_object* v_n_17401_, lean_object* v_baseB_17402_, lean_object* v_s_17403_, lean_object* v_p_17404_, lean_object* v_A_17405_, lean_object* v_B_17406_, lean_object* v_n_17407_, lean_object* v_x_17408_, lean_object* v_i_17409_){
_start:
{
uint8_t v___x_17410_; 
v___x_17410_ = lean_nat_dec_lt(v_i_17409_, v_n_17407_);
if (v___x_17410_ == 0)
{
lean_dec(v_i_17409_);
return v_x_17408_;
}
else
{
lean_object* v___x_17411_; float v_s1_17412_; lean_object* v___x_17413_; lean_object* v___x_17414_; uint32_t v___x_17415_; lean_object* v___x_17416_; lean_object* v___x_17417_; lean_object* v___x_17418_; lean_object* v___x_17419_; 
v___x_17411_ = lean_array_fget_borrowed(v_s_17403_, v_i_17409_);
v_s1_17412_ = lean_ctor_get_float32(v___x_17411_, 4);
v___x_17413_ = lean_nat_add(v_baseA_17400_, v_n_17401_);
v___x_17414_ = lean_nat_add(v_baseB_17402_, v_i_17409_);
v___x_17415_ = lp_competition_Submission_Packed10_finish(v_n_17401_, v___x_17413_, v___x_17414_, v_p_17404_, v_A_17405_, v_B_17406_, v_s1_17412_);
lean_dec(v___x_17414_);
lean_dec(v___x_17413_);
v___x_17416_ = lean_box_uint32(v___x_17415_);
v___x_17417_ = lean_array_push(v_x_17408_, v___x_17416_);
v___x_17418_ = lean_unsigned_to_nat(1u);
v___x_17419_ = lean_nat_add(v_i_17409_, v___x_17418_);
lean_dec(v_i_17409_);
v_x_17408_ = v___x_17417_;
v_i_17409_ = v___x_17419_;
goto _start;
}
}
}