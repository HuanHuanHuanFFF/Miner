LEAN_EXPORT uint32_t lp_competition_Submission_R14DIntegerNormal_core(uint32_t v_u_7263_, uint32_t v_v_7264_){
_start:
{
uint32_t v___y_7266_; uint32_t v___y_7267_; uint32_t v___y_7268_; uint32_t v___y_7269_; uint32_t v___y_7270_; uint32_t v___y_7271_; uint32_t v___y_7278_; uint32_t v___y_7279_; uint8_t v___y_7280_; uint32_t v___y_7281_; uint32_t v___y_7282_; uint64_t v___y_7283_; uint64_t v___y_7289_; uint32_t v___y_7290_; uint64_t v___y_7291_; uint32_t v___y_7292_; uint32_t v___y_7293_; uint8_t v___y_7294_; uint32_t v___y_7295_; uint64_t v___y_7296_; uint8_t v___y_7325_; uint8_t v___y_7374_; uint32_t v___x_7376_; uint8_t v___x_7377_; uint8_t v___x_7378_; 
v___x_7376_ = 2147483648;
v___x_7377_ = lean_uint32_dec_le(v___x_7376_, v_u_7263_);
v___x_7378_ = lean_uint32_dec_le(v___x_7376_, v_v_7264_);
if (v___x_7377_ == 0)
{
if (v___x_7378_ == 0)
{
goto v___jp_7371_;
}
else
{
v___y_7374_ = v___x_7377_;
goto v___jp_7373_;
}
}
else
{
v___y_7374_ = v___x_7378_;
goto v___jp_7373_;
}
v___jp_7265_:
{
uint32_t v___x_7272_; uint32_t v___x_7273_; uint32_t v___x_7274_; uint32_t v___x_7275_; uint32_t v___x_7276_; 
v___x_7272_ = lean_uint32_land(v___y_7270_, v___y_7268_);
v___x_7273_ = lean_uint32_shift_left(v___x_7272_, v___y_7267_);
v___x_7274_ = lean_uint32_lor(v___y_7271_, v___x_7273_);
v___x_7275_ = lean_uint32_land(v___y_7266_, v___y_7269_);
v___x_7276_ = lean_uint32_lor(v___x_7274_, v___x_7275_);
return v___x_7276_;
}
v___jp_7277_:
{
uint32_t v___x_7284_; uint32_t v___x_7285_; 
v___x_7284_ = lean_uint64_to_uint32(v___y_7283_);
v___x_7285_ = lean_uint32_land(v___x_7284_, v___y_7282_);
if (v___y_7280_ == 0)
{
uint32_t v___x_7286_; 
v___x_7286_ = 0;
v___y_7266_ = v___x_7285_;
v___y_7267_ = v___y_7278_;
v___y_7268_ = v___y_7279_;
v___y_7269_ = v___y_7282_;
v___y_7270_ = v___y_7281_;
v___y_7271_ = v___x_7286_;
goto v___jp_7265_;
}
else
{
uint32_t v___x_7287_; 
v___x_7287_ = 2147483648;
v___y_7266_ = v___x_7285_;
v___y_7267_ = v___y_7278_;
v___y_7268_ = v___y_7279_;
v___y_7269_ = v___y_7282_;
v___y_7270_ = v___y_7281_;
v___y_7271_ = v___x_7287_;
goto v___jp_7265_;
}
}
v___jp_7288_:
{
uint64_t v___x_7297_; uint64_t v___x_7298_; uint32_t v___x_7299_; uint32_t v___x_7300_; uint64_t v___x_7301_; uint64_t v___x_7302_; uint64_t v___x_7303_; uint8_t v___x_7304_; 
v___x_7297_ = 24ULL;
v___x_7298_ = lean_uint64_shift_right(v___y_7296_, v___x_7297_);
v___x_7299_ = lean_uint64_to_uint32(v___x_7298_);
v___x_7300_ = lean_uint32_add(v___y_7290_, v___x_7299_);
v___x_7301_ = 23ULL;
v___x_7302_ = lean_uint64_add(v___x_7301_, v___y_7291_);
v___x_7303_ = 0ULL;
v___x_7304_ = lean_uint64_dec_eq(v___x_7302_, v___x_7303_);
if (v___x_7304_ == 0)
{
uint64_t v___x_7305_; uint8_t v___x_7306_; 
v___x_7305_ = 64ULL;
v___x_7306_ = lean_uint64_dec_lt(v___x_7302_, v___x_7305_);
if (v___x_7306_ == 0)
{
uint8_t v___x_7307_; 
v___x_7307_ = lean_uint64_dec_eq(v___x_7302_, v___x_7305_);
if (v___x_7307_ == 0)
{
v___y_7278_ = v___y_7292_;
v___y_7279_ = v___y_7293_;
v___y_7280_ = v___y_7294_;
v___y_7281_ = v___x_7300_;
v___y_7282_ = v___y_7295_;
v___y_7283_ = v___x_7303_;
goto v___jp_7277_;
}
else
{
uint64_t v___x_7308_; uint8_t v___x_7309_; 
v___x_7308_ = 9223372036854775808ULL;
v___x_7309_ = lean_uint64_dec_lt(v___x_7308_, v___y_7289_);
if (v___x_7309_ == 0)
{
v___y_7278_ = v___y_7292_;
v___y_7279_ = v___y_7293_;
v___y_7280_ = v___y_7294_;
v___y_7281_ = v___x_7300_;
v___y_7282_ = v___y_7295_;
v___y_7283_ = v___x_7303_;
goto v___jp_7277_;
}
else
{
uint64_t v___x_7310_; 
v___x_7310_ = 1ULL;
v___y_7278_ = v___y_7292_;
v___y_7279_ = v___y_7293_;
v___y_7280_ = v___y_7294_;
v___y_7281_ = v___x_7300_;
v___y_7282_ = v___y_7295_;
v___y_7283_ = v___x_7310_;
goto v___jp_7277_;
}
}
}
else
{
uint64_t v_quotient_7311_; uint64_t v___x_7312_; uint64_t v___x_7313_; uint64_t v___x_7314_; uint64_t v_remainder_7315_; uint64_t v___x_7316_; uint64_t v_half_7317_; uint8_t v___x_7318_; 
v_quotient_7311_ = lean_uint64_shift_right(v___y_7289_, v___x_7302_);
v___x_7312_ = 1ULL;
v___x_7313_ = lean_uint64_shift_left(v___x_7312_, v___x_7302_);
v___x_7314_ = lean_uint64_sub(v___x_7313_, v___x_7312_);
v_remainder_7315_ = lean_uint64_land(v___y_7289_, v___x_7314_);
v___x_7316_ = lean_uint64_sub(v___x_7302_, v___x_7312_);
v_half_7317_ = lean_uint64_shift_left(v___x_7312_, v___x_7316_);
v___x_7318_ = lean_uint64_dec_lt(v_remainder_7315_, v_half_7317_);
if (v___x_7318_ == 0)
{
uint8_t v___x_7319_; 
v___x_7319_ = lean_uint64_dec_lt(v_half_7317_, v_remainder_7315_);
if (v___x_7319_ == 0)
{
uint64_t v___x_7320_; uint8_t v___x_7321_; 
v___x_7320_ = lean_uint64_land(v_quotient_7311_, v___x_7312_);
v___x_7321_ = lean_uint64_dec_eq(v___x_7320_, v___x_7303_);
if (v___x_7321_ == 0)
{
uint64_t v___x_7322_; 
v___x_7322_ = lean_uint64_add(v_quotient_7311_, v___x_7312_);
v___y_7278_ = v___y_7292_;
v___y_7279_ = v___y_7293_;
v___y_7280_ = v___y_7294_;
v___y_7281_ = v___x_7300_;
v___y_7282_ = v___y_7295_;
v___y_7283_ = v___x_7322_;
goto v___jp_7277_;
}
else
{
v___y_7278_ = v___y_7292_;
v___y_7279_ = v___y_7293_;
v___y_7280_ = v___y_7294_;
v___y_7281_ = v___x_7300_;
v___y_7282_ = v___y_7295_;
v___y_7283_ = v_quotient_7311_;
goto v___jp_7277_;
}
}
else
{
uint64_t v___x_7323_; 
v___x_7323_ = lean_uint64_add(v_quotient_7311_, v___x_7312_);
v___y_7278_ = v___y_7292_;
v___y_7279_ = v___y_7293_;
v___y_7280_ = v___y_7294_;
v___y_7281_ = v___x_7300_;
v___y_7282_ = v___y_7295_;
v___y_7283_ = v___x_7323_;
goto v___jp_7277_;
}
}
else
{
v___y_7278_ = v___y_7292_;
v___y_7279_ = v___y_7293_;
v___y_7280_ = v___y_7294_;
v___y_7281_ = v___x_7300_;
v___y_7282_ = v___y_7295_;
v___y_7283_ = v_quotient_7311_;
goto v___jp_7277_;
}
}
}
else
{
v___y_7278_ = v___y_7292_;
v___y_7279_ = v___y_7293_;
v___y_7280_ = v___y_7294_;
v___y_7281_ = v___x_7300_;
v___y_7282_ = v___y_7295_;
v___y_7283_ = v___y_7289_;
goto v___jp_7277_;
}
}
v___jp_7324_:
{
uint32_t v___x_7326_; uint32_t v___x_7327_; uint32_t v___x_7328_; uint32_t v___x_7329_; uint32_t v___x_7330_; uint32_t v___x_7331_; uint32_t v___x_7332_; uint32_t v___x_7333_; uint32_t v___x_7334_; uint32_t v___x_7335_; uint32_t v___x_7336_; uint32_t v___x_7337_; uint32_t v___x_7338_; uint64_t v___x_7339_; uint32_t v___x_7340_; uint32_t v___x_7341_; uint64_t v___x_7342_; uint64_t v___x_7343_; uint64_t v___x_7344_; uint64_t v___x_7345_; uint32_t v___x_7346_; uint32_t v___x_7347_; uint64_t v___x_7348_; uint64_t v___x_7349_; uint64_t v___x_7350_; uint8_t v___x_7351_; 
v___x_7326_ = 23;
v___x_7327_ = lean_uint32_shift_right(v_u_7263_, v___x_7326_);
v___x_7328_ = 255;
v___x_7329_ = lean_uint32_land(v___x_7327_, v___x_7328_);
v___x_7330_ = lean_uint32_shift_right(v_v_7264_, v___x_7326_);
v___x_7331_ = lean_uint32_land(v___x_7330_, v___x_7328_);
v___x_7332_ = lean_uint32_add(v___x_7329_, v___x_7331_);
v___x_7333_ = 127;
v___x_7334_ = lean_uint32_sub(v___x_7332_, v___x_7333_);
v___x_7335_ = 8388607;
v___x_7336_ = lean_uint32_land(v_u_7263_, v___x_7335_);
v___x_7337_ = 8388608;
v___x_7338_ = lean_uint32_lor(v___x_7336_, v___x_7337_);
v___x_7339_ = lean_uint32_to_uint64(v___x_7338_);
v___x_7340_ = lean_uint32_land(v_v_7264_, v___x_7335_);
v___x_7341_ = lean_uint32_lor(v___x_7340_, v___x_7337_);
v___x_7342_ = lean_uint32_to_uint64(v___x_7341_);
v___x_7343_ = lean_uint64_mul(v___x_7339_, v___x_7342_);
v___x_7344_ = 47ULL;
v___x_7345_ = lean_uint64_shift_right(v___x_7343_, v___x_7344_);
v___x_7346_ = lean_uint64_to_uint32(v___x_7345_);
v___x_7347_ = lean_uint32_add(v___x_7334_, v___x_7346_);
v___x_7348_ = 23ULL;
v___x_7349_ = lean_uint64_add(v___x_7348_, v___x_7345_);
v___x_7350_ = 0ULL;
v___x_7351_ = lean_uint64_dec_eq(v___x_7349_, v___x_7350_);
if (v___x_7351_ == 0)
{
uint64_t v___x_7352_; uint8_t v___x_7353_; 
v___x_7352_ = 64ULL;
v___x_7353_ = lean_uint64_dec_lt(v___x_7349_, v___x_7352_);
if (v___x_7353_ == 0)
{
uint8_t v___x_7354_; 
v___x_7354_ = lean_uint64_dec_eq(v___x_7349_, v___x_7352_);
if (v___x_7354_ == 0)
{
v___y_7289_ = v___x_7343_;
v___y_7290_ = v___x_7347_;
v___y_7291_ = v___x_7345_;
v___y_7292_ = v___x_7326_;
v___y_7293_ = v___x_7328_;
v___y_7294_ = v___y_7325_;
v___y_7295_ = v___x_7335_;
v___y_7296_ = v___x_7350_;
goto v___jp_7288_;
}
else
{
uint64_t v___x_7355_; uint8_t v___x_7356_; 
v___x_7355_ = 9223372036854775808ULL;
v___x_7356_ = lean_uint64_dec_lt(v___x_7355_, v___x_7343_);
if (v___x_7356_ == 0)
{
v___y_7289_ = v___x_7343_;
v___y_7290_ = v___x_7347_;
v___y_7291_ = v___x_7345_;
v___y_7292_ = v___x_7326_;
v___y_7293_ = v___x_7328_;
v___y_7294_ = v___y_7325_;
v___y_7295_ = v___x_7335_;
v___y_7296_ = v___x_7350_;
goto v___jp_7288_;
}
else
{
uint64_t v___x_7357_; 
v___x_7357_ = 1ULL;
v___y_7289_ = v___x_7343_;
v___y_7290_ = v___x_7347_;
v___y_7291_ = v___x_7345_;
v___y_7292_ = v___x_7326_;
v___y_7293_ = v___x_7328_;
v___y_7294_ = v___y_7325_;
v___y_7295_ = v___x_7335_;
v___y_7296_ = v___x_7357_;
goto v___jp_7288_;
}
}
}
else
{
uint64_t v_quotient_7358_; uint64_t v___x_7359_; uint64_t v___x_7360_; uint64_t v___x_7361_; uint64_t v_remainder_7362_; uint64_t v___x_7363_; uint64_t v_half_7364_; uint8_t v___x_7365_; 
v_quotient_7358_ = lean_uint64_shift_right(v___x_7343_, v___x_7349_);
v___x_7359_ = 1ULL;
v___x_7360_ = lean_uint64_shift_left(v___x_7359_, v___x_7349_);
v___x_7361_ = lean_uint64_sub(v___x_7360_, v___x_7359_);
v_remainder_7362_ = lean_uint64_land(v___x_7343_, v___x_7361_);
v___x_7363_ = lean_uint64_sub(v___x_7349_, v___x_7359_);
v_half_7364_ = lean_uint64_shift_left(v___x_7359_, v___x_7363_);
v___x_7365_ = lean_uint64_dec_lt(v_remainder_7362_, v_half_7364_);
if (v___x_7365_ == 0)
{
uint8_t v___x_7366_; 
v___x_7366_ = lean_uint64_dec_lt(v_half_7364_, v_remainder_7362_);
if (v___x_7366_ == 0)
{
uint64_t v___x_7367_; uint8_t v___x_7368_; 
v___x_7367_ = lean_uint64_land(v_quotient_7358_, v___x_7359_);
v___x_7368_ = lean_uint64_dec_eq(v___x_7367_, v___x_7350_);
if (v___x_7368_ == 0)
{
uint64_t v___x_7369_; 
v___x_7369_ = lean_uint64_add(v_quotient_7358_, v___x_7359_);
v___y_7289_ = v___x_7343_;
v___y_7290_ = v___x_7347_;
v___y_7291_ = v___x_7345_;
v___y_7292_ = v___x_7326_;
v___y_7293_ = v___x_7328_;
v___y_7294_ = v___y_7325_;
v___y_7295_ = v___x_7335_;
v___y_7296_ = v___x_7369_;
goto v___jp_7288_;
}
else
{
v___y_7289_ = v___x_7343_;
v___y_7290_ = v___x_7347_;
v___y_7291_ = v___x_7345_;
v___y_7292_ = v___x_7326_;
v___y_7293_ = v___x_7328_;
v___y_7294_ = v___y_7325_;
v___y_7295_ = v___x_7335_;
v___y_7296_ = v_quotient_7358_;
goto v___jp_7288_;
}
}
else
{
uint64_t v___x_7370_; 
v___x_7370_ = lean_uint64_add(v_quotient_7358_, v___x_7359_);
v___y_7289_ = v___x_7343_;
v___y_7290_ = v___x_7347_;
v___y_7291_ = v___x_7345_;
v___y_7292_ = v___x_7326_;
v___y_7293_ = v___x_7328_;
v___y_7294_ = v___y_7325_;
v___y_7295_ = v___x_7335_;
v___y_7296_ = v___x_7370_;
goto v___jp_7288_;
}
}
else
{
v___y_7289_ = v___x_7343_;
v___y_7290_ = v___x_7347_;
v___y_7291_ = v___x_7345_;
v___y_7292_ = v___x_7326_;
v___y_7293_ = v___x_7328_;
v___y_7294_ = v___y_7325_;
v___y_7295_ = v___x_7335_;
v___y_7296_ = v_quotient_7358_;
goto v___jp_7288_;
}
}
}
else
{
v___y_7289_ = v___x_7343_;
v___y_7290_ = v___x_7347_;
v___y_7291_ = v___x_7345_;
v___y_7292_ = v___x_7326_;
v___y_7293_ = v___x_7328_;
v___y_7294_ = v___y_7325_;
v___y_7295_ = v___x_7335_;
v___y_7296_ = v___x_7343_;
goto v___jp_7288_;
}
}
v___jp_7371_:
{
uint8_t v___x_7372_; 
v___x_7372_ = 0;
v___y_7325_ = v___x_7372_;
goto v___jp_7324_;
}
v___jp_7373_:
{
if (v___y_7374_ == 0)
{
uint8_t v___x_7375_; 
v___x_7375_ = 1;
v___y_7325_ = v___x_7375_;
goto v___jp_7324_;
}
else
{
goto v___jp_7371_;
}
}
}
}