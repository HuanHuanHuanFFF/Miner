# 冻结9f7上的B2热A内联转换：精确草稿与验收

**交付精确两处修改的草稿，建议先检查新源编译及选中caller C/ASM。** 候选为`Kernel-index-inline-convert.draft.lean`，SHA`f84ea2dbffbf0406f453bbc20b4335288ba5d77bb787ae33db203665016ac384`，234290B。父源为冻结`f01-r19-dev-b2-index1/Kernel.lean`的`9f7f96d71c153681c6a2500fd229e0627cd2ea38a3ad375afdeee25a1657eee1`，234277B。**新源Lean/replay/axioms/full gate/MainFull C/ASM/性能均NOT_RUN。**

本阶段UTC20:54:30开始，上限21:24:30；首检查点`inline-convert-checkpoint.md`于21:00前落盘。仅写本目录新文件，无Git/CI/本地编译、候选或manifest修改。没有读取40398675395或后续D/A/B输入、计时、结果；新源未按在途结果调参。

## 旧负结果的准确边界

`audit_inline_convert_history.py`认证旧40164630534的58个原件/3215332B和40165220696的46个原件/1949103B，原件哈希及精确源绑定见`inline-convert-history.json`。

| 精确历史对象 | 已验证事实 | 对本轮的约束 |
|---|---|---|
| f65e4aa5旧inline-decode1 | R15冻结清单为`COMPONENT_PROTOTYPE_NOT_SELECTED_STANDALONE`；在所查冻结/回执内没有其单独完整D。源码只改R14ThinBCache：单累加器、Nat/getD、Array Float32 B缓存，guard为m≥4,n>1,p>0且(p≤2或n≤4)。没有R15PackedB2。 | 保留历史NOT_RUN；不能说精确B2/USize方案已负测。 |
| cb7f1099组合 | B1转换部分与f65e逐字节相同；另加短n准入及scalar MUL cutoff84。40165220696/1526003完整25轮gate正确，对DF whole0.980419638、BMM0.856268405、p05=-0.004020053，首D门槛失败。 | 失败继续有效，不换seed重置。组合不隔离converter成本；相对DF的BMM结果不能转移为相对B2/9f7收益。 |
| cb7f的原选中C | MainFull闭包指向public bmm，静态调用图可沿B1分派到41493–41622的R14ThinBCache_loop。转换确实已内联：拒绝arm保留ofBits，接纳arm为共享table、内联uint32 cast和乘法。动态路由次数/该对象机器码时间UNKNOWN。 | 给本次最小源码改动提供可行性证据；旧单累加器caller不能证明新双累加器没有spill。 |
| 9f7首诊断C | 已认证40392789163的实际B2 caller；wordLoop每k一个ofBits call，诊断机器码保存两份活跃向量跨call。 | 这是本轮要删除的真实成本入口，保留原读取/布局/输出。 |

在上述精确范围中，未发现“B2双列＋USize＋已验convert”同一机制完整负测，故继续草稿；不因此宣称新发明或预期提速。

## 精确差异与证明义务

新源只改两个行块，行数不变，净增13B：

1. **6492–6493，Indexed.wordLoop的A转换。** `ExecFloat.Binary.toFloat32 (A.uget ...)`替换为根`R2W01b.convert (A.uget ...).raw.1`。同一个合法raw A uget只读一次，原B2读取和两条`s0+a*b.s0`、`s1+a*b.s1`原序递推保留。
2. **6519，Indexed.wordLoop_eq。** 原simp-only列表加入根`R2W01c.convert_eq`，对两个更新中的转换值都改回原Float32.ofBits；再沿原uget/getD、机器字地址和步进等式接旧loop。该引理无输入域前提，证明结构与原递归终止项不变。

没有新增声明、import或信任接口。根namespace已有`R2W01b`；实际旧C符号是`lp_competition_R2W01b_convert`，不带Submission。packB、shape分派、output全局范围守卫、NaN finish/replay、原fallback loop、所有scalar/sum及其他源码字节均保留，无A.map/面板/tiles。

`inline-convert-exact.diff.txt`保留两块可审查diff，`inline-convert-exact-delta.json`保留old/new原文。逆替换逐字节恢复父9f7。静态复核另确认两处replace、单导入、字节帽及2560个定向原字的gate含义；有限gate检查不替代数值证明或Lean。

