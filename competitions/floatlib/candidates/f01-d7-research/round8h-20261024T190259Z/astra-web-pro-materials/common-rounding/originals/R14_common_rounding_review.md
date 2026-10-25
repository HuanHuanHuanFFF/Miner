# R14 共享舍入模块：严格 Lean / 数学证明审阅

**状态：NOT_RUN / 未验证。没有执行 Lean elaboration、kernel 检查或传递公理审计。**

日期：2026-10-25（Asia/Shanghai）。交付对象为附加证明模块；没有运行浮点候选、性能测试或 CI，没有安装工具链、推送 Git，未改原 contracts、gate、bench 或编译参数。

## 1. 审阅结论与修订性质

在原稿完整前提下，未发现能推翻这 13 个公开定理的数学反例，也未发现已被证实的 Lean API 错名或必然编译错误。`shifted_signed_word_general` 原稿确实证明了**已经带符号的原始 UInt32 字**加上指数 delta 的等式，不能把它误判为只证明正数中间量再 OR 符号。

这次修订解决的是可独立交付片段的依赖闭合、证明展开的显式化，以及调用方条件的完整表达：

- 原 packing / word algebra 四个证明原样保留。
- 原 `roundedMantissa`、`carry`、`normalized` 三个定义逐字节保留；原 13 个公开 theorem statement 全部保留，没有删减前提。
- 两个小 h 左移证明显式加入 `Nat.shiftLeft_eq'`，再使用 `Nat.shiftLeft_eq`，减少直接函数写法与 notation 之间的匹配依赖。
- `native_round_normal` 显式展开固定 `NativeBinary32.roundDyadic`，先消除零值和原 subnormal 分支，再对应 carry / overflow / packing。原始 normal 下界与含 carry 的上界均保留。
- 把旧父本中已经提供完整证明的 `FastMul.log2_shift` 复制为新命名空间内的私有辅助定理，移除片段对旧父本名称的依赖。
- 增加 proof-only 桥：postguard 上下界、编码指数、真实 rounder 的 aligned normal 结果、零值 +0、精确 Int 的带符号平移，以及 normal 乘积的直接 normal 下界。

**“未验证”不可省略。** 原 proof 的 `simp/rw` 是否已经能成功，本次没有运行证据；显式化修订不构成“原稿已复现编译失败”的证据。

## 2. 输入、版本和字节证据

| 对象 | UTF-8 字节 | SHA256 |
|---|---:|---|
| `astra-web-pro-common-rounding-input.txt` | 242452 | `9de663c43f518aa0dbd09b5336f28d46a68e943138d739223a2cbd0f163f2a4e` |
| `astra-web-pro-native32-source.txt` | 6683 | `1a00aeab50520759e90e3af0cbcea0e61a03ec1b2648907409f4da9d6c73ef67` |
| 原父本第 1–6648 行的完整前缀 | 227657 | `3c6af73f9d679e9831ac8c4abb9f0e6d41b61718301dd045bedd2402e980632a` |
| `R14_common_rounding_repaired.lean` | 20004 | `9d841b404f705d60c51c4242a43c86972d5be6654e3292d90e4ac16f061a7429` |
| 内部用于字节核对的拼接文件 | 247641 | `b1f2962958b10898d8a7d43316eb3912eba80256e4f0c3b4ae40d4686993b9ca` |

固定版本：

- Lean **4.34.0**，commit `293d5d0c0c3f3dded4688b3ccd6a33939ac5102b`。
- FloatLib commit `0d91825727839f597fd06b22fdd038ea21480f0c`。
- 正式单文件仅 `import ContractTensor`。
- 仅允许 `propext`、`Classical.choice`、`Quot.sound`；是否满足实际传递公理集合仍须 runner 审计。

本次使用指定 commit 的公开 GitHub 文件读取核对 API。附带 native32 原文对应固定 FloatLib 的 `FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Base/Runtime.lean`，其 Git blob 为 `dc080c68fa47df803354e28654c3973c6d2b48a2`；对附件实际字节计算 Git blob，结果一致。[F1]

`command -v lean lake elan` 均无结果；现成执行路径和缓存盘点没有找到可直接使用的固定编译器。缓存的版本声明、公开源码或 headers 不能视为编译器或通过记录。因此全部 Lean 验证状态为 **NOT_RUN**。

## 3. 精确修订位置

下表“原行号”属于完整输入；“交付行号”属于 460 行的修订片段。

