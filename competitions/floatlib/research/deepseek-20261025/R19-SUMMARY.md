# R19 DeepSeek 六小时总结（2026-10-26T19:47Z—2026-10-27T01:47Z）

分支 `huan/dhs-deepseek`；保留候选 B2 `622d8394`（未改动）。无新采用、无正式提交、无组合。

## 口径

- **归一化**（采用口径）：`(Σ work×sub_ns / Σ work×inc_ns)_cand ÷ (同式)_B2`，即扣除同 run 参照漂移。
- **raw**：`Σ work×sub_ns_cand ÷ Σ work×sub_ns_B2`，仅诊断；本轮多次出现参照漂移 5—6%，
  raw 与归一化可差 5pp 以上（peer 第一组 bmm raw 0.999 vs norm 0.948）。
- p05：本地独立 bootstrap（2000、Random(90423)、25 抽中位数、linear p05，对归一化 whole）。
- 每候选独立 full gate；A/B 同 run 对 B2 anchor。

## 一、实验总表（归一化）

| # | 机制 | 回执 | whole | 关键项 | p05 | 结论 |
|---|---|---|---:|---|---:|---|
| 1 | B2 放宽 m≥2 | 40390827505 | 1.0213 | bmm 1.149 | −0.0268 | 负 |
| 1b | B2 放宽 m≥1 | 同上 | 1.0187 | bmm 1.197 | −0.0435 | 负 |
| 1c | B2 放宽 m≥1∧n≥1 | 同上 | 1.0217 | bmm 1.195 | −0.0380 | 负 |
| 2 | 一阶循环 pair 行 | 40395050251 | 0.9979 | bmm 0.980 | −0.0162 | 小幅正、不显著 |
| 2b | 一阶循环 DirectContinuous | 同上 | 0.9878 | bmm 0.970 | −0.0071 | 小幅正、不显著 |
| 2c | 两者组合 | 同上 | 0.9875 | bmm 0.975 | −0.0120 | 小幅正、不显著 |
| 3 | mul th0（EPYC 7763, seed 1826011） | 40397668271 | **0.9691** | mul 0.9219 | **+0.0212** | 单组过线，确认失败 |
| 3b | th0（Xeon 8573C, seed 1826012） | 40400995011 | 0.9940 | mul 0.9863 | −0.0204 | 确认失败 |
| 3c | th0（EPYC 9V74, seed 1826011） | 40410071271 | 0.9544 | mul 0.8837 | +0.0450 | 同 seed 复核 |
| 3d | th0（EPYC 9V74, seed 1826012） | 40412279339 | 0.9784 | mul 0.9402 | −0.0301 | 同 seed 对照 |
| 4 | convert→ofBits（add+mul） | 40405652739 | 1.1215 | add 1.1558 / mul 1.1375 | −0.1295 | 强负 |
| 5 | dot 内联 | 40403277972 | 1.0409 | bmm 0.9949 | −0.0323 | 负 |
| 6 | finish 内联 | 40408096257 | 0.9977 | bmm 1.0018 | −0.0387 | 无变化 |
| 7 | peer temporal-b2 复刻（5 组） | 见下 | 0.988—1.012 | bmm 0.942—0.996（末组噪声） | 1 正 3 负 1 无效 | 方向复现、整包不达标 |
| 8 | B2 按 p 带收窄 p≥3/4/6 | 40422242456 | 1.007/1.007/1.009 | bmm 1.042/1.041/1.056 | 负 | 保持 p≥2 |

## 二、mul th0：最接近的发现，CPU 相关

- 机制：`if ex+ey<128 then LowScale.mul else nativeMul` 常数改 0（恒 native）；0 新证明；
  优化器 DCE 掉 `expField` 与整条软件路径。
- EPYC 上 mul −6%—−12%，whole −2.2%—−4.6%；Xeon 上 mul −1.4%，whole −0.6%。
- 同 seed 1826012：Intel whole 0.9940 vs EPYC 0.9784，mul 0.9863 vs 0.9402（seed 对照支持 CPU 关联）。
- 即使 EPYC，seed 1826012 的 whole 0.9784 > 0.97、p05 为负 → 不满足采用；**REJECTED**。
- 若将来确认官方硬件为 EPYC，可重新评估；Intel 的 `mul:subnormal` 慢 23%。

