# Wide 28b819 源码容量只读审计

绑定源为 `f01-r11-wide4-inline-proof3/Kernel.lean`，**253315 B / `28b819120cd3aaa1f19038f66042a9ceffe0c9329baab20fe223e98d151ce00b`**，当前余量2685 B。未写任何 Kernel、helper或压缩副本，所有变换只在内存 dry-run；新Lean/fullgate均NOT_RUN。完整区间、原文、hash与限制见[JSON](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/review-wide-capacity.json)。

固定 `source-budget.py` 为 e1ee62f4…a5d6ee51；R8 inventory parser 来自 `f01-r8-combined-result-guard/build.py`。两者及当前builder、Cross builder、现有headroom清单的完整hash均记录。仅提取既有纯函数，不执行builder/main，不产生pycache或源码文件。也读取了 `compose-structural.py` 的保护/空白分类：它保留所有comment，仅允许按物理行移除comment外的普通空白；没有放宽其适用recipe或写权限。

容量结果：

| 类别 | 数量 | 字节 | 结论 |
| --- | ---: | ---: | --- |
| 全部comment | 210 | 30930 | 不是可全删池 |
| scanner自动保护notice | 9 | 11720 | 原字节必须保留 |
| 额外保守保护来源/拼接状态说明 | 19 | 3036 | scanner未识别，仍保留 |
| 其余普通技术/数学说明 | 182 | 16174 | 上限池，需Root逐段选择；不是批量删除授权 |
| comment外普通空白行 | 1538 | 1538 | 单列，不含comment内部空行 |
| 下表10段纯数学说明示例 | 10 | 1788 | 小型可审阅起点，不足以独自容纳Cross |

原scanner纯内存 `prepare/report_for` 得到234105 B，省19210 B，并核实live物理代码行及9份notice hash序列相同。但是这会移除 R7-W01/W02片段标识、Dependencies/Add/Mul拼接来源、W05/TorchLean说明、旧NOT_RUN资产状态等额外3036 B；**不能直接把该自动结果当作符合全部来源保留要求的最终稿。** 已把这些19段原文/hash列为额外保护。scanner是启发式notice识别器，不是法律文本分类器。

若Root最终人工审阅并选择全部16174 B普通说明，加1538 B普通空白，则规划值为235603 B、剩余20397 B。再加既有冻结Cross增量15499 B，算术投影251102 B、余4898 B；新alias/dispatcher glue及Panel4尾部模块大小尚UNKNOWN。这不是已构造组合，更不是编译结论。仅下表10段加空白可省3326 B，连现有余量只有6011 B，不足合回完整Cross。

10段示例均为28b819原始行号，区间不含代码，JSON还给出精确byte范围与全文。相同注释出现在两个证明归属中，分别绑定各自位置。

| 原行 | B | SHA-256 | 内容摘要 |
| --- | ---: | --- | --- |
| 3476–3482 | 264 | `8ca9e52a66faa15910161f53d016a0dd412c8687165fd0ed9cf7b2e71ce951f3` | 全输入add的canonical-native桥及NaN元数据边界 |
| 1274–1277 | 183 | `0c146b79c7b8b7ec2fe24d290e412f27fc9e7842494fb9d1173cac49f04c04ab` | finite unpack满足roundWithAccuracy前提 |
| 2480–2483 | 183 | `0c146b79c7b8b7ec2fe24d290e412f27fc9e7842494fb9d1173cac49f04c04ab` | 同上，另一namespace |
| 4136–4139 | 168 | `1f3b4a1a249db38d3480c904400f6ef51b81b51d718d65ac6ad17b5be71ed436` | nonNaN native状态重建完整原字 |
| 3080–3081 | 167 | `b427c658531b770970691dce6ed8a4030180bc7befb44a003ebfa95697a52969` | 右sNaN优先级及quiet后sign/payload |
| 641–642 | 166 | `3160af5b5086b4368c94a90b3899a96f6dfaa98ff9089385e6e99764273cd41a` | quiet-left-NaN与右sNaN分支 |
| 1247–1250 | 165 | `a663d8204271742cd7c8325e5316c176d90f68bf7addfb4cb64e4b8910ca8d91` | 非零mantissa乘积满足舍入前提 |
| 2453–2456 | 165 | `a663d8204271742cd7c8325e5316c176d90f68bf7addfb4cb64e4b8910ca8d91` | 同上，另一namespace |
| 3851–3854 | 164 | `cfb1ea84839528f87998d8b627c709f946d6362bcff9219d3992d8e969eca162` | 左NaN原模型元数据与native规范化边界 |
| 3932–3935 | 163 | `3af3bc2a779204072c6d66368fc6b9412b5863be920347d9d181578486e376c7` | 全输入canonical-native mul桥，无finite/payload前提 |

未把“projection contract要求buildTiles只求值一次”的说明放进纯数学十段示例，避免把运行表示义务当作纯证明叙述；完整普通说明池仍包含此类技术说明，最终选择应保留其可审阅性或在外部设计原文中明确定位。

词法空白方面，保持每条newline、leading indent及全部comment原字节时，当前源的comment外行尾horizontal空白为0 B，首token之后长度大于1的horizontal空白可压量也为0 B。进一步省掉单一分隔符的收益UNKNOWN：必须有真正Lean词法token序列核对，覆盖Unicode标识符/运算符、字符串、字符、quotation、quoted id及syntax扩展；即使leading indent未变，token列位置变化仍可能影响layout。R8 inventory不是Lean lexer。当前容量投影已不需要这条高风险压缩路线，建议PARK。

R8 inventory在原源上得到506个def/theorem/abbrev，namespace栈平衡、四export与四spec各一份、无重复限定名。这只是命令清单，不能证明删注释/空白后的Lean语义或proof-term闭包。

现有unused-chain清单之外，发现两个**仅词法筛查的新线索，未计入容量节省，也不建议无验证直接删**：

- `Submission.WordFinite`，原2395–2421，byte `[98617,99863)`，1246 B / `f0d542db81286e5aca6e818f54b4e5164fe1c00266a857ac5735ad1aaf971242`；其中 `modelFiniteOfExp/nativeFiniteOfExp` 及namespace名称在块外exact-word命中均0。仍有scoped open等环境语义待核。
- `Submission.FinalFinite`，原2994–3032，byte `[127604,129614)`，2010 B / `38e35ab9fe290993242bbaac2da3dbc01c6387f8e3dd89838565b22ee1422473`；四个具名theorem及namespace名称块外命中均0。块内2996–2999是306 B明确来源notice（Lean FRO/Apache-2.0），即使以后移除定理也必须原字节保留，不能整块删掉后声称仅删unused证明。

这些扫描未覆盖所有声明类别、attribute/instance与隐式elaboration依赖，没有新增形式闭包结论。Root若决定新包装稿，应保留完整原28b819源、精确edit/inverse清单、notice hash序列、原policy与256000 B限制，并对精确新稿重跑原full gate；不继承旧稿验收。