| 原行号 | 交付行号 | 精确处理 | 分类 |
|---|---|---|---|
| 6658–6793 | 28–163 | 四个 packing / word 定理与证明保留 | 无已证缺陷，不做无依据重写 |
| 2093–2106 的完整辅助证明；6865 的调用 | 173–186；242 | 在新命名空间内提供 `private theorem log2_shift`；调用改为 `log2_shift n k hq` | 独立片段依赖闭合 |
| 6839 | 216 | `simp only` 加 `Nat.shiftLeft_eq'` | notation 规范化；不是已复现报错 |
| 6886 | 263 | 同上 | notation 规范化 |
| 6908–6933 | 285–322 | statement 不变；proof 显式展开真实 rounder、保留原 normal 和含 carry 的 overflow 判断 | 证明展开显式化 |
| 6935–6946 | 324–335 | 模型桥保留 | API 方向已核对 |
| 6950–6977 | 339–366 | 全部前提、位型结论和 signed-word 调用保留 | 不能改成正数 mid 的 OR 结论 |
| 原稿没有这些 caller wrapper | 375–456 | 补完整 postguard、+0、精确 Int 与乘法下界桥 | 仅增加证明定理 |

两个最小改行如下：

```lean
simpa only [roundedMantissa, h23, ↓reduceIte,
  Nat.shiftLeft_eq', Nat.shiftLeft_eq] using hu

have hr : roundedMantissa n = n * 2 ^ (23 - n.log2) := by
  simp only [roundedMantissa, h23, ↓reduceIte,
    Nat.shiftLeft_eq', Nat.shiftLeft_eq]
```

固定 Lean API 明确区分：

```lean
Nat.shiftLeft_eq' : m.shiftLeft n = m <<< n
Nat.shiftLeft_eq (a b : Nat) : a <<< b = a * 2 ^ b
```

这也符合固定 FloatLib 自身在 `Quantization/Deterministic/ShiftRight.lean` 中的显式规范化写法。[L3][F3]

原 `rw [hr] at hu ⊢` 所在小 h 分支的目标确实包含 `roundedMantissa n`；它不能被列为已证错误。`Nat.mul_le_mul_right`、`Nat.mul_lt_mul_of_pos_right`、`Nat.pow_le_pow_right` 的原参数顺序也正确。[L1]

## 4. IntegerShape 的完整数学核对

记 `h = n.log2`、`R = roundedMantissa n`、`c = carry n`、`P = 2^23`。`c` 始终是对同一个 `n` 定义的真实 carry，不是独立任取的 0/1 变量。

### 4.1 h < 23：左移精确归一化

对 `n ≠ 0`，固定 Nat 对数引理给：

```text
2^h ≤ n < 2^(h+1).
```

左乘正数 `2^(23-h)`，由 `h+(23-h)=23` 与 `(h+1)+(23-h)=24` 得：

```text
2^23 ≤ n * 2^(23-h) < 2^24.
```

这里使用真实 Nat 左移乘幂恒等式，未引入实数表示或转换假设。原 `rounded_small` 只需严格上界，因此允许 `n=0`；`normalized_bounds` 的下界必须保留 `n≠0`。[L1][L2][L3]

### 4.2 h = 23：右移 0 位

`roundShiftRightEven n 0 = n`，又有 `n < 2^24`，所以不发生 carry。把 `h=23` 错放成“可能因 RNE 进位”的分支是不必要且错误的扩大。

### 4.3 h ≥ 23：真实右移商和 RNE

令 `k=h-23`、`q=n>>>k`。先证明 `2^k≤n`，再通过

```lean
Nat.div_eq_zero_iff : n / 2^k = 0 ↔ 2^k = 0 ∨ n < 2^k
```

排除 `q=0`。完整 `log2_shift` 证明给 `h=k+q.log2`，于是 `q.log2=23`，即：

```text
2^23 ≤ q < 2^24.
```

固定 FloatLib 的两个无条件定理给：

```text
q ≤ roundShiftRightEven n k ≤ q+1.
```

所以 `2^23≤R≤2^24`。若 `R=2^24`，归一化结果为 `2^23`；否则 `R<2^24`。最终：

```text
2^23 ≤ normalized n < 2^24,
0 ≤ normalized n - 2^23 < 2^23.
```

这一步确实覆盖 RNE 右移，包括 halfway-to-even；它没有把 RNE 当成截断。[F3]

