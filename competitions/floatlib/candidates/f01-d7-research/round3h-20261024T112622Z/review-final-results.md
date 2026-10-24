# RESULTS.md R13 最终只读复核

## 结论

R12/R13 当前源、链接、主要性能值和证据边界整体准确。相关20个本地 Markdown 链接均存在；R12 df5c、R13四个源的SHA和四份结果 JSON 相符。R13 全部四个发现包的 candidate 与 df5c baseline full gate 均通过，四个 discovery ratio 仍高于 0.97，因而“不采用”的结论正确。

## 需要修正的边界表述

1. **M35 把 C 检查写成“证明”容易混淆。** `R13N1Prepared.onePreparedDot_eq`、`row_eq`、`output_eq`、`output_prefix`、`core_eq_reference` 是 Lean 证明；`astra-n1-statement-codegen-1324008.json` 是另一份 statement build 的生成 C 数据流检查，记录行函数将 unboxed `Float32` 作为参数传给列函数。它不证明机器码，也不证明 D9 的计时代码经过相同优化；D9 结果 JSON 明示 `codegen_present=false`。建议将 M35 末句改为：“独立 statement-build 生成 C 审查观察到该 unboxed 参数传递；D9 计时回执未附 codegen，最终编译对象/汇编与机器成本仍 UNKNOWN。”并给 C 审查 JSON 加链接。

2. **补明 N1 路线的 dispatch 范围。** `R13N1Prepared.dispatch` 的新分支只在 `n=1 ∧ p>2` 执行；当前 M35 的“n=1 时”容易读成覆盖所有列宽。建议明确写成“n=1 且 p>2”。D9/1324009 的 exact full gate both 通过；whole ratio `0.9976344726`、BMM `0.993289`、p05 `+0.0019698239`。它仍因 headline ratio 高于 0.97 被拒绝，`local_discovery_screen_passed=false`；建议把正 p05 一并列出，避免误读为统计门槛失败。

3. **3c 正确性范围包含 n=1,p=2，但其 full discovery 没测到这类输入。** `Submission.bmmBeforeUnderflowZero` 的 3c 选路在 `p=2`、`4≤batch*m`、`0<n` 且各 USize 守卫通过时生效；证明对 n=1 有效。可是 `astra-cross-full-1324007.json` 记录该次 plan 的 `eligible_n1_case_count=0`。三seed df5c whole 诊断中，n=1,p=2 的高输出 Cross 只在 seed 1224091 的 dense3 出现（176,454 输出、whole 诊断约3.575%）；这是调用路径/诊断观察，不是 3c 的性能确认。建议在 M34 或邻近结果段加一句，区分“定理/dispatch 可用”与“当前 3c 性能输入覆盖”。R13 的独立 N1 候选只测 n=1,p>2，不覆盖此 p=2 Cross case。

## 核对结果

- M33 名称 `DWordNaN.selected_add/selected_mul`、`ScalarNaN.add_spec/mul_spec`、`nativeMul_spec`、`mul_spec` 与 df5c 源码一致；R12 精确验收链接有效。
- M34 名称 `R13CrossFused.emitRow_prefix/emitBlock_prefix/output_prefix/core_eq_reference` 与 3c 源码一致。whole `1.0014260520`、BMM `1.0089523373`、p05 `+0.0016557436` 与 discovery receipt 一致；正 p05 已正确说明不能代替 0.97 headline 门槛。W8 保留、不可宣称去掉单组 W8 或完全无中间值，当前措辞符合边界。
- R13 四个 whole ratio：708 `1.0034345585` / p05 `-0.0138223552`；252b `1.0016181267` / `-0.0599300367`；3c `1.0014260520` / `+0.0016557436`；8661 `0.9976344726` / `+0.0019698239`。每个均 `full_gate_both=true`、`local_discovery_screen_passed=false`。这是逐候选单 discovery 输入，不是四组确认。
- R13 共享状态记录 10 项 `started_ci`、10 项 `completed_ci`，均 `TERMINAL_COLLECTED_SUCCESS`，`active_ci=[]`；研究轮仍为 `ACTIVE`，deadline 是 2026-10-24 14:26 UTC。没有把窗口写成已结束。df5c/5d946 模型冻结保持，R13 没有采用状态。
- 同宽 scale-fusion 段明确是 8852 个整数模型检查/纸面推导、缺 Lean 证明；浮点跨宽仍为 `Float.toFloat32` opaque 语义桥阻断。profile 段明确为未插桩 whole 诊断份额，不是官方分数。两处边界表述准确。
- 顶部 R13 README 链接存在但文件本身仅是入口；结果判断有 M34/M35 与两条其他候选源码链接支撑。更完整的入口可另补到四份 result JSON 或唯一状态文件，但不是当前结论错误。

本审查只读；没有修改 RESULTS、状态、源码或回执，也没有运行 CI/Lean。研究轮仍开放，不能把 review 当作轮次收尾。
