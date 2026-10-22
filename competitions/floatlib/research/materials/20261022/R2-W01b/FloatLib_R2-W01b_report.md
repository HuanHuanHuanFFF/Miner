# FloatLib R2-W01b：把有符号零并入表驱动转换

**研究日期：2026-10-22（Asia/Shanghai）**  
**状态：数学推导完成；有限诊断完成；一组 C surrogate 完成；Lean 编译、生成码与目标性能均为 NOT_RUN / UNKNOWN。**

## 0. 结论与本轮决策

新准入条件在指定的 **UInt32 回卷、无符号比较** 语义下成立，没有发现反例：

\[
 ((a-1)\bmod 2^{32}\ge \mathtt{0x0bffffff})\land
 (a<\mathtt{0x7f800000})
 \iff a=0\;\lor\;
 (\mathtt{0x0c000000}\le a<\mathtt{0x7f800000}).
\]

其中 `a=u&0x7fffffff`。准入域恰是 **±0 与 biased exponent 24..254 的 normal**。两个零都可以执行同一个 `M.toFloat32 * table[j]`，结果保留原零符号；每个输入仍在原位置参加一次 add。

**本轮最重要的性能修正是：官方 ReLU 的零并非随机散布。** 固定 `Bench.lean` 的 LCG 两个系数均为奇数，最低位每步翻转；固定 `sumRelu` 用最低位决定零，因此 1000 项向量中的 500 个 `+0` 与 500 个正 normal 严格交替。[S1]、[S2] 这不影响新转换的正确性，却直接影响“消除随机零分支能改善官方计时”的推断。

唯一 C 对照中，合并准入相对旧 `u==0` 路径的配对中位耗时比：

- 自造随机约 50% 正零：**0.228435**，7/7 轮更快。
- 官方形状的交替 ReLU：**0.997870**，仅 4/7 轮更快，最后两轮约为 **1.105 / 1.108**。
- 三个官方形状类等权合计：**0.983720**，也只有 4/7 轮更快。

这些数据支持“移除随机零分流有工程价值”，**没有建立官方 ReLU 的显著增益，也没有建立 Lean 性能优势**。普通 `Array Float32` 的初始化、对象读取、解箱以及可能的 `once` 检查未被平铺 C 表模拟。没有测硬件 branch-miss 计数，因果判断只限于与该机制一致的观察。

建议将本轮零域与合并接口交给正在闭合 normal 定理的路线，作为小范围、可选择的 converter 替换。下一步最多做现成固定环境内的候选编译与生成码检查，并在完整原生 ordered sum 上配对比较。若官方分布没有稳定增益，就停止这一性能分支；不扩大为新的分段扫描、固定锚点或大规模形式化项目。

## 1. 范围、合同与证据边界

本轮只使用本消息、三个指定公开版本和本轮新造输入；未读取旧报告、旧 ZIP、旧会话、旧项目附件或私有源码。旧包保持原样。已通过 gate 的原生 ordered sum / bmm 与末尾 finite 守卫视为用户给定基线，本轮没有重证、改写或重新宣称该成果。没有安装 Lean 工具链，没有正式提交，没有修改官方配置或固定依赖。

固定版本：

| 项目 | 固定版本 |
|---|---|
| 官方 kernels | `978cc5b445edb9943fd9953b0a9037d97a9f33a8` |
| FloatLib | `0d91825727839f597fd06b22fdd038ea21480f0c` |
| Lean | `v4.34.0`，公开 tag 解析为 `293d5d0c0c3f3dded4688b3ccd6a33939ac5102b` |

合同保持 binary32、RN-even、gradual subnormal。sum 从 `+0` 开始，依原索引逐次加法；本轮只替换逐输入转换函数，不过滤零、不改输入次序、不融合 mul/add。非准入输入使用原 `Float32.ofBits`。原始 raw FloatLib 回退继续接收原始 raw 输入，不能改为接收被 native 规范化后的数据。[S3]、[S4]

| 证据层 | 本轮状态 | 能说明什么 |
|---|---|---|
| 准入、零符号、合并的纸面证明 | 完成 | 给出全域数学命题及逐步推导 |
| 固定公开源码核对 | 完成 | 91 个相关源码文件及真实声明、导入链、运行时/编译器机制 |
| 候选全文词法与 import 检查 | 通过文本检查 | 不是 elaboration、kernel replay 或完整 gate |
| 独立整数诊断 | 已运行 | 136,705 个不同 raw word、全部 512 个表索引；有限证据 |
| 单一 C surrogate | 已运行一次预设实验 | 871,620 次转换检查、768 条完整 sum；168 条计时记录 |
| 候选 Lean 编译 | **NOT_RUN** | 当前 PATH 没有 lean / lake |
| Lean 依赖审计、原生生成码 | **NOT_RUN** | 没有生成 C 或汇编可供断言 |
| 完整新 Kernel / 官方 gate | **NOT_RUN** | 候选是条件化组合文件，不是完成的 Kernel |
| 目标速度与成功率 | **UNKNOWN** | 不从 C surrogate 外推 |

来源核验：三个仓库共 1,660 个 Git tree 对象按 Git 编码重建并与固定 commit 的 tree 对照；91 个下载源码共 2,147,157 字节，逐个 blob SHA-1 与 SHA-256 核验。文件清单、URL 和 hash 见 `sources/source_manifest.json`；完整性记录见 `sources/tree_integrity.json` 与 `sources/source_integrity.json`。这验证了本轮使用的文本来源，不是 Lean 构建记录。

## 2. 先反驳：哪些几乎相同的写法会错

以下反例均为本轮自造，已在独立整数诊断或 C 转换诊断中检查。正确的新条件未发现反例；反例用于明确边界不可放松。

