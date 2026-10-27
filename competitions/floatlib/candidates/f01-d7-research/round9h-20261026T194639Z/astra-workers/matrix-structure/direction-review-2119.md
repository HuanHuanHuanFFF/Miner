# 15分钟方向复盘：保留c70c，新增结构重证明暂不投入

**预算判断。** 两次真实D说明“更少索引/对象”不能代替完整成本：9f7整包1.00880负；c70c整包0.990205、BMM0.922129，只有单发现组小收益。当前B2本样本BMM占16.83%，10%整包需约2.46倍的整个BMM改善，c70c远未达到。保留它作为实质组合储备，新组合重新完整D/A/B；下一份连续重证明/完整CI预算优先给标量主线，不继续索引、宽度或rowLoop变体。

| 不同机制 | 当前证据与决定 |
| --- | --- |
| **B列含NaN时直接early replay，跳过native pass** | 证明接口确实低成本：`R7NaNReplay.replayEarly_eq`全输入成立，选择flag只影响性能，不需要先证明flag正确；原地址/输出仍须接好。已见1927003按原整数生成器得到127个poison列、334输出，仅8710个native MAC可选；普通路径需扫约1843123个B word、99012个flag槽。原B2/F10组要全部有效lane均poison才能原样省组loop，实际仅236输出可按原组直接省，全部在p=1；B2双列范围没有全poison组。**PARK，不写第三稿。** |
| **仅首B值NaN的词捷径** | 99012次每列首值检查只命中13列/20输出，选择2189个native MAC；证明同样可复用replay，然而普通miss和caller成本仍在。两种NaN路线只触及specials，其完整整格时间也仅占本样本整包**1.94%**；即使整格免费也过不了3%门槛，更不支持10%。 |
| **零行/列＋另一侧finite证书，直接填+0并跳过整dot/整batch准备** | 与现有“整张A/B均极小”underflow guard不同；合法条件也排除0×Inf/NaN。原输入模型覆盖9286输出/161504 MAC、2782个小batch，但只在sparse的2个case；整个sparse格上界5.20%，真实目标耗时UNKNOWN。最大的短n sparse case的zeroKind=3其实是tiny非零，不能按zeroPct当零。无足够高上限证据，暂不投完整证明。 |

**历史约束已查。** `bmm-scan-sharing-screen.md`早有807全量summary普通路径增读/flag成本；旧poison screen已见被污染案例native loop占比很小。当前fresh计数仍不支持重开；它不同于R9每MAC检查earlyNaN，但“机制不同”本身不是足够收益依据。zero路线需要新零乘finite与填充桥，不能借现有both-small命题抹掉B有限前提。

**最小重开判别。** 先取得别的已授权/已见输入上足够大的目标完整调用时间，或当前source低扰动诊断确认native-first-pass/零可跳段真占主导，并计正常miss、扫描、flag存储、准备和回退；有新证据才接一个真实完整路径。不为当前1.94%上界的NaN路线排新完整CI。此界只限本次已见样本/该NaN机制，不封死其他输入或整个矩阵结构。

证据：`nan-column-screen.json`、`zero-certificate-screen.json`及同名脚本，原plan/生成器SHA保留；整数输入/地址模型，非实际Float32执行或时间。两次模型约0.07秒/2.34秒，外部12/20秒上限；无Lean编译、源码变体、Git/CI。开始约21:20 UTC，约21:33交付，在15分钟内；token/cache UNKNOWN。
