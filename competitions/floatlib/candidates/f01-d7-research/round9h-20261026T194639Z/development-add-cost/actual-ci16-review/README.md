# CI16 ADD成本结论：停放精确D3与昂贵public证明

**建议停止精确d3c550da运行体的大public ADD证明投入。** 四块ADD完整case计时均慢约48%–51%，whole慢约18%–20%；实际caller确是期望的arity2、零捕获入口，D3正常非零成功臂也已没有临时spill。当前负结果不是旧MUL的固定Bool捕获问题。它不证明所有整数ADD都慢，也不评价数学储备本身；只说明这份精确运行体在现有完整诊断条件下不值得继续购买昂贵公共等价证明。

## 精确边界与原件

run40436948264，commit a6c829564d4964eee6319b04141f8598a3e8e24c，精确Kernel d3c550da…/228686B，冻结manifest ada78534…及16组件已逐项复核。150份原件、16333291B的SHA/size/文件集合全部一致。Main C为7e1a7c77…，ASM91376197…，caller7208074c…；本地可重核这些raw bytes。对象20ce1204…和binary b7aba7dd…未导出ELF，其计时前后不变是远端成功断言，不能称本地重新hash过原ELF。详细绑定在originals.json、source-bindings.json、codegen.json。

同一个新binary，AMD EPYC9V74、CPU0、4GiB build/512MiB bench、固定Lean4.34/clang -O3 -ffp-contract=off。独立比较真实compile22参数、link4参数、rsp4156参数，只有MainFull→R19AddCostMain及benchFull→r19AddCost路径映射；其余flags/依赖/顺序相等。原source/object/binary和official文件前后不变有原driver断言。没有插入内核timer/observer，原Suite full-pass/checksum/drop-reference边界保持，whole是152个case原best_ns之和，不是进程wall time或纯算术周期。

CI16普通statement及成本stage完成；本stage明示当前D3模块回放/七根NOT_RUN，CI12回放只绑定77377父源。这里只确认八次已见样本的checksum一致，不是所有输出逐项相等、guarded ADD全域数学证明、25轮原score、原D或新runner确认。

## 独立原log重算

review.py不调用原driver或R13 parser，直接解析8个log：每份156唯一行、152正ns timed、4个零ns非timed；每份42个ADD，四块共168个ADD pair及全部608个timed pair。与保存rows/metadata/四项及whole汇总逐项一致，同seed四进程全部checksum一致。慢样本和唯一快ADD pair均保留。

| seed / block | ADD control ns | ADD guarded ns | ADD ratio | whole ratio |
|---|---:|---:|---:|---:|
|1927003 / 0|51753030|77891777|1.505066988|1.175670592|
|1927003 / 1|50593947|75352507|1.489358144|1.176788695|
|1927005 / 0|51249357|76748266|1.497545930|1.197037195|
|1927005 / 1|51834656|76919710|1.483943677|1.204367716|

四块描述性合计：ADD306912260/205430990=1.493992021，多101481270ns；whole652707630/549388562=1.188061920，多103319068ns。ADD计时增加占净whole增加98.2212%，这是计时归属，不是对每个指令的因果分解。未改MUL/SUM/BMM仍分别为1.004879709/1.012056342/1.002693139，完整波动保留，不把它们强行写成1，也不全部归因于ADD逻辑。

168个ADD pair中167个变慢，唯一变快为1927003 block1 add:paired:6，ratio0.940710139、delta−78977ns。跨四块汇总的42个同名case全部变慢；同名在两个seed可能有不同参数，表不把它们当同一输入重复。

| pooled同名case | control sum ns | guarded sum ns | extra ns | ADD净增加份额 |
|---|---:|---:|---:|---:|
|add:dense:2|4848952|9128129|4279177|4.2167%|
|add:dense:5|4975968|9247302|4271334|4.2090%|
|add:dense:4|4969830|8545410|3575580|3.5234%|
|add:dense:0|4856322|8093404|3237082|3.1898%|
|add:ml:5|4864706|8091253|3226547|3.1795%|

top5只占ADD净增加18.3184%，top10占33.6537%，不是单个异常case造成。实测标签的合计ratio：dense1.720286、ml1.557302、sparse1.355064、specials1.551690、subnormal1.427277、paired1.368315、extremes1.563201。**这些只是plan/log名称标签，各类eligible比例全部UNKNOWN。** 未生成本机500k输入，未用旧256点/等成本代理推命中率或解释slowdown。