| 错误变化 | 最小见证 | 后果 |
|---|---|---|
| 用 Nat 饱和减法代替 UInt32 回卷 | `u=0x00000000` | `a-1` 变 0，正零被拒；准入等价和同路径目标失败，旧转换回退仍可保正确 |
| 第一个比较用严格 `>` | `u=0x0c000000` | 恰处 E=24 下界的合法 normal 被拒；这是路径覆盖错误，不自动是输出错误 |
| 第一个阈值降低 1，改为 `0x0bfffffe` | `u=0x0bffffff` | E=23 非零值被接受，表项却是 +0，输出被错误改成 `0x00000000` |
| 丢掉有限上界，或把 `<0x7f800000` 改成 `≤` | `u=0x7f800000` | +Inf 的表项是 +0，转换错误变成 +0 |
| 下界计算忘了先去掉符号，而上界仍用 magnitude | `u=0x80000001` | 最小负次正规被误放行，表乘法输出 -0，丢掉非零值 |
| 把表第 256 项改为 +0 | `u=0x80000000` | 原 -0 转成 +0；数值比较和某些完整 sum 检查都可能漏报 |

**最强的守卫反例是无穷：错误接受 +Inf 会使 native 结果变成有限的 +0，既有“末尾非 finite 则回退”因此也不会触发。** 正确的 converter 准入证明不能靠最终 finite 守卫补救。

**最强的零位测试反例是单项 `[-0]`：**正确 converter 产生 -0，若错误 converter 产生 +0，两者从 +0 开始求和都得到 +0。故“完整 sum 比特一致”不能替代逐项转换比特一致。我们的诊断分别检查 converter 与整个 sum，没有只检查后者。

对 NaN 还要区分两个目标：`0xffa12345` 经原 `Float32.ofBits` 的 native 可观察编码规范化为 `0x7fc00000`；错误放入表路径则变成 -0。前一个是原 converter 的既定行为，不能拿它当作完整 raw FloatLib 算法可以丢 payload 的依据。[S5]、[S13]

## 3. 命题 A：精确准入等价

定义无符号整数常数：

\[
Q=2^{32},\quad T=\mathtt{0x0bffffff}=201326591,\quad
L=T+1=\mathtt{0x0c000000},\quad H=\mathtt{0x7f800000}=2139095040.
\]

### 3.1 任意 UInt32 的一般命题

对任意 `a : UInt32`，无需先假设 `a` 已去掉符号，均有：

\[
G(a)\iff a=0\lor(L\le a<H),\qquad
G(a):=((a-1)\bmod Q\ge T)\land(a<H).
\]

证明分两种情况：

1. `a=0`：回卷差是 `Q-1=0xffffffff`，大于 T；同时 `0<H`，两个条件都真。
2. `a>0`：减一不回卷，因此第一个条件等价于 `a-1≥T`，再等价于 `a≥T+1=L`；与第二个条件合取即得目标区间。

反方向同样成立：零满足两个条件；`L≤a<H` 意味着 a 非零且 `a-1≥T`。上界由第二个条件直接提供。这里的比较全部是无符号比较。

### 3.2 代入 magnitude 后对应的浮点类

`a=u&0x7fffffff` 满足 `0≤a<2^31`。掩码为零当且仅当原编码是 `0x00000000` 或 `0x80000000`。另一方面：

\[
L=24\cdot2^{23},\qquad H=255\cdot2^{23}.
\]

因此 `L≤a<H` 恰好是 biased exponent 在 24..254，而 fraction 任意的 finite normal，符号也任意。E=1..23 的 normal、全部非零 subnormal、±Inf 和所有 NaN 均不准入。不能把该域缩写成“所有 normal”。

关键边界如下，负号编码完全对称：

| magnitude a | 回卷 `a-1` | 结果 |
|---|---|---|
| `00000000` | `ffffffff` | 接受零 |
| `00000001` | `00000000` | 拒绝 |
| `0bffffff` | `0bfffffe` | 拒绝 E=23 最大值 |
| `0c000000` | `0bffffff` | 接受 E=24 最小值 |
| `7f7fffff` | `7f7ffffe` | 接受最大 finite |
| `7f800000` | `7f7fffff` | 被第二条件拒绝 |
| `7fffffff` | `7ffffffe` | 被第二条件拒绝 |

### 3.3 Lean 草稿的证明策略

候选 `wrap_gate_iff` 使用固定核心引理 `UInt32.toNat_sub`：

\[
(a-b).toNat=(2^{32}-b.toNat+a.toNat)\bmod2^{32},
\]

以及 `UInt32.toNat_lt_size`、比较的 toNat 等价式，将目标化为关于 `a.toNat` 的固定常数模算术，再交给 `omega`。mask→mod 使用 `Nat.and_two_pow_sub_one_eq_mod`。这些名字与导入链已核对固定源码。[S7] 完整候选见附录 A 和 ZIP 的 `lean/AdmissionZero.lean`。

候选不依赖普通 `bv_decide` 的编译反射路线。固定版本的该路线可引入额外依赖，而本合同只允许三项基础公理；普通 `decide` 的默认实现与 `omega` 则构造供内核核查的证明项。**这说明选择了可审核的证明方式，并不等于本文件已经编译或通过依赖审计。**[S8]、[S14] 普通 decide / omega 的具体源码分支与导入链见随包 `appendices/source_audit.md`。

## 4. 命题 B：±0 的 native 逐位等价

表与整数定义完全使用本消息给出的公式：

```text
j = u >>> 23
e = j & 255
s = (j & 256) << 23
scaleBits(j) = s | ((e-23)<<23), if 24<=e<=254; else s
M = (u & 0x007fffff) | 0x00800000
P(u) = UInt32.toFloat32(M) * table[j]
```

`j` 对任意 32 位输入都在 0..511。表总计 512 项，其中 462 项为带符号非零 scale，50 项为带符号零。**表里有 50 个零项不代表相应的全部输入都可走快路**；准入域中的零只占两个 raw word。

### 4.1 正零

代入 `u=0`：`j=0, e=0, s=0, M=2^23`。表第 0 项的位为 `0x00000000`。`UInt32.toFloat32(2^23)` 精确等于位为 `0x4b000000` 的正有限值。固定 native model 的 finite×zero 分支取两操作数符号乘积，因此：

\[
P(\mathtt{0x00000000})=2^{23}\times(+0)=+0,
\quad bits(P)=\mathtt{0x00000000}.
\]

### 4.2 负零

代入 `u=0x80000000`：`j=256, e=0, s=0x80000000, M=2^23`。表第 256 项是 -0，不是 +0。于是：

\[
P(\mathtt{0x80000000})=2^{23}\times(-0)=-0,
\quad bits(P)=\mathtt{0x80000000}.
\]

