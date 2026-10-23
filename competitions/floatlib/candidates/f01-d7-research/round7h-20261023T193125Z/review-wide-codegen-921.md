# 921 wide4 实际代码生成审查

结论：**GO，仅指继续已证明的实际 BMM 接入与有界成本实验。** 这次真实 statement 对象中的 `R11WideRows4.wordLoop___redArg` 已生成四行×十列 SSE 算术，k 回边内没有调用、堆分配、栈访问或整数除法。尚无该算法的实际 BMM 正确性验收或性能收益；当前四个入口仍为 a066，wide 定义没有接入。

审查于 2026-10-23 23:36—23:41 UTC 进行。仅写本报告及同名 JSON；未改源码、helper、原始证据，未运行 Git、CI、网络或本地 Lean/Linux 工具链。逐条指令及完整收据在 [JSON](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/review-wide-codegen-921.json)。

## 原件与编译绑定

- run `40039524733`，HEAD `3e1cdb890abc801f9a2f1c3f8d41d853c1bb57fa`，floatlib job `120707050589`，两者 conclusion 均 success。下载索引全部 **69/69** 成员重算长度与 SHA-256 一致。
- wide Kernel、保存的 `compiled-Submission.lean` 及当前本地探针均为 **241262 B / `eb9e76393b13448bd031134035706d3b05ce08b018f7d81dd5614db0c9ac007f`**。
- 原 a066 为 237142 B / `a06608bdc419d4647af301bfdd617d52e4796c404661a28672a022eef4a10b78`，是探针完整逐字节前缀；仅追加 4120 B。四个既有入口及其证明未被改写。
- 当前官方 `4b7e83841cc0c32c6529f533923c73d33b5ecf97`、public-v2 suite SHA `a16494e97c6a073bfd8accf72480c34534c87808092c56074fdcfa42cd34868a`；seed 921、25 rounds、500000 pairs。两个原 verdict 均 `passed=true / slot=full / stage=score / reason=""`，绑定 wide eb9e 与控制 41bce。full-mode summary 的 `statement_pass=false` 不是原 statement 失败结论。
- 捕获器 `3872fc7edf981e68fc139f23814bec6e62dd2a62389036607614a37b4cb028ed`，原 gate.py SHA `1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194`。这是同一个原 gate process 的 statement 输出旁路捕获，未额外重编译。

| 原件 | 字节 | SHA-256 |
| --- | ---: | --- |
| `file-0-Submission.c` | 1388863 | `8a2a78e8a39566a6481bcdc2f13d839df503977dd18fd5689e3763ca470777fa` |
| `file-1-Submission.c.o.export.trace` | 1303 | `4783a87e00e5fd7f574597508239bd68789951bf1a3253ffaa3b060599f55464` |
| `file-2-Submission.trace` | 21749 | `7a54654890bf69cccd74a3af1cf37f4c8453a3cf124abf113e84ed10aaf09b60` |
| 原对象（仅收据，已删除私有临时副本） | 564544 | `087deded94d8c128de3e6ff81d83827332f07f5fcad0bd025b34ee075057e795` |
| `nm-0.txt` | 36499 | `df40fa9e6db9457e37484607363f7aab807bc136f5063dd5709f47e8fec63d07` |
| `asm-0-0.txt` | 34707 | `d7710bbe98d748ab63ce244c2ab8ccb24bff6fa4df69bbc712ed3297b21dcb05` |
| `asm-0-1.txt` | 32053 | `d1078d959a85df8d9013cfdd49e1a3580574b29d5b8f488e25c24bcb87420c07` |

原 C / trace / asm 均位于 [capture 目录](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40039524733/download-0da81a10f7af486da7e3e5a19f864b7a/diagnostics/f01-d7-public-suite/public-suite/codegen/f01-r11-wide4-codegen-probe/capture-ff7f22510d27440f810c8119333bf631)。对象本身未保留，不能在本机独立重新反汇编；对象 SHA、临时副本 SHA 一致性、实际 nm/objdump argv、退出码及原输出均由保存的捕获记录绑定。最终链接二进制与链接映射未收集。

编译 trace 的真实命令使用 Lean 4.34.0（commit `293d5d0c0c3f3dded4688b3ccd6a33939ac5102b`）自带 clang，目标 `x86_64-unknown-linux-gnu`。选项包含 `-O3 -DNDEBUG -DLEAN_EXPORTING -ffp-contract=off -fstack-clash-protection -fdata-sections -ffunction-sections -fPIC -fvisibility=hidden`。完整命令在 JSON；没有从本地假编译推断这些参数。