## 三、peer temporal-b2（c70c）独立复刻

复制字节 `c70cf947…` 未改，B2 anchor + 复制，三 seed：

| 组 | run | seed | CPU | bmm norm | whole norm | p05 |
|---|---|---|---|---:|---:|---:|
| 1 | 40414394748 | 1826017 | EPYC 9V45 | **0.9477** | 0.98762 | +0.0067 |
| 2 | 40416378615 | 1826018 | EPYC 7763 | 0.9676 | 0.99586 | −0.0268 |
| 3 | 40418221837 | 1826019 | EPYC 9V74 | 0.9732 | 0.99461 | −0.0078 |
| 4 | 40420082968 | 1927003（peer 原 seed） | EPYC 9V74 | **0.9418** | 0.98790 | −0.0074 |
| 5 | 40428246442 | 1826022 | EPYC 9V45 | 0.9958（add 漂 +3.5%，噪声） | 1.01179 | −0.0099 |

- BMM 方向在 DeepSeek seed 上复现 −2.7%—−5.8%；在 peer 自己的 seed 1927003 上为 −5.8%（peer 原组 −7.8%）。
  整包 0.988—0.996 不达标；幅度随 seed 变化，不能把不同 seed 的 bmm 收益相加。
- peer 自己的旧失败/不采用不变。

## 四、可迁移教训

1. **raw 与 normalized 必须分开标**：参照漂移 5—6% 时，raw 0.999 与 norm 0.948 可以同源；
   我此前用 raw 判读 peer/循环组，已更正。
2. **C 证据须确认 selected body**：旧 `RowOutput_row` 的闭包不在 B2 实际调用链；生成 C 无 closure
   但计时仅 −1—2.5% 且不显著 → 闭包不是瓶颈。
3. **Xeon 单 run 未改动标量可漂 ±10%**；小效应必须多组/同 run 对照。
4. **表解码已优于 `Float32.ofBits`**（add +15.6%、mul +13.7%）；bitcast 不是免费替代。
5. **CPU 影响 denormal 路径**：去软件 denormal 分支的候选必须记录 runner CPU 并做同 seed 对照。
6. BMM 小 n（≤4）形状占 bmm 时间 11%—37%，但 d70 类展开历史为负；下一步应走 USize writer/结构。

## 五、回执与文件

- 原始 CI：`ci-runs/40390827505`、`40394386767`、`40395050251`、`40397668271`、`40400995011`、
  `40410071271`、`40412279339`、`40405652739`、`40403277972`、`40408096257`、`40414394748`、
  `40416378615`、`40418221837`、`40420082968`（peer 原 seed 复跑）。
- 逐题：`R19-b2-relax-negative.md`、`R19-loop-negative.md`、`R19-mul-native.md`、
  `R19-conversion-inline-negatives.md`、`R19-peer-replication.md`、`R19-small-n-share.md`。
- 脚本：`norm-metrics.py`、`compute-p05.py`、`show-public-classes.py`、`build-*.py`、`make-*.py`、
  `small-shape-share.py`。

## 六、保留状态

- B2 `622d8394`（226829 B，三组采用证据）不变。
- 本轮所有候选源码保留在分支，作负结果/机制证据，不进入采用。

## 七、额外独立验证：peer jam 数学探针（编译失败）

- 复制 `astra-grs-jam-proof-probe.lean`（`5d0f2e8b…`，230284 B）到
  `candidates/f01-deepseek-peercheck-jam-probe/`，statement-only。
- run **40429425157** 失败：`Submission.lean:6618` whnf 心跳超时（200000）；
  随后 `R19JamVariableProbe.low_states` unknown constant。
- 结论：该探针原样在官方 statement 预算下不可编译；`low_states` 需拆分或减少展开。
  未改动探针字节、未放宽 gate 参数。已回执 R。