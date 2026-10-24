# R11 研究提炼与承接边界

本页提炼 W01–W03 原件，并用项目后续回执更新可复用范围；原报告中的 NOT_RUN 保持原义。共同验收口径见[技术规则](../../../docs/track-rules.md)，已验组件总入口仍为 [RESULTS](../../RESULTS.md)。本次仅整理资料，未新增候选、Lean 执行、CI 或性能实验。

## W01：四行双列的真实证明连接

[完整审查](originals/W01/original-extracted/R11-W01/R11-W01-report.md)针对 252609B、SHA `4bdd1e7d…54fa0`：实际 pack 读取 → 每 lane 原序点积 → USize 循环 → 精确 finish → 跨 batch／尾行 → flat 输出 → 原 bmm_spec。可复用的是这些具体接口和逐层义务，不是“pack 正确”的抽象前提。共享 B 必须比较四行各自的实际基址；`batch=2,m=3,n=1,p=2`、A 全1、B=`[1,2,4,8]` 时，跨 batch 的第3行应为 `[4,8]`，全共享首基址会错成 `[1,2]`。

另一边界是尾部虚拟行：U=2^32、m=5、n=858993459 时，真实 A 长度仍小于 U，但虚拟 row7 的 A 基址为6012954213。当前 Nat/getD 总读取有定义；未来迁移到 USize/uget 必须补每次实际读取界，不能沿用长度守卫便直接截断。

网页只有 SOURCE_INSPECTION，条件 `decreasing_by omega` 补丁未采用。后续 [908 回执][r11-908]实际出现三处证明失败；仅修证明的 [5c5e 源码][cross-source]在914完整通过，见[精确验收记录][r11-final]。因此复用应从5c5e开始，保留4bdd失败原件；无需重做网页假设性 termination 修补。

[项目交接][r11-handoff]另纠正原上传上下文的选项名：官方使用 `synthInstance.maxHeartbeats≤400000`，不能照抄网页中的 `maxSynthPendingDepth`。片段检查、statement、kernel replay、公理审计和checksum各自的执行边界仍须保留。

## W02：零列与单非零列的有序摘要

[稀疏报告](originals/W02/R11-W02-report.md)给出：B 全为任意符号零时，A 最早非有限项决定结果；无异常为+0，NaN为原字 quiet 后的值，Inf为 canonical invalid NaN。前提是实际零乘积、+0前缀和分类器最小位置桥均成立；后缀吸收只因每个乘积不再是 sNaN，不能推广到一般 sum。

[本地数学补充][sparse-math]将单非零列摘要压为最早两个非有限 A 位置：排除唯一活跃位置后，两个记录足以找到下一异常。只记一个会失败：A=`[+Inf,qNaN(payload1)]`、B=`[1,+0]`，真实为后者 qNaN，错误摘要返回 Inf。中心仍须执行原 mul/add，不能自选 NaN payload。

网页1555例只是类别规则互比；本地36576例也共用原字算术模型，均非独立 FP 执行器或 Lean 验收。[旧852筛查][sparse-screen]只有2个零列、14个单非零列，覆盖160/262629输出、2080/4294742乘加，分类却需110205次 B 读。性能 UNKNOWN，当前停放。最小承接是先证明分类可融合现有准备且有足够命中，再补真实+0前缀、raw摘要及单非零后缀不变性；尚缺完整 gate 与完整调用成本。

## W03：短 n 去掉 P12 准备对象

[完整报告](originals/W03/original-extracted/R11-W03/R11-W03-report.md)、[候选说明](originals/W03/original-extracted/R11-W03/agent-candidates/candidate-notes.md)的机制仅限 n=1/2 且四个 B 基址相同：显式解码后展开八条原序链，省临时 Array/P12；mixed batch、尾组及长 n 保留回退。A `short-shared` 与 B `short-scalar-call` 是同一算法的两种 lowering。网页精确 A=5645、B=4d77 均未编译；不能继承另一源的通过状态。

[runtime审查](originals/W03/original-extracted/R11-W03/agent-runtime/RUNTIME-AUDIT.md)纠正成本模型：原循环已有八个标量累加器；P12是一个含12个标量字段的对象，不是12个浮点盒。去包仍保留输入转换、F8/W8、finish和原字NaN重放。[编译审查](originals/W03/original-extracted/R11-W03/agent-clang/CLANG_COST_REVIEW.md)指出 Lean noinline 不保证 Clang 保留边界；13个float参数的栈传递只是调用存活时的条件结论。源码预加载也不保证机器无spill。

