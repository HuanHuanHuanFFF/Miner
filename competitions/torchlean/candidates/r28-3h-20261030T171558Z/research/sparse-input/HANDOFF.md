# R主控隔离新路线
source-level目标覆盖先完成：近榜cnn/mnet的dot均relu=false，直接ReLU符号证书暂停。父后续提出pointwise输入支撑CSR：新public53 narrow完整span31允许56位偏置factor+7位index打包到63bit smallNat，升序删零fold保持原UInt64四累加器逐字一致，复用bias/零fallback。详SPARSE-INPUT-CSR.md；csr63_model.py已100298 pack/decode、1100 arbitraryUInt64 fold有限检查；Lean abstract bridge未编译，实际Kernel/计时未实现，不占CI。
旧已见Mobile18cell操作计数表明pointwise占conv逻辑MAC28.28%，目标零项占全部非零weightMAC12.0—12.9%；它不是整模时间上界或收益。若逐项skip实际branch负，可用这条减少不可预测分支的布局路线；prep/指针/weight-sparse交集是关键成本，不重复声称打包就是收益。
父另对A空间Winograd给出保守block8 signed64范围及scale4恢复/bias接口，见requests/1746-winograd-block8-bound.md，等A关键反证；不与B/C现有独立机制抢写。
