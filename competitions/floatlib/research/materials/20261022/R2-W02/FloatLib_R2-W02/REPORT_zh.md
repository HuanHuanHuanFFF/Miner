# FloatLib R2-W02：一次预转换、B 四字段打包与四条原生累加链

日期：2026-10-21（UTC）。仅使用本轮消息、指定固定公开源码和本轮自造合成例。

## 结论与交付状态

**值得进入一次真实 codegen 与完整调用对照的唯一候选是：A 一次转换为 `Array Float32`；B 从原始字直接转换、打包为 `Array F4`；F4 含四个原生 Float32 字段，按 `[batch][columnBlock][k]` 排列；每次点积用四个独立 Float32 递归参数承载四个输出。**

这个选择减少重复转换与 B 的持久元素对象、共享每步 A/B 对象读取，并暴露四条独立累加链，供编译器与 CPU 重叠执行。单个输出的 100 步串行依赖并未缩短。每个有效输出仍从 +0 开始，按 k 递增执行独立 RN32 乘法、再独立 RN32 加法；四路只是交错执行。证明的核心是“投影出任一路后，恰好还是原来的顺序递推”，不需要浮点结合律。

默认形状的源程序计数是：输入转换 1,000,000 → 20,000；A 热循环读取 500,000 → 130,000；B 热循环对象读取 500,000 → 130,000；代价包括 A 的 10,000 个 Float32 元素对象、B 的 2,600 个 F4、准备过程、RC/释放以及尾块增加的 20,000 个 MAC，即总计 **520,000 MAC，增加 4%**。这些是次数推导，**没有换算成速度或微秒**。

本轮完成固定源码审查、完整候选实现源码（待编译）、结构证明草稿、生成 C 的检查入口、完整调用对照请求、有限 RN32 与索引小诊断。当前环境没有 Lean/lake，未安装工具链。

| 工作项 | 本轮状态 |
| --- | --- |
| 指定 commit/tag 的合同、计时器、FloatLib 桥和 Lean runtime/compiler 源码 | 已读取、留存 URL 与 SHA256 |
| Python 精确整数/RN-even 与布局诊断 | 已执行；720 形状、4,860 输出、10,000 索引检查通过 |
| 单文件候选 `candidate/Kernel.lean` | 已生成；唯一 `import ContractTensor`；4,525 字节 |
| 禁止标识/导入/字节数静态预检 | 已执行；仅词法预检，不是 Lean gate |
| Lean 候选/证明 elaboration | **NOT_RUN** |
| 该候选实际生成 C、机器码、SLP/RC 消除 | **NOT_RUN** |
| 原生 FloatLib NaN payload 逐位诊断 | **NOT_RUN** |
| 官方完整 gate、完整调用时间 | **NOT_RUN** |
| 无条件 `Submission.bmm_spec` | **尚未完成**；布局与 builder 证明及既有数值桥待接入 |

`Kernel.lean` 暴露 `Submission.bmm`，供 codegen/直接运行原 `benchBmm` 二进制的诊断；**它不是可直接通过完整 gate 的提交，当前也不能使用固定版本的 `gate --bench`**。没有声明假的 `bmm_spec`，也没有用证明占位、额外公理或本机决策绕过缺口。已写出的证明源码同样没有被本轮 Lean 编译验证。

## 1. 固定源码核对结果

### 1.1 合同确实约束逐步操作和原始字

`Competition.Binary32` 是 `ExecFloat.Binary 8 23`。`bmmSpec` 对每个输出先解码 `(b,i,j)`，再对 `List.finRange n` 作左 fold：

```lean
ExecFloat.add acc (ExecFloat.mul a bVal)
```

初值是 `ExecFloat.Binary.zero false`。A 地址为 `(b*m+i)*n+k`，B 地址为 `(b*n+k)*p+j`。合同的 `getD` 越界返回同一个 +0。最终义务要求输出 `Vector.get` 函数与参考函数相等，不能以实数相等、普通 `==` 或计时样例相等替代。[S01]、[S02]

固定 `VerifyBmm` 的目标是：

```lean
theorem accepted : Competition.BmmObligation Submission.bmm := Submission.bmm_spec
```

所以带未提供假设的定理、只证明 finite 输入的定理，或者长度检查，都不能通过这个目标。[S03]

### 1.2 已有原生桥与本轮依赖

真实公共 finite-add 桥的完整条件为：

```lean
theorem ofFloat32_add_of_isFinite (x y : Float32)
    (hx : x.isFinite = true) (hy : y.isFinite = true) :
    ofFloat32 (x + y) = ofFloat32 x + ofFloat32 y
```

条件约束两个输入，输出允许成为零、次正规或 Inf。`ExecFloat` 的 `+` 和 `*` 实例分别接到合同所用的 `ExecFloat.add`、`ExecFloat.mul`。[S04]、[S05]

往返方向不能混淆：

- `toFloat32_ofFloat32`：原生 Float32 导入再导出，所有原生值都成立。
- `ofFloat32_toFloat32`：任意原始 Binary32 导出再导入，右侧是 canonicalized word，不能无条件还原原输入 payload。[S06]、[S07]

用户已给出的 native finite-mul、finiteRoundtrip 和“最终 finite ⇒ 原始精确 dot”定理，作为**现有开发者提供的接口**使用。本轮没有重新研发 final-finite 守卫，也没有声称这些接口已经接入本候选或通过 gate。

建议数值接口面向任意两条原始输入序列，而不是绑定到旧数组循环的具体函数体。这样完成布局与 fold 的外延等价后，可以直接复用该定理，不必重做浮点数学。

### 1.3 计时语义已确认

