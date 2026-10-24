# R11-W01：实际 R11CrossRows 证明连接审查与最小条件补丁

日期：2026-10-24（Asia/Shanghai）  
对象：所附完整 Kernel；不是旧 Ascend/TRSM 工程  
主结论状态：**SOURCE_INSPECTION；固定 Lean、官方 gate、传递公理审计均 NOT_RUN；性能 UNKNOWN。**

## 1. 结论与交付决策

**本轮没有找到足以断言“原 R11CrossRows 证明有错”的源码反例或确定类型错配。不能因此宣称它已经通过 Lean。** 对精确父本的实际准备、八路有序点积、机器循环、精确 finish、跨 batch/tail 取词、flat core 和原 bmm_spec，纸面连接完整；主要剩余风险是固定 elaborator 对递归证明、局部 let/Fin 投影及 Vector 展开的实际接受情况。[S0]

建议本地首先编译**原 SHA**。不要因为这份报告存在而强制修改已经可能可编译的证明。为了使“编译器若确实卡住时如何修”具体可审，本包提供：

1. **20 字节条件补丁**：仅给 theorem `natLoop_lane` 的已有 `termination_by n-k` 加 `decreasing_by omega`。它针对默认终止 tactic 未关闭减小量的假设故障；本轮未观察到该故障。
2. `rowWord_eq` 的可选正规化替换片段：只加两处 `dsimp only`，仅在固定编译器报告对应 let/Fin 正规化问题时使用。未并入条件 Kernel。
3. 实际 A/B 读取界、实际 packet `uget=get`、零维分支和原四 spec 类型的诊断片段；没有抽象 read 正确性假设，没有新运行时函数，没有占位证明。
4. 原字节、条件 Kernel、准确 unified diff、静态复核脚本、原始检查结果和 manifest。

**没有完成的部分必须保持未完成：** 两个 Kernel 的固定 Lean 类型检查、官方 statement build、kernel replay、传递公理 allowlist、checksum suite 和 25 组 paired full-call timing 均未执行。条件补丁不是 accepted candidate。

## 2. 精确工件和证据级别

| 工件 | UTF-8 字节 | SHA256 | 距 256000 字节上限 |
|---|---:|---|---:|
| 原 Kernel | 252609 | `4bdd1e7db35cd85e17d06511721d5dbf7f654ec12e58633264b08a086ec54fa0` | 3391 |
| 条件 Kernel | 252629 | `96f8b69364e93a145853f5d98b23222b82b20d55a0c359507dbaa25cf389f40c` | 3371 |

原上传文本为 263896 字节，SHA256 为：

`8278e5bf3a955ba6971b7db0aac77b43a7888942f11f3f33ae2c5876c1c40fcc`

上传容器用了 CRLF。提取 BEGIN/END 中的 Kernel、恢复 LF 并保留源码末尾一个 LF 后，命中题目指定的完整 SHA。不是根据“看起来相同”推断一致。原上传文件没有修改。

| 检查 | 实际状态 | 能支持的结论 |
|---|---|---|
| 原 Kernel 字节、SHA、大小 | PASS | 研究对象确为指定源 |
| 条件补丁适用及逆向还原 | PASS | 原文件只在指定 theorem 内增加一行 |
| 全部其他源码字节比较 | PASS | 每个运行时定义及原四 spec 声明保留原字节 |
| import、source options、禁用 token 静态扫描 | PASS | 唯一 import 为 ContractTensor；源码没有 set_option；扫描未见所列禁用项 |
| 全链源码与纸面审查 | 完成，SOURCE_INSPECTION | 列出的等式、地址和前提相互匹配 |
| 固定 Lean elaboration/typecheck | NOT_RUN | 无编译通过结论 |
| 官方 gate／kernel replay／公理审计／checksum | NOT_RUN | 无正式接收结论 |
| 浮点有限测试 | NOT_RUN | 未以其代替证明 |
| 地址反例 | EXACT_INTEGER_CONSTRUCTION | 仅说明被反驳的地址假设不成立 |
| 汇编、full-call timing | NOT_RUN / UNKNOWN | 无速度、spill、SIMD 或收益结论 |

