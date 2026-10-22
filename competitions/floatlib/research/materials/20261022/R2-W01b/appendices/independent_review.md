# R2-W01b 独立反驳审查

## 结论与证据边界

**没有找到题设准入式及新增 `±0` 乘法路径的语义反例。** 对 `UInt32` 回卷减法而言，下界没有 off-by-one；两个零确实进入同一个转换、查表、乘法分支，而且分别产生 `0x00000000` 与 `0x80000000`。最强的风险不是这个公式本身，而是验证方法会漏掉错误：**把负零错误地变成正零，完整的 `+0` 起始求和仍可能完全一致。** NaN 也能掩盖之后的解码错误。因此“所有完整 sum 一致”不能替代逐项位模式校验。

本评审先只读任务消息、公开固定源码并构造独立例子；后按根代理的明确追加请求，静态审阅本轮新建的 `diagnostics/zero_merge_probe.c`、`ofbits_external.c`，随后只读核验唯一一次 C 实验的已保存结果与反汇编，并审阅 `admission/AdmissionZero.lean`。未读取旧会话、旧附件、`floatlib_r2w01` 目录。没有运行 C benchmark，没有运行 Lean，没有为已经成立的 native finite guard 设计替代算法。曾收到另一代理的准入推导简讯；本评审此前已经完成相同推导，并要求后续只分享公开源码路径。

这里的“通过”分别指下述源码推导、独立整数诊断和已保存 C 结果的内部一致性。它不表示 Lean 文件已编译或定理已被内核验收。唯一 C 实验支持随机零模式下的机制收益；官方形状三类的稳定收益未建立，见第 7 节。

## 1. 准入式：两个区域，边界精确

令 `a = u & 0x7fffffff`，所以 `0 ≤ a ≤ 0x7fffffff`。检查的是：

```text
((a - 1) mod 2^32) >= 0x0bffffff
AND a < 0x7f800000
```

只有两种情况：

1. `a = 0` 时，回卷结果为 `0xffffffff`，下界成立，上界也成立。
2. `a ≥ 1` 时，减法不回卷；下界等价于 `a ≥ 0x0c000000`，再与严格上界相交。

所以准入集合恰为：

```text
a = 0 OR 0x0c000000 <= a < 0x7f800000
```

这是覆盖全部 `UInt32` 的整数推导，不依赖抽样。符号位先被清掉，所以正负两侧具有相同边界。它既排除所有次正规数和指数域 `1..23` 的小 normal，又排除 `±Inf` 和全部 NaN。

| magnitude `a` | 对应边界 | 准入 | 路径 |
|---|---|---:|---|
| `0x00000000` | 两个零 | 是 | 数值转换、查表、乘法 |
| `0x00000001` | 最小次正规数 | 否 | 原 `ofBits` |
| `0x007fffff` | 最大次正规数 | 否 | 原 `ofBits` |
| `0x00800000` | 最小 normal | 否 | 原 `ofBits` |
| `0x0b800000` | 指数域 23 的首项 | 否 | 原 `ofBits` |
| `0x0bffffff` | 乘法域下界的前一项 | 否 | 原 `ofBits` |
| `0x0c000000` | 指数域 24 的首项 | 是 | 乘法 |
| `0x7f7fffff` | 最大有限数 | 是 | 乘法 |
| `0x7f800000` | 无穷 | 否 | 原 `ofBits` |
| `0x7f800001` | 最小非零 NaN fraction | 否 | 原 `ofBits` |
| `0x7fffffff` | 最大 NaN 位字 | 否 | 原 `ofBits` |

表中每行都必须同时检查 `u=a` 与 `u=a|0x80000000`。

**控制流也有独立义务。** 如果把回卷减法误写成饱和的自然数减法，零会退回 `ofBits`；如果把 `>=` 改成 `>`，`0x0c000000` 会退回 `ofBits`。这两种错误可能仍然输出正确位模式，却不满足“恰好接受目标集合、让零共用乘法路径”的要求。单独检查路由真值可以抓住它们。

