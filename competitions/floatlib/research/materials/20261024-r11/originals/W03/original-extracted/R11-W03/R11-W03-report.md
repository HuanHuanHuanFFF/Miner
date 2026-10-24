# R11-W03 — Lean 4.34 四行 p2、n1/n2 BMM：去掉 P12 准备数组的可实现路线

日期：2026-10-24（Asia/Shanghai）  
任务边界：固定附件源码 + 固定 Lean/FloatLib 与 LLVM 一手源码；隔离研究，不修改 gate、确认输入或原文件。

## 1. 结论与建议

**可以在 Lean 源码层消除所选四行 n1/n2 分支中的 `Vector P12` 和 P12 构造，并保留八条原顺序 Float32 乘加链。当前最值得做的最小目标试验是：只对四行实际 B 起点相同的组，先解码全部一至两轮输入，再显式展开算术。**

这是一项“减少准备对象及其生命周期”的候选。它不能仅凭源码宣布八个累加器始终在寄存器、机器算术区间没有转换调用、或完整 BMM 更快。固定工具链没有在本环境执行；具体机器结果仍待本地 actor 验证。

交付的是**一个推荐的有界展开机制，两个独立的 lowering 实现**：

- **A：`short-shared`，优先试验。** 内联标量读取/算术，不经过临时包数组。源码中 n2 的全部 12 个输入解码先于八个部分和。
- **B：`short-scalar-call`，用于区分函数边界/参数传递成本。** 解码器调用只接收 Float32 参数的算术函数；n1 为 7 个参数，n2 为 13 个，包含起始 +0。它和 A 使用同一数学候选，不能算两项独立算法突破。

**一个决定性的负边界：Lean `@[noinline]` 不保证 Clang 不内联。** 固定版本 `LCNF/EmitC.emitDecl` 发出普通 `LEAN_EXPORT` 声明，没有把该属性发成 C `noinline`。B 的函数边界可在 Lean 阶段保留，却仍可能被 Clang22.1.4 `-O3` 消去。因此 B 是可执行的代码生成试验，不是可靠的机器调度屏障。[S4]

当前 `wordLoop` 本来就有八个标量累加器参数；本轮没有发现“原来八个累加器都是盒装”的问题。也没有证据允许删掉最终 NaN 检查/原始字重放。[K][S1–S4]

### 验证状态

| 项目 | 本轮状态 | 能支持的结论 |
|---|---|---|
| 附件还原、精确 SHA/字节数 | PASS | 确实基于指定源码 |
| 两个补丁零 fuzz 应用并与完整文件比对 | PASS | 补丁可机械复现；不是 Lean 类型检查 |
| 未改变区间、大小、新增文本禁用项检查 | PASS（静态） | 原 wordLoop/finish8/输出/spec 区间保留，无新增绕过项 |
| 固定 Lean/LLVM/FloatLib 源码调查 | SOURCE_INSPECTION | 布局、转换实现、C 发射和 ABI 的证据 |
| 有限有理数反例程序 | PASS，4 项 | 反驳删 +0、FMA、一次最终舍入；不是候选验证 |
| 固定 Lean elaboration / 四 spec / 公理审计 | **NOT_RUN** | 没有接受结论 |
| 候选 C / Clang22.1.4 / 汇编 | **NOT_RUN** | 寄存器、内联、SLP、实际分配次数未知 |
| checksum / full gate / 25 paired timing | **NOT_RUN** | 性能 **UNKNOWN**，没有测得增益 |

## 2. 精确基线、文件与工具链

上传的文本包装使用 CRLF。只对包装中的换行作 CRLF→LF 还原，提取两个 EXACT 标记之间的 Kernel 字节；得到附件声明的精确 SHA。原上传文件没有修改。

| 工件 | UTF-8 字节 | SHA256 |
|---|---:|---|
| 上传包装 `astra-web-r11-source(2).txt` | 263896 | `8278e5bf3a955ba6971b7db0aac77b43a7888942f11f3f33ae2c5876c1c40fcc` |
| `source/Kernel.lean` | 252609 | `4bdd1e7db35cd85e17d06511721d5dbf7f654ec12e58633264b08a086ec54fa0` |
| A `Kernel.short-shared.lean` | 254458 | `5645b861ce6eeaa00cbb80a791dcb225dca75463f1816ca051d52fe6b62ba910` |
| B `Kernel.short-scalar-call.lean` | 254712 | `4d778479f3c97c9793678b5f9e1d5742fe6190344d406ef3c9fef7b0ac86595e` |

