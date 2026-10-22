# R2-W03 codegen / 完整成本独立审计

状态：**已读固定tag源码，已运行独立C诊断；Lean候选编译、官方gate、官方bench均 NOT_RUN**。没有安装工具链，没有修改依赖、账户、编译参数或官方benchmark。

## 1. 结论边界

有真实而窄的性能机会：out-of-line `ofBits` 除call本身外，会迫使调用者保存跨call存活的浮点累加器；内联数值重构能够去掉hit路径的call和累加器spill/reload。在本机独立C模型，这个差别已经出现。不能把这一结果叫Lean加速：C模型没有Lean输入对象、数组bounds、RC、closed term once检查、FloatLib包装以及完整守卫/回退成本；输入为本轮合成1000-item向量，绝非官方bench。

浮点转换不改变ordered sum的顺序；所有诊断始终从+0逐项加，没有并行局部和，没有FMA。本候选也不预转换输入数组。

## 2. 固定源码核查

1. `src/include/lean/lean.h:3253–3271`：ofBits/toBits外部；add/mul/neg为inline C；UInt32、UInt64、Int32、Int64转Float32都是inline C cast。
2. `src/runtime/object.cpp:1987–2003`：ofBits先bit_cast，NaN规范化；toBits将NaN返回0x7fc00000。**不能用native转换保留raw NaN payload**。原软件payload路径必须独立保留。
3. `src/Init/Data/Float/Float32.lean:303–304`：UInt32.toFloat32是有`.ofModel(.ofUInt32 n)`定义的def；其逻辑语义并非opaque。Float32被编译器识别为C float。
4. `src/include/lean/lean.h:963–965, 998–1012, 3007–3014`：通用Array存对象指针，Float32 box是独立对象。Array Float32 lookup通常先读数组中的pointer，再unbox读取float；非borrowed accessor还可能有inc。不能假设C的`float table[512]`形状。
5. `src/Init/Data/FloatArray/Basic.lean:17–21`：FloatArray是Array Float(double)，不是Float32 packed数组。不能未经证明借opaque Float32↔Float往返取得packed表示。
6. `src/Lean/Compiler/LCNF/EmitC.lean:84–93, 629–634`：被lift的closed Float32/Array通过lean_float32_once/lean_obj_once读取。`lean.h:3376–3380, 3430–3434`热路径仍读取atomic state并分支。
7. 但**不能反过来说每个命名常量每次都带once检查**：EmitC.lean:1003–1005给普通无参数named declaration在module initializer中赋全局值。`stage0/stdlib/Init/Data/Float/Float32.c`的Float32.nan给出实例：初始化时调用once，正常引用可读全局。建议纯表为普通命名顶层def，loop前绑定，最终以该候选generated C确定是否hoist成功。
8. **固定tag默认禁止FMA contraction**：`src/CMakeLists.txt:219–221`把`-ffp-contract=off`加入LEANC_EXTRA_CC_FLAGS和LEAN_EXTRA_CXX_FLAGS。Lake的`Config/LeanConfig.lean:117–121`中release参数是`-O3 -DNDEBUG`。官方fixed commit `gate.py:540,543`执行`lake build`，该文件未发现浮点参数override，已给lakefile也无moreLeancArgs覆盖。因此存在不改变编译选项的正常实现路径；最终仍需检查官方实际编译命令是否override，检查汇编。不能拿本诊断flags替代官方构建证据。

以上文件本轮从指定公共tag下载，URL/SHA256/字节数在source_manifest.json；未读旧项目或私有附件。

## 3. 常量表合法实现与成本

推荐先比较一个**带符号的scale表**：index=u>>>23（9位，包含sign）；normal E≥24且E≤254时，表项是带输入sign的2^(E-150)，M始终正，结果是M.toFloat32 * signedScale[index]。数学上省掉最后float neg；代码生成上省掉随机sign branch。该表仍是纯数学常量，绝不是输入或结果cache。

可用512项表（非法/回退entry给任意有限占位，guard证明不读取它们）。或者231项正表+单独neg；后者表小但可能留下随机sign分支。本诊断比较带符号512项flat/boxed形状；未生成512项Lean literal。