## 2. 新增 zero 义务必须停在位模式层

两个零的完整轨迹如下；`M` 的数值转换不是 `ofBits M`。

| 输入 `u` | `j=u>>>23` | 整数 `M` | `M.toFloat32.toBits` | `table[j].toBits` | 乘积 `toBits` |
|---|---:|---|---|---|---|
| `0x00000000` | 0 | `0x00800000` | `0x4b000000` | `0x00000000` | `0x00000000` |
| `0x80000000` | 256 | `0x00800000` | `0x4b000000` | `0x80000000` | `0x80000000` |

`M=8388608` 是正的有限 binary32 数。固定 Lean 的逻辑模型对 `finite sign₁ × zero sign₂` 直接返回 `zero (sign₁ * sign₂)`；符号乘法中，`positive * positive = positive`，`positive * negative = negative`。[S2][S3] 因此这里得到两个不同的零位模式，不存在用“实数值都等于 0”替代该结论的空间。

需要落到候选 Lean 交付物里的具体断言是：

```text
(newConvert 0x00000000).toBits = 0x00000000
(newConvert 0x80000000).toBits = 0x80000000
```

还必须确认对应表项实际存的就是这两个零，而不是在生成表时把所有 zero 统一成正零。512 项中有 462 个 normal scale 与 50 个带符号零；新增路径只使用这些零表项中的 `j=0` 和 `j=256`。

本轮不重做已有 normal 域证明。有限诊断仍覆盖 normal 边界，是为了抓代码变体的错误，不应把抽样结果包装成新证明。

## 3. 最强可复现反例，以及它们能否被完整 sum 发现

以下是有意破坏一处条件后立即出现的反例。它们是诊断敏感性的证据，不是声称题设正确公式存在这些错误。

| 被破坏的条件 | 反例输入 | 正确可观测输出 | 错误输出 |
|---|---|---|---|
| 下界常数低 1：`0x0bfffffe` | `0x0bffffff` | `0x0bffffff` | `+0` |
| 删去有限上界 | `0x7f800000` | `+Inf` | `+0` |
| 删去有限上界 | `0xffa12345` | 规范 NaN `0x7fc00000` | `-0` |
| 下界比较忘记去符号 | `0x80000001` | 原负次正规位字 | `-0` |
| `table[256]` 的 sign 被清掉 | `0x80000000` | `-0` | `+0` |

最后一行尤其危险。正确转换和错误转换对向量 `[-0]` 的完整结果都为 `+0`，因为规定初始 accumulator 为 `+0`，而固定 Lean 的加法模型对异号两个零返回正零。[S4] 所以：

```text
correct decode(-0) = -0, but fullSum([-0]) = +0
broken decode(-0)  = +0, and fullSum([-0]) = +0
```

另一种掩盖来自 NaN。对 `[0x7fa12345, 0x0bffffff]`，正确实现和“下界低 1”的错误实现最终都产生 NaN；第二项确实已经解码错，完整 sum 看不出来。固定 Lean `Float32.ofBits` 会规范 NaN，`Float32.toBits` 又明确返回统一的 `0x7fc00000`，不能把原 NaN sign/payload 原样往返当作该转换的契约。[S1]

必须区别三个层次：

- 转换层应该比较与旧 `Float32.ofBits` 一致的可观测位模式。
- 已有整个算法的 finite guard 及软件回退承担的 raw payload 语义，本轮继续沿用。
- 只做 native 转换与有限 full sum 的 C surrogate 没有资格证明第二层。

`sum` 的顺序也能被很短的例子否证：`[2^24, 1, -2^24]` 按序结果为 `+0`，把后两项调换则为 `1`。对应位字为 `0x4b800000, 0x3f800000, 0xcb800000`。固定官方契约是从 `+0` 开始、按索引顺序、每项执行一次 `ExecFloat.add`。[S5] 本轮要求不 skip zero；即使某一具体全有限输入上省略零能得到相同末值，也不能把这种少做运算的程序放进这次公平成本比较。

