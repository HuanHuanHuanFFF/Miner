# R 检查点 04：native mul 桥接与张量状态路线

2026-10-21 10:52 UTC。D 已采用 R-03 的 native-add；按反馈，此处只交付研究证明草稿，不增加候选或要求立即排队。

## 乘法的实际缺项

Pinned 版本没有 Native/MulDiv 或 Arithmetic/LeanModel/MulDiv。较新搜索结果不能直接用；旧版 Arithmetic/LeanModel 只有对应实数舍入解释，没有所需完整位等式。

但比对真实 pinned `Model.Spec.mul` 与 Lean4.34 `UnpackedFloat.mul`：两者对有限非零输入都先做精确 mantissa 乘法、exponent 相加，然后同一个 nearest-even round；零输入都用符号乘积／XOR生成带符号零。因此补桥接不需要重证 UInt64 乘法算法或定点舍入，只需有限四分支与表示包装。

已写 `native-mul-bridge-draft.lean`，分三层：

1. `modelMulFinite`：对 `Model.toModel x/y` 作 case；排除 NaN/Inf，剩 zero/zero、zero/finite、finite/zero、finite/finite。逐分支展开 Spec.mul 与 toDyadic?，符号四种组合化简，有限非零分支 round 与 roundWithAccuracy exact 定义归一。
2. `toModelNativeMul`：用 Float32.Model.mul、Model.ofFloat32Model_pack，以及层1连接 native packed model。
3. `ofFloat32Mul`：通过 Configured.Family.toModel_injective 和 ExecFloat mul_spec 提升到 Binary32 等式。

**全份 NOT_COMPILED**。源码名、公开定理均逐个回查原文件；具体 tactic 仍可能需要修复，完整公理审计未运行。若 R-03 失败于 axiom，先按该依赖决定是否整条native路线暂停；若只是语法／API问题，应修复后再判断。

来源正文与URL/SHA：`mul-source-responses.json`、`mul-source-receipts.json`、sources/。证明组织借鉴 pinned Native/AddSub 的公开证明，乘法分支为本次适配；保留FloatLib Team/MIT及Lean原作者归属。

## 若 native-add 通过后，优先保留 native 累加状态

逐元素调用 Binary32→Float32→Binary32 的标量包装仍带转换和重复guard。后续更有潜力的是候选自己的尾递归 `Option Float32` 累加循环：

- 起点 native +0；每步要求 native acc finite、当前输入转换后finite且raw往返相等，再调用已证native add；否则返回 none。
- 最外层 `some v` 用 `ofFloat32 v`，`none` 整体回退原 sum。native加法的有限前提只限制输入，最后一步输出Inf也可合法成功；后续还有元素才触发回退。
- 归纳不变量：若循环返回some结果，它的ofFloat32等于从相同acc开始的原顺序fold；none不作值断言，由外层fallback保证正确性。
- bmm类同：先做独立native mul，乘积finite及acc finite时native add；遇到非finite或round-trip失配，回退整个当前点积。保持每k两个分离舍入，不用FMA。后续还可预转换A/B一次并证明逐元素相等，再减少跨输出重复转换。

这条路线不依赖“所有输入的幅度界保证永不溢出”的长实数证明，也不需偷改官方测试。每步guard与失败回退都在候选实际运行路径内。C验证要确认返回Option只在结束／失败处分配、累加器为原生float，且乘加没有融合；官方完整checksum仍必需。

尚未实现该张量候选；需先有native-add合法性与直接循环结果，控制当前验证积压。