A 比原文件增加1849字节，剩余1542字节；B 增加2103字节，剩余1288字节。两者是互斥版本，不要叠加应用。并行 W01 证明修复若也要合入，必须重新计算组合文件大小、SHA 和全部验收；这里的余量没有替尚未收到的修复预留空间。

固定目标：Lean4.34.0 commit `293d5d0c0c3f3dded4688b3ccd6a33939ac5102b`；FloatLib `0d91825727839f597fd06b22fdd038ea21480f0c`；competition `4b7e83841cc0c32c6529f533923c73d33b5ecf97`；Clang22.1.4 `-O3 -ffp-contract=off`，不加 `-march=native`。这些是**目标 pin**，不能写成已经运行的工具身份。

本环境 PATH 中没有 lean/lake/elan/clang/clang-22；没有下载安装或重建工具链，没有用 gcc/其他 Lean 替代。`logs/toolchain-availability.json` 记录现状。公开源码访问的初始网页路径失败，随后通过只读公开下载/连接器取得指定 commit/tag 的源码；各源文件有实际 SHA/URL。没有使用更新 Lean/AVX API。

## 3. 附件的真实数据流

原 Kernel 的以下位置是本轮锚点（行号指还原后的原件）：

| 层 | 原件位置 | 实际内容 |
|---|---|---|
| 输入包 | 6475–6538 | `packGeneral` / `packShared` / `pack` 生成 `Vector P12 n` |
| 逻辑有序循环 | 6555–6575 | `natLoop`，逐 k 调 `update`；`natLoop_lane` 接实际 `NativeFinal.dotLoop` |
| 机器计数循环 | 6577–6607 | `wordLoop`，8 个 Float32 参数；每次读取一个 P12，终点构造 F8 |
| 单组算术 | 6609–6625 | `dot8` 先完整 pack，再进入 wordLoop |
| 精确终结 | 6639–6677 | `finish8` / `blockAt_word`，复用 `Packed10.finish` |
| 跨 batch 行映射 | 6679–6694 | `blockRows` 的每一行使用自己 `r/m*n*p` 的 B 起点 |
| 输出组织 | 6696–6752 | ceil 分组、`words`、`rowWord`、flat `Vector.ofFn` |
| 总入口 | 6760–6774 | p2、至少4行、正 n、机器长度 guard，最后接原 `bmm_spec` |

附件中没有名为 `localP12` 或 `directrawgather` 的定义。本文把前者作为“每组 pack 一个 P12 向量”的描述，把后者作为待比较的“循环内直接 raw 读取/转换”架构；没有假装它们是额外已编译候选。[K]

每个 k，P12 保存4个 A 值及8个 B 字段。四个 B 起点全相等时，`packShared` 只做两次 B 解码，然后复制同一值到四个字段。累加器顺序为列优先：

| 累加器 | 输出 |
|---|---|
| s0,s1,s2,s3 | 第0列的四行 |
| s4,s5,s6,s7 | 第1列的四行 |

`finish8` 的 W8 顺序是 `s0,s4,s1,s5,s2,s6,s3,s7`，对应每行两列。这个置换必须保留。`rowWord` 最后使用 `ExecFloat.Binary.ofBits32` 从 UInt32 重建载体；它不是另一次 `Float32.ofBits` 原生浮点解码。[K][S5]

## 4. 真实对象布局、分配与 RC

固定 Lean 编译器把 Float32 降成 C `float`，UInt32 降成 `uint32_t`；一般多字段 structure 降成 `lean_object*`。构造器布局会把同种标量字段放进 scalar payload，而不是为每个字段做一个对象。[S1][S3]

| 若结构实际物化 | 指针子字段 | 标量 payload | 64位下含8字节对象头的逻辑大小 |
|---|---:|---:|---:|
| P12 | 0 | 48字节 | 56字节 |
| F8 | 0 | 32字节 | 40字节 |
| W8 | 0 | 32字节 | 40字节 |
| 已保留 F10 | 0 | 40字节 | 48字节 |

这些是未计 allocator 分档/元数据的布局计算，不是实际 malloc 大小、动态分配次数或流量测量。P12 是一个有12个原始标量字段的对象，不能按“12个 Float32 box”计费。P12 没有指针子字段，销毁时也不需要递归 dec 12个浮点对象。[S1–S3]

Vector 的尺寸证明及单个 Array 包装会被擦除；底层 Array 仍然存在。普通 Array 是对象指针槽，不是内嵌 P12 payload 的连续数组。一个容量恰为 n、完全物化的 pack 的64位逻辑占用是：

