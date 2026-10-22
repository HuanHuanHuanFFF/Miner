# R5-W01 输出组织独立审查

状态：本轮实际读取了固定公开父本与 Lean v4.34.0 的 Vector/Array API。没有 Lean 编译器，没有执行新候选、浮点模拟、C 实验或计时。下面的反例是解析见证，状态均为 **ANALYTICAL / NOT_RUN**。

## 1. 审查对象与结论边界

父本：

https://github.com/HuanHuanHuanFFF/Miner/blob/e5b144bf77d477919f4787e36311cf65d2a23c15/competitions/floatlib/candidates/f01-d4-final-lowmul/Kernel.lean

公开下载长度 132965 字节，SHA256 为 `ba93c233f87935aaadb9ec697487b316d4538d014831ee8d6e00127d6c34f630`，与用户给定一致。本轮阅读了 `Packed10.tileResults`、`outputFromTiles`、`finish`、`core`、`core_eq_reference` 及外层 `bmm`。用户提供的三次完整 gate 通过记录没有在本轮重跑。

只改变输出顺序的构造方式可以直接以“对任意 tiles，结果向量等于原 `Vector.ofFn (outputFromTiles ...)`”连接已有数值证明。这个等式必须是整个向量逐元素相等；只证明长度，或只对某个全有限输入族相等，都不足够。对任意 tiles 的结构等式一旦成立，原 native 解码、NaN/Inf/零处理和原始输入回退可以完整复用，无需重新证明热循环。

最终选择的唯一方案是：**每 batch 用 `Vector.ofFn` 构造 m 个长度 p 的行，先 flatten 为长度 m*p 的 batch 输出；再将 batch 输出 flatten，最后作 Nat 乘法结合的长度转换。** 该顺序直接匹配父本 `inlineDecodeC` 的 `q/(m*p)`、`(q%(m*p))/p`、`(q%(m*p))%p`。本审查不提交其他布局或 builder 路线。

## 2. 实际 API 显示 flatten 有遍历与追加费用

已读取固定文件：

- https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Vector/Basic.lean
- https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Vector/Lemmas.lean
- https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Array/Basic.lean

相关实际定义如下（仅说明既有标准库实现，不复制进候选）：

```lean
Vector.flatten xs =
  ⟨(xs.toArray.map Vector.toArray).flatten, ...⟩

Array.flatten xss =
  xss.foldl (init := empty) fun acc xs => acc ++ xs

Array.append as bs =
  bs.foldl (init := as) fun xs v => xs.push v
```

`Vector.ofFn` 包装 `Array.ofFn`；后者先 `emptyWithCapacity n`，然后按 0 到 n−1 逐项 push。`Array.flatten` 本身从 empty 开始，定义没有一次预留最终总长度。不能将 flatten 说成零拷贝视图或只有长度证明擦除。

`Array.map` 的实际标准库运行实现可以复用独占数组，所以也不能把每次逻辑 map 机械算成一次新物理分配。`Vector.toArray` 的表示投影和长度证明可能被擦除；是否消去整个 map、是否借用对象、实际引用计数增减和扩容次数，本轮未观测。由这些源码不应推导精确字节数、机器 load 数或运行时间。

## 3. 完整路径费用：省全局解码，增加行容器和两遍结果追加

设 β=batch、R=β*m、N=β*m*p。既有 `nativeA`、`packB`、`tileResults` 各计算一次，10 路 dot 完全不变；`finish` 仍调用 N 次，只有合法的 p 列，不为尾块填充 lane 执行 finish。

在理想的源码外提位置，访问表达式数量为：

| 源级项目 | 原平坦输出 | 行序输出 |
| --- | ---: | ---: |
| 全局 q→batch/row/column 解码 | N | 0 |
| `tiles.get b` | N | β |
| 对该 batch 的 `.get i` | N | R |
| 对该行的 `.get (j/10)` | N | N |
| `j/10`、`j%10` | 各 N | 各 N |
| `finish` | N | N |
| 从构造行首次写出结果元素 | 原最终数组 N 次 | 行数组合计 N 次 |
| 第一层 flatten 的 append 元素 | 0 | N |
| 第二层 flatten 的 append 元素 | 0 | N |

