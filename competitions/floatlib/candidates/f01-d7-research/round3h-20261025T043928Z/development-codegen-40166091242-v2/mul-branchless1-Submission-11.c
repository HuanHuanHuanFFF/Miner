LEAN_EXPORT uint32_t lp_competition_Submission_R15BranchlessNormal_core(uint32_t v_u_7801_, uint32_t v_v_7802_){
_start:
{
uint32_t v___y_7804_; uint32_t v___y_7805_; uint32_t v___y_7806_; uint32_t v___y_7807_; uint32_t v___y_7808_; uint32_t v___y_7809_; uint64_t v___y_7816_; uint32_t v___y_7817_; uint64_t v___y_7818_; uint64_t v___y_7819_; uint8_t v___y_7820_; uint64_t v___y_7839_; uint32_t v___y_7840_; uint64_t v___y_7841_; uint64_t v___y_7842_; uint64_t v___y_7845_; uint32_t v___y_7846_; uint64_t v___y_7847_; uint64_t v___y_7848_; uint8_t v___y_7849_; uint64_t v___y_7852_; uint32_t v___x_7869_; uint32_t v___x_7870_; uint32_t v___x_7871_; uint32_t v___x_7872_; uint64_t v___x_7873_; uint32_t v___x_7874_; uint32_t v___x_7875_; uint64_t v___x_7876_; uint64_t v_product_7877_; uint64_t v___x_7878_; uint64_t v___x_7879_; uint64_t v___x_7880_; uint64_t v___x_7881_; uint8_t v___x_7882_; 
v___x_7869_ = 8388607;
v___x_7870_ = lean_uint32_land(v_u_7801_, v___x_7869_);
v___x_7871_ = 8388608;
v___x_7872_ = lean_uint32_lor(v___x_7870_, v___x_7871_);
v___x_7873_ = lean_uint32_to_uint64(v___x_7872_);
v___x_7874_ = lean_uint32_land(v_v_7802_, v___x_7869_);
v___x_7875_ = lean_uint32_lor(v___x_7874_, v___x_7871_);
v___x_7876_ = lean_uint32_to_uint64(v___x_7875_);
v_product_7877_ = lean_uint64_mul(v___x_7873_, v___x_7876_);
v___x_7878_ = 23ULL;
v___x_7879_ = 47ULL;
v___x_7880_ = lean_uint64_shift_right(v_product_7877_, v___x_7879_);
v___x_7881_ = lean_uint64_add(v___x_7878_, v___x_7880_);
v___x_7882_ = lean_uint64_dec_eq(v___x_7881_, v___x_7878_);
if (v___x_7882_ == 0)
{
uint64_t v___x_7883_; uint64_t v_q_7884_; uint64_t v___y_7886_; uint64_t v___y_7887_; uint64_t v___y_7888_; uint64_t v___x_7892_; uint64_t v___y_7894_; uint64_t v___y_7895_; uint64_t v___x_7899_; uint64_t v_r_7900_; uint64_t v_half_7901_; uint8_t v___x_7902_; uint8_t v___x_7903_; uint64_t v___y_7905_; 
v___x_7883_ = 24ULL;
v_q_7884_ = lean_uint64_shift_right(v_product_7877_, v___x_7883_);
v___x_7892_ = 1ULL;
v___x_7899_ = 16777215ULL;
v_r_7900_ = lean_uint64_land(v_product_7877_, v___x_7899_);
v_half_7901_ = 8388608ULL;
v___x_7902_ = lean_uint64_dec_lt(v_r_7900_, v_half_7901_);
v___x_7903_ = lean_uint64_dec_lt(v_half_7901_, v_r_7900_);
if (v___x_7902_ == 0)
{
v___y_7905_ = v___x_7892_;
goto v___jp_7904_;
}
else
{
uint64_t v___x_7907_; 
v___x_7907_ = 0ULL;
v___y_7905_ = v___x_7907_;
goto v___jp_7904_;
}
v___jp_7885_:
{
uint64_t v___x_7889_; uint64_t v___x_7890_; uint64_t v___x_7891_; 
v___x_7889_ = lean_uint64_lor(v___y_7886_, v___y_7888_);
v___x_7890_ = lean_uint64_land(v___y_7887_, v___x_7889_);
v___x_7891_ = lean_uint64_add(v_q_7884_, v___x_7890_);
v___y_7852_ = v___x_7891_;
goto v___jp_7851_;
}
v___jp_7893_:
{
uint64_t v___x_7896_; uint64_t v___x_7897_; uint8_t v___x_7898_; 
v___x_7896_ = lean_uint64_land(v_q_7884_, v___x_7892_);
v___x_7897_ = 0ULL;
v___x_7898_ = lean_uint64_dec_eq(v___x_7896_, v___x_7897_);
if (v___x_7898_ == 0)
{
v___y_7886_ = v___y_7895_;
v___y_7887_ = v___y_7894_;
v___y_7888_ = v___x_7892_;
goto v___jp_7885_;
}
else
{
v___y_7886_ = v___y_7895_;
v___y_7887_ = v___y_7894_;
v___y_7888_ = v___x_7897_;
goto v___jp_7885_;
}
}
v___jp_7904_:
{
if (v___x_7903_ == 0)
{
uint64_t v___x_7906_; 
v___x_7906_ = 0ULL;
v___y_7894_ = v___y_7905_;
v___y_7895_ = v___x_7906_;
goto v___jp_7893_;
}
else
{
v___y_7894_ = v___y_7905_;
v___y_7895_ = v___x_7892_;
goto v___jp_7893_;
}
}
}
else
{
uint64_t v_q_7908_; uint64_t v___y_7910_; uint64_t v___y_7911_; uint64_t v___y_7912_; uint64_t v___x_7916_; uint64_t v___y_7918_; uint64_t v___y_7919_; uint64_t v___x_7923_; uint64_t v_r_7924_; uint64_t v_half_7925_; uint8_t v___x_7926_; uint8_t v___x_7927_; uint64_t v___y_7929_; 
v_q_7908_ = lean_uint64_shift_right(v_product_7877_, v___x_7878_);
v___x_7916_ = 1ULL;
v___x_7923_ = 8388607ULL;
v_r_7924_ = lean_uint64_land(v_product_7877_, v___x_7923_);
v_half_7925_ = 4194304ULL;
v___x_7926_ = lean_uint64_dec_lt(v_r_7924_, v_half_7925_);
v___x_7927_ = lean_uint64_dec_lt(v_half_7925_, v_r_7924_);
if (v___x_7926_ == 0)
{
v___y_7929_ = v___x_7916_;
goto v___jp_7928_;
}
else
{
uint64_t v___x_7931_; 
v___x_7931_ = 0ULL;
v___y_7929_ = v___x_7931_;
goto v___jp_7928_;
}
v___jp_7909_:
{
uint64_t v___x_7913_; uint64_t v___x_7914_; uint64_t v___x_7915_; 
v___x_7913_ = lean_uint64_lor(v___y_7910_, v___y_7912_);
v___x_7914_ = lean_uint64_land(v___y_7911_, v___x_7913_);
v___x_7915_ = lean_uint64_add(v_q_7908_, v___x_7914_);
v___y_7852_ = v___x_7915_;
goto v___jp_7851_;
}
v___jp_7917_:
{
uint64_t v___x_7920_; uint64_t v___x_7921_; uint8_t v___x_7922_; 
v___x_7920_ = lean_uint64_land(v_q_7908_, v___x_7916_);
v___x_7921_ = 0ULL;
v___x_7922_ = lean_uint64_dec_eq(v___x_7920_, v___x_7921_);
if (v___x_7922_ == 0)
{
v___y_7910_ = v___y_7919_;
v___y_7911_ = v___y_7918_;
v___y_7912_ = v___x_7916_;
goto v___jp_7909_;
}
else
{
v___y_7910_ = v___y_7919_;
v___y_7911_ = v___y_7918_;
v___y_7912_ = v___x_7921_;
goto v___jp_7909_;
}
}
v___jp_7928_:
{
if (v___x_7927_ == 0)
{
uint64_t v___x_7930_; 
v___x_7930_ = 0ULL;
v___y_7918_ = v___y_7929_;
v___y_7919_ = v___x_7930_;
goto v___jp_7917_;
}
else
{
v___y_7918_ = v___y_7929_;
v___y_7919_ = v___x_7916_;
goto v___jp_7917_;
}
}
}
v___jp_7803_:
{
uint32_t v___x_7810_; uint32_t v___x_7811_; uint32_t v___x_7812_; uint32_t v___x_7813_; uint32_t v___x_7814_; 
v___x_7810_ = lean_uint32_land(v___y_7805_, v___y_7804_);
v___x_7811_ = lean_uint32_shift_left(v___x_7810_, v___y_7806_);
v___x_7812_ = lean_uint32_lor(v___y_7809_, v___x_7811_);
v___x_7813_ = lean_uint32_land(v___y_7808_, v___y_7807_);
v___x_7814_ = lean_uint32_lor(v___x_7812_, v___x_7813_);
return v___x_7814_;
}
v___jp_7815_:
{
uint32_t v___x_7821_; uint32_t v___x_7822_; uint32_t v___x_7823_; uint32_t v___x_7824_; uint32_t v___x_7825_; uint32_t v___x_7826_; uint32_t v___x_7827_; uint32_t v___x_7828_; uint32_t v___x_7829_; uint32_t v___x_7830_; uint32_t v___x_7831_; uint32_t v___x_7832_; uint32_t v___x_7833_; uint32_t v___x_7834_; uint32_t v___x_7835_; 
v___x_7821_ = 23;
v___x_7822_ = lean_uint32_shift_right(v_u_7801_, v___x_7821_);
v___x_7823_ = 255;
v___x_7824_ = lean_uint32_land(v___x_7822_, v___x_7823_);
v___x_7825_ = lean_uint32_shift_right(v_v_7802_, v___x_7821_);
v___x_7826_ = lean_uint32_land(v___x_7825_, v___x_7823_);
v___x_7827_ = lean_uint32_add(v___x_7824_, v___x_7826_);
v___x_7828_ = 127;
v___x_7829_ = lean_uint32_sub(v___x_7827_, v___x_7828_);
v___x_7830_ = lean_uint64_to_uint32(v___y_7818_);
v___x_7831_ = lean_uint32_add(v___x_7829_, v___x_7830_);
v___x_7832_ = lean_uint64_to_uint32(v___y_7816_);
v___x_7833_ = lean_uint32_add(v___x_7831_, v___x_7832_);
v___x_7834_ = lean_uint64_to_uint32(v___y_7819_);
v___x_7835_ = lean_uint32_land(v___x_7834_, v___y_7817_);
if (v___y_7820_ == 0)
{
uint32_t v___x_7836_; 
v___x_7836_ = 0;
v___y_7804_ = v___x_7823_;
v___y_7805_ = v___x_7833_;
v___y_7806_ = v___x_7821_;
v___y_7807_ = v___y_7817_;
v___y_7808_ = v___x_7835_;
v___y_7809_ = v___x_7836_;
goto v___jp_7803_;
}
else
{
uint32_t v___x_7837_; 
v___x_7837_ = 2147483648;
v___y_7804_ = v___x_7823_;
v___y_7805_ = v___x_7833_;
v___y_7806_ = v___x_7821_;
v___y_7807_ = v___y_7817_;
v___y_7808_ = v___x_7835_;
v___y_7809_ = v___x_7837_;
goto v___jp_7803_;
}
}
v___jp_7838_:
{
uint8_t v___x_7843_; 
v___x_7843_ = 0;
v___y_7816_ = v___y_7839_;
v___y_7817_ = v___y_7840_;
v___y_7818_ = v___y_7841_;
v___y_7819_ = v___y_7842_;
v___y_7820_ = v___x_7843_;
goto v___jp_7815_;
}
v___jp_7844_:
{
if (v___y_7849_ == 0)
{
uint8_t v___x_7850_; 
v___x_7850_ = 1;
v___y_7816_ = v___y_7845_;
v___y_7817_ = v___y_7846_;
v___y_7818_ = v___y_7847_;
v___y_7819_ = v___y_7848_;
v___y_7820_ = v___x_7850_;
goto v___jp_7815_;
}
else
{
v___y_7839_ = v___y_7845_;
v___y_7840_ = v___y_7846_;
v___y_7841_ = v___y_7847_;
v___y_7842_ = v___y_7848_;
goto v___jp_7838_;
}
}
v___jp_7851_:
{
uint32_t v___x_7853_; uint32_t v___x_7854_; uint32_t v___x_7855_; uint32_t v___x_7856_; uint64_t v___x_7857_; uint32_t v___x_7858_; uint32_t v___x_7859_; uint64_t v___x_7860_; uint64_t v___x_7861_; uint64_t v___x_7862_; uint64_t v_high_7863_; uint64_t v___x_7864_; uint64_t v_carry_7865_; uint32_t v___x_7866_; uint8_t v___x_7867_; uint8_t v___x_7868_; 
v___x_7853_ = 8388607;
v___x_7854_ = lean_uint32_land(v_u_7801_, v___x_7853_);
v___x_7855_ = 8388608;
v___x_7856_ = lean_uint32_lor(v___x_7854_, v___x_7855_);
v___x_7857_ = lean_uint32_to_uint64(v___x_7856_);
v___x_7858_ = lean_uint32_land(v_v_7802_, v___x_7853_);
v___x_7859_ = lean_uint32_lor(v___x_7858_, v___x_7855_);
v___x_7860_ = lean_uint32_to_uint64(v___x_7859_);
v___x_7861_ = lean_uint64_mul(v___x_7857_, v___x_7860_);
v___x_7862_ = 47ULL;
v_high_7863_ = lean_uint64_shift_right(v___x_7861_, v___x_7862_);
v___x_7864_ = 24ULL;
v_carry_7865_ = lean_uint64_shift_right(v___y_7852_, v___x_7864_);
v___x_7866_ = 2147483648;
v___x_7867_ = lean_uint32_dec_le(v___x_7866_, v_u_7801_);
v___x_7868_ = lean_uint32_dec_le(v___x_7866_, v_v_7802_);
if (v___x_7867_ == 0)
{
if (v___x_7868_ == 0)
{
v___y_7839_ = v_carry_7865_;
v___y_7840_ = v___x_7853_;
v___y_7841_ = v_high_7863_;
v___y_7842_ = v___y_7852_;
goto v___jp_7838_;
}
else
{
v___y_7845_ = v_carry_7865_;
v___y_7846_ = v___x_7853_;
v___y_7847_ = v_high_7863_;
v___y_7848_ = v___y_7852_;
v___y_7849_ = v___x_7867_;
goto v___jp_7844_;
}
}
else
{
v___y_7845_ = v_carry_7865_;
v___y_7846_ = v___x_7853_;
v___y_7847_ = v_high_7863_;
v___y_7848_ = v___y_7852_;
v___y_7849_ = v___x_7868_;
goto v___jp_7844_;
}
}
}
}