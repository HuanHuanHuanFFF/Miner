# f529 branchless-normal 片段独立审查

开始2026-10-25 05:42:22Z。审查对象为236154B的 `f529f4d4a693b6bee91aa10882237d30112637383cb447f3037057ff9bdb70d9`，父源 `9038f8d653f030a8812c3187733488f70995253a1a7b284759c4f58b96378c19`。未改D文件、未生成候选、未执行Lean/编译/CI。

**未发现实际量词、flag或位宽错误。** 片段的恒等式连接路径完整；独立有限模型没有找到反例。审查过程中已有run40166091242实际产物落盘，本方核对了其f529输入及C哈希，回执为 **statement-only PASS，25.1秒**。这不升级为完整gate、公理审计、checksum或性能通过。

## 1. 0/1 flag与任意shift等式

f529 Kernel:3645–3652：

- notLess是 `if r<half then (0:UInt64) else 1`；
- greater是 `if r>half then (1:UInt64) else 0`；
- odd是 `if (q &&& 1)==0 then (0:UInt64) else 1`。

三者无其他来源，始终为0/1。increment `notLess &&& (greater ||| odd)`也只能为0/1。它和旧rse的返回选择相同：

| 情况 | increment | 旧rse |
|---|---:|---|
| r<half | 0 | q |
| r>half | 1 | q+1 |
| r=half | odd | q偶数时q，奇数时q+1 |

`round_eq_rse`(3654)对任意value、shift成立的目标只是**与相同UInt64表达式定义的旧rse相等**。两边使用完全相同的q、r、half、移位语义和模2^64加法。它并未声称任意shift都等于完整RNE数学规范，也不需要在此层添加1<=shift<64前提。

`split <;> split <;> split <;> simp_all`分别枚举三个if结果，常量0/1位运算化简后匹配旧条件树；即使枚举含不可能的比较组合也无新增义务。该具体脚本现在已有精确f529 statement成功佐证，纸面审查没有替它补定理。

## 2. literal23/24层、guard和fallback

`roundedWord_eq`(3665)用父源无前提的 `shiftWord_values u v`分成23/24两支。该父定理对任意UInt32 raw都成立，因为productWord总是先设置24位隐藏位；它不假设raw已normal。两支只在旧rseAny的shift=23/24处展开，0/≥64边界均被排除。不能把本层结论误写为新round等于rseAny对所有shift成立。

`core_eq`(3680)先替换roundedWord，再展开旧exponentWord/fractionWord/carryWord。新的let rounded只是共享同一个旧rounded值；high、carry、指数和、fraction mask与旧core完全相同。等式量化所有u/v，没有增加normal前提或原生桥假设。

`guardedMul_eq`(3691)对任意fallback及所有Binary32输入量化。eligible完全沿用9038，false分支调用同一个fallback；true分支用core_eq和旧core别名接上。最终mul_spec将既有 `mulBeforeExponent_spec`传给旧 `R14ExponentShift.guardedMul_spec`。±0、subnormal、Inf、NaN以及eligible之外的有限输入继续走旧路径；无规格范围收窄。

## 3. 32/64位界

既有父源证明提供：

- 两个尾数都在[2^23,2^24−1]，所以product在[2^46,(2^24−1)^2]，严格小于2^48；UInt64乘法不溢出。
- high=product>>>47仅为0/1；shift=23/24。
- rounded在[2^23,2^24]，carry=rounded>>>24仅为0/1。rounded与carry转UInt32不丢数据。
- high=1时最大product=(2^24−1)^2不足以向上舍入到2^24，所以不能high=carry=1；旧`no_carry_at_47`和相关bounds负责此处。
- eligible保证两指数1..254且和128..380；UInt32加法不溢出，先减127不下溢，最终encoded exponent在1..254。
- rounded==2^24时carry=1、fraction mask为0；其他情况mask去掉隐藏位，保持旧拼装。sign XOR未变。