环境探测没有找到 lean/lake/elan；常见固定工具链路径也不存在。固定 Lean 的公开原始源码请求返回 DisabledError，直接网络读取返回 Operation not permitted。它们表示本轮访问不可用，不表示源文件不存在或 API 不兼容。没有安装替代工具链，没有用另一个 Lean 版本冒充固定版本。[E1]

## 3. 实际证明依赖链

下面所有节点都是附件里的实际定义或定理名；不存在将读取义务替换为“假设 pack 正确”的新接口。[S0]

| 层 | 实际声明 | 连接内容 |
|---|---|---|
| 准备 | packGeneral_a/b → pack_eq_general → pack_a/b | 实际 Vector.ofFn、A/B.getD 和共享 B 分支 |
| 每 lane 有序循环 | lane_update → natLoop_lane | 每个 k 的实际 multiply 后 add，k 递增 |
| 机器循环 | wordLoop_eq → dot8_lane | 真实 P12 vector 的 uget；USize 步进与 Nat 循环相等 |
| 精确完成 | finish8_word → blockAt_word | F8 列优先 lane → W8 行优先 word；原 Packed10.finish_eq_dot |
| 跨 batch 分组 | blockRows_word | 四个全局 row 分别计算 row/m 的 B batch 基址 |
| 尾部／取词 | group_bound、row_decomposition、rowWord_eq | 只选择合法输出 row；尾部多算 lane 不被输出 |
| flat 输出 | core_eq_rows | q/p、q%p 对齐原 DirectRows.core |
| 原合同 | DirectRows.core_eq → DirectSmall.core_eq_reference → referenceBmm_spec | 回到原 bmmSpec 的完整 .get 函数相等 |
| dispatch | bmm_spec | 真分支使用上链；假分支使用 bmmBeforeR11Cross_spec |

需分别理解两件事：这些连接在源码中确实被写出，并且纸面上相符；这些 proof term 是否被指定 Lean 在允许资源内接受，仍须真实运行确认。

## 4. pack_a/b：真正的读取已经接上

取 `l : Fin 8`，令 `r=l.val%4`、`j=l.val/4`。八个 lane 的输入为：

| l | r | j | A 字段 | B 字段 | 原始 A 索引 | 原始 B 索引 |
|---:|---:|---:|---|---|---|---|
| 0 | 0 | 0 | a0 | b0 | a0+k | b0+k*p |
| 1 | 1 | 0 | a1 | b1 | a1+k | b1+k*p |
| 2 | 2 | 0 | a2 | b2 | a2+k | b2+k*p |
| 3 | 3 | 0 | a3 | b3 | a3+k | b3+k*p |
| 4 | 0 | 1 | a0 | b4 | a0+k | (b0+1)+k*p |
| 5 | 1 | 1 | a1 | b5 | a1+k | (b1+1)+k*p |
| 6 | 2 | 1 | a2 | b6 | a2+k | (b2+1)+k*p |
| 7 | 3 | 1 | a3 | b7 | a3+k | (b3+1)+k*p |

这里 P12 字段名 b4..b7 不是四个新 batch 基址，而是第 1 列的四个解码值。

`packGeneral_a/b` 把实际 `Vector.ofFn` 的 .get 展开，再枚举 Fin 8 的八个值。得到的右边明确是：

```lean
ExecFloat.Binary.toFloat32
  (A.getD (select4 a0 a1 a2 a3 (l.val%4)+k.val) posZero)

ExecFloat.Binary.toFloat32
  (B.getD ((select4 b0 b1 b2 b3 (l.val%4)+l.val/4)+k.val*p) posZero)
```

`pack` 的共享条件为 `b1=b0 ∧ b2=b0 ∧ b3=b0`。在真分支，替换这三个基址后，packShared 的 let 共享与 packGeneral 的重复表达式定义相等，因此 `packShared_eq` 用 rfl 是合理的。假分支就是 general。最终 `pack_a/b` 通过 `pack_eq_general` 使用上面的实际读取定理。

此处没有外加 `∀k, read k = expected k` 前提。原先 Packed10 的某些通用 helper 带有抽象 hb 参数，不等于本次 R11 的具体 packing 义务未完成：R11 的 natLoop_lane 直接重写本命名空间的 pack_a/b。

