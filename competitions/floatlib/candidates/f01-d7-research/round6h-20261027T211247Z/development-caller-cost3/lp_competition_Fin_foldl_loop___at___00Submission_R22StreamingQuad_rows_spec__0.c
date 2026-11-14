LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_R22StreamingQuad_rows_spec__0(lean_object* v_b_17505_, lean_object* v_m_17506_, lean_object* v_p_17507_, lean_object* v_n_17508_, lean_object* v_A_17509_, lean_object* v_B_17510_, lean_object* v_n_17511_, lean_object* v_x_17512_, lean_object* v_i_17513_){
_start:
{
uint8_t v___x_17514_; 
v___x_17514_ = lean_nat_dec_lt(v_i_17513_, v_n_17511_);
if (v___x_17514_ == 0)
{
lean_dec(v_i_17513_);
return v_x_17512_;
}
else
{
lean_object* v___x_17515_; lean_object* v___x_17516_; lean_object* v___x_17517_; lean_object* v___x_17518_; lean_object* v___x_17519_; lean_object* v___x_17520_; lean_object* v___x_17521_; lean_object* v___x_17522_; lean_object* v___x_17523_; lean_object* v___x_17524_; lean_object* v___x_17525_; lean_object* v___x_17526_; lean_object* v___x_17527_; uint32_t v___x_17528_; lean_object* v___x_17529_; lean_object* v___x_17530_; lean_object* v___x_17531_; lean_object* v___x_17532_; 
v___x_17515_ = lean_unsigned_to_nat(4u);
v___x_17516_ = lean_nat_mul(v_b_17505_, v_m_17506_);
v___x_17517_ = lean_unsigned_to_nat(2u);
v___x_17518_ = lean_nat_shiftr(v_m_17506_, v___x_17517_);
v___x_17519_ = lean_nat_mul(v___x_17518_, v___x_17515_);
lean_dec(v___x_17518_);
v___x_17520_ = lean_nat_add(v___x_17516_, v___x_17519_);
lean_dec(v___x_17519_);
lean_dec(v___x_17516_);
v___x_17521_ = lean_nat_div(v_i_17513_, v_p_17507_);
v___x_17522_ = lean_nat_add(v___x_17520_, v___x_17521_);
lean_dec(v___x_17521_);
lean_dec(v___x_17520_);
v___x_17523_ = lean_nat_mul(v___x_17522_, v_n_17508_);
lean_dec(v___x_17522_);
v___x_17524_ = lean_nat_mul(v_b_17505_, v_n_17508_);
v___x_17525_ = lean_nat_mul(v___x_17524_, v_p_17507_);
lean_dec(v___x_17524_);
v___x_17526_ = lean_nat_mod(v_i_17513_, v_p_17507_);
v___x_17527_ = lean_nat_add(v___x_17525_, v___x_17526_);
lean_dec(v___x_17526_);
lean_dec(v___x_17525_);
v___x_17528_ = lp_competition_Submission_NativeFinal_dot(v_n_17508_, v___x_17523_, v___x_17527_, v_p_17507_, v_A_17509_, v_B_17510_);
lean_dec(v___x_17527_);
lean_dec(v___x_17523_);
v___x_17529_ = lean_box_uint32(v___x_17528_);
v___x_17530_ = lean_array_push(v_x_17512_, v___x_17529_);
v___x_17531_ = lean_unsigned_to_nat(1u);
v___x_17532_ = lean_nat_add(v_i_17513_, v___x_17531_);
lean_dec(v_i_17513_);
v_x_17512_ = v___x_17530_;
v_i_17513_ = v___x_17532_;
goto _start;
}
}
}