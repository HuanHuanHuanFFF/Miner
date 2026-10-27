LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_2677_; lean_object* v___x_2678_; 
v___x_2677_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_2678_ = lean_io_getenv(v___x_2677_);
if (lean_obj_tag(v___x_2678_) == 0)
{
lean_object* v___f_2679_; lean_object* v___f_2680_; lean_object* v___x_2681_; lean_object* v___x_2682_; lean_object* v___x_2683_; 
v___f_2679_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_2680_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_2681_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_2682_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_2683_ = lp_competition_Bench_runFull(v___f_2679_, v___f_2680_, v___x_2681_, v___x_2682_);
return v___x_2683_;
}
else
{
lean_object* v___f_2684_; lean_object* v___f_2685_; lean_object* v___x_2686_; lean_object* v___x_2687_; lean_object* v___x_2688_; 
lean_dec_ref_known(v___x_2678_, 1);
v___f_2684_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_2685_ = ((lean_object*)(lp_competition_main___closed__5));
v___x_2686_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_2687_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_2688_ = lp_competition_Bench_Suite_run(v___f_2684_, v___f_2685_, v___x_2686_, v___x_2687_);
return v___x_2688_;
}
}
}