`(24 + 8*n) + 56*n = 24 + 64*n` 字节。

所以 n1 为88，n2 为152；另有可能保留的 F8、闭包/索引中间值、输出和分配器成本。优化、复用、借用推断也可能减少部分成本。这里**不把88/152字节当作已测可回收成本**。[S1–S3]

相对地，`Array Float32` 在普通多态槽里需要 Float32 box；它不是一个可用的 FP32 scalar array 代替方案。64位机器的 UInt32 装箱则是 immediate tagging，因此 raw Binary32 输入/输出载体与 boxed Float32 的成本也不同。不能给每个最终 Binary32 额外虚构一个浮点盒子。无可用 Float32Array 的前提照旧；FloatArray 用 double，不能把累加改成 Float64。[S1][S5]

局部 P12 有两个不同结果：

1. 只删 Vector、仍让 P12 逃逸：还保留一至两个堆结构。
2. producer/consumer 内联后，所有 projection 对已知 constructor 可见：Lean 的 `SimpValue` 能直接替换成对应字段，P12 才可能完全消去。

“local”不等于“C stack struct”。本候选直接用 Float32 lets/参数，避免依赖一次尚未观察到的 P12 scalar replacement；但终点 F8 接口仍存在。[S3][S4]

## 5. Float32 的实际转换与终结调用

FloatLib 固定 `Formats/IEEE754/Native.lean` 给出：

- `toFloat32 value = Float32.ofBits (toBits32 value)`。
- `ofFloat32 value = ofBits32 value.toBits`。
- `ofBits32` / `toBits32` 是精确原始字载体包装/提取，不调用原生浮点转换。[S5]

Lean 固定 runtime 中：

| 原语 | 源码行为 | 不能跳过的边界 |
|---|---|---|
| `lean_float32_of_bits` | bit_cast 后检查 NaN，并返回原生 quiet NaN | 是导出的外部函数；生成调用处不能无证据当成免费 bitcast |
| `lean_float32_to_bits` | NaN 返回固定 `0x7fc00000`，其他值 bit_cast | 同样是外部函数；不保留任意 NaN payload |
| `lean_float32_isnan` | 原生 isnan 布尔结果 | 源码很短不等于调用、保存寄存器成本为零 |
| `lean_float32_add/mul` | header 中 static inline 的 C `+` / `*` | 结合原 Clang 选项保留分开的乘、加；不能改 FMA |

`of_bits` 和 `to_bits` 的源函数本身没有 Lean 分配或 RC；但实际 PLT/direct、链接/LTO、caller spill、cache 等都需要目标二进制。没有它们的反汇编，本报告不报指令数、周期或纳秒。[S1][S2]

**实际附加 Kernel 的 `Packed10.finish` 使用 `result.isNaN = false`，不是前面定义的 R7W04 自比较 guard。** 非 NaN 的每个输出继续 `ofFloat32`；八个全非 NaN 输出因此有8个 isnan、8个 to_bits 的源调用，除非目标编译证明确实消除/内联。起始 `Float32.ofBits 0` 可能成为闭合常量初始化，应单独观察，不能按每 lane 计一次。[K][S1][S2][S5]

原始 raw A/B 必须保留给 `R7NaNReplay.replayEarly`。把最后 native Float32 的 bits 直接作为所有结果会丢失 NaN payload、signaling 选择次序等合同。候选没有触碰这条终结路径。

## 6. 可集成候选 A：共享 B 的 n1/n2 显式展开

实际选择条件是：

```lean
(n=1 ∨ n=2) ∧ b1=b0 ∧ b2=b0 ∧ b3=b0
```

它放在原 `dot8` 内，因此外层原始 p2、正 n、机器长度 guard 不动。混合 B 起点及 n>2 继续走原 pack+wordLoop。 helper 用实际 `Array.getD` 和 `ExecFloat.Binary.toFloat32`，没有抽象 read 假设。n2 的第二 B slice 使用 `b0+p`、`(b0+1)+p`，所以内部引理无需额外把 p 固定为2。

完整插入及替换片段如下，编译状态 **NOT_RUN**：

