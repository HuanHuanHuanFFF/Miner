# R7-W15 runtime 叶函数选件复核

2026-10-23 01:35:43–01:44:56 UTC；复核人 nan_probe_review_r7。未参与 W15 的取源、审计脚本或反汇编生成。本次只读已有原件，未运行编译、候选、gate、计时或外部工具链。

**结论：六份函数摘录均是原始 objdump 中的完整精确符号段，31/16/7 字节、ABI 和 canonical 常量的文本证据一致。** 这是回收文本的一致性核查；三个大二进制未随包持有，其哈希仍是外部记录。任何最终 CI 链接对象的身份和收益均 UNKNOWN。numeric mul/noinline 继续 PARK。

选件核了 119 个 W15 文件、560,081 bytes，逐一重新 SHA256，与 `manifest.json` 和 `SHA256SUMS.txt` 同时相符；没有重做大 ZIP/CRC 全扫。完整路径、SHA、命令参数及各函数编码 SHA 在 [JSON](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/runtime-primitives-w15-review.json)。回收原件均 LOCAL_ONLY，未制造远端文件链接。

| 目标 / 精确符号 | 完整地址范围，右端不含 | bytes / 指令数 | 原始 stdout 行 |
|---|---|---:|---:|
| shared / `lean_float32_of_bits` | `0x98fd550..0x98fd56f` | 31 / 8 | 11–19 |
| shared / `lean_float32_to_bits` | `0x98fd570..0x98fd580` | 16 / 5 | 11–16 |
| shared / `lean_float32_isnan` | `0x98fd440..0x98fd447` | 7 / 3 | 11–14 |
| archive / `lean_float32_of_bits` | `.text+0x61e0..0x61ff` | 31 / 8 | 7–15 |
| archive / `lean_float32_to_bits` | `.text+0x6200..0x6210` | 16 / 5 | 7–12 |
| archive / `lean_float32_isnan` | `.text+0x60d0..0x60d7` | 7 / 3 | 7–10 |

复核从每个 raw `.stdout` 的唯一精确符号头开始，取到紧随其后的空行，与对应 `.function.txt` 比原始字节；解析每条指令地址和机器码，确认地址连续、长度恰好到符号末尾、末条为 `ret`。六份均相同，无截尾、混入相邻函数或只取热块。原始命令是 `objdump -drwC --disassemble=<精确符号>`，两类各三条的 exit 文件及 command metadata 均为 0，stderr 均空。可从 [shared of_bits 原 stdout](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W15/original-extracted/R7-W15/evidence/binary/shared-lean_float32_of_bits.stdout:11) 和 [archive of_bits 原 stdout](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W15/original-extracted/R7-W15/evidence/binary/archive-lean_float32_of_bits.stdout:7) 核入口；另外四份精确路径见 JSON。

`readelf -Ws` 与 `nm -S` 的地址/大小全部吻合。shared 每个符号在两份符号表记录中出现，都是 GLOBAL FUNC、section 14；archive 三个提供者均是 `object.cpp.o`，section 2 `.text`、GLOBAL FUNC。shared 地址是 ELF 链接虚拟地址，不能当进程实际 PC；archive 数值是节内偏移。

| 函数 | 已核源级 C 类型 | 当前 x86-64 标量寄存器接口 | 完整函数形状 |
|---|---|---|---|
| of_bits | `float(uint32_t)` | EDI → XMM0 | movd、NaN 自比较/掩码、常量 load、ret |
| to_bits | `uint32_t(float)` | XMM0 → EAX | ucomiss、movd、固定整数常量、cmovnp、ret |
| isnan | `uint8_t(float)` | XMM0 → AL | ucomiss、setp、ret |

这六个符号段内没有 call、allocator/RC 引用、显式栈帧或显式栈内存操作。`ret` 本身仍依赖返回地址栈。无内部 call 仅描述这些 callee，不证明 caller、PLT、保存寄存器或整个 bench 闭包边界免费；也不是每次 UInt32 标量调用都分配堆对象的证据。

共享库 `of_bits+0xd` 的 `movss` 位于 `0x98fd55d`，指令长 8，disp32 原字节 `6f 00 96 f8`；独立按 next-RIP 加有符号位移得到 `0x225d5d4`。限定 `[0x225d5d4,0x225d5d8)` 的 [原 dump](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W15/original-extracted/R7-W15/evidence/binary/shared-constant.stdout:5) 为 `00 00 c0 7f`。archive 在 `.text+0x61f1` 的 [原 relocation](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W15/original-extracted/R7-W15/evidence/binary/archive-member-relocations.stdout:1104) 是 `R_X86_64_PC32 .LCPI135_0 - 4`；符号记录将 `.LCPI135_0` 定到 section 32 `.rodata.cst4+4`，该节 `[4,8)` 的 [原 dump](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W15/original-extracted/R7-W15/evidence/binary/archive-constant.stdout:5) 同为四字节 `00 00 c0 7f`。ELF header 确认为 little-endian x86-64，故均为 `0x7fc00000`。to_bits 的该常量直接在指令立即数内；不是凭符号注释猜值。