`BenchBmm` 固定 m=50、n=100、p=50，默认 `BENCH_PAIRS=500000`，所以 batch=2。每次受测调用先执行完整 kernel，再遍历全部输出计算 checksum；计时涵盖两者。每类默认三次计时，取最小值；raw 类运行 checksum，但不计入三个性能类。[S08]

固定 gate 默认使用 25 个交替先后顺序的 paired rounds；它的 headline minimum-time ratio 与 paired-round 统计是不同量。每次 evaluation 在循环前选一次 seed，同一组 25 轮复用它，不是每一轮重新选 seed。[S09]

**复现时容易踩到的一点：此固定版本的 `--bench` 仍运行 statement 阶段，而 statement 会 `lake build VerifyBmm`。** 它省去部分策略、公理与 kernel replay 阶段，但没有省去 `Submission.bmm_spec` 的 statement 检查。因此本包未补齐证明时，不能用 `gate --bench` 取得时间。第 9 节给出在隔离目录正常构建原 `benchBmm`、直接执行原二进制的诊断方法；完整 gate 留待证明接齐。这里以固定 `gate.py` 的实际 stage 列表和函数体为准。[S09]

## 2. 为什么选择 B 的四字段结构

### 2.1 boxed uint32 不等于每个元素都有堆对象

在固定 Lean runtime 的 64 位分支，`lean_box_uint32` 用 tagged immediate；`lean_box_float32` 则分配 constructor 对象存一个 float。因此，输入 `Array Binary32` 的 boxed uint32 与新建 `Array Float32` 的成本不同：一次预转换能去掉大量转换调用，但也会引入新的 Float32 堆对象，不能把 map 成本当成零。[S11]

若 A、B 都直接 map 到普通 `Array Float32`，默认产生 20,000 个元素的 Float32 表示。选定方案仍为 A 保留 10,000 个 Float32 元素对象，但 B 用 2,600 个四字段对象承载 10,000 个有效值与 400 个补零字段。

### 2.2 单对象里的字段确实可以是原生 float

Lean 4.34 的 `LCNF/ToImpureType` 将 `Float32` constructor 字段归为 4-byte scalar。四个同类型字段顺序获得偏移 0、4、8、12；F4 的对象字段数为 0，scalar payload 为 16 字节。`EmitC` 按这些布局信息生成 constructor 与 scalar projection；`lean_ctor_get_float32` 是 inline 字段读取。[S12]、[S13]、[S14]

这是选择 F4 的实际源码依据。不过，它只保证**每个 F4 内的四个字段连续**；`Array F4` 仍是对象指针数组，各 F4 的堆地址不保证连续。它不是标准 packed Float32Array，也不是一个可以假定整块连续 SIMD load 的裸 float buffer。

准备过程中的局部函数是否被完全消除、是否产生临时 Float32 box，仍需看实际生成 C。2,600 是源程序显式 F4 构造次数，不能据此声称整个准备过程只有 2,600 次运行时分配。

### 2.3 数据结构与累加状态采用不同表示

静态 B 使用 F4，有利于共享一个指针和相邻字段。动态累加状态使用四个独立 `Float32` 递归参数，F4 结果只在 k 循环终点构建。

`EmitC` 明确把 Float32 类型降成 C `float`，并把直接自尾递归降成参数赋值与 `goto _start`。这使四个独立累加器有直接的代码生成依据。[S13]

不能反过来断言“结构状态必然每步重新分配”：Lean 有 reset/reuse 等优化，结构状态可能复用原对象。独立参数的价值是减少对结构消除、复用及 scalar replacement 的依赖。包内小探针保留结构状态版本，只用于解释实际 codegen 差异，不作为第二条主路线。

## 3. 唯一候选的完整数据流

令：

\[
G=\lceil p/4\rceil=(p+3)\mathbin{/}4,\quad R=batch\cdot m,\quad O=R\cdot p.
\]

### 3.1 早返回

若 O=0，立即返回长度为零的输出，不转换任何输入。若 n=0，立即返回 O 个 +0。这不仅处理逻辑边界，也避免在例如 p=0、A 仍非空时做无用转换。

### 3.2 每次调用的准备

```lean
let nativeA := A.toArray.map ExecFloat.Binary.toFloat32
let packedB := packB batch n p B
```

B 直接从原始 Binary32 转换并打包，**不先构造完整的 `Array Float32 B` 再打包一次**。packed 地址及其四个字段为：

\[
P[(bG+g)n+k]_\ell=
\begin{cases}
\operatorname{toFloat32}(B[(bn+k)p+4g+\ell]),&4g+\ell<p,\\
+0,&\text{otherwise}.
\end{cases}
\]

其中 \(0\le\ell<4\)。B 的新逻辑顺序是 `[batch][columnBlock][k]`。热循环在同一 tile 内对 A 与 packed B 的索引都每步 +1。

**补零必须检查列号 `< p`。** 仅对 flat index 使用 getD，越过当前行末时可能读到下一 k 行的有效元素。本候选明确检查列宽。无效 lane 最终完全不观察，因此“padding 不为零”本身不必然导致有效 C 错误；这里保留显式补零，使布局契约与成本可审。

### 3.3 每行按四列成块，绝不跨行共享 A

对 `row < batch*m`，令 `b=row/m`。一个块使用：

- A 起点 `row*n`；
- packed B 起点 `(b*G+g)*n`；
- 原始输出列 `4*g ... 4*g+3`。

这样四个输出属于同一个矩阵行，才可以共享 A。若简单把平坦输出每四个一组，p 不是四的倍数时会跨到下一行，错误复用 A；第 8 节给出真实反例。

### 3.4 原生核心

以下是包内实际候选的核心，而不是伪造的已生成 C：