```lean
-- INSERT before dot8 inside namespace Submission.R11CrossRows. Lean NOT_RUN.
@[inline] def read32 (v : Array Binary32) (i : Nat) : Float32 :=
  ExecFloat.Binary.toFloat32 (v.getD i posZero)

/-- Called only for n=1 or n=2; decode both slices before accumulator arithmetic. -/
@[inline] def shortShared (n p a0 a1 a2 a3 b0 : Nat) (A B : Array Binary32) : F8 :=
  let z := Float32.ofBits 0
  let x0 := read32 A a0
  let x1 := read32 A a1
  let x2 := read32 A a2
  let x3 := read32 A a3
  let y0 := read32 B b0
  let y1 := read32 B (b0+1)
  if n=1 then
    ⟨z+x0*y0,z+x1*y0,z+x2*y0,z+x3*y0,
     z+x0*y1,z+x1*y1,z+x2*y1,z+x3*y1⟩
  else
    let u0 := read32 A (a0+1)
    let u1 := read32 A (a1+1)
    let u2 := read32 A (a2+1)
    let u3 := read32 A (a3+1)
    let v0 := read32 B (b0+p)
    let v1 := read32 B ((b0+1)+p)
    let s0 := z+x0*y0
    let s1 := z+x1*y0
    let s2 := z+x2*y0
    let s3 := z+x3*y0
    let s4 := z+x0*y1
    let s5 := z+x1*y1
    let s6 := z+x2*y1
    let s7 := z+x3*y1
    ⟨s0+u0*v0,s1+u1*v0,s2+u2*v0,s3+u3*v0,
     s4+u0*v1,s5+u1*v1,s6+u2*v1,s7+u3*v1⟩

theorem shortShared_lane (n p a0 a1 a2 a3 b0 : Nat) (A B : Array Binary32)
    (hn : n=1 ∨ n=2) (l : Fin 8) :
    lane (shortShared n p a0 a1 a2 a3 b0 A B) l =
      NativeFinal.dotLoop n (select4 a0 a1 a2 a3 (l.val%4))
        (select4 b0 b0 b0 b0 (l.val%4)+l.val/4) p A B 0 (Float32.ofBits 0) := by
  rcases l with ⟨l,hl⟩
  have h : l=0 ∨ l=1 ∨ l=2 ∨ l=3 ∨ l=4 ∨ l=5 ∨ l=6 ∨ l=7 := by omega
  rcases h with rfl|rfl|rfl|rfl|rfl|rfl|rfl|rfl <;>
    rcases hn with rfl|rfl <;>
    simp [shortShared, read32, lane, select4, NativeFinal.dotLoop, Nat.add_assoc]

-- REPLACE existing dot8:
def dot8 (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32)
    (hn : n<USize.size) : F8 :=
  if (n=1 ∨ n=2) ∧ b1=b0 ∧ b2=b0 ∧ b3=b0 then
    shortShared n p a0 a1 a2 a3 b0 A B
  else
    let v := pack n p a0 a1 a2 a3 b0 b1 b2 b3 A B
    let z := Float32.ofBits 0
    wordLoop n v (USize.ofNat n) (USize.toNat_ofNat_of_lt' hn) 0 z z z z z z z z

-- REPLACE proof body of dot8_lane:
  unfold dot8
  split
  · rename_i h
    rcases h with ⟨hs,h1,h2,h3⟩
    subst b1; subst b2; subst b3
    exact shortShared_lane n p a0 a1 a2 a3 b0 A B hs l
  · rw [wordLoop_eq, USize.toNat_zero]
    simpa only [lane_zero] using
      natLoop_lane n p a0 a1 a2 a3 b0 b1 b2 b3 A B 0 zero8 l
```

这个代码保留 `z+x*y`，不会把 n1 简化成直接 product。n2 先取 x/y/u/v，再显式计算 s0…s7 和第二轮。源码中没有临时 P12、Vector、逐 k 递归、或一轮后构造的中间 F8；仍返回终点 F8。

源码顺序只建立了一个适合代码生成的形状。编译器可以移动独立运算，或将两轮融合为每 lane 的短表达式；它不保证八个 s 同时占有八个物理寄存器。应以数据依赖及实际调用位置判定“conversion-free eight-chain arithmetic”，不要把源变量数误当机器存活集。

### 复用证明的具体路线

`shortShared_lane` 只枚举 n=1/2 和8个 lane，**不枚举浮点输入**；数组、索引、raw words 始终是任意量。它展开真实 `NativeFinal.dotLoop` 的一至两轮及具体读取，预期由定义和 Nat 归一化关闭等式。

`dot8_lane` 真分支代入三个 B 起点相等式，使用该新引理；假分支保留原 `wordLoop_eq → natLoop_lane`。其 statement 没有改变。下游复用：

