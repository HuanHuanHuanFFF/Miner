LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_2915_; lean_object* v___x_2916_; 
v___x_2915_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_2916_ = lean_io_getenv(v___x_2915_);
if (lean_obj_tag(v___x_2916_) == 0)
{
lean_object* v___f_2917_; lean_object* v___f_2918_; lean_object* v___x_2919_; lean_object* v___x_2920_; lean_object* v___x_2921_; 
v___f_2917_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_2918_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_2919_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_2920_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_2921_ = lp_competition_Bench_runFull(v___f_2917_, v___f_2918_, v___x_2919_, v___x_2920_);
return v___x_2921_;
}
else
{
lean_object* v___f_2922_; lean_object* v___f_2923_; lean_object* v___x_2924_; lean_object* v___x_2925_; lean_object* v___x_2926_; 
lean_dec_ref_known(v___x_2916_, 1);
v___f_2922_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_2923_ = ((lean_object*)(lp_competition_main___closed__5));
v___x_2924_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_2925_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_2926_ = lp_competition_Bench_Suite_run(v___f_2922_, v___f_2923_, v___x_2924_, v___x_2925_);
return v___x_2926_;
}
}
}