# R7检查点07：NaN后缀完整PASS，原生前缀修复稿就绪

2026-10-22 19:48 UTC。R独立回收读取806实际artifact，9a2 NaN-fullpath完整PASS，来源 `39839349846/download-ebea3aedaed046f19fe9a034758012cf/diagnostics/f01-d7-public-suite/public-suite/`。

`nan-first-full-806.json`核验精确本地/保存Kernel SHA、原verdict哈希、原版public-v2 SHA、25配对轮、26cell实际work、完整重放、三公理与前后fingerprint。CPU AMD EPYC7763。同机同计划相对8eb：整包raw0.80633656，按reference归一化0.80670725；BMM归一化0.65188410；add0.99857791、mul0.99855509、sum0.99285027。这里是发现样本，不是冻结后独立确认，也非现任冠军/私有suite结果。

两个独立组件已通过：c760非NaN终点与9a2 quiet后缀。**优先待测精确组合仍为b1696ff9**（上一检查点；尚未编译完整组合），由D与direct-small等布局合成/验收。7ac原始字quiet守卫仍为单一受控变体，等待实际比较。

## 下一实质机制 ee309626

`f01-r7-native-repair/Kernel.lean`，SHA256 `ee309626cd64c601242497f36e67c6b38376f4964ebc2686d7e2cf6126e0c6f0`，176296字节，父本b1696ff9，**NOT_RUN_NEW_MECHANISM**。静态哈希/导入/禁词/大小检查PASS，不代表Lean接受。

用途仅NaN终点回退：原来的native第一遍不变；第二遍的非NaN前缀用Float32保持累加器，在第一次native NaN事件从上一精确非NaN累加器与当前原始A/B执行一个已证明的原始字步骤。若repair为quiet NaN，则使用806已接受的全输入乘积quiet/后缀吸收证明直接返回；若不是quiet，则原样跑剩余精确Fin.foldl.loop。没有把这个冷分支假设为不可能。

新具体证明`nativeStep_eq`由已接受NotNaNProbe.add_inputs/mul_inputs、R7Native.ofFloat32Add/Mul及原始字roundtrip推导；`nativeReplayLoop_eq`按n-k递归与真实原始fold一致。入口`nativeReplay_eq`保持+0，集成点为R7NaNReplay.replayEarly，NativeFinal.dot/Packed10.finish都沿原完整定理接通。没有List索引分配，没有FMA或顺序调整，普通finite路径无新增逐步守卫。

D可把该稿作为b169组合后的独立候选验证；若槽有限，先组合已有两个PASS组件。最小证伪是固定Lean编译`nativeStep_eq`/递归fold桥，然后原版完整gate与b169配对全部成本，不只统计少调用的software add/mul。若编译失败按精确错误修新命名源，保留ee309626。有限字模型与公开计划机会计数均不是性能证据。

W03网页仍在研究完整sum的last-sNaN规则；R没有阻塞等待，也不重复D的标量特殊值实现或阶段profile。完整窗口、资源与最终冻结时点不变。

## 19:52 UTC补充：求和对应机制与公开机会计数

`f01-r7-sum-native-repair/Kernel.lean`，SHA256 `627c31a8292c13be690b06c0f74b2482f357b281be8e4242bedfe9d84016f6b5`，188277字节，父本仍为b169，**NOT_RUN_NEW_MECHANISM**。只修改NaN终点的sum回退，独立于ee矩阵稿；原有USize第一遍、BMM与标量不变。第二遍非NaN前缀用已接受桥保持native，首次NaN处做一次精确原始加法；建立真实qQuiet后使用W02纯原始字step扫描所有剩余输入，后来的sNaN仍覆盖符号/payload。若quiet检查不通过，保留完整精确冷后缀。Nat循环直接读原Vector，无List构造。W02只取Raw/Step部分，不带未用List适配器；新递归证明完整接到原sumSpec。

新增有限整数模型6369序列通过，包括边界全三元组与长随机序列；2735个last-sNaN命中与真实源码转录fold一致。这不是Lean/硬件验证或收益结果。最终源码仍需固定Lean编译与完整gate。

`public-nonfinite-opportunity-805.json`对已经公开的发现计划805全部34个sum、34个BMM计时case做源码转录计数。生成器实际源2f167273经Git blob校验，计划原字节SHA2db46ccb；没有改基准或窥探未来冻结确认计划。

该有限模型中，sum有1180个NaN结果，其旧精确回放共8819步；native前缀4022步（含1180个事件步骤），后缀4797字。581个输出含sNaN，反向扫描全部NaN输出需读6697字；单独last-sNaN捷径不明显优于native修复加线性后缀，暂不立即增加另一个近似候选。BMM有1322个NaN结果，旧精确回放16980个乘加步，早停后保留9103个前缀步；ee可以把其中非事件前缀转为native，留1322个精确事件修复。这里的原始步数并非实际时间或私有suite比例；特殊soft步骤与普通native步骤单价差别很大，不能按全体输出数量占比推断收益。

建议顺序：精确已有组件组合b169优先；ee矩阵prefix与627求和prefix分别相对b169完整对照，7ac守卫仅作一次受控比较。由D统一槽位和最终组合，R不派发额外CI。