这是带符号零的运算规则，不是仅用实数等式“0=0”推导。正的 finite M 排除了 Inf×0 的 NaN 情况；没有溢出或非零下溢。舍入模式在这两个 exact zero case 中不会制造另一个非零值。[S6]

### 4.3 证明落点与实际表读取

候选使用顶层、与输入无关的 `Array.ofFn` 建立实际 512 项数组，再给出：

- `scaleTable_size` / `scaleTable_entry`：数组长度与每个表项公式。
- `tableIndex_toNat_lt`：所有 raw 输入索引均小于 512。
- `scaleAt_eq`：有证明的数组读取与公式相等。
- `zero_fields`：两个零对应的完整 `u/j/M/scaleBits`。
- `zero_mantissa_conversion`：`2^23` 的数值转换确为 `0x4b000000`。
- `tableProduct_positive_zero` / `tableProduct_negative_zero`：先证明 `Float32` 命题相等，再用 `congrArg Float32.toBits` 得到逐位相等。
- `tableProduct_zero_bits`：最终结论就是原零编码 `u`，包括负零。

闭合零实例采用 `decide`；不拿 IEEE 的 `==` 或实数 `toReal` 相等代替位相等。`Float32` 的 `BEq` 会把 ±0 判为相等，而结构性的命题相等与 `toBits` 能区分它们。[S5]、[S6]

`Array.ofFn` 的表是一次构造的闭合数组，不是每次输入重算 e/s/scale。它是依据消息公式给出的自包含表定义；接入已有常量表时，应保留现有表并证明相应条目读取与本公式一致，不为迁就草稿强制改写已有常量布局。

## 5. 命题 C：与 normal 定理的明确组合接口

令 `N(u)` 表示 `0x0c000000≤magnitude u<0x7f800000`。本轮没有证明一般 normal 乘法重构，只请求另一条路线提供以下三个接口之一。

### 5.1 推荐的命题相等接口

```lean
hNormal : ∀ u, NormalBand u → tableProduct u = Float32.ofBits u
```

由新准入 iff，接受输入必为 zero 或 NormalBand：zero 分支使用本轮命题 B，normal 分支直接使用 `hNormal`。拒绝输入按定义返回原 `Float32.ofBits`。因此组合得到：

```lean
∀ u, convert u = Float32.ofBits u
```

这里结论覆盖所有 raw word，但整个定理仍**显式依赖 hNormal**。它叫组合定理，不叫已经完成的新 Kernel，不补写无证据的 normal 证明。

### 5.2 如果另一方提供的是完整 word 定理

候选同时接受两种 word 形式：

```lean
∀ u, NormalBand u →
  (tableProduct u).toBits = (Float32.ofBits u).toBits
```

用 `float32_eq_of_toBits_eq` 得到命题相等。该引理按固定核心的两层结构字段展开，最后利用证明不可区分性，不经浮点数值比较。

更强的 raw 形式也可以直接接：

```lean
∀ u, NormalBand u → (tableProduct u).toBits = u
```

这里无需重做一份 normal 乘法证明，也无需假设任意 raw NaN roundtrip。固定 FloatLib 的 `ExecFloat.Binary.toFloat32_ofFloat32` 加上 native codec 定义给出正确方向：

\[
\forall x:\mathrm{Float32},\quad Float32.ofBits(x.toBits)=x.
\]

将 `x=tableProduct u` 代入，然后用已给出的 word 等式改写其 bits，便得 `tableProduct u=Float32.ofBits u`。这是 **native 值→其 canonical bits→native 值** 的 roundtrip；与错误的“任意 raw u→native→raw 仍等于 u”不同。[S9]

### 5.3 整段有序计算如何合并

候选给出 `foldl_convert_eq`：对于任意初始 accumulator、任意二元 `step`、同一原始列表，逐元素替换 converter 后左折叠完全相等。取 `step=Float32.add`、初值为 +0 即对应 native 有序求和。归纳只替换当前输入的转换结果，随后使用同一个 step；没有任何可结合性或交换性假设。

另给 `replace_decoder`：把整个已有 native sum / 最终 finite guard / raw 回退看成接受 decoder 的纯上下文，利用函数外延和 congruence 替换。实际落地时仍须把它接到现有函数的真实类型、数组遍历和最终义务；泛型上下文等式本身不证明那些已有程序已经实现合同。

接口接入步骤：

1. 让现有表的第 0/256 项与 `scaleAt` 的相应位等式对齐，并保留现有 512 项表布局。
2. 将 normal 词定理接到 `normal_value_of_bits` 或 `normal_value_of_raw_bits`；若另一方的 NormalBand 用 exponent 表达，只补 guard-to-exponent 的位域接口。
3. 仅替换 native 路径的逐输入 decoder，保留每次原序 add。
4. 用 `convert_eq`、`replace_decoder` 或原循环归纳替换引理，复用已完成的末尾 finite 守卫证明。
5. 回退函数仍接收原始 raw 向量。不要先覆盖原始存储，再试图从 native `toBits` 恢复 NaN payload。

## 6. NaN、次正规、溢出与零：两层合同不能混淆

| 输入/行为 | 新 converter | 既有完整算法层 |
|---|---|---|
| ±0 | 同表乘法路径，保留原零位 | 每个零继续参加原序 add |
| E=24..254 normal | 依赖另一方 normal 重构定理 | 原序加法及其逐步舍入不变 |
| 非零 subnormal、E=1..23 normal | 原 `Float32.ofBits` | 原处理方式不变 |
| ±Inf、NaN | 原 `Float32.ofBits`，包括原 NaN 规范化 | 非 finite 时原 raw FloatLib 回退负责精确行为 |
| 有限输入在累加中溢出 | converter 等价不能消除溢出 | 既有末尾 finite 检查/原回退继续负责 |
| 消去、零结果、次正规 accumulator | 输入 decoder 不改 add 的结果 | 继续使用既有原生逐步加法等价 |

本轮的全域转换结论应写成：

\[
bits(convert(u))=bits(Float32.ofBits(u)),
\]

而不能把右边无条件改写成 `u`。固定 runtime 明确规范化 NaN；FloatLib 的 raw codec `toBits32_ofBits32` 则保留原始 word，这两个接口的合同不同。[S4]、[S5]、[S9]

