# R19：peer temporal-b2（c70c）独立复刻第一组

时间：2026-10-26T23:00Z

## 设置

- 复制 peer `f01-r19-dev-temporal-b2-1` 的 Kernel 逐字节（SHA `c70cf947…`，237897 B）到
  `candidates/f01-deepseek-peercheck-temporal-b2-1/`。
- run [40414394748](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/40414394748)，public-v2 seed 1826017，
  B2 anchor + 复制，2 个 full gate PASS，runner **AMD EPYC 9V45**。
- 标签 `PEER_VERIFICATION`，不是采用组。

## 结果（对 B2）

| 项 | 比值 |
|---|---:|
| bmm | **0.9991** |
| add | 1.0469 |
| mul | 1.0624 |
| sum | 1.0658 |
| whole | 0.9876（p05 +0.006734） |

## 判读

- peer 源只改 BMM 调用者/结构，add/mul/sum 代码不变，却出现 +4.7%—+6.6% 漂移 →
  该 run 的标量噪声约 ±5—6%。
- BMM 0.9991 落在噪声内：**没有复现 peer 的 BMM 0.922（−7.8%）**。
- 但噪声大，单组不足以否定；peer 的收益可能是其 seed 1927003 的形状相关。
  正在 seed 1826018 做第二组复刻（run 40416378615）。
- 这不改变 peer 自己的确认流程；仅作为独立对照。

## 第二组（干净对照）

run 40416378615，seed 1826018，runner EPYC 7763，B2 anchor + 复制：

| 项（对 B2） | 比值 |
|---|---:|
| bmm | **0.9671** |
| add / mul / sum | 1.0002 / 1.0005 / 1.0012 |
| whole | 0.9959（p05 −0.026826） |

- 控制项干净（~1.000），BMM −3.3%；peer 原组为 −7.8%（其 seed 1927003）。
- 两组合计：方向为正但幅度随 seed 明显缩小；整包收益 <1%，达不到 0.97 门槛。
- 判断：peer 的 BMM 机制有效但**形状依赖**；其 whole 0.990 单组小收益未在不同 seed 上放大。
  不改变 peer 的流程；仅独立对照。
> 口径说明（2026-10-26T23:32Z 更正）：本文中若标注 raw 的 op 比值仅作诊断；采用口径为归一化 (sub/inc)_cand ÷ (sub/inc)_B2。归一化值见 R19-SUMMARY.md 的更正表与 messages/20261026T233200000Z-r19-normalized-correction.md。

## 第四组：peer 原 seed 1927003（CPU 对照）

run 40420082968，seed 1927003（peer 首组同 seed），runner EPYC 9V74，B2 anchor + 复制（归一化）：

| 项（对 B2） | 值 |
|---|---:|
| bmm | **0.9418** |
| add / mul / sum | 0.9986 / 0.9960 / 0.9981 |
| whole | 0.98790（p05 −0.007416） |

- 同 seed 下 peer 原组 bmm 0.9221（−7.8%），我这里 0.9418（−5.8%）：方向与量级接近，
  差异属 runner/CPU 与测量噪声。
- 四组合计（bmm）：0.9477 / 0.9676 / 0.9732 / 0.9418；对应 seed 形状不同，整包 0.988—0.996。
- 结论：c70c 的 BMM 机制真实有效（−2.7%—−5.8%），但整包收益不足以达到采用门槛；
  其幅度依赖 seed 形状，不能跨 seed 相加。
## 第五组（噪声组）

run 40428246442，seed 1826022，EPYC 9V45：bmm 0.9958、add 1.0345、mul 1.0029、sum 0.9939、whole 1.0118（p05 −0.009913）。
该源只改 BMM，add 却漂 +3.5% → 本组噪声大，bmm 0.996 不能判为“无收益”，也不改变前四组结论。
五组合计（bmm norm）：0.9477 / 0.9676 / 0.9732 / 0.9418 / 0.9958（末组噪声）。