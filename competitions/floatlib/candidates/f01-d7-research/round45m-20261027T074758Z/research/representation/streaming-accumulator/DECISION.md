# 后继表示前提：安全Array.modify使流式Cell复用成为可检验假设

此方向独立于已冻结b6b7，不新增CI或公共BMM源。固定Lean4.34/293d5d0c的`Array.Basic.lean`，75780B/SHA85b1fcc2eac430164656c02295d9cf5d3549826517a2a89083a7afae28b1e4f2，Git blob7d58dee5983aa201468b99df02a6d8c18c7a1794，已按原字节校验；完整头部版权与Apache2许可保留。母路径`research/source-intake/lean-runtime-293d5d0c`也有主控核过的同字节源与LICENSE。

关键原文L489–495：先取`xs[i]`，把槽替为`box(0)`，再调用更新函数，再写回。完整限定语是 **“This ensures that `v` remains unshared if possible.”** 安全API链为L544 `Array.modify`→L526 `modifyM`→固定运行后端；候选只调用公开safe API，不复制或新增上游底层实现、替换属性或编译器。

**可改变决定的前提**：一份新建、单一所有者的`Array<F2>`若各Cell也无其他别名，槽的旧引用先移走，结构更新就有机会复用Cell。此前简单`get; set`时旧槽仍持有Cell，不能默认同样无分配。**这不保证实际CtorReuse、零closure、零copy、零alloc**：候选的真实selected C必须证明这些；本轮没有运行这个接口。

`SafeState.lean.inc`只给普通`Array.modify`+record update、两字段rfl等式、size及pointwise get?证明尝试、单个k的双行更新`advance`和`Represents`状态投影。精确2265B/SHA67336d6fafeba957da66556b0de8303c5ff10354318f01bf35e5699cf7d0dd13，NOT_RUN。`Array.getElem?_modify`按固定Lemmas L4011–4014实际binder对齐，未声称Lean通过。

`Represents`要求每列Cell.s0/s1分别等于两行从0累加到k的原`NativeFinal.dotLoop k ...`，所以拟议outer-k/inner-column仅交织独立输出，各点积k序与每一步Float32加乘不变。最终必须继续用原`Packed10.finish`及原raw输入做NaN回放，先输出完整row0再row1；不能直接改ofFloat32。需补initial、advance保持、prefix-snoc及完整batch/奇行/输出投影证明。两行必须属于同batch，不能跨batch共享Bbase。

## 完整成本分列（数量不是速度）

以同batch两行、p列、n项为单位；只比较原DC类未打包路径，**不把同一codec计数用于B2/Packed10已经缓存B的路径**。

| 工作 | 两行原独立DC dot | 逐行rawpair列配对（p偶数） | 双行流式状态提案 |
|---|---:|---:|---:|
| A/B原codec调用 | 4np | 3np | n(p+2)：A两次/k，B一次/列/k |
| 每条输出的mul/add | 2np / 2np | 2np / 2np | 2np / 2np，不加phantom MAC |
| 全局B pack及其析构 | 无 | 无 | 无；不能对此声称额外删除 |
| 中间状态容量 | 单dot寄存器 | 一pair寄存器/终态F2 | p个F2槽，跨k持久 |

| 新增/保留成本 | 必须计入 |
|---|---|
| initial=Array.replicate p zeroCell | 所有槽共享同一Cell，可能是persistent常量；**不是p个独占Cell**。第一有效k通常需逐槽新造Cell，不能声称从首轮零分配。只有随后无其他别名时复用才可能成立。 |
| 每次slot更新 | 固定后端有两次槽替换，元素RC、数组独占/COW处理、边界/索引转换与Cell复用检查均有成本；编译器是否消掉部分物理store/check未知，不能把源站点数当最终机器次数。 |
| 每k状态Array变更 | p次modify，跨列closure捕获两个Float32与B索引；没有源级state别名捕获，但真实闭包消除/借用/RC仍待C，不能称closure0。 |
| 原输入读取及活跃状态 | 两A值需跨列使用，B每k连续读；额外活跃寄存器和FPspill可抵销codec减少。未移除原of_bits单调用本身。 |
| finalize | 读取每个Cell两lane，原finish/所有NaN重放，2p次输出push，最终p个F2及状态Array析构；Binary32在64位为即时值，不计成2p堆对象。 |
| 奇行、p/n0和n1 | odd行需原路径；零维度需完整入口处理；n1没有steady复用可摊销，不能继承旧n1cache的收益。 |

`updateCell`只保留一个被消费的Cell，两个字段先读后写；`advance`的折叠状态参数未被其闭包捕获。这支持进行未来一份所有权/CtorReuse判别，但不是已证明实际独占。输入A/B仍只读；状态数组新分配，不能尝试原位修改用户共享输入。

**最小下一判别**：未来仅编译一个实际消费独占state的完整两行/单k循环caller，保留初始化、两槽写和finalize；检查是否先挪槽引用、Cell复用路径是否在steady有效、是否出现每slot构造/closure/apply/Array复制、spill是否扩大。如果仍每更新分配Cell或closure，停止该表示前提；如果复用确立，再买完整DC路径成本及原序证明。当前不选域阈值、不组完整Kernel、不声称10%whole可达。B2-only旧样本4–6%上限没有被当作全域结论。