### 4.4 carry = 1 ⇒ h ≥ 24

`h≤23` 已给 `R<2^24`，因而 `c=0`。反证立即得到 `c=1 ⇒ h≥24`。边界见证 `n=2^25−1=33554431`：`h=24`、`k=1`、商为奇数 `2^24−1`，余数正好一半，RNE 进到 `2^24`，所以 `c=1`。这里的下界 24 是紧的。

### 4.5 native_round_normal 对应真实源码

固定实际 rounder 的顺序为：非零判断 → 原 `h+e<-126` 判断 → 计算 `R` → 判断 carry → 计算 `h+e+c` → 判断 `>127` → 打包。[F1]

修订 proof 保持此顺序：

```lean
have hnormal : ¬ (n.log2 : Int) + e < -126 := by omega
unfold Model.NativeBinary32.roundDyadic
simp only [beq_iff_eq, hn, ↓reduceIte, hnormal, Model.pow2_eq_two_pow]
```

随后 `change` 把实际分支折回共享 `roundedMantissa`、`normalized`，分别在 `R=2^24` 与 `R≠2^24` 下由 **`h+e+c≤127`** 排除真实 overflow 分支。结果是实际 UInt32 字：

```text
mkBits sign ((h+e+c+127).toNat) (normalized n - 2^23).
```

三个前提全部保留：`n≠0`、**舍入前** `h+e≥−126`、**含 carry** 的 `h+e+c≤127`。这不是实数值相等的替代证明。

`model_round_normal` 再通过固定 `ofUInt32_roundDyadic` 与 `ofUInt32_mkBits` 回到 Model；原反向重写方向正确，后者没有额外字段范围前提。[F2]

## 5. UInt32 模运算与两个符号

令 `M=2^32`、`P=2^23`、`B=2^31`、`E=em+s−k`。这里 `s,k` 在数学式中表示 UInt32 的 `toNat`，而代码 `s-k` 仍为 UInt32 模减。

固定 Lean 的真实减法投影是：

```text
(s-k).toNat = (M-k.toNat+s.toNat) % M.
```

不能直接换成自然数截断减法 `s.toNat-k.toNat`。[L4]

`s≥k` 时，delta 是普通非负差乘 `P` 后模 `M`。`s<k` 时，原证明利用 `s<512`、`k≤512` 得：

```text
((M-k+s)*P) % M = (s+512-k)*P.
em*P+f+(s+512-k)*P = M+E*P+f.
```

其中 `E>0` 保证 `k<em+s`，避免把错误的 Nat 截断当成整数减法。`E<255`、`f<P` 给输出的字段和数值界。

对负号，实际输入字已经是 `B+em*P+f`；原 `shifted_signed_word_general` 使用 `Nat.add_mod` 继续证明：

```text
(B+em*P+f+delta) % M = B+E*P+f.
```

这才连接 signed64 结果已经带符号时的实际加法。`shifted_word_general` 的“正数 mid 后 OR 符号”身份不能自行代替这一步。原稿已经提供正确的 signed 版本，修订保留它。

具体有效回卷例：

```text
sign=true, em=127, f=0, s=0, k=1
0xbf800000 + 0xff800000 mod 2^32 = 0xbf000000.
```

边界 `k=512` 也被原前提覆盖：`sign=true, em=255, f=8388607, s=511, k=512` 给 `0xff7fffff`。word-only 引理允许初始 `em=0` 或 `255`，这不代表浮点调用路径允许特殊输入；上层 rounder 定理另行建立 normal / finite 条件。

关于前提必要性要精确：`E<255` 保证有限输出；纯 packing 恒等式可在某些 `E=255` 情形继续成立。`hs/hk` 是当前证明的充分范围条件；不能声称分别删掉它们就一定有反例。对于抽象 Nat 版，同时去掉范围限制可取 `s=k=M+1`，使书写的 `M-k` 先发生截断而破坏等式。交付仍完整保留所有原前提，没有扩展接口。

## 6. 加法 postguard：量词、零值与 Int/Nat 桥

对两个实际 normal raw exponent `ex,ey∈[1,254]`，设：

```text
a = min(ex,ey) ≥ 1
mx = 2^23 + fx,  my = 2^23 + fy
z = σx * mx * 2^(ex-a) + σy * my * 2^(ey-a)   （精确 Int）
N = z.natAbs,  sign = decide (z<0)
精确 dyadic 指数 = a−150
h = N.log2, c = carry N
E = h+c+a−23.
```