`dot8_lane → finish8_word + Packed10.finish_eq_dot → blockAt_word → blockRows_word → rowWord_eq → core_eq_rows → DirectRows/DirectSmall/referenceBmm → bmm_spec`。

其中终结与 NaN 精确性来自已有实际定义和证明，不重新引入“native 一定等于 exact”的假设。原 R11 新 wiring 尚未编译，本轮也没有把这个事实抹去。新引理若 simp 不闭合，应先分离两个具体 n 的方程，显式 `rw [NativeFinal.dotLoop]` 并归一化加法；不要替换为额外公理或 read 假设。

新增 proof 当前最大的可执行检查点是固定 Lean 下：`simp` 对递归方程的一至两轮展开、Fin lane case 和 `Nat.add_assoc` 是否完全匹配。没有 pinned compiler，不能用“无 sorry 的文本”代替已证明。

## 7. 候选 B：纯标量算术函数，作为边界对照

B 使用同样 decoder、guard 和 proof reuse，只把算术单独命名：

```lean
@[noinline] def shortArith1 (z x0 x1 x2 x3 y0 y1 : Float32) : F8 :=
  ⟨z+x0*y0,z+x1*y0,z+x2*y0,z+x3*y0,
   z+x0*y1,z+x1*y1,z+x2*y1,z+x3*y1⟩

@[noinline] def shortArith2 (z x0 x1 x2 x3 y0 y1 u0 u1 u2 u3 v0 v1 : Float32) : F8 :=
  let s0 := z+x0*y0
  let s1 := z+x1*y0
  let s2 := z+x2*y0
  let s3 := z+x3*y0
  let s4 := z+x0*y1
  let s5 := z+x1*y1
  let s6 := z+x2*y1
  let s7 := z+x3*y1
  ⟨s0+u0*v0,s1+u1*v0,s2+u2*v0,s3+u3*v0,
   s4+u0*v1,s5+u1*v1,s6+u2*v1,s7+u3*v1⟩
```

完整替换在 `agent-candidates/short-scalar-call-fragment.lean`；完整单文件与 SHA 在第2节。fully applied、静态已知的 Float32 函数走标量签名；偏应用或经通用 closure 调用可能重新引入 boxing。不要把它改成捕获数组/浮点值的 CPS closure 后仍声称相同成本。[S3]

**条件 ABI 结论：**若最终仍是普通 x86-64 System V 的独立 C 调用，前8个 scalar float 参数用 XMM0…XMM7；n2 的13个参数中5个使用8字节 stack 参数槽，共40字节（不包括对齐、调用帧、保存值）。n1 的7个参数不超该寄存器参数数量。typed scalar 不等于 register-only，也不等于 heap box。[S8]

但是固定 EmitC 不输出 C noinline，因此最终调用是否存在必须看 Clang 产物。若 A/B 变成同一机器代码，记录“lowering 收敛”，无需将它们各自做完整性能搜索。B 即使保留边界，也仍需终点 F8 分配、返回及 finish8；它的价值只能由相对 pack 的整调用代价判断。

## 8. 与 localP12、directrawgather 的区别

| 维度 | 当前 per-group P12 vector | 有界 scalar staging A/B | directrawgather 循环 |
|---|---|---|---|
| 输入解码 | shared每k6次；general每k12次 | 所选 shared n1=6、n2=12次 | 若保留同一 sharing，次数可相同 |
| 输入解码时机 | pack阶段，进入累加循环前 | 源码全部置于展开算术之前 | k循环内部；n2第二轮穿过第一轮部分和 |
| P12+临时 Array | 源码有 | 所选分支无 | 可以无 |
| 循环计数/packet取值 | USize循环+uget | n1/n2无内层循环 | 仍有k循环或逐轮读取 |
| 活跃值保存压力 | 包内存+8条累加链 | 预解码输入、ABI/局部stack、终点值 | 输入调用期间的8个部分和 |
| exact finish/NaN replay/W8 | 有 | 保留 | 仍必须保留 |
| 跨 batch 与末尾 | 原有 | 混合/末尾退回原路径 | 需逐行实际 base，不能共享错 |
| 性能 | 本R11 UNKNOWN | UNKNOWN | UNKNOWN |

directrawgather 能删包，却把真实 of_bits 调用带回累加期间。普通 SysV callee-saved 集合不保护 XMM 寄存器；这会使“八个部分和如何跨调用存活”成为具体风险，而非抽象顾虑。预解码把这个风险移到输入值保存，不能称为把保存成本全部消除了。[S8]

