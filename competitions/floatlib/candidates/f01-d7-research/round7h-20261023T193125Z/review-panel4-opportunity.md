# Panel4 表示与机会预检

**GO，仅限一个有界 codegen-only 探针；运行收益 UNKNOWN。** 921 已证四行×十列 SIMD 热循环不分配、不调用、不热栈溢出，但每 k 仍需四个 A 对象指针读取、四个 Float32 字段读取及两次 unpack/一次 lane merge。把四行的同 k 值放进一个四标量字段 F4 记录，有具体机会减少这些操作及 A 准备阶段的小对象数量。新的 F4、pack、调用者与生命周期尚未编译，不能把布局推导写成实测节省。

本次只写报告和 [JSON](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/review-panel4-opportunity.json)，不生成 Kernel，不改正在组装的 wide 主稿或任何 helper。00:46 UTC 最终源码冻结安排不变。只读取已完成 901/902/904/914/916 的实际输入，及现有 921 编译/runtime 证据；未查看未来输入、运行 CI/Git/网络或创建 agent。

## 实际 runtime 与 C 支持到哪一步

固定 Lean commit `293d5d0c0c3f3dded4688b3ccd6a33939ac5102b` 的原始 [lean.h](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round1h-20261023T110107Z/runtime-boundary/lean.h.raw) 为 136786 B / `982c731a1fbacc7688006f44f9f7af9d9e3e0247d310a728827f49e7f1466c13`；[object.cpp](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round1h-20261023T110107Z/runtime-boundary/object.cpp.raw) 为 100916 B / `b53499ae7db8ed722a489ae5a79a394b93f6fda2e6663a3784d886867583985a`。已重新核对原下载收据。该 commit 与 921 编译 trace 的 Lean 版本一致。

`lean.h:3007–3014` 明确把 Float32 放进 `lean_alloc_ctor(0,0,sizeof(float))`，再存/取标量字段。**Array Float32 的元素不是 immediate。** 头部为 8 B（151–156），constructor 大小由头、对象字段与标量区相加（772–776）；实际 mimalloc 分支按 8 B 对齐（32、482–520）。921 机器码的 F40 为 160 B payload 请求 168 B，也独立支持该布局。普通对象数组头为 24 B，后跟每槽 8 B 对象指针（190–201、941–955）。

| 表示 | constructor 请求 | 数组槽 | 四个值的请求布局 |
| --- | ---: | ---: | ---: |
| 现有 Float32 box | 12 B 逻辑大小，runtime 对齐至16 B/值 | 8 B/值 | 96 B |
| 拟议四标量字段 F4 | 8 B头+16 B字段=24 B/记录 | 8 B/记录 | 32 B |

F4 一行是**依照实际 header 及现有标量记录生成方式推导**，不是新 F4 的编译结果。这里列的是 runtime 请求布局，不是 allocator usable size、RSS、缓存未命中或耗时；后者 UNKNOWN。Vector 的长度证明在现有 `Vector F10 n` 机器入口中被擦除，B 参数直接作为数组读取；拟议 `Vector F4 n` 预期同样不增加运行时 wrapper，仍需实际编译确认。

921 原 C 为 1388863 B / `8a2a78e8a39566a6481bcdc2f13d839df503977dd18fd5689e3763ca470777fa`，热 asm 为 `d7710bbe98d748ab63ce244c2ab8ccb24bff6fa4df69bbc712ed3297b21dcb05`，精确路径与原对象绑定见 [921审查](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/review-wide-codegen-921.md)。当前检查重新验证了所用 C、asm、compiled source 与 capture metadata，未改变原件。

实际 C `39650–39677` 的 nativeA map 每元素执行一次 `lean_float32_of_bits`，再 `lean_box_float32`。RowStream.core `40817–40824` 先保留原 A，再构造全局 nativeA 和全局 packedB。原 A 仍用于精确 NaN 回放，不能删除。map 的 array_uset 经 header `1057–1062` 的 exclusive 检查，初次共享更新需按 `object.cpp:2728–2749` 复制指针数组；不是免费地覆盖并丢弃原 A。

另一个有用正例是实际 `Packed10.packB___lam__1` C `38499–38560`：十个带类型 Float32 局部量直接写入一个 40 B 标量 payload，未为这些字段逐个建立 Float32 box。相反，泛型 `Packed10.packet` C `38272–38340` 通过 `lean_apply_1` 读取装箱结果，再 unbox 到记录。**不能仅选了 F4 类型就假定没有临时装箱或闭包。** 新 prepare 应使用直接的四个 Float32 标量字段构造，最终由实际 C 裁决。

## 全部准备计时下的条件模型

无尾行时令 `H=batch*m/4`、`N=4*H*n`、`G=ceil(p/10)`，数组容量暂按长度计算。只统计 A 的主要 constructor/container 请求，不含原始 raw A、全局 packedB、输出/F40、行索引、闭包、Nat 临时对象、allocator 余量等。

- 现有 global nativeA：`N` 个 Float32 box 加一个数组，累计请求 `24+24*N = 24+96*H*n` B，主要对象分配事件 `N+1`，转换 `N` 次。
- 每块一个 local F4 panel：累计 `H*n` 个 F4 加 `H` 个数组，请求 `H*(24+32*n)` B，主要对象分配事件 `H*(n+1)`。它比一个全局数组多了 `H-1` 次 panel 数组分配，不能只报告记录数减少75%。
- 若每次仅持有一个 panel，且上一个在开始下一块前释放，额外 A 表示的峰值请求可从 `24+96*H*n` 降至 `24+32*n` B。B 仍全局打包，原始输入与输出仍存活，因此这不是进程总峰值内存的比例。
- 每块必须在所有 G 列组之前只 prepare 一次，才能仍只转换 `4*H*n` 个 A 值。在 g 循环内重建会把转换与 panel 分配乘以 G；若 guard 前仍构造全局 nativeA，F4 就成为额外准备，以上替代节省不成立。

