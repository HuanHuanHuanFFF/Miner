# DeepSeek 8小时协作窗（2026-10-25）

角色：free agent（探索／研究／开发验证）。窗口：北京时间 2026-10-25 03:03—11:03（UTC 19:03—03:03）。
本地不运行 Lean／大型工具链；Lean 与完整 gate 只在临时 GitHub runner。

## 已做的静态分析

数据源：`candidates/f01-d7-research/public-suite-results.json` 最后一条 df5c 记录（run 40098465163，seed 1324009），
按 `cell_work` 还原每个 op:class 的绝对耗时（复算总和与 `operation_total_ns` 一致，见 `analyze-shares.py`）。

主要观察（INFERRED，单次 drawn 样本）：

| 现象 | 数据 | 说明 |
|---|---|---|
| 乘法 sparse 是 mul 最大且相对最差的桶 | 10.90 ms，12.72 ns/work，ratio 0.7226 | 其他 mul 类 ratio 0.46—0.49 |
| 求和 sparse 每元素成本约为 dense 的 2.8 倍 | 4.27 vs 1.51 ns/work | sparse 占 sum 37.2% |
| BMM sparse 每 MAC 约为 dense 的 1.6 倍 | 14.57 vs 8.97 ns/work | 见形状分析 |
| BMM subnormal 极快 | 1.86 ns/work | 全小值证书命中，直接零填充 |

形状分析（`analyze-bmm-shapes.py`）：按 df5c 实际分派顺序
（underflow-zero → Cross(p=2,batch·m≥4) → DirectContinuous(n≤4,p>2) → DirectSmall(n≤4 或 p≤2) → Packed10）
还原后：

- `n>4 且 3≤p≤8` 的 case 占 bmm 计分工作量约 15.9%，现走 Packed10，每行固定 10 lane；p=3 时约 70% 填充。
  六条此类 case：ml:0(1×41×3)、ml:6(8×36×3)、sparse:3(6×181×5)、subnormal:3(2×84×3)、
  specials:1(24×6×6)、specials:4(6×225×5)。
- p=2 的 case（dense 全部 6 条、sparse 3 条等）走 R11CrossRows（四行×两列 → P12），不是 DirectSmall；
  它们是 dense 组 7.93 ms 的主体。

## 已排除的重复路线

`f01-d7-low-zero`（e139093a）已在 `ex+ey<128` 分支内加零操作数快路，但整包 1.0243 更慢；
sparse 数据上零检测分支不可预测。不重复该路线。

## 本窗候选

| 候选 | 机制 | 证明负担 | 状态 |
|---|---|---|---|
| `f01-deepseek-p8-direct`（d2f97bad） | BMM 分派 `p ≤ 8` 改走既有 DirectSmall | 0 新证明 | 旧十二类：慢 1.19%；public-v2：慢 0.7% |
| `f01-deepseek-p2-direct`（43d15b12） | p=2 Cross 守卫 `4≤batch·m` → `batch·m<4`，p=2 改走 DirectSmall | 0 新证明 | 未进 public-v2 |
| `f01-deepseek-p2p8`（386af2d5） | 上述两条组合 | 0 新证明 | 未进 public-v2 |
| `f01-deepseek-p2cont`（e878b0f2） | p=2 改走 DirectContinuous（全形状定理），并放宽其守卫到 `p≤2` | 0 新证明 | run 3 发现组 |
| `f01-deepseek-p2cont8`（169f8198） | p2cont + p8 组合 | 0 新证明 | public-v2：whole 0.9584，bmm 0.8319 |
| `f01-deepseek-p2contp8`（69901745） | p≤2 与 p≤8 全部 DirectContinuous | 0 新证明 | **终选**；6 run 全正 |
| `f01-deepseek-directall`（ad91388b） | p≤64 全部 DirectContinuous | 0 新证明 | public-v2：whole 0.9585，bmm 0.8346 |
| `f01-deepseek-directallfull`（a84bd96b） | 无界直算探针（p≤1000000） | 0 新证明 | 未测 |
| `f01-deepseek-p2contp16`（a08d4f4a） | p≤16 直算阈值 | 0 新证明 | 比 p≤8 差 1.4% → 锁定 p≤8 |

## 终选汇总（p2contp8，public-v2 原版 full gate，全部 PASS）

| seed | run | whole/df5c | bmm/df5c |
|---|---|---:|---:|
| 1425003 | 40128718577 | 0.9667 | 0.8384 |
| 1525001 | 40130503671 | 0.9914 | 0.9522 |
| 1525002 | 40131881480 | 0.9706 | 0.8188 |
| 1525003 | 40133209118 | 0.8912 | 0.5784 |
| 1525003 复跑（顺序颠倒） | 40134598315 | 0.8911 | 0.5788 |
| 1525004 | 40135988993 | 0.9736 | 0.8641 |

中位数：whole ≈ **0.9689**，bmm ≈ **0.8268**。同 run 的 add/mul/sum 为同源码控制，
前 5 run 噪声 <0.3%；1525004 run 噪声较大（±3.8%），只用于同 run 阈值比较。
采用包：`ADOPTION-p2contp8.md`。

## public-v2 发现组（seed 1425002，run 40126911323，4 个 full gate 全 PASS）

| 候选 | whole/df5c | bmm/df5c | dense | ml | sparse | specials |
|---|---:|---:|---:|---:|---:|---:|
| `p2cont8` | **0.9584** | **0.8319** | 0.707 | 0.838 | 0.888 | 1.268 |
| `directall` | 0.9585 | 0.8346 | — | — | — | — |
| `p8-direct` | 1.0070 | 1.0329 | 0.9625 | 1.066 | 1.063 | 1.222 |

归因：增益来自 p≤2（含 p=1）改走 DirectContinuous；p3–8 改 DirectSmall 单独更差；
p>8 的 direct 与 Packed10 在本 seed 基本等价。specials（NaN-heavy p2）退化 +26.8%。

## public-v2 发现组 2（seed 1425003，run 40128718577）

| 候选 | whole/df5c | bmm/df5c |
|---|---:|---:|
| `p2contp8`（p≤8 全 DirectContinuous） | **0.9667** | **0.8384** |
| `p2cont`（只改 p≤2） | 0.9799 | 0.9062 |
| `directall`（p≤64 全直算） | 0.9881 | 0.9494 |

合并两 seed：p≤2 直算是主收益；p3–8 直算 ≥ DirectSmall；**p>8 保留 Packed10**。
specials 在 seed 1425002 退化、1425003 改善，对 NaN 密度敏感，不单独下结论。

## 口径更正（run 1）

run 1 旧十二类曾按 12 类 `submission_ns` 不加权求和得到 whole 0.9987；官方 headline 应使用裁判比值归一：
`0.1961162362 / 0.1938124588 = 1.01189`，即 p8 候选慢 1.19%。per-class 求和只作方向参考，
不能替代 headline。public-v2 的数字按 `cell_work` 加权，无此问题。

## 边界

类级耗时来自单次 public-v2 drawn 样本，不是官方计分份额；机制判断不等于收益。
所有性能结论必须由临时 runner 上同 run 的候选／df5c 配对测量给出。
单 seed 是发现组；确认需新 seed（DeepSeek 后续用 1525xxx）与新 runner。