## 真正 k 回边

实际符号是 **`lp_competition_Submission_R11WideRows4_wordLoop___redArg`，951 B**。`asm-0-0.txt:736–790`，偏移 **0x200–0x2df** 是唯一 k 回边，末尾 `inc r9; cmp rdi,r9; jne 0x200`。55 条指令中有十个 `mulps`、十个 `addps`，每个 SIMD lane 对应一个独立行，合计每 k 四十次乘法、四十次加法，没有横向 k 归约或 FMA。

十个累加向量分别位于 `xmm8,xmm4,xmm3,xmm5,xmm6,xmm7,xmm9,xmm10,xmm11,xmm12`。A 四行组装完成后为 `xmm0`，每个 B 标量广播到 `xmm1` 再相乘，因此 MAC 段是十个 accumulator 加 A/B 两个临时。**A gather 阶段还暂用 `xmm2`，回边实际出现十三个 XMM 名字；不能把“MAC 段十二个活跃寄存器”写成整个回边最多十二个。**

回边内直接核到的零项：`call=0`、`[rsp]` 访问 0、除法/取模指令 0、分配 0、新装箱 0。C 中的 `lean_array_uget_borrowed`、`lean_unbox_float32`、`lean_float32_mul/add` 均在这段对象机器码中消为取值与硬件算术，没有 foreign call。

仍存在的每 k 结构成本是四个 A 对象指针读取、四个 A Float32 字段读取、一个 F10 对象指针读取、十个 B 字段读取、两次 unpack/一次 lane merge 及十次广播。A 是预解码的 `Array Float32`，因此“回边无新装箱”不等于移除了上游 nativeA 分配或指针间接层。这里没有它们的净耗时证据。

C 对应位置：定义 `41767–42006`；借用数组读取 `41825–41839`；原始四十组乘加 `41842–41961`；递归改成参数赋值与 `goto _start` 在 `41962–42003`。源 `compiled-Submission.lean:6404–6444` 的 F40 按列存四行，`6446–6509` 是当前 wordLoop 定义及终止证明。

## 栈与分配分清阶段

入口 `asm-0-0.txt:646–735 / 0x0–0x1f6` 的 `sub rsp,0xa8` 及 `[rsp+0xd0]…[rsp+0x1c8]` 加载发生在 k 回边前。四十个标量浮点参数中首八个由 XMM 传入，其余三十二个从调用者栈读取，再构造十个累加向量。这是每次调用的 ABI 开销，**不是每 k spill**。

退出后 `791–835 / 0x2e5…` 保存十个累加向量到栈，调用 `lean_inc_heartbeat` 和 `mi_malloc_small(0xa8)`，再恢复并写入结果。C `41775` 为一次 `lean_alloc_ctor(0,0,160)`，对应 160 B 浮点 payload 加对象头的 168 B 请求。此处保存是为跨分配调用保留结果；包括 count 已结束的调用也需构造 F40，不能称整次调用无分配。错误分支的 OOM panic 也在回边外。

## fullPASS 的精确边界与下一判别

保存源码 `6381–6394` 的最终 bmm 仍为 `n≤4 ∧ p>2 → DirectRows.core`，否则 `bmmBeforeDirectRows`。原 C `41733–41765` 一致。Wide 只在既有 `bmm_spec` 后追加，全部 C 调用引用仅来自它自己的标准/boxed ABI wrapper，没有任何 BMM 或输出调用者。因此此次原 full gate 证明既有入口可用，并编译了探针定义和终止证明；**没有证明四十路结果与 referenceBmm 相等，没有执行 wide 矩阵算法的成本测量，也不能从该 full-gate 的 ratio 推出 wide 收益。** 最终链接可能移除未使用 section，当前是否保留该符号为 UNKNOWN。

快照复制时间为 `23:29:11.050108–23:29:11.054782 UTC`，约 4.67 ms。记录称其早于 reader 观察到 score，但原日志时区无法确认，`capture_vs_axioms_emission=UNKNOWN`；CPU/cache 扰动仍 UNKNOWN。此轮不能作为 clean 独立确认。

最小下一步是一个有证明、接入真实 guard 的宽行 BMM：保留每输出的 k 顺序、+0 种子规则、NaN 原字回放、尾列/尾行及巨大 Nat 后备。先捕获真实输出调用者及其 wordLoop，证伪接入后是否又引入闭包、装箱或热 spill；随后关闭 observer，以完整公共 suite 成本判定打包、输出和 ABI 开销是否抵消共享收益。此前形状/MAC 曝光只能给机会，不能分配 cell 耗时或预报收益。