因为是逐输入的同值替换，所有累加前缀、消去、溢出、次正规数与 signed-zero 行为都由同一 add 序列逐步对应，不需要新的“所有前缀落在某 binade”的检查，也不需要根据最终实数和猜测中间行为。这正是本轮比固定锚点路线窄得多的地方。

## 7. 固定 Lean 源码审查：可确定与不能确定的控制流

### 7.1 同路径并不等于完全没有跳转

新准入的两个比较对所有接受输入都是真。即使 `&&` 编成两层条件跳转，零和准入 normal 都沿同一接受路径；它们不再被 `u==0` 单独分开。

固定 `Bool.and` 的编译实现具有短路结构，LCNF case 可以发出 C `if`。把 `&&` 改写成 `Bool.and`、提前绑定两个 Bool 或改成 nested if，都不足以承诺机器码 branchless；编译器仍能变换这些形式。[S10] 本轮候选直接使用两个 UInt32 比较的合取，不为追求拼写上的 branchless 引入额外转换。

### 7.2 数值转换、乘法与零值没有额外语义分流要求

固定 native primitive 将 `UInt32.toFloat32` 对应为 C 的 `(float)a`，mul 对应 `a*b`，add 对应 `a+b`。两个零的 M 与普通 normal 一样都在 `[2^23,2^24)` 内；表元素 `+0/-0` 都可以直接参加普通 float 乘法。模型里区分零的逻辑定义不等于运行时必须调用软件分情况函数。[S5]、[S6]

实际候选是否被充分内联，是否产生额外 wrapper/call，必须由 Lean 生成码确认。此项 **NOT_RUN**。

### 7.3 表的静态性、一次初始化与 once 不是同一件事

固定编译器有三种相关路径：[S11]

| 路径 | 源码可确定的机制 | 对本候选的限制 |
|---|---|---|
| simple-ground 静态对象 | 部分闭合 constructor / literal / array push 结构直接发射静态对象 | Float32.ofBits 调用及 Float32 boxing 不能仅因常量输入就视为平铺静态 float 字面量 |
| 普通零参数全局 def | 模块初始化调用构造并标记 persistent；普通引用可直接读全局值 | 顶层 scaleTable 可走此机制，但具体输出未生成 |
| `_closed` 的非 simple-ground 项 | 带 once cell；引用可调用 lean_obj_once，热路径有状态测试 | 是否存在、是否在内循环、是否经 C 优化消除均 UNKNOWN |

官方 `runSum` 在计时 `bestSum` 前先执行一次完整 checksum sweep，因此若表在第一个正常输入时惰性初始化，该首次构造通常已在未计时 sweep 中发生。这个源码顺序不消除可能存在的**每次读取** once 热路径成本。[S2]

### 7.4 Array 的 bounds 与 boxing

普通 `Array Float32` 的槽位是对象指针。运行时 Float32 boxing 分配保存四字节 float payload 的对象，unboxing 从对象取值；不是一个语义上自动等于 2048 字节的 `float[512]`。持久对象、借用读和编译器优化可减少引用处理，但不能仅看 Lean 源码推定它们都消失。[S12]

候选用 `table[index]'proof`，并证明 `index<512`，避免主动使用 `!` / `getD` 的语言级越界 fallback。C runtime core 仍有 assert；实际构建是否保留，必须核对既定构建产物，不能通过改选项去排除。

装箱本身不按浮点数值是否为零区分表示；正零、负零、normal 都是 Float32 对象。源码没有要求对零建立特殊对象标签，但查表地址、缓存与引用处理仍可能有成本。本轮无法给出完整新 Lean 循环中“零相关不可预测分支为零”的实测证书。

## 8. 唯一 C surrogate 的预设方法

只有一组实验、三条路径，没有根据结果重新挑选向量或重复寻找单向量最好值。

| 路径 | 定义 |
|---|---|
| external_ofbits | 独立 C translation unit 的外部函数；bitcast 后按固定 runtime 的行为规范化 NaN；无 LTO，实际汇编保留每项调用 |
| old_zero_branch | 先 `u==0` 返回 +0，再检查 E=24..254，然后 M 数值转换、查表、乘法；其余调用同一外部 ofBits |
| merged_guard | 本题两个 UInt32 比较准入；接受值统一数值转换、查表、乘法；其余调用同一外部 ofBits |

三条路径都从 float +0 开始，for-loop 访问每个原索引，逐次执行一次 float add，最后包含相同的 finite 检查并返回结果位。没有额外浮点归约，没有 FMA，没有 skip-zero。计时还包括逐向量调用与 checksum；数据构造和一次性表构造另列。非 finite sum 在此诊断中会立即失败：**本 C 程序没有模拟整包的 raw FloatLib 回退**，计时数据全部有限且所有最终和有限。

固定配置：GCC 13.3.0，x86_64，AMD EPYC 9V74 80-Core Processor；进程固定到允许的 CPU 0，未锁频。RN-even、FTZ/DAZ 关闭由程序启动时读取并检查，未改全局浮点环境。编译参数是本独立诊断的 `-O3 -std=c11 -fno-fast-math -ffp-contract=off -fno-lto`，没有调整官方编译参数。

每类 **96 条不同向量×1000 元素**，逐类用 memcmp 核实向量不同。每轮每条向量都被计算 80 次，共 7 轮；方法执行次序覆盖六种排列后再重复一轮，类的先后次序也轮换。保留全部 168 条计时行，不取最好值作结论。表采用 **flat float[512]**，明确不模拟 Lean Array boxing、once 或实际向量载体。

前三类复用官方 LCG 和映射公式，但采用本轮三个新种子；没有声称重现 `runSum` 的共同 seed/salt 数据。候选转换与 sum 函数看不到种子或类名。其余类用本轮 SplitMix 风格自造 word。随机与成簇 50% 类拥有相同非零值序列和零个数，成簇类只改变自造输入中零的分布；**各算法对每条输入向量仍保持原索引顺序**。

## 9. 数据分布、初始化与原始数值结果

### 9.1 实际输入计数

