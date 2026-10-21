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

## 用户追加两小时后的只读可行性审计

追加截止2026-10-08 15:14:07 +08。本次只读核对Rust6ef、parent e0、meta首稿052及Funs d00全部精确哈希，工作区开始干净、分支codex/round11-frontier；暂不生成Lean/候选，不发CI。下列判断支持投入一次真实gate，不是接受证明。

### 已验证接口与最小适配范围

- 原两个d_dp loopstate实物均9项，wrapper返回形状与e0相同；只有初始化load、gap内block/gap、node处block共四个lemma绑定需要改名，不移植新的outer状态不变量。
- 元数据max helper实物 `(i,maximum,positive)->(maximum,positive)`，meta052的这两条总性lemma可以作为草稿复用；052从未编译，不能按“已通过”处理。
- word inner实物 `(l,flat)->Bool`，outer `(mask,g)->U32`。从两个实际while guard可直接取measure512-l、20-g，inv True；所有数组index都有l<512/g<20或%512范围证据。这里只证明可执行/终止，不把flat/max语义作为总性前提。
- fill实物 `(ring,out,ri,p)->(ring,out)`，post仅out.length，measurehi-p。p加1受p<hi和Usize.max界保护，ri加1受ri<D_RING=1024；endpoint-p及两数组写入均有运行时guard，独立任意helper入参也不需要metadata来源假设。
- groups gap前三loop均四项 `(ring,out,q,nxt)`，loop2最终返回 `(nxt,ring,out)`，word/max/kc是稳定函数参数。前两loop可按原e0证明改名；loop2的seed Array/Slice index_mut back closures要从052借用长度桥接，两个fill仅合成out.length。count>0/count<=q1明确给出lower=q1-count<q1<q_entry，故不需meta版nested q_out<=q_in证明。
- 新loader/block只拼接原d_load、word总性、固定511更新和原bs流程。原公共helpers、Root/checked emitter与LZ77.Obligation/axiom规则保留。

最少新增14条helper/loop specs加2条mut-back桥接，四个外层callee绑定。七个相关loop中，max/前两gap已有同接口证明模式，word两loop、fill、扩展gap loop2是实际新闭合。新来源/最优性/父子全输入token等价没有成为原gate义务，也不得插作前提。

### 风险收窄与尚未编译的部分

unsigned移位API风险已收窄：**parent e0本身1671–1679行已有d1_shr/d1_shl**，调用UScalar.ShiftRight_spec / ShiftLeft_spec，随原pipeline精确pair通过完整gate。新的rhs实物是Usize；constructor g<20推出g<32，query%32给<32，直接复用这两包装，不依赖主分支API猜测。比赛Aeneas完整pin为5b9dcf33dccdb1560ea7203ac57ea202476b6ed3（本地lake-manifest），不修改。

最大余下风险是loop2的mut-back store与两个fill的out-length合成、各lift/bind的战术位置及count减法上下文；这类草稿尚无实际Lean编译。其次d_gap_group实物展开425行，62个if、31个固定非零division、16个d_min调用（短路else复制）；逻辑只是纯totality，但粗暴全展开可能放大term/编译时间。应使用现有d1/d2分支、wrapping lift、常数div和d_min包装局部关闭，必要时抽出重复结果块的辅助totality lemma，不改变Rust。

### 时间判断（推断，不是保证）

首次真实完整gate尝试预计约 **1小时，范围0.75–1.5小时**；在约90分钟验证窗口内有可行路径，但不能保证accepted。时间依据是本仓库：meta首份真实接口草稿准备约6分39秒但未编译；pipeline完整core gate实测542.4秒（含Parse编译374.9秒，排除后续public score/runner启动）。groups比meta多word/group/fill而且group分支展开较大，首稿和静态核对暂估20–35分钟、首次runner准备/core/roundtrip暂留15–25分钟，余量用于一次有根据的编译错误闭合；复杂失败另报剩余，不无限回修。

AA直接查询约3秒， [Coding Agents](https://artificialanalysis.ai/agents/coding-agents) execution-time数据当前显示not publicly available，未获得同gpt-6.1-sol/xhigh/Codex的agent wall-time参考；不套用其他模型或decode-time估计。[方法说明](https://artificialanalysis.ai/methodology/coding-agents-benchmarking)。以上是基于本仓库实物与已观察耗时的临时推断，授权时间本身不当作预测时长。

建议只在独立性能复测仍支持保留源码时投入首稿/真实gate；准备可与复测并行，但此轮授权目前只到可行性审计。若首次编译显示loop2或branch展开需要大改，交付精确error、未闭合义务和剩余预算，不弱化原命题。接受结论必须绑定新Rust/Lean精确pair及官方重提取、原obligation、三个允许公理和完整roundtrip；不能继承e0或有限native/cross-ring结果。

## 有界首稿与停止

主线程随后授权25分钟首稿准备；13:39:29生成Rust6ef逐字副本与Lean `19a72dfdf1440b227c0f0d841495b53cf4b8f29ff6af8f3d1a8ed63ec290f3b2`。14helper/2borrow/4callee只作为UNCOMPILED文本存在，13,918新增字节反转可恢复parent e0，原root/checked emitter suffix不变，无sorry/admit/axiom。没有运行Lean、fullgate或修复；生成时manifest和UNCOMPILED_STATUS保留当时pending状态。

两个独立确认h/i均更慢：对pipeline均值+0.3817614%/+0.3972566%，对同source pipeline-shadow也+0.2523741%/+0.1624838%；四块同输出。来源 `evidence/round11/independent-confirmation.json`。主线程据此停止证明投入，追加 `STOPPED_STATUS.json` 记录最终选择；19a首稿不继续补修或gate。本页此前约1小时是条件化首个gate尝试估计，因性能改变选择而未执行，不是已接受或已编译的声明。