## 4. 已执行的独立有限诊断

文件：`review/diagnostic.py`、`review/diagnostic.json`。执行命令为 `python3 diagnostic.py`。诊断使用纯 Python 整数实现 binary32 的精确中间值与 round-to-nearest/ties-to-even；不使用主机 float 作为 oracle，也不运行 C。

结果：

| 检查 | 执行证据 |
|---|---:|
| 不同 32 位输入 | 136,705 |
| 覆盖表索引 | 全部 512 个 |
| admitted normal | 123,290 |
| 小 normal | 12,341 |
| 次正规数 | 558 |
| NaN 位字 | 512 |
| 两个零与两个 Inf | 各完整覆盖 |
| 路由、old/merged 与基准位模式不一致 | 0 |
| 自造完整求和向量 | 96 条，每条 1000 项 |
| 每臂实际模型 add 次数 | 96,000 |
| 完整结果不一致 | 0 |
| 不同向量 / 不同最终结果 | 96 / 96 |

完整求和诊断特意选择全有限且不溢出的向量，避免 96 条向量几乎都被 NaN 或 Inf 吞掉而产生虚假的覆盖感。NaN 掩盖、负零掩盖和重排反例另外单列。诊断还确认上述五个输出错误变体、两个只改变路由的错误变体都能被相应检查抓住。

这是有限诊断加简单准入数学推导；不是整个 `2^32` 输入空间的运行穷举，不是 Lean 编译结果，也不是 native 浮点环境验证。

## 5. 唯一 C surrogate 实验的独立静态审阅

本评审按追加请求查看的新实验源码有三个臂：独立 translation unit 的 external `ofBits`、旧 `u==0` 特例、merged guard。三个 sum 都写成从 `0.0f` 开始的相同长度按序循环，且逐项执行加法。使用共享的 `float[512]` 平坦表；运行前检查 IEEE binary32 参数、舍入模式与 FTZ/DAZ；转换和逐向量 sum 都独立校验。8 类数据、每类 96 条不同的 1000 项向量，预定 7 轮、每轮 80 次遍历。**运行前静态审阅没有发现需要取消这次实验的语义阻断。** 根代理随后完成该唯一实验；本评审没有运行或重跑它，只核验保存的证据。

### 必须如实说明的官方分布

官方 LCG 的更新式是 `s := s * 1664525 + 1013904223`；两个常数都为奇数，所以最低位每步翻转。官方 `sumRelu` 正是用这一位决定是否输出 `+0`。[S6][S7] 因此每条长度 1000 的官方 ReLU 向量都有**恰好 500 个正零，零位置严格交替**；长度为偶数，各向量的交替相位相同。这不是随机的 50% zero mask。

官方 dense 的指数域为 `124..130`，wide 为 `102..151`，两者的值都在乘法准入 normal 区间；官方 ReLU 的非零项也在前一个区间。[S6] 所以本轮要区分：

| 维度 | 能回答的问题 |
|---|---|
| 官方 dense / wide | 没有零时，合并 guard 的额外整数工作是否有成本 |
| 官方交替 ReLU | 规律正零模式下，去掉特例是否划算 |
| 随机约 25% / 50% / 75% 正零 | 零比例与不可预测位置怎样改变结果 |
| 相同非零序列、把零聚集 | 零排列怎样改变 branch 行为 |
| 相同零位置、部分改为 `-0` | old 的正零特例与负零回退差异 |

这些维度不能互相替代。尤其 old 对 `+0` 不执行数值转换、查表和乘法；merged 增加这些工作，可能靠控制流改善抵消，也可能更慢。old 对 `-0` 则走 external 回退。因此只用负零较多的 synthetic 类得出“ReLU 已获益”不成立。

### 启动前已向根代理提出的两项小修

