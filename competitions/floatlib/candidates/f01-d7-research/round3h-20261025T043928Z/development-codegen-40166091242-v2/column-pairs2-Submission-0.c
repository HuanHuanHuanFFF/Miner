LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_rse(uint64_t v_value_3481_, uint64_t v_shift_3482_){
_start:
{
uint64_t v_quotient_3483_; uint64_t v___x_3484_; uint64_t v___x_3485_; uint64_t v___x_3486_; uint64_t v_remainder_3487_; uint64_t v___x_3488_; uint64_t v_half_3489_; uint8_t v___x_3490_; 
v_quotient_3483_ = lean_uint64_shift_right(v_value_3481_, v_shift_3482_);
v___x_3484_ = 1ULL;
v___x_3485_ = lean_uint64_shift_left(v___x_3484_, v_shift_3482_);
v___x_3486_ = lean_uint64_sub(v___x_3485_, v___x_3484_);
v_remainder_3487_ = lean_uint64_land(v_value_3481_, v___x_3486_);
v___x_3488_ = lean_uint64_sub(v_shift_3482_, v___x_3484_);
v_half_3489_ = lean_uint64_shift_left(v___x_3484_, v___x_3488_);
v___x_3490_ = lean_uint64_dec_lt(v_remainder_3487_, v_half_3489_);
if (v___x_3490_ == 0)
{
uint8_t v___x_3491_; 
v___x_3491_ = lean_uint64_dec_lt(v_half_3489_, v_remainder_3487_);
if (v___x_3491_ == 0)
{
uint64_t v___x_3492_; uint64_t v___x_3493_; uint8_t v___x_3494_; 
v___x_3492_ = lean_uint64_land(v_quotient_3483_, v___x_3484_);
v___x_3493_ = 0ULL;
v___x_3494_ = lean_uint64_dec_eq(v___x_3492_, v___x_3493_);
if (v___x_3494_ == 0)
{
uint64_t v___x_3495_; 
v___x_3495_ = lean_uint64_add(v_quotient_3483_, v___x_3484_);
return v___x_3495_;
}
else
{
return v_quotient_3483_;
}
}
else
{
uint64_t v___x_3496_; 
v___x_3496_ = lean_uint64_add(v_quotient_3483_, v___x_3484_);
return v___x_3496_;
}
}
else
{
return v_quotient_3483_;
}
}
}