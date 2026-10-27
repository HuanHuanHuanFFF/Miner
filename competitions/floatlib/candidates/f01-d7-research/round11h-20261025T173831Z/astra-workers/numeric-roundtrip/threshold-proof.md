# 从原输入域推出 R 阈值与 shift

状态：完整纸面推导与 Lean 证明尝试；**NOT_COMPILED**。没有改动冻结的 `01cff` 探针或 `e085` 运行片段，没有新增运行变体／Kernel。本文件针对先前 `numeric_shift_toNat` 的 `hs` 缺口；新最终声明不再把归一化 shift 等式作为假设。

## 对象与原域

令 `2^23 <= a,b < 2^24`、`0<=d<=7`。同号 `N=a*2^d+b`；异号要求 `d>=1`，且保留 `N=a*2^d-b>=2^23`。已有无回绕对齐引理负责将实际 UInt32 的 N 接到这些 Nat 表达式，输入域未变化。

沿用冻结探针的定义：

```text
h = floor(log2 N)
q = roundShiftRightEven N (h-23)
c = [q=2^24]
m = if c=1 then 2^23 else q
H = h+c
S = H-23
R = m*2^S = roundedInteger N
```

R 是已定义的 RNE 整数，不是 N。原探针中的 `roundedInteger_eq_RNE` 对 c=0/1 给出 `R=q*2^(h-23)`；待验证的 `high_roundtrip` 将实际数值 cast 接到 R。这里的 Nat 证明先独立推出 H、R 区间和 S，随后 UInt32 lift 调用该 cast 桥。

## 一般归一化事实

原域导出 `2^23<=N<=2164260735`。冻结探针已有完整证明尝试给出 `23<=H<=31`、`2^23<=m<2^24`。由于 `23+S=H`，直接乘 `2^S` 得

```text
2^H <= R < 2^(H+1),     log2 R = H.
```

新 `rounded_binade` 与 `rounded_log2` 只使用这些定义／界，不假设 N 精确可表示，也不用新的浮点舍入单调性定理。

## 同号：最高一档不再进位

输入范围给 `2^(23+d)<=N<2^(25+d)`，所以 `23+d<=h<=24+d`。若 `h<24+d`，由 c<=1 立即有 `H<=24+d`。只需排除 `h=24+d` 时 c=1，此时舍入移位为 `d+1`。

当 d>=1，取最大 `Nmax=(2^24-1)*(2^d+1)`。固定库定理给

```text
q <= floor(N / 2^(d+1)) + 1
  <= 2^23 + 2^(23-d) < 2^24.
```

最后一式对 d=1..7 成立，因此 c=0。Lean 草稿仅对这个已固定的有限指数差做 `interval_cases d`，每支的 a、b 仍是满足原界的任意 Nat，使用线性整数算术；这不是枚举 mantissa 样本。

**d=0 单独用精确公式。** 此时 N=a+b<=2^25-2。固定 FloatLib `roundShiftRightEven_one` 给出

```text
q = if N % 4 = 3 then N/2+1 else N/2.
```

非加一支 q<=2^24-1。加一支还知道 N%4=3；在 N<=2^25-2 下，最大此类 N 为 2^25-5，所以 q<=2^24-2。故两支都严格低于 2^24。该证明保留任意 N 的奇偶情况，没有把 Nmax 为偶数误当成所有 N 都是偶数。

因此全域 `23+d<=H<=24+d`，结合一般归一化事实，得到

```text
2^(23+d) <= R < 2^(25+d).
```

## 异号高 N：同样排除最高一档进位

当 d=1，原 high-N 条件给 `N>=2^23=2^(22+d)`；当 d>=2，输入下界直接给

```text
N >= 2^(23+d) - (2^24-1) > 2^(22+d).
```

上界 `N<2^(24+d)`，故 `22+d<=h<=23+d`。若 h 低于最高一档，c<=1 已足够；若 `h=23+d`，舍入移位为 d，且

```text
N <= (2^24-1)*2^d - 2^23
q <= floor(N/2^d)+1 <= 2^24 - 2^(23-d) < 2^24.
```

所以 c=0，全域 `22+d<=H<=23+d`，并得到

```text
2^(22+d) <= R < 2^(24+d).
```

## 阈值选择与实际 UInt32 表达式

若某 K 满足 `K<=H<=K+1` 且 `2^H<=R<2^(H+1)`，则 `R>=2^(K+1)` 当且仅当 H=K+1。于是

| 原输入域 | R 的 leading exponent | 实际归一化 shift |
| --- | --- | --- |
| 同号 | `23+d+[R>=2^(24+d)]` | `d+[R>=2^(24+d)]` |
| 异号、d>=1、高 N | `22+d+[R>=2^(23+d)]` | `d-1+[R>=2^(23+d)]` |

`same_threshold_from_inputs` 和 `opposite_threshold_from_inputs` 的最终声明同时给出 `log2 R` 和 `roundedShift N`，前提只有 mantissa 范围、指数差范围及异号 high-N 条件；没有 R 阈值形状或 shift 等式假设。

`Threshold-word-lift-v1.lean.inc` 进一步证明尝试：若 `base.toNat<=7`，则 `(base+24).toNat<=31`，阈值 `1 <<< (base+24)` 的 Nat 值精确为 `2^(base.toNat+24)`，不会发生 shift-count 模32或字长截断；bump 为0/1，`base+bump<=8` 也不回绕。调用待验证 `high_roundtrip` 后，UInt32 比较与上述 R 的 Nat 比较一致。

最终 `same_word_shift_from_inputs` / `opposite_word_shift_from_inputs` 直接覆盖冻结运行片段两条符号分支的实际 UInt32 shift 表达式，前提保留实际 N 等于对齐幅度的等式及原域；**不再需要 `hs : shift.toNat=roundedShift N`**。它们可用于解除先前 `numeric_shift_toNat` / `numeric_fraction_toNat` 的 hs。

## 范围、依赖与停止点

- 固定库源码：FloatLib `0d918257…/Numerics/Quantization/Deterministic/ShiftRight.lean`，真实公开定理 `roundShiftRightEven_le_shiftRight_add1`（173行）、`roundShiftRightEven_one`（180行）。源码和既有获取索引绑定于新 manifest。
- Nat 草稿依赖冻结探针的 `carry_le`、`rounded_leading`、`high_mantissa` 及定义；UInt32 lift 另依赖 pending `high_roundtrip`。没有新增未证明声明、占位证明或公理入口。
- 完整域的纸面推导已给出；Lean 的 elaboration、定理实际依赖、公理审计和内核重放仍全部未运行，不能写成形式化已闭合。
- 尚需 D 的真实编译目标反馈；最终公开 ADD 还要接旧排序／幅度语义、E 字段等式、模型包装及全部原 gate。没有验证资源时到此保留可检查的小证明链，停止扩展证明族，不追加运行版本。