1. 审阅快照中的官方三类各自使用任意 LCG 初始状态。若要称为重放固定 `BenchTensor.runSum` 数据，应从单一新 `base_seed` 按 `base_seed XOR (salt * 0x9e3779b9)` 派生，salt 分别为 `0x51/0x52/0x53`；否则准确称为“复用官方生成公式与 LCG”。[S6]
2. 独立 TU 且无 LTO 已阻止通常的跨文件内联，但给 external 函数显式写上 `noinline,noclone`，会让所声称的 external noinline 条件更容易审计。

最终处理：实验保留三个自造 seed，根代理明确只称“官方形状/复用生成公式”，没有声称重放 `runSum` 的 seed/salt 数据。external 未额外加属性，但编译明确关闭 LTO，反汇编确认每项 external 调用存在，因而本项证据已经足够；不要求为添加属性重跑实验。

### 必须排除的不公平解释

- **新贡献的对照是 merged/old。** 两个 table 臂对 external 基准的共同提升，不能全归因于本轮 zero 合并。
- **路由计数须有方法名。** 当前分布表的 `accepted/fallback` 是 merged 的计数。old 的 table 次数是 normal 数量，正零特例次数是 `plus_zero`，external 次数为 `elements - normal - plus_zero`；这些不能共用一列而不说明。
- **三个臂对同一原始向量、同一顺序、同一长度求和。** 校验每个向量并保留每轮 checksum，不能只比较类别总 hash；不得把输入转换预先缓存给某一臂。
- **保留严格浮点编译条件。** 保存无 fast-math、无 LTO、禁止 contraction/reassociation 的实际命令；反汇编确认 external 调用仍在，old 的零路径仍有 add，merged 的正常路径没有被变成少算元素的特殊算法。
- **初始化与稳态分列。** old 与 merged 共用同样的表，二者的表初始化成本本来就相同；不能只向一臂收费。若与 external 比较一次性 break-even，只能用 C 的实际 setup 时间和 C 的逐项节省推导，且节省必须为正。
- **平坦表是有意缩小的 C 模型。** 它不包括 Lean Array、Float32 装箱、引用计数、bounds check 或真实生成码。凭一个未经核对的 16B box stub 猜测 Lean 布局，只会加入额外假设。不能把平坦表 C 的时间换算成 Lean 提速。
- **报告所有 7 轮的配对数据。** 审阅的轮次顺序先覆盖 6 种方法排列，第 7 轮重复其中一种，应如实说明。不要择最小值、删除慢轮、混入后续重跑后再报告一个好看的数。
- **Synthetic 与官方结果分开。** 不能通过增加某种有利 synthetic 类的数量改变整体平均，掩盖官方类的退化。实际 CPU affinity、CPU/编译器/flags、数据 seed、长度、重复次数、缓存预热方式都应留档。

## 6. 建议预先固定的停止门槛

### 语义或实验有效性的硬停止

任意一个逐项位模式不一致、准入真值不一致、表负零符号错误、逐向量完整 sum 不一致，都应立即停止声称该变体有效。若实际生成码 skip zero、重排加法、内联掉预定 external 基准、三个臂使用不同输入，所得 timing 也不得作为该问题的证据。只有先修正明确缺陷才有继续资格，不能用“绝大多数样本通过”抵消这些问题。

“完整 sum 通过但 zero 的单项 `toBits` 未验证”本身就是未关闭的证据缺口。

### 是否值得继续投入 Lean 实现的工程筛选

如果没有更早约定的量化门槛，可在看到结果前采用保守筛选：以每轮官方 dense、ReLU、wide 的总时间比较 merged 与 old；**中位改善至少 3%，且 7 轮中至少 6 轮同向**，才把这次 C 实验视为值得投入下一步的证据。任何官方单类中位退化达到 5% 应单列解释，不能藏进 synthetic 平均。若未满足，结论停在“语义上可行，唯一 C 实验不足以支持继续投入”，不再通过改分布、调重复次数和追加实验寻找胜利。

