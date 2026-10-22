# FloatLib R5-W01：Packed10 行序输出构造与精确等价证明

日期：2026-10-22。固定 Lean v4.34.0、FloatLib `0d91825727839f597fd06b22fdd038ea21480f0c`、官方 `978cc5b445edb9943fd9953b0a9037d97a9f33a8`。

## 1. 已交付什么，哪些仍未编译

本轮只交一条路线：**每 batch 按行构造 p 个输出，先展平为该 batch 的 m*p 个值，再展平 batch，保持原 batch/row/column 顺序。** 原有十路 dot、USize 热循环、输入转换、packB、tileResults、数值解码和 final-finite/raw 回退全部复用。

主片段 `OutputRows.inc.lean` 为 **134 行、5143 字节，6 个定义、8 条带完整证明体的定理**。其中 `outputRows_eq` 对任意给定 tiles 证明整个结果向量等于旧 `Vector.ofFn (Packed10.outputFromTiles ...)`；后续证明接回父本 `core_eq_reference` 和 `referenceBmm_spec`，得到无条件的 `bmmRows_spec`。没有把正确性作为参数，也没有用长度等式代替元素等式。

**所有 Lean elaboration、内核验证、公理检查、完整 gate、新候选执行与计时均为 NOT_RUN。** 本机 PATH 中无 lean/lake/elan，未安装工具链。源码和证明已经写全，经过独立静态审阅；没有实际 Lean 错误日志，不能把静态可闭合写成编译通过。

| 项目 | 本轮证据 |
| --- | --- |
| 固定公开父本 | 实际下载，132965 字节，SHA 完全匹配 |
| 固定 Vector/Array API | 实际阅读定义与索引定理 |
| 通用矩形引理和具体接线 | 完整脚本；独立静态审阅未发现具体阻断 |
| 两种源码拼接模式 | 实际生成并校验，只涉及同一条实现路线 |
| 激活后的单文件 | 138209 字节，唯一 `import ContractTensor`，低于 256000 字节 |
| 固定官方禁词正则扫描 | 对片段及两份组合源码执行，含注释零命中 |
| 原父本其他内容保留 | 拼接脚本反向还原并比对父本全部字节 |
| 完整调用数值与性能 | NOT_RUN；没有 C surrogate 或热循环实验 |

