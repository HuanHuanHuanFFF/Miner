# RESULTS.md 最小更新提稿（只读审查）

目标是只替换 `competitions/floatlib/research/RESULTS.md` 顶部仍称 R11/6c 为当前采用版本的段落，并在其后加一段 R13 发现状态。保留下方 `K=8eb63a…` 的历史定义、R1–R11 原文与旧suite份额，不把旧份额带入 df5c/R13。

## 建议替换/新增文本

**当前采用（R12）**：精确候选为 [f01-d12-scalar-combined/Kernel.lean](../candidates/f01-d12-scalar-combined/Kernel.lean)，SHA `df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172`（248144 B）。冻结的 D/A/B 三组均通过原版完整 gate 与本地采用门槛（`relative_normalized_ratio ≤ 0.97`、bootstrap `p05 > 0`）：D/40074431355 为 0.887877、p05 0.113671；A/40083425886 为 0.870513、p05 0.137200；B/40083571000 为 0.897198、p05 0.084925。证据见 [三组验证](../candidates/f01-d7-research/round6h-20261024T051445Z/three-group-verification.json)、[独立复核](../candidates/f01-d7-research/round6h-20261024T051445Z/astra-three-group-confirmation-recheck.json) 与 [采纳回执](../candidates/f01-d7-research/round6h-20261024T051445Z/adoption-attempt-20261024T101456Z-d6e3eba7/receipt.json)。

R12 的标量路径复用已有 raw NaN 选择资产：`rawChoose=some` 按原优先级返回所选原始字，`none` 保留认证后的回退；`DWordNaN.selected_add` / `selected_mul`、`ScalarNaN.add_spec` / `mul_spec`、`nativeMul_spec` 与 `mul_spec` 将冷分支和 numericMul 路径接回原规格。单遍求和用 `R7SinglePassSum.native_step_eq`、`repair_quiet`、`natLoop_eq`、`loop_eq` 和 `run_spec` 证明原序更新及 NaN 修复。[3ff4 冷 NaN 候选](../candidates/f01-d12-scalar-cold-nan-select-proof2/Kernel.lean) 是在当前结果守卫中接入既有证明，不作为新发明；最终 df5c 只以已证明等价的 converter 替换 `nativeMul` 输入。精确声明和绑定回执见 [R12 数学结论](../candidates/f01-d7-research/round6h-20261024T051445Z/astra-r12-conclusions.json)。

估算文件 [champion-time-estimate.json](../candidates/f01-d7-research/champion-time-estimate.json) 仍绑定 df5c，SHA `5d946420b8e1a7ecc68aacde44b0e2910a467ee3e3546724d502f252fe8a031f`；它是基于冻结 41-source anchor 的 `INFERRED` 跨suite估算，不是官方同suite成绩。R12 的[官方快照](../candidates/f01-d7-research/round6h-20261024T051445Z/official-refresh-confirmation-20261024T110032Z.json)记录冠军 #285；没有正式提交、夺冠或奖励结论。三组验证表示这份精确源码在冻结输入上的本地结果，不能改写成官方准入或通用成功率。

**R13 发现状态（未采用）**：708 ([source](../candidates/f01-r13-preparation-convert/Kernel.lean))、252b ([source](../candidates/f01-d13-short-packed/Kernel.lean)) 与 3c ([source](../candidates/f01-r13-cross-fused-output/Kernel.lean)) 的精确源码均通过各自完整原版 gate；但相对 df5c 的发现组归一化 whole ratios 分别为 1.003435、1.001618、1.001426，均未达到增量门槛 0.97。对应 `gain_p05` 为 -0.013822、-0.059930、+0.001656；3c 的正 p05 也未弥补 headline ratio 未达标。其证明接口分别包括 `R13NativePrep.toNative_eq` / `bmm_spec`、`RowStream.core_eq_reference` / `bmmBeforeR11Cross_spec`、以及 `R11CrossRows.emitRow_prefix` / `emitBlock_prefix` / `output_prefix` / `core_eq_reference` / `bmm_spec`。完整回执：[708](../candidates/f01-d7-research/round3h-20261024T112622Z/result-1324003-f01-r13-preparation-convert-vs-f01-d12-scalar-combined.json)、[252b](../candidates/f01-d7-research/round3h-20261024T112622Z/result-1324005-f01-d13-short-packed-vs-f01-d12-scalar-combined.json)、[3c](../candidates/f01-d7-research/round3h-20261024T112622Z/result-1324007-f01-r13-cross-fused-output-vs-f01-d12-scalar-combined.json)。这些是不同单seed discovery package 的正确性与性能证据，不是三组确认。N1 [source](../candidates/f01-r13-n1-prepared-row-output/Kernel.lean) (`f01-r13-n1-prepared-row-output`) SHA `8661a3a5a1988b2d6b3d827aa37a7abeb81c50fffabcc38f8c8476961b425e0c` 目前只有 statement run 40097476072 通过；full D9 run 40098465163 尚无终态回执，性能与新汇编均 UNKNOWN，见 [R13 状态](../candidates/f01-d7-research/round3h-20261024T112622Z/astra-status.json)。

**保留缺口**：Float64 跨宽 cast 仍 `BLOCKED`，固定 Lean 接口没有获准的 `Float.toFloat32` 语义桥；同宽 scale-fusion 目前只有 8852 个有限word oracle cases 与纸面推导，不是 Lean 证明、candidate 或完整性能结果。分别见 [跨宽审计](../candidates/f01-d7-research/round3h-20261024T112622Z/profile-scalar-wide-summary.md) 和 [scale-fusion 预检](../candidates/f01-d7-research/round3h-20261024T112622Z/astra-scale-fusion-feasibility.json)。

经验记录保留两点：逐元素阶段探针会显著改变被测整包（本轮示例约 8.00× 与 4.69×），阶段占比只能定位调用族，不能当可移除时间；发现seed、阶段profile和冻结后的 unseen A/B 多seed确认必须分列，不能把单seed路径占比或多个不同candidate的结果合并成普遍收益。

## 依据与边界

- R12 三组 receipt 与最终 adoption review 均绑定 df5c；显示标签后续更新的 receipt 说明 model 数值未改。
- R13 三个结果 JSON 的 `full_gate_both=true` 是两边各自完整 gate 通过；其 `local_discovery_screen_passed=false` 是性能增量筛选未通过。不能把前者写成性能通过。
- D9 当前 status 只证实 run 已识别并等待终态收集；本文不预断该作业结论。
- 本次仅生成提稿与证据索引；没有改写 `RESULTS.md`，没有运行 CI 或 Lean。