全42行及四块ratio在ADD-42-cases.md；168个ADD pair原ns/delta/贡献份额在ADD-168-case-pairs.csv；全部608 pair、plan字段、labels与eight-process时长在raw-recomputed.json。没有筛掉负delta或慢block。

## 实际被调用的代码

Main C3337–3386在Suite前选闭包11(control)或10(guarded)，两者静态m_arity2/m_num_fixed0；在同一join里把ADD选择与共同MUL/SUM/BMM闭包1/2/3传入唯一Suite.run。成功选择路径没有动态closure分配；variant不是热callback捕获参数。两个boxed wrapper各116B，指令/relocation除typed call目标外相同；返回`lea rax,[rax*2+1]`是立即carrier tag，无新返回heap object。

真实typed control是C88–421、448B/130条静态指令；guarded为C435–1637、1189B/313条。guarded内实际展开R19 GRS，C1533附近就是uint32_to_float32→float32_to_bits→mid+delta；Main C没有diagnosticEntry，也没有额外guardedAdd helper调用。函数总体大小及指令数量不转换成耗时。

| 实际普通非NaN/非零臂 | control原R2 numeric | guarded D3接纳臂 |
|---|---|---|
|读取/准备|原两个raw word，无额外准备|相同，无额外容器准备|
|主要工作|两次mantissa数值cast、两次共享scaleTable读取/mul、native add、自比较|两输入normal guard、magnitude排序cmov、variable shift/sticky或大gap常数1、符号加减/零检查、eh25..253 guard、一次cast与整数rebias|
|codec|恢复栈后0xd4尾跳toBits|0x381普通call toBits，之后0x386/388完成rebias并返回|
|临时[rsp]访存|0（两输入落R2 numeric臂时）|0（非零接纳臂）|
|入口保存|rbp/r14/rbx三callee saves，加16B局部/对齐|rbp/r15/r14/r13/r12/rbx六callee saves，加8B局部/对齐|
|入口RSP下移，不含return address|40B|56B|
|静态完整路径指令|54，未展开codec|gap≤31为79，gap≥32为65，未展开codec|

这验证当前selected D3的“delta跨call、无临时热spill”结构前提。它也显示D3没有把最终codec消掉：这是一次非尾foreigncall，control同普通路径则尾跳同一codec。新路径保留整数依赖链及更大prologue。不能用79/54或保存数计算速度，也不能把旧773独立diagnosticEntry的spill差异当同binary时间改善。

所有input-normal guard miss和eh pre-guard miss仍执行完整原B2 ADD。若两个输入normal但最后eh拒绝，已先支付排序/对齐/sticky/符号计算再执行fallback；这一机械重复可从实际ASM10a→…→33c→34a→fallback追到，**实际发生比例UNKNOWN**。fallback保留table/casts、input ofBits及其条件xmm spill、NaN raw/softwareAdd冷链。C有三处软件fallback展开，LLVM共享部分冷block；它不代表一次输入调用三次fallback。

两个typed ADD都没有显式ctor/closure/apply；D3接纳臂无heap分配。boxed通用input RC冷分支完全相同；软件ADD helper内部物理分配仍UNKNOWN，未计数。不能把整个guarded函数说成无call/spill/分配。

## 决定与未关闭的问题

当前代码机制差异与较慢结果一致，但没有dynamic path计数、硬件cycle或eligible分解，无法把50%慢精确拆成“对齐多少、callee-save多少、fallback多少”。同源其他三项的小波动也不做删样或强因果解释。足够确定的是：预期实际callee已选中、旧MUL的arity3/固定Bool因素在本次不存在、正常成功臂没有临时spill，而这份完整运行体四块均明显退步、所有42同名case合计均退步。这里不声称control与原MainFull绝对机器码相同。因此停止精确D3及昂贵public等价证明，比继续证明一个尚未达到成本门槛的实现更符合本轮选择规则。

本已见样本control ADD占whole37.3927%。条件性敏感性：其他项不变时，10%whole需要ADD≤原control0.732568，约比本D3再降低50.9657%。当前没有实际代码/测量证据支持一个能跨过该差距的新机制；仅有“挪fallback”“少保存寄存器”等静态可能性不够，不提出新框架、阈值网格或重测同源换seed。重开须不同运行机制及真实caller证据，保留本次所有负结果。

本任务只写本review目录；没有改冻结组件/manifest/Harness，没有Git/CI/Lean或本机生成500k输入。