```lean
structure F4 where
  s0 : Float32
  s1 : Float32
  s2 : Float32
  s3 : Float32

def dot4 (A : Array Float32) (B : Array F4) :
    (fuel aIndex bIndex : Nat) →
    (s0 s1 s2 s3 : Float32) → F4
  | 0, _, _, s0, s1, s2, s3 => ⟨s0, s1, s2, s3⟩
  | fuel + 1, aIndex, bIndex, s0, s1, s2, s3 =>
    let a := A.getD aIndex zero32
    let v := B.getD bIndex zero4
    let m0 := a * v.s0
    let m1 := a * v.s1
    let m2 := a * v.s2
    let m3 := a * v.s3
    let t0 := s0 + m0
    let t1 := s1 + m1
    let t2 := s2 + m2
    let t3 := s3 + m3
    dot4 A B fuel (aIndex + 1) (bIndex + 1) t0 t1 t2 t3
```

进入点为 n 次递推、四个 `Float32.ofBits 0`。四路 k 次序都保留；没有局部和合并，没有用第一项乘积替代初始 +0，没有跳过零乘法。

### 3.5 尾块与逐 lane 回退

第一轮统一计算完整四路。默认 p=50，最后一块两路有效、两路是 padding，故多做 4% 算术。p=1 时额外算术可接近四倍，所以本轮不承诺所有形状加速。

`pushLane` 先检查 `col<p`，只有有效列才调用：

```lean
if x.isFinite then ExecFloat.Binary.ofFloat32 x
else exactAt batch m n p A B q
```

原始 A/B 始终保留。NaN payload 已在原生缓冲中规范化，不能从 nativeA/packedB 重建精确回退输入。[S07]、[S15]

软件 dot 必须在 `else` 内。Lean 严格求值：若把 `exactAt ...` 当普通参数传给一个 finish 函数，可能在分支选择前就计算所有软件点积。候选直接把它留在分支中。

有效 lane 分别接纳/回退；一个异常输出不牵连其他输出。无效 lane 不写出、不判断 finite、不回退。没有借此省略任何有效输出的 MAC。

### 3.6 输出缓冲

外层按 row、block、lane 顺序 `Array.push`，每个 tile 只计算一次。它没有用 `Vector.ofFn` 对每个输出重新运行 dot4。

最终通过 `out.size = batch*m*p` 的运行时检查构造 Vector；失败时返回原 `bmmSpec`。该检查只是避免掩盖尚未完成的长度证明，**不检查也不证明元素正确性**。证明接好后可以用静态长度不变量去掉此检查；本轮保留并计入调用。

## 4. 完整费用模型

对非空、n>0 的调用，令 \(F\) 为最终非有限而回退的有效输出数，\(0\le F\le O\)。候选总成本必须包含：

\[
T_{\rm call} = T_{A\rm map} + T_{B\rm pack} + T_{4\rm lane}
 + T_{\rm output/finite} + T_{\rm fallback}(F)
 + T_{\rm RC/free} + T_{\rm shape}.
\]

官方受测时间还包含输出 checksum。不能将它与孤立的 dot4 循环时间混用。公开 dense/relu/wide 生成器的输入都是有限值，raw 则包含特殊位模式；本轮没有插桩测量 F，因此表中保留条件回退成本，不把 F=0 当成测量结果。[S08]

| 项目 | 任意形状的源级次数 | 默认形状 |
| --- | ---: | ---: |
| 有效输出 | `batch*m*p` | 5,000 |
| 原始 MAC | `batch*m*n*p` | 500,000 |
| A 转换 | `batch*m*n` | 10,000 |
| B 有效值转换 | `batch*n*p` | 10,000 |
| B F4 显式构造 | `batch*G*n` | 2,600 |
| B 补零字段 | `batch*n*(4G-p)` | 400 |
| dot4 调用/终点 F4 显式构造 | `batch*m*G` | 1,300 |
| 四路循环步数 | `batch*m*G*n` | 130,000 |
| A 热读取 | 同上 | 130,000 |
| B packet 热读取 | 同上 | 130,000 |
| B scalar 字段读取 | 四倍循环步数 | 520,000 |
| 原生 mul 和 add | 各四倍循环步数 | 各 520,000 |
| packB 中除/余表达式 | `4*batch*G*n` | 10,400 |
| packB 列界判断 | `4*batch*G*n` | 10,400 |
| 输出列界判断 | `4*batch*m*G` | 5,200 |
| 有效终点 finite 判断 | `O` | 5,000 |
| 有限结果转回 Binary32 | `O-F` | 0–5,000 |
| 软件回退点积 | `F` | 0–5,000 |

这些是**源码逻辑计数**，不是机器指令计数或实际堆分配计数。编译器可能合并除余、外提不变量、消除对象或增加闭包/临时装箱，必须检查实际 C。

还需要计入以下具体成本：

1. A.map 保留原始 A 供回退时，不能假定原数组可以原位零拷贝复用。标准库 map 的实现会写数组元素，共享输入可触发 COW；此外还有指针数组构建和 RC。[S16]
2. 当前 `blocksGo` 在每块源码中仍计算 `(p+3)/4`、`row/m`、`row*n`，默认各出现 1,300 次。第一轮保留这个明确草案，不把尚未观察的循环不变量外提收益计入结果。
3. packB 的局部 read 函数、Array.ofFn/map 适配及默认值是否有残留分配，需要 C 核查。不能只数显式 `F4.mk`。
4. `exactAt` 采用原合同的 `List.finRange n` fold，回退除了 n 个软件 MAC，还有列表/Fin 构建、原索引和 total read 成本。最坏是准备与全部原生工作之后，再做 O 个完整软件点积。
5. 原始 A/B 与新缓冲同时存活，增加峰值内存；native 缓冲销毁、F4 结果释放和输出 Array 的创建都在完整调用路径上。

