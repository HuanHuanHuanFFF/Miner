LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_1357_; lean_object* v___x_1358_; 
v___x_1357_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_1358_ = lean_io_getenv(v___x_1357_);
if (lean_obj_tag(v___x_1358_) == 0)
{
lean_object* v___f_1359_; lean_object* v___f_1360_; lean_object* v___x_1361_; lean_object* v___x_1362_; lean_object* v___x_1363_; 
v___f_1359_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_1360_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_1361_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_1362_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_1363_ = lp_competition_Bench_runFull(v___f_1359_, v___f_1360_, v___x_1361_, v___x_1362_);
return v___x_1363_;
}
else
{
lean_object* v___f_1364_; lean_object* v___f_1365_; lean_object* v___x_1366_; lean_object* v___x_1367_; lean_object* v___x_1368_; 
lean_dec_ref_known(v___x_1358_, 1);
v___f_1364_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_1365_ = ((lean_object*)(lp_competition_main___closed__5));
v___x_1366_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_1367_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_1368_ = lp_competition_Bench_Suite_run(v___f_1364_, v___f_1365_, v___x_1366_, v___x_1367_);
return v___x_1368_;
}
}
}
