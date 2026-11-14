LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t v___y_265_, uint32_t v___y_266_){
_start:
{
uint8_t v___y_273_; uint8_t v___y_287_; uint8_t v___y_301_; uint8_t v___y_318_; float v___y_325_; float v___y_326_; float v___y_340_; uint8_t v___y_341_; float v___y_356_; uint8_t v___y_366_; uint32_t v___x_389_; uint32_t v___x_390_; uint32_t v___x_391_; uint32_t v_eu_392_; uint32_t v___y_394_; uint32_t v___y_395_; uint32_t v___y_396_; uint32_t v___y_397_; uint32_t v___y_414_; uint32_t v___y_415_; uint32_t v___y_416_; uint32_t v___y_417_; uint32_t v___y_418_; uint32_t v___y_419_; uint32_t v___y_420_; uint32_t v___x_430_; uint32_t v_ev_431_; uint32_t v___y_433_; uint32_t v___y_434_; uint32_t v___y_435_; uint32_t v___y_436_; uint32_t v___y_453_; uint32_t v___y_454_; uint32_t v___y_455_; uint32_t v___y_456_; uint32_t v___y_457_; uint32_t v___y_458_; uint32_t v___y_459_; uint8_t v___y_470_; uint32_t v___x_510_; uint32_t v___x_511_; uint8_t v___x_512_; 
v___x_389_ = 23;
v___x_390_ = lean_uint32_shift_right(v___y_265_, v___x_389_);
v___x_391_ = 255;
v_eu_392_ = lean_uint32_land(v___x_390_, v___x_391_);
v___x_430_ = lean_uint32_shift_right(v___y_266_, v___x_389_);
v_ev_431_ = lean_uint32_land(v___x_430_, v___x_391_);
v___x_510_ = lean_uint32_xor(v___y_265_, v___y_266_);
v___x_511_ = 2147483648;
v___x_512_ = lean_uint32_dec_lt(v___x_510_, v___x_511_);
if (v___x_512_ == 0)
{
v___y_470_ = v___x_512_;
goto v___jp_469_;
}
else
{
uint32_t v___x_513_; uint32_t v___x_514_; uint32_t v___x_515_; uint8_t v___x_516_; 
v___x_513_ = 1;
v___x_514_ = lean_uint32_sub(v_eu_392_, v___x_513_);
v___x_515_ = 254;
v___x_516_ = lean_uint32_dec_lt(v___x_514_, v___x_515_);
v___y_470_ = v___x_516_;
goto v___jp_469_;
}
v___jp_267_:
{
lean_object* v___x_268_; lean_object* v___x_269_; lean_object* v___x_270_; uint32_t v___x_271_; 
v___x_268_ = lean_uint32_to_nat(v___y_265_);
v___x_269_ = lean_uint32_to_nat(v___y_266_);
v___x_270_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_268_, v___x_269_);
v___x_271_ = lean_uint32_of_nat(v___x_270_);
lean_dec(v___x_270_);
return v___x_271_;
}
v___jp_272_:
{
if (v___y_273_ == 0)
{
goto v___jp_267_;
}
else
{
uint32_t v___x_274_; uint32_t v___x_275_; 
v___x_274_ = 4194304;
v___x_275_ = lean_uint32_lor(v___y_266_, v___x_274_);
return v___x_275_;
}
}
v___jp_276_:
{
uint32_t v___x_277_; uint32_t v___x_278_; uint32_t v___x_279_; uint32_t v___x_280_; uint8_t v___x_281_; 
v___x_277_ = 23;
v___x_278_ = lean_uint32_shift_right(v___y_266_, v___x_277_);
v___x_279_ = 255;
v___x_280_ = lean_uint32_land(v___x_278_, v___x_279_);
v___x_281_ = lean_uint32_dec_eq(v___x_280_, v___x_279_);
if (v___x_281_ == 0)
{
v___y_273_ = v___x_281_;
goto v___jp_272_;
}
else
{
uint32_t v___x_282_; uint32_t v___x_283_; uint32_t v___x_284_; uint8_t v___x_285_; 
v___x_282_ = 8388607;
v___x_283_ = lean_uint32_land(v___y_266_, v___x_282_);
v___x_284_ = 0;
v___x_285_ = lean_uint32_dec_eq(v___x_283_, v___x_284_);
if (v___x_285_ == 0)
{
v___y_273_ = v___x_281_;
goto v___jp_272_;
}
else
{
goto v___jp_267_;
}
}
}
v___jp_286_:
{
if (v___y_287_ == 0)
{
goto v___jp_276_;
}
else
{
uint32_t v___x_288_; uint32_t v___x_289_; 
v___x_288_ = 4194304;
v___x_289_ = lean_uint32_lor(v___y_265_, v___x_288_);
return v___x_289_;
}
}
v___jp_290_:
{
uint32_t v___x_291_; uint32_t v___x_292_; uint32_t v___x_293_; uint32_t v___x_294_; uint8_t v___x_295_; 
v___x_291_ = 23;
v___x_292_ = lean_uint32_shift_right(v___y_265_, v___x_291_);
v___x_293_ = 255;
v___x_294_ = lean_uint32_land(v___x_292_, v___x_293_);
v___x_295_ = lean_uint32_dec_eq(v___x_294_, v___x_293_);
if (v___x_295_ == 0)
{
v___y_287_ = v___x_295_;
goto v___jp_286_;
}
else
{
uint32_t v___x_296_; uint32_t v___x_297_; uint32_t v___x_298_; uint8_t v___x_299_; 
v___x_296_ = 8388607;
v___x_297_ = lean_uint32_land(v___y_265_, v___x_296_);
v___x_298_ = 0;
v___x_299_ = lean_uint32_dec_eq(v___x_297_, v___x_298_);
if (v___x_299_ == 0)
{
v___y_287_ = v___x_295_;
goto v___jp_286_;
}
else
{
goto v___jp_276_;
}
}
}
v___jp_300_:
{
if (v___y_301_ == 0)
{
goto v___jp_290_;
}
else
{
uint32_t v___x_302_; uint32_t v___x_303_; uint32_t v___x_304_; uint8_t v___x_305_; 
v___x_302_ = 4194304;
v___x_303_ = lean_uint32_land(v___y_266_, v___x_302_);
v___x_304_ = 0;
v___x_305_ = lean_uint32_dec_eq(v___x_303_, v___x_304_);
if (v___x_305_ == 0)
{
goto v___jp_290_;
}
else
{
uint32_t v___x_306_; 
v___x_306_ = lean_uint32_lor(v___y_266_, v___x_302_);
return v___x_306_;
}
}
}
v___jp_307_:
{
uint32_t v___x_308_; uint32_t v___x_309_; uint32_t v___x_310_; uint32_t v___x_311_; uint8_t v___x_312_; 
v___x_308_ = 23;
v___x_309_ = lean_uint32_shift_right(v___y_266_, v___x_308_);
v___x_310_ = 255;
v___x_311_ = lean_uint32_land(v___x_309_, v___x_310_);
v___x_312_ = lean_uint32_dec_eq(v___x_311_, v___x_310_);
if (v___x_312_ == 0)
{
v___y_301_ = v___x_312_;
goto v___jp_300_;
}
else
{
uint32_t v___x_313_; uint32_t v___x_314_; uint32_t v___x_315_; uint8_t v___x_316_; 
v___x_313_ = 8388607;
v___x_314_ = lean_uint32_land(v___y_266_, v___x_313_);
v___x_315_ = 0;
v___x_316_ = lean_uint32_dec_eq(v___x_314_, v___x_315_);
if (v___x_316_ == 0)
{
v___y_301_ = v___x_312_;
goto v___jp_300_;
}
else
{
goto v___jp_290_;
}
}
}
v___jp_317_:
{
if (v___y_318_ == 0)
{
goto v___jp_307_;
}
else
{
uint32_t v___x_319_; uint32_t v___x_320_; uint32_t v___x_321_; uint8_t v___x_322_; 
v___x_319_ = 4194304;
v___x_320_ = lean_uint32_land(v___y_265_, v___x_319_);
v___x_321_ = 0;
v___x_322_ = lean_uint32_dec_eq(v___x_320_, v___x_321_);
if (v___x_322_ == 0)
{
goto v___jp_307_;
}
else
{
uint32_t v___x_323_; 
v___x_323_ = lean_uint32_lor(v___y_265_, v___x_319_);
return v___x_323_;
}
}
}
v___jp_324_:
{
float v_result_327_; uint8_t v___x_328_; 
v_result_327_ = lean_float32_add(v___y_325_, v___y_326_);
v___x_328_ = lean_float32_beq(v_result_327_, v_result_327_);
if (v___x_328_ == 0)
{
uint32_t v___x_329_; uint32_t v___x_330_; uint32_t v___x_331_; uint32_t v___x_332_; uint8_t v___x_333_; 
v___x_329_ = 23;
v___x_330_ = lean_uint32_shift_right(v___y_265_, v___x_329_);
v___x_331_ = 255;
v___x_332_ = lean_uint32_land(v___x_330_, v___x_331_);
v___x_333_ = lean_uint32_dec_eq(v___x_332_, v___x_331_);
if (v___x_333_ == 0)
{
v___y_318_ = v___x_333_;
goto v___jp_317_;
}
else
{
uint32_t v___x_334_; uint32_t v___x_335_; uint32_t v___x_336_; uint8_t v___x_337_; 
v___x_334_ = 8388607;
v___x_335_ = lean_uint32_land(v___y_265_, v___x_334_);
v___x_336_ = 0;
v___x_337_ = lean_uint32_dec_eq(v___x_335_, v___x_336_);
if (v___x_337_ == 0)
{
v___y_318_ = v___x_333_;
goto v___jp_317_;
}
else
{
goto v___jp_307_;
}
}
}
else
{
uint32_t v___x_338_; 
v___x_338_ = lean_float32_to_bits(v_result_327_);
return v___x_338_;
}
}
v___jp_339_:
{
if (v___y_341_ == 0)
{
float v___x_342_; 
v___x_342_ = lean_float32_of_bits(v___y_266_);
v___y_325_ = v___y_340_;
v___y_326_ = v___x_342_;
goto v___jp_324_;
}
else
{
uint32_t v___x_343_; uint32_t v___x_344_; uint32_t v___x_345_; uint32_t v___x_346_; float v___x_347_; lean_object* v___x_348_; uint32_t v___x_349_; uint32_t v___x_350_; lean_object* v___x_351_; lean_object* v___x_352_; float v___x_353_; float v___x_354_; 
v___x_343_ = 8388607;
v___x_344_ = lean_uint32_land(v___y_266_, v___x_343_);
v___x_345_ = 8388608;
v___x_346_ = lean_uint32_lor(v___x_344_, v___x_345_);
v___x_347_ = lean_uint32_to_float32(v___x_346_);
v___x_348_ = lp_competition_R2W01b_scaleTable;
v___x_349_ = 23;
v___x_350_ = lean_uint32_shift_right(v___y_266_, v___x_349_);
v___x_351_ = lean_uint32_to_nat(v___x_350_);
v___x_352_ = lean_array_fget_borrowed(v___x_348_, v___x_351_);
lean_dec(v___x_351_);
v___x_353_ = lean_unbox_float32(v___x_352_);
v___x_354_ = lean_float32_mul(v___x_347_, v___x_353_);
v___y_325_ = v___y_340_;
v___y_326_ = v___x_354_;
goto v___jp_324_;
}
}
v___jp_355_:
{
uint32_t v___x_357_; uint32_t v_a_358_; uint32_t v___x_359_; uint32_t v___x_360_; uint32_t v___x_361_; uint8_t v___x_362_; 
v___x_357_ = 2147483647;
v_a_358_ = lean_uint32_land(v___y_266_, v___x_357_);
v___x_359_ = 201326591;
v___x_360_ = 1;
v___x_361_ = lean_uint32_sub(v_a_358_, v___x_360_);
v___x_362_ = lean_uint32_dec_le(v___x_359_, v___x_361_);
if (v___x_362_ == 0)
{
v___y_340_ = v___y_356_;
v___y_341_ = v___x_362_;
goto v___jp_339_;
}
else
{
uint32_t v___x_363_; uint8_t v___x_364_; 
v___x_363_ = 2139095040;
v___x_364_ = lean_uint32_dec_lt(v_a_358_, v___x_363_);
v___y_340_ = v___y_356_;
v___y_341_ = v___x_364_;
goto v___jp_339_;
}
}
v___jp_365_:
{
if (v___y_366_ == 0)
{
float v___x_367_; 
v___x_367_ = lean_float32_of_bits(v___y_265_);
v___y_356_ = v___x_367_;
goto v___jp_355_;
}
else
{
uint32_t v___x_368_; uint32_t v___x_369_; uint32_t v___x_370_; uint32_t v___x_371_; float v___x_372_; lean_object* v___x_373_; uint32_t v___x_374_; uint32_t v___x_375_; lean_object* v___x_376_; lean_object* v___x_377_; float v___x_378_; float v___x_379_; 
v___x_368_ = 8388607;
v___x_369_ = lean_uint32_land(v___y_265_, v___x_368_);
v___x_370_ = 8388608;
v___x_371_ = lean_uint32_lor(v___x_369_, v___x_370_);
v___x_372_ = lean_uint32_to_float32(v___x_371_);
v___x_373_ = lp_competition_R2W01b_scaleTable;
v___x_374_ = 23;
v___x_375_ = lean_uint32_shift_right(v___y_265_, v___x_374_);
v___x_376_ = lean_uint32_to_nat(v___x_375_);
v___x_377_ = lean_array_fget_borrowed(v___x_373_, v___x_376_);
lean_dec(v___x_376_);
v___x_378_ = lean_unbox_float32(v___x_377_);
v___x_379_ = lean_float32_mul(v___x_372_, v___x_378_);
v___y_356_ = v___x_379_;
goto v___jp_355_;
}
}
v___jp_380_:
{
uint32_t v___x_381_; uint32_t v_a_382_; uint32_t v___x_383_; uint32_t v___x_384_; uint32_t v___x_385_; uint8_t v___x_386_; 
v___x_381_ = 2147483647;
v_a_382_ = lean_uint32_land(v___y_265_, v___x_381_);
v___x_383_ = 201326591;
v___x_384_ = 1;
v___x_385_ = lean_uint32_sub(v_a_382_, v___x_384_);
v___x_386_ = lean_uint32_dec_le(v___x_383_, v___x_385_);
if (v___x_386_ == 0)
{
v___y_366_ = v___x_386_;
goto v___jp_365_;
}
else
{
uint32_t v___x_387_; uint8_t v___x_388_; 
v___x_387_ = 2139095040;
v___x_388_ = lean_uint32_dec_lt(v_a_382_, v___x_387_);
v___y_366_ = v___x_388_;
goto v___jp_365_;
}
}
v___jp_393_:
{
uint32_t v_e_398_; uint32_t v___x_399_; uint32_t v_s_400_; uint8_t v___x_401_; 
v_e_398_ = lean_uint32_add(v_eu_392_, v___y_396_);
v___x_399_ = 2147483648;
v_s_400_ = lean_uint32_land(v___y_265_, v___x_399_);
v___x_401_ = lean_uint32_dec_le(v___x_391_, v_e_398_);
if (v___x_401_ == 0)
{
uint32_t v___x_402_; uint32_t v___x_403_; uint32_t v___x_404_; uint32_t v___x_405_; uint32_t v_m_406_; uint32_t v___x_407_; uint32_t v___x_408_; uint32_t v___x_409_; uint32_t v___x_410_; 
v___x_402_ = lean_uint32_add(v___y_397_, v___y_394_);
v___x_403_ = lean_uint32_shift_right(v___y_397_, v___y_394_);
v___x_404_ = lean_uint32_land(v___x_403_, v___y_395_);
v___x_405_ = lean_uint32_add(v___x_402_, v___x_404_);
v_m_406_ = lean_uint32_shift_right(v___x_405_, v___y_394_);
v___x_407_ = lean_uint32_sub(v_e_398_, v___y_395_);
v___x_408_ = lean_uint32_shift_left(v___x_407_, v___x_389_);
v___x_409_ = lean_uint32_add(v___x_408_, v_m_406_);
v___x_410_ = lean_uint32_lor(v_s_400_, v___x_409_);
return v___x_410_;
}
else
{
uint32_t v___x_411_; uint32_t v___x_412_; 
v___x_411_ = 2139095040;
v___x_412_ = lean_uint32_lor(v_s_400_, v___x_411_);
return v___x_412_;
}
}
v___jp_413_:
{
uint32_t v___x_421_; uint32_t v___x_422_; uint32_t v_t_423_; uint32_t v___x_424_; uint32_t v_carry_425_; uint8_t v___x_426_; 
v___x_421_ = lean_uint32_shift_right(v___y_417_, v___y_415_);
v___x_422_ = lean_uint32_lor(v___x_421_, v___y_420_);
v_t_423_ = lean_uint32_add(v___y_416_, v___x_422_);
v___x_424_ = 27;
v_carry_425_ = lean_uint32_shift_right(v_t_423_, v___x_424_);
v___x_426_ = lean_uint32_dec_eq(v_carry_425_, v___y_419_);
if (v___x_426_ == 0)
{
uint32_t v___x_427_; uint32_t v___x_428_; uint32_t v___x_429_; 
v___x_427_ = lean_uint32_shift_right(v_t_423_, v___y_418_);
v___x_428_ = lean_uint32_land(v_t_423_, v___y_418_);
v___x_429_ = lean_uint32_lor(v___x_427_, v___x_428_);
v___y_394_ = v___y_414_;
v___y_395_ = v___y_418_;
v___y_396_ = v_carry_425_;
v___y_397_ = v___x_429_;
goto v___jp_393_;
}
else
{
v___y_394_ = v___y_414_;
v___y_395_ = v___y_418_;
v___y_396_ = v_carry_425_;
v___y_397_ = v_t_423_;
goto v___jp_393_;
}
}
v___jp_432_:
{
uint32_t v_e_437_; uint32_t v___x_438_; uint32_t v_s_439_; uint8_t v___x_440_; 
v_e_437_ = lean_uint32_add(v_ev_431_, v___y_433_);
v___x_438_ = 2147483648;
v_s_439_ = lean_uint32_land(v___y_266_, v___x_438_);
v___x_440_ = lean_uint32_dec_le(v___x_391_, v_e_437_);
if (v___x_440_ == 0)
{
uint32_t v___x_441_; uint32_t v___x_442_; uint32_t v___x_443_; uint32_t v___x_444_; uint32_t v_m_445_; uint32_t v___x_446_; uint32_t v___x_447_; uint32_t v___x_448_; uint32_t v___x_449_; 
v___x_441_ = lean_uint32_add(v___y_436_, v___y_434_);
v___x_442_ = lean_uint32_shift_right(v___y_436_, v___y_434_);
v___x_443_ = lean_uint32_land(v___x_442_, v___y_435_);
v___x_444_ = lean_uint32_add(v___x_441_, v___x_443_);
v_m_445_ = lean_uint32_shift_right(v___x_444_, v___y_434_);
v___x_446_ = lean_uint32_sub(v_e_437_, v___y_435_);
v___x_447_ = lean_uint32_shift_left(v___x_446_, v___x_389_);
v___x_448_ = lean_uint32_add(v___x_447_, v_m_445_);
v___x_449_ = lean_uint32_lor(v_s_439_, v___x_448_);
return v___x_449_;
}
else
{
uint32_t v___x_450_; uint32_t v___x_451_; 
v___x_450_ = 2139095040;
v___x_451_ = lean_uint32_lor(v_s_439_, v___x_450_);
return v___x_451_;
}
}
v___jp_452_:
{
uint32_t v___x_460_; uint32_t v___x_461_; uint32_t v_t_462_; uint32_t v___x_463_; uint32_t v_carry_464_; uint8_t v___x_465_; 
v___x_460_ = lean_uint32_shift_right(v___y_458_, v___y_454_);
v___x_461_ = lean_uint32_lor(v___x_460_, v___y_459_);
v_t_462_ = lean_uint32_add(v___y_456_, v___x_461_);
v___x_463_ = 27;
v_carry_464_ = lean_uint32_shift_right(v_t_462_, v___x_463_);
v___x_465_ = lean_uint32_dec_eq(v_carry_464_, v___y_453_);
if (v___x_465_ == 0)
{
uint32_t v___x_466_; uint32_t v___x_467_; uint32_t v___x_468_; 
v___x_466_ = lean_uint32_shift_right(v_t_462_, v___y_457_);
v___x_467_ = lean_uint32_land(v_t_462_, v___y_457_);
v___x_468_ = lean_uint32_lor(v___x_466_, v___x_467_);
v___y_433_ = v_carry_464_;
v___y_434_ = v___y_455_;
v___y_435_ = v___y_457_;
v___y_436_ = v___x_468_;
goto v___jp_432_;
}
else
{
v___y_433_ = v_carry_464_;
v___y_434_ = v___y_455_;
v___y_435_ = v___y_457_;
v___y_436_ = v_t_462_;
goto v___jp_432_;
}
}
v___jp_469_:
{
if (v___y_470_ == 0)
{
goto v___jp_380_;
}
else
{
uint32_t v___x_471_; uint32_t v___x_472_; uint32_t v___x_473_; uint8_t v___x_474_; 
v___x_471_ = 1;
v___x_472_ = lean_uint32_sub(v_ev_431_, v___x_471_);
v___x_473_ = 254;
v___x_474_ = lean_uint32_dec_lt(v___x_472_, v___x_473_);
if (v___x_474_ == 0)
{
goto v___jp_380_;
}
else
{
uint8_t v___x_475_; 
v___x_475_ = lean_uint32_dec_lt(v_eu_392_, v_ev_431_);
if (v___x_475_ == 0)
{
uint32_t v___x_476_; uint32_t v___x_477_; uint8_t v___x_478_; 
v___x_476_ = lean_uint32_sub(v_eu_392_, v_ev_431_);
v___x_477_ = 25;
v___x_478_ = lean_uint32_dec_le(v___x_477_, v___x_476_);
if (v___x_478_ == 0)
{
uint32_t v___x_479_; uint32_t v___x_480_; uint32_t v___x_481_; uint32_t v___x_482_; uint32_t v___x_483_; uint32_t v_a_484_; uint32_t v___x_485_; uint32_t v___x_486_; uint32_t v_b_487_; uint32_t v___x_488_; uint32_t v_mask_489_; uint32_t v___x_490_; uint32_t v___x_491_; uint8_t v___x_492_; 
v___x_479_ = 8388607;
v___x_480_ = lean_uint32_land(v___y_265_, v___x_479_);
v___x_481_ = 8388608;
v___x_482_ = lean_uint32_lor(v___x_480_, v___x_481_);
v___x_483_ = 3;
v_a_484_ = lean_uint32_shift_left(v___x_482_, v___x_483_);
v___x_485_ = lean_uint32_land(v___y_266_, v___x_479_);
v___x_486_ = lean_uint32_lor(v___x_485_, v___x_481_);
v_b_487_ = lean_uint32_shift_left(v___x_486_, v___x_483_);
v___x_488_ = lean_uint32_shift_left(v___x_471_, v___x_476_);
v_mask_489_ = lean_uint32_sub(v___x_488_, v___x_471_);
v___x_490_ = lean_uint32_land(v_b_487_, v_mask_489_);
v___x_491_ = 0;
v___x_492_ = lean_uint32_dec_eq(v___x_490_, v___x_491_);
if (v___x_492_ == 0)
{
v___y_414_ = v___x_483_;
v___y_415_ = v___x_476_;
v___y_416_ = v_a_484_;
v___y_417_ = v_b_487_;
v___y_418_ = v___x_471_;
v___y_419_ = v___x_491_;
v___y_420_ = v___x_471_;
goto v___jp_413_;
}
else
{
v___y_414_ = v___x_483_;
v___y_415_ = v___x_476_;
v___y_416_ = v_a_484_;
v___y_417_ = v_b_487_;
v___y_418_ = v___x_471_;
v___y_419_ = v___x_491_;
v___y_420_ = v___x_491_;
goto v___jp_413_;
}
}
else
{
return v___y_265_;
}
}
else
{
uint32_t v___x_493_; uint32_t v___x_494_; uint8_t v___x_495_; 
v___x_493_ = lean_uint32_sub(v_ev_431_, v_eu_392_);
v___x_494_ = 25;
v___x_495_ = lean_uint32_dec_le(v___x_494_, v___x_493_);
if (v___x_495_ == 0)
{
uint32_t v___x_496_; uint32_t v___x_497_; uint32_t v___x_498_; uint32_t v___x_499_; uint32_t v___x_500_; uint32_t v_a_501_; uint32_t v___x_502_; uint32_t v___x_503_; uint32_t v_b_504_; uint32_t v___x_505_; uint32_t v_mask_506_; uint32_t v___x_507_; uint32_t v___x_508_; uint8_t v___x_509_; 
v___x_496_ = 8388607;
v___x_497_ = lean_uint32_land(v___y_266_, v___x_496_);
v___x_498_ = 8388608;
v___x_499_ = lean_uint32_lor(v___x_497_, v___x_498_);
v___x_500_ = 3;
v_a_501_ = lean_uint32_shift_left(v___x_499_, v___x_500_);
v___x_502_ = lean_uint32_land(v___y_265_, v___x_496_);
v___x_503_ = lean_uint32_lor(v___x_502_, v___x_498_);
v_b_504_ = lean_uint32_shift_left(v___x_503_, v___x_500_);
v___x_505_ = lean_uint32_shift_left(v___x_471_, v___x_493_);
v_mask_506_ = lean_uint32_sub(v___x_505_, v___x_471_);
v___x_507_ = lean_uint32_land(v_b_504_, v_mask_506_);
v___x_508_ = 0;
v___x_509_ = lean_uint32_dec_eq(v___x_507_, v___x_508_);
if (v___x_509_ == 0)
{
v___y_453_ = v___x_508_;
v___y_454_ = v___x_493_;
v___y_455_ = v___x_500_;
v___y_456_ = v_a_501_;
v___y_457_ = v___x_471_;
v___y_458_ = v_b_504_;
v___y_459_ = v___x_471_;
goto v___jp_452_;
}
else
{
v___y_453_ = v___x_508_;
v___y_454_ = v___x_493_;
v___y_455_ = v___x_500_;
v___y_456_ = v_a_501_;
v___y_457_ = v___x_471_;
v___y_458_ = v_b_504_;
v___y_459_ = v___x_508_;
goto v___jp_452_;
}
}
else
{
return v___y_266_;
}
}
}
}
}
}
}
