# R25：NativeBinary32 到 ContractExact 输出字

`ContractWordBridge.lean` 仅依赖 ContractExact，4295 B，SHA-256 `9a79cd70b8c33dd28cf15e97850264aa5892fc8bd9e75b42412ab754c6811d9a`。同正文去首行的 `.inc` 为4274 B，SHA `32b7320cad0359fb1427b2ed1cc55e6cb030524a2dd109c6aab3021205882eb4`。12个审计根及固定源blob回执在 `receipt.json`。本文件是小证明探针，没有新Kernel；全部Lean/重放/公理检查NOT_RUN。

| 实际端点 | 薄接口及条件 | 仍需调用方证明 |
|---|---|---|
| `toWord (Model.roundDyadic Fmt d)` | `native_dyadic_result`：NB.roundDyadic d = q即得真实输出q，所有d | NB舍入结果 |
| `toWord (Model.roundRatScaled Fmt s n den e)` | `native_ratScaled_result`：固定源Agreement直接运输，所有参数 | 此rational中间值与实际target的联系 |
| `finishWord T e negZero` | `finishWord_of_native_result`：T≠0，d.toRat=(T:Rat)·2^e，NB.roundDyadic d=q | 实际整数总和和精确dyadic的同值；非零 |
| 同上，实数接口 | `finishWord_of_native_real_result`：用d.toReal=(T:Real)·2^e给同一结果 | 相同的非零条件；由cast运输到有理数等式 |
| 精确总和为零 | `finishWord_exact_zero_native` 使用dyadic符号negZero；`zero_sign_cannot_be_erased`给negZero=true时擦除零符号的直接反例 | 实际dot累积的allTermsNegativeZero/sawFiniteTerm旗标 |
| `dotOf n fa fb` | `dotOf_of_native_nonzero`使用实际Array.ofFn/map后的官方dotState.exact，要求实际输入全部finite、finiteDot ≠ .ok 0及该exact的NB舍入为q | producer等于这份actualDotExact，不能换ghost d；零/NaN/Inf走其它已证路径 |

非零条件约束精确总和T，不约束舍入后q。非零极小输入仍可能舍入为±0，接口允许这一点。T=0时`ofIntDyadic 0 e`总选正号，故不能用于返回负零；代码保留并展示此区别。

08:07补 `DotZeroBridge.lean.inc`（1451 B，SHA `b7d892cb461fb30bb4656c61f8ab4042bb6d39e3b0df9f09a867b45e575867ee`）：实际有限dot的exact.significand=0时，`dotOf`等于`finishWord 0 (-298)`，零符号直接取官方实际dotState的`sawFiniteTerm && allTermsNegativeZero`。这份零端点依赖core及固定Reduction/Proof的`dotWithStatus_eq_zero_of_finite`，没有把自定义producer旗标当已正确；NOT_RUN。另在core显式标明actualDotExact的destination State Fmt，消除不可从Dyadic结果推断目的格式的歧义；最新版哈希见首段。

固定API：FloatLib 0d918257 的 [Narrow/Agreement.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Agreement.lean) 声明 `ofUInt32_roundDyadic`、`ofUInt32_roundRatScaled`；官方accb82b6的 [ExactToolkit/Values.lean](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/accb82b6e2adeda1b41a57a260d68fb3879c427e/lean/contract/ExactToolkit/Values.lean) 声明 `finishWord_of_ne`、`finishWord_zero`。原官方incumbent已使用同一个 `dotWithStatus_eq_round_of_finite_nonzero` 桥；新薄lemma仍需独立编译，不能继承其接受结果。

`RationalDenOneBridge.lean.inc`（737 B，SHA `98ecda089cb57768faaa38289419301fc9df290b7d64558c899407978c80dc10`）是可选17行组合：依赖旧R24DyadicAgreement＋本core，把既有NB.roundRatScaled(sign,num,1,source)=q接到finishWord。旧NB内部agreement仍NOT_RUN，故这份薄组合也NOT_RUN；未拼入独立core，未声称ContractExact整体闭合。

上游Values/Round全文保存于本目录Git忽略的source-private，已核Git blob；公开仅API摘要和哈希。FloatLib Agreement有MIT头，公开原字节保存于sources。冻结的policy1保持SHA82399ee3，未动其预测cast或任何规则/资源；本段未启动本机Lean或新CI。首次工具07:56:17 UTC；共同截止08:19:16 UTC。