| 类别 | 元素数 | 不同向量 | +0 | -0 | normal | 新路径准入/回退 | 零/非零相邻变化 |
|---|---:|---:|---:|---:|---:|---:|---:|
| `lcg_dense` | 96,000 | 96 | 0 | 0 | 96,000 | 96,000 / 0 | 0 |
| `lcg_relu_alternating` | 96,000 | 96 | 48,000 | 0 | 48,000 | 96,000 / 0 | 95,904 |
| `lcg_wide` | 96,000 | 96 | 0 | 0 | 96,000 | 96,000 / 0 | 0 |
| `random_relu50` | 96,000 | 96 | 47,686 | 0 | 48,314 | 96,000 / 0 | 48,359 |
| `random_relu25` | 96,000 | 96 | 24,096 | 0 | 71,904 | 96,000 / 0 | 36,174 |
| `random_relu75` | 96,000 | 96 | 72,065 | 0 | 23,935 | 96,000 / 0 | 35,721 |
| `clustered_relu50` | 96,000 | 96 | 47,686 | 0 | 48,314 | 96,000 / 0 | 96 |
| `random_relu_pmzero50` | 96,000 | 96 | 23,719 | 23,967 | 48,314 | 96,000 / 0 | 48,359 |

“零/非零相邻变化”按每向量内部 999 对相邻元素计数，官方交替类因此为 `96×999=95,904`。所有计时输入都在新准入域内。旧路径的 table 次数等于 normal 数，`u==0` 特例次数等于正零数，旧外部转换次数等于负零数；baseline 每项都调用外部转换。随机 ±0 类的收益同时包含去掉随机分支和减少负零回退调用，不能全部归因于正零分支。

### 9.2 初始化单独计数

| 初始化项目 | 本次原始计数 | 解释 |
|---|---:|---|
| 512 项 C 表构造 | **1,142 ns** | 一次测量，含 512 次外部 ofBits；不是稳定的初始化性能估计 |
| C 表存储 | **2,048 bytes** | 仅本 C flat 表，不能拿来描述 Lean Array Float32 |
| 8 类全部输入生成 | **3,165,492 ns** | 一次构造，未包含在每项热循环时间内 |

每条计时路径之前还预热本类全部 96 条向量一次，预热不计时。一次性构造、预热、正确性诊断与正式热循环计时都在源码和输出中分开。

### 9.3 每项耗时与配对结果

下面前三个时间列是各方法**各自七轮 ns/项的中位数**；比值列是**同轮 merged/old 比值再取中位数**。两者统计运算不同，不能用时间中位数直接相除来质疑或替代配对中位比值。

| 类别 | 外部 ofBits 中位 ns/项 | 旧路径中位 ns/项 | 合并中位 ns/项 | 合并/旧：配对比值中位数 | 合并更快轮数 |
|---|---:|---:|---:|---:|---:|
| `lcg_dense` | 3.397993 | 0.908185 | 0.875426 | **0.994875** | 4/7 |
| `lcg_relu_alternating` | 3.420229 | 0.859918 | 0.873836 | **0.997870** | 4/7 |
| `lcg_wide` | 3.447390 | 0.893678 | 0.857622 | **0.960255** | 7/7 |
| `random_relu50` | 3.412532 | 3.746633 | 0.862880 | **0.228435** | 7/7 |
| `random_relu25` | 3.468581 | 2.431810 | 0.909672 | **0.367272** | 7/7 |
| `random_relu75` | 3.396639 | 1.958863 | 0.892094 | **0.447385** | 7/7 |
| `clustered_relu50` | 3.439915 | 0.885146 | 0.876852 | **0.983026** | 6/7 |
| `random_relu_pmzero50` | 3.397211 | 4.733033 | 0.882399 | **0.185943** | 7/7 |

官方交替 ReLU 的七个原始配对比值依轮次为：

```text
0.997870, 0.988273, 0.934583, 0.975812, 1.025050, 1.105115, 1.107867
```

这个序列不支持稳定官方 ReLU 加速。其独立时间中位数之比为约 `1.016185`，与配对比值中位数 `0.997870` 并不矛盾。三个官方形状类等权总耗时的 paired 比值为：

```text
0.971887, 0.983720, 0.944863, 0.894872, 1.000241, 1.032761, 1.011771
```

该有限实验中的 wide 七轮同向改善和随机类大幅改善都保留在原始数据里；没有把 wide 的变化解释成零域扩展的数学收益，也没有在没有计数器和目标环境的条件下给它编造微架构原因。

三条路径与 external_ofbits 的比较用于记录原基线。**旧表路径已存在的优势不能算成本轮 zero 合并的新发现。** 本轮增量判断主要看 merged/old。

### 9.4 逐位正确性记录

单一 C 程序共检查 **871,620 次逐项转换**：包括所有符号×所有指数×7 个 fraction 代表、边界例、100,000 个自造 raw word，以及所有计时输入。所有准入判定和转换位均匹配；NaN 在这里比较的是原 ofBits 的 canonical 输出。之后逐条比对 **768 条完整 sum**，三臂结果全部相同。每轮同类三臂 checksum 相同。

独立 Python 整数模型另检查 **136,705 个不同 raw word**，覆盖全部 512 个索引、50 个带符号零表项和 462 个 normal scale 表项；另有 96 条不同的有限 1000 项向量，每臂实际执行 96,000 次加法，结果均一致。该模型是独立有限诊断，不是 Lean native 执行或全 2^32 穷举。

原始文件：`results/probe_conversion_cases.csv`、`probe_vector_results.csv`、`probe_rounds.csv`、`probe_distribution.csv`、`probe_setup.csv`、`probe_validation.json`、`probe_environment.json`；独立模型的完整边界与错误变体见 `results/independent_diagnostic.json`。

## 10. 实际 C 汇编证据与完整成本解释

在本次 GCC 生成物中，旧路径有 `test u,u; je ...` 的正零分流。跳到零路径后仍执行 `addss`，没有跳过该次 add。合并路径执行去符号 mask、回卷减一、两个边界比较；在所有准入值上两个拒绝跳转都不取，随后统一 `cvtsi2ss → mulss → addss`。

外部 ofBits 仍是逐元素 call，其函数体保留 NaN 检测与 canonical 选择。本次代码中该选择被编成浮点 unordered compare 加条件移动，而不是靠省掉 NaN 检测得到快基线。完整反汇编见 `results/probe_disassembly.txt`，并另提供三条 sum 与 converter 的摘录。