这些百分比是建议的本轮工程停止线，不是官方 admission 规则，不是统计显著性的保证，更不是 Lean 性能验收；若已有用户门槛，以已有约定为准。即使通过，下一步真正需要补的是固定 Lean 工具链上的编译、bitwise zero 定理和真实生成码/性能证据，不能直接宣称方案已获验收。

## 7. 对唯一实验结果的独立复算

`review/audit_results.py` 只读取已保存文件，不调用编译器或实验二进制。它核对源文件 SHA256 与构建记录一致，重算了 168 行 timing、56 组每轮三臂 checksum、768 条逐向量结果以及 36 条单列边界记录；全部通过，所有配对比值与 `probe_summary.json` 一致。产物是 `review/experiment_audit.json`。

C 的 `871620` 是**转换检查次数，包含重复输入**：36 个边界检查、512×7 个字段组合、100000 个 raw 样本、768000 个数据集元素；不得写成 871620 个不同输入。完整 sum 检查为 8×96=768 个向量，未发现 mismatch。

| 数据类 | merged/old 配对比值的中位数 | merged 更快的轮数 |
|---|---:|---:|
| 官方形状 dense | 0.994875 | 4 / 7 |
| 官方形状交替 ReLU | 0.997870 | 4 / 7 |
| 官方形状 wide | 0.960255 | 7 / 7 |
| 随机约 25% 正零 | 0.367272 | 7 / 7 |
| 随机约 50% 正零 | 0.228435 | 7 / 7 |
| 随机约 75% 正零 | 0.447385 | 7 / 7 |
| 与随机 50% 类相同非零序列、零聚集 | 0.983026 | 6 / 7 |
| 相同 50% 零位置、部分负零 | 0.185943 | 7 / 7 |
| 官方形状三类等元素数合计 | 0.983720 | 4 / 7 |

比值小于 1 表示 merged 更快。官方形状三类合计约 1.63% 的中位改善且仅 4/7 轮同向，未通过第 6 节在查看结果前提出的 3%/6-of-7 工程筛选。交替 ReLU 的最后两轮比值分别为 `1.105115`、`1.107867`，不能据其中位配对比值略低于 1 宣称稳定收益。

要特别标明统计口径：交替 ReLU 的**配对比值中位数**是 `0.997870`，而**两个独立时间中位数之比**是 `1.016185`。两者不是同一个统计量，数值方向不同不构成计算错误；表头如果不写清楚，会给读者制造矛盾。

分布计数也与生成方式相符：交替 ReLU 为 48000 个 `+0`；随机 50% 类为 47686 个 `+0`；其聚集变体保留相同非零顺序；混合符号变体为 23719 个 `+0` 与 23967 个 `-0`。交替类的 zero transitions 恰为 `96×999=95904`，随机 50% 类为 48359。**相邻状态切换更多并不意味着更难预测**：严格交替可形成规律，随机 mask 才缺少这种规则。

### 反汇编核验

- `sum_external` 在 `0x2606` 每项仍调用 `external_of_bits`，随后 `0x260b` 执行 `addss`；外部函数在 `0x293d` 使用 `ucomiss`，后接条件选择规范 NaN，canonicalization 未被优化掉。
- `sum_old` 在 `0x2785/0x2787` 检查并分流 `u==0`。零分支跳到 `0x2772`，随后仍执行 `0x2776` 的 `addss`，没有 skip zero。
- `sum_merged` 保留 `0x26a4/0x26ac` 的两次整数比较及两个条件跳转；通过后是 `0x26ca` 的数值转换、`0x26ce` 的 `mulss`、`0x26d4` 的 `addss`。它**不是 branchless**，只是本次所有 timed 输入都让准入分支走同一条路径。
- 两个 table 臂都保持独立的标量乘法与按序标量加法；没有看到 FMA 或横向重排。

构建记录为 GCC 13.3.0，包含 `-O3 -std=c11 -fno-fast-math -ffp-contract=off -fno-lto`。CPU affinity 固定为 CPU 0，frequency locking 为 false。评审只读 `/proc/cpuinfo` 得到 CPU 型号 `AMD EPYC 9V74 80-Core Processor`。表 setup 单次记录为 1142 ns，数据生成单次为 3165492 ns，均未混入逐项 steady-state timing。

