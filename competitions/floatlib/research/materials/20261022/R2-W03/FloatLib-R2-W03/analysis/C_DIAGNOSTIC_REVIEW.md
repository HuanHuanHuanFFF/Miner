# 本轮 C surrogate 的独立窄审查

审查对象：本轮新建 `codegen/diagnostic.c`、`variants.c`、`runtime_stub.c`、保存的 `diagnostic.log`、`surrogate_assembly.txt` 与 `diagnostic.o` 的反汇编。没有重新运行大测试。

最终状态更新：已读取补充后的源码与日志。初审指出的宿主 binary32/FTZ/DAZ 未核查、仅一条1000项数组计时两项局限已得到定向补充；下文保留发现来源并更新为当前状态。此次更新没有新执行测试。

## 审查结论

**当前证据足以支持“外部转换调用的移除可能有实际价值，值得进入一次固定 Lean 版本的编译与整调用验证”。当前证据不能支持“Lean 已加速”“原 FloatLib 全输入逐位验收已完成”或“表方案完整成本一定获胜”。**

没有发现本次性能差异由死代码删除或把整个 sum 循环移出计时循环造成的迹象。最实在的积极证据是：已有汇编同时保留了基线的逐元素外部调用、候选的整数转换/乘法，以及原序 add；C surrogate 能在这个严格执行图下显示差异。

补充的64向量 pool 给出了重要反证：`wide64` 在 wide 域的 median 为7.2452 ns/item，慢于基线3.6984；`boxed` 为1.0031，仍保留优势。因此应优先验证表重构，并把双组 UInt64 无表版本视为已出现分布敏感退化的备选，不能根据单数组结果宣称它更优。

## 1. DCE、顺序与实际执行

`diagnostic.c` 每次将 sum 的 bit pattern 写入 volatile sink，sum 来自独立翻译单元并通过函数指针调用。进一步检查 `diagnostic.o`，`main` 中确实有 4000 次循环，每次都执行间接 sum call，然后把返回值存入 sink；计数器减1后回到 call，没有把只算一次的结果重复写入。

`surrogate_assembly.txt` 显示：

- 基线 sum 内仍有 `runtime_of_bits` 的逐元素调用及顺序 `addss`。
- 重构热路有 `cvtsi2ss`、`mulss`、随后 `addss`；不是 FMA，也不是树归约。
- 重构慢路仍有外部调用。
- 所查 normal 热循环没有以多个局部 sum 重结合的证据。

因此本轮“C 调用屏障差异”有执行证据。它仍只是 GCC13.3/x86-64 的 C surrogate；Lean 的 Nat/Array、对象传递、引用计数、闭合常量表示、实际 C 参数与优化结果未由此覆盖。

## 2. 比较数量与覆盖范围必须准确表述

日志的 `4,194,448` 是**位比较次数**，不是这么多个互异随机输入。

- 指数256种，每指数2048个随机符号/fraction：524,288个生成输入。
- 另有18个显式特殊输入，总计524,306个输入位置。
- 对8个入口各比较一次，得到4,194,448次；其中一个入口就是基线对自身。
- 随机输入可能重复，不能把524,306称为严格互异数量。
- 这是有限样本，数学上全fraction的正确性仍来自独立证明，不来自该计数。

特殊数组包含 ±0、最小/最大subnormal、最小normal、最大有限、±Inf、带payload qNaN/sNaN。随机循环按每个指数取样使极小指数和 E255 获得覆盖，但 E0 的随机 fraction 几乎不可能恰好为0，±0主要靠显式样例。

relu 生成器使用 r 的最低位选择归零，未归零时又保留同一个 r 的 fraction。因此非零 relu fraction 的最低位固定为0。它仍是一种合法合成输入，却不覆盖任意 fraction 的完整分布；不得把它当题目 relu 域的穷尽代表。此相关性不推翻重构数学证明，也无需因此重做大规模性能测试。

## 3. NaN 的证据边界

`runtime_stub.c` 用 bit-copy 加 `isnan`/`NAN` 模拟 native `ofBits` 规范化；`bits` 又直接 bit-copy，而非调用 Lean 的 `Float32.toBits`。在所测 GCC/x86-64 主机上能作为 native finite 转换的对照，也确实检查了回退入口的所测位型。

但是所有 NaN 输入都可能在基线转换时先变成同一个 canonical NaN。这个比较不检查原 raw FloatLib 的 NaN payload 传播，也不证明 sNaN、sign、payload 应怎样穿过完整 sum。

raw 样本的最终 sum 为 `7fc00000`。一旦前缀产生 canonical NaN，最终相同的 NaN 可以掩盖后续转换或加法的某些错误。因而 raw sum 的最终值相同不能充当逐步 trace、全输入等价或异常类传播的验收。它最多说明该样本在此 native surrogate 下的最终返回位相同。

还应区分：Lean 源码 `ofBits` 使用 C++ `quiet_NaN()`，其具体 native pattern 是实现相关的；`toBits` 明确将 NaN 规范化为 `0x7fc00000`。C stub 的 `NAN` 不是实际链接 Lean runtime 的证据。

