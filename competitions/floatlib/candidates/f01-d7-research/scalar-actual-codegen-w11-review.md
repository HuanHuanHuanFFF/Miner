# W11 实际标量代码生成独立复核

开始：2026-10-22 23:42:02 UTC；本任务上限 45 分钟，主窗截止仍为 2026-10-23 04:22:17 UTC。只写本报告及同名 JSON；没有修改候选、R 文件或执行 Git、CI、上传、编译器安装。

**决定：停放选择性 noinline LowScale。** 实际 MainFull 乘法普通有限路径只经过 **89 字节、26 个指令位置**，已经跳过内联软件块。LowScale 仍然内联，不能写成“编译器已经隔离”；但现有对象满足此前“热入口很短即停”的条件。没有链接后布局、缓存命中或计时证据支持继续制造变体。外部 Float32 位转换调用确实保留，具体周期与可实现收益仍为 **UNKNOWN**。

## 精确来源与验收边界

W11 的 [原始 Kernel](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/source/Kernel.lean) 与本地 `f01-d7-direct-nonnan/Kernel.lean` 逐字节相同：155103 字节，SHA-256 `60f74aa4af01a9b35ece66a7c310e6b05b5b84b9b7121a4cccd12a0a9c987e15`。[公开精确源](https://raw.githubusercontent.com/HuanHuanHuanFFF/Miner/f69da28963f2a68cf9232818b4facf74de161d5b/competitions/floatlib/candidates/f01-d7-direct-nonnan/Kernel.lean) 的 Git blob 为 `82ccbe5ed9dfd725a1e380b672a55b454b78166a`；以 [身份原件](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/evidence/kernel-identity.json) 和 [最终身份原件](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/evidence/kernel-final-identity.json) 绑定。

固定环境：官方 `4b7e83841cc0c32c6529f533923c73d33b5ecf97`，FloatLib `0d91825727839f597fd06b22fdd038ea21480f0c`，Lean 4.34.0 / `293d5d0c0c3f3dded4688b3ccd6a33939ac5102b`，clang 22.1.4 / LLVM `35990504507d79e0b9deb809c8ee5e1b34ceef20`，x86_64。实际命令包含 `-O3 -ffp-contract=off -fdata-sections -ffunction-sections`，没有 LTO 标志。见 [编译命令原行](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/logs/target-facets.stdout:5663)、[版本原件](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/logs/toolchain-version.stdout)、[依赖版本原件](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/evidence/dependency-revisions.json)。

五份实际采用的官方 Lean 文件另与 harness-source-manifest、official-original-files、official-source-preservation 的原始哈希链逐项相符，固定在上述官方 commit。

本次鲜核 **77 个引用原件，共 28,141,574 字节**，每个 SHA/字节数均与 W11 `manifest.json` 及 `SHA256SUMS` 双重相符；这是引用子集审计，不冒充整包审计。同名 JSON 保存逐件哈希、完整命令、符号大小与实际指令抽取。

| W11 原始动作 | 原始结果 | 本次可作结论 |
|---|---|---|
| 22:35:03 开始 `build VerifyFull benchFull`，600 秒上限 | exit **124** | 完整目标构建尝试超时 |
| 22:48:02 恢复同目标，100 秒上限 | exit **124** | 第二次完整目标构建尝试超时 |
| 22:45:34 单独构建 Submission/MainFull/Bench/BenchFull/BenchSuite 的 C/object facets | exit **0** | 五模块诊断对象实际产生 |

两次超时尾日志仍在依赖编译（7812/8232、7992/8232）；没有查到最终 `benchFull` 链接命令，[产物记录](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/evidence/build-artifacts.json) 的 `benchFull.exists=false`。因此保留“两次完整 build/link 目标超时”，**不能断言最终链接器本身超时**。恢复日志的 MainFull:c.o 是 [Replayed](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/logs/official-resume.stdout:5659)，不计为另一次新编译。

以下都是独立诊断 **ELF64 ET_REL 对象**，不是清理后的 25 轮 score 对象，也没有完整链接 ELF、W11 全 gate 或计时收益。二进制对象未打包；下表对象 SHA 来自 W11 保存的检查前/后身份记录，两者相同，**本机没有重新散列缺失对象二进制**。本机鲜核的是生成 C、原始反汇编/重定位、命令与元数据字节。

| 模块 | C 字节 / SHA-256 | 记录对象字节 / SHA-256 |
|---|---|---|
| Submission | 715720 / `69cc5063eb3fadad54df3a0b849c0261d7eae170a56bf25ec830c1dadfc0c7d6` | 193776 / `26974d94bd560615dd0c9927c00c809bc61e7cef6c56ac9271649a29f1539800` |
| MainFull | 83831 / `72d050dd6da03770c38f0344f8f4c0bfd1c25f62a236d636acc1f496d4524aad` | 12832 / `f87b30d3644aa60f2b604a19f88525f3ea5c6cdd73b4abaea1ec981fc160783f` |
| Bench | 148451 / `0e241f41ba3de5d960a9e36e99db572d14783d8549e820c8d2df6744746e8894` | 121896 / `3a9f28e29febbf01b98b0cfb8f6c1132d2218c74adee562afb7da19f9d800dd6` |
| BenchFull | 66403 / `f0dd6ef5182ef899afe4b286ef554390f358527c104133b44d274631965522c5` | 39584 / `aca0f9a70ab767a5890fca95bbb2c0c9a833d9c7886f7a4ab38d1a87ae17a104` |
| BenchSuite | 393988 / `959b8a6c43010728275d57b3087f4b15a14035dc40832ed713439073cad8a1a7` | 287352 / `5f9647fdd7f2864a78942e51d6d3117754f4a97a58182cd295f26a53edbdb374` |

## 真实闭包调用与分配

**VERIFIED：** [MainFull 原始入口](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/source/official/lean/bench/MainFull.lean:8) 用 BENCH_PLAN 选择 Suite 或 legacy。[生成 C 62—71 行](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/generated/MainFull.c:62) 是静态闭包（`m_rc=0`）；[实际 data relocation 117—135 行](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/evidence/elf/raw/MainFull/readelf-relocations.stdout:117) 将 add、legacy mul、suite mul 分别绑定到 `main___lam__0___boxed`、`lam__1___boxed`、`lam__3___boxed`。候选算术已被 Lean 克隆进 MainFull 本地 lambda；真实标量入口不能仅用独立 `Submission_mul` 概括。

| 真实调用位置 | 实际对象证据 | 含义 |
|---|---|---|
| legacy `Bench.sweep` 的 range loop | 880 字节，`+0x1ae → lean_apply_2`；[C 调用](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/generated/Bench.c:1753) | 每元素仍通过通用闭包接口 |
| Suite `runScalar` 的 array loop | 301 字节，`+0x86 → lean_apply_2`；[C 调用](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/generated/BenchSuite.c:8443) | 同一接口在 suite 中保留 |
| MainFull mul boxed wrapper | 116 字节；[原始反汇编 673—716 行](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/evidence/elf/raw/MainFull/objdump-disassembly.stdout:673) | `+0x2c` 直接调用本地未装箱 lambda，当前没有合并该调用 |

**UInt32 装箱不等于每次堆分配。** 固定 [lean.h 334—336 行](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/source/toolchain/include/lean/lean.h:334) 的 `lean_box` 是 `(n<<1)|1`；[2955—2974 行](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/source/toolchain/include/lean/lean.h:2955) 只有 32 位目标的 UInt32 分支需要分配，本次 ELF64 使用立即数。头文件 SHA 为 `982c731a1fbacc7688006f44f9f7af9d9e3e0247d310a728827f49e7f1466c13`，并由 [实际 include 路径回执](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/evidence/toolchain-source-files.json) 对齐实际编译器。

wrapper 实际做两次 tag test（`+0x4/+0x15`）、两次右移解包（`+0x26/+0x29`）、本地 body call，再以 `lea` 构造标记结果（`+0x33`）。其仅有的另外两个外调是非 scalar 参数的冷 `lean_dec_ref_cold`；没有 allocator。装箱 ABI 仍有解包、调用和间接派发成本，但不能把它写成每次调用 heap alloc。这里没有展开 `lean_apply_2` 的运行时内部，也不推导整个后端无分配。

真正分配另列：

- Suite 的 pair `lean_alloc_ctor` 位于 [生成 C 8405 行](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/generated/BenchSuite.c:8405)，generator/pass closure 位于 [8499、8503 行](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/generated/BenchSuite.c:8499)。[官方 196—204 行](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/source/official/lean/bench/BenchSuite.lean:196) 先构造输入数组，再调用 measure。
- 元素循环的 `lean_apply_2` 在 8443 行，随后解包校验和与循环回边；[8430 行](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/generated/BenchSuite.c:8430) 的 IO 结果构造属于**遍历结束**分支。[实际 loop 汇编](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/evidence/elf/raw/BenchSuite/objdump-disassembly.stdout:19219) 的 `+0xe6 → mi_malloc_small` 前传入 16 字节，位于 loop termination 路径，不是每元素回边。
- [measure 184—194 行](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/source/official/lean/bench/BenchSuite.lean:184) 每个 pass 用时钟包围；pass 结果构造属于这个边界，输入准备在它之外。不能因此宣称整个 bench 零分配。

**INFERRED：** 固定官方 harness、分模块编译且无 LTO 时，单改 Kernel 没有已验证方法去掉 Bench 中的外层 `lean_apply_2` 接口。候选仍可改变本地算术及 MainFull clone，甚至可能影响 wrapper→body 的内联决定；后者是 **UNKNOWN**，须新对象证明，不能把所有调用边界都称为不可变。

## 实际 mul：大函数与短普通路径

以下偏移均为 **ET_REL section 内相对符号入口的偏移**，不是最终地址，不据此推断 cache line。原始视图为 `objdump-disassembly.stdout`（`-drwC`），不用派生 `objdump-parsed-view` 的行号。

| 实际符号 | readelf 大小 | 普通有限路径 |
|---|---:|---|
| `Submission_mul` | 894 字节 / 250 个指令位置 | `[0,0x32) + [0x214,0x23b)`，89 字节 / 26 个位置 |
| MainFull `main___lam__1`（legacy mul） | 884 字节 / 248 个位置 | `[0,0x32) + [0x20a,0x231)`，89 字节 / 26 个位置 |
| MainFull `main___lam__3`（suite mul） | 884 字节 / 248 个位置 | 同上 |
| 独立 `Submission_LowScale_mul` | 843 字节 / 242 个位置 | MainFull mul **没有调用这个符号**，其实现已内联 |

证据：[MainFull lambda3 原始汇编](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/evidence/elf/raw/MainFull/objdump-disassembly.stdout:421)、[Submission mul 原始汇编](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/evidence/elf/raw/Submission/objdump-disassembly.stdout:5581) 和各模块 readelf symbols 原件。MainFull 两份 mul 的完整编码字节 SHA 都为 `37b69abf620162d1decb820b143e5279042ddc6dad13e71bc02771dd2b08a96a`，transfer 目标也一致；它们是两种入口的替代副本，不是一调用执行两次乘法。

普通路径条件是 `ex+ey>=128` 且两 exponent 都不为 255。`+0x1d jb 0x3e` 选择低指数路径；`+0x2c jne 0x20a` 跨过内联 LowScale。`+0x32` 的非有限 trampoline 通过 `+0x39` 尾跳 FastMul。普通路实际执行 50 字节入口和 39 字节硬件块；**89 字节不含被调函数、外层 boxed ABI 或耗时信息**。

MainFull 内联 LowScale 主要占 `[0x3e,0x20a)` 及 `[0x231,0x374)`。它没有被独立隔离；但软件块总长度、源码 C 行数都不等于正常调用的动态成本。缺少链接后地址、分支频率和 instruction-cache 证据，本次不推进 noinline。仅有未来真实布局/缓存证据或另一条独立合理改动产生新对象，才重新打开此项。

## 哪些转换消失，哪些真实留下

[MainFull 普通 mul 块 560—569 行](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/evidence/elf/raw/MainFull/objdump-disassembly.stdout:560) 显示：

| suite/legacy lambda 偏移 | 实际指令/relocation | 判断 |
|---|---|---|
| `+0x20d` | call `lean_float32_of_bits` | 第一次外部位解码保留 |
| `+0x212` | `movss %xmm0,0x4(%rsp)` | 跨下一次解码调用保存结果 |
| `+0x21a` | call `lean_float32_of_bits` | 第二次外部位解码保留 |
| `+0x21f` | `mulss 0x4(%rsp),%xmm0` | Float32 mul 的 inline primitive 已消成机器乘法 |
| `+0x22c` | epilogue 后 tail jump `lean_float32_to_bits` | 外部位编码保留 |

独立 Submission 对应偏移是 `+0x217/+0x21c/+0x224/+0x229/+0x236`。这是此前“只见 C”缺口的实际闭合：高层 ExecFloat nominal/subtype/构造投影包装不再有单独调用，**底层 ofBits/toBits 的外部边界仍在**。普通路没有 `lean_float32_isnan/isfinite` 外调，而用 raw exponent guard；这里没有测转换函数耗时，也没有支持重新尝试旧 numeric-mul/整数 normal-mul 的新收益证据。

补充条件路径：

- [MainFull add 汇编](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/evidence/elf/raw/MainFull/objdump-disassembly.stdout:7) 中 `+0x44/+0xa2` 是条件 of-bits 站点，`+0xe9` 是最终 to-bits；numeric 分支保留 `cvtsi2ss`、scale table 与 `mulss`。不能说所有 add 输入都执行两次外部解码。
- mul 的 `+0x1de` 专门化 MulBackend、`+0x1ee lean_uint32_of_big_nat`、`+0x364 lean_dec_ref_cold` 都不在上述普通有限路径。独立 Submission 使用 generic backend，导致它比 MainFull 多 10 个静态字节；这不是测得的性能差。
- 不能把符号中所有静态调用、所有冷分支或完整 884 字节，都累计成每次乘法成本。

## 本次交付与停点

九项结论的精确证据、77 原件 SHA、五模块 C/object 身份、六条真实 clang 命令、三次动作原始 exit、符号字节重建和普通路径指令列表保存在同名 JSON。W11 实际 C/object facets 成功与两次完整目标超时分列；本次未运行新 Lean、fullgate 或 benchmark。最终鲜核时间：2026-10-23T00:07:21Z。

**noinline LowScale 停放；W11 没有实际时间收益。** 仅当新证据改变上述布局判断，再在精确候选的真实 MainFull 闭包上取对象，并完成原版完整配对计时。此结果只绑定 60f，不外推到 97f、singleton、scanner 或其他新候选。

