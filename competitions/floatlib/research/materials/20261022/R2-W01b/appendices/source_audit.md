# R2-W01b 固定公开源码审查

审查范围只包含本轮指定的三个公开版本、本轮新写的准入/零值草稿和直接推导。不读取旧会话、私有附件或旧实验目录；没有安装 Lean/Lake，没有编译 Lean，也没有运行 C 基准。本报告不重做一般 normal 乘法证明，不改变已给定的 ordered-sum / finite-guard 基线。

## 1. 版本、来源和完整性

| 对象 | 指定版本 / 已解析 commit | commit 中的根 tree SHA-1 |
|---|---|---|
| Lean | `v4.34.0` → `293d5d0c0c3f3dded4688b3ccd6a33939ac5102b` | `934fb4fc8820afd564126241d69633a8c0611704` |
| FloatLib | `0d91825727839f597fd06b22fdd038ea21480f0c` | `e767f2ab2534547c9a043c7b922d8be5775d05fa` |
| 官方 kernels | `978cc5b445edb9943fd9953b0a9037d97a9f33a8` | `d790bec3b28ddf83e341a1c4e427622985a045b6` |

每个仓库保存 `revision.json` 和完整的、`truncated=false` 的递归 `tree.json`。`repository_manifest.json` 记录下载 URL 和元数据文件 SHA-256；`source_manifest.json` 逐文件记录固定 commit 的 raw URL、字节数、SHA-256、Git blob SHA-1 和 blob 校验结果。

另外按 Git tree 对象的编码重新计算全部目录对象：Lean 992 个、FloatLib 582 个、官方仓库 86 个，全部匹配，根 tree 匹配对应 commit 声明的 tree。下载源码的 `SHA1("blob " + length + NUL + bytes)` 也全部匹配清单。结果见 `tree_integrity.json`。API 递归响应的顶层 `sha` 此次返回的是请求 commit；本报告没有把该字段误当成 tree SHA，而是使用 commit 的 `commit.tree.sha` 并重建校验。

源码均来自 `raw.githubusercontent.com/<repo>/<resolved-commit>/<path>`，没有读取移动分支。完整逐文件来源由 `source_manifest.json` 给出。下列网页链接也固定到相同 commit。

## 2. 结论先行

1. 新准入条件的接受集合是 **两个有符号零，以及无符号 magnitude 在 `0x0c000000 .. 0x7f7fffff` 的输入**；后者恰是 exponent `24 .. 254` 的 normal 子集。两个零和该 normal 子集都使两个比较为真，因此不会因零值而走不同的准入逻辑分支。这不是“所有 normal 都准入”。
2. 表的零项必须保留符号：`j=0` 取 `+0`，`j=256` 取 `-0`。这时 `M=0x00800000`，数值转换为正的 `2^23`，乘法的有符号零结果保留表项符号。应检查 `toBits` 或 Lean 的结构相等；IEEE 数值比较本身不能区分正负零。
3. 固定 Lean 运行时的 `Float32.ofBits` **不是对 NaN payload 完全透明的 bitcast**；它会检测 NaN 并替换为 quiet NaN。`toBits` 对任意 NaN 返回固定 `0x7fc00000`。因此 converter 与原 `Float32.ofBits` 的等价，不能替代整个 ordered-sum 算法对原始 FloatLib raw 值的 fallback 论证。
4. `&&`、预先 `let` 绑定后调用 `Bool.and`、以及 nested `if` 都不能仅凭 Lean 写法获得“机器码无分支”的结论。源码明确把 Boolean conjunction 编成可短路匹配，LCNF 的两路 case 可以发出 C `if`。可以成立的是零与准入 normal 走相同的接受结果；实际比较/跳转布局要看生成 C 和汇编。
5. 512 项纯表可以是独立于输入的闭合计算，但 **闭合提取、只初始化一次、C 静态字面量、每次读取无 guard** 是不同性质。固定编译器分别支持 simple-ground 静态对象、模块初始化的零参数全局值、以及带 `once` 读取的 `_closed` 项。不能把 `Array Float32` 当成平铺 `float[512]`。
6. 普通 `bv_decide` 虽未出现在词法禁词中，其常规 LRAT 反射路径会创建额外公理；官方 gate 只允许三项基础公理，因此不能把它当作该 gate 下已认证的纯内核证明路线。本轮草稿已改用 UInt/Nat 引理、`omega` 和闭合 `decide`。