## 5. 八路 ordered dotLoop：归纳对象与终止量

`update` 对 lane l 做的表达式精确为：

```lean
lane s l + inputA packet l * inputB packet l
```

它没有跨 lane 求和、没有 partial-sum 合并，也没有改变某一输出的 k 顺序。`natLoop_lane` 的不变量是：从任意 Nat k 和任意 F8 s 开始，该 lane 的后续 natLoop 等于同一 A/B 基址上的实际 NativeFinal.dotLoop，初始 accumulator 为 `lane s l`。

在 `hk : k<n` 分支：

1. 两个循环都展开同一个 k<n 分支。
2. 从 k 递归到 k+1。
3. 递归假设中的 `lane (update s packet) l` 用 lane_update 展开。
4. 用 pack_a/b 将实际 packet 两个字段还原为上述原始 A/B.getD。
5. 得到 NativeFinal.dotLoop 同一个表达式上的递归等式。

在 k≥n 分支，两边都返回输入 accumulator。不需要添加 k≤n 假设。

数学上的终止义务是：

```lean
hk : k < n ⊢ n - (k + 1) < n - k
```

这对于任意 Nat n,k 成立。原 theorem 已写 `termination_by n-k`，但未显式给 decreasing_by。附带的最小条件补丁只将这一义务交给 omega；它不修正任何数值节点或地址。

**尚不能确定的问题：** 默认 termination tactic 在固定 Lean 上是否本来就成功。附件父本有大量同形写法，这支持“原写法可能已经足够”，不构成编译证据。

## 6. wordLoop：guard 实际建立了哪些机器前提

令 U=USize.size。新路径中显式的 USize 索引运算只用于 P12 packed vector 的 count/k；准备和回放中的原 A/B 地址保持 Nat。

### 6.1 初始 count

dispatch 的 conjunction 右结合结构如下：

```text
p=2 ∧ 4≤batch*m ∧ 0<n ∧ n<U ∧ A.size<U ∧ B.size<U ∧ batch*m*p<U
```

因此：

- `h.1` 是 p=2；
- `h.2.1` 是 4≤batch*m；
- `h.2.2.1` 是 0<n；
- **`h.2.2.2.1` 正是 n<U。**

`dot8` 将它实际传给 `USize.toNat_ofNat_of_lt' hn`，建立 `(USize.ofNat n).toNat=n`。不是从某个“输入足够短”的口头条件推断。

### 6.2 真实 packet 读取

在 `hk : k<count` 下，源码经 `USize.lt_iff_toNat_lt` 和 count.toNat=n 得到 k.toNat<n。随后：

```lean
v.toArray.uget k (by simpa only [v.size_toArray] using hkn)
```

的边界来自实际 `v : Vector P12 n`。wordLoop_eq 的 hread 是：

```lean
v.toArray.uget k (...) = v.get ⟨k.toNat,hkn⟩
```

并由 rfl 证明。附件原有 Packed10Index.ugetB_get 已使用相同数组／向量定义相等模式。不同边界 proof 参数可由 proof irrelevance 对齐；这仍待实际 elaborator 检查。

### 6.3 递增不回绕

从 k<count 有：

```text
k.toNat+1 ≤ count.toNat < U
```

故 `(k+1).toNat=k.toNat+1`。源码中的 `Packed10Index.stepNat hk` 就是这一证明，而 `next_decreases hk` 给出：

```lean
count.toNat - (k+1).toNat < count.toNat - k.toNat
```

二者被实际 wordLoop/wordLoop_eq 调用。不存在到最大值后“相信它不会 wrap”的缺口。

### 6.4 不应制造的额外机器义务

A/B.getD 的索引是 Nat；尾部虚拟行的地址允许超过数组长度，甚至超过 U。不能因为 dispatch 检查了 A/B 长度<U，就声称**每一个虚拟 row 的基址**都<U。

一个准确的反例：U=2^32，batch=1，m=5，p=2，n=858993459。此时：

