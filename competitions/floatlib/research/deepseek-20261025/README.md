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

形状分析（`analyze-bmm-shapes.py`）：`n>4 且 3≤p≤8` 的 case 占 bmm 计分工作量约 15.9%，
现走 Packed10，每行固定 10 lane，p=3 时约 70% 填充。六条此类 case：
ml:0(1×41×3)、ml:6(8×36×3)、sparse:3(6×181×5)、subnormal:3(2×84×3)、
specials:1(24×6×6)、specials:4(6×225×5)。

## 已排除的重复路线

`f01-d7-low-zero`（e139093a）已在 `ex+ey<128` 分支内加零操作数快路，但整包 1.0243 更慢；
sparse 数据上零检测分支本身不可预测。不重复该路线。

## 本窗候选

| 候选 | 机制 | 证明负担 | 状态 |
|---|---|---|---|
| `f01-deepseek-p8-direct`（d2f97bad） | BMM 分派 `p ≤ 8` 改走既有 DirectSmall | 0 新证明 | 本地静态 diff；待 CI |

## 边界

类级耗时来自单次 public-v2 drawn 样本，不是官方计分份额；机制判断不等于收益。
所有性能结论必须由临时 runner 上同 run 的候选／df5c 配对测量给出。
