LEAN_EXPORT uint32_t lp_competition_R24DotBankHarness_sumRemaining(lean_object* v_out_487_, lean_object* v_index_488_, uint32_t v_acc_489_, lean_object* v_remaining_490_)
{
_start:
{
lean_object* v_zero_491_; uint8_t v_isZero_492_; 
v_zero_491_ = lean_unsigned_to_nat(0u);
v_isZero_492_ = lean_nat_dec_eq(v_remaining_490_, v_zero_491_);
if (v_isZero_492_ == 1)
{
lean_dec(v_remaining_490_);
lean_dec(v_index_488_);
return v_acc_489_;
}
else
{
lean_object* v_one_493_; lean_object* v_n_494_; lean_object* v___x_495_; lean_object* v___x_496_; lean_object* v___x_497_; uint32_t v___x_498_; uint32_t v___x_499_; 
v_one_493_ = lean_unsigned_to_nat(1u);
v_n_494_ = lean_nat_sub(v_remaining_490_, v_one_493_);
lean_dec(v_remaining_490_);
v___x_495_ = lean_nat_add(v_index_488_, v_one_493_);
v___x_496_ = lp_competition_R24DotBankHarness_sumRemaining___boxed__const__1;
v___x_497_ = lean_array_get_borrowed(v___x_496_, v_out_487_, v_index_488_);
lean_dec(v_index_488_);
v___x_498_ = lean_unbox_uint32(v___x_497_);
v___x_499_ = lean_uint32_add(v_acc_489_, v___x_498_);
v_index_488_ = v___x_495_;
v_acc_489_ = v___x_499_;
v_remaining_490_ = v_n_494_;
goto _start;
}
}
}