完整准备账必须包含：常量构造、每个必要ofBits调用、Float32 boxing、Array分配/构建、持久标记或once初始化，以及冷cache。顶层预定义纯表可以让这些成本每process支付一次，但**这不自动满足本用户要求的“所有准备计入”**：报告应给冷启动/首次调用总成本和稳态分别计量，若官方计时入口只排除模块初始化也须显式记账，不能把初始化藏出总成本。逐次构建表则必须每次计入，不能把它叫常量免费。

Array中的Float32值不是每次读取都重新box；box可在构造时发生。实际RC是否优化掉、是否borrowed、once位置、bounds check是否消除，都需要generated C检查。

纯match exponent 的代价也不保证小：大量分支/跳转表，case内closed scalar可能带once读取；它可能比Array差，也可能让C编译器形成理想常量加载。没有Lean编译不能预判。范围证明本身会擦除，但Nat转换、运行时bounds、所选accessor仍可能收费。

## 4. 表外最小对照

### DenseShift

对124≤E≤130，r=E-124，N=M<<r，N<2^30，且只有24位有效significand。N可以大于2^24，但仍是精确binary32整数，不应错误地以N>2^24否决。

`y = N.toFloat32 * 2^-26`，然后施加sign。它用一个常量与一次shift替代动态表读取；无数组准备。

可以把sign提前进整数：mask=0-(u>>>31)，signedBits=(N xor mask)-mask，再`.toInt32.toFloat32 * 2^-26`。因为N<2^30，解释成有符号整数安全；这样去掉随机浮点sign branch，但增加整数操作和Int32模型桥接证明。C诊断没有稳定显示signed版本必胜，不能只按指令个数判定。

### WideShift64

对102≤E≤151：若E≤133，用r=E-102、scale=2^-48；否则r=E-134、scale=2^-16。N=UInt64(M)<<r、0≤r≤31、N<2^55，仍只有24位有效significand。`N.toFloat32*scale`精确，最后施加符号。

在GCC13.3这段实际C里，unsigned64转换已经根据范围变成一个signed `cvtsi2ss`，没有昂贵的UInt64高位分支。显式signed整形sign trick版本并非免费，也未稳定优于unsigned+float neg；先检查真实Lean C能否推导同样范围。

## 5. 已运行C诊断

- host：x86_64，AMD EPYC 9V74，GCC13.3.0。
- 三个独立translation unit；无LTO，模拟ofBits为external call。目标代码不使用固定种子或数据特化。合成输入seed默认取时钟，并写入日志；可CLI传seed供复现。
- 编译：`-O3 -std=c11 -fno-fast-math -ffp-contract=off`。这是独立诊断，不修改或代表官方参数。
- 8个converter，每种18个明确边界输入+每biased exponent2048个合成bit-pattern，共4,194,448次converter比较通过。包括±0、最小/最大subnormal、min normal、E23/24边界、max finite、±Inf、正负quiet/signaling NaN。
- **比较对象是native canonical-NaN语义**；不是FloatLib原始payload合同的完整gate。特殊类fallback仅证明本converter没有比native原函数多改结果。
- 4个域（dense/relu/wide/raw）每域1000项，8个ordered sum逐位对比native baseline均通过。
- 每项时间：每case11轮，各4000次完整1000项sum，变换variant计时顺序，表中为median ns/item。非独立重复采样置信区间，raw结果可能很快进入NaN，不能据此推算实际raw吞吐。

| 版本 | dense | relu | wide | raw |
|---|---:|---:|---:|---:|
| call | 3.7750 | 3.6183 | 3.5441 | 3.5974 |
| zero | 3.6347 | 2.3701 | 3.5947 | 3.5513 |
| flat | 0.8824 | 0.8511 | 0.8959 | 1.0900 |
| boxed | 0.8866 | 0.8535 | 0.9204 | 1.0912 |
| dense | 1.0925 | 0.9661 | 3.1757 | 3.5048 |
| dense_signed | 1.1771 | 0.8736 | 3.1575 | 3.4410 |
| wide64 | 1.1484 | 0.8950 | 1.2671 | 3.0039 |
| wide64_signed | 1.3412 | 0.9089 | 1.4151 | 3.0149 |

`zero`只有+0直接生成Float32零，其他仍external call；它是区分relu的zero收益与数值重构收益的必要control。

