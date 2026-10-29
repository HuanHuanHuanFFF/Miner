# 40774570580：实际四caller复核通过，停放精确GRS体

源**08a0208e…／229522B**，commit`6f57a6ad59fa967db4d8c5f06afed7954ce4fec1`；AMD EPYC9V45。`review-407745.py`复用固定`inventory_callbacks.py`和static runner审计及原R13 row parser，独立重hash **148原件／16834295B**，24日志/计划/156行/152计时/checksum/ABBA及全部比值复算一致。详细`actual407745-review.json`；所有慢样本保留。

实际Main C为**c339fa7d…／224073B**；compile/link/.rsp只做原root/target路径映射后三者完全相同。4个World-only IO runner各自静态闭包arity2/fixed0，ADD→boxed→typed链明确；没有捕获Bool或每调用重建table。SUM/BMM选择同一函数；MUL由同一Submission.mul生成不同lambda副本，C文本非逐字相同，不能将其他op计时漂移当成实现收益。

| 实际选中ADD | C/ASM中的不同工作 | ASM全函数指令数，非cycles |
|---|---|---:|
| B2 control | 原F32表/低值ofBits/结果守卫/冷Model分支；3个callee-save push＋16B frame |130|
| FloatArray＋GRS | 两次连续double getter、两次数值cast/mul、一次F64 ADD；同宽toBits后整数GRS。1个rax push，toBits为普通call；非finite tail-jump B2 |83|
| boxed Array Float＋GRS | 2次unbox_float、额外generic array/panic路径、4个callee-save push＋24B frame；相同GRS |133|
| FloatArray＋opaque cast | 相同数值解码；actual cvtsd2ss，随后tail-jump float32_to_bits；无push/frame/call。两份静态返回路径各有一条cvtsd2ss，不是一次执行两遍 |48|

legal两体C明确只有`lean_float_to_bits`，没有opaque Float.toFloat32；cast体才有后者。FloatArray getter已内联成连续load/边界检查，nativeScales在Submission初始化时构造（原C有push/empty调用）；四个typed ADD中均无table allocation/push/init。Wrapper均2 unbox_uint32＋2 dec＋1 box_uint32；64位UInt32为immediate，不能把它说成每次heap分配。新Main object/binary原字节未导出；其identity按remote receipt绑定，不能声称本地重算ELF。

**四块结果**：FloatArray＋GRS ADD/B2=`1.04887,1.06412,1.06517,1.07735`；whole=`1.00664,1.00818,1.01943,1.04374`。Boxed更慢。cast ADD=`.84623,.89310,.83989,.88087`，whole=`.91713,.94498,.93416,.95230`，但它不具备准入语义桥，且非ADD计时有漂移。

结论：测量链没有wrong callback、改flags、captured参数或每调用重建表的问题。当前合法word缩窄的额外工作确实在实际路径上，完整成本未达收益；**停放精确08a，不改小参数/追seed/补大证明**。这不否定所有F64表示或同宽toBits工具；后续滤波证书可以复用native猜值，但必须由精确检查保障原题结果，另测其完整路径。

审计器首版把`unbox_float32`误归为allocator，已改为精确匹配box/alloc后完成同一批原件复核；这不改变原候选、回执或负结果。原4public spec仍B2；新helper数学/完整gate/正式成绩均未通过或未运行，无新采用。
