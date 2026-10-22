# Scalar NaN select 独立静态审查

审查开始：2026-10-22T22:02:17Z；25 分钟预算上限：22:27:17Z。只读候选、构建脚本及固定源码，只写本报告和同名 JSON；没有执行 builder、修改候选、Git/CI、安装工具链或上传源码。

**结论：没有发现可确定的静态错误。** 四项检查的源码边界与接口一致；新整合的 **Lean 编译、候选执行、完整 gate 和性能仍为 NOT_RUN / UNKNOWN**。DWordNaN block 本身也尚未在本轮编译，不能由本报告将它升级为已验数学；三个原已验闭证明块的历史结论不受此静态审查否定。

## 精确对象与改动范围

- 候选：`f01-d7-scalar-nan-select/Kernel.lean`，**163399 字节**，SHA-256 **`4a30c99f8230aae6d1b0cd238d1a6b1c9ac0aac0c448ca67d3005d3a6d00d528`**。
- 父本：`f01-d7-direct-nonnan/Kernel.lean`，SHA-256 `60f74aa4af01a9b35ece66a7c310e6b05b5b84b9b7121a4cccd12a0a9c987e15`；807/809 gate 是协调者给定背景，本次没有重跑。
- Builder：`build-scalar-nan-select.py`，SHA-256 `71257fd35cd1fd403f806af37fdb221d1072dbaac50cb1372e6fdd5c036e916c`。

本次从原父本读取字节，独立提取三个证明块及 builder 中 helper 字面量，重新组合后与当前候选全部字节一致；再去掉插入块、还原两处 cold call 和两处 proof call，与只移除三个原证明块的父本文本完全一致。未执行 builder 的文件写入部分。

因此，除三块证明移动、新 NaN/ScalarNaN 声明，以及两处冷调用和对应证明替换外，没有源码变化。候选只有原 `import ContractTensor`，第一处 `namespace Submission` 之前的 R2 前缀完整保留；新增内容没有 `sorry/axiom/unsafe/native_decide/extern/implemented_by`。

## 四项核对

以下行号均为新候选 `Kernel.lean`。

| 检查 | 结论与精确位置 |
|---|---|
| 普通 add | **源码保持**：2723–2726 行的两个原指数条件、数值 decoder、native add 均不变；仅 2727 行原 `TunedAdd.add` 冷调用替换为 `ScalarNaN.add`。2733–2740 行有限分支证明不变。 |
| 普通 mul 与低指数 | **源码保持**：2745–2748 行的有限条件/native mul 不变；仅 2749 行冷调用替换。2763–2773 行仍先检查指数和 `<128` 并调用原 `LowScale.mul`，否则进入 nativeMul，证明也不变。指数字段各不超过 255，所以任一 NaN/Inf 输入不可能误进 `<128` 分支。 |
| Tensor 次序/布局 | **全部非搬移文本保持**：sum、dot、BMM 的读取、布局、循环、逐步运算顺序及所有调用实参，均由全源码重构/反向比较覆盖。没有将标量 NaN 选择当作 tensor 后缀吸收或重关联。 |
| 非 NaN 的 Inf/invalid 冷路 | **仍调用原函数**：2699 行为 `TunedAdd.add x y`，2711 行为 `FastMul.mul x y`。纯 Inf、Inf 异号相加、Inf×±0 都没有 NaN 输入，rawChoose 为 none，进入原 fallback。这里增加的分类开销尚未测量。 |

### 证明块与命名空间

| 块 | 新位置 | 字节身份 |
|---|---|---|
| `Submission.NativeBridge` | 2044–2234 | `03b626fbaf4e5ac0cc3c9bd6a0009eeaa00eb4d508b0f9b64d867fee2682d3fc`，与父本相同 |
| `Submission.NotNaNProbe` | 2236–2291 | `6440cc47ffac4bbfc9c5a42f48d3a4ef7b455d2f7f6792a341b2d0e2630061a1`，与父本相同 |
| `Submission.R7Native` | 2293–2516 | `1f60d2bac8219bc597768fc77bd54a71ddf5a4c1bcadacb61ef56fa39856bf2b`，与父本相同 |
| 原 `nan-choice-block.lean` 完整块 | namespace 位于 2520–2692 | 完整源块 `584ace5443838454b3687f7a93cfca07be4f9cce2c889c7196b171b7cfd4c93c` 原字节出现一次；现在嵌入 `Submission.DWordNaN` |
| 新 ScalarNaN helper | 2694–2720 | 原字面量完整出现，先于导出的 scalar 定义 |

较早同名块仍是 **`R2W01c.NativeBridge`**（474–645 行），没有被移动。所有显式 namespace/end 成对。FastMul.ofBits 和所需库声明在这些块之前；NativeBridge → NotNaNProbe → R7Native → DWordNaN → ScalarNaN 的候选内依赖顺序闭合，没有发现前向引用。

原 NaN block 的 `Submission.FastMul.ofBits`、`Submission.R7Native.toModelExecAdd`、`Submission.NativeBridge.toModelExecMul` 仍指向同一外层声明；内部 helper 名现在自然位于 `Submission.DWordNaN`。`open` 没有搬到命名空间之外。这里只确认名称与依赖布局，没有重判原有已验三块数学。旧 block 的 Bool/UInt32/BitVec 和 configured carrier `change` 仍须新位置的实际 elaboration，详见 [先前审查](nan-probe-review.md)。

### 两个 match 证明

- 2696–2706 行：some 分支目标是 `FastMul.ofBits w = ExecFloat.Spec.add x y`，与 2674–2681 行 selected_add 的结论相同；需要的前提恰为 `rawChoose x.raw.1 y.raw.1 = some w`。none 分支的原 TunedAdd 规范适用于所有输入，不需要额外使用 none 方程。
- 2708–2718 行：mul 的目标及前提与 2683–2690 行 selected_mul 对应，none 分支直接使用原 FastMul 全输入规范。