## 3. `Float32` 位语义与零乘法

### 3.1 真实定义和 native 边界

| 功能 | Lean 定义 | native 对应 |
|---|---|---|
| `Float32.ofBits` | `src/Init/Data/Float/Float32.lean:132–133`，使用 `Float32.Model.ofBits` | `src/runtime/object.cpp:1987–1993`：bit-cast 后测试 NaN，再替换为平台 quiet NaN |
| `Float32.toBits` | 同文件 `145–146`，返回 model bits | `object.cpp:1995–2004`：NaN 固定返回 `0x7fc00000`，否则 bit-cast |
| `UInt32.toFloat32` | 同文件 `303–304`，走 `.ofUInt32` | `src/include/lean/lean.h:3265`：C 的无符号整数到 `float` 数值转换 |
| `Float32.mul` | 同文件 `90–91`，model multiplication | `lean.h:3257`：C 的 `a * b` |
| `Float32.add` | 同文件 `76–77` | `lean.h:3255`：C 的 `a + b` |

来源：[Float32 定义](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Float/Float32.lean)、[runtime bit conversion](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/runtime/object.cpp#L1987)、[runtime primitive header](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/include/lean/lean.h#L3253)。

`Float32.Model` 本身含有 NaN canonicality 条件，而不是任意 `UInt32` 的无约束容器（`Model/Float32.lean:19–39`）。它的 `mul` 经 unpack、`UnpackedFloat.mul`、pack（`86–87`）。`Unpacked/Operations/Mul.lean:27–31` 明确区分 infinity×zero 的 NaN 分支、finite×zero 的带符号零分支、zero×zero 的带符号零分支；符号乘法见 `Unpacked/Sign.lean:34–39`。这是零值行为的定义级依据，没有借用未经证实的 `Float32.mul_zero` 名称。

来源：[Float32.Model](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Float/Model/Float32.lean)、[零乘法定义](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Float/Model/Unpacked/Operations/Mul.lean#L21)、[符号乘法](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Float/Model/Unpacked/Sign.lean#L34)。

### 3.2 本轮零值的精确代入

| 输入 `u` | `a=u&0x7fffffff` | `j=u>>>23` | `e=j&255` | `s=(j&256)<<23` | 表项位 | `M` | 期望结果位 |
|---|---:|---:|---:|---:|---:|---:|---:|
| `0x00000000` | 0 | 0 | 0 | `0x00000000` | `0x00000000` | `0x00800000` | `0x00000000` |
| `0x80000000` | 0 | 256 | 0 | `0x80000000` | `0x80000000` | `0x00800000` | `0x80000000` |

这是对用户给定公式的直接代入。两个输入都满足环绕减一的准入条件。`M` 是正整数 `8388608`，其 binary32 位型为 `0x4b000000`；乘正有限数与带符号零的定义分支保留零符号。本轮草稿将这些实例写成闭合 `decide` 命题，再通过 `magnitude_zero_iff` 推广到全部零输入；它仍是 **NOT_RUN 的 Lean 草稿**，不能以源码审查冒充内核通过记录。

表公式中，每个符号有 231 个非零 scale 项（exponent 24..254），以及 25 个带符号零项（0..23 和 255），共 512 项。低指数、无穷和 NaN 对应的零 scale 不代表那些输入被允许走乘法；准入守卫仍负责拒绝它们。

## 4. FloatLib 真实桥接名称及单 import 可达性

### 4.1 已核实的公开 import 链

`ContractTensor.lean:1 → Contract.lean:1 → FloatLib.lean:9 → FloatLib/Floats.lean:12 → FloatLib/Floats/Formats.lean`。

从 `Formats.lean:16` 进入 `IEEE754.lean`，其 `9–13` 公开导入 native codec、整数、表示和相关 bridge 模块。`Formats.lean:9` 进入 `BinaryInterchange.lean`，其 `26–27` 公开导入 arithmetic proof 和 semantics；`Semantics.lean:9` 公开导入 signed-zero packing lemmas。从 `Floats.lean:11 → ExecFloat.lean:13` 可达 configured arithmetic 的通用 refinement 定理。

以上是逐文件公开链的源码核对，用户候选不需要额外写 import。官方唯一 import 行的限制见后文。来源：[ContractTensor](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/contract/ContractTensor.lean)、[FloatLib Formats](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats.lean)、[IEEE754 umbrella](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754.lean)。

### 4.2 确认存在的名字

下表的 `B` 表示完整命名空间 `FloatLib.Floats.ExecFloat.Binary`；`M` 表示 `FloatLib.Floats.Formats.BinaryInterchange.Model`。这些缩写只是报告缩写。

| 真实名称 | 固定文件和行 | 能支持的命题 |
|---|---|---|
| `B.toBits32_ofBits32` | `IEEE754/Native.lean:74–76` | 从原始 word 构造 configured binary32，再读回 word，严格等于输入 |
| `B.ofBits32_toBits32` | 同文件 `79–84` | 原始 word codec 的反向 roundtrip，包括 NaN payload |
| `B.toBits32_ofFloat32` | 同文件 `137–139` | native→configured 的 word 等于 native `toBits` |
| `B.toModel_toFloat32` | 同文件 `142–145` | 转 native 的逻辑模型等于从原 word 构造的 `Float32.Model.ofBits` |
| `B.ofFloat32_toFloat32` | 同文件 `151–158` | configured→native→configured 等于明写的 canonicalize 结果，**不是对任意 raw 值恒等** |
| `B.toFloat32_ofFloat32` | `IEEE754/Native/Representation.lean:49–54` | native→configured→native 恒等 |
| `M.ofFloat32Model_toFloat32Model` | `IEEE754/Native/Model.lean:62–64` | packed-model roundtrip 等于 `canonicalizeModel` |
| `M.toFloat32Model_ofFloat32Model` | 同文件 `79–82` | native model 的反向 roundtrip 恒等 |
| `M.toModel_posZero` / `M.toModel_negZero` | `BinaryInterchange/Model/Packing/Special.lean:522–530` | 正、负零 unpack 到对应符号的 `.zero` |
| `M.toModel_ofModel_zero` | 同文件 `345–348` | 对任意零符号，pack 后 unpack 保持该符号 |
| `M.pack_unpack_of_valid` | `IEEE754/Native/Model/Representation.lean:101–111` | 输入 bits 满足核心 `Format.Valid` 时，pack(unpack(bits)) 严格返回 bits；可供 non-NaN roundtrip 适配，不涉及一般乘法 |
| `FloatLib.Floats.ExecFloat.Proof.mul_eq_spec` | `ExecFloat/Proof/Arithmetic.lean:55–59` | configured executable multiplication 等于其 specification |
| `M.Proof.mul_eq_spec` | `BinaryInterchange/Arithmetic/Proof.lean:44–46` | model executable multiplication 等于 `M.Spec.mul` |

来源：[raw/native codec](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native.lean)、[native representation bridge](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Representation.lean)、[native model bridge](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Model.lean)、[zero packing](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Model/Packing/Special.lean)、[model multiplication refinement](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Arithmetic/Proof.lean#L44)。

没有把未核实的 `mul_zero` 或 `zero_mul` 名称写成可调用 Float32 定理。此版本已审查的 FloatLib 算术路径中，零乘法依据是 `M.Spec.mul` 的明确分支（`Spec/Dyadic.lean:70–80`）：两个可解码有限输入，只要一个 significand 为零，就返回符号异或的 `M.zero`。通用 `mul_eq_spec` 可以把软件乘法转到该定义；这与 Lean 核心 `UnpackedFloat.mul` 的零分支是两个应明确区分的层次。来源：[FloatLib 乘法 specification](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Spec/Dyadic.lean#L67)。

`Configured.NativeFPU.Runtime` 的说明和实现主要是软件 FMA 与原始 word carrier，不能根据目录名把它当作 native 乘法正确性定理。另设的 `Configured.NativeFPU.Unchecked` 不由该 runtime 公开导入，且其名字本身命中官方禁词，不用于候选。来源：[NativeFPU runtime](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Configured/NativeFPU/Runtime.lean#L13)。

### 4.3 草稿使用的 UInt、Nat、Array 和 tactic

默认 `Init → Init.Data → Init.Data.UInt / Nat / Array` 的公开链分别导入 `UInt.Lemmas`、`UInt.Bitwise`、`Nat.Bitwise.Basic/Lemmas`、`Array.Lemmas`。已核实：

- `UInt32.toNat_sub`、`UInt32.toNat_lt_size`、`UInt32.ofNat_toNat`，位于 `UInt/Lemmas.lean` 生成模板的 139、149、194 行。
- `UInt32.lt_iff_toNat_lt` / `le_iff_toNat_le`，同模板 70–72 行。
- `UInt32.toNat_and`、`UInt32.toNat_shiftRight`，`UInt/Bitwise.lean:37–41`。
- `Nat.and_two_pow_sub_one_eq_mod`，`Nat/Bitwise/Lemmas.lean:537`；`Nat.shiftRight_eq_div_pow` 来自公开导入的 Bitwise Basic。
- `Array.size_ofFn`、`Array.getElem_ofFn`，`Array/Lemmas.lean:4254`、`4282–4285`。
- `omega` 的公开 meta 导入可沿 FloatLib 的 `BinaryInterchange.Automation → Numerics.Automation.Numerics:14 → Lean.Elab.Tactic.Omega` 核实。

这些声明的存在与 import 可达性已查源码；具体 `simp only`、`change`、依赖索引化简、心跳消耗以及闭合 float `decide` 是否在允许资源内完成，仍需固定 Lean 的实际 elaboration。

## 5. 两比较、`Bool.and` 与分支

Lean `Init/Prelude.lean:1205–1215` 规定 Boolean conjunction 的编译实现为 `@[macro_inline]`，先匹配第一个 Bool，false 时返回 false，true 时使用第二个值；`4815–4817` 把公开 `Bool.and` 与这个内部实现连接。因此把 `p && q` 拼写成 `Bool.and p q` 不会自动绕过短路实现。来源：[Bool conjunction](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Prelude.lean#L1200)。

| 候选形态 | 源码可确定的性质 | 不能据此宣称 |
|---|---|---|
| `cmp1 && cmp2` | 有短路语义；两个准入零和准入 normal 的 `cmp1`、`cmp2` 均为真 | 只有一个跳转或完全 branchless |
| 先 `let p := cmp1; let q := cmp2` 再 `Bool.and p q` | 源程序显式先绑定比较值；and 本身仍是 Boolean case | 强制生成位运算 AND，或者阻止编译器重排/简化 |
| nested `if` | 两层源级条件，成功分支共享 `tableProduct` | 后端必保留恰好两个条件跳转，或一定比 `&&` 更快 |

`ToLCNF.lean:621–674` 处理 case，`EmitC.lean:870–889` 对合适两路 case 发出 C `if/else`，其他 case 用 switch。后续 LCNF 优化和 C 编译器都可能改变具体形状，单看 Lean AST 不足以给出指令数。来源：[LCNF lowering](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Lean/Compiler/LCNF/ToLCNF.lean#L621)、[C case emission](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Lean/Compiler/LCNF/EmitC.lean#L870)。

本轮能够说“移除了原有 `u == 0` 的专门 converter 分流”，但一次 table 访问仍可能遇到初始化检查、数组 bounds 检查、对象引用计数判断等。它们与数据零值专门分支不是同一问题。

## 6. 512 项 `Array Float32` 的初始化、边界和对象成本

### 6.1 三种生成路径必须区分

`ExtractClosed.lean:117–164` 专门识别 `Array.mkEmpty/emptyWithCapacity + push` 字面量链；`168–179` 在可提取时生成闭合项。纯常量表达式的通用提取判定见 `67–113`。`Array.ofFn` 是一个真实数组构造（`Array/Basic.lean:331–337`），不是每次索引调用表公式；本轮候选将它放入无输入参数的顶层 `scaleTable`。来源：[闭合提取](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Lean/Compiler/LCNF/ExtractClosed.lean)、[Array.ofFn](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Array/Basic.lean#L331)。

固定 `EmitC` 区分：

1. **Simple-ground 静态对象**：`474–475` 走静态发射，读取 `627–628` 直接引用。`SimpleGroundExpr` 接受部分 constructor、字面量和 array-push 模式；其数组表示仍是 `lean_object*` 数组（`SimpleGroundExpr.lean:75–77`）。
2. **普通零参数顶层值**：`EmitC.lean:986–1005` 在模块初始化里调用 `_init` 并标记 persistent；普通引用 `635–636` 直接读全局变量。
3. **非 simple-ground 的 `_closed` 项**：`481–483` 生成静态 `lean_once_cell_t` 和存储；`629–634` 每次引用发出相应 `lean_*_once`。对象表使用 `lean_obj_once`。其热路径仍测试 token 的原子状态，冷路径加锁、执行构造、标记 persistent（`lean.h:3367–3380`；`object.cpp:2896–2904`）。

来源：[发射与初始化](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Lean/Compiler/LCNF/EmitC.lean)、[simple-ground 支持范围](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Lean/Compiler/LCNF/SimpleGroundExpr.lean#L165)、[once 热路径](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/include/lean/lean.h#L3367)。

`Float32.ofBits` 调用及 Float32 装箱不属于该 simple-ground 检测器直接接受的 float literal 模式（`SimpleGroundExpr.lean:192–235,356–364`；没有 float32 scalar case）。因此“512 项完全纯，所以一定发出 C 静态 float 常量表”不成立。普通顶层 `scaleTable` 有一次初始化的源码依据，但具体候选是否留有 `_closed` 引用、一次检查是否位于循环内部、表是否在顶层初始化时已触发，以及 C 优化是否消除部分包装，都须查实际生成产物。

### 6.2 bounds 检查

| Lean 读取方式 | 固定源码行为 |
|---|---|
| `table[i]'h` / 有证明的 `getElem` | `Init/Prelude.lean:3281–3293` 使用 `lean_array_fget`，没有语言级动态 fallback 分支；运行时 core 有 C `assert`，release 是否移除由实际构建参数决定 |
| `table[i]!` | `lean_array_get` 检查 Nat 是否 scalar、索引是否小于 size；失败调用 panic 路径（`lean.h:1017–1029`） |
| `table.getD i fallback` | `Init/Prelude.lean:3307–3308` 明确用 `dite (i < size)`，有 fallback 分支，除非后续优化能消除 |

本轮草稿最终用有证明的 `getElem`，利用 `j.toNat<512` 与 `scaleTable_size`。这优于把“逻辑上已知索引不越界”当成 `!`/`getD` 自动消除检查的证据。来源：[Array get definitions](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Prelude.lean#L3281)、[runtime reads](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/include/lean/lean.h#L998)。

### 6.3 装箱、解箱与内存布局

普通 `Array` 的 slot 是 `lean_object*`。`lean_box_float32` 分配带四字节 scalar payload 的 constructor；`lean_unbox_float32` 从对象中读 float32（`lean.h:3007–3014`）。编译器 `ExplicitBoxing.lean` 的职责正是对 scalar/object 边界插入 box/unbox；`EmitC.lean:46–61` 对 Float32 使用上述操作名。

因此该表通常涉及：一次性对象构造与表构造、索引读对象指针、从对象取四字节 float、以及可能的引用计数/借用处理。不能把表大小断言成仅 2048 字节，也不能断言每次查表都会重新分配；persistent 对象与 borrowed read 可减少这部分热路径成本。究竟哪些增减引用、守卫、包装函数和 pointer loads 留在循环里，要看生成 C/汇编。

来源：[Float32 box/unbox](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/include/lean/lean.h#L3007)、[ExplicitBoxing](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Lean/Compiler/LCNF/ExplicitBoxing.lean)。平铺 C `float[512]` 实验只隔离算术和控制流趋势，不是上述 Lean 表实现的完整性能复刻。

## 7. 官方 policy 的真实词法规则

固定 `gate.py:205–210` 的完整正则为：

```python
r"\b(sorry|admit|native_decide|axiom|implemented_by|extern|export|csimp|init|initialize"
r"|builtin_initialize|run_cmd|run_elab|run_meta|macro|macro_rules|elab|elab_rules|syntax"
r"|attribute|IO|include_str|include_bytes|includeStr|run_tac|declare_simp_like_tactic)\b"
r"|\w*simproc\w*|\bregister_\w+|\w+_elab\b|\w*_syntax_\w*|unsafe|Unchecked|dbg|#[a-z_]+"
```

`policy` 对整个原始文本进行 `BANNED.search`，**注释也会命中**。每一行只要含独立单词 `import`，去除首尾空白后必须完全等于 `import ContractTensor`；带尾注释、`public import`、注释里单独谈 import 都可能被拒。属性白名单仅为 `inline/noinline/always_inline/specialize/simp/reducible/irreducible`。选项只允许三个有上限的心跳/深度选项；`#check`、`#print` 因 `#[a-z_]+` 匹配而禁止。来源：[固定 gate policy](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/gate.py#L191)、[policy 实施](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/gate.py#L501)。

词法检查之外还有实际 proof replay 和公理检查：`gate.py:191` 的公理允许集合是 `propext, Classical.choice, Quot.sound`；`564–573` 拒绝其他公理。固定 Lean 的 `BVDecide/Prover/Bitblast.lean:38–44` 调用 `nativeEqTrue`；`Lean/Meta/Native.lean:75–82` 实际创建 `Declaration.axiomDecl`，不是仅文档声称的风险。若某次 `bv_decide` 只由预处理提前关闭目标，可能不进入此分支；未经编译与公理检查不能依赖这个例外，更不能把“不在正则中”当成可提交证明。来源：[BV 反射调用](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Lean/Meta/Tactic/BVDecide/Prover/Bitblast.lean#L26)、[nativeEqTrue 实现](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Lean/Meta/Native.lean#L31)。

普通 `by decide` 的情况不同：`Init/Tactics.lean:1384–1394` 中 `kernel=false`、`native=false` 是默认配置；`Lean/Elab/Tactic/Decide.lean:81–98` 默认走 `doElab`，构造 `mkDecideProof`、先由 elaborator 归约确认 `isTrue`，返回由内核再次检查的 proof term。只有显式启用 native 配置的路径才调用 `nativeEqTrue`。`omega` 的 frontend `649–675` 返回可证明矛盾的表达式并赋给目标，`694–696` 经 `mkAuxTheorem` 保存证明，不使用该 native 反射创建公理的路径。此源码依据支持本轮选择普通 `decide`/`omega`；具体已完成定理的依赖集合仍需独立审计，不能以 tactic 名称取代 `#print axioms` 和官方 replay 的实际结果。来源：[DecideConfig 默认值](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Tactics.lean#L1384)、[普通 decide 实现](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Lean/Elab/Tactic/Decide.lean#L70)、[omega proof construction](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Lean/Elab/Tactic/Omega/Frontend.lean#L649)。

## 8. 官方 benchmark 输入域：ReLU 的零不是随机散布

`BenchTensor.lean:26–27` 按 `w & 1` 分流：偶数 word 变 `+0`；奇数 word 保留低 23 位 fraction，构造 exponent 124..130、正符号的 normal。`Bench.lean:17–23` 的 LCG 更新是乘 `1664525` 再加 `1013904223`。两常量都是奇数，模 2 下每步翻转低位，所以该 ReLU 流的 `+0/positive-normal` **严格交替**；`sumLen=1000`，每个完整向量恰有 500 个 +0。该结论是两段源码的模 2 推导，不是概率猜测。

来源：[BenchTensor 输入生成](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/bench/BenchTensor.lean#L18)、[LCG](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/bench/Bench.lean#L16)。

因此独立自造 C 实验至少要把 official-shaped alternating ReLU 与随机 25/50/75% 零、成簇 50% 零、有符号零混合区分。它们测试不同的分支可预测性。这里没有读取或报告任何 C 实验结果，也没有将 flat-table C 时间映射成 Lean gate 时间。

## 9. 可确认范围与仍未知范围

| 状态 | 命题 |
|---|---|
| 源码已确认 | 指定版本的 extern 映射、NaN canonicalization、零乘法逻辑分支、真实 codec/refinement 定理名、公开导入链、policy 正则和公理门禁 |
| 直接数学推导 | 准入集合、两个零的表 index/scale/M、LCG ReLU 严格交替 |
| 本轮未编译草稿 | 准入/零值 `omega` 与 `decide` 证明、Array 读取桥接、以既有 normal 等价为参数的 converter/fold 拼接 |
| 必须实际生成代码确认 | 是否留下 zero-sensitive 跳转、比较数量、`once` 检查位置、顶层表初始化路径、对象读取与解箱/借用/引用计数、C assert 是否保留、向量化、具体指令和成本 |
| 本任务没有声称完成 | 一般 normal 乘法证明、完整 ordered-sum 新验收、FloatLib raw fallback 等价、官方 gate/score、新方案 Lean 性能优势 |

关键验收边界：`convert u = Float32.ofBits u` 即使证明完成，也只替换 native converter；它不自动证明原始 FloatLib NaN payload 经 native 转换后不丢失，亦不允许省略既有的整算法 fallback 和 finite 守卫。