这验证了本 C 实现的控制流目标：**去掉按零/normal 分流的条件跳转，同时保留每次加法**。它不验证 Lean 输出的同一性质；C 程序也不是完全无分支。

定性成本式能解释为什么必须区分输入分布。记 table 路径的 mask、整数转换、表读取和乘法成本合为 K，零占比为 p。旧路径只对约 `1-p` 的输入付 K，但付出按零分流的预测成本；新路径对所有准入输入付 K，同时付固定的新守卫。若旧分支难预测，去掉误预测可能超过新增的 `pK`；若零严格交替、成簇或原分支已可预测，新增零乘法/查表就未必有回报。这里 K 只是定性成本符号，实际指令会重叠执行，不能把这些成本机械相加预测 ns。

未覆盖、因此保持 UNKNOWN 的成本包括：Lean table once/装箱/引用处理、真实 Binary32/Vector 读取、真实最终 finite primitive 的调用形状、拒绝域密集工作负载的性能、首次 Lean 模块初始化、完整 raw 回退的目标成本，以及官方 gate 时间分布。

## 11. 可送编译的文件与最小实施顺序

`lean/AdmissionZero.lean` 是独立候选文件，只有一条 `import ContractTensor`，没有诊断命令或注释；本次文本检查大小为 **8,829 bytes**，远低于单文件上限。全文按固定 gate 的实际禁词正则扫描，无命中；没有借助调整资源选项来宣称已完成编译。此状态只叫**文本检查通过**。

`diagnostics/AuditAdmissionZero.lean` 是同一候选正文加依赖输出命令，供现成固定环境诊断，不属于 Kernel 候选。它故意单独存放，不能拼进提交文件。所有诊断命令见 `diagnostics/COMMANDS.md`。

最小实施顺序：

1. 在现有固定环境编译候选，先确认 UInt32/Nat 化简、数组依赖索引和两个闭合零 case 在默认资源内通过；随后审计对应证明依赖。
2. 接入 normal 路线实际已经证明的 theorem，统一表读取名称和 NormalBand 的定义；不要用一个仍带 normal 前提的 `convert_eq` 冒充完整义务。
3. 在现有 converter 中替换唯一的准入判定，保留原循环、原最终 finite 守卫和原始 raw 回退数据。
4. 用既定构建过程观察生成 C 和汇编：确认原 `u==0` 分流消失，查表只构造一次，识别每项是否仍取 once、是否读/解箱多个对象，确认 add 次数与原索引顺序不变。
5. 先比较完整原生 sum 在官方 dense/交替 ReLU/wide 上的配对时间；随机零类作为额外机制诊断单列。没有稳定正收益就停止性能推广。

这一步序列不要求新的工具链、固定锚点形式化、normal 乘法重复证明或编译选项调整。本轮因没有 Lean 环境，停在可复核的候选与原始有限证据处。

## 12. 明确停止条件

- 任一 raw 输入违反准入 iff，或两个零的转换 `toBits` 不等于原编码：立即停止集成，先修复守卫/表项；末尾 finite 检查不能补救错误接受 Inf/NaN。
- 必须增加不允许的依赖、候选禁词、额外导入或修改固定环境才能编译：停止该证明实现，不把形式化缺口转移给合同。
- normal 定理尚未闭合：保留组合定理状态，不声称完整 Kernel。
- 生成码重新引入按零分流，或每项 once/对象处理成本抵消预期收益：停止按 C 结果推广，先决定这条小替换是否值得保留；不启动另一轮大范围表表示工程。
- 官方形状的完整 sum 配对结果没有稳定改善，或某类显著退化：停止性能合并。随机零 surrogate 的改善不能覆盖这个验收缺口。
- 任一完整 raw 特殊类失败，或现有 payload 回退被喂入 native 规范化后的数据：撤回 converter 集成。

本轮没有继续扩大固定锚点路线，也没有因为 C 随机零结果漂亮而增加第二组 C 优化实验。

## 13. 来源索引

以下都是固定公开一手源码，完整文件列表和内容 hash 随包提供。

[S1]: https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/bench/Bench.lean#L16
[S2]: https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/bench/BenchTensor.lean
[S3]: https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/contract/ContractTensor.lean
[S4]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native.lean
[S5]: https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Float/Float32.lean
[S6]: https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Float/Model/Unpacked/Operations/Mul.lean
[S7]: https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/UInt/Lemmas.lean
[S8]: https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/gate.py#L191
[S9]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Representation.lean#L48
[S10]: https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Prelude.lean#L1200
[S11]: https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Lean/Compiler/LCNF/EmitC.lean
[S12]: https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/include/lean/lean.h
[S13]: https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/runtime/object.cpp#L1987
[S14]: https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Lean/Meta/Tactic/BVDecide/Prover/Bitblast.lean#L26

| 编号 | 内容 |
|---|---|
| [S1] | LCG 系数与更新顺序 |
| [S2] | sumDense/sumRelu/sumWide，向量长度，checksum 与计时顺序 |
| [S3] | ordered sum/bmm 合同与唯一 import 入口 |
| [S4] | raw codec、native codec、NaN canonicalization 边界 |
| [S5] | Float32 结构、ofBits/toBits、mul/add、UInt32 数值转换 |
| [S6] | 核心 native 模型的 finite×zero 带符号分支 |
| [S7] | UInt32 回卷到 Nat 的真实引理 |
| [S8] | 全文词法 policy 与依赖白名单 |
| [S9] | native 值 roundtrip，可接 normal 全量词定理 |
| [S10] | Boolean conjunction 的编译结构 |
| [S11] | C 发射、静态/模块初始化/once 路径 |
| [S12] | native 算术 primitive、数组读取、Float32 box/unbox、once 热路径 |
| [S13] | runtime ofBits/toBits 的 NaN canonicalization |
| [S14] | BV 证明路线的 native 反射调用边界 |