- A 长度为 4294967295<U；
- B 长度为 1717986918<U；
- 输出长度 10<U；
- p=2、rows≥4、n>0、n<U 均成立；
- 最后一组的虚拟 row=7，其 A 基址是 6012954213≥U。

原实现对此仍有定义：Nat 不回绕，getD 越界返回默认值，而 row=7 不被输出。这不是原 Kernel 的错误，是“guard 蕴含全部 tail 地址可直接 cast USize”这一更强命题的反例。包内也给出 U=2^64 的同形精确整数构造；没有尝试分配这些大数组。[E3]

因此不能把这组 guard 原样当成将来所有 tail raw reads 转为 USize/uget 的证明。那种实现变化需要新的实际边界推导。本轮保持原运行时定义。

## 7. exact finish8：列优先 accumulator 到行优先 raw word

`laneIndex r j=r.val+4*j.val`，finish8 的对应表为：

| 输出 (r,j) | F8 lane | W8 字段 | 原 A base | 原 B base |
|---|---|---|---|---|
| (0,0) | s0 | w0 | a0 | b0 |
| (0,1) | s4 | w1 | a0 | b0+1 |
| (1,0) | s1 | w2 | a1 | b1 |
| (1,1) | s5 | w3 | a1 | b1+1 |
| (2,0) | s2 | w4 | a2 | b2 |
| (2,1) | s6 | w5 | a2 | b2+1 |
| (3,0) | s3 | w6 | a3 | b3 |
| (3,1) | s7 | w7 | a3 | b3+1 |

`finish8_word` 的八种 case 使用实际 `Packed10.finish`，再由 `rebuild` 恢复 Binary32：

```lean
ExecFloat.Binary.ofBits32 q.raw.1 = q
```

这里恢复的是 finish 已经产生的完整 Binary32 word，不是在假设 native Float32 能保存原始 signaling/payload。

`blockAt_word` 实际调用 `Packed10.finish_eq_dot`。该定理要求的前提只有：

```lean
result = NativeFinal.dotLoop n baseA baseB p A B 0 Packed10.zero32
```

此处的 result 是指定 lane；dot8_lane 正好提供该等式。八种 r,j case 将 (laneIndex r j)%4 和 /4 化为 r,j。非 NaN 端使用原桥；NaN 端仍在原 A/B 和该 lane 的准确 base 上调用 R7NaNReplay.replayEarly。

本轮没有改用普通复合 sum、native NaN raw bits 或另一个近似 fallback。原父本关于 exact add/mul、NaN replay、signed zero、subnormal 的传递依赖仍必须纳入最终官方公理和 kernel replay 审计。

## 8. 跨 batch、tail 和 flat core

### 8.1 每行独立的 batch 基址

blockRows 的第 t 个 lane row 是 R=4*g+t：

```text
A base = R*n
B base = floor(R/m)*n*p
```

每行分别求 R/m，组不要求留在同一个 batch 内。pack 的共享 B 条件比较的是四个实际 B base。

精确小见证：batch=2,m=3,n=1,p=2，A 全 1，B=[1,2,4,8]。组 0 的 rows=[0,1,2,3]，B bases=[0,0,0,2]。正确 row 3 是 [4,8]；错误地全共享 b0 会产生 [1,2]。实际 guard 因 b3≠b0 拒绝共享。组 1 中 rows 4、5 被输出，6、7 不被输出。[E3]

这个构造检查跨 batch 逻辑；不是 FloatLib 正式执行或 acceptance 数据。

### 8.2 rowWord 选择的就是原 row

对任意实际 `r : Fin (batch*m)`：

```text
g = floor(r/4)
rr = r mod 4
g < ceil((batch*m)/4)
4*g+rr = r
```

`group_bound` 与 `row_decomposition` 建立这些关系。rowWord_eq 再使用：

```text
floor(r/m)*m + r mod m = r
```

对齐 DirectRows 的 A base。这个 Nat 欧几里得恒等式不额外要求 m>0；当 m=0 时，这里的 Fin(batch*m) 本来也没有值。

尾部可能仍执行多余 lane 的 finish/replay，但没有这些 lane 到有效输出的依赖。证明不需要假设多余 lane 恒为 +0，只需要它们不被 rowWord 选中。

### 8.3 实际有效 A/B 读取界

