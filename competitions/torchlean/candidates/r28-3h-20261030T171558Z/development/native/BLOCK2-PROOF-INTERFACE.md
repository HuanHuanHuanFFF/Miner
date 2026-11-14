# Source36 分块2的证明边界

当前成本原型 `b5c20fde/253202B` **UNPROVED_NATIVE_RESEARCH_ONLY**，无新 `Submission.correct`，不继承原完整gate。它只改 `MVj` 分发、增加 `R28MD2B2`，所有原输入准备、GEMM、回退、最终bias和round保持。先量整模型，再为实际收益买完整证明。

与R27负结果不同：新起点是36的dense Array Nat + 双行128位循环，不是23的P/I四行稀疏调度；本轮按实际bias-inclusive span<=14合并2项，保留原MD2窄外/尾部，而非固定16项入口。R27单batch小收益、全batch退化仍是投入风险，不作已排除。

已买判别证据：`BLOCK2-PAIR-MODEL.json`以9个旧完整Mixer公式回放，4490条行累加器与原逐项native word128相同；110582/180132逻辑linear MAC进入新分支。不是速度、全输入证明或新可采用候选。

关键代数界面 `WordPairMerge2.lean.inc`：当两个signed64项之和仍在[-2^63,2^63)时，两次128位sign/carry更新等于合并其UInt64和后更新一次；依赖源36 `Z128`。未编译。`PAIR-MERGE2-MODEL.json`保留了去掉范围条件的7588个反例计数，不能把等式无条件化。

若原生成本达标，最小完整路线：

1. 在源36 `ZL15` 同一接口证明 `R28L14`：span<=14给每项绝对值<2^62。用 `Zpt` 与signed64唯一表示将其绑定真实cache产品；分块2之和严格落在signed64。
2. 增加scalar `MDblock2`，证明在真实cache/magnitude前提下 `MDblock2=MD`；保留原MD尾和原YL/bias/round。缓存正确性来自原 `ZMaU` 的hx/hw，不可仅凭metadata假设任意arrays正确。
3. paired结构引理先把 `R28MD2B2` 与两条scalar block计算联系；替换 `MaU` 的窄域call后，`ZMVs`处理both-narrow及mixed分支，恢复 `ZMVj/ZMVi/ZMV0`。这个层次避免在generic `ZMVs` 对任意XP/WP直接假设cache正确。
4. 精确256000B内重建全12证明，原statement/kernel/axioms gate、完整Mixer计时及冻结新runner确认。独立helper/有限模型/原source36证明均不填补这些缺口。

成本与资源：本机只有轻量Python/源码，模型各<1秒；无本机Lean/native，无本角色CI。token/cache UNKNOWN。原型准备、proof工程和等待均计入17:15:58–20:15:58窗口；不加新队列挤占近榜和最终确认。