每个 Float32 转换仍可在 prepare 中调用原 foreign ofBits；现有 global nativeA 本就每输入转换一次。该机制减少对象/间接读取，**不以在每 MAC 重做 foreign 转换为代价**。prepare 内跨四次 foreign call 的暂存或栈保存仍有成本，必须计入完整 gate。

若先创建所有 panel 的嵌套 Vector，再逐块使用，依然可以减少记录体积，但所有 panel 会被外层数组保留，不能宣称局部生命周期节省。理想接线是块循环内建 panel、借用给所有列组，完成该四行输出后释放；输出只保留原字结果，不应捕获 panel。实际 closure、RC 与释放点仍 UNKNOWN。

## 五组已公开形状的曝光

基准 wide guard 固定为 `batch>0,m≥4,p>2,n>4`；只计算同一 batch 内完整四行组 `batch*4*floor(m/4)*n*p`，尾行不计入该 MAC。以下都是**占该组全部 timed BMM MAC 的比例，绝非时间份额**。raw case 保留在 JSON，未计入 ROI。既有 p=2 Cross、n≤4 Direct 与该 guard 的交集为零。

| seed | 全部完整四行块 | 再限m%4=0 | 再限m≥8 | 同时m%4=0且m≥8 | 最后一列中p>10部分 |
| --- | ---: | ---: | ---: | ---: | ---: |
| 901 | 52.2315% | 10.6520% | 52.2315% | 10.6520% | 2.8094% |
| 902 | 32.6483% | 7.7258% | 22.4950% | 3.6329% | 3.6329% |
| 904 | 33.8966% | 1.8368% | 33.1914% | 1.1316% | 0% |
| 914 | 38.0853% | 9.5561% | 31.0995% | 9.5561% | 9.4706% |
| 916 | 39.8107% | 16.3993% | 33.8848% | 16.1812% | 16.1812% |

无尾行且 m≥8 的精确 case 数分别3、1、2、6、5。901主要为小 p，904该子集全为 p<10，仅复用一个列组；916该子集全部 p>10，按 F4 位置加权约复用5.546个列组。不能把单一组的有利布局当稳定分布。所有具体 shape、m≥8时尚未覆盖的尾行/MAC、p≥10/p>10分列与输入 SHA 均在 JSON。

无尾行且 m≥8 子集的条件 constructor/数组模型如下。这里的“请求字节/事件”不是实测分配器数据，也不含上述排除成本。

| seed | 原Float32 box数 | 新F4数 | 新panel数组数 | 原请求B | 新累计请求B |
| --- | ---: | ---: | ---: | ---: | ---: |
| 901 | 88792 | 22198 | 2287 | 2131080 | 765224 |
| 902 | 9680 | 2420 | 20 | 232344 | 77920 |
| 904 | 8824 | 2206 | 122 | 211824 | 73520 |
| 914 | 14168 | 3542 | 70 | 340176 | 115024 |
| 916 | 13924 | 3481 | 102 | 334296 | 113840 |

重新读取五份原 drawn-plan、cell_work、summary、verdict 与精确输入绑定，**395个 indexed 原件长度/hash全匹配**；复用只读计算模块前后 SHA 均 `b6ac1cdfd5d0979c7908c68ac81bb2e46abe894cb4ed884871a2a017297583e8`，没有生成输入或重写旧报告。

对无尾行且 m≥8 子集，整块“被触及 cell 的全部耗时”占 a066 whole 的松上界依次17.9051%、9.1777%、5.8351%、21.3788%、17.3070%；916实测 DirectContinuous 对应松上界为15.2421%。上界包括这些 cell 内其余 shape、准备、原字回放、输出和当前所有计算，远宽于可节省的 A 表示成本。逐 case、panel、尾部时间全部 UNKNOWN；不能用 MAC、对象数或字节比例分配它们。几个类别的 cell 上界重叠，不能相加。

## 证明与首次证伪检查

最小数学桥应逐字段给出：对 `r<4,k<n`，`packA[b,q][k].field[r] = ExecFloat.Binary.toFloat32 A[((b*m+4*q+r)*n)+k]`。随后每个字段的 k 归纳对齐现有 native loop，保留原乘法后加法顺序、+0 seed 与原字 NaN 回放。只改变存储并不自动给出 raw NaN payload 等价。列侧继续用既有 F10 lane 桥，不改全局 B 准备。

尾行需要独立后备、行优先输出序、每输出仅一次回放，以及 USize/巨大 Nat 边界。m%4=0 初始 guard 可避开尾行，但上表说明机会明显缩窄；不应为了覆盖宣称尾部免费。空输出不 prepare，n=0及不适用维度继续原路径。

建议在主 wide 源码冻结后，先做**一个未接入四入口的 F4 prepare+wordLoop 代码生成探针**。首个可证伪标准是：实际 prepare C 每 k 仅一份24 B标量记录请求、无四个临时 Float32 box；hot asm 从四指针+四字段+三 pack 指令，变成一个 F4 指针+一次偏移8的非对齐向量加载，同时保留原十组 SIMD 乘加且无新热调用/分配/栈访问。`movups` 是预期，当前仍未编译；若仍标量拼接或产生热 foreign call，应 PARK该表示路线。

然后才检查真实调用者：panel在g循环外构造一次、无global nativeA、跨列借用、下一panel前释放。该探针即使 fullPASS，也仍不能替代实际 BMM 接入证明与关闭 observer 的完整成本对照。此次没有省去现有 B打包、输出/F40分配、40参数ABI开销或 NaN 回放的依据，不把这些收益重复归给Panel4。