64 位下每个 F4 的 scalar payload 为 16 字节，另有对象头与指针槽；allocator rounding、容量和临时对象影响真实内存。报告不把这些理论字节加总冒充 RSS 测量。

## 5. 证明分解：布局、调度、数值桥分开

### 5.1 已写出的结构证明源码

`proof/ProofAppend.lean` 可拼接在候选末尾，仍只有一个 ContractTensor import。它包含完整证明体，没有证明洞；**本轮尚未 elaboration**。

| 定理/定义 | 保证 | 是否依赖浮点数学 |
| --- | --- | --- |
| `dot4_projection` | 四路递归等于四个独立 `dotLane` 的字段组合 | 否，只用 fuel 归纳 |
| `dotLane_eq_finRange` | Nat 尾递归按原顺序等于 `List.finRange` 左 fold | 否，只用索引与列表等式 |
| `totalRead_map` / `array_getD_map` | map 与 total read 交换，默认值也必须 map | 否 |
| `finish_eq_exactAt` | 在显式 sound 前提下，接纳/回退都等于原软件 dot | 数值事实由调用者提供 |
| `pushLane_size` | 有效列 push 一项，padding 不增加长度 | 否 |
| `exactAt_eq_spec` | 合法 q 上 exactAt 就是固定 bmmSpec | 定义等式 `rfl` |

四路投影定理的主体是：

```lean
dot4 A B fuel ai bi s0 s1 s2 s3 =
  ⟨dotLane F4.s0 A B fuel ai bi s0,
   dotLane F4.s1 A B fuel ai bi s1,
   dotLane F4.s2 A B fuel ai bi s2,
   dotLane F4.s3 A B fuel ai bi s3⟩
```

归纳每走一步，仅在四条独立状态上应用同一个规定的操作。这个等式不需要更改加法顺序，甚至不依赖加法具有任何代数性质。

### 5.2 尚需开发者接完的三段

**第一段：准备后的读取对应。**

对 A，需要将 `array_getD_map` 与 `toFloat32 posZero = zero32` 接上。对 B，使用 `Array.getElem_ofFn`，证明有效 b/g/k/lane 下的 div/mod 解码和索引界：

\[
((bG+g)n+k)<batch\cdot G\cdot n,
\]

以及字段对应原始 `B[(bn+k)p+4g+lane]`。这不是有限域假设；其内容只是 Nat 布局等价。padding 用显式列界分支处理。

**第二段：既有数值定理适配。**

把准备读取等价、四路投影和 finRange 顺序连接到既有开发者的 final-finite dot 定理。接受分支所需接口可以明确写成：

```lean
sound : x.isFinite = true →
  ExecFloat.Binary.ofFloat32 x = exactAt batch m n p A B q
```

附录的 `finish_eq_exactAt` 接受这个证明作为普通 theorem 参数。它不是一个未经证明的全局事实，也不是最终的无条件 `bmm_spec`。用户指定的 finite-mul、finiteRoundtrip 与逆向有限性推导仍需由真实已证明 lemma 提供。

**第三段：输出前缀。**

维护“已经追加的每个 q 都正确”以及长度不变量。处理某行前 g 个块后，该行已追加 `min(4*g,p)` 项；处理完一行恰好增加 p。用 `Array.getElem_push_lt` 保持旧前缀，用 `getElem_push_eq` 证明新末项；最终经 Vector.get 的函数外延得到 BmmObligation。[S17]

这三段尚未全写完或编译，报告不会把 projection 的完成等同于完整 bmm 证明完成。

## 6. 预期生成 C 与向量化边界

下列内容是**依据 compiler/runtime 源码画出的期望形态，不是本轮观测的生成 C**：

```c
loop(A, packedB, fuel, ai, bi, float s0, float s1, float s2, float s3) {
start:
    if (fuel == 0) return make_F4_once(s0, s1, s2, s3);
    float a = load_A_float_or_zero(A, ai);
    object *v = load_F4_or_zero(packedB, bi);
    float m0 = a * field_float(v, 0);
    float m1 = a * field_float(v, 4);
    float m2 = a * field_float(v, 8);
    float m3 = a * field_float(v, 12);
    s0 = s0 + m0;
    s1 = s1 + m1;
    s2 = s2 + m2;
    s3 = s3 + m3;
    --fuel; ++ai; ++bi;
    goto start;
}
```

实际 Nat 表示不是此示意中的裸机器整数，getD/RC 也可能保留分支与 helper。此示意只表达四个原生 scalar 参数、独立 mul/add 以及没有每步 F4 状态构造的目标。

### SLP、标量指令并行与线程不是一回事

- **SLP**：C 编译器可能把同一步四个互不依赖的乘法、四个加法打成四 lane 指令。lane 内 k 次序不变，不需要 fast-math 或归约重结合。
- **标量指令并行**：即使没有 SIMD，四条累加依赖链也可能让 CPU 重叠发射独立标量工作。它与 SLP 是两种可能的实现结果，不能把假想倍数相加。
- 本候选没有创建线程。这里的跨输出并行指机器指令层面可并行的独立状态，不是四个 OS 线程。

转换外部调用的消失、单个 B packet 的四个相邻字段，给 SLP 提供更好的局部结构；但以下项目都可能阻止或抵消收益：Nat helper、getD 分支、RC 条件、函数未内联、临时装箱、指针追踪和寄存器 spill。四个 scalar 参数也不自动保证机器寄存器常驻。

标准 Array 安全读取可以由编译器在借用分析允许时改成 borrowed primitive，省掉元素读取的 RC 增量。是否发生必须看候选 C；不得在候选中手写调用不安全借用接口。[S18]

### FMA 的实际边界

