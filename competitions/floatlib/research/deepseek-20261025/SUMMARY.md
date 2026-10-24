# DeepSeek R14 总结：BMM p≤8 直算路由

时间：2026-10-24T23:05Z。窗口 UTC 19:03—03:03。本文件是研究线的收尾索引；细节在
`ADOPTION-p2contp8.md`、`README.md`、`ci-runs/`。

## 结论

- 终选 `f01-deepseek-p2contp8`（SHA `699017452ec031efd8f0f161c944c4f45aab4c4eed8fff88f30faac533354049`，
  248158 B）：只改两个 BMM 分派谓词，0 新证明。
- 9 次 public-v2 原版 full gate 测量（7 个 seed）方向全为正：whole 中位 ≈0.945，bmm 中位 ≈0.771。
- 预注册三 seed（1525006/7/8）whole 0.9450 / 0.9063 / 0.9570。
- **统计范围**：首次 D（1425003）p05 −0.009302 未过，按开发侧裁定，预注册批次只作附加输入泛化诊断，
  不构成既有三组 guard 的完整采用。
- 阈值：p≤16 同 run 更差 1.4% → p≤8 锁定；p>8 保留 Packed10。
- specials 对 NaN 密度双向波动；extremes 平均 +2.8%（单 seed 最高 +33%，绝对量小）。

## 机制

1. p=2 且 batch·m≥4 不再走 R11CrossRows（守卫改为 `batch*m < 4`）；
2. `bmmBeforeR11Cross` 的 DirectContinuous 守卫从 `n ≤ 4 ∧ 2 < p` 放宽到
   `(n ≤ 4 ∧ 2 < p) ∨ p ≤ 8`，p≤8 全部走直接行写出；p>8 仍为 Packed10。

主收益来自 p≤2（尤其 p=1 与 p=2 的大 batch 形状）从 Cross/DirectSmall 切到 DirectContinuous。

## 证据

- run 汇总：`confirmation-batch-runs.json`、`ci-runs/<run>/deepseek-public-v2-ab.json`
- 采用包：`ADOPTION-p2contp8.md`
- gate 阶段性证据（axioms 仅允许三项、25 轮、suite hash）：`ADOPTION` 内引用 run 40134598315 log
- 原始 artifact 与逐文件 SHA：`ci-runs/<run>/original-artifact-hashes.json`
- 方法脚本：`dispatch-ci.py`、`collect-run.py`、`analyze-shares.py`、`analyze-bmm-shapes.py`、
  `summarize-runs.py`、`confirm-batch.py`
- 静态审阅开发侧新候选：`review-deepseek-static-20261025.md`

## 未闭合

- 官方私有套件与冠军 #309 的同套件比较：UNKNOWN（本窗口只跑公开 public-v2）。
- 与开发侧 83a9 / combined-slim1 的组合效果：NOT_RUN（其源码未编译、未授权公开推送）。
- specials/extremes 的 seed 相关退化未做机制级修复。
- p>8 packed 路径未优化。

## 复现

```powershell
# 派发（需本分支已推送、工作区干净、无在途 run）
python competitions/floatlib/research/deepseek-20261025/dispatch-ci.py `
  --candidates f01-d7-public-suite --seed 1525008
# 收齐与 A/B
python competitions/floatlib/research/deepseek-20261025/collect-run.py --run <run_id>
```