完全物化的64位 packet Array加P12逻辑体积为 `24+64n` 字节，n1/n2分别88/152；这是布局推算，不是实际可回收流量。实际 finish 用 isNaN 后 toBits，八个非NaN输出仍有八次各类源调用；输入预解码没有消除这些终结成本。direct raw gather则把ofBits转换放回活跃累加期间，须具体查跨调用保存，不能只按少了对象判快。

反例须继续保留：`−0×1` 的乘积为−0，但原 `+0+product` 为+0；n2中 `[-1,1+2^-23]·[1,1−2^-23]` 原序结果为+0，FMA／一次最终舍入得到 `0xa8800000`。不可删初始加法或合并舍入。

集成实际证明修复后的7cad已在916/918完整通过；[918同场对5c5e][short-result]整包1.023697、BMM0.999003、收益p05=−0.028232，未采用。这条旧short路线已试过。再承接须有不同成本机制或覆盖证据，先查实际 bmm caller 的分配、转换位置与终结成本，再决定是否值得完整计时；网页 A/B 无独立增益结论。

## R13：后续负结果约束

以下各精确源与df5c控制均完整 gate通过；比值是同次运行各自对参照归一化后的比较，并非直接候选／控制配对。四条均未过整包≤0.97，未进入独立确认或采用。

| 机制／精确源 | 整包／df5c | BMM／df5c | 原回执 |
|---|---:|---:|---|
| 一次性转换7086 | 1.003435 | 1.005952 | [1324003][r13-3] |
| 短点积复用打包252b | 1.001618 | 1.006563 | [1324005][r13-5] |
| Cross连续输出3c5e | 1.001426 | 1.008952 | [1324007][r13-7] |
| n=1、p>2行共享8661 | 0.997634 | 0.993289 | [1324009][r13-9] |

3c与8661的p05分别为正0.001656、0.001970，仍不满足headline门槛。3c发现组没有n=1 Cross热点，其他同源诊断不能补成其确认。可复用其输出Prefix与行共享等式；最终机器成本、分布变化后的净收益仍 UNKNOWN。后续先核真实覆盖与可移除成本，不重复同源换seed求通过；完整 gate、25轮原边界计时和冻结后的独立确认仍须分别闭合，见[R13结束回执][r13-final]。

R13三组未插桩whole诊断中，n=1、p>2目标仅占1.223%–1.768%；这不是官方计分份额。逐元素探针曾显著放大运行时间，阶段百分比不能直接换算可省收益。8661的statement生成C观察到共享unboxed参数，但计时回执未附codegen，不能由该C推认最终计时对象的机器优化。

[r11-908]: ../../../candidates/f01-d7-research/round7h-20261023T193125Z/result-908-statement.json
[cross-source]: ../../../candidates/f01-r11-crossrow-p2-pack12-proof2/Kernel.lean
[r11-final]: ../../../candidates/f01-d7-research/round7h-20261023T193125Z/README.md
[r11-handoff]: README.md
[sparse-math]: project-evidence/astra-sparse-math.md
[sparse-screen]: project-evidence/astra-sparse-screen.json
[short-result]: ../../../candidates/f01-d7-research/round7h-20261023T193125Z/result-918-f01-r11-crossrow-short-shared-vs-f01-r11-crossrow-p2-pack12-proof2.json
[r13-3]: ../../../candidates/f01-d7-research/round3h-20261024T112622Z/result-1324003-f01-r13-preparation-convert-vs-f01-d12-scalar-combined.json
[r13-5]: ../../../candidates/f01-d7-research/round3h-20261024T112622Z/result-1324005-f01-d13-short-packed-vs-f01-d12-scalar-combined.json
[r13-7]: ../../../candidates/f01-d7-research/round3h-20261024T112622Z/result-1324007-f01-r13-cross-fused-output-vs-f01-d12-scalar-combined.json
[r13-9]: ../../../candidates/f01-d7-research/round3h-20261024T112622Z/result-1324009-f01-r13-n1-prepared-row-output-vs-f01-d12-scalar-combined.json
[r13-final]: ../../../candidates/f01-d7-research/round3h-20261024T112622Z/round-results.json