`z` 必须是精确整数和。机器移位或 signed64 累加无回卷不能由这些数学定义自动得到。

### 6.1 完整下界推导

原 `postguard_pre_normal` 对所有 `n a : Nat`、`ha:1≤a` 和真实 `carry n` 成立。若 `E≥1`：

- `c=0`：自然数截断减法的正结果推出 `h+a≥24`，故 `h+a−150≥−126`。
- `c=1`：整数形状给 `h≥24`；由 `a≥1` 得 `h+a≥25`，原 normal 下界成立。

它不要求 `n≠0`，因为它只证明一个指数不等式。这与真正舍入定理需要非零前提没有矛盾。

量词不能把 `c` 放松成任意 0/1：取 `N=2^23−1`，`h=22,a=1`，若伪造 `c=1`，则 `E=1`，但原指数为 `−127`。真实 `carry N=0`，所以此输入原本不会被 postguard 接受。

### 6.2 完整上界与编码等式

`E≤254` 给：

```text
h+(a−150)+c ≤ 127.
```

又由 `E≥1` 得正确的 `Int.toNat` 桥：

```text
Int.toNat (h+(a−150)+c+127) = h+c+a−23.
```

新增 `postguard_normal_bounds` 同时返回真实 rounder 所需的下界和含 carry 上界；`postguard_encodedExponent` 单独连接编码指数。没有拿任意 Int 的截断恒等式替代有前提的转换。

### 6.3 零值独立走 +0

`N=0` 时，postguard 仍可能通过，因此必须先分流。交付的 `native_round_aligned_int_zero` 从 `z=0` 直接连接真实 rounder：`decide(z<0)=false`、`natAbs z=0`，得到字 `0x00000000`。

对 admitted normal 输入的精确抵消，这就是所需 +0。它没有把一般负零输入一并改成正零；新模块没有改运行定义。

### 6.4 native_round_shifted 的实际位型连接

先令 `em=h+c+127`。完整 `hfirst` 给第一次整数舍入的有限编码界；原 `hmin` 与含 carry 的 `hmax` 给目标 `1≤em+s−k≤254`。证明分别调用：

```lean
native_round_normal sign n ((s.toNat : Int) - (k.toNat : Int)) ...
native_round_normal sign n 0 ...
```

然后通过 `heFirst`、`heTarget` 连接 Int 编码与 Nat 目标，最后调用 **`shifted_signed_word_general`**。所以等式直接涉及固定实际 `NativeBinary32.roundDyadic` 的 UInt32 输出，没有抽象 rounder 假设。

新增 `native_round_aligned_int_shifted` 用 `s=a,k=150`，符号实际为 `decide(z<0)`。其中 `N<2^64` 仅用于推出 `h<64`、`h+c≤64≤127`；**它不是 signed64 可表示性证明**。实际 signed64 范围应由调用方证明 `−2^63≤z≤2^63−1`，进而得 `N≤2^63<2^64`。

本片段不声称已经证明具体 signed64 转 Float32 primitive 等于 `roundDyadic ⟨sign,N,0⟩`。真实机器对齐和、无回卷、转换接口依然属于开发侧 caller 的接线义务；本次没有虚构接口或用假设替代它们。

## 7. 乘法的独立 normal 下界

normal 输入的 significand 满足 `2^23≤mx,my<2^24`。设 `N=mx*my`，则 `2^46≤N<2^48`，通过真实 `Nat.le_log2` 得 `h≥46`。若 raw exponent sum `S≥128`：

```text
h+S−300 ≥ 46+128−300 = −126.
```

这是独立的直接 normal 下界，不需要借用加法 postguard 的低 h 不进位推理。交付中的 `product_leading_lower` 以 `Nat.mul_le_mul` 实际证明乘积下界，`normal_product_pre_normal` 再连接 `S≥128`。

`S≥128` 单独对任意 `N` 不够，例如 `N=1,S=128` 给 `−172`。乘法调用方仍需 normal mantissa 下界，并且最终上界必须包含 carry。

两个调用路径的参数对应为：

| 路径 | `s` | `k` | 原 normal 下界来源 | 额外必需义务 |
|---|---:|---:|---|---|
| 精确对齐加法 | `a=min(ex,ey)` | `150` | `a≥1`、真实 carry 和 `E≥1` | `N=0` 分流；非零分支；精确 signed 和与转换；`E≤254` |
| normal 乘法 | `S=ex+ey≤508` | `300` | `h≥46`、`S≥128` | `N<2^48`；乘积精确性；含 carry 的最终上界 |

