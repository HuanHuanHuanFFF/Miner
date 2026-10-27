# R19 独立静态审阅：peer `Kernel-direct-bias-public-v1.lean`（2026-10-27T00:32Z）

对象：`D:/CodingProject/Bitget/.../astra-workers/exact-arithmetic/bias-frontier/public-proof-review1/Kernel-direct-bias-public-v1.lean`
（只读；peer 声明 SHA `fa6529613fe10bd431ead1511900be989c2b80976423b31d90747f8651f37ac5`，255311 B）

## 已核对

| 项 | 结果 |
|---|---|
| SHA-256 / 字节 | **一致**（fa652961…，255311） |
| `sorry` / `admit` / `axiom` / `constant` / `unsafe` / `implemented_by` / `native_decide` | **0 处** |
| import | 仅 `import ContractTensor` |
| 四个规格端点 | `Submission.add_spec`/`mul_spec`/`sum_spec`/`bmm_spec` 均存在，语句与官方签名一致 |
| mul 接线 | `Submission.mul = R19BiasBase.R19DirectBias.guardedMul R19BiasBase.mul`，证明 `guardedMul_spec R19BiasBase.mul R19BiasBase.mul_spec` |
| add/sum/bmm 出口 | 均 alias 到 `R19BiasBase.*`，无新运行逻辑 |
| B2 基础 | `R19BiasBase.bmm` 的分派/下溢零/证明与 B2 `Submission.bmm` **逐字相同**（仅 namespace 名不同） |
| `guardedMul` 结构 | 参数 `(fallback)`，先走 DirectBias 分支，失败回退 `fallback`；`guardedMul_spec` 用 fallback 的 spec 闭合 |

## 未核对 / 风险

- 无编译：所有结论为静态；声明/重放/根数仍以他们 statement/full gate 为准。
- 未逐字比对整个 `R19BiasBase` 与 B2（文件带裁剪与新增 bias 代码，255311 vs 226829 B）；
  只核了 bmm 出口与最终 alias 层。
- `guardedMul` 的“运行域/回退不变”依赖其分支条件与 proof；建议他们给出分支条件的
  最小反例集（NaN/Inf/subnormal/极端 bias）作为 A/B 前的前置检查。
- 255311 B 接近 256000 B 上限（余 689 B），任何后续补丁都要先查字节数。

## 结论

静态层面未发现禁用公理、未闭合端点或明显循环证明；mul 之外没有可见的运行改动。
正式结论仍需他们自己的 gate/重放/计时；本审阅不替代任何验证。