表中是词法调用/逻辑遍历需求，不能冒充经优化 C 的指令数。原实现中编译器是否已经外提某些表达式，本轮没有检查；新实现中也仍存在 Array.ofFn 自己的 Nat 索引/迭代工作。

每 batch 先 flatten 的方案引入 R 个长度 p 的逻辑行数组、β 个存放 m 行的容器、β 个长度 m*p 的扁平 batch 中间结果、一个存放 β 个 batch 结果的容器，以及最终长度 N 的数组。两次 flatten 中的 `map Vector.toArray` 还要逻辑访问 R+β 个向量引用。物理分配/释放数量受唯一性复用及编译器影响，不能逐个逻辑 Vector 算一个对象。

默认 β=2、m=50、n=100、p=50 时，N=5000、R=100：有 100 个长度 50 的行结果、2 个长度 2500 的 batch 中间结果；两层 flatten 的源码 append 合计遍历 **10000 个输出元素**。这些元素是已计算结果的转存，不重做 finish，不重做 dot。不能说消除了每输出大除余就必然更快。

这条路线的风险很明确：省下的全局解码及 tiles 上两层索引，可能被新增行数组构造、结果元素转存、容量增长和引用计数/释放抵消。所有这些都必须在原有完整调用边界里比较。

## 4. 输出语义最易错的地方

### 4.1 有限值测试不足以检查 raw 回退地址

父本 finish 在结果 finite 时直接采用原生值；这一分支不会用 raw A/B 地址来计算结果。因而 baseA/baseB 外提错了，普通 finite 矩阵仍可能完全通过。必须安排非finite的合法输出，逼出原始输入回退。

以下均是 `(batch,m,n,p)`，A/B/输出均为行主序。NaN 只给类别，精确 payload 必须由固定原始软件参考产生，不猜传播策略。

| 针对的错误 | 完整输入 | 正确结果 | 明确错误表现 |
| --- | --- | --- | --- |
| flatten 成列优先，或交换 i/j | `(1,2,1,2)`，A=[1,2]，B=[3,5] | [3,5,6,10] | 列优先会成为 [3,6,5,10] |
| 行 tiles 缓存始终取第 0 行 | `(1,2,1,1)`，A=[1,2]，B=[3] | [3,6] | 第二项变成 3 |
| 第二行非finite回退复用第一行 baseA | `(1,2,1,1)`，A=[1,+Inf]，B=[+0] | [+0,NaN] | 第二项错误为 +0 |
| 第二 batch 回退误用第一 batch 的 A 基址 | `(2,1,1,1)`，A=[1,+Inf]，B=[+0,1] | [+0,+Inf] | 第二项错误为 1 |
| 第二 batch 回退遗漏 B 的 batch 偏移 | `(2,1,1,1)`，A=[+Inf,+Inf]，B=[1,+0] | [+Inf,NaN] | 第二项错误为 +Inf |
| 回退列基址遗漏 j 或 lane 内偏移 | `(1,1,1,2)`，A=[+Inf]，B=[1,+0] | [+Inf,NaN] | 第二项错误为 +Inf |
| j=10 仍取第 0 个 tile | `(1,1,1,11)`，A=[1]，B=[1,2,…,11] | [1,2,…,11] | 末项取旧 tile 的 lane 0，得到 1 |

还应覆盖 `(2,3,2,11)`：n>1 能检查地址中 n 的乘数、不同真实行列能检查外提位置、p=11 能检查尾块。有限和非finite两组都需要，以免 finite 接纳掩盖错误回退地址。

