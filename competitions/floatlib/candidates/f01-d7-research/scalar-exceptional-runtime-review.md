# Scalar exceptional-word 实际冷路独立审查

开始 2026-10-23 00:24:36 UTC，最多 40 分钟；主窗截止仍为 04:22:17 UTC。只写本报告和同名 JSON。未执行 builder，未修改候选或 R，未运行 Git、CI、上传或本地 Lean。 最终核对：2026-10-23T00:40:33Z。

**未发现可确定的静态整合错误。** 精确 939 的两个冷调用均传递各自真实的 false finite-guard 前提；数学运行体保留已有 17331 的 NaN 优先级及 Inf/±0/invalid 规则。独立整文件逆变换、作用域/声明顺序、原版静态 policy 和 30 对小 word 模型相符。**旧全局 17331 数学探针与新 nested 939 分别为 NOT_RUN；新完整 Lean、kernel/axiom/fullgate、C/asm 和实际收益均未验证。**

## 精确身份与改动边界

| 对象 | 字节 | SHA-256 |
|---|---:|---|
| [新运行候选](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-scalar-exceptional-word/Kernel.lean) | 175363 | `939dbf31705408ac5177e4ede746b7cd52c72e9b7ab7b75eb2a1fd2178635237` |
| [父4a30](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-scalar-nan-select/Kernel.lean) | 163399 | `4a30c99f8230aae6d1b0cd238d1a6b1c9ac0aac0c448ca67d3005d3a6d00d528` |
| [原全局数学探针](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-exceptional-word-probe/Kernel.lean) | 175262 | `17331a8b2ff3ddcced087d4165eaf5887620caf0e0051da70eb01800383cc04c` |
| [数学原块](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/exceptional-word-block.lean) | 12596 | `b884fff04a3353c02d37a824e57aa43ea3b79834569b47601b225441023c79f1` |

新 nested 完整块 SHA 为 `9134fffd86d5653bbbf27d6c13d47febf4ce76c6e787f9748cc15c1b0a544f67`。与数学原块相比，只改“global→nested”的说明和一处会命中 policy 的注释词；全部声明、证明及运行体原样保留。它替代原 ScalarNaN helper，没有新增第二条语义或参数变体。

本次独立完成三个字节核对：

1. 将 939 的两处冷调用、两处证明叶和 nested block 逆回旧 helper，得到完整精确 4a30。
2. 从 4a30 正向替换相同四处与块，得到完整精确 939。
3. 另从精确 60f 重新提取三个旧闭证明块、原 NaN 块及父 builder 的 helper 字面量，重建完整 4a30；没有执行任何写文件 builder。

因此 finite/numeric 分支、LowScale、全部 tensor 地址/布局/顺序及其余非搬移文本保持。source 保持不等于机器布局或时间保持。939 **仍是 4a30/60f 的 tensor 源码**，不是已经组合 97f quiet-stop 和 3d9 单遍 sum 的候选。

固定官方 `4b7e838...` 原始 `policy/options` 函数经 AST 原样加载，以真实 full-slot `ContractTensor` 约束检查，结果 PASS；原始 gate SHA 为 `1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194`。175363 字节低于 256000 上限。这里只是本地静态 policy，不能替代 statement/fullgate。25 个引用原件的精确摘要保存在同名 JSON。

## 两个真实 cold guard

| 位置 | 实际调用/证明 | 核对 |
|---|---|---|
| [Kernel:2992](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-scalar-exceptional-word/Kernel.lean:2992)—3011 | add 的 false 分支调用 `DExceptionalWord.addCold x y`；证明用 `addCold_spec x y hf` | true 分支两个原指数条件、R2W01b decoder/native add 及证明未动 |
| [Kernel:3015](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-scalar-exceptional-word/Kernel.lean:3015)—3032 | nativeMul 的 false 分支调用 `mulCold x y`；证明用 `mulCold_spec x y hf` | true 分支原生乘法及证明未动 |

