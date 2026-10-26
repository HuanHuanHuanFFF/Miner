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
