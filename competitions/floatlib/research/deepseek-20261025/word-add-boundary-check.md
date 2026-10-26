# 独立证伪：pure-word add 域边界（DeepSeek，2026-10-25T00:45Z）

对象：开发侧 230553 / 235825 提出的整数加法快域（normal、gap≤7、sameSign 或 opposite gap≥2）。
方法：纯整数精确 RNE 参照，与提议公式逐位比较；本机轻量 Python、20 秒墙钟上限、不跑 Lean、不派 CI。

## 结论

- **9,223,371 个域内用例 0 处不一致**（边界 mantissa 组合 + 随机；接受域内逐位等于精确 binary32 RNE）。
- `h == log2(N)` 在全部用例成立；`t = h−23 ∈ 1..8`；opposite d≥2 时 `L>R` 恒成立。
- `N_max` 观测 2,163,839,253 ≤ 2,164,260,735，UInt32 对齐加减不回卷；`h ≤ 30`。
- `E` 观测范围 **[2,255]**（elo≥1、h≥24 ⇒ E≥2）；E=255 出现在 exp=254 且进位，必须由 guard 拒绝。
  随机样本里 255 约占 0.07%；E=256 未出现（carry 最多使 h+1）。
- d=0 同号（N≥2^24，h=24）、d=2 异号最小 N=2^24+1、d=7 上界、ties（2^24−1 / 2^23+2^22）、
  输入顺序交换（同指数同号）均覆盖，无差异。

## 必须保留的 guard

- 结果 E 不在 1..254（本域只会出现 255）→ 回退原 add；不能把 E=255 打包成 normal。
- 输入必须 normal 1..254；零/NaN/Inf/subnormal、opposite d≤1、结果 subnormal 都不在域内。
- 本检查只验证算术模型，不验证运行时代码的 guard/打包/调用成本，也不构成性能结论。

## 复现

```
python competitions/floatlib/research/deepseek-20261025/check-word-add.py    # 20s, 9.2M cases
python competitions/floatlib/research/deepseek-20261025/word-add-stats.py   # E/N 分布
```