n1 没有 k1 部分和需要保留，direct gather 与 bounded staging 更接近；n2 才清楚地区分两者。没有目标汇编时不能断言 generic gather 必败，也不能从“少一次分配”推定它值得晋升。

## 9. Clang22.1.4、SLP 与有序 IEEE

固定 Clang driver 在普通 `-O3` 开启 loop/SLP vectorization；LLVM 文档将 SLP 描述为合并独立的标量操作。四个行实例在同一个 k 的运算相互独立，存在把它们放入 SSE/向量 lane 的机会；每个输出自己的 k0→k1 依赖必须保留。[S6][S7]

允许的形状：把四行第0列的 k0 products 并排，再按 lane 做加法；另四个第1列同理；k1再对应更新。禁止的形状：跨 k 创建两组 partial sums 再横向归约、FMA contraction、把 `(+0+product0)+product1` 代换为任意实数等式。

`-ffp-contract=off` 禁止乘加收缩；默认精确选项保留 signed zero、不启用 associative math。它不单独承诺完整 IEEE exception environment、FTZ/DAZ 状态或 NaN payload 合同。保留官方全部选项与运行环境，不能通过更换 flags 或修改 runtime 获得此研究之外的结果。[S6]

没有 `-march=native` 不能推出“此机器完整 target features 是什么”；仍需完整 argv、triple、默认 CPU/配置和 `-###`。常见 Linux baseline x86-64 下，SSE 宽度合理，不能因为写了8个数就断言有AVX/YMM。具体 SLP 成败由发出的 C/IR、call/alias/control flow、成本模型决定。[S7][S8]

旧2x4/2x8已得到SIMD、没有hot spills却整调用变慢，这一历史由附件提供，本轮没有重测。它排除了把“出现 mulps/addps”当成果的做法。本候选与该历史的实质差异是对象准备/销毁的消除，不是第一次获得 SIMD。

## 10. 完整成本与可达范围

令 `R=batch*m`，`G=(R+3)/4`。原源码每组有8n次乘法、8n次加法，尾部即使只有1–3个有效行也会计算整组；这是操作图计数，不是时间模型。输入解码源次数为 `n*Σ_g q_g`，shared组 `q_g=6`，其他组12；起始zero、终结转换、NaN重放另算。

A/B 对选中组只改变准备和有界执行形状；没有减少正常 input decode 次数。仍需计入：

- 原始数组读取、Nat 地址运算/边界分支、跨 batch base 计算；
- 早期解码值跨后续调用的保存、可能的scalar ABI传递与stack；
- F8结果物化或标量替换、8次终结检查及实际to_bits、NaN重放；
- W8及words数组、最终flat Vector.ofFn、输出生命期与销毁；
- 增加的 n1/n2 + sharing predicate，以及未选中n>2/mixed组的额外分支成本；
- 代码体积、缓存与函数内联造成的连带变化。

不能把几个局部节省相加成完整收益。尤其 W8 输出对象没有消失，terminal F8 还可能使结果在分配/终结调用间保存在对象或stack上；这并不自动判败，但需要全成本测量。

对于 p2、n>0、m>0，选择条件等价于四个 flattened rows 全部在同一个 batch：

`floor(4g/m) = floor((4g+3)/m)`。

因此 m1/m2/m3 完全没有这项特化；跨 batch 组保留旧路径；不完整的最后一组含有下一 batch 的虚行，也回退。

附件提到的旧 `(batch,m,n,p)=(2941,15,2,2)` 的纯索引几何为：R44115，G11029，8823组符合sharing，2206组走原路径，其中有1个尾组、1个unused row。这些数量已经用独立整数枚举复核。**约80%组数不是80%时间，更不能与旧14.81% exposure相乘得到可回收收益。** 所有数据仅说明分支可达范围；这个旧组也不是本轮新增权重。[K]

## 11. 正确性负边界、空维度与任意 Nat

### 11.1 起始 +0 不可删

n1：`A=0x80000000`（-0），`B=0x3f800000`（+1）。乘积为 -0；规定的 `RN(+0 + RN(A*B))` 为 +0。直接返回乘积会产生 `0x80000000`，而规定结果为 `0x00000000`。

n2 两项乘积均为 -0 时，规定两轮仍得到+0；先把两个product相加可得到-0。候选明确保留初始加法；没有复用之前未被采用的 n1 raw-product/-0-correction 路线。

### 11.2 FMA / 更宽累加会改变 n2

某一输出使用：