加法的 `a<150` 和乘法的 `128≤S<300` 都会实际使用 `k>s` 的 UInt32 回卷分支。

## 8. 精确边界反例

这些例子反驳的是删减前提或错误接线后的版本，**不反驳原完整定理**。位型用 Python 任意精度整数、显式模数和参考源码的 RNE 分支独立核算；不是 Lean 证明，也不是运行候选结果。

| 被错误删减/替代的条件 | 输入 | 精确后果 |
|---|---|---|
| 以 postguard 代替 `N≠0` | `N=0,a=24,E=1` | 实际 +0 为 `0x00000000`；误套 normal packing 为 `0x00800000` |
| 删去 `native_round_shifted.hfirst` | `N=2^129,sign=false,s=0,k=129` | 目标 round 是 `1.0=0x3f800000`；首次 round 为 +Inf，再加 delta 得 `0.5=0x3f000000` |
| finite 上界漏 carry | `N=2^25−1,e=103,h=24,c=1` | 舍入前指数 127，舍入后 128，实际 +Inf `0x7f800000` |
| 删去原 normal 下界 | `N=1,e=−127` | 实际 subnormal `0x00400000`；误用 normal 公式得到 `0x00000000` |
| 用“舍入后 normal”证明原分支 normal | `N=2^25−1,e=−151,h=24,c=1` | 最终是 minNormal `0x00800000`，但原总指数 −127，实际执行 subnormal 分支 |
| 删去 word 目标正指数前提 | `em=127,f=0,s=0,k=128,sign=false` | 实际 LHS `0xff800000`；Nat 截断目标为 0，RHS `0x00000000` |
| 允许 word 目标指数越过 sign 位 | `em=255,f=0,s=1,k=0,E=256` | 正号 LHS `0x80000000` / RHS `0x00000000`；负号结果反过来 |
| packing 丢 fraction 界 | `f=2^23` | `mkBits` 掩码后 fraction 为 0，未掩码 Nat 等式增加了 `2^23` |

第五行只是原分支推理的反例：该例中的 normal 公式碰巧也给 minNormal，**不能声称它同时反驳位型恒等式**。

`hfirst` 反例的完整字运算为：

```text
roundDyadic(false, 2^129, −129) = 0x3f800000
roundDyadic(false, 2^129, 0)    = 0x7f800000
((0−129) mod 2^32) << 23 mod 2^32 = 0xbf800000
0x7f800000 + 0xbf800000 mod 2^32  = 0x3f000000.
```

辅助 word 枚举覆盖 166,785,798 个实例：全部 `em∈[0,255]`、`s∈[0,511]`、所有满足 `1≤em+s−k≤254` 的 `k∈[0,512]`、两种符号，以及 `f∈{0,1,2^23−1}`，均通过。它没有穷举全部 fraction，也没有任何 Lean 接受效力。

## 9. 固定 API 签名核对表

以下省略部分自动隐式变量，只展示影响调用方向和参数顺序的真实部分。

