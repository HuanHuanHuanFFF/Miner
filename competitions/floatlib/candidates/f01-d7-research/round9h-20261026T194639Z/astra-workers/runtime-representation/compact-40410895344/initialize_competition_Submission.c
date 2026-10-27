LEAN_EXPORT lean_object* initialize_competition_Submission(uint8_t builtin) {
lean_object * res;
if (_G_initialized) return lean_io_result_mk_ok(lean_box(0));
_G_initialized = true;
lean_initialize();
res = initialize_Init(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = initialize_Init(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = initialize_competition_ContractTensor(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
lp_competition_R2W01b_scaleTable = _init_lp_competition_R2W01b_scaleTable();
lean_mark_persistent(lp_competition_R2W01b_scaleTable);
lp_competition_R19CompactScales_packed = _init_lp_competition_R19CompactScales_packed();
lean_mark_persistent(lp_competition_R19CompactScales_packed);
lp_competition_R19CompactScales_valid = _init_lp_competition_R19CompactScales_valid();
lp_competition_Submission_FastMul_Plan = _init_lp_competition_Submission_FastMul_Plan();
lp_competition_Submission_Packed10_zero32 = _init_lp_competition_Submission_Packed10_zero32();
lp_competition_Submission_Packed10_zero10 = _init_lp_competition_Submission_Packed10_zero10();
lean_mark_persistent(lp_competition_Submission_Packed10_zero10);
lp_competition_Submission_UnderflowZero_zeros___boxed__const__1 = _init_lp_competition_Submission_UnderflowZero_zeros___boxed__const__1();
lean_mark_persistent(lp_competition_Submission_UnderflowZero_zeros___boxed__const__1);
return lean_io_result_mk_ok(lean_box(0));
}
