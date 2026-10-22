# 807 标量 add/mul 代码生成复核

2026-10-22 20:37 UTC 开始。范围仅现有源码、C、汇编、历史回执与公开原件；只新增本报告，无候选修改、Git/CI 操作或上传。R7 主窗仍按用户指定的 04:22:17 UTC 截止。

**结论：没有找到已获 807 收益证据支持、且未重复历史路线的高收益标量替换。** 正常 mul 的高层转换包装已消失，但不能说转换成本已全部消失：留下两次外部 `lean_float32_of_bits` 和一次外部 `lean_float32_to_bits`。正常 add 仍有 numeric 转换/查表路径。numeric-mul、删低指数守卫和全整数 normal-mul 都有历史实验，不能只看到源码“转换”二字就重试。仅保留下面两个待证方向，收益均为 **UNKNOWN**，不建议在没有最小判别证据时扩大候选队列。

## 身份与证据范围

回执根目录 `R`：

`competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/39840672791/download-81e3479e9e2b47249bf76c8d44eb2e62/diagnostics/f01-d7-public-suite/`

当前官方诊断构建位于 `R/public-suite/parent-stage-profile/`。`R/candidate-generated-0.c` 是外层旧 pin 的 statement 输出；逐字节复核发现它与当前官方诊断构建的 `profile-current-original.c` 相同。分析以下 C 行号时使用后者，不能由目录层级猜测它属于哪个环境。

| 实际文件/对象 | 字节 | SHA-256 |
|---|---:|---|
| `R/candidate-generated-0.c` | 708275 | `65665cb68141c2603e48f62731058e45414af8faeffce9b1d02040e8a7705677` |
| `R/public-suite/parent-stage-profile/profile-current-original.c` | 708275 | `65665cb68141c2603e48f62731058e45414af8faeffce9b1d02040e8a7705677` |
| `R/public-suite/parent-stage-profile/profile-current-kernel.lean` | 139972 | `8eb63a2fea39f8c483eb16857cb1dcc35ac4a30168ab91046a48aa1cb561e045` |
| `R/public-suite/parent-stage-profile/profile-current-build-commands.json` | — | `c4443d31e88ede4f0d433e28edb53c7a5daa4573248fc7503af89db8d06b6dd3` |
| `R/public-suite/parent-stage-profile/profile-current-build-identities-before.json` | — | `b90d5d9035e3bfecb55f82c4496de09941a2d434b815e44ff96aeaa72ff29a42` |
| 该 JSON 记录的原始诊断 `Submission.c.o.export` | 186416 | `bad8b1473a4255ccf2663b3ebb94b8cb36b1d84aaee2350ae825cb18717d70b9` |
| 该 JSON 记录的原始诊断 `benchFull` | 148041312 | `5529c1ee6623eefd4f33cae2271c29ac6bd6da631bd456adf4b6d848e36bda2d` |
| `R/public-suite/public-drawn-plan.json` | 99920 | `9cc5d7368749c369172b019d66bc4cd8455ae4323d0b9a175bd031f936e78622` |
| `R/public-suite/f01-d5-stream-pack-verdict.json` | 7856 | `368d814eed49afae32d55e5543773c55109388b37fe9c564cc2077acf43b4920` |

对象/二进制 SHA 来自保存的身份回执，其二进制本身未保留在本地目录；不能由这些 SHA 重新生成缺失的标量反汇编。当前官方版本为 `4b7e83841cc0c32c6529f533923c73d33b5ecf97`，Lean 4.34.0，seed 807，pairs 500000，25 轮。这里的 C 属于独立 statement 诊断构建，不冒充清理后的 25 轮 score 对象。

## C 中实际留下了什么

### add

- **VERIFIED**：入口为 `LEAN_EXPORT uint32_t lp_competition_Submission_add(uint32_t, uint32_t)`，完整函数第 **14399—14543** 行。它不符合旧 `profile.function` 的 `lean_object*` 返回类型模式，但确实存在。
- 第 **14404—14414** 行先检查双方 exponent 是否为 255。第 **14440、14447** 行把拒绝路径交给 `TunedAdd_add`。
- 第 **14418—14434** 行以及 **14500—14517** 附近保留 `fastOK` 的幅值区间检查。numeric 分支第 **14469—14482、14524—14537** 行分别构造 24 位整数 mantissa、`UInt32.toFloat32`、读取 `R2W01b_scaleTable`、再乘 scale。
- 第 **14453—14455** 行是最终 Float32 add 与 to-bits 返回。低幅值/不适用 numeric 的分支仍分别使用第 **14462、14519** 行附近的 `lean_float32_of_bits`。
- C 静态站点数为：2 个 numeric cast、2 个 scaleTable 引用、2 个备选 of-bits 站点、1 个最终 add、1 个最终 to-bits；这不是每次调用的动态次数，numeric/备选分支互斥。
- 表读取中的 `lean_object*` 临时量不等于每次分配对象：固定 runtime 中 `lean_array_fget_borrowed`、`lean_unbox_float32` 是 inline 读取；`UInt32.toNat` 在 64 位主机可用立即数表示。这里不能从 C 类型名虚构“每次有两次堆分配”。

