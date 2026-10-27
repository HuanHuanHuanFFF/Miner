# CI16补充：机器边已闭合，park精确6a0c

**不建议再投原完整D，也不提出新变体。** 150原件SHA核过；源6a0c、Submission C e43e059e、MainFull C94f69ed1及对象d9f3358e均与CI14相同，沿用已核C/两模块/14根，不重做。D17冻结物未读取或修改。

真实pair caller在`0x194`的PLT relocation直接调用`R19DCRawPair.loop`一次，`0x1c5`调用emit/spec0，两列共读同一F2；没有拿导出helper替代caller，也没有被clang复制出另一hot体。新loop三处call relocation均为原`lean_float32_of_bits`；旧NativeFinal.dotLoop两处同目标。odd分支`0x253`转spec1，仍一个旧dot；n≤1/p≤1和原DC外层guard沿CI14不变。

按合法范围内、小Nat、k>0的**同两列工作**比较，另存k=0捷径，不用一条新pair对一条旧dot：

| native热工作 | 两次旧dotLoop | 一次新pair loop |
|---|---:|---:|
| codec外调/每k | 4 | 3 |
| 浮点栈mov/每k | 8条×4B | 6条×16B |
| 浮点栈读写字节/每k | 32B | 96B |
| 条件分支/steady k | 38 | 26 |
| 其他显式栈访问/steady k | 16 | 11 |
| 单次栈框架 | 88B+6push，顺序两次 | 168B+6push，一次 |

共享A/k*p、一个计数流、较少分支/整数栈访问，以及小Nat的baseB+1在prologue预计算，都是实际优势。新两lane mulps/addps代替两条scalar链的对应操作，源级原顺序不变。上述call、分支、指令或字节均**不是速度模型**；16B stack access不等于4B的4倍延迟，旧栈也不能将两次88B相加冒充同时峰值。

新每pair终态还真实调用`lean_inc_heartbeat`及`mi_malloc_small(16)`，存入两个Float32；emit后实际caller的RC路径调用`lean_dec_ref_cold`。旧dotLoop直接返Float32，无F2分配。这些是一次固定成本，不能乘成每k；n=2时也不能忽略。保留的finish/输出box/NaN回放不算删除。比较已覆盖新完整caller关键边和两旧loop热体；旧完整NativeFinal.dot/finish native未补采，不声称建立完整延迟模型或测得净回归。

新增证据关闭了CI14的helper/caller及call目标未知，但不支持所需的大幅局部节省：少25% codec调用伴随更宽的栈保存、较大峰值框架和新终态生命周期。既有作用域约5.98%whole，whole3%约需完整局部省50.18%；当前没有足够依据为此抢完整D。**这是投入决定，不是必慢证明或速度上界。** 无计时、成功概率、原gate/采用结论。

原件、relocation、首次k=0和steady路径、完整计数与精确hash在`review.json`、`equal-work-native.json`、`all-originals.json`及`receipt.json`；三段原ASM摘录分别为old-dot/new-pair/actual-pair-caller。未Git/CI/本机Lean，未改旧审计、候选、全局或Harness。
