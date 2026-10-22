# R4-W01 地址证明片段审阅记录

`RowPairBounds.lean` 为独立的纯 Nat 辅助文件，仅 `import ContractTensor`，命名空间为 `Submission.RowPairBounds`。20 个定理、124 行、4,693 字节。没有内层循环、数值转换、机器字调度、诊断命令或证明占位。

**Lean elaboration、内核检查、公理输出均为 NOT_RUN。** 本轮环境没有 Lean/lake，没有安装工具链。以下记录是实际源码接口核对与静态数学审阅，不是编译成功记录。

## 主要接口

| 定理 | 用途 |
| --- | --- |
| `pair_index_lt` | i<m 推出 i/2<(m+1)/2 |
| `row_decomposition` | 2*(i/2)+i%2=i |
| `selected_base` | 行对起点加所选行偏移，恢复原行地址 |
| `second_base` | base0+n 等于扁平行号 2*h+1 的起点 |
| `row_lt` / `row_end_le` | 先建立扁平行号和整行排他上界 |
| `point_bound` / `row_span` | 任意有效 k 与非空行末元素的界 |
| `row0_point` / `row0_span` | 前提 2*h<m 的第一条流 |
| `row1_point` / `row1_span` | 前提 2*h+1<m 的第二条有效流 |
| `selected_point` / `selected_span` | 直接以合法输出行 i 证明所选流地址 |
| `pair_first_valid` / `pair_second_cases` | 合法 h 必有第一行；第二行有效或恰为 m |
| `tail_second_base` | 2*h+1=m 时，base1=(b+1)*m*n |
| `tail_next_span` | 非最后 batch 的未观察尾流属于下一 batch 第一行 |
| `tail_last_point_outside` / `tail_last_span_fails` | 最后 batch 的尾流全部越界，严格完整 span 准入必失败 |

## 正确的界区分

不能仅从 `h < (m+1)/2` 就给第二条流套用“当前 batch 的有效行”证明。它只推出 `2*h+1<m` 或 `2*h+1=m`。

在等号尾行情况下，`tail_second_base` 精确定位到下一 batch 边界。如果 `b+1<batch` 且 n>0，`tail_next_span` 说明读取下一 batch 首行仍在整个 A 数组内；它不把该行说成全零。如果 `b+1=batch`，所有 `base1+k` 都至少为数组总长；`tail_last_span_fails` 证明第二流不能满足严格完整 span 检查。因此按用户给定“两流都满足才走机器字快路”的策略，最后 batch 的奇数尾行对必走 Nat 路径。

这些地址事实本身不证明浮点 lane 独立性；是否可以忽略第二流，需要实现保持两组累加器互不影响、有效输出独立选择和原始输入回退。地址片段没有用未观察等价于零的假设。

## 零维与巨大 Nat

`row_end_le` 允许 n=0。`row_span` 必须使用 0<n，因为 n=0 时目标会成为 0<0。`point_bound` 在 n=0 时没有可满足的 k<n 前提。

m=0 时不存在 i<m 或 h<(m+1)/2；batch=0 时不存在 b<batch。定理保持对任意 Nat 维度的蕴含形式，不把这些条件添加到最终 bmm 规格。所有乘法在 Nat 中完成，没有机器字截断。

## 实际 API 核对

已实际读取本轮下载的 Lean v4.34.0 `src/Init/Data/Nat/Basic.lean`：

- 第 166 行 `Nat.add_assoc`；
- 第 223 行 `Nat.one_mul`；
- 第 240 行 `Nat.add_mul (n m k)`；
- 第 496 行 `Nat.add_lt_add_left (h : n<m) (k : Nat)`；
- 第 757 行 `Nat.mul_le_mul_right (k : Nat) (h : n≤m)`。

变量乘法的上界由 `Nat.mul_le_mul_right` 建立；`omega` 仅处理常数除法/余数、线性比较及 n−1 的界。

源码：

https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Nat/Basic.lean

https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/contract/ContractTensor.lean

已从本轮固定官方 `gate.py` 的 AST 提取原始 BANNED 正则，扫描整个片段（含注释），零命中。

源码 SHA256：

```text
71c868bb29f5cadad49046c9f84178d299b82264e3e7e774671c61cc0a8c500b
```