固定 Lean `src/CMakeLists.txt` 为生成 C 与 C++ 默认加入 `-ffp-contract=off`；固定比赛 lakefile 没有另加 C 优化参数，Lake release 构建列出的优化是 `-O3 -DNDEBUG`。[S19]、[S20]、[S21]

这比“写两个 let，所以一定不会 FMA”更可靠，但仍只是固定源码依据。开发者应保存实际安装环境 `lake env leanc --print-cflags`、正常 Lake 构建日志和最终机器码。发现有效输出链 FMA 或 k 重结合时必须停止，不能为取得速度修改编译参数。

## 7. 任意维度、getD 与 Nat/USize

主候选全部使用 Nat 的 fuel、维度和地址计算，因此没有 `USize.ofNat` 取模截断。零维度在准备前退出，尾块按列界裁剪，每个有效输出仍执行完整 n 次递推。

在非空路径，需证明：

\[
\begin{aligned}
b<batch,\ i<m,\ k<n&\Rightarrow(bm+i)n+k<batch\,m\,n,\\
b<batch,\ k<n,\ j<p&\Rightarrow(bn+k)p+j<batch\,n\,p.
\end{aligned}
\]

总读定义仍保留越界 +0；预转换读取使用 map 后的默认 +0，不能用未证明的默认值替换。Nat 下的大尺寸数学语义与实际内存资源不足是两件事；本轮没有宣称可以在机器上分配任意大数组。

USize 暂缓的原因是新的证明负担，而不是它不可用。以后若实际 C 表明 Nat 成本主导，可以在 **Nat 中先检查/证明**容量与所有地址界，再走 USize 快路，不满足时精确回退。`USize.toNat_ofNat_of_lt` 要求严格小于 `USize.size`；先转 USize 再检查会丢失溢出信息。[S22]

还要处理最后一次递归形成的 one-past 指针。原 stride-B 布局里，数组容量检查不一定限制 `bIndex+p`；本次 packed 布局每次 +1，让终止态界更简单，但不是自动证明。第一轮不要同时引入它。

## 8. 已执行诊断、精确反例与未执行项

### 8.1 实际运行的 Python 诊断

`diagnostics/diagnose_layout.py` 只使用 Python 标准库，以精确 dyadic 整数实现有限 binary32 RN-even；不依赖宿主 double 的累加结果来充当参考。范围为 batch 0..2、m 0..3、n 0..5、p 0..9，共 720 形状、4,860 输出；另作 10,000 个任意精度索引恒等检查，尺寸乘积可超过机器字。

值集包含 ±0、正负最小次正规、最大次正规、最小正常、±1、±0.5。所有这些有限输出与原序模型一致。诊断脚本本身是自造 oracle，**不是经过证明的 IEEE 实现，也不是 FloatLib 的执行**；它用于发现布局/次序错误，不证明全输入合同。

脚本未执行 Inf/NaN/payload 语义。原始 stdout、JSON、Python/OS 版本与 Lean/lake 缺失状态均在包内。

### 8.2 已由整数诊断复核的反例

| 错误变换 | 精确见证 | 原合同 | 错误结果 |
| --- | --- | --- | --- |
| 改变 k 归约次序 | A=`[2^24,1,-2^24]`，B 全 1 | `0x00000000` | 先抵消两大数得到 `0x3f800000` |
| 把 mul/add 收缩成 FMA | 从 +0 开始先加 -1，再做 `0x3f800001 * 0x3f7ffffe` | `0x00000000` | fused 得 `0xa8800000`，即 `-2^-46` |
| flat 四输出块跨行仍共享 A | shape `(1,2,1,3)`，A=`[1,2]`，B=`[1,1,1]` | q=3 为 2 | 复用首行 A 得 1 |
| 仅靠 flat getD 填尾零 | B 两行 `[11,12,13]`,`[21,22,23]`，p=3 | 第一行 lane3 应补 0 | 读到下一行 21；这是 padding 不变量反例，不单独宣称有效输出必错 |

### 8.3 必须加入原生逐位诊断的边界

另附 `NumericCheckAppend.lean`，包含 17 个小用例，但其编译和执行均 **NOT_RUN**。尤其应保留：

- n=1、A=-0、B=+1：必须计算 `+0 + (-0)`，不能用第一项乘积初始化而直接返回 -0。
- A=+0、B=Inf：不能因为 ReLU 零值而跳过 `0*Inf`，否则可能把应为非有限的路径误变成 finite。
- 非规范 NaN payload（如 `0x7fc12345`、`0xffa12345`）：native buffer 的规范化不能成为原始软件回退输入。
- 正负最小次正规乘 0.5、最小正常乘 0.5：检查 gradual underflow 与 RN-even。
- 乘积溢出及相反 Inf、部分 lane 异常、p=1/3/5 的尾块、batch/m/n/p 各为零。

这些用例针对具体错误，不是额外改造 benchmark。`lean --run` 的小诊断即使通过，也不替代优化 native 二进制的 raw 校验和与完整证明。

## 9. 最小编译与完整计时对照

完整逐项命令见 `RUN_REQUEST.md`；入口如下：

```bash
bash codegen/run_codegen_probe.sh \
  /absolute/competition/lean /absolute/r2w02-codegen \
  /absolute/lean-4.34.0/bin
```

脚本只接受真实已安装 4.34.0 的 bin 目录、已构建 ContractTensor 的环境；拒绝普通 elan shim 目录，不安装工具链或拉依赖，输出在外部指定目录。它发射独立小探针 C、完整候选 C，以及带结构证明的 ProofProbe。

首先审查四个 native scalar 参数、F4 字段偏移、hot loop 无转换/无每步状态构造、剩余 Nat/RC 和实际 FMA 控制。不能只根据源码中出现了四个 let 就宣布 SIMD。