### mul

- **VERIFIED**：入口为 `LEAN_EXPORT uint32_t lp_competition_Submission_mul(uint32_t, uint32_t)`，完整函数第 **14609—16011** 行；独立 `nativeMul` 为 **14557—14595** 行。
- 第 **14614—14622** 行提取 ex/ey 并选择 `ex+ey<128`。常规有限高指数分支最终进入 **14665—14672** 行：两个原始 word 经 `lean_float32_of_bits`，一次 `lean_float32_mul`，再 `lean_float32_to_bits` 返回。
- 这个常规分支**没有**保留 Model/codec/Dyadic 对象转换调用，也**没有** numeric mantissa 重建或 scaleTable 读取。高层 `ExecFloat.Binary.toFloat32` 已在 Lean 生成阶段展开为 of-bits primitive；不能再按源层包装数量估算开销。
- 低指数软件路径仍被内联到大函数中。第 **15614—15615** 行先计算 UInt64 mantissa product/scale；zero-product 检查位于第 **15565** 行的 join block，运行流从 product/scale 等准备跳到该 block，不能按文本行号误判 zero 检查发生在乘积准备之前。
- 第 **14635、16001** 行的非有限路径调用 `FastMul_mul`；后者 **9133—9152** 行重新做 special 位检查，**10361—10365** 行最终调用 FloatLib `MulBackend_word`。低指数路径还保留 **14647—14662** 行的 special 检查，以及 **15980—15985** 行的原后端出口。

### C 内联与机器码内联必须分开