23 份二进制检查命令回执中，22 份 exit 0；唯一例外是 [shared-related-relocations](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W15/original-extracted/R7-W15/evidence/binary/shared-related-relocations.command.json)。其原命令为 `set -o pipefail; readelf -rW … | rg 'lean_float32_(of_bits|to_bits|isnan)(\\s|$)'`，exit **1**，stdout **0 bytes**，stderr **0 bytes**。这是既定名称筛选未命中的回执，不能改写成整条命令 PASS/0，也不能当链接错误。该命令未独立保留 readelf 上游退出码或未过滤输出，因此不推断全库无相关调用或最终无 PLT。archive 提取命令的 stdout 是写到外部 `/tmp/r7w15-object.cpp.o` 的二进制流，包内没有对应文本 stdout；exit0/stderr0 和目标路径有原回执。

固定源码读取的是 Lean commit `293d5d0c0c3f3dded4688b3ccd6a33939ac5102b`：

| 原件 | 实际持有 bytes / 本次重算 SHA256 | 精确接口位置 |
|---|---|---|
| [object.cpp](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W15/original-extracted/R7-W15/source/upstream/src/runtime/object.cpp:1976) | 100916 / `b53499ae7db8ed722a489ae5a79a394b93f6fda2e6663a3784d886867583985a` | isnan:1976；of_bits:1987–1993；to_bits:2000–2004 |
| [lean.h](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W15/original-extracted/R7-W15/source/upstream/src/include/lean/lean.h:2948) | 136786 / `982c731a1fbacc7688006f44f9f7af9d9e3e0247d310a728827f49e7f1466c13` | isnan:2948；of_bits/to_bits:3253/3254 |

两次原 curl 均是固定 commit 匿名 URL，原 HTTP 响应为 200、exit0；stdout 为空，stderr 各 317 bytes 是进度条。对应 command/headers/stdout/stderr/exit 全部在此次 119 选件中核了 SHA。原 `lean --version` 回执 exit0，明确给出 4.34.0、x86_64 和该 commit。W15 头文件与本地持有的 W11 头文件还做了完整字节相等比较，均为上述 `982c…`，而非只信 metadata。

源码使用 extern C 导出的标量接口；of_bits 先 bit_cast，再把 NaN 改为实现定义的 quiet_NaN；to_bits 用 object.cpp:1998 的固定 `quietNaN32=0x7fc00000`。因此仅凭源码不能给 of_bits 的 quiet_NaN 指定物理位型，本次两个记录的二进制 dump 补足了该构建的常量证据。NaN 的 sign/payload/signaling 属性不承诺往返保持；未证明 FP flags/trap 行为，也未运行值域测试。源码/header/version 绑定不等于独立重建并证明二进制可复现。固定公开原源：[object.cpp](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/runtime/object.cpp#L1976)、[lean.h](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/include/lean/lean.h#L3253)。

| 缺失二进制 | 原记录 bytes | 原记录 SHA256；本次不能重算 |
|---|---:|---|
| libleanshared.so | 233656768 | `ab523f803d805db2c08eb755f0fa8189345bf6ae9b408664cdf3cf67fa0112d9` |
| libleanrt.a | 1264720 | `11f3c08cfd66b00741e125f350390198518616df32bff9c5784d66b0082111c4` |
| object.cpp.o | 163784 | `64a2bd38873c39f720dc2aaeb698f4c0ed6895e59f424849aeb18c2f10a68e46` |

此次只确认包内无这三个二进制，并核了持有的 identity 文本；不能用 identity 的哈希替代实际 binary 字节。与任何 CI 最终链接对象的绑定仍 UNKNOWN。

W11 的 [MainFull 原始 objdump 560–569 行](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/evidence/elf/raw/MainFull/objdump-disassembly.stdout:560)，SHA `b0f1a5ca130057f486431b5c12c5c6aa4967dfe269ba7f374bafd431f4876d02`，仍显示普通乘法入口 `+0x20d/+0x21a` 两次 of_bits 的 PLT32 relocation call、`+0x212` spill、`+0x22c` 到 to_bits 的尾跳 relocation。PLT32 记录本身不决定最终 linker 会直接绑定、松弛还是保留 PLT。W15 没有把这些边消掉，没有周期或收益证据。

本次又核 W11 原两份完整目标构建 command/exit：600s 和 100s 都 exit124；build-artifacts 原记录 `benchFull exists=false`。W11 是公共精确60f的独立诊断对象，完整链接未完成；不是原25轮计时后被清理的对象。顺手读取 R 的 [subject audit](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/codegen-subject-audit-807-w11.json)，只作为已记录上下文：807保存的诊断 C/asm 属8eb，W11属60f，本次未重新审遍8eb原件。不同 subject 的 C 不相同不能推成编译器不稳定，也不能把两者或原 score 对象互认。

维持停放；只有绑定当前真实 caller/最终链接对象、看到调用边界发生变化，再完成规定完整配对计时，才足以重开成本判断。W15 本身未提出实现变体，未改变任何新候选的 Lean/fullgate/C/性能 NOT_RUN 状态。