完整计时应对照**同一个 final-finite 适配层的单输出原生基线**，否则减少软件浮点工作的收益会被错误归到本轮打包。在两个已经准备好的隔离 checkout 中，仅分别放入两份 `lean/work/Submission.lean`，用真实已安装的 `lake` 正常构建原 `benchBmm` target。该 target 的主程序调用 `Submission.bmm`，不依赖 `bmm_spec`；没有改动任何 benchmark、gate 或编译参数。[S27] 然后直接比较两个原 benchmark 二进制：

```bash
python3 diagnostics/compare_bench.py \
  /absolute/native1/lean/.lake/build/bin/benchBmm \
  /absolute/packed4/lean/.lake/build/bin/benchBmm \
  /absolute/r2w02-native-comparison --cpu 3
```

CPU 应选与原对照环境一致且允许使用的核心。脚本维持默认 500000 MAC、三次内部 sweep、25 个交替顺序 paired rounds；每组比较选一次 seed，逐次核对全部四类 checksum，保留 stdout/stderr 与 JSON。它执行原生完整调用，但**不是 gate，也不复现 gate 的资源隔离与统计晋升判定**。当前标记为 `UNPROVED_DIRECT_NATIVE_BENCH_DIAGNOSTIC`。需要同时保存两个 Kernel 与固定源码 hash、实际编译命令和生成 C/机器码。所有输入 map、打包、数组构建、回退、RC/释放都必须留在每次 kernel 调用内。

接齐无条件 bmm_spec 后，再走未修改的完整本地 gate。没有正式参赛上传。若只是一次 codegen 或一组未证明计时，就按其证据范围汇报。

## 10. 淘汰或推迟的路线

| 路线 | 本轮决定与理由 |
| --- | --- |
| 普通 A/B 双 `Array Float32` + 四路 | 可作诊断控制，但 B 仍有四个箱子/指针读取；主候选直接用 F4 |
| 每步以 F4 作为累加状态 | 不断言一定分配；但要依赖结构复用/标量化，先用独立参数减少不确定性 |
| 八输出 | 增加寄存器与尾部压力；在四路真实 C/计时前无依据扩大 |
| 二路专用尾块 | 能去掉默认 4% padding MAC，但会增加一条核心与证明分支；先测统一四路 |
| FloatArray binary64 容器 | 标准 FloatArray 元素是 Float；Float32/Float 转换 opaque，无现成无损往返连接可直接假用 [S23]、[S24] |
| USize 热索引 | 可做下一项有界快路；当前先闭合 Nat 布局/调度证明 |
| k 分块局部和、树归约、FMA | 直接违背硬合同，已有明确反例 |
| ReLU 零跳过 | 全输入存在 `0*Inf`/NaN 障碍；本轮不增加新准入守卫 |
| 线程任务并行 | 超出这次窄候选，会引入调度、资源和测量变量；先确认单核 ILP/SLP |

## 11. 停止条件与路线判断

推荐结论是 **“进入一次固定环境 codegen 与完整调用实测”**，不是已实现加速。

1. 若布局/投影证明或有效输出原始字比较失败，停止晋升并修复该具体缺口。
2. 若生成 C 仍在每 MAC 转换、装箱累加器或构造状态对象，先定位原因，不继续扩大路数。
3. 若有效链发生 FMA/重结合，停止；不能调整合同或编译参数来解释差异。
4. 若 codegen 形态成立，但准备、RC、内存和回退吞掉完整收益，停放此候选；不拿孤立循环时间代替。
5. 若唯一观察到的主因是 Nat 或准备端的重复除余，可做一次针对该原因的窄修复，再走相同比较；不要同时增加多个未验证机制。

四路 F4 布局的价值在于，它在现有限制内提供了一个**具体、无需改变单输出数值图、可由简单投影归纳证明的组织方式**。它也保留了明确的可证伪终点：真实 C 与包含准备的完整计时。

## 12. 文件、来源与许可

包内包含：

- `candidate/Kernel.lean`：4,525 字节的单文件 bench/codegen 候选。
- `candidate/NativePacked4.lean`：带说明的同一核心与组织；无虚构 bmm_spec。
- `proof/ProofAppend.lean`：可拼接结构证明源码，NOT_RUN。
- `codegen/`：三个极小表示对照入口及运行脚本。
- `diagnostics/`：已执行 Python 小诊断、原始 stdout/JSON、环境、计数模型、静态预检，以及未执行的 Lean 边界诊断和原 benchmark 二进制对照脚本 `compare_bench.py`。
- `RUN_REQUEST.md`：最小实际编译与完整调用对照请求。
- `sources/`：固定来源 URL、字节数、SHA256 和需要保持不变的 workspace 文件。
- `licenses/`：FloatLib MIT、Lean Apache-2.0 原许可文本。

FloatLib 固定版本是 MIT；Lean 固定版本是 Apache-2.0。[S25]、[S26] 已检查的比赛固定 tree/README 未找到明确 LICENSE/COPYING 声明，因此本包只放来源链接/hash与本轮自写候选，不重分发整个比赛源码。没有据“公开可读”擅自推定其许可证。

本报告及诊断没有读取旧会话、项目私有附件或私有源码；没有安装大型工具链、改账户、修改固定规则或进行在线参赛提交。

### 固定公开来源