两个 helper 规格在 [Kernel:2963](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-scalar-exceptional-word/Kernel.lean:2963) 和 [Kernel:2976](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-scalar-exceptional-word/Kernel.lean:2976) 的前提都精确为：

```lean
¬ (Model.NativeBinary32.expField x.raw.1 ≠ 0xff ∧
   Model.NativeBinary32.expField y.raw.1 ≠ 0xff)
```

这与各自 `if hf : ...` 的否定分支同型，不需要把不相关条件强转，也没有换序或改用别处 hf。`special_of_rejected` 从它推出至少一侧指数 255，才调用特殊域 Model.Spec 桥。实际 `split/rename_i` 和定义等价匹配仍须 Lean 对精确 939 接受。

[Kernel:3034](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-scalar-exceptional-word/Kernel.lean:3034) 的外层 mul 仍先判 `ex+ey<128` 再走原 LowScale。原指数提取是 8 位 mask，两字段和至多 510；含 NaN/Inf 的指数至少 255，无法误进低指数分支。helper **没有普通有限输入运行调用点**。

冷 helper 本身没有有限算术：例如 `addWord(0x3f800000,0x3f800000)` 返回 `0x7fc00000`，正确结果为 `0x40000000`；mulWord 同对输入也会返回 canonical NaN，而正确结果是 `0x3f800000`。这些是明确域外反例，不能去掉上述 guard 或把冷域 theorem 当全输入 theorem。

## 作用域、原证明搬移与依赖

| 完整 namespace | 939 行号 | 与 60f 原块关系 |
|---|---|---|
| `R2W01c.NativeBridge` | 474—645 | 较早 R2 前缀逐字节保持，没有被搬移 |
| `Submission.NativeBridge` | 2044—2234 | 10136 字节，SHA `03b626fb…`，与 60f/4a30 相同 |
| `Submission.NotNaNProbe` | 2236—2291 | 2494 字节，SHA `6440cc47…`，与 60f/4a30 相同 |
| `Submission.R7Native` | 2293—2516 | 11022 字节，SHA `1f60d2ba…`，与 60f/4a30 相同 |
| `Submission.DWordNaN` | 2520—2692 | 原 nan-choice-block 字节出现一次 |
| `Submission.DExceptionalWord` | 2710—2989 | 新 nested 上下文，尚未编译 |

所有 namespace/end 经保留行号的嵌套注释剥离后成对。新块内部 `DWordNaN` 指向已有 `Submission.DWordNaN`；`Submission.FastMul.ofBits`、`Submission.NativeBridge.toModelExecMul`、`Submission.R7Native.toModelExecAdd` 都已在使用前定义。新增 `open` 留在新 namespace 内，没有泄漏到后续 exported 定义。

两条 toModelExec 引理的真实结论分别是 Model.Spec.mul/add，恰与新 word-model 结论对接。[Kernel:2943](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-scalar-exceptional-word/Kernel.lean:2943) 的 carrier_model 直接比较原 UInt32 对应 BitVec，不经 Float32 canonicalization；因此没有把 NaN sign/payload 的保真任务变成同态逆推。ofBits_model → cold runtime → cold spec 的声明顺序闭合。

这里保留原三块数学的字节身份，**不从文本搬移推定新上下文已 elaboration**。没有重新否定其旧数学结论。

## 数学特殊域与定向边界

已对照固定 FloatLib `0d918257...` 的 [Model.Spec.add/mul](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Spec/Dyadic.lean) 和 [Model.Carrier 的 IEEE NaN 策略](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Model/Carrier.lean)，并鲜核引用的本地原件和已保存公开片段 SHA。