| API | 固定签名/结果要点 | 审阅结论 |
|---|---|---|
| `Nat.mul_le_mul_right` | `(k : Nat) → n≤m → n*k≤m*k` | 原6880正确 |
| `Nat.mul_lt_mul_of_pos_right` | `n<m → 0<k → n*k<m*k` | 原6833正确 |
| `Nat.pow_le_pow_right` | `0<n → i≤j → n^i≤n^j` | 原6857 base=2 正确 |
| `Nat.pow_add` | `(a m n : Nat) : a^(m+n)=a^m*a^n` | 合并幂的方向正确 |
| `Nat.log2_self_le` | `n≠0 → 2^n.log2≤n` | 保留非零前提 |
| `Nat.lt_log2_self` | `n<2^(n.log2+1)` | 对零也成立 |
| `Nat.div_eq_zero_iff` | `a/b=0 ↔ b=0 ∨ a<b` | 原分支次序正确 |
| `Nat.shiftLeft_eq'` / `Nat.shiftLeft_eq` | raw shiftLeft → notation → 乘幂 | 本次显式补两处 |
| `Nat.two_pow_add_eq_or_of_lt` | `(b<2^i) → (a:Nat) → 2^i*a+b=2^i*a ||| b` | 原参数次序、`.symm` 正确 |
| `UInt32.toNat_inj` | `a.toNat=b.toNat ↔ a=b` | `.mp` 正确 |
| `UInt32.toNat_add` | `(a+b).toNat=(a.toNat+b.toNat)%2^32` | 正确 |
| `UInt32.toNat_sub` | `(a-b).toNat=(2^32-b.toNat+a.toNat)%2^32` | 覆盖回卷 |
| `UInt32.toNat_shiftLeft` | `(a<<<b).toNat=(a.toNat<<<(b.toNat%32))%2^32` | 常量23规范化合法 |
| `Int.toNat_of_nonneg` | `0≤a → (a.toNat : Int)=a` | 结果仍是 Int 等式 |
| `Int.toNat_sub` | `(m n:Nat) : toNat((m:Int)-(n:Int))=m-n` | 不是任意 Int 减法的一般裸等式 |
| `Int.natAbs_ne_zero` | `z.natAbs≠0 ↔ z≠0` | wrapper 中方向正确 |
| `FloatLib.Numerics.roundShiftRightEven_zero` | `(value:Nat) : RNE value 0=value` | 原使用正确 |
| `shiftRight_le_roundShiftRightEven` | `(value shift:Nat) : Nat.shiftRight value shift≤RNE value shift` | namespace `FloatLib.Numerics` |
| `roundShiftRightEven_le_shiftRight_add1` | `(value shift:Nat) : RNE value shift≤Nat.shiftRight value shift+1` | 无额外前提 |
| `Model.NativeBinary32.ofUInt32_roundDyadic` | `ofUInt32(roundDyadic d)=Model.roundDyadic binary32 d` | 原反向 rw 正确 |
| `Model.NativeBinary32.ofUInt32_mkBits` | `ofUInt32(mkBits s e f)=Model.ofFields binary32 s e f` | 无字段范围参数 |

所有 Dyadic 构造均显式标注 **`FloatLib.Numerics.Dyadic`**。它不是 `_root_.Dyadic`；namespace 同名不能代替类型等价。

### 9.1 单一 import 的可达性

现成公开官方 contract 缓存给出 `ContractTensor → Contract → FloatLib`；两份 contract 都是没有 `module` header 的旧式文件。其后固定 FloatLib 源码逐边为 `public import`：`FloatLib → FloatLib.Floats → FloatLib.Numerics → Quantization → Deterministic → ShiftRight`。`ShiftRight.lean` 第22行打开 `@[expose] public section`，所用 RNE 引理在其中。因此不是仅在仓库中找到同名声明，而是有实际公开导入链支持。

`Int.natAbs_ne_zero` 则由固定 Lean 的隐式 `Init → Init.Data → Init.Data.Int → Init.Data.Int.Order` 公开导入链提供。最终 runner 仍须核对它实际加载的 contract 文件与依赖；本次没有将缓存导入声明冒充正式环境的执行记录。[F3][L8]

## 10. 集成方式、静态核验和 runner 接手

### 10.1 只替换附加模块

交付 `.lean` 是独立的新模块片段，第一行只有 `import ContractTensor`。不包含整个旧父本。

拼接到完整正式单文件时：保留原输入第 **1–6648 行**，移除原第6650行起的附加模块；取交付片段时去掉它的第一行 import，然后拼接。不能保留旧 R14 定义再重复追加新副本。

本次内部核对使用精确规则：`旧前缀 + 两个LF + 修订文件去掉第一行后的内容`。所得 **247641 字节**，距离 256000 上限还剩 **8359 字节**。内部拼接文件只用于静态核对，没有运行或宣称为性能候选。

### 10.2 已执行的静态核验

- 原父本前缀与原附件字节一致；四个公开函数及其既有 proof 位于该前缀，未编辑。
- 13 个原公开 theorem statement 逐一比较，全部相同。
- 三个 shape 定义逐字节相同。
- packing / word 全段与原稿相同。
- 片段和拼接文件均只有 `import ContractTensor`。
- 新片段只有原有的三个 `def`，其余增加项为 theorem。
- 新片段沿用已有 `set_option maxRecDepth 8192`；没有加入新的编译参数或其他 option。
- 对注释/字符串剥离后的新片段扫描，没有 `sorry`、`admit`、新 `axiom`、`unsafe`、`extern`、`implemented_by` 或 `native_decide`。

