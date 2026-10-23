# 815实际错误：cc06证明修复交接

限时起点05:09:32 UTC，截止05:29:32 UTC。原十小时研究已结束；本次仅处理新授权验证发现的实际失败，不开启新研究窗口。D是唯一Git/push/CI协调者。

新源：[f01-d7-direct-singlepass-proof2/Kernel.lean](../../candidates/f01-d7-direct-singlepass-proof2/Kernel.lean)，SHA `a84c1618cebe5892cbffd3657de8f2e6b96f0f70df2811af75c09a6ea3c5f736`，233714B。**准备供D做精确statement验收，尚未编译。** 原cc06/3d9未修改。该稿保留全部运行算法，不改变四项义务。

## 原始失败证据

811 run39903049887（4b9f84c230ca2e26d21486568e9d09adeb60d151）中60f完整gate通过，cc06在statement拒绝。815 run39904116090（6d849434301c9b92aba532598344440a3e7fa9c1）用同一cc06重放，完整输出位于：

`candidates/f01-mul-log2-proof1/ci-runs/39904116090/download-e93b4b2f375c40e091f8e5cb24c2a844/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-d7-direct-singlepass/full-build-output.txt`

该原文件未修改。完整输出实际含13个源错误，超过811截断摘要的8个位置；原始SHA/大小及所有错误行在同名JSON。这里没有把真实statement拒绝归为环境问题，也没有为cc06填写性能。

## 实际错误到最小证明改动

| 815原行 | 实际错误 | 本稿修改 |
|---|---|---|
| 4979 | ih两边的累积值被改成Submission.add，目标左侧仍是R7W02.step | 在suffixLoop_eq中保留ih的原始累积值；单独证step等式，再用congrArg把fold的累积值向目标运输，最后Eq.trans连接 |
| 6104 | omega只剩UInt32常量toNat的未归约量；反向toNat_inj被报告unused | 用UInt32.not_lt把下界转换，再由le_antisymm与hi不等式矛盾；不再交给Nat归一化或omega |
| 6124、6135 | 两个simp_all实际达到最大递归深度 | 用固定Lean4.34的Bool.not_inj和已有raw/native classifier等式直接运输；没有提高maxRecDepth或放宽任何option |
| 6174、6185、6194 | rewrite模式分别含toBits32/toFloat32，目标中是raw.1/ofBits，未找到模式 | 传入明确的运行值；table分支局部展开两层codec建立hv。保留归纳等式，通过congrArg与Eq.trans运输fold累积值，避免依赖rw的匹配透明度 |
| 6181 | 改写hinf后仍剩UInt32常量≤自身 | 用固定库UInt32.le_of_eq hinf直接得到所需不等式 |
| 6232、6235、6236、6238 | Array.uget和Vector.get导致左右条件未同步，rfl目标右侧仍是一整棵if | 在loop_eq中先建立原读取的rfl等式并重写，再对同一low/high/Inf判据显式by_cases及simp only，最后接原USize后继等式 |
| 6252 | 最终List.foldl与sumSpec定义等价仍未闭合 | 原两次rewrite之后添加rfl，展开原sumSpec；不替换规格 |

7个证明体的完整前后文本与旧/新行号、哈希都在JSON，可精确逆向恢复父本。原错误清单和修复意图是VERIFIED源/日志对应；新证明是否被Lean接受仍为NOT_RUN，不以人工审查代替编译。

## 源码不变检查

- 父cc06精确232363B/SHA核对通过，新源233714B，仍小于256000B。
- 删除且仅删除7个目标theorem证明体后，前后各228722字节完全一致。这个投影保留theorem声明/类型、termination_by/decreasing_by、所有def运行声明、imports、options、全部外部许可文本及其他证明。
- 按保存的7个逆patch恢复全部原cc06字节，SHA仍为`cc06a47faf9f982c324d265c90beb2b9cea953f33773eabed3ed6eab29260dfc`。所有运行分支、USize/Nat循环、direct BMM布局、NaN顺序和scalar操作原样保留。
- 使用固定原gate SHA `1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194` 的禁词/options/attributes规则做静态核对：单文件、唯一ContractTensor导入、大小和原policy通过。没有修改原gate或候选外部入口。
- 源码运行部分逐字节不变，不等于已核对新编译C/对象。编译器可能因证明布局产生不同内部命名，本轮没有生成对象。

## 待D验收与停止条件

下一步只需对上述精确新源按原Lean4.34.0/FloatLib/public-v2设置跑statement并保存完整输出。通过后才可走原完整gate；完整四义务、内核重放、允许公理、checksum和25配对轮都不能省略。全部运行收益仍UNKNOWN。

若新错误仍在这些证明连接处，按实际目标继续一处一处判断；不预先换运行机制或扩大近邻。若这条新sum接线无法在后续授权预算内可靠闭合，已有97f是可供D另验的fallback，但它自身精确完整gate也未通过，不能因为DirectSmall来自60f就继承接受。

本次未处理正在并行验证的e139标量路线；未派发网页任务、子agent、Git或CI，也未本地安装/运行大型Linux工具链。