本次核读固定 [Lean 4.34 Split.lean](https://github.com/leanprover/lean4/blob/v4.34.0/src/Lean/Meta/Tactic/Split.lean)（Git blob `926a29ced11c22889cd09f9306b3e4f9a7fe054d`）：match 判别式一般化建立原判别式到构造子的等式，源码中的方向支持这里的 hw；没有依据预先加 `.symm`。但 `split` 后 `rename_i w hw` 的具体 binder 与 some-first 分支仍须在实际编译确认，不以元程序源码阅读代替编译。

## 紧凑的有限反例域

建议固定以下 **10 个 word、16 个定向用例**。这不是全输入证明，也不声称集合具有形式上的绝对最小性；它避免无判别的笛卡尔积枚举。

| 标签 | word | 标签 | word |
|---|---|---|---|
| Z+ | `00000000` | Z− | `80000000` |
| F1（1.0） | `3f800000` | F2（2.0） | `40000000` |
| I+ | `7f800000` | I− | `ff800000` |
| S+（payload 1） | `7f800001` | S−（payload 2） | `ff800002` |
| Q+（payload 3） | `7fc00003` | Q−（payload 4） | `ffc00004` |

| ID | a, b | rawChoose 应得 | 判别目标 |
|---|---|---|---|
| P1 | S+, S− | `7fc00001` | signaling 同级左优先及 quieting |
| P2 | S−, S+ | `ffc00002` | 反号左优先与负号保留 |
| P3 | Q+, Q− | `7fc00003` | quiet 同级左优先及 payload |
| P4 | Q−, Q+ | `ffc00004` | quiet 负号保留 |
| P5 | Q+, S− | `ffc00002` | 右 signaling 胜左 quiet |
| P6 | Q−, S+ | `7fc00001` | 上项换号，不能只取左符号 |
| P7 | S+, Q− | `7fc00001` | 左 signaling 胜右 quiet |
| P8 | S−, Q+ | `ffc00002` | 上项反号 |
| N1 | F1, Q− | `ffc00004` | 只在右侧出现 NaN |
| N2 | Q+, F2 | `7fc00003` | 只在左侧出现 NaN |
| I1 | I+, I− | none | add invalid 回原 fallback |
| I2 | I−, I+ | none | 上项反号顺序 |
| I3 | I+, Z+ | none | mul Inf×+0 invalid 回原 fallback |
| I4 | Z−, I− | none | mul −0×−Inf invalid 回原 fallback |
| C1 | Z+, F2 | none | 导出 add 直接走原有限路径；mul 指数和 128 走 native |
| C2 | Z−, F1 | none | 导出 add 走原有限路径；mul 指数和 127 走 LowScale |

本次仅执行这 16 个 word 模型用例：源码逻辑的独立转录与另一种 IEEE 分类表达（去符号后 word 大于 Inf，再按 signaling/左右排序）及表中预期全部一致。用例集还能区分 8 种故意错误模型：先左 NaN、同级右优先、统一 canonical NaN、清符号、丢 payload、不 quiet signaling、忽略右 NaN、把 Inf 当 NaN。各故障被哪些 case 捕捉见 JSON。

**以上没有执行新 Lean 候选。** 首次实际 runner 测试应让这 16 对原始 word 分别通过新 add/mul 和原 Spec，对照原始结果 word；none 用例核对真实原 fallback 输出。不能用 Python 模型相符替代该步骤。

## 首次实际编译与代码生成的检查项

1. 对精确 **4a30c99f…** 编译整包，首先观察 2520–2692 行旧 NaN block 的新上下文，2703–2705/2715–2717 行新 match 证明，以及两个导出冷调用的原规格。
2. **Option 消除仍为 UNKNOWN。** `rawChoose : Option UInt32` 与 helper 虽有 `@[inline]`，并不保证完整编译链消除 some/none 物化。获取同一整包的实际 C 和最终优化汇编，核对 ScalarNaN.add/mul、rawChoose 对应的真实调用处；函数被内联时检查调用者，不能因独立符号消失就判定生成失败或优化成功。
3. 核对选中 NaN 路径是否还存在构造子分配、装箱/拆箱；普通有限分支是否绕过 rawChoose；无输入 NaN 的 exceptional 路径是否到达原 fallback。保留精确工具链、编译器选项和源码身份。孤立小探针的汇编不能当作完整候选证据。
4. 根据真实完整成本与 gate 反馈决定是否继续；当前不扩无 Option 变体。源码普通分支不变不等于机器布局、内联或计时必然不变。

已读取并一致性核对 `scalar-nan-fallback-807.json`（SHA-256 `dc0b3af910cfdd67cfb47415ca7a912b836512df3bb06a183f1da49467a09f0f`）：70 tensor case 中 280 个报告的 actual-checksum 匹配标记全真，并从逐 case 重算 timed 汇总一致。sum 的选 NaN 加法为 **11393**，BMM 加法 **13659**、乘法 **2940**；无 NaN exceptional miss 分别为 sum add 119、BMM add 2545/mul 1173。

这些统计来自父本 60f 到达 NaN 终点后的完整原始回放；其涉及整 cell 耗时 **26.3686% 只是曝光上限**，包含初次 native pass、分配准备及其他回放成本，不能当收益或每次操作周期数。它与 R 的 quiet-suffix/prefix 路线重叠，不能相加。本次只核对统计文件内部与锚点标记，不宣称独立重跑实际 Lean 输出或新候选。新候选收益仍为 **UNKNOWN**。