**接受的解释：** 随机零模式与聚集/交替零模式之间的强烈差异，与移除难预测的 `u==0` 分支这一机制一致；未采集硬件 branch-miss 计数，因此不能把具体微架构因果当作已经直接测量。wide 的 7/7 同向信号可以保留，但不改变“官方形状整体与 ReLU 的稳定收益未建立”的判断。这些 C 结果不推出 Lean 提速。

## 8. Lean 增量候选的静态审阅

`admission/AdmissionZero.lean` 的接口覆盖准入、表索引界、零字段、表的实际零位模式、两个零的乘积、`toBits` 往返、零进入乘法路径以及逐项转换替换的 `foldl` 同态。其 `tableProduct_zero_bits` 的结论确实是 `(tableProduct u).toBits = u`，不是实数投影相等。已再审阅最终补充的 bits→value 桥、normal 位接口适配与 `replace_decoder`；它们没有改变运行时定义。`float32_ofBits_toBits` 使用的 FloatLib native 往返定理及 `toBits32_ofFloat32` 可在固定公开源码中找到。[S10][S11]

所用 `decide` 是命题等号的决定过程，Float32 的结构模型保留两个零的位模式；这里没有误用会把两个零判成相等的浮点 `BEq`。固定源码中的 `UInt32.toNat_sub` 是 `(2^32 - b.toNat + a.toNat) % 2^32`，与候选 gate 证明中的 `change` 目标一致；没有发现已证实的语义反例。

仍有明确的验收边界：`convert_eq`、`convert_bits_eq`、`foldl_convert_eq` 都显式接收 `hNormal`，本文件未把已有 normal 定理实例化进去；它也不是完整 `SumObligation` 的证明或整个 native-guard sum kernel。参数化复用已有 normal 结论符合“不重复 normal 证明”的范围，但不能把参数化定理说成已经无条件关闭全部义务。**该文件没有编译运行，状态仍为 NOT_RUN。** 没有 Lean elaboration、kernel audit 或真实生成码证据，本评审不把其静态合理性升级为已验收证明。

## 固定公开来源

Lean `v4.34.0` 在本轮源码清单中解析为 `293d5d0c0c3f3dded4688b3ccd6a33939ac5102b`；FloatLib 固定为 `0d91825727839f597fd06b22fdd038ea21480f0c`；official 固定为 `978cc5b445edb9943fd9953b0a9037d97a9f33a8`。下载内容及 blob/SHA256 记录由本轮 `sources/source_manifest.json` 给出。

- [S1 — Lean runtime `Float32.ofBits` / `toBits`，`object.cpp`](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/runtime/object.cpp#L1987-L2003)
- [S2 — Lean unpacked multiplication 的 finite × zero 分支](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Float/Model/Unpacked/Operations/Mul.lean)
- [S3 — Lean `Sign` 的乘法与 sign bit](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Float/Model/Unpacked/Sign.lean)
- [S4 — Lean unpacked addition 的 zero 规则](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Float/Model/Unpacked/Operations/Add.lean)
- [S5 — official `ContractTensor.sumSpec` 与 `SumObligation`](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/contract/ContractTensor.lean)
- [S6 — official `BenchTensor` 生成器、长度、salt、checksum](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/bench/BenchTensor.lean)
- [S7 — official `Bench.lcg`](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/bench/Bench.lean)
- [S8 — Lean C header：Float32 add/mul 与 UInt32 数值转换](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/include/lean/lean.h#L3253-L3265)
- [S9 — 固定 FloatLib 的 `Configured.NativeFPU.Runtime`](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Configured/NativeFPU/Runtime.lean)
- [S10 — 固定 FloatLib native `toFloat32_ofFloat32`](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Representation.lean)
- [S11 — 固定 FloatLib native bits/value 定义与位往返](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native.lean)
