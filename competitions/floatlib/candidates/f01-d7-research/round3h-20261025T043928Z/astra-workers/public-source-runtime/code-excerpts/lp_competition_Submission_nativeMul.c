LEAN_EXPORT uint32_t lp_competition_Submission_nativeMul(uint32_t v_x_6231_, uint32_t v_y_6232_){
_start:
{
uint8_t v___y_6234_; uint8_t v___y_6250_; uint8_t v___y_6264_; uint8_t v___y_6281_; float v___y_6288_; float v___y_6289_; float v___y_6303_; uint8_t v___y_6304_; float v___y_6319_; uint8_t v___y_6329_; uint32_t v___x_6343_; uint32_t v_a_6344_; uint32_t v___x_6345_; uint32_t v___x_6346_; uint32_t v___x_6347_; uint8_t v___x_6348_; 
v___x_6343_ = 2147483647;
v_a_6344_ = lean_uint32_land(v_x_6231_, v___x_6343_);
v___x_6345_ = 201326591;
v___x_6346_ = 1;
v___x_6347_ = lean_uint32_sub(v_a_6344_, v___x_6346_);
v___x_6348_ = lean_uint32_dec_le(v___x_6345_, v___x_6347_);
if (v___x_6348_ == 0)
{
v___y_6329_ = v___x_6348_;
goto v___jp_6328_;
}
else
{
uint32_t v___x_6349_; uint8_t v___x_6350_; 
v___x_6349_ = 2139095040;
v___x_6350_ = lean_uint32_dec_lt(v_a_6344_, v___x_6349_);
v___y_6329_ = v___x_6350_;
goto v___jp_6328_;
}
v___jp_6233_:
{
if (v___y_6234_ == 0)
{
uint32_t v___x_6235_; 
v___x_6235_ = lp_competition_Submission_FastMul_mul(v_x_6231_, v_y_6232_);
return v___x_6235_;
}
else
{
uint32_t v___x_6236_; uint32_t v___x_6237_; 
v___x_6236_ = 4194304;
v___x_6237_ = lean_uint32_lor(v_y_6232_, v___x_6236_);
return v___x_6237_;
}
}
v___jp_6238_:
{
uint32_t v___x_6239_; uint32_t v___x_6240_; uint32_t v___x_6241_; uint32_t v___x_6242_; uint8_t v___x_6243_; 
v___x_6239_ = 23;
v___x_6240_ = lean_uint32_shift_right(v_y_6232_, v___x_6239_);
v___x_6241_ = 255;
v___x_6242_ = lean_uint32_land(v___x_6240_, v___x_6241_);
v___x_6243_ = lean_uint32_dec_eq(v___x_6242_, v___x_6241_);
if (v___x_6243_ == 0)
{
v___y_6234_ = v___x_6243_;
goto v___jp_6233_;
}
else
{
uint32_t v___x_6244_; uint32_t v___x_6245_; uint32_t v___x_6246_; uint8_t v___x_6247_; 
v___x_6244_ = 8388607;
v___x_6245_ = lean_uint32_land(v_y_6232_, v___x_6244_);
v___x_6246_ = 0;
v___x_6247_ = lean_uint32_dec_eq(v___x_6245_, v___x_6246_);
if (v___x_6247_ == 0)
{
v___y_6234_ = v___x_6243_;
goto v___jp_6233_;
}
else
{
uint32_t v___x_6248_; 
v___x_6248_ = lp_competition_Submission_FastMul_mul(v_x_6231_, v_y_6232_);
return v___x_6248_;
}
}
}
v___jp_6249_:
{
if (v___y_6250_ == 0)
{
goto v___jp_6238_;
}
else
{
uint32_t v___x_6251_; uint32_t v___x_6252_; 
v___x_6251_ = 4194304;
v___x_6252_ = lean_uint32_lor(v_x_6231_, v___x_6251_);
return v___x_6252_;
}
}
v___jp_6253_:
{
uint32_t v___x_6254_; uint32_t v___x_6255_; uint32_t v___x_6256_; uint32_t v___x_6257_; uint8_t v___x_6258_; 
v___x_6254_ = 23;
v___x_6255_ = lean_uint32_shift_right(v_x_6231_, v___x_6254_);
v___x_6256_ = 255;
v___x_6257_ = lean_uint32_land(v___x_6255_, v___x_6256_);
v___x_6258_ = lean_uint32_dec_eq(v___x_6257_, v___x_6256_);
if (v___x_6258_ == 0)
{
v___y_6250_ = v___x_6258_;
goto v___jp_6249_;
}
else
{
uint32_t v___x_6259_; uint32_t v___x_6260_; uint32_t v___x_6261_; uint8_t v___x_6262_; 
v___x_6259_ = 8388607;
v___x_6260_ = lean_uint32_land(v_x_6231_, v___x_6259_);
v___x_6261_ = 0;
v___x_6262_ = lean_uint32_dec_eq(v___x_6260_, v___x_6261_);
if (v___x_6262_ == 0)
{
v___y_6250_ = v___x_6258_;
goto v___jp_6249_;
}
else
{
goto v___jp_6238_;
}
}
}
v___jp_6263_:
{
if (v___y_6264_ == 0)
{
goto v___jp_6253_;
}
else
{
uint32_t v___x_6265_; uint32_t v___x_6266_; uint32_t v___x_6267_; uint8_t v___x_6268_; 
v___x_6265_ = 4194304;
v___x_6266_ = lean_uint32_land(v_y_6232_, v___x_6265_);
v___x_6267_ = 0;
v___x_6268_ = lean_uint32_dec_eq(v___x_6266_, v___x_6267_);
if (v___x_6268_ == 0)
{
goto v___jp_6253_;
}
else
{
uint32_t v___x_6269_; 
v___x_6269_ = lean_uint32_lor(v_y_6232_, v___x_6265_);
return v___x_6269_;
}
}
}
v___jp_6270_:
{
uint32_t v___x_6271_; uint32_t v___x_6272_; uint32_t v___x_6273_; uint32_t v___x_6274_; uint8_t v___x_6275_; 
v___x_6271_ = 23;
v___x_6272_ = lean_uint32_shift_right(v_y_6232_, v___x_6271_);
v___x_6273_ = 255;
v___x_6274_ = lean_uint32_land(v___x_6272_, v___x_6273_);
v___x_6275_ = lean_uint32_dec_eq(v___x_6274_, v___x_6273_);
if (v___x_6275_ == 0)
{
v___y_6264_ = v___x_6275_;
goto v___jp_6263_;
}
else
{
uint32_t v___x_6276_; uint32_t v___x_6277_; uint32_t v___x_6278_; uint8_t v___x_6279_; 
v___x_6276_ = 8388607;
v___x_6277_ = lean_uint32_land(v_y_6232_, v___x_6276_);
v___x_6278_ = 0;
v___x_6279_ = lean_uint32_dec_eq(v___x_6277_, v___x_6278_);
if (v___x_6279_ == 0)
{
v___y_6264_ = v___x_6275_;
goto v___jp_6263_;
}
else
{
goto v___jp_6253_;
}
}
}
v___jp_6280_:
{
if (v___y_6281_ == 0)
{
goto v___jp_6270_;
}
else
{
uint32_t v___x_6282_; uint32_t v___x_6283_; uint32_t v___x_6284_; uint8_t v___x_6285_; 
v___x_6282_ = 4194304;
v___x_6283_ = lean_uint32_land(v_x_6231_, v___x_6282_);
v___x_6284_ = 0;
v___x_6285_ = lean_uint32_dec_eq(v___x_6283_, v___x_6284_);
if (v___x_6285_ == 0)
{
goto v___jp_6270_;
}
else
{
uint32_t v___x_6286_; 
v___x_6286_ = lean_uint32_lor(v_x_6231_, v___x_6282_);
return v___x_6286_;
}
}
}
v___jp_6287_:
{
float v_result_6290_; uint8_t v___x_6291_; 
v_result_6290_ = lean_float32_mul(v___y_6288_, v___y_6289_);
v___x_6291_ = lean_float32_beq(v_result_6290_, v_result_6290_);
if (v___x_6291_ == 0)
{
uint32_t v___x_6292_; uint32_t v___x_6293_; uint32_t v___x_6294_; uint32_t v___x_6295_; uint8_t v___x_6296_; 
v___x_6292_ = 23;
v___x_6293_ = lean_uint32_shift_right(v_x_6231_, v___x_6292_);
v___x_6294_ = 255;
v___x_6295_ = lean_uint32_land(v___x_6293_, v___x_6294_);
v___x_6296_ = lean_uint32_dec_eq(v___x_6295_, v___x_6294_);
if (v___x_6296_ == 0)
{
v___y_6281_ = v___x_6296_;
goto v___jp_6280_;
}
else
{
uint32_t v___x_6297_; uint32_t v___x_6298_; uint32_t v___x_6299_; uint8_t v___x_6300_; 
v___x_6297_ = 8388607;
v___x_6298_ = lean_uint32_land(v_x_6231_, v___x_6297_);
v___x_6299_ = 0;
v___x_6300_ = lean_uint32_dec_eq(v___x_6298_, v___x_6299_);
if (v___x_6300_ == 0)
{
v___y_6281_ = v___x_6296_;
goto v___jp_6280_;
}
else
{
goto v___jp_6270_;
}
}
}
else
{
uint32_t v___x_6301_; 
v___x_6301_ = lean_float32_to_bits(v_result_6290_);
return v___x_6301_;
}
}
v___jp_6302_:
{
if (v___y_6304_ == 0)
{
float v___x_6305_; 
v___x_6305_ = lean_float32_of_bits(v_y_6232_);
v___y_6288_ = v___y_6303_;
v___y_6289_ = v___x_6305_;
goto v___jp_6287_;
}
else
{
uint32_t v___x_6306_; uint32_t v___x_6307_; uint32_t v___x_6308_; uint32_t v___x_6309_; float v___x_6310_; lean_object* v___x_6311_; uint32_t v___x_6312_; uint32_t v___x_6313_; lean_object* v___x_6314_; lean_object* v___x_6315_; float v___x_6316_; float v___x_6317_; 
v___x_6306_ = 8388607;
v___x_6307_ = lean_uint32_land(v_y_6232_, v___x_6306_);
v___x_6308_ = 8388608;
v___x_6309_ = lean_uint32_lor(v___x_6307_, v___x_6308_);
v___x_6310_ = lean_uint32_to_float32(v___x_6309_);
v___x_6311_ = lp_competition_R2W01b_scaleTable;
v___x_6312_ = 23;
v___x_6313_ = lean_uint32_shift_right(v_y_6232_, v___x_6312_);
v___x_6314_ = lean_uint32_to_nat(v___x_6313_);
v___x_6315_ = lean_array_fget_borrowed(v___x_6311_, v___x_6314_);
lean_dec(v___x_6314_);
v___x_6316_ = lean_unbox_float32(v___x_6315_);
v___x_6317_ = lean_float32_mul(v___x_6310_, v___x_6316_);
v___y_6288_ = v___y_6303_;
v___y_6289_ = v___x_6317_;
goto v___jp_6287_;
}
}
v___jp_6318_:
{
uint32_t v___x_6320_; uint32_t v_a_6321_; uint32_t v___x_6322_; uint32_t v___x_6323_; uint32_t v___x_6324_; uint8_t v___x_6325_; 
v___x_6320_ = 2147483647;
v_a_6321_ = lean_uint32_land(v_y_6232_, v___x_6320_);
v___x_6322_ = 201326591;
v___x_6323_ = 1;
v___x_6324_ = lean_uint32_sub(v_a_6321_, v___x_6323_);
v___x_6325_ = lean_uint32_dec_le(v___x_6322_, v___x_6324_);
if (v___x_6325_ == 0)
{
v___y_6303_ = v___y_6319_;
v___y_6304_ = v___x_6325_;
goto v___jp_6302_;
}
else
{
uint32_t v___x_6326_; uint8_t v___x_6327_; 
v___x_6326_ = 2139095040;
v___x_6327_ = lean_uint32_dec_lt(v_a_6321_, v___x_6326_);
v___y_6303_ = v___y_6319_;
v___y_6304_ = v___x_6327_;
goto v___jp_6302_;
}
}
v___jp_6328_:
{
if (v___y_6329_ == 0)
{
float v___x_6330_; 
v___x_6330_ = lean_float32_of_bits(v_x_6231_);
v___y_6319_ = v___x_6330_;
goto v___jp_6318_;
}
else
{
uint32_t v___x_6331_; uint32_t v___x_6332_; uint32_t v___x_6333_; uint32_t v___x_6334_; float v___x_6335_; lean_object* v___x_6336_; uint32_t v___x_6337_; uint32_t v___x_6338_; lean_object* v___x_6339_; lean_object* v___x_6340_; float v___x_6341_; float v___x_6342_; 
v___x_6331_ = 8388607;
v___x_6332_ = lean_uint32_land(v_x_6231_, v___x_6331_);
v___x_6333_ = 8388608;
v___x_6334_ = lean_uint32_lor(v___x_6332_, v___x_6333_);
v___x_6335_ = lean_uint32_to_float32(v___x_6334_);
v___x_6336_ = lp_competition_R2W01b_scaleTable;
v___x_6337_ = 23;
v___x_6338_ = lean_uint32_shift_right(v_x_6231_, v___x_6337_);
v___x_6339_ = lean_uint32_to_nat(v___x_6338_);
v___x_6340_ = lean_array_fget_borrowed(v___x_6336_, v___x_6339_);
lean_dec(v___x_6339_);
v___x_6341_ = lean_unbox_float32(v___x_6340_);
v___x_6342_ = lean_float32_mul(v___x_6335_, v___x_6341_);
v___y_6319_ = v___x_6342_;
goto v___jp_6318_;
}
}
}
}