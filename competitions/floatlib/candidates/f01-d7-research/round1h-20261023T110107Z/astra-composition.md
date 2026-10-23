# R8：a84接入bee6标量守卫

本轮窗口2026-10-23 11:01:07—12:01:07 UTC（北京时间19:01—20:01）。R于11:03:03开始接入核对，首稿要求11:13前；D仍为唯一Git/push/CI协调者。本交接不新增正式提交、注册、资金或merge权限。

## 精确产物与父本

[新Kernel](../../f01-r8-combined-result-guard/Kernel.lean)：**41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7**，235169B，余20831B。仅导入ContractTensor。

| 角色 | 原目录 | 原SHA-256 | 字节 |
|---|---|---|---|
| 当前运行父本 | f01-d7-direct-singlepass-proof2 | a84c1618cebe5892cbffd3657de8f2e6b96f0f70df2811af75c09a6ea3c5f736 | 233714 |
| 已验证scalar来源 | f01-d7-result-guard-both-proof2 | bee6ccdfec16d2b21810af4bea2389bcb2765e534b667cdc952188845227f183 | 156558 |
| 提取改动基准 | f01-d7-direct-nonnan | 60f74aa4af01a9b35ece66a7c310e6b05b5b84b9b7121a4cccd12a0a9c987e15 | 155103 |

父本实际字节均重新核对。原manifest里的NOT_RUN是创建时历史状态，不覆盖D已收齐的818/819、817/812结果；本新组合仍需要自己完整验收。

## 机制和保留范围

add/nativeMul改用原生结果的自比较判据：非NaN结果直接封装，NaN仍回到原精确TunedAdd/FastMul，从而保留原字NaN优先级与载荷。普通scalar改用结果判据，Inf可接受，NaN路径也可能多付一次原生运算；净成本必须整包实测。乘法外层低指数分支原样保留，没有接入e139，也没有新参数。

新add_spec完整来自修复后的bee6，包含额外change规范化目标，未从旧d027或原builder的未修复文本重建。a84的R7W03/NaN suffix、quiet replay、完整单遍sum证明、Nat/USize、direct BMM及其布局全部保留。它们的源码声明不变，但其scalar被调用函数变化，因此不宣称整条运行路径与父本二进制相同。

## 两种字节核对

1. 构建器抽取三份源完全一致的NativeBridge/NotNaNProbe/R7Native块，将其原样前移到scalar前；插入bee6原R7W04；替换两段有唯一起点的add/nativeMul声明和证明。先对60f执行并断言结果**全文等于bee6**，随后要求同7个before/after文本在a84上也严格成立。完整逆操作恢复a84，不使用宽WordFinite→NativeFinal锚点。
2. 独立核对不使用上述操作偏移：移除bee6首个1672B插入后，对60f取最长公共字节前后缀，得到原29959B/新29742B的唯一scalar区。原区在a84偏移113717唯一出现；替换再插入头部后得到相同41bce完整源，逆向恢复a84。净增1455B。

原R7Native结束之后的**90038B尾部逐字节保留**，另对完整R7SinglePassSum namespace及最终exports核对一致。三份闭合块、头部guard、全部7次操作的原/新文本、SHA和偏移均保存在同名JSON。所有父本只读，没有修改原源码、原manifest、wrapper或计划。

第一次构建预检把通用mul导出结束标记误设成全文件唯一，在写任何候选前拒绝；它在多个namespace中本来就重复。已修正为唯一开始标记后的第一个结束标记，并由完整bee6重现、相同操作及两次逆变换约束范围。此为构建预检问题，没有产生另一运行候选。

## 依赖、规格与静态policy

三份前移块在60f、bee6、a84上哈希一致；bee6中已经使用同一前置位置。块内是证明及F/M类型别名，不依赖后置a84新循环。原R2W01c.NativeBridge保持原样，未与Submission.NativeBridge混淆。新全局R7W04在a84原源不存在，合成后恰好一份。

轻量命令清点核对namespace/section闭合、搬移后公共名唯一，以及Submission.add/mul/sum/bmm及四个原spec各一份。它不替代Lean parser或elaboration。原gate SHA为1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194，禁词、唯一import、options/attributes、UTF8和大小检查通过。全部许可保留，不删注释压缩。

## 下一次实际证伪

1. 对精确41bce按原Lean4.34/FloatLib设置编译，首先检验新scalar证明与a84后置定理是否仍在同一名称/类型下闭合。没有新公理、sorry或义务变化。
2. 原四义务、重放、仅允许三公理、所有checksum case和25配对轮完整通过后才讨论接受。
3. 同runner以a84为保留包控制，量整包及add/mul，检查NaN原生尝试的额外成本、普通case、sum/BMM冷调用是否回归。不能把22.5–22.8%与约10.5%相加。
4. 有价值结果须冻结同一源，在新seed/newrunner且关闭observer条件下确认。公开public-v2不等于当前冠军私有scoring-v2，冠军源码不可得时不推算正式优势。

**新Lean/fullgate/C/timing全部NOT_RUN；gain UNKNOWN。** D负责下一批精确验收。R未操作Git、push、CI、网页、其他会话或新agent，也未本地安装/运行大型Linux工具链。
