LEAN_EXPORT uint64_t lp_competition_Submission_R15BranchlessNormal_roundedWord(uint32_t v_u_7730_, uint32_t v_v_7731_){
_start:
{
uint32_t v___x_7732_; uint32_t v___x_7733_; uint32_t v___x_7734_; uint32_t v___x_7735_; uint64_t v___x_7736_; uint32_t v___x_7737_; uint32_t v___x_7738_; uint64_t v___x_7739_; uint64_t v_product_7740_; uint64_t v___x_7741_; uint64_t v___x_7742_; uint64_t v___x_7743_; uint64_t v___x_7744_; uint8_t v___x_7745_; 
v___x_7732_ = 8388607;
v___x_7733_ = lean_uint32_land(v_u_7730_, v___x_7732_);
v___x_7734_ = 8388608;
v___x_7735_ = lean_uint32_lor(v___x_7733_, v___x_7734_);
v___x_7736_ = lean_uint32_to_uint64(v___x_7735_);
v___x_7737_ = lean_uint32_land(v_v_7731_, v___x_7732_);
v___x_7738_ = lean_uint32_lor(v___x_7737_, v___x_7734_);
v___x_7739_ = lean_uint32_to_uint64(v___x_7738_);
v_product_7740_ = lean_uint64_mul(v___x_7736_, v___x_7739_);
v___x_7741_ = 23ULL;
v___x_7742_ = 47ULL;
v___x_7743_ = lean_uint64_shift_right(v_product_7740_, v___x_7742_);
v___x_7744_ = lean_uint64_add(v___x_7741_, v___x_7743_);
v___x_7745_ = lean_uint64_dec_eq(v___x_7744_, v___x_7741_);
if (v___x_7745_ == 0)
{
uint64_t v___x_7746_; uint64_t v_q_7747_; uint64_t v___y_7749_; uint64_t v___y_7750_; uint64_t v___y_7751_; uint64_t v___x_7755_; uint64_t v___y_7757_; uint64_t v___y_7758_; uint64_t v___x_7762_; uint64_t v_r_7763_; uint64_t v_half_7764_; uint8_t v___x_7765_; uint8_t v___x_7766_; uint64_t v___y_7768_; 
v___x_7746_ = 24ULL;
v_q_7747_ = lean_uint64_shift_right(v_product_7740_, v___x_7746_);
v___x_7755_ = 1ULL;
v___x_7762_ = 16777215ULL;
v_r_7763_ = lean_uint64_land(v_product_7740_, v___x_7762_);
v_half_7764_ = 8388608ULL;
v___x_7765_ = lean_uint64_dec_lt(v_r_7763_, v_half_7764_);
v___x_7766_ = lean_uint64_dec_lt(v_half_7764_, v_r_7763_);
if (v___x_7765_ == 0)
{
v___y_7768_ = v___x_7755_;
goto v___jp_7767_;
}
else
{
uint64_t v___x_7770_; 
v___x_7770_ = 0ULL;
v___y_7768_ = v___x_7770_;
goto v___jp_7767_;
}
v___jp_7748_:
{
uint64_t v___x_7752_; uint64_t v___x_7753_; uint64_t v___x_7754_; 
v___x_7752_ = lean_uint64_lor(v___y_7749_, v___y_7751_);
v___x_7753_ = lean_uint64_land(v___y_7750_, v___x_7752_);
v___x_7754_ = lean_uint64_add(v_q_7747_, v___x_7753_);
return v___x_7754_;
}
v___jp_7756_:
{
uint64_t v___x_7759_; uint64_t v___x_7760_; uint8_t v___x_7761_; 
v___x_7759_ = lean_uint64_land(v_q_7747_, v___x_7755_);
v___x_7760_ = 0ULL;
v___x_7761_ = lean_uint64_dec_eq(v___x_7759_, v___x_7760_);
if (v___x_7761_ == 0)
{
v___y_7749_ = v___y_7758_;
v___y_7750_ = v___y_7757_;
v___y_7751_ = v___x_7755_;
goto v___jp_7748_;
}
else
{
v___y_7749_ = v___y_7758_;
v___y_7750_ = v___y_7757_;
v___y_7751_ = v___x_7760_;
goto v___jp_7748_;
}
}
v___jp_7767_:
{
if (v___x_7766_ == 0)
{
uint64_t v___x_7769_; 
v___x_7769_ = 0ULL;
v___y_7757_ = v___y_7768_;
v___y_7758_ = v___x_7769_;
goto v___jp_7756_;
}
else
{
v___y_7757_ = v___y_7768_;
v___y_7758_ = v___x_7755_;
goto v___jp_7756_;
}
}
}
else
{
uint64_t v_q_7771_; uint64_t v___y_7773_; uint64_t v___y_7774_; uint64_t v___y_7775_; uint64_t v___x_7779_; uint64_t v___y_7781_; uint64_t v___y_7782_; uint64_t v___x_7786_; uint64_t v_r_7787_; uint64_t v_half_7788_; uint8_t v___x_7789_; uint8_t v___x_7790_; uint64_t v___y_7792_; 
v_q_7771_ = lean_uint64_shift_right(v_product_7740_, v___x_7741_);
v___x_7779_ = 1ULL;
v___x_7786_ = 8388607ULL;
v_r_7787_ = lean_uint64_land(v_product_7740_, v___x_7786_);
v_half_7788_ = 4194304ULL;
v___x_7789_ = lean_uint64_dec_lt(v_r_7787_, v_half_7788_);
v___x_7790_ = lean_uint64_dec_lt(v_half_7788_, v_r_7787_);
if (v___x_7789_ == 0)
{
v___y_7792_ = v___x_7779_;
goto v___jp_7791_;
}
else
{
uint64_t v___x_7794_; 
v___x_7794_ = 0ULL;
v___y_7792_ = v___x_7794_;
goto v___jp_7791_;
}
v___jp_7772_:
{
uint64_t v___x_7776_; uint64_t v___x_7777_; uint64_t v___x_7778_; 
v___x_7776_ = lean_uint64_lor(v___y_7773_, v___y_7775_);
v___x_7777_ = lean_uint64_land(v___y_7774_, v___x_7776_);
v___x_7778_ = lean_uint64_add(v_q_7771_, v___x_7777_);
return v___x_7778_;
}
v___jp_7780_:
{
uint64_t v___x_7783_; uint64_t v___x_7784_; uint8_t v___x_7785_; 
v___x_7783_ = lean_uint64_land(v_q_7771_, v___x_7779_);
v___x_7784_ = 0ULL;
v___x_7785_ = lean_uint64_dec_eq(v___x_7783_, v___x_7784_);
if (v___x_7785_ == 0)
{
v___y_7773_ = v___y_7782_;
v___y_7774_ = v___y_7781_;
v___y_7775_ = v___x_7779_;
goto v___jp_7772_;
}
else
{
v___y_7773_ = v___y_7782_;
v___y_7774_ = v___y_7781_;
v___y_7775_ = v___x_7784_;
goto v___jp_7772_;
}
}
v___jp_7791_:
{
if (v___x_7790_ == 0)
{
uint64_t v___x_7793_; 
v___x_7793_ = 0ULL;
v___y_7781_ = v___y_7792_;
v___y_7782_ = v___x_7793_;
goto v___jp_7780_;
}
else
{
v___y_7781_ = v___y_7792_;
v___y_7782_ = v___x_7779_;
goto v___jp_7780_;
}
}
}
}
}