新源需普通编译、整个Submission/VerifyFull重放、原完整gate/校验和及helper公理检查。保留父9f7实际存在的15根，特别是已改变的`Submission.R15PackedB2.Indexed.wordLoop_eq`；可额外显式打印已存在的根`R2W01c.convert_eq`。不要列不存在的`Submission.R15PackedB2.Indexed.runDot_eq`。旧convert_eq已验不授予新source编译或性能状态。

## 域与完整成本

原convert接纳域精确为`magnitude=0`或`0x0c000000 ≤ magnitude < 0x7f800000`：±0以及E24..254。E0非零、E1..23、Inf和NaN沿原Float32.ofBits。guard包含UInt32减一回绕，±0不能漏掉；不修改原阈值。既有全输入值等式足够连接旧点积，payload敏感的raw finish保持原样。

固定Lean293d头部确认`lean_uint32_to_float32`是`static inline ... return (float)a`，`lean_float32_of_bits`为导出函数。9f7原C12557附近的convert接纳arm使用现有`R2W01b_scaleTable`全局指针，没有per-step once。新表达式增加每A一次资格判断、整数掩码/转换、table读取及一项精确Float32乘法，期待换掉接纳arm的外部call及相关spill；这些新增工作可能抵消收益。公共scalar代码早已使用同一表，未新增表/数组/输入准备，但新选中C仍须验证。

域外仍有原call且多付资格检查。新源每k不能据源码直接宣称call-free；即使接纳arm无call，编译器仍可能把spill放到共同路径。旧B1 C及root leaf只作可行性证据。BMM的整包占比和当前接纳arm动态时间均未重测，收益保持UNKNOWN。

## 新选中MainFull C/ASM验收条件

1. **精确绑定。** 内层input、C索引和本地候选都必须匹配f84ea2db；再沿MainFull的public bmm闭包 → 原underflow/shape分派 → B2 output全局guard快速arm → 实际`Indexed.wordLoop___redArg`。检查实际caller，不能用未选中的generic wrapper或单独root convert。
2. **原结构。** count/baseA/k继续机器字；A/B仍两次borrowed uget，A原字只读一次、B2两字段保持；原B准备一次。无A.map/新Array.ofFn/面板/tiles/重复B准备，range guard仍只在output一次。新增加的是decoder资格判断，别与range guard混淆。
3. **转换分支。** R2W01b.convert/tableProduct/scaleAt应进入实际循环C。接纳arm没有`Float32.ofBits`或`R2W01b.convert`外部调用，只有共享表和内联cast/mul；拒绝arm保留原ofBits。table索引的有界UInt32→Nat桥可能仍出现于C，须确认机器码消除其RC/大数分支，不能把C符号站点当真实调用。
4. **逐路径机器码。** 从循环头沿资格成立arm回到循环头，确认无call、逐步heap/RC或为转换保存/读取活跃累加器的栈流量；记录拒绝arm与合并点，检查spill是否被提到共同路径。函数prologue的push、unused generic wrapper的栈参数不能作per-k spill证据。保留全部不利指令与慢路径。
5. **数值和输出。** 原两条独立mul→add顺序及尾列/raw基址保持；官方`-ffp-contract=off`保留，不引入FMA。finish、NaN原字回放、终态F2和输出调用保持。原机器码只有诊断对象身份时，继续明确它与未来timed对象/ELF的边界。
6. **决定。** 接纳arm仍有同类call或共同spill且无另一可核实成本收益时，先记录反证，不以root helper已验为由排完整D。若选中代码实现目标，再由D用原样完整源做无观察器完整发现组，准备/资格判断/table/域外fallback/输出全部计时。采用仍按当轮冻结参照和既定D+A+B；不能把旧组合收益加到9f7或用当前在途D调guard。

可检验的后续仅在实际代码未内联时重开：在同一A转换表达式显式展开现有`if fastOK then tableProduct else Float32.ofBits`，仍以convert定义及convert_eq证明相等，仍无准备。但现有B1 C已显示自动内联，当前没有理由先复制该变体。若实际问题是共享spill，需先展示接纳路径上的指令和合并位置，才决定最小控制流改动；本稿不预造更多版本。

复核入口：`build_inline_convert_draft.py`、`audit_inline_convert_history.py`、`validate_inline_convert_draft.py`。三者只做轻量源码/旧证据检查，均未编译新源。