[S01]: https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/contract/ContractTensor.lean
[S02]: https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/contract/Contract.lean
[S03]: https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/verify/VerifyBmm.lean
[S04]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/AddSub.lean#L241-L247
[S05]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Instances.lean#L31-L40
[S06]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Representation.lean#L49-L54
[S07]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native.lean#L115-L159
[S08]: https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/bench/BenchBmm.lean#L18-L74
[S09]: https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/gate.py
[S10]: https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/docs/BENCHMARKING.md
[S11]: https://github.com/leanprover/lean4/blob/v4.34.0/src/include/lean/lean.h#L2955-L3014
[S12]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Lean/Compiler/LCNF/ToImpureType.lean#L200-L270
[S13]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Lean/Compiler/LCNF/EmitC.lean
[S14]: https://github.com/leanprover/lean4/blob/v4.34.0/src/include/lean/lean.h#L847-L884
[S15]: https://github.com/leanprover/lean4/blob/v4.34.0/src/runtime/object.cpp#L1987-L2004
[S16]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Array/Basic.lean#L734-L755
[S17]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Array/Lemmas.lean
[S18]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Lean/Compiler/LCNF/ExplicitRC.lean#L580-L602
[S19]: https://github.com/leanprover/lean4/blob/v4.34.0/src/CMakeLists.txt#L219-L221
[S20]: https://github.com/leanprover/lean4/blob/v4.34.0/src/lake/Lake/Config/LeanConfig.lean#L116-L121
[S21]: https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/lakefile.lean
[S22]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/UInt/Lemmas.lean#L61-L64
[S23]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/FloatArray/Basic.lean#L18-L24
[S24]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Float32.lean#L540-L555
[S25]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/LICENSE
[S26]: https://github.com/leanprover/lean4/blob/v4.34.0/LICENSE
[S27]: https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/bench/MainBmm.lean

上述 source id 是本报告的 Markdown 链接标签；完整 URL/hash 映射另见包内 source_manifest.json。附录给出整份候选与结构证明源码，便于只下载 Markdown 时查看。

## 附录 A：完整候选 Kernel.lean

以下为包内原样候选，4,525 字节。未编译，没有完整 bmm_spec。

```lean
import ContractTensor

namespace R2W02

open Competition FloatLib.Floats

structure F4 where
  s0 : Float32
  s1 : Float32
  s2 : Float32
  s3 : Float32

def zero32 : Float32 := Float32.ofBits 0

def zero4 : F4 := ⟨zero32, zero32, zero32, zero32⟩

def packB (batch n p : Nat) (B : Vector Binary32 (batch * n * p)) : Array F4 :=
  let blocks := (p + 3) / 4
  Array.ofFn fun (t : Fin (batch * blocks * n)) =>
    let b := t.val / (blocks * n)
    let r := t.val % (blocks * n)
    let g := r / n
    let k := r % n
    let col := g * 4
    let base := (b * n + k) * p
    let read := fun (j : Nat) =>
      if j < p then
        ExecFloat.Binary.toFloat32 (B.toArray.getD (base + j) posZero)
      else zero32
    ⟨read col, read (col + 1), read (col + 2), read (col + 3)⟩

def dot4 (A : Array Float32) (B : Array F4) :
    (fuel aIndex bIndex : Nat) →
    (s0 s1 s2 s3 : Float32) → F4
  | 0, _, _, s0, s1, s2, s3 => ⟨s0, s1, s2, s3⟩
  | fuel + 1, aIndex, bIndex, s0, s1, s2, s3 =>
    let a := A.getD aIndex zero32
    let v := B.getD bIndex zero4
    let m0 := a * v.s0
    let m1 := a * v.s1
    let m2 := a * v.s2
    let m3 := a * v.s3
    let t0 := s0 + m0
    let t1 := s1 + m1
    let t2 := s2 + m2
    let t3 := s3 + m3
    dot4 A B fuel (aIndex + 1) (bIndex + 1) t0 t1 t2 t3

def exactAt (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (q : Nat) : Binary32 :=
  let (b, i, j) := bmmDecodeC m p q
  (List.finRange n).foldl
    (fun acc k =>
      ExecFloat.add acc
        (ExecFloat.mul
          (getD A.get (bmmAIndex m n b i k.val))
          (getD B.get (bmmBIndex n p b k.val j))))
    posZero

theorem exactAt_eq_spec (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (q : Fin (batch * m * p)) :
    exactAt batch m n p A B q.val = bmmSpec batch m n p A.get B.get q := by
  rfl

def finish (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (q : Nat) (x : Float32) : Binary32 :=
  if x.isFinite then ExecFloat.Binary.ofFloat32 x
  else exactAt batch m n p A B q

def pushLane (batch m n p row col : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (x : Float32) (out : Array Binary32) : Array Binary32 :=
  if col < p then
    out.push (finish batch m n p A B (row * p + col) x)
  else out

def blocksGo (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (nativeA : Array Float32) (packedB : Array F4)
    (row : Nat) : (fuel block : Nat) → Array Binary32 → Array Binary32
  | 0, _, out => out
  | fuel + 1, block, out =>
    let blocks := (p + 3) / 4
    let b := row / m
    let s := dot4 nativeA packedB n (row * n)
      ((b * blocks + block) * n) zero32 zero32 zero32 zero32
    let col := block * 4
    let out := pushLane batch m n p row col A B s.s0 out
    let out := pushLane batch m n p row (col + 1) A B s.s1 out
    let out := pushLane batch m n p row (col + 2) A B s.s2 out
    let out := pushLane batch m n p row (col + 3) A B s.s3 out
    blocksGo batch m n p A B nativeA packedB row fuel (block + 1) out

def rowsGo (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (nativeA : Array Float32) (packedB : Array F4) :
    (fuel row : Nat) → Array Binary32 → Array Binary32
  | 0, _, out => out
  | fuel + 1, row, out =>
    let out := blocksGo batch m n p A B nativeA packedB row ((p + 3) / 4) 0 out
    rowsGo batch m n p A B nativeA packedB fuel (row + 1) out

def bmmDraft (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if batch * m * p = 0 then Vector.replicate (batch * m * p) posZero
  else if n = 0 then Vector.replicate (batch * m * p) posZero
  else
    let nativeA := A.toArray.map ExecFloat.Binary.toFloat32
    let packedB := packB batch n p B
    let out := rowsGo batch m n p A B nativeA packedB
      (batch * m) 0 (Array.emptyWithCapacity (batch * m * p))
    if h : out.size = batch * m * p then ⟨out, h⟩
    else Vector.ofFn (bmmSpec batch m n p A.get B.get)

end R2W02

namespace Submission

open Competition FloatLib.Floats

def bmm (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  R2W02.bmmDraft batch m n p A B

end Submission
```