静态禁用词扫描不能代替传递公理审计。上述“相同/无禁用词/字节数”属于实际文件检查；Lean 是否接受属于 **NOT_RUN**。

### 10.3 固定 runner 的必要核验

1. 核对真实可执行 Lean 的版本和 commit，以及加载的 FloatLib revision。不要仅凭目录名或 `lean-toolchain` 声明认定。
2. 按现有正式 runner 的完整原 argv 编译拼接后的单文件；保持原 contracts、gate、bench 和编译参数。这里不猜测或新增 argv，也不要求 CI 或性能测试。
3. 保存 exact source SHA、UTF-8 bytes、真实命令、exit code、完整诊断。优先检查 `native_round_normal` 的 `simp only` 后 `change`、两个 shiftLeft 规范化点、private `log2_shift` 与 `omega` 的 Int/Nat 归约。
4. 使用现有公理审计入口核对新模块所有公开定理和最终四个公开 contracts 的传递公理，只允许三项白名单。可在独立审计输入中列出 `#print axioms`，不能把文本无禁用词当作通过。
5. 接 caller 时逐项建立真实输入的 normal 分类、`a=min(raw ex)`、精确对齐和与机器运算无回卷、`N=0` 的 +0 分流、signed64 转换接口、完整 postguard。若调用方不在本次附件中，不得把该义务标为已闭合。

优先审计对象：`mkBits_nat`、`translated_nat_general`、两个 word 平移定理、`normalized_bounds`、`carry_one_leading`、`postguard_pre_normal`、`native_round_normal`、`model_round_normal`、`native_round_shifted`，以及新加的 postguard / aligned / multiplication 桥。

本交付是可交给固定 runner 的完整新增证明片段和源码审阅结论；最终接受状态须由开发 agent 的实际编译与公理记录更新。

## 11. 固定一手来源

所有链接均固定到本任务指定 commit；没有以 default branch 的声明替代版本证据。

- [F1 — FloatLib Native binary32 Base/Runtime](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Base/Runtime.lean)，Git blob `dc080c68fa47df803354e28654c3973c6d2b48a2`；与附带 native32 文本字节一致。
- [F2 — FloatLib Narrow/Agreement](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Agreement.lean)，Git blob `f319e0d19a7aa8f421a169c0c4f8bf6d2497722a`；packing 与 roundDyadic 的模型桥。
- [F3 — FloatLib Deterministic/ShiftRight](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Numerics/Quantization/Deterministic/ShiftRight.lean)，Git blob `d53bd9ec15f51006a945e3c49d7c3e1d3185af19`；RNE 定义和边界引理。
- [F4 — FloatLib Exact/Dyadic/Basic](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Numerics/Exact/Dyadic/Basic.lean)；`FloatLib.Numerics.Dyadic` 的真实结构。
- [L1 — Lean Nat/Basic](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Nat/Basic.lean)，Git blob `88cfc9ace257e1d79efaf89815fd7df94f63e03b`；Nat 乘法与幂。
- [L2 — Lean Nat/Lemmas](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Nat/Lemmas.lean)，Git blob `64350aa666a6f9ac4c7a05fcb571671dbf75a0e3`；log2、div 与幂。
- [L3 — Lean Nat/Bitwise/Basic](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Nat/Bitwise/Basic.lean)，Git blob `1e2adf9e812a8aa3e890ae9f7ee08de0388e9f1b`；两种 shiftLeft 写法。
- [L4 — Lean UInt/Lemmas](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/UInt/Lemmas.lean)，Git blob `02b968ed5eb711b01772298133624b23326b821b`；实际 UInt32 模加减与注入。
- [L5 — Lean UInt/Bitwise](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/UInt/Bitwise.lean)，Git blob `28cff6606b591e9dcc1d1207c4b4d451d3378e45`；移位量取模与 word 位操作。
- [L6 — Lean Nat/Bitwise/Lemmas](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Nat/Bitwise/Lemmas.lean)，Git blob `79793dc8141a2a957cf8021da3141b7063f68501`；无重叠字段 OR 与加法桥。
- [L7 — Lean Int/Lemmas](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Int/Lemmas.lean)，Git blob `be4123f91d766b8563c965e72e9f96010dfbee61`；`Int.toNat_sub`。
- [L8 — Lean Int/Order](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Int/Order.lean)，Git blob `0141f8ed145cc8a4502f7fba762a5f20b074335e`；`Int.toNat_of_nonneg`、`Int.natAbs_ne_zero`。
