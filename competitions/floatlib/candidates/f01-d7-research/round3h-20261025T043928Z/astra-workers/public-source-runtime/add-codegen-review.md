# b116 / f529 的 ADD 源码与真实选中 C 对照

2026-10-25 06:13:04Z开始，只读原始产物；本次没有新候选、编译、Lean、runner、Git或CI。已有结果记录两项完整正确性gate通过、首次D性能门槛失败，这两个层次保持原样。

**结论：所查 public add、其前置helper源码、实际选中的add函数C体和常量表构造C没有差异。两个boxed适配器仅局部标识名不同；MainFull调用入口也只局部标识名不同。可以排除这些源码/诊断C体变化，不能由此把约7%的归一化ADD差距归因CPU噪声，或宣称本轮timed机器码相同。**

## 版本及计时边界

本方逐字节确认：本地Kernel、40166091242 statement诊断保存输入、40166656717完整D保存输入三处对应文件相同：

| 候选 | 精确Kernel SHA | bytes | 完整D whole | ADD归一化 |
|---|---|---:|---:|---:|
| column-pairs2 | b116067185626ccb758fbadd608ce7514cb1ddef70ddd0a07e1596f8c776952b | 217371 | 1.0312472485 | 1.0705879402 |
| mul-branchless1 | f529f4d4a693b6bee91aa10882237d30112637383cb447f3037057ff9bdb70d9 | 236154 | 1.2448032060 | 1.0018813774 |

两项发现组结果明确 `codegen_present=false`。本报告使用的是**同Kernel、此前40166091242诊断statement构建的C**，绝非40166656717已清理的timed对象，也没有借用旧df5c C。

ADD归一化结果之比是1.0685775425，即b116相对f529约高6.86%。这些数值来自各候选对参照、再对DF的归一化，不是候选之间直接配对的同一个计时进程。两个完整D仍失败，不因本报告删掉任何慢样本或另换seed。

## Lean源码：整个ADD依赖前缀相同

两份Kernel最初119108字节相同，首次差异在第3064行的MUL相关定义。直到public add/spec结束、下一个nativeMul定义开始的118185字节完全相同，SHA：

`3074f8bb885070e6300824f0499a459c7ef4eff93165e8b0d21e026e8c601f26`

该相同前缀包含R7W04.nonNaN、R2W01b的fastOK/magnitude/mantissa/tableIndex/scaleBits/scaleTable/scaleAt/tableProduct/convert、DWordNaN.rawChoose、ScalarNaN.add，以及它们之前的声明。public add及其spec本身在3023–3043行，883B，原字节SHA：

`3150c18a71716ed42bf55327076a1288d771213878c7539ab749d9bc2fc71c6e`

这比只看到同名add更强：本地前置定义的文本也一致。导入仍是同一ContractTensor；这里未重新导出所有外部库callee机器码。

## 真正选中的add入口

两份MainFull.c均在BENCH_PLAN存在时沿：
`_lean_main → Bench.Suite.run第一个实参closed__1 → main___lam__0___boxed → main___lam__0`。

closed__1的closure声明逐字节一致；boxed adapter在409–421行；真正内联ADD实现的unboxed lambda在75–408行。不是只比较没有被选择的Submission.add或generic包装。

| C体 | b116 / f529 原行 | 原字节关系 | SHA-256 |
|---|---|---|---|
| selected main___lam__0 | 两者75–408 | **完全相同，8286B** | 7888289dc32091fa85b4dab9af02f11081a133b51cd23dd7c486036f9b9f269f |
| Submission.add export | 21192–21526 / 21222–21556 | **完全相同，9071B** | 0a3d819a71fdacbc12137c91b7c58be235056cbdf323e2e86de7169ebe99ce37 |
| main___lam__0___boxed | 两者409–421 | 541B；仅两个local名字不同 | b116: c7c0a551d7d342797b9794d1db7dede645fd14b54d790a1ef0c92f64379cb44f；f529: 0960951487a54c2017b374125ff2ec4ca2b0f81253607257303e33ca1f616f47 |
| _lean_main | 3794–3822 / 8590–8618 | 1314B；local编号不同 | 详见JSON，alpha后相同 |

boxed中只出现如下重命名，类型、调用顺序、callee和常量未变：
`v___y_4533__boxed_126_ → v___y_8953__boxed_126_`、
`v___y_4534__boxed_127_ → v___y_8954__boxed_127_`。
原diff保存于[适配器差异](add-codegen-excerpts/lp_competition_main___lam__0___boxed.raw.diff)。

有限SSA归一化只按首次出现顺序重命名`v_*`局部值/参数/join标签，随后压缩空白；**不改callee/global名字、常量、运算符、类型、控制流顺序**。selected lambda本就原字节相等，归一化不增加其结论；boxed与_lean_main经此处理后相同。

selected lambda alpha SHA：
`83c47d6aabe6c911d8c0f79f3180fc7af337009deec4b98db7fbf829a8efbc8d`

boxed alpha SHA：
`2edbadb4953987498acffc6fdb1e8fef62adf8ad9248fdcb082347e495946be8`

## 表和hot helper：已核到的层次

另外逐函数提取对照了ScalarNaN.add、DWordNaN.rawChoose、R2W01b.convert/tableProduct/scaleAt、scaleTable元素lambda、两个scaleTable初始化函数、R7W04.nonNaN。**这些C体全部原字节相同**，不只是alpha相同；完整行号、大小和hash在[add-codegen-comparison.json](add-codegen-comparison.json)。

其中scaleTable元素生成函数1383B，SHA `38d5c00b1a3f8a63581f274c3314da0ccc37eb5a98414a0c7f1daef7915b672c`；table初始化373B和306B也各自相同。因此没有观察到表构造逻辑差异、helper内联展开差异或ADD所用符号/常量差异。

**仍未知**：

- 40166656717 timed程序的ADD机器指令、函数对齐、整个可执行文件布局与编译器上下文优化；
- 同样的table构造代码在两个不同程序中的实际地址、缓存状态和初始化/驻留情形；
- Bench.Suite外部调用循环与导入库callee的最终机器码；MainFull调用表达式相同不能覆盖全部传递依赖；
- 实际CPU频率、调度、缓存、测量顺序和参照归一化对这次差异的因果贡献。

不同整包内容可能改变上述条件；这只是未排除集合，不是已证实解释。C相同也不推出timed ELF相同，alpha相同更不能证明CPU噪声。

## 交接结论

本轮可以排除“b116不小心改了public add/前置hot helper”和“此前诊断构建给ADD生成了不同函数体”这两类解释。不能排除最终编译/布局/测量上下文差异，也不能识别约6.86%差距的具体来源。

保留两项失败D、原逐项数据与明确UNKNOWN。没有请求或启动重试。后续研究记录可使用本次同源码、同选中诊断C而不同完整测量结果的事实；若未来已有合法保留的timed对象，才可继续比机器码，本报告不因此新建runner。