| 规则 | 新 source |
|---|---|
| signaling 先于 quiet，同级左优先 | [Kernel:2805](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-scalar-exceptional-word/Kernel.lean:2805) / 2812：sNaN a → sNaN b → NaN a → NaN b |
| quieting 保留完整 word | 只 OR `0x00400000`；不清 sign/payload，不统一 canonical |
| Inf 加法 | [Kernel:2784](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-scalar-exceptional-word/Kernel.lean:2784)：同号双 Inf 保留 a，异号 canonical invalid；单 Inf 保留该侧 |
| Inf 乘法 | [Kernel:2792](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-scalar-exceptional-word/Kernel.lean:2792)：任一侧 ±0 与 Inf invalid；否则按双方 sign 不等构造 ±Inf |
| binary32 invalid/overflow | 原局部常量证明对应 canonical `0x7fc00000` 和 IEEE signed Inf |

[固定 Agreement](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Agreement.lean) 的公开字段比较/符号引理接受实际 Value，适配 `ofUInt32 u` 后用 `toUInt32_ofUInt32` 化简。没有调用其 private 的 posInf/negInf/canonicalNaN/signedInf 常量引理；新常量证明使用局部 decide 和公开 nativeOverflow 引理。这确认源码签名路线，不认证精确 ContractTensor 环境中的全部导入可见性或 proof elaboration。

只复跑原有 **30 对固定 word / 60 项运算检查**，完整重现旧 trace `cf5be09579eb5a1419e2d96ed2c7f28e242ed96f97ffa54926444cf0e41a04d4`；同时保留原四个域外例、七条错误规则反例。新块运行声明与原块相同，检查覆盖双 sNaN/双 qNaN 左优先、右 sNaN 覆盖左 qNaN、±payload、Inf 同/异号、Inf×双方 ±0、Inf×有符号非零等。未重跑 110 秒的 807 大域，也没有执行新 Lean 候选。

## 源级 Option 边界

11 个新 runtime 定义没有 Option、rawChoose、generic dyadic 或 Model.Spec 调用。两条源码链为：

- add false guard → addCold → addWord → rawSNaN/rawNaN 或 addNoNaN → 原 FastMul.ofBits；
- nativeMul false guard → mulCold → mulWord → rawSNaN/rawNaN 或 mulNoNaN → 原 FastMul.ofBits。

旧 `DWordNaN.rawChoose : Option UInt32` 仍在 [Kernel:2586](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-scalar-exceptional-word/Kernel.lean:2586)，新 equality/model 证明也会引用它；这不构成两个冷运行入口到它的源码调用边。反过来，**源级无 Option 不证明新 C 已消除分配，更不证明整个 benchmark 无 heap allocation**。新 939 的实际 C、MainFull callback clone、优化对象和分配站点仍为 UNKNOWN，不能用旧 60f W11 对象代替。

## 机会与下一次证伪点

以下只是 [已完成的 807 组件前沿模型](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/frontier-scalar-counts-807.json) 的计分域优先级背景，**不是 939 已组合后的实际调用或时间**：

| 来源 | 冷调用 | NaN 选择 | 无 NaN 特殊 |
|---|---:|---:|---:|
| 独立 scalar add | 6689 | 3412 | 3277 |
| 独立 scalar mul | 4004 | 1962 | 2042 |
| 97f BMM add | 4772 | 2227 | 2545 |
| 97f BMM mul | 2734 | 2132 | 602 |
| 3d9 单遍 sum 修复 | 320 | 320 | 0 |

此候选接入的是已有 exceptional 语义，覆盖 NaN-only 仍保留的 Inf/invalid；不能只拿 sum 的 320 次 repair 作收益故事，也不能继续使用旧完整 tensor 回放次数或整 cell 曝光。native result guard、canonical BMM scan 和本冷 helper 有重叠，收益仍 UNKNOWN。

下一次应先在精确 939 全文件观察 rawInf_eq/rawZero_eq/rawSign_eq、闭常量证明、word choice/model、carrier_model/ofBits_model、两 cold_spec 及 add/nativeMul 的 hf 叶。然后完成 kernel/axiom/fullgate 与具体 raw-word 对照。实际代码生成需查看 MainFull 真正被 bench 闭包调用的冷链及内联点，再做完整配对计时；不能依据独立符号消失或源码 Option 缺席宣称收益。