读取了精确 [Lean v4.34.0 runtime header](https://github.com/leanprover/lean4/blob/v4.34.0/src/include/lean/lean.h#L3253)；Git blob 为 `910ecae72a7d1c149d4ccc8111ee438c8b4551dd`（这是 Git SHA-1，不是文件 SHA-256）。of-bits/to-bits 在头文件中只有外部导出声明，Float32 add/mul 和 UInt32→Float32 则是 static inline。保存的编译命令使用 `clang -c ... -O3`，没有 LTO。

因此：**VERIFIED** 是常规 mul 的 3 个 codec C 调用站点和 inline primitive 的区别；**INFERRED** 是这些外部 codec 调用在该非 LTO 构建中仍构成跨函数边界；其实际指令、调用周期、寄存器移动与最终布局为 **UNKNOWN**。不能因为运算语义是 bit reinterpret 就写成“零成本 mov，compiler 已全部消除”。

实际保存的 5 份 `native-loop-*.asm.txt` 仅覆盖 NativeDecodeSumWord/NativeDecodeSum 和 Packed10Index 循环，均无 `<lp_competition_Submission_add>` 或 `<lp_competition_Submission_mul>` 标量反汇编。其 SHA 已逐一复核：

| 文件 | SHA-256 |
|---|---|
| `native-loop-0.asm.txt` | `74f70d3be0ba40dd15c9820e6b215a8a1a74635ff15abf9b2a5a4a32f0a63034` |
| `native-loop-1.asm.txt` | `16cacf7540b1d9af1405166bd8588f4ac700678e89ccc2c6b9a34e8f146d8dc1` |
| `native-loop-2.asm.txt` | `3394cb731c15073e0d23a16c903da5e1d36c9de7c5c5690cae3b323e2691c1f1` |
| `native-loop-3.asm.txt` | `787153e1fea19d7c9b95209e793ab58aab3fbec75e5dc66fb03bbe8b3c375e01` |
| `native-loop-4.asm.txt` | `44692c6c2995c5309503e013f20449eb63c7260450efd897c57df9fd89b5225e` |

## fallback 及历史路线去重

**VERIFIED**：在 Submission C 边界，finite/special 位分类有重复，随后把原始两 word 转成 Nat 传给 FloatLib 后端。后端自己的生成 C 不在该产物中，所以仅靠这份 C 不能测出其内部 toDyadic 次数或分摊成本。D 的 `f01-d7-special-model-proof1`（`40a281d9…`）正把现有拒绝 finite 的分支改为先做 Spec special dispatch；这是同一未闭合缺口，本报告不另造重复候选。

| 已有路线 | 已查证据及决定 |
|---|---|
| 全面 numeric scalar decode | R4 `f01-d4-scalar-decode`，SHA `a7dca716f0076511875209b043f761559235a74b5729227916360e4d9373e7e9`；run 39746211363、Intel 8370C、seed 504。mul raw ratio **1.0376698243**，reference-normalized **1.0374780640**；add raw **0.8787207098**。解释了为何保留 numeric add 而没有统一替换 mul。无新条件不重试。 |
| add numeric 的重复 finite/range 检查 | 已有 `f01-d6-finite-decode-proof1`，SHA `e46dd156…`，以及 `f01-r6-normal-add-proof1`。前者的 manifest 仍是 proof-repair/NOT_RUN，不能当作已验证性能；后者 seed 706 完整通过，但 raw add ratio 约 **0.9953**、reference-normalized 约 **0.9704**，整包 raw **1.0127**。新 suite 重测可以是旧路线重访，不能列为新机制。 |
| 低指数 mul 删 special/product-width 守卫 | 已有 `f01-r6-web-lowguards`，SHA `75ddbcff…`，run 39791810276 完整通过；mul raw **1.0438451**、reference-normalized **0.9984433**，整包 raw **1.0388691**。不能把“C 有冗余检查”直接升级为稳定收益。 |
| 常规 mul 换整数 rounder | `f01-r6-normal-mul-proof1`，SHA `96865cba…`，run 39793280952 完整通过；mul raw **1.2590481**、reference-normalized **1.2390494**。仅凭去掉转换不足以支持再做整段整数乘法。 |

R4 比较原件为 `f01-d4-global8/window2h-20261022/same-batch-comparisons.json`，SHA `436ad4132bb6470a3491440c1526063316c1df63c0d97567c5be64616f903058`。R6 汇总原件 `f01-d6-research/summary.json`，本次 SHA `38a03e10be67556fe4bc09a5987ac6cf1e7bf43aec2087d581e99e925591e264`；这是可追加的索引，长期追溯以其链接的精确 verdict 为准。

## 只保留两个条件明确的待证方向

807 原版 25 轮 verdict 按每 cell 的工作量还原后，总候选时间 **367334242 ns**；add **21.1926%**、mul **21.6044%**、sum **12.0582%**、BMM **45.1448%**。这不是函数内阶段份额。add/mul specials 两 cell 分别占整包 **5.2732% / 3.8897%**，不表示其中时间全部可由 Dspecial 消除。

1. **仅在既有低指数分支内提前返回 finite signed zero。收益 UNKNOWN，暂存为低成本小探针。**
   - 机制：保持 `ex+ey<128` 外层选择及高指数 native 路径不变；仅该分支内若任一 magnitude=0，直接按双方 sign xor 构造 signed zero。此 guard 已排除 exponent 255，因此无需在新分支重做 NaN/Inf dispatch。未命中时完整保留现有 LowScale。
   - 相对历史差异：不替换转换、rounder 或删守卫，而是在 mantissa/scale/乘积准备之前处理已有精确零恒等式。已查 manifest、R4/R6 记录未见这一条 runtime identity 路径；未索引的更早尝试仍为 UNKNOWN。
   - 最小证明：在该低指数域内，从 `LowScale.mul_eq`/`FastMul.core` 的 zero-product 返回化简到同一 sign packing；先覆盖双方 ±0 与另一 finite normal/subnormal，不能扩展到 0×Inf 或 NaN。
   - 最小判别：生成 C 中 zero 返回必须位于 UInt64 mantissa-product/scale 准备之前；完整测量必须保留未命中的低指数非零输入成本。807 `mul:sparse` 仅占整包 **3.1518%**，其计划 zeroPct 为 8—80；这是组暴露及生成参数，**不是实际 low-branch 命中率或收益**。单凭这一 cell 不支持“高收益”承诺，tensor fallback 中额外暴露也未测。
   - **Parking 条件**：无法证实有足够 low-branch 零调用，或新 guard 已被原机器码等价消除，就不投入完整证明/大批 CI。若走到计时而无净改善，保留负面结果，不改为对全部正常乘法加零 guard 的无差别重试。

2. **把 LowScale 软件慢路径作为单独不内联 helper，检验热入口代码体积。收益 UNKNOWN，先取机器码再决定。**
   - 机制：只对现有低指数软件实现做允许属性/调用边界隔离，保留所有运算、域、回退和证明。和 numeric-mul/整数正常乘法不同：目标是避免软件冷块挤入正常入口，不是重新实现算术。
   - 证据上限：`mul` 有 1403 行 C，而独立 `nativeMul` 只有 39 行；但正常硬件返回已放在大函数前部。**C 行数不等于热点大小，不能据此断言 I-cache 或分支预测有问题。** 已查 manifest 中未见针对 LowScale 的选择性 noinline 实验，历史 blanket inline 工作也不证明本方向有效。
   - **Parking 条件/最小判别**：先对同一对象保留 `Submission_mul`、`nativeMul`、低指数 helper 的反汇编、relocation 和符号大小，确认快路径布局与实际调用边界。如果编译器已隔离冷块或热入口很短，直接停；若存在明确布局负担，再做一个保持源码语义不变的属性变体并完整配对，不从一份 C 的大小跳到性能结论。

本任务没有新计时、候选或上传。高收益方向仍未证实；Dspecial 是已有独立工作，其他路线保持上述 parking 条件。
