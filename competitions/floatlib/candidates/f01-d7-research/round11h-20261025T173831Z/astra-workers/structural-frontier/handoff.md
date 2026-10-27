# R17 结构路线阶段交接

决定：不为当前两条结构路线排完整计时；保留可复核核心，主控可将连续投入留给数值桥。没有当前10%整包收益依据。目录内唯一状态入口为status.json；全部原始来源与精确成本在audit.json。

- **固定接口已重新核实。** 从Lean293d5d0c精确取回FloatArray/Basic、Float/Float32、ByteArray/Basic原文。FloatArray连续存double；两个跨宽cast依然opaque。已存在的合法checked FloatArray需逐值raw往返检查，旧5be0735a全gate不等于当前public-v2收益。本轮没有据旧“opaque gap”标签跳过实源。详细比较见direction.md。
- **不同机制的实物。** TemporalCore.lean按连续4个k将8个Float32字段打入一记录，保留2输出累加器、相同逐步乘加、0–3项真实尾段。不是重开A4/4×10/只n1守卫；无A panel或tiles。OrderedBlocks.lean提供任意状态、任意step的分块有序归约等价证明尝试，尚未Lean检查。
- **可交D的精确接口探针。** Probe-temporal-interface.lean：231882B，SHA7da3ef64d2418141525178f99e8f6a96c99d434590629b8aaf9a1ac7041f072c。前226829B逐字等于622d保留版，原四公开入口不变。原固定intake/policy/options均通过；16个新增helper须显式重放/依赖审计，原四spec不能替代它。不是参测性能候选。
- **实际检查。** 5秒外部timeout内完成固定源/原C/哈希核对及201960输出通道、3332340有序MAC地址对的有限模型，约1.5–1.8秒。模型无索引/顺序差异；未本机Lean、未编译、未CI、未读取当前确认数据。
- **完整成本界。** B2每4个k的记录+槽位请求96→48B；F10对应224→176B。仍保留每k原始A解码、数值MAC、raw finish/replay；不能宣称消除ofBits调用/spill。当前全部BMM仅占整包16.14%/20.02%/19.06%，10%整包需删除其中61.95%/49.94%/52.47%。条件内存量不支持该时间结论。
- **下一决定。** 若以后取得当前保留版准备/allocator/指针工作占BMM主导的实测，再先检查这份核心的实际C是否真少对象，再接原B2循环/Prefix证明并测完整成本。否则停放；不以新种子、仅布局字节或旧A4负结果作收益依据。core-interface.md列了确切未闭合接线。

本阶段提前交付，不填满19:08:31配额；tokens/cache UNKNOWN，CI占用0。没有修改他人文件、Git/index、官方文件或全局状态。
