# Run 2 运行计划：public-v2 嵌套入口（DeepSeek）

前提：run 40123953691（旧 pins 十二类 + 通用诊断）终态并回收后派发。

## 为什么用嵌套入口

`floatlib-validate.yml` 直接传普通候选时跑的是 pins `978cc5b4` 的旧十二类；当前计分口径是
`4b7e8384` 的 public-v2。现有仓库路径是 `candidates=f01-d7-public-suite` 的 statement 包装，
由 `candidates/f01-d7-research/public-suite.py` 在独立 checkout 里对 `suite-plan.json` 列出的候选
跑原版 full gate（25 轮、500k pairs、900s 预算），输出 `public-suite/summary.json` 与逐候选 verdict。

## 计划

- 源 commit：派发时的 `huan/dhs-deepseek` HEAD（`suite-plan.json` 已改为本计划）。
- seed：`1425002`（必须与 plan 内 seed 一致，adapter 会断言）。
- 候选（3 个，控制在 45 分钟 job 上限内）：
  1. `f01-d12-scalar-combined`（anchor，df5c）
  2. `f01-deepseek-p2cont8`（p=2 → DirectContinuous；p≤8 → DirectSmall）
  3. `f01-deepseek-directall`（p≤64 全部走 DirectContinuous，量化 Packed10 价值）
- 派发：`candidates=f01-d7-public-suite`、`seed=1425002`。
- 预计：warm cache 下 setup 5—8 min + 包装 statement 2—3 min + 3 个 public-v2 full gate 约 12—16 min。

## 判定

- 以 work-weighted whole/df5c 与 bmm/df5c 为主；同一 run 同参照。
- `directall` 若在 p=18/23/32/50/59 上不劣或更优，说明 Packed10 准备与 lane 填充在当前套件是净开销。
- 失败/超时保留回执；单 seed 只作发现组，确认另起新 seed 与新 runner。
