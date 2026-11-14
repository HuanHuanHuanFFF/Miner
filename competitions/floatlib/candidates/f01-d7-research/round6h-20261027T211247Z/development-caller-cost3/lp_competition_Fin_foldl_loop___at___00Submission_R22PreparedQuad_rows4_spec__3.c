LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_R22PreparedQuad_rows4_spec__3(lean_object* v_n_17981_, lean_object* v_baseA_17982_, lean_object* v_baseB_17983_, lean_object* v_s_17984_, lean_object* v_p_17985_, lean_object* v_A_17986_, lean_object* v_B_17987_, lean_object* v_n_17988_, lean_object* v_x_17989_, lean_object* v_i_17990_){
_start:
{
uint8_t v___x_17991_; 
v___x_17991_ = lean_nat_dec_lt(v_i_17990_, v_n_17988_);
if (v___x_17991_ == 0)
{
lean_dec(v_i_17990_);
return v_x_17989_;
}
else
{
lean_object* v___x_17992_; float v_s3_17993_; lean_object* v___x_17994_; lean_object* v___x_17995_; lean_object* v___x_17996_; lean_object* v___x_17997_; uint32_t v___x_17998_; lean_object* v___x_17999_; lean_object* v___x_18000_; lean_object* v___x_18001_; lean_object* v___x_18002_; 
v___x_17992_ = lean_array_fget_borrowed(v_s_17984_, v_i_17990_);
v_s3_17993_ = lean_ctor_get_float32(v___x_17992_, 12);
v___x_17994_ = lean_unsigned_to_nat(3u);
v___x_17995_ = lean_nat_mul(v___x_17994_, v_n_17981_);
v___x_17996_ = lean_nat_add(v_baseA_17982_, v___x_17995_);
lean_dec(v___x_17995_);
v___x_17997_ = lean_nat_add(v_baseB_17983_, v_i_17990_);
v___x_17998_ = lp_competition_Submission_Packed10_finish(v_n_17981_, v___x_17996_, v___x_17997_, v_p_17985_, v_A_17986_, v_B_17987_, v_s3_17993_);
lean_dec(v___x_17997_);
lean_dec(v___x_17996_);
v___x_17999_ = lean_box_uint32(v___x_17998_);
v___x_18000_ = lean_array_push(v_x_17989_, v___x_17999_);
v___x_18001_ = lean_unsigned_to_nat(1u);
v___x_18002_ = lean_nat_add(v_i_17990_, v___x_18001_);
lean_dec(v_i_17990_);
v_x_17989_ = v___x_18000_;
v_i_17990_ = v___x_18002_;
goto _start;
}
}
}