计时日志中首个cold sample：baseline 1000项3425ns；静态table初始化2574ns；table初始化+boxed首个1000项3435ns。**这是没有heap allocation/Lean RC的C surrogate单样本**，只说明准备成本能吃掉首次调用收益，不能视为Lean cold值或确定成本。稳态表值未将setup摊入每次sum。无表方案只有一/两个scalar常量；真实Lean仍须把这些常量初始化记账。

汇编实证：sum_call每个元素`movss`保存acc到栈，调用runtime_of_bits，然后恢复acc再addss。命中重构快路时acc留在xmm寄存器，只有cvtsi2ss、mulss、addss等；无call、无FMA，没有SIMD重结合。table_boxed比flat多一次dependent pointer load，诊断中未产生RC/bounds。

### 独立复查提出的分支历史反证：64向量pool

前面的单个1000-item数组被重复计时，会使cache/分支历史过于有利；不能把该表直接外推到任意新输入。为解除这个具体风险，只补一项有限实验：每域64个不同raw UInt32向量（总256,000byte），逐个完整ordered sum，不建立输入Float32转换数组。每个sweep对64个输出形成可观测checksum；5轮×128 sweep，各variant轮换顺序。追加960个逐向量逐位比较全部通过。输入生成/分配时间单列在日志，不冒充candidate执行时间；常量table仍是warm且setup单列。

| 版本 | dense pool | relu pool | wide pool |
|---|---:|---:|---:|
| call | 3.4661 | 3.6075 | 3.6984 |
| zero | 3.5897 | 3.4846 | 3.6130 |
| boxed | 0.8446 | 2.0746 | 1.0031 |
| dense_signed | 1.1199 | 3.6724 | 3.3627 |
| wide64 | 4.2111 | 3.2224 | 7.2452 |

**反驳成立**：WideShift64在wide pool反而约7.25ns/item，明显慢于external call约3.70ns/item；在dense pool也反慢。其汇编保留随机sign branch，wide还多一条指数分段branch。不能把“无表”当成性能保证。DenseSigned在dense pool仍有机会，但relu出现退化；随机+0分支是可能解释，尚无硬件计数器证据。带符号boxed scale表在三种pool仍领先，故本轮C证据更支持把它作为首个真实Lean codegen验证对象。WideSigned64的pool未运行；单向量数据不足以给它晋升。

这仍是合成C诊断而非目标Lean测量；没有估计完整guard、回退、proof wrapper、actual input representation、表heap allocation。

环境检查为实际通过：float.h确认sizeof(float)=4、FLT_RADIX=2、FLT_MANT_DIG=24、FLT_MIN_EXP=-125、FLT_MAX_EXP=128、FLT_EVAL_METHOD=0；fegetround=FE_TONEAREST；MXCSR=0x1f80，FTZ=0、DAZ=0。程序只读取这些状态，若不匹配则退出，不修改浮点环境。

## 6. 下一次设备/Lean验证的停止条件

最少比较四种完整API：原有转换、仅+0快路、常量table重构、DenseShift/WideShift64（必要时选择其中覆盖目标域者），其余guard/回退/输出路径完全相同。首先看Lean生成C/汇编：快路径残留ofBits/boxed调用或per-item alloc/once重复、循环acc仍每元素spill、未保持strict add次序，都先判机制未实现；不要用手写C成绩晋升。

若完整首次调用含所有准备后不及baseline且目标只调用一次，table方案可直接PARK；可单独检验无表Shift候选。若完整稳态没有改善，先结合generated C解释实际瓶颈，不因C surrogate高倍差别继续大量变体。若FloatLib附加证明不能在仅ContractTensor/允许公理下完成，候选仍不能进入验收。

## 7. 文件与状态

- runtime_stub.c、variants.c、diagnostic.c：本轮自写有限C surrogate，**不是新增Lean FFI**，不随Kernel提交。
- run_diagnostic.sh：本地复现；可执行`bash run_diagnostic.sh [seed]`。
- diagnostic.log：本轮实际输出；compiler_version.txt：编译器版本。
- surrogate_assembly.txt / runtime_stub_assembly.txt：实际本地C汇编。
- source_manifest.json：公开fixed-tag证据URL/SHA。
- Lean compile / official gate / official bench：**NOT_RUN**。