已核对的[公开父本](https://github.com/HuanHuanHuanFFF/Miner/blob/e5b144bf77d477919f4787e36311cf65d2a23c15/competitions/floatlib/candidates/f01-d4-final-lowmul/Kernel.lean)为：

```text
commit e5b144bf77d477919f4787e36311cf65d2a23c15
bytes  132965
sha256 ba93c233f87935aaadb9ec697487b316d4538d014831ee8d6e00127d6c34f630
```

父本“三次完整 gate 通过”来自用户给定反馈，本轮未访问 CI、账户、私有会话或附件。

## 2. 唯一实现路线：让行闭包持有地址与 tiles

输出构造器的计算放置如下：

1. 整个输出阶段绑定 `Araw=A.toArray`、`Braw=B.toArray`。
2. 每 batch 绑定 `batchTiles=tiles.get b`、`aBatch=b*m`、`bBatch=b*n*p`。
3. 每行绑定 `rowTiles=batchTiles.get i`、`baseA=(aBatch+i)*n`。
4. 列闭包仅做 `g=j/10`、`l=j%10`、`rowTiles.get g`、lane 选择和原 `Packed10.finish`，B 回退基址仍是 `bBatch+j`。
5. 每 batch 将行向量展平，外层再将 batch 向量展平；最后用 `Nat.mul_assoc` 的证明把长度 `batch*(m*p)` 转为 `(batch*m)*p`。

关键代码如下，完整源码在报告末尾和 `OutputRows.inc.lean`：

```lean
let batches : Vector (Vector Binary32 (m * p)) batch :=
  Vector.ofFn fun b =>
    let batchTiles := tiles.get b
    let aBatch := b.val * m
    let bBatch := b.val * n * p
    OutputRows.rowsOfFn m p fun i =>
      let rowTiles := batchTiles.get i
      let baseA := (aBatch + i.val) * n
      fun j =>
        let g : Fin (Packed10.groups p) :=
          ⟨j.val / 10, Packed10.groups_pos_of_col p j.val j.isLt⟩
        let l : Fin 10 := ⟨j.val % 10, Nat.mod_lt _ (by decide)⟩
        Packed10.finish n baseA (bBatch + j.val) p Araw Braw
          (Packed10.lane (rowTiles.get g) l)
batches.flatten.cast (Nat.mul_assoc batch m p).symm
```

这里没有逐输出调用 dot，也没有重算 tile。`coreRows` 和父本一样，先各准备一次 nativeA、packedB、tiles，再进入输出构造。每个合法输出只调用一次 finish；两层 flatten 只是转存已产生的 Binary32 值。

这一版保留列内 `j/10`、`j%10` 和逐输出的组 get，不额外扩大机制。它消除的是构造路径中的全局 q 解码，并在源码中把上两层 tiles.get 与地址计算放到 batch/row 闭包。编译器最终是否保持这些放置、是否已经优化旧实现、是否引入额外闭包或引用计数，尚无生成代码证据。

## 3. 通用矩形引理与具体证明连接

### 3.1 通用 rowsOfFn 不要求正维

`Rectangular.lean` 仅 `import ContractTensor`，可单独送编译。其定义为：

```lean
def rowsOfFn {α : Type} (rows cols : Nat)
    (f : Fin rows → Fin cols → α) : Vector α (rows * cols) :=
  (Vector.ofFn (fun i : Fin rows => Vector.ofFn (f i))).flatten
```

配套 `rowIndex`、`colIndex` 从 `q : Fin(rows*cols)` 构造两个 Fin 索引。`0<cols` 来自 q 的界，使用固定 API `Nat.pos_of_lt_mul_left`，无需外部正维假设。完整证明提供：

```lean
rowsOfFn rows cols f =
  Vector.ofFn (fun q : Fin (rows * cols) =>
    f (rowIndex q) (colIndex q))
```

证明是 `Vector.ext` 后应用 `Vector.getElem_flatten`、`Vector.getElem_ofFn`，确实逐元素证明了构造顺序和值。除商余数边界外不需要新的地址乘法归纳或数值理论。

### 3.2 父本实际解码与两层 flatten 正好对应

实际父本的 `inlineDecodeC` 是：

```text
b = q / (m*p)
r = q % (m*p)
i = r / p
j = r % p
```

其定义含零除数分支。对合法 q，零维情况不可能发生，证明中局部推出 `p≠0`、`m*p≠0` 后展开这些分支。

本路线两层 flatten 的读取公式直接得到相同的 `q/(m*p)`、`(q%(m*p))/p`、`(q%(m*p))%p`。所以无需先把最后一项改写成 `q%p`，也无需增加变量除余数引理。`Vector.cast` 不改元素或索引值；双方 Fin 的值相同，界证明差异由内核证明无关性处理。

具体桥的结论为：

```lean
theorem outputRows_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (tiles : Vector (Vector (Vector Packed10.F10 (Packed10.groups p)) m) batch) :
    outputRows batch m n p A B tiles =
      Vector.ofFn (Packed10.outputFromTiles batch m n p A B tiles)
```

注意 tiles 是任意向量，并未假设它来源于正确点积，也未要求其中任何值 finite。证明中双方最终是**相同原始 A/B、相同 baseA/baseB、相同所选 lane 的同一次 finish 表达式**。因此 NaN payload、Inf、次正规和 ±0 的行为由原 finish 完整保留，而不是重新论证某个有限子域。

### 3.3 全输入规格链

| 定理 | 连接 |
| --- | --- |
| `rowsOfFn_getElem/get/eq_ofFn` | 通用矩形构造的元素顺序和值 |
| `Packed10OutputRows.outputRows_eq` | 任意 tiles 的新旧完整输出向量相等 |
| `Packed10OutputRows.coreRows_eq` | 相同准备后，新 core 等于父本 Packed10.core |
| `Packed10OutputRows.coreRows_eq_reference` | 接父本 `Packed10.core_eq_reference` |
| `Packed10OutputRows.bmmRows_eq_reference` | 原空输出/n=0 分支与非空分支统一 |
| `Packed10OutputRows.bmmRows_spec` | 接原 `referenceBmm_spec`，保留全部原量词 |

新的 bmmRows_spec 仍量化任意 `batch m n p : Nat` 和全部原始 Binary32 向量。没有外部 sound 参数、finite 条件或机器字维度上界。

### 3.4 明确的未编译边界

8 条定理都提供完整证明脚本，没有占位。独立静态审查未发现具体语义或类型阻断，但以下仍需要真实 Lean 确认：

- `outputRows_eq` 的最终 `simp only` 是否在固定导入闭包下完成所有依赖 Fin 的化简。
- `rowsOfFn`、Vector.getElem/cast/flatten/ofFn 的 elaboration 与实例推断。
- 组合后的内核验证、允许公理集合和官方完整 gate。

没有获得真实编译错误，因此不列虚构的“当前未解目标”。若首次编译停在最后化简，应保存实际目标；静态分析预期两侧剩余内容仅为同一 q 的 finish/tiles.get 表达式。不能为了关闭它而添加正确性前提。

## 4. 零维与巨大 Nat

`rowsOfFn` 和 `outputRows_eq` 都对任意 Nat 维度成立。rows=0 或 cols=0 时没有合法 `Fin(rows*cols)`；batch*m*p=0 时也没有合法输出 q，外延证明不需要把正维条件加到结论上。n=0 对输出重排等式没有特殊要求：两侧仍调用同一个 finish。

但是，**逻辑空向量不意味着单独调用通用构造器没有准备费用**。例如 rows 很大、cols=0，嵌套 ofFn 仍可能建立大量空行容器。新 `bmmRows` 和启用脚本保留父本“输出空或 n=0，在准备前返回 referenceBmm”的两个分支，因此不会向完整调用引入这类新准备。

示例 `(batch,m,n,p)=(0,1,2^128+123,1)` 的 A、B、输出都为空；无需先把 n 转为机器字。`(1,1,0,2)` 则应输出两个 +0，仍由原参考分支负责。整个输出改写只使用 Nat、Fin 和标准 Vector/Array；没有新增 UInt/USize 截断，也没有把巨大维度排除出规格。

## 5. 完整费用：两次 flatten 不是零拷贝

实际核对的 [Vector.Basic](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Vector/Basic.lean) 和 [Array.Basic](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Array/Basic.lean) 定义显示：

- `Vector.ofFn` 包装 Array.ofFn；后者预留长度后按序 push。
- `Vector.flatten` 先 `map Vector.toArray`，再调用 Array.flatten。
- `Array.flatten` 从 empty 开始，对子数组逐一 append。
- `Array.append` 遍历右数组，将元素逐个 push。
- `Vector.cast` 保留同一个 toArray，仅调整长度证明，不进行元素遍历。

因此两层标量 flatten 各追加全部 N=`batch*m*p` 个输出。它们不重新计算 finish 或 dot，但会转存结果值，并涉及中间容器、容量增长及释放。Array.map 可能复用独占数组；不能把一个逻辑 map 或 Vector 机械算成一次物理分配，也不能逐项推定引用计数增减。

默认 `(2,50,100,50)` 有 N=5000、R=batch*m=100：

| 源级项目 | 原平坦输出 | 本行序输出 |
| --- | ---: | ---: |
| 全局 q 解码 | 5000 次 | 构造路径中 0 次 |
| `tiles.get b` 的放置次数 | 5000 | 2 |
| batchTiles 的行 get | 5000 | 100 |
| rowTiles 的组 get | 5000 | 5000 |
| j/10、j%10 | 各 5000 | 各 5000 |
| finish | 5000 | 5000 |
| 首次写出标量结果 | 5000 | 5000，分布在行数组 |
| 内层 flatten 追加元素 | 0 | 5000 |
| 外层 flatten 追加元素 | 0 | 5000 |

另累计构造 100 个长度 50 的行结果、2 个长度 2500 的 batch 扁平中间结果，以及收集行/批结果的引用容器。flatten 内的 `map Vector.toArray` 合计逻辑访问 102 个向量引用。这里没有推算同时存活的峰值、精确物理分配、字节流量或 RC 指令数。

收益方向是减少全局解码和上层索引；代价是额外 **10000 次源级标量追加**、行/batch 容器和相应释放。旧实现的编译器优化也尚未观察。这些费用可能抵消收益，本轮不宣称必然更快或预测倍数。

选择这条展平顺序是为了在本轮范围内给出较短、可审的完整等价脚本。没有同时交付 push builder、其他展平顺序、更多 tile 形状或新的循环路线。

## 6. 最小集成：区分追加验证与真实启用

主片段 `OutputRows.inc.lean` 已合并通用引理和具体接线，**不含 import**，可直接追加到精确父本。独立的 `Rectangular.lean` 只用于通用引理单独检查；不要把它和已经合并的主片段重复追加。

### 6.1 追加模式：验证新证明，旧入口保持原样

包内 `compose_attempt.py` 只做文本组合、父本 SHA/字节验证和完整性检查，不调用 Lean，不更改环境，不覆盖既有输出文件。

在现有固定 Lean 工作区内运行：

```bash
python3 /absolute/path/FloatLib_R5-W01/compose_attempt.py --parent /absolute/path/fixed/Kernel.lean --output /tmp/R5W01_Append.lean --mode append
lake env lean /tmp/R5W01_Append.lean
```

此模式只追加定义和证明。**原 Submission.bmm 仍使用旧输出组织，不能用此模式的官方入口计时宣称测到了新路径。** 新入口是 `Submission.Packed10OutputRows.bmmRows`。

本轮实际生成的追加源码：138109 字节，SHA256：

```text
7b63d0f5b1d1f33c4e504616a1b1f9069696922781b572bd2a6727834875f7fc
```

### 6.2 启用模式：只切换原 bmm 的非空输出核心及证明调用

```bash
python3 /absolute/path/FloatLib_R5-W01/compose_attempt.py --parent /absolute/path/fixed/Kernel.lean --output /tmp/R5W01_Active.lean --mode activate
lake env lean /tmp/R5W01_Active.lean
```

脚本在原 bmm 声明前关闭/重新打开 namespace，插入同一份扩展；原 bmm 的非空分支只从 `Packed10.core` 换为 `Packed10OutputRows.coreRows`，原 bmm_spec 对应使用 `coreRows_eq_reference`。父本 add/mul/sum、热循环、数值桥、旧 core、两条提前返回和最终规格量词不变。没有前向引用新定义，也无需重命名原四函数。

脚本通过反向撤销唯一插入和两处替换，核对全部父本字节复原；本轮已执行该检查。激活源码仅一个 `import ContractTensor`，138209 字节，SHA256：

```text
a2ab63d0fe04639062f0d791732677123e71a360ae0dc3489ee15b7fe6b71d9b
```

这只是**已经生成、可送编译的源码**，不是已编译或已过 gate 的候选。为保持小包，ZIP 不重复放入完整父本/组合文件；脚本在精确父本上生成相同字节。

### 6.3 诊断与正式文件分离

`diagnostics/AxiomChecks.inc.lean` 包含新定理的公理打印请求，追加到临时检查文件运行即可。正式候选不能追加该诊断文件：

```bash
cat /tmp/R5W01_Active.lean /absolute/path/FloatLib_R5-W01/diagnostics/AxiomChecks.inc.lean > /tmp/R5W01_Axioms.lean
lake env lean /tmp/R5W01_Axioms.lean
```

应确认只出现允许的 `propext`、`Classical.choice`、`Quot.sound`。本轮未实际输出公理列表；词法扫描不等于公理或完整 gate 验证。没有改 toolchain、依赖、官方 gate/bench 或编译器参数，也未正式提交。

## 7. 输出语义最易错的反例

**最重要的盲区：finite 接纳不使用 raw 回退地址。** 如果外提 baseA/baseB 写错，普通有限矩阵仍可能全部通过。必须使合法输出非finite，真正进入 raw 回退。

以下反例针对明确错误改动，并非已观察到本实现失败。shape 为 `(batch,m,n,p)`，数组均为行主序；执行状态全部为 ANALYTICAL_NOT_RUN。

| 错误改动 | 最小完整输入 | 合同结果 | 错误表现 |
| --- | --- | --- | --- |
| 展平成列优先，交换 i/j | `(1,2,1,2)`，A=[1,2]，B=[3,5] | [3,5,6,10] | [3,6,5,10] |
| 下一行复用第 0 行 rowTiles | `(1,2,1,1)`，A=[1,2]，B=[3] | [3,6] | 第二项为 3 |
| 第二行 raw 回退仍用第一行 baseA | `(1,2,1,1)`，A=[1,+Inf]，B=[+0] | [+0,NaN] | 第二项为 +0 |
| 第二 batch 回退遗漏 A batch 偏移 | `(2,1,1,1)`，A=[1,+Inf]，B=[+0,1] | [+0,+Inf] | 第二项为 1 |
| 第二 batch 回退遗漏 B batch 偏移 | `(2,1,1,1)`，A=[+Inf,+Inf]，B=[1,+0] | [+Inf,NaN] | 第二项为 +Inf |
| raw B 回退基址遗漏列 j | `(1,1,1,2)`，A=[+Inf]，B=[1,+0] | [+Inf,NaN] | 第二项为 +Inf |
| j=10 仍取第 0 个 tile | `(1,1,1,11)`，A=[1]，B=[1,…,11] | [1,…,11] | 末项为 1 |

`diagnostics/output_witnesses.json` 给出以上输入的十六进制位型，另有 -0、最小次正规、三类带 payload 的 NaN、n=0、m=0、p=0 和巨大 n 的空 batch，共 16 例。**NaN 的精确期望位型须由固定原始软件参考生成**，不猜 payload，不使用宿主浮点的 NaN 相等规则。Python 只编码精确常量和检查向量长度，没有模拟 BMM。

还应使用有限和非finite两组 `(2,3,2,11)`：不同真实行/列、n>1、尾块同时覆盖外提位置和基址中 n/p 的乘数。有限集合不能替代上述量化 Lean 证明。

## 8. 最小完整调用比较要求与停止条件

1. 冻结激活版本源码 SHA，先按既有固定环境尝试编译与原完整 gate，确认被测入口确实调用新 coreRows。
2. 原 raw 校验加第 7 节定向反例，逐位对照原始参考；任何位型、证明或政策失败即可停止该版本。
3. 确认输入准备和 tileResults 仍各执行一次，输出阶段无 dot 重算；空输出/n=0 仍在准备前返回。
4. 只使用既有完整调用 runner 做父本 A → 行序版 B → 父本 A，保持 dense/relu/wide 与原汇总规则，记录原始时间及 A 的漂移。
5. 完整计入转换、打包、tiles、行数组、两个 flatten、finish/raw 回退、所有中间缓冲构造/释放及输出；默认 ns/MAC 分母仍为 **500000 个有效 MAC**。

若 B 在完整调用中被前后两次 A 支配且差距超过同轮 A 漂移，停止晋升这版；如果只见输出子段改善而整体无收益，不把局部节省当作已获得速度提升。若差异处于噪声内，不宣布胜出；遵循已有验收流程，不新增统计门槛或 bench 改动。

## 9. 来源、许可和包内容

主要固定来源：

- [父本 Kernel.lean](https://github.com/HuanHuanHuanFFF/Miner/blob/e5b144bf77d477919f4787e36311cf65d2a23c15/competitions/floatlib/candidates/f01-d4-final-lowmul/Kernel.lean)：本轮实际读取 Packed10 的 finish、tileResults、inlineDecodeC、outputFromTiles、core 及证明、原 bmm/spec。
- [Vector.Basic](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Vector/Basic.lean)：ofFn、flatten、cast、get 的实际定义。
- [Vector.Lemmas](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Vector/Lemmas.lean)：Vector.ext、getElem_flatten、getElem_cast。
- [Vector.OfFn](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Vector/OfFn.lean)：getElem_ofFn。
- [Array.Basic](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Array/Basic.lean)：Array.ofFn、append、flatten 的遍历与构造。
- [Nat.Div.Basic](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Nat/Div/Basic.lean)：div_lt_iff_lt_mul。
- [官方 ContractTensor](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/contract/ContractTensor.lean) 与 [gate.py](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/gate.py)。

完整下载记录、字节数和 SHA 在 `sources/source_manifest.json`。FloatLib 固定 commit 本轮未重新下载；数值桥使用真实父本已有定义和证明，没有重新声明假设接口。

父本自带 Conjectures.io、FloatLib、TorchLean 的 MIT 通知，逐字保留于 `sources/PARENT_NOTICES.txt`，组合脚本保留父本原许可头。Lean 源文件头标注 Apache 2.0，本包只调用 API、不重分发标准库实现。新增片段、组合脚本和报告的 MIT 许可单独列出，不改变上游许可。

包内包括主追加片段、通用独立文件、组合脚本、报告、独立审查原件、诊断/计数/解析输入、来源许可和 SHA256SUMS。所有诊断与正式 Lean 片段分离。

## 附录：完整主追加片段

以下与 `OutputRows.inc.lean` 逐字一致。它追加到父本，不另加 import；**编译状态仍为 NOT_RUN**。

```lean
namespace Submission.OutputRows

def rowIndex {rows cols : Nat} (q : Fin (rows * cols)) : Fin rows :=
  ⟨q.val / cols,
    (Nat.div_lt_iff_lt_mul (Nat.pos_of_lt_mul_left q.isLt)).2 q.isLt⟩

def colIndex {rows cols : Nat} (q : Fin (rows * cols)) : Fin cols :=
  ⟨q.val % cols, Nat.mod_lt q.val (Nat.pos_of_lt_mul_left q.isLt)⟩

/-- Materialize the rows, then concatenate them in row order. -/
def rowsOfFn {α : Type} (rows cols : Nat)
    (f : Fin rows → Fin cols → α) : Vector α (rows * cols) :=
  (Vector.ofFn (fun i : Fin rows => Vector.ofFn (f i))).flatten

theorem rowsOfFn_getElem {α : Type} {rows cols : Nat}
    (f : Fin rows → Fin cols → α) (q : Nat) (hq : q < rows * cols) :
    (rowsOfFn rows cols f)[q]'hq =
      f (rowIndex ⟨q, hq⟩) (colIndex ⟨q, hq⟩) := by
  simp only [rowsOfFn, Vector.getElem_flatten, Vector.getElem_ofFn,
    rowIndex, colIndex]

theorem rowsOfFn_get {α : Type} {rows cols : Nat}
    (f : Fin rows → Fin cols → α) (q : Fin (rows * cols)) :
    (rowsOfFn rows cols f).get q = f (rowIndex q) (colIndex q) := by
  change (rowsOfFn rows cols f)[q.val]'q.isLt = _
  exact rowsOfFn_getElem f q.val q.isLt

theorem rowsOfFn_eq_ofFn {α : Type} (rows cols : Nat)
    (f : Fin rows → Fin cols → α) :
    rowsOfFn rows cols f =
      Vector.ofFn (fun q : Fin (rows * cols) => f (rowIndex q) (colIndex q)) := by
  apply Vector.ext
  intro q hq
  simp only [rowsOfFn_getElem, Vector.getElem_ofFn]

end Submission.OutputRows

namespace Submission.Packed10OutputRows

open FloatLib.Floats Competition

def outputRows (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (tiles : Vector (Vector (Vector Packed10.F10 (Packed10.groups p)) m) batch) :
    Vector Binary32 (batch * m * p) :=
  let Araw := A.toArray
  let Braw := B.toArray
  let batches : Vector (Vector Binary32 (m * p)) batch :=
    Vector.ofFn fun b =>
      let batchTiles := tiles.get b
      let aBatch := b.val * m
      let bBatch := b.val * n * p
      OutputRows.rowsOfFn m p fun i =>
        let rowTiles := batchTiles.get i
        let baseA := (aBatch + i.val) * n
        fun j =>
          let g : Fin (Packed10.groups p) :=
            ⟨j.val / 10, Packed10.groups_pos_of_col p j.val j.isLt⟩
          let l : Fin 10 := ⟨j.val % 10, Nat.mod_lt _ (by decide)⟩
          Packed10.finish n baseA (bBatch + j.val) p Araw Braw
            (Packed10.lane (rowTiles.get g) l)
  batches.flatten.cast (Nat.mul_assoc batch m p).symm

theorem outputRows_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (tiles : Vector (Vector (Vector Packed10.F10 (Packed10.groups p)) m) batch) :
    outputRows batch m n p A B tiles =
      Vector.ofFn (Packed10.outputFromTiles batch m n p A B tiles) := by
  apply Vector.ext
  intro q hq
  have hp : p ≠ 0 := by
    intro hp
    simp [hp] at hq
  have hmp : m * p ≠ 0 := by
    intro hmp
    have hq' : q < batch * (m * p) := by
      simpa only [Nat.mul_assoc] using hq
    simp [hmp] at hq'
  simp only [outputRows, OutputRows.rowsOfFn, Vector.getElem_cast,
    Vector.getElem_flatten, Vector.getElem_ofFn,
    Packed10.outputFromTiles, Packed10.inlineDecodeC, hmp, hp, if_false]

def coreRows (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  let nativeA := A.toArray.map ExecFloat.Binary.toFloat32
  let packedB := Packed10.packB batch n p B
  let tiles := Packed10.tileResults batch m n p nativeA packedB
  outputRows batch m n p A B tiles

theorem coreRows_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    coreRows batch m n p A B = Packed10.core batch m n p A B := by
  unfold coreRows Packed10.core
  dsimp only
  exact outputRows_eq batch m n p A B _

theorem coreRows_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    coreRows batch m n p A B = referenceBmm batch m n p A B := by
  exact (coreRows_eq batch m n p A B).trans
    (Packed10.core_eq_reference batch m n p A B)

def bmmRows (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if batch * m * p = 0 then referenceBmm batch m n p A B
  else if n = 0 then referenceBmm batch m n p A B
  else coreRows batch m n p A B

theorem bmmRows_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    bmmRows batch m n p A B = referenceBmm batch m n p A B := by
  unfold bmmRows
  split
  · rfl
  · split
    · rfl
    · exact coreRows_eq_reference batch m n p A B

theorem bmmRows_spec : ∀ (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmmRows batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  rw [bmmRows_eq_reference]
  exact referenceBmm_spec batch m n p A B

end Submission.Packed10OutputRows
```