额外链接：[runtime NaN 转换](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/runtime/object.cpp#L1987)、[闭合提取](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Lean/Compiler/LCNF/ExtractClosed.lean)、[Float32.Model](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Float/Model/Float32.lean)、[FloatLib mul specification](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Spec/Dyadic.lean#L67)。更多已核实的定理真名、行号与导入链见 `appendices/source_audit.md`。

## 附录 A：完整候选 Lean 片段

**NOT_RUN。** 下列正文与 ZIP 中 `lean/AdmissionZero.lean` 完全相同。它包含实际表、零域与准入证明草稿、normal 接口适配和有序折叠组合；不含完成的 normal 定理或完整比赛 Kernel。

```lean
import ContractTensor

namespace R2W01b

def magnitude (u : UInt32) : UInt32 :=
  u &&& 0x7fffffff

def fastOK (u : UInt32) : Bool :=
  let a := magnitude u
  decide (0x0bffffff ≤ a - 1) && decide (a < 0x7f800000)

def NormalBand (u : UInt32) : Prop :=
  0x0c000000 ≤ magnitude u ∧ magnitude u < 0x7f800000

theorem wrap_gate_iff (a : UInt32) :
    (decide (0x0bffffff ≤ a - 1) && decide (a < 0x7f800000)) = true ↔
      a = 0 ∨ (0x0c000000 ≤ a ∧ a < 0x7f800000) := by
  have ha := a.toNat_lt_size
  simp only [Bool.and_eq_true, decide_eq_true_eq, UInt32.le_iff_toNat_le,
    UInt32.lt_iff_toNat_lt, UInt32.toNat_sub, ← UInt32.toNat_inj]
  change a.toNat < 4294967296 at ha
  change
    (201326591 ≤ (4294967295 + a.toNat) % 4294967296 ∧
      a.toNat < 2139095040) ↔
    (a.toNat = 0 ∨ (201326592 ≤ a.toNat ∧ a.toNat < 2139095040))
  omega

theorem fastOK_iff (u : UInt32) :
    fastOK u = true ↔ magnitude u = 0 ∨ NormalBand u := by
  exact wrap_gate_iff (magnitude u)

theorem magnitude_toNat (u : UInt32) :
    (magnitude u).toNat = u.toNat % 2147483648 := by
  rw [magnitude, UInt32.toNat_and]
  change u.toNat &&& (2 ^ 31 - 1) = u.toNat % 2 ^ 31
  exact Nat.and_two_pow_sub_one_eq_mod u.toNat 31

theorem magnitude_zero_iff (u : UInt32) :
    magnitude u = 0 ↔ u = 0 ∨ u = 0x80000000 := by
  have hu := u.toNat_lt_size
  simp only [← UInt32.toNat_inj, magnitude_toNat]
  change u.toNat < 4294967296 at hu
  change
    u.toNat % 2147483648 = 0 ↔ u.toNat = 0 ∨ u.toNat = 2147483648
  omega

theorem fastOK_positive_zero : fastOK 0 = true := by
  decide

theorem fastOK_negative_zero : fastOK 0x80000000 = true := by
  decide

def tableIndex (u : UInt32) : UInt32 :=
  u >>> 23

def mantissa (u : UInt32) : UInt32 :=
  (u &&& 0x7fffff) ||| 0x800000

def scaleBits (j : UInt32) : UInt32 :=
  let e := j &&& 255
  let s := (j &&& 256) <<< 23
  if decide (24 ≤ e) && decide (e ≤ 254) then
    s ||| ((e - 23) <<< 23)
  else
    s

theorem tableIndex_toNat_lt (u : UInt32) :
    (tableIndex u).toNat < 512 := by
  have hu := u.toNat_lt_size
  rw [tableIndex, UInt32.toNat_shiftRight]
  change u.toNat >>> 23 < 512
  rw [Nat.shiftRight_eq_div_pow]
  change u.toNat < 4294967296 at hu
  change u.toNat / 8388608 < 512
  omega

def scaleTable : Array Float32 :=
  Array.ofFn fun j : Fin 512 => Float32.ofBits (scaleBits (UInt32.ofNat j.val))

theorem scaleTable_size : scaleTable.size = 512 := by
  simp only [scaleTable, Array.size_ofFn]

theorem scaleTable_entry (j : Fin 512) :
    scaleTable[j.val]'(by rw [scaleTable_size]; exact j.isLt) =
      Float32.ofBits (scaleBits (UInt32.ofNat j.val)) := by
  simp only [scaleTable, Array.getElem_ofFn]

def scaleAt (u : UInt32) : Float32 :=
  scaleTable[(tableIndex u).toNat]'(by
    rw [scaleTable_size]
    exact tableIndex_toNat_lt u)

theorem scaleAt_eq (u : UInt32) :
    scaleAt u = Float32.ofBits (scaleBits (tableIndex u)) := by
  simp only [scaleAt, scaleTable, Array.getElem_ofFn, UInt32.ofNat_toNat]

theorem zero_fields (u : UInt32) (h : magnitude u = 0) :
    (u = 0 ∧ tableIndex u = 0 ∧ mantissa u = 0x800000 ∧
      scaleBits (tableIndex u) = 0) ∨
    (u = 0x80000000 ∧ tableIndex u = 256 ∧ mantissa u = 0x800000 ∧
      scaleBits (tableIndex u) = 0x80000000) := by
  cases (magnitude_zero_iff u).mp h with
  | inl hu =>
    subst u
    left
    decide
  | inr hu =>
    subst u
    right
    decide

theorem scaleAt_positive_zero : scaleAt 0 = Float32.ofBits 0 := by
  rw [scaleAt_eq]
  exact congrArg Float32.ofBits (by decide : scaleBits (tableIndex 0) = 0)

theorem scaleAt_negative_zero :
    scaleAt 0x80000000 = Float32.ofBits 0x80000000 := by
  rw [scaleAt_eq]
  exact congrArg Float32.ofBits
    (by decide : scaleBits (tableIndex 0x80000000) = 0x80000000)

theorem zero_mantissa_conversion :
    (0x800000 : UInt32).toFloat32 = Float32.ofBits 0x4b000000 := by
  decide

def tableProduct (u : UInt32) : Float32 :=
  (mantissa u).toFloat32 * scaleAt u

theorem tableProduct_positive_zero : tableProduct 0 = Float32.ofBits 0 := by
  rw [tableProduct, scaleAt_positive_zero]
  decide

theorem tableProduct_negative_zero :
    tableProduct 0x80000000 = Float32.ofBits 0x80000000 := by
  rw [tableProduct, scaleAt_negative_zero]
  decide

theorem tableProduct_zero_eq (u : UInt32) (h : magnitude u = 0) :
    tableProduct u = Float32.ofBits u := by
  cases (magnitude_zero_iff u).mp h with
  | inl hu =>
    subst u
    exact tableProduct_positive_zero
  | inr hu =>
    subst u
    exact tableProduct_negative_zero

theorem tableProduct_zero_bits_eq (u : UInt32) (h : magnitude u = 0) :
    (tableProduct u).toBits = (Float32.ofBits u).toBits := by
  exact congrArg Float32.toBits (tableProduct_zero_eq u h)

theorem zero_ofBits_toBits (u : UInt32) (h : magnitude u = 0) :
    (Float32.ofBits u).toBits = u := by
  cases (magnitude_zero_iff u).mp h with
  | inl hu => subst u; decide
  | inr hu => subst u; decide

theorem tableProduct_zero_bits (u : UInt32) (h : magnitude u = 0) :
    (tableProduct u).toBits = u := by
  exact (tableProduct_zero_bits_eq u h).trans (zero_ofBits_toBits u h)

theorem float32_eq_of_toBits_eq {x y : Float32} (h : x.toBits = y.toBits) :
    x = y := by
  cases x with
  | ofModel xm =>
    cases y with
    | ofModel ym =>
      cases xm with
      | mk xb xv =>
        cases ym with
        | mk yb yv =>
          change xb = yb at h
          cases h
          rfl

theorem float32_ofBits_toBits (x : Float32) : Float32.ofBits x.toBits = x := by
  simpa only [FloatLib.Floats.ExecFloat.Binary.toFloat32,
    FloatLib.Floats.ExecFloat.Binary.toBits32_ofFloat32] using
    FloatLib.Floats.ExecFloat.Binary.toFloat32_ofFloat32 x

theorem float32_eq_of_raw_bits {x : Float32} {u : UInt32} (h : x.toBits = u) :
    x = Float32.ofBits u := by
  calc
    x = Float32.ofBits x.toBits := (float32_ofBits_toBits x).symm
    _ = Float32.ofBits u := congrArg Float32.ofBits h

theorem normal_value_of_bits
    (hNormalBits : ∀ u, NormalBand u →
      (tableProduct u).toBits = (Float32.ofBits u).toBits) :
    ∀ u, NormalBand u → tableProduct u = Float32.ofBits u := by
  intro u hn
  exact float32_eq_of_toBits_eq (hNormalBits u hn)

theorem normal_value_of_raw_bits
    (hNormalRawBits : ∀ u, NormalBand u → (tableProduct u).toBits = u) :
    ∀ u, NormalBand u → tableProduct u = Float32.ofBits u := by
  intro u hn
  exact float32_eq_of_raw_bits (hNormalRawBits u hn)

theorem tableProduct_of_fastOK
    (hNormal : ∀ u, NormalBand u → tableProduct u = Float32.ofBits u)
    (u : UInt32) (h : fastOK u = true) :
    tableProduct u = Float32.ofBits u := by
  cases (fastOK_iff u).mp h with
  | inl hz => exact tableProduct_zero_eq u hz
  | inr hn => exact hNormal u hn

def convert (u : UInt32) : Float32 :=
  if fastOK u then tableProduct u else Float32.ofBits u

theorem convert_zero_path (u : UInt32) (h : magnitude u = 0) :
    convert u = tableProduct u := by
  have hf : fastOK u = true := (fastOK_iff u).mpr (Or.inl h)
  rw [convert, if_pos hf]

theorem convert_fallback (u : UInt32) (h : fastOK u = false) :
    convert u = Float32.ofBits u := by
  simp [convert, h]

theorem convert_eq
    (hNormal : ∀ u, NormalBand u → tableProduct u = Float32.ofBits u)
    (u : UInt32) : convert u = Float32.ofBits u := by
  by_cases h : fastOK u = true
  · rw [convert, if_pos h]
    exact tableProduct_of_fastOK hNormal u h
  · rw [convert, if_neg h]

theorem convert_bits_eq
    (hNormal : ∀ u, NormalBand u → tableProduct u = Float32.ofBits u)
    (u : UInt32) : (convert u).toBits = (Float32.ofBits u).toBits := by
  exact congrArg Float32.toBits (convert_eq hNormal u)

theorem convert_eq_of_normal_bits
    (hNormalBits : ∀ u, NormalBand u →
      (tableProduct u).toBits = (Float32.ofBits u).toBits)
    (u : UInt32) : convert u = Float32.ofBits u := by
  exact convert_eq (normal_value_of_bits hNormalBits) u

theorem convert_eq_of_normal_raw_bits
    (hNormalRawBits : ∀ u, NormalBand u → (tableProduct u).toBits = u)
    (u : UInt32) : convert u = Float32.ofBits u := by
  exact convert_eq (normal_value_of_raw_bits hNormalRawBits) u

theorem replace_decoder {α : Sort _}
    (hNormal : ∀ u, NormalBand u → tableProduct u = Float32.ofBits u)
    (core : (UInt32 → Float32) → α) : core convert = core Float32.ofBits := by
  exact congrArg core (funext (convert_eq hNormal))

theorem foldl_convert_eq
    (hNormal : ∀ u, NormalBand u → tableProduct u = Float32.ofBits u)
    (xs : List UInt32) (step : Float32 → Float32 → Float32) (acc : Float32) :
    xs.foldl (fun z u => step z (convert u)) acc =
      xs.foldl (fun z u => step z (Float32.ofBits u)) acc := by
  induction xs generalizing acc with
  | nil => rfl
  | cons u us ih =>
    simp only [List.foldl_cons, convert_eq hNormal u]
    exact ih _

end R2W01b
```

## 附录 B：包内复现入口

`README.md` 给出文件对应关系。`diagnostics/run_probe.py` 可重新运行同一个预设 C 协议并保留新输出；`diagnostics/independent_diagnostic.py` 是独立整数诊断。包内保留的是本轮已经运行一次的原始证据，不需要再运行脚本才能阅读结论。

`diagnostics/COMMANDS.md` 单独列出固定 Lean 环境中的编译、依赖与生成码观察命令。当前没有这些命令的成功输出。ZIP 的 `SHA256SUMS.txt` 覆盖包内其余每个文件，交付前已核对 ZIP CRC 与全部清单项。
