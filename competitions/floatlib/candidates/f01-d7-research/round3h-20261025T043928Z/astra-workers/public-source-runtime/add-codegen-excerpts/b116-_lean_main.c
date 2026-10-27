LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_1213_; lean_object* v___x_1214_; 
v___x_1213_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_1214_ = lean_io_getenv(v___x_1213_);
if (lean_obj_tag(v___x_1214_) == 0)
{
lean_object* v___f_1215_; lean_object* v___f_1216_; lean_object* v___x_1217_; lean_object* v___x_1218_; lean_object* v___x_1219_; 
v___f_1215_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_1216_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_1217_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_1218_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_1219_ = lp_competition_Bench_runFull(v___f_1215_, v___f_1216_, v___x_1217_, v___x_1218_);
return v___x_1219_;
}
else
{
lean_object* v___f_1220_; lean_object* v___f_1221_; lean_object* v___x_1222_; lean_object* v___x_1223_; lean_object* v___x_1224_; 
lean_dec_ref_known(v___x_1214_, 1);
v___f_1220_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_1221_ = ((lean_object*)(lp_competition_main___closed__5));
v___x_1222_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_1223_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_1224_ = lp_competition_Bench_Suite_run(v___f_1220_, v___f_1221_, v___x_1222_, v___x_1223_);
return v___x_1224_;
}
}
}