即使在eligible之外新core的某些模运算不代表正确IEEE乘法，core_eq仍保留旧相同模运算；public guard从未在这些输入采用core。不能错误地将core的裸量词解释为无guard完整乘法正确性。

## 4. 实际变更及反方成本结论

已解析D的builder取出原needle，独立确认：needle与新2873B片段均只出现一次；用父源替换得到精确f529，逆替换逐字恢复9038；其余源码字节不变，未修改导入、gate或axiom设置。单包余量19846B。

真变化是新runtime的0/1位运算组合、23/24字面量分支和共享rounded值；并非同9038换名换seed。但**名称branchless不代表C或机器无分支**。

这次实际f529 statement构建已留下：
- Submission.c SHA `50f1081d10a8adddac3c7fe8eb44e159b3dc001bcd976ff381c7ec02d8c8ba27`；
- MainFull.c SHA `b04106a7f03be192415931cb1c58e1e94d05c7514fb55f29593b9c9dac5faccf`。

BENCH_PLAN存在时，MainFull的`_lean_main`通过closed__5将`main___lam__3___boxed`传给Bench.Suite.run；该adapter进入`main___lam__3`，mul已内联。不是未选中的generic guardedMul或外层8eb carrier。

可见lowering：

1. standalone round在Submission.c:25996–26068仍有三个C if来构造flag，然后OR/AND/add。正常core还显式按high选择23/24；最终机器分支是否经Clang转成setcc/cmov未知。
2. selected MainFull正常路径在8491计算product，8496选择shift，8500–8507使用常量24/0xffffff/0x800000，8538–8544使用23/0x7fffff/0x400000；字面量确实出现在生成C。
3. 两个literal分支分别经7423–7431或7496–7504合成rounded，并共同跳到7360的`v___jp_2444_`，再从同一rounded算carry和fraction。这验证共享rounded在C数据流中存在。
4. **不能声称product也只算一次。** 同一正常C路径初次product在8491；到shared-round终点后，7371又从两个raw mantissa计算product，用7373的>>>47取high。standalone core也有两个对应乘积站点。Clang可能CSE掉第二次；没有选中scalar汇编，不将两站点断言为机器执行两次乘法。
5. 未取得同SHA9038实际timed scalar C/ELF，不能用df5c C或新module里保留的旧helper定义推断旧9038已有/没有某项优化。因此“比9038少了多少机器分支/移位/乘法”仍UNKNOWN。
6. literal high分支本身可能不易预测，新增不依赖短路的flag计算也可能付出无用比较。普通路径能否更快只由自己的完整D说明。非MUL定义字节不变，也不能保证所有调用mul的BMM cold路径机器成本完全不变。

附带native-loop汇编仅为Packed10Index两个符号，而且注明diagnostic object；没有据此认定scalar branchless或性能改善。旧9038完整D：whole1.047144/MUL1.290801的负结果保留，不改成可忽略噪声。

## 5. 独立有限模型与验收缺项

[branchless-finite-model.json](branchless-finite-model.json)由独立Python模型产生，外层subprocess timeout=5秒硬限制；模型约0.055秒，总包装约0.159秒。

- 8个flag真值组合全部匹配旧嵌套选择；
- 13170组任意UInt64 value/shift样本，包括0、63、64、65和最大word边界，无新旧rse差异；
- 全65536组8位指数对检查eligible与数学范围一致；
- 6768组eligible normal尾数组合及边界，检查新core对独立divmod ties-to-even结果，位宽/carry/exponent界无反例；覆盖high0=2654、high1=4114，carry1、tie-even、tie-odd各24例。

这不是Lean证明，也没有建模fallback实际输出或执行原生浮点，更不是速度试验。证明声明另依精确statement回执；完整gate、公理与checksum、25轮D及冻结后的独立确认尚不由本报告建立。

[branchless-review-evidence.json](branchless-review-evidence.json)含版本、逆splice、真实回执/C哈希和选中caller。当前结论为 **未发现应阻止继续既定验证的具体正确性缺项；不支持任何收益或无机器分支声明**。