这里没有改变数值运算，但回归集合仍应包含 -0、最小正次正规、Inf 和带 payload 的 quiet/signaling/负号 NaN。所有 32 位均与原始参考比较；不使用宿主浮点的 NaN 相等规则。

### 4.2 零维、巨大 Nat 与长度结合

嵌套 flatten 返回长度 `batch*(m*p)`，父本返回长度 `(batch*m)*p`。两者的转换必须由 Nat.mul_assoc 的证明完成，不得以截断、UInt/USize 转换或重写规格类型代替。

对于任意合法 `q : Fin(batch*m*p)`，其存在本身能导出必要的正除数；零维时根本没有 q，逐元素等价应由空 Fin 情况闭合。不能把 `0<m` 或 `0<p` 添加到最终结果等式的定理前提。

单独调用通用矩形构造器时，`rows` 很大而 `cols=0` 可能仍构造许多空行容器；这在逻辑上正确，但不是应向完整 bmm 引入的额外开销。应完整保留父本最外层“输出为空或 n=0 就在准备前回参考”的分支。例如 `(batch,m,n,p)=(0,1,2^128+123,1)` 的 A/B/输出均为空，不需要先截断巨大 n 或分配准备缓冲。n=0 且非空输出仍应得到每项 +0。

## 5. 最小完整调用比较与停止条件

1. 固定新源码 SHA，先在原环境尝试编译辅助代码和完整候选；按原 gate 验收所有量词、公理和政策，不改配置。
2. 原 raw 校验加上表中有限/非finite输出见证以及 `(2,3,2,11)`，完整调用逐位对照原始参考。任一位型不符即可否决。
3. 保持同一 nativeA/packB/tileResults 路径，确认输出循环没有重新调用 dot 或每输出重新算 tile；只修改输出构造。
4. 只用既有完整调用 runner 做原父本 A → 行序版 B → 原父本 A，在 dense/relu/wide 及原汇总规则下记录原始时间和漂移。包括新行容器、两层 flatten、所有转换、输出、fallback 和释放。
5. 默认 ns/MAC 分母仍为 500000 个有效 MAC。若 B 的完整调用被前后两次 A 支配且差距超过同轮 A 漂移，停止晋升该版本；若差异处在噪声内，不宣布必然提速。

本审查没有执行以上候选检查或性能比较；没有实测改善可报告。

## 6. 本轮生成源码的静态复核

已阅读本轮 `Rectangular.lean` 与 `Packed10OutputRows.inc.lean`：

- 通用 `rowsOfFn` 为 `(Vector.ofFn (fun i => Vector.ofFn (f i))).flatten`，将 `f i` 作为整行函数传入。接线的 `f i` 先取得 rowTiles/baseA 后返回列函数，表达了每行外提意图；没有在每列重新调用旧 `outputFromTiles` 来保留原全局解码。
- `outputRows_eq` 使用 `Vector.ext`，在任意 tiles 上比较元素。非空索引只在证明中导出 `p≠0`、`m*p≠0`，用来消去旧解码中的零除数分支；它们不是定义的运行时新增检查，也不是定理外部前提。
- 两层 flatten 的元素索引正是 `q/(m*p)`、`(q%(m*p))/p`、`(q%(m*p))%p`，与实际父本的旧解码一致；不需要未经证明地改写为另一种商余分解。
- `coreRows` 只计算一次 nativeA、packedB、tileResults，随后调用 outputRows；`bmmRows` 保留输出空或 n=0 的准备前回退。没有新 dot 或重复 tile 计算。
- `coreRows_eq` 连接旧 core，`bmmRows_spec` 连接父本的无条件 bmm_spec；没有新增 sound 参数、维度范围前提或只证明长度的替代物。

静态审查没有发现确定语义缺口。仍须由固定 Lean 环境确认 `simp only`、cast/getElem 归约、命名空间和最终公理输出；本轮没有编译成功记录，也没有真实 Lean 未解目标日志可报告。
