# FloatLib R4-W01：2 行 × 4 列微块反方审查与地址证明

日期：2026-10-22。范围仅为给定 2×4 组织的独立审查、Nat 地址辅助证明和完整调用否决请求。

## 1. 结论与适用状态

**所述组织可以保持全输入逐位合同。奇数 m 的未观察第二行读到下一 batch 的非零、Inf 或 NaN，并不自动污染有效输出。** 成立的关键是八条累加链逐步独立、输出 lane 解码正确，以及每个被输出的 lane 使用自己的 final-finite 接纳证据和原始输入回退。新 2×4 实现源文件未提供，因此这是对精确定义的组织的条件性审查结论，不是对某个新候选的编译或 gate 认证。

另一个确定结论是：**奇数 m、最后 batch 的尾行对，其第二条流起点恰为 A.size；按“两条流完整 span 都通过”的准入规则，该 tile 必须回到 Nat getD 循环。** 不能用第一行有效来证明第二行有效，也不能用未观察这一事实替代实际读取的边界证明。

| 项目 | 本轮状态 |
| --- | --- |
| 公开父本下载、字节数、SHA256 | 已核对，匹配用户给定 SHA |
| 父本相关定义和固定 Nat/Array/Vector API | 已实际阅读 |
| 完整地址辅助文件 | 已给出 20 个带证明体的定理，124 行、4693 字节 |
| 官方词法规则对辅助源码的扫描 | 已执行，含注释，零命中；不等于官方完整 gate |
| 数学计数 | 已复核，并执行 Python 整数计算；原始 JSON 随包 |
| Lean elaboration、内核验证、公理检查 | **NOT_RUN**：本机没有 lean/lake/elan，未安装工具链 |
| 新 2×4 全候选、原生执行、性能测量 | **NOT_RUN**；未实现热循环，未改 bench、编译参数或环境 |
| 反例输入 | 17 个解析见证；**ANALYTICAL_NOT_RUN**，不是实跑失败记录 |
| 父本两次完整 gate | 用户给定反馈，本轮未访问 CI 或账户核实 |

固定父本实际解析到公开 commit `1a2b072ef6efa83c7413624b83241e0f5fa87c00`，文件为 125837 字节，SHA256：

```text
6744be2bd784bea7a7e347d68f813bc865d2d18abab87f19fa37aec8a8c2c1f7
```