| k | A原始字 | B原始字 |
|---|---|---|
| 0 | `bf800000` (-1) | `3f800000` (1) |
| 1 | `3f800001` (1+2^-23) | `3f7ffffe` (1-2^-23) |

第一轮是-1。第二项精确乘积为 `1-2^-46`，单独binary32乘法舍入成1，然后加-1得到+0。如果把第二轮融合，得到 `-2^-46`，字为 `a8800000`。用更宽类型保留乘积精度并只在最后舍入，也会得到这个不同值。

`negative_witnesses.py` 使用 Fraction/整数 RN-even，实际输出保存在 `logs/negative-witnesses.json`。这验证反例算术，不是 FloatLib、Lean、所有输入或实际机器的验证。

### 11.3 NaN 与无效运算

native解码本身已经会合并NaN payload。不同raw qNaN/sNaN可以进入相同native中间结果，但原始Spec应选择不同字。因此必须保留原始输入与 `Packed10.finish`/`replayEarly`，包括后续sNaN、Inf*0、Inf冲突等。不要让自造Python IEEE模型代替实际Spec的payload选择；本轮有限反例程序特意不实现NaN分支。

### 11.4 空维度与 USize

- batch=0或m=0时不满足 `4≤batch*m`，新快路不可达。
- p=0时不满足p2；最终空输出由原路径处理。
- n=0时不满足 `0<n`；有输出时原语义为零项有序和，从+0开始。
- n1/n2外、p2外、少于4行、机器长度不满足的情况继续原fallback。

新片段的索引全部是Nat+`getD`，没有新增Nat→USize截断或未经证明的uget。即使单独讨论任意base、空数组或极大Nat，读取仍总定义，与原dotLoop一致。原fallback wordLoop 的 USize termination/stepNat 义务保留，未另行宣称已编译。

长度小于USize.size不能自动证明所有虚尾行的索引也小于它。若将来把 `getD` 换成uget，必须逐个证明实际index、加法/乘法无回绕及 `i<size`，或者对无效行保留total fallback；不能仅凭有效输出范围解除这个义务。

## 12. 最小可证伪试验与停止条件

完整具体协议在 `VERIFICATION-PLAN.md`，代码生成root在 `probes/R11W03Probe.lean`，本轮均未运行。

**第一步只买代码生成证据。** 在隔离的固定官方环境中先编译原 R11 源；它本身若失败，记录真实错误，并把独立确认的父本证明修复对照地应用到控制和候选，重新绑定SHA。随后先编A；只有需要区分边界/寄存器压力时才编B。

四个wrapper直接调用实际 `Submission.bmm`：共享n1、共享n2、m1跨batch n2、R5尾组n2。跟踪它们实际可达的 C call graph，不能只grep整份C里仍存在的老P12符号。观察：

1. 所选分支有无packet Array或P12分配；有则否证“已消除包”的目标。
2. 有无Float32 boxing、closure、通用apply；存在则先确认其实际路径和成本。
3. 每条mul/add链的顺序、conversion call位置、FMA/horizontal reduction是否出现。
4. 分开统计预解码输入保存、参数stack、部分和spill、终点结果保存；“有stack”本身不等于候选失败。
5. F8/W8/output分配、8个exact finish、NaN重放和尾行路径仍在。
6. B若没有保留机器函数边界，则条件ABI解释不适用；若两候选产物相同，合并结论。

需要固定Clang22.1.4原flags和真正的C/object/relocation/disassembly；SLP remark只能解释选择，不能取代产物。不能用“函数源码很短”或“mulps出现了”推断时间。

**第二步是开发范围的完整BMM调用。** 只计预处理好的算术体不能回答本题。保留原harness对输入、输出消费/销毁的边界，覆盖选中组、mixed组、tail、n>2负控制；新分支也会给未选中情况收费。

**最后才是原验收。** 冻结候选后运行原四spec、statement build、kernel replay、仅允许三项标准公理的审计、checksum及25 paired full timing rounds。保持原输入、权重、统计/不确定性规则与retained accepted control；不要把当前未编译R11直接当作接受控制。没有这套证据，本轮只能交付研究候选。

停止或暂存：正确性/公理失败；包分配未被移除；目标机器算术区间仍穿过转换调用而该成本假说失效；完整调用不优或不满足原置信/验收规则。局部代码生成改善仍可作为证据留存，不能冒充性能采纳。

## 13. 交付物与证据导航

