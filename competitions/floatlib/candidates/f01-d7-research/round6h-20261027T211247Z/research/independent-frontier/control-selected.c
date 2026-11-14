LEAN_EXPORT uint32_t lp_competition_main___lam__2(uint32_t v___y_2486_, uint32_t v___y_2487_){
_start:
{
uint8_t v___y_2494_; uint8_t v___y_2508_; uint8_t v___y_2522_; uint8_t v___y_2539_; float v___y_2546_; float v___y_2547_; float v___y_2561_; uint8_t v___y_2562_; float v___y_2577_; uint8_t v___y_2587_; uint32_t v___x_2601_; uint32_t v_a_2602_; uint32_t v___x_2603_; uint32_t v___x_2604_; uint32_t v___x_2605_; uint8_t v___x_2606_; 
v___x_2601_ = 2147483647;
v_a_2602_ = lean_uint32_land(v___y_2486_, v___x_2601_);
v___x_2603_ = 201326591;
v___x_2604_ = 1;
v___x_2605_ = lean_uint32_sub(v_a_2602_, v___x_2604_);
v___x_2606_ = lean_uint32_dec_le(v___x_2603_, v___x_2605_);
if (v___x_2606_ == 0)
{
v___y_2587_ = v___x_2606_;
goto v___jp_2586_;
}
else
{
uint32_t v___x_2607_; uint8_t v___x_2608_; 
v___x_2607_ = 2139095040;
v___x_2608_ = lean_uint32_dec_lt(v_a_2602_, v___x_2607_);
v___y_2587_ = v___x_2608_;
goto v___jp_2586_;
}
v___jp_2488_:
{
lean_object* v___x_2489_; lean_object* v___x_2490_; lean_object* v___x_2491_; uint32_t v___x_2492_; 
v___x_2489_ = lean_uint32_to_nat(v___y_2486_);
v___x_2490_ = lean_uint32_to_nat(v___y_2487_);
v___x_2491_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_2489_, v___x_2490_);
v___x_2492_ = lean_uint32_of_nat(v___x_2491_);
lean_dec(v___x_2491_);
return v___x_2492_;
}
v___jp_2493_:
{
if (v___y_2494_ == 0)
{
goto v___jp_2488_;
}
else
{
uint32_t v___x_2495_; uint32_t v___x_2496_; 
v___x_2495_ = 4194304;
v___x_2496_ = lean_uint32_lor(v___y_2487_, v___x_2495_);
return v___x_2496_;
}
}
v___jp_2497_:
{
uint32_t v___x_2498_; uint32_t v___x_2499_; uint32_t v___x_2500_; uint32_t v___x_2501_; uint8_t v___x_2502_; 
v___x_2498_ = 23;
v___x_2499_ = lean_uint32_shift_right(v___y_2487_, v___x_2498_);
v___x_2500_ = 255;
v___x_2501_ = lean_uint32_land(v___x_2499_, v___x_2500_);
v___x_2502_ = lean_uint32_dec_eq(v___x_2501_, v___x_2500_);
if (v___x_2502_ == 0)
{
v___y_2494_ = v___x_2502_;
goto v___jp_2493_;
}
else
{
uint32_t v___x_2503_; uint32_t v___x_2504_; uint32_t v___x_2505_; uint8_t v___x_2506_; 
v___x_2503_ = 8388607;
v___x_2504_ = lean_uint32_land(v___y_2487_, v___x_2503_);
v___x_2505_ = 0;
v___x_2506_ = lean_uint32_dec_eq(v___x_2504_, v___x_2505_);
if (v___x_2506_ == 0)
{
v___y_2494_ = v___x_2502_;
goto v___jp_2493_;
}
else
{
goto v___jp_2488_;
}
}
}
v___jp_2507_:
{
if (v___y_2508_ == 0)
{
goto v___jp_2497_;
}
else
{
uint32_t v___x_2509_; uint32_t v___x_2510_; 
v___x_2509_ = 4194304;
v___x_2510_ = lean_uint32_lor(v___y_2486_, v___x_2509_);
return v___x_2510_;
}
}
v___jp_2511_:
{
uint32_t v___x_2512_; uint32_t v___x_2513_; uint32_t v___x_2514_; uint32_t v___x_2515_; uint8_t v___x_2516_; 
v___x_2512_ = 23;
v___x_2513_ = lean_uint32_shift_right(v___y_2486_, v___x_2512_);
v___x_2514_ = 255;
v___x_2515_ = lean_uint32_land(v___x_2513_, v___x_2514_);
v___x_2516_ = lean_uint32_dec_eq(v___x_2515_, v___x_2514_);
if (v___x_2516_ == 0)
{
v___y_2508_ = v___x_2516_;
goto v___jp_2507_;
}
else
{
uint32_t v___x_2517_; uint32_t v___x_2518_; uint32_t v___x_2519_; uint8_t v___x_2520_; 
v___x_2517_ = 8388607;
v___x_2518_ = lean_uint32_land(v___y_2486_, v___x_2517_);
v___x_2519_ = 0;
v___x_2520_ = lean_uint32_dec_eq(v___x_2518_, v___x_2519_);
if (v___x_2520_ == 0)
{
v___y_2508_ = v___x_2516_;
goto v___jp_2507_;
}
else
{
goto v___jp_2497_;
}
}
}
v___jp_2521_:
{
if (v___y_2522_ == 0)
{
goto v___jp_2511_;
}
else
{
uint32_t v___x_2523_; uint32_t v___x_2524_; uint32_t v___x_2525_; uint8_t v___x_2526_; 
v___x_2523_ = 4194304;
v___x_2524_ = lean_uint32_land(v___y_2487_, v___x_2523_);
v___x_2525_ = 0;
v___x_2526_ = lean_uint32_dec_eq(v___x_2524_, v___x_2525_);
if (v___x_2526_ == 0)
{
goto v___jp_2511_;
}
else
{
uint32_t v___x_2527_; 
v___x_2527_ = lean_uint32_lor(v___y_2487_, v___x_2523_);
return v___x_2527_;
}
}
}
v___jp_2528_:
{
uint32_t v___x_2529_; uint32_t v___x_2530_; uint32_t v___x_2531_; uint32_t v___x_2532_; uint8_t v___x_2533_; 
v___x_2529_ = 23;
v___x_2530_ = lean_uint32_shift_right(v___y_2487_, v___x_2529_);
v___x_2531_ = 255;
v___x_2532_ = lean_uint32_land(v___x_2530_, v___x_2531_);
v___x_2533_ = lean_uint32_dec_eq(v___x_2532_, v___x_2531_);
if (v___x_2533_ == 0)
{
v___y_2522_ = v___x_2533_;
goto v___jp_2521_;
}
else
{
uint32_t v___x_2534_; uint32_t v___x_2535_; uint32_t v___x_2536_; uint8_t v___x_2537_; 
v___x_2534_ = 8388607;
v___x_2535_ = lean_uint32_land(v___y_2487_, v___x_2534_);
v___x_2536_ = 0;
v___x_2537_ = lean_uint32_dec_eq(v___x_2535_, v___x_2536_);
if (v___x_2537_ == 0)
{
v___y_2522_ = v___x_2533_;
goto v___jp_2521_;
}
else
{
goto v___jp_2511_;
}
}
}
v___jp_2538_:
{
if (v___y_2539_ == 0)
{
goto v___jp_2528_;
}
else
{
uint32_t v___x_2540_; uint32_t v___x_2541_; uint32_t v___x_2542_; uint8_t v___x_2543_; 
v___x_2540_ = 4194304;
v___x_2541_ = lean_uint32_land(v___y_2486_, v___x_2540_);
v___x_2542_ = 0;
v___x_2543_ = lean_uint32_dec_eq(v___x_2541_, v___x_2542_);
if (v___x_2543_ == 0)
{
goto v___jp_2528_;
}
else
{
uint32_t v___x_2544_; 
v___x_2544_ = lean_uint32_lor(v___y_2486_, v___x_2540_);
return v___x_2544_;
}
}
}
v___jp_2545_:
{
float v_result_2548_; uint8_t v___x_2549_; 
v_result_2548_ = lean_float32_add(v___y_2546_, v___y_2547_);
v___x_2549_ = lean_float32_beq(v_result_2548_, v_result_2548_);
if (v___x_2549_ == 0)
{
uint32_t v___x_2550_; uint32_t v___x_2551_; uint32_t v___x_2552_; uint32_t v___x_2553_; uint8_t v___x_2554_; 
v___x_2550_ = 23;
v___x_2551_ = lean_uint32_shift_right(v___y_2486_, v___x_2550_);
v___x_2552_ = 255;
v___x_2553_ = lean_uint32_land(v___x_2551_, v___x_2552_);
v___x_2554_ = lean_uint32_dec_eq(v___x_2553_, v___x_2552_);
if (v___x_2554_ == 0)
{
v___y_2539_ = v___x_2554_;
goto v___jp_2538_;
}
else
{
uint32_t v___x_2555_; uint32_t v___x_2556_; uint32_t v___x_2557_; uint8_t v___x_2558_; 
v___x_2555_ = 8388607;
v___x_2556_ = lean_uint32_land(v___y_2486_, v___x_2555_);
v___x_2557_ = 0;
v___x_2558_ = lean_uint32_dec_eq(v___x_2556_, v___x_2557_);
if (v___x_2558_ == 0)
{
v___y_2539_ = v___x_2554_;
goto v___jp_2538_;
}
else
{
goto v___jp_2528_;
}
}
}
else
{
uint32_t v___x_2559_; 
v___x_2559_ = lean_float32_to_bits(v_result_2548_);
return v___x_2559_;
}
}
v___jp_2560_:
{
if (v___y_2562_ == 0)
{
float v___x_2563_; 
v___x_2563_ = lean_float32_of_bits(v___y_2487_);
v___y_2546_ = v___y_2561_;
v___y_2547_ = v___x_2563_;
goto v___jp_2545_;
}
else
{
uint32_t v___x_2564_; uint32_t v___x_2565_; uint32_t v___x_2566_; uint32_t v___x_2567_; float v___x_2568_; lean_object* v___x_2569_; uint32_t v___x_2570_; uint32_t v___x_2571_; lean_object* v___x_2572_; lean_object* v___x_2573_; float v___x_2574_; float v___x_2575_; 
v___x_2564_ = 8388607;
v___x_2565_ = lean_uint32_land(v___y_2487_, v___x_2564_);
v___x_2566_ = 8388608;
v___x_2567_ = lean_uint32_lor(v___x_2565_, v___x_2566_);
v___x_2568_ = lean_uint32_to_float32(v___x_2567_);
v___x_2569_ = lp_competition_R2W01b_scaleTable;
v___x_2570_ = 23;
v___x_2571_ = lean_uint32_shift_right(v___y_2487_, v___x_2570_);
v___x_2572_ = lean_uint32_to_nat(v___x_2571_);
v___x_2573_ = lean_array_fget_borrowed(v___x_2569_, v___x_2572_);
lean_dec(v___x_2572_);
v___x_2574_ = lean_unbox_float32(v___x_2573_);
v___x_2575_ = lean_float32_mul(v___x_2568_, v___x_2574_);
v___y_2546_ = v___y_2561_;
v___y_2547_ = v___x_2575_;
goto v___jp_2545_;
}
}
v___jp_2576_:
{
uint32_t v___x_2578_; uint32_t v_a_2579_; uint32_t v___x_2580_; uint32_t v___x_2581_; uint32_t v___x_2582_; uint8_t v___x_2583_; 
v___x_2578_ = 2147483647;
v_a_2579_ = lean_uint32_land(v___y_2487_, v___x_2578_);
v___x_2580_ = 201326591;
v___x_2581_ = 1;
v___x_2582_ = lean_uint32_sub(v_a_2579_, v___x_2581_);
v___x_2583_ = lean_uint32_dec_le(v___x_2580_, v___x_2582_);
if (v___x_2583_ == 0)
{
v___y_2561_ = v___y_2577_;
v___y_2562_ = v___x_2583_;
goto v___jp_2560_;
}
else
{
uint32_t v___x_2584_; uint8_t v___x_2585_; 
v___x_2584_ = 2139095040;
v___x_2585_ = lean_uint32_dec_lt(v_a_2579_, v___x_2584_);
v___y_2561_ = v___y_2577_;
v___y_2562_ = v___x_2585_;
goto v___jp_2560_;
}
}
v___jp_2586_:
{
if (v___y_2587_ == 0)
{
float v___x_2588_; 
v___x_2588_ = lean_float32_of_bits(v___y_2486_);
v___y_2577_ = v___x_2588_;
goto v___jp_2576_;
}
else
{
uint32_t v___x_2589_; uint32_t v___x_2590_; uint32_t v___x_2591_; uint32_t v___x_2592_; float v___x_2593_; lean_object* v___x_2594_; uint32_t v___x_2595_; uint32_t v___x_2596_; lean_object* v___x_2597_; lean_object* v___x_2598_; float v___x_2599_; float v___x_2600_; 
v___x_2589_ = 8388607;
v___x_2590_ = lean_uint32_land(v___y_2486_, v___x_2589_);
v___x_2591_ = 8388608;
v___x_2592_ = lean_uint32_lor(v___x_2590_, v___x_2591_);
v___x_2593_ = lean_uint32_to_float32(v___x_2592_);
v___x_2594_ = lp_competition_R2W01b_scaleTable;
v___x_2595_ = 23;
v___x_2596_ = lean_uint32_shift_right(v___y_2486_, v___x_2595_);
v___x_2597_ = lean_uint32_to_nat(v___x_2596_);
v___x_2598_ = lean_array_fget_borrowed(v___x_2594_, v___x_2597_);
lean_dec(v___x_2597_);
v___x_2599_ = lean_unbox_float32(v___x_2598_);
v___x_2600_ = lean_float32_mul(v___x_2593_, v___x_2599_);
v___y_2577_ = v___x_2600_;
goto v___jp_2576_;
}
}
}
}
