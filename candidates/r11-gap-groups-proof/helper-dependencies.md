# groups-d提取前：8–10分钟首稿路径与风险

冻结Rust `6ef07be874052d23fbe3cdca8de7e311e82a306338a93f70389fe35006e99992`。当前只有依赖预排，没有新Lean。实际Funs/Constants/Types一到先核对参数、loopstate、return与borrow，再开始首稿预算；8–10分钟指UNCOMPILED草稿准备，不保证CI编译。

1. d_gap_positive_max及旧gap前两段可复用meta首稿的总性模式；新loader/block仅拼接d_gap_word、固定511更新和原bs调用，不扩d_dp数组/tuple。
2. d_gap_word先按已存在positive-max helper禁用0/>4095，再对20常量group验证。outer measure20-g，inner measure512-l；indices分别受g<20、l<512或%512保护。constructor的 `1u32<<g` 要由g<20推出g<32；mask<<12是固定IScalar移位。
3. U32 unsigned-variable移位可用Std的 `U32.ShiftLeft_spec` / `U32.ShiftRight_spec`，post降为True，界来自g<20或rhs%32<32。API按 [Aeneas Bitwise](https://github.com/AeneasVerif/aeneas/blob/main/backends/lean/Aeneas/Std/Scalar/Bitwise.lean) 主源码核对；比赛pin是否一致仍需真实编译，不能当已通过。
4. d_gap_group全部区间分支使用wrapping加减乘、常数非零除法和已有d_min；仅证明forall totality，不需把“group_end正确”作为原obligation前提。
5. d_gap_group_fill显式while p<hi、p<out.length、ri<D_RING、endpoint>=p。post仅out.length保持；measure hi-p，p加1由p<hi且hi<=Usize.max，ri加1由ri<1024闭合。ring update以ri<1024，out update以p<len，endpoint-p以端点guard闭合；不需要literal/group来源假设。
6. 第三gap段先原scalar seed使q减1。只有count>0且count<=q才做lower=q-count，由lower+count=q与count>0得到lower<q；两次fill的out-length post合成。否则返回scalar seed状态。无嵌套fill返回游标的桥接，不需meta版q_out<=q_in invariant。
7. final nxt使用wrapping end-lower，planner总性不要求语义证明；源级合法调用下endpoint>=seed q>=lower、group验证与价格守卫保证完整cell一致。元数据来源和升序写语义属于另一个说明，不能混为out-length totality。

主要未验证风险：constructor/query变量U32移位在实际Funs中的rhs类型与library名称；group-validation内层return是否只保留flat；fill的p/ri state顺序及双增绑定；outer seed的Array/Slice.index_mut back closures与两次fill返回；外层q减count的tactic上下文。旧两个d_dp九项state预计只四个callee binding迁移，实际接口变化则以实物为准。无sorry/新axiom/原义务弱化；若首稿不能在预算内或CI错误复杂，准确交付未闭合。
