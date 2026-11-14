LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_R22StreamingQuad_rows4_spec__3(lean_object* v_n_17366_, lean_object* v_baseA_17367_, lean_object* v_baseB_17368_, lean_object* v_s_17369_, lean_object* v_p_17370_, lean_object* v_A_17371_, lean_object* v_B_17372_, lean_object* v_n_17373_, lean_object* v_x_17374_, lean_object* v_i_17375_){
_start:
{
uint8_t v___x_17376_; 
v___x_17376_ = lean_nat_dec_lt(v_i_17375_, v_n_17373_);
if (v___x_17376_ == 0)
{
lean_dec(v_i_17375_);
return v_x_17374_;
}
else
{
lean_object* v___x_17377_; float v_s3_17378_; lean_object* v___x_17379_; lean_object* v___x_17380_; lean_object* v___x_17381_; lean_object* v___x_17382_; uint32_t v___x_17383_; lean_object* v___x_17384_; lean_object* v___x_17385_; lean_object* v___x_17386_; lean_object* v___x_17387_; 
v___x_17377_ = lean_array_fget_borrowed(v_s_17369_, v_i_17375_);
v_s3_17378_ = lean_ctor_get_float32(v___x_17377_, 12);
v___x_17379_ = lean_unsigned_to_nat(3u);
v___x_17380_ = lean_nat_mul(v___x_17379_, v_n_17366_);
v___x_17381_ = lean_nat_add(v_baseA_17367_, v___x_17380_);
lean_dec(v___x_17380_);
v___x_17382_ = lean_nat_add(v_baseB_17368_, v_i_17375_);
v___x_17383_ = lp_competition_Submission_Packed10_finish(v_n_17366_, v___x_17381_, v___x_17382_, v_p_17370_, v_A_17371_, v_B_17372_, v_s3_17378_);
lean_dec(v___x_17382_);
lean_dec(v___x_17381_);
v___x_17384_ = lean_box_uint32(v___x_17383_);
v___x_17385_ = lean_array_push(v_x_17374_, v___x_17384_);
v___x_17386_ = lean_unsigned_to_nat(1u);
v___x_17387_ = lean_nat_add(v_i_17375_, v___x_17386_);
lean_dec(v_i_17375_);
v_x_17374_ = v___x_17385_;
v_i_17375_ = v___x_17387_;
goto _start;
}
}
}