对于真实输出 row r、col j 和 consumed k，令 b=floor(r/m)：

```text
r < batch*m
k < n
j < p
```

r 的存在推出 m>0，因而 b<batch。于是：

```text
r*n+k < (r+1)*n ≤ batch*m*n
(b*n+k)*p+j < (b*n+k+1)*p ≤ batch*n*p
```

R11 的 B 地址是 `(b*n*p+j)+k*p`，原参考使用 `(b*n+k)*p+j`。二者是整数地址恒等式，附件 `index_address` 正是该桥；没有浮点交换或重结合。

诊断片段中的 `selected_read_bounds` 直接针对实际 A/B Vector 证明两个实际 getD 索引的边界，而不是把它们放进 theorem 前提。这不是 R11 原证明新增的必要假设，主要用于防止本地后续改成非 total 读取时漏掉真实义务。

### 8.4 core 到原 spec

core_eq_rows 由 `Vector.ext` 取 q<batch*m*p。在这个局部上下文中证明 p>0，然后使用：

```text
r=q/p < batch*m
j=q%p < p
```

因此从未在全局假设所有 p 都正。对 p=0 的空向量，根本不存在要检查的 q。Vector.getElem_ofFn 和 Vector.getElem_flatMap 将两边化为同一个 rowWord_eq 实例。

之后的原链为：

```lean
rw [R11CrossRows.core_eq_rows, DirectRows.core_eq,
    DirectSmall.core_eq_reference]
exact referenceBmm_spec batch m n p A B
```

最后 bmm_spec 的目标仍然是原 `.get = bmmSpec ...`，不是一个放宽后的新规格。

## 9. 零维与任意 Nat 的覆盖

| 情形 | 实际 submission dispatch | 通用 R11 证明里的含义 |
|---|---|---|
| m=0 | 4≤batch*m 为假，回父本 | 输出长度 0；无有效 r/q，不需要对实际输出除以 0 |
| batch=0 | 同上 | 同上 |
| p=0 | p=2 为假，回父本 | core 输出为空；lambda 内 p>0 从不存在的 q 条件推出 |
| n=0 | 0<n 为假，回父本 | 通用 dot8 count=0，pack 空，无 uget；八个 +0 空点积匹配原 finish |
| p=1 | p=2 为假，回父本 | core 的更一般 hp≤2 定理仍只输出 j=0 |
| p>2 | p=2 为假，回父本 | R11 core 的 hp≤2 不适用；并不妨碍总 bmm_spec |
| n≥USize.size | n<USize.size 为假，回父本 | 不进行这个新路径的 Nat→USize count 转换 |
| 其他超出机器长度 guard 的尺寸 | 新路径拒绝，回父本 | 原任意 Nat spec 保留；没有用有限尺寸枚举代替 |

还要区分形式语义与资源可实现性：这里的任意 Nat 定理描述纯函数结果与分支，不证明计算任意巨大输入都能在有限内存／时间内成功分配。source guard 也不是整个 Lean runtime 的内存资源合同。

## 10. 可能的 elaboration 失败点与精确修补假设

本表列的是**检查点和条件修补**，不是本轮编译错误日志；没有运行编译器就不能称其为已经出现的错误。