## 附录 B：完整结构证明附录

将下列内容拼到候选末尾可供单独 elaboration。它没有 import 或证明占位；`finish_eq_exactAt` 的 sound 是调用者仍须证明的显式前提。编译状态为 NOT_RUN，不可据此宣称完整合同已证。

```lean
/-!
Append this file after NativePacked4.lean, preserving its only import,
`import ContractTensor`.  It is a source-level proof draft, NOT_RUN: this
environment has no Lean executable.  No claim of elaboration or gate success
is made.  These lemmas prove scheduling/structural facts only; they do not
silently assume the finite-result arithmetic bridge has been integrated.
-/

namespace R2W02

open Competition FloatLib.Floats

/-- A single component of exactly the same packed traversal as dot4. -/
def dotLane (pick : F4 → Float32) (A : Array Float32) (B : Array F4) :
    (fuel aIndex bIndex : Nat) → Float32 → Float32
  | 0, _, _, s => s
  | fuel + 1, aIndex, bIndex, s =>
    dotLane pick A B fuel (aIndex + 1) (bIndex + 1)
      (s + A.getD aIndex zero32 * pick (B.getD bIndex zero4))

/-- Projection uses only induction and definitional equality.
    No associative law and no floating-point theorem occurs here. -/
theorem dot4_projection (A : Array Float32) (B : Array F4)
    (fuel aIndex bIndex : Nat) (s0 s1 s2 s3 : Float32) :
    dot4 A B fuel aIndex bIndex s0 s1 s2 s3 =
      ⟨dotLane F4.s0 A B fuel aIndex bIndex s0,
       dotLane F4.s1 A B fuel aIndex bIndex s1,
       dotLane F4.s2 A B fuel aIndex bIndex s2,
       dotLane F4.s3 A B fuel aIndex bIndex s3⟩ := by
  induction fuel generalizing aIndex bIndex s0 s1 s2 s3 with
  | zero => rfl
  | succ fuel ih =>
      simpa only [dot4, dotLane] using
        ih (aIndex + 1) (bIndex + 1)
          (s0 + A.getD aIndex zero32 * (B.getD bIndex zero4).s0)
          (s1 + A.getD aIndex zero32 * (B.getD bIndex zero4).s1)
          (s2 + A.getD aIndex zero32 * (B.getD bIndex zero4).s2)
          (s3 + A.getD aIndex zero32 * (B.getD bIndex zero4).s3)

/-- The Nat tail recursion has exactly ContractTensor's increasing Fin order. -/
theorem dotLane_eq_finRange (pick : F4 → Float32)
    (A : Array Float32) (B : Array F4)
    (fuel aIndex bIndex : Nat) (s : Float32) :
    dotLane pick A B fuel aIndex bIndex s =
      (List.finRange fuel).foldl
        (fun acc k => acc +
          A.getD (aIndex + k.val) zero32 *
          pick (B.getD (bIndex + k.val) zero4)) s := by
  induction fuel generalizing aIndex bIndex s with
  | zero => simp [dotLane]
  | succ fuel ih =>
      simp only [dotLane, List.finRange_succ,
        List.foldl_cons, List.foldl_map]
      rw [ih]
      simp only [Fin.val_zero, Fin.val_succ, Nat.add_zero]
      congr 1
      funext acc k
      have ha : aIndex + 1 + k.val = aIndex + (k.val + 1) := by omega
      have hb : bIndex + 1 + k.val = bIndex + (k.val + 1) := by omega
      rw [ha, hb]

/-- Total reads commute with a map only when the default is mapped as well.
    This lemma is independent of floating-point representation. -/
def totalRead {α : Type} {n : Nat}
    (v : Fin n → α) (default : α) (i : Nat) : α :=
  if h : i < n then v ⟨i, h⟩ else default

theorem totalRead_map {α β : Type} {n : Nat}
    (f : α → β) (v : Fin n → α) (default : α) (i : Nat) :
    totalRead (fun j => f (v j)) (f default) i =
      f (totalRead v default i) := by
  unfold totalRead
  split <;> rfl

/-- Concrete Array form, using lemmas present in Lean v4.34.0. -/
theorem array_getD_map {α β : Type}
    (f : α → β) (xs : Array α) (default : α) (i : Nat) :
    (xs.map f).getD i (f default) = f (xs.getD i default) := by
  simp only [Array.getD_eq_getD_getElem?, Array.getElem?_map]
  cases xs[i]? <;> rfl

/-- Explicit theorem interface, not an axiom: the caller must supply `sound`.
    The executable fallback is in the else branch, so it is not eager. -/
theorem finish_eq_exactAt (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (q : Nat) (x : Float32)
    (sound : x.isFinite = true →
      ExecFloat.Binary.ofFloat32 x = exactAt batch m n p A B q) :
    finish batch m n p A B q x = exactAt batch m n p A B q := by
  unfold finish
  split
  · exact sound ‹x.isFinite = true›
  · rfl

theorem pushLane_size (batch m n p row col : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (x : Float32) (out : Array Binary32) :
    (pushLane batch m n p row col A B x out).size =
      out.size + (if col < p then 1 else 0) := by
  unfold pushLane
  split <;> simp_all

end R2W02
```
