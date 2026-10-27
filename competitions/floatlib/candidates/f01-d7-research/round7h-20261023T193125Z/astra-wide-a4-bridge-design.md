# A4 的条件接线：避免两份全 A 准备

00:05 UTC 前的源结构推导，**不是新候选、未编译、未计时**。当前实际候选仍为冻结 43aaf31f。D 正在安排独立四值 A 记录探针；本文件只给后续 GO 时的整体成本和形式接口，不预设探针成功。

921 已见 global Array Float32 热读取为四次对象指针、四次 Float32 字段再拼向量。F4 四字段记录有机会让同 k 四行连续读取，且减少准备阶段对象；真实收益依赖完整打包、输出、尾部和引用计数。绝不能只把 wordLoop 的 A 参数改为 F4 就宣称整矩阵消除了旧 nativeA。

## 先处理尾行成本

当前 43aa 的完整块共享 global nativeA / F10 B，尾行调用旧 RowStream.row。如果后续完整块改用 A4、尾行仍要求整份 global nativeA，这就引入两份全 A 准备。按 shape 先判 m%4=0 可以避免某些重复，但会把路线变成新的形状门槛；本文件没有提出这种未测筛选或生成候选。

一个统一替代是按 batch 内 ceil(m/4) 个行块打包 A4，最后块不足四行的位置明确填 native +0。最后块仍计算四十条独立链，只发出真正存在的行/列。最多增加每 batch 三行的计算；无效行的 Inf/NaN 运算不得触发 finish 回放或写出结果。保留当前最外层 UnderflowZero 的优先级。比较量必须包括新增无效行计算，与保留旧数组/单独尾部准备的真实成本。

另一种是只给尾部单独准备紧凑 Float32 数组，然后让尾行算术地址和 raw NaN 回放地址分离。当前 Packed10.finish_dot10_lane 的复用路径绑定整份 raw A 的 map，不能仅改下标假装已经证明；需要新的地址映射桥。该方案没有现成完整证明，不可把它当零成本接线。

## 四值包的精确逻辑关系

固定 b、行块 h、r:Fin4、k:Finn。有效行条件为 `4*h+r<m`。F4 的第 r 个字段必须满足

`laneA (packA[b][h][k]) r = toFloat32 (A.getD ((b*m+4*h+r)*n+k) posZero)`。

完整块不需原全 nativeA。无效行可以填 +0，但不要求它与跨到下一 batch 的 raw getD 相等：证明只对当前 batch 的有效行使用该等式，最后输出循环也只接受有效行。不能套用“虚拟行按全局 getD 自然为零”，因为该地址可能进入下一 batch。

对于每个有效 r，先证明 F4 版循环的 projectRow 等于当前旧 `Packed10.dot10` 在 `(b*m+4*h+r)*n`、真实 `A.toArray.map toFloat32`、同一个已存在 F10 B tile 上的结果。递归一步仅使用上面的 packA 字段等式，B 字段与算术顺序完全不变；+0 初值和 native Float32 运算不引入新转换往返假设。该证明可以复用已通过的 40 参数投影结构，但原 afd8 定理针对四个 Array A.uget，不能不改前提就直接重用。

F4/F10 都是长度 n 的向量，机器循环只需同一个 k<count 的向量界，n<USize.size 保证递增。这会移除当前四个 A 地址的 machine-span 前提；外层原始地址仍是 Nat，不能把乘积截断为 USize。若 n 不满足界则须保留正确的旧完整路径或证明 Nat 版新循环。

## 输出证明必须同步收窄

当前 Projects 要求四个 r 全部映射正确；尾块需要改为带 `4*h+r<m` 的有效行前提。emitBlock 的固定四行也须改为 `min 4 (m-4*h)` 行，其前缀端点为 `min (4*(h+1)) m`，最后才等于 m。每个有效标量仍通过同一个 Packed10.finish 和真实 raw A/B 地址闭合到 RowStream.point、referenceBmm 与原 bmmSpec。若新候选继续保留原 Projects / hblock:first+4≤m，却把不足四行也送入它，就是未闭合的证明接口。

所需可证伪检查：真实 BMM 不再调用完整 A.toArray.map；每块 F4/F40 构造只发生一次；旧 nativeA 未被隐藏保留给尾部；无效行只产生独立额外 MAC，不 finish；循环实际读取和寄存器分配与探针一致。只有这些成立后，完整 gate 和配对整次计时才可评价此方向。