| 检查点 | 必须实际关闭的义务 | 静态判断／最小动作 |
|---|---|---|
| packShared_eq | let-sharing 展开后两 P12 值相同 | rfl 合理；不建议改 |
| natLoop_lane | k<n 下 n-(k+1)<n-k | 可选追加 decreasing_by omega，20 字节 |
| wordLoop_eq | hread 匹配真实 uget；递归 theorem 的 k+1 上下文及 proof 参数对齐 | 与原 Packed10Index.loop_eq 模式一致；不建议预先重写 |
| wordLoop_eq termination | next_decreases 的隐式 count/k 从 hk 解析正确 | 原 helper 的 n/k 是显式绑定的隐式参数 `{n k : USize}`；实际编译仍待跑 |
| dot8_lane | zero8 与八个 Float32.ofBits 0 的定义相等 | 原 simpa only [lane_zero] 合理；不新增零值假设 |
| finish8_word | 8 个 Fin case，raw round-trip 在 simp 中触发 | 使用实际 rebuild；不替换 finish |
| blockAt_word | laneIndex 的 mod/div 化为 r,j，zero32 对齐 | 小有限类型 case 属证明拆分；不等同于只跑有限浮点测试 |
| rowWord_eq | let g/rr/jj 的 Fin 投影露出后应用两条 row 恒等式 | 若实际报错，加两处 dsimp only 的备用片段 |
| core_eq_rows | Vector.getElem_flatMap/ofFn 得到 q/p,q%p；Fin proof 参数无关 | 原 simp 列表与父本同源；不制造 m>0/p>0 的全局额外假设 |
| final bmm_spec | conjunction 投影、hp : p≤2、原 .get 函数目标匹配 | h.2.2.2.1 和 Nat.le_of_eq h.1 在类型上相符 |
| 资源上限 | 各 theorem elaboration 不超指定选项 | 静态无法推断；需原设置真实记录 |

条件补丁的全部改变是：

```diff
 termination_by n-k
+decreasing_by omega

 def wordLoop
```

精确 unified diff 位于 R11-W01-conditional.patch。它只落在 theorem natLoop_lane 内，runtime natLoop 本身不改。若原 SHA 编译成功，没有由本轮证据支持必须应用此补丁的理由。

## 11. allowed options、源码限额和后续实际执行

原文件和条件文件唯一 import 均为 `ContractTensor`；两个文件都没有 `set_option`。静态扫描排除了 `sorry/admit/unsafe/extern/implemented_by/axiom/native_decide` token；这只是源码扫描，不能代替传递公理审计。[E2]

上下文给出的资源上限为：

| 项 | 上限 | 本轮是否实际用固定 Lean 确认 |
|---|---:|---|
| recursion depth | 8192 | NOT_RUN |
| heartbeats | 4000000 | NOT_RUN |
| synth pending depth | 400000 | NOT_RUN |

诊断时应显式关闭 autoImplicit 和 relaxedAutoImplicit，防止未声明变量被悄悄补成参数。R11 新声明的变量在源码中已显式绑定，但严格选项下的实际接受仍需验证。不要把较宽松配置下的成功当成固定官方设置成功。

以下命令是交给现成固定环境的**执行计划，未运行**。上下文未附 runner 文件或固定 Lean 的选项注册表，所以 `maxSynthPendingDepth` 这个 CLI 拼写也应先由固定二进制的真实接受结果确认；不能用报告中的拼写代替该检查。若选项拒绝，保留错误，使用官方 runner 的真实参数，不能静默删除上限。

```bash
# 在已经固定 Lean/FloatLib/official 4b7 的现成工作目录执行。
# 先记录工具链版本、实际 argv、工作目录、LEAN_PATH 和依赖 commits。
lake env lean --version
lake env lean --githash

# 先把原 Kernel 原字节复制成隔离目录内的 Kernel.lean，
# 不覆写本地 actor 正在工作的文件。
lake env lean \
  -DautoImplicit=false -DrelaxedAutoImplicit=false \
  -DmaxRecDepth=8192 -DmaxHeartbeats=4000000 \
  -DmaxSynthPendingDepth=400000 \
  -o R11Original.olean Kernel.lean
```

如果主文件通过，再在单独审计文件里串接：原 Kernel、R11-W01-audit.fragment.lean、R11-W01-edge-cases.fragment.lean，使用相同设置检查。该文件会检查原四 spec 的准确类型并打印传递公理。**这些诊断片段不是提交文件，不要直接塞进 256000 字节限制下的 Kernel。**

若原文件仅在 natLoop_lane 的默认 decrease 处失败，再对独立副本应用条件补丁，并重新记录精确 SHA 与完整结果。若失败在别处，条件补丁不能冒充对应修复。row-fallbacks 片段的同名 rowWord_eq 是替换片段，不能直接附加到已有同名 theorem 后面。

主文件和诊断通过仍只是形式检查的一部分；继续使用原官方 statement build、kernel replay、公理 allowlist（仅 propext/Classical.choice/Quot.sound）、checksum 和 25 组 paired timing。官方 runner 未提供，包里没有伪造一份“等价全 gate”。