## 4. FTZ/DAZ 与浮点宿主前提：本机缺口已补查

初审版本启动只检查 `sizeof(float)==4` 与 `fegetround()==FE_TONEAREST`，未完整核查 binary32 与 FTZ/DAZ。最终版本已增加并实际记录：`FLT_RADIX=2`、`FLT_MANT_DIG=24`、`FLT_MIN_EXP=-125`、`FLT_MAX_EXP=128`、`FLT_EVAL_METHOD=0`、RN模式，以及 x86 `MXCSR=0x00001f80`、`FTZ=0`、`DAZ=0`。源码对不符条件主动拒绝比较，没有修改宿主浮点环境。

因此，“本机实验没有检查FTZ/DAZ”已不再是当前事实。对该次 x86 SSE 实验，所需环境证据已补齐。dense/wide 热路的因子和结果本身也是 normal。

这些记录仍不能代替未来实际 Lean 目标进程的同类证据，也不把 native NaN 比较提升为 raw FloatLib 验收；非x86分支明确拒绝认证，未声称可跨平台推广。

## 5. 初始化账与计时不能混同

首组 warm timing 在 `init_tables()` 完成以后开始，每域重复同一个1000项数组，11轮、每轮4000次调用。输入数组4 KiB；静态表亦较小。初审指出其缓存与重复分支历史条件过于有利；最终版本已追加每域64个不同1000项向量、256000 bytes 的 pool。新增pool有192个向量，对5个入口做960次最终位比较（仍包含基线自比），日志为PASS。

pool并未成为实际Lean/官方计时，仍是已初始化表、重复遍历相同有限数据池的 C surrogate；但它已经足以推翻“单数组无表方案优势稳定”的推断。最新 median（ns/item）为：

| pool域 | call | boxed | dense_signed | wide64 |
|---|---:|---:|---:|---:|
| dense | 3.4661 | 0.8446 | 1.1199 | 4.2111 |
| relu | 3.6075 | 2.0746 | 3.6724 | 3.2224 |
| wide | 3.6984 | 1.0031 | 3.3627 | 7.2452 |

这支持保留表方案的本机机制机会，同时要求撤回对wide64的一般优越性描述。分支预测是合理的解释候选，但未有性能计数器证据，不应写成已经确定的归因。relu fraction低bit相关性在pool生成器中仍存在，见第2节。

代码记录了一次初始化和首次调用：这说明初始化并非0，但它是单次样本，不能当可靠统计量，也不能把该值与 warm median 拼成正式整调用速度。

尤其 `boxed` 模型只是预分配静态 `Box` 对象加指针，模拟依赖load：

- 没有 Lean Array 构造、对象分配、引用计数或析构。
- `init_tables` 同时初始化 flat、Box values、boxed pointers，且含512个位置。它不是任何一个 Lean 候选的准确初始化实现。
- 因此这个 init 数值既不是 Lean 完整初始化的测量，也不能严谨地称为其上界或下界。
- 不能按跨调用永远摊销来绕过题目要求；必须以官方 bench 实际计入的完整准备/转换/缓冲边界为准。

无需表的 dense/wide常量方案可避开本次这种数据相关表构建，但 Lean 闭合常量初始化及其读取形态仍需实际检查。

## 6. two-group wide (L=102/134) 精确性

实际 C 实现不是 L24 的8表通用版，而是专用于 `102<=E<=151` 的两组。两组都正确：

1. E102..133：`r=E-102`，r∈[0,31]；`N=M<<r<2^55`；`C=2^-48`。
2. E134..151：`r=E-134`，r∈[0,17]；`N=M<<r<2^41`；`C=2^-16`。

第一组 `N*C=M*2^(E-102-48)=M*2^(E-150)`；第二组 `N*C=M*2^(E-134-16)=M*2^(E-150)`。N 的有效位数仍至多24，所以两次 UInt64→Float32 转换都精确；乘积恰为目标 normal。组边界 E133/E134 也没有不连续或额外舍入。

signed variants 的整数负号构造在所测 GCC 的二补码解释下正确，且 N<2^55 避开 signed64 负端点溢出。但 C 中超出signed范围的unsigned-to-signed转换有实现相关性；交给 Lean 时应以实际 Int32/Int64 primitive 的语义及定理为准，不能用 C 运行结果替代该桥接证明。

## 7. 建议交付措辞

> 原始数值重构和两个移位改进在指定 IEEE 模型下精确；本机独立 C surrogate 已核查binary32/RN/FTZ/DAZ环境，并排除明显 DCE/FMA/重结合。表重构在单向量及64向量pool中都观察到热循环优势，值得一次固定 Lean 版本验证；双组UInt64无表版本在wide pool中反而变慢，暂不作为默认性能推荐。实际 Lean 转换等价证明、生成代码、全输入 raw 语义，以及含初始化与完整API边界的性能，仍未验收。

这已经是足够明确的推进理由，无需把有限 C 诊断包装成更强结论。
