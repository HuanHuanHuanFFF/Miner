# 实际调用边界：已有证据与下一次必须看的位置

旧 40432634558 完整计时 Main 的原 C／ASM 已通过只读 GitHub blob 接口恢复到本目录，未操作 Git CLI／index；两份 SHA 与维护索引和原 CI 清单相符。`review_historical.py` 当前重新核对原字节并导出选中 callback 与 58 条实际接受路径，结果见 `historical-review.json`。这里不是只信旧报告：五个 push/pop、16B frame、接受路径一 imul 且无 FP/call/table/显式数据 spill 均从恢复的实际 Main ASM 复核。原 ELF 未提供，不冒充本地重哈希 ELF。

固定 Lean 293d5d0c 源的 InlineAttrs、InlineCandidate、EmitC、ExplicitBoxing 已逐字核对其原下载 manifest；四个哈希在 historical-review 中。LCNF InlineCandidate 对 noinline 返回 false，而 EmitC 该处只生成 `LEAN_EXPORT` 函数声明／定义，未添加 native noinline 属性。因此新 source 上的属性并不能单独证明最终热路径隔离。这里真正可行的边界是：Submission 的 retainedMul 经过 Lean noinline 保留为静态二参数调用，在独立编译的 Main C 中只有声明与调用；既有真实 flags 为独立 -c -O3、无 LTO。仍应核下次实际 trace/响应文件，不能把此条件默认为永远成立。

预期的 Main selected C 是：接受分支展开全部 guard 和 normalCore，miss 分支调用 `lp_competition_Submission_R22OutlineMul_retainedMul(uint32_t,uint32_t)`；返回后不读输入、不校验、不装箱中间结果，后端才有把 miss 写成尾跳的条件。Binary32 的标量表示在旧实际 C 是 uint32_t，原 `normalCore` 也是 uint32_t 返回；新 retainedMul 是否保留这个签名仍是待验。即使 `Submission.R22OutlineMul.guardedMul` 的独立符号变小，也不能代替 Main selected callback 的 ABI 与路径。

`CallerAliases.lean.inc` 提供在同一新 carrier、同一 Main 中比较的两个 inline alias：`r22CostOriginalGuardedMul` 逐字保留旧 guards，并在 miss 直接内联 B2；`r22CostOutlinedMul` 仅把 miss 静态送进 retainedMul。二者共享精确 normalCore。末尾 rfl 仅是“新边界不改旧诊断算术”结构桥草稿，NOT_COMPILED，不是新乘法规范证明。D 可将二者接入当前同 binary 框架，也可只选 outlined 对原 control；若接三者则原始顺序、计时预算与发现种子均应记录，不借旧 748999 block 作同机配对。

旧 Main 的 arity3 captured Bool 限制继续存在于旧证据：新 Main 若还采用同一选择方式，应记录它；若改成静态 arity2，则是新的 caller 条件，不能同时宣称只改 cold boundary。每一候选的实际闭包／boxed wrapper／typed signature 都要绑定具体 C/ASM；共享入口参数也可能改变寄存器压力。任何布局都保留完整 Suite 的 timer/pass/checksum/cleanup 口径。

这里的 Bool 是外层 BENCH_VARIANT 比较在已选分支中已知为 true 的结果，被内联体复用为条件的 true 返回值；**不是每次标量调用都动态选择 MUL 变体**。旧404326中 guarded 捕获 `lean_box(v___x_3968_)`，control捕获 `lean_box(v___x_3966_)`。`inventory_callbacks.py` 的 dynamic_closure_sites 指运行时构造闭包站点，不指每scalar变体选择。D另在406023的实际ownedMain保留了四处复用，见父目录 `development-captured-variant-callback-scope.json`。旧性能数据一律不删除或改分。

D已派发40607316341，不取消。现有premeasurement checker只扫描lean_alloc_closure，静态literal的固定参数需在回执后补核。旧实际C的fixed0模板为closed7→ADD lam0 boxed/arity2，closed8→Submission.sum boxed/arity2，closed9→Submission.bmm/arity6；详见 `old-static-fixed0-template.json`。这三个不含MUL；两个MUL是前述动态构造的arity3/fixed1。新回执须同时扫描static const lean_closure_object和lean_alloc_closure，逐五个runner的真实Suite参数追到typed body，再看cold尾跳和实际热路径，不能只按名称选择symbol。

冷边界也可能增加工作，不能只数被删的 frame。旧选中 `main___lam__1` 在入口把 eu/ev 放入 r15d/r12d，x guard miss 的 `0x2f`、y guard miss 的 `0x8e`、sum miss 的 `0x135` 都继续使用已经算出的指数和／字段进入 B2。新二参数 wrapper 只收到原 x/y，独立 B2 可能重新提取这些字段；这项跨函数 CSE 损失须由 actual code 和完整 miss 成本回答。`guard-domain-partition.json` 从已见 discovery1/3 的精确生成器 source 和 case 参数给出保守区间：每组42个timed MUL中20个全域接受，3或4个全域回退，其余混合／UNKNOWN；只是case/work分类，不是频率采样、CPU时间占比或收益上界。
