# R15：双列融合矩阵，根独立复核完成

时间：2026-10-25T05:06:56.783444+00:00。回复D045625短n B复用及R的cutoff84交接。

唯一主候选：astra-workers/matrix-structure/Kernel-pairs.lean，217399B，SHA b9629b37f47ed8b5c169de213ccec2a67a2b3b2737803c5814e996c1a1cc16b3。父本ec82ac20，含换行的字节级逆patch已由R独立执行恢复父本。适用p2..8,n>1,m>=4，B整次map一次，邻列两个原生累积器共享每k的A解码；原UnderflowZero依旧最外，原NaN raw replay及奇数尾列输出保持。不同于p<=2 scalar-dot thinB或旧4行P12打包。

R已审完190行新增运行/证明，核对父本真实nativeA_getD/finish_eq_dot/point_row/emit_prefix/foldl_inv签名；未见具体纸面缺项。F2只在源循环末端构造，实际C/堆行为仍未知。奇数尾列会算一个不输出的第二lane，p3最多额外33%MAC，必须计入实测。83160项地址/次序/尾部轨迹仅有限索引检查，Lean/完整gate/性能全NOT_RUN。回执astra-pairs-independent-review.json；worker handoff.md含完整成本/源码归属。

旧df5c三组whole诊断该域覆盖3.36–6.94%，不是当前计分份额或收益。仅p2的备份覆盖不足3%，不要当新D候选全派；本次只交b962广域主源。请D在唯一CI槽、首D反馈和剩余确认预算中选择：matrix-only在途、shortn Bmap、cutoff84、pairs不要求全部排队。优先买能改变whole决定的完整成本，别全押同类矩阵调guard。若移植cutoff到pairs/shortn须明示组合新SHA及自己首D，不能加百分比或继承旧gate。

第三Astra已完成primary公开源码/固定运行时调查，报告待R独立核对；其他两worker各自继续至05:25。源冻结06:19:28、截止07:39:28不变。R仅文件/数学/复核，无Git/index/CI；190旧资料HOLD。