本轮可立即复现的真实检查：

```bash
python3 R11-W01-verify.py
```

它核验精确父本、条件源码、patch 正反向字节关系、导入、source options 和禁用 token，并明确输出 Lean NOT_RUN。运行时定义字节保留已由这一检查确认；生成 C/汇编是否逐字节相同未检查。

## 12. 文件说明与停止条件

| 文件 | 用途 |
|---|---|
| R11-W01-report.md | 本完整报告 |
| Kernel.original.lean | 精确指定父本，252609 字节 |
| Kernel.conditional.lean | 仅加 theorem decrease 的条件候选，252629 字节 |
| R11-W01-conditional.patch | 唯一已组装到条件 Kernel 的补丁 |
| R11-W01-natLoop_lane.fragment.lean | 同一 theorem 的完整替换片段 |
| R11-W01-row-fallbacks.fragment.lean | 未并入 Kernel 的 rowWord 正规化替换及真实读取界草稿 |
| R11-W01-audit.fragment.lean | 原四 spec、真实读取／机器桥、core→原规格及公理打印 |
| R11-W01-edge-cases.fragment.lean | m/p/n/batch 为零及机器尺寸拒绝分支诊断 |
| R11-W01-verify.py | 精确字节／限额／token 复核 |
| R11-W01-address-witnesses.py | 地址构造复现，不执行浮点 Kernel |
| evidence/ | 环境、静态结果、整数见证及分段审查记录 |
| R11-W01-manifest.json、SHA256SUMS.txt | 工件 SHA 和验证状态 |

manifest 不给自己或 ZIP 写循环哈希；内部 SHA256SUMS 包含 manifest，外部 R11-W01-SHA256SUMS.txt 给最终 ZIP 的哈希。

停止理由是：本环境缺少指定工具链和依赖，外部固定源码访问也不可用；继续重复未编译 proof 改写不能增加 acceptance 证据。已经完成可做的具体源码连接、反例、条件修补和字节核验。下一项能改变结论的证据是**本地固定环境对原 SHA 的第一份真实编译诊断**，而不是更多有限浮点样例或额外 SIMD 估计。

## 来源与证据定位

- **[S0]** 用户所附 astra-web-r11-source.txt；上下文及完整 Kernel。源码锚点：Submission.R11CrossRows 的 packGeneral/packShared/pack_a/b、natLoop_lane、wordLoop_eq、dot8_lane、finish8_word、blockAt_word、blockRows_word、rowWord_eq、core_eq_rows；以及同文件 Packed10.finish_eq_dot、Packed10Index.stepNat/next_decreases、DirectRows.core_eq、DirectSmall.core_eq_reference、referenceBmm_spec、最终 bmm_spec。以上源码随包保存，SHA 见第 2 节。
- **[E1]** evidence/environment.json：本轮实际工具链探测及受限网络结果。
- **[E2]** evidence/static-verification.json：R11-W01-verify.py 的本轮真实输出。
- **[E3]** evidence/address-witnesses.json：R11-W01-address-witnesses.py 的精确整数构造输出；不是 FloatLib/Lean 验收。
- **[E4]** evidence/pack-dot-audit.md、finish-audit.md、row_core_audit.md：分段审查记录。多个审查者意见一致不增加编译或数学公理证据。
- **固定版本来源状态**：Lean commit 293d5d0c0c3f3dded4688b3ccd6a33939ac5102b、FloatLib commit 0d91825727839f597fd06b22fdd038ea21480f0c、official commit 4b7e83841cc0c32c6529f533923c73d33b5ecf97 来自附件上下文。本轮未独立取得它们的工具链／仓库。
- 尝试访问的公开一手入口：[Lean Vector/Lemmas](https://raw.githubusercontent.com/leanprover/lean4/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Vector/Lemmas.lean)、[Lean Array/Basic](https://raw.githubusercontent.com/leanprover/lean4/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Array/Basic.lean)、[Lean UInt/Lemmas](https://raw.githubusercontent.com/leanprover/lean4/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/UInt/Lemmas.lean)。内容访问失败；没有把未读到的页面用作 API 已确认的证据。