- `source/Kernel.lean`：精确还原原件，附 `attachment-context.txt`。
- `agent-candidates/`：两套独立patch、完整Kernel、Lean片段、大小/SHA、source review及shape覆盖。
- `agent-runtime/`：固定Lean原语/布局/内联调查与候选独立review；`primary/manifest.json`列出25个精确源文件。
- `agent-clang/`：Clang22.1.4/LLVM/ABI、完整成本及反方review；精确tag源文件与SHA记录。
- `primary-floatlib/`：载体与原生转换的固定源文件，Git blob SHA核验及SHA256。
- `scripts/verify_source_artifacts.py`：零fuzz重新应用两patch，检查SHA、边界字节及新增文本；不是语法或公理审计。
- `scripts/negative_witnesses.py`：有限精确有理数反例，不执行候选。
- `probes/R11W03Probe.lean` / `VERIFICATION-PLAN.md`：目标端最小实验入口及不改gate的复现要求。
- `logs/`：本轮实际静态检查/有理数反例/工具可用性结果。
- `manifest.json` / `SHA256SUMS`：实际交付文件清单与SHA；manifest不对自己做递归哈希。

两个完整候选都只保留 `import ContractTensor`。新增片段没有sorry/admit/unsafe/extern/implemented_by/公理替代/native计算公理/option变更。静态文本检查不能证明传递公理集合；正式审计仍是NOT_RUN。也没有替用户的其他并行任务改连续输出writer或compactB准备路线。

## 14. 一手来源索引

以下GitHub链接均固定到实际读取的commit/tag，下载副本及SHA在工件中；没有用较新版本接口替代。

- **[K] 附件精确 Kernel 与上下文**：`source/Kernel.lean`，SHA `4bdd1e7d…54fa0`；历史测速/14.81%只作为用户提供的上下文，本轮未独立复测。
- **[S1] Lean runtime header**：[lean.h](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/include/lean/lean.h)。Array195–202；ctor772–777；UInt32/Float32 boxing2955–3014；原生浮点3253–3275。
- **[S2] Lean runtime implementation**：[object.cpp](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/runtime/object.cpp)。Array/ctor销毁387–438；isnan1976；of_bits/to_bits1987–2004。
- **[S3] Lean类型降级和boxing**：[ToImpureType.lean](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Lean/Compiler/LCNF/ToImpureType.lean)190–277；[ExplicitBoxing.lean](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Lean/Compiler/LCNF/ExplicitBoxing.lean)335–350；[Vector/Basic.lean](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Vector/Basic.lean)32–36、320–321。
- **[S4] Lean内联、projection和C生成**：[SimpValue.lean](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Lean/Compiler/LCNF/Simp/SimpValue.lean)16–25；[InlineCandidate.lean](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Lean/Compiler/LCNF/Simp/InlineCandidate.lean)61–108；[EmitC.lean](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Lean/Compiler/LCNF/EmitC.lean)30–43、575–588、725–747、932–965。
- **[S5] FloatLib原生转换与直接载体**：[IEEE754/Native.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native.lean)；[ExecFloat/Carrier.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Carrier.lean)；[Storage/Core.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Configured/Storage/Core.lean)。
- **[S6] Clang22.1.4浮点选项**：[UsersManual.rst](https://github.com/llvm/llvm-project/blob/llvmorg-22.1.4/clang/docs/UsersManual.rst)1746–1811、2084–2092。
- **[S7] LLVM22.1.4向量化**：[Vectorizers.rst](https://github.com/llvm/llvm-project/blob/llvmorg-22.1.4/llvm/docs/Vectorizers.rst)8–16、203–215、469–499；[CommonArgs.cpp](https://github.com/llvm/llvm-project/blob/llvmorg-22.1.4/clang/lib/Driver/ToolChains/CommonArgs.cpp)3342–3388；[PassBuilderPipelines.cpp](https://github.com/llvm/llvm-project/blob/llvmorg-22.1.4/llvm/lib/Passes/PassBuilderPipelines.cpp)1316–1422。
- **[S8] 目标与ABI**：[X86.cpp](https://github.com/llvm/llvm-project/blob/llvmorg-22.1.4/clang/lib/Driver/ToolChains/Arch/X86.cpp)22–140；[X86CallingConv.td](https://github.com/llvm/llvm-project/blob/llvmorg-22.1.4/llvm/lib/Target/X86/X86CallingConv.td)570–599、1119–1135。

**本轮可交给D的决定：先编译/审视A的实际shared n2路径，验证临时packet真的消失以及转换调用与部分和的相对位置。若这个结果支持继续，再用原完整调用判断；B仅用于分辨内联/参数边界。现在不采纳性能结论。**