本轮实际阅读了 [该父本](https://github.com/HuanHuanHuanFFF/Miner/blob/1a2b072ef6efa83c7413624b83241e0f5fa87c00/competitions/floatlib/candidates/f01-d3-final-package/Kernel.lean) 的 `Packed8.finish`、`Packed8Index.loop/loop_eq/within/within_eq/runDot`、`tileResults`、输出构造和最外层 `bmm`。父本的非finite `finish` 用原始 Binary32 A/B 进行有序回退；原生准备缓冲不能替代这一来源。包内记录了精确来源和许可，不复制 125 KB 父本。

## 2. 为什么未观察行可以任意，而不是必须为零

令 `s[r,l](k)` 表示完成前 k 项后的状态，r∈{0,1}、l∈{0,1,2,3}。要求的单步关系是：

\[
s_{r,l}(0)=+0,\qquad
s_{r,l}(k+1)=\operatorname{add32}\bigl(s_{r,l}(k),
\operatorname{mul32}(a_r(k),v_l(k))\bigr).
\]

这里 add32、mul32 是两次独立 RN32 运算。每个右侧只读取自己的旧状态、自己的 A 行和对应 B 字段；对 k 归纳，任意选定 lane 的状态就是对应原生标量有序链。该投影等式不要求其他 lane finite，也不要求未观察 A 行为 +0。它只是在原生链之间投影；原生链到原始 Binary32 合同的桥仍由所选输出自己的 final-finite 证明或精确回退承担。

这一推理依赖以下可检查条件，正确实现应在定义和证明内部满足它们，不能把它们添加成最终 `bmm_spec` 的外部前提：

1. 八个初值都是精确 +0，每条更新只使用该条自己的旧状态。顺序写出的 let 或递归参数不能误用另一条已更新状态。
2. k 严格递增，先乘再加；不能首项播种、FMA、重结合或无条件跳零。
3. B 的有效 lane 是同一 batch 的原始列，地址为 `(b*n+k)*p+4*g+l`；列越界填充 +0，但填充 lane 从不作为合法列输出。
4. 合法输出选择 `h=i/2`、`r=i%2`、`g=j/4`、`l=j%4`，F8 lane 是 **`4*r+l`**。
5. 只对选中的合法结果进行最终接纳或回退；回退读取原始 `A[(b*m+i)*n+k]` 和 `B[(b*n+k)*p+j]`。
6. word 快路与 Nat 路径逐步相等；准入失败后执行同一 Nat getD 链，不能使用已回卷地址伪造准入。

特别要区分两种共享判定：若“任一 lane 非finite”只是让所有有效输出分别执行正确的 raw 回退，仍可正确，只会额外回退；若“任一 lane finite”被用来接纳其他非finite lane，则不能调用针对那些结果的有限值桥。不能把保守共享回退一概报告成语义错误。

### 2.1 跨 batch 尾行的精确地址

当 `2*h+1=m`，

\[
\text{base1}=(b m+2h)n+n=(b+1)mn.
\]

因此，`b+1<batch` 时未观察的第二流就是下一 batch 的第一行，完整 span 可在整个 A 数组内。它使用的 B 仍属于当前 b，所以不能把这条未观察链当成下一 batch 的真实输出。`b+1=batch` 时 `base1=A.size`，所有 `base1+k` 均越界，Nat getD 返回 +0，且严格完整 span 检查必失败。

最小非干扰见证：shape `(batch,m,n,p)=(2,1,1,1)`，A=`[1,+Inf]`、B=`[+0,1]`。合法结果是 `[+0,+Inf]`；第一个 tile 的未观察第二行算出 `Inf*0` 的 NaN，不应改变第一个合法 +0。另一个见证 A=`[1,+Inf]`、B=`[1,1]` 中，未观察有效列为 Inf、填充列可为 NaN，合法首项仍为 1。这些是解析预期，尚未运行新候选。

### 2.2 尾列与符号零

合法 `j<p` 时，`j=4*(j/4)+j%4`，故选中的 B 字段不是填充列。填充列上的 `Inf*+0` 可以产生 NaN，只要该 lane 不参与有效输出的计算或错误接纳，就不构成污染。

零必须按位处理。例如 n=1、A=`[-0]`、B=`[1]`：乘积为 -0，但规定的第一次加法是 `+0 + -0`，结果为 +0。将首项乘积直接作为累加器会得到 -0；最终 finite 检查不会纠正这个错误。

## 3. 针对具体错误改动的最小反例

下面的“错误”均指明了一个具体改动；没有声称用户正在写的实现已经包含它们。shape 均按 `(batch,m,n,p)`，输入和输出均为行主序。

| 错误改动 | 最小输入 | 合同结果 | 可识别的错误 |
| --- | --- | --- | --- |
| r=1 仍选择第一行的 lane l | `(1,2,1,1)`，A=[1,2]，B=[3] | [3,6] | 第二项成为 3；应选择 4+l |
| 用补齐后的行数做 A 的 batch stride：`(b*ceil(m/2)+h)*2*n` | `(2,1,1,1)`，A=[1,2]，B=[3,5] | [3,10] | 第二 batch 从 A[2] 开始，getD 得 +0 |
| 将未观察跨 batch 行结果复用成下一 batch 输出 | 同上 | [3,10] | 前一 tile 的未观察值为 2×3=6，下一 batch 应为 2×5=10 |
| 第二行 raw 回退误用 base0 | `(1,2,1,1)`，A=[1,+Inf]，B=[+0] | [+0,NaN] | 第二项错误读取第一行而得到 +0 |
| raw 回退列基址遗漏 l | `(1,1,1,2)`，A=[+Inf]，B=[1,+0] | [+Inf,NaN] | 第二项错误变成 +Inf |
| 保留旧 `j/8` 列块索引 | `(1,1,1,5)`，A=[1]，B=[1,2,3,4,5] | 第五项 5 | 若仍取块 0、lane 0，得到 1 |
| 原始 B 的 k 步长写成 4 | `(1,1,2,1)`，A=[1,1]，B=[1,2] | 3 | 原始 getD(0)、getD(4) 得到 1 |
| 首项乘积直接播种 | `(1,1,1,1)`，A=[-0]，B=[1] | +0，位型 `00000000` | -0，位型 `80000000` |
| 看到 A 为零就跳过乘法 | `(1,1,1,1)`，A=[+0]，B=[+Inf] | NaN | +0 |

`diagnostics/witnesses.json` 还包含禁止 FMA/重结合的解析见证、最小正次正规 `00000001` 乘 1，以及 `7fc12345`、`7f812345`、`ffc54321` 三个 NaN 原始输入。非 NaN 解析结果给出完整十六进制位型。**NaN 的完整期望位型必须由固定原始软件参考产生**，本包没有猜测 payload 传播、NaN 规范化结果或用“所有 NaN 相等”替代按位检查。

### 3.1 机器字准入不能比较回卷后的 span

所有 base、末地址和数组长度关系必须先在 Nat 中成立，再使用已证明无回卷的转换。设 `W=USize.size`，取 `batch=m=1`、`n=W/2+1`，则 `A.size=n<W`，未观察第二流 `base1=n`，原末地址 `2*n-1=W+1` 越界；如果先做机器字加法再比较，回卷后的 1 反而小于 A.size。此为错误准入方式的数学反例，不是对当前明确使用 Nat 完整 span 的组织的反例，也没有分配或运行该巨大数组。

空输出和 n=0 必须继续在准备前回参考。比如 `(0,1,2^128+123,1)` 的 A、B、输出都为空；n 超过任何普通机器字不影响该合法 Nat 输入。不能先截断 n 再把它误判为可用的非空问题。`(1,1,0,1)` 则有一个输出，正确值是初始 +0。

## 4. Lean 辅助片段与证明分解

完整原件是 `RowPairBounds.lean`，唯一导入 `ContractTensor`，命名空间 `Submission.RowPairBounds`。它只含命题与证明；不增加运行时条件、热循环、数组构造或数值桥。

| 定理组 | 可直接复用的结论 |
| --- | --- |
| `pair_index_lt`、`row_decomposition` | `i<m` 给出合法行对，且 `2*(i/2)+i%2=i` |
| `selected_base`、`second_base` | 选中行地址与原始行地址相同；第二流是下一行 |
| `row_lt`、`row_end_le` | 扁平行号小于 batch*m；排他行末不超过总长度 |
| `point_bound`、`row_span` | 有效 k 的地址界；n>0 时完整 span 界 |
| `row0_point/span`、`row1_point/span` | 两种真实有效行各自的点界和完整行界 |
| `selected_point/span` | 直接从合法输出行 i 获得所选流的地址界 |
| `pair_first_valid`、`pair_second_cases` | 合法 h 的第一行有效；第二行有效或恰在边界 m |
| `tail_second_base`、`tail_next_span` | 尾流的跨 batch 地址和非最后 batch 的全 span |
| `tail_last_point_outside`、`tail_last_span_fails` | 最后 batch 的尾流越界、完整 span 必不成立 |

变量乘法没有整体交给 omega。关键链条为：

\[
bm+i<bm+m=(b+1)m\le batch\cdot m,
\]

再用 `Nat.mul_le_mul_right n` 将 `bm+i+1≤batch*m` 乘 n，得到整行排他端点上界；最后由 `k<n` 或 `n-1<n` 得到严格地址界。

已核对 [Lean v4.34.0 Nat.Basic](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Nat/Basic.lean) 的实际接口：

```lean
Nat.add_lt_add_left {n m : Nat} (h : n < m) (k : Nat)
Nat.mul_le_mul_right {n m : Nat} (k : Nat) (h : n ≤ m)
Nat.add_mul (n m k : Nat)
Nat.one_mul (n : Nat)
```

omega 只负责常数 2 的除余数、线性比较和 `n-1<n`。`row_end_le` 不需要 n>0；`row_span` 的 n>0 只属于非空快路内的局部前提。n=0 时没有 k<n；m=0 或 batch=0 时没有相应合法 Fin 索引。因而这些辅助定理不需要缩小最终 bmm 的任意 Nat 域。

### 4.1 nativeA 长度的接线方式

附带 `IntegrationExamples.inc.lean`，追加在辅助文件后即可作为独立最小 elaboration 请求。示例以一般映射函数写成，避免依赖正在开发的命名空间：

```lean
example {α β : Type} {batch m n b i : Nat}
    (A : Vector α (batch * m * n)) (toNative : α → β)
    (hb : b < batch) (hi : i < m) (hn : 0 < n) :
    (b * m + 2 * (i / 2)) * n + (i % 2) * n + (n - 1) <
      (A.toArray.map toNative).size := by
  simpa only [Array.size_map, Vector.size_toArray] using
    (Submission.RowPairBounds.selected_span (n := n) hb hi hn)
```

这两条真实长度接口分别来自 [Array.Lemmas](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Array/Lemmas.lean) 和 [Vector.Basic](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Vector/Basic.lean)。第二个完整示例处理 `2*h+1<m` 时第二流的映射数组界。不会由该前提证明不存在的尾行；尾行必须按 `pair_second_cases` 分情况使用后续定理或保留原 Nat 路径。

### 4.2 这份证明的明确边界

这些是地址命题的完整证明脚本，没有占位体；**尚未经过 Lean elaboration 与内核检查，因此不能称为已编译定理**。本机也没有实际 Lean 未解目标输出可报告，不能凭空捏造错误日志。

它不重写 `within`，不新增全局 guard8，不涉及 k 双步展开，也不声称已证明新 2×4 的 `dot_projection`、packB 有效 lane 值、tileResults/get、输出选择、final-finite 桥或最终 `bmm_spec`。这些仍应在开发者完整候选中连接；本片段提供其中可复用的外围 Nat 地址部分，且未把缺失连接包装成额外 sound 前提。

## 5. 默认形状的源码计数

令 `G8=(p+7)/8`，`H2=(m+1)/2`，`G4=(p+3)/4`。块数分别为 `T8=batch*m*G8`、`T24=batch*H2*G4`；每块执行 n 次 k 迭代。

对默认 `(2,50,100,50)`，`G8=7`、`H2=25`、`G4=13`：

| 项目 | 1×8 起点 | 2×4 提案 |
| --- | ---: | ---: |
| 有效输出 | 5000 | 5000 |
| 有效 MAC | 500000 | 500000 |
| 结果 F8 块 | 700 | 650 |
| k 迭代 | 70000 | 65000 |
| 含填充 MAC | 560000 | 520000 |
| A 元素读取 | 70000 | 130000 |
| B 包读取 | 70000 | 65000 |
| 每个不同 B 字段每轮取一次 | 560000 | 260000 |
| B 缓存对象 | 1400 个 F8 | 2600 个 F4 |
| B 缓存标量字段 | 11200 | 10400 |
| B 填充字段 | 1200 | 400 |
| 结果缓存标量槽 | 5600 | 5200 |
| A 有效输入转换 | 10000 | 10000 |
| B 有效输入转换 | 10000 | 10000 |
| 准备阶段有效转换合计 | 20000 | 20000 |

用户给定计数全部成立。默认 m 为偶数，2×4 额外 20000 MAC 来自尾列；一般奇数 m 时还会计算未观察的第二行，必须用 `batch*ceil(m/2)*ceil(p/4)*n*8` 计含填充 MAC。

**260000 是四个不同 B 字段每轮取一次并供两行复用的需求数。** 若两行更新表达式各自重复写四个投影，则有 520000 个源码投影表达式。编译器是否消除重复投影、保留寄存器值以及实际 load 数，均未观测。该数字不能冒充机器内存读取次数。

减少的 MAC、B 字段与包访问要和以下增加费用一起看：

- A 读取由 70000 增为 130000，涉及两条 A 地址流和更多元素取得/解包需求；不能假定每次都新增一对引用计数增减，借用及优化行为尚未观察。
- B 对象从 1400 个 F8 增为 2600 个 F4，而字段总数从 11200 降为 10400；对象头、容器指针槽、构造与回收费用可能抵消字段节省，不能直接据此计算总字节盈亏。
- 结果 F8 块从 700 降为 650，但仍要输出 5000 个合法值。输出还需 `i/2`、`i%2` 和 `4*r+l`；列除余数也从 8 换到 4。源码没有给出这些选择、除余数和公共表达式最终如何生成的证据。
- 20000 只表示准备阶段的有效输入转换。final-finite 失败后的原始逐输出回退是额外完整调用费用。

本轮没有 C、汇编、硬件计数或计时结果，不预测加速倍数。

## 6. 最小集成与完整调用否决请求

### 6.1 先编译地址片段

在已经配置好的固定官方 Lean 工作区运行，保持原 toolchain、依赖与参数：

```bash
lake env lean /absolute/path/FloatLib_R4-W01/RowPairBounds.lean
```

若要同时检查两个接线示例，可将文件拼接到临时诊断文件后执行：

```bash
cat /absolute/path/FloatLib_R4-W01/RowPairBounds.lean /absolute/path/FloatLib_R4-W01/IntegrationExamples.inc.lean > /tmp/R4W01AddressExamples.lean
lake env lean /tmp/R4W01AddressExamples.lean
```

另有 `diagnostics/AddressChecks.inc.lean`，仅包含对 20 个定理的公理打印请求；同样追加到临时诊断文件后运行。它不能拼入候选 Kernel。应确认公理集合只在允许的 `propext`、`Classical.choice`、`Quot.sound` 内。源码本身唯一 import 和官方词法扫描结果已经保存，但这些不能替代实际 Lean 检查。

集成至真实候选时，将辅助 namespace 放进已有单一 Kernel，保留唯一 `import ContractTensor` 和原许可头；不用把本文件变成新依赖。根据合法输出的 `b.isLt`、`i.isLt`，直接使用 `selected_base/selected_point/selected_span`；两条真实有效流使用 `row0_*`、`row1_*`。奇数尾行则保留当前准入失败后的 Nat 路径。这里不给循环补丁，也不改变现有数值证明。

### 6.2 一组足以早期否决的完整调用检查

冻结新候选 SHA，先跑不变的官方 gate/原 raw 校验。再将包内见证交给现有完整调用测试入口，与固定原始软件参考比较所有 32 位；无需新建性能脚本或修改官方 bench。

最低限度需要覆盖：

1. `(2,1,1,1)`，同时触达跨 batch 未观察流与最后 batch 越界流，使用 P2 的 A=[1,Inf]、B=[0,1]。
2. `(2,3,2,5)`，真实行列赋不同值，覆盖两组实际行、奇数尾行、尾列、k 最后一步与所有合法 lane 解码。避免全相等输入掩盖索引错误。
3. 包内错误 lane、batch stride、错误 raw 回退行/列、符号零、NaN 原始位型与次正规见证。
4. 空输出各来源和 n=0；巨大 Nat 空形状不分配非空巨型矩阵。
5. 独立性变形：只改变下一 batch 首行 A，依次放有限非零、Inf、带 payload NaN、±0、次正规；前一 batch 奇数尾行的合法输出必须不变，下一 batch 的真实输出仍逐位对照参考。这是局部非干扰，不是宣称整个 bmm 对该 A 行不敏感。

任一合法输出位型不符、任一证明/政策/既有 gate 失败，足以停止该版本。若源码实际上为每个输出重复算四路或八路点积，或遗漏准备、转换、缓冲构造/释放、输出和回退成本，也不接受该版本的性能结论。

若正确性已经通过，只用既有完整调用 runner 做最小 **起点 A → 新候选 B → 起点 A** 对照，保留 dense、relu、wide 三域、原汇总规则、精确构建 SHA 和原始时间。完整调用包括上述全部费用；默认 ns/MAC 分母固定为 **500000 个有效 MAC**，不能改用 520000 或 560000 个含填充 MAC。

如果 B 在全部默认域都被前后两次 A 支配、差距也超过同轮 A 的漂移，就有充分的早期否决理由。若差异处于噪声内，这一轮不足以宣布加速或冠军；按现有验收流程处理，不另造统计门槛。没有请求新 C 性能实验，也不要求停止开发者正在进行的独立编译与实测。

## 7. 包内容、来源与许可

主要原件：`RowPairBounds.lean`、`IntegrationExamples.inc.lean`、本报告、独立审查笔记、17 个完整调用解析见证、整数计数结果、环境和静态扫描记录，以及固定源清单与 SHA256SUMS。完整地址源码也附在报告末尾。

固定环境是 Lean v4.34.0、[FloatLib 0d91825727839f597fd06b22fdd038ea21480f0c](https://github.com/lean-dojo/FloatLib/tree/0d91825727839f597fd06b22fdd038ea21480f0c)、[官方 978cc5b445edb9943fd9953b0a9037d97a9f33a8](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/tree/978cc5b445edb9943fd9953b0a9037d97a9f33a8)。本轮没有重新下载整个 FloatLib 或安装工具链。仅使用本消息、会话给定合同与公开来源。

父本头部已有 Conjectures.io、FloatLib、TorchLean 的 MIT 通知，随包逐字保留；Lean API 源文件头为 Apache 2.0，本包没有分发其实现源码。新增材料的 MIT 授权单独列出，不改变上游许可。完整链接和已读范围见 `sources/SOURCES_AND_LICENSES.md`。

## 附录：完整 RowPairBounds.lean

以下代码与独立原件逐字一致，状态仍为 **NOT_RUN**。

```lean
import ContractTensor

namespace Submission.RowPairBounds

/-- Every valid row selects a valid row pair. -/
theorem pair_index_lt {m i : Nat} (hi : i < m) :
    i / 2 < (m + 1) / 2 := by
  omega

theorem row_decomposition (i : Nat) : 2 * (i / 2) + i % 2 = i := by
  omega

/-- Selecting one row of a pair recovers the original matrix row address. -/
theorem selected_base (b m n i : Nat) :
    (b * m + 2 * (i / 2)) * n + (i % 2) * n = (b * m + i) * n := by
  rw [← Nat.add_mul, Nat.add_assoc, row_decomposition]

/-- The second stream starts at the next row. -/
theorem second_base (b m n h : Nat) :
    (b * m + 2 * h) * n + n = (b * m + (2 * h + 1)) * n := by
  simp only [Nat.add_mul, Nat.one_mul, Nat.add_assoc]

theorem row_lt {batch m b i : Nat} (hb : b < batch) (hi : i < m) :
    b * m + i < batch * m := by
  calc
    b * m + i < b * m + m := Nat.add_lt_add_left hi (b * m)
    _ = (b + 1) * m := by simp only [Nat.add_mul, Nat.one_mul]
    _ ≤ batch * m := Nat.mul_le_mul_right m (by omega)

/-- The exclusive end of a valid row does not exceed the input length. -/
theorem row_end_le {batch m n b i : Nat} (hb : b < batch) (hi : i < m) :
    (b * m + i) * n + n ≤ batch * m * n := by
  have hr := row_lt hb hi
  calc
    (b * m + i) * n + n = (b * m + i + 1) * n := by
      simp only [Nat.add_mul, Nat.one_mul]
    _ ≤ batch * m * n := Nat.mul_le_mul_right n (by omega)

theorem point_bound {batch m n b i k : Nat}
    (hb : b < batch) (hi : i < m) (hk : k < n) :
    (b * m + i) * n + k < batch * m * n := by
  calc
    (b * m + i) * n + k < (b * m + i) * n + n :=
      Nat.add_lt_add_left hk ((b * m + i) * n)
    _ ≤ batch * m * n := row_end_le hb hi

theorem row_span {batch m n b i : Nat}
    (hb : b < batch) (hi : i < m) (hn : 0 < n) :
    (b * m + i) * n + (n - 1) < batch * m * n := by
  exact point_bound hb hi (by omega)

theorem row0_point {batch m n b h k : Nat}
    (hb : b < batch) (hrow : 2 * h < m) (hk : k < n) :
    (b * m + 2 * h) * n + k < batch * m * n := by
  exact point_bound hb hrow hk

theorem row0_span {batch m n b h : Nat}
    (hb : b < batch) (hrow : 2 * h < m) (hn : 0 < n) :
    (b * m + 2 * h) * n + (n - 1) < batch * m * n := by
  exact row_span hb hrow hn

theorem row1_point {batch m n b h k : Nat}
    (hb : b < batch) (hrow : 2 * h + 1 < m) (hk : k < n) :
    (b * m + 2 * h) * n + n + k < batch * m * n := by
  rw [second_base]
  exact point_bound hb hrow hk

theorem row1_span {batch m n b h : Nat}
    (hb : b < batch) (hrow : 2 * h + 1 < m) (hn : 0 < n) :
    (b * m + 2 * h) * n + n + (n - 1) < batch * m * n := by
  rw [second_base]
  exact row_span hb hrow hn

theorem selected_point {batch m n b i k : Nat}
    (hb : b < batch) (hi : i < m) (hk : k < n) :
    (b * m + 2 * (i / 2)) * n + (i % 2) * n + k < batch * m * n := by
  rw [selected_base]
  exact point_bound hb hi hk

theorem selected_span {batch m n b i : Nat}
    (hb : b < batch) (hi : i < m) (hn : 0 < n) :
    (b * m + 2 * (i / 2)) * n + (i % 2) * n + (n - 1) < batch * m * n := by
  rw [selected_base]
  exact row_span hb hi hn

theorem pair_first_valid {m h : Nat} (hh : h < (m + 1) / 2) :
    2 * h < m := by
  omega

/-- A row pair's second row is either valid or exactly the matrix row boundary. -/
theorem pair_second_cases {m h : Nat} (hh : h < (m + 1) / 2) :
    2 * h + 1 < m ∨ 2 * h + 1 = m := by
  have hfirst := pair_first_valid hh
  omega

/-- An unobserved tail stream starts at the next batch boundary. -/
theorem tail_second_base (b m n h : Nat) (htail : 2 * h + 1 = m) :
    (b * m + 2 * h) * n + n = (b + 1) * m * n := by
  rw [second_base, htail]
  simp only [Nat.add_mul, Nat.one_mul]

/-- Before the last batch, the tail stream is the next batch's first valid row. -/
theorem tail_next_span {batch m n b h : Nat}
    (hnext : b + 1 < batch) (htail : 2 * h + 1 = m) (hn : 0 < n) :
    (b * m + 2 * h) * n + n + (n - 1) < batch * m * n := by
  rw [tail_second_base b m n h htail]
  have hm : 0 < m := by omega
  simpa only [Nat.add_zero] using (row_span (i := 0) hnext hm hn)

/-- In the final batch, every tail-stream address is outside the whole input. -/
theorem tail_last_point_outside {batch m n b h k : Nat}
    (hlast : b + 1 = batch) (htail : 2 * h + 1 = m) :
    batch * m * n ≤ (b * m + 2 * h) * n + n + k := by
  rw [tail_second_base b m n h htail, hlast]
  omega

/-- The final unobserved stream cannot meet a strict full-span admission test. -/
theorem tail_last_span_fails {batch m n b h : Nat}
    (hlast : b + 1 = batch) (htail : 2 * h + 1 = m) :
    ¬ (b * m + 2 * h) * n + n + (n - 1) < batch * m * n := by
  have ho := tail_last_point_outside (n := n) (k := n - 1) hlast htail
  omega

end Submission.RowPairBounds
```
