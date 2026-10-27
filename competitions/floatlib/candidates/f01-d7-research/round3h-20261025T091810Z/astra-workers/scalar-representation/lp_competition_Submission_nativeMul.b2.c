LEAN_EXPORT uint32_t lp_competition_Submission_nativeMul(uint32_t v_x_6213_, uint32_t v_y_6214_){
_start:
{
uint8_t v___y_6216_; uint8_t v___y_6232_; uint8_t v___y_6246_; uint8_t v___y_6263_; float v___y_6270_; float v___y_6271_; float v___y_6285_; uint8_t v___y_6286_; float v___y_6301_; uint8_t v___y_6311_; uint32_t v___x_6325_; uint32_t v_a_6326_; uint32_t v___x_6327_; uint32_t v___x_6328_; uint32_t v___x_6329_; uint8_t v___x_6330_; 
v___x_6325_ = 2147483647;
v_a_6326_ = lean_uint32_land(v_x_6213_, v___x_6325_);
v___x_6327_ = 201326591;
v___x_6328_ = 1;
v___x_6329_ = lean_uint32_sub(v_a_6326_, v___x_6328_);
v___x_6330_ = lean_uint32_dec_le(v___x_6327_, v___x_6329_);
if (v___x_6330_ == 0)
{
v___y_6311_ = v___x_6330_;
goto v___jp_6310_;
}
else
{
uint32_t v___x_6331_; uint8_t v___x_6332_; 
v___x_6331_ = 2139095040;
v___x_6332_ = lean_uint32_dec_lt(v_a_6326_, v___x_6331_);
v___y_6311_ = v___x_6332_;
goto v___jp_6310_;
}
v___jp_6215_:
{
if (v___y_6216_ == 0)
{
uint32_t v___x_6217_; 
v___x_6217_ = lp_competition_Submission_FastMul_mul(v_x_6213_, v_y_6214_);
return v___x_6217_;
}
else
{
uint32_t v___x_6218_; uint32_t v___x_6219_; 
v___x_6218_ = 4194304;
v___x_6219_ = lean_uint32_lor(v_y_6214_, v___x_6218_);
return v___x_6219_;
}
}
v___jp_6220_:
{
uint32_t v___x_6221_; uint32_t v___x_6222_; uint32_t v___x_6223_; uint32_t v___x_6224_; uint8_t v___x_6225_; 
v___x_6221_ = 23;
v___x_6222_ = lean_uint32_shift_right(v_y_6214_, v___x_6221_);
v___x_6223_ = 255;
v___x_6224_ = lean_uint32_land(v___x_6222_, v___x_6223_);
v___x_6225_ = lean_uint32_dec_eq(v___x_6224_, v___x_6223_);
if (v___x_6225_ == 0)
{
v___y_6216_ = v___x_6225_;
goto v___jp_6215_;
}
else
{
uint32_t v___x_6226_; uint32_t v___x_6227_; uint32_t v___x_6228_; uint8_t v___x_6229_; 
v___x_6226_ = 8388607;
v___x_6227_ = lean_uint32_land(v_y_6214_, v___x_6226_);
v___x_6228_ = 0;
v___x_6229_ = lean_uint32_dec_eq(v___x_6227_, v___x_6228_);
if (v___x_6229_ == 0)
{
v___y_6216_ = v___x_6225_;
goto v___jp_6215_;
}
else
{
uint32_t v___x_6230_; 
v___x_6230_ = lp_competition_Submission_FastMul_mul(v_x_6213_, v_y_6214_);
return v___x_6230_;
}
}
}
v___jp_6231_:
{
if (v___y_6232_ == 0)
{
goto v___jp_6220_;
}
else
{
uint32_t v___x_6233_; uint32_t v___x_6234_; 
v___x_6233_ = 4194304;
v___x_6234_ = lean_uint32_lor(v_x_6213_, v___x_6233_);
return v___x_6234_;
}
}
v___jp_6235_:
{
uint32_t v___x_6236_; uint32_t v___x_6237_; uint32_t v___x_6238_; uint32_t v___x_6239_; uint8_t v___x_6240_; 
v___x_6236_ = 23;
v___x_6237_ = lean_uint32_shift_right(v_x_6213_, v___x_6236_);
v___x_6238_ = 255;
v___x_6239_ = lean_uint32_land(v___x_6237_, v___x_6238_);
v___x_6240_ = lean_uint32_dec_eq(v___x_6239_, v___x_6238_);
if (v___x_6240_ == 0)
{
v___y_6232_ = v___x_6240_;
goto v___jp_6231_;
}
else
{
uint32_t v___x_6241_; uint32_t v___x_6242_; uint32_t v___x_6243_; uint8_t v___x_6244_; 
v___x_6241_ = 8388607;
v___x_6242_ = lean_uint32_land(v_x_6213_, v___x_6241_);
v___x_6243_ = 0;
v___x_6244_ = lean_uint32_dec_eq(v___x_6242_, v___x_6243_);
if (v___x_6244_ == 0)
{
v___y_6232_ = v___x_6240_;
goto v___jp_6231_;
}
else
{
goto v___jp_6220_;
}
}
}
v___jp_6245_:
{
if (v___y_6246_ == 0)
{
goto v___jp_6235_;
}
else
{
uint32_t v___x_6247_; uint32_t v___x_6248_; uint32_t v___x_6249_; uint8_t v___x_6250_; 
v___x_6247_ = 4194304;
v___x_6248_ = lean_uint32_land(v_y_6214_, v___x_6247_);
v___x_6249_ = 0;
v___x_6250_ = lean_uint32_dec_eq(v___x_6248_, v___x_6249_);
if (v___x_6250_ == 0)
{
goto v___jp_6235_;
}
else
{
uint32_t v___x_6251_; 
v___x_6251_ = lean_uint32_lor(v_y_6214_, v___x_6247_);
return v___x_6251_;
}
}
}
v___jp_6252_:
{
uint32_t v___x_6253_; uint32_t v___x_6254_; uint32_t v___x_6255_; uint32_t v___x_6256_; uint8_t v___x_6257_; 
v___x_6253_ = 23;
v___x_6254_ = lean_uint32_shift_right(v_y_6214_, v___x_6253_);
v___x_6255_ = 255;
v___x_6256_ = lean_uint32_land(v___x_6254_, v___x_6255_);
v___x_6257_ = lean_uint32_dec_eq(v___x_6256_, v___x_6255_);
if (v___x_6257_ == 0)
{
v___y_6246_ = v___x_6257_;
goto v___jp_6245_;
}
else
{
uint32_t v___x_6258_; uint32_t v___x_6259_; uint32_t v___x_6260_; uint8_t v___x_6261_; 
v___x_6258_ = 8388607;
v___x_6259_ = lean_uint32_land(v_y_6214_, v___x_6258_);
v___x_6260_ = 0;
v___x_6261_ = lean_uint32_dec_eq(v___x_6259_, v___x_6260_);
if (v___x_6261_ == 0)
{
v___y_6246_ = v___x_6257_;
goto v___jp_6245_;
}
else
{
goto v___jp_6235_;
}
}
}
v___jp_6262_:
{
if (v___y_6263_ == 0)
{
goto v___jp_6252_;
}
else
{
uint32_t v___x_6264_; uint32_t v___x_6265_; uint32_t v___x_6266_; uint8_t v___x_6267_; 
v___x_6264_ = 4194304;
v___x_6265_ = lean_uint32_land(v_x_6213_, v___x_6264_);
v___x_6266_ = 0;
v___x_6267_ = lean_uint32_dec_eq(v___x_6265_, v___x_6266_);
if (v___x_6267_ == 0)
{
goto v___jp_6252_;
}
else
{
uint32_t v___x_6268_; 
v___x_6268_ = lean_uint32_lor(v_x_6213_, v___x_6264_);
return v___x_6268_;
}
}
}
v___jp_6269_:
{
float v_result_6272_; uint8_t v___x_6273_; 
v_result_6272_ = lean_float32_mul(v___y_6270_, v___y_6271_);
v___x_6273_ = lean_float32_beq(v_result_6272_, v_result_6272_);
if (v___x_6273_ == 0)
{
uint32_t v___x_6274_; uint32_t v___x_6275_; uint32_t v___x_6276_; uint32_t v___x_6277_; uint8_t v___x_6278_; 
v___x_6274_ = 23;
v___x_6275_ = lean_uint32_shift_right(v_x_6213_, v___x_6274_);
v___x_6276_ = 255;
v___x_6277_ = lean_uint32_land(v___x_6275_, v___x_6276_);
v___x_6278_ = lean_uint32_dec_eq(v___x_6277_, v___x_6276_);
if (v___x_6278_ == 0)
{
v___y_6263_ = v___x_6278_;
goto v___jp_6262_;
}
else
{
uint32_t v___x_6279_; uint32_t v___x_6280_; uint32_t v___x_6281_; uint8_t v___x_6282_; 
v___x_6279_ = 8388607;
v___x_6280_ = lean_uint32_land(v_x_6213_, v___x_6279_);
v___x_6281_ = 0;
v___x_6282_ = lean_uint32_dec_eq(v___x_6280_, v___x_6281_);
if (v___x_6282_ == 0)
{
v___y_6263_ = v___x_6278_;
goto v___jp_6262_;
}
else
{
goto v___jp_6252_;
}
}
}
else
{
uint32_t v___x_6283_; 
v___x_6283_ = lean_float32_to_bits(v_result_6272_);
return v___x_6283_;
}
}
v___jp_6284_:
{
if (v___y_6286_ == 0)
{
float v___x_6287_; 
v___x_6287_ = lean_float32_of_bits(v_y_6214_);
v___y_6270_ = v___y_6285_;
v___y_6271_ = v___x_6287_;
goto v___jp_6269_;
}
else
{
uint32_t v___x_6288_; uint32_t v___x_6289_; uint32_t v___x_6290_; uint32_t v___x_6291_; float v___x_6292_; lean_object* v___x_6293_; uint32_t v___x_6294_; uint32_t v___x_6295_; lean_object* v___x_6296_; lean_object* v___x_6297_; float v___x_6298_; float v___x_6299_; 
v___x_6288_ = 8388607;
v___x_6289_ = lean_uint32_land(v_y_6214_, v___x_6288_);
v___x_6290_ = 8388608;
v___x_6291_ = lean_uint32_lor(v___x_6289_, v___x_6290_);
v___x_6292_ = lean_uint32_to_float32(v___x_6291_);
v___x_6293_ = lp_competition_R2W01b_scaleTable;
v___x_6294_ = 23;
v___x_6295_ = lean_uint32_shift_right(v_y_6214_, v___x_6294_);
v___x_6296_ = lean_uint32_to_nat(v___x_6295_);
v___x_6297_ = lean_array_fget_borrowed(v___x_6293_, v___x_6296_);
lean_dec(v___x_6296_);
v___x_6298_ = lean_unbox_float32(v___x_6297_);
v___x_6299_ = lean_float32_mul(v___x_6292_, v___x_6298_);
v___y_6270_ = v___y_6285_;
v___y_6271_ = v___x_6299_;
goto v___jp_6269_;
}
}
v___jp_6300_:
{
uint32_t v___x_6302_; uint32_t v_a_6303_; uint32_t v___x_6304_; uint32_t v___x_6305_; uint32_t v___x_6306_; uint8_t v___x_6307_; 
v___x_6302_ = 2147483647;
v_a_6303_ = lean_uint32_land(v_y_6214_, v___x_6302_);
v___x_6304_ = 201326591;
v___x_6305_ = 1;
v___x_6306_ = lean_uint32_sub(v_a_6303_, v___x_6305_);
v___x_6307_ = lean_uint32_dec_le(v___x_6304_, v___x_6306_);
if (v___x_6307_ == 0)
{
v___y_6285_ = v___y_6301_;
v___y_6286_ = v___x_6307_;
goto v___jp_6284_;
}
else
{
uint32_t v___x_6308_; uint8_t v___x_6309_; 
v___x_6308_ = 2139095040;
v___x_6309_ = lean_uint32_dec_lt(v_a_6303_, v___x_6308_);
v___y_6285_ = v___y_6301_;
v___y_6286_ = v___x_6309_;
goto v___jp_6284_;
}
}
v___jp_6310_:
{
if (v___y_6311_ == 0)
{
float v___x_6312_; 
v___x_6312_ = lean_float32_of_bits(v_x_6213_);
v___y_6301_ = v___x_6312_;
goto v___jp_6300_;
}
else
{
uint32_t v___x_6313_; uint32_t v___x_6314_; uint32_t v___x_6315_; uint32_t v___x_6316_; float v___x_6317_; lean_object* v___x_6318_; uint32_t v___x_6319_; uint32_t v___x_6320_; lean_object* v___x_6321_; lean_object* v___x_6322_; float v___x_6323_; float v___x_6324_; 
v___x_6313_ = 8388607;
v___x_6314_ = lean_uint32_land(v_x_6213_, v___x_6313_);
v___x_6315_ = 8388608;
v___x_6316_ = lean_uint32_lor(v___x_6314_, v___x_6315_);
v___x_6317_ = lean_uint32_to_float32(v___x_6316_);
v___x_6318_ = lp_competition_R2W01b_scaleTable;
v___x_6319_ = 23;
v___x_6320_ = lean_uint32_shift_right(v_x_6213_, v___x_6319_);
v___x_6321_ = lean_uint32_to_nat(v___x_6320_);
v___x_6322_ = lean_array_fget_borrowed(v___x_6318_, v___x_6321_);
lean_dec(v___x_6321_);
v___x_6323_ = lean_unbox_float32(v___x_6322_);
v___x_6324_ = lean_float32_mul(v___x_6317_, v___x_6323_);
v___y_6301_ = v___x_6324_;
goto v___jp_6300_;
}
}